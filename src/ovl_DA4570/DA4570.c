#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    u8 w;
    u8 h;
    char unk6[2];
    u8* pixels;
    u16* palette;
} UnkStruct_801004E8;

typedef struct {
    s32 width;
    s32 height;
    s32 advance;
    s32 lineHeight;
} UnkFont_8010566C;

typedef struct {
    u32 unk0;
    u32 unk4;
    u16 unk8;
    u8 unkA;
    char unkB[3];
    u8 name[18];
} UnkStruct_80107080;

extern u8 D_80101FA0_ovl_DA4570[];
extern u8 D_80101FC0_ovl_DA4570[];
extern UnkStruct_801004E8 D_80103F28_ovl_DA4570[];
extern UnkStruct_801004E8 D_80104DD8_ovl_DA4570[];
extern UnkStruct_801004E8 D_80105288_ovl_DA4570[];
extern UnkStruct_801004E8 D_801053E8_ovl_DA4570[];
extern UnkStruct_801004E8 D_801053F8_ovl_DA4570[];
extern u8 D_803245A0[];

/* .data 80105660..80107050 (the earlier overlay data is still asm) */
s32 D_80105660_ovl_DA4570 = 0;
u16* D_80105664_ovl_DA4570[2] = { (u16*) 0x80200000, (u16*) 0x80225800 };
UnkFont_8010566C D_8010566C_ovl_DA4570[1] = { { 10, 13, 10, 14 } };
u16 D_8010567C_ovl_DA4570[8] = {
#include "assets/D_8010567C_ovl_DA4570.inc.c"
};
/* 4bpp font bitmap, 0x1980 bytes */
u8 D_8010568C_ovl_DA4570[0x1980] = {
#include "assets/D_8010568C_ovl_DA4570.inc.c"
};
/* 7 palettes of 4 colours */
u16 D_8010700C_ovl_DA4570[28] = {
#include "assets/D_8010700C_ovl_DA4570.inc.c"
};
u16* D_80107044_ovl_DA4570 = &D_8010700C_ovl_DA4570[4];
/* func_80101C80's two statics follow at 80107048/4C */
/* .bss 80107080..80107300 */
UnkStruct_80107080 D_80107080_ovl_DA4570[16];
s32 D_80107280_ovl_DA4570;
s32 D_80107284_ovl_DA4570;
s32 D_80107288_ovl_DA4570[16];
s16 D_801072C8_ovl_DA4570;
s16 D_801072CA_ovl_DA4570;
s16 D_801072CC_ovl_DA4570;
u8 D_801072CE_ovl_DA4570;
u8 D_801072CF_ovl_DA4570;
s16 D_801072D0_ovl_DA4570;
s16 D_801072D2_ovl_DA4570;
s16 D_801072D4_ovl_DA4570;
s32 D_801072D8_ovl_DA4570;
s32 D_801072DC_ovl_DA4570;
u16* D_801072E0_ovl_DA4570;
OSMesgQueue* D_801072E4_ovl_DA4570;
OSMesgQueue* D_801072E8_ovl_DA4570;
OSMesg D_801072EC_ovl_DA4570;
u16* D_801072F0_ovl_DA4570;
s16 D_801072F4_ovl_DA4570;
s16 D_801072F6_ovl_DA4570;

void func_80100000_ovl_DA4570(u16 arg0, u8* arg1);
void func_801000E4_ovl_DA4570(s32 arg0);
void func_8010022C_ovl_DA4570(s16 arg0, s16 arg1);
void func_8010028C_ovl_DA4570(u8* arg0, s32 arg1);
void func_801002F0_ovl_DA4570(s32 arg0);
void func_80100310_ovl_DA4570(s16 x, s16 y, s16 w, s16 h, u8* pixels, u16* palette, u8 mode);
void func_801004E8_ovl_DA4570(UnkStruct_801004E8* arg0, s32 arg1);
void func_80100620_ovl_DA4570(s32 arg0);
void func_80100854_ovl_DA4570(u16 arg0);
void func_80100944_ovl_DA4570(void);
void func_80101C80_ovl_DA4570(s32 x, s32 y, u8* str);

void func_80100000_ovl_DA4570(u16 arg0, u8* arg1) {
    s32 var_v0 = arg0;

    if (var_v0 >= 1000) {
        var_v0 = 999;
    }
    arg1[0] = (var_v0 / 100) + (var_v0 >= 100) + 0xF;
    arg1[1] = ((var_v0 % 100) / 10) + (var_v0 >= 10) + 0xF;
    arg1[2] = (var_v0 % 10) + 0x10;
}

