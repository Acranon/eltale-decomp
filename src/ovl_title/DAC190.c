#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
} UnkStruct_8020EF00;

extern Gfx* D_8007A184;
extern Gfx D_8020F470_ovl_title[];
extern s32 D_8020F4F0_ovl_title;
extern s32 D_8020F4F4_ovl_title;
extern s32 D_80226DC0;

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAC190/func_8020CC70_ovl_title.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAC190/func_8020EF00_ovl_title.s")

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
