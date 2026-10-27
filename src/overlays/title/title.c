#include "overlays/title/title.h"
#include "game/audio/audio.h"
#include "game/core/main.h"
#include "game/event/cutscene.h"
#include "game/input/input.h"
#include "overlays/title/title_draw.h"

/*
 * Title overlay: entry, per-frame update, the phase state machine, button handling.
 * Original file: ovl_title/DAB5F0.c (ROM 0xDAB5F0).
 */

/* .bss 80226D90..80226DB0 */
s32 title_flow_state;
s32 title_state_timer;
s32 D_80226D98_ovl_title;
s32 title_pulse_alpha; /* black overlay alpha, 0..255 */
s32 title_pulse_step;
s32 title_menu_state;


void Title_Init(void) {
    title_flow_state = 0;
    title_menu_state = 0;
    title_screen_fade_frames = 1;
    title_screen_fade_state = 0;
    title_state_timer = 1;
    title_pulse_alpha = 0;
    title_pulse_step = 8;
    D_80226D98_ovl_title = 0;
}

s32 Title_Update(void) {
    if (Title_RunPhase() == 0) {
        if (title_menu_state == 0) {
            return 1;
        }
        if (title_menu_state == 0xF) {
            title_menu_state = 0;
            return 0;
        }
    }
    return 2;
}



/* .data 8020F1E0..8020F200: D_8020F1E0, then func_8020C178's statics F1E4..F1F0. */
s32 D_8020F1E0_ovl_title = 0;

