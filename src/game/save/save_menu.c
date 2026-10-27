#include "game/save/save_menu.h"
#include "game/audio/sound.h"
#include "game/core/main.h"
#include "game/enemy/boss.h"
#include "game/env/env.h"
#include "game/event/cutscene.h"
#include "game/input/input.h"
#include "game/item/item.h"
#include "game/map/chest.h"
#include "game/map/map.h"
#include "game/map/spirit.h"
#include "game/player/player.h"
#include "game/text/text.h"
#include "game/text/text_window.h"
#include "game/ui/menu.h"


/*
 * Controller Pak save/load menu: file discovery, UI states, and game-state
 * capture and restoration.
 * Original file: 30600.c (ROM 0x30600).
 */

/* .bss 8008FB70..80090450 */
u16 save_menu_flags; /* low three bits select the save-menu state */
u8 save_menu_dialog_index;
u8 save_menu_operation_panel_index;
s32 save_menu_pak_error;
u8 save_menu_choice_cursor;
s8 save_menu_delay_frames; /* save-menu delay, in frames */
s8 save_menu_selected_slot;
#ifdef NON_MATCHING
u8 save_menu_stick_repeat_counter; /* SaveMenu_UpdateSlotList reads it with lbu */
#else
s8 save_menu_stick_repeat_counter;
#endif
u8 save_menu_repair_count;
SaveFileEntry save_menu_file_entries[17];
SaveHeader save_menu_save_headers[16];
SaveGameStateBlock save_menu_game_state_block;
SaveHeader save_menu_header_read_scratch; /* Pak_ReadFile reads 0x80 bytes into it */
u8 D_80090358[0x18];    /* the rest of that 0x80-byte buffer: unreferenced */
u8 save_menu_state_read_scratch[0xE0];


