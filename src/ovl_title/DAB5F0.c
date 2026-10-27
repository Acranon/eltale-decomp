#include "common.h"

/*
 * Title overlay: entry, per-frame update, the phase state machine, button handling.
 * Folder: src/game/title/   (proposed for round 4)
 */

typedef struct {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
} UnkStruct_8020EF00;

extern Gfx* gfx_dl_head;
extern u16 input_pressed_buttons;
extern s32 D_8020F1E0_ovl_title;
extern Gfx D_8020F208_ovl_title[];
extern Gfx D_8020F470_ovl_title[];
extern s32 D_8020F4F0_ovl_title;
extern s32 D_8020F4F4_ovl_title;
/* .bss 80226D90..80226DB0 */
s32 D_80226D90_ovl_title;
s32 D_80226D94_ovl_title;
s32 D_80226D98_ovl_title;
s32 D_80226D9C_ovl_title; /* black overlay alpha, 0..255 */
s32 D_80226DA0_ovl_title;
s32 D_80226DA4_ovl_title;
extern s8 D_80226DB0_ovl_title;
extern s32 D_80226DB4_ovl_title;
extern s32 D_80226DC0_ovl_title;

void Sfx_Enqueue(s32, s32, s32);
s32 Title_RunPhase(void);
void Title_DrawScreenAndMoveCursor(s32);

void Title_Init(void) {
    D_80226D90_ovl_title = 0;
    D_80226DA4_ovl_title = 0;
    D_8020F4F4_ovl_title = 1;
    D_8020F4F0_ovl_title = 0;
    D_80226D94_ovl_title = 1;
    D_80226D9C_ovl_title = 0;
    D_80226DA0_ovl_title = 8;
    D_80226D98_ovl_title = 0;
}

s32 Title_Update(void) {
    if (Title_RunPhase() == 0) {
        if (D_80226DA4_ovl_title == 0) {
            return 1;
        }
        if (D_80226DA4_ovl_title == 0xF) {
            D_80226DA4_ovl_title = 0;
            return 0;
        }
    }
    return 2;
}

extern u8 D_8006CC80;
extern u8 title_menu_choice;
extern s8 input_stick_x;
extern s8 input_stick_y;
void Title_UpdateScreen(void);
void Title_UpdateSelectionExit(void);
void Title_UpdateScreenFade(void);


/* .data 8020F1E0..8020F200: D_8020F1E0, then func_8020C178's statics F1E4..F1F0. */
s32 D_8020F1E0_ovl_title = 0;

