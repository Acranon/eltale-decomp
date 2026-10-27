#include "game/math/math.h"

/*
 * Math: the random number generator, arctangent, 2D vector helpers, float matrix builders
 * (rotate/scale/translate, aim, align) with Mtx wrappers, and world-to-screen projection.
 * Original file: 27A90.c (ROM 0x27A90).
 */

#define PI 3.141592653589793
#define SQ(x) ((x) * (x))

/* This file's .data, 8004F770..8004F780: a bit table (used by other files),
 * the random seed, and Math_MtxFRotDegScaleTrans's static degrees-to-radians factor
 * (8004F77C), which must be a function-scope static for IDO to match. */
u8 math_bit_masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
u32 math_rand_seed = 0x9B0;
MtxF math_scratch_mtxf; /* .bss 8008CE60..8008CEA0 */

extern MtxF camera_view_mtx;
extern f32 camera_near;
extern f32 camera_tan_half_fovy;

u32 Math_Rand(u32 max) {
    if (max != 0) {
        return ((math_rand_seed = (math_rand_seed * 0x41C64E6D) + 0x3039) >> 0x10) % max;
    }
    return 0;
}

f32 Math_Atan(f32 x) {
    f32 conv = 0.0f;
    s32 sector;
    s32 i;

    if (x > 1.0f) {
        sector = 1;
        x = 1.0f / x;
    } else if (x < -1.0f) {
        sector = -1;
        x = 1.0f / x;
    } else {
        sector = 0;
    }

    for (i = 12; i > 0; i--) {
        conv = ((SQ(i) * x * x) / (i * 2 + 1 + conv));
    }

    if (sector > 0) {
        return PI / 2 - (x / (1.0f + conv));
    } else if (sector < 0) {
        return -PI / 2 - (x / (1.0f + conv));
    } else {
        return x / (1.0f + conv);
    }
}

void Math_NormalizeVec2(f32* arg0, f32* arg1) {
    f32 temp_f2_2;

    temp_f2_2 = 1.0f / sqrtf((*arg0 * *arg0) + (*arg1 * *arg1));
    *arg0 *= temp_f2_2;
    *arg1 *= temp_f2_2;
}

f32 Math_Atan2(f32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 == 0.0f) {
        var_f2 = arg0 >= 0.0f ? (PI / 2) : -(PI / 2);
    } else if (arg1 > 0.0f) {
        var_f2 = Math_Atan(arg0 / arg1);
    } else if ((arg1 < 0.0f) && (arg0 <= 0.0f)) {
        var_f2 = Math_Atan(arg0 / arg1) - PI;
    } else {
        var_f2 = Math_Atan(arg0 / arg1) + PI;
    }
    return var_f2;
}

void Math_RotateVec2(f32 angle, Vec2f* coords) {
    f32 sinAngle;
    f32 cosAngle;
    f32 x;

    sinAngle = sinf(angle);
    cosAngle = cosf(angle);
    x = coords->x;
    coords->x = (coords->y * sinAngle) - (x * cosAngle);
    coords->y = (coords->y * cosAngle) + (x * sinAngle);
}

void Math_MtxFRotScaleTrans(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_f20;
    f32 sp3C;
    f32 temp_f0;

    sp4C = sinf(arg1);
    temp_f20 = cosf(arg1);
    sp48 = sinf(arg2);
    sp3C = cosf(arg2);
    sp44 = sinf(arg3);
    temp_f0 = cosf(arg3);
    arg0->mf[0][0] = (f32) (((temp_f0 * sp3C) + ((sp44 * sp4C) * sp48)) * arg4);
    arg0->mf[0][1] = (f32) ((sp44 * temp_f20) * arg4);
    arg0->mf[0][2] = (f32) ((((-sp48) * temp_f0) + ((sp44 * sp4C) * sp3C)) * arg4);
    arg0->mf[0][3] = 0.0f;
    arg0->mf[1][0] = (f32) ((((-sp44) * sp3C) + ((temp_f0 * sp4C) * sp48)) * arg4);
    arg0->mf[1][1] = (f32) ((temp_f0 * temp_f20) * arg4);
    arg0->mf[1][2] = (f32) ((((-sp44) * (-sp48)) + ((temp_f0 * sp4C) * sp3C)) * arg4);
    arg0->mf[1][3] = 0.0f;
    arg0->mf[2][0] = (f32) ((temp_f20 * sp48) * arg4);
    arg0->mf[2][1] = (f32) ((-sp4C) * arg4);
    arg0->mf[2][2] = (f32) ((temp_f20 * sp3C) * arg4);
    arg0->mf[2][3] = 0.0f;
    arg0->mf[3][0] = arg5;
    arg0->mf[3][1] = arg6;
    arg0->mf[3][2] = arg7;
    arg0->mf[3][3] = 1.0f;
}

