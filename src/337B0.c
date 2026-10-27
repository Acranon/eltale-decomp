#include "common.h"

/*
 * Text windows: slot lifecycle, message and choice layout, input, and drawing.
 * Folder: src/game/text/
 */

typedef struct {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
#ifdef NON_MATCHING
    /* Text_UpdateAndDrawWindows reads these with lb/lhu/lb (the matched functions only store
       them or compile the same with these widths) */
    /* 0x010 */ s8 unk10;
    /* 0x012 */ u16 unk12;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ s8 unk15;
#else
    /* 0x010 */ u8 unk10;
    /* 0x012 */ s16 unk12;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 unk15;
#endif
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17[32];
    /* 0x038 */ s16 unk38;
    /* 0x03A */ s16 unk3A;
    /* 0x03C */ u8 unk3C[4][24];
    /* 0x09C */ u8 unk9C[0x4B0];
    /* 0x54C */ u8 unk54C[0x4B0];
} Unk80090470; /* size = 0x9FC */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} Unk800616A8;

typedef struct {
    /* 0x00 */ s32 n;
    /* 0x04 */ s32 m;
    /* 0x08 */ u8 *rows[4];
} Unk80090458;

typedef struct {
    /* 0x0 */ u8 v[8];
} Unk8Bytes;

typedef struct {
    /* 0x00 */ u8 v[32];
} Bytes32;

typedef struct {
    /* 0x00 */ u8 *p[5];
} TexPtrs5;

typedef struct {
    /* 0x00 */ s32 w;
    /* 0x04 */ s32 h;
    /* 0x08 */ s32 cms;
    /* 0x0C */ s32 cmt;
    /* 0x10 */ s32 masks;
    /* 0x14 */ s32 maskt;
} TexParam; /* size = 0x18 */

typedef struct {
    /* 0x00 */ TexParam e[5];
} TexParams5;

extern Gfx *gfx_dl_head;
extern u16 text_window_tlut[];
/* This file's .data, 80061660..80061760. */
s8 text_reveal_delay_steps[8] = {
    -1, 0, 1, 2, 4, 8, 16, 30,
};
Unk800616A8 text_window_default_rects[8] = {
    { 34, 148, 252, 68 }, { 34, 20, 252, 68 }, { 40, 30, 240, 52 }, { 40, 150, 240, 52 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
};
Unk800616A8 text_choice_window_rect = { 180, 110, 30, 40 };
s8 menu_text_delay_option = 2;
s32 D_800616B4 = -1;
Unk8Bytes D_800616B8 = { { 5, 3, 1, 0, 1, 2, 3, 4 } };
Unk8Bytes D_800616C0 = { { 7, 5, 3, 0, 1, 3, 5, 7 } };
Unk8Bytes D_800616C8 = { { 3, 1, 0, 0, 0, 1, 2, 3 } };
extern u8 text_window_fill_tex[];
extern u8 text_speaker_name_bg_tex[];
extern u8 text_advance_icon_tex[];
extern u8 text_window_line_tex[];
extern u8 text_choice_cursor_tex[];
TexPtrs5 text_rect_texture_ptrs = { { text_window_fill_tex, text_speaker_name_bg_tex, text_advance_icon_tex, text_window_line_tex, text_choice_cursor_tex } };
TexParams5 text_rect_texture_params = { { { 16, 16, 0, 0, 4, 4 }, { 40, 13, 0, 0, 0, 0 }, { 12, 12, 0, 0, 0, 0 }, { 1, 1, 2, 2, 0, 0 }, { 12, 12, 0, 0, 0, 0 } } };
extern u8 text_speaker_name[32];
extern u8 text_message_buf[0x4B0];
extern s32 core_flags;
/* .bss 80090450..80092C70 */
s32 text_active_window_count;
s32 text_last_choice_index;
Unk80090458 text_pending_choice_rows;
Unk80090470 text_window_slots[4];
u8 text_stick_advance_enabled;
u16 text_stick_advance_frames;
extern s8 input_stick_x;
extern s8 input_stick_y;

void Text_ResetWindow(s32 arg0, u8 arg1);
void Text_DrawTexturedRect(s32, s32, s32, s32, s32);
void Text_DrawEncodedString(s32, s32, u8 *);
void Text_ResetStickAdvanceTimer(void);

#ifdef NON_MATCHING
typedef union {
    /* 0x0 */ s8 v[4];
    struct { s8 a, b, c, d; } s;
    s32 w;
} Bytes4;

extern Gfx text_glyph_setup_dl[];
extern u16 input_pressed_buttons;
extern u8 save_menu_choice_cursor;
void Sfx_Play(u8, s8, u8);
s32 Text_AnimateWindowSize(s32);
void Text_DrawWindowFrame(s32);
void Text_BuildVisiblePage(s32);
void Text_DrawAdvanceIndicator(s32);
void Text_MeasureChoiceWindow(s32);
void Text_DrawWindowContents(s32);
s32 Text_IsStickAdvanceHeld(void);
s32 Text_OpenWindow(s32);
#endif

void Text_ResetAllWindows(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        Text_ResetWindow(i, 0);
    }
}

