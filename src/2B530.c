#include "common.h"

extern Gfx* D_8007A184;
extern u16 D_8008FB3C;
extern u16 D_8008FB3E;
extern u16 D_8008FB70;

void func_8002A930(void) {
    D_8008FB3E = 0x8000;
    D_8008FB70 = 0;
    D_8008FB3C = 0;
}

void func_8002A954(void) {
    D_8008FB3E = (D_8008FB3E & 3) | 0x8000;
    D_8008FB70 = 0;
    D_8008FB3C = 0;
}

extern Gfx* D_8007A184;
extern Gfx D_80061770[];
extern u16 D_8007A170;
extern s8 D_8008FB40;
extern s32 D_8008FB44;
extern u16 D_80092C86;
void func_8002A7C8(u8 arg0, s8 arg1, u8 arg2);

void func_8002AC1C(void);
void func_8002AE58(s32);
void func_8002B844(s32);
void func_8002C598(s32);
void func_8002D7CC(s32);
void func_8002E9DC();
void func_8002FA6C(void);

void func_8002A984(s32 arg0) {
    gSPDisplayList(D_8007A184++, D_80061770);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    func_8002E9DC();
    D_8008FB44++;
    if (D_8008FB3E & 0x4000) {
        func_8002FA6C();
    } else if (D_8008FB3E & 0x2000) {
        func_8002AC1C();
    } else {
        switch ((u16)(D_8008FB3E & 3)) {
            case 0:
                func_8002AE58(0);
                break;
            case 1:
                func_8002C598(0);
                break;
            case 2:
                func_8002D7CC(0);
                break;
            case 3:
                func_8002B844(0);
                break;
        }
    }
    D_8008FB3E &= ~0x10;
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
    gDPSetBlendColor(D_8007A184++, 0, 0, 0, 1);
    if ((D_80092C86 & 0x5000) && !(D_8008FB3E & 0x6020)) {
        D_8008FB3E &= 0x7FFF;
        func_8002A7C8(0, 1, 0xFF);
    }
    if (!(D_8008FB3E & 0x8000)) {
        if (D_8008FB3E & 0x4000) {
            switch ((u16)(D_8008FB3E & 0xC)) {
                case 0:
                    if (D_8008FB70 & 0x80) {
                        D_8007A170 = 1;
                        D_8008FB40 = 1;
                    } else {
                        D_8007A170 = 3;
                        D_8008FB40 = 0;
                    }
                    break;
                case 8:
                    D_8007A170 = 3;
                    break;
                case 4:
                    D_8007A170 = 1;
                    break;
            }
        } else {
            D_8007A170 = 1;
        }
        func_8002A954();
    }
}

extern s32 D_8008FB30;
extern s32 D_8008FB34;
extern s32 D_8008FB38;
void func_8002AE58(s32);
void func_8002B844(s32);
void func_8002C598(s32);
void func_8002D7CC(s32);