void func_8003D8EC(const char *, ...);
s32 func_8003D0F0(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D554(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D6B0(OSMesgQueue *, OSPfs *, s32);

#ifdef NON_MATCHING
#endif

void SaveMenu_Init(s32 arg0) {
    core_game_mode = 2;
    menu_flags = menu_flags | arg0 | 0x4000;
    save_menu_flags = 0x1000;
    save_menu_choice_cursor = 0xFF;
    save_menu_selected_slot = 0;
    save_menu_delay_frames = 0;
    save_menu_dialog_index = 0;
    save_menu_stick_repeat_counter = 0;
    save_menu_repair_count = 0;
}

void SaveMenu_Update(void) {
    SaveMenu_DrawBackground();
    if (!(save_menu_flags & 0x4000)) {
        if (save_menu_flags & 0x2000) {
            SaveMenu_CheckControllerPak();
            save_menu_flags |= 0x4000;
            save_menu_flags &= ~0x2000;
            save_menu_repair_count = 0;
        } else {
            save_menu_flags |= 0x2000;
            save_menu_operation_panel_index = 0;
        }
    }
    if (save_menu_flags & 0x4000) {
        switch (save_menu_flags & 7) {
            case 5:
                SaveMenu_UpdateDialog();
                break;
            case 0:
                SaveMenu_UpdateSlotList(0);
                break;
            case 4:
                SaveMenu_DeleteSelectedFile();
                break;
            case 2:
                SaveMenu_LoadSelectedFile();
                break;
            case 3:
                SaveMenu_SaveSelectedFile();
                break;
            case 1:
                SaveMenu_RepairPak();
                break;
            case 6:
                SaveMenu_UpdateDelay();
                break;
        }
    }
    if (save_menu_flags & 0x2000) {
        SaveMenu_DrawOperationPanel();
    }
    if (save_menu_flags & 0x8000) {
        menu_flags &= 0x7FFF;
    }
}

void SaveMenu_DrawOperationPanel(void) {
    u8 unused[4];
    s16 *r = save_menu_operation_panel_rects[save_menu_operation_panel_index];
    s16 x = r[0];
    s16 y = r[1];
    s16 w = r[2];
    s16 h = r[3];

    Menu_DrawSprite(0, x, y, w, h);
    Menu_DrawSprite(0x37, x + 3, y + h, w, 3);
    Menu_DrawSprite(0x37, x + w + 1, y + 6, 2, h - 5);
    Menu_DrawSprite(0x37, x - 1, y - 1, w + 2, 1);
    Menu_DrawSprite(0x37, x - 1, y + h, w + 2, 1);
    Menu_DrawSprite(0x37, x - 1, y, 1, h);
    Menu_DrawSprite(0x37, x + w, y, 1, h);
    Menu_DrawSprite(0x38, x + 1, y + 1, w - 3, 1);
    Menu_DrawSprite(0x38, x + 1, y + 2, 1, h - 4);
    Menu_DrawSprite(0x39, x + 1, y + h - 2, w - 2, 1);
    Menu_DrawSprite(0x39, x + w - 2, y + 1, 1, h - 3);
    Text_DrawEncodedString(x + 6, y + 6, save_menu_operation_panel_messages[save_menu_operation_panel_index]);
    SaveMenu_SetTextDrawState();
}

void SaveMenu_CheckControllerPak(void) {
    s32 mode = menu_flags & 0xC;
    s32 err;
    PakFileScan *p;

    if (save_menu_flags & 0x1000) {
        err = func_8003D0F0(&input_si_queue, &pak_port_states[input_primary_port], input_primary_port);
        if (err == 2) {
            err = 0;
        } else if (err == 10) {
            if (func_8003D554(&input_si_queue, &pak_port_states[input_primary_port], input_primary_port) == 0) {
                err = 1;
            } else if (func_8003D6B0(&input_si_queue, &pak_port_states[input_primary_port], input_primary_port) == 0) {
                err = 1;
            } else {
                err = 10;
            }
        }
        save_menu_flags &= ~0x1000;
    }
    if (err == 0) {
        err = Pak_ScanGameFiles(input_primary_port);
    }
    if (err != 0) {
        save_menu_pak_error = err;
        if (-Pak_ClassifyError(err) == 1) {
            if (mode == 4) {
                save_menu_dialog_index = 13;
                save_menu_delay_frames = 10;
            } else {
                save_menu_dialog_index = 8;
                save_menu_delay_frames = 10;
            }
        } else {
            save_menu_dialog_index = 17;
            save_menu_delay_frames = 10;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
    } else {
        if (mode == 4) {
            p = &pak_game_file_scans[input_primary_port];
            if (p->free_pages < 2) {
                if (p->flags & 0x4000) {
                    save_menu_dialog_index = 21;
                } else {
                    save_menu_dialog_index = 20;
                }
                save_menu_delay_frames = 10;
                save_menu_flags &= 0xFFF8;
                save_menu_flags |= 5;
                return;
            }
            if (p->flags & 0x2000) {
                if (p->flags & 0x4000) {
                    save_menu_dialog_index = 21;
                    save_menu_selected_slot = 0;
                    save_menu_flags &= ~0x20;
                } else {
                    save_menu_dialog_index = 20;
                }
                save_menu_delay_frames = 10;
                save_menu_flags &= 0xFFF8;
                save_menu_flags |= 5;
                return;
            }
        } else if (save_menu_repair_count != 0 && ((p = &pak_game_file_scans[input_primary_port])->free_pages < 2 || p->flags & 0x2000)) {
            save_menu_dialog_index = 24;
            save_menu_delay_frames = 10;
            SaveMenu_RefreshFileList();
            save_menu_flags &= 0xFFF8;
            save_menu_flags |= 5;
            save_menu_selected_slot = 0;
            save_menu_flags &= ~0x20;
            return;
        } else if (!(pak_game_file_scans[input_primary_port].flags & 0x4000)) {
            if (mode == 0) {
                save_menu_dialog_index = 9;
                save_menu_delay_frames = 10;
            } else {
                save_menu_dialog_index = 10;
                save_menu_delay_frames = 10;
            }
            save_menu_flags &= 0xFFF8;
            save_menu_flags |= 5;
            return;
        }
        SaveMenu_RefreshFileList();
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 0;
        save_menu_selected_slot = 0;
        save_menu_flags &= ~0x20;
    }
}

void SaveMenu_UpdateDialog(void) {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u8 *msg;

    if (save_menu_dialog_index == 4 || save_menu_dialog_index == 5 || save_menu_dialog_index == 22 || save_menu_dialog_index == 23) {
        SaveMenu_UpdateSlotList(1);
    }
    x = save_menu_dialog_rects[save_menu_dialog_index][0];
    y = save_menu_dialog_rects[save_menu_dialog_index][1];
    w = save_menu_dialog_rects[save_menu_dialog_index][2];
    h = save_menu_dialog_rects[save_menu_dialog_index][3];
    if (menu_flags & 4) {
        msg = save_menu_dialog_messages_save[save_menu_dialog_index];
    } else {
        msg = save_menu_dialog_messages_load_delete[save_menu_dialog_index];
    }
    Menu_DrawSprite(0, x, y, w, h);
    Menu_DrawSprite(0x37, x + 3, y + h, w, 3);
    Menu_DrawSprite(0x37, x + w + 1, y + 6, 2, h - 5);
    Menu_DrawSprite(0x37, x - 1, y - 1, w + 2, 1);
    Menu_DrawSprite(0x37, x - 1, y + h, w + 2, 1);
    Menu_DrawSprite(0x37, x - 1, y, 1, h);
    Menu_DrawSprite(0x37, x + w, y, 1, h);
    Menu_DrawSprite(0x38, x + 1, y + 1, w - 3, 1);
    Menu_DrawSprite(0x38, x + 1, y + 2, 1, h - 4);
    Menu_DrawSprite(0x39, x + 1, y + h - 2, w - 2, 1);
    Menu_DrawSprite(0x39, x + w - 2, y + 1, 1, h - 3);
    Text_DrawEncodedString(x + 6, y + 6, msg);
    SaveMenu_SetTextDrawState();
    if (save_menu_delay_frames >= 0) {
        save_menu_delay_frames--;
    }
    if (save_menu_delay_frames < 0 && !(save_menu_flags & 0x800)) {
        if (input_pressed_buttons & 0x8000) {
            switch (save_menu_dialog_index) {
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 16:
                case 20:
                    save_menu_flags |= 0x8000;
                    Sfx_Play(0, 1, 0xFF);
                    break;
                case 24:
                    save_menu_flags = 0x1000;
                    break;
            }
        }
        if (input_pressed_buttons & 0xC000) {
            switch (save_menu_dialog_index) {
                case 19:
                    save_menu_flags &= ~0x2000;
                    save_menu_flags &= 0xFFF8;
                    save_menu_flags &= ~0x4000;
                    save_menu_flags &= ~0x20;
                    save_menu_selected_slot = 0;
                    save_menu_flags |= 0x1000;
                    Sfx_Play(0, 1, 0xFF);
                    break;
                case 17:
                    save_menu_flags |= 0x10;
                    save_menu_flags |= 0x800;
                    save_menu_choice_cursor = 0;
                    save_menu_delay_frames = 10;
                    Sfx_Play(0, 1, 0xFF);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 13:
                case 14:
                case 15:
                case 21:
                case 22:
                case 23:
                    save_menu_flags &= ~0x10;
                    save_menu_flags |= 0x800;
                    if (save_menu_dialog_index == 4 || save_menu_dialog_index == 5 || save_menu_dialog_index == 6) {
                        save_menu_choice_cursor = 0;
                    } else {
                        save_menu_choice_cursor = 1;
                    }
                    save_menu_delay_frames = 10;
                    Sfx_Play(0, 1, 0xFF);
                    break;
            }
        } else {
            switch (save_menu_dialog_index) {
                case 17:
                    save_menu_flags |= 0x10;
                    save_menu_flags |= 0x800;
                    save_menu_choice_cursor = 0;
                    save_menu_delay_frames = 10;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 13:
                case 14:
                case 15:
                case 18:
                case 21:
                case 22:
                case 23:
                    save_menu_flags &= ~0x10;
                    save_menu_flags |= 0x800;
                    if (save_menu_dialog_index == 4 || save_menu_dialog_index == 5 || save_menu_dialog_index == 6 || save_menu_dialog_index == 18) {
                        save_menu_choice_cursor = 0;
                    } else {
                        save_menu_choice_cursor = 1;
                    }
                    save_menu_delay_frames = 10;
                    break;
            }
        }
    }
    if (save_menu_flags & 0x800) {
        if (save_menu_flags & 0x10) {
            x = save_menu_dialog_rects[0][0];
            y = save_menu_dialog_rects[0][1];
            w = save_menu_dialog_rects[0][2];
            h = save_menu_dialog_rects[0][3];
        } else {
            x = save_menu_dialog_rects[2][0];
            y = save_menu_dialog_rects[2][1];
            w = save_menu_dialog_rects[2][2];
            h = save_menu_dialog_rects[2][3];
        }
        Menu_DrawSprite(0, x, y, w, h);
        Menu_DrawSprite(0x37, x + 3, y + h, w, 3);
        Menu_DrawSprite(0x37, x + w + 1, y + 6, 2, h - 5);
        Menu_DrawSprite(0x37, x - 1, y - 1, w + 2, 1);
        Menu_DrawSprite(0x37, x - 1, y + h, w + 2, 1);
        Menu_DrawSprite(0x37, x - 1, y, 1, h);
        Menu_DrawSprite(0x37, x + w, y, 1, h);
        Menu_DrawSprite(0x38, x + 1, y + 1, w - 3, 1);
        Menu_DrawSprite(0x38, x + 1, y + 2, 1, h - 4);
        Menu_DrawSprite(0x39, x + 1, y + h - 2, w - 2, 1);
        Menu_DrawSprite(0x39, x + w - 2, y + 1, 1, h - 3);
        if (save_menu_flags & 0x10) {
            msg = save_menu_dialog_messages_save[1];
            Text_DrawEncodedString(x + 6, y + 6, msg);
            Text_DrawEncodedString(x + 6, y + 19, save_menu_dialog_messages_save[0]);
        } else {
            msg = save_menu_dialog_messages_save[2];
            Text_DrawEncodedString(x + 6, y + 6, msg);
            Text_DrawEncodedString(x + 6, y + 19, save_menu_dialog_messages_save[3]);
        }
        SaveMenu_SetTextDrawState();
        if (save_menu_delay_frames < 0) {
            if (input_stick_y < -20 || input_stick_y > 20) {
                if (!(save_menu_flags & 8)) {
                    save_menu_choice_cursor ^= 1;
                    save_menu_flags |= 8;
                    Sfx_Play(0, 0, 0xFF);
                }
            } else {
                save_menu_flags &= ~8;
            }
            SaveMenu_SetTextDrawState();
            if (save_menu_flags & 0x10) {
                Menu_DrawSprite(4, save_menu_choice_cursor_positions[save_menu_choice_cursor + 2][0], save_menu_choice_cursor_positions[save_menu_choice_cursor + 2][1], 12, 12);
            } else {
                Menu_DrawSprite(4, save_menu_choice_cursor_positions[save_menu_choice_cursor][0], save_menu_choice_cursor_positions[save_menu_choice_cursor][1], 12, 12);
            }
            if (input_pressed_buttons & 0x8000) {
                if (save_menu_choice_cursor == 0) {
                    Sfx_Play(0, 1, 0xFF);
                    switch (save_menu_dialog_index) {
                        case 17:
                            save_menu_dialog_index = 18;
                            save_menu_delay_frames = 10;
                            break;
                        case 5:
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags |= 4;
                            save_menu_flags |= 0x2000;
                            save_menu_operation_panel_index = 3;
                            break;
                        case 4:
                            save_menu_flags |= 0x2000;
                            save_menu_operation_panel_index = 2;
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags |= 3;
                            break;
                        case 6:
                            save_menu_flags |= 0x2000;
                            save_menu_operation_panel_index = 4;
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags |= 1;
                            break;
                        case 21:
                            SaveMenu_RefreshFileList();
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags |= 0;
                            break;
                        case 14:
                        case 15:
                        case 18:
                        case 22:
                        case 23:
                            save_menu_flags &= ~0x2000;
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags &= ~0x4000;
                            save_menu_flags |= 0x1000;
                            break;
                        case 13:
                            save_menu_flags |= 0x8000;
                            break;
                        case 7:
                            save_menu_flags |= 0x8000;
                            break;
                    }
                } else {
                    Sfx_Play(0, 2, 0xFF);
                    switch (save_menu_dialog_index) {
                        case 17:
                            save_menu_dialog_index = 6;
                            break;
                        case 15:
                        case 18:
                        case 22:
                        case 23:
                            save_menu_flags |= 0x8000;
                            break;
                        case 13:
                            save_menu_flags &= ~0x2000;
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags &= ~0x4000;
                            save_menu_flags |= 0x1000;
                            break;
                        case 14:
                        case 21:
                            save_menu_dialog_index = 15;
                            save_menu_delay_frames = 10;
                            break;
                        case 4:
                        case 5:
                        case 7:
                            save_menu_flags &= 0xFFF8;
                            if (save_menu_flags & 0x1000) {
                                save_menu_flags &= ~0x4000;
                                save_menu_flags |= 0x2000;
                            } else {
                                save_menu_flags |= 0;
                            }
                            break;
                        case 6:
                            save_menu_flags &= ~0x2000;
                            save_menu_flags &= 0xFFF8;
                            save_menu_flags |= 0x1005;
                            save_menu_dialog_index = 7;
                            break;
                    }
                }
                save_menu_flags &= ~0x800;
            } else if (input_pressed_buttons & 0x4000) {
                switch (save_menu_dialog_index) {
                    case 6:
                    case 7:
                    case 13:
                    case 14:
                    case 15:
                    case 17:
                    case 18:
                    case 21:
                    case 22:
                    case 23:
                        break;
                    default:
                        save_menu_flags &= ~0x800;
                        save_menu_delay_frames = 2;
                        save_menu_flags &= 0xFFF8;
                        save_menu_flags |= 0;
                        break;
                }
            }
        }
    }
}

/* .data 80061650..80061660: SaveMenu_UpdateSlotList's local message (an initialized u8[14]
 * that IDO copies to the stack); becomes its initializer when the function is C. */
#ifdef NON_MATCHING
SaveBytes14 D_80061650 = { {
#include "assets/D_80061650.inc.c"
} };
#else
u8 D_80061650[0xE] = {
#include "assets/D_80061650.inc.c"
};
#endif

#ifdef NON_MATCHING
/* stack homes and flag/cursor lifetimes differ (code 0x18 bytes short); code is equivalent */
void SaveMenu_UpdateSlotList(s32 arg0) {
    s32 idx;
    s32 flag;
    s32 secs;
    s32 n;
    s32 pad_x;
    s32 colors[1];
    SaveBytes14 buf;
    SaveFileEntry *ptr[1];

    flag = 0;
    buf = D_80061650;
    if (save_menu_flags & 0x20) {
        if (save_menu_selected_slot == 0) {
            idx = save_menu_selected_slot;
            save_menu_flags &= 0xFFDF;
        } else {
            idx = save_menu_selected_slot - 1;
        }
    } else {
        idx = save_menu_selected_slot;
    }
    ptr[0] = &save_menu_file_entries[idx];
    if (ptr[0]->unk0 != -2) {
        if (ptr[0]->unk1 != -1) {
            if (idx == save_menu_selected_slot) {
                Menu_DrawNumber(2, 0x6F, 0x36, idx, 0xA);
                Menu_DrawSprite(0x36, 0x53, 0x35, 0x1C, 0xD);
                Menu_DrawSprite(0x19, 0x92, 0x36, 8, 0xA);
                Menu_DrawSprite(0x43, 0xD9, 0x35, 0x1C, 0xE);
                colors[0] = 0xA;
            } else {
                Menu_DrawNumber(2, 0x6F, 0x36, idx, 0x48);
                Menu_DrawSprite(0x45, 0x53, 0x35, 0x1C, 0xD);
                Menu_DrawSprite(0x52, 0x92, 0x36, 8, 0xA);
                Menu_DrawSprite(0x44, 0xD9, 0x35, 0x1C, 0xE);
                colors[0] = 0x48;
            }
            Menu_DrawNumber(2, 0x65, 0x6C, save_menu_save_headers[idx].unk0.unk24[0], 0xA);
            Menu_DrawNumber(2, 0x8A, 0x6C, save_menu_save_headers[idx].unk0.unk24[1], 0xA);
            Menu_DrawNumber(2, 0xAF, 0x6C, save_menu_save_headers[idx].unk0.unk24[2], 0xA);
            Menu_DrawNumber(2, 0xD4, 0x6C, save_menu_save_headers[idx].unk0.unk24[3], 0xA);
            switch (save_menu_save_headers[idx].unk3C) {
                case 15:
                    if (save_menu_save_headers[idx].unk40 == 5) {
                        n = 0;
                    } else {
                        n = 0x10;
                    }
                    break;
                case 16:
                    if (save_menu_save_headers[idx].unk40 == 7) {
                        n = 1;
                    } else {
                        n = 2;
                    }
                    break;
                case 17:
                    n = 4;
                    break;
                case 18:
                    if (save_menu_save_headers[idx].unk40 == 6) {
                        n = 3;
                    } else {
                        n = 5;
                    }
                    break;
                case 20:
                    n = 6;
                    break;
                case 22:
                    if (save_menu_save_headers[idx].unk40 == 0x16) {
                        n = 7;
                    } else {
                        n = 8;
                    }
                    break;
                case 23:
                    switch (save_menu_save_headers[idx].unk40) {
                        case 0:
                            n = 9;
                            break;
                        case 8:
                            n = 0xC;
                            break;
                        case 19:
                            n = 0xA;
                            break;
                        case 22:
                            n = 0xB;
                            break;
                    }
                    break;
                case 25:
                    n = 0xE;
                    break;
                case 26:
                    n = 0xD;
                    break;
                case 30:
                    n = 0xF;
                    break;
            }
            Text_DrawEncodedString(0x51, 0x48, save_menu_slot_map_labels[n]);
            SaveMenu_SetTextDrawState();
            n = 0;
            secs = save_menu_save_headers[idx].unk38;
            while (secs >= 60) {
                secs -= 60;
                n++;
            }
            Menu_DrawNumber(3, 0x7E, 0x36, n, colors[0]);
            Menu_DrawNumberZeroPad(2, 0x9A, 0x36, secs, colors[0]);
            Menu_DrawNumber(3, 0xC0, 0x36, save_menu_save_headers[idx].unk3A, colors[0]);
            Menu_PrintNumber(3, 0x70, 0x58, save_menu_save_headers[idx].unk0.unk4);
            Menu_PrintNumber(3, 0xC0, 0x58, save_menu_save_headers[idx].unk0.unk8);
        }
    } else {
        flag = 1;
        Text_DrawEncodedString(0x82, 0x33, buf.b);
    }
    SaveMenu_SetTextDrawState();
    idx++;
    ptr[0]++;
    if (ptr[0]->unk0 != -1 && flag == 0) {
        if (ptr[0]->unk0 != -2) {
            if (ptr[0]->unk1 != -1) {
                    if (idx == save_menu_selected_slot) {
                    Menu_DrawNumber(2, 0x6F, 0x83, idx, 0xA);
                    Menu_DrawSprite(0x36, 0x53, 0x82, 0x1C, 0xD);
                    Menu_DrawSprite(0x19, 0x92, 0x83, 8, 0xA);
                    Menu_DrawSprite(0x43, 0xD9, 0x82, 0x1C, 0xE);
                    colors[0] = 0xA;
                } else {
                    Menu_DrawNumber(2, 0x6F, 0x83, idx, 0x48);
                    Menu_DrawSprite(0x45, 0x53, 0x82, 0x1C, 0xD);
                    Menu_DrawSprite(0x52, 0x92, 0x83, 8, 0xA);
                    Menu_DrawSprite(0x44, 0xD9, 0x82, 0x1C, 0xE);
                    colors[0] = 0x48;
                }
                Menu_DrawNumber(2, 0x65, 0xBA, save_menu_save_headers[idx].unk0.unk24[0], 0xA);
                Menu_DrawNumber(2, 0x8A, 0xBA, save_menu_save_headers[idx].unk0.unk24[1], 0xA);
                Menu_DrawNumber(2, 0xAF, 0xBA, save_menu_save_headers[idx].unk0.unk24[2], 0xA);
                Menu_DrawNumber(2, 0xD4, 0xBA, save_menu_save_headers[idx].unk0.unk24[3], 0xA);
                switch (save_menu_save_headers[idx].unk3C) {
                    case 15:
                        if (save_menu_save_headers[idx].unk40 == 5) {
                            n = 0;
                        } else {
                            n = 0x10;
                        }
                        break;
                    case 16:
                        if (save_menu_save_headers[idx].unk40 == 7) {
                            n = 1;
                        } else {
                            n = 2;
                        }
                        break;
                    case 17:
                        n = 4;
                        break;
                    case 18:
                        if (save_menu_save_headers[idx].unk40 == 6) {
                            n = 3;
                        } else {
                            n = 5;
                        }
                        break;
                    case 20:
                        n = 6;
                        break;
                    case 22:
                        if (save_menu_save_headers[idx].unk40 == 0x16) {
                            n = 7;
                        } else {
                            n = 8;
                        }
                        break;
                    case 23:
                        switch (save_menu_save_headers[idx].unk40) {
                            case 0:
                                n = 9;
                                break;
                            case 8:
                                n = 0xC;
                                break;
                            case 19:
                                n = 0xA;
                                break;
                            case 22:
                                n = 0xB;
                                break;
                        }
                        break;
                    case 25:
                        n = 0xE;
                        break;
                    case 26:
                        n = 0xD;
                        break;
                    case 30:
                        n = 0xF;
                        break;
                }
                Text_DrawEncodedString(0x51, 0x96, save_menu_slot_map_labels[n]);
                SaveMenu_SetTextDrawState();
                n = 0;
                secs = save_menu_save_headers[idx].unk38;
                while (secs >= 60) {
                    secs -= 60;
                    n++;
                }
                Menu_DrawNumber(3, 0x7E, 0x83, n, colors[0]);
                Menu_DrawNumberZeroPad(2, 0x9A, 0x83, secs, colors[0]);
                Menu_DrawNumber(3, 0xC0, 0x83, save_menu_save_headers[idx].unk3A, colors[0]);
                Menu_PrintNumber(3, 0x70, 0xA6, save_menu_save_headers[idx].unk0.unk4);
                Menu_PrintNumber(3, 0xC0, 0xA6, save_menu_save_headers[idx].unk0.unk8);
            }
        } else {
            Text_DrawEncodedString(0x82, 0x7F, buf.b);
        }
    }
    SaveMenu_SetTextDrawState();
    flag = menu_wobble_offsets[(menu_frame_counter >> 2) & 0xF];
    if (save_menu_selected_slot >= 2) {
        Menu_DrawSprite(5, 0x38, 0x4D, 7, 7);
        Menu_DrawSprite(0x53, 0x36, flag + 0x3F, 0xC, 0x10);
    } else if (save_menu_selected_slot == 1 && !(save_menu_flags & 0x20)) {
        Menu_DrawSprite(5, 0x38, 0x4D, 7, 7);
        Menu_DrawSprite(0x53, 0x36, flag + 0x3F, 0xC, 0x10);
    }
    if (ptr[0] < &save_menu_file_entries[16] && ptr[0][1].unk0 != -1) {
        Menu_DrawSprite(5, 0x38, 0xA4, 7, 7);
        Menu_DrawSprite(0x54, 0x36, 0xAC - flag, 0xE, 0xB);
    }
    if (save_menu_flags & 0x20) {
        Menu_DrawSprite(1, flag + 0x42, 0x80, 0x10, 0xD);
    } else {
        Menu_DrawSprite(1, flag + 0x42, 0x37, 0x10, 0xD);
    }
    if (arg0 != 1) {
        n = 0;
        if (input_stick_y < -20) {
            if (save_menu_stick_repeat_counter == 0) {
                Sfx_Play(0, 0, 0xFF);
                save_menu_selected_slot++;
                if (save_menu_file_entries[save_menu_selected_slot].unk0 == -1) {
                    save_menu_selected_slot--;
                    n = 1;
                }
                if (!(save_menu_flags & 0x20) && n == 0) {
                    save_menu_flags |= 0x20;
                } else if (n == 0) {
                    save_menu_flags &= 0xFFF8;
                    save_menu_flags |= 6;
                    save_menu_delay_frames = 4;
                }
            }
            save_menu_stick_repeat_counter++;
            save_menu_stick_repeat_counter &= 0xF;
        } else if (input_stick_y > 20) {
            if (save_menu_stick_repeat_counter == 0) {
                Sfx_Play(0, 0, 0xFF);
                save_menu_selected_slot--;
                if (save_menu_selected_slot < 0) {
                    save_menu_selected_slot = 0;
                    n = 1;
                }
                if (save_menu_flags & 0x20) {
                    save_menu_flags &= 0xFFDF;
                } else if (n == 0) {
                    save_menu_flags &= 0xFFF8;
                    save_menu_flags |= 6;
                    save_menu_delay_frames = 4;
                }
            }
            save_menu_stick_repeat_counter++;
            save_menu_stick_repeat_counter &= 0xF;
        } else {
            save_menu_stick_repeat_counter = 0;
        }
        if (input_pressed_buttons & 0x8000) {
            idx = menu_flags & 0xC;
            Sfx_Play(0, 1, 0xFF);
            switch (idx) {
                case 0:
                    save_menu_flags |= 0x2000;
                    save_menu_operation_panel_index = 1;
                    save_menu_flags &= ~7;
                    save_menu_flags |= 2;
                    break;
                case 8:
                    save_menu_dialog_index = 5;
                    save_menu_delay_frames = 10;
                    save_menu_flags &= ~7;
                    save_menu_flags |= 5;
                    break;
                case 4:
                    if (save_menu_file_entries[save_menu_selected_slot].unk0 == -2) {
                        save_menu_flags |= 0x2000;
                        save_menu_operation_panel_index = 2;
                        save_menu_flags &= ~7;
                        save_menu_flags |= 3;
                    } else {
                        save_menu_dialog_index = 4;
                        save_menu_delay_frames = 10;
                        save_menu_flags &= ~7;
                        save_menu_flags |= 5;
                    }
                    break;
            }
        } else if (input_pressed_buttons & 0x5000) {
            save_menu_dialog_index = 7;
            save_menu_delay_frames = 10;
            save_menu_flags &= ~7;
            save_menu_flags |= 5;
            Sfx_Play(0, 2, 0xFF);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/save/save_menu/SaveMenu_UpdateSlotList.s")
#endif

void SaveMenu_UpdateDelay(void) {
    save_menu_delay_frames--;
    if (save_menu_delay_frames < 0) {
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 0;
    }
}

void SaveMenu_DeleteSelectedFile(void) {
    s32 err = Pak_DeleteGameFile(input_primary_port, (u8)save_menu_file_entries[save_menu_selected_slot].unk1);

    if (err != 0) {
        save_menu_pak_error = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                save_menu_dialog_index = 8;
                save_menu_delay_frames = 10;
                break;
            case 4:
                save_menu_dialog_index = 12;
                save_menu_delay_frames = 10;
                break;
            default:
                save_menu_dialog_index = 17;
                save_menu_delay_frames = 10;
                break;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
        save_menu_flags &= ~0x2000;
    } else {
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
        save_menu_flags &= ~0x2000;
        save_menu_dialog_index = 22;
        save_menu_delay_frames = 10;
        save_menu_file_entries[save_menu_selected_slot].unk1 = -1;
    }
}

void SaveMenu_LoadSelectedFile(void) {
    s32 err = Pak_ReadFile(input_primary_port, save_menu_file_entries[save_menu_selected_slot].unk0, 0x80, 0xE0, save_menu_state_read_scratch);

    save_menu_game_state_block = *(SaveGameStateBlock *)save_menu_state_read_scratch;
    if (err != 0) {
        save_menu_pak_error = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                save_menu_dialog_index = 8;
                save_menu_delay_frames = 10;
                break;
            case 4:
                save_menu_dialog_index = 11;
                save_menu_delay_frames = 10;
                break;
            default:
                save_menu_dialog_index = 17;
                save_menu_delay_frames = 10;
                break;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
        save_menu_flags &= ~0x2000;
    } else {
        SaveMenu_RestoreGameState(save_menu_selected_slot);
        save_menu_flags |= 0x80;
        save_menu_flags |= 0x8000;
    }
}

#ifdef NON_MATCHING
/* register-only: index/pointer a3/t0 colouring differs; code is equivalent */
void SaveMenu_SaveSelectedFile(void) {
    s32 err;
    s32 n;
    s32 id;
    s32 i;
    s32 idx;
    SaveFileEntry *p;
    s32 k;
    s32 cont;

    idx = save_menu_selected_slot;
    p = &save_menu_file_entries[idx];

    if (p->unk0 == -2) {
        cont = input_primary_port;
        n = pak_game_file_scans[cont].flags & 0xF;
        id = 0xF;
        do {
            i = 0;
            id++;
            do {
                if (id == save_menu_file_entries[i].unk1) {
                    i = 0x7F;
                    break;
                }
                i++;
            } while (i < n);
            if (i != 0x7F) {
                n = id;
                id = -1;
            }
        } while (id >= 0);
        p->unk1 = n;
        if (idx + 1 < 16) {
            p[1].unk1 = -2;
        }
        err = Pak_AllocateGameFile(cont, n);
        if (err >= 0) {
            idx = save_menu_selected_slot;
            save_menu_file_entries[idx].unk0 = err;
        } else {
            idx = save_menu_selected_slot;
        }
        SaveMenu_CaptureGameState(idx);
    } else {
        SaveMenu_CaptureGameState(idx);
    }
    id = save_menu_selected_slot;
    err = Pak_WriteFile(input_primary_port, save_menu_file_entries[id].unk0, 0, 0x80, &save_menu_save_headers[id]);
    if (err != 0) {
        save_menu_pak_error = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                save_menu_dialog_index = 13;
                save_menu_delay_frames = 10;
                break;
            case 4:
                save_menu_dialog_index = 14;
                save_menu_delay_frames = 10;
                break;
            default:
                save_menu_dialog_index = 17;
                save_menu_delay_frames = 10;
                break;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
        save_menu_flags &= ~0x2000;
        return;
    }
    err = Pak_WriteFile(input_primary_port, save_menu_file_entries[save_menu_selected_slot].unk0, 0x80, 0xE0, &save_menu_game_state_block);
    if (err != 0) {
        save_menu_pak_error = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                save_menu_dialog_index = 13;
                save_menu_delay_frames = 10;
                break;
            case 4:
                save_menu_dialog_index = 14;
                save_menu_delay_frames = 10;
                break;
            default:
                save_menu_dialog_index = 17;
                save_menu_delay_frames = 10;
                break;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags |= 5;
        save_menu_flags &= ~0x2000;
        return;
    }
    save_menu_flags &= 0xFFF8;
    save_menu_flags |= 5;
    save_menu_flags &= ~0x2000;
    save_menu_dialog_index = 23;
    save_menu_delay_frames = 10;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/save/save_menu/SaveMenu_SaveSelectedFile.s")
#endif

void SaveMenu_RepairPak(void) {
    s32 err;

    func_8003D8EC("Repair Info %d %d\n", save_menu_selected_slot, save_menu_pak_error);
    err = Pak_TryRepair(save_menu_file_entries[save_menu_selected_slot].unk0, save_menu_pak_error);
    if (err != 0) {
        save_menu_pak_error = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                save_menu_dialog_index = 8;
                save_menu_delay_frames = 10;
                break;
            case 3:
                save_menu_dialog_index = 16;
                save_menu_delay_frames = 10;
                break;
            default:
                save_menu_dialog_index = 17;
                save_menu_delay_frames = 10;
                break;
        }
        save_menu_flags &= 0xFFF8;
        save_menu_flags &= ~0x4000;
        save_menu_flags |= 0x1000;
    } else {
        save_menu_flags &= ~0x2000;
        save_menu_flags &= 0xFFF8;
        save_menu_flags &= ~0x4000;
        save_menu_flags |= 0x1000;
        save_menu_repair_count++;
    }
}

void SaveMenu_RefreshFileList(void) {
    SaveFileEntry *p;
    s32 cont;
    s32 n;
    s32 err = 0;
    s32 i;
    SaveHeader *e;
    s32 ret;

    for (i = 0; i < 17; i++) {
        save_menu_file_entries[i].unk0 = -1;
        save_menu_file_entries[i].unk1 = -1;
    }
    cont = input_primary_port;
    n = 0;
    for (i = 0; i < 16; i++) {
        if (pak_game_file_scans[cont].note_ext_first_bytes[i] == 0x7F) {
            continue;
        }
        if (pak_game_file_scans[cont].note_ext_first_bytes[i] >= 0) {
            save_menu_file_entries[n].unk0 = i;
            save_menu_file_entries[n].unk1 = pak_game_file_scans[cont].note_ext_first_bytes[i];
            n++;
        }
    }
    if (menu_flags & 4) {
        if (pak_game_file_scans[cont].free_pages >= 2 && !(pak_game_file_scans[cont].flags & 0x2000)) {
            save_menu_file_entries[n].unk0 = -2;
        }
    }
    save_menu_selected_slot = 0;
    for (i = 0; i < 16; i++) {
        if (save_menu_file_entries[i].unk0 >= 0) {
            e = &save_menu_save_headers[i];
            ret = Pak_ReadFile(input_primary_port, save_menu_file_entries[i].unk0, 0, 0x80, (u8 *)&save_menu_header_read_scratch);
            *e = save_menu_header_read_scratch;
            if (ret != 0) {
                save_menu_pak_error = err;
                err = -Pak_ClassifyError(err);
                if (err == 1) {
                    save_menu_dialog_index = 8;
                    save_menu_delay_frames = 10;
                } else {
                    save_menu_dialog_index = 17;
                    save_menu_delay_frames = 10;
                }
                save_menu_flags &= 0xFFF8;
                save_menu_flags |= 5;
            } else if (e->unk64 != 0) {
                core_flags |= 0x20000;
            }
        }
    }
}

void SaveMenu_SetTextDrawState(void) {
    gSPDisplayList(gfx_dl_head++, text_glyph_setup_dl);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    menu_flags &= ~0x10;
}

void SaveMenu_DrawBackground(void) {
    Menu_DrawSprite(0, 0x3C, 0x22, 0xC8, 0xAB);
    Menu_DrawSprite(0x37, 0x3F, 0xCE, 0xC8, 3);
    Menu_DrawSprite(0x37, 0x105, 0x28, 2, 0xA9);
    Menu_DrawSprite(0x37, 0x3B, 0x21, 0xCA, 1);
    Menu_DrawSprite(0x37, 0x3B, 0xCD, 0xCA, 1);
    Menu_DrawSprite(0x37, 0x3B, 0x21, 1, 0xAD);
    Menu_DrawSprite(0x37, 0x104, 0x21, 1, 0xAD);
    Menu_DrawSprite(0x38, 0x3D, 0x23, 0xC5, 1);
    Menu_DrawSprite(0x38, 0x3D, 0x23, 1, 0xA8);
    Menu_DrawSprite(0x39, 0x3D, 0xCB, 0xC6, 1);
    Menu_DrawSprite(0x39, 0x102, 0x23, 1, 0xA9);
    Menu_DrawSprite(0x3F, 0x5A, 0x2E, 0x96, 2);
    Menu_DrawSprite(0x3F, 0x5A, 0x44, 0x96, 2);
    Menu_DrawSprite(0x3F, 0x5A, 0x7B, 0x96, 2);
    Menu_DrawSprite(0x3F, 0x5A, 0x91, 0x96, 2);
    Menu_DrawSprite(0x42, 0x5E, 0x67, 0x7C, 0xC);
    Menu_DrawSprite(0x42, 0x5E, 0xB5, 0x7C, 0xC);
    Menu_DrawSprite(0x46, 0x55, 0x58, 0x14, 0xE);
    Menu_DrawSprite(0x47, 0xA2, 0x58, 0x18, 0xE);
    Menu_DrawSprite(0x46, 0x55, 0xA6, 0x14, 0xE);
    Menu_DrawSprite(0x47, 0xA2, 0xA6, 0x18, 0xE);
}

void SaveMenu_CaptureGameState(s32 arg0) {
    SaveHeader *e = &save_menu_save_headers[arg0];
    u8 *d;
    u8 *s;
    s32 n;

    e->unk0 = player_stats;
    e->unk38 = env_play_time;
    e->unk3A = env_day_count;
    e->unk3C = map_id;
    e->unk40 = map_subarea;
    e->unk44 = map_flag4_return_map;
    e->unk48 = map_flag4_return_subarea;
    e->unk4C = map_flag4_return_entry;
    e->unk50 = map_flag8_return_map;
    e->unk54 = map_flag8_return_subarea;
    e->unk58 = map_flag8_return_entry;
    e->unk5C = player_respawn_map;
    e->unk5E = player_respawn_subarea;
    e->unk60 = player_respawn_entry;
    e->unk62 = menu_text_delay_option;
    e->unk63 = menu_bgm_volume_option;
    if (core_flags & 0x20000) {
        e->unk64 = 1;
    } else {
        e->unk64 = 0;
    }
    d = save_menu_game_state_block.unk0.b;
    for (s = chest_opened_flags, n = sizeof(save_menu_game_state_block.unk0); n != 0; n--) {
        *d++ = *s++;
    }
    d = save_menu_game_state_block.unk20.b;
    for (s = spirit_collected_flags, n = sizeof(save_menu_game_state_block.unk20); n != 0; n--) {
        *d++ = *s++;
    }
    d = save_menu_game_state_block.unk30.b;
    for (s = item_inventory, n = sizeof(save_menu_game_state_block.unk30); n != 0; n--) {
        *d++ = *s++;
    }
    d = save_menu_game_state_block.unkC7.b;
    for (s = boss_defeated_bits, n = sizeof(save_menu_game_state_block.unkC7); n != 0; n--) {
        *d++ = *s++;
    }
}

void SaveMenu_RestoreGameState(s32 arg0) {
    SaveHeader *e = &save_menu_save_headers[arg0];
    u8 *d;
    u8 *s;
    s32 n;

    player_stats = e->unk0;
    env_play_time = e->unk38;
    env_day_count = e->unk3A;
    map_id = e->unk3C;
    map_subarea = e->unk40;
    map_flag4_return_map = e->unk44;
    map_flag4_return_subarea = e->unk48;
    map_flag4_return_entry = e->unk4C;
    map_flag8_return_map = e->unk50;
    map_flag8_return_subarea = e->unk54;
    map_flag8_return_entry = e->unk58;
    player_respawn_map = e->unk5C;
    player_respawn_subarea = e->unk5E;
    player_respawn_entry = e->unk60;
    menu_text_delay_option = e->unk62;
    menu_bgm_volume_option = e->unk63;
    if (e->unk64 != 0) {
        core_flags |= 0x20000;
    }
    for (s = save_menu_game_state_block.unk0.b, d = chest_opened_flags, n = sizeof(save_menu_game_state_block.unk0); n != 0; n--) {
        *d++ = *s++;
    }
    s = save_menu_game_state_block.unk20.b;
    for (d = spirit_collected_flags, n = sizeof(save_menu_game_state_block.unk20); n != 0; n--) {
        *d++ = *s++;
    }
    s = save_menu_game_state_block.unk30.b;
    for (d = item_inventory, n = sizeof(save_menu_game_state_block.unk30); n != 0; n--) {
        *d++ = *s++;
    }
    s = save_menu_game_state_block.unkC7.b;
    for (d = boss_defeated_bits, n = sizeof(save_menu_game_state_block.unkC7); n != 0; n--) {
        *d++ = *s++;
    }
}