void Text_ResetWindow(s32 arg0, u8 arg1) {
    s32 i;
    s32 j;

    if (arg1 == 0) {
        text_window_slots[arg0].unk6 = 0;
        text_window_slots[arg0].unkA = 0;
        text_window_slots[arg0].unk0 = 0;
        text_window_slots[arg0].unk4 = text_window_slots[arg0].unk6;
        text_window_slots[arg0].unk8 = text_window_slots[arg0].unkA;
    }
    text_window_slots[arg0].unkC = 1;
    text_window_slots[arg0].unkE = 0;
    text_window_slots[arg0].unkF = 0;
    text_window_slots[arg0].unk10 = 0;
    text_window_slots[arg0].unk12 = 0;
    text_window_slots[arg0].unk14 = 0xFF;
    text_window_slots[arg0].unk15 = 0;
    text_window_slots[arg0].unk16 = 0;
    for (i = 0; i < 32; i++) {
        text_window_slots[arg0].unk17[i] = 0xFF;
    }
    for (i = 0; i < 0x4B0; i++) {
        text_window_slots[arg0].unk9C[i] = 0xFF;
        text_window_slots[arg0].unk54C[i] = 0xFF;
    }
    text_window_slots[arg0].unk38 = 0;
    text_window_slots[arg0].unk3A = 0;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 4; j++) {
            text_window_slots[arg0].unk3C[j][i] = 0xFF;
        }
    }
}

s32 Text_OpenWindow(s32 arg0) {
    s32 ret = -1;
    s32 i;
    s32 j;
    s32 k;
    u8 *s;
    s32 c;

    for (i = 0; i < 4; i++) {
        if (text_window_slots[i].unk0 & 0x20000000) {
            j = (text_window_slots[i].unk0 & 7) - 1;
            if (j > 0) {
                text_window_slots[i].unk0 &= ~7;
                text_window_slots[i].unk0 |= j;
                text_window_slots[i].unk0 &= 0x7FFFFFFF;
            }
            text_window_slots[i].unk0 |= 0x400000;
        } else if (ret < 0) {
            text_window_slots[i].unk0 |= 0x10000000;
            if (arg0 < 0) {
                text_window_slots[i].unk0 |= 0x40000000;
                if (arg0 == -2) {
                    text_window_slots[i].unk0 |= 0x80000;
                    text_window_slots[i].unk0 &= ~0x40000000;
                }
                if (arg0 == -3) {
                    text_window_slots[i].unk0 |= 0x80000;
                }
            }
            text_window_slots[i].unk0 &= ~7;
            text_window_slots[i].unk0 |= 4;
            if (!(text_window_slots[i].unk0 & 0x80000)) {
                for (j = 0; j < 32; j++) {
                    text_window_slots[i].unk17[j] = text_speaker_name[j];
                }
                for (j = 0; j < 0x4B0; j++) {
                    c = text_reveal_delay_steps[0] + menu_text_delay_option;
                    text_window_slots[i].unk9C[j] = text_message_buf[j];
                }
                for (k = 0; k < text_pending_choice_rows.n; k++) {
                    s = text_pending_choice_rows.rows[k];
                    for (j = 0; j < 24; j++) {
                        text_window_slots[i].unk3C[k][j] = s[j];
                    }
                }
                text_window_slots[i].unk38 = text_pending_choice_rows.n;
                text_window_slots[i].unk3A = text_pending_choice_rows.m;
                if (arg0 >= 0) {
                    text_window_slots[i].unkE = arg0;
                    text_window_slots[i].unk4 = text_window_default_rects[arg0].unk0;
                    text_window_slots[i].unk6 = text_window_default_rects[arg0].unk2;
                    text_window_slots[i].unk8 = text_window_default_rects[arg0].unk4;
                    text_window_slots[i].unkA = text_window_default_rects[arg0].unk6;
                } else {
                    text_window_slots[i].unk4 = text_choice_window_rect.unk0;
                    text_window_slots[i].unk6 = text_choice_window_rect.unk2;
                    text_window_slots[i].unk8 = text_choice_window_rect.unk4;
                    text_window_slots[i].unkA = text_choice_window_rect.unk6;
                    text_window_slots[i].unkE = 0x80;
                }
                text_window_slots[i].unkF = text_reveal_delay_steps[0] + menu_text_delay_option;
                text_window_slots[i].unk10 = c;
            }
            text_window_slots[i].unk12 = 1;
            text_window_slots[i].unk14 = text_window_slots[i].unk9C[1];
            text_window_slots[i].unk9C[1] = 0xFF;
            ret = i;
            text_active_window_count++;
        }
    }
    core_flags |= 2;
    text_stick_advance_enabled = 0;
    return ret;
}

