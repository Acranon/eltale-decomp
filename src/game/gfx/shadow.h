#ifndef GAME_GFX_SHADOW_H
#define GAME_GFX_SHADOW_H

#include "common.h"

struct GfxFrameData;

/* One queued shadow: a floor-aligned quad at x, y, z, its up vector r and its scale. */
typedef struct ShadowEntry {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ f32 scale;
} ShadowEntry; /* 0x1C bytes */

/* .bss 80084B80..80085290 */
extern ShadowEntry shadow_queue[0x40];
extern s32 shadow_count;

void Shadow_Queue(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale);
void Shadow_DrawAll(struct GfxFrameData *arg0);

#endif
