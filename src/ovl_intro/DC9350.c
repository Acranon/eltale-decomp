#include "common.h"

/*
 * Intro overlay: the three splash screens, the no-controller message and the pak warning screens.
 * Folder: src/game/intro/   (proposed for round 4)
 */

#define GFX_WORDS(a, b)                    {                                          Gfx *_g = gfx_dl_head++;                _g->words.w0 = (a);                    _g->words.w1 = (b);                }


/* ovl_intro .data 80212250..80212270 (the rest of the slab is still asm): 250, 254,
   then the statics of func_80210140 (258/25C/260) and func_80211634 (264/268/26C).
   .bss 80277080..80277090: their statics 77080..82 and 77083..85. */
s32 D_80212250_ovl_intro = 0;
s32 D_80212254_ovl_intro = 0;

extern Gfx *gfx_dl_head;
extern s32 D_80212230_ovl_intro;
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
extern u16 input_pressed_buttons;
extern s8 input_stick_x;
extern s8 input_stick_y;
extern u16 D_80264538_ovl_intro[];
extern u8 D_802617B0_ovl_intro[];
extern u16 D_80268280_ovl_intro[];
extern u8 D_80268220_ovl_intro[];
extern u16 D_8025D2F8_ovl_intro[];
extern u8 D_8025C1E0_ovl_intro[];
extern u16 D_8025BFD8_ovl_intro[];
extern u8 D_80259250_ovl_intro[];

void Intro_DrawSplash1(void);
void Intro_DrawSplash2(void);
void Intro_DrawSplash3(void);

void Intro_RunSplash1(void) {
    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    Intro_DrawSplash1();
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

void Intro_RunSplash2(void) {
    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    Intro_DrawSplash2();
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

void Intro_RunSplash3(void) {
    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCFA7D);
    GFX_WORDS(0xB900031D, 0x504240);
    GFX_WORDS(0xFB000000, D_80212250_ovl_intro & 0xFF);
    Intro_DrawSplash3();
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

void Intro_DrawSplash1(void) {
    s32 i;

    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80264E98_ovl_intro);
    for (i = 0; i * 9 + 120 != 138; i++) {
        gDPLoadTextureTile_4b(gfx_dl_head++, D_80264740_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 9, 200, i * 9 + 8, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 9 + 111) << 2, 261 << 2, (i * 9 + 120) << 2, G_TX_RENDERTILE, 0, (i * 9) << 5, 1 << 10, 1 << 10);
    }
}

