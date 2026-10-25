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
extern s16 D_8008C042;
extern s32 D_8008C044;
extern s32 D_8008C048;
extern s32 D_8008C04C;
extern u16 D_8008C050;
extern s32 D_8008C054;
extern s32 D_8008C138;
extern u16 D_8008C14C[2];
extern u16 D_8008C15A;
extern u16 D_8008C15C;
extern s16 D_8008C15E;
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

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80020B78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800213A8.s")

typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

extern s32 D_8004DCA0;
extern s32 D_8007A180;
extern Unk2000000 D_2000000;
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

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021C04.s")

typedef struct {
    /* 0x000 */ char unk0[0x122];
    /* 0x122 */ u16 unk122;
} Struct_80022658;

extern u8 D_8039EC90[];
extern Struct_80024A54 D_803A8718;

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800230A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800231C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800232A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_8002338C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023470.s")

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

extern s32 D_8004DCA0;
extern Struct_803AA628 D_803AA628[];

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023D28.s")

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
