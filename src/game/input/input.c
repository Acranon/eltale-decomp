#include "game/input/input.h"

/*
 * Controller polling and Controller Pak file discovery and operations.
 * Original file: 363B0.c (ROM 0x363B0).
 */

/* .bss 80092C80..80092ED0 */
s8 input_primary_port;
s8 input_stick_x;
s8 input_stick_y;
u16 input_held_buttons;
u16 input_pressed_buttons; /* button down edges for the selected controller */
u16 input_previous_button_inverse;
OSMesgQueue input_si_queue;
OSPfs pak_port_states[4];
PakFileScan pak_game_file_scans[4];
u8 input_connected_port_bits;
OSContStatus input_controller_statuses[4];
OSMesg input_si_mesg;
OSContPad input_pad_states[4];
/* This file's .data, 80061810..80061850: the pak file's game_name, an
 * unreferenced digit string, and the two ext_name values. */
u8 pak_game_name[16] = "SxbQx";
char D_80061820[] = "012345678901234567890123456789";
PakExtName pak_allocate_extension_template = { { 0, 0, 0, 0 } };
PakExtName pak_delete_extension_template = { { 0, 0, 0, 0 } };

s32 osContInit();
s32 osPfsFreeBlocks();
s32 func_8003D554();
s32 func_8003D6B0();
s32 func_8003D0F0();
s32 osPfsRepairId();
s32 func_8003EDC0();
s32 osPfsFileState();
s32 osPfsFreeBlocks();

s32 Input_InitControllers(void) {
    s32 pad[2];
    s32 ret = 0;
    s32 count;
    s32 i;

    input_previous_button_inverse = 0;
    for (i = 0; i < 4; i++) {
        pak_game_file_scans[i].unk12 = -0x80;
    }
    for (i = 0; i < 4; i++) {
        input_pad_states[i].button = 0;
        input_pad_states[i].stick_x = 0;
        input_pad_states[i].stick_y = 0;
    }
    osCreateMesgQueue(&input_si_queue, &input_si_mesg, 1);
    osSetEventMesg(OS_EVENT_SI, &input_si_queue, &input_si_mesg);
    osContInit(&input_si_queue, &input_connected_port_bits, input_controller_statuses);
    osContSetCh(4);
    input_primary_port = -1;
    count = 0;
    for (i = 0; i != 4; i++) {
        if (input_connected_port_bits & (1 << i)) {
            if (input_controller_statuses[i].errno & 4) {
                pak_game_file_scans[i].unk12 = -1;
            } else if (input_controller_statuses[i].type & 2) {
                pak_game_file_scans[i].unk12 = -2;
            } else {
                pak_game_file_scans[i].unk12 = 0;
                count++;
                if (input_primary_port == -1) {
                    input_primary_port = i;
                }
                if (input_controller_statuses[i].status & 1) {
                    pak_game_file_scans[i].unk0 |= 0x8000;
                } else {
                    pak_game_file_scans[i].unk0 = 0;
                    if (i == input_primary_port) {
                        ret = 1;
                    }
                }
            }
        } else {
            pak_game_file_scans[i].unk12 = -3;
        }
    }
    if (count == 0) {
        return -1;
    }
    return ret;
}

void Input_ReadController(s32 cont) {
    OSContPad *pad;
    u16 button;

    osContSetCh(4);
    osContStartReadData(&input_si_queue);
    if (osRecvMesg(&input_si_queue, NULL, 1) != -1) {
        osContGetReadData(input_pad_states);
    }
    pad = &input_pad_states[cont];
    button = pad->button;
    input_held_buttons = button;
    input_stick_x = pad->stick_x;
    input_stick_y = pad->stick_y;
    input_pressed_buttons = button & input_previous_button_inverse;
    input_previous_button_inverse = ~button;
}

