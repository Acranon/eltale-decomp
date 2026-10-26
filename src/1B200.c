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
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void* unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ void* unk10;
    /* 0x14 */ void* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 pad3D[3];
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
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Unk1B200Pos* unk14;
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
extern s16 D_800865CC;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
    /* 0x18 */ f32 vz;
    /* 0x1C */ f32 x0;
    /* 0x20 */ f32 y0;
    /* 0x24 */ f32 z0;
} Unk80087298; // size = 0x28

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk1B200Vec3;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Unk1B200Vec3 pts[16];
    /* 0xD4 */ Unk1B200Vec3 norms[16];
} Unk800877A8; // size = 0x194

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
} Unk80087798; // size = 0x4

typedef struct {
    /* 0x00 */ void* target;
    /* 0x04 */ u8 digits[8];
    /* 0x0C */ u16 timer;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 numDigits;
    /* 0x18 */ s32 unk18;
} Unk800865C0; // size = 0x1C

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
} Unk1B200Spark;

extern u8 D_800EB5E4[][4];
extern s32 D_80084B6C;
extern s32 D_80084B70;
extern s32 D_80084B74;
typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 eyeX;
    /* 0x10 */ f32 eyeY;
    /* 0x14 */ f32 eyeZ;
    /* 0x18 */ u8 pad18[0x14];
    /* 0x2C */ f32 yaw;
} Unk80085E48;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ void* unk8;
} Unk800EB2B4; // size = 0xC

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 mask;
    /* 0x04 */ u16 shift;
    /* 0x06 */ u16 tlut;
    /* 0x08 */ s32 img;
    /* 0x0C */ s16 s;
    /* 0x0E */ s16 t;
    /* 0x10 */ s16 ds;
    /* 0x12 */ s16 dt;
} Unk800DA0F0; // size = 0x14

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ Unk800EB2B4 unk38;
    /* 0x44 */ Unk800DA0F0 unk44;
} Unk80086798b; // size = 0x58

/* This file's .bss, 800863F0..80087E30 (in address order; first declaration
 * fixes the order). 800865C0..80087E00 is the 16-byte-aligned run that holds D_80087798 (func_8001D688 shares a lui between its pairs only when it
 * is defined here). Labels splat put inside these arrays (D_800865CC..,
 * D_8008779C.., D_8008793C) are gone; no asm uses them now. */

extern Unk80085E48 D_80085E48;
extern s32 D_8007A17C;
extern Unk800EB2B4 D_800EB2B4[];
extern u8 D_800CADA8[][4];
extern Unk800DA0F0 D_800DA0F0[];
typedef struct {
    f32 mf[4][4];
} MtxF;

extern Gfx D_800EB6D0[];
s32 func_8001CBD0(Unk80086798b*, s32);
s32 func_8001CDF4(Unk80086798b*);
void func_80027430(MtxF*, f32, f32, f32);
f32 func_800270D0(f32, f32);
u32 func_80026E90(u32);
s32 func_800281F0(s32, u8*, u16);
extern s32 D_8007A180;
void func_80027220(MtxF*, f32, f32, f32, f32, f32, f32, f32);
void func_800278C8(MtxF*, f32, f32, f32);
void func_80027CB4(MtxF*, f32, f32, f32);
f32 sqrtf(f32);
typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000_1B200;
extern Unk2000000_1B200 D_2000000;
extern Gfx D_800EB880[];
extern Gfx D_800EB8E8[];

void func_8001A828(Unk1B200Particle* arg0);
void func_8001AC20(Unk1B200Particle* arg0);
void func_8001AD64(Unk1B200Particle* arg0);
void func_8001B688(Unk1B200Spark* arg0);
void func_8001B9C0(Unk1B200Spark* arg0);

/* This file's .data, 8004EE20..8004F060: effect descriptors (Unk8004EE20,
 * 0x40 bytes each) and their tables, in source order: these first, then
 * func_8001AB44's static descriptor (8004EE9C), D_8004EEDC, func_8001AD28's
 * static descriptor (8004EF0C) and the tables after func_8001AD28. Both
 * descriptors must be function statics: IDO then stores their fields through
 * lui/%lo instead of the descriptor's address register. */
