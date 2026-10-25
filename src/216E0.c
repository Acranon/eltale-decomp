#include "common.h"

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x1C - 0x8];
    /* 0x1C */ f32 unk1C;
} Struct_80024338_64;

typedef struct {
    /* 0x00 */ char unk0[0x94];
    /* 0x94 */ f32 unk94;
} Struct_80024338_68;

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x24 - 0x8];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x64 - 0x28];
    /* 0x64 */ u16* unk64;
    /* 0x68 */ Struct_80024338_68* unk68;
} Struct_8002433C_arg;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x04 */ Struct_8002433C_arg* unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
} Struct_8008C058;

extern Struct_8008C058 D_8008C058[8];
extern u8** D_800C03D8[];
extern u8 D_8004F2C4[];
extern u8 D_8004F498[];

u32 func_800167B0(u16, s32);
s32 func_800168F0(u32, u16);
s32 func_800281F0(s32, u8*, u16);
void func_80024694(s32, s32, s32, u8*);
s32 func_80024904(u8*);
typedef struct {
    /* 0x00 */ void* img;
    /* 0x04 */ u16 is4b;
    /* 0x08 */ u32 width;
} Struct_80024A54;

void func_80024A54(Struct_80024A54*, s32, s32, s32, s32);
void func_80024D40(s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ char unk0[0x1C];
    /* 0x1C */ f32 unk1C;
} Struct_8007AA08_7C;

typedef struct {
    /* 0x00 */ char unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x3C - 0x24];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ char unk40[0x7C - 0x40];
    /* 0x7C */ Struct_8007AA08_7C* unk7C;
} Struct_8007AA08;

extern Gfx* D_8007A184;
extern Struct_8007AA08 D_8007AA08;
extern u16 D_8008C042;
extern s32 D_8008C044;
extern s32 D_8008C048;
extern s32 D_8008C04C;
extern u16 D_8008C050;
extern s32 D_8008C054;
extern u32 D_8008C138;
extern u16 D_8008C14C[2];
extern u16 D_8008C15A;
extern u16 D_8008C15C;
extern u16 D_8008C15E;
extern u16 D_8008C162;
extern s32 D_8008C168;
extern s32 D_8008C16C;
extern s32 D_8008C170;
extern s32 D_8008C174;
extern s32 D_8008C178;
extern Gfx D_803AA448[];
extern Gfx D_803AA4C0[];
extern Gfx D_803AA538[];

s32 func_80027FFC(f32, f32, f32, s32*, s32*);
s16 sins(u16);
void func_80024D40(s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 x, y, z;
} Vec3f_216E0;

extern u8 D_803A4118[];
extern u8 D_803A8728[];
extern u8* D_803A8778[];
extern Struct_80024A54 D_803A8748;

void func_80024EB0(void*, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x18 - 0x2];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} Struct_8002373C_64;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x12 - 0x2];
    /* 0x12 */ u8 unk12[0x10];
    /* 0x22 */ s8 unk22[0x10];
    /* 0x32 */ s8 unk32[0x12];
    /* 0x44 */ s32 unk44[4];
    /* 0x54 */ char unk54[0x94 - 0x54];
    /* 0x94 */ f32 unk94;
} Struct_8002373C_68;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x24 - 0xC];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x64 - 0x28];
    /* 0x64 */ Struct_8002373C_64* unk64;
    /* 0x68 */ Struct_8002373C_68* unk68;
} Struct_8002373C;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AA6C4;

typedef struct {
    char unk0[0xA];
} Struct_803AA690;

extern u16 D_8004F2DC[];
extern u16 D_8004F2EC[];
extern Vec3f_216E0 D_8008C140;
extern Struct_803AA690 D_803AA690[];
extern Struct_803AA6C4 D_803AA6C4[];

s32 func_80019820(u16, u16, f32, f32, f32, f32, Struct_803AA690*, Vec3f_216E0*, Struct_8002373C*);

void func_80020AE0(void) {
    D_8008C168 = 0;
    D_8008C16C = 0;
    D_8008C170 = -1;
    D_8008C178 = 0;
    D_8008C174 = D_8008C178;
    D_8008C048 = 0;
    D_8008C044 = D_8008C048;
    D_8008C04C = 0x140;
    D_8008C054 = 0xF0;
    D_8008C162 = 0;
    D_8008C15E = 0;
    D_8008C15C = 0;
    D_8008C15A = D_8008C15C;
    D_8008C138 = 0;
    D_8008C042 = 0;
}

typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

typedef struct {
    /* 0x000 */ char unk0[0x2C];
    /* 0x02C */ char unk2C[0x7C - 0x2C];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ char unk7E[0x130 - 0x7E];
} Struct_8007B908_216E0;

typedef struct {
    /* 0x00 */ char unk0[0x14];
    /* 0x14 */ u16 unk14;
} Struct_8007C288;

extern Unk2000000 D_2000000;
extern s32 D_8004DCA0;
extern s32 D_8007A180;
extern s32 D_8007A9C0;
extern s32 D_8007A9C4;
extern s32 D_8007A9C8;
extern s32 D_8007A9CC;
extern u16 D_8007AA0A;
extern s32 D_8007AA10;
extern s32 D_8007AA1C;
extern u8 D_8007AA20[];
extern u16 D_8007AA80;
extern s32 D_8007B900;
extern Struct_8007B908_216E0 D_8007B908[];
extern Struct_8007C288* D_8007C288;
extern u16 D_800842B8;
extern s32 D_80085F90;
extern u16 D_8008BE52;
extern u16 D_8008C152;
extern u16 D_8008C154;
extern Gfx D_803A8788[];

struct Struct_80021030;
void func_80021030(struct Struct_80021030* arg0);
void func_800213A8(Unk2000000* arg0, s32 arg1);
void func_80021920(Unk2000000* buf);
struct Struct_80021C04;
void func_80021C04(Unk2000000* arg0, struct Struct_80021C04* arg1);
void func_80022658(void* arg0);
struct Struct_80022970;
void func_80022970(Unk2000000* arg0, struct Struct_80022970* arg1);
void func_800230A8(void);
void func_800231C4(void);
void func_800232A8(void);
void func_8002338C(void);
void func_80023470(u16 arg0);
void func_800235D8(void);
void func_80023930(Struct_8002373C* arg0);
void func_80023E14(void);
void func_8002440C(void);

