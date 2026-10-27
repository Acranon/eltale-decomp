#ifndef GAME_GFX_SPRITE_EFFECT_H
#define GAME_GFX_SPRITE_EFFECT_H

#include "common.h"

struct GfxFrameData;

/*
 * One sprite of the effect pool (effect_sprite_slots), or a descriptor copied into it by
 * Effect_AllocateSprite. Drawn each frame as a camera-facing quad (or aligned to the vector
 * at 0x30 if flags bit 0), after its update callback ran.
 */
typedef struct EffectSprite {
    /* 0x00 */ u16 life; /* frames left, 0 = free slot */
    /* 0x02 */ u8 flags; /* bit 0: align to the vector at 0x30 instead of facing the camera */
    /* 0x03 */ u8 pad3;
    /* 0x04 */ void (*update)(struct EffectSprite *); /* called before drawing; NULL = the default setup dl */
    /* 0x08 */ u8 texFmt; /* Effect_LoadSpriteTexture's fmt */
    /* 0x09 */ u8 texWidth;
    /* 0x0A */ u8 texHeight;
    /* 0x0B */ u8 cms;
    /* 0x0C */ u8 cmt;
    /* 0x0D */ u8 padD[3];
    /* 0x10 */ u8 *tex;
    /* 0x14 */ Gfx *dl;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 roll; /* rotation about the view axis */
    /* 0x28 */ f32 scaleX;
    /* 0x2C */ f32 scaleY;
    /* 0x30 */ f32 vecX; /* alignment vector (flags bit 0), also used as velocity by update callbacks */
    /* 0x34 */ f32 vecY;
    /* 0x38 */ f32 vecZ;
    /* 0x3C */ u8 unk3C; /* per-sprite counter of the update callbacks */
    /* 0x3D */ u8 pad3D[3];
} EffectSprite; /* 0x40 bytes */

/* .data */
extern Gfx effect_sprite_setup_dl[8];
extern u8 effect_texture_tile_sizes[8];

/* .bss 80087E30..8008BE40 */
extern s32 effect_active_sprite_count;
extern EffectSprite effect_sprite_slots[0x100];

void Effect_ResetSpritePool(void);
EffectSprite *Effect_AllocateSprite(EffectSprite *arg0);
void Effect_UpdateAndDrawSprites(struct GfxFrameData *arg0);
void Effect_LoadSpriteTexture(u8 fmt, u8 *timg, s32 width, s32 height, u8 cms, u8 cmt);

#endif