Unk8004EE20 D_8004EE20 = {
    0x000C, 0, (void*)func_8001A828, 0x02101000, 0, (void*)0x800C3650, (void*)0x800C3790,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0,
};
f32 D_8004EE60[12] = {
    3.25f, 3.24f, 3.23f, 3.22f, 3.21f, 3.2f, 3.0f, 2.8f, 2.6f, 2.4f, 2.2f, 2.0f,
};
u8 D_8004EE90[12] = { 0x10, 0x20, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xB0, 0xA0, 0x80, 0x40 };
typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 y;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ Unk1B200Vec3 normal;
    /* 0x18 */ u16 flags;
} Coll1B200;

s32 D_800863F0;
u16 D_800863F4;
s32 D_800863F8;
Unk80086400 D_80086400[8];
Unk80086440 D_80086440[8];
Unk80086440 D_80086500[8];
Unk800865C0 D_800865C0[10];
Unk800866D8 D_800866D8[8];
Unk80086798b D_80086798[32];
Unk80087298 D_80087298[32];
Unk80087798 D_80087798[4];
Unk800877A8 D_800877A8[4];
u16 D_80087DF8;
Unk1B200Vec2 D_80087E00;
u8 D_80087E08[8]; /* unreferenced */
Coll1B200 D_80087E10;

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
s32 func_8001D9A8(void*);
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

void func_8001A948(f32 x, f32 y, f32 z, Unk1B200Pos* arg3) {
    s32 pad[4];
    Unk80086440* cur;
    Unk80086440* prev;
    f32 angle;
    s32 n;

    cur = D_8007A17C ? D_80086440 : D_80086500;
    prev = D_8007A17C ? D_80086500 : D_80086440;
    angle = func_800270D0(x - D_80085E48.eyeX, z - D_80085E48.eyeZ) - D_80085E48.yaw + 3.141592653589793;
    if (angle < -3.141592653589793) {
        angle += 6.283185307179586;
    } else if (angle > 3.141592653589793) {
        angle -= 6.283185307179586;
    }
    if (angle > -1.5707963267948966 && angle < 1.5707963267948966 && D_800863F0 < 8) {
        n = D_800863F8;
        cur += D_800863F0;
        while (n != 0 && arg3 != prev->unk14) {
            n--;
            prev++;
        }
        if (n != 0) {
            cur->unk0 = prev->unk0;
        } else {
            cur->unk0 = func_80026E90(4) * 4 + 1;
        }
        cur->x = x;
        cur->y = y;
        cur->z = z;
        cur->unk10 = arg3->unk10;
        cur->unk14 = arg3;
        D_800863F0++;
    }
}

void func_8001AB44(void) {
    static Unk8004EE20 D_8004EE9C = {
        0x002D, 0, (void*)func_8001AC20, 0x02101000, 0, (void*)0x800C3650, (void*)0x800C37E0,
        0.0f, 0.0f, 0.0f, 0.0f, 4.0f, 4.0f, 0.1f, 0.25f, 0.05f, 0,
    };
    Unk80086440* p;
    s32 n;

    D_800863F8 = D_800863F0;
    p = D_8007A17C ? D_80086440 : D_80086500;
    n = D_800863F8;
    while (n != 0) {
        if (p->unk0 != 0 && --p->unk0 == 0) {
            D_8004EE9C.unk18 = p->x;
            D_8004EE9C.unk1C = p->y;
            D_8004EE9C.unk20 = p->z;
            D_8004EE9C.unk28 = D_8004EE9C.unk2C = p->unk10;
            func_8001D9A8(&D_8004EE9C);
            p->unk0 = 0x19;
        }
        n--;
        p++;
    }
}

/* func_8001AC20's table sits between the two function statics. */
u8 D_8004EEDC[48] = {
    0x08, 0x1C, 0x30, 0x44, 0x58, 0x6C, 0x80, 0x94, 0xA8, 0xBC, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
    0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00, 0x00, 0x00,
};

void func_8001AC20(Unk1B200Particle* arg0) {
    s32 r;
    s32 g;
    s32 b;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk28 += 0.08;
    arg0->unk2C += 0.08;
    r = D_80084B6C + 0x40;
    g = D_80084B70 + 0x40;
    b = D_80084B74 + 0x40;
    if (r >= 0x100) {
        r = 0xFF;
    }
    if (g >= 0x100) {
        g = 0xFF;
    }
    if (b >= 0x100) {
        b = 0xFF;
    }
    gDPSetEnvColor(D_8007A184++, r, g, b, D_8004EEDC[arg0->unk0]);
}

