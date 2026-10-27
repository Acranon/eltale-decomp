#ifndef GAME_NPC_NPC_H
#define GAME_NPC_NPC_H

#include "common.h"
#include "game/actor/actor.h"

struct CollResult;
struct GfxFrameData; /* game/core/main.h */
struct AnimSet;
struct RomRange;

/* An NPC definition record (the area's NPC list, NpcList). */
typedef struct NpcDef {
    /* 0x00 */ u16 area; /* compared with map_subarea */
    /* 0x02 */ u16 unk2; /* talk kind (Npc_StartTalk) */
    /* 0x04 */ u8 unk4; /* 2: wanders */
    /* 0x05 */ u8 flags;
    union {
        /* 0x06 */ u16 unk6;
        struct {
            /* 0x06 */ u8 unk6_hi;
            /* 0x07 */ u8 unk7;
        } b;
    } u6;
    /* 0x08 */ u16 unk8; /* message offset */
    /* 0x0A */ u16 unkA; /* other message offset */
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ struct AnimSet *unk10; /* anim set table */
    /* 0x14 */ u8 *name;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 x;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 angle;
    /* 0x28 */ f32 unk28; /* copied to Actor.scale */
} NpcDef; /* 0x2C bytes */

/* An area's NPC list (MapAreaDef's npcs). */
typedef struct NpcList {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ NpcDef *defs;
} NpcList; /* 0x8 bytes */

/* One npc_slots entry. */
typedef struct Npc {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 timer;
    /* 0x04 */ f32 homeX;
    /* 0x08 */ f32 homeZ;
    /* 0x0C */ f32 homeAngle;
    /* 0x10 */ f32 unk10; /* turn to the player, per 15 frames */
    /* 0x14 */ Actor actor;
    /* 0x80 */ NpcDef *def;
} Npc; /* 0x84 bytes */

/* .bss 8007AB70..8007B900, in address order (unreferenced gaps included) */
extern struct RomRange *npc_area_set_rom_range;
extern u16 npc_walking_count;
extern f32 npc_walk_step[2];
extern s32 D_8007AB80[2];
extern struct CollResult npc_move_coll;
extern s32 npc_count;
extern s32 npc_drawn_count;
extern s32 D_8007ABAC;
extern Actor *npc_drawn_list[16];
extern Npc npc_slots[16];
extern u8 text_message_buf[0x4B0];
extern u8 text_speaker_name[0x20];

/* .data */
extern u8 npc_rest_choice_row0[8];
extern u8 npc_rest_choice_row1[8];

void Npc_InitArea(void);
void Npc_UpdateAll(void);
void Npc_DrawAll(struct GfxFrameData *arg0);
void func_80009764(s32 arg0);
void Npc_SpawnForArea(NpcDef *def, s32 n);
void Npc_Move(f32 dx, f32 dz, Actor *obj);
void Npc_PushOutOfObjects(f32 *dx, f32 *dz, Actor *obj);
void Npc_StartTalk(s32 idx);
void Npc_EndTalk(s32 idx);
void Npc_LoadMessage(Npc *npc, s32 arg1);
void Npc_SetMessage(s32 arg0, u8 *arg1);

#endif
