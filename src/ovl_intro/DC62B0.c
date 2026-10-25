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
    /* 0x32 */ u16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C;
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

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} IntroRect;

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

s32 func_8020D8E8_ovl_intro(s32 idx, s32 arg1) {
    IntroSprite *p = &D_802684E0[idx];
    f32 step;

    if (!(p->unk0.w & 0x80000000)) {
        return 0;
    }
    p->unk32++;
    step = 255.0f / p->unk38;
    p->unk48 += step;
    if (p->unk48 >= 255.0f || p->unk32 >= p->unk38) {
        p->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        p->unk4E = p->unk48;
    } else {
        p->unk4E = 255.0f - p->unk48;
    }
    if (p->unk32 >= p->unk38) {
        p->unk32 = 0;
        p->unk48 = 0.0f;
        if (arg1 == 0) {
            p->unk4E = 0xFF;
        } else {
            p->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020D9EC_ovl_intro(s32 idx, s32 arg1) {
    IntroSprite *p = &D_802684E0[idx];
    f32 step;

    if (!(p->unk0.w & 0x80000000)) {
        return 0;
    }
    p->unk32++;
    step = 255.0f / p->unk38;
    p->unk48 += step;
    if (p->unk48 >= 255.0f || p->unk32 >= p->unk38) {
        p->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        p->unk4E = p->unk48;
    } else {
        p->unk4E = 255.0f - p->unk48;
    }
    if (p->unk32 >= p->unk38) {
        p->unk32 = 0;
        p->unk48 = 0.0f;
        if (arg1 == 0) {
            p->unk4E = 0xFF;
        } else {
            p->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020DAF0_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0[idx];
    f32 step;
    s32 tx;
    s32 ty;
    s32 dx;
    s32 dy;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0;
    }
    p->unk24++;
    step = ((f32) p->unk2A - (f32) p->unk26) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk1C += step;
    dir = 2;
    tx = p->unk1C;
    step = ((f32) p->unk2C - (f32) p->unk28) / p->unk38;
    dx = tx;
    if (step < 0) {
        step = -step;
    }
    p->unk20 += step;
    ty = p->unk20;
    dy = ty;
    if (p->unk4 < p->unk2A) {
        dir = 1;
    } else {
        dx = -tx;
    }
    if (p->unk6 < p->unk2C) {
        dir |= 4;
    } else {
        dy = -ty;
        dir |= 8;
    }
    p->unk4 += dx;
    p->unk6 += dy;
    if (p->unk1C >= 1.0f) {
        p->unk1C -= tx;
    }
    if (p->unk20 >= 1.0f) {
        p->unk20 -= ty;
    }
    if (p->unk24 >= p->unk38) {
        p->unk4 = p->unk2A;
        p->unk6 = p->unk2C;
    }
    if (dir & 1) {
        if (p->unk4 >= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    } else if (dir & 2) {
        if (p->unk4 <= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    }
    if (dir & 4) {
        if (p->unk6 >= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    } else if (dir & 8) {
        if (p->unk6 <= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

void func_8020DD6C_ovl_intro(s32 idx, s32 arg1, s32 arg2) {
    IntroSprite *p = &D_802684E0[idx];

    p->unk2A = arg1;
    p->unk2C = arg2;
    p->unk26 = p->unk4;
    p->unk28 = p->unk6;
}

s32 func_8020DDA0_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->unk24++;
    step = ((f32) p->unk2A - (f32) p->unk26) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk1C += step;
    dir = 2;
    t = p->unk1C;
    d = t;
    if (p->unk4 < p->unk2A) {
        dir = 1;
    } else {
        dir = 2;
        d = -t;
    }
    p->unk4 += d;
    if (p->unk1C >= 1.0f) {
        p->unk1C -= t;
    }
    if (p->unk24 >= p->unk38) {
        p->unk4 = p->unk2A;
    }
    if (dir & 1) {
        if (p->unk4 >= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    } else if (dir & 2) {
        if (p->unk4 <= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 func_8020DF20_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->unk24++;
    step = ((f32) p->unk2C - (f32) p->unk28) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk20 += step;
    dir = 8;
    t = p->unk20;
    d = t;
    if (p->unk6 < p->unk2C) {
        dir = 4;
    } else {
        dir = 8;
        d = -t;
    }
    p->unk6 += d;
    if (p->unk20 >= 1.0f) {
        p->unk20 -= t;
    }
    if (p->unk24 >= p->unk38) {
        p->unk6 = p->unk2C;
    }
    if (dir & 4) {
        if (p->unk6 >= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    } else if (dir & 8) {
        if (p->unk6 <= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

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
