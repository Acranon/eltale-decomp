#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
} UnkStruct_8020EF00;

typedef struct {
    s16 x;
    s16 y;
} UnkPos_8020F4DC;

typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
} UnkFade_8020F4F8;

extern Gfx* D_8007A184;
extern s32 D_80226DC0;
extern u8 D_8020FE10_ovl_title[];
extern u8 D_80210010_ovl_title[];
extern u8 D_80210D20_ovl_title[];

/* .data 8020F200..8020F510. The data before it (8020F1E0..F200) is DAB5F0.c's, still asm. */
s32 D_8020F200_ovl_title = 0;
Gfx D_8020F208_ovl_title[11] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xB6000000, 0xFFFFFFFF }},
    {{ 0xB7000000, 0x00000204 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xBA000903, 0x00000C00 }},
    {{ 0xBA001102, 0x00020000 }},
    {{ 0xB9000002, 0x0C087008 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xBA000C02, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F260_ovl_title[4] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x0F0A4000 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F280_ovl_title[5] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F2A8_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF4000000, 0x0706A02C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400800, 0x00000000 }},
    {{ 0xF2000000, 0x000D402C }},
    {{ 0xE41AC2B0, 0x000D4280 }},
    {{ 0xB4000000, 0x00000000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F300_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF406C000, 0x070D802C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400800, 0x00000000 }},
    {{ 0xF20D8000, 0x001B002C }},
    {{ 0xE42E02B0, 0x00204280 }},
    {{ 0xB4000000, 0x06C00000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F358_ovl_title[11] = {
    {{ 0xFD480057, (u32) D_80210D20_ovl_title }},
    {{ 0xF5480A00, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF40DA000, 0x0715C02C }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5400A00, 0x00000000 }},
    {{ 0xF21B4000, 0x002B802C }},
    {{ 0xE44342B0, 0x0032C280 }},
    {{ 0xB4000000, 0x0DA00000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F3B0_ovl_title[21] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xFD100000, (u32) D_8020FE10_ovl_title }},
    {{ 0xE8000000, 0x00000000 }},
    {{ 0xF5000100, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF0000000, 0x073FC000 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFD480063, (u32) D_80210010_ovl_title }},
    {{ 0xF5481800, 0x07000000 }},
    {{ 0xE6000000, 0x00000000 }},
    {{ 0xF4000000, 0x07168038 }},
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xF5481800, 0x00000000 }},
    {{ 0xF2000000, 0x00168038 }},
    {{ 0xE43342BC, 0x001C8280 }},
    {{ 0xB4000000, 0x00000000 }},
    {{ 0xB3000000, 0x04000400 }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F458_ovl_title[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xB8000000, 0x00000000 }},
};
Gfx D_8020F470_ovl_title[3] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xFC32FFFF, 0x1FFFF6FB }},
    {{ 0xB8000000, 0x00000000 }},
};
/* not referenced by name */
s32 D_8020F488_ovl_title[18] = {
    0x00000035, 0x000000A0, 0x00000000, 0x00000000, 0x00000036, 0x0000000C,
    0x00000081, 0x000000A0, 0x00000036, 0x00000000, 0x00000037, 0x0000000C,
    0x000000CB, 0x000000A0, 0x0000006D, 0x00000000, 0x00000042, 0x0000000C,
};
/* func_8020CC70's state; they become its statics once it is C */
s32 D_8020F4D0_ovl_title = 0;
s8 D_8020F4D4_ovl_title = 0;
s8 D_8020F4D8_ovl_title = 0;
UnkPos_8020F4DC D_8020F4DC_ovl_title[5] = { { 0x2A, 0xA0 }, { 0x77, 0xA1 }, { 0xBF, 0xA0 }, { 0, 0 }, { 0, 0 } };

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_title/DAC190/func_8020CC70_ovl_title.s")

s32 D_8020F4F0_ovl_title = 0;
s32 D_8020F4F4_ovl_title = 2;

void func_8020EFE4_ovl_title(UnkStruct_8020EF00* arg0);

void func_8020EF00_ovl_title(void) {
    static UnkFade_8020F4F8 fade = { 0 };

    if (D_8020F4F0_ovl_title == 0) {
        if (fade.unk0 != 0) {
            fade.unk0 = 0;
        }
    } else {
        if (fade.unk0 == 0) {
            fade.unk0 = -1;
            fade.unk4 = 255.0f / D_8020F4F4_ovl_title;
            fade.unk2 = D_8020F4F4_ovl_title;
            switch (D_8020F4F0_ovl_title) {
                case 1:
                case 3:
                    fade.unk8 = 0.0f;
                    break;
                case 2:
                case 4:
                    fade.unk8 = 255;
                    break;
                default:
                    fade.unk8 = 128.0f;
                    break;
            }
        }
        func_8020EFE4_ovl_title((UnkStruct_8020EF00*) &fade);
    }
}

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
