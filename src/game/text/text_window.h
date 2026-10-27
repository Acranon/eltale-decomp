#ifndef GAME_TEXT_TEXT_WINDOW_H
#define GAME_TEXT_TEXT_WINDOW_H

#include "common.h"

typedef struct TextWindow {
    /* 0x000 */ s32 flags;
    /* 0x004 */ s16 x;
    /* 0x006 */ s16 y;
    /* 0x008 */ s16 width;
    /* 0x00A */ s16 height;
    /* 0x00C */ s16 anim_frame;
    /* 0x00E */ u8 window_type;
    /* 0x00F */ u8 reveal_delay;
#ifdef NON_MATCHING
    /* Text_UpdateAndDrawWindows reads these with lb/lhu/lb (the matched functions only store
       them or compile the same with these widths) */
    /* 0x010 */ s8 reveal_timer;
    /* 0x012 */ u16 reveal_index;
    /* 0x014 */ u8 pending_byte;
    /* 0x015 */ s8 choice_cursor;
#else
    /* 0x010 */ u8 reveal_timer;
    /* 0x012 */ s16 reveal_index;
    /* 0x014 */ u8 pending_byte;
    /* 0x015 */ u8 choice_cursor;
#endif
    /* 0x016 */ u8 choice_input_latch;
    /* 0x017 */ u8 speaker_name[32];
    /* 0x038 */ s16 choice_count;
    /* 0x03A */ s16 unk3A;
    /* 0x03C */ u8 choice_rows[4][24];
    /* 0x09C */ u8 message_bytes[0x4B0];
    /* 0x54C */ u8 visible_bytes[0x4B0];
} TextWindow; /* size = 0x9FC */

typedef struct TextWindowRect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
} TextWindowRect; /* 0x8 bytes */

typedef struct TextChoiceRows {
    /* 0x00 */ s32 n;
    /* 0x04 */ s32 m;
    /* 0x08 */ u8 *rows[4];
} TextChoiceRows; /* 0x18 bytes */

typedef struct TextAnimSteps {
    /* 0x0 */ u8 v[8];
} TextAnimSteps; /* 0x8 bytes */

typedef struct TextTexturePointers {
    /* 0x00 */ u8 *p[5];
} TextTexturePointers; /* 0x14 bytes */

typedef struct TextTextureTile {
    /* 0x00 */ s32 w;
    /* 0x04 */ s32 h;
    /* 0x08 */ s32 cms;
    /* 0x0C */ s32 cmt;
    /* 0x10 */ s32 masks;
    /* 0x14 */ s32 maskt;
} TextTextureTile; /* size = 0x18 */

typedef struct TextTextureTiles {
    /* 0x00 */ TextTextureTile e[5];
} TextTextureTiles; /* 0x78 bytes */

extern s8 text_reveal_delay_steps[8];
extern TextWindowRect text_window_default_rects[8];
extern TextWindowRect text_choice_window_rect;
extern s8 menu_text_delay_option;
extern s32 text_choice_order_empty_word;
extern TextAnimSteps text_advance_icon_diagonal_offsets;
extern TextAnimSteps text_advance_line_widths;
extern TextAnimSteps text_advance_line_x_offsets;
extern TextTexturePointers text_rect_texture_ptrs;
extern TextTextureTiles text_rect_texture_params;
extern s32 text_active_window_count;
extern s32 text_last_choice_index;
extern TextChoiceRows text_pending_choice_rows;
extern TextWindow text_window_slots[4];
extern u8 text_stick_advance_enabled;
extern u16 text_stick_advance_frames;

void Text_ResetAllWindows(s32 arg0);
void Text_ResetWindow(s32 arg0, u8 arg1);
s32 Text_OpenWindow(s32 arg0);
void Text_UpdateAndDrawWindows(void);
s32 Text_AnimateWindowSize(s32 idx);
void Text_DrawWindowContents(s32 arg0);
void Text_DrawWindowFrame(s32 idx);
void Text_BuildVisiblePage(s32 idx);
void Text_DrawAdvanceIndicator(s32 idx);
void Text_MeasureChoiceWindow(s32 arg0);
s32 Text_FindWindow(s32 arg0, s32 arg1);
void Text_DrawFramedRect(s32 x, s32 y, s32 w, s32 h);
void Text_ResetStickAdvanceTimer(void);
s32 Text_IsStickAdvanceHeld(void);
void Text_DrawTexturedRect(s32 type, s32 x, s32 y, s32 w, s32 h);

#endif
