#include "common.h"

typedef struct {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
    /* 0x010 */ u8 unk10;
    /* 0x012 */ s16 unk12;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17[32];
    /* 0x038 */ s16 unk38;
    /* 0x03A */ s16 unk3A;
    /* 0x03C */ u8 unk3C[4][24];
    /* 0x09C */ u8 unk9C[0x4B0];
    /* 0x54C */ u8 unk54C[0x4B0];
} Unk80090470; /* size = 0x9FC */

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} Unk800616A8;

extern Gfx *D_8007A184;
extern Unk800616A8 D_800616A8;
extern Unk80090470 D_80090470[4];
extern u8 D_80092C60;
extern u16 D_80092C62;
extern s8 D_80092C81;
extern s8 D_80092C82;

void func_80032BF8(s32 arg0, u8 arg1);
void func_80034C9C(s32, s32, s32, s32, s32);
void func_80035350(s32, s32, u8 *);

void func_80032BB0(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80032BF8(i, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80032BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80032D20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80033050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_8003403C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80034274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80034380.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_8003453C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_800348B8.s")

void func_80034B30(s32 arg0) {
    s32 max = 0;
    s32 n = D_80090470[arg0].unk38;
    s32 i;
    s32 j;
    s32 cnt;

    D_800616A8.unk6 = n * 13 + 12;
    for (i = 0; i < n; i++) {
        j = 0;
        cnt = 0;
        while (D_80090470[arg0].unk3C[i][j] != 0xFF) {
            if (D_80090470[arg0].unk3C[i][j] < 0x80) {
                cnt++;
            }
            j++;
        }
        if (max < cnt) {
            max = cnt;
        }
    }
    D_800616A8.unk4 = max * 10 + 24;
}

s32 func_80034C18(s32 arg0, s32 arg1) {
    s32 ret = -1;
    s32 i;

    if (arg0 >= 0) {
        for (i = 0; i < 4; i++) {
            if (arg0 == D_80090470[i].unkE) {
                ret = i;
                break;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (arg1 == (D_80090470[i].unk0 & 7)) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80034C9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_8003509C.s")

void func_8003521C(void) {
    D_80092C62 = 0;
}

s32 func_8003522C(void) {
    s32 ret = 0;
    u32 sum;

    if (D_80092C60 != 0) {
        sum = D_80092C81 * D_80092C81 + D_80092C82 * D_80092C82;
        if (sum > 60 * 60) {
            D_80092C62++;
            if (D_80092C62 >= 5) {
                ret = 1;
            }
        } else {
            D_80092C62 = 0;
        }
    }
    return ret;
}