#ifdef NON_MATCHING
/* 18 words: menu_text_delay_option, the text cursor index and 0xE7000000 sit in other registers (allocation only); code is equivalent */
void Text_UpdateAndDrawWindows(void) {
    Gfx *gfx;
    s32 w;
    s32 idx;
    s32 i;
    s32 j;
    s32 m;
    u8 c;
    s32 x;
    s32 y;
    s32 col;
    Bytes4 order;
    s32 tab;
    s32 max;
    s32 flagD8 = 0;
    s32 flagD4 = 0;
    s32 n = 0;
    s32 cnt = 0;

    order.w = D_800616B4;
    gSPDisplayList(gfx_dl_head++, text_glyph_setup_dl);
    gDPSetBlendColor(gfx_dl_head++, 0, 0, 0, 1);
    for (j = 0; j < 4; j++) {
        c = text_window_slots[j].unk0 & 7;
        switch (c) {
            case 1: order.s.a = j; break;
            case 2: order.s.b = j; break;
            case 3: order.s.c = j; break;
            case 4: order.s.d = j; break;
        }
        if (c != 0) {
            n++;
        }
    }
    for (w = 0; w < 4; w++) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
        gDPPipeSync(gfx_dl_head++);
        gDPLoadTLUT_pal256(gfx_dl_head++, text_window_tlut);
        idx = order.v[w];
        if (idx >= 0) {
            if (text_window_slots[idx].unk0 & 0x10000000) {
                if (Text_AnimateWindowSize(idx) < 0) {
                    text_window_slots[idx].unk0 &= ~0x10000000;
                    text_window_slots[idx].unk0 |= 0xA8000000;
                }
            } else if (text_window_slots[idx].unk0 & 0x01000000) {
                if (Text_AnimateWindowSize(idx) < 0) {
                    text_window_slots[idx].unk0 = 0;
                    for (j = 0; j < 4; j++) {
                        if ((c = text_window_slots[j].unk0 & 7) != 0) {
                            c = c + 1;
                            text_window_slots[j].unk0 &= ~7;
                            text_window_slots[j].unk0 |= c;
                            if (c >= 4) {
                                text_window_slots[j].unk0 &= ~0x400000;
                                text_window_slots[j].unk0 |= 0x80000000;
                                if (text_window_slots[idx].unk0 & 0x80000) {
                                    Text_ResetWindow(j, 1);
                                    text_window_slots[j].unk0 |= 0x01000000;
                                    text_window_slots[j].unk0 &= ~0x80000000;
                                }
                            }
                        }
                    }
                    Text_ResetWindow(idx, 0);
                    text_active_window_count--;
                    if (n <= 0) {
                        core_flags &= ~2;
                    }
                }
            } else {
                if (text_window_slots[idx].unk0 & 0x20000000) {
                    Text_DrawWindowFrame(idx);
                    if (text_window_slots[idx].unk0 & 0x40000000) {
                        gDPPipeSync(gfx_dl_head++);
                        gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xCC);
                        x = text_window_slots[idx].unk4 + 12;
                        y = text_window_slots[idx].unk6 + 6;
                        for (i = 0; i < text_window_slots[idx].unk38; i++) {
                            Text_DrawEncodedString(x, y, text_window_slots[idx].unk3C[i]);
                            y += 13;
                        }
                        if (text_window_slots[idx].unk0 & 0x80000000) {
                            if (input_pressed_buttons & 0xA000) {
                                Sfx_Play(0, 1, 0xFF);
                                if (text_window_slots[idx].unk0 & 0x80000) {
                                    save_menu_choice_cursor = text_window_slots[idx].unk15;
                                } else {
                                    text_last_choice_index = text_window_slots[idx].unk15;
                                }
                                Text_ResetWindow(idx, 1);
                                text_window_slots[idx].unk0 |= 0x01000000;
                            } else {
                                if (input_stick_y > 20) {
                                    if (text_window_slots[idx].unk16 == 0) {
                                        text_window_slots[idx].unk15--;
                                        text_window_slots[idx].unk16 = 1;
                                        Sfx_Play(0, 0, 0xFF);
                                    }
                                } else if (input_stick_y < -20) {
                                    if (text_window_slots[idx].unk16 == 0) {
                                        text_window_slots[idx].unk15++;
                                        text_window_slots[idx].unk16 = 1;
                                        Sfx_Play(0, 0, 0xFF);
                                    }
                                } else {
                                    text_window_slots[idx].unk16 = 0;
                                }
                                if (text_window_slots[idx].unk15 >= text_window_slots[idx].unk38) {
                                    text_window_slots[idx].unk15 = 0;
                                } else if (text_window_slots[idx].unk15 < 0) {
                                    text_window_slots[idx].unk15 = text_window_slots[idx].unk38 - 1;
                                }
                            }
                            if (!(text_window_slots[idx].unk0 & 0x01000000)) {
                                gDPPipeSync(gfx_dl_head++);
                                gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xFF);
                                x = text_window_slots[idx].unk4 - 2;
                                y = text_window_slots[idx].unk6 + text_window_slots[idx].unk15 * 13 + 2;
                                gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
                                gDPLoadTLUT_pal256(gfx_dl_head++, text_window_tlut);
                                Text_DrawTexturedRect(4, x, y, 12, 12);
                            }
                        }
                    } else if (text_window_slots[idx].unk0 & 0x80000000) {
                        if (text_window_slots[idx].unk0 & 0x08000000) {
                            if (text_window_slots[idx].unk0 & 0x04000000) {
                                flagD8 = 1;
                                m = -1;
                                if (input_pressed_buttons & 0xA000) {
                                    j = text_window_slots[idx].unk12;
                                    tab = 0;
                                    text_window_slots[idx].unk9C[j] = text_window_slots[idx].unk14;
                                    max = j;
                                    do {
                                        c = text_window_slots[idx].unk9C[max];
                                        max--;
                                        if (c >= 0xC0 && c < 0xE0 && !(tab & 1)) {
                                            text_window_slots[idx].unk9C[++m] = c;
                                            tab |= 1;
                                        }
                                        if (c >= 0x80 && c < 0xA0 && !(tab & 2)) {
                                            text_window_slots[idx].unk9C[++m] = c;
                                            tab |= 2;
                                        }
                                        if (c >= 0xA0 && c < 0xB0 && !(tab & 4)) {
                                            text_window_slots[idx].unk9C[++m] = c;
                                            tab |= 4;
                                        }
                                    } while (max >= 0);
                                    do {
                                        text_window_slots[idx].unk9C[++m] = text_window_slots[idx].unk9C[j++];
                                    } while (text_window_slots[idx].unk9C[m] != 0xFF);
                                    text_window_slots[idx].unk12 = 1;
                                    text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[1];
                                    text_window_slots[idx].unk9C[1] = 0xFF;
                                    text_window_slots[idx].unk0 &= ~0x04000000;
                                    for (j = 0; j < 0x4B0; j++) {
                                        text_window_slots[idx].unk54C[j] = 0xFF;
                                    }
                                }
                            } else {
                                if (menu_text_delay_option != 0) {
                                    if (!(text_window_slots[idx].unk0 & 0x100000) && (input_pressed_buttons & 0xA000)) {
                                        text_window_slots[idx].unk0 |= 0x100000;
                                    }
                                } else {
                                    text_window_slots[idx].unk0 |= 0x100000;
                                }
                                if (!(text_window_slots[idx].unk0 & 0x100000)) {
                                    text_window_slots[idx].unk10--;
                                    if (text_window_slots[idx].unk10 <= 0) {
                                        text_window_slots[idx].unk10 = text_window_slots[idx].unkF;
                                        col = text_window_slots[idx].unk12++;
                                        text_window_slots[idx].unk9C[col++] = text_window_slots[idx].unk14;
                                        c = text_window_slots[idx].unk14;
                                        text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[col];
                                        *(text_window_slots[idx].unk9C + col) = 0xFF;
                                        switch (c) {
                                            case 0xF2:
                                                text_window_slots[idx].unk0 |= 0x400000;
                                                flagD4 = 1;
                                                Text_MeasureChoiceWindow(idx);
                                                text_window_slots[idx].unk0 |= 0x40000;
                                                break;
                                            case 0xF0:
                                                if (cnt != 0) {
                                                    text_window_slots[idx].unk0 |= 0x04000000;
                                                }
                                                break;
                                            case 0xFF:
                                                text_window_slots[idx].unk0 |= 0x02000000;
                                                text_window_slots[idx].unk0 &= ~0x08000000;
                                                Text_ResetStickAdvanceTimer();
                                                break;
                                            case 0xE1:
                                            case 0xE2:
                                            case 0xE3:
                                            case 0xE4:
                                            case 0xE5:
                                            case 0xE6:
                                            case 0xE7:
                                            case 0xE8:
                                                col = text_reveal_delay_steps[c & 7] * menu_text_delay_option;
                                                text_window_slots[idx].unk10 = text_window_slots[idx].unkF = col;
                                            default:
                                                cnt++;
                                                Sfx_Play(0, 3, 0xFF);
                                                while (c >= 0x80) {
                                                    j = text_window_slots[idx].unk12++;
                                                    text_window_slots[idx].unk9C[j++] = text_window_slots[idx].unk14;
                                                    c = text_window_slots[idx].unk14;
                                                    text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[j];
                                                    *(text_window_slots[idx].unk9C + j) = 0xFF;
                                                }
                                                break;
                                        }
                                    }
                                } else {
                                    j = text_window_slots[idx].unk12;
                                    text_window_slots[idx].unk9C[j] = text_window_slots[idx].unk14;
                                    tab = 0;
                                    col = 0;
                                    max = ((text_window_slots[idx].unk8 - 20) / 10) * 4;
                                    while (TRUE) {
                                        if (text_window_slots[idx].unk9C[j] & 0x80) {
                                            if (text_window_slots[idx].unk9C[j] == 0xE0) {
                                                tab += (text_window_slots[idx].unk8 - 20) / 10;
                                                if (tab < col) {
                                                    col -= tab;
                                                    col += tab;
                                                } else {
                                                    col = tab;
                                                }
                                                if (col >= max) {
                                                    text_window_slots[idx].unk0 |= 0x04000000;
                                                    text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                                    text_window_slots[idx].unk9C[j] = 0xFF;
                                                    text_window_slots[idx].unk12++;
                                                    break;
                                                }
                                            }
                                        } else {
                                            col++;
                                            if (col >= max) {
                                                text_window_slots[idx].unk0 |= 0x04000000;
                                                text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                                text_window_slots[idx].unk9C[j] = 0xFF;
                                                text_window_slots[idx].unk12++;
                                                break;
                                            } else if (max < col) {
                                                text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                                text_window_slots[idx].unk9C[j] = 0xFF;
                                                text_window_slots[idx].unk12++;
                                                text_window_slots[idx].unk0 |= 0x04000000;
                                                break;
                                            }
                                        }
                                        if (text_window_slots[idx].unk9C[j] == 0xF2) {
                                            text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                            text_window_slots[idx].unk9C[j] = 0xFF;
                                            text_window_slots[idx].unk12++;
                                            break;
                                        } else if (text_window_slots[idx].unk9C[j] == 0xF0) {
                                            text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                            text_window_slots[idx].unk9C[j] = 0xFF;
                                            text_window_slots[idx].unk12++;
                                            text_window_slots[idx].unk0 |= 0x04000000;
                                            break;
                                        } else if (text_window_slots[idx].unk9C[j] == 0xFF) {
                                            text_window_slots[idx].unk14 = text_window_slots[idx].unk9C[++j];
                                            text_window_slots[idx].unk9C[j] = 0xFF;
                                            text_window_slots[idx].unk9C[j + 1] = 0xFF;
                                            break;
                                        }
                                        j++;
                                        text_window_slots[idx].unk12++;
                                    }
                                    switch (text_window_slots[idx].unk9C[j - 1]) {
                                        case 0xF2:
                                            text_window_slots[idx].unk0 |= 0x400000;
                                            Text_MeasureChoiceWindow(idx);
                                            flagD4 = 1;
                                            text_window_slots[idx].unk0 |= 0x40000;
                                            break;
                                        case 0xF0:
                                            text_window_slots[idx].unk0 |= 0x04000000;
                                            break;
                                        case 0xFF:
                                            text_window_slots[idx].unk0 |= 0x02000000;
                                            text_window_slots[idx].unk0 &= ~0x08000000;
                                            Text_ResetStickAdvanceTimer();
                                            break;
                                    }
                                    text_window_slots[idx].unk0 &= ~0x100000;
                                }
                            }
                            Text_BuildVisiblePage(idx);
                            Text_DrawWindowContents(idx);
                        } else if (text_window_slots[idx].unk0 & 0x02000000) {
                            if ((input_pressed_buttons & 0xA000) || Text_IsStickAdvanceHeld() != 0) {
                                Text_ResetWindow(idx, 1);
                                text_window_slots[idx].unk0 |= 0x01000000;
                            } else {
                                if (text_window_slots[idx].unk0 & 0x40000) {
                                    text_window_slots[idx].unk0 &= ~0x40000;
                                    Text_ResetWindow(idx, 1);
                                    text_window_slots[idx].unk0 |= 0x01000000;
                                }
                                Text_DrawWindowContents(idx);
                            }
                        }
                    } else {
                        Text_DrawWindowContents(idx);
                    }
                }
                if (flagD8) {
                    Text_DrawAdvanceIndicator(idx);
                }
            }
        }
    }
    if (flagD4) {
        if (text_window_slots[idx].unk0 & 0x80000) {
            Text_OpenWindow(-3);
        } else {
            Text_OpenWindow(-1);
        }
    }
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    gDPPipeSync(gfx_dl_head++);
    gfx = gfx_dl_head++; gfx->words.w0 = 0xF9000000; gfx->words.w1 = 1;
    gfx = gfx_dl_head++; gfx->words.w0 = 0xE7000000; gfx->words.w1 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/337B0/Text_UpdateAndDrawWindows.s")
