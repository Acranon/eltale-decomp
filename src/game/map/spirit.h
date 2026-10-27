#ifndef GAME_MAP_SPIRIT_H
#define GAME_MAP_SPIRIT_H

#include "common.h"
#include "game/map/collision.h"
#include "game/gfx/fade.h"
#include "game/gfx/sprite_effect.h"

struct Actor; /* game/actor/actor.h (h_actors) */

/* A spirit of the current sub-area (spirit_objects). */
typedef struct SpiritObj {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 sparkleAngle; /* where the next sparkle spawns around it */
    /* 0x10 */ u16 collected; /* Spirit_IsCollected at load */
    /* 0x12 */ s16 sparkleTimer;
    /* 0x14 */ u8 flagId; /* bit index into spirit_collected_flags */
    /* 0x15 */ u8 pad15[3];
} SpiritObj; /* 0x18 bytes */

/* One spirit placement (in the map overlays). */
typedef struct SpiritDef {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z; /* negated at load */
    /* 0x08 */ u8 flagId;
    /* 0x09 */ u8 pad9[3];
} SpiritDef; /* 0xC bytes */

/* spirit_map_placements entry: the spirits of one map sub-area. */
typedef struct SpiritPlacement {
    /* 0x00 */ u16 mapId;
    /* 0x02 */ u16 subarea;
    /* 0x04 */ u16 count;
    /* 0x08 */ SpiritDef *defs;
} SpiritPlacement; /* 0xC bytes */

/* .bss 800859B0..80085AB0 */
extern s32 spirit_count;
extern SpiritObj spirit_objects[8];
extern CollResult spirit_coll;
extern u8 spirit_collected_flags[0x10];

/* .data */
extern SpiritPlacement spirit_map_placements[0x2B];
extern Vtx spirit_sparkle_vtx[4];
extern Gfx spirit_sparkle_dl[10];
extern u8 spirit_sparkle_tex[4][0x100];
extern ColorRGBA8 spirit_sparkle_colors[2];

void Spirit_ClearCollectedFlags(void);
void Spirit_LoadForMap(void);
SpiritObj *Spirit_FindInFront(struct Actor *arg0);
void Spirit_SpawnSparkles(void);
void Spirit_MoveSparkle(EffectSprite *arg0);
u8 Spirit_IsCollected(u16 arg0);

#endif