void func_8001AD28(f32 x, f32 y, f32 z) {
    static Unk8004EE20 D_8004EF0C = {
        0x000C, 0, (void*)func_8001AD64, 0x04202000, 0, (void*)0x800C3830, (void*)0x800C4070,
        0.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f, 0,
    };

    D_8004EF0C.unk18 = x;
    D_8004EF0C.unk1C = y;
    D_8004EF0C.unk20 = z;
    func_8001D9A8(&D_8004EF0C);
}

/* The rest of this file's .data (each table belongs to one of the functions below). */
s32 D_8004EF4C[3] = { 0x800C3E30, 0x800C3C30, 0x800C3A30 };
f32 D_8004EF58[12] = {
    0.88f, 0.88f, 0.84f, 0.84f, 0.82f, 0.82f, 0.8f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f,
};
u8 D_8004EF88[12] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0xA0, 0xC0, 0xC8, 0x80, 0x60 };
u8 D_8004EF94[4][4] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xC8, 0xFF, 0xC8, 0xFF }, { 0xC8, 0xC8, 0xFF, 0xFF }, { 0xFF, 0x7F, 0x7F, 0xFF },
};
Unk8004EE20 D_8004EFA4 = {
    0x0014, 0, (void*)func_8001B688, 0x02101000, 0, (void*)0x800C4128, (void*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
Unk8004EE20 D_8004EFE4 = {
    0x0014, 0, (void*)func_8001B9C0, 0x02101000, 0, (void*)0x800C4128, (void*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
u16 D_8004F024[4] = { 0x14, 0xC, 0xC, 0 };
u8 D_8004F02C[3][4] = { { 0xC8, 0xC8, 0x00, 0x00 }, { 0xC8, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xC8, 0x00 } };
u8 D_8004F038[4] = { 0xFF, 0x96, 0x00, 0x00 };
s32 D_8004F03C[4] = { 0x800CAE68, 0x800CB068, 0x800CB268, 0x800CB468 };
u8 D_8004F04C[5][4] = {
    { 0xFF, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0xFF, 0x00 }, { 0x00, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },
};

void func_8001AD64(Unk1B200Particle* arg0) {
    u16 v = arg0->unk0;

    if (!(v & 3)) {
        arg0->unk10 = D_8004EF4C[v >> 2];
    }
    arg0->unk28 = arg0->unk2C = D_8004EF58[v];
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, D_8004EF88[arg0->unk0]);
}

void func_8001ADE4(void) {
    s32 i = 10;
    Unk800865C0* p = D_800865C0;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void func_8001AE24(void* arg0, s32 arg1, s32 arg2) {
    s32 pad[2];
    Unk800865C0* var_t0;
    s32 var_v1;
    s32 i;

    i = 9;
    var_t0 = D_800865C0;
    while ((i != 0) && (var_t0->timer != 0)) {
        i--;
        var_t0++;
    }
    var_t0->timer = 0x2D;
    var_t0->target = arg0;
    var_t0->unk10 = arg1;

    if (arg2 < 0) {
        arg2 = -arg2;
    }

    var_t0->numDigits = func_800281F0(arg2, var_t0->digits, 1U);
    var_v1 = 0;

    for (i = 0; i < 10; i++) {
        if ((D_800865C0[i].timer != 0) && (arg0 == D_800865C0[i].target)) {
            var_v1++;
        }
    }
    var_t0->unk18 = var_v1 - 1;
}

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pad2[0x1A];
    /* 0x1C */ f32 height;
} Unk1B200DmgModel;

typedef struct {
    /* 0x00 */ u8 pad0[0x94];
    /* 0x94 */ f32 top;
} Unk1B200DmgModel2;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[0x18];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x3C];
    /* 0x64 */ Unk1B200DmgModel* model;
    /* 0x68 */ Unk1B200DmgModel2* model2;
} Unk1B200DmgActor;

extern Gfx D_800C40C0[];
extern u8 D_8039E290[];
s32 func_80027FFC(f32, f32, f32, s32*, s32*);
s16 sins(u16);

void func_8001AF90(void) {
    s32 n;
    Unk800865C0* d;
    s32 first;
    Unk1B200DmgActor* actor;
    s32 sx;
    s32 sy;
    f32 y;
    s16 dsdx;
    s16 dtdy;
    s32 w;
    s32 h;
    s32 k;
    u8* dp;
    u8* c;

    first = 0;
    n = 10;
    d = D_800865C0;
    do {
        if (d->timer) {
            actor = d->target;
            if (actor->model->type == 0) {
                y = actor->y + actor->model->height * actor->scale;
            } else if (actor->model->type == 1) {
                y = actor->model2->top;
            } else {
                y = actor->y + 600.0 * actor->scale;
            }
            if (func_80027FFC(actor->x, y, actor->z, &sx, &sy)) {
                if (!first) {
                    gSPDisplayList(D_8007A184++, D_800C40C0);
                    gDPLoadTextureBlock(D_8007A184++, D_8039E290, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
                    first++;
                }
                if (d->unk10 & 0x8000) {
                    dsdx = 0x280;
                    dtdy = 0x280;
                    w = 6;
                    h = 8;
                } else {
                    dsdx = 0x400;
                    dtdy = 0x400;
                    w = 4;
                    h = 5;
                }
                if (d->timer >= 30) {
                    s32 a = sins((45 - d->timer) << 12) >> 11;
                    if (a < 0) {
                        a = -a;
                    }
                    sy -= a;
                }
                sx -= d->unk18 * w;
                sy = sy - d->unk18 * 5 - 8;
                c = D_8004EF94[d->unk10 & 0xF];
                gDPPipeSync(D_8007A184++);
                gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], 255);
                dp = d->digits;
                sx -= (k = d->numDigits) * 4;
                while (k) {
                    k--;
                    if (*dp != 0x20) {
                        gSPTextureRectangle(D_8007A184++, (sx - w) << 2, (sy - h) << 2, (sx + w) << 2, (sy + h) << 2, G_TX_RENDERTILE, *dp << 8, 0, dtdy, dsdx);
                        sx += w * 2;
                    }
                    dp++;
                }
            }
            d->timer--;
        }
        n--;
        d++;
    } while (n);
}


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

