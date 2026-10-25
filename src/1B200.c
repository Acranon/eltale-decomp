#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk1B200Pos;

typedef struct {
    /* 0x00 */ s32 timer;
    /* 0x04 */ Unk1B200Pos* pos;
} Unk80086400; // size = 0x8

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Unk8004EE20;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk1B200Vec2;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Unk1B200Particle;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x14];
} Unk80086440; // size = 0x18

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u8 padE[0xE];
} Unk800865DC; // size = 0x1C

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk800866D8; // size = 0x18

extern Gfx* D_8007A184;
extern Unk80086400 D_80086400[];
extern Unk8004EE20 D_8004EE20;
extern Unk1B200Vec2 D_80087E00;
extern f32 D_8004EE60[];
extern u8 D_8004EE90[];
extern s32 D_800863F8;
extern Unk80086440 D_80086440[];
extern Unk80086440 D_80086500[];
extern Unk8004EE20 D_8004EF0C;
extern f32 D_8004EF24[];
extern s32 D_8004EF4C[];
extern f32 D_8004EF58[];
extern u8 D_8004EF88[];
extern s16 D_800865CC;
extern Unk800865DC D_800865DC[];
extern Unk800866D8 D_800866D8[];
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x26];
} Unk80087298; // size = 0x28

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[0x180];
} Unk800877A8; // size = 0x194

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x56];
} Unk80086798; // size = 0x58

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} Unk80087798; // size = 0x4

extern Unk80087298 D_80087298[];
extern Unk800877A8 D_800877A8[];
extern Unk80086798 D_80086798[];
extern Unk80087798 D_80087798[];

void func_8001A6B4(void);
void func_8001A8F4(void);
void func_8001ADE4(void);
void func_8001B3CC(void);
void func_8001BB18(void);
void func_8001C038(void);
void func_8001C7E8(void);
void func_8001D688(void);
void func_8001A728(void);
void func_8001AB44(void);
void func_8001AF90(void);
void func_8001B45C(void);
void func_8001BB48(void*);
void func_8001C2F8(void*);
void func_8001C948(void*);
void func_8001D6A8(void*);
void func_8001D9A8(void*);
void func_800271B4(f32, Unk1B200Vec2*);

void func_8001A600(void) {
    func_8001A6B4();
    func_8001A8F4();
    func_8001B3CC();
    func_8001BB18();
    func_8001D688();
    func_8001ADE4();
    func_8001C7E8();
    func_8001C038();
}

void func_8001A658(void* arg0) {
    func_8001A728();
    func_8001AB44();
    func_8001B45C();
    func_8001BB48(arg0);
    func_8001D6A8(arg0);
    func_8001C2F8(arg0);
    func_8001C948(arg0);
    func_8001AF90();
}

void func_8001A6B4(void) {
    s32 i = 8;
    Unk80086400* p = D_80086400;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void func_8001A6E4(Unk1B200Pos* arg0) {
    s32 i = 7;
    Unk80086400* p = D_80086400;

    while (i != 0 && p->timer != 0) {
        i--;
        p++;
    }
    p->timer = 4;
    p->pos = arg0;
}

void func_8001A728(void) {
    s32 i;
    Unk80086400* p;
    Unk1B200Pos* pos;

    i = 8;
    p = D_80086400;
    do {
        if (p->timer != 0) {
            p->timer--;
            if (p->timer & 1) {
                pos = p->pos;
                D_8004EE20.unk18 = pos->x;
                D_8004EE20.unk1C = pos->y + 1.0f;
                D_8004EE20.unk20 = pos->z;
                D_80087E00.x = 0.0f;
                D_80087E00.y = 0.7f;
                func_800271B4(pos->unk10, &D_80087E00);
                D_8004EE20.unk34 = 0.2f;
                D_8004EE20.unk30 = D_80087E00.x;
                D_8004EE20.unk38 = D_80087E00.y;
                func_8001D9A8(&D_8004EE20);
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void func_8001A828(Unk1B200Particle* arg0) {
    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.8;
    arg0->unk28 = arg0->unk2C = D_8004EE60[arg0->unk0];
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, D_8004EE90[arg0->unk0]);
}

void func_8001A8F4(void) {
    s32 i;
    Unk80086440* a;
    Unk80086440* b;

    D_800863F8 = 0;
    i = 8;
    a = D_80086440;
    b = D_80086500;
    do {
        i--;
        b->unk0 = 0;
        a->unk0 = 0;
        a++;
        b++;
    } while (i != 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001A948.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001AB44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001AC20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001AD28.s")

void func_8001AD64(Unk1B200Particle* arg0) {
    u16 v = arg0->unk0;

    if (!(v & 3)) {
        arg0->unk10 = D_8004EF4C[v >> 2];
    }
    arg0->unk28 = arg0->unk2C = D_8004EF58[v];
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, D_8004EF88[arg0->unk0]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001ADE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001AE24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001AF90.s")

void func_8001B3CC(void) {
    Unk800866D8* p = D_800866D8;
    s32 i = 8;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

void func_8001B3FC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Unk800866D8* p = D_800866D8;
    s32 i = 7;

    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unk0 = arg1;
    p->unk4 = arg0;
    p->unk8 = arg2;
    p->unkC = arg3;
    p->unk10 = arg4;
    p->unk14 = arg5;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001B45C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001B688.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001B7E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001B9C0.s")

void func_8001BB18(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80087298[i].unk0 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001BB48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001BE2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001C038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001C060.s")

void func_8001C298(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Unk800877A8* p = &D_800877A8[arg0];

    p->unk0 = 3;
    p->unk2 = 0;
    p->unk4 = 10;
    p->unk8 = arg1;
    p->unkC = arg2;
    p->unk10 = arg3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001C2F8.s")

void func_8001C7E8(void) {
    s32 i = 32;
    Unk80086798* p = D_80086798;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001C818.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001C948.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001CBD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001CDF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001D688.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B200/func_8001D6A8.s")

void func_8001D94C(s32 arg0) {
    D_80087798[arg0].unk0 = 25;
}
