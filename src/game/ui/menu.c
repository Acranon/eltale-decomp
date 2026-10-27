#include "game/ui/menu.h"
#include "game/audio/sound.h"
#include "game/core/dma.h"
#include "game/core/main.h"
#include "game/event/cutscene.h"
#include "game/input/input.h"
#include "game/map/map.h"
#include "game/player/player.h"
#include "game/save/save_menu.h"
#include "game/text/text.h"
#include "game/text/text_window.h"

/*
 * Start-button menu (game state 2): four pages (stats, map, element levels, options) with
 * slide transitions, its sprite/number drawing helpers, and the map-page location lookup.
 * Also holds .data tables used by other modules.
 * Original file: 2B530.c (ROM 0x2B530).
 */

/* .bss 8008FB30..8008FB70 */
s32 menu_slide_right_x;
s32 menu_slide_left_x;
s32 menu_slide_timer;
u16 menu_map_cursor_active;
u16 menu_flags; /* bits 0-1 page, 0x10 TLUT loaded, 0x20 page edit mode, 0x1000 slide direction, 0x2000 slide, 0x4000 save menu, 0x8000 open */
s8 menu_save_loaded;
s32 menu_frame_counter;
f32 menu_map_marker_x;
f32 menu_map_marker_z;
s32 menu_map_region;
s32 menu_map_spot;
#ifndef NON_MATCHING /* a function static in the NON_MATCHING C */
s32 menu_options_marker_x; /* only Menu_UpdateOptionsPage (asm) uses it */
#endif
f32 menu_map_cursor_saved_x; /* only Menu_UpdateMapPage (asm) uses these two */
f32 menu_map_cursor_saved_y;


void Menu_Init(void) {
    menu_flags = 0x8000;
    save_menu_flags = 0;
    menu_map_cursor_active = 0;
}

void Menu_ResetKeepPage(void) {
    menu_flags = (menu_flags & 3) | 0x8000;
    save_menu_flags = 0;
    menu_map_cursor_active = 0;
}



void Menu_Update(struct GfxFrameData *arg0) {
    gSPDisplayList(gfx_dl_head++, text_glyph_setup_dl);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    Menu_DrawBackground();
    menu_frame_counter++;
    if (menu_flags & 0x4000) {
        SaveMenu_Update();
    } else if (menu_flags & 0x2000) {
        Menu_UpdatePageSlide();
    } else {
        switch ((u16)(menu_flags & 3)) {
            case 0:
                Menu_UpdateStatsPage(0);
                break;
            case 1:
                Menu_UpdateMapPage(0);
                break;
            case 2:
                Menu_UpdateElementsPage(0);
                break;
            case 3:
                Menu_UpdateOptionsPage(0);
                break;
        }
    }
    menu_flags &= ~0x10;
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    gDPSetBlendColor(gfx_dl_head++, 0, 0, 0, 1);
    if ((input_pressed_buttons & 0x5000) && !(menu_flags & 0x6020)) {
        menu_flags &= 0x7FFF;
        Sfx_Play(0, 1, 0xFF);
    }
    if (!(menu_flags & 0x8000)) {
        if (menu_flags & 0x4000) {
            switch ((u16)(menu_flags & 0xC)) {
                case 0:
                    if (save_menu_flags & 0x80) {
                        core_game_mode = 1;
                        menu_save_loaded = 1;
                    } else {
                        core_game_mode = 3;
                        menu_save_loaded = 0;
                    }
                    break;
                case 8:
                    core_game_mode = 3;
                    break;
                case 4:
                    core_game_mode = 1;
                    break;
            }
        } else {
            core_game_mode = 1;
        }
        Menu_ResetKeepPage();
    }
}


void Menu_UpdatePageSlide(void) {
    s32 mode;
    s32 dir = 0;
    s32 d;
    s32 a;
    s32 b;

    d = menu_slide_timer * menu_slide_timer * 0.3125;
    if (menu_flags & 0x1000) {
        menu_slide_right_x = 0x140 - d;
        menu_slide_left_x = -d;
        a = menu_slide_right_x;
        b = menu_slide_left_x;
        if (menu_slide_timer == 0) {
            dir = -1;
        }
    } else {
        menu_slide_right_x = d;
        menu_slide_left_x = d - 0x140;
        a = menu_slide_left_x;
        b = menu_slide_right_x;
        if (menu_slide_timer == 0) {
            dir = 1;
        }
    }
    menu_slide_timer--;
    mode = menu_flags & 3;
    switch (mode) {
        case 0:
            Menu_UpdateStatsPage(a);
            if (menu_flags & 0x1000) {
                Menu_UpdateOptionsPage(b);
            } else {
                Menu_UpdateMapPage(b);
            }
            break;
        case 1:
            Menu_UpdateMapPage(a);
            if (menu_flags & 0x1000) {
                Menu_UpdateStatsPage(b);
            } else {
                Menu_UpdateElementsPage(b);
            }
            break;
        case 2:
            Menu_UpdateElementsPage(a);
            if (menu_flags & 0x1000) {
                Menu_UpdateMapPage(b);
            } else {
                Menu_UpdateOptionsPage(b);
            }
            break;
        case 3:
            Menu_UpdateOptionsPage(a);
            if (menu_flags & 0x1000) {
                Menu_UpdateElementsPage(b);
            } else {
                Menu_UpdateStatsPage(b);
            }
            break;
    }
    if (dir != 0) {
        menu_flags &= ~0x2000;
        menu_flags &= ~0x1000;
        mode += dir;
        menu_flags &= ~3;
        menu_flags |= mode & 3;
    }
}

extern u16 D_8007A9D4;
extern u16 D_8007A9D6;
extern u16 D_8007A9D8;
extern u16 D_8007A9DA;
extern u16 D_8007A9DC;
extern u16 D_8007A9DE;
extern u16 D_8007A9F8;
extern u16 D_8007A9FA;
extern u16 D_8007A9FC;
extern u16 D_8007A9FE;
extern u8 D_8007AA00;
extern u8 D_8007AA01;
extern u8 D_8007AA02;
extern u8 D_8007AA03;
extern s32 D_8007AA10;

void Menu_UpdateStatsPage(s32 x) {
    s32 px;
    s32 i;
    f32 f;
    s32 pad[2]; // unused locals in the original (frame size)

    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, 255);
    Menu_DrawSprite(0, x + 0x28, 0x1E, 0xF0, 0x98);
    Menu_DrawSprite(0x37, x + 0x2B, 0xB7, 0xF0, 3);
    Menu_DrawSprite(0x37, x + 0x119, 0x24, 2, 0x96);
    Menu_DrawSprite(0x37, x + 0x27, 0x1D, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0xB6, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0x1D, 1, 0x9A);
    Menu_DrawSprite(0x37, x + 0x118, 0x1D, 1, 0x9A);
    Menu_DrawSprite(0x38, x + 0x29, 0x1F, 0xED, 1);
    Menu_DrawSprite(0x38, x + 0x29, 0x1F, 1, 0x95);
    Menu_DrawSprite(0x39, x + 0x29, 0xB4, 0xEE, 1);
    Menu_DrawSprite(0x39, x + 0x116, 0x1F, 1, 0x96);
    Menu_DrawSprite(0x3C, x + 0x3A, 0x1E, 0x15, 0x98);
    px = 0x4B;
    for (i = 0; i < 3; i++, px += 0x21) {
        Menu_DrawSprite(0x3D, x + 0x5D, px, 0xA7, 2);
    }
    px = 0x40;
    for (i = 0; i < 4; i++, px += 0x21) {
        Menu_DrawSprite(0x32, x + 0x63, px, 0x3C, 7);
    }
    px = 0x3C;
    for (i = 0; i < 4; i++, px += 0x21) {
        Menu_DrawSprite(0x20, x + 0xC3, px, 0x13, 11);
    }
    Menu_DrawSprite(0x1B, x + 0x38, 0x34, 0x18, 0xE);
    Menu_DrawSprite(0x1C, x + 0x37, 0x54, 0x1C, 0xD);
    Menu_DrawSprite(0x1D, x + 0x35, 0x78, 0x24, 0xF);
    Menu_DrawSprite(0x1E, x + 0x35, 0x99, 0x1C, 0xE);
    Menu_DrawSprite(5, x + 0x45, 0x1C, 8, 8);
    Menu_DrawSprite(5, x + 0xF3, 0x1C, 8, 8);
    i = menu_frame_counter;
    i = (i >> 2) & 0xF;
    i = menu_wobble_offsets[i];
    Menu_DrawSprite(6, x + i + 0x36, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(7, x - i + 0xFB, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(0x14, x + 0x79, 0x35, 8, 0xA);
    Menu_DrawSprite(0x14, x + 0x79, 0x56, 8, 0xA);
    i = D_8007A9D6;
    Menu_DrawNumber(3, x + 0x80, 0x35, i, 0xA);
    i = D_8007A9DA;
    Menu_DrawNumber(3, x + 0x80, 0x56, i, 0xA);
    i = D_8007A9D4;
    Menu_DrawNumber(3, x + 0x64, 0x35, i, 0xA);
    i = D_8007A9D8;
    Menu_DrawNumber(3, x + 0x64, 0x56, i, 0xA);
    i = D_8007A9DE;
    Menu_DrawNumber(3, x + 0x80, 0x77, i, 0xA);
    i = D_8007A9DC;
    Menu_DrawNumber(3, x + 0x80, 0x98, i, 0xA);
    i = player_stat_xp_costs[D_8007AA00];
    Menu_DrawNumber(3, x + 0xDA, 0x3B, D_8007A9F8 * 100 / i, 0xA);
    i = player_stat_xp_costs[D_8007AA01];
    if (D_8007AA10 & 0x4000) {
        i = i * 3;
    } else {
        i = i * 4;
    }
    Menu_DrawNumber(3, x + 0xDA, 0x5C, D_8007A9FA * 100 / i, 0xA);
    i = player_stat_xp_costs[D_8007AA03];
    if (D_8007AA10 & 0x2000) {
        i = (f32) i * 0.8;
    }
    Menu_DrawNumber(3, x + 0xDA, 0x7D, D_8007A9FE * 100 / i, 0xA);
    i = player_stat_xp_costs[D_8007AA02];
    if (D_8007AA10 & 0x8000) {
        i = (f32) i * 0.8;
    }
    Menu_DrawNumber(3, x + 0xDA, 0x9E, D_8007A9FC * 100 / i, 0xA);
    f = (u32)D_8007A9D4;
    f /= (u32)D_8007A9D6;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0x64, 0x41, f, 3);
    f = (u32)D_8007A9D8;
    f /= (u32)D_8007A9DA;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0x64, 0x62, f, 3);
    f = (u32)D_8007A9DE;
    f /= 255.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0x64, 0x83, f, 3);
    f = (u32)D_8007A9DC;
    f /= 255.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0x64, 0xA4, f, 3);
    Menu_DrawSprite(0x15, x + 0xF6, 0x3B, 8, 0xA);
    Menu_DrawSprite(0x15, x + 0xF6, 0x5C, 8, 0xA);
    Menu_DrawSprite(0x15, x + 0xF6, 0x7D, 8, 0xA);
    Menu_DrawSprite(0x15, x + 0xF6, 0x9E, 8, 0xA);
    Menu_DrawSprite(0x1A, x + 0x77, 0x19, 0x52, 0xD);
    if (!(menu_flags & 0x2000)) {
        if (input_stick_x > 20 || (input_held_buttons & 0x10)) {
            menu_flags |= 0x2000;
            menu_slide_timer = 31;
            Sfx_Play(0, 0, 0xFF);
        } else if (input_stick_x < -20 || (input_held_buttons & 0x2000)) {
            menu_flags |= 0x3000;
            menu_slide_timer = 31;
            Sfx_Play(0, 0, 0xFF);
        }
    }
}

#ifdef NON_MATCHING
/* context for the NON_MATCHING Menu_UpdateOptionsPage and Menu_UpdateMapPage (their data is defined below) */
#endif

