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
void func_80024A54(void*, s32, s32, s32, s32);
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
extern s16 D_8008C15A;
extern u16 D_8008C15C;
extern s16 D_8008C15E;
extern s16 D_8008C162;
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
extern u8 D_803A8748[];

void func_80024EB0(void*, s32, s32, s32, s32, s32, s32, s32, s32);

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

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021C04.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_8002373C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023E14.s")

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
                func_80024A54(D_803A8748, 0, row * 9, 0xA0, 9);
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

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80024A54.s")

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