void Math_MtxRotScaleTrans(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Math_MtxFRotScaleTrans(&math_scratch_mtxf, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(math_scratch_mtxf.mf, arg0);
}

void Math_MtxFRotate(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sin1;
    f32 sin2;
    f32 sin3;
    f32 cos1;
    f32 cos2;
    f32 cos3;

    sin1 = sinf(arg1);
    cos1 = cosf(arg1);
    sin2 = sinf(arg2);
    cos2 = cosf(arg2);
    sin3 = sinf(arg3);
    cos3 = cosf(arg3);

    arg0->mf[0][0] = (cos3 * cos2) + (sin3 * sin1 * sin2);
    arg0->mf[0][1] = sin3 * cos1;
    arg0->mf[0][2] = (-sin2 * cos3) + (sin3 * sin1 * cos2);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = (-sin3 * cos2) + (cos3 * sin1 * sin2);
    arg0->mf[1][1] = cos3 * cos1;
    arg0->mf[1][2] = (-sin3 * -sin2) + (cos3 * sin1 * cos2);
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = cos1 * sin2;
    arg0->mf[2][1] = -sin1;
    arg0->mf[2][2] = cos1 * cos2;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = 0.0f;
    arg0->mf[3][1] = 0.0f;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

void Math_MtxRotate(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3) {
    Math_MtxFRotate(&math_scratch_mtxf, arg1, arg2, arg3);
    guMtxF2L(math_scratch_mtxf.mf, arg0);
}

void Math_MtxFAimAt(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_f0_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f18;
    f32 var_f20;
    f32 var_f2;

    temp_f2 = arg4 - arg1;
    temp_f16 = arg6 - arg3;
    temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16));
    if (temp_f0 == 0.0f) {
        var_f18 = 0.0f;
        var_f20 = 1.0f;
    } else {
        var_f18 = temp_f2 / temp_f0;
        var_f20 = temp_f16 / temp_f0;
    }

    temp_f16_2 = arg5 - arg2;
    temp_f0_2 = sqrtf((temp_f0 * temp_f0) + (temp_f16_2 * temp_f16_2));

    if (temp_f0_2 == 0.0f) {
        var_f2 = 0.0f;
        var_f12 = 1.0f;
    } else {
        var_f2 = (-temp_f16_2) / temp_f0_2;
        var_f12 = temp_f0 / temp_f0_2;
    }

    arg0->mf[0][0] = var_f20;
    arg0->mf[0][1] = 0.0f;
    arg0->mf[0][2] = -var_f18;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = var_f2 * var_f18;
    arg0->mf[1][1] = var_f12;
    arg0->mf[1][2] = var_f2 * var_f20;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = var_f12 * var_f18;
    arg0->mf[2][1] = -var_f2;
    arg0->mf[2][2] = var_f12 * var_f20;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = arg3;
    arg0->mf[3][3] = 1.0f;
}

void Math_MtxAimAt(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Math_MtxFAimAt(&math_scratch_mtxf, arg1, arg2, arg3, arg4, arg5, arg6);
    guMtxF2L(math_scratch_mtxf.mf, arg0);
}

void Math_MtxFMulVecTransposed(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6) {
    *arg4 = arg0->mf[0][0] * arg1 + arg0->mf[0][1] * arg2 + arg0->mf[0][2] * arg3;
    *arg5 = arg0->mf[1][0] * arg1 + arg0->mf[1][1] * arg2 + arg0->mf[1][2] * arg3;
    *arg6 = arg0->mf[2][0] * arg1 + arg0->mf[2][1] * arg2 + arg0->mf[2][2] * arg3;
}