void func_801000E4_ovl_DA4570(s32 arg0) {
    u32* src;
    u16* dst;
    s32 i;
    s32 shift;
    u16 px;

    if (arg0 == 1) {
        D_801072F0_ovl_DA4570 += 3;
        return;
    }
    if (arg0 == 10) {
        D_801072F6_ovl_DA4570 += 13;
        func_8010022C_ovl_DA4570(D_801072F4_ovl_DA4570, D_801072F6_ovl_DA4570);
        return;
    }
    if ((arg0 < 0xF) || (arg0 > D_80107280_ovl_DA4570)) {
        arg0 = 0x3B;
    }
    arg0 -= 0xF;
    src = (u32*) (D_8010568C_ovl_DA4570 + (((arg0 & 0xF8) * 0x60) / 2) + (((arg0 & 7) * 8) / 2));
    dst = D_801072F0_ovl_DA4570;
    for (i = 0; i < 12; i++) {
        for (shift = 28; shift >= 0; shift -= 4) {
            px = (*src >> shift) & 0xF;
            if (px != 0) {
                *dst = D_80107044_ovl_DA4570[px];
            }
            dst++;
        }
        dst += 312;
        src += 8;
    }
    D_801072F0_ovl_DA4570 += 9;
}

void func_8010022C_ovl_DA4570(s16 arg0, s16 arg1) {
    D_801072F4_ovl_DA4570 = arg0;
    D_801072F6_ovl_DA4570 = arg1;
    D_801072F0_ovl_DA4570 = D_801072E0_ovl_DA4570 + (arg0 + (arg1 * 320));
}

void func_80100284_ovl_DA4570(void) {
}

void func_8010028C_ovl_DA4570(u8* arg0, s32 arg1) {
    while (arg1-- && *arg0) {
        func_801000E4_ovl_DA4570(*arg0++);
    }
}

void func_801002F0_ovl_DA4570(s32 arg0) {
    D_80107044_ovl_DA4570 = D_8010700C_ovl_DA4570 + arg0 * 4;
}

void func_80100310_ovl_DA4570(s16 x, s16 y, s16 w, s16 h, u8* pixels, u16* palette, u8 mode) {
    u16* dst = D_801072E0_ovl_DA4570 + (x + y * 320);
    u8* src = pixels;
    s32 i;
    s32 j;
    u8 c;
    u16 hi;
    u16 lo;

    if (mode == 5) {
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                *dst++ = palette[*src++];
            }
            dst += 320 - w;
        }
    } else if (mode == 2) {
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j += 2) {
                c = *src++;
                hi = c >> 4;
                lo = c & 0xF;
                if (hi != 0) {
                    *dst++ = palette[hi];
                } else {
                    dst++;
                }
                if (lo != 0) {
                    *dst++ = palette[lo];
                } else {
                    dst++;
                }
            }
            dst += 320 - w;
        }
    }
}

void func_801004E8_ovl_DA4570(UnkStruct_801004E8* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        func_80100310_ovl_DA4570(arg0[i].x, arg0[i].y, arg0[i].w, arg0[i].h, arg0[i].pixels, arg0[i].palette, 2);
    }
}

void func_8010055C_ovl_DA4570(void) {
    osWritebackDCacheAll();
    osRecvMesg(D_801072E8_ovl_DA4570, &D_801072EC_ovl_DA4570, OS_MESG_BLOCK);
    if ((s32) D_801072EC_ovl_DA4570 == 0x29D) {
        osViBlack(1);
        return;
    }
    if (D_801072DC_ovl_DA4570 != 0) {
        osViSwapBuffer(D_80105664_ovl_DA4570[D_80105660_ovl_DA4570 & 1]);
        D_801072E0_ovl_DA4570 = D_80105664_ovl_DA4570[++D_80105660_ovl_DA4570 & 1];
        D_801072DC_ovl_DA4570 = 0;
    }
}

void func_80100620_ovl_DA4570(s32 arg0) {
    u8 buf[3];
    s16 y;

    D_80107280_ovl_DA4570 = 0x94;
    if ((arg0 == D_801072CA_ovl_DA4570) && (D_801072C8_ovl_DA4570 >= 2) && (D_801072C8_ovl_DA4570 < 5)) {
        func_801002F0_ovl_DA4570(3);
    } else {
        func_801002F0_ovl_DA4570(1);
    }
    if (D_80107288_ovl_DA4570[arg0 + D_801072CE_ovl_DA4570] == 0) {
        y = arg0 * 13 + 0x58;
        func_8010022C_ovl_DA4570(0x52, y);

        func_8010028C_ovl_DA4570((&D_80107080_ovl_DA4570[arg0])[D_801072CE_ovl_DA4570].name, 16);
        if ((&D_80107080_ovl_DA4570[arg0])[D_801072CE_ovl_DA4570].unkA != 0) {
            func_801000E4_ovl_DA4570(0x3C);
            D_801072F0_ovl_DA4570 = D_801072F0_ovl_DA4570;
            func_801000E4_ovl_DA4570((&D_80107080_ovl_DA4570[arg0])[D_801072CE_ovl_DA4570].unkA);
        }
        func_8010022C_ovl_DA4570(0x100, y);
        func_80100000_ovl_DA4570(((&D_80107080_ovl_DA4570[arg0])[D_801072CE_ovl_DA4570].unk0 + 0xFF) >> 8, buf);
        func_8010028C_ovl_DA4570(buf, 3);
    }
    y = arg0 * 13 + 0x58;
    if (D_801072CE_ovl_DA4570 + arg0 < 9) {
        func_8010022C_ovl_DA4570(0x3C, y);
        func_801000E4_ovl_DA4570(D_801072CE_ovl_DA4570 + arg0 + 0x11);
    } else {
        func_8010022C_ovl_DA4570(0x37, y);
        func_801000E4_ovl_DA4570(0x11);
        func_8010022C_ovl_DA4570(0x3D, y);
        func_801000E4_ovl_DA4570(D_801072CE_ovl_DA4570 + arg0 + 7);
    }
    func_8010022C_ovl_DA4570(0x43, y);
    func_801000E4_ovl_DA4570(0x3E);
    D_80107280_ovl_DA4570 = 0x62;
}