void func_80020B78(Unk2000000* buf) {
    s32 n;
    Struct_8007B908_216E0* e;

    gSPMatrix(D_8007A184++, &D_2000000.unk0[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guTranslate(&buf->unkC0[D_8007A180], -160.0f, -120.0f, 0.0f);
    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    D_8008C04C = 0x140;
    D_8008C054 = 0xF0;
    gSPDisplayList(D_8007A184++, D_803A8788);
    if ((D_8004DCA0 & 2) && D_8008C154 != 1) {
        D_8008C154 = 1;
    } else if (!(D_8004DCA0 & 2) && D_8008C154 == 1) {
        D_8008C154 = 2;
    }
    if (!(D_8004DCA0 & 0xC00)) {
        func_80021030((struct Struct_80021030*)D_8007AA20);
        func_800213A8(buf, D_8007AA1C);
        if (D_8008C154 == 1) {
            if (++D_8008C152 >= 13) {
                D_8008C152 = 12;
            }
        } else if (D_8008C154 == 2) {
            if (--D_8008C152 == 0) {
                D_8008C154 = 0;
            }
        }
    }
    if ((D_800842B8 & 0xD) && !(D_8008BE52 & 1) && !(D_8007C288->unk14 & 8) && !(D_8004DCA0 & 2)) {
        func_80021920(buf);
    }
    if ((D_8008BE52 & 1) && D_8008C162) {
        func_80023E14();
        D_8008C162--;
    }
    D_8008C174 = D_8008C178 = 0;
    if (D_8008BE52 & 1) {
        func_8002440C();
        if (!(D_8008BE52 & 2) && D_8007AA0A && !(D_8007AA80 & 1) && !(D_80085F90 & 1)) {
            func_80023470(D_8007AA0A - 1);
        }
        if ((D_8007AA10 & 0x20) && !(D_8004DCA0 & 0x800)) {
            func_800235D8();
        }
        func_80023930((Struct_8002373C*)D_8007AA20);
        n = D_8007B900;
        e = D_8007B908;
        while (n != 0) {
            if (e->unk7C != -1) {
                func_80023930((Struct_8002373C*)e->unk2C);
                n--;
            }
            e++;
        }
    } else if (!(D_8004DCA0 & 0x87) && !(D_8007AA80 & 1)) {
        if (D_8007A9C0) {
            func_800230A8();
        } else if (D_8007A9C4 && !(D_8004DCA0 & 8)) {
            func_800231C4();
        } else if (D_8007A9C8) {
            func_800232A8();
        } else if (D_8007A9CC) {
            func_8002338C();
        }
    }
    if (D_8004DCA0 & 4) {
        func_80021C04(buf, (struct Struct_80021C04*)&D_8007AA08);
    } else if (D_8004DCA0 & 8) {
        func_80022970(buf, (struct Struct_80022970*)&D_8007AA08);
    }
    if (D_8008C15E) {
        func_80022658(&D_8007AA08);
        D_8008C15E--;
    }
}

typedef struct {
    /* 0x0 */ char unk0[4];
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 unk8;
    /* 0xA */ u16 unkA;
} Struct_80021030_64;

typedef struct Struct_80021030 {
    /* 0x00 */ char unk0[0x64];
    /* 0x64 */ Struct_80021030_64* unk64;
} Struct_80021030;

extern u16 D_8008C152;
extern u16 D_8008C154;
extern u16 D_8008C156;
extern u16 D_8008C158;
extern Struct_80024A54 D_803A86F8;
void func_80024974(u16 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80021030(Struct_80021030* arg0) {
    Struct_80021030_64* st;
    s32 w;
    s32 d;

    D_8008C174 = 0x1C;
    D_8008C178 = 0x18;
    if (D_8008C154 != 0) {
        w = D_8008C152 * D_8008C152;
        D_8008C174 -= w * 150 / 144;
    }
    st = arg0->unk64;
    func_80024EB0(&D_803A86F8, 0, 1, 0x3E, 0x11, 0x20, 0x27, 0x400, 0x400);
    func_80024EB0(&D_803A86F8, 0, 0x12, 0x3E, 0x12, 0x20, 0x38, 0x400, 0x400);
    w = st->unk4 * 56 / st->unk6;
    d = w - D_8008C156;
    if (d >= 2 || d < -1) {
        D_8008C156 += d >> 1;
    } else {
        D_8008C156 = w;
    }
    if (D_8008C156) {
        func_80024EB0(&D_803A86F8, 3, 0xB, D_8008C156, 5, 0x5E, 0x27, 0x400, 0x400);
    }
    w = st->unk8 * 56 / st->unkA;
    d = w - D_8008C158;
    if (d >= 2 || d < -1) {
        D_8008C158 += d >> 1;
    } else {
        D_8008C158 = w;
    }
    if (D_8008C158) {
        func_80024EB0(&D_803A86F8, 3, 0x15, D_8008C158, 5, 0x5E, 0x2C, 0x400, 0x400);
    }
    func_80024A54(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    func_80024974(3, 0xC, 0, st->unk4);
    func_80024974(1, 0x36, 0, st->unk6);
    func_80024974(3, 0xC, 0x1B, st->unk8);
    func_80024974(1, 0x36, 0x1B, st->unkA);
    func_80024D40(0x2F, 0, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
    func_80024D40(0x2F, 0x1B, 8, 0xA, 0x70, 0x1D, 0x400, 0x400);
}

extern s32 D_8004F2F4[];
extern Gfx D_803AA3C8[];
extern u8 D_8004F2CC[][4];
extern Gfx D_803AA2F8[];
extern u32 D_8008C13C;
extern u16 D_8008C180;

void func_800213A8(Unk2000000* buf, s32 arg1) {
    s32 x;
    f32 fx;
    f32 fy;
    s32 i;
    u8* p;
    u8* col;
    u16 *angle = &D_8008C180;

    D_8008C174 = 0x1C;
    D_8008C178 = 0xC6;
    if (D_8008C154 != 0) {
        i = D_8008C152 * D_8008C152;
        D_8008C174 -= i * 200 / 144;
    }
    func_80024EB0(&D_803A86F8, 0, 0, 0xC, 0xC, 0x20, 0x10, 0x400, 0x400);
    func_80024EB0(&D_803A86F8, 0x16, 0, 0xC, 0xC, 0x2C, 0x10, 0x400, 0x400);
    func_80024EB0(&D_803A86F8, 0x2C, 0, 0xC, 0xC, 0x38, 0x10, 0x400, 0x400);
    func_80024EB0(&D_803A86F8, 0x42, 0, 0xC, 0xC, 0x44, 0x10, 0x400, 0x400);
    func_80024A54(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    x = 6;
    for (i = 0, p = (u8*)arg1; i < 4; i++) {
        func_80024974(1, x, 6, p[0x24]);
        p++;
        x += 0x16;
    }
    for (i = 0; i < 4; i++) {
        if (((s32*)&D_8007AA08)[2] & D_8004F2F4[i]) {
            col = &D_8004F2CC[0][i];
            fx = i * 22.0f + 5.0 + (f32)D_8008C174;
            fy = D_8008C178 + 5.0f;
            guTranslate(&buf->unkC0[D_8007A180], fx, fy, 0.0f);
            gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gDPPipeSync(D_8007A184++);
            gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], (sins(*angle) >> 10) + 0x88);
            gSPDisplayList(D_8007A184++, D_803AA3C8);
        }
    }
    *angle += 0x444;
    if (D_8008C138) {
        col = D_8004F2CC[D_8008C13C];
        fx = D_8008C13C * 22.0f + 5.0 + (f32)D_8008C174;
            fy = D_8008C178 + 5.0f;
            guTranslate(&buf->unkC0[D_8007A180], fx, fy, 0.0f);
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, col[0], col[1], col[2], D_8008C138 * 255 / 30);
        gSPDisplayList(D_8007A184++, D_803AA2F8);
        D_8008C138--;
    }
}


extern f32 D_80085E74;
extern f32 D_8008FB48;
extern f32 D_8008FB4C;
extern s32 D_8008FB50;
extern s32 D_8008FB54;
extern Gfx D_803AA758[];
extern Struct_80024A54 D_803A86F8;
f32 sqrtf(f32);
f32 func_800270D0(f32, f32);
void func_800271B4(f32, Vec3f_216E0*);
void func_80027430(f32 (*)[4], f32, f32, f32);

void func_80021920(Unk2000000* buf) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ang;
    f32 mf[4][4];

    D_8008C174 = 0x104;
    D_8008C178 = 0x18;
    func_80027430(mf, 0.0f, 0.0f, D_80085E74);
    mf[3][0] = D_8008C174 + 17;
    mf[3][1] = D_8008C178 + 17;
    mf[3][2] = 0.0f;
    guMtxF2L(mf, &buf->unkC0[D_8007A180]);
    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(D_8007A184++, D_803AA758);
    func_80024EB0(&D_803A86F8, 13, 10, 11, 14, 0x93, 0, 0x400, 0x400);
    if (D_8008FB50 < 6 && D_8008FB54 < 0 && !(D_8004DCA0 & 0x80)) {
        dx = D_8008FB48 - D_8007AA08.unk18;
        dz = D_8008FB4C - D_8007AA08.unk20;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist > 10.0) {
            ang = func_800270D0(dx, dz) - D_80085E74;
            if (ang < -3.141592653589793) {
                ang += 6.283185307179586;
            } else if (ang > 3.141592653589793) {
                ang -= 6.283185307179586;
            }
            D_8008C140.x = 0.0f;
            D_8008C140.y = 18.0f;
            func_800271B4(ang, &D_8008C140);
            func_80024EB0(&D_803A86F8, D_8008C140.x + 14.0f, D_8008C140.y + 13.0f, 8, 8, 0, 0x32, 0x400, 0x400);
        }
    }
}

extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A8718;

typedef struct {
    /* 0x0 */ char unk0[8];
    /* 0x8 */ u16 unk8;
} Struct_80021C04_14;

typedef struct Struct_80021C04 {
    /* 0x000 */ char unk0[0x14];
    /* 0x014 */ Struct_80021C04_14* unk14;
    /* 0x018 */ char unk18[0x11D - 0x18];
    /* 0x11D */ u8 unk11D[3];
    /* 0x120 */ u16 unk120;
} Struct_80021C04;

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
} Struct_8004F324;

