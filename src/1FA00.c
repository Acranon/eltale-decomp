#include "common.h"

typedef struct {
    char unk0[8];
} Struct_8007C284_30;

typedef struct {
    char unk0[0x10];
} Struct_8007C284_34;

typedef struct {
    char unk0[0x30];
    Struct_8007C284_30* unk30;
    Struct_8007C284_34* unk34;
} Struct_8007C284;

extern Struct_8007C284* D_8007C284;
extern s32 D_800842C0;
extern u16 D_800842E8;
extern u16 D_8008BE52;
extern s32 D_8008BF98;
extern s32 D_8008BF9C;
extern f32 D_8008BFAC;
extern s16 D_8008BFB0;

void func_8001EE00(void) {
    D_8008BE52 &= 0x8000;
    D_8008BFAC = 0.0f;
    D_8008BFB0 = 0;
    if (D_800842E8 & 1) {
        if (D_8007C284->unk30 != NULL) {
            D_8008BF98 = (s32) &D_8007C284->unk30[D_800842C0];
            D_8008BF9C = (s32) &D_8007C284->unk34[D_800842C0];
            return;
        }
        D_8008BF98 = 0;
        D_8008BF9C = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001EE94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F36C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FC14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FD44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FE08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FF10.s")

void func_800200F0(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_800200F8.s")
