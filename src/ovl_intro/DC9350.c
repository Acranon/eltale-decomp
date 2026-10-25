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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_8020F878_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_8020FCDC_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_80210140_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_80210D38_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_802111A4_ovl_intro.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC9350/func_80211634_ovl_intro.s")