void func_8001B45C(void) {
    Unk800866D8* p;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    f32 a;
    MtxF mtx;
    f32 b;
    Unk8004EE20 spawn;

    spawn = D_8004EFA4;
    p = D_800866D8;
    i = 8;
    do {
        if (p->unk0 != 0) {
            if (p->unk0 & 1) {
                a = (f32)func_80026E90(32) * 3.141592653589793 / 16.0f;
                b = (f32)func_80026E90(32) * 3.141592653589793 / 16.0f;
                func_80027430(&mtx, a, b, 0.0f);
                guMtxXFMF(mtx.mf, 0.0f, 0.0f, p->unk14, &x, &y, &z);
                spawn.unk18 = p->unk8 + x;
                spawn.unk1C = p->unkC + y;
                spawn.unk20 = p->unk10 + z;
                spawn.unk30 = x * -0.03;
                spawn.unk34 = y * -0.03;
                spawn.unk38 = z * -0.03;
                spawn.unk3C = p->unk4;
                func_8001D9A8(&spawn);
            }
            p->unk0--;
        }
        i--;
        p++;
    } while (i != 0);
}

void func_8001B688(Unk1B200Spark* arg0) {
    u8* c;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.9;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.9;
    arg0->unk24 += 0.39269908169872414;
    if (arg0->unk0 < 10) {
        arg0->unk28 = arg0->unk2C = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->unk0 & 1) {
        gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], 0xDC);
    } else {
        gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], 0x20);
    }
}

void func_8001B7E0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    f32 a;
    f32 b;
    f32 c;
    MtxF mtx;
    Unk8004EE20 spawn;
    spawn = D_8004EFE4;
    i = 15;
    do {
        a = (f32)func_80026E90(32) * 3.141592653589793 / 16.0f;
        b = (f32)func_80026E90(32) * 3.141592653589793 / 16.0f;
        func_80027430(&mtx, a, b, 0.0f);
        guMtxXFMF(mtx.mf, 0.0f, 0.0f, arg4, &a, &b, &c);
        spawn.unk18 = arg1;
        spawn.unk1C = arg2;
        spawn.unk20 = arg3;
        spawn.unk30 = a;
        spawn.unk34 = b;
        spawn.unk38 = c;
        spawn.unk3C = arg0;
        func_8001D9A8(&spawn);
        i--;
    } while (i != 0);
}

void func_8001B9C0(Unk1B200Spark* arg0) {
    u8* c;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.8;
    arg0->unk38 *= 0.8;
    arg0->unk24 += 0.39269908169872414;
    if (arg0->unk0 < 10) {
        arg0->unk28 = arg0->unk2C = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->unk0 & 1) {
        gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], 0xDC);
    } else {
        gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], 0x20);
    }
}

void func_8001BB18(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80087298[i].unk0 = 0;
    }
}