void Math_MtxFMulVecNegZ(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6) {
    *arg4 = arg0->mf[0][0] * arg1 + arg0->mf[1][0] * arg2 + arg0->mf[2][0] * arg3;
    *arg5 = arg0->mf[0][1] * arg1 + arg0->mf[1][1] * arg2 + arg0->mf[2][1] * arg3;
    *arg6 = -(arg0->mf[0][2] * arg1 + arg0->mf[1][2] * arg2 + arg0->mf[2][2] * arg3);
}

void Math_MtxFAlignYToVector(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sin1;
    f32 sin2;
    f32 sin3;
    f32 cos1;
    f32 cos2;
    f32 cos3;
    f32 d;
    f32 e;

    d = sqrtf(arg1 * arg1 + arg3 * arg3);
    if (d != 0.0f) {
        sin2 = arg1 / d;
        cos2 = arg3 / d;
    } else {
        sin2 = 0.0f;
        cos2 = (arg2 >= 0.0f) ? 1.0 : -1.0;
    }
    e = sqrtf(d * d + arg2 * arg2);
    sin1 = d / e;
    cos1 = arg2 / e;
    sin3 = 0.0;
    cos3 = 1.0;
    arg0->mf[0][0] = (cos3 * cos2) + (sin3 * sin1 * sin2);
    arg0->mf[0][1] = sin3 * cos1;
    arg0->mf[0][2] = (-sin2 * cos3) + (sin3 * sin1 * cos2);
    arg0->mf[0][3] = 0.0;
    arg0->mf[1][0] = (-sin3 * cos2) + (cos3 * sin1 * sin2);
    arg0->mf[1][1] = cos3 * cos1;
    arg0->mf[1][2] = (-sin3 * -sin2) + (cos3 * sin1 * cos2);
    arg0->mf[1][3] = 0.0;
    arg0->mf[2][0] = cos1 * sin2;
    arg0->mf[2][1] = -sin1;
    arg0->mf[2][2] = cos1 * cos2;
    arg0->mf[2][3] = 0.0;
    arg0->mf[3][0] = 0.0;
    arg0->mf[3][1] = 0.0;
    arg0->mf[3][2] = 0.0;
    arg0->mf[3][3] = 1.0;
}

void Math_MtxAlignYToVector(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3) {
    Math_MtxFAlignYToVector(&math_scratch_mtxf, arg1, arg2, arg3);
    guMtxF2L(math_scratch_mtxf.mf, arg0);
}

void Math_MtxFRotDegScaleTrans(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9) {
    f32 sin1;
    f32 sin2;
    f32 sin3;
    f32 cos1;
    f32 cos2;
    f32 cos3;
    static f32 D_8004F77C = 0.017453292f;

    arg4 *= D_8004F77C;
    arg5 *= D_8004F77C;
    arg6 *= D_8004F77C;
    sin1 = sinf(arg4);
    cos1 = cosf(arg4);
    sin2 = sinf(arg5);
    cos2 = cosf(arg5);
    sin3 = sinf(arg6);
    cos3 = cosf(arg6);

    arg0->mf[0][0] = ((cos3 * cos2) + (sin3 * sin1 * sin2)) * arg7;
    arg0->mf[0][1] = sin3 * cos1 * arg7;
    arg0->mf[0][2] = ((-sin2 * cos3) + (sin3 * sin1 * cos2)) * arg7;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-sin3 * cos2) + (cos3 * sin1 * sin2)) * arg8;
    arg0->mf[1][1] = cos3 * cos1 * arg8;
    arg0->mf[1][2] = ((-sin3 * -sin2) + (cos3 * sin1 * cos2)) * arg8;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = cos1 * sin2 * arg9;
    arg0->mf[2][1] = -sin1 * arg9;
    arg0->mf[2][2] = cos1 * cos2 * arg9;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = arg3;
    arg0->mf[3][3] = 1.0f;
}

void Math_MtxFScaleAxes(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->mf[0][0] *= arg1;
    arg0->mf[0][1] *= arg1;
    arg0->mf[0][2] *= arg1;
    arg0->mf[1][0] *= arg2;
    arg0->mf[1][1] *= arg2;
    arg0->mf[1][2] *= arg2;
    arg0->mf[2][0] *= arg3;
    arg0->mf[2][1] *= arg3;
    arg0->mf[2][2] *= arg3;
}

