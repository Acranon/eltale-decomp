#include "common.h"

#define PI 3.141592653589793
#define SQ(x) ((x) * (x))

typedef struct {
    f32 mf[4][4];
} MtxF;

typedef struct {
    f32 x;
    f32 y;
} Vec2f;

extern u32 D_8004F778;
extern f32 D_8004F77C;
extern MtxF D_8008CE60;

extern MtxF D_80085F10;
extern f32 D_80085F54;
extern f32 D_80085F5C;

f32 func_80026EE8(f32 x);
void func_80027220(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void func_80027430(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3);
void func_800275DC(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_800278C8(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3);

u32 func_80026E90(u32 max) {
    if (max != 0) {
        return ((D_8004F778 = (D_8004F778 * 0x41C64E6D) + 0x3039) >> 0x10) % max;
    }
    return 0;
}

f32 func_80026EE8(f32 x) {
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

void func_80027070(f32* arg0, f32* arg1) {
    f32 temp_f2_2;

    temp_f2_2 = 1.0f / sqrtf((*arg0 * *arg0) + (*arg1 * *arg1));
    *arg0 *= temp_f2_2;
    *arg1 *= temp_f2_2;
}

f32 func_800270D0(f32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 == 0.0f) {
        var_f2 = arg0 >= 0.0f ? (PI / 2) : -(PI / 2);
    } else if (arg1 > 0.0f) {
        var_f2 = func_80026EE8(arg0 / arg1);
    } else if ((arg1 < 0.0f) && (arg0 <= 0.0f)) {
        var_f2 = func_80026EE8(arg0 / arg1) - PI;
    } else {
        var_f2 = func_80026EE8(arg0 / arg1) + PI;
    }
    return var_f2;
}

void func_800271B4(f32 angle, Vec2f* coords) {
    f32 sinAngle;
    f32 cosAngle;
    f32 x;

    sinAngle = sinf(angle);
    cosAngle = cosf(angle);
    x = coords->x;
    coords->x = (coords->y * sinAngle) - (x * cosAngle);
    coords->y = (coords->y * cosAngle) + (x * sinAngle);
}

void func_80027220(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
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

void func_800273C0(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    func_80027220(&D_8008CE60, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(D_8008CE60.mf, arg0);
}

void func_80027430(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
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

void func_8002758C(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_80027430(&D_8008CE60, arg1, arg2, arg3);
    guMtxF2L(D_8008CE60.mf, arg0);
}

void func_800275DC(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
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

void func_8002773C(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    func_800275DC(&D_8008CE60, arg1, arg2, arg3, arg4, arg5, arg6);
    guMtxF2L(D_8008CE60.mf, arg0);
}

void func_800277A4(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6) {
    *arg4 = arg0->mf[0][0] * arg1 + arg0->mf[0][1] * arg2 + arg0->mf[0][2] * arg3;
    *arg5 = arg0->mf[1][0] * arg1 + arg0->mf[1][1] * arg2 + arg0->mf[1][2] * arg3;
    *arg6 = arg0->mf[2][0] * arg1 + arg0->mf[2][1] * arg2 + arg0->mf[2][2] * arg3;
}

void func_80027834(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6) {
    *arg4 = arg0->mf[0][0] * arg1 + arg0->mf[1][0] * arg2 + arg0->mf[2][0] * arg3;
    *arg5 = arg0->mf[0][1] * arg1 + arg0->mf[1][1] * arg2 + arg0->mf[2][1] * arg3;
    *arg6 = -(arg0->mf[0][2] * arg1 + arg0->mf[1][2] * arg2 + arg0->mf[2][2] * arg3);
}

void func_800278C8(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
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

void func_80027A8C(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_800278C8(&D_8008CE60, arg1, arg2, arg3);
    guMtxF2L(D_8008CE60.mf, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/27A90/func_80027ADC.s")

void func_80027CB4(MtxF* arg0, f32 arg1, f32 arg2, f32 arg3) {
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

void func_80027D40(MtxF* arg0, MtxF* arg1, MtxF* arg2) {
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

s32 func_80027FFC(f32 arg0, f32 arg1, f32 arg2, s32* arg3, s32* arg4) {
    s32 ret;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    guMtxXFMF(D_80085F10.mf, arg0, arg1, arg2, &x, &y, &z);
    ret = z < -D_80085F54;
    if (ret) {
        w = z * D_80085F5C;
        *arg3 = 160 - (s32) (((x * 160.0) / w) * 0.75);
        *arg4 = (s32) ((120.0f * y) / w) + 120;
    }
    return z < -D_80085F54;
}
