#ifndef GAME_GFX_FADE_H
#define GAME_GFX_FADE_H

#include "common.h"

struct GfxFrameData;

typedef struct ColorRGBA8 {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} ColorRGBA8; /* 0x4 bytes */

/* .bss 8008CA50..8008CE60 */
extern u16 fade_flags; /* bit 0 quad on, 1 hold at the end, 2 step the ramp backwards, 3 letterbox bars */
extern u8 fade_grey_ramp_256[0x100][4];
extern s32 fade_frames_left;
extern ColorRGBA8 *fade_ramp_ptr;

/* .data 8004F4D0..8004F770 */
extern Vtx fade_quad_vtx[4];
extern Gfx fade_quad_dl[8];
extern Gfx fade_letterbox_dl[10];
extern ColorRGBA8 fade_black_ramp[5];
extern ColorRGBA8 fade_black_ramp_dim[10];
extern ColorRGBA8 fade_black_ramp_end[1];
extern ColorRGBA8 fade_grey_ramp[15];
extern ColorRGBA8 fade_grey_ramp_end[1];
extern ColorRGBA8 fade_black_ramp_slow[31];
extern ColorRGBA8 fade_black_ramp_slow_end[9];
extern ColorRGBA8 fade_grey_ramp_slow[31];
extern ColorRGBA8 fade_grey_ramp_slow_end[9];
extern ColorRGBA8 fade_damage_flash[4];

void Fade_Init(void);
void Fade_UpdateAndDraw(struct GfxFrameData *arg0);
void Fade_Start(s32 arg0, u16 arg1, ColorRGBA8 *arg2);

#endif