#endif

s32 Text_AnimateWindowSize(s32 idx) {
    Unk80090470 *p = &text_window_slots[idx];
    s32 ret;
    s32 ww;
    s32 hh;
    s32 x;
    s32 y;
    s16 cx;
    s16 cy;
    u32 steps;

    ret = 0;
    cx = p->unk4 + (p->unk8 >> 1);
    cy = p->unk6 + (p->unkA >> 1);
    if (p->unk0 & 0x10000000) {
        steps = 10;
        ww = p->unk8 / steps;
        ww = p->unkC * ww;
        hh = p->unkA / steps;
        hh = p->unkC * hh;
    } else {
        steps = 8;
        ww = p->unk8 / steps;
        ww = (9 - p->unkC) * ww;
        hh = p->unkA / steps;
        hh = (9 - p->unkC) * hh;
    }
    x = cx - (ww >> 1);
    y = cy - (hh >> 1);
    Text_DrawTexturedRect(0, x, y, ww, hh);
    Text_DrawTexturedRect(3, x + ww, y + 3, 3, hh);
    Text_DrawTexturedRect(3, x + 3, y + hh, ww, 3);
    Text_DrawTexturedRect(3, x, y, ww, 1);
    Text_DrawTexturedRect(3, x, y + hh - 1, ww, 1);
    Text_DrawTexturedRect(3, x, y, 1, hh);
    Text_DrawTexturedRect(3, x + ww - 1, y, 1, hh);
    p->unkC++;
    if (p->unkC > steps) {
        ret = -1;
    }
    return ret;
}

