#include "common.h"

typedef struct {
    f32 mf[4][4];
} MtxF;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x00 */ char unk0[0x50];
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

#pragma GLOBAL_ASM("asm/nonmatchings/20DA0/func_80020428.s")

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
