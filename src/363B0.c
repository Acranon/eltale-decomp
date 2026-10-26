#include "common.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2[16];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 unk13;
} Unk80092E48; /* size = 0x14 */

typedef struct {
    u8 b[4];

} Ext4;

extern s8 D_80092C80;
extern s8 D_80092C81;
extern s8 D_80092C82;
extern u16 D_80092C84;
extern u16 D_80092C86;
extern u16 D_80092C88;
extern OSMesgQueue D_80092C90;
extern OSPfs D_80092CA8[4];
extern Unk80092E48 D_80092E48[4];
extern u8 D_80092E98;
extern OSContStatus D_80092EA0[4];
extern OSMesg D_80092EB0;
extern OSContPad D_80092EB8[4];
/* This file's .data, 80061810..80061850: the pak file's game_name, an
 * unreferenced digit string, and the two ext_name values. */
u8 D_80061810[16] = "SxbQx";
char D_80061820[] = "012345678901234567890123456789";
Ext4 D_80061840 = { { 0, 0, 0, 0 } };
Ext4 D_80061844 = { { 0, 0, 0, 0 } };

s32 osContInit();
s32 osPfsFreeBlocks();
s32 func_8003D554();
s32 func_8003D6B0();
s32 func_8003D0F0();
s32 osPfsRepairId();
s32 func_8003EDC0();
s32 osPfsFileState();
s32 func_800360F8();
s32 osPfsFreeBlocks();

s32 func_800357B0(void) {
    s32 pad[2];
    s32 ret = 0;
    s32 count;
    s32 i;

    D_80092C88 = 0;
    for (i = 0; i < 4; i++) {
        D_80092E48[i].unk12 = -0x80;
    }
    for (i = 0; i < 4; i++) {
        D_80092EB8[i].button = 0;
        D_80092EB8[i].stick_x = 0;
        D_80092EB8[i].stick_y = 0;
    }
    osCreateMesgQueue(&D_80092C90, &D_80092EB0, 1);
    osSetEventMesg(OS_EVENT_SI, &D_80092C90, &D_80092EB0);
    osContInit(&D_80092C90, &D_80092E98, D_80092EA0);
    osContSetCh(4);
    D_80092C80 = -1;
    count = 0;
    for (i = 0; i != 4; i++) {
        if (D_80092E98 & (1 << i)) {
            if (D_80092EA0[i].errno & 4) {
                D_80092E48[i].unk12 = -1;
            } else if (D_80092EA0[i].type & 2) {
                D_80092E48[i].unk12 = -2;
            } else {
                D_80092E48[i].unk12 = 0;
                count++;
                if (D_80092C80 == -1) {
                    D_80092C80 = i;
                }
                if (D_80092EA0[i].status & 1) {
                    D_80092E48[i].unk0 |= 0x8000;
                } else {
                    D_80092E48[i].unk0 = 0;
                    if (i == D_80092C80) {
                        ret = 1;
                    }
                }
            }
        } else {
            D_80092E48[i].unk12 = -3;
        }
    }
    if (count == 0) {
        return -1;
    }
    return ret;
}

void func_80035970(s32 cont) {
    OSContPad *pad;
    u16 button;

    osContSetCh(4);
    osContStartReadData(&D_80092C90);
    if (osRecvMesg(&D_80092C90, NULL, 1) != -1) {
        osContGetReadData(D_80092EB8);
    }
    pad = &D_80092EB8[cont];
    button = pad->button;
    D_80092C84 = button;
    D_80092C81 = pad->stick_x;
    D_80092C82 = pad->stick_y;
    D_80092C86 = button & D_80092C88;
    D_80092C88 = ~button;
}