void func_8001BB48(void* arg0) {
    s32 n;
    Unk80087298* p;
    s32 first;
    u32 alpha;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    MtxF mtx;

    first = 0;
    p = D_80087298;
    n = 32;
    do {
        if (p->unk0 != 0) {
            p->x += p->vx;
            p->y += p->vy;
            p->z += p->vz;
            if (D_8007A180 < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(D_8007A184++, D_800EB880);
                    first++;
                }
                if (p->unk0 & 1) {
                    alpha = 250;
                } else {
                    alpha = 150;
                }
                if (p->unk0 < 8) {
                    alpha = (p->unk0 * alpha) >> 3;
                }
                func_800278C8(&mtx, p->vx, p->vy, p->vz);
                dx = p->x - p->x0;
                dy = p->y - p->y0;
                dz = p->z - p->z0;
                dist = sqrtf(dx * dx + dy * dy + dz * dz);
                func_80027CB4(&mtx, 0.35f, dist * 0.1, 0.35f);
                mtx.mf[3][0] = p->x;
                mtx.mf[3][1] = p->y;
                mtx.mf[3][2] = p->z;
                guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[D_8007A180]);
                gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gDPSetEnvColor(D_8007A184++, 255, 255, 255, alpha);
                gSPDisplayList(D_8007A184++, D_800EB8E8);
            }
            p->unk0--;
            p->vx *= 0.6;
            p->vy *= 0.6;
            p->vz *= 0.6;
        }
        n--;
        p++;
    } while (n != 0);
}

void func_8001BE2C(f32 x, f32 y, f32 z) {
    s32 n;
    Unk80087298* p;
    s32 count;
    f32 a;
    f32 b;
    f32 r;
    MtxF mtx;

    p = D_80087298;
    n = 31;
    count = 16;
    do {
        while (n != 0 && p->unk0 != 0) {
            n--;
            p++;
        }
        p->unk0 = func_80026E90(8) + 10;
        p->x = x;
        p->x0 = x;
        p->y = y;
        p->y0 = y;
        p->z0 = z;
        p->z = z;
        a = func_80026E90(20) * 3.141592653589793 / 10.0;
        b = func_80026E90(20) * 3.141592653589793 / 10.0;
        r = (f32)func_80026E90(10) / 3.0 + 3.0;
        func_80027430(&mtx, a, b, 0.0f);
        guMtxXFMF(mtx.mf, 0.0f, 0.0f, r, &p->vx, &p->vy, &p->vz);
        count--;
    } while (count != 0 && n != 0);
}

void func_8001C038(void) {
    s32 i = 4;
    Unk800877A8* p = D_800877A8;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ f32 unk1C;
} Unk8007AA08_1B200;
extern Unk8007AA08_1B200 D_8007AA08;
void func_800107F0(f32, f32, f32, s32, Coll1B200*);
s32 func_8001C060(u16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    Unk800877A8* p;
    Unk1B200Vec3* pt;
    Unk1B200Vec3* n;
    s32 j;
    f32 angle;
    f32 dy;

    p = D_800877A8;
    for (i = 0; i != 3; i++, p++) {
        if (p->unk0 == 0) {
            break;
        }
    }
    p->unk6 = arg0;
    p->unk0 = 1;
    p->unk2 = 0;
    p->unk4 = D_8004F024[arg0];
    p->unk8 = arg1;
    p->unkC = arg2;
    p->unk10 = arg3;
    pt = p->pts; n = p->norms; j = 16;
    angle = 0.0f;
    do {
        D_80087E00.x = 0.0f;
        D_80087E00.y = arg4;
        func_800271B4(angle, &D_80087E00);
        pt->x = D_80087E00.x + arg1;
        pt->z = D_80087E00.y + arg3;
        func_800107F0(pt->x, D_8007AA08.unk1C, pt->z, 0xA00, &D_80087E10);
        if (D_80087E10.flags & 0x8000) {
            pt->y = arg2;
            n->x = 0.0f;
            n->y = 1.0f;
            n->z = 0.0f;
        } else {
            dy = D_80087E10.y - arg2;
            if (dy < -40.0 || dy > 40.0) {
                pt->y = arg2;
                n->x = 0.0f;
                n->y = 1.0f;
                n->z = 0.0f;
            } else {
                pt->y = D_80087E10.y;
                n->x = D_80087E10.normal.x;
                n->y = D_80087E10.normal.y;
                n->z = D_80087E10.normal.z;
            }
        }
        angle += 0.39269908169872414;
        pt++;
        n++;
    } while (--j != 0);
    return i;
}