s32 Title_RunPhase(void) {
    static u8 D_8020F1E4_ovl_title = 0;
    static u32 D_8020F1E8_ovl_title = 0;
    static u16 D_8020F1EC_ovl_title = 0;
    static u8 D_8020F1F0_ovl_title = 0;

    if (D_8020F1F0_ovl_title == 0) {
        D_80226D90_ovl_title = 3;
        D_80226D94_ovl_title = 1;
        D_80226DA4_ovl_title = 0;
        D_8006CC80 = 0;
        D_8020F1F0_ovl_title++;
    }

    switch (D_80226D90_ovl_title) {
        case 3:
            D_80226D94_ovl_title = D_80226D94_ovl_title - 1;
            if (D_80226D94_ovl_title == 0) {
                D_80226D94_ovl_title = 0x1518;
                D_80226D90_ovl_title++;
                D_8020F4F4_ovl_title = 0x14;
                D_8020F4F0_ovl_title = 2;
            }
            break;
        case 4:
            Title_UpdateScreen();
            if (D_8020F4F0_ovl_title == 2) {
                Title_UpdateScreenFade();
            }
            if ((D_80226D94_ovl_title == 0) && (D_80226DA4_ovl_title == 0) && (D_8020F1E0_ovl_title == 0)) {
                D_8020F1E0_ovl_title = 1;
                D_8020F4F4_ovl_title = 0x3C;
                D_8020F4F0_ovl_title = 1;
                D_80226D94_ovl_title = 0x3C;
            }
            if (D_8020F1E0_ovl_title == 1) {
                Title_UpdateScreenFade();
                if (D_8020F4F0_ovl_title == 0) {
                    D_80226D9C_ovl_title = 0;
                    D_80226DA0_ovl_title = 8;
                    D_80226D94_ovl_title = 0;
                    D_80226D90_ovl_title = 0;
                    D_8020F1E0_ovl_title = 0;
                    D_80226DA4_ovl_title = 0;
                }
            }
            if ((D_80226D94_ovl_title == 0) && (D_80226DA4_ovl_title == 1)) {
                D_80226DA4_ovl_title = 2;
                D_80226D94_ovl_title = 2;
                D_80226D90_ovl_title++;
            }
            break;
        case 5:
            Title_UpdateScreen();
            if (D_8020F1EC_ovl_title == 0) {
                D_8020F1E8_ovl_title++;
            } else {
                D_8020F1E8_ovl_title = 0;
            }
            if (!(input_pressed_buttons & 0xF000) && (input_stick_x >= -0x13) && (input_stick_x < 0x14) && (input_stick_y >= -0x13) &&
                (input_stick_y < 0x14)) {
                D_8020F1EC_ovl_title = 0;
            } else {
                D_8020F1EC_ovl_title = 1;
            }
            if (D_8020F1E8_ovl_title >= 0x1C21U) {
                D_8020F1EC_ovl_title = 0;
                D_80226DA4_ovl_title = 4;
                D_8020F1E0_ovl_title = 1;
                D_80226D94_ovl_title = 2;
                D_8020F1E8_ovl_title = 0;
            }
            if (D_8020F1E0_ovl_title == 0) {
                D_80226D94_ovl_title = 0x14;
            }
            if ((D_80226D94_ovl_title == 0) && ((D_80226DA4_ovl_title == 3) || (D_80226DA4_ovl_title == 4))) {
                if (D_80226DA4_ovl_title == 4) {
                    D_8020F1E0_ovl_title = 2;
                    D_8020F4F4_ovl_title = 0x3C;
                    D_8020F4F0_ovl_title = 1;
                }
                D_80226D94_ovl_title = 0x3C;
                if (D_80226DA4_ovl_title == 3) {
                    D_80226DA4_ovl_title = 5;
                    D_80226D90_ovl_title += 1;
                    D_80226D9C_ovl_title = 0xFF;
                    D_80226DA0_ovl_title = 0;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            if (D_8020F1E0_ovl_title == 2) {
                Title_UpdateScreenFade();
                if (D_8020F4F0_ovl_title == 0) {
                    D_80226D9C_ovl_title = 0;
                    D_80226DA0_ovl_title = 8;
                    D_80226D94_ovl_title = 0;
                    D_80226D98_ovl_title = 0;
                    D_80226D90_ovl_title = 3;
                    D_80226DA4_ovl_title = 0;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            break;
        case 6:
            Title_UpdateScreen();
            if (D_8020F1E4_ovl_title < 2) {
                D_8020F1E4_ovl_title++;
            } else if ((title_menu_choice & 0xF0) == 0x10) {
                D_80226D90_ovl_title = 8;
                D_8020F4F4_ovl_title = 0x3C;
                D_8020F4F0_ovl_title = 1;
            } else {
                D_80226D90_ovl_title = 8;
                D_8020F4F4_ovl_title = 0x3C;
                D_8020F4F0_ovl_title = 1;
            }
            break;
        case 7:
            Title_UpdateScreen();
            if (D_8020F1E0_ovl_title == 0) {
                D_80226D94_ovl_title = 0x14;
            }
            if (D_80226DA4_ovl_title == 2) {
                D_80226D90_ovl_title = 5;
            }
            if ((D_80226D94_ovl_title == 0) && ((D_80226DA4_ovl_title == 0xB) || (D_80226DA4_ovl_title == 0xC) || (D_80226DA4_ovl_title == 0xD) ||
                                      (D_80226DA4_ovl_title == 0xE) || (D_80226DA4_ovl_title == 9) || (D_80226DA4_ovl_title == 0xA))) {
                if (D_80226DA4_ovl_title == 9) {
                    D_80226D94_ovl_title = 0xA;
                    D_80226D90_ovl_title = 5;
                    D_8020F1E0_ovl_title = 0;
                    D_80226DA4_ovl_title = 2;
                }
                if (D_80226DA4_ovl_title == 0xA) {
                    D_80226D94_ovl_title = 0xA;
                    D_80226D90_ovl_title = 5;
                    D_8020F1E0_ovl_title = 0;
                    D_80226DA4_ovl_title = 2;
                }
                if (D_80226DA4_ovl_title == 0xC) {
                    D_80226D94_ovl_title = 5;
                    D_80226DA4_ovl_title = 9;
                    D_8020F1E0_ovl_title = 0;
                }
                if (D_80226DA4_ovl_title == 0xB) {
                    D_80226D94_ovl_title = 0x3C;
                    D_80226D90_ovl_title += 1;
                    D_80226DA4_ovl_title = 0xF;
                    D_80226D9C_ovl_title = 0;
                    D_80226DA0_ovl_title = 0x100;
                    D_8020F4F4_ovl_title = 0x3C;
                    D_8020F4F0_ovl_title = 1;
                    D_8020F1E0_ovl_title = 0;
                }
                if (D_80226DA4_ovl_title == 0xD) {
                    D_80226D94_ovl_title = 5;
                    D_80226DA4_ovl_title = 0xA;
                    D_8020F1E0_ovl_title = 0;
                }
                if (D_80226DA4_ovl_title == 0xE) {
                    D_80226D94_ovl_title = 0xA;
                    D_80226D90_ovl_title = 5;
                    D_80226DA4_ovl_title = 2;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            break;
        case 8:
            Title_UpdateSelectionExit();
            Title_UpdateScreenFade();
            break;
    }
    if (D_80226D94_ovl_title == 0) {
        D_8020F1EC_ovl_title = 0;
        D_8020F1E8_ovl_title = 0;
    }
    return D_80226D94_ovl_title;
}

void Title_UpdateScreen(void) {
    s32 var_v0;

    gSPDisplayList(gfx_dl_head++, D_8020F208_ovl_title);
    gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, D_80226D9C_ovl_title);

    Title_DrawScreenAndMoveCursor((u32)D_80226DA4_ovl_title);
    D_80226D9C_ovl_title += D_80226DA0_ovl_title;
    if (D_80226D9C_ovl_title >= 0x100) {
        D_80226D9C_ovl_title = 0xFF;
        D_80226DA0_ovl_title = -D_80226DA0_ovl_title;
    } else if (D_80226D9C_ovl_title < 0) {
        D_80226D9C_ovl_title = 0;
        D_80226D9C_ovl_title = 0;
        D_80226DA0_ovl_title = -D_80226DA0_ovl_title;
    }
    D_80226DB4_ovl_title = D_80226D9C_ovl_title;
    if (D_8020F4F0_ovl_title == 0) {
        if ((D_80226DA4_ovl_title == 0) && (input_pressed_buttons & 0x1000)) {
            Sfx_Enqueue(1, 0xFF, 0x40);
            D_80226D9C_ovl_title = 0;
            D_80226DA0_ovl_title = 0x80;
            D_80226DA4_ovl_title = 1;
            D_80226D94_ovl_title = 0x3C;
        } else if (D_80226DA4_ovl_title == 2) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                D_80226D9C_ovl_title = 0;
                D_80226DA0_ovl_title = 0x80;
                D_80226DA4_ovl_title = 3;
                D_80226D94_ovl_title = 0x3C;
                D_8020F1E0_ovl_title = 1;
            } else if (input_pressed_buttons & 0x4000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                D_80226D9C_ovl_title = 0xFF;
                D_80226DA0_ovl_title = 0x80;
                D_80226DA4_ovl_title = 4;
                D_80226D94_ovl_title = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((D_80226DA4_ovl_title == 8) || (D_80226DA4_ovl_title == 7)) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                D_80226D9C_ovl_title = 0;
                D_80226DA0_ovl_title = 0x80;
                D_8020F1E0_ovl_title = 1;
                D_80226D94_ovl_title = 0x3C;
                if (D_80226DB0_ovl_title == 0) {
                    if (D_80226DA4_ovl_title == 8) {
                        D_80226DA4_ovl_title = 0xB;
                    } else {
                        D_80226DA4_ovl_title = 0xD;
                    }
                } else if (D_80226DA4_ovl_title == 8) {
                    D_80226DA4_ovl_title = 0xC;
                } else {
                    D_80226DA4_ovl_title = 0xE;
                }
            } else if (input_pressed_buttons & 0x4000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                D_80226D9C_ovl_title = 0xFF;
                D_80226DA0_ovl_title = 0x80;
                D_80226DA4_ovl_title = 2;
                D_80226D94_ovl_title = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if (D_80226DA4_ovl_title == 6) {
            if (input_pressed_buttons & 0xF000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                D_80226D9C_ovl_title = 0xFF;
                D_80226DA0_ovl_title = 0x80;
                D_80226DA4_ovl_title = 2;
                D_80226D94_ovl_title = 2;
            }
        } else if (D_80226DA4_ovl_title == 9) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((D_80226DA4_ovl_title == 0xA) && (input_pressed_buttons & 0xB000)) {
            Sfx_Enqueue(1, 0xFF, 0x40);
            D_8020F1E0_ovl_title = 1;
        }
    }
    D_80226D94_ovl_title -= 1;
}

void Title_UpdateSelectionExit(void) {
    gSPDisplayList(gfx_dl_head++, D_8020F208_ovl_title);
    gDPSetEnvColor(gfx_dl_head++, 0x00, 0x00, 0x00, 0xFF);

    Title_DrawScreenAndMoveCursor(D_80226DA4_ovl_title);
    if (--D_80226D94_ovl_title == 0) {
        D_80226DA4_ovl_title = 0xF;
    }
}
