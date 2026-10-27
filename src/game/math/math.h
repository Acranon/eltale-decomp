#ifndef GAME_MATH_MATH_H
#define GAME_MATH_MATH_H

#include "common.h"

/* Shared vector and matrix types (D3_TYPES.md). A ground-plane Vec2f holds the world x in .x
 * and the world z in .y. */
typedef struct Vec2f {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f; /* 0x8 bytes */

typedef struct Vec3f {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f; /* 0xC bytes */

typedef struct MtxF {
    /* 0x00 */ f32 mf[4][4];
} MtxF; /* 0x40 bytes */

extern u8 math_bit_masks[8];
extern u32 math_rand_seed;
extern MtxF math_scratch_mtxf;

u32 Math_Rand(u32 max);
f32 Math_Atan(f32 x);
void Math_NormalizeVec2(f32* arg0, f32* arg1);
f32 Math_Atan2(f32 arg0, f32 arg1);
void Math_RotateVec2(f32 angle, Vec2f* coords);
void Math_MtxFRotScaleTrans(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void Math_MtxRotScaleTrans(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void Math_MtxFRotate(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3);
void Math_MtxRotate(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3);
void Math_MtxFAimAt(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void Math_MtxAimAt(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void Math_MtxFMulVecTransposed(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6);
void Math_MtxFMulVecNegZ(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6);
void Math_MtxFAlignYToVector(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3);
void Math_MtxAlignYToVector(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3);
void Math_MtxFRotDegScaleTrans(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                               f32 arg9);
void Math_MtxFScaleAxes(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3);
void Math_MtxFMul(MtxF* arg0, MtxF* arg1, MtxF* arg2);
s32 Camera_WorldToScreen(f32 arg0, f32 arg1, f32 arg2, s32* arg3, s32* arg4);

#endif
