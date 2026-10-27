#ifndef GAME_TEXT_TEXT_H
#define GAME_TEXT_TEXT_H

#include "common.h"

typedef struct TextFontMetrics {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 advance;
    /* 0x0C */ s32 line_height;
} TextFontMetrics; /* 0x10 bytes */

extern TextFontMetrics text_font_metrics[1];
extern Gfx text_glyph_setup_dl[20];
extern s32 text_font_index;
extern s32 text_extra_glyph_spacing;

void Text_CopyTerminatedBytes(u8 *dst, u8 *src);
void Text_LoadFontAssets(void);
void Text_DrawEncodedString(s32 x0, s32 y0, u8 *str);

#endif