void Text_DrawWindowContents(s32 arg0) {
    s32 x;
    s32 y;

    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xCC);
    if (text_window_slots[arg0].unk17[0] != 0xFF) {
        x = text_window_slots[arg0].unk4;
        y = text_window_slots[arg0].unk6;
        Text_DrawTexturedRect(1, x + 27, y + 4, 40, 13);
        x = text_window_slots[arg0].unk4;
        y = text_window_slots[arg0].unk6;
        Text_DrawEncodedString(x + 73, y + 4, text_window_slots[arg0].unk17);
        x = text_window_slots[arg0].unk4;
        y = text_window_slots[arg0].unk6;
        Text_DrawEncodedString(x + 10, y + 20, text_window_slots[arg0].unk54C);
    } else {
        x = text_window_slots[arg0].unk4;
        x = x + 10;
        y = text_window_slots[arg0].unk6;
        y = y + 12;
        Text_DrawEncodedString(x, y, text_window_slots[arg0].unk54C);
    }
}

void Text_DrawWindowFrame(s32 idx) {
    Unk80090470 *p;
    s32 x;
    s32 y;

    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xCC);
    p = &text_window_slots[idx];
    Text_DrawTexturedRect(0, p->unk4, p->unk6, p->unk8, p->unkA);
    Text_DrawTexturedRect(3, p->unk8 + p->unk4, p->unk6 + 2, 2, p->unkA);
    Text_DrawTexturedRect(3, p->unk4 + 2, p->unkA + p->unk6, p->unk8, 2);
    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xFF);
    x = p->unk4;
    y = p->unk6;
    Text_DrawTexturedRect(3, x, y, p->unk8, 1);
    Text_DrawTexturedRect(3, x, p->unkA + y - 1, p->unk8, 1);
    Text_DrawTexturedRect(3, x, y, 1, p->unkA);
    Text_DrawTexturedRect(3, p->unk8 + x - 1, y, 1, p->unkA);
}