void func_80100854_ovl_DA4570(u16 arg0) {
    u8 buf[4];

    func_801002F0_ovl_DA4570(1);
    func_80100000_ovl_DA4570(arg0, buf);
    func_8010022C_ovl_DA4570(200, 173);
    func_8010028C_ovl_DA4570(buf, 3);
}

void func_8010089C_ovl_DA4570(void) {
    func_80100310_ovl_DA4570(D_801072D0_ovl_DA4570, D_801072D2_ovl_DA4570, 16, 14, D_80101FC0_ovl_DA4570, (u16*) D_80101FA0_ovl_DA4570, 2);
}

void func_801008F0_ovl_DA4570(s32 arg0) {
    func_80100944_ovl_DA4570();
    func_801004E8_ovl_DA4570(D_80104DD8_ovl_DA4570, 75);
    func_801004E8_ovl_DA4570(D_80105288_ovl_DA4570, 22);
    func_80101C80_ovl_DA4570(0x34, 0x4E, arg0);
}

void func_80100944_ovl_DA4570(void) {
    s32 i;

    func_801004E8_ovl_DA4570(D_80103F28_ovl_DA4570, 235);
    func_80100854_ovl_DA4570(D_801072D8_ovl_DA4570);
    if (D_801072CE_ovl_DA4570 != 0) {
        func_801004E8_ovl_DA4570(D_801053E8_ovl_DA4570, 1);
    }
    if (D_801072CE_ovl_DA4570 < 10) {
        func_801004E8_ovl_DA4570(D_801053F8_ovl_DA4570, 1);
    }
    for (i = 0; i < 6; i++) {
        func_80100620_ovl_DA4570(i);
    }
    D_801072DC_ovl_DA4570 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_801009EC_ovl_DA4570.s")

void func_80101C80_ovl_DA4570(s32 x, s32 y, u8* str) {
    s32 rowOff = 0;
    s32 curX = x;
    s32 curY = y;
    UnkFont_8010566C* f;
    u16* dst;
    u8* src;
    s32 rows;
    s32 n;
    u16 px;
    s32 arg;
    static s32 font = 0;
    static s32 spacing = 0;

    if (*str != 0xFF) { do {
        if (*str & 0x80) {
            arg = *str & 0x1F;
            switch (*str & 0x60) {
                case 0x00:
                    rowOff = (arg * 0x130) / 2;
                        rowOff = rowOff * 13;
                    break;
                case 0x20:
                    break;
                case 0x40:
                    if (arg < 0x10) {
                        font = arg;
                    } else {
                        spacing = arg;
                    }
                    break;
                case 0x60:
                    switch (arg) {
                        case 0:
                            curX = x;
                            curY += D_8010566C_ovl_DA4570[font].lineHeight;
                            break;
                        case 30:
                            break;
                    }
                    break;
            }
        } else {
            f = &D_8010566C_ovl_DA4570[font];
            if (*str == 0x7F) {
                curX += f->advance + spacing;
            } else {
                dst = D_801072E0_ovl_DA4570 + (curY * 320 + curX);
                arg = *str & 0x7F;
                src = D_803245A0 + (f->width >> 1) * arg + rowOff;
                for (rows = f->height; rows != 0;) {
                    for (n = f->width >> 1; n != 0; n--) {
                        if ((px = D_8010567C_ovl_DA4570[(*src & 0xF0) >> 4]) & 1) {
                            *dst = px;
                        }
                        dst++;
                        if ((px = D_8010567C_ovl_DA4570[*src++ & 0xF]) & 1) {
                            *dst = px;
                        }
                        dst++;
                    }
                    dst += 320 - f->width;
                    src += 0x98 - (f->width >> 1);
                    rows--;
                }
                curX += f->advance + spacing;
            }
        }
    } while (*++str != 0xFF);
    }
}