void func_8001C298(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Unk800877A8* p = &D_800877A8[arg0];

    p->unk0 = 3;
    p->unk2 = 0;
    p->unk4 = 10;
    p->unk8 = arg1;
    p->unkC = arg2;
    p->unk10 = arg3;
}

extern Gfx D_800C4780[];
extern u8 D_800C47C0[];
extern Gfx D_800C4840[];

void func_8001C2F8(void* arg0) {
    s32 cnt;
    Unk800877A8* p;
    s32 first;
    u8 alpha;
    s32 j;
    Unk1B200Vec3* pt;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 len;
    f32 scale;
    u8* color;
    f32 dx;
    f32 dy;
    f32 dz;
    MtxF mtx;

    first = 0;
    p = D_800877A8;
    cnt = 4;
    do {
        if (p->unk0) {
            if (first == 0) {
                gSPDisplayList(D_8007A184++, D_800C4780);
                gDPLoadTextureBlock(D_8007A184++, D_800C47C0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_WRAP, G_TX_WRAP, 3, 0, G_TX_NOLOD, G_TX_NOLOD);
                first++;
            }
            p->unk2++;
            alpha = D_8004F038[p->unk2 & 1];
            switch (p->unk0) {
                case 1:
                    if (p->unk2 < 4) {
                        alpha = (alpha * p->unk2) >> 2;
                    }
                    if (p->unk4 < p->unk2) {
                        p->unk0++;
                    } else {
                        scale = sinf(p->unk2 * 3.141592653589793 / (p->unk4 * 2));
                    }
                    break;
                case 3:
                    alpha = (alpha * (p->unk4 - p->unk2)) / p->unk4;
                    if (!(p->unk2 < p->unk4)) {
                        p->unk0 = 0;
                    }
                    break;
            }
            color = D_8004F02C[p->unk6];
            gDPSetEnvColor(D_8007A184++, color[0], color[1], color[2], alpha);
            pt = p->pts;
            j = 16;
            do {
                x0 = pt->x;
                y0 = pt->y + 5.0f;
                z0 = pt->z;
                pt++;
                if (--j == 0) {
                    pt = p->pts;
                }
                x1 = pt->x;
                y1 = pt->y + 5.0f;
                z1 = pt->z;
                if (p->unk0 == 1) {
                    x0 = (x0 - p->unk8) * scale + p->unk8;
                    y0 = (y0 - p->unkC) * scale + p->unkC;
                    z0 = (z0 - p->unk10) * scale + p->unk10;
                    x1 = (x1 - p->unk8) * scale + p->unk8;
                    y1 = (y1 - p->unkC) * scale + p->unkC;
                    z1 = (z1 - p->unk10) * scale + p->unk10;
                }
                dx = x1 - x0;
                dy = y1 - y0;
                dz = z1 - z0;
                len = sqrtf(dx * dx + dy * dy + dz * dz);
                if (len != 0.0f) {
                    func_800278C8(&mtx, dx, dy, dz);
                    func_80027CB4(&mtx, 2.0f, len, 1.5f);
                    mtx.mf[3][0] = x0;
                    mtx.mf[3][1] = y0;
                    mtx.mf[3][2] = z0;
                    guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[D_8007A180]);
                    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                    gSPDisplayList(D_8007A184++, D_800C4840);
                }
            } while (j != 0);
        }
        p++;
    } while (--cnt != 0);
}

