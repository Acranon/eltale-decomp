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

extern u16 D_8007A9D4;
extern u16 D_8007A9D6;
extern u16 D_8007A9D8;
extern u16 D_8007A9DA;
extern u16 D_8007A9DC;
extern u16 D_8007A9DE;
extern u16 D_8007A9F8;
extern u16 D_8007A9FA;
extern u16 D_8007A9FC;
extern u16 D_8007A9FE;
extern u8 D_8007AA00;
extern u8 D_8007AA01;
extern u8 D_8007AA02;
extern u8 D_8007AA03;
extern s32 D_8007AA10;
extern u16 D_80055F0C[];
extern s8 D_80060D64[];
extern s32 D_8008FB38;
extern s32 D_8008FB44;
extern s8 D_80092C81;
extern u16 D_80092C84;
void func_8002A7C8(u8 arg0, s8 arg1, u8 arg2);
void func_8002DECC(s32 id, s32 x, s32 y, s32 w, s32 h);
void func_8002EED8(s32 ndigits, s32 x, s32 y, u32 value, s32 pal);

void func_8002AE58(s32 x) {
    s32 px;
    s32 i;
    f32 f;
    s32 pad[2]; // unused locals in the original (frame size)

    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, 255);
    func_8002DECC(0, x + 0x28, 0x1E, 0xF0, 0x98);
    func_8002DECC(0x37, x + 0x2B, 0xB7, 0xF0, 3);
    func_8002DECC(0x37, x + 0x119, 0x24, 2, 0x96);
    func_8002DECC(0x37, x + 0x27, 0x1D, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0xB6, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x1D, 1, 0x9A);
    func_8002DECC(0x37, x + 0x118, 0x1D, 1, 0x9A);
    func_8002DECC(0x38, x + 0x29, 0x1F, 0xED, 1);
    func_8002DECC(0x38, x + 0x29, 0x1F, 1, 0x95);
    func_8002DECC(0x39, x + 0x29, 0xB4, 0xEE, 1);
    func_8002DECC(0x39, x + 0x116, 0x1F, 1, 0x96);
    func_8002DECC(0x3C, x + 0x3A, 0x1E, 0x15, 0x98);
    px = 0x4B;
    for (i = 0; i < 3; i++, px += 0x21) {
        func_8002DECC(0x3D, x + 0x5D, px, 0xA7, 2);
    }
    px = 0x40;
    for (i = 0; i < 4; i++, px += 0x21) {
        func_8002DECC(0x32, x + 0x63, px, 0x3C, 7);
    }
    px = 0x3C;
    for (i = 0; i < 4; i++, px += 0x21) {
        func_8002DECC(0x20, x + 0xC3, px, 0x13, 11);
    }
    func_8002DECC(0x1B, x + 0x38, 0x34, 0x18, 0xE);
    func_8002DECC(0x1C, x + 0x37, 0x54, 0x1C, 0xD);
    func_8002DECC(0x1D, x + 0x35, 0x78, 0x24, 0xF);
    func_8002DECC(0x1E, x + 0x35, 0x99, 0x1C, 0xE);
    func_8002DECC(5, x + 0x45, 0x1C, 8, 8);
    func_8002DECC(5, x + 0xF3, 0x1C, 8, 8);
    i = D_8008FB44;
    i = (i >> 2) & 0xF;
    i = D_80060D64[i];
    func_8002DECC(6, x + i + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, x - i + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x14, x + 0x79, 0x35, 8, 0xA);
    func_8002DECC(0x14, x + 0x79, 0x56, 8, 0xA);
    i = D_8007A9D6;
    func_8002EED8(3, x + 0x80, 0x35, i, 0xA);
    i = D_8007A9DA;
    func_8002EED8(3, x + 0x80, 0x56, i, 0xA);
    i = D_8007A9D4;
    func_8002EED8(3, x + 0x64, 0x35, i, 0xA);
    i = D_8007A9D8;
    func_8002EED8(3, x + 0x64, 0x56, i, 0xA);
    i = D_8007A9DE;
    func_8002EED8(3, x + 0x80, 0x77, i, 0xA);
    i = D_8007A9DC;
    func_8002EED8(3, x + 0x80, 0x98, i, 0xA);
    i = D_80055F0C[D_8007AA00];
    func_8002EED8(3, x + 0xDA, 0x3B, D_8007A9F8 * 100 / i, 0xA);
    i = D_80055F0C[D_8007AA01];
    if (D_8007AA10 & 0x4000) {
        i = i * 3;
    } else {
        i = i * 4;
    }
    func_8002EED8(3, x + 0xDA, 0x5C, D_8007A9FA * 100 / i, 0xA);
    i = D_80055F0C[D_8007AA03];
    if (D_8007AA10 & 0x2000) {
        i = (f32) i * 0.8;
    }
    func_8002EED8(3, x + 0xDA, 0x7D, D_8007A9FE * 100 / i, 0xA);
    i = D_80055F0C[D_8007AA02];
    if (D_8007AA10 & 0x8000) {
        i = (f32) i * 0.8;
    }
    func_8002EED8(3, x + 0xDA, 0x9E, D_8007A9FC * 100 / i, 0xA);
    f = (u32)D_8007A9D4;
    f /= (u32)D_8007A9D6;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0x64, 0x41, f, 3);
    f = (u32)D_8007A9D8;
    f /= (u32)D_8007A9DA;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0x64, 0x62, f, 3);
    f = (u32)D_8007A9DE;
    f /= 255.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0x64, 0x83, f, 3);
    f = (u32)D_8007A9DC;
    f /= 255.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0x64, 0xA4, f, 3);
    func_8002DECC(0x15, x + 0xF6, 0x3B, 8, 0xA);
    func_8002DECC(0x15, x + 0xF6, 0x5C, 8, 0xA);
    func_8002DECC(0x15, x + 0xF6, 0x7D, 8, 0xA);
    func_8002DECC(0x15, x + 0xF6, 0x9E, 8, 0xA);
    func_8002DECC(0x1A, x + 0x77, 0x19, 0x52, 0xD);
    if (!(D_8008FB3E & 0x2000)) {
        if (D_80092C81 > 20 || (D_80092C84 & 0x10)) {
            D_8008FB3E |= 0x2000;
            D_8008FB38 = 31;
            func_8002A7C8(0, 0, 0xFF);
        } else if (D_80092C81 < -20 || (D_80092C84 & 0x2000)) {
            D_8008FB3E |= 0x3000;
            D_8008FB38 = 31;
            func_8002A7C8(0, 0, 0xFF);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002B844.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002C598.s")

extern s8 D_80060D64[];
extern u8 D_8007A9F4;
extern u8 D_8007A9F5;
extern u8 D_8007A9F6;
extern u8 D_8007A9F7;
extern s32 D_8007A9E0;
extern u8 D_8007AA04;
extern u32 D_80055D7C[];
extern s32 D_8008FB38;
extern s32 D_8008FB44;
extern s8 D_80092C81;
extern u16 D_80092C84;
void func_8002A7C8(u8 arg0, s8 arg1, u8 arg2);
void func_8002DECC(s32 id, s32 x, s32 y, s32 w, s32 h);
void func_8002E42C(s32 arg0, s32 arg1);
void func_8002EED8(s32 ndigits, s32 x, s32 y, u32 value, s32 pal);

void func_8002D7CC(s32 x) {
    s32 p;
    s32 v;
    f32 f;

    func_8002DECC(0, x + 0x28, 0x1E, 0xF0, 0x9F);
    func_8002DECC(0x37, x + 0x2B, 0xBE, 0xF0, 3);
    func_8002DECC(0x37, x + 0x119, 0x24, 2, 0x9A);
    func_8002DECC(0x37, x + 0x27, 0x1D, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0xBD, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x1E, 1, 0x9F);
    func_8002DECC(0x37, x + 0x118, 0x1E, 1, 0x9F);
    func_8002DECC(0x38, x + 0x29, 0x1F, 0xED, 1);
    func_8002DECC(0x38, x + 0x29, 0x20, 1, 0x9B);
    func_8002DECC(0x39, x + 0x29, 0xBB, 0xEE, 1);
    func_8002DECC(0x39, x + 0x116, 0x1F, 1, 0x9C);
    func_8002DECC(5, x + 0x45, 0x1C, 7, 7);
    func_8002DECC(5, x + 0xF3, 0x1C, 7, 7);
    p = D_8008FB44;
    p = (p >> 2) & 0xF;
    p = D_80060D64[p];
    func_8002DECC(6, x + p + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, x - p + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x2D, x + 0x75, 0x19, 0x56, 0xD);
    func_8002DECC(0x32, x + 0xA5, 0x35, 0x35, 6);
    func_8002DECC(0x32, x + 0x31, 0x78, 0x35, 6);
    func_8002DECC(0x32, x + 0xD9, 0x78, 0x35, 6);
    func_8002DECC(0x32, x + 0xA5, 0xAE, 0x35, 6);
    func_8002DECC(0x14, x + 0x86, 0x34, 8, 0xA);
    func_8002DECC(0x14, x + 0x47, 0x6B, 8, 0xA);
    func_8002DECC(0x14, x + 0xF0, 0x6B, 8, 0xA);
    func_8002DECC(0x14, x + 0x86, 0xAD, 8, 0xA);
    func_8002DECC(0x2E, x + 0x9A, 0x3D, 0xC, 0xC);
    func_8002DECC(0x2F, x + 0x67, 0x6F, 0xC, 0xC);
    func_8002DECC(0x30, x + 0xCC, 0x6F, 0xC, 0xC);
    func_8002DECC(0x31, x + 0x9A, 0xA1, 0xC, 0xC);
    func_8002DECC(0x15, x + 0xA7, 0x92, 8, 0xA);
    func_8002EED8(2, x + 0x8D, 0x34, 50, 0xA);
    func_8002EED8(2, x + 0x4E, 0x6B, 50, 0xA);
    func_8002EED8(2, x + 0xF7, 0x6B, 50, 0xA);
    func_8002EED8(2, x + 0x8D, 0xAD, 50, 0xA);
    p = D_8007A9F4;
    func_8002EED8(2, x + 0x78, 0x34, p, 0xA);
    p = D_8007A9F5;
    func_8002EED8(2, x + 0x39, 0x6B, p, 0xA);
    p = D_8007A9F7;
    func_8002EED8(2, x + 0xE2, 0x6B, p, 0xA);
    p = D_8007A9F6;
    func_8002EED8(2, x + 0x78, 0xAD, p, 0xA);
    f = (u32)D_8007A9F4;
    f /= 50.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0xA6, 0x36, f, 3);
    f = (u32)D_8007A9F5;
    f /= 50.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0x32, 0x79, f, 3);
    f = (u32)D_8007A9F7;
    f /= 50.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0xDA, 0x79, f, 3);
    f = (u32)D_8007A9F6;
    f /= 50.0f;
    f *= 50.0f;
    func_8002DECC(0x33, x + 0xA6, 0xAF, f, 3);
    v = D_8007A9E0 * 100 / D_80055D7C[D_8007AA04];
    if (v > 100) {
        v = 100;
    }
    func_8002EED8(3, x + 0x91, 0x92, v, 0xA);
    func_8002E42C(v, x);
    if (!(D_8008FB3E & 0x2000)) {
        if (D_80092C81 > 20 || (D_80092C84 & 0x10)) {
            D_8008FB3E |= 0x2000;
            D_8008FB38 = 31;
            func_8002A7C8(0, 0, 0xFF);
        } else if (D_80092C81 < -20 || (D_80092C84 & 0x2000)) {
            D_8008FB3E |= 0x3000;
            D_8008FB38 = 31;
            func_8002A7C8(0, 0, 0xFF);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002DECC.s")

typedef struct {
    u16* v[4];
} Unk4Pals;
typedef struct {
    u8* v[4][2];
} Unk4x2Ptrs;
extern Unk4Pals D_800615E4;
extern Unk4x2Ptrs D_800615F4;
extern Gfx D_80060ED8[];
extern Gfx D_80060EF0[];

void func_8002E42C(s32 arg0, s32 arg1) {
    s32 k;
    s32 j;
    s32 d;
    Unk4Pals pals = D_800615E4;
    Unk4x2Ptrs tex = D_800615F4;
    s32 xr;
    s32 x;
    s32 y;
    s32 w;
    s32 h = 0;
    s32 texW;
    s32 texH;
    s32 ult;
    s32 s[1];
    s32 t;
    s32 ret;

    for (k = 0; k < 4; k++) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
        gDPPipeSync(D_8007A184++);
        if (k != 1) {
            gSPDisplayList(D_8007A184++, D_80060ED8);
        } else {
            gSPDisplayList(D_8007A184++, D_80060EF0);
            gDPSetEnvColor(D_8007A184++, 255, 255, 255, 0x80);
        }
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, pals.v[k]);
        for (j = 0; j < 2; j++) {
            s[0] = 0;
            switch (k) {
                case 2:
                    x = arg1 + 0x87;
                    ult = 0x32 - arg0 / 2;
                    y = ult + 0x52;
                    w = 0x19;
                    h = 0x32;
                    texW = 0x19;
                    texH = 0x32;
                    t = ult << 5;
                    break;
                case 3:
                    ult = 0;
                    t = 0;
                    x = arg1 + 0x84;
                    y = 0x4F;
                    w = 0x1C;
                    h = 0x38;
                    texW = 0x1C;
                    texH = 0x38;
                    break;
                default:
                    ult = 0;
                    t = 0;
                    x = arg1 + 0x87;
                    y = 0x52;
                    w = 0x19;
                    h = 0x32;
                    texW = 0x19;
                    texH = 0x32;
                    break;
            }
            x += w * j;
            if (x < 0 && x + w >= 0) {
                d = -x;
                x = 0;
                w -= d;
                s[0] = d << 5;
            }
            if (x > 320) {
                ret = -1;
            } else {
                ret = 0;
                xr = x + w;
                if (xr > 320) {
                    w = w - xr + 320;
                }
            }
            if (w <= 0) {
                ret = -1;
            }
            if (ret >= 0) {
                gDPLoadTextureTile(D_8007A184++, tex.v[k][j], G_IM_FMT_CI, G_IM_SIZ_8b, texW, texH, 0, ult, texW - 1,
                                   texH - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h - ult) << 2, G_TX_RENDERTILE, s[0],
                                    t, 1 << 10, 1 << 10);
                gDPPipeSync(D_8007A184++);
            }
        }
    }
    D_8008FB3E &= ~0x10;
}

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

void func_8002F87C(void) {
    s32 cnt = 0;
    s32 i;
    s32 count = 0;
    s32 sub = -1;
    f32 x;

    s32 idx;
    f32 y;

    for (i = 0; D_80060F30[i].a != -8; i++) {
        switch (D_80060F30[i].a) {
            case -2:
                i++;
                sub++;
                break;
            case -1:
                i++;
                count++;
                sub = -1;
                break;
        }
        if (D_80060F30[i].a == D_800842BC && D_80060F30[i].b == D_800842C0) {
            break;
        }
    }
    D_8008FB50 = count;
    D_8008FB54 = sub;
    cnt = D_8008FB50;
    if (cnt < 6 && D_8008FB54 < 0) { idx = cnt; if (D_80060F28 == -1.0f) { D_80060F28 = 115.0f;
            D_80060F2C = 86.0f;
        }
        x = D_80060F28 - D_800614CC[idx];
        y = D_80060F2C;
        y = y - D_800614CC[idx + 6];
        D_8008FB48 = D_800614B4[idx] * x;
        D_8008FB4C = D_800614B4[idx + 6] * y;
    }
}
