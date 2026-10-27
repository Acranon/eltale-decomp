#ifndef GAME_MAP_CHEST_H
#define GAME_MAP_CHEST_H

#include "common.h"
#include "game/math/math.h"
#include "game/map/collision.h"

struct Actor; /* game/actor/actor.h (h_actors): a chest is an Actor */
struct GfxFrameData;

/* One chest of a sub-area (in the map overlays). */
typedef struct ChestDef {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 ry;
    /* 0x0C */ f32 boxX; /* centre of the box the player must stand in to open it */
    /* 0x10 */ f32 boxZ;
    /* 0x14 */ f32 boxAngle;
    /* 0x18 */ f32 boxHalfW;
    /* 0x1C */ f32 boxHalfD;
    /* 0x20 */ u8 flagId; /* bit index into chest_opened_flags */
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 pad22[2];
} ChestDef; /* 0x24 bytes */

/* A sub-area's chests. */
typedef struct ChestGroup {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ ChestDef *defs;
} ChestGroup; /* 0x8 bytes */

/* chest_map_placements entry: a map's chest groups, one per sub-area. */
typedef struct ChestPlacement {
    /* 0x00 */ s32 mapId;
    /* 0x04 */ ChestGroup *groups;
} ChestPlacement; /* 0x8 bytes */

/* .bss 80085290..800859B0 */
extern struct Actor chest_objects[16];
extern s32 chest_count;
extern Vec2f chest_local_offset;
extern u8 D_80085960[8]; /* unreferenced */
extern CollResult chest_coll;
extern u8 chest_opened_flags[0x20];
extern u8 D_800859A8[8];

/* .data */
extern u8 item_message_prefix[8];
extern u8 item_message_suffix[20];
extern ChestPlacement chest_map_placements[19];

void Chest_ClearOpenedFlags(void);
void Chest_LoadForMap(void);
void Chest_UpdateAll(struct GfxFrameData *arg0);
struct Actor *Chest_FindInFront(struct Actor *arg0);
void Chest_Open(struct Actor *arg0);
void Item_BuildMessage(s32 arg0);
u8 Chest_IsOpened(u16 arg0);

#endif
