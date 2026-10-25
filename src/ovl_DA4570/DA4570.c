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
extern s32 D_80105660_ovl_DA4570;
extern u16* D_80105664_ovl_DA4570[];
extern UnkFont_8010566C D_8010566C_ovl_DA4570[];
extern u16 D_8010567C_ovl_DA4570[];
extern u8 D_8010568C_ovl_DA4570[];
extern s32 D_80107048_ovl_DA4570;
extern s32 D_8010704C_ovl_DA4570;
extern u8 D_803245A0[];
extern u16 D_8010700C_ovl_DA4570[];
extern u16* D_80107044_ovl_DA4570;
extern UnkStruct_80107080 D_80107080[];
extern s32 D_80107280;
extern s32 D_80107288[];
extern s16 D_801072C8;
extern s16 D_801072CA;
extern u8 D_801072CE;
extern s16 D_801072D0;
extern s16 D_801072D2;
extern u16 D_801072DA;
extern s32 D_801072DC;
extern u16* D_801072E0;
extern OSMesgQueue* D_801072E8;
extern OSMesg D_801072EC;
extern u16* D_801072F0;
extern s16 D_801072F4;
extern s16 D_801072F6;

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
        D_801072F0 += 3;
        return;
    }
    if (arg0 == 10) {
        D_801072F6 += 13;
        func_8010022C_ovl_DA4570(D_801072F4, D_801072F6);
        return;
    }
    if ((arg0 < 0xF) || (arg0 > D_80107280)) {
        arg0 = 0x3B;
    }
    arg0 -= 0xF;
    src = (u32*) (D_8010568C_ovl_DA4570 + (((arg0 & 0xF8) * 0x60) / 2) + (((arg0 & 7) * 8) / 2));
    dst = D_801072F0;
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
    D_801072F0 += 9;
}

void func_8010022C_ovl_DA4570(s16 arg0, s16 arg1) {
    D_801072F4 = arg0;
    D_801072F6 = arg1;
    D_801072F0 = D_801072E0 + (arg0 + (arg1 * 320));
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
    u16* dst = D_801072E0 + (x + y * 320);
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
    osRecvMesg(D_801072E8, &D_801072EC, OS_MESG_BLOCK);
    if ((s32) D_801072EC == 0x29D) {
        osViBlack(1);
        return;
    }
    if (D_801072DC != 0) {
        osViSwapBuffer(D_80105664_ovl_DA4570[D_80105660_ovl_DA4570 & 1]);
        D_801072E0 = D_80105664_ovl_DA4570[++D_80105660_ovl_DA4570 & 1];
        D_801072DC = 0;
    }
}

void func_80100620_ovl_DA4570(s32 arg0) {
    u8 buf[3];
    s16 y;

    D_80107280 = 0x94;
    if ((arg0 == D_801072CA) && (D_801072C8 >= 2) && (D_801072C8 < 5)) {
        func_801002F0_ovl_DA4570(3);
    } else {
        func_801002F0_ovl_DA4570(1);
    }
    if (D_80107288[arg0 + D_801072CE] == 0) {
        y = arg0 * 13 + 0x58;
        func_8010022C_ovl_DA4570(0x52, y);

        func_8010028C_ovl_DA4570((&D_80107080[arg0])[D_801072CE].name, 16);
        if ((&D_80107080[arg0])[D_801072CE].unkA != 0) {
            func_801000E4_ovl_DA4570(0x3C);
            D_801072F0 = D_801072F0;
            func_801000E4_ovl_DA4570((&D_80107080[arg0])[D_801072CE].unkA);
        }
        func_8010022C_ovl_DA4570(0x100, y);
        func_80100000_ovl_DA4570(((&D_80107080[arg0])[D_801072CE].unk0 + 0xFF) >> 8, buf);
        func_8010028C_ovl_DA4570(buf, 3);
    }
    y = arg0 * 13 + 0x58;
    if (D_801072CE + arg0 < 9) {
        func_8010022C_ovl_DA4570(0x3C, y);
        func_801000E4_ovl_DA4570(D_801072CE + arg0 + 0x11);
    } else {
        func_8010022C_ovl_DA4570(0x37, y);
        func_801000E4_ovl_DA4570(0x11);
        func_8010022C_ovl_DA4570(0x3D, y);
        func_801000E4_ovl_DA4570(D_801072CE + arg0 + 7);
    }
    func_8010022C_ovl_DA4570(0x43, y);
    func_801000E4_ovl_DA4570(0x3E);
    D_80107280 = 0x62;
}

void func_80100854_ovl_DA4570(u16 arg0) {
    u8 buf[4];

    func_801002F0_ovl_DA4570(1);
    func_80100000_ovl_DA4570(arg0, buf);
    func_8010022C_ovl_DA4570(200, 173);
    func_8010028C_ovl_DA4570(buf, 3);
}

void func_8010089C_ovl_DA4570(void) {
    func_80100310_ovl_DA4570(D_801072D0, D_801072D2, 16, 14, D_80101FC0_ovl_DA4570, (u16*) D_80101FA0_ovl_DA4570, 2);
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
    func_80100854_ovl_DA4570(D_801072DA);
    if (D_801072CE != 0) {
        func_801004E8_ovl_DA4570(D_801053E8_ovl_DA4570, 1);
    }
    if (D_801072CE < 10) {
        func_801004E8_ovl_DA4570(D_801053F8_ovl_DA4570, 1);
    }
    for (i = 0; i < 6; i++) {
        func_80100620_ovl_DA4570(i);
    }
    D_801072DC = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_801009EC_ovl_DA4570.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_80101C80_ovl_DA4570.s")
