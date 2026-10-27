#ifndef GAME_MAGIC_MAGIC_H
#define GAME_MAGIC_MAGIC_H

#include "common.h"
#include "game/actor/actor.h"
#include "game/math/math.h"

struct CollResult;
struct EffectModel;
struct Enemy;

/* One D_800C18D8 entry: a visual effect for Magic_CreateVisualEffect. */
typedef struct MagicVisualDef {
    /* 0x00 */ u16 x_scale_source; /* x scale source: 0 ActorStats.unk18, 1 ActorStats.unk1C, 3 arg7->z (times scale) */
    /* 0x02 */ u16 y_scale_source; /* y scale source */
    /* 0x04 */ u16 display_list_index;
    /* 0x06 */ u16 texture_index;
    /* 0x08 */ u16 anim_index;
} MagicVisualDef; /* 0xA bytes */

/* One spell definition (row of the D_800C185C tables, indexed [group][index]). */
typedef struct SpellDef {
    /* 0x00 */ u16 required_level; /* level the caster needs in group input_sequence[0] (Magic_GetSpellRestrictionFlags) */
    /* 0x02 */ u16 flags; /* bit 0: usable in battle, bit 1: on the field; also the damage flags */
    /* 0x04 */ u16 input_length; /* input sequence length */
    /* 0x06 */ u8 input_sequence[4]; /* input sequence; input_sequence[0] is the group (element) */
    /* 0x0A */ u16 effect_lifetime; /* effect lifetime */
    /* 0x0C */ u16 unkC; /* heal percent of max (Magic_HealTarget), damage base (Magic_CalculateEffectDamage) */
    /* 0x0E */ u16 hit_chance; /* hit chance, percent */
    /* 0x10 */ u16 hit_handler_index; /* magic_hit_handlers index */
    /* 0x12 */ u16 move_handler_index; /* magic_move_handlers index; launch kind in Magic_CreateCastEffect */
    /* 0x14 */ u16 floor_collision_mode; /* floor collision mode */
    /* 0x16 */ u16 find_target_handler_index; /* magic_find_target_handlers index */
    /* 0x18 */ u16 target_select_handler_index; /* magic_target_select_handlers index */
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 hit_range; /* hit range */
    /* 0x20 */ u16 cast_count; /* cast count (repeats through magic_cast_repeats) */
    /* 0x22 */ u16 repeat_interval; /* frames between repeats */
    /* 0x24 */ u16 start_delay; /* start delay */
    /* 0x26 */ u16 place_handler_index; /* magic_place_handlers index */
    /* 0x28 */ u16 homing_strength_index; /* magic_homing_strengths index */
    /* 0x2A */ u16 launch_flags; /* bit 0: vy -= 0.3 per frame, bit 1: launched with vy = 0 */
    /* 0x2C */ u16 launch_direction_index; /* launch direction (D_800C1878 index) */
    /* 0x2E */ u16 homing_accel_index; /* magic_homing_accels index */
    /* 0x30 */ s16 launch_speed_index; /* magic_launch_speeds index */
    /* 0x32 */ u8 status_args[12]; /* argument for each magic_status_handlers entry, 0: not applied */
    /* 0x3E */ u8 pad3E[6];
} SpellDef; /* 0x44 bytes */

/* A spell's presentation record (D_800C3268 tables, same index as SpellDef): four
 * visual-effect stages (cast, timed, ground hit, hit: table index, two args, scale x/y)
 * and four sound pairs. */
typedef struct SpellFxDef {
    /* 0x00 */ s16 cast_visual_index; /* cast: D_800C18D8 index, -1: none */
    /* 0x02 */ u16 cast_color_index;
    /* 0x04 */ u16 cast_flags;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 cast_scale_x;
    /* 0x0C */ f32 cast_scale_y;
    /* 0x10 */ s16 timed_visual_index; /* timed */
    /* 0x12 */ u16 timed_color_index;
    /* 0x14 */ u16 timed_flags;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 timed_scale_x;
    /* 0x1C */ f32 timed_scale_y;
    /* 0x20 */ s16 ground_hit_visual_index; /* ground hit */
    /* 0x22 */ u16 ground_hit_color_index;
    /* 0x24 */ u16 ground_hit_flags;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ f32 ground_hit_scale_x;
    /* 0x2C */ f32 ground_hit_scale_y;
    /* 0x30 */ s16 hit_visual_index; /* hit */
    /* 0x32 */ u16 hit_color_index;
    /* 0x34 */ u16 hit_flags;
    /* 0x36 */ u8 pad36[2];
    /* 0x38 */ f32 hit_scale_x;
    /* 0x3C */ f32 hit_scale_y;
    /* 0x40 */ s8 cast_sound_id; /* cast sound (Sfx_Play arg 2, -1: none) */
    /* 0x41 */ u8 cast_sound_delay;
    /* 0x42 */ s8 hit_sound_id; /* hit sound */
    /* 0x43 */ u8 hit_sound_delay;
    /* 0x44 */ s8 ground_hit_sound_id; /* ground hit sound */
    /* 0x45 */ u8 ground_hit_sound_delay;
    /* 0x46 */ s8 timed_sound_id; /* timed sound */
    /* 0x47 */ u8 timed_sound_delay;
} SpellFxDef; /* 0x48 bytes */