#ifdef NON_MATCHING
/* frame 0x40 vs 0x48, one more saved register, row loop tested as row != rows + 1; code is equivalent */
void Text_BuildVisiblePage(s32 idx) {
    Unk80090470 *p = &text_window_slots[idx];
    s32 cols = (p->unk8 - 20) / 10 + 1;
    s32 rows = (p->unkA - 20) / 13;
    s32 k = 0;
    s32 dst = -1;
    s32 src = -1;
    s32 row;
    s32 col;
    s32 j;
    s32 n;
    u8 c;

    for (row = 1; row <= rows; row++) {
        for (col = 0; col < cols;) {
            text_window_slots[idx].unk54C[++dst] = text_window_slots[idx].unk9C[++src];
            c = text_window_slots[idx].unk54C[dst];
            if (c & 0x80) {
                if (c == 0xE0 || c == 0xFF || (c == 0xF0 && k != 0)) {
                    break;
                }
            } else {
                col++;
                k++;
            }
        }
        c = text_window_slots[idx].unk54C[dst];
        if (c == 0xFF) {
            break;
        }
        if (c == 0xF0) {
            p->unk0 |= 0x4000000;
            break;
        }
        if (c != 0xE0 && c != 0xE0) {
            n = -1;
            for (j = src + 1; text_window_slots[idx].unk9C[j] >= 0x80; j++) {
                if (text_window_slots[idx].unk9C[j] == 0xE0) {
                    for (n = j - src; n > 0; n--) {
                        text_window_slots[idx].unk54C[++dst] = text_window_slots[idx].unk9C[++src];
                    }
                    text_window_slots[idx].unk54C[++dst] = text_window_slots[idx].unk9C[++src];
                    n = 0;
                    break;
                }
            }
            if (n != 0) {
                text_window_slots[idx].unk54C[++dst] = 0xE0;
            }
        }
    }
    c = text_window_slots[idx].unk54C[dst];
    if (c != 0xFF && c != 0xF0) {
        p->unk0 |= 0x4000000;
        p->unk54C[dst + 1] = 0xFF;
        if (p->unk14 != 0xFF) {
            p->unk9C[(u16)p->unk12] = p->unk14;
            p->unk12 = src + 1;
            p->unk14 = p->unk9C[src + 1];
            p->unk9C[src + 1] = 0xFF;
        } else {
            p->unk0 |= 0x2000000;
            p->unk0 &= ~0x8000000;
            Text_ResetStickAdvanceTimer();
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/337B0/Text_BuildVisiblePage.s")
#endif

void Text_DrawAdvanceIndicator(s32 idx) {
    s32 x;
    s32 y;
    s32 i;
    Unk8Bytes a = D_800616B8;
    Unk8Bytes b = D_800616C0;
    Unk8Bytes c = D_800616C8;

    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    gDPPipeSync(gfx_dl_head++);
    gDPLoadTLUT_pal256(gfx_dl_head++, text_window_tlut);
    text_window_slots[idx].unkC++;
    i = (text_window_slots[idx].unkC >> 1) & 7;
    x = text_window_slots[idx].unk4 + text_window_slots[idx].unk8 - 11;
    y = text_window_slots[idx].unk6 + text_window_slots[idx].unkA - 3;
    x -= c.v[i];
    Text_DrawTexturedRect(3, x, y, b.v[i], 1);
    x = text_window_slots[idx].unk4 + text_window_slots[idx].unk8 - 12;
    y = text_window_slots[idx].unk6 + text_window_slots[idx].unkA - 15;
    x = a.v[i] + x;
    y -= a.v[i];
    Text_DrawTexturedRect(2, x, y, 12, 12);
}

void Text_MeasureChoiceWindow(s32 arg0) {
    s32 max = 0;
    s32 n = text_window_slots[arg0].unk38;
    s32 i;
    s32 j;
    s32 cnt;

    text_choice_window_rect.unk6 = n * 13 + 12;
    for (i = 0; i < n; i++) {
        j = 0;
        cnt = 0;
        while (text_window_slots[arg0].unk3C[i][j] != 0xFF) {
            if (text_window_slots[arg0].unk3C[i][j] < 0x80) {
                cnt++;
            }
            j++;
        }
        if (max < cnt) {
            max = cnt;
        }
    }
    text_choice_window_rect.unk4 = max * 10 + 24;
}

s32 Text_FindWindow(s32 arg0, s32 arg1) {
    s32 ret = -1;
    s32 i;

    if (arg0 >= 0) {
        for (i = 0; i < 4; i++) {
            if (arg0 == text_window_slots[i].unkE) {
                ret = i;
                break;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (arg1 == (text_window_slots[i].unk0 & 7)) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

#ifdef NON_MATCHING
/* frame 0xE0 vs 0xD8, type == 0 tested as &tex.p[type] == &tex.p[0], one dead _g home store missing; code is equivalent */
void Text_DrawTexturedRect(s32 type, s32 x, s32 y, s32 w, s32 h)
{
  u32 new_var;
  Gfx *new_var2;
  TexParam *t;
  TexPtrs5 tex = text_rect_texture_ptrs;
  TexParams5 prm = text_rect_texture_params;

  { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; }
  ;
  t = &prm.e[type];
  {
    { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = ((((unsigned int) ((((unsigned int) 0xfd) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (t->w - 1)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (unsigned int) tex.p[type]; }
    ;
    { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) ((((((t->w - 1) - 0) + 1) * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) t->cmt) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) t->maskt) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) t->cms) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) prm.e[type].masks) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); }
    ;
    { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe6) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; }
    ;
    { Gfx *_g = (Gfx *) (gfx_dl_head++); new_var2 = _g; new_var2->words.w0 = (((unsigned int) ((((unsigned int) 0xf4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (0 << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) (0 << 2)) & ((0x01 << 12) - 1)) << 0)); new_var2->words.w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((t->w - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((prm.e[type].h - 1) << 2)) & ((0x01 << 12) - 1)) << 0)); }
    ;
 { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (((((unsigned int) ((((unsigned int) 0xf5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) ((((((t->w - 1) - 0) + 1) * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0)); _g->words.w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) t->cmt) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) t->maskt) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) t->cms) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) prm.e[type].masks) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0)); } ; { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (0 << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) (0 << 2)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((t->w - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((prm.e[type].h - 1) << 2)) & ((0x01 << 12) - 1)) << 0)); } } ; { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; if (type == 0) { { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (((unsigned int) (new_var = (((unsigned int) 0xe4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((x + w) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((y + h) << 2)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (x << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) (y << 2)) & ((0x01 << 12) - 1)) << 0)); { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) ((-65) - 11)) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) ((x & 0xF) << 5)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) ((y & 0xF) << 5)) & ((0x01 << 16) - 1)) << 0))); } ; { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) ((-65) - 12)) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 0))); } ; } ; } else { { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((x + w) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((y + h) << 2)) & ((0x01 << 12) - 1)) << 0)); _g->words.w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (x << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) (y << 2)) & ((0x01 << 12) - 1)) << 0)); { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) ((-65) - 11)) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0))); } ; { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) ((-65) - 12)) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) (((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 0))); } ; }
    ;
  }
  { Gfx *_g = (Gfx *) (gfx_dl_head++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; }
  ;

}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/337B0/Text_DrawTexturedRect.s")
#endif