s32 Pak_ScanGameFiles(s32 cont) {
    s32 i;
    s32 pad1;
    OSPfs *pfs;
    s32 err;
    s32 found;
    s32 cnt;
    s32 pad2[3];
    OSPfsState st;

    found = 0;
    cnt = 0;
    pak_game_file_scans[cont].unk13 = 0xFF;
    pak_game_file_scans[cont].unk0 = 0;
    for (i = 0; i < 16; i++) {
        pak_game_file_scans[cont].unk2[i] = -1;
    }
    pfs = &pak_port_states[cont];
    err = func_8003D0F0(&input_si_queue, pfs, cont);
    if (err != 0) {
        if (err == 10) {
            if (func_8003D554(&input_si_queue, pfs, cont) == 0) {
                return 1;
            }
            if (func_8003D6B0(&input_si_queue, pfs, cont) == 0) {
                return 1;
            }
            err = 10;
        }
        return err;
    }
    for (i = 0; i < 16; i++) {
        err = osPfsFileState(pfs, i, &st);
        if (err == 0) {
            if (st.game_code == 0x4E45544A && st.company_code == 0x3943) {
                if (Pak_CompareNameBytes(pak_game_name, st.game_name, 16) == 0) {
                    found++;
                    pak_game_file_scans[cont].unk2[i] = ((u8 *) st.ext_name)[0];
                    pak_game_file_scans[cont].unk0 |= 0x4000;
                } else {
                    pak_game_file_scans[cont].unk2[i] = 0x7F;
                }
            } else {
                pak_game_file_scans[cont].unk2[i] = 0x7F;
            }
            cnt++;
        } else if (err == 5) {
            pak_game_file_scans[cont].unk2[i] = -1;
            err = 0;
        } else {
            break;
        }
    }
    if (err == 0) {
        pak_game_file_scans[cont].unk0 &= 0xFFF0;
        pak_game_file_scans[cont].unk0 |= found;
        if (found >= 16) {
            pak_game_file_scans[cont].unk0 |= 0x2000;
        }
        if (cnt >= 16) {
            pak_game_file_scans[cont].unk0 |= 0x2000;
        }
        osPfsFreeBlocks(pfs, &i);
        i = i / 256;
        pak_game_file_scans[cont].unk13 = i;
        if (i < 2) {
            pak_game_file_scans[cont].unk0 |= 0x2000;
        }
    }
    return err;
}

u8 func_80035CC8(s32 arg0) {
    s32 i;
    s32 j;
    s32 k = arg0;

    i = -1;
    do {
        i++;
        j = 0;
        arg0 = 0;
        for (; j < 16; j++) {
            if (i + 0x1A == pak_game_file_scans[k].unk2[j]) {
                arg0 = -1;
                break;
            }
        }
        if (i >= 16 && arg0) {
            arg0 = -1;
            break;
        }
    } while (arg0 == 0);
    if (arg0 == 0) {
        arg0 = i + 0x1A;
    }
    return arg0;
}

u8 Pak_AllocateGameFile(s32 arg0, u8 arg1) {
    u8 unused[4];
    s32 file_no;
    PakExtName ext;
    s32 ret;

    ext = pak_allocate_extension_template;
    file_no = -1;
    ext.b[0] = arg1;
    ret = osPfsAllocateFile(&pak_port_states[arg0], 0x3943, 0x4E45544A, pak_game_name, &ext, 0x200, &file_no);
    if (ret == 0) {
        ret = file_no;
        pak_game_file_scans[arg0].unk2[ret] = arg1;
    } else {
        ret = -ret;
    }
    return ret;
}

u8 Pak_DeleteGameFile(s32 arg0, u8 arg1) {
    u8 unused[4];
    PakExtName ext;

    ext = pak_delete_extension_template;
    ext.b[0] = arg1;
    return osPfsDeleteFile(&pak_port_states[arg0], 0x3943, 0x4E45544A, pak_game_name, &ext);
}

void Pak_ReadFile(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    osPfsReadWriteFile(&pak_port_states[arg0], file_no, 0, offset, nbytes, buf);
}

s32 Pak_WriteFile(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    s32 ret;
    s32 bytes;

    ret = osPfsFreeBlocks(&pak_port_states[arg0], &bytes);
    if (ret != 0) {
        return ret;
    }
    return osPfsReadWriteFile(&pak_port_states[arg0], file_no, 1, offset, nbytes, buf);
}

s32 Pak_TryRepair(s32 arg0, s32 arg1) {
    s32 err;
    s32 cont = input_primary_port;

    if (arg1 == 10) {
        if (func_8003D554(&input_si_queue, &pak_port_states[cont], cont) != 0) {
            if (func_8003D6B0(&input_si_queue, &pak_port_states[cont], cont) != 0) {
                err = func_8003D0F0(&input_si_queue, &pak_port_states[cont], cont);
                if (err != 11 && err != 1 && err != 2) {
                    err = osPfsRepairId(&pak_port_states[cont]);
                }
            } else {
                err = 4;
            }
        } else {
            err = 4;
        }
    } else {
        err = func_8003D0F0(&input_si_queue, &pak_port_states[cont], cont);
    }
    return err;
}

s32 Pak_ClassifyError(s32 arg0) {
    s32 ret;

    switch (arg0) {
        case 1:
            ret = -1;
            break;
        case 4:
        case 11:
            ret = -2;
            break;
        case 3:
        case 10:
            ret = -3;
            break;
        case 2:
            ret = -4;
            break;
        case 9:
            ret = -5;
            break;
        default:
            ret = -6;
            break;
    }
    return ret;
}

s32 Pak_CompareNameBytes(u8 *a, u8 *b, s32 n) {
    do {
        if (*a++ != *b++) {
            break;
        }
    } while (n--);
    return n;
}

void func_80036124(void) {
    func_8003EDC0();
}

void Input_StartControllerQuery(OSMesgQueue *mq) {
    osContStartQuery(mq);
}

void Input_GetControllerQuery(OSContStatus *status) {
    osContGetQuery(status);
}

void func_80036184(void) {
    func_8003D6B0();
}
