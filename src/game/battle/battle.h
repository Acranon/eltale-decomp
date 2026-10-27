#ifndef GAME_BATTLE_BATTLE_H
#define GAME_BATTLE_BATTLE_H

#include "common.h"

struct Vec3f;

/* Random-encounter data of a map area (MapAreaDef 0x30/0x34, indexed by sub-area). */

/* A rectangle the player can meet the region's groups in (Battle_FindEncounterRegion). */
typedef struct EncounterRegion {
    /* 0x00 */ s16 unk0; /* x */
    /* 0x02 */ s16 unk2; /* z */
    /* 0x04 */ s16 unk4; /* x extent */
    /* 0x06 */ s16 unk6; /* z extent */
    /* 0x08 */ u8 unk8[0x18 - 0x8]; /* group list: u16 count, then group ids (Battle_SpawnEncounterGroup) */
} EncounterRegion; /* 0x18 bytes */

typedef struct EncounterRegionList {
    /* 0x00 */ EncounterRegion *unk0;
    /* 0x04 */ s32 unk4; /* count */
} EncounterRegionList; /* 0x8 bytes */

/* A spawn point a battle can be centred on (Battle_ChooseNearbyEncounterPoint). */
typedef struct EncounterPoint {
    /* 0x00 */ s16 unk0; /* x */
    /* 0x02 */ s16 unk2; /* z */
} EncounterPoint; /* 0x4 bytes */

/* One kind of enemy in a group. */
typedef struct EncounterGroupEntry {
    /* 0x00 */ s32 unk0; /* enemy def index (Enemy_Spawn) */
    /* 0x04 */ s32 unk4; /* count */
    /* 0x08 */ s32 unk8; /* random extra count, 0..unk8 */
} EncounterGroupEntry; /* 0xC bytes */

typedef struct EncounterGroup {
    /* 0x00 */ EncounterGroupEntry *unk0;
    /* 0x04 */ u16 unk4; /* entry count */
    /* 0x06 */ u16 unk6; /* first formation position */
} EncounterGroup; /* 0x8 bytes */

typedef struct EncounterGroupTable {
    /* 0x00 */ struct Vec3f **unk0; /* formation positions */
    /* 0x04 */ EncounterGroup *unk4;
    /* 0x08 */ EncounterPoint *unk8;
    /* 0x0C */ s32 unkC; /* point count */
} EncounterGroupTable; /* 0x10 bytes */

/* battle_camera_offsets entry (per map id) */
typedef struct BattleCameraOffset {
    /* 0x00 */ f32 unk0; /* added to camera_state 0x58 */
    /* 0x04 */ f32 unk4; /* added to camera_state 0x4C */
    /* 0x08 */ f32 unk8;
} BattleCameraOffset; /* 0xC bytes */

/* .bss 8008BE40..8008BFC0, in address order */
extern struct Vec3f battle_temp_vec;
extern u16 battle_camera_phase;
extern u16 battle_camera_phase_timer;
extern u16 battle_camera_enemy_index;
extern u16 battle_flags; /* bit 0x1: in battle; 0x2: enemy turn; 0x100: boss encounter */
extern u16 battle_turn_delay;
extern s16 D_8008BE56;
extern u16 battle_turn_order_index;
extern u16 battle_enemy_count;
extern f32 battle_center_x;
extern f32 battle_center_z;
extern f32 battle_turn_origin_x;
extern f32 battle_turn_origin_z;
extern f32 battle_arena_radius;
extern u8 D_8008BE70[0x100];
extern void *D_8008BF70[8];
extern u32 D_8008BF90;
extern s16 battle_outer_ring_slot;
extern u16 battle_turn_ring_slot;
extern EncounterRegionList *battle_encounter_region_table;
extern EncounterGroupTable *battle_encounter_group_table;
extern void *battle_saved_enemy_anim_tables;
extern void *battle_saved_enemy_names;
extern s32 battle_boss_index_plus_one;
extern f32 battle_travel_accumulator;
extern u16 battle_encounter_roll_limit;

/* .data */
extern BattleCameraOffset battle_camera_offsets[36];
extern u8 D_8004F260[0x24];
extern u8 D_8004F284[0x1C];
extern f32 battle_boss_arena_radii[8];

void Battle_ResetState(void);
void Battle_TryStartRandomEncounter(void);
void Battle_StartBossEncounter(void);
void Battle_UpdateStartCamera(void);
void Battle_UpdateTurnTransition(void);
void Battle_EndTurn(struct Vec3f *arg0); /* callers pass the actor (D3_PROTO.md) */
EncounterRegion *Battle_FindEncounterRegion(f32 x, f32 y, EncounterRegionList *list);
EncounterPoint *Battle_ChooseNearbyEncounterPoint(f32 x, f32 y);
void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16 *list);
void func_800200F0(void); /* empty */
s32 func_800200F8(void);
void func_8002018C(void); /* empty */

#endif