void func_800245D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
extern Struct_8004F324 D_8004F304[];
extern u8 D_8004F2CC[][4];
extern Gfx D_803AA2F8[];

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021C04.s")

typedef struct {
    /* 0x000 */ char unk0[0x122];
    /* 0x122 */ u16 unk122;
} Struct_80022658;

extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A8718;

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022658.s")

typedef struct {
    /* 0x00 */ char unk0[0x24];
    /* 0x24 */ u8 unk24[4];
} Struct_80022970_14;

typedef struct Struct_80022970 {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ char unkC[0x14 - 0xC];
    /* 0x14 */ Struct_80022970_14* unk14;
} Struct_80022970;


extern u8 D_8004F2CC[][4];
extern Struct_8004F324 D_8004F324[];
extern s32 D_8004F344[];
extern u8 D_8007A9F4;
extern u8 D_8007A9F5;
extern u8 D_8007A9F6;
extern u8 D_8007A9F7;
extern u32 D_8008C13C;
extern u16 D_8008C160;
extern u16 D_80092C86;
extern u8 D_8039ADB0[];
extern Gfx D_803AA2F8[];
void func_8002A7C8(s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022970.s")

extern u16 D_8008C040;

typedef struct {
    /* 0x00 */ char unk0[0x14];
    /* 0x14 */ Vec3f_216E0 unk14;
    /* 0x20 */ char unk20[0x84 - 0x20];
} Struct_8007ABF0;

extern s32 D_8007A9C0;
extern Struct_8007ABF0 D_8007ABF0[];
extern s32 D_8008C17C;

void func_800230A8(void) {
    s32 sx;
    s32 bob;
    Vec3f_216E0* p;
    u16 *angle = &D_8008C040;

    p = &D_8007ABF0[D_8007A9C0 - 1].unk14;
    if (func_80027FFC(p->x, p->y + 14.0, p->z, &sx, &D_8008C17C)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA448);
        func_80024D40(sx, D_8008C17C - bob - 30, 0x40, 29, 0, 0, 0x400, 0x400);
    } else {
        D_8008C17C = 0xF0;
    }
}