void func_8001C7E8(void) {
    s32 i = 32;
    Unk80086798b* p = D_80086798;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

Unk80086798b* func_8001C818(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    s32 i;
    Unk80086798b* p;

    i = 31;
    p = D_80086798;
    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unkC = arg5;
    p->unk10 = arg6;
    p->unk14 = arg7;
    p->unk18 = arg8;
    p->unk1C = arg9;
    p->unk20 = arg10;
    p->unk24 = arg11;
    p->unk28 = 0.0f;
    p->unk2C = 0.0f;
    p->unk30 = 1.0f;
    p->unk38 = D_800EB2B4[arg0];
    p->unk4 = 0;
    p->unk6 = arg3;
    p->unk38.unk8 = D_800CADA8[arg1];
    p->unk0 = p->unk2 = p->unk38.unk2;
    p->unk8 = arg4;
    p->unk34 = 0;
    p->unk44 = D_800DA0F0[arg2];
    return p;
}

void func_8001C948(void* arg0) {
    Unk80086798b* p;
    s32 i;
    u32 alpha;
    u8* col;
    u16* cnt;

    cnt = &D_800863F4;
    gSPDisplayList(D_8007A184++, D_800EB6D0);
    D_80087DF8 = 0xFFFF;
    i = 32;
    p = D_80086798;
    do {
        if (p->unk0 != 0) {
            func_8001CDF4(p);
            if (p->unk8 & 2) {
                if (*cnt & 1) {
                    alpha = 240;
                } else {
                    alpha = 150;
                }
            } else {
                alpha = 250;
            }
            if (!(p->unk8 & 1) && p->unk0 < 8) {
                alpha = (p->unk0 * alpha) >> 3;
            } else if ((p->unk8 & 0x80) && p->unk4 < 8) {
                alpha = (p->unk4 * alpha) >> 3;
            }
            col = D_800EB5E4[p->unk6 & 0xFF];
            gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], alpha);
            if (p->unk8 & 8) {
                gSPSetGeometryMode(D_8007A184++, G_CULL_BACK);
            } else {
                gSPClearGeometryMode(D_8007A184++, G_CULL_BACK);
            }
            func_8001CBD0(p, (s32)arg0);
            p->unk34++;
            if (--p->unk0 == 0) {
                if (p->unk8 & 1) {
                    p->unk0 = p->unk2;
                }
            }
            p->unk4++;
        }
        i--;
        p++;
    } while (i != 0);
    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
    (*cnt)++;
}


typedef struct {
    f32 x, y, z;
} Vec3f_1B200;
typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ s8 unk14;
    /* 0x15 */ u8 pad15[0xB];
} Anim1B200; // size = 0x20
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ Anim1B200* unk4;
} AnimSet1B200;
extern s32 D_8008BFF0;
void func_80020568(MtxF*, Vec3f_1B200, s32, s32, s32, s32, AnimSet1B200*, Anim1B200*, s32);
s32 func_8001CBD0(Unk80086798b* arg0, s32 arg1) {
    u32 i;
    Anim1B200* anims;
    s32 frame;
    MtxF mtx;
    Vec3f_1B200 scale;

    D_8008BFF0 = 0;
    if (arg0->unk8 & 4) {
        func_800278C8(&mtx, arg0->unk28, arg0->unk2C, arg0->unk30);
        mtx.mf[3][0] = arg0->unkC;
        mtx.mf[3][1] = arg0->unk10;
        mtx.mf[3][2] = arg0->unk14;
        func_80027CB4(&mtx, arg0->unk1C * 0.01, arg0->unk20 * 0.01, arg0->unk24 * 0.01);
    } else {
        func_80027220(&mtx, 0.0f, arg0->unk18, 0.0f, 0.01f, arg0->unkC, arg0->unk10, arg0->unk14);
        func_80027CB4(&mtx, arg0->unk1C, arg0->unk20, arg0->unk24);
    }
    scale.x = arg0->unk1C * 0.01;
    scale.y = arg0->unk20 * 0.01;
    scale.z = arg0->unk24 * 0.01;
    anims = ((AnimSet1B200*)&arg0->unk38)->unk4;
    frame = arg0->unk34;
    if (D_8007A180 < 0x1E6) {
        for (i = 0; i < ((AnimSet1B200*)&arg0->unk38)->unk0; i++) {
            if (anims[i].unk14 == 0) {
                func_80020568(&mtx, scale, 0, i, frame, 0, (AnimSet1B200*)&arg0->unk38, anims, arg1);
            }
        }
    }
}

