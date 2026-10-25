#include "common.h"

typedef struct {
    f32 mf[4][4];
} MtxF;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ char unk18[0x24 - 0x18];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x38 - 0x28];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
} Struct_800201A0;

typedef struct {
    s16 unk0;
    s16 unk2;
    void* unk4;
    void* unk8;
} Struct_8002099C;

typedef struct {
    void* unk0;
    u16 unk4;
    u16 unk6;
    Vec3f unk8;
    s8 unk14;
    s8 unk15;
    u8 unk16;
    char unk17;
    s32 unk18;
    char unk1C[4];
} Struct_80020A28;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x32 - 0xC];
    /* 0x32 */ u16 unk32;
} Struct_80020214_kf;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ Struct_80020A28* unk4;
} Struct_80020214_set;

extern s32 D_8008BFF0;

void func_80026A00(Struct_80020A28*, Vec3f*, s32);
void func_80027220(MtxF*, f32, f32, f32, f32, f32, f32, f32);
void func_80020568(MtxF*, Vec3f, s32, s32, s32, s32, Struct_80020214_set*, Struct_80020A28*, s32);

void func_800201A0(Struct_800201A0* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    if (arg1 != -1) {
        if (arg1 != arg0->unk52) {
            arg0->unk52 = arg1;
            arg0->unk60 = arg0->unk60 | 0x400;
            arg0->unk60 = arg0->unk60 & 0xFDFF;
        }

        arg0->unk58 = arg2;
        if (arg5 & 1) {
            arg0->unk54 = arg0->unk56 = 0;
        }
    }

    if (arg3 != -1) {
        if (arg3 != arg0->unk5A) {
            arg0->unk5A = arg3;
        }
        arg0->unk5C = arg4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/20DA0/func_80020214.s")

void func_80020428(s32 arg0, Struct_800201A0* arg1, Struct_80020214_set* arg2, s32 arg3) {
    s32 i;
    u16 frame;
    Struct_80020A28* anims;
    u16 total;
    MtxF mtx;
    Vec3f scale;

    D_8008BFF0 = 0;
    func_80027220(&mtx, arg1->unkC.x, arg1->unkC.y, arg1->unkC.z, arg1->unk24, arg1->unk0.x, arg1->unk0.y, arg1->unk0.z);
    scale.x = arg1->unk24;
    scale.y = arg1->unk24;
    scale.z = arg1->unk24;
    anims = arg2->unk4;
    frame = arg1->unk54;
    total = arg1->unk56;
    for (i = 0; i < arg2->unk0; i++) {
        if (anims[i].unk14 == 0) {
            func_80020568(&mtx, scale, arg0, i, frame, total, arg2, anims, arg3);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/20DA0/func_80020568.s")

void func_8002099C(s32 arg0, Struct_800201A0* arg1, Struct_8002099C* arg2) {
    s32 temp_v0 = arg1->unk54 += arg0;

    if (temp_v0 >= arg2->unk2) {
        if (arg1->unk52 != arg1->unk5A) {
            arg1->unk52 = arg1->unk5A;
            arg1->unk54 = 0U;
            arg1->unk56 = 0U;
            arg1->unk58 = arg1->unk5C;
            arg1->unk60 |= 0x400;
        } else {
            arg1->unk54 = temp_v0 - arg2->unk2;
            arg1->unk60 |= 0x200;
        }
    } else {
        arg1->unk60 &= ~0x600;
    }
    arg1->unk56++;
}

void func_80020A28(MtxF* arg0, Struct_80020A28* arg1) {
    f32 x, y, z;
    x = arg0->mf[0][0];
    y = arg0->mf[1][0];
    z = arg0->mf[2][0];
    arg0->mf[3][0] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
    x = arg0->mf[0][1];
    y = arg0->mf[1][1];
    z = arg0->mf[2][1];
    arg0->mf[3][1] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
    x = arg0->mf[0][2];
    y = arg0->mf[1][2];
    z = arg0->mf[2][2];
    arg0->mf[3][2] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
}
