#include "common.h"

/* .bss 8008FB30..8008FB70 */
s32 D_8008FB30;
s32 D_8008FB34;
s32 D_8008FB38;
u16 D_8008FB3C;
u16 D_8008FB3E;
s8 D_8008FB40;
s32 D_8008FB44;
f32 D_8008FB48;
f32 D_8008FB4C;
s32 D_8008FB50;
s32 D_8008FB54;
#ifndef NON_MATCHING /* a function static in the NON_MATCHING C */
s32 D_8008FB58; /* only func_8002B844 (asm) uses it */
#endif
f32 D_8008FB5C; /* only func_8002C598 (asm) uses these two */
f32 D_8008FB60;

extern Gfx* D_8007A184;
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

#ifdef NON_MATCHING
/* context for the NON_MATCHING func_8002B844 and func_8002C598 (their data is defined below) */
typedef struct { void *dst; u32 start; u32 end; } D2DstRom;
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08_2B530;
extern Unk8007AA08_2B530 D_8007AA08;
extern s8 D_80060CB0;
extern s8 D_800616B0;
extern s8 D_80092C82;
extern s16 D_800615AC[][2];
extern s16 D_800615CC[][2];
extern f32 D_80060F28;
extern f32 D_80060F2C;
extern s16 D_80061184[];
extern void *D_8006125C[];
extern void *D_80061274[];
extern s16 D_800614B4[];
extern s16 D_800614CC[];
extern D2DstRom D_800614E4[];
extern void *D_8006155C[];
extern void *D_8006156C[];
extern u8 D_8006158C[][3];
extern s16 D_80061598[];
void func_80028120(u32, void *, s32);
void func_800324F4(void);
#endif

#ifdef NON_MATCHING
/* stack homes and register allocation differ; code is equivalent */
void func_8002B844(s32 x) {
    s32 wob;
    s32 sel;
    s32 y;
    u8 ids[3] = { 0x28, 0x27, 0x26 }; /* the retail build keeps these bytes as the file-scope D_800615A8 */
    static s32 D_8008FB58; /* the retail build keeps it as the file-scope D_8008FB58 */

    D_800616B0 = 4 - D_800616B0;
    func_8002DECC(0, x + 0x28, 0x1E, 0xF0, 0x6C);
    func_8002DECC(0x37, x + 0x2B, 0x8B, 0xF0, 3);
    func_8002DECC(0x37, x + 0x119, 0x24, 2, 0x68);
    func_8002DECC(0x37, x + 0x27, 0x1D, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x8A, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x1E, 1, 0x6D);
    func_8002DECC(0x37, x + 0x118, 0x1E, 1, 0x6D);
    func_8002DECC(0x38, x + 0x29, 0x1F, 0xED, 1);
    func_8002DECC(0x38, x + 0x29, 0x20, 1, 0x68);
    func_8002DECC(0x39, x + 0x29, 0x88, 0xEE, 1);
    func_8002DECC(0x39, x + 0x116, 0x1F, 1, 0x69);
    func_8002DECC(0x3C, x + 0x3A, 0x1E, 0x15, 0x6C);
    func_8002DECC(0x3D, x + 0x5D, 0x56, 0xA7, 2);
    func_8002DECC(0x24, x + 0x8D, 0x3E, 0x54, 7);
    func_8002DECC(0x24, x + 0x8D, 0x6C, 0x54, 7);
    func_8002DECC(0x57, x + 0xE9, 0x3C, 0x1A, 9);
    func_8002DECC(0x56, x + 0x6C, 0x3C, 0x1A, 9);
    func_8002DECC(0x29, x + 0xE9, 0x6B, 0x1A, 9);
    func_8002DECC(0x2A, x + 0x6C, 0x6B, 0x1A, 9);
    func_8002DECC(0x22, x + 0x31, 0x3B, 0x36, 0xC);
    func_8002DECC(0x23, x + 0x35, 0x68, 0x2A, 0xC);
    func_8002DECC(5, x + 0x45, 0x1C, 7, 7);
    func_8002DECC(5, x + 0xF3, 0x1C, 7, 7);
    wob = D_8008FB44;
    wob = (wob >> 2) & 0xF;
    wob = D_80060D64[wob];
    func_8002DECC(6, x + wob + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, x - wob + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x21, x + 0x75, 0x18, 0x56, 0xE);
    func_8002DECC(0x25, x + 0x8E, 0x3F, 0x50, 3);
    func_8002DECC(0x25, x + 0x8E, 0x6D, 0x50, 3);
    func_8002DECC(0x27, x + 0xB3, 0x39, 8, 0xB);
    func_8002DECC(0x27, x + 0xB3, 0x67, 8, 0xB);
    if (D_8008FB3E & 0x200) {
        switch (D_8008FB3E & 0x100) {
            case 0:
                func_8002DECC(ids[D_800615CC[D_80060CB0][1]], D_800615CC[D_80060CB0][0] + x, 0x67, 8, 0xB);
                break;
            case 0x100:
                func_8002DECC(ids[D_800615AC[D_800616B0][1]], D_800615AC[D_800616B0][0] + x, 0x39, 8, 0xB);
                break;
        }
    } else {
        func_8002DECC(ids[D_800615CC[D_80060CB0][1]], D_800615CC[D_80060CB0][0] + x, 0x67, 8, 0xB);
        func_8002DECC(ids[D_800615AC[D_800616B0][1]], D_800615AC[D_800616B0][0] + x, 0x39, 8, 0xB);
    }
    if (D_8008FB3E & 0x2000) {
        D_800616B0 = 4 - D_800616B0;
        return;
    }
    if (!(D_8008FB3E & 0x800)) {
        if (D_80092C81 > 0x14 || (D_80092C84 & 0x10)) {
            D_8008FB3E |= 0x2000;
            D_8008FB38 = 0x1F;
            func_8002A7C8(0, 0, 0xFF);
        } else if (D_80092C81 < -0x14 || (D_80092C84 & 0x2000)) {
            D_8008FB3E |= 0x3000;
            D_8008FB38 = 0x1F;
            func_8002A7C8(0, 0, 0xFF);
        }
        if (D_80092C86 & 0x8000) {
            D_8008FB3E |= 0x820;
            func_8002A7C8(0, 1, 0xFF);
        }
    } else {
        if ((D_80092C86 & 0x8000) && !(D_8008FB3E & 0x200)) {
            D_8008FB3E &= ~0x920;
            func_8002A7C8(0, 2, 0xFF);
            D_800616B0 = 4 - D_800616B0;
            return;
        }
        wob = D_8008FB44;
        wob = (wob >> 1) & 0xF;
        wob = D_80060D64[wob];
        sel = D_8008FB3E & 0x100;
        if (D_8008FB3E & 0x200) {
            switch (sel) {
                case 0:
                    if (D_8008FB58 < D_800615AC[D_800616B0][0]) {
                    } else if (D_800615AC[D_800616B0][0] < D_8008FB58) {
                    } else {
                        D_8008FB3E &= ~0x200;
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615AC[D_800616B0][1]];
                        if (D_80092C81 < 0x14 && D_80092C81 > -0x14) {
                            func_8002DECC(sel, D_8008FB58 + x, 0x39, 8, 0xB);
                        }
                        y = 0x3A;
                        sel = 0;
                    }
                    break;
                case 0x100:
                    if (D_8008FB58 < D_800615CC[D_80060CB0][0]) {
                    } else if (D_800615CC[D_80060CB0][0] < D_8008FB58) {
                    } else {
                        D_8008FB3E &= ~0x200;
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615CC[D_80060CB0][1]];
                        if (D_80092C81 < 0x14 && D_80092C81 > -0x14) {
                            func_8002DECC(sel, D_8008FB58 + x, 0x67, 8, 0xB);
                        }
                        y = 0x65;
                        sel = 0x100;
                    }
                    break;
            }
        }
        if (!(D_8008FB3E & 0x200)) {
            switch (sel) {
                case 0:
                    y = 0x3A;
                    if (D_80092C82 < -0x1E || D_80092C82 > 0x1E) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB3E &= ~0x100;
                            D_8008FB3E |= 0x100;
                            D_8008FB3E |= 0x400;
                            func_8002A7C8(0, 0, 0xFF);
                        }
                    } else if (D_80092C81 < -0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615AC[D_800616B0--][0];
                            if (D_800616B0 < 0) {
                                D_800616B0 = 0;
                            }
                            D_8008FB3E |= 0x600;
                        }
                    } else if (D_80092C81 > 0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615AC[D_800616B0++][0];
                            if (D_800616B0 > 4) {
                                D_800616B0 = 4;
                            }
                            D_8008FB3E |= 0x600;
                        }
                    } else {
                        D_8008FB3E &= ~0x400;
                    }
                    break;
                case 0x100:
                    y = 0x65;
                    if (D_80092C82 < -0x1E || D_80092C82 > 0x1E) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB3E &= ~0x100;
                            D_8008FB3E |= 0;
                            D_8008FB3E |= 0x400;
                            func_8002A7C8(0, 0, 0xFF);
                        }
                    } else if (D_80092C81 < -0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615CC[D_80060CB0--][0];
                            if (D_80060CB0 < 0) {
                                D_80060CB0 = 0;
                            }
                            D_8008FB3E |= 0x400;
                            D_8008FB3E |= 0x200;
                        }
                    } else if (D_80092C81 > 0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615CC[D_80060CB0++][0];
                            if (D_80060CB0 > 4) {
                                D_80060CB0 = 4;
                            }
                            D_8008FB3E |= 0x400;
                            D_8008FB3E |= 0x200;
                        }
                    } else {
                        D_8008FB3E &= ~0x400;
                    }
                    break;
            }
        }
        if (D_8008FB3E & 0x200) {
            s32 pos;

            switch (sel) {
                case 0:
                    y = 0x3A;
                    pos = D_8008FB58 + x;
                    if (D_8008FB58 < D_800615AC[D_800616B0][0]) {
                        D_8008FB58++;
                        pos++;
                        sel = ids[D_800615AC[D_800616B0 - 1][1]];
                    } else if (D_800615AC[D_800616B0][0] < D_8008FB58) {
                        D_8008FB58--;
                        pos--;
                        sel = ids[D_800615AC[D_800616B0 + 1][1]];
                    } else {
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615AC[D_800616B0][1]];
                    }
                    func_8002DECC(sel, pos, 0x39, 8, 0xB);
                    break;
                case 0x100:
                    y = 0x65;
                    pos = D_8008FB58 + x;
                    if (D_8008FB58 < D_800615CC[D_80060CB0][0]) {
                        D_8008FB58++;
                        pos++;
                        sel = ids[D_800615CC[D_80060CB0 - 1][1]];
                    } else if (D_800615CC[D_80060CB0][0] < D_8008FB58) {
                        D_8008FB58--;
                        pos--;
                        sel = ids[D_800615CC[D_80060CB0 + 1][1]];
                    } else {
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615CC[D_80060CB0][1]];
                    }
                    func_8002DECC(sel, pos, 0x67, 8, 0xB);
                    break;
            }
        }
        func_8002DECC(1, x - wob + 0x1E, y, 0x10, 0xD);
    }
    D_800616B0 = 4 - D_800616B0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002B844.s")
