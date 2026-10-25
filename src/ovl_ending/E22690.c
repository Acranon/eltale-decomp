#include "common.h"

extern Gfx* D_8007A184;
extern s32 D_8020F698_ovl_ending;
extern Gfx D_8020F6C0_ovl_ending[];
extern Gfx D_8022EA18[2][2500];
extern Gfx* D_80238658;

void func_8020C254_ovl_ending(void);

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u16 unk32;
    s16 unk34;
    char unk36[2];
    s32 unk38;
    s32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s16 unk4C;
    s16 unk4E;
} UnkStruct_8022BB38;

typedef struct {
    char unk0[0x22];
    s16 unk22;
    char unk24[4];
} UnkStruct_802107F0_inner;

typedef struct {
    UnkStruct_802107F0_inner* unk0;
    u32 unk4;
} UnkStruct_802107F0;

extern UnkStruct_8022BB38 D_8022BB38[];
extern UnkStruct_802107F0 D_802107F0_ovl_ending[];
extern u32 D_802107F8_ovl_ending;
extern s32 D_8020F690_ovl_ending;
extern s32 D_8020F694_ovl_ending;
extern s32 D_8022BB10;
extern s32 D_8022BB14;
extern s32 D_8022BB18;
extern s32 D_8022BB1C;
extern s32 D_8022BB20;
extern s32 D_8022BB24;
extern s32 D_8022BB28;
extern s32 D_8022BB2C;
extern s32 D_8022BB30;
extern s32 D_8022BB34;

void func_8020CA60_ovl_ending(void);

void func_8020C0D0_ovl_ending(void) {
    func_8020CA60_ovl_ending();
    D_8022BB10 = 0xA;
    D_8022BB14 = 1;
    D_8022BB18 = 0x12C;
    D_8022BB1C = 0xDF;
    D_8022BB2C = 0;
    D_8022BB30 = 0;
    D_8022BB20 = 0;
    D_8022BB24 = 0;
    D_8022BB34 = 0;
    D_8020F690_ovl_ending = 0;
    D_8020F694_ovl_ending = 0;
    D_8022BB28 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020C15C_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020C254_ovl_ending.s")

s32 func_8020C8FC_ovl_ending(s32 arg0, u32* arg1) {
    u32 i, j;

    for (i = 0; i < D_802107F8_ovl_ending; i++) {
        for (j = 0; j < D_802107F0_ovl_ending[i].unk4; j++) {
            if (arg0 == D_802107F0_ovl_ending[i].unk0[j].unk22) {
                *arg1 = i;
                return j;
            }
        }
    }

    return -1;
}

void func_8020C978_ovl_ending(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38[arg0];
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk6 = arg3;
    temp_v0->unkC = arg4;
    temp_v0->unkE = arg5;
    temp_v0->unk8 = arg6;
    temp_v0->unkA = arg7;
    if ((arg1 & 0x04000000) == 0x04000000) {
        temp_v0->unk10 = (arg8 + 0xF) & 0xFFF0;
    } else {
        temp_v0->unk10 = arg8;
    }
    temp_v0->unk12 = arg9;
    temp_v0->unk14 = argB;
    temp_v0->unk18 = argA;
    temp_v0->unk4C = 0;
    temp_v0->unk4E = 0xFF;
    temp_v0->unk32 = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk34 = 0;
    temp_v0->unk40 = 0.0f;
    temp_v0->unk44 = 0.0f;
    temp_v0->unk48 = 0.0f;
    temp_v0->unk1C = 0.0f;
    temp_v0->unk20 = 0.0f;
    temp_v0->unk38 = argC;
    temp_v0->unk3C = argD;
    temp_v0->unk2E = temp_v0->unk30 = 0;
}

void func_8020CA60_ovl_ending(void) {
    s32 i;
    UnkStruct_8022BB38* temp_v0 = D_8022BB38;

    for (i = 0; i < 150; i++, temp_v0++) {
        temp_v0->unk0 = 0;
        temp_v0->unk4 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unkC = 0;
        temp_v0->unkE = 0;
        temp_v0->unk8 = 0;
        temp_v0->unkA = 0;
        temp_v0->unk10 = 0;
        temp_v0->unk12 = 0;
        temp_v0->unk14 = 0;
        temp_v0->unk18 = 0;
        temp_v0->unk48 = 0.0f;
        temp_v0->unk4E = 0xFF;
        temp_v0->unk32 = 0;
        temp_v0->unk1C = 0.0f;
        temp_v0->unk20 = 0.0f;
        temp_v0->unk24 = 0;
        temp_v0->unk2A = 0;
        temp_v0->unk2C = 0;
        temp_v0->unk26 = 0;
        temp_v0->unk28 = 0;
        temp_v0->unk34 = 0;
        temp_v0->unk40 = 0.0f;
        temp_v0->unk44 = 1.0f;
        temp_v0->unk4C = 0;
        temp_v0->unk38 = 0;
        temp_v0->unk3C = 0;
        temp_v0->unk2E = temp_v0->unk30 = 0;
    }
}

void func_8020CB84_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38[arg0];
    temp_v0->unk0 = 0;
    temp_v0->unk4 = 0;
    temp_v0->unk6 = 0;
    temp_v0->unkC = 0;
    temp_v0->unkE = 0;
    temp_v0->unk8 = 0;
    temp_v0->unkA = 0;
    temp_v0->unk10 = 0;
    temp_v0->unk12 = 0;
    temp_v0->unk14 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk4E = 0xFF;
    temp_v0->unk32 = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk2A = 0;
    temp_v0->unk2C = 0;
    temp_v0->unk26 = 0;
    temp_v0->unk28 = 0;
    temp_v0->unk34 = 0;
    temp_v0->unk4C = 0;
    temp_v0->unk38 = 0;
    temp_v0->unk3C = 0;
    temp_v0->unk48 = 0.0f;
    temp_v0->unk1C = 0.0f;
    temp_v0->unk20 = 0.0f;
    temp_v0->unk40 = 0.0f;
    temp_v0->unk44 = 1.0f;
    temp_v0->unk2E = temp_v0->unk30 = 0;
}

s32 func_8020CC28_ovl_ending(void) {
    s32 count;
    UnkStruct_8022BB38* ptr = D_8022BB38;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if ((ptr->unk0 & 0x80000000) == 0) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

s32 func_8020CCD8_ovl_ending(void) {
    s32 count;
    UnkStruct_8022BB38* ptr = D_8022BB38;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if (ptr->unk0 & 0x80000000) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020CD88_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020CE70_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020CFD4_ovl_ending.s")

void func_8020D130_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38[arg0];
    temp_v0->unk2E = temp_v0->unk4 + temp_v0->unk8;
    temp_v0->unk30 = temp_v0->unk6 + temp_v0->unkA;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D16C_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D270_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D374_ovl_ending.s")

void func_8020D5F0_ovl_ending(s32 arg0, s32 arg1, s32 arg2) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38[arg0];
    temp_v0->unk2A = (s16) arg1;
    temp_v0->unk2C = (s16) arg2;
    temp_v0->unk26 = temp_v0->unk4;
    temp_v0->unk28 = temp_v0->unk6;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D624_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D7A4_ovl_ending.s")

s32 func_8020D924_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38[arg0];
    temp_v0->unk34 += 1;
    if (temp_v0->unk34 >= temp_v0->unk38) {
        return 0xFF;
    }
    return 0;
}

void func_8020D970_ovl_ending(s32 arg0) {
    D_8022BB38[arg0].unk34 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D98C_ovl_ending.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020E9C8_ovl_ending.s")