s32 func_80035A24(s32 cont) {
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
    D_80092E48[cont].unk13 = 0xFF;
    D_80092E48[cont].unk0 = 0;
    for (i = 0; i < 16; i++) {
        D_80092E48[cont].unk2[i] = -1;
    }
    pfs = &D_80092CA8[cont];
    err = func_8003D0F0(&D_80092C90, pfs, cont);
    if (err != 0) {
        if (err == 10) {
            if (func_8003D554(&D_80092C90, pfs, cont) == 0) {
                return 1;
            }
            if (func_8003D6B0(&D_80092C90, pfs, cont) == 0) {
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
                if (func_800360F8(D_80061810, st.game_name, 16) == 0) {
                    found++;
                    D_80092E48[cont].unk2[i] = ((u8 *) st.ext_name)[0];
                    D_80092E48[cont].unk0 |= 0x4000;
                } else {
                    D_80092E48[cont].unk2[i] = 0x7F;
                }
            } else {
                D_80092E48[cont].unk2[i] = 0x7F;
            }
            cnt++;
        } else if (err == 5) {
            D_80092E48[cont].unk2[i] = -1;
            err = 0;
        } else {
            break;
        }
    }
    if (err == 0) {
        D_80092E48[cont].unk0 &= 0xFFF0;
        D_80092E48[cont].unk0 |= found;
        if (found >= 16) {
            D_80092E48[cont].unk0 |= 0x2000;
        }
        if (cnt >= 16) {
            D_80092E48[cont].unk0 |= 0x2000;
        }
        osPfsFreeBlocks(pfs, &i);
        i = i / 256;
        D_80092E48[cont].unk13 = i;
        if (i < 2) {
            D_80092E48[cont].unk0 |= 0x2000;
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
            if (i + 0x1A == D_80092E48[k].unk2[j]) {
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

u8 func_80035D58(s32 arg0, u8 arg1) {
    u8 unused[4];
    s32 file_no;
    Ext4 ext;
    s32 ret;

    ext = D_80061840;
    file_no = -1;
    ext.b[0] = arg1;
    ret = osPfsAllocateFile(&D_80092CA8[arg0], 0x3943, 0x4E45544A, D_80061810, &ext, 0x200, &file_no);
    if (ret == 0) {
        ret = file_no;
        D_80092E48[arg0].unk2[ret] = arg1;
    } else {
        ret = -ret;
    }
    return ret;
}

u8 func_80035E24(s32 arg0, u8 arg1) {
    u8 unused[4];
    Ext4 ext;

    ext = D_80061844;
    ext.b[0] = arg1;
    return osPfsDeleteFile(&D_80092CA8[arg0], 0x3943, 0x4E45544A, D_80061810, &ext);
}

void func_80035EA8(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    osPfsReadWriteFile(&D_80092CA8[arg0], file_no, 0, offset, nbytes, buf);
}

s32 func_80035F0C(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    s32 ret;
    s32 bytes;

    ret = osPfsFreeBlocks(&D_80092CA8[arg0], &bytes);
    if (ret != 0) {
        return ret;
    }
    return osPfsReadWriteFile(&D_80092CA8[arg0], file_no, 1, offset, nbytes, buf);
}

s32 func_80035F94(s32 arg0, s32 arg1) {
    s32 err;
    s32 cont = D_80092C80;

    if (arg1 == 10) {
        if (func_8003D554(&D_80092C90, &D_80092CA8[cont], cont) != 0) {
            if (func_8003D6B0(&D_80092C90, &D_80092CA8[cont], cont) != 0) {
                err = func_8003D0F0(&D_80092C90, &D_80092CA8[cont], cont);
                if (err != 11 && err != 1 && err != 2) {
                    err = osPfsRepairId(&D_80092CA8[cont]);
                }
            } else {
                err = 4;
            }
        } else {
            err = 4;
        }
    } else {
        err = func_8003D0F0(&D_80092C90, &D_80092CA8[cont], cont);
    }
    return err;
}

s32 func_8003609C(s32 arg0) {
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

s32 func_800360F8(u8 *a, u8 *b, s32 n) {
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

void func_80036144(OSMesgQueue *mq) {
    osContStartQuery(mq);
}

void func_80036164(OSContStatus *status) {
    osContGetQuery(status);
}

void func_80036184(void) {
    func_8003D6B0();
}
