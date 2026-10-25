#include "common.h"

typedef struct {
    /* 0x00 */ s32 active : 1;
    /* 0x00 */ u32 flags : 31;
} SpriteFlags;

typedef union {
    SpriteFlags b;
    s32 w;
} SpriteFlagsU;

typedef struct {
    /* 0x00 */ SpriteFlagsU unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 unk4E;
} IntroSprite; /* size = 0x50 */

typedef struct {
    /* 0x00 */ u8 pad0[0x22];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u8 pad24[4];
} Unk28; /* size = 0x28 */

typedef struct {
    /* 0x00 */ Unk28 *unk0;
    /* 0x04 */ u32 unk4;
} Unk802170E8;

extern Unk802170E8 D_802170E8_ovl_intro[];
extern u32 D_802170F0_ovl_intro;
extern s32 D_80212230_ovl_intro;
extern s32 D_80212250_ovl_intro;
extern s32 D_802684B0;
extern s32 D_802684B4;
extern s32 D_802684B8;
extern s32 D_802684BC;
extern s32 D_802684C0;
extern s32 D_802684C4;
extern s32 D_802684C8;
extern s32 D_802684CC;
extern s32 D_802684D0;
extern s32 D_802684D4;
extern s32 D_802684D8;
extern s32 D_802684DC;
extern IntroSprite D_802684E0[150];

void func_8020D1DC_ovl_intro(void);

void func_8020C0D0_ovl_intro(void) {
    func_8020D1DC_ovl_intro();
    D_802684B0 = 10;
    D_802684B4 = 1;
    D_802684B8 = 300;
    D_802684BC = 223;
    D_802684CC = 0;
    D_802684D0 = 0;
    D_802684C0 = 0;
    D_802684C4 = 0;
    D_802684D4 = 0;
    D_802684D8 = 0;
    D_802684DC = 0;
    D_80212230_ovl_intro = 0;
    D_80212250_ovl_intro = 0;
    D_802684C8 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020C16C_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020C6A8_ovl_intro.s")

s32 func_8020D078_ovl_intro(s32 id, u32 *outIdx) {
    u32 i;
    u32 j;

    for (i = 0; i < D_802170F0_ovl_intro; i++) {
        for (j = 0; j < D_802170E8_ovl_intro[i].unk4; j++) {
            if (id == D_802170E8_ovl_intro[i].unk0[j].unk22) {
                *outIdx = i;
                return j;
            }
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D0F4_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D1DC_ovl_intro.s")

void func_8020D300_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0[idx];

    p->unk0.w = 0;
    p->unk4 = 0;
    p->unk6 = 0;
    p->unkC = 0;
    p->unkE = 0;
    p->unk8 = 0;
    p->unkA = 0;
    p->unk10 = 0;
    p->unk12 = 0;
    p->unk14 = 0;
    p->unk18 = 0;
    p->unk48 = 0.0f;
    p->unk4E = 0xFF;
    p->unk32 = 0;
    p->unk1C = 0.0f;
    p->unk20 = 0.0f;
    p->unk24 = 0;
    p->unk2A = 0;
    p->unk2C = 0;
    p->unk26 = 0;
    p->unk28 = 0;
    p->unk34 = 0;
    p->unk40 = 0.0f;
    p->unk44 = 1.0f;
    p->unk4C = 0;
    p->unk38 = 0;
    p->unk3C = 0;
    p->unk2E = p->unk30 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D3A4_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D454_ovl_intro.s")

s16 func_8020D504_ovl_intro(void) {
    s32 i;
    IntroSprite *p = D_802684E0;

    for (i = 0; i < 150; i++, p++) {
        if (!(p->unk0.w & 0x80000000)) {
            return i;
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D5EC_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D750_ovl_intro.s")

void func_8020D8AC_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0[idx];

    p->unk2E = p->unk4 + p->unk8;
    p->unk30 = p->unk6 + p->unkA;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D8E8_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020D9EC_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020DAF0_ovl_intro.s")

void func_8020DD6C_ovl_intro(s32 idx, s32 arg1, s32 arg2) {
    IntroSprite *p = &D_802684E0[idx];

    p->unk2A = arg1;
    p->unk2C = arg2;
    p->unk26 = p->unk4;
    p->unk28 = p->unk6;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020DDA0_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020DF20_ovl_intro.s")

s32 func_8020E0A0_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0[idx];

    p->unk34++;
    if (p->unk34 >= p->unk38) {
        return 0xFF;
    }
    return 0;
}

void func_8020E0EC_ovl_intro(s32 idx) {
    D_802684E0[idx].unk34 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020E108_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/D_80268490_ovl_intro.s")
