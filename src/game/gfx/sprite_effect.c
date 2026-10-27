#include "common.h"

/*
 * Sprite effect pool: allocate, update, transform, draw, and load textures.
 * Original file: 1E570.c (ROM 0x1E570).
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
Gfx effect_sprite_setup_dl[8] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000205 }},
    {{ 0xFCFFFFFF, 0xFFFCF238 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xB8000000, 0x00000000 }},
};
extern s32 gfx_mtx_index;
extern Gfx* gfx_dl_head;
extern Struct_80085E48 camera_state;
/* This file's .bss, 80087E30..8008BE40. */
s32 effect_active_sprite_count;
Struct_80087E38 effect_sprite_slots[0x100];

void Effect_LoadSpriteTexture(u8, u8*, s32, s32, u8, u8);
void Math_MtxFRotate(MtxF*, f32, f32, f32);
void Math_MtxFAimAt(MtxF*, f32, f32, f32, f32, f32, f32);
void Math_MtxFAlignYToVector(MtxF*, f32, f32, f32);
void Math_MtxFScaleAxes(MtxF*, f32, f32, f32);

void Effect_ResetSpritePool(void) {
    s32 var_v1;
    Struct_80087E38* var_v0;

    var_v0 = effect_sprite_slots;
    var_v1 = 0x100;
    while (var_v1 > 0) {
        var_v0->unk0 = 0;
        var_v0++;
        var_v1--;
    }
    effect_active_sprite_count = 0;
}

Struct_80087E38* Effect_AllocateSprite(Struct_80087E38* arg0) {
    Struct_80087E38* ret = effect_sprite_slots;
    u32 i = 0x100;

    while ((i > 0) && (ret->unk0 != 0)) {
        i--;
        ret++;
    }

    if (i != 0) {
        *ret = *arg0;
        effect_active_sprite_count++;
    } else {
        ret = NULL;
    }
    return ret;
}

void Effect_UpdateAndDrawSprites(Struct_8001DA3C* arg0) {
    s32 i;
    u8* tex;
    Struct_80087E38* dust;
    MtxF spB4;
    MtxF sp74;

    i = effect_active_sprite_count;
    tex = NULL;
    dust = effect_sprite_slots;
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
                gSPDisplayList(gfx_dl_head++, effect_sprite_setup_dl);
            }
            if (dust->unk2 & 1) {
                Math_MtxFAlignYToVector(&spB4, dust->unk30, dust->unk34, dust->unk38);
                spB4.mf[3][0] = dust->unk18;
                spB4.mf[3][1] = dust->unk1C;
                spB4.mf[3][2] = dust->unk20;
                Math_MtxFScaleAxes(&spB4, dust->unk28, dust->unk28, dust->unk28);
            } else {
                Math_MtxFAimAt(&spB4, dust->unk18, dust->unk1C, dust->unk20, camera_state.unkC, camera_state.unk10, camera_state.unk14);
                if (dust->unk24 != 0.0f) {
                    Math_MtxFRotate(&sp74, 0.0f, 0.0f, dust->unk24);
                    guMtxCatF((f32 (*)[4]) &sp74, (f32 (*)[4]) &spB4, (f32 (*)[4]) &spB4);
                }
                Math_MtxFScaleAxes(&spB4, dust->unk28, dust->unk2C, 1.0f);
            }
            if (gfx_mtx_index < 0x1E6) {
                guMtxF2L((f32 (*)[4]) &spB4, &arg0->unkC0[gfx_mtx_index]);
                gSPMatrix(gfx_dl_head++, &D_2000000[gfx_mtx_index + 3].m[0][0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gfx_mtx_index++;
                gSPDisplayList(gfx_dl_head++, dust->unk14);
            }
            if (dust->unk0 == 0) {
                effect_active_sprite_count -= 1;
            }
            i--;
        }
        dust++;
    }
}

u8 effect_texture_tile_sizes[8] = { 2, 4, 8, 16, 32, 64, 128, 0 };

void Effect_LoadSpriteTexture(u8 fmt, u8* timg, s32 width, s32 height, u8 cms, u8 cmt) {
    u8 masks;
    u8 maskt;

    for (masks = 0; masks < 7U; masks++) {
        if (effect_texture_tile_sizes[masks] >= width) {
            break;
        }
    }
    masks++;
    for (maskt = 0; maskt < 7U; maskt++) {
        if (effect_texture_tile_sizes[maskt] >= height) {
            break;
        }
    }
    maskt++;
    switch (fmt) {
        case 0:
            gDPLoadTextureBlock(gfx_dl_head++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 1:
            gDPLoadTextureBlock(gfx_dl_head++, timg, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 2:
            gDPLoadTextureBlock(gfx_dl_head++, timg, G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 3:
            gDPLoadTextureBlock(gfx_dl_head++, timg, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 4:
            gDPLoadTextureBlock_4b(gfx_dl_head++, timg, G_IM_FMT_I, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 5:
            gDPLoadTextureBlock_4b(gfx_dl_head++, timg, G_IM_FMT_IA, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            break;
        case 6:
            gDPLoadTextureBlock_4b(gfx_dl_head++, timg, G_IM_FMT_CI, width, height, 0, cms, cmt, masks, maskt,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
            break;
        case 7:
            gDPLoadTextureBlock(gfx_dl_head++, timg, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks,
                                maskt, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
            break;
    }
}