void func_800231C4(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &D_8008C050;

    if (func_80027FFC(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA538);
        func_80024D40(sx, sy - bob - 30, 24, 30, 0, 0, 0x400, 0x400);
    }
}

void func_800232A8(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &D_8008C14C[0];

    if (func_80027FFC(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x600;
        gSPDisplayList(D_8007A184++, D_803AA4C0);
        func_80024D40(sx, sy - bob - 30, 0x10, 30, 0, 0, 0x400, 0x400);
    }
}

void func_8002338C(void) {
    s32 sx;
    s32 sy;
    s32 bob;
    u16 *angle = &D_8008C14C[1];

    if (func_80027FFC(D_8007AA08.unk18, D_8007AA08.unk1C + 11.0, D_8007AA08.unk20, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(D_8007A184++, D_803AA448);
        func_80024D40(sx, sy - bob - 30, 0x40, 29, 0, 0, 0x400, 0x400);
    }
}

extern u16 D_8008C150;

extern Gfx D_803AA5B0[];

void func_80023470(u16 arg0) {
    s32 sx;
    s32 sy;
    s32 bob;
    f32 y;
    Struct_8002373C* a;
    u16 *angle = &D_8008C150;

    a = (Struct_8002373C*)D_8007B908[arg0].unk2C;
    if (a->unk64->unk0 == 1) {
        y = a->unk68->unk94;
    } else if (a->unk64->unk0 == 2) {
        y = a->unk4 + 350.0 * a->unk24;
    } else {
        y = a->unk4 + a->unk64->unk1C * a->unk24;
    }
    if (func_80027FFC(a->unk0, y, a->unk8, &sx, &sy)) {
        bob = sins(*angle) >> 13;
        if (bob < 0) {
            bob = -bob;
        }
        *angle += 0x800;
        gSPDisplayList(D_8007A184++, D_803AA5B0);
        func_80024D40(sx - 4, sy - bob - 42, 24, 42, 0, 0, 0x400, 0x400);
    }
}

void func_800235D8(void) {
    s32 sx;
    s32 sy;
    f32 y;
    f32 h;

    h = D_8007AA08.unk7C->unk1C * D_8007AA08.unk3C;
    y = D_8007AA08.unk1C + h;
    if (func_80027FFC(D_8007AA08.unk18, y, D_8007AA08.unk20, &sx, &sy) != 0) {
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
        func_80024EB0(D_803A8728, sx - 0x17, sy - 0xF, 0x2E, 0xF, 0x51, 0x31, 0x400, 0x400);
    }
}

void func_8002373C(Struct_8002373C* arg0, u16 mask, u16 idx, s16 val) {
    Struct_8002373C_68* s = arg0->unk68;
    u32 i;
    Struct_803AA6C4* e;
    f32 y;
    Struct_803AA690* fx;

    for (i = 0; i < 7; i++) {
        if (D_8004F2DC[i] & mask) {
            s->unk12[i] = idx;
            s->unk22[i] = val;
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((D_8004F2EC[i] & mask) && s->unk44[i] == 0) {
            s->unk32[i] = val;
            e = &D_803AA6C4[idx];
            D_8008C140.x = e->unk8;
            D_8008C140.y = e->unkC;
            D_8008C140.z = 1.0f;
            fx = &D_803AA690[e->unk0];
            if (arg0->unk64->unk0 == 1) {
                if (e->unk4 & 0x100) {
                    y = arg0->unk68->unk94;
                } else {
                    y = arg0->unk68->unk94 - arg0->unk64->unk18 * arg0->unk24;
                }
            } else if (e->unk4 & 0x100) {
                y = arg0->unk4 + arg0->unk64->unk1C * 0.5 * arg0->unk24;
            } else {
                y = arg0->unk4;
            }
            s->unk44[i] = func_80019820(e->unk2, e->unk4, arg0->unk0, y, arg0->unk8, 0.0f, fx, &D_8008C140, arg0);
            return;
        }
    }
}

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
} Struct_803AA628;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x8 - 0x2];
    /* 0x08 */ u16 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Struct_80023930_fx;

extern Struct_803AA628 D_803AA628[];

void func_80023930(Struct_8002373C* arg0) {
    Struct_8002373C_68* s = arg0->unk68;
    f32 y;
    s32 vis;
    s32 sx;
    s32 sy;
    s32 pad1;
    s32 pad2;
    s16 u;
    s16 v;
    s32 ox;
    s32 oy;
    u32 i;
    Struct_803AA628* e;
    s32 w;
    s32 h;
    Struct_80023930_fx* fx;

    if (!(D_8004DCA0 & 0x800)) {
        if (arg0->unk64->unk0 == 1) {
            y = arg0->unk68->unk94;
        } else {
            y = arg0->unk4 + arg0->unk64->unk1C * arg0->unk24;
        }
        pad1 = pad2 = 0;
    vis = func_80027FFC(arg0->unk0, y, arg0->unk8, &sx, &sy);
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
        oy = 0;
        ox = 0;
        for (i = 0; i < 7; i++) {
            if (s->unk12[i] != 0) {
                e = &D_803AA628[s->unk12[i]];
                u = e->unk0;
                v = e->unk2;
                w = e->unk4;
                h = e->unk6;
                if (vis) {
                    func_80024EB0(D_803A8728, sx + ox - (w >> 1), sy + oy - (h >> 1), w, h, u, v, 0x400, 0x400);
                }
                if (!(D_8004F2DC[i] & s->unk0)) {
                    s->unk12[i] = 0;
                } else if (s->unk22[i] > 0) {
                    if (--s->unk22[i] == 0) {
                        s->unk12[i] = 0;
                    }
                }
                ox += w >> 1;
                oy -= h >> 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->unk44[i] != 0) {
            fx = (Struct_80023930_fx*)arg0->unk68->unk44[i];
            fx->unkC = arg0->unk0;
            fx->unk14 = arg0->unk8;
            if (arg0->unk64->unk0 == 1) {
                if (fx->unk8 & 0x100) {
                    fx->unk10 = arg0->unk68->unk94;
                } else {
                    fx->unk10 = arg0->unk68->unk94 - arg0->unk64->unk18 * arg0->unk24;
                }
            } else if (fx->unk8 & 0x100) {
                fx->unk10 = arg0->unk4 + arg0->unk64->unk1C * 0.5 * arg0->unk24;
            } else {
                fx->unk10 = arg0->unk4;
            }
            if (!(D_8004F2EC[i] & s->unk0)) {
                s->unk44[i] = 0;
                if (fx->unk8 & 1) {
                    fx->unk8 &= ~1;
                    fx->unk0 = 8;
                }
            } else if (s->unk32[i] > 0) {
                if (--s->unk32[i] == 0) {
                    s->unk44[i] = 0;
                    if (fx->unk8 & 1) {
                        fx->unk8 &= ~1;
                        fx->unk0 = 8;
                    }
                }
            }
        }
    }
}

void func_80023D28(Struct_8002373C* arg0) {
    Struct_8002373C_68* s = arg0->unk68;
    u32 i;
    Struct_80023930_fx* fx;

    for (i = 0; i < 7; i++) {
        if (s->unk12[i] != 0) {
            s->unk12[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (s->unk44[i] != 0) {
            fx = (Struct_80023930_fx*)s->unk44[i];
            fx->unk0 = 8;
            fx->unk8 &= ~1;
            s->unk44[i] = 0;
        }
    }
}

void func_80023DEC(void) {
}

void func_80023DF4(void) {
}

void func_80023DFC(void) {
}

void func_80023E04(void) {
}

void func_80023E0C(void) {
}

typedef struct {
    /* 0x00 */ char unk0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[2];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ char unk8[4];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ char unk10[0x26 - 0x10];
    /* 0x26 */ u16 unk26;
    /* 0x28 */ char unk28[2];
    /* 0x2A */ u16 unk2A;
} Struct_8007C028_28;

typedef struct {
    /* 0x00 */ char unk0[0x28];
    /* 0x28 */ Struct_8007C028_28* unk28;
    /* 0x2C */ char unk2C[0x98 - 0x2C];
    /* 0x98 */ u16 unk98;
} Struct_8007C028;

extern Struct_8007C028* D_8007C028;
extern u8** D_8007C04C;
extern u8 D_8039ADB0[];
extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A86F8;
extern Struct_80024A54 D_803A8718;
void func_80024974(u16 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80023E14(void) {
    s32 d;

    D_8008C174 = 0xB5;
    D_8008C178 = 0x1A;
    d = D_8008C162 - 50;
    if (d > 0) {
        d *= d;
        D_8008C174 += d * 120 / 100;
    }
    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039EC90);
    if (D_8007C028->unk98 & 0x80) {
        func_80024EB0(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        func_80024EB0(&D_803A8718, 0, 0x10, 0x6E, 0x10, 0x64, 0x2C, 0x400, 0x400);
        func_80024EB0(&D_803A8718, 0, 0x20, 0x6E, 0x10, 0x64, 0x3C, 0x400, 0x400);
        func_80024EB0(&D_803A8718, 0, 0x30, 0x6E, 4, 0x64, 0x4C, 0x400, 0x400);
    } else {
        func_80024EB0(&D_803A8718, 0, 0, 0x6E, 0x10, 0x64, 0x1C, 0x400, 0x400);
        func_80024EB0(&D_803A8718, 0, 0x10, 0x6E, 0xA, 0x64, 0x2C, 0x400, 0x400);
        func_80024EB0(&D_803A8718, 0, 0x1A, 0x6E, 2, 0x64, 0x4E, 0x400, 0x400);
    }
    func_80024694(4, 0x11, 0, D_8007C04C[D_8007C028->unk28->unk2]);
    func_80024A54(&D_803A86F8, 0x20, 0x1D, 0x80, 0xA);
    gDPLoadTLUT_pal256(D_8007A184++, D_8039ADB0);
    if (D_8007C028->unk98 & 0x80) {
        func_80024974(3, 0x10, 0x1C, D_8007C028->unk28->unk6);
        func_80024974(3, 0x10, 0x26, D_8007C028->unk28->unkE);
        func_80024974(3, 0x46, 0x1C, D_8007C028->unk28->unk2A);
        func_80024974(3, 0x46, 0x26, D_8007C028->unk28->unkC);
        if (D_8007C028->unk28->unk26 != 4) {
            func_80024EB0(&D_803A86F8, 0x5B, 3, 0xC, 0xC, D_8007C028->unk28->unk26 * 0xC + 0x20, 0x10, 0x400, 0x400);
        }
    }
}

void func_8002430C(void) {
    Struct_8008C058* p = D_8008C058;
    s32 i = 8;

    while (i > 0) {
        p->unk0 = 0;
        p++;
        i--;
    }
}

void func_8002433C(Struct_8002433C_arg* arg0) {
    Struct_8008C058* p = D_8008C058;
    s32 i = 7;

    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unk0 = 0x2D;
    p->unk4 = arg0;
    p->unk10 = 0.0f;
    p->unk8 = 0.0f;
    if (*arg0->unk64 == 0) {
        p->unkC = ((Struct_80024338_64*) arg0->unk64)->unk1C * arg0->unk24;
    } else if (*arg0->unk64 == 1) {
        p->unkC = arg0->unk68->unk94 - arg0->unk4;
    } else {
        p->unkC = arg0->unk24 * 600.0;
    }
    p->unk14 = 0x23;
    p->unk16 = 0x31;
    p->unk18 = 0x29;
    p->unk1A = 0xE;
}

void func_8002440C(void) {
    s32 i;
    Struct_8008C058* p;
    f32 x;
    f32 y;
    s32 sx;
    s32 sy;
    f32 z;

    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_803A4118);
    p = D_8008C058;
    i = 8;
    do {
        if (p->unk0 != 0) {
            x = p->unk8;
            y = p->unkC;
            z = p->unk10;
            if (p->unk4 != NULL) {
                x += ((Vec3f_216E0*) p->unk4)->x;
                y += ((Vec3f_216E0*) p->unk4)->y;
                z += ((Vec3f_216E0*) p->unk4)->z;
            }
            func_80027FFC(x, y, z, &sx, &sy);
            func_80024EB0(D_803A8728, sx - (p->unk18 >> 1), sy - p->unk1A, p->unk18, p->unk1A, p->unk14, p->unk16, 0x400, 0x400);
            p->unk0--;
        }
        i--;
        p++;
    } while (i != 0);
}

void func_800245D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    u32 id;
    s32 w;
    u8 flags;
    u8* str;
    u32 tmp;

    id = func_800167B0(arg3, arg2);
    flags = func_800168F0(id, arg4);
    tmp = (id >> 8) & 0xF;
    id &= 0xFF;
    str = D_800C03D8[tmp][id];
    if (flags & 4) {
        str = D_8004F2C4;
    }
    w = func_80024904(str);
    arg0 = arg0 - w / 2 + 0x37;
    func_80024694(arg0, arg1, D_8004F498[flags], str);
}

void func_80024694(s32 x, s32 y, s32 pal, u8* str) {
    s32 cur = 8;
    s32 col;
    s32 row;

    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_803A8778[pal]);
    while (*str != 0xFF) {
        if (*str == 0x80) {
            func_80024D40(x - 2, y - 1, 8, 9, 0x78, row, 0x400, 0x400);
            x += 1;
        } else if (*str == 0x81) {
            func_80024D40(x - 2, y - 1, 8, 9, 0x80, row, 0x400, 0x400);
            x += 1;
        } else if (*str == 0x82) {
            x += 4;
        } else {
            col = (*str & 0xF) * 8;
            row = (*str & 0x70) >> 4;
            if (row != cur) {
                func_80024A54(&D_803A8748, 0, row * 9, 0xA0, 9);
                cur = row;
            }
            row *= 9;
            func_80024D40(x, y, 8, 9, col, row, 0x400, 0x400);
            x += 8;
        }
        str++;
    }
}

s32 func_80024904(u8* str) {
    s32 w = 0;

    while (*str != 0xFF) {
        if (!(*str & 0x80)) {
            w += 8;
        } else if (*str == 0x80 || *str == 0x81) {
            w += 1;
        } else if (*str == 0x82) {
            w += 4;
        }
        str++;
    }
    return w;
}

void func_80024974(u16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    u8* p;
    u8 buf[8];

    p = buf;
    for (n = func_800281F0(arg3, buf, arg0); n != 0; n--) {
        if (*p != 0x20) {
            func_80024D40(arg1, arg2, 8, 0xA, *p * 8 + 0x20, 0x1D, 0x400, 0x400);
            arg1 += 7;
        } else if (arg0 & 6) {
            arg1 += 7;
        }
        p++;
    }
}

void func_80024A4C(void) {
}

void func_80024A54(Struct_80024A54* tex, s32 x, s32 y, s32 w, s32 h) {
    if (tex->is4b == 0) {
        gDPLoadTextureTile(D_8007A184++, tex->img, G_IM_FMT_CI, G_IM_SIZ_8b, tex->width, 0, x, y, x + w, y + h, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    } else {
        gDPLoadTextureTile_4b(D_8007A184++, tex->img, G_IM_FMT_CI, tex->width, 0, x, y, x + w - 1, y + h - 1, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
    }
}

void func_80024D40(s32 x, s32 y, s32 x2, s32 y2, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    x += D_8008C174;
    x2 += x;
    y += D_8008C178;
    if (x2 < D_8008C044) {
        return;
    }
    y2 += y;
    if (y2 < D_8008C048) {
        return;
    }
    if (D_8008C04C < x) {
        return;
    }
    if (D_8008C054 < y) {
        return;
    }
    if (D_8008C04C < x2) {
        x2 = D_8008C04C;
    }
    if (D_8008C054 < y2) {
        y2 = D_8008C054;
    }
    if (x < D_8008C044) {
        s = s - x + D_8008C044;
        x = D_8008C044;
    }
    if (y < D_8008C048) {
        t = t - y + D_8008C048;
        y = D_8008C048;
    }
    gSPTextureRectangle(D_8007A184++, x << 2, y << 2, x2 << 2, y2 << 2, 0, s << 5, t << 5, dsdx, dtdy);
}

void func_80024EB0(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_80024A54(arg0, arg5, arg6, arg3, arg4);
    func_80024D40(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/D_8006F530.s")