s32 func_8001CDF4(Unk80086798b* arg0) {
    Unk800DA0F0* t;
    u32 mask;
    u32 size;
    s32 geom = 0;
    s32 img;
    s32 clamp;

    if (arg0->unk44.img != 0) {
        t = &arg0->unk44;
        if (arg0->unk8 & 0x20) {
            geom = G_LIGHTING;
        }
        t->s += t->ds;
        t->t += t->dt;
        img = t->img;
        size = (t->flags & 1) ? 16 : 32;
        if (t->flags & 1) {
            mask = 4;
        } else {
            mask = 5;
        }
        if (t->flags & 4) {
            img += (arg0->unk4 >> t->shift) * size * size;
        } else if (t->flags & 8) {
            img += ((arg0->unk4 >> t->shift) & t->mask) * size * size;
        }
        if (t->flags & 0x10) {
            clamp = 1;
        } else {
            clamp = 0;
        }
        if (t->flags & 2) {
            gDPLoadTextureBlock(D_8007A184++, img, G_IM_FMT_I, G_IM_SIZ_8b, size, size, 0, clamp, clamp, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            if (t->flags & 0x40) {
                if (arg0->unk8 & 0x20) {
                    gDPSetCombine(D_8007A184++, 0x629A04, 0x1F10FFFF);
                } else {
                    gDPSetCombine(D_8007A184++, 0x629BFF, 0x1F10FE3F);
                }
            } else if (arg0->unk8 & 0x20) {
                gDPSetCombine(D_8007A184++, 0x62FE04, 0x1F10FBFF);
            } else {
                gDPSetCombine(D_8007A184++, 0x62FFFF, 0x1F10FA3F);
            }
        } else {
            gDPLoadTextureBlock(D_8007A184++, img, G_IM_FMT_CI, G_IM_SIZ_8b, size, size, 0, clamp, clamp, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
            if (arg0->unk8 & 0x20) {
                gDPSetCombine(D_8007A184++, 0x129804, 0xFF17FFFF);
            } else {
                gDPSetCombine(D_8007A184++, 0x1299FF, 0xFF17FE3F);
            }
            if (D_80087DF8 != t->tlut) {
                D_80087DF8 = t->tlut;
                gDPLoadTLUT_pal256(D_8007A184++, D_8004F03C[D_80087DF8]);
            }
        }
        gDPSetTileSize(D_8007A184++, G_TX_RENDERTILE, t->s, t->t, t->s + size, t->t + size);
        if (t->flags & 0x20) {
            gSPTexture(D_8007A184++, size << 6, size << 6, 0, G_TX_RENDERTILE, G_ON);
            geom |= G_LIGHTING | G_TEXTURE_GEN;
        } else {
            gSPTexture(D_8007A184++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        }
    } else {
        gDPPipeSync(D_8007A184++);
        gDPSetCombine(D_8007A184++, 0x62CBFF, 0x4FFE7E38);
        gSPTexture(D_8007A184++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
    }
    gSPClearGeometryMode(D_8007A184++, G_LIGHTING | G_TEXTURE_GEN);
    if (geom) {
        gSPSetGeometryMode(D_8007A184++, geom);
    }
}

void func_8001D688(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_80087798[i].unk0 = 0;
    }
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk8007AB48;
extern Unk8007AB48 D_8007AB48;
extern f32 D_8007AA44;
extern Gfx D_800EB9C8[];
extern Gfx D_800EB990[];
void func_800275DC(MtxF*, f32, f32, f32, f32, f32, f32);
void func_8001D6A8(void* arg0) {
    s32 first;
    s32 i;
    Unk80087798* p;
    u32 alpha;
    f32 x;
    f32 y;
    f32 z;
    MtxF mtx;
    Gfx* gfx;

    first = 0;
    for (i = 0, p = D_80087798; i < 4; i++, p++) {
        if (p->unk0 != 0) {
            if (D_8007A180 < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(D_8007A184++, D_800EB990);
                    first++;
                }
                alpha = 200 - func_80026E90(32);
                if (p->unk0 < 8) {
                    alpha = (p->unk0 * alpha) >> 3;
                } else if (p->unk0 >= 22) {
                    alpha = ((25 - p->unk0) * alpha) >> 2;
                }
                x = D_8007AB48.x;
                y = D_8007AA44 * 70.0 + D_8007AB48.y;
                z = D_8007AB48.z;
                func_800275DC(&mtx, x, y, z, D_80085E48.eyeX, D_80085E48.eyeY, D_80085E48.eyeZ);
                func_80027CB4(&mtx, D_8007AA44, D_8007AA44, D_8007AA44);
                guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[D_8007A180]);
                /* Keep the index update in the matrix command's scope for IDO scheduling. */
                {
                    Gfx* _g = D_8007A184++;
                    _g->words.w0 = 0x01020040;
                    _g->words.w1 = (u32)&D_2000000.unkC0[D_8007A180];
                    D_8007A180++;
                }
                gDPSetEnvColor(D_8007A184++, D_8004F04C[i / 1][0], D_8004F04C[i / 1][1], D_8004F04C[i / 1][2], alpha);
                gSPDisplayList(D_8007A184++, D_800EB9C8);
            }
            p->unk0--;
        }
    }
}


void func_8001D94C(s32 arg0) {
    D_80087798[arg0].unk0 = 25;
}