#ifdef NON_MATCHING
/* stack homes and register allocation differ; code is equivalent */
void Menu_UpdateOptionsPage(s32 x) {
    s32 wob;
    s32 sel;
    s32 y;
    u8 ids[3] = { 0x28, 0x27, 0x26 }; /* the retail build keeps these bytes as the file-scope menu_options_marker_sprites */
    static s32 menu_options_marker_x; /* the retail build keeps it as the file-scope menu_options_marker_x */

    menu_text_delay_option = 4 - menu_text_delay_option;
    Menu_DrawSprite(0, x + 0x28, 0x1E, 0xF0, 0x6C);
    Menu_DrawSprite(0x37, x + 0x2B, 0x8B, 0xF0, 3);
    Menu_DrawSprite(0x37, x + 0x119, 0x24, 2, 0x68);
    Menu_DrawSprite(0x37, x + 0x27, 0x1D, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0x8A, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0x1E, 1, 0x6D);
    Menu_DrawSprite(0x37, x + 0x118, 0x1E, 1, 0x6D);
    Menu_DrawSprite(0x38, x + 0x29, 0x1F, 0xED, 1);
    Menu_DrawSprite(0x38, x + 0x29, 0x20, 1, 0x68);
    Menu_DrawSprite(0x39, x + 0x29, 0x88, 0xEE, 1);
    Menu_DrawSprite(0x39, x + 0x116, 0x1F, 1, 0x69);
    Menu_DrawSprite(0x3C, x + 0x3A, 0x1E, 0x15, 0x6C);
    Menu_DrawSprite(0x3D, x + 0x5D, 0x56, 0xA7, 2);
    Menu_DrawSprite(0x24, x + 0x8D, 0x3E, 0x54, 7);
    Menu_DrawSprite(0x24, x + 0x8D, 0x6C, 0x54, 7);
    Menu_DrawSprite(0x57, x + 0xE9, 0x3C, 0x1A, 9);
    Menu_DrawSprite(0x56, x + 0x6C, 0x3C, 0x1A, 9);
    Menu_DrawSprite(0x29, x + 0xE9, 0x6B, 0x1A, 9);
    Menu_DrawSprite(0x2A, x + 0x6C, 0x6B, 0x1A, 9);
    Menu_DrawSprite(0x22, x + 0x31, 0x3B, 0x36, 0xC);
    Menu_DrawSprite(0x23, x + 0x35, 0x68, 0x2A, 0xC);
    Menu_DrawSprite(5, x + 0x45, 0x1C, 7, 7);
    Menu_DrawSprite(5, x + 0xF3, 0x1C, 7, 7);
    wob = menu_frame_counter;
    wob = (wob >> 2) & 0xF;
    wob = menu_wobble_offsets[wob];
    Menu_DrawSprite(6, x + wob + 0x36, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(7, x - wob + 0xFB, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(0x21, x + 0x75, 0x18, 0x56, 0xE);
    Menu_DrawSprite(0x25, x + 0x8E, 0x3F, 0x50, 3);
    Menu_DrawSprite(0x25, x + 0x8E, 0x6D, 0x50, 3);
    Menu_DrawSprite(0x27, x + 0xB3, 0x39, 8, 0xB);
    Menu_DrawSprite(0x27, x + 0xB3, 0x67, 8, 0xB);
    if (menu_flags & 0x200) {
        switch (menu_flags & 0x100) {
            case 0:
                Menu_DrawSprite(ids[menu_options_bgm_row_pos[menu_bgm_volume_option][1]], menu_options_bgm_row_pos[menu_bgm_volume_option][0] + x, 0x67, 8, 0xB);
                break;
            case 0x100:
                Menu_DrawSprite(ids[menu_options_top_row_pos[menu_text_delay_option][1]], menu_options_top_row_pos[menu_text_delay_option][0] + x, 0x39, 8, 0xB);
                break;
        }
    } else {
        Menu_DrawSprite(ids[menu_options_bgm_row_pos[menu_bgm_volume_option][1]], menu_options_bgm_row_pos[menu_bgm_volume_option][0] + x, 0x67, 8, 0xB);
        Menu_DrawSprite(ids[menu_options_top_row_pos[menu_text_delay_option][1]], menu_options_top_row_pos[menu_text_delay_option][0] + x, 0x39, 8, 0xB);
    }
    if (menu_flags & 0x2000) {
        menu_text_delay_option = 4 - menu_text_delay_option;
        return;
    }
    if (!(menu_flags & 0x800)) {
        if (input_stick_x > 0x14 || (input_held_buttons & 0x10)) {
            menu_flags |= 0x2000;
            menu_slide_timer = 0x1F;
            Sfx_Play(0, 0, 0xFF);
        } else if (input_stick_x < -0x14 || (input_held_buttons & 0x2000)) {
            menu_flags |= 0x3000;
            menu_slide_timer = 0x1F;
            Sfx_Play(0, 0, 0xFF);
        }
        if (input_pressed_buttons & 0x8000) {
            menu_flags |= 0x820;
            Sfx_Play(0, 1, 0xFF);
        }
    } else {
        if ((input_pressed_buttons & 0x8000) && !(menu_flags & 0x200)) {
            menu_flags &= ~0x920;
            Sfx_Play(0, 2, 0xFF);
            menu_text_delay_option = 4 - menu_text_delay_option;
            return;
        }
        wob = menu_frame_counter;
        wob = (wob >> 1) & 0xF;
        wob = menu_wobble_offsets[wob];
        sel = menu_flags & 0x100;
        if (menu_flags & 0x200) {
            switch (sel) {
                case 0:
                    if (menu_options_marker_x < menu_options_top_row_pos[menu_text_delay_option][0]) {
                    } else if (menu_options_top_row_pos[menu_text_delay_option][0] < menu_options_marker_x) {
                    } else {
                        menu_flags &= ~0x200;
                        menu_flags &= ~0x400;
                        sel = ids[menu_options_top_row_pos[menu_text_delay_option][1]];
                        if (input_stick_x < 0x14 && input_stick_x > -0x14) {
                            Menu_DrawSprite(sel, menu_options_marker_x + x, 0x39, 8, 0xB);
                        }
                        y = 0x3A;
                        sel = 0;
                    }
                    break;
                case 0x100:
                    if (menu_options_marker_x < menu_options_bgm_row_pos[menu_bgm_volume_option][0]) {
                    } else if (menu_options_bgm_row_pos[menu_bgm_volume_option][0] < menu_options_marker_x) {
                    } else {
                        menu_flags &= ~0x200;
                        menu_flags &= ~0x400;
                        sel = ids[menu_options_bgm_row_pos[menu_bgm_volume_option][1]];
                        if (input_stick_x < 0x14 && input_stick_x > -0x14) {
                            Menu_DrawSprite(sel, menu_options_marker_x + x, 0x67, 8, 0xB);
                        }
                        y = 0x65;
                        sel = 0x100;
                    }
                    break;
            }
        }
        if (!(menu_flags & 0x200)) {
            switch (sel) {
                case 0:
                    y = 0x3A;
                    if (input_stick_y < -0x1E || input_stick_y > 0x1E) {
                        if (!(menu_flags & 0x400)) {
                            menu_flags &= ~0x100;
                            menu_flags |= 0x100;
                            menu_flags |= 0x400;
                            Sfx_Play(0, 0, 0xFF);
                        }
                    } else if (input_stick_x < -0x14) {
                        if (!(menu_flags & 0x400)) {
                            menu_options_marker_x = menu_options_top_row_pos[menu_text_delay_option--][0];
                            if (menu_text_delay_option < 0) {
                                menu_text_delay_option = 0;
                            }
                            menu_flags |= 0x600;
                        }
                    } else if (input_stick_x > 0x14) {
                        if (!(menu_flags & 0x400)) {
                            menu_options_marker_x = menu_options_top_row_pos[menu_text_delay_option++][0];
                            if (menu_text_delay_option > 4) {
                                menu_text_delay_option = 4;
                            }
                            menu_flags |= 0x600;
                        }
                    } else {
                        menu_flags &= ~0x400;
                    }
                    break;
                case 0x100:
                    y = 0x65;
                    if (input_stick_y < -0x1E || input_stick_y > 0x1E) {
                        if (!(menu_flags & 0x400)) {
                            menu_flags &= ~0x100;
                            menu_flags |= 0;
                            menu_flags |= 0x400;
                            Sfx_Play(0, 0, 0xFF);
                        }
                    } else if (input_stick_x < -0x14) {
                        if (!(menu_flags & 0x400)) {
                            menu_options_marker_x = menu_options_bgm_row_pos[menu_bgm_volume_option--][0];
                            if (menu_bgm_volume_option < 0) {
                                menu_bgm_volume_option = 0;
                            }
                            menu_flags |= 0x400;
                            menu_flags |= 0x200;
                        }
                    } else if (input_stick_x > 0x14) {
                        if (!(menu_flags & 0x400)) {
                            menu_options_marker_x = menu_options_bgm_row_pos[menu_bgm_volume_option++][0];
                            if (menu_bgm_volume_option > 4) {
                                menu_bgm_volume_option = 4;
                            }
                            menu_flags |= 0x400;
                            menu_flags |= 0x200;
                        }
                    } else {
                        menu_flags &= ~0x400;
                    }
                    break;
            }
        }
        if (menu_flags & 0x200) {
            s32 pos;

            switch (sel) {
                case 0:
                    y = 0x3A;
                    pos = menu_options_marker_x + x;
                    if (menu_options_marker_x < menu_options_top_row_pos[menu_text_delay_option][0]) {
                        menu_options_marker_x++;
                        pos++;
                        sel = ids[menu_options_top_row_pos[menu_text_delay_option - 1][1]];
                    } else if (menu_options_top_row_pos[menu_text_delay_option][0] < menu_options_marker_x) {
                        menu_options_marker_x--;
                        pos--;
                        sel = ids[menu_options_top_row_pos[menu_text_delay_option + 1][1]];
                    } else {
                        menu_flags &= ~0x400;
                        sel = ids[menu_options_top_row_pos[menu_text_delay_option][1]];
                    }
                    Menu_DrawSprite(sel, pos, 0x39, 8, 0xB);
                    break;
                case 0x100:
                    y = 0x65;
                    pos = menu_options_marker_x + x;
                    if (menu_options_marker_x < menu_options_bgm_row_pos[menu_bgm_volume_option][0]) {
                        menu_options_marker_x++;
                        pos++;
                        sel = ids[menu_options_bgm_row_pos[menu_bgm_volume_option - 1][1]];
                    } else if (menu_options_bgm_row_pos[menu_bgm_volume_option][0] < menu_options_marker_x) {
                        menu_options_marker_x--;
                        pos--;
                        sel = ids[menu_options_bgm_row_pos[menu_bgm_volume_option + 1][1]];
                    } else {
                        menu_flags &= ~0x400;
                        sel = ids[menu_options_bgm_row_pos[menu_bgm_volume_option][1]];
                    }
                    Menu_DrawSprite(sel, pos, 0x67, 8, 0xB);
                    break;
            }
        }
        Menu_DrawSprite(1, x - wob + 0x1E, y, 0x10, 0xD);
    }
    menu_text_delay_option = 4 - menu_text_delay_option;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/ui/menu/Menu_UpdateOptionsPage.s")
#endif

#ifdef NON_MATCHING
/* frame, stack homes and register allocation differ; code is equivalent */
void Menu_UpdateMapPage(s32 arg0) {
    static s32 menu_map_loaded_region = -1; /* the retail build keeps it as the file-scope menu_map_loaded_region */
    s32 cx;
    s32 cy;
    s32 x;
    f32 f;
    s32 s;
    s32 n;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;
    s32 ox;
    s32 w;
    s32 h;
    s32 y;
    s32 i;

    s = 0;
    if (menu_map_region < 6) {
        if (menu_map_region != menu_map_loaded_region) {
            Dma_ReadRom(menu_map_picture_dma[menu_map_region].start, menu_map_picture_dma[menu_map_region].dst,
                          menu_map_picture_dma[menu_map_region].end - menu_map_picture_dma[menu_map_region].start);
            menu_map_loaded_region = menu_map_region;
        }
        w = 0xF4;
        h = 8;
        x = arg0 + 0x27;
        y = 0x1D;
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal256(gfx_dl_head++, menu_map_tluts[menu_map_region]);
            for (i = 0; i < 24; i++) {
                if (i == 23) {
                    h = 1;
                }
                gDPLoadTextureTile(gfx_dl_head++, menu_map_strips[menu_map_region * 24 + i], G_IM_FMT_CI, G_IM_SIZ_8b, 244, h, 0, 0,
                                   243, h - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx_dl_head++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                    1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
                y += h;
            }
            SaveMenu_SetTextDrawState();
        }
    } else {
        Menu_DrawSprite(0, arg0 + 0x28, 0x1E, 0xF0, 0xB4);
        Menu_DrawSprite(0x38, arg0 + 0x29, 0x1F, 0xED, 1);
        Menu_DrawSprite(0x38, arg0 + 0x29, 0x20, 1, 0xB1);
        Menu_DrawSprite(0x39, arg0 + 0x29, 0xD0, 0xEE, 1);
        Menu_DrawSprite(0x39, arg0 + 0x117, 0x1F, 1, 0xB2);
        Menu_DrawSprite(0x37, arg0 + 0x2C, 0xD4, 0xF0, 3);
        Menu_DrawSprite(0x37, arg0 + 0x11A, 0x25, 2, 0xB2);
        Menu_DrawSprite(0x37, arg0 + 0x27, 0x1D, 0xF2, 1);
        Menu_DrawSprite(0x37, arg0 + 0x27, 0xD3, 0xF2, 1);
        Menu_DrawSprite(0x37, arg0 + 0x27, 0x1E, 1, 0xB3);
        Menu_DrawSprite(0x37, arg0 + 0x119, 0x1E, 1, 0xB3);
        if (menu_map_region != menu_map_loaded_region) {
            Dma_ReadRom(menu_map_picture_dma[menu_map_region].start, menu_map_picture_dma[menu_map_region].dst,
                          menu_map_picture_dma[menu_map_region].end - menu_map_picture_dma[menu_map_region].start);
            menu_map_loaded_region = menu_map_region;
        }
        n = menu_map_region - 6;
        w = menu_map_small_sizes[n][0];
        h = menu_map_small_sizes[n][1];
        x = menu_map_small_pos[n * 2] + arg0;
        y = menu_map_small_pos[n * 2 + 1];
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPLoadTLUT_pal256(gfx_dl_head++, menu_map_small_tluts[n]);
            menu_flags &= ~0x10;
            gDPLoadTextureTile(gfx_dl_head++, menu_map_small_tex[n * 2], G_IM_FMT_CI, G_IM_SIZ_8b, menu_map_small_sizes[n][0], menu_map_small_sizes[n][1], 0, 0,
                               menu_map_small_sizes[n][0] - 1, menu_map_small_sizes[n][1] - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(gfx_dl_head++);
            gSPTextureRectangle(gfx_dl_head++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                1 << 10, 1 << 10);
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTextureTile(gfx_dl_head++, menu_map_small_tex[n * 2 + 1], G_IM_FMT_CI, G_IM_SIZ_8b, menu_map_small_sizes[n][0], menu_map_small_sizes[n][2], 0, 0,
                               menu_map_small_sizes[n][0] - 1, menu_map_small_sizes[n][2] - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(gfx_dl_head++);
            gSPTextureRectangle(gfx_dl_head++, x << 2, (y + menu_map_small_sizes[n][1]) << 2, (x + w) << 2, (y + h + menu_map_small_sizes[n][2]) << 2,
                                G_TX_RENDERTILE, s, 0, 1 << 10, 1 << 10);
            SaveMenu_SetTextDrawState();
        }
    }
    Menu_DrawSprite(5, arg0 + 0x45, 0x1C, 7, 7);
    Menu_DrawSprite(5, arg0 + 0xF3, 0x1C, 7, 7);
    n = (menu_frame_counter >> 2) & 0xF;
    n = menu_wobble_offsets[n];
    Menu_DrawSprite(6, arg0 + n + 0x36, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(7, arg0 - n + 0xFB, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(0x2B, arg0 + 0x83, 0x18, 0x3A, 0x10);
    if (menu_map_region < 6) {
        if (menu_map_spot < 0) {
            cx = (s32) player_state.actor.x / menu_map_world_scale[menu_map_region] + menu_map_origin[menu_map_region];
            cy = (s32) player_state.actor.z / menu_map_world_scale[menu_map_region + 6] + menu_map_origin[menu_map_region + 6];
        } else {
            cx = menu_map_spot_coords[menu_map_region * 18 + menu_map_spot * 2];
            cy = menu_map_spot_coords[menu_map_region * 18 + menu_map_spot * 2 + 1];
        }
        if (menu_frame_counter & 0x20) {
            Menu_DrawSprite(0x2C, arg0 + cx + 0x23, cy + 0xD, 0xC, 0x10);
        }
        if (menu_map_spot < 0) {
            sx = menu_map_world_scale[menu_map_region];
            sy = menu_map_world_scale[menu_map_region + 6];
            px = menu_map_origin[menu_map_region];
            py = menu_map_origin[menu_map_region + 6];
            if (menu_map_cursor_x == -1.0f) {
                menu_map_cursor_x = cx;
                menu_map_cursor_y = cy;
            }
            if (menu_map_cursor_active != 0) {
                f = input_stick_x;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                menu_map_cursor_x += f * 0.08;
                f = input_stick_y;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                menu_map_cursor_y -= f * 0.08;
                if (menu_map_cursor_x < 6.0f) {
                    menu_map_cursor_x = 6.0f;
                } else if (menu_map_cursor_x > 236.0f) {
                    menu_map_cursor_x = 236.0f;
                }
                if (menu_map_cursor_y < 6.0f) {
                    menu_map_cursor_y = 6.0f;
                } else if (menu_map_cursor_y > 178.0f) {
                    menu_map_cursor_y = 178.0f;
                }
            }
            menu_map_marker_x = sx * ((s32) menu_map_cursor_x - px);
            menu_map_marker_z = sy * ((s32) menu_map_cursor_y - py);
            y = 0;
            h = 5;
            ox = -2;
            if (menu_map_cursor_active != 0) {
                y = -2;
                h = 6;
            }
            Menu_DrawSprite(0x55, arg0 + menu_map_cursor_x + 39.0f + ox, menu_map_cursor_y + 29.0f - 1.0f, h, 1);
            Menu_DrawSprite(4, arg0 + menu_map_cursor_x + 39.0f - 2.0f, menu_map_cursor_y + 29.0f - 12.0f + y, 0xC, 0xC);
        }
    }
    if (!(menu_flags & 0x2000)) {
        if (menu_map_cursor_active == 0) {
            if (input_stick_x > 20 || (input_held_buttons & 0x10)) {
                menu_flags |= 0x2000;
                menu_slide_timer = 31;
                Sfx_Play(0, 0, 0xFF);
            } else if (input_stick_x < -20 || (input_held_buttons & 0x2000)) {
                menu_flags |= 0x3000;
                menu_slide_timer = 31;
                Sfx_Play(0, 0, 0xFF);
            }
        }
        if (menu_map_region < 6 && menu_map_spot < 0) {
            if (menu_map_cursor_active == 0) {
                menu_map_cursor_saved_x = menu_map_cursor_x;
                menu_map_cursor_saved_y = menu_map_cursor_y;
            }
            if (input_pressed_buttons & 0x8000) {
                menu_map_cursor_active ^= 1;
                menu_flags ^= 0x20;
                Sfx_Play(0, 0x17, 0xFF);
            } else if ((input_pressed_buttons & 0x4000) && menu_map_cursor_active != 0) {
                menu_map_cursor_x = menu_map_cursor_saved_x;
                menu_map_cursor_y = menu_map_cursor_saved_y;
                Sfx_Play(0, 0x13, 0xFF);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/ui/menu/Menu_UpdateMapPage.s")
#endif

extern u8 D_8007A9F4;
extern u8 D_8007A9F5;
extern u8 D_8007A9F6;
extern u8 D_8007A9F7;
extern s32 D_8007A9E0;
extern u8 D_8007AA04;

void Menu_UpdateElementsPage(s32 x) {
    s32 p;
    s32 v;
    f32 f;

    Menu_DrawSprite(0, x + 0x28, 0x1E, 0xF0, 0x9F);
    Menu_DrawSprite(0x37, x + 0x2B, 0xBE, 0xF0, 3);
    Menu_DrawSprite(0x37, x + 0x119, 0x24, 2, 0x9A);
    Menu_DrawSprite(0x37, x + 0x27, 0x1D, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0xBD, 0xF2, 1);
    Menu_DrawSprite(0x37, x + 0x27, 0x1E, 1, 0x9F);
    Menu_DrawSprite(0x37, x + 0x118, 0x1E, 1, 0x9F);
    Menu_DrawSprite(0x38, x + 0x29, 0x1F, 0xED, 1);
    Menu_DrawSprite(0x38, x + 0x29, 0x20, 1, 0x9B);
    Menu_DrawSprite(0x39, x + 0x29, 0xBB, 0xEE, 1);
    Menu_DrawSprite(0x39, x + 0x116, 0x1F, 1, 0x9C);
    Menu_DrawSprite(5, x + 0x45, 0x1C, 7, 7);
    Menu_DrawSprite(5, x + 0xF3, 0x1C, 7, 7);
    p = menu_frame_counter;
    p = (p >> 2) & 0xF;
    p = menu_wobble_offsets[p];
    Menu_DrawSprite(6, x + p + 0x36, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(7, x - p + 0xFB, 0x1A, 0xE, 0xB);
    Menu_DrawSprite(0x2D, x + 0x75, 0x19, 0x56, 0xD);
    Menu_DrawSprite(0x32, x + 0xA5, 0x35, 0x35, 6);
    Menu_DrawSprite(0x32, x + 0x31, 0x78, 0x35, 6);
    Menu_DrawSprite(0x32, x + 0xD9, 0x78, 0x35, 6);
    Menu_DrawSprite(0x32, x + 0xA5, 0xAE, 0x35, 6);
    Menu_DrawSprite(0x14, x + 0x86, 0x34, 8, 0xA);
    Menu_DrawSprite(0x14, x + 0x47, 0x6B, 8, 0xA);
    Menu_DrawSprite(0x14, x + 0xF0, 0x6B, 8, 0xA);
    Menu_DrawSprite(0x14, x + 0x86, 0xAD, 8, 0xA);
    Menu_DrawSprite(0x2E, x + 0x9A, 0x3D, 0xC, 0xC);
    Menu_DrawSprite(0x2F, x + 0x67, 0x6F, 0xC, 0xC);
    Menu_DrawSprite(0x30, x + 0xCC, 0x6F, 0xC, 0xC);
    Menu_DrawSprite(0x31, x + 0x9A, 0xA1, 0xC, 0xC);
    Menu_DrawSprite(0x15, x + 0xA7, 0x92, 8, 0xA);
    Menu_DrawNumber(2, x + 0x8D, 0x34, 50, 0xA);
    Menu_DrawNumber(2, x + 0x4E, 0x6B, 50, 0xA);
    Menu_DrawNumber(2, x + 0xF7, 0x6B, 50, 0xA);
    Menu_DrawNumber(2, x + 0x8D, 0xAD, 50, 0xA);
    p = D_8007A9F4;
    Menu_DrawNumber(2, x + 0x78, 0x34, p, 0xA);
    p = D_8007A9F5;
    Menu_DrawNumber(2, x + 0x39, 0x6B, p, 0xA);
    p = D_8007A9F7;
    Menu_DrawNumber(2, x + 0xE2, 0x6B, p, 0xA);
    p = D_8007A9F6;
    Menu_DrawNumber(2, x + 0x78, 0xAD, p, 0xA);
    f = (u32)D_8007A9F4;
    f /= 50.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0xA6, 0x36, f, 3);
    f = (u32)D_8007A9F5;
    f /= 50.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0x32, 0x79, f, 3);
    f = (u32)D_8007A9F7;
    f /= 50.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0xDA, 0x79, f, 3);
    f = (u32)D_8007A9F6;
    f /= 50.0f;
    f *= 50.0f;
    Menu_DrawSprite(0x33, x + 0xA6, 0xAF, f, 3);
    v = D_8007A9E0 * 100 / player_level_exp_table[D_8007AA04];
    if (v > 100) {
        v = 100;
    }
    Menu_DrawNumber(3, x + 0x91, 0x92, v, 0xA);
    Menu_DrawExpGauge(v, x);
    if (!(menu_flags & 0x2000)) {
        if (input_stick_x > 20 || (input_held_buttons & 0x10)) {
            menu_flags |= 0x2000;
            menu_slide_timer = 31;
            Sfx_Play(0, 0, 0xFF);
        } else if (input_stick_x < -20 || (input_held_buttons & 0x2000)) {
            menu_flags |= 0x3000;
            menu_slide_timer = 31;
            Sfx_Play(0, 0, 0xFF);
        }
    }
}

#ifdef NON_MATCHING
/* w, s, lrs and lrt are kept in registers where retail reloads them from the stack; code is equivalent */

void Menu_DrawSprite(s32 id, s32 x, s32 y, s32 w, s32 h) {
    s32 ret;
    s32 alpha;
    s32 xr;
    s32 masks;
    s32 maskt;
    s32 ult;
    s32 uls;
    s32 s;
    s32 t;
    s32 dsdx;
    s32 dtdy;
    s32 texH;
    s32 d;
    s32 lrs;
    s32 lrt;
    u8* tex;
    s32 texW;
    s32 pad[2];

    tex = menu_sprite_tex[id];
    texW = menu_sprite_sizes[id][0];
    texH = menu_sprite_sizes[id][1];
    lrs = texW - 1;
    lrt = texH - 1;
    alpha = 0;
    ret = 0;
    maskt = 0;
    masks = 0;
    s = 0;
    t = 0;
    uls = 0;
    ult = 0;
    dtdy = 0x400;
    dsdx = 0x400;

    switch (id) {
        case 0:
            maskt = 4;
            masks = 4;
            s = (x & 0xF) << 5;
            t = (y & 0xF) << 5;
            break;
        case 0x3C:
            alpha = -0x80;
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3E:
            alpha = 0x50;
            break;
        case 0x37:
        case 0x38:
        case 0x39:
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3D:
            dsdx = 0;
            break;
    }
    if (x < 0) {
        if (x + w < 0) {
            ret = -1;
        } else {
            d = -x;
            s += d << 5;
            x = 0;
            w -= d;
        }
    }
    if (x > 320) {
        ret = -1;
    } else if ((xr = x + w) > 320) {
        w = w - xr + 320;
    }
    if (w <= 0 || h <= 0) {
        ret = -1;
    }
    if (ret >= 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
        gDPPipeSync(gfx_dl_head++);
        if (alpha == 0) {
            gSPDisplayList(gfx_dl_head++, menu_sprite_opaque_dl);
        } else {
            gSPDisplayList(gfx_dl_head++, menu_sprite_alpha_dl);
            gDPPipeSync(gfx_dl_head++);
            gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, alpha);
        }
        if (!(menu_flags & 0x10)) {
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal256(gfx_dl_head++, menu_sprite_tlut);
            menu_flags |= 0x10;
        }
        gDPLoadTextureTile(gfx_dl_head++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, texW, 0, uls, ult, lrs, lrt, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx_dl_head++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, t, dsdx,
                            dtdy);
        gDPPipeSync(gfx_dl_head++);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/ui/menu/Menu_DrawSprite.s")
#endif


void Menu_DrawExpGauge(s32 arg0, s32 arg1) {
    s32 k;
    s32 j;
    s32 d;
    MenuExpGaugePalettes pals = menu_exp_gauge_tluts;
    MenuExpGaugeTextures tex = menu_exp_gauge_tex;
    s32 xr;
    s32 x;
    s32 y;
    s32 w;
    s32 h = 0;
    s32 texW;
    s32 texH;
    s32 ult;
    s32 s[1];
    s32 t;
    s32 ret;

    for (k = 0; k < 4; k++) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0x504240, 0);
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
        gDPPipeSync(gfx_dl_head++);
        if (k != 1) {
            gSPDisplayList(gfx_dl_head++, menu_sprite_opaque_dl);
        } else {
            gSPDisplayList(gfx_dl_head++, menu_sprite_alpha_dl);
            gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, 0x80);
        }
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, pals.v[k]);
        for (j = 0; j < 2; j++) {
            s[0] = 0;
            switch (k) {
                case 2:
                    x = arg1 + 0x87;
                    ult = 0x32 - arg0 / 2;
                    y = ult + 0x52;
                    w = 0x19;
                    h = 0x32;
                    texW = 0x19;
                    texH = 0x32;
                    t = ult << 5;
                    break;
                case 3:
                    ult = 0;
                    t = 0;
                    x = arg1 + 0x84;
                    y = 0x4F;
                    w = 0x1C;
                    h = 0x38;
                    texW = 0x1C;
                    texH = 0x38;
                    break;
                default:
                    ult = 0;
                    t = 0;
                    x = arg1 + 0x87;
                    y = 0x52;
                    w = 0x19;
                    h = 0x32;
                    texW = 0x19;
                    texH = 0x32;
                    break;
            }
            x += w * j;
            if (x < 0 && x + w >= 0) {
                d = -x;
                x = 0;
                w -= d;
                s[0] = d << 5;
            }
            if (x > 320) {
                ret = -1;
            } else {
                ret = 0;
                xr = x + w;
                if (xr > 320) {
                    w = w - xr + 320;
                }
            }
            if (w <= 0) {
                ret = -1;
            }
            if (ret >= 0) {
                gDPLoadTextureTile(gfx_dl_head++, tex.v[k][j], G_IM_FMT_CI, G_IM_SIZ_8b, texW, texH, 0, ult, texW - 1,
                                   texH - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx_dl_head++, x << 2, y << 2, (x + w) << 2, (y + h - ult) << 2, G_TX_RENDERTILE, s[0],
                                    t, 1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
            }
        }
    }
    menu_flags &= ~0x10;
}


void Menu_DrawBackground(void) {
    s32 i;
    s32 y;
    MenuFourWords texH = menu_bg_strip_tex_heights;
    MenuFourWords stripH = menu_bg_strip_heights;
    MenuFourPointers tex = menu_bg_strip_tex;

    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, menu_bg_tlut);
    menu_flags &= ~0x10;
    for (i = 0, y = 22; i < 4; i++) {
        gDPLoadTextureTile(gfx_dl_head++, tex.v[i], G_IM_FMT_CI, G_IM_SIZ_8b, 64, texH.v[i], 0, 0, 63, texH.v[i] - 1, 0,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx_dl_head++, 23 << 2, y << 2, 297 << 2, (y + stripH.v[i]) << 2, G_TX_RENDERTILE, 0, 0,
                            0x4A8, 0x4E6);
        gDPPipeSync(gfx_dl_head++);
        y += stripH.v[i];
    }
    for (i = 3, y = 120; i >= 0; i--) {
        gDPLoadTextureTile(gfx_dl_head++, tex.v[i], G_IM_FMT_CI, G_IM_SIZ_8b, 64, texH.v[i], 0, 0, 63, texH.v[i] - 1, 0,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx_dl_head++, 23 << 2, y << 2, 297 << 2, (y + stripH.v[i]) << 2, G_TX_RENDERTILE, 0,
                            (texH.v[i] - 1) << 5, 0x4A8, -0x4E6);
        gDPPipeSync(gfx_dl_head++);
        y += stripH.v[i];
    }
}


void Menu_DrawNumber(s32 ndigits, s32 x, s32 y, u32 value, s32 pal) {
    s32 i;
    u64 div;
    s64 v;
    s8 digits[10];
    s32 xoff;
    s32 j;
    s32 n;

    div = 1000000000;
    v = value;
    xoff = 0;
    j = 9;
    if (ndigits >= 10) {
        ndigits = 9;
    }
    for (i = 0; i < 9; i++) {
        n = 0;
        while (TRUE) {
            v -= div;
            if (v < 0) {
                v += div;
                break;
            }
            n++;
        }
        digits[j--] = n;
        div /= 10;
    }
    digits[0] = v;
    i = 0;
    if (!(menu_flags & 0x10)) {
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, menu_sprite_tlut);
        menu_flags |= 0x10;
    }
    for (n = ndigits - 1; n >= 0; n--) {
        i += digits[n];
        if (i != 0 || n == 0) {
            gDPLoadTextureTile(gfx_dl_head++, menu_sprite_tex[pal + digits[n]], G_IM_FMT_CI, G_IM_SIZ_8b, 8, 10, 0, 0, 7, 9,
                               0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx_dl_head++, (x + xoff) << 2, y << 2, (x + xoff + 8) << 2, (y + 10) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            gDPPipeSync(gfx_dl_head++);
        }
        xoff += 7;
    }
}

void Menu_DrawNumberZeroPad(s32 ndigits, s32 x, s32 y, u32 value, s32 pal) {
    s32 i;
    s32 n;
    u64 div;
    s64 v;
    s8 digits[10];
    s32 xoff;
    s32 j;

    div = 1000000000;
    v = value;
    xoff = 0;
    j = 9;
    if (ndigits >= 10) {
        ndigits = 9;
    }
    for (i = 0; i < 9; i++) {
        n = 0;
        while (TRUE) {
            v -= div;
            if (v < 0) {
                v += div;
                break;
            }
            n++;
        }
        digits[j--] = n;
        div /= 10;
    }
    digits[0] = v;
    if (!(menu_flags & 0x10)) {
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, menu_sprite_tlut);
        menu_flags |= 0x10;
    }
    for (n = ndigits - 1; n >= 0; n--) {
        gDPLoadTextureTile(gfx_dl_head++, menu_sprite_tex[pal + digits[n]], G_IM_FMT_CI, G_IM_SIZ_8b, 8, 10, 0, 0, 7, 9,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx_dl_head++, (x + xoff) << 2, y << 2, (x + xoff + 8) << 2, (y + 10) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        gDPPipeSync(gfx_dl_head++);
        xoff += 7;
    }
}




/* ---------------------------------------------------------------------------
 * .data 80055D40..80061650 (after 2B0F0, before 30600). Besides this file's own
 * tables it holds tables that 3F50, 9D50, AEA0 and E2A0 use: by link order they
 * belong here (or to a data-only file we can't tell apart). Pixels, palettes,
 * message text and animation keyframes are assets; ROM offsets and overlay or
 * buffer addresses are written as numbers.
 */
#ifndef NON_MATCHING /* the NON_MATCHING build declares it earlier, for Menu_UpdateMapPage */
#endif
void *player_char_data[1] = {
    (void*)0x80206064,
};
ActorStats player_default_stats = { 0, 0, 0x0032, 0x0032, 0x000F, 0x000F, 5, 4, 0, 500, 5e+01f, 1.6e+02f, 0.07f, { 1, 1, 1, 1 }, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
u32 player_level_exp_table[100] = {
    8, 10, 13, 17, 22, 28, 35, 44, 55, 69,
    86, 106, 130, 159, 193, 234, 282, 338, 404, 481,
    571, 674, 793, 929, 1085, 1263, 1464, 1691, 1947, 2235,
    2557, 2916, 3315, 3757, 4246, 4785, 5377, 6025, 6733, 7505,
    8344, 9253, 10237, 11297, 12438, 13663, 14975, 16377, 17871, 19462,
    21151, 22940, 24832, 26829, 28933, 31145, 33466, 35898, 38442, 41098,
    43866, 46747, 49740, 52846, 56063, 59390, 62826, 66371, 70022, 73778,
    77636, 81594, 85650, 89801, 94045, 98378, 102798, 107300, 111883, 116541,
    121272, 126072, 130938, 135865, 140849, 145887, 150975, 156109, 161284, 166497,
    171745, 177022, 182326, 187652, 192996, 198356, 203726, 209104, 214486, 219868,
};
u16 player_stat_xp_costs[70] = {
    0x000A, 0x000B, 0x000B, 0x000B, 0x000C, 0x000C, 0x000C, 0x000D, 0x000D, 0x000D, 0x000D, 0x000E,
    0x000E, 0x000E, 0x000F, 0x000F, 0x0010, 0x0010, 0x0010, 0x0011, 0x0011, 0x0012, 0x0012, 0x0012,
    0x0013, 0x0013, 0x0014, 0x0014, 0x0015, 0x0015, 0x0016, 0x0016, 0x0017, 0x0017, 0x0018, 0x0019,
    0x0019, 0x001A, 0x001A, 0x001B, 0x001C, 0x001C, 0x001D, 0x001E, 0x001F, 0x001F, 0x0020, 0x0021,
    0x0022, 0x0023, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C,
    0x002D, 0x002E, 0x0030, 0x0031, 0x0032, 0x0032, 0x0032, 0x0032, 0x0032, 0x0032,
};
MenuRomRange player_anim_rom_ranges[30] = {
    { 0x00EF21A0, 0x00EF3770 }, { 0x00EF3770, 0x00EF5B10 }, { 0x00EF5B10, 0x00EF7EB0 },
    { 0x00EF7EB0, 0x00EFA2A0 }, { 0x00EFA2A0, 0x00EFBD30 }, { 0x00EFBD30, 0x00EFD390 },
    { 0x00EFD390, 0x00EFF280 }, { 0x00EFF280, 0x00F00D10 }, { 0x00F00D10, 0x00F027A0 },
    { 0x00F027A0, 0x00F05F50 }, { 0x00F05F50, 0x00F07D40 }, { 0x00F07D40, 0x00F09E30 },
    { 0x00F2C170, 0x00F2D120 }, { 0x00F2D120, 0x00F2E9F0 }, { 0x00F2E9F0, 0x00F2FB70 },
    { 0x00F09E30, 0x00F0C1D0 }, { 0x00F0C1D0, 0x00F10A60 }, { 0x00F10A60, 0x00F11FF0 },
    { 0x00F11FF0, 0x00F143E0 }, { 0x00F143E0, 0x00F15770 }, { 0x00F15770, 0x00F192D0 },
    { 0x00F192D0, 0x00F1DBD0 }, { 0x00F1DBD0, 0x00F1F660 }, { 0x00F1F660, 0x00F210A0 },
    { 0x00F210A0, 0x00F22AE0 }, { 0x00F22AE0, 0x00F23ED0 }, { 0x00F23ED0, 0x00F26B90 },
    { 0x00F26B90, 0x00F28740 }, { 0x00F28740, 0x00F2A2F0 }, { 0x00F2A2F0, 0x00F2C170 },
};
SaveSpawnPoint player_save_spawn_points[17] = {
    { 0x000F, 5, -2.36f, 1.23f, 1.5793f }, { 0x0010, 7, -2.36f, 1.23f, 1.5793f },
    { 0x0010, 0x000F, -2.36f, 1.23f, 1.5793f }, { 0x0012, 6, 13.31f, 16.56f, 2.43f },
    { 0x0011, 0, -7.9f, -40.5f, -1.51f }, { 0x0012, 7, -14.4f, 18.41f, 2.46f },
    { 0x0014, 5, -2.36f, 1.23f, 1.5793f }, { 0x0016, 0x0016, 9.93f, 17.45f, 2.2467f },
    { 0x0016, 0x000E, -2.36f, 1.23f, 1.5793f }, { 0x0017, 0, -2.36f, 1.23f, 1.5793f },
    { 0x0017, 0x0014, -3.65f, -8.81f, 2.4174f }, { 0x0017, 0x0016, 2.45f, 14.41f, 2.4171f },
    { 0x0017, 8, -2.36f, 1.23f, 1.5793f }, { 0x001A, 3, 14.15f, 0.67f, 1.97f },
    { 0x0019, 3, 2.96f, 0.12f, -0.9817f }, { 0x001E, 0x000F, 1.4f, -89.5f, -0.2801f },
    { 0x000F, 0x000D, 11.0f, 15.98f, 2.2914f },
};
u32 D_80056198[2] = {
    0, 0,
};
EnemyAreaSet enemy_area_sets[6] = {
    { (u8 *)0x00A77F10, (u8 *)0x00ADA190, (void*)0x80270890, (void*)0x802705F0, (s32)0x80270934 },
    { (u8 *)0x00ADA190, (u8 *)0x00B61550, (void*)0x80295990, (void*)0x80295648, (s32)0x80295A6C },
    { (u8 *)0x00B61550, (u8 *)0x00BBBF30, (void*)0x80269010, (void*)0x80268DA8, (s32)0x8026909C },
    { (u8 *)0x00BBBF30, (u8 *)0x00C2F900, (void*)0x80281FD0, (void*)0x80281CF8, (s32)0x80282088 },
    { (u8 *)0x00C2F900, (u8 *)0x00C99EF0, (void*)0x80278C10, (void*)0x80278970, (s32)0x80278CB0 },
    { (u8 *)0x00C99EF0, (u8 *)0x00CC2280, (void*)0x80236A38, (void*)0x80236958, (s32)0x80236A70 },
};
EnemyScriptCmd enemy_attack_script_0[6] = {
    { 25, 0, 0, { 0, 0 }, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 26, 0, 8, { 0, 0 }, 0.0f, 0.0f, -2.0f, 0.0f },
    { 29, 1, 0, { 0, 0 }, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 33, 1, 0, { 0, 0 }, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 37, 1, 0, { 0, 0 }, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 41, 1, 1, { 0, 0 }, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_1[1] = {
    { 32, 2, 5, { 0, 0 }, 0.0f, 0.0f, 2e+02f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_2[5] = {
    { 30, 16, 0, { 0, 0 }, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 34, 16, 0, { 0, 0 }, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 38, 16, 0, { 0, 0 }, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 42, 16, 0, { 0, 0 }, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 46, 16, 1, { 0, 0 }, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_3[1] = {
    { 25, 17, 1, { 0, 0 }, 0.0f, 2e+02f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_5[6] = {
    { 1, 4, 0, { 0, 0 }, 0.0f, 1.3e+02f, 0.0f, 0.0f },
    { 2, 5, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 8, 5, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 14, 5, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 20, 5, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 26, 5, 1, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_7[1] = {
    { 23, 14, 1, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_8[5] = {
    { 18, 6, 0, { 0, 0 }, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 19, 0, 8, { 0, 0 }, 0.0f, 0.0f, -1.0f, 0.0f },
    { 20, 7, 0, { 0, 0 }, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 26, 7, 0, { 0, 0 }, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 32, 7, 1, { 0, 0 }, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_10[6] = {
    { 25, 8, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 32, 9, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 38, 9, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 44, 9, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 50, 9, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 56, 9, 1, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_11[4] = {
    { 0, 10, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 4, 10, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 8, 10, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 31, 15, 3, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_12[4] = {
    { 1, 11, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.0f },
    { 9, 11, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 0.7853982f },
    { 17, 11, 0, { 0, 0 }, 0.0f, 0.0f, 0.0f, 15.707963f },
    { 25, 11, 1, { 0, 0 }, 0.0f, 0.0f, 0.0f, 3.1415927f },
};
EnemyScriptCmd enemy_attack_script_13[5] = {
    { 35, 12, 0, { 0, 0 }, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 36, 0, 8, { 0, 0 }, 0.0f, 0.0f, -2.0f, 0.0f },
    { 41, 13, 0, { 0, 0 }, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 47, 13, 0, { 0, 0 }, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 53, 13, 1, { 0, 0 }, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_14[2] = {
    { 50, 18, 0, { 0, 0 }, 0.0f, 8e+02f, 0.0f, 0.0f },
    { 51, 19, 1, { 0, 0 }, 0.0f, 8e+02f, 0.0f, 0.0f },
};
EnemyScriptCmd enemy_attack_script_16[4] = {
    { 38, 21, 0, { 0, 0 }, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 42, 21, 0, { 0, 0 }, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 46, 21, 0, { 0, 0 }, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 50, 21, 1, { 0, 0 }, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
};
EnemyScriptCmd *enemy_attack_scripts[20] = {
    enemy_attack_script_0, enemy_attack_script_1, enemy_attack_script_2, enemy_attack_script_3, NULL,
    enemy_attack_script_5, NULL, enemy_attack_script_7, enemy_attack_script_8, NULL,
    enemy_attack_script_10, enemy_attack_script_11, enemy_attack_script_12, enemy_attack_script_13, enemy_attack_script_14,
    NULL, enemy_attack_script_16, NULL, NULL, NULL,
};
/* D_8005685A and D_8005685C (undefined_syms.txt) are fields of enemy_effect_defs[20]. */
EnemyEffectDef enemy_effect_defs[22] = {
    { 0x0046, 7, 0x000A, 0, 1.1f, 1.1f }, { 0x0047, 0x0037, 2, 0, 1.0f, 1.0f },
    { 0x0048, 7, 2, 0, 11.0f, 11.0f }, { 0x0049, 7, 0, 0, 4.0f, 4.0f },
    { 0x004F, 7, 0x0082, 0, 4.0f, 4.0f }, { 0x0050, 7, 2, 0, 6.0f, 6.0f },
    { 0x0055, 6, 2, 0, 0.6f, 0.6f }, { 0x0056, 0x0032, 2, 0, 1.2f, 1.2f },
    { 0x0058, 7, 2, 0, 2.0f, 2.0f }, { 0x0059, 7, 0, 0, 2.0f, 2.0f },
    { 0x005B, 7, 2, 0, 1.0f, 1.0f }, { 0x005D, 0x002C, 2, 0, 1.0f, 1.0f },
    { 0x005E, 4, 0x000A, 0, 2.0f, 2.0f }, { 0x005F, 0x0038, 2, 0, 1.0f, 1.0f },
    { 0x0054, 7, 2, 0, 1.0f, 1.0f }, { 0x005A, 7, 0, 0, 1.0f, 1.0f },
    { 0x004B, 0x002A, 2, 0, 1.0f, 1.0f }, { 0x004C, 0x0036, 0, 0, 6.0f, 6.0f },
    { 0x0060, 4, 0x0080, 0, 1.0f, 1.0f }, { 0x0061, 0x0035, 0x0080, 0, 1.0f, 1.0f },
    { 0x0042, 2, 0, 0, 1.0f, 1.0f }, { 0x0047, 0x0037, 2, 0, 0.5f, 0.5f },
};
s32 D_80056878[2] = {
    0, 0,
};
MenuRomRange npc_area_set_rom_ranges[7] = {
    { 0x00871D10, 0x008D1960 }, { 0x008D1960, 0x00926C00 }, { 0x00926C00, 0x0095D4E0 }, { 0x0095D4E0, 0x00988580 },
    { 0x00988580, 0x009E16C0 }, { 0x009E16C0, 0x00A14190 }, { 0x00A14190, 0x00A70350 },
};
u8 npc_area_entry_message[0x2F8] = {
#include "assets/npc_area_entry_message.inc.c"
};
MapAreaDef map_area_defs[36] = {
    { 0x0081, { 0, 0 }, (u8 *)0x000EF280, (u8 *)0x00133F20, (void*)0x8010FE00, (void*)0x8014F640, (void*)0x8014FB80, (void*)0x8014FF78, (void*)0x8015084C, (void*)0x80150290, (void*)0x80150518, (void*)0x80154810, (void*)0x801547BC, NULL, NULL, (void*)0x80154A90, 0, { 0, 0, 0, 5 } },
    { 1, { 0, 0 }, (u8 *)0x00133F20, (u8 *)0x00165E70, (void*)0x8010FE00, (void*)0x80140430, (void*)0x80140790, (void*)0x80140A28, (void*)0x80140F3C, (void*)0x80140C20, (void*)0x80140D10, (void*)0x80141CA0, (void*)0x80141C8C, NULL, NULL, (void*)0x80141D44, 1, { 0, 0, 0, 1 } },
    { 4, { 0, 0 }, (u8 *)0x00165E70, (u8 *)0x0019C1D0, (void*)0x8010FE00, (void*)0x80144464, (void*)0x80144710, (void*)0x80144858, (void*)0x80144CFC, (void*)0x80144A50, (void*)0x80144AD0, (void*)0x80145D70, (void*)0x80145D54, (void*)0x80146128, (void*)0x80146130, NULL, 1, { 0, 0, 0, 1 } },
    { 4, { 0, 0 }, (u8 *)0x0019C1D0, (u8 *)0x001CA8C0, (void*)0x8010FE00, (void*)0x8013C564, (void*)0x8013C870, (void*)0x8013C9F0, (void*)0x8013CEEC, (void*)0x8013CC00, (void*)0x8013CCB8, (void*)0x8013E190, (void*)0x8013E168, (void*)0x8013E460, (void*)0x8013E468, (void*)0x8013E4DC, 1, { 0, 0, 0, 2 } },
    { 1, { 0, 0 }, (u8 *)0x001CA8C0, (u8 *)0x00206D70, (void*)0x8010FE00, (void*)0x80149C98, (void*)0x8014A020, (void*)0x8014A3F8, (void*)0x8014AAFC, (void*)0x8014A6B0, (void*)0x8014A8C8, (void*)0x8014C1C0, (void*)0x8014C190, NULL, NULL, (void*)0x8014C2A4, 2, { 0, 0, 0, 3 } },
    { 4, { 0, 0 }, (u8 *)0x00206D70, (u8 *)0x00251D30, (void*)0x8010FE00, (void*)0x80157D98, (void*)0x801582C0, (void*)0x80158518, (void*)0x80158A1C, (void*)0x80158730, (void*)0x801587E8, (void*)0x8015A9C0, (void*)0x8015A99C, (void*)0x8015AD2C, (void*)0x8015AD34, (void*)0x8015ADAC, 2, { 0, 0, 0, 2 } },
    { 1, { 0, 0 }, (u8 *)0x00251D30, (u8 *)0x002768B0, (void*)0x8010FE00, (void*)0x80133438, (void*)0x80133720, (void*)0x80133948, (void*)0x80133DEC, (void*)0x80133B40, (void*)0x80133BC0, (void*)0x801348B0, (void*)0x80134898, NULL, NULL, (void*)0x80134974, 2, { 0, 0, 0, 1 } },
    { 4, { 0, 0 }, (u8 *)0x002768B0, (u8 *)0x002A8510, (void*)0x8010FE00, (void*)0x8013F1FC, (void*)0x8013F500, (void*)0x8013F6B8, (void*)0x8013FBBC, (void*)0x8013F8D0, (void*)0x8013F988, (void*)0x80141550, (void*)0x80141528, (void*)0x801419CC, (void*)0x801419D4, (void*)0x80141A4C, 3, { 0, 0, 0, 2 } },
    { 1, { 0, 0 }, (u8 *)0x002A8510, (u8 *)0x002F63B0, (void*)0x8010FE00, (void*)0x8015B89C, (void*)0x8015BD20, (void*)0x8015C090, (void*)0x8015C5FC, (void*)0x8015C270, (void*)0x8015C3D0, (void*)0x8015DB50, (void*)0x8015DB28, NULL, NULL, (void*)0x8015DC8C, 3, { 0, 0, 0, 2 } },
    { 4, { 0, 0 }, (u8 *)0x002F63B0, (u8 *)0x003457F0, (void*)0x8010FE00, (void*)0x8015A824, (void*)0x8015AE10, (void*)0x8015B230, (void*)0x8015B7AC, (void*)0x8015B4F0, (void*)0x8015B580, (void*)0x8015E870, (void*)0x8015E860, (void*)0x8015F1A8, (void*)0x8015F1B0, NULL, 4, { 0, 0, 0, 1 } },
    { 4, { 0, 0 }, (u8 *)0x003457F0, (u8 *)0x0036B800, (void*)0x8010FE00, (void*)0x801343D8, (void*)0x801345C0, (void*)0x80134738, (void*)0x80134CEC, (void*)0x80134920, (void*)0x80134AB8, (void*)0x80135DB0, (void*)0x80135D90, NULL, NULL, NULL, 4, { 0, 0, 0, 2 } },
    { 4, { 0, 0 }, (u8 *)0x0036B800, (u8 *)0x003C9490, (void*)0x8010FE00, (void*)0x80169190, (void*)0x80169610, (void*)0x80169CE8, (void*)0x8016A510, NULL, (void*)0x8016A018, (void*)0x8016D6D8, (void*)0x8016D57C, (void*)0x8016D9C4, (void*)0x8016D9DC, (void*)0x8016DA7C, 4, { 0, 0, 0, 8 } },
    { 4, { 0, 0 }, (u8 *)0x003C9490, (u8 *)0x003E1090, (void*)0x8010FE00, (void*)0x80125DA4, (void*)0x80126010, (void*)0x801261D4, (void*)0x801267BC, (void*)0x801264C0, (void*)0x80126588, (void*)0x80127800, (void*)0x801277CC, (void*)0x8012796C, (void*)0x80127974, (void*)0x801279EC, 5, { 0, 0, 0, 3 } },
    { 2, { 0, 0 }, (u8 *)0x003F1BA0, (u8 *)0x004374F0, (void*)0x801539F0, (void*)0x80194B14, (void*)0x80195480, (void*)0x80195E98, (void*)0x801967F8, (void*)0x80196108, (void*)0x80196510, (void*)0x80198F84, (void*)0x80198980, NULL, NULL, (void*)0x80199330, 0, { 0, 0, 0, 18 } },
    { 2, { 0, 0 }, (u8 *)0x004374F0, (u8 *)0x00487890, (void*)0x801539F0, (void*)0x8019DFA0, (void*)0x8019EC80, (void*)0x8019F7E0, (void*)0x8019FFF0, NULL, (void*)0x8019FD88, (void*)0x801A3900, (void*)0x801A3590, NULL, NULL, (void*)0x801A3D7C, 1, { 0, 0, 0, 16 } },
    { 2, { 0, 0 }, (u8 *)0x00487890, (u8 *)0x0049D830, (void*)0x801539F0, (void*)0x80166974, (void*)0x80167120, (void*)0x80167738, (void*)0x80167EF0, (void*)0x80167948, (void*)0x80167C98, (void*)0x801696A0, (void*)0x80169530, NULL, NULL, (void*)0x80169980, 0, { 0, 0, 0, 14 } },
    { 2, { 0, 0 }, (u8 *)0x0049D830, (u8 *)0x004CD2E0, (void*)0x801539F0, (void*)0x8017DA08, (void*)0x8017E510, (void*)0x8017EF80, (void*)0x8017FB58, (void*)0x8017F300, (void*)0x8017F850, (void*)0x8018302C, (void*)0x80182D34, NULL, NULL, (void*)0x8018348C, 1, { 0, 0, 0, 22 } },
    { 2, { 0, 0 }, (u8 *)0x004CD2E0, (u8 *)0x004E44A0, (void*)0x801539F0, (void*)0x80168D4C, (void*)0x801691F0, (void*)0x80169680, (void*)0x80169BD0, (void*)0x801697F8, (void*)0x80169AA0, (void*)0x8016A978, (void*)0x8016A75C, NULL, NULL, (void*)0x8016ABA4, 2, { 0, 0, 0, 8 } },
    { 2, { 0, 0 }, (u8 *)0x004E44A0, (u8 *)0x004F4E70, (void*)0x801539F0, (void*)0x801621D4, (void*)0x80162940, (void*)0x80162C10, (void*)0x801630B0, NULL, (void*)0x80162E90, (void*)0x80164180, (void*)0x801640FC, NULL, NULL, (void*)0x801643B8, 2, { 0, 0, 0, 8 } },
    { 2, { 0, 0 }, (u8 *)0x004F4E70, (u8 *)0x004FFFE0, (void*)0x801539F0, (void*)0x8015DE28, (void*)0x8015E010, (void*)0x8015E1A0, (void*)0x8015E468, NULL, (void*)0x8015E2E0, (void*)0x8015EA70, (void*)0x8015EA28, NULL, NULL, NULL, 2, { 0, 0, 0, 4 } },
    { 2, { 0, 0 }, (u8 *)0x004FFFE0, (u8 *)0x0051A6C0, (void*)0x801539F0, (void*)0x8016B158, (void*)0x8016B920, (void*)0x8016BEE8, (void*)0x8016C500, (void*)0x8016C0C8, (void*)0x8016C3A8, (void*)0x8016DE70, (void*)0x8016DD1C, NULL, NULL, (void*)0x8016E0BC, 2, { 0, 0, 0, 12 } },
    { 2, { 0, 0 }, (u8 *)0x0051A6C0, (u8 *)0x0056DB40, (void*)0x801539F0, (void*)0x801A2518, (void*)0x801A2CE0, (void*)0x801A34B8, (void*)0x801A3B08, NULL, (void*)0x801A3938, (void*)0x801A6A68, (void*)0x801A6644, NULL, NULL, (void*)0x801A6E68, 3, { 0, 0, 0, 13 } },
    { 2, { 0, 0 }, (u8 *)0x0056DB40, (u8 *)0x0059D6F0, (void*)0x801539F0, (void*)0x8017DA18, (void*)0x8017E500, (void*)0x8017F0A8, (void*)0x8017FDF8, (void*)0x8017F3D8, (void*)0x8017F9D8, (void*)0x80182FCC, (void*)0x80182D28, NULL, NULL, (void*)0x80183594, 3, { 0, 0, 0, 26 } },
    { 2, { 0, 0 }, (u8 *)0x0059D6F0, (u8 *)0x005D6D20, (void*)0x801539F0, (void*)0x80186F78, (void*)0x801879E0, (void*)0x801886D8, (void*)0x80189368, (void*)0x80188A08, (void*)0x80189040, (void*)0x8018C910, (void*)0x8018C644, NULL, NULL, (void*)0x8018D010, 4, { 0, 0, 0, 26 } },
    { 2, { 0, 0 }, (u8 *)0x005D6D20, (u8 *)0x005E99E0, (void*)0x801539F0, (void*)0x80164FB0, (void*)0x80165070, (void*)0x80165250, (void*)0x80165538, NULL, (void*)0x801653B8, (void*)0x80166464, (void*)0x801661A0, NULL, NULL, (void*)0x8016669C, 4, { 0, 0, 0, 3 } },
    { 2, { 0, 0 }, (u8 *)0x005E99E0, (u8 *)0x006078D0, (void*)0x801539F0, (void*)0x8016EEE0, (void*)0x8016F360, (void*)0x8016F860, (void*)0x80170018, (void*)0x8016FAC0, (void*)0x8016FD70, (void*)0x801716D0, (void*)0x8017162C, NULL, NULL, (void*)0x801718D0, 5, { 0, 0, 0, 10 } },
    { 0x0088, { 0, 0 }, (u8 *)0x006078D0, (u8 *)0x00665670, (void*)0x8010FE00, (void*)0x801649D8, (void*)0x80165460, (void*)0x80165A34, (void*)0x80165EB8, NULL, (void*)0x80165C38, (void*)0x8016D480, (void*)0x8016D430, (void*)0x8016DAC0, (void*)0x8016DAC8, (void*)0x8016DB98, 0, { 0, 0, 0, 5 } },
    { 0x0088, { 0, 0 }, (u8 *)0x00665670, (u8 *)0x006C4880, (void*)0x8010FE00, (void*)0x80168D08, (void*)0x8016A590, (void*)0x8016A668, (void*)0x8016A778, NULL, (void*)0x8016A6F0, (void*)0x8016E920, (void*)0x8016E910, (void*)0x8016EFD8, (void*)0x8016EFE0, NULL, 0, { 0, 0, 0, 1 } },
    { 0x0088, { 0, 0 }, (u8 *)0x006C4880, (u8 *)0x0071EB90, (void*)0x8010FE00, (void*)0x80163770, (void*)0x80164C90, (void*)0x80164D30, (void*)0x80164EE8, NULL, (void*)0x80164E68, (void*)0x80169C70, (void*)0x80169C5C, (void*)0x8016A0B4, (void*)0x8016A0BC, NULL, 0, { 0, 0, 0, 1 } },
    { 0x0088, { 0, 0 }, (u8 *)0x0071EB90, (u8 *)0x007428A0, (void*)0x8010FE00, (void*)0x8012FC8C, (void*)0x80130610, (void*)0x801306B0, (void*)0x80130868, NULL, (void*)0x801307E8, (void*)0x80133440, (void*)0x80133428, (void*)0x80133ACC, (void*)0x80133AD4, NULL, 0, { 0, 0, 0, 1 } },
    { 8, { 0, 0 }, (u8 *)0x007428A0, (u8 *)0x00785690, (void*)0x8010FE00, (void*)0x8014CFFC, (void*)0x8014D4A0, (void*)0x8014DDF4, (void*)0x8014E6C0, NULL, (void*)0x8014E370, (void*)0x80152534, (void*)0x80151E6C, (void*)0x80152A8C, (void*)0x80152AC4, (void*)0x80152BC4, 0, { 0, 0, 0, 16 } },
    { 8, { 0, 0 }, (u8 *)0x00785690, (u8 *)0x007C1CE0, (void*)0x8010FE00, (void*)0x801476DC, (void*)0x80147D20, (void*)0x80147F00, (void*)0x8014838C, NULL, (void*)0x80148068, (void*)0x8014BF70, (void*)0x8014BF38, (void*)0x8014C3F8, (void*)0x8014C400, NULL, 0, { 0, 0, 0, 3 } },
    { 8, { 0, 0 }, (u8 *)0x007C1CE0, (u8 *)0x007EF930, (void*)0x8010FE00, (void*)0x8013B150, (void*)0x8013B5F0, (void*)0x8013B7D0, (void*)0x8013BBB4, NULL, (void*)0x8013B900, (void*)0x8013D580, (void*)0x8013D550, (void*)0x8013D9A4, (void*)0x8013D9AC, (void*)0x8013DA3C, 0, { 0, 0, 0, 3 } },
    { 8, { 0, 0 }, (u8 *)0x007EF930, (u8 *)0x008231F0, (void*)0x8010FE00, (void*)0x80140DC4, (void*)0x80141190, (void*)0x80141370, (void*)0x80141714, NULL, (void*)0x80141468, (void*)0x80143300, (void*)0x801432C4, (void*)0x8014365C, (void*)0x80143664, NULL, 0, { 0, 0, 0, 3 } },
    { 8, { 0, 0 }, (u8 *)0x008231F0, (u8 *)0x00851240, (void*)0x8010FE00, (void*)0x80139374, (void*)0x80139680, (void*)0x80139ACC, (void*)0x8013A1B0, NULL, (void*)0x80139E80, (void*)0x8013D910, (void*)0x8013D854, (void*)0x8013DCE4, (void*)0x8013DD3C, (void*)0x8013DE48, 0, { 0, 0, 0, 11 } },
    { 0x0088, { 0, 0 }, (u8 *)0x00851240, (u8 *)0x00869620, (void*)0x8010FE00, (void*)0x801269B4, (void*)0x80127A80, (void*)0x80127AE8, (void*)0x80127C28, NULL, (void*)0x80127BA8, (void*)0x801281D0, (void*)0x801281C0, NULL, NULL, NULL, 0, { 0, 0, 0, 1 } },
};
MapRomRange map_extra_rom_ranges[6] = {
    { 0x000C8DE0, 0x000D0570, (void*)0x801F8000 }, { 0x000D0570, 0x000D7FE0, (void*)0x801F8000 },
    { 0x000D7FE0, 0x000DD790, (void*)0x801F8000 }, { 0x000DD790, 0x000E4D00, (void*)0x801F8000 },
    { 0x000E4D00, 0x000EBDE0, (void*)0x801F8000 }, { 0x000EBDE0, 0x000EF280, (void*)0x801F8000 },
};
/* One cell (the player's own); [1] pads to the word the table occupies. */
CellOffset mapobj_cell_single[2] = { { 0, 0 }, { 0, 0 } };
CellOffset mapobj_cell_disc_r7[158] = {
    { -1, -7 }, { 0, -7 }, { 1, -7 }, { -3, -6 }, { -2, -6 }, { -1, -6 }, { 0, -6 }, { 1, -6 }, { 2, -6 }, { 2, -6 },
    { -4, -5 }, { -3, -5 }, { -2, -5 }, { -1, -5 }, { 0, -5 }, { 1, -5 }, { 2, -5 }, { 3, -5 }, { 4, -5 }, { -5, -4 },
    { -4, -4 }, { -3, -4 }, { -2, -4 }, { -1, -4 }, { 0, -4 }, { 1, -4 }, { 2, -4 }, { 3, -4 }, { 4, -4 }, { 5, -4 },
    { -6, -3 }, { -5, -3 }, { -4, -3 }, { -3, -3 }, { -2, -3 }, { -1, -3 }, { 0, -3 }, { 1, -3 }, { 2, -3 }, { 3, -3 },
    { 4, -3 }, { 5, -3 }, { 6, -3 }, { -6, -2 }, { -5, -2 }, { -4, -2 }, { -3, -2 }, { -2, -2 }, { -1, -2 }, { 0, -2 },
    { 1, -2 }, { 2, -2 }, { 3, -2 }, { 4, -2 }, { 5, -2 }, { 6, -2 }, { -7, -1 }, { -6, -1 }, { -5, -1 }, { -4, -1 },
    { -3, -1 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 4, -1 }, { 5, -1 }, { 6, -1 },
    { 7, -1 }, { -7, 0 }, { -6, 0 }, { -5, 0 }, { -4, 0 }, { -3, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 },
    { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 }, { -7, 1 }, { -6, 1 }, { -5, 1 }, { -4, 1 },
    { -3, 1 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 },
    { 7, 1 }, { -6, 2 }, { -5, 2 }, { -4, 2 }, { -3, 2 }, { -2, 2 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 2, 2 },
    { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 }, { -6, 3 }, { -5, 3 }, { -4, 3 }, { -3, 3 }, { -2, 3 }, { -1, 3 },
    { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { -5, 4 }, { -4, 4 }, { -3, 4 },
    { -2, 4 }, { -1, 4 }, { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { -4, 5 }, { -3, 5 },
    { -2, 5 }, { -1, 5 }, { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 }, { 4, 5 }, { -3, 6 }, { -2, 6 }, { -1, 6 },
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 }, { -1, 7 }, { 0, 7 }, { 1, 7 }, { 0, 0 },
};
CellOffset mapobj_cell_disc_r5[90] = {
    { -1, -5 }, { 0, -5 }, { 1, -5 }, { -3, -4 }, { -2, -4 }, { -1, -4 }, { 0, -4 }, { 1, -4 }, { 2, -4 }, { 3, -4 },
    { -4, -3 }, { -3, -3 }, { -2, -3 }, { -1, -3 }, { 0, -3 }, { 1, -3 }, { 2, -3 }, { 3, -3 }, { 4, -3 }, { -4, -2 },
    { -3, -2 }, { -2, -2 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 2, -2 }, { 3, -2 }, { 4, -2 }, { -5, -1 }, { -4, -1 },
    { -3, -1 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 4, -1 }, { 5, -1 }, { -5, 0 },
    { -4, 0 }, { -3, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 },
    { -5, 1 }, { -4, 1 }, { -3, 1 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 },
    { 5, 1 }, { -4, 2 }, { -3, 2 }, { -2, 2 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 },
    { -4, 3 }, { -3, 3 }, { -2, 3 }, { -1, 3 }, { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { -3, 4 },
    { -2, 4 }, { -1, 4 }, { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { -1, 5 }, { 0, 5 }, { 1, 5 }, { 0, 0 },
};
CellOffset mapobj_cell_square_3x3[10] = {
    { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 0, 0 },
};
CellOffset mapobj_cell_disc_r2[22] = {
    { -1, -2 }, { 0, -2 }, { -1, -2 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { -2, 0 }, { -1, 0 }, { 0, 0 },
    { 1, 0 }, { 2, 0 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 0, 0 },
};
/* Animations: keyframes (assets, 0x34-byte records) and their headers. */
u32 mapobjanim_type23_keys[0x8F] = {
#include "assets/mapobjanim_type23_keys.inc.c"
};
MapObjAnimDef mapobjanim_type23_anim = { mapobjanim_type23_keys, 0x000B, 0x0051, 0, 0, 0, 0, 0, 0 };
u32 D_80057A18[0xC3] = {
#include "assets/D_80057A18.inc.c"
};
MapObjAnimDef D_80057D24 = { D_80057A18, 0x000F, 0x006E, 0, 0, 0, 0, 0, 0 };
u32 mapobjanim_type23_odd_keys[0x8F] = {
#include "assets/mapobjanim_type23_odd_keys.inc.c"
};
MapObjAnimDef mapobjanim_type23_odd_anim = { mapobjanim_type23_odd_keys, 0x000B, 0x0064, 0, 0, 0, 0, 0, 0 };
u32 mapobjanim_type4_keys[0x1A] = {
#include "assets/mapobjanim_type4_keys.inc.c"
};
MapObjAnimDef mapobjanim_type4_anim = { mapobjanim_type4_keys, 2, 0x001E, 0, 0, 0, 0, 0, 0 };
u32 mapobj_loop_anim0_keys[0x27] = {
#include "assets/mapobj_loop_anim0_keys.inc.c"
};
u32 mapobj_loop_anim1_keys[0x34] = {
#include "assets/mapobj_loop_anim1_keys.inc.c"
};
u32 mapobj_loop_anim2_keys[0x41] = {
#include "assets/mapobj_loop_anim2_keys.inc.c"
};
u32 mapobj_loop_anim3_keys[0x41] = {
#include "assets/mapobj_loop_anim3_keys.inc.c"
};
MapObjAnimDef mapobj_loop_anims[4] = {
    { mapobj_loop_anim0_keys, 3, 0x003C, 0, 0, 0, 0, 0, 0 },
    { mapobj_loop_anim1_keys, 4, 0x003C, 0, 0, 0, 0, 0, 0 },
    { mapobj_loop_anim2_keys, 5, 0x0050, 0, 0, 0, 0, 0, 0 },
    { mapobj_loop_anim3_keys, 5, 0x0050, 0, 0, 0, 0, 0, 0 },
};
u16 mapobj_kind11_tlut[0x200] = {
#include "assets/mapobj_kind11_tlut.inc.c"
};
u8 mapobj_kind11_tex_0[0x600] = {
#include "assets/mapobj_kind11_tex_0.inc.c"
};
u8 mapobj_kind11_tex_1[0x600] = {
#include "assets/mapobj_kind11_tex_1.inc.c"
};
u8 mapobj_kind11_tex_2[0x600] = {
#include "assets/mapobj_kind11_tex_2.inc.c"
};
u8 mapobj_kind11_tex_3[0x600] = {
#include "assets/mapobj_kind11_tex_3.inc.c"
};
u8 mapobj_kind11_tex_4[0x600] = {
#include "assets/mapobj_kind11_tex_4.inc.c"
};
u8 mapobj_kind11_tex_5[0x600] = {
#include "assets/mapobj_kind11_tex_5.inc.c"
};
u8 mapobj_kind11_tex_6[0x600] = {
#include "assets/mapobj_kind11_tex_6.inc.c"
};
u8 mapobj_kind11_tex_7[0x200] = {
#include "assets/mapobj_kind11_tex_7.inc.c"
};
u16 mapobj_kind12_tlut[0x200] = {
#include "assets/mapobj_kind12_tlut.inc.c"
};
u8 mapobj_kind12_tex_0[0x600] = {
#include "assets/mapobj_kind12_tex_0.inc.c"
};
u8 mapobj_kind12_tex_1[0x600] = {
#include "assets/mapobj_kind12_tex_1.inc.c"
};
u8 mapobj_kind12_tex_2[0x600] = {
#include "assets/mapobj_kind12_tex_2.inc.c"
};
u8 mapobj_kind12_tex_3[0x600] = {
#include "assets/mapobj_kind12_tex_3.inc.c"
};
u8 mapobj_kind12_tex_4[0x600] = {
#include "assets/mapobj_kind12_tex_4.inc.c"
};
u8 mapobj_kind12_tex_5[0x600] = {
#include "assets/mapobj_kind12_tex_5.inc.c"
};
u8 mapobj_kind12_tex_6[0x600] = {
#include "assets/mapobj_kind12_tex_6.inc.c"
};
u8 mapobj_kind12_tex_7[0x200] = {
#include "assets/mapobj_kind12_tex_7.inc.c"
};
Vtx mapobj_kind11_vtx[4] = {
    {{ { 8, 23, 0 }, 0, { 960, 0 }, { 0, 0, 0, 0 } }},
    {{ { -8, 23, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 8, 0, 0 }, 0, { 960, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -8, 0, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Vtx mapobj_kind12_vtx[4] = {
    {{ { 8, 32, 0 }, 0, { 960, 0 }, { 0, 0, 0, 0 } }},
    {{ { -8, 32, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 8, 0, 0 }, 0, { 960, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -8, 0, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Gfx mapobj_kind11_setup_dl[13] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)mapobj_kind11_tlut }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_8005E51C (undefined_syms.txt) is mapobj_kind12_setup_dl + 0x14. */
Gfx mapobj_kind12_setup_dl[13] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)mapobj_kind12_tlut }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx mapobj_kind11_quad_dl[3] = {
    {{ 0x0400103F, (u32)mapobj_kind11_vtx }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx mapobj_kind12_quad_dl[3] = {
    {{ 0x0400103F, (u32)mapobj_kind12_vtx }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_8005E5AC (undefined_syms.txt) is mapobj_animtex_dls[1].b. */
MapDlPair mapobj_animtex_dls[2] = {
    { mapobj_kind11_setup_dl, mapobj_kind11_quad_dl }, { mapobj_kind12_setup_dl, mapobj_kind12_quad_dl },
};
u8 *mapobj_kind11_frames[8] = {
    mapobj_kind11_tex_0, mapobj_kind11_tex_1, mapobj_kind11_tex_2, mapobj_kind11_tex_3,
    mapobj_kind11_tex_4, mapobj_kind11_tex_5, mapobj_kind11_tex_6, mapobj_kind11_tex_7,
};
u8 *mapobj_kind12_frames[8] = {
    mapobj_kind12_tex_0, mapobj_kind12_tex_1, mapobj_kind12_tex_2, mapobj_kind12_tex_3,
    mapobj_kind12_tex_4, mapobj_kind12_tex_5, mapobj_kind12_tex_6, mapobj_kind12_tex_7,
};
u8 **mapobj_animtex_frame_tables[2] = {
    mapobj_kind11_frames, mapobj_kind12_frames,
};
u16 mapobj_arc_sprite_tlut[0x200] = {
#include "assets/mapobj_arc_sprite_tlut.inc.c"
};
u8 mapobj_arc_sprite_tex[0x2000] = {
#include "assets/mapobj_arc_sprite_tex.inc.c"
};
Vtx mapobj_arc_sprite_vtx[4] = {
    {{ { 1, 1, 1 }, 0, { 1984, 0 }, { 0, 0, 0, 0 } }},
    {{ { -1, 1, 1 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 1, -1, 1 }, 0, { 1984, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -1, -1, 1 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Gfx mapobj_arc_sprite_dl[16] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)mapobj_arc_sprite_tlut }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0x0400103F, (u32)mapobj_arc_sprite_vtx }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
u8 mapobj_drop_sprite_tex[0x100] = {
#include "assets/mapobj_drop_sprite_tex.inc.c"
};
Vtx mapobj_drop_sprite_vtx[4] = {
    {{ { 1, 2, 1 }, 0, { 448, 0 }, { 0, 0, 0, 0 } }},
    {{ { -1, 2, 1 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 1, -2, 1 }, 0, { 448, 960 }, { 0, 0, 0, 0 } }},
    {{ { -1, -2, 1 }, 0, { 0, 960 }, { 0, 0, 0, 0 } }},
};
Gfx mapobj_drop_sprite_dl[10] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0x0400103F, (u32)mapobj_drop_sprite_vtx }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_80060C4C (undefined_syms.txt) is map_backdrop_defs[0].dl. */
MapBackdropDef map_backdrop_defs[8] = {
    { 0x00D86970, 0x01001300 }, { 0x00D8B170, 0x01001300 }, { 0x00D8F970, 0x01002410 }, { 0x00D92D70, 0x01003630 },
    { 0x00D96570, 0x01003630 }, { 0x00D99D70, 0x01003630 }, { 0x00D9D570, 0x01003630 }, { 0x00DA0D70, 0x01003630 },
};
u8 mapobj_translucent_alpha[40] = {
    0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
    0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0x78, 0x78, 0x78, 0x78, 0x78, 0x96, 0x96, 0x96, 0x78, 0x78, 0, 0, 0, 0,
};
s8 menu_bgm_volume_option = 2;
u8 menu_sprite_sizes[88][2] = {
    { 0x10, 0x10 }, { 0x10, 0x0D }, { 0x10, 0x10 }, { 0x10, 0x10 }, { 0x0C, 0x0C }, { 8, 8 }, { 0x10, 0x0B }, { 0x10, 0x0B },
    { 0x0C, 0x0A }, { 0x0C, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 0x52, 0x0D }, { 0x18, 0x0F }, { 0x1C, 0x0D }, { 0x24, 0x0F }, { 0x1C, 0x0F }, { 0x24, 0x0D },
    { 0x14, 0x0B }, { 0x56, 0x0E }, { 0x36, 0x0C }, { 0x2A, 0x0C }, { 0x54, 7 }, { 0x50, 3 }, { 8, 0x0B }, { 8, 0x0B },
    { 8, 0x0B }, { 0x1A, 9 }, { 0x1A, 9 }, { 0x3A, 0x10 }, { 0x0C, 0x10 }, { 0x56, 0x0D }, { 0x0C, 0x0C }, { 0x0C, 0x0C },
    { 0x0C, 0x0C }, { 0x0C, 0x0C }, { 0x3C, 7 }, { 0x34, 3 }, { 0x3C, 0x14 }, { 0x20, 0x0C }, { 0x1C, 0x0D }, { 4, 4 },
    { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 0x64, 0x0E }, { 0x96, 2 },
    { 2, 0x78 }, { 4, 4 }, { 0x7C, 0x0C }, { 0x1C, 0x0E }, { 0x1C, 0x0E }, { 0x1C, 0x0D }, { 0x14, 0x0E }, { 0x18, 0x0E },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 0x0C, 0x10 }, { 0x0C, 0x10 }, { 8, 1 }, { 0x1A, 9 }, { 0x1A, 9 },
};
s8 menu_wobble_offsets[16] = {
    -1, -2, -2, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -1, 0, 0,
};
u8 *menu_sprite_tex[89] = {
    D_800620A0, D_800621A8, D_80062280, D_80062290, D_800622A0, D_80062338,
    D_80062380, D_80062438, D_800624F0, D_80062500, D_80062510, D_80062568,
    D_800625C0, D_80062618, D_80062670, D_800626C8, D_80062720, D_80062778,
    D_800627D0, D_80062828, D_80062880, D_800628D8, D_80062930, D_80062988,
    D_800629E0, D_80062A38, D_80062A90, D_80062EC8, D_80063038, D_800631B0,
    D_800633D8, D_80063588, D_80063598, D_80063680, D_80063B40, D_80063DD0,
    D_80063FD0, D_80064228, D_80064320, D_80064380, D_800643E0, D_80064440,
    D_80064538, D_80064630, D_800649D8, D_80064AA0, D_80064F08, D_80064FA0,
    D_80065038, D_800650D0, D_80065168, D_80065350, D_800653F8, D_80065408,
    D_80065418, D_80065590, D_800655A8, D_800655C0, D_800655D8, D_800655F0,
    D_80065608, D_80065620, D_80065638, D_80065648, D_80065780, D_80065790,
    D_800657A0, D_80065D78, D_80065F08, D_80066098, D_80066210, D_80066330,
    D_80066488, D_800664E0, D_80066538, D_80066590, D_800665E8, D_80066640,
    D_80066698, D_800666F0, D_80066748, D_800667A0, D_800667F8, D_80066850,
    D_80066918, D_800669E0, D_800669F0, D_80066AE8, NULL,
};
Gfx menu_sprite_opaque_dl[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx menu_sprite_alpha_dl[7] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC129A25, 0xFF37FFFF }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x0F0A4000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
f32 menu_map_cursor_x = -1.0f;
f32 menu_map_cursor_y = -1.0f;
MenuMapLocation menu_map_location_list[298] = {
    { 2, 0 }, { -2, -1 }, { 0, 0 }, { 0, 1 }, { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 },
    { 13, 6 }, { 13, 7 }, { 13, 8 }, { 13, 9 }, { 13, 10 }, { 13, 11 }, { 13, 12 }, { 13, 13 }, { 13, 14 }, { 13, 15 },
    { 13, 16 }, { 13, 17 }, { 15, 0 }, { 15, 1 }, { 15, 2 }, { 15, 3 }, { 15, 4 }, { 15, 5 }, { 15, 6 }, { 15, 7 },
    { 15, 8 }, { 15, 9 }, { 15, 10 }, { 15, 11 }, { 15, 12 }, { -2, -1 }, { 1, 0 }, { 14, 0 }, { 14, 1 }, { 14, 2 },
    { 14, 3 }, { 14, 4 }, { 14, 5 }, { 14, 6 }, { 14, 7 }, { 14, 8 }, { 14, 9 }, { 14, 10 }, { 14, 11 }, { 14, 12 },
    { 14, 14 }, { 14, 15 }, { 16, 0 }, { 16, 1 }, { 16, 2 }, { 16, 3 }, { 16, 4 }, { 16, 6 }, { 16, 7 }, { 16, 8 },
    { 16, 9 }, { 16, 10 }, { 16, 11 }, { 16, 12 }, { 16, 13 }, { 16, 14 }, { -2, -1 }, { 16, 5 }, { -2, -1 }, { 16, 21 },
    { -2, -1 }, { 31, 0 }, { 31, 1 }, { 31, 2 }, { -1, -1 }, { 3, 0 }, { -2, -1 }, { 16, 15 }, { 16, 16 }, { 16, 17 },
    { 16, 18 }, { 16, 19 }, { 16, 20 }, { -2, -1 }, { 3, 1 }, { -2, -1 }, { 32, 0 }, { 32, 1 }, { 32, 2 }, { -1, -1 },
    { 5, 0 }, { -2, -1 }, { 5, 1 }, { -2, -1 }, { 4, 0 }, { 4, 1 }, { 4, 2 }, { 17, 0 }, { 17, 1 }, { 17, 2 },
    { 17, 3 }, { 17, 4 }, { 17, 5 }, { 17, 6 }, { 17, 7 }, { 17, 8 }, { 18, 0 }, { 18, 1 }, { 18, 2 }, { 18, 3 },
    { 18, 4 }, { -2, -1 }, { 6, 0 }, { 19, 0 }, { 19, 1 }, { 19, 2 }, { 19, 3 }, { 20, 0 }, { 20, 1 }, { 20, 2 },
    { 20, 3 }, { 20, 4 }, { 20, 5 }, { 20, 6 }, { 20, 7 }, { 20, 8 }, { 20, 9 }, { 20, 10 }, { 20, 11 }, { -2, -1 },
    { 18, 6 }, { -2, -1 }, { 18, 5 }, { -2, -1 }, { 18, 7 }, { -2, -1 }, { 33, 0 }, { 33, 1 }, { 33, 2 }, { -2, -1 },
    { 27, 0 }, { -2, -1 }, { 26, 0 }, { 26, 1 }, { 26, 2 }, { 26, 3 }, { 26, 4 }, { -1, -1 }, { 7, 0 }, { -2, -1 },
    { 7, 1 }, { -2, -1 }, { 8, 0 }, { 8, 1 }, { 22, 0 }, { 22, 1 }, { 22, 2 }, { 22, 3 }, { 22, 4 }, { 22, 5 },
    { 22, 6 }, { 22, 7 }, { 22, 8 }, { 22, 9 }, { 22, 10 }, { 22, 11 }, { 22, 12 }, { 22, 13 }, { 22, 14 }, { 22, 15 },
    { 22, 16 }, { 22, 17 }, { 22, 18 }, { 22, 19 }, { 22, 20 }, { 22, 21 }, { 21, 0 }, { 21, 1 }, { 21, 2 }, { 21, 3 },
    { 21, 4 }, { 21, 5 }, { 21, 6 }, { 21, 7 }, { 21, 8 }, { 21, 9 }, { 21, 10 }, { 21, 11 }, { 21, 12 }, { -2, -1 },
    { 22, 22 }, { -2, -1 }, { 22, 23 }, { -2, -1 }, { 28, 0 }, { -1, -1 }, { 9, 0 }, { -2, -1 }, { 23, 0 }, { 23, 1 },
    { 23, 2 }, { 23, 3 }, { 23, 4 }, { 23, 5 }, { -2, -1 }, { 23, 19 }, { -2, -1 }, { 23, 20 }, { 23, 21 }, { -2, -1 },
    { 29, 0 }, { -1, -1 }, { 11, 2 }, { -2, -1 }, { 23, 22 }, { 23, 23 }, { 23, 24 }, { 23, 25 }, { -2, -1 }, { 23, 6 },
    { 23, 7 }, { 23, 8 }, { 23, 9 }, { 23, 10 }, { 23, 11 }, { 23, 12 }, { 23, 13 }, { 23, 14 }, { 23, 15 }, { 23, 16 },
    { 23, 17 }, { 23, 18 }, { 11, 0 }, { -2, -1 }, { 30, 0 }, { 30, 1 }, { 30, 2 }, { 30, 3 }, { 30, 4 }, { 30, 5 },
    { 30, 6 }, { 30, 7 }, { 30, 8 }, { 30, 9 }, { 30, 10 }, { 30, 11 }, { 30, 12 }, { 30, 13 }, { 30, 14 }, { 30, 15 },
    { 11, 1 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 11, 6 }, { 11, 7 }, { -1, -1 }, { 12, 0 }, { 12, 1 }, { 25, 0 },
    { 25, 1 }, { 35, 0 }, { -1, -1 }, { 25, 5 }, { 25, 8 }, { 25, 9 }, { 25, 2 }, { 25, 3 }, { 25, 4 }, { 12, 2 },
    { -1, -1 }, { 10, 0 }, { 10, 1 }, { 24, 0 }, { 24, 1 }, { 24, 2 }, { -1, -1 }, { 0, 2 }, { 0, 3 }, { 0, 4 },
    { 14, 13 }, { 34, 0 }, { 34, 1 }, { 34, 2 }, { 34, 3 }, { 34, 4 }, { 34, 5 }, { 34, 6 }, { 34, 7 }, { 34, 8 },
    { 34, 9 }, { 34, 10 }, { 15, 13 }, { 25, 6 }, { 25, 7 }, { 25, 24 }, { 25, 25 }, { -8, -1 },
};
s16 menu_map_spot_coords[108] = {
    150, 10, 90, 115, 143, 128, 131, 70, 98, 167, -1, -1,
    -1, -1, -1, -1, -1, -1, 150, 162, 132, 152, 70, 80,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    187, 88, 134, 31, 100, 164, 171, 82, 142, 140, 107, 113,
    131, 155, 96, 147, 135, 17, 34, 63, 182, 47, 27, 74,
    185, 150, 178, 166, -1, -1, -1, -1, -1, -1, -1, -1,
    67, 54, 122, 36, 125, 62, 24, 82, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 177, 88, 88, 98, 70, 97,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};
void *menu_map_tluts[6] = {
    (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000,
};
void *menu_map_strips[144] = {
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
};
s16 menu_map_world_scale[12] = {
    26, 20, 24, 24, 34, 13, 26, 21, 23, 24, 28, 13,
};
s16 menu_map_origin[12] = {
    139, 125, 124, 124, 88, 133, 88, 95, 87, 78, 60, 96,
};
MenuPictureDma menu_map_picture_dma[10] = {
    { (void*)0x801C0000, 0x00F2FB70, 0x00F3ADD0 }, { (void*)0x801C0000, 0x00F3ADD0, 0x00F46030 },
    { (void*)0x801C0000, 0x00F46030, 0x00F51290 }, { (void*)0x801C0000, 0x00F51290, 0x00F5C4F0 },
    { (void*)0x801C0000, 0x00F5C4F0, 0x00F67750 }, { (void*)0x801C0000, 0x00F67750, 0x00F729B0 },
    { (void*)0x801C0000, 0x00F729B0, 0x00F73050 }, { (void*)0x801C0000, 0x00F73050, 0x00F73730 },
    { (void*)0x801C0000, 0x00F73730, 0x00F73F90 }, { (void*)0x801C0000, 0x00F73F90, 0x00F74890 },
};
void *menu_map_small_tluts[4] = {
    (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000,
};
void *menu_map_small_tex[8] = {
    (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200,
    (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200,
};
u8 menu_map_small_sizes[4][3] = {
    { 0x41, 0x12, 0 }, { 0x41, 0x13, 0 }, { 0x60, 0x11, 0 }, { 0x63, 0x12, 0 },
};
s16 menu_map_small_pos[8] = {
    127, 112, 127, 112, 112, 112, 110, 112,
};
#ifndef NON_MATCHING /* Menu_UpdateOptionsPage's local ids[] initializer in the NON_MATCHING C */
u8 menu_options_marker_sprites[4] = {
    0x28, 0x27, 0x26, 0,
};
#endif
s16 menu_options_top_row_pos[8][2] = {
    { 138, 0 }, { 159, 0 }, { 179, 1 }, { 199, 2 }, { 219, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};
s16 menu_options_bgm_row_pos[5][2] = {
    { 138, 0 }, { 159, 0 }, { 179, 1 }, { 199, 2 }, { 219, 2 },
};
#ifndef NON_MATCHING /* a function static in the NON_MATCHING C */
s32 menu_map_loaded_region = -1;
#endif
MenuExpGaugePalettes menu_exp_gauge_tluts = { { D_80068EB0, D_8006A8F0, D_8006B4D8, D_80069A98 } };
MenuExpGaugeTextures menu_exp_gauge_tex = { { { D_800690B8, D_800695A8 }, { D_8006AAF8, D_8006AFE8 }, { D_8006B6E0, D_8006BBD0 }, { D_80069CA0, D_8006A2C8 } } };
MenuFourWords menu_bg_strip_tex_heights = { { 32, 32, 32, 24 } };
MenuFourWords menu_bg_strip_heights = { { 26, 26, 26, 20 } };
MenuFourPointers menu_bg_strip_tex = { { menu_bg_strip_tex_0, menu_bg_strip_tex_1, menu_bg_strip_tex_2, menu_bg_strip_tex_3 } };








void Menu_PrintNumber(s32 ndigits, s32 x, s32 y, u32 value) {
    s32 i;
    u64 div = 1000000000;
    s64 v = value;
    s8 digits[10];
    s32 j;
    u8 msg[5] = {
#include "assets/D_80061644.inc.c"
    };
    s32 n;

    j = 9;
    if (ndigits >= 10) {
        ndigits = 9;
    }
    for (i = 0; i < 9; i++) {
        n = 0;
        while (TRUE) {
            v -= div;
            if (v < 0) {
                v += div;
                break;
            }
            n++;
        }
        digits[j--] = n;
        div /= 10;
    }
    digits[0] = v;
    i = 0;
    for (n = ndigits - 1; n >= 0; n--) {
        i += digits[n];
        if (i != 0 || n == 0) {
            msg[3] = digits[n];
            Text_DrawEncodedString(x, y, msg);
        }
        x += 10;
    }
}

void Menu_FindMapPageLocation(void) {
    s32 cnt = 0;
    s32 i;
    s32 count = 0;
    s32 sub = -1;
    f32 x;

    s32 idx;
    f32 y;

    for (i = 0; menu_map_location_list[i].a != -8; i++) {
        switch (menu_map_location_list[i].a) {
            case -2:
                i++;
                sub++;
                break;
            case -1:
                i++;
                count++;
                sub = -1;
                break;
        }
        if (menu_map_location_list[i].a == map_id && menu_map_location_list[i].b == map_subarea) {
            break;
        }
    }
    menu_map_region = count;
    menu_map_spot = sub;
    cnt = menu_map_region;
    if (cnt < 6 && menu_map_spot < 0) { idx = cnt; if (menu_map_cursor_x == -1.0f) { menu_map_cursor_x = 115.0f;
            menu_map_cursor_y = 86.0f;
        }
        x = menu_map_cursor_x - menu_map_origin[idx];
        y = menu_map_cursor_y;
        y = y - menu_map_origin[idx + 6];
        menu_map_marker_x = menu_map_world_scale[idx] * x;
        menu_map_marker_z = menu_map_world_scale[idx + 6] * y;
    }
}
