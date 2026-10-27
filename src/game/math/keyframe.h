#ifndef GAME_MATH_KEYFRAME_H
#define GAME_MATH_KEYFRAME_H

#include "common.h"

/* One key of a 9-channel track: TCB spline parameters, or a linear segment into this key. */
typedef struct Keyframe {
    /* 0x00 */ f32 v[9];
    /* 0x24 */ f32 tension;
    /* 0x28 */ f32 continuity;
    /* 0x2C */ f32 bias;
    /* 0x30 */ u16 linear;
    /* 0x32 */ u16 frame;
} Keyframe; /* 0x34 bytes */

typedef struct KfAnim {
    /* 0x00 */ Keyframe* kfs;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 last;
} KfAnim; /* 0x8 bytes */

void Math_EvalTcbSpline(KfAnim* anim, f32* out, s32 frame);
void Math_HermiteBasis(f32 t, f32* a, f32* b, f32* c, f32* d);

#endif