void Intro_DrawSplash2(void) {
    s32 i;
    s32 x;
    s16 rx;

    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80267048_ovl_intro);
    x = 0;
    i = 8;
    do {
        gDPLoadTextureTile_4b(gfx_dl_head++, D_802650A0_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 19, 91, 0, 0, 0, 0, 0, 0, 0);
        rx = x + 75;
        gSPTextureRectangle(gfx_dl_head++, rx << 2, 73 << 2, (s16) (rx + 20) << 2, 165 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
        x += 20;
    } while (--i != 0);
    gDPLoadTextureTile_4b(gfx_dl_head++, D_802650A0_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 7, 91, 0, 0, 0, 0, 0, 0, 0);
    rx = x + 75;
    gSPTextureRectangle(gfx_dl_head++, rx << 2, 73 << 2, (s16) (rx + 8) << 2, 165 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
}

void Intro_DrawSplash3(void) {
    s32 i;
    s32 x;
    s16 rx;

    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80268018_ovl_intro);
    x = 0;
    i = 3;
    do {
        gDPLoadTextureTile_4b(gfx_dl_head++, D_80267250_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 47, 39, 0, 0, 0, 0, 0, 0, 0);
        rx = x + 75;
        gSPTextureRectangle(gfx_dl_head++, rx << 2, 99 << 2, (s16) (rx + 48) << 2, 139 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
        x += 48;
    } while (--i != 0);
    gDPLoadTextureTile_4b(gfx_dl_head++, D_80267250_ovl_intro, G_IM_FMT_CI, 176, 0, x, 0, x + 23, 39, 0, 0, 0, 0, 0, 0, 0);
    rx = x + 75;
    gSPTextureRectangle(gfx_dl_head++, rx << 2, 99 << 2, (s16) (rx + 24) << 2, 139 << 2, G_TX_RENDERTILE, x << 5, 0, 1 << 10, 1 << 10);
}

s32 Intro_RunNoPakScreen(void) {
    s32 pad[2];
    s32 ret = 0;
    u8 *tex[77];
    s32 i;
    s8 dir;
    s8 pressed;
    s8 dx;
    s8 dy;
    static u8 D_80212258_ovl_intro = 0;
    static s8 D_8021225C_ovl_intro = 0;
    static s8 D_80212260_ovl_intro = 0;
    static s8 D_80277080_ovl_intro;
    static s8 D_80277081_ovl_intro;
    static s8 D_80277082_ovl_intro;

    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x504240);
    dir = 0;
    if (input_stick_x > 20) {
        dir = 8;
    } else if (input_stick_x < -20) {
        dir = 4;
    }
    if (input_stick_y > 20) {
        dir |= 1;
    }
    if (input_stick_y < -20) {
        dir |= 2;
    }
    pressed = (dir ^ D_80277080_ovl_intro) & dir;
    D_80277080_ovl_intro = dir;
    dx = 0;
    dy = 0;
    if (pressed & 1) {
        dx = -1;
    }
    if (pressed & 2) {
        dx = 1;
    }
    if (pressed & 4) {
        dy = -1;
    }
    if (pressed & 8) {
        dy = 1;
    }
    D_80277081_ovl_intro = dx;
    D_8021225C_ovl_intro += dx;
    if (D_8021225C_ovl_intro < 0) {
        D_8021225C_ovl_intro = 0;
    } else if (D_8021225C_ovl_intro > 1) {
        D_8021225C_ovl_intro = 1;
    }
    D_80277082_ovl_intro = dy;
    D_80212260_ovl_intro += dy;
    if (D_80212260_ovl_intro < 0) {
        D_80212260_ovl_intro = 0;
    } else if (D_80212260_ovl_intro > 1) {
        D_80212260_ovl_intro = 1;
    }
    switch (D_80212258_ovl_intro) {
        case 0:
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_8025BFD8_ovl_intro);
            tex[0] = D_80259250_ovl_intro;
            for (i = 0; i < 11; i++) {
                gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 74) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            }
            gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 66) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80268280_ovl_intro);
            gDPLoadTextureTile_4b(gfx_dl_head++, D_80268220_ovl_intro, G_IM_FMT_CI, 16, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, (D_80212260_ovl_intro * 71 + 90) << 2, 157 << 2, (D_80212260_ovl_intro * 71 + 101) << 2, 168 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            if (input_pressed_buttons & 0xB000) {
                if (D_80212260_ovl_intro == 1) {
                    D_80212258_ovl_intro = 1;
                } else {
                    ret = 1;
                }
            }
            break;
        case 1:
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_8025D2F8_ovl_intro);
            tex[0] = D_8025C1E0_ovl_intro;
            for (i = 0; i < 4; i++) {
                gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 109) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            }
            gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 101) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            if (input_pressed_buttons & 0x4000) {
                D_80212258_ovl_intro = 0;
            }
            break;
    }
    return ret;
}

void Intro_DrawNoControllerMessage(void) {
    s32 i;

    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_802615A8_ovl_intro);
    for (i = 0; i < 4; i++) {
        gDPLoadTextureTile_4b(gfx_dl_head++, D_80260490_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 109) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile_4b(gfx_dl_head++, D_80260490_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 101) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
}

s32 Intro_RunPakFullScreen(void) {
    s32 ret = 0;
    s32 i;

    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x0F0A4000);
    gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80260288_ovl_intro);
    for (i = 0; i < 11; i++) {
        gDPLoadTextureTile_4b(gfx_dl_head++, D_8025D500_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 74) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    }
    gDPLoadTextureTile_4b(gfx_dl_head++, D_8025D500_ovl_intro, G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
    gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 66) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
    if (input_pressed_buttons & 0x9000) {
        ret = 1;
    }
    return ret;
}