void Math_MtxFMul(MtxF* arg0, MtxF* arg1, MtxF* arg2) {
    f32 temp_f2;
    f32 temp_f20;
    f32 temp_f14;
    f32 temp_f12;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f18;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 temp_f10;
    f32 sp48;
    f32 temp_f6;
    f32 temp_f8;
    f32 sp3C;
    f32 temp_f4;
    f32 sp34;
    f32 sp30;
    f32 temp_f10_2;
    f32 sp28;
    f32 temp_f6_2;
    f32 sp20;

    temp_f0 = arg0->mf[0][0];
    temp_f2 = arg0->mf[0][1];
    temp_f12 = arg0->mf[0][2];

    temp_f14 = arg0->mf[1][0];
    temp_f16 = arg0->mf[1][1];
    temp_f18 = arg0->mf[1][2];

    temp_f20 = arg0->mf[2][0];
    temp_f22 = arg0->mf[2][1];
    temp_f24 = arg0->mf[2][2];

    sp58 = arg0->mf[3][0];
    sp54 = arg0->mf[3][1];
    sp50 = arg0->mf[3][2];

    temp_f10 = arg1->mf[0][0];
    sp48 = arg1->mf[0][1];
    temp_f6 = arg1->mf[0][2];

    temp_f8 = arg1->mf[1][0];
    sp3C = arg1->mf[1][1];
    temp_f4 = arg1->mf[1][2];

    sp34 = arg1->mf[2][0];
    sp30 = arg1->mf[2][1];
    temp_f10_2 = arg1->mf[2][2];

    sp28 = arg1->mf[3][0];
    temp_f6_2 = arg1->mf[3][1];
    sp20 = arg1->mf[3][2];

    arg2->mf[0][0] = ((temp_f0 * temp_f10) + (temp_f14 * sp48)) + (temp_f20 * temp_f6);
    arg2->mf[1][0] = ((temp_f0 * temp_f8) + (temp_f14 * sp3C)) + (temp_f20 * temp_f4);
    arg2->mf[2][0] = ((temp_f0 * sp34) + (temp_f14 * sp30)) + (temp_f20 * temp_f10_2);
    arg2->mf[3][0] = (((temp_f0 * sp28) + (temp_f14 * temp_f6_2)) + (temp_f20 * sp20)) + sp58;

    arg2->mf[0][1] = ((temp_f2 * temp_f10) + (temp_f16 * sp48)) + (temp_f22 * temp_f6);
    arg2->mf[1][1] = ((temp_f2 * temp_f8) + (temp_f16 * sp3C)) + (temp_f22 * temp_f4);
    arg2->mf[2][1] = ((temp_f2 * sp34) + (temp_f16 * sp30)) + (temp_f22 * temp_f10_2);
    arg2->mf[3][1] = (((temp_f2 * sp28) + (temp_f16 * temp_f6_2)) + (temp_f22 * sp20)) + sp54;

    arg2->mf[0][2] = ((temp_f12 * temp_f10) + (temp_f18 * sp48)) + (temp_f24 * temp_f6);
    arg2->mf[1][2] = ((temp_f12 * temp_f8) + (temp_f18 * sp3C)) + (temp_f24 * temp_f4);
    arg2->mf[2][2] = ((temp_f12 * sp34) + (temp_f18 * sp30)) + (temp_f24 * temp_f10_2);
    arg2->mf[3][2] = (((temp_f12 * sp28) + (temp_f18 * temp_f6_2)) + (temp_f24 * sp20)) + sp50;

    arg2->mf[0][3] = 0.0f;
    arg2->mf[1][3] = 0.0f;
    arg2->mf[2][3] = 0.0f;
    arg2->mf[3][3] = 1.0f;
}

s32 Camera_WorldToScreen(f32 arg0, f32 arg1, f32 arg2, s32* arg3, s32* arg4) {
    s32 ret;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    guMtxXFMF(camera_view_mtx.mf, arg0, arg1, arg2, &x, &y, &z);
    ret = z < -camera_near;
    if (ret) {
        w = z * camera_tan_half_fovy;
        *arg3 = 160 - (s32) (((x * 160.0) / w) * 0.75);
        *arg4 = (s32) ((120.0f * y) / w) + 120;
    }
    return z < -camera_near;
}
