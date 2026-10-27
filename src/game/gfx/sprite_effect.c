#include "game/gfx/sprite_effect.h"
#include "game/camera/camera.h"

/*
 * EffectSprite effect pool: allocate, update, transform, draw, and load textures.
 * Original file: 1E570.c (ROM 0x1E570).
 */

/* Local view of GfxFrameData (game/core/main.h, h_core) until H2. */
typedef struct GfxFrameData {
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
/* This file's .bss, 80087E30..8008BE40. */
s32 effect_active_sprite_count;
EffectSprite effect_sprite_slots[0x100];


void Effect_ResetSpritePool(void) {
    s32 var_v1;
    EffectSprite* var_v0;

    var_v0 = effect_sprite_slots;
    var_v1 = 0x100;
    while (var_v1 > 0) {
        var_v0->life = 0;
        var_v0++;
        var_v1--;
    }
    effect_active_sprite_count = 0;
}

EffectSprite* Effect_AllocateSprite(EffectSprite* arg0) {
    EffectSprite* ret = effect_sprite_slots;
    u32 i = 0x100;

    while ((i > 0) && (ret->life != 0)) {
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
    EffectSprite* dust;
    MtxF spB4;
    MtxF sp74;

    i = effect_active_sprite_count;
    tex = NULL;
    dust = effect_sprite_slots;
    while (i != 0) {
        if (dust->life != 0) {
            dust->life--;
            if (tex != dust->tex) {
                tex = dust->tex;
                Effect_LoadSpriteTexture(dust->texFmt, tex, dust->texWidth, dust->texHeight, (s32) dust->cms, (s32) dust->cmt);
            }
            if (dust->update != NULL) {
                dust->update(dust);
            } else {
                gSPDisplayList(gfx_dl_head++, effect_sprite_setup_dl);
            }
            if (dust->flags & 1) {
                Math_MtxFAlignYToVector(&spB4, dust->unk30, dust->unk34, dust->unk38);
                spB4.mf[3][0] = dust->x;
                spB4.mf[3][1] = dust->y;
                spB4.mf[3][2] = dust->z;
                Math_MtxFScaleAxes(&spB4, dust->scaleX, dust->scaleX, dust->scaleX);
            } else {
                Math_MtxFAimAt(&spB4, dust->x, dust->y, dust->z, camera_state.eyeX, camera_state.eyeY, camera_state.eyeZ);
                if (dust->roll != 0.0f) {
                    Math_MtxFRotate(&sp74, 0.0f, 0.0f, dust->roll);
                    guMtxCatF((f32 (*)[4]) &sp74, (f32 (*)[4]) &spB4, (f32 (*)[4]) &spB4);
                }
                Math_MtxFScaleAxes(&spB4, dust->scaleX, dust->scaleY, 1.0f);
            }
            if (gfx_mtx_index < 0x1E6) {
                guMtxF2L((f32 (*)[4]) &spB4, &arg0->unkC0[gfx_mtx_index]);
                gSPMatrix(gfx_dl_head++, &D_2000000[gfx_mtx_index + 3].m[0][0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gfx_mtx_index++;
                gSPDisplayList(gfx_dl_head++, dust->dl);
            }
            if (dust->life == 0) {
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