void Text_DrawFramedRect(s32 x, s32 y, s32 w, s32 h) {
    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xCC);
    Text_DrawTexturedRect(0, x, y, w, h);
    Text_DrawTexturedRect(3, x + w, y + 2, 2, h);
    Text_DrawTexturedRect(3, x + 2, y + h, w, 2);
    gDPPipeSync(gfx_dl_head++);
    gDPSetEnvColor(gfx_dl_head++, 0xFF, 0xFF, 0xFF, 0xFF);
    Text_DrawTexturedRect(3, x, y, w, 1);
    Text_DrawTexturedRect(3, x, y + h - 1, w, 1);
    Text_DrawTexturedRect(3, x, y, 1, h);
    Text_DrawTexturedRect(3, x + w - 1, y, 1, h);
}

void Text_ResetStickAdvanceTimer(void) {
    text_stick_advance_frames = 0;
}

s32 Text_IsStickAdvanceHeld(void) {
    s32 ret = 0;
    u32 sum;

    if (text_stick_advance_enabled != 0) {
        sum = input_stick_x * input_stick_x + input_stick_y * input_stick_y;
        if (sum > 60 * 60) {
            text_stick_advance_frames++;
            if (text_stick_advance_frames >= 5) {
                ret = 1;
            }
        } else {
            text_stick_advance_frames = 0;
        }
    }
    return ret;
}
