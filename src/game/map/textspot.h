#ifndef GAME_MAP_TEXTSPOT_H
#define GAME_MAP_TEXTSPOT_H

#include "common.h"
#include "game/math/math.h"

struct Actor; /* game/actor/actor.h (h_actors) */

/* A text spot: a point of a map sub-area that shows a message read from ROM. */
typedef struct TextSpotDef {
    /* 0x00 */ s32 mapId;
    /* 0x04 */ s32 subarea;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 angle; /* the player must be inside its front quarter unless flags bit 0 */
    /* 0x14 */ f32 radius;
    /* 0x18 */ s32 flags;
    /* 0x1C */ u16 nameOffset; /* speaker name, offset into the ROM text block */
    /* 0x1E */ u16 textOffset; /* message, offset into the ROM text block */
} TextSpotDef; /* 0x20 bytes */

/* A text spot of the current sub-area (textspot_list). */
typedef struct TextSpot {
    /* 0x00 */ TextSpotDef *entry;
    /* 0x04 */ f32 interactionHeading; /* the player's heading minus the direction to the spot */
    /* 0x08 */ s32 unk8;
} TextSpot; /* 0xC bytes */

/* .data */
extern TextSpotDef textspot_table[0x26];
extern s32 D_8004EB60; /* the entry count; nothing reads it */

/* .bss 80085AB0..80085B80 */
extern Vec2f textspot_local_dir;
extern s32 D_80085AB8; /* unreferenced */
extern s32 textspot_count;
extern TextSpot textspot_list[16];

void Spirit_SetCollected(u16 arg0);
void TextSpot_LoadForMap(void);
TextSpot *TextSpot_FindInFront(struct Actor *arg0);
void TextSpot_LoadMessage(TextSpot *arg0);

#endif