#endif

#ifdef NON_MATCHING
/* frame, stack homes and register allocation differ; code is equivalent */
void func_8002C598(s32 arg0) {
    static s32 D_800615E0 = -1; /* the retail build keeps it as the file-scope D_800615E0 */
    s32 cx;
    s32 cy;
    s32 x;
    f32 f;
    s32 s;
    s32 n;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;
    s32 ox;
    s32 w;
    s32 h;
    s32 y;
    s32 i;

    s = 0;
    if (D_8008FB50 < 6) {
        if (D_8008FB50 != D_800615E0) {
            func_80028120(D_800614E4[D_8008FB50].start, D_800614E4[D_8008FB50].dst,
                          D_800614E4[D_8008FB50].end - D_800614E4[D_8008FB50].start);
            D_800615E0 = D_8008FB50;
        }
        w = 0xF4;
        h = 8;
        x = arg0 + 0x27;
        y = 0x1D;
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPPipeSync(D_8007A184++);
            gDPLoadTLUT_pal256(D_8007A184++, D_8006125C[D_8008FB50]);
            for (i = 0; i < 24; i++) {
                if (i == 23) {
                    h = 1;
                }
                gDPLoadTextureTile(D_8007A184++, D_80061274[D_8008FB50 * 24 + i], G_IM_FMT_CI, G_IM_SIZ_8b, 244, h, 0, 0,
                                   243, h - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                    1 << 10, 1 << 10);
                gDPPipeSync(D_8007A184++);
                y += h;
            }
            func_800324F4();
        }
    } else {
        func_8002DECC(0, arg0 + 0x28, 0x1E, 0xF0, 0xB4);
        func_8002DECC(0x38, arg0 + 0x29, 0x1F, 0xED, 1);
        func_8002DECC(0x38, arg0 + 0x29, 0x20, 1, 0xB1);
        func_8002DECC(0x39, arg0 + 0x29, 0xD0, 0xEE, 1);
        func_8002DECC(0x39, arg0 + 0x117, 0x1F, 1, 0xB2);
        func_8002DECC(0x37, arg0 + 0x2C, 0xD4, 0xF0, 3);
        func_8002DECC(0x37, arg0 + 0x11A, 0x25, 2, 0xB2);
        func_8002DECC(0x37, arg0 + 0x27, 0x1D, 0xF2, 1);
        func_8002DECC(0x37, arg0 + 0x27, 0xD3, 0xF2, 1);
        func_8002DECC(0x37, arg0 + 0x27, 0x1E, 1, 0xB3);
        func_8002DECC(0x37, arg0 + 0x119, 0x1E, 1, 0xB3);
        if (D_8008FB50 != D_800615E0) {
            func_80028120(D_800614E4[D_8008FB50].start, D_800614E4[D_8008FB50].dst,
                          D_800614E4[D_8008FB50].end - D_800614E4[D_8008FB50].start);
            D_800615E0 = D_8008FB50;
        }
        n = D_8008FB50 - 6;
        w = D_8006158C[n][0];
        h = D_8006158C[n][1];
        x = D_80061598[n * 2] + arg0;
        y = D_80061598[n * 2 + 1];
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPLoadTLUT_pal256(D_8007A184++, D_8006155C[n]);
            D_8008FB3E &= ~0x10;
            gDPLoadTextureTile(D_8007A184++, D_8006156C[n * 2], G_IM_FMT_CI, G_IM_SIZ_8b, D_8006158C[n][0], D_8006158C[n][1], 0, 0,
                               D_8006158C[n][0] - 1, D_8006158C[n][1] - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(D_8007A184++);
            gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                1 << 10, 1 << 10);
            gDPPipeSync(D_8007A184++);
            gDPLoadTextureTile(D_8007A184++, D_8006156C[n * 2 + 1], G_IM_FMT_CI, G_IM_SIZ_8b, D_8006158C[n][0], D_8006158C[n][2], 0, 0,
                               D_8006158C[n][0] - 1, D_8006158C[n][2] - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(D_8007A184++);
            gSPTextureRectangle(D_8007A184++, x << 2, (y + D_8006158C[n][1]) << 2, (x + w) << 2, (y + h + D_8006158C[n][2]) << 2,
                                G_TX_RENDERTILE, s, 0, 1 << 10, 1 << 10);
            func_800324F4();
        }
    }
    func_8002DECC(5, arg0 + 0x45, 0x1C, 7, 7);
    func_8002DECC(5, arg0 + 0xF3, 0x1C, 7, 7);
    n = (D_8008FB44 >> 2) & 0xF;
    n = D_80060D64[n];
    func_8002DECC(6, arg0 + n + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, arg0 - n + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x2B, arg0 + 0x83, 0x18, 0x3A, 0x10);
    if (D_8008FB50 < 6) {
        if (D_8008FB54 < 0) {
            cx = (s32) D_8007AA08.x / D_800614B4[D_8008FB50] + D_800614CC[D_8008FB50];
            cy = (s32) D_8007AA08.z / D_800614B4[D_8008FB50 + 6] + D_800614CC[D_8008FB50 + 6];
        } else {
            cx = D_80061184[D_8008FB50 * 18 + D_8008FB54 * 2];
            cy = D_80061184[D_8008FB50 * 18 + D_8008FB54 * 2 + 1];
        }
        if (D_8008FB44 & 0x20) {
            func_8002DECC(0x2C, arg0 + cx + 0x23, cy + 0xD, 0xC, 0x10);
        }
        if (D_8008FB54 < 0) {
            sx = D_800614B4[D_8008FB50];
            sy = D_800614B4[D_8008FB50 + 6];
            px = D_800614CC[D_8008FB50];
            py = D_800614CC[D_8008FB50 + 6];
            if (D_80060F28 == -1.0f) {
                D_80060F28 = cx;
                D_80060F2C = cy;
            }
            if (D_8008FB3C != 0) {
                f = D_80092C81;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                D_80060F28 += f * 0.08;
                f = D_80092C82;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                D_80060F2C -= f * 0.08;
                if (D_80060F28 < 6.0f) {
                    D_80060F28 = 6.0f;
                } else if (D_80060F28 > 236.0f) {
                    D_80060F28 = 236.0f;
                }
                if (D_80060F2C < 6.0f) {
                    D_80060F2C = 6.0f;
                } else if (D_80060F2C > 178.0f) {
                    D_80060F2C = 178.0f;
                }
            }
            D_8008FB48 = sx * ((s32) D_80060F28 - px);
            D_8008FB4C = sy * ((s32) D_80060F2C - py);
            y = 0;
            h = 5;
            ox = -2;
            if (D_8008FB3C != 0) {
                y = -2;
                h = 6;
            }
            func_8002DECC(0x55, arg0 + D_80060F28 + 39.0f + ox, D_80060F2C + 29.0f - 1.0f, h, 1);
            func_8002DECC(4, arg0 + D_80060F28 + 39.0f - 2.0f, D_80060F2C + 29.0f - 12.0f + y, 0xC, 0xC);
        }
    }
    if (!(D_8008FB3E & 0x2000)) {
        if (D_8008FB3C == 0) {
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
        if (D_8008FB50 < 6 && D_8008FB54 < 0) {
            if (D_8008FB3C == 0) {
                D_8008FB5C = D_80060F28;
                D_8008FB60 = D_80060F2C;
            }
            if (D_80092C86 & 0x8000) {
                D_8008FB3C ^= 1;
                D_8008FB3E ^= 0x20;
                func_8002A7C8(0, 0x17, 0xFF);
            } else if ((D_80092C86 & 0x4000) && D_8008FB3C != 0) {
                D_80060F28 = D_8008FB5C;
                D_80060F2C = D_8008FB60;
                func_8002A7C8(0, 0x13, 0xFF);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002C598.s")
#endif

extern s8 D_80060D64[];
extern u8 D_8007A9F4;
extern u8 D_8007A9F5;
extern u8 D_8007A9F6;
extern u8 D_8007A9F7;
extern s32 D_8007A9E0;
extern u8 D_8007AA04;
extern u32 D_80055D7C[];
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

#ifdef NON_MATCHING
/* w, s, lrs and lrt are kept in registers where retail reloads them from the stack; code is equivalent */
extern u8 *D_80060D74[];
extern u8 D_80060CB4[][2];
extern Gfx D_80060ED8[];
extern Gfx D_80060EF0[];
extern u16 D_80061E98[];

void func_8002DECC(s32 id, s32 x, s32 y, s32 w, s32 h) {
    s32 ret;
    s32 alpha;
    s32 xr;
    s32 masks;
    s32 maskt;
    s32 ult;
    s32 uls;
    s32 s;
    s32 t;
    s32 dsdx;
    s32 dtdy;
    s32 texH;
    s32 d;
    s32 lrs;
    s32 lrt;
    u8* tex;
    s32 texW;
    s32 pad[2];

    tex = D_80060D74[id];
    texW = D_80060CB4[id][0];
    texH = D_80060CB4[id][1];
    lrs = texW - 1;
    lrt = texH - 1;
    alpha = 0;
    ret = 0;
    maskt = 0;
    masks = 0;
    s = 0;
    t = 0;
    uls = 0;
    ult = 0;
    dtdy = 0x400;
    dsdx = 0x400;

    switch (id) {
        case 0:
            maskt = 4;
            masks = 4;
            s = (x & 0xF) << 5;
            t = (y & 0xF) << 5;
            break;
        case 0x3C:
            alpha = -0x80;
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3E:
            alpha = 0x50;
            break;
        case 0x37:
        case 0x38:
        case 0x39:
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3D:
            dsdx = 0;
            break;
    }
    if (x < 0) {
        if (x + w < 0) {
            ret = -1;
        } else {
            d = -x;
            s += d << 5;
            x = 0;
            w -= d;
        }
    }
    if (x > 320) {
        ret = -1;
    } else if ((xr = x + w) > 320) {
        w = w - xr + 320;
    }
    if (w <= 0 || h <= 0) {
        ret = -1;
    }
    if (ret >= 0) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
        gDPPipeSync(D_8007A184++);
        if (alpha == 0) {
            gSPDisplayList(D_8007A184++, D_80060ED8);
        } else {
            gSPDisplayList(D_8007A184++, D_80060EF0);
            gDPPipeSync(D_8007A184++);
            gDPSetEnvColor(D_8007A184++, 255, 255, 255, alpha);
        }
        if (!(D_8008FB3E & 0x10)) {
            gDPPipeSync(D_8007A184++);
            gDPLoadTLUT_pal256(D_8007A184++, D_80061E98);
            D_8008FB3E |= 0x10;
        }
        gDPLoadTextureTile(D_8007A184++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, texW, 0, uls, ult, lrs, lrt, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, t, dsdx,
                            dtdy);
        gDPPipeSync(D_8007A184++);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002DECC.s")
#endif

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


typedef struct { s8 a; s8 b; } Unk80060F30;
extern Unk80060F30 D_80060F30[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern f32 D_80060F28;
extern f32 D_80060F2C;
extern s16 D_800614B4[];
extern s16 D_800614CC[];


/* ---------------------------------------------------------------------------
 * .data 80055D40..80061650 (after 2B0F0, before 30600). Besides this file's own
 * tables it holds tables that 3F50, 9D50, AEA0 and E2A0 use: by link order they
 * belong here (or to a data-only file we can't tell apart). Pixels, palettes,
 * message text and animation keyframes are assets; ROM offsets and overlay or
 * buffer addresses are written as numbers.
 */
typedef struct { u16 unk0; s16 unk2; u16 unk4, unk6, unk8, unkA, unkC, unkE; s32 unk10, unk14; f32 unk18, unk1C, unk20; u8 unk24[4]; u8 unk28[0x10]; } D2ActorStats; /* 0x38 */
typedef struct { u32 start; u32 end; } D2RomRange;
typedef struct { u16 unk0; u16 unk2; f32 x; f32 y; f32 rot; } D2PosRot;
typedef struct { u32 start; u32 end; void *unk8; void *unkC; void *unk10; } D2OvlDef;
typedef struct { s16 unk0, unk2, unk4, unk6; f32 unk8, unkC, unk10, unk14; } D2Place; /* 0x18 */
typedef struct { u16 unk0, unk2, unk4, unk6; f32 unk8, unkC; } D2Scale; /* 0x10 */
typedef struct { u16 flags; u16 unk2; u32 romStart; u32 romEnd; void *dst; void *unk10[10]; void *unk38; s32 unk3C; s32 unk40; } D2MapDef; /* 0x44 */
typedef struct { u32 start; u32 end; void *dst; } D2RomDst;
typedef struct { void *keys; u16 count; u16 frames; s32 pad[6]; } D2Anim; /* 0x20 */
typedef struct { Gfx *a; Gfx *b; } D2DlPair;
typedef struct { u32 start; u32 dl; } D2SegDl;
#ifndef NON_MATCHING /* the NON_MATCHING build declares it earlier, for func_8002C598 */
typedef struct { void *dst; u32 start; u32 end; } D2DstRom;
#endif
extern u8 D_800620A0[];
extern u8 D_800621A8[];
extern u8 D_80062280[];
extern u8 D_80062290[];
extern u8 D_800622A0[];
extern u8 D_80062338[];
extern u8 D_80062380[];
extern u8 D_80062438[];
extern u8 D_800624F0[];
extern u8 D_80062500[];
extern u8 D_80062510[];
extern u8 D_80062568[];
extern u8 D_800625C0[];
extern u8 D_80062618[];
extern u8 D_80062670[];
extern u8 D_800626C8[];
extern u8 D_80062720[];
extern u8 D_80062778[];
extern u8 D_800627D0[];
extern u8 D_80062828[];
extern u8 D_80062880[];
extern u8 D_800628D8[];
extern u8 D_80062930[];
extern u8 D_80062988[];
extern u8 D_800629E0[];
extern u8 D_80062A38[];
extern u8 D_80062A90[];
extern u8 D_80062EC8[];
extern u8 D_80063038[];
extern u8 D_800631B0[];
extern u8 D_800633D8[];
extern u8 D_80063588[];
extern u8 D_80063598[];
extern u8 D_80063680[];
extern u8 D_80063B40[];
extern u8 D_80063DD0[];
extern u8 D_80063FD0[];
extern u8 D_80064228[];
extern u8 D_80064320[];
extern u8 D_80064380[];
extern u8 D_800643E0[];
extern u8 D_80064440[];
extern u8 D_80064538[];
extern u8 D_80064630[];
extern u8 D_800649D8[];
extern u8 D_80064AA0[];
extern u8 D_80064F08[];
extern u8 D_80064FA0[];
extern u8 D_80065038[];
extern u8 D_800650D0[];
extern u8 D_80065168[];
extern u8 D_80065350[];
extern u8 D_800653F8[];
extern u8 D_80065408[];
extern u8 D_80065418[];
extern u8 D_80065590[];
extern u8 D_800655A8[];
extern u8 D_800655C0[];
extern u8 D_800655D8[];
extern u8 D_800655F0[];
extern u8 D_80065608[];
extern u8 D_80065620[];
extern u8 D_80065638[];
extern u8 D_80065648[];
extern u8 D_80065780[];
extern u8 D_80065790[];
extern u8 D_800657A0[];
extern u8 D_80065D78[];
extern u8 D_80065F08[];
extern u8 D_80066098[];
extern u8 D_80066210[];
extern u8 D_80066330[];
extern u8 D_80066488[];
extern u8 D_800664E0[];
extern u8 D_80066538[];
extern u8 D_80066590[];
extern u8 D_800665E8[];
extern u8 D_80066640[];
extern u8 D_80066698[];
extern u8 D_800666F0[];
extern u8 D_80066748[];
extern u8 D_800667A0[];
extern u8 D_800667F8[];
extern u8 D_80066850[];
extern u8 D_80066918[];
extern u8 D_800669E0[];
extern u8 D_800669F0[];
extern u8 D_80066AE8[];
extern u8 D_80067090[];
extern u8 D_80067898[];
extern u8 D_800680A0[];
extern u8 D_800688A8[];
extern u8 D_80068EB0[];
extern u8 D_800690B8[];
extern u8 D_800695A8[];
extern u8 D_80069A98[];
extern u8 D_80069CA0[];
extern u8 D_8006A2C8[];
extern u8 D_8006A8F0[];
extern u8 D_8006AAF8[];
extern u8 D_8006AFE8[];
extern u8 D_8006B4D8[];
extern u8 D_8006B6E0[];
extern u8 D_8006BBD0[];
void *D_80055D40[1] = {
    (void*)0x80206064,
};
D2ActorStats D_80055D44 = { 0, 0, 0x0032, 0x0032, 0x000F, 0x000F, 5, 4, 0, 500, 5e+01f, 1.6e+02f, 0.07f, { 1, 1, 1, 1 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
u32 D_80055D7C[100] = {
    8, 10, 13, 17, 22, 28, 35, 44, 55, 69,
    86, 106, 130, 159, 193, 234, 282, 338, 404, 481,
    571, 674, 793, 929, 1085, 1263, 1464, 1691, 1947, 2235,
    2557, 2916, 3315, 3757, 4246, 4785, 5377, 6025, 6733, 7505,
    8344, 9253, 10237, 11297, 12438, 13663, 14975, 16377, 17871, 19462,
    21151, 22940, 24832, 26829, 28933, 31145, 33466, 35898, 38442, 41098,
    43866, 46747, 49740, 52846, 56063, 59390, 62826, 66371, 70022, 73778,
    77636, 81594, 85650, 89801, 94045, 98378, 102798, 107300, 111883, 116541,
    121272, 126072, 130938, 135865, 140849, 145887, 150975, 156109, 161284, 166497,
    171745, 177022, 182326, 187652, 192996, 198356, 203726, 209104, 214486, 219868,
};
u16 D_80055F0C[70] = {
    0x000A, 0x000B, 0x000B, 0x000B, 0x000C, 0x000C, 0x000C, 0x000D, 0x000D, 0x000D, 0x000D, 0x000E,
    0x000E, 0x000E, 0x000F, 0x000F, 0x0010, 0x0010, 0x0010, 0x0011, 0x0011, 0x0012, 0x0012, 0x0012,
    0x0013, 0x0013, 0x0014, 0x0014, 0x0015, 0x0015, 0x0016, 0x0016, 0x0017, 0x0017, 0x0018, 0x0019,
    0x0019, 0x001A, 0x001A, 0x001B, 0x001C, 0x001C, 0x001D, 0x001E, 0x001F, 0x001F, 0x0020, 0x0021,
    0x0022, 0x0023, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C,
    0x002D, 0x002E, 0x0030, 0x0031, 0x0032, 0x0032, 0x0032, 0x0032, 0x0032, 0x0032,
};
D2RomRange D_80055F98[30] = {
    { 0x00EF21A0, 0x00EF3770 }, { 0x00EF3770, 0x00EF5B10 }, { 0x00EF5B10, 0x00EF7EB0 },
    { 0x00EF7EB0, 0x00EFA2A0 }, { 0x00EFA2A0, 0x00EFBD30 }, { 0x00EFBD30, 0x00EFD390 },
    { 0x00EFD390, 0x00EFF280 }, { 0x00EFF280, 0x00F00D10 }, { 0x00F00D10, 0x00F027A0 },
    { 0x00F027A0, 0x00F05F50 }, { 0x00F05F50, 0x00F07D40 }, { 0x00F07D40, 0x00F09E30 },
    { 0x00F2C170, 0x00F2D120 }, { 0x00F2D120, 0x00F2E9F0 }, { 0x00F2E9F0, 0x00F2FB70 },
    { 0x00F09E30, 0x00F0C1D0 }, { 0x00F0C1D0, 0x00F10A60 }, { 0x00F10A60, 0x00F11FF0 },
    { 0x00F11FF0, 0x00F143E0 }, { 0x00F143E0, 0x00F15770 }, { 0x00F15770, 0x00F192D0 },
    { 0x00F192D0, 0x00F1DBD0 }, { 0x00F1DBD0, 0x00F1F660 }, { 0x00F1F660, 0x00F210A0 },
    { 0x00F210A0, 0x00F22AE0 }, { 0x00F22AE0, 0x00F23ED0 }, { 0x00F23ED0, 0x00F26B90 },
    { 0x00F26B90, 0x00F28740 }, { 0x00F28740, 0x00F2A2F0 }, { 0x00F2A2F0, 0x00F2C170 },
};
D2PosRot D_80056088[17] = {
    { 0x000F, 5, -2.36f, 1.23f, 1.5793f }, { 0x0010, 7, -2.36f, 1.23f, 1.5793f },
    { 0x0010, 0x000F, -2.36f, 1.23f, 1.5793f }, { 0x0012, 6, 13.31f, 16.56f, 2.43f },
    { 0x0011, 0, -7.9f, -40.5f, -1.51f }, { 0x0012, 7, -14.4f, 18.41f, 2.46f },
    { 0x0014, 5, -2.36f, 1.23f, 1.5793f }, { 0x0016, 0x0016, 9.93f, 17.45f, 2.2467f },
    { 0x0016, 0x000E, -2.36f, 1.23f, 1.5793f }, { 0x0017, 0, -2.36f, 1.23f, 1.5793f },
    { 0x0017, 0x0014, -3.65f, -8.81f, 2.4174f }, { 0x0017, 0x0016, 2.45f, 14.41f, 2.4171f },
    { 0x0017, 8, -2.36f, 1.23f, 1.5793f }, { 0x001A, 3, 14.15f, 0.67f, 1.97f },
    { 0x0019, 3, 2.96f, 0.12f, -0.9817f }, { 0x001E, 0x000F, 1.4f, -89.5f, -0.2801f },
    { 0x000F, 0x000D, 11.0f, 15.98f, 2.2914f },
};
u32 D_80056198[2] = {
    0, 0,
};
D2OvlDef D_800561A0[6] = {
    { 0x00A77F10, 0x00ADA190, (void*)0x80270890, (void*)0x802705F0, (void*)0x80270934 },
    { 0x00ADA190, 0x00B61550, (void*)0x80295990, (void*)0x80295648, (void*)0x80295A6C },
    { 0x00B61550, 0x00BBBF30, (void*)0x80269010, (void*)0x80268DA8, (void*)0x8026909C },
    { 0x00BBBF30, 0x00C2F900, (void*)0x80281FD0, (void*)0x80281CF8, (void*)0x80282088 },
    { 0x00C2F900, 0x00C99EF0, (void*)0x80278C10, (void*)0x80278970, (void*)0x80278CB0 },
    { 0x00C99EF0, 0x00CC2280, (void*)0x80236A38, (void*)0x80236958, (void*)0x80236A70 },
};
D2Place D_80056218[6] = {
    { 25, 0, 0, 0, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 26, 0, 8, 0, 0.0f, 0.0f, -2.0f, 0.0f },
    { 29, 1, 0, 0, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 33, 1, 0, 0, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 37, 1, 0, 0, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
    { 41, 1, 1, 0, 0.0f, 1.9e+02f, 2e+02f, 0.0f },
};
D2Place D_800562A8[1] = {
    { 32, 2, 5, 0, 0.0f, 0.0f, 2e+02f, 0.0f },
};
D2Place D_800562C0[5] = {
    { 30, 16, 0, 0, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 34, 16, 0, 0, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 38, 16, 0, 0, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 42, 16, 0, 0, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
    { 46, 16, 1, 0, 0.0f, 1.1e+02f, 4e+01f, 0.0f },
};
D2Place D_80056338[1] = {
    { 25, 17, 1, 0, 0.0f, 2e+02f, 0.0f, 0.0f },
};
D2Place D_80056350[6] = {
    { 1, 4, 0, 0, 0.0f, 1.3e+02f, 0.0f, 0.0f },
    { 2, 5, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 8, 5, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 14, 5, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 20, 5, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 26, 5, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f },
};
D2Place D_800563E0[1] = {
    { 23, 14, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f },
};
D2Place D_800563F8[5] = {
    { 18, 6, 0, 0, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 19, 0, 8, 0, 0.0f, 0.0f, -1.0f, 0.0f },
    { 20, 7, 0, 0, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 26, 7, 0, 0, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
    { 32, 7, 1, 0, 0.0f, 1.6e+02f, 1.6e+02f, 0.0f },
};
D2Place D_80056470[6] = {
    { 25, 8, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 32, 9, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 38, 9, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 44, 9, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 50, 9, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 56, 9, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f },
};
D2Place D_80056500[4] = {
    { 0, 10, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 4, 10, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 8, 10, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 31, 15, 3, 0, 0.0f, 0.0f, 0.0f, 0.0f },
};
D2Place D_80056560[4] = {
    { 1, 11, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f },
    { 9, 11, 0, 0, 0.0f, 0.0f, 0.0f, 0.7853982f },
    { 17, 11, 0, 0, 0.0f, 0.0f, 0.0f, 15.707963f },
    { 25, 11, 1, 0, 0.0f, 0.0f, 0.0f, 3.1415927f },
};
D2Place D_800565C0[5] = {
    { 35, 12, 0, 0, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 36, 0, 8, 0, 0.0f, 0.0f, -2.0f, 0.0f },
    { 41, 13, 0, 0, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 47, 13, 0, 0, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
    { 53, 13, 1, 0, 0.0f, 1.5e+02f, 1.5e+02f, 0.0f },
};
D2Place D_80056638[2] = {
    { 50, 18, 0, 0, 0.0f, 8e+02f, 0.0f, 0.0f },
    { 51, 19, 1, 0, 0.0f, 8e+02f, 0.0f, 0.0f },
};
D2Place D_80056668[4] = {
    { 38, 21, 0, 0, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 42, 21, 0, 0, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 46, 21, 0, 0, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
    { 50, 21, 1, 0, 0.0f, 3.8e+02f, 3.5e+02f, 0.0f },
};
D2Place *D_800566C8[20] = {
    D_80056218, D_800562A8, D_800562C0, D_80056338, NULL,
    D_80056350, NULL, D_800563E0, D_800563F8, NULL,
    D_80056470, D_80056500, D_80056560, D_800565C0, D_80056638,
    NULL, D_80056668, NULL, NULL, NULL,
};
/* D_8005685A and D_8005685C (undefined_syms.txt) are fields of D_80056718[20]. */
D2Scale D_80056718[22] = {
    { 0x0046, 7, 0x000A, 0, 1.1f, 1.1f }, { 0x0047, 0x0037, 2, 0, 1.0f, 1.0f },
    { 0x0048, 7, 2, 0, 11.0f, 11.0f }, { 0x0049, 7, 0, 0, 4.0f, 4.0f },
    { 0x004F, 7, 0x0082, 0, 4.0f, 4.0f }, { 0x0050, 7, 2, 0, 6.0f, 6.0f },
    { 0x0055, 6, 2, 0, 0.6f, 0.6f }, { 0x0056, 0x0032, 2, 0, 1.2f, 1.2f },
    { 0x0058, 7, 2, 0, 2.0f, 2.0f }, { 0x0059, 7, 0, 0, 2.0f, 2.0f },
    { 0x005B, 7, 2, 0, 1.0f, 1.0f }, { 0x005D, 0x002C, 2, 0, 1.0f, 1.0f },
    { 0x005E, 4, 0x000A, 0, 2.0f, 2.0f }, { 0x005F, 0x0038, 2, 0, 1.0f, 1.0f },
    { 0x0054, 7, 2, 0, 1.0f, 1.0f }, { 0x005A, 7, 0, 0, 1.0f, 1.0f },
    { 0x004B, 0x002A, 2, 0, 1.0f, 1.0f }, { 0x004C, 0x0036, 0, 0, 6.0f, 6.0f },
    { 0x0060, 4, 0x0080, 0, 1.0f, 1.0f }, { 0x0061, 0x0035, 0x0080, 0, 1.0f, 1.0f },
    { 0x0042, 2, 0, 0, 1.0f, 1.0f }, { 0x0047, 0x0037, 2, 0, 0.5f, 0.5f },
};
s32 D_80056878[2] = {
    0, 0,
};
D2RomRange D_80056880[7] = {
    { 0x00871D10, 0x008D1960 }, { 0x008D1960, 0x00926C00 }, { 0x00926C00, 0x0095D4E0 }, { 0x0095D4E0, 0x00988580 },
    { 0x00988580, 0x009E16C0 }, { 0x009E16C0, 0x00A14190 }, { 0x00A14190, 0x00A70350 },
};
u8 D_800568B8[0x2F8] = {
#include "assets/D_800568B8.inc.c"
};
D2MapDef D_80056BB0[36] = {
    { 0x0081, 0, 0x000EF280, 0x00133F20, (void*)0x8010FE00, (void*)0x8014F640, (void*)0x8014FB80, (void*)0x8014FF78, (void*)0x8015084C, (void*)0x80150290, (void*)0x80150518, (void*)0x80154810, (void*)0x801547BC, NULL, NULL, (void*)0x80154A90, 0, 5 },
    { 1, 0, 0x00133F20, 0x00165E70, (void*)0x8010FE00, (void*)0x80140430, (void*)0x80140790, (void*)0x80140A28, (void*)0x80140F3C, (void*)0x80140C20, (void*)0x80140D10, (void*)0x80141CA0, (void*)0x80141C8C, NULL, NULL, (void*)0x80141D44, 1, 1 },
    { 4, 0, 0x00165E70, 0x0019C1D0, (void*)0x8010FE00, (void*)0x80144464, (void*)0x80144710, (void*)0x80144858, (void*)0x80144CFC, (void*)0x80144A50, (void*)0x80144AD0, (void*)0x80145D70, (void*)0x80145D54, (void*)0x80146128, (void*)0x80146130, NULL, 1, 1 },
    { 4, 0, 0x0019C1D0, 0x001CA8C0, (void*)0x8010FE00, (void*)0x8013C564, (void*)0x8013C870, (void*)0x8013C9F0, (void*)0x8013CEEC, (void*)0x8013CC00, (void*)0x8013CCB8, (void*)0x8013E190, (void*)0x8013E168, (void*)0x8013E460, (void*)0x8013E468, (void*)0x8013E4DC, 1, 2 },
    { 1, 0, 0x001CA8C0, 0x00206D70, (void*)0x8010FE00, (void*)0x80149C98, (void*)0x8014A020, (void*)0x8014A3F8, (void*)0x8014AAFC, (void*)0x8014A6B0, (void*)0x8014A8C8, (void*)0x8014C1C0, (void*)0x8014C190, NULL, NULL, (void*)0x8014C2A4, 2, 3 },
    { 4, 0, 0x00206D70, 0x00251D30, (void*)0x8010FE00, (void*)0x80157D98, (void*)0x801582C0, (void*)0x80158518, (void*)0x80158A1C, (void*)0x80158730, (void*)0x801587E8, (void*)0x8015A9C0, (void*)0x8015A99C, (void*)0x8015AD2C, (void*)0x8015AD34, (void*)0x8015ADAC, 2, 2 },
    { 1, 0, 0x00251D30, 0x002768B0, (void*)0x8010FE00, (void*)0x80133438, (void*)0x80133720, (void*)0x80133948, (void*)0x80133DEC, (void*)0x80133B40, (void*)0x80133BC0, (void*)0x801348B0, (void*)0x80134898, NULL, NULL, (void*)0x80134974, 2, 1 },
    { 4, 0, 0x002768B0, 0x002A8510, (void*)0x8010FE00, (void*)0x8013F1FC, (void*)0x8013F500, (void*)0x8013F6B8, (void*)0x8013FBBC, (void*)0x8013F8D0, (void*)0x8013F988, (void*)0x80141550, (void*)0x80141528, (void*)0x801419CC, (void*)0x801419D4, (void*)0x80141A4C, 3, 2 },
    { 1, 0, 0x002A8510, 0x002F63B0, (void*)0x8010FE00, (void*)0x8015B89C, (void*)0x8015BD20, (void*)0x8015C090, (void*)0x8015C5FC, (void*)0x8015C270, (void*)0x8015C3D0, (void*)0x8015DB50, (void*)0x8015DB28, NULL, NULL, (void*)0x8015DC8C, 3, 2 },
    { 4, 0, 0x002F63B0, 0x003457F0, (void*)0x8010FE00, (void*)0x8015A824, (void*)0x8015AE10, (void*)0x8015B230, (void*)0x8015B7AC, (void*)0x8015B4F0, (void*)0x8015B580, (void*)0x8015E870, (void*)0x8015E860, (void*)0x8015F1A8, (void*)0x8015F1B0, NULL, 4, 1 },
    { 4, 0, 0x003457F0, 0x0036B800, (void*)0x8010FE00, (void*)0x801343D8, (void*)0x801345C0, (void*)0x80134738, (void*)0x80134CEC, (void*)0x80134920, (void*)0x80134AB8, (void*)0x80135DB0, (void*)0x80135D90, NULL, NULL, NULL, 4, 2 },
    { 4, 0, 0x0036B800, 0x003C9490, (void*)0x8010FE00, (void*)0x80169190, (void*)0x80169610, (void*)0x80169CE8, (void*)0x8016A510, NULL, (void*)0x8016A018, (void*)0x8016D6D8, (void*)0x8016D57C, (void*)0x8016D9C4, (void*)0x8016D9DC, (void*)0x8016DA7C, 4, 8 },
    { 4, 0, 0x003C9490, 0x003E1090, (void*)0x8010FE00, (void*)0x80125DA4, (void*)0x80126010, (void*)0x801261D4, (void*)0x801267BC, (void*)0x801264C0, (void*)0x80126588, (void*)0x80127800, (void*)0x801277CC, (void*)0x8012796C, (void*)0x80127974, (void*)0x801279EC, 5, 3 },
    { 2, 0, 0x003F1BA0, 0x004374F0, (void*)0x801539F0, (void*)0x80194B14, (void*)0x80195480, (void*)0x80195E98, (void*)0x801967F8, (void*)0x80196108, (void*)0x80196510, (void*)0x80198F84, (void*)0x80198980, NULL, NULL, (void*)0x80199330, 0, 18 },
    { 2, 0, 0x004374F0, 0x00487890, (void*)0x801539F0, (void*)0x8019DFA0, (void*)0x8019EC80, (void*)0x8019F7E0, (void*)0x8019FFF0, NULL, (void*)0x8019FD88, (void*)0x801A3900, (void*)0x801A3590, NULL, NULL, (void*)0x801A3D7C, 1, 16 },
    { 2, 0, 0x00487890, 0x0049D830, (void*)0x801539F0, (void*)0x80166974, (void*)0x80167120, (void*)0x80167738, (void*)0x80167EF0, (void*)0x80167948, (void*)0x80167C98, (void*)0x801696A0, (void*)0x80169530, NULL, NULL, (void*)0x80169980, 0, 14 },
    { 2, 0, 0x0049D830, 0x004CD2E0, (void*)0x801539F0, (void*)0x8017DA08, (void*)0x8017E510, (void*)0x8017EF80, (void*)0x8017FB58, (void*)0x8017F300, (void*)0x8017F850, (void*)0x8018302C, (void*)0x80182D34, NULL, NULL, (void*)0x8018348C, 1, 22 },
    { 2, 0, 0x004CD2E0, 0x004E44A0, (void*)0x801539F0, (void*)0x80168D4C, (void*)0x801691F0, (void*)0x80169680, (void*)0x80169BD0, (void*)0x801697F8, (void*)0x80169AA0, (void*)0x8016A978, (void*)0x8016A75C, NULL, NULL, (void*)0x8016ABA4, 2, 8 },
    { 2, 0, 0x004E44A0, 0x004F4E70, (void*)0x801539F0, (void*)0x801621D4, (void*)0x80162940, (void*)0x80162C10, (void*)0x801630B0, NULL, (void*)0x80162E90, (void*)0x80164180, (void*)0x801640FC, NULL, NULL, (void*)0x801643B8, 2, 8 },
    { 2, 0, 0x004F4E70, 0x004FFFE0, (void*)0x801539F0, (void*)0x8015DE28, (void*)0x8015E010, (void*)0x8015E1A0, (void*)0x8015E468, NULL, (void*)0x8015E2E0, (void*)0x8015EA70, (void*)0x8015EA28, NULL, NULL, NULL, 2, 4 },
    { 2, 0, 0x004FFFE0, 0x0051A6C0, (void*)0x801539F0, (void*)0x8016B158, (void*)0x8016B920, (void*)0x8016BEE8, (void*)0x8016C500, (void*)0x8016C0C8, (void*)0x8016C3A8, (void*)0x8016DE70, (void*)0x8016DD1C, NULL, NULL, (void*)0x8016E0BC, 2, 12 },
    { 2, 0, 0x0051A6C0, 0x0056DB40, (void*)0x801539F0, (void*)0x801A2518, (void*)0x801A2CE0, (void*)0x801A34B8, (void*)0x801A3B08, NULL, (void*)0x801A3938, (void*)0x801A6A68, (void*)0x801A6644, NULL, NULL, (void*)0x801A6E68, 3, 13 },
    { 2, 0, 0x0056DB40, 0x0059D6F0, (void*)0x801539F0, (void*)0x8017DA18, (void*)0x8017E500, (void*)0x8017F0A8, (void*)0x8017FDF8, (void*)0x8017F3D8, (void*)0x8017F9D8, (void*)0x80182FCC, (void*)0x80182D28, NULL, NULL, (void*)0x80183594, 3, 26 },
    { 2, 0, 0x0059D6F0, 0x005D6D20, (void*)0x801539F0, (void*)0x80186F78, (void*)0x801879E0, (void*)0x801886D8, (void*)0x80189368, (void*)0x80188A08, (void*)0x80189040, (void*)0x8018C910, (void*)0x8018C644, NULL, NULL, (void*)0x8018D010, 4, 26 },
    { 2, 0, 0x005D6D20, 0x005E99E0, (void*)0x801539F0, (void*)0x80164FB0, (void*)0x80165070, (void*)0x80165250, (void*)0x80165538, NULL, (void*)0x801653B8, (void*)0x80166464, (void*)0x801661A0, NULL, NULL, (void*)0x8016669C, 4, 3 },
    { 2, 0, 0x005E99E0, 0x006078D0, (void*)0x801539F0, (void*)0x8016EEE0, (void*)0x8016F360, (void*)0x8016F860, (void*)0x80170018, (void*)0x8016FAC0, (void*)0x8016FD70, (void*)0x801716D0, (void*)0x8017162C, NULL, NULL, (void*)0x801718D0, 5, 10 },
    { 0x0088, 0, 0x006078D0, 0x00665670, (void*)0x8010FE00, (void*)0x801649D8, (void*)0x80165460, (void*)0x80165A34, (void*)0x80165EB8, NULL, (void*)0x80165C38, (void*)0x8016D480, (void*)0x8016D430, (void*)0x8016DAC0, (void*)0x8016DAC8, (void*)0x8016DB98, 0, 5 },
    { 0x0088, 0, 0x00665670, 0x006C4880, (void*)0x8010FE00, (void*)0x80168D08, (void*)0x8016A590, (void*)0x8016A668, (void*)0x8016A778, NULL, (void*)0x8016A6F0, (void*)0x8016E920, (void*)0x8016E910, (void*)0x8016EFD8, (void*)0x8016EFE0, NULL, 0, 1 },
    { 0x0088, 0, 0x006C4880, 0x0071EB90, (void*)0x8010FE00, (void*)0x80163770, (void*)0x80164C90, (void*)0x80164D30, (void*)0x80164EE8, NULL, (void*)0x80164E68, (void*)0x80169C70, (void*)0x80169C5C, (void*)0x8016A0B4, (void*)0x8016A0BC, NULL, 0, 1 },
    { 0x0088, 0, 0x0071EB90, 0x007428A0, (void*)0x8010FE00, (void*)0x8012FC8C, (void*)0x80130610, (void*)0x801306B0, (void*)0x80130868, NULL, (void*)0x801307E8, (void*)0x80133440, (void*)0x80133428, (void*)0x80133ACC, (void*)0x80133AD4, NULL, 0, 1 },
    { 8, 0, 0x007428A0, 0x00785690, (void*)0x8010FE00, (void*)0x8014CFFC, (void*)0x8014D4A0, (void*)0x8014DDF4, (void*)0x8014E6C0, NULL, (void*)0x8014E370, (void*)0x80152534, (void*)0x80151E6C, (void*)0x80152A8C, (void*)0x80152AC4, (void*)0x80152BC4, 0, 16 },
    { 8, 0, 0x00785690, 0x007C1CE0, (void*)0x8010FE00, (void*)0x801476DC, (void*)0x80147D20, (void*)0x80147F00, (void*)0x8014838C, NULL, (void*)0x80148068, (void*)0x8014BF70, (void*)0x8014BF38, (void*)0x8014C3F8, (void*)0x8014C400, NULL, 0, 3 },
    { 8, 0, 0x007C1CE0, 0x007EF930, (void*)0x8010FE00, (void*)0x8013B150, (void*)0x8013B5F0, (void*)0x8013B7D0, (void*)0x8013BBB4, NULL, (void*)0x8013B900, (void*)0x8013D580, (void*)0x8013D550, (void*)0x8013D9A4, (void*)0x8013D9AC, (void*)0x8013DA3C, 0, 3 },
    { 8, 0, 0x007EF930, 0x008231F0, (void*)0x8010FE00, (void*)0x80140DC4, (void*)0x80141190, (void*)0x80141370, (void*)0x80141714, NULL, (void*)0x80141468, (void*)0x80143300, (void*)0x801432C4, (void*)0x8014365C, (void*)0x80143664, NULL, 0, 3 },
    { 8, 0, 0x008231F0, 0x00851240, (void*)0x8010FE00, (void*)0x80139374, (void*)0x80139680, (void*)0x80139ACC, (void*)0x8013A1B0, NULL, (void*)0x80139E80, (void*)0x8013D910, (void*)0x8013D854, (void*)0x8013DCE4, (void*)0x8013DD3C, (void*)0x8013DE48, 0, 11 },
    { 0x0088, 0, 0x00851240, 0x00869620, (void*)0x8010FE00, (void*)0x801269B4, (void*)0x80127A80, (void*)0x80127AE8, (void*)0x80127C28, NULL, (void*)0x80127BA8, (void*)0x801281D0, (void*)0x801281C0, NULL, NULL, NULL, 0, 1 },
};
D2RomDst D_80057540[6] = {
    { 0x000C8DE0, 0x000D0570, (void*)0x801F8000 }, { 0x000D0570, 0x000D7FE0, (void*)0x801F8000 },
    { 0x000D7FE0, 0x000DD790, (void*)0x801F8000 }, { 0x000DD790, 0x000E4D00, (void*)0x801F8000 },
    { 0x000E4D00, 0x000EBDE0, (void*)0x801F8000 }, { 0x000EBDE0, 0x000EF280, (void*)0x801F8000 },
};
u32 D_80057588 = 0;
s8 D_8005758C[158][2] = {
    { -1, -7 }, { 0, -7 }, { 1, -7 }, { -3, -6 }, { -2, -6 }, { -1, -6 }, { 0, -6 }, { 1, -6 }, { 2, -6 }, { 2, -6 },
    { -4, -5 }, { -3, -5 }, { -2, -5 }, { -1, -5 }, { 0, -5 }, { 1, -5 }, { 2, -5 }, { 3, -5 }, { 4, -5 }, { -5, -4 },
    { -4, -4 }, { -3, -4 }, { -2, -4 }, { -1, -4 }, { 0, -4 }, { 1, -4 }, { 2, -4 }, { 3, -4 }, { 4, -4 }, { 5, -4 },
    { -6, -3 }, { -5, -3 }, { -4, -3 }, { -3, -3 }, { -2, -3 }, { -1, -3 }, { 0, -3 }, { 1, -3 }, { 2, -3 }, { 3, -3 },
    { 4, -3 }, { 5, -3 }, { 6, -3 }, { -6, -2 }, { -5, -2 }, { -4, -2 }, { -3, -2 }, { -2, -2 }, { -1, -2 }, { 0, -2 },
    { 1, -2 }, { 2, -2 }, { 3, -2 }, { 4, -2 }, { 5, -2 }, { 6, -2 }, { -7, -1 }, { -6, -1 }, { -5, -1 }, { -4, -1 },
    { -3, -1 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 4, -1 }, { 5, -1 }, { 6, -1 },
    { 7, -1 }, { -7, 0 }, { -6, 0 }, { -5, 0 }, { -4, 0 }, { -3, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 },
    { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 }, { -7, 1 }, { -6, 1 }, { -5, 1 }, { -4, 1 },
    { -3, 1 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 },
    { 7, 1 }, { -6, 2 }, { -5, 2 }, { -4, 2 }, { -3, 2 }, { -2, 2 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 2, 2 },
    { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 }, { -6, 3 }, { -5, 3 }, { -4, 3 }, { -3, 3 }, { -2, 3 }, { -1, 3 },
    { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { -5, 4 }, { -4, 4 }, { -3, 4 },
    { -2, 4 }, { -1, 4 }, { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { -4, 5 }, { -3, 5 },
    { -2, 5 }, { -1, 5 }, { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 }, { 4, 5 }, { -3, 6 }, { -2, 6 }, { -1, 6 },
    { 0, 6 }, { 1, 6 }, { 2, 6 }, { 3, 6 }, { -1, 7 }, { 0, 7 }, { 1, 7 }, { 0, 0 },
};
s8 D_800576C8[90][2] = {
    { -1, -5 }, { 0, -5 }, { 1, -5 }, { -3, -4 }, { -2, -4 }, { -1, -4 }, { 0, -4 }, { 1, -4 }, { 2, -4 }, { 3, -4 },
    { -4, -3 }, { -3, -3 }, { -2, -3 }, { -1, -3 }, { 0, -3 }, { 1, -3 }, { 2, -3 }, { 3, -3 }, { 4, -3 }, { -4, -2 },
    { -3, -2 }, { -2, -2 }, { -1, -2 }, { 0, -2 }, { 1, -2 }, { 2, -2 }, { 3, -2 }, { 4, -2 }, { -5, -1 }, { -4, -1 },
    { -3, -1 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { 3, -1 }, { 4, -1 }, { 5, -1 }, { -5, 0 },
    { -4, 0 }, { -3, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 },
    { -5, 1 }, { -4, 1 }, { -3, 1 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 },
    { 5, 1 }, { -4, 2 }, { -3, 2 }, { -2, 2 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 },
    { -4, 3 }, { -3, 3 }, { -2, 3 }, { -1, 3 }, { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { -3, 4 },
    { -2, 4 }, { -1, 4 }, { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { -1, 5 }, { 0, 5 }, { 1, 5 }, { 0, 0 },
};
s8 D_8005777C[10][2] = {
    { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 0, 0 },
};
s8 D_80057790[22][2] = {
    { -1, -2 }, { 0, -2 }, { -1, -2 }, { -2, -1 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 2, -1 }, { -2, 0 }, { -1, 0 }, { 0, 0 },
    { 1, 0 }, { 2, 0 }, { -2, 1 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { -1, 2 }, { 0, 2 }, { 1, 2 }, { 0, 0 },
};
/* Animations: keyframes (assets, 0x34-byte records) and their headers. */
u32 D_800577BC[0x8F] = {
#include "assets/D_800577BC.inc.c"
};
D2Anim D_800579F8 = { D_800577BC, 0x000B, 0x0051, 0, 0, 0, 0, 0, 0 };
u32 D_80057A18[0xC3] = {
#include "assets/D_80057A18.inc.c"
};
D2Anim D_80057D24 = { D_80057A18, 0x000F, 0x006E, 0, 0, 0, 0, 0, 0 };
u32 D_80057D44[0x8F] = {
#include "assets/D_80057D44.inc.c"
};
D2Anim D_80057F80 = { D_80057D44, 0x000B, 0x0064, 0, 0, 0, 0, 0, 0 };
u32 D_80057FA0[0x1A] = {
#include "assets/D_80057FA0.inc.c"
};
D2Anim D_80058008 = { D_80057FA0, 2, 0x001E, 0, 0, 0, 0, 0, 0 };
u32 D_80058028[0x27] = {
#include "assets/D_80058028.inc.c"
};
u32 D_800580C4[0x34] = {
#include "assets/D_800580C4.inc.c"
};
u32 D_80058194[0x41] = {
#include "assets/D_80058194.inc.c"
};
u32 D_80058298[0x41] = {
#include "assets/D_80058298.inc.c"
};
D2Anim D_8005839C[4] = {
    { D_80058028, 3, 0x003C, 0, 0, 0, 0, 0, 0 },
    { D_800580C4, 4, 0x003C, 0, 0, 0, 0, 0, 0 },
    { D_80058194, 5, 0x0050, 0, 0, 0, 0, 0, 0 },
    { D_80058298, 5, 0x0050, 0, 0, 0, 0, 0, 0 },
};
u16 D_8005841C[0x200] = {
#include "assets/D_8005841C.inc.c"
};
u8 D_8005881C[0x600] = {
#include "assets/D_8005881C.inc.c"
};
u8 D_80058E1C[0x600] = {
#include "assets/D_80058E1C.inc.c"
};
u8 D_8005941C[0x600] = {
#include "assets/D_8005941C.inc.c"
};
u8 D_80059A1C[0x600] = {
#include "assets/D_80059A1C.inc.c"
};
u8 D_8005A01C[0x600] = {
#include "assets/D_8005A01C.inc.c"
};
u8 D_8005A61C[0x600] = {
#include "assets/D_8005A61C.inc.c"
};
u8 D_8005AC1C[0x600] = {
#include "assets/D_8005AC1C.inc.c"
};
u8 D_8005B21C[0x200] = {
#include "assets/D_8005B21C.inc.c"
};
u16 D_8005B41C[0x200] = {
#include "assets/D_8005B41C.inc.c"
};
u8 D_8005B81C[0x600] = {
#include "assets/D_8005B81C.inc.c"
};
u8 D_8005BE1C[0x600] = {
#include "assets/D_8005BE1C.inc.c"
};
u8 D_8005C41C[0x600] = {
#include "assets/D_8005C41C.inc.c"
};
u8 D_8005CA1C[0x600] = {
#include "assets/D_8005CA1C.inc.c"
};
u8 D_8005D01C[0x600] = {
#include "assets/D_8005D01C.inc.c"
};
u8 D_8005D61C[0x600] = {
#include "assets/D_8005D61C.inc.c"
};
u8 D_8005DC1C[0x600] = {
#include "assets/D_8005DC1C.inc.c"
};
u8 D_8005E21C[0x200] = {
#include "assets/D_8005E21C.inc.c"
};
Vtx D_8005E420[4] = {
    {{ { 8, 23, 0 }, 0, { 960, 0 }, { 0, 0, 0, 0 } }},
    {{ { -8, 23, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 8, 0, 0 }, 0, { 960, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -8, 0, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Vtx D_8005E460[4] = {
    {{ { 8, 32, 0 }, 0, { 960, 0 }, { 0, 0, 0, 0 } }},
    {{ { -8, 32, 0 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 8, 0, 0 }, 0, { 960, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -8, 0, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Gfx D_8005E4A0[13] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)D_8005841C }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_8005E51C (undefined_syms.txt) is D_8005E508 + 0x14. */
Gfx D_8005E508[13] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)D_8005B41C }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8005E570[3] = {
    {{ 0x0400103F, (u32)D_8005E420 }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8005E588[3] = {
    {{ 0x0400103F, (u32)D_8005E460 }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_8005E5AC (undefined_syms.txt) is D_8005E5A0[1].b. */
D2DlPair D_8005E5A0[2] = {
    { D_8005E4A0, D_8005E570 }, { D_8005E508, D_8005E588 },
};
u8 *D_8005E5B0[8] = {
    D_8005881C, D_80058E1C, D_8005941C, D_80059A1C,
    D_8005A01C, D_8005A61C, D_8005AC1C, D_8005B21C,
};
u8 *D_8005E5D0[8] = {
    D_8005B81C, D_8005BE1C, D_8005C41C, D_8005CA1C,
    D_8005D01C, D_8005D61C, D_8005DC1C, D_8005E21C,
};
u8 **D_8005E5F0[2] = {
    D_8005E5B0, D_8005E5D0,
};
u16 D_8005E5F8[0x200] = {
#include "assets/D_8005E5F8.inc.c"
};
u8 D_8005E9F8[0x2000] = {
#include "assets/D_8005E9F8.inc.c"
};
Vtx D_800609F8[4] = {
    {{ { 1, 1, 1 }, 0, { 1984, 0 }, { 0, 0, 0, 0 } }},
    {{ { -1, 1, 1 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 1, -1, 1 }, 0, { 1984, 1984 }, { 0, 0, 0, 0 } }},
    {{ { -1, -1, 1 }, 0, { 0, 1984 }, { 0, 0, 0, 0 } }},
};
Gfx D_80060A38[16] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xFD100000, (u32)D_8005E5F8 }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0x0400103F, (u32)D_800609F8 }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
u8 D_80060AB8[0x100] = {
#include "assets/D_80060AB8.inc.c"
};
Vtx D_80060BB8[4] = {
    {{ { 1, 2, 1 }, 0, { 448, 0 }, { 0, 0, 0, 0 } }},
    {{ { -1, 2, 1 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    {{ { 1, -2, 1 }, 0, { 448, 960 }, { 0, 0, 0, 0 } }},
    {{ { -1, -2, 1 }, 0, { 0, 960 }, { 0, 0, 0, 0 } }},
};
Gfx D_80060BF8[10] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFCFF9BFF, 0xFFFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0x0400103F, (u32)D_80060BB8 }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
/* D_80060C4C (undefined_syms.txt) is D_80060C48[0].dl. */
D2SegDl D_80060C48[8] = {
    { 0x00D86970, 0x01001300 }, { 0x00D8B170, 0x01001300 }, { 0x00D8F970, 0x01002410 }, { 0x00D92D70, 0x01003630 },
    { 0x00D96570, 0x01003630 }, { 0x00D99D70, 0x01003630 }, { 0x00D9D570, 0x01003630 }, { 0x00DA0D70, 0x01003630 },
};
u8 D_80060C88[40] = {
    0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
    0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0x78, 0x78, 0x78, 0x78, 0x78, 0x96, 0x96, 0x96, 0x78, 0x78, 0, 0, 0, 0,
};
s8 D_80060CB0 = 2;
u8 D_80060CB4[88][2] = {
    { 0x10, 0x10 }, { 0x10, 0x0D }, { 0x10, 0x10 }, { 0x10, 0x10 }, { 0x0C, 0x0C }, { 8, 8 }, { 0x10, 0x0B }, { 0x10, 0x0B },
    { 0x0C, 0x0A }, { 0x0C, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 0x52, 0x0D }, { 0x18, 0x0F }, { 0x1C, 0x0D }, { 0x24, 0x0F }, { 0x1C, 0x0F }, { 0x24, 0x0D },
    { 0x14, 0x0B }, { 0x56, 0x0E }, { 0x36, 0x0C }, { 0x2A, 0x0C }, { 0x54, 7 }, { 0x50, 3 }, { 8, 0x0B }, { 8, 0x0B },
    { 8, 0x0B }, { 0x1A, 9 }, { 0x1A, 9 }, { 0x3A, 0x10 }, { 0x0C, 0x10 }, { 0x56, 0x0D }, { 0x0C, 0x0C }, { 0x0C, 0x0C },
    { 0x0C, 0x0C }, { 0x0C, 0x0C }, { 0x3C, 7 }, { 0x34, 3 }, { 0x3C, 0x14 }, { 0x20, 0x0C }, { 0x1C, 0x0D }, { 4, 4 },
    { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 4, 4 }, { 0x64, 0x0E }, { 0x96, 2 },
    { 2, 0x78 }, { 4, 4 }, { 0x7C, 0x0C }, { 0x1C, 0x0E }, { 0x1C, 0x0E }, { 0x1C, 0x0D }, { 0x14, 0x0E }, { 0x18, 0x0E },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A },
    { 8, 0x0A }, { 8, 0x0A }, { 8, 0x0A }, { 0x0C, 0x10 }, { 0x0C, 0x10 }, { 8, 1 }, { 0x1A, 9 }, { 0x1A, 9 },
};
s8 D_80060D64[16] = {
    -1, -2, -2, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -1, 0, 0,
};
u8 *D_80060D74[89] = {
    D_800620A0, D_800621A8, D_80062280, D_80062290, D_800622A0, D_80062338,
    D_80062380, D_80062438, D_800624F0, D_80062500, D_80062510, D_80062568,
    D_800625C0, D_80062618, D_80062670, D_800626C8, D_80062720, D_80062778,
    D_800627D0, D_80062828, D_80062880, D_800628D8, D_80062930, D_80062988,
    D_800629E0, D_80062A38, D_80062A90, D_80062EC8, D_80063038, D_800631B0,
    D_800633D8, D_80063588, D_80063598, D_80063680, D_80063B40, D_80063DD0,
    D_80063FD0, D_80064228, D_80064320, D_80064380, D_800643E0, D_80064440,
    D_80064538, D_80064630, D_800649D8, D_80064AA0, D_80064F08, D_80064FA0,
    D_80065038, D_800650D0, D_80065168, D_80065350, D_800653F8, D_80065408,
    D_80065418, D_80065590, D_800655A8, D_800655C0, D_800655D8, D_800655F0,
    D_80065608, D_80065620, D_80065638, D_80065648, D_80065780, D_80065790,
    D_800657A0, D_80065D78, D_80065F08, D_80066098, D_80066210, D_80066330,
    D_80066488, D_800664E0, D_80066538, D_80066590, D_800665E8, D_80066640,
    D_80066698, D_800666F0, D_80066748, D_800667A0, D_800667F8, D_80066850,
    D_80066918, D_800669E0, D_800669F0, D_80066AE8, NULL,
};
Gfx D_80060ED8[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_80060EF0[7] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC129A25, 0xFF37FFFF }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x0F0A4000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
f32 D_80060F28 = -1.0f;
f32 D_80060F2C = -1.0f;
Unk80060F30 D_80060F30[298] = {
    { 2, 0 }, { -2, -1 }, { 0, 0 }, { 0, 1 }, { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 },
    { 13, 6 }, { 13, 7 }, { 13, 8 }, { 13, 9 }, { 13, 10 }, { 13, 11 }, { 13, 12 }, { 13, 13 }, { 13, 14 }, { 13, 15 },
    { 13, 16 }, { 13, 17 }, { 15, 0 }, { 15, 1 }, { 15, 2 }, { 15, 3 }, { 15, 4 }, { 15, 5 }, { 15, 6 }, { 15, 7 },
    { 15, 8 }, { 15, 9 }, { 15, 10 }, { 15, 11 }, { 15, 12 }, { -2, -1 }, { 1, 0 }, { 14, 0 }, { 14, 1 }, { 14, 2 },
    { 14, 3 }, { 14, 4 }, { 14, 5 }, { 14, 6 }, { 14, 7 }, { 14, 8 }, { 14, 9 }, { 14, 10 }, { 14, 11 }, { 14, 12 },
    { 14, 14 }, { 14, 15 }, { 16, 0 }, { 16, 1 }, { 16, 2 }, { 16, 3 }, { 16, 4 }, { 16, 6 }, { 16, 7 }, { 16, 8 },
    { 16, 9 }, { 16, 10 }, { 16, 11 }, { 16, 12 }, { 16, 13 }, { 16, 14 }, { -2, -1 }, { 16, 5 }, { -2, -1 }, { 16, 21 },
    { -2, -1 }, { 31, 0 }, { 31, 1 }, { 31, 2 }, { -1, -1 }, { 3, 0 }, { -2, -1 }, { 16, 15 }, { 16, 16 }, { 16, 17 },
    { 16, 18 }, { 16, 19 }, { 16, 20 }, { -2, -1 }, { 3, 1 }, { -2, -1 }, { 32, 0 }, { 32, 1 }, { 32, 2 }, { -1, -1 },
    { 5, 0 }, { -2, -1 }, { 5, 1 }, { -2, -1 }, { 4, 0 }, { 4, 1 }, { 4, 2 }, { 17, 0 }, { 17, 1 }, { 17, 2 },
    { 17, 3 }, { 17, 4 }, { 17, 5 }, { 17, 6 }, { 17, 7 }, { 17, 8 }, { 18, 0 }, { 18, 1 }, { 18, 2 }, { 18, 3 },
    { 18, 4 }, { -2, -1 }, { 6, 0 }, { 19, 0 }, { 19, 1 }, { 19, 2 }, { 19, 3 }, { 20, 0 }, { 20, 1 }, { 20, 2 },
    { 20, 3 }, { 20, 4 }, { 20, 5 }, { 20, 6 }, { 20, 7 }, { 20, 8 }, { 20, 9 }, { 20, 10 }, { 20, 11 }, { -2, -1 },
    { 18, 6 }, { -2, -1 }, { 18, 5 }, { -2, -1 }, { 18, 7 }, { -2, -1 }, { 33, 0 }, { 33, 1 }, { 33, 2 }, { -2, -1 },
    { 27, 0 }, { -2, -1 }, { 26, 0 }, { 26, 1 }, { 26, 2 }, { 26, 3 }, { 26, 4 }, { -1, -1 }, { 7, 0 }, { -2, -1 },
    { 7, 1 }, { -2, -1 }, { 8, 0 }, { 8, 1 }, { 22, 0 }, { 22, 1 }, { 22, 2 }, { 22, 3 }, { 22, 4 }, { 22, 5 },
    { 22, 6 }, { 22, 7 }, { 22, 8 }, { 22, 9 }, { 22, 10 }, { 22, 11 }, { 22, 12 }, { 22, 13 }, { 22, 14 }, { 22, 15 },
    { 22, 16 }, { 22, 17 }, { 22, 18 }, { 22, 19 }, { 22, 20 }, { 22, 21 }, { 21, 0 }, { 21, 1 }, { 21, 2 }, { 21, 3 },
    { 21, 4 }, { 21, 5 }, { 21, 6 }, { 21, 7 }, { 21, 8 }, { 21, 9 }, { 21, 10 }, { 21, 11 }, { 21, 12 }, { -2, -1 },
    { 22, 22 }, { -2, -1 }, { 22, 23 }, { -2, -1 }, { 28, 0 }, { -1, -1 }, { 9, 0 }, { -2, -1 }, { 23, 0 }, { 23, 1 },
    { 23, 2 }, { 23, 3 }, { 23, 4 }, { 23, 5 }, { -2, -1 }, { 23, 19 }, { -2, -1 }, { 23, 20 }, { 23, 21 }, { -2, -1 },
    { 29, 0 }, { -1, -1 }, { 11, 2 }, { -2, -1 }, { 23, 22 }, { 23, 23 }, { 23, 24 }, { 23, 25 }, { -2, -1 }, { 23, 6 },
    { 23, 7 }, { 23, 8 }, { 23, 9 }, { 23, 10 }, { 23, 11 }, { 23, 12 }, { 23, 13 }, { 23, 14 }, { 23, 15 }, { 23, 16 },
    { 23, 17 }, { 23, 18 }, { 11, 0 }, { -2, -1 }, { 30, 0 }, { 30, 1 }, { 30, 2 }, { 30, 3 }, { 30, 4 }, { 30, 5 },
    { 30, 6 }, { 30, 7 }, { 30, 8 }, { 30, 9 }, { 30, 10 }, { 30, 11 }, { 30, 12 }, { 30, 13 }, { 30, 14 }, { 30, 15 },
    { 11, 1 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 11, 6 }, { 11, 7 }, { -1, -1 }, { 12, 0 }, { 12, 1 }, { 25, 0 },
    { 25, 1 }, { 35, 0 }, { -1, -1 }, { 25, 5 }, { 25, 8 }, { 25, 9 }, { 25, 2 }, { 25, 3 }, { 25, 4 }, { 12, 2 },
    { -1, -1 }, { 10, 0 }, { 10, 1 }, { 24, 0 }, { 24, 1 }, { 24, 2 }, { -1, -1 }, { 0, 2 }, { 0, 3 }, { 0, 4 },
    { 14, 13 }, { 34, 0 }, { 34, 1 }, { 34, 2 }, { 34, 3 }, { 34, 4 }, { 34, 5 }, { 34, 6 }, { 34, 7 }, { 34, 8 },
    { 34, 9 }, { 34, 10 }, { 15, 13 }, { 25, 6 }, { 25, 7 }, { 25, 24 }, { 25, 25 }, { -8, -1 },
};
s16 D_80061184[108] = {
    150, 10, 90, 115, 143, 128, 131, 70, 98, 167, -1, -1,
    -1, -1, -1, -1, -1, -1, 150, 162, 132, 152, 70, 80,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    187, 88, 134, 31, 100, 164, 171, 82, 142, 140, 107, 113,
    131, 155, 96, 147, 135, 17, 34, 63, 182, 47, 27, 74,
    185, 150, 178, 166, -1, -1, -1, -1, -1, -1, -1, -1,
    67, 54, 122, 36, 125, 62, 24, 82, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 177, 88, 88, 98, 70, 97,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};
void *D_8006125C[6] = {
    (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000,
};
void *D_80061274[144] = {
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
    (void*)0x801C0200, (void*)0x801C09A0, (void*)0x801C1140, (void*)0x801C18E0, (void*)0x801C2080, (void*)0x801C2820,
    (void*)0x801C2FC0, (void*)0x801C3760, (void*)0x801C3F00, (void*)0x801C46A0, (void*)0x801C4E40, (void*)0x801C55E0,
    (void*)0x801C5D80, (void*)0x801C6520, (void*)0x801C6CC0, (void*)0x801C7460, (void*)0x801C7C00, (void*)0x801C83A0,
    (void*)0x801C8B40, (void*)0x801C92E0, (void*)0x801C9A80, (void*)0x801CA220, (void*)0x801CA9C0, (void*)0x801CB160,
};
s16 D_800614B4[12] = {
    26, 20, 24, 24, 34, 13, 26, 21, 23, 24, 28, 13,
};
s16 D_800614CC[12] = {
    139, 125, 124, 124, 88, 133, 88, 95, 87, 78, 60, 96,
};
D2DstRom D_800614E4[10] = {
    { (void*)0x801C0000, 0x00F2FB70, 0x00F3ADD0 }, { (void*)0x801C0000, 0x00F3ADD0, 0x00F46030 },
    { (void*)0x801C0000, 0x00F46030, 0x00F51290 }, { (void*)0x801C0000, 0x00F51290, 0x00F5C4F0 },
    { (void*)0x801C0000, 0x00F5C4F0, 0x00F67750 }, { (void*)0x801C0000, 0x00F67750, 0x00F729B0 },
    { (void*)0x801C0000, 0x00F729B0, 0x00F73050 }, { (void*)0x801C0000, 0x00F73050, 0x00F73730 },
    { (void*)0x801C0000, 0x00F73730, 0x00F73F90 }, { (void*)0x801C0000, 0x00F73F90, 0x00F74890 },
};
void *D_8006155C[4] = {
    (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000, (void*)0x801C0000,
};
void *D_8006156C[8] = {
    (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200,
    (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200, (void*)0x801C0200,
};
u8 D_8006158C[4][3] = {
    { 0x41, 0x12, 0 }, { 0x41, 0x13, 0 }, { 0x60, 0x11, 0 }, { 0x63, 0x12, 0 },
};
s16 D_80061598[8] = {
    127, 112, 127, 112, 112, 112, 110, 112,
};
#ifndef NON_MATCHING /* func_8002B844's local ids[] initializer in the NON_MATCHING C */
u8 D_800615A8[4] = {
    0x28, 0x27, 0x26, 0,
};
#endif
s16 D_800615AC[8][2] = {
    { 138, 0 }, { 159, 0 }, { 179, 1 }, { 199, 2 }, { 219, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};
s16 D_800615CC[5][2] = {
    { 138, 0 }, { 159, 0 }, { 179, 1 }, { 199, 2 }, { 219, 2 },
};
#ifndef NON_MATCHING /* a function static in the NON_MATCHING C */
s32 D_800615E0 = -1;
#endif
Unk4Pals D_800615E4 = { { D_80068EB0, D_8006A8F0, D_8006B4D8, D_80069A98 } };
Unk4x2Ptrs D_800615F4 = { { { D_800690B8, D_800695A8 }, { D_8006AAF8, D_8006AFE8 }, { D_8006B6E0, D_8006BBD0 }, { D_80069CA0, D_8006A2C8 } } };
Unk4Words D_80061614 = { { 32, 32, 32, 24 } };
Unk4Words D_80061624 = { { 26, 26, 26, 20 } };
Unk4Ptrs D_80061634 = { { D_80067090, D_80067898, D_800680A0, D_800688A8 } };

void func_80035350(s32, s32, u8 *);







void func_8002F6D8(s32 ndigits, s32 x, s32 y, u32 value) {
    s32 i;
    u64 div = 1000000000;
    s64 v = value;
    s8 digits[10];
    s32 j;
    u8 msg[5] = {
#include "assets/D_80061644.inc.c"
    };
    s32 n;

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
    for (n = ndigits - 1; n >= 0; n--) {
        i += digits[n];
        if (i != 0 || n == 0) {
            msg[3] = digits[n];
            func_80035350(x, y, msg);
        }
        x += 10;
    }
}

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