void func_8002AC1C(void) {
    s32 mode;
    s32 dir = 0;
    s32 d;
    s32 a;
    s32 b;

    d = D_8008FB38 * D_8008FB38 * 0.3125;
    if (D_8008FB3E & 0x1000) {
        D_8008FB30 = 0x140 - d;
        D_8008FB34 = -d;
        a = D_8008FB30;
        b = D_8008FB34;
        if (D_8008FB38 == 0) {
            dir = -1;
        }
    } else {
        D_8008FB30 = d;
        D_8008FB34 = d - 0x140;
        a = D_8008FB34;
        b = D_8008FB30;
        if (D_8008FB38 == 0) {
            dir = 1;
        }
    }
    D_8008FB38--;
    mode = D_8008FB3E & 3;
    switch (mode) {
        case 0:
            func_8002AE58(a);
            if (D_8008FB3E & 0x1000) {
                func_8002B844(b);
            } else {
                func_8002C598(b);
            }
            break;
        case 1:
            func_8002C598(a);
            if (D_8008FB3E & 0x1000) {
                func_8002AE58(b);
            } else {
                func_8002D7CC(b);
            }
            break;
        case 2:
            func_8002D7CC(a);
            if (D_8008FB3E & 0x1000) {
                func_8002C598(b);
            } else {
                func_8002B844(b);
            }
            break;
        case 3:
            func_8002B844(a);
            if (D_8008FB3E & 0x1000) {
                func_8002D7CC(b);
            } else {
                func_8002AE58(b);
            }
            break;
    }
    if (dir != 0) {
        D_8008FB3E &= ~0x2000;
        D_8008FB3E &= ~0x1000;
        mode += dir;
        D_8008FB3E &= ~3;
        D_8008FB3E |= mode & 3;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002AE58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002B844.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002C598.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002D7CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002DECC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002E42C.s")

typedef struct {
    s32 v[4];
} Unk4Words;
typedef struct {
    u8* v[4];
} Unk4Ptrs;
extern Unk4Words D_80061614;
extern Unk4Words D_80061624;
extern Unk4Ptrs D_80061634;
extern u16 D_80066E88[];

void func_8002E9DC(void) {
    s32 i;
    s32 y;
    Unk4Words texH = D_80061614;
    Unk4Words stripH = D_80061624;
    Unk4Ptrs tex = D_80061634;

    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_80066E88);
    D_8008FB3E &= ~0x10;
    for (i = 0, y = 22; i < 4; i++) {
        gDPLoadTextureTile(D_8007A184++, tex.v[i], G_IM_FMT_CI, G_IM_SIZ_8b, 64, texH.v[i], 0, 0, 63, texH.v[i] - 1, 0,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(D_8007A184++, 23 << 2, y << 2, 297 << 2, (y + stripH.v[i]) << 2, G_TX_RENDERTILE, 0, 0,
                            0x4A8, 0x4E6);
        gDPPipeSync(D_8007A184++);
        y += stripH.v[i];
    }
    for (i = 3, y = 120; i >= 0; i--) {
        gDPLoadTextureTile(D_8007A184++, tex.v[i], G_IM_FMT_CI, G_IM_SIZ_8b, 64, texH.v[i], 0, 0, 63, texH.v[i] - 1, 0,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(D_8007A184++, 23 << 2, y << 2, 297 << 2, (y + stripH.v[i]) << 2, G_TX_RENDERTILE, 0,
                            (texH.v[i] - 1) << 5, 0x4A8, -0x4E6);
        gDPPipeSync(D_8007A184++);
        y += stripH.v[i];
    }
}

extern u8* D_80060D74[];
extern u16 D_80061E98[];

void func_8002EED8(s32 ndigits, s32 x, s32 y, u32 value, s32 pal) {
    s32 i;
    u64 div;
    s64 v;
    s8 digits[10];
    s32 xoff;
    s32 j;
    s32 n;

    div = 1000000000;
    v = value;
    xoff = 0;
    j = 9;
    if (ndigits >= 10) {
        ndigits = 9;
    }
    for (i = 0; i < 9; i++) {
        n = 0;
        while (TRUE) {
            v -= div;
            if (v < 0) {
                v += div;
                break;
            }
            n++;
        }
        digits[j--] = n;
        div /= 10;
    }
    digits[0] = v;
    i = 0;
    if (!(D_8008FB3E & 0x10)) {
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_80061E98);
        D_8008FB3E |= 0x10;
    }
    for (n = ndigits - 1; n >= 0; n--) {
        i += digits[n];
        if (i != 0 || n == 0) {
            gDPLoadTextureTile(D_8007A184++, D_80060D74[pal + digits[n]], G_IM_FMT_CI, G_IM_SIZ_8b, 8, 10, 0, 0, 7, 9,
                               0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(D_8007A184++, (x + xoff) << 2, y << 2, (x + xoff + 8) << 2, (y + 10) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            gDPPipeSync(D_8007A184++);
        }
        xoff += 7;
    }
}

void func_8002F2E4(s32 ndigits, s32 x, s32 y, u32 value, s32 pal) {
    s32 i;
    s32 n;
    u64 div;
    s64 v;
    s8 digits[10];
    s32 xoff;
    s32 j;

    div = 1000000000;
    v = value;
    xoff = 0;
    j = 9;
    if (ndigits >= 10) {
        ndigits = 9;
    }
    for (i = 0; i < 9; i++) {
        n = 0;
        while (TRUE) {
            v -= div;
            if (v < 0) {
                v += div;
                break;
            }
            n++;
        }
        digits[j--] = n;
        div /= 10;
    }
    digits[0] = v;
    if (!(D_8008FB3E & 0x10)) {
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_80061E98);
        D_8008FB3E |= 0x10;
    }
    for (n = ndigits - 1; n >= 0; n--) {
        gDPLoadTextureTile(D_8007A184++, D_80060D74[pal + digits[n]], G_IM_FMT_CI, G_IM_SIZ_8b, 8, 10, 0, 0, 7, 9,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, 4, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(D_8007A184++, (x + xoff) << 2, y << 2, (x + xoff + 8) << 2, (y + 10) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        gDPPipeSync(D_8007A184++);
        xoff += 7;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002F6D8.s")

typedef struct { s8 a; s8 b; } Unk80060F30;
extern Unk80060F30 D_80060F30[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern s32 D_8008FB50;
extern s32 D_8008FB54;
extern f32 D_80060F28;
extern f32 D_80060F2C;
extern s16 D_800614B4[];
extern s16 D_800614CC[];
extern f32 D_8008FB48;
extern f32 D_8008FB4C;

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002F87C.s")
