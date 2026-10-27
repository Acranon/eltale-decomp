#include "common.h"

/*
 * Title overlay: draws the title screen, its menu cursors and message windows; screen fades.
 * Folder: src/game/title/   (proposed for round 4)
 */

typedef struct {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
} UnkStruct_8020EF00;

typedef struct {
    s16 x;
    s16 y;
} UnkPos_8020F4DC;

typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
} UnkFade_8020F4F8;

extern Gfx* gfx_dl_head;
extern u16 D_8020FE10_ovl_title[];
extern u8 D_80210010_ovl_title[];
extern u8 D_80210D20_ovl_title[];

/* .data 8020F200..8020F510. The data before it (8020F1E0..F200) is DAB5F0.c's, still asm. */
s32 D_8020F200_ovl_title = 0;
Gfx D_8020F208_ovl_title[11] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xB6000000, 0xFFFFFFFF }},
    {{ 0xB7000000, 0x00000204 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xBA000903, 0x00000C00 }},
    {{ 0xBA001102, 0x00020000 }},
    {{ 0xB9000002, 0x0C087008 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xBA000C02, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F260_ovl_title[4] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x0F0A4000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F280_ovl_title[5] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F2A8_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF4000000, 0x0706A02C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400800, 0x00000000 }},
    {{ 0xF2000000, 0x000D402C }},
    {{ 0xE41AC2B0, 0x000D4280 }},
    {{ 0xB4000000, 0x00000000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F300_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF406C000, 0x070D802C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400800, 0x00000000 }},
    {{ 0xF20D8000, 0x001B002C }},
    {{ 0xE42E02B0, 0x00204280 }},
    {{ 0xB4000000, 0x06C00000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F358_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480A00, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF40DA000, 0x0715C02C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400A00, 0x00000000 }},
    {{ 0xF21B4000, 0x002B802C }},
    {{ 0xE44342B0, 0x0032C280 }},
    {{ 0xB4000000, 0x0DA00000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F3B0_ovl_title[21] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFD100000, (u32) D_8020FE10_ovl_title }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFD480063, (u32) D_80210010_ovl_title }},
    {{ 0xF5481800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF4000000, 0x07168038 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5481800, 0x00000000 }},
    {{ 0xF2000000, 0x00168038 }},
    {{ 0xE43342BC, 0x001C8280 }},
    {{ 0xB4000000, 0x00000000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F458_ovl_title[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F470_ovl_title[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC32FFFF, 0x1FFFF6FB }},
    {{ 0xB8000000, 0x00000000 }},
};
/* not referenced by name */
s32 D_8020F488_ovl_title[18] = {
    0x00000035, 0x000000A0, 0x00000000, 0x00000000, 0x00000036, 0x0000000C,
    0x00000081, 0x000000A0, 0x00000036, 0x00000000, 0x00000037, 0x0000000C,
    0x000000CB, 0x000000A0, 0x0000006D, 0x00000000, 0x00000042, 0x0000000C,
};
#define GFX_WORDS(a, b) { Gfx *_g = gfx_dl_head++; _g->words.w0 = (a); _g->words.w1 = (b); }


extern u8 title_menu_choice;
extern s8 input_stick_x;
extern s8 input_stick_y;
extern u16 text_font_tlut[];
extern u16 title_menu_cursor_tlut[];
extern u8 title_menu_cursor_tex[];
extern u8 title_menu_strip_tex[];
extern u16 title_menu_strip_tlut[];
extern u16 D_80210D00_ovl_title[];
extern u8 D_80211148_ovl_title[];
extern u16 D_802111A8_ovl_title[];
extern u8 D_802113A8_ovl_title[];
extern u8 D_80211428_ovl_title[];
extern u8 D_80211464_ovl_title[];
extern u8 D_802114E0_ovl_title[];
extern u8 D_8021150C_ovl_title[];
extern u8 D_80211540_ovl_title[];
extern u8 D_80211548_ovl_title[];
extern u16 title_center_image_tlut[];
extern u8 title_center_image_tex[];
extern u16 title_background_tlut[];
extern u8 title_background_tex[];
extern u16 D_80226AF8_ovl_title[];
extern u8 D_80226D00_ovl_title[];
extern u8 D_80226D18_ovl_title[];

void Sfx_Enqueue(s32, s32, s32);
void Text_DrawTexturedRect(s32, s32, s32, s32, s32);
void Text_DrawEncodedString(s32, s32, u8*);


/* .bss 80226DB0..80226DD0: DB0 and DB4 are shared with DAB5F0.c */
s8 title_confirmation_row;
s32 title_overlay_fade_alpha;

void Title_DrawScreenAndMoveCursor(s32 arg0) {
    static s32 title_cursor_blink_frame = 0;
    static s8 title_menu_row = 0;
    static s8 title_option_index = 0;
    static UnkPos_8020F4DC title_option_cursor_positions[5] = { { 0x2A, 0xA0 }, { 0x77, 0xA1 }, { 0xBF, 0xA0 }, { 0, 0 }, { 0, 0 } };
    static s8 title_previous_direction_bits;
    static s8 title_vertical_direction;
    static s8 title_horizontal_direction;
    static u8* title_current_message;
    s32 i;
    s32 blink;
    s8 held;
    s8 pressed;
    s8 t;
    s8 dx;
    s8 dy;

    if (D_8020F200_ovl_title == 0) {
        title_cursor_blink_frame = 0;
        title_confirmation_row = 0;
        if (title_menu_choice & 0xF0) {
            title_option_index = ((title_menu_choice >> 4) & 0xF) - 1;
        } else {
            title_option_index = 0;
        }
        title_current_message = D_802113A8_ovl_title;
        D_8020F200_ovl_title = 1;
    }

    gSPDisplayList(gfx_dl_head++, D_8020F260_ovl_title);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, title_background_tlut);
    for (i = 0; i < 37; i++) {
        gDPLoadTextureTile(gfx_dl_head++, title_background_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i * 6, 319, i * 6 + 5, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx_dl_head++, 0 << 2, (i * 6) << 2, 320 << 2, (i * 6 + 6) << 2, G_TX_RENDERTILE, 0, (i * 6) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile(gfx_dl_head++, title_background_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i * 6, 319, i * 6 + 1, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 0 << 2, (i * 6) << 2, 320 << 2, (i * 6 + 2) << 2, G_TX_RENDERTILE, 0, (i * 6) << 5, 1 << 10, 1 << 10);

    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, title_center_image_tlut);
    for (i = 0; i < 7; i++) {
        gDPLoadTextureTile(gfx_dl_head++, title_center_image_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 194, 0, 0, i * 10, 193, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx_dl_head++, 63 << 2, (i * 10 + 69) << 2, 257 << 2, (i * 10 + 79) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile(gfx_dl_head++, title_center_image_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 194, 0, 0, i * 10, 193, i * 10 + 5, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 63 << 2, (i * 10 + 69) << 2, 257 << 2, (i * 10 + 75) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);

    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, title_menu_strip_tlut);
    gDPLoadTextureTile_4b(gfx_dl_head++, title_menu_strip_tex, G_IM_FMT_CI, 160, 0, 0, 0, 146, 9, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 85 << 2, 178 << 2, 232 << 2, 188 << 2, G_TX_RENDERTILE, 0, 0 << 5, 1 << 10, 1 << 10);
    gDPLoadTextureTile_4b(gfx_dl_head++, title_menu_strip_tex, G_IM_FMT_CI, 160, 0, 0, 10, 146, 15, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 85 << 2, 188 << 2, 232 << 2, 194 << 2, G_TX_RENDERTILE, 0, 10 << 5, 1 << 10, 1 << 10);

    held = 0;
    if (input_stick_x > 20) {
        held = 8;
    } else if (input_stick_x < -20) {
        held = 4;
    }
    if (input_stick_y > 20) {
        held |= 1;
    }
    if (input_stick_y < -20) {
        held |= 2;
    }
    title_vertical_direction = 0;
    pressed = (held ^ title_previous_direction_bits) & held;
    title_previous_direction_bits = held;
    title_horizontal_direction = 0;
    if (pressed & 1) {
        title_vertical_direction = -1;
    }
    if (pressed & 2) {
        title_vertical_direction = 1;
    }
    if (pressed & 4) {
        title_horizontal_direction = -1;
    }
    if (pressed & 8) {
        title_horizontal_direction = 1;
    }

    switch (arg0) {
        case 0:
        case 1:
            if (arg0 < 2) {
                gSPDisplayList(gfx_dl_head++, D_8020F3B0_ovl_title);
            }
            break;
        case 2:
            if (arg0 == 2) {
                title_menu_row += title_vertical_direction;
                if (title_menu_row < 0) {
                    title_menu_row = 0;
                } else if (title_menu_row >= 3) {
                    title_menu_row = 2;
                } else if (title_vertical_direction != 0) {
                    title_cursor_blink_frame = 0;
                }
                if ((title_option_index += title_horizontal_direction) < 0) {
                    title_option_index = 0;
                } else if (title_option_index >= 3) {
                    title_option_index = 2;
                } else if (title_horizontal_direction != 0) {
                    title_cursor_blink_frame = 0;
                }
                if (title_horizontal_direction != 0) {
                    Sfx_Enqueue(0, 0xFF, 0x40);
                }
                title_menu_choice &= 0xF;
                title_menu_choice |= (title_option_index + 1) << 4;
            }
        case 6:
        case 7:
        case 8:
            if (arg0 != 6) {
                title_confirmation_row += title_vertical_direction;
                if (title_vertical_direction != 0) {
                    Sfx_Enqueue(0, 0xFF, 0x40);
                }
                if (title_confirmation_row < 0) {
                    title_confirmation_row = 0;
                } else if (title_confirmation_row >= 2) {
                    title_confirmation_row = 1;
                }
            }
        case 3:
        case 4:
        case 5:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            gSPDisplayList(gfx_dl_head++, D_8020F280_ovl_title);
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80210D00_ovl_title);
            gSPDisplayList(gfx_dl_head++, D_8020F2A8_ovl_title);
            gSPDisplayList(gfx_dl_head++, D_8020F300_ovl_title);
            gSPDisplayList(gfx_dl_head++, D_8020F358_ovl_title);
            if (arg0 == 3 || arg0 == 5) {
                gDPPipeSync(gfx_dl_head++);
                GFX_WORDS(0xB900031D, 0x504240);
                gSPDisplayList(gfx_dl_head++, D_8020F458_ovl_title);
            }
            if (++title_cursor_blink_frame >= 32) {
                title_cursor_blink_frame = 0;
            }
            if (title_cursor_blink_frame > 16) {
                blink = 8 - title_cursor_blink_frame / 4;
            } else {
                blink = title_cursor_blink_frame / 4;
            }
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_802111A8_ovl_title);
            gDPLoadTextureTile_4b(gfx_dl_head++, D_80211148_ovl_title, G_IM_FMT_CI, 16, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, title_option_cursor_positions[title_option_index].x << 2, title_option_cursor_positions[title_option_index].y << 2,
                                (title_option_cursor_positions[title_option_index].x + 11) << 2, (title_option_cursor_positions[title_option_index].y + 11) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            if (arg0 == 6 || arg0 == 7 || arg0 == 8 || arg0 == 9 || arg0 == 10 || arg0 == 11 || arg0 == 12 || arg0 == 13 || arg0 == 14) {
                if (arg0 == 6) {
                    title_current_message = D_802113A8_ovl_title;
                } else if (arg0 == 7) {
                    title_current_message = D_80211428_ovl_title;
                } else if (arg0 == 8) {
                    title_current_message = D_80211464_ovl_title;
                } else if (arg0 == 9) {
                    title_current_message = D_802114E0_ovl_title;
                } else if (arg0 == 10) {
                    title_current_message = D_8021150C_ovl_title;
                }
                gDPPipeSync(gfx_dl_head++);
                gDPLoadTLUT_pal256(gfx_dl_head++, text_font_tlut);
                gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255);
                Text_DrawTexturedRect(0, 0x3E, 0x28, 0xC4, 0x67);
                Text_DrawTexturedRect(3, 0x102, 0x2A, 2, 0x67);
                Text_DrawTexturedRect(3, 0x40, 0x8F, 0xC4, 2);
                gDPPipeSync(gfx_dl_head++);
                Text_DrawTexturedRect(3, 0x3E, 0x28, 0xC4, 1);
                Text_DrawTexturedRect(3, 0x3E, 0x8E, 0xC4, 1);
                Text_DrawTexturedRect(3, 0x3E, 0x28, 1, 0x67);
                Text_DrawTexturedRect(3, 0x101, 0x28, 1, 0x67);
                gDPPipeSync(gfx_dl_head++);
                gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
                GFX_WORDS(0xB900031D, 0x504240);
                gDPLoadTLUT_pal256(gfx_dl_head++, D_80226AF8_ovl_title);
                gDPPipeSync(gfx_dl_head++);
                gDPLoadTextureTile(gfx_dl_head++, D_80226D00_ovl_title, G_IM_FMT_CI, G_IM_SIZ_8b, 4, 4, 0, 0, 3, 3, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 64 << 2, 42 << 2, 256 << 2, 43 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
                gDPLoadTextureTile(gfx_dl_head++, D_80226D00_ovl_title, G_IM_FMT_CI, G_IM_SIZ_8b, 4, 4, 0, 0, 3, 3, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 64 << 2, 42 << 2, 65 << 2, 140 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
                gDPLoadTextureTile(gfx_dl_head++, D_80226D18_ovl_title, G_IM_FMT_CI, G_IM_SIZ_8b, 4, 4, 0, 0, 3, 3, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 64 << 2, 141 << 2, 256 << 2, 142 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
                gDPLoadTextureTile(gfx_dl_head++, D_80226D18_ovl_title, G_IM_FMT_CI, G_IM_SIZ_8b, 4, 4, 0, 0, 3, 3, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 256 << 2, 42 << 2, 257 << 2, 142 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                gDPPipeSync(gfx_dl_head++);
                gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255);
                Text_DrawEncodedString(0x44, 0x2E, title_current_message);
                if (arg0 == 8 || arg0 == 7 || arg0 == 11 || arg0 == 12 || arg0 == 13 || arg0 == 14) {
                    Text_DrawEncodedString(0x94, 0x73, D_80211540_ovl_title);
                    Text_DrawEncodedString(0x94, 0x80, D_80211548_ovl_title);
                    if (arg0 == 11 || arg0 == 12 || arg0 == 13 || arg0 == 14) {
                        gDPPipeSync(gfx_dl_head++);
                        GFX_WORDS(0xB900031D, 0x504240);
                        gSPDisplayList(gfx_dl_head++, D_8020F458_ovl_title);
                        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, title_overlay_fade_alpha);
                    }
                    gDPPipeSync(gfx_dl_head++);
                    gSPDisplayList(gfx_dl_head++, D_8020F458_ovl_title);
                    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
                    GFX_WORDS(0xB900031D, 0x504240);
                    gDPLoadTLUT_pal256(gfx_dl_head++, title_menu_cursor_tlut);
                    gDPLoadTextureTile(gfx_dl_head++, title_menu_cursor_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, 100, 0, 113, 9, 0, 0, 0, 0, 0, 0, 0);
                    gSPTextureRectangle(gfx_dl_head++, (blink + 123) << 2, (title_confirmation_row * 13 + 118) << 2, (blink + 137) << 2, (title_confirmation_row * 13 + 128) << 2, G_TX_RENDERTILE, 100 << 5, 0, 1 << 10, 1 << 10);
                    gDPLoadTextureTile(gfx_dl_head++, title_menu_cursor_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, 51, 0, 57, 6, 0, 0, 0, 0, 0, 0, 0);
                    gSPTextureRectangle(gfx_dl_head++, 114 << 2, (title_confirmation_row * 13 + 120) << 2, 121 << 2, (title_confirmation_row * 13 + 127) << 2, G_TX_RENDERTILE, 51 << 5, 0, 1 << 10, 1 << 10);
                    gDPLoadTextureTile(gfx_dl_head++, title_menu_cursor_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, 72, 0, 85, 13, 0, 0, 0, 0, 0, 0, 0);
                    gSPTextureRectangle(gfx_dl_head++, (blink + 122) << 2, (title_confirmation_row * 13 + 116) << 2, (blink + 136) << 2, (title_confirmation_row * 13 + 130) << 2, G_TX_RENDERTILE, 72 << 5, 0, 1 << 10, 1 << 10);
                    gDPLoadTextureTile(gfx_dl_head++, title_menu_cursor_tex, G_IM_FMT_CI, G_IM_SIZ_8b, 128, 0, 22, 0, 28, 6, 0, 0, 0, 0, 0, 0, 0);
                    gSPTextureRectangle(gfx_dl_head++, 114 << 2, (title_confirmation_row * 13 + 118) << 2, 121 << 2, (title_confirmation_row * 13 + 125) << 2, G_TX_RENDERTILE, 22 << 5, 0, 1 << 10, 1 << 10);
                }
            }
            break;
    }
}

s32 title_screen_fade_state = 0;
s32 title_screen_fade_frames = 2;
s32 D_80226DC0_ovl_title;

void Title_StepAndDrawScreenFade(UnkStruct_8020EF00* arg0);

void Title_UpdateScreenFade(void) {
    static UnkFade_8020F4F8 fade = { 0 };

    if (title_screen_fade_state == 0) {
        if (fade.unk0 != 0) {
            fade.unk0 = 0;
        }
    } else {
        if (fade.unk0 == 0) {
            fade.unk0 = -1;
            fade.unk4 = 255.0f / title_screen_fade_frames;
            fade.unk2 = title_screen_fade_frames;
            switch (title_screen_fade_state) {
                case 1:
                case 3:
                    fade.unk8 = 0.0f;
                    break;
                case 2:
                case 4:
                    fade.unk8 = 255;
                    break;
                default:
                    fade.unk8 = 128.0f;
                    break;
            }
        }
        Title_StepAndDrawScreenFade((UnkStruct_8020EF00*) &fade);
    }
}

void Title_StepAndDrawScreenFade(UnkStruct_8020EF00* arg0) {
    s32 rgbColorValue;
    s32 alpha;

    arg0->unk2 -= 1;
    if (title_screen_fade_state & 1) {
        arg0->unk8 += arg0->unk4;
    } else {
        arg0->unk8 -= arg0->unk4;
    }
    switch (title_screen_fade_state) {
    case 3:
    case 4:
        rgbColorValue = 255;
        break;
    case 1:
    case 2:
        rgbColorValue = 0;
        break;
    default:
        rgbColorValue = 0;
        break;
    }

    if (arg0->unk8 <= 0.0f) {
        title_screen_fade_state = 0;
        arg0->unk8 = 0.0f;
        arg0->unk0 = 0;
    } else if (arg0->unk8 > 255.0f) {
        title_screen_fade_state = 0;
        arg0->unk8 = 255.0f;
        arg0->unk0 = 0;
    }
    if (arg0->unk2 == 0) {
        if ((title_screen_fade_state == 3) || (title_screen_fade_state == 1)) {
            title_screen_fade_state = 0;
            arg0->unk8 = 255.0f;
            arg0->unk0 = 0;
        } else if ((title_screen_fade_state == 4) || (title_screen_fade_state == 2)) {
            title_screen_fade_state = 0;
            arg0->unk8 = 0.0f;
            arg0->unk0 = 0;
        }
    }

    alpha = arg0->unk8;
    gDPPipeSync(gfx_dl_head++);
    gDPSetPrimColor(gfx_dl_head++, 0, 0, rgbColorValue, rgbColorValue, rgbColorValue, alpha);
    gDPSetRenderMode(gfx_dl_head++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(gfx_dl_head++, D_8020F470_ovl_title);
    gDPFillRectangle(gfx_dl_head++, 0, 0, 336, 960);

    D_80226DC0_ovl_title = rgbColorValue;
}