s32 Title_RunPhase(void) {
    static u8 D_8020F1E4_ovl_title = 0;
    static u32 title_idle_frames = 0;
    static u16 D_8020F1EC_ovl_title = 0;
    static u8 D_8020F1F0_ovl_title = 0;

    if (D_8020F1F0_ovl_title == 0) {
        title_flow_state = 3;
        title_state_timer = 1;
        title_menu_state = 0;
        D_8006CC80[0] = 0;
        D_8020F1F0_ovl_title++;
    }

    switch (title_flow_state) {
        case 3:
            title_state_timer = title_state_timer - 1;
            if (title_state_timer == 0) {
                title_state_timer = 0x1518;
                title_flow_state++;
                title_screen_fade_frames = 0x14;
                title_screen_fade_state = 2;
            }
            break;
        case 4:
            Title_UpdateScreen();
            if (title_screen_fade_state == 2) {
                Title_UpdateScreenFade();
            }
            if ((title_state_timer == 0) && (title_menu_state == 0) && (D_8020F1E0_ovl_title == 0)) {
                D_8020F1E0_ovl_title = 1;
                title_screen_fade_frames = 0x3C;
                title_screen_fade_state = 1;
                title_state_timer = 0x3C;
            }
            if (D_8020F1E0_ovl_title == 1) {
                Title_UpdateScreenFade();
                if (title_screen_fade_state == 0) {
                    title_pulse_alpha = 0;
                    title_pulse_step = 8;
                    title_state_timer = 0;
                    title_flow_state = 0;
                    D_8020F1E0_ovl_title = 0;
                    title_menu_state = 0;
                }
            }
            if ((title_state_timer == 0) && (title_menu_state == 1)) {
                title_menu_state = 2;
                title_state_timer = 2;
                title_flow_state++;
            }
            break;
        case 5:
            Title_UpdateScreen();
            if (D_8020F1EC_ovl_title == 0) {
                title_idle_frames++;
            } else {
                title_idle_frames = 0;
            }
            if (!(input_pressed_buttons & 0xF000) && (input_stick_x >= -0x13) && (input_stick_x < 0x14) && (input_stick_y >= -0x13) &&
                (input_stick_y < 0x14)) {
                D_8020F1EC_ovl_title = 0;
            } else {
                D_8020F1EC_ovl_title = 1;
            }
            if (title_idle_frames >= 0x1C21U) {
                D_8020F1EC_ovl_title = 0;
                title_menu_state = 4;
                D_8020F1E0_ovl_title = 1;
                title_state_timer = 2;
                title_idle_frames = 0;
            }
            if (D_8020F1E0_ovl_title == 0) {
                title_state_timer = 0x14;
            }
            if ((title_state_timer == 0) && ((title_menu_state == 3) || (title_menu_state == 4))) {
                if (title_menu_state == 4) {
                    D_8020F1E0_ovl_title = 2;
                    title_screen_fade_frames = 0x3C;
                    title_screen_fade_state = 1;
                }
                title_state_timer = 0x3C;
                if (title_menu_state == 3) {
                    title_menu_state = 5;
                    title_flow_state += 1;
                    title_pulse_alpha = 0xFF;
                    title_pulse_step = 0;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            if (D_8020F1E0_ovl_title == 2) {
                Title_UpdateScreenFade();
                if (title_screen_fade_state == 0) {
                    title_pulse_alpha = 0;
                    title_pulse_step = 8;
                    title_state_timer = 0;
                    D_80226D98_ovl_title = 0;
                    title_flow_state = 3;
                    title_menu_state = 0;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            break;
        case 6:
            Title_UpdateScreen();
            if (D_8020F1E4_ovl_title < 2) {
                D_8020F1E4_ovl_title++;
            } else if ((title_menu_choice & 0xF0) == 0x10) {
                title_flow_state = 8;
                title_screen_fade_frames = 0x3C;
                title_screen_fade_state = 1;
            } else {
                title_flow_state = 8;
                title_screen_fade_frames = 0x3C;
                title_screen_fade_state = 1;
            }
            break;
        case 7:
            Title_UpdateScreen();
            if (D_8020F1E0_ovl_title == 0) {
                title_state_timer = 0x14;
            }
            if (title_menu_state == 2) {
                title_flow_state = 5;
            }
            if ((title_state_timer == 0) && ((title_menu_state == 0xB) || (title_menu_state == 0xC) || (title_menu_state == 0xD) ||
                                      (title_menu_state == 0xE) || (title_menu_state == 9) || (title_menu_state == 0xA))) {
                if (title_menu_state == 9) {
                    title_state_timer = 0xA;
                    title_flow_state = 5;
                    D_8020F1E0_ovl_title = 0;
                    title_menu_state = 2;
                }
                if (title_menu_state == 0xA) {
                    title_state_timer = 0xA;
                    title_flow_state = 5;
                    D_8020F1E0_ovl_title = 0;
                    title_menu_state = 2;
                }
                if (title_menu_state == 0xC) {
                    title_state_timer = 5;
                    title_menu_state = 9;
                    D_8020F1E0_ovl_title = 0;
                }
                if (title_menu_state == 0xB) {
                    title_state_timer = 0x3C;
                    title_flow_state += 1;
                    title_menu_state = 0xF;
                    title_pulse_alpha = 0;
                    title_pulse_step = 0x100;
                    title_screen_fade_frames = 0x3C;
                    title_screen_fade_state = 1;
                    D_8020F1E0_ovl_title = 0;
                }
                if (title_menu_state == 0xD) {
                    title_state_timer = 5;
                    title_menu_state = 0xA;
                    D_8020F1E0_ovl_title = 0;
                }
                if (title_menu_state == 0xE) {
                    title_state_timer = 0xA;
                    title_flow_state = 5;
                    title_menu_state = 2;
                    D_8020F1E0_ovl_title = 0;
                }
            }
            break;
        case 8:
            Title_UpdateSelectionExit();
            Title_UpdateScreenFade();
            break;
    }
    if (title_state_timer == 0) {
        D_8020F1EC_ovl_title = 0;
        title_idle_frames = 0;
    }
    return title_state_timer;
}

void Title_UpdateScreen(void) {
    s32 var_v0;

    gSPDisplayList(gfx_dl_head++, D_8020F208_ovl_title);
    gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, title_pulse_alpha);

    Title_DrawScreenAndMoveCursor((u32)title_menu_state);
    title_pulse_alpha += title_pulse_step;
    if (title_pulse_alpha >= 0x100) {
        title_pulse_alpha = 0xFF;
        title_pulse_step = -title_pulse_step;
    } else if (title_pulse_alpha < 0) {
        title_pulse_alpha = 0;
        title_pulse_alpha = 0;
        title_pulse_step = -title_pulse_step;
    }
    title_confirm_cursor_alpha = title_pulse_alpha;
    if (title_screen_fade_state == 0) {
        if ((title_menu_state == 0) && (input_pressed_buttons & 0x1000)) {
            Sfx_Enqueue(1, 0xFF, 0x40);
            title_pulse_alpha = 0;
            title_pulse_step = 0x80;
            title_menu_state = 1;
            title_state_timer = 0x3C;
        } else if (title_menu_state == 2) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                title_pulse_alpha = 0;
                title_pulse_step = 0x80;
                title_menu_state = 3;
                title_state_timer = 0x3C;
                D_8020F1E0_ovl_title = 1;
            } else if (input_pressed_buttons & 0x4000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                title_pulse_alpha = 0xFF;
                title_pulse_step = 0x80;
                title_menu_state = 4;
                title_state_timer = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((title_menu_state == 8) || (title_menu_state == 7)) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                title_pulse_alpha = 0;
                title_pulse_step = 0x80;
                D_8020F1E0_ovl_title = 1;
                title_state_timer = 0x3C;
                if (title_confirmation_row == 0) {
                    if (title_menu_state == 8) {
                        title_menu_state = 0xB;
                    } else {
                        title_menu_state = 0xD;
                    }
                } else if (title_menu_state == 8) {
                    title_menu_state = 0xC;
                } else {
                    title_menu_state = 0xE;
                }
            } else if (input_pressed_buttons & 0x4000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                title_pulse_alpha = 0xFF;
                title_pulse_step = 0x80;
                title_menu_state = 2;
                title_state_timer = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if (title_menu_state == 6) {
            if (input_pressed_buttons & 0xF000) {
                Sfx_Enqueue(2, 0xFF, 0x40);
                title_pulse_alpha = 0xFF;
                title_pulse_step = 0x80;
                title_menu_state = 2;
                title_state_timer = 2;
            }
        } else if (title_menu_state == 9) {
            if (input_pressed_buttons & 0xB000) {
                Sfx_Enqueue(1, 0xFF, 0x40);
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((title_menu_state == 0xA) && (input_pressed_buttons & 0xB000)) {
            Sfx_Enqueue(1, 0xFF, 0x40);
            D_8020F1E0_ovl_title = 1;
        }
    }
    title_state_timer -= 1;
}

void Title_UpdateSelectionExit(void) {
    gSPDisplayList(gfx_dl_head++, D_8020F208_ovl_title);
    gDPSetEnvColor(gfx_dl_head++, 0x00, 0x00, 0x00, 0xFF);

    Title_DrawScreenAndMoveCursor(title_menu_state);
    if (--title_state_timer == 0) {
        title_menu_state = 0xF;
    }
}