s32 Intro_RunPakErrorScreen(void) {
    s32 pad[2];
    s32 ret = 0;
    u8 *tex[77];
    s32 i;
    s8 dir;
    s8 pressed;
    s8 dx;
    s8 dy;
    static u8 D_80212264_ovl_intro = 0;
    static s8 D_80212268_ovl_intro = 0;
    static s8 D_8021226C_ovl_intro = 0;
    static s8 D_80277083_ovl_intro;
    static s8 D_80277084_ovl_intro;
    static s8 D_80277085_ovl_intro;

    gSPDisplayList(gfx_dl_head++, D_80212270_ovl_intro);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
    GFX_WORDS(0xFCFFFFFF, 0xFFFCF279);
    GFX_WORDS(0xB900031D, 0x504240);
    dir = 0;
    if (input_stick_x > 20) {
        dir = 8;
    } else if (input_stick_x < -20) {
        dir = 4;
    }
    if (input_stick_y > 20) {
        dir |= 1;
    }
    if (input_stick_y < -20) {
        dir |= 2;
    }
    pressed = (dir ^ D_80277083_ovl_intro) & dir;
    D_80277083_ovl_intro = dir;
    dx = 0;
    dy = 0;
    if (pressed & 1) {
        dx = -1;
    }
    if (pressed & 2) {
        dx = 1;
    }
    if (pressed & 4) {
        dy = -1;
    }
    if (pressed & 8) {
        dy = 1;
    }
    D_80277084_ovl_intro = dx;
    D_80212268_ovl_intro += dx;
    if (D_80212268_ovl_intro < 0) {
        D_80212268_ovl_intro = 0;
    } else if (D_80212268_ovl_intro > 1) {
        D_80212268_ovl_intro = 1;
    }
    D_80277085_ovl_intro = dy;
    D_8021226C_ovl_intro += dy;
    if (D_8021226C_ovl_intro < 0) {
        D_8021226C_ovl_intro = 0;
    } else if (D_8021226C_ovl_intro > 1) {
        D_8021226C_ovl_intro = 1;
    }
    switch (D_80212264_ovl_intro) {
        case 0:
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80264538_ovl_intro);
            tex[0] = D_802617B0_ovl_intro;
            for (i = 0; i < 11; i++) {
                gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 74) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            }
            gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 64) << 2, 260 << 2, (i * 10 + 66) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_80268280_ovl_intro);
            gDPLoadTextureTile_4b(gfx_dl_head++, D_80268220_ovl_intro, G_IM_FMT_CI, 16, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, (D_8021226C_ovl_intro * 74 + 90) << 2, 157 << 2, (D_8021226C_ovl_intro * 74 + 101) << 2, 168 << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            if (input_pressed_buttons & 0xB000) {
                if (D_8021226C_ovl_intro == 1) {
                    D_80212264_ovl_intro = 1;
                } else {
                    ret = 1;
                }
            }
            break;
        case 1:
            gDPPipeSync(gfx_dl_head++);
            gDPLoadTLUT_pal16(gfx_dl_head++, 0, D_8025D2F8_ovl_intro);
            tex[0] = D_8025C1E0_ovl_intro;
            for (i = 0; i < 4; i++) {
                gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 9, 0, 0, 0, 0, 0, 0, 0);
                gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 109) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            }
            gDPLoadTextureTile_4b(gfx_dl_head++, tex[0], G_IM_FMT_CI, 208, 0, 0, i * 10, 199, i * 10 + 1, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(gfx_dl_head++, 60 << 2, (i * 10 + 99) << 2, 260 << 2, (i * 10 + 101) << 2, G_TX_RENDERTILE, 0, (i * 10) << 5, 1 << 10, 1 << 10);
            if (input_pressed_buttons & 0x4000) {
                D_80212264_ovl_intro = 0;
            }
            break;
    }
    return ret;
}
