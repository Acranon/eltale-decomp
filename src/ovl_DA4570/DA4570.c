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

extern u8 D_80101FA0_ovl_DA4570[];
extern u8 D_80101FC0_ovl_DA4570[];
extern UnkStruct_801004E8 D_80103F28_ovl_DA4570[];
extern UnkStruct_801004E8 D_80104DD8_ovl_DA4570[];
extern UnkStruct_801004E8 D_80105288_ovl_DA4570[];
extern UnkStruct_801004E8 D_801053E8_ovl_DA4570[];
extern UnkStruct_801004E8 D_801053F8_ovl_DA4570[];
extern s32 D_80105660_ovl_DA4570;
extern u16* D_80105664_ovl_DA4570[];
extern u8 D_8010568C_ovl_DA4570[];
extern u16 D_8010700C_ovl_DA4570[];
extern u16* D_80107044_ovl_DA4570;
extern s32 D_80107280;
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
void func_80100310_ovl_DA4570(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8* arg4, u16* arg5, s32 arg6);
void func_801004E8_ovl_DA4570(UnkStruct_801004E8* arg0, s32 arg1);
void func_80100620_ovl_DA4570(s32 arg0);
void func_80100854_ovl_DA4570(u16 arg0);
void func_80100944_ovl_DA4570(void);
void func_80101C80_ovl_DA4570(s32 arg0, s32 arg1, s32 arg2);

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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_8010028C_ovl_DA4570.s")

void func_801002F0_ovl_DA4570(s32 arg0) {
    D_80107044_ovl_DA4570 = D_8010700C_ovl_DA4570 + arg0 * 4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_80100310_ovl_DA4570.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_DA4570/DA4570/func_80100620_ovl_DA4570.s")

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
