#include "common.h"

#define GFX_WORDS(a, b)                    {                                          Gfx *_g = D_8007A184++;                _g->words.w0 = (a);                    _g->words.w1 = (b);                }

extern Gfx *D_8007A184;
extern s32 D_80212230_ovl_intro;
extern s32 D_80212250_ovl_intro;
extern s32 D_80212254_ovl_intro;
extern Gfx D_80212270_ovl_intro[];
extern u8 D_802650A0_ovl_intro[];
extern u16 D_80267048_ovl_intro[];
extern u8 D_80267250_ovl_intro[];
extern u16 D_80268018_ovl_intro[];
extern u8 D_80260490_ovl_intro[];
extern u8 D_80264740_ovl_intro[];
extern u16 D_80264E98_ovl_intro[];
extern u16 D_802615A8_ovl_intro[];
extern u16 D_80260288_ovl_intro[];
extern u8 D_8025D500_ovl_intro[];
extern u16 D_80092C86;
extern s8 D_80092C81;
extern s8 D_80092C82;
extern u8 D_80212264_ovl_intro;
extern s8 D_80212268_ovl_intro;
extern s8 D_8021226C_ovl_intro;
extern s8 D_80277083;
extern s8 D_80277084;
extern s8 D_80277085;
extern u16 D_80264538_ovl_intro[];
extern u8 D_802617B0_ovl_intro[];
extern u16 D_80268280_ovl_intro[];
extern u8 D_80268220_ovl_intro[];
extern u16 D_8025D2F8_ovl_intro[];
extern u8 D_8025C1E0_ovl_intro[];

void func_8020F5B4_ovl_intro(void);
void func_8020F878_ovl_intro(void);
void func_8020FCDC_ovl_intro(void);

void func_8020F170_ovl_intro(void) {
    gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    func_8020F5B4_ovl_intro();
    D_80212230_ovl_intro--;
    switch (D_80212254_ovl_intro) {
        case 0:
            D_80212250_ovl_intro += 16;
            if (D_80212250_ovl_intro >= 0x100) {
                D_80212250_ovl_intro = 0xFF;
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 90;
            }
            break;
        case 1:
            if (D_80212230_ovl_intro == 0) {
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 0x20;
            }
            break;
        case 2:
            D_80212250_ovl_intro -= 16;
            if (D_80212250_ovl_intro < 0) {
                D_80212250_ovl_intro = 0;
                D_80212254_ovl_intro = 0;
                D_80212230_ovl_intro = 0;
            }
            break;
    }
}

void func_8020F2DC_ovl_intro(void) {
    gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    func_8020F878_ovl_intro();
    D_80212230_ovl_intro--;
    switch (D_80212254_ovl_intro) {
        case 0:
            D_80212250_ovl_intro += 8;
            if (D_80212250_ovl_intro >= 0x100) {
                D_80212250_ovl_intro = 0xFF;
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 100;
            }
            break;
        case 1:
            if (D_80212230_ovl_intro == 0) {
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 0x20;
            }
            break;
        case 2:
            D_80212250_ovl_intro -= 8;
            if (D_80212250_ovl_intro < 0) {
                D_80212250_ovl_intro = 0;
                D_80212254_ovl_intro = 0;
                D_80212230_ovl_intro = 0;
            }
            break;
    }
}

void func_8020F448_ovl_intro(void) {
    gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    func_8020FCDC_ovl_intro();
    D_80212230_ovl_intro--;
    switch (D_80212254_ovl_intro) {
        case 0:
            D_80212250_ovl_intro += 8;
            if (D_80212250_ovl_intro >= 0x100) {
                D_80212250_ovl_intro = 0xFF;
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 120;
            }
            break;
        case 1:
            if (D_80212230_ovl_intro == 0) {
                D_80212254_ovl_intro++;
                D_80212230_ovl_intro = 0x20;
            }
            break;
        case 2:
            D_80212250_ovl_intro -= 8;
            if (D_80212250_ovl_intro < 0) {
                D_80212250_ovl_intro = 0;
                D_80212254_ovl_intro = 0;
                D_80212230_ovl_intro = 0;
            }
            break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_8020F5B4_ovl_intro.s")

void func_8020F878_ovl_intro(void) {
    s32 i;
    s32 x;
    s16 rx;

    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_80267048_ovl_intro);
    x = 0;
    i = 8;
    do {
        gDPLoadTextureTile_4b(D_8007A184++, D_802650A0_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 19, 91, 0, 0, 0, 0, 0, 0, 0);
        rx = x + 75;
        gSPTextureRectangle(D_8007A184++, rx << 2, 73 << 2, (s16) (rx + 20) << 2, 165 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
        x += 20;
    } while (--i != 0);
    gDPLoadTextureTile_4b(D_8007A184++, D_802650A0_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 7, 91, 0, 0, 0, 0, 0, 0, 0);
    rx = x + 75;
    gSPTextureRectangle(D_8007A184++, rx << 2, 73 << 2, (s16) (rx + 8) << 2, 165 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
}

void func_8020FCDC_ovl_intro(void) {
    s32 i;
    s32 x;
    s16 rx;

    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_80268018_ovl_intro);
    x = 0;
    i = 3;
    do {
        gDPLoadTextureTile_4b(D_8007A184++, D_80267250_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 47, 39, 0, 0, 0, 0, 0, 0, 0);
        rx = x + 75;
        gSPTextureRectangle(D_8007A184++, rx << 2, 99 << 2, (s16) (rx + 48) << 2, 139 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
        x += 48;
    } while (--i != 0);
    gDPLoadTextureTile_4b(D_8007A184++, D_80267250_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 23, 39, 0, 0, 0, 0, 0, 0, 0);
    rx = x + 75;
    gSPTextureRectangle(D_8007A184++, rx << 2, 99 << 2, (s16) (rx + 24) << 2, 139 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_80210140_ovl_intro.s")

void func_80210D38_ovl_intro(void) {
    s32 i;

    gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_802615A8_ovl_intro);
    for (i = 0; i < 4; i++) {
        gDPLoadTextureTile_4b(D_8007A184++, D_80260490_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(D_8007A184++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 109) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile_4b(D_8007A184++, D_80260490_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(D_8007A184++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 101) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
}

s32 func_802111A4_ovl_intro(void) {
    s32 ret = 0;
    s32 i;

    gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x0F0A4000);
    gDPLoadTLUT_pal16(D_8007A184++, 0, D_80260288_ovl_intro);
    for (i = 0; i < 11; i++) {
        gDPLoadTextureTile_4b(D_8007A184++, D_8025D500_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(D_8007A184++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 74) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile_4b(D_8007A184++, D_8025D500_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(D_8007A184++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 66) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    if (D_80092C86 & 0x9000) {
        ret = 1;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_80211634_ovl_intro.s")
