#include "common.h"

/*
 * Sprite effect pool: allocate, update, transform, draw, and load textures.
 * Folder: src/game/gfx/
 */

typedef struct {
    f32 mf[4][4];
} MtxF;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ char pad3;
    /* 0x04 */ void* unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ char unkD[3];
    /* 0x10 */ u8* unk10;
    /* 0x14 */ u8* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ char unk3C[4];
} Struct_80087E38;

typedef struct {
    char unk0[0xC];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Struct_80085E48;

typedef struct {
    char unk00[0xC0];
    Mtx unkC0[1];
} Struct_8001DA3C;

extern Mtx D_2000000[];
Gfx D_8004F060[8] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000205 }},
    {{ 0xFCFFFFFF, 0xFFFCF238 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xB8000000, 0x00000000 }},
};
extern s32 D_8007A180;
extern Gfx* D_8007A184;
extern Struct_80085E48 D_80085E48;
/* This file's .bss, 80087E30..8008BE40. */
s32 D_80087E30;
Struct_80087E38 D_80087E38[0x100];

void Effect_LoadSpriteTexture(u8, u8*, s32, s32, u8, u8);
void func_80027430(MtxF*, f32, f32, f32);
void func_800275DC(MtxF*, f32, f32, f32, f32, f32, f32);
void func_800278C8(MtxF*, f32, f32, f32);
void func_80027CB4(MtxF*, f32, f32, f32);

void Effect_ResetSpritePool(void) {
    s32 var_v1;
    Struct_80087E38* var_v0;

    var_v0 = D_80087E38;
    var_v1 = 0x100;
    while (var_v1 > 0) {
        var_v0->unk0 = 0;
        var_v0++;
        var_v1--;
    }
    D_80087E30 = 0;
}

Struct_80087E38* Effect_AllocateSprite(Struct_80087E38* arg0) {
    Struct_80087E38* ret = D_80087E38;
    u32 i = 0x100;

    while ((i > 0) && (ret->unk0 != 0)) {
        i--;
        ret++;
    }

    if (i != 0) {
        *ret = *arg0;
        D_80087E30++;
    } else {
        ret = NULL;
    }
    return ret;
}

void Effect_DrawSprites(Struct_8001DA3C* arg0) {
    s32 i;
    u8* tex;
    Struct_80087E38* dust;
    MtxF spB4;
    MtxF sp74;

    i = D_80087E30;
    tex = NULL;
    dust = D_80087E38;
    while (i != 0) {
        if (dust->unk0 != 0) {
            dust->unk0--;
            if (tex != dust->unk10) {
                tex = dust->unk10;
                Effect_LoadSpriteTexture(dust->unk8, tex, dust->unk9, dust->unkA, (s32) dust->unkB, (s32) dust->unkC);
            }
            if (dust->unk4 != NULL) {
                ((void (*)(Struct_80087E38*)) dust->unk4)(dust);
            } else {
                gSPDisplayList(D_8007A184++, D_8004F060);
            }
            if (dust->unk2 & 1) {
                func_800278C8(&spB4, dust->unk30, dust->unk34, dust->unk38);
                spB4.mf[3][0] = dust->unk18;
                spB4.mf[3][1] = dust->unk1C;
                spB4.mf[3][2] = dust->unk20;
                func_80027CB4(&spB4, dust->unk28, dust->unk28, dust->unk28);
            } else {
                func_800275DC(&spB4, dust->unk18, dust->unk1C, dust->unk20, D_80085E48.unkC, D_80085E48.unk10, D_80085E48.unk14);
                if (dust->unk24 != 0.0f) {
                    func_80027430(&sp74, 0.0f, 0.0f, dust->unk24);
                    guMtxCatF((f32 (*)[4]) &sp74, (f32 (*)[4]) &spB4, (f32 (*)[4]) &spB4);
                }
                func_80027CB4(&spB4, dust->unk28, dust->unk2C, 1.0f);
            }
            if (D_8007A180 < 0x1E6) {
                guMtxF2L((f32 (*)[4]) &spB4, &arg0->unkC0[D_8007A180]);
                gSPMatrix(D_8007A184++, &D_2000000[D_8007A180 + 3].m[0][0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                D_8007A180++;
                gSPDisplayList(D_8007A184++, dust->unk14);
            }
            if (dust->unk0 == 0) {
                D_80087E30 -= 1;
            }
            i--;
        }
        dust++;
    }
}

u8 D_8004F0A0[8] = { 2, 4, 8, 16, 32, 64, 128, 0 };

void Effect_LoadSpriteTexture(u8 fmt, u8* timg, s32 width, s32 height, u8 cms, u8 cmt) {
    u8 masks;
    u8 maskt;

    for (masks = 0; masks < 7U; masks++) {
        if (D_8004F0A0[masks] >= width) {
            break;
        }
    }
    masks++;
    for (maskt = 0; maskt < 7U; maskt++) {
        if (D_8004F0A0[maskt] >= height) {
            break;
        }
    }
    maskt++;
    switch (fmt) {
        case 0:
            gDPLoadTextureBlock(D_8007A184++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 1:
            gDPLoadTextureBlock(D_8007A184++, timg, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 2:
            gDPLoadTextureBlock(D_8007A184++, timg, G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 3:
            gDPLoadTextureBlock(D_8007A184++, timg, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 4:
            gDPLoadTextureBlock_4b(D_8007A184++, timg, G_IM_FMT_I, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 5:
            gDPLoadTextureBlock_4b(D_8007A184++, timg, G_IM_FMT_IA, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
            break;
        case 6:
            gDPLoadTextureBlock_4b(D_8007A184++, timg, G_IM_FMT_CI, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
            break;
        case 7:
            gDPLoadTextureBlock(D_8007A184++, timg, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
            break;
    }
}
