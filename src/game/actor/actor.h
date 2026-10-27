#ifndef GAME_ACTOR_ACTOR_H
#define GAME_ACTOR_ACTOR_H

#include "common.h"

/*
 * Shared actor types (types only: no prototypes, no externs, so any header can include it).
 * The player (player_state.actor), the enemies (enemy_slots[].actor, boss_field_record.actor)
 * and the NPCs (npc_slots[].actor) are each an Actor followed by owner data; Actor.unk64
 * points to the actor's ActorStats (player_stats, or an EnemyDef for enemies) and
 * Actor.unk68 to the ActorBattle right after the actor in its owner (Player 0x84, Enemy 0x98).
 */

/* An actor's base record: player_stats for the player. Enemy definitions (EnemyDef,
 * game/enemy/enemy.h) share 0x00..0x23 and differ after it. */
typedef struct ActorStats {
    /* 0x00 */ u16 unk0; /* 1: Magic_/Enemy_ code use unk68->unk94 as the body height; 2: no shadow */
    /* 0x02 */ s16 unk2; /* anim set index, copied to Actor.unk50 */
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6; /* cap of unk4 (Player_StateMeleeAttack) */
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA; /* cap of unk8 */
    /* 0x0C */ u16 unkC; /* copied to ActorBattle.unk86 */
    /* 0x0E */ u16 unkE; /* copied to ActorBattle.unk88 */
    /* 0x10 */ u32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18; /* multiplied by Actor.scale for the collision radius */
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20; /* copied to Actor.scale */
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35[0x38 - 0x35];
} ActorStats; /* 0x38 bytes */

/* What Actor.unk68 points to: the 0x98 bytes after the actor in its owner. */
typedef struct ActorBattle {
    /* 0x00 */ u16 unk0; /* status bits (Magic_ status handlers; bit 0x40 blocks spell input) */
    /* 0x02 */ u8 timers[12]; /* status timers, counted down by Magic_StepActorStatusTimers */
    /* 0x0E */ u8 unkE[0x84 - 0xE];
    /* 0x84 */ u16 unk84;
    /* 0x86 */ u16 unk86; /* from ActorStats.unkC (Player_InitBattle, Enemy_Spawn) */
    /* 0x88 */ u16 unk88; /* from ActorStats.unkE */
    /* 0x8A */ u16 unk8A; /* 0x10 normally (damage scale / 16) */
    /* 0x8C */ u16 unk8C; /* magic_slot_bits of the effects that hit this actor */
    /* 0x8E */ u16 unk8E;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ f32 unk94;
} ActorBattle; /* 0x98 bytes */

/* A posed, animated actor model. Anim_* (game/actor/anim.c) drive 0x38..0x60; chests
 * (game/map/chest.c) reuse 0x18..0x20 and 0x44/0x4C for their open box. */
typedef struct Actor {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC; /* x rotation for Math_MtxFRotScaleTrans (Anim_DrawModel) */
    /* 0x10 */ f32 rot; /* yaw, radians: the angle Math_RotateVec2 turns movement by */
    /* 0x14 */ f32 unk14; /* z rotation for Math_MtxFRotScaleTrans */
    /* 0x18 */ f32 vx; /* this frame's x/z step, added to x/z by the move functions; chest: box half width */
    /* 0x1C */ f32 unk1C; /* chest: facing angle of the open box */
    /* 0x20 */ f32 vz; /* chest: box half depth */
    /* 0x24 */ f32 scale;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 nx; /* floor normal from Coll_ResolveFloorAndWalls */
    /* 0x30 */ f32 ny;
    /* 0x34 */ f32 nz;
    /* 0x38 */ f32 rootX; /* root node position * scale, from Anim_UpdateRootMotion */
    /* 0x3C */ f32 rootY;
    /* 0x40 */ f32 rootZ;
    /* 0x44 */ f32 unk44; /* root motion since the last Anim_UpdateRootMotion (x); chest: box centre x */
    /* 0x48 */ f32 unk48; /* root motion y */
    /* 0x4C */ f32 unk4C; /* root motion z; chest: box centre z */
    /* 0x50 */ s16 unk50; /* anim set index; -1: slot unused (enemies) */
    /* 0x52 */ s16 unk52; /* current animation (AnimSet index) */
    /* 0x54 */ u16 frame; /* frame within the current animation */
    /* 0x56 */ u16 ticks; /* frames since the animation was set (+1 per Anim_AdvanceFrame) */
    /* 0x58 */ u16 unk58; /* animation step: frames per Anim_AdvanceFrame */
    /* 0x5A */ s16 nextAnim; /* played when the current one ends */
    /* 0x5C */ u16 nextAnimStep;
    /* 0x5E */ u16 unk5E; /* bit 0: enemy */
    /* 0x60 */ u16 unk60; /* flags: 0x200 animation looped this frame, 0x400 animation changed */
    /* 0x62 */ u16 unk62; /* floor flags from Coll_ResolveFloorAndWalls */
    /* 0x64 */ ActorStats *unk64;
    /* 0x68 */ ActorBattle *unk68;
} Actor; /* 0x6C bytes */

#endif
