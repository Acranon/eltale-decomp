#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
} UnkStruct_8020EF00;

extern Gfx* D_8007A184;
extern u16 D_80092C86;
extern s32 D_8020F1E0_ovl_title;
extern Gfx D_8020F208_ovl_title[];
extern Gfx D_8020F470_ovl_title[];
extern s32 D_8020F4F0_ovl_title;
extern s32 D_8020F4F4_ovl_title;
extern s32 D_80226D90;
extern s32 D_80226D94;
extern s32 D_80226D98;
extern s32 D_80226D9C;
extern s32 D_80226DA0;
extern s32 D_80226DA4;
extern s8 D_80226DB0;
extern s32 D_80226DB4;
extern s32 D_80226DC0;

void func_80029A88(s32, s32, s32);
s32 func_8020C178_ovl_title(void);
void func_8020CC70_ovl_title(s32);

void func_8020C0D0_ovl_title(void) {
    D_80226D90 = 0;
    D_80226DA4 = 0;
    D_8020F4F4_ovl_title = 1;
    D_8020F4F0_ovl_title = 0;
    D_80226D94 = 1;
    D_80226D9C = 0;
    D_80226DA0 = 8;
    D_80226D98 = 0;
}

s32 func_8020C11C_ovl_title(void) {
    if (func_8020C178_ovl_title() == 0) {
        if (D_80226DA4 == 0) {
            return 1;
        }
        if (D_80226DA4 == 0xF) {
            D_80226DA4 = 0;
            return 0;
        }
    }
    return 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAB5F0/func_8020C178_ovl_title.s")

void func_8020C7A8_ovl_title(void) {
    s32 var_v0;

    gSPDisplayList(D_8007A184++, D_8020F208_ovl_title);
    gDPSetEnvColor(D_8007A184++, 0, 0, 0, D_80226D9C);

    func_8020CC70_ovl_title((u32)D_80226DA4);
    D_80226D9C += D_80226DA0;
    if (D_80226D9C >= 0x100) {
        D_80226D9C = 0xFF;
        D_80226DA0 = -D_80226DA0;
    } else if (D_80226D9C < 0) {
        D_80226D9C = 0;
        D_80226D9C = 0;
        D_80226DA0 = -D_80226DA0;
    }
    D_80226DB4 = D_80226D9C;
    if (D_8020F4F0_ovl_title == 0) {
        if ((D_80226DA4 == 0) && (D_80092C86 & 0x1000)) {
            func_80029A88(1, 0xFF, 0x40);
            D_80226D9C = 0;
            D_80226DA0 = 0x80;
            D_80226DA4 = 1;
            D_80226D94 = 0x3C;
        } else if (D_80226DA4 == 2) {
            if (D_80092C86 & 0xB000) {
                func_80029A88(1, 0xFF, 0x40);
                D_80226D9C = 0;
                D_80226DA0 = 0x80;
                D_80226DA4 = 3;
                D_80226D94 = 0x3C;
                D_8020F1E0_ovl_title = 1;
            } else if (D_80092C86 & 0x4000) {
                func_80029A88(2, 0xFF, 0x40);
                D_80226D9C = 0xFF;
                D_80226DA0 = 0x80;
                D_80226DA4 = 4;
                D_80226D94 = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((D_80226DA4 == 8) || (D_80226DA4 == 7)) {
            if (D_80092C86 & 0xB000) {
                func_80029A88(1, 0xFF, 0x40);
                D_80226D9C = 0;
                D_80226DA0 = 0x80;
                D_8020F1E0_ovl_title = 1;
                D_80226D94 = 0x3C;
                if (D_80226DB0 == 0) {
                    if (D_80226DA4 == 8) {
                        D_80226DA4 = 0xB;
                    } else {
                        D_80226DA4 = 0xD;
                    }
                } else if (D_80226DA4 == 8) {
                    D_80226DA4 = 0xC;
                } else {
                    D_80226DA4 = 0xE;
                }
            } else if (D_80092C86 & 0x4000) {
                func_80029A88(2, 0xFF, 0x40);
                D_80226D9C = 0xFF;
                D_80226DA0 = 0x80;
                D_80226DA4 = 2;
                D_80226D94 = 2;
                D_8020F1E0_ovl_title = 1;
            }
        } else if (D_80226DA4 == 6) {
            if (D_80092C86 & 0xF000) {
                func_80029A88(2, 0xFF, 0x40);
                D_80226D9C = 0xFF;
                D_80226DA0 = 0x80;
                D_80226DA4 = 2;
                D_80226D94 = 2;
            }
        } else if (D_80226DA4 == 9) {
            if (D_80092C86 & 0xB000) {
                func_80029A88(1, 0xFF, 0x40);
                D_8020F1E0_ovl_title = 1;
            }
        } else if ((D_80226DA4 == 0xA) && (D_80092C86 & 0xB000)) {
            func_80029A88(1, 0xFF, 0x40);
            D_8020F1E0_ovl_title = 1;
        }
    }
    D_80226D94 -= 1;
}

void func_8020CBE4_ovl_title(void) {
    gSPDisplayList(D_8007A184++, D_8020F208_ovl_title);
    gDPSetEnvColor(D_8007A184++, 0x00, 0x00, 0x00, 0xFF);

    func_8020CC70_ovl_title(D_80226DA4);
    if (--D_80226D94 == 0) {
        D_80226DA4 = 0xF;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAB5F0/func_8020CC70_ovl_title.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAB5F0/func_8020EF00_ovl_title.s")

void func_8020EFE4_ovl_title(UnkStruct_8020EF00* arg0) {
    s32 rgbColorValue;
    s32 alpha;

    arg0->unk2 -= 1;
    if (D_8020F4F0_ovl_title & 1) {
        arg0->unk8 += arg0->unk4;
    } else {
        arg0->unk8 -= arg0->unk4;
    }
    switch (D_8020F4F0_ovl_title) {
    case 3:
    case 4:
        rgbColorValue = 255;
        break;
    case 1:
    case 2:
        rgbColorValue = 0;
        break;
    default:
        rgbColorValue = 0;
        break;
    }

    if (arg0->unk8 <= 0.0f) {
        D_8020F4F0_ovl_title = 0;
        arg0->unk8 = 0.0f;
        arg0->unk0 = 0;
    } else if (arg0->unk8 > 255.0f) {
        D_8020F4F0_ovl_title = 0;
        arg0->unk8 = 255.0f;
        arg0->unk0 = 0;
    }
    if (arg0->unk2 == 0) {
        if ((D_8020F4F0_ovl_title == 3) || (D_8020F4F0_ovl_title == 1)) {
            D_8020F4F0_ovl_title = 0;
            arg0->unk8 = 255.0f;
            arg0->unk0 = 0;
        } else if ((D_8020F4F0_ovl_title == 4) || (D_8020F4F0_ovl_title == 2)) {
            D_8020F4F0_ovl_title = 0;
            arg0->unk8 = 0.0f;
            arg0->unk0 = 0;
        }
    }

    alpha = arg0->unk8;
    gDPPipeSync(D_8007A184++);
    gDPSetPrimColor(D_8007A184++, 0, 0, rgbColorValue, rgbColorValue, rgbColorValue, alpha);
    gDPSetRenderMode(D_8007A184++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(D_8007A184++, D_8020F470_ovl_title);
    gDPFillRectangle(D_8007A184++, 0, 0, 336, 960);

    D_80226DC0 = rgbColorValue;
}