/* A spell's particle record (D_800C363C tables, same index as SpellDef): for three
 * presentation stages a kind (1: Effect_StartConvergeEmitter, 2: Effect_SpawnBurst, 0: none)
 * and the emitter argument. */
typedef struct SpellParticleDef {
    /* 0x00 */ u16 cast_kind; /* cast (Magic_CreateCastPresentation) */
    /* 0x02 */ u16 cast_effect_arg;
    /* 0x04 */ u16 ground_hit_kind; /* ground hit (Magic_CreateGroundHitPresentation) */
    /* 0x06 */ u16 ground_hit_effect_arg;
    /* 0x08 */ u16 hit_kind; /* hit (Magic_CreateHitPresentation) */
    /* 0x0A */ u16 hit_effect_arg;
} SpellParticleDef; /* 0xC bytes */

/* One magic_effects slot: a live spell effect. */
typedef struct MagicEffect {
    /* 0x00 */ u16 unk0; /* spell group */
    /* 0x02 */ u16 unk2; /* spell index */
    /* 0x04 */ u16 unk4; /* frames left, 0: slot free */
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8; /* start delay */
    /* 0x0A */ u16 unkA; /* flags */
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 vy;
    /* 0x20 */ f32 vz;
    /* 0x24 */ Actor *unk24; /* caster */
    /* 0x28 */ Actor *target;
    /* 0x2C */ SpellDef *cfg;
    /* 0x30 */ SpellFxDef *def;
    /* 0x34 */ struct EffectModel *unk34; /* cast visual (Magic_CreateCastPresentation) */
    /* 0x38 */ struct EffectModel *unk38; /* hit visual (Magic_CreateHitPresentation) */
} MagicEffect; /* 0x3C bytes */

/* One magic_cast_repeats slot: the remaining casts of a multi-cast spell. */
typedef struct MagicCastRepeat {
    /* 0x00 */ u16 casts_left; /* casts left */
    /* 0x02 */ u16 frames_until_next_cast; /* frames to the next cast */
    /* 0x04 */ u16 casts_done; /* casts done */
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 spell_id; /* spell id */
    /* 0x0C */ u16 cast_flags; /* cast flags */
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ SpellDef *spell_def;
    /* 0x14 */ Actor *caster; /* caster */
} MagicCastRepeat; /* 0x18 bytes */

typedef struct MagicSpeedTable {
    /* 0x00 */ f32 v[5];
} MagicSpeedTable; /* 0x14 bytes */

typedef void (*MagicPlaceFunc)(MagicEffect *, Actor *);
typedef void (*MagicSelectFunc)(MagicEffect *);
typedef void (*MagicMoveFunc)(MagicEffect *);
typedef Actor *(*MagicFindTargetFunc)(MagicEffect *, s32);
typedef void (*MagicHitFunc)(MagicEffect *, Actor *);
typedef void (*MagicStatusFunc)(u8, Actor *);

/* .bss 80085F90..800863F0, in address order */
extern s32 magic_cast_state; /* 1 cast running, 2 ending (magic_cast_state_timer frames left) */
extern s32 magic_cast_state_timer;
extern MagicEffect magic_effects[16];
extern MagicCastRepeat magic_cast_repeats[4];
extern struct Vec3f magic_temp_vec;
extern struct Enemy *magic_target_enemy_rec;
extern struct CollResult magic_coll;

/* .data */
extern MagicPlaceFunc magic_place_handlers[10];
extern MagicSelectFunc magic_target_select_handlers[3];
extern MagicMoveFunc magic_move_handlers[3];
extern MagicFindTargetFunc magic_find_target_handlers[3];
extern MagicHitFunc magic_hit_handlers[10];
extern MagicStatusFunc magic_status_handlers[12];
extern u16 magic_slot_bits[16];
extern MagicSpeedTable magic_launch_speeds;
extern MagicSpeedTable magic_homing_strengths;
extern MagicSpeedTable magic_homing_accels;
extern u16 magic_damage_bonus_stats[10];
extern s32 magic_hit_outcomes[3];
extern u8 magic_status_chances[12];
extern s32 magic_status_time_range_other[12];
extern s32 magic_status_time_range_self[12];

/* The spell data block: fixed addresses in a block read from ROM (no C module defines it). */
extern SpellDef *D_800C185C[]; /* per group (element): its SpellDef rows */
extern u16 D_800C186E[]; /* indexed by SpellDef.input_length (input length): Magic_GetSpellRestrictionFlags */
extern Vec3f D_800C1878[]; /* launch directions (SpellDef.launch_direction_index) */
extern MagicVisualDef D_800C18D8[]; /* visual effects (SpellFxDef stage indices) */
extern SpellFxDef *D_800C3268[]; /* per group: its SpellFxDef rows */
extern SpellParticleDef *D_800C363C[]; /* per group: its SpellParticleDef rows */

void Magic_ResetEffectSystem(void);
s32 Magic_LookupSpellSequence(u16 n, u8 *arg1);
s32 Magic_GetSpellRestrictionFlags(u32 arg0, u16 arg1);
void Magic_CreateCastEffect(Actor *arg0, u32 arg1, s32 arg2, u16 arg3);
void Magic_PlaceEffectAtActorLowerPoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtActorMiddlePoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtActorUpperPoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAheadAtMiddlePoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAheadAtUpperPoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectBehindAtUpperPoint(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtSelectedTarget(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtRandomOffset(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtDiagonalOffset(MagicEffect *arg0, Actor *arg1);
void Magic_PlaceEffectAtFixedForwardOffset(MagicEffect *arg0, Actor *arg1);
void Magic_UpdateEffects(void);
s32 Magic_IsAnyEffectActive(void);
void Magic_MoveHomingEffect(MagicEffect *arg0);
void Magic_MoveVerticalEffect(MagicEffect *arg0);
Actor *Magic_FindTargetInRange(MagicEffect *arg0, s32 arg1);
Actor *Magic_FindEligibleTarget(MagicEffect *arg0, s32 arg1);
Actor *Magic_FindTargetInRangeIfLanded(MagicEffect *arg0, s32 arg1);
void Magic_ApplyEffectDamage(MagicEffect *arg0, Actor *arg1);
void Magic_HealTarget(MagicEffect *arg0, Actor *arg1);
void Magic_TransferTargetResource(MagicEffect *arg0, Actor *arg1);
void func_80018968(s32 arg0, Actor *arg1);
void func_800189F0(s32 arg0, Actor *arg1);
void Magic_ApplyZeroDamageHit(MagicEffect *arg0, Actor *arg1);
void func_80018B40(s32 arg0, Actor *arg1);
void Magic_RemoveEnemyOrDamagePlayer(MagicEffect *arg0, Actor *arg1);
void Magic_ClearActorStatuses(s32 arg0, Actor *arg1);
void Magic_DamageAndClearStatuses(s32 arg0, Actor *arg1);
void Magic_SelectClosestAimTarget(MagicEffect *arg0);
void Magic_SelectFirstActiveTarget(MagicEffect *arg0);
void Magic_TargetCaster(MagicEffect *arg0);
void Magic_ApplyShrinkStatus(s32 arg0, Actor *arg1);
void func_800190BC(s32 arg0, Actor *arg1);
void func_80019104(s32 arg0, Actor *arg1);
void func_80019184(s32 arg0, Actor *arg1);
void func_8001920C(s32 arg0, Actor *arg1);
void func_800192C8(s32 arg0, Actor *arg1);
void func_800193A4(s32 arg0, Actor *arg1);
void func_80019408(s32 arg0, Actor *arg1);
void func_80019450(s32 arg0, Actor *arg1);
void func_80019498(s32 arg0, Actor *arg1);
void func_800194E0(s32 arg0, Actor *arg1);
void func_800195E0(s32 arg0, Actor *arg1);
u16 Magic_CalculateEffectDamage(SpellDef *arg0, Actor *arg1);
struct EffectModel *Magic_CreateVisualEffect(u16 arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                                             MagicVisualDef *arg6, struct Vec3f *arg7, Actor *arg8);
void Magic_CreateCastPresentation(MagicEffect *arg0, Actor *arg1);
void Magic_CreateTimedPresentation(MagicEffect *arg0, Actor *arg1);
void Magic_CreateHitPresentation(MagicEffect *arg0, Actor *arg1);
void Magic_CreateGroundHitPresentation(MagicEffect *arg0, Actor *arg1);
void Magic_StepActorStatusTimers(Actor *arg0);
s32 Magic_WasActorHitBySlot(s32 arg0, Actor *arg1);
void Magic_MarkActorHitBySlot(s32 arg0, Actor *arg1);
void Magic_ResetHitTracking(void);
void Magic_ClearSlotHitTracking(s32 arg0);
s32 Magic_GetHitOutcome(MagicEffect *arg0, Actor *arg1);
s32 Magic_ShouldApplyStatus(MagicEffect *arg0, Actor *arg1, s32 arg2);
void Magic_StartStatusTimer(MagicEffect *arg0, Actor *arg1, s32 arg2);

#endif
