#ifndef GAME_ENEMY_ENEMY_H
#define GAME_ENEMY_ENEMY_H

#include "common.h"
#include "game/actor/actor.h"

struct Vec3f;
struct GfxFrameData; /* game/core/main.h */
struct CollResult;
struct AnimSet;

/* One entry of an EnemyDef's attack list (unk30, unk2C entries). */
typedef struct EnemyAttack {
    /* 0x00 */ u16 unk0; /* bit 15: spell (id in the low bits, Enemy_StateCastSpell) */
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s16 unk8; /* anim */
    /* 0x0A */ s16 unkA; /* next anim, -1: none */
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 unkE[2];
    /* 0x10 */ f32 unk10; /* range, times the actor's scale */
    /* 0x14 */ f32 unk14;
} EnemyAttack; /* 0x18 bytes */

/* An enemy definition record (enemy_area_set->unkC[], the boss defs). 0x00..0x23 are
 * the same fields as ActorStats: Enemy_Spawn points the actor's unk64 at it. */
typedef struct EnemyDef {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[2];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26; /* index into enemy_element_bits */
    /* 0x28 */ s16 unk28; /* hurt anim */
    /* 0x2A */ u16 unk2A; /* copied to ActorBattle.unk84 */
    /* 0x2C */ u16 unk2C; /* attack count */
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ EnemyAttack *unk30; /* attack list */
    /* 0x34 */ u8 unk34; /* item id (func_800200F8) */
    /* 0x35 */ u8 pad35[3];
} EnemyDef; /* 0x38 bytes */

/* One enemy_area_sets entry. */
typedef struct EnemyAreaSet {
    /* 0x00 */ u8 *start; /* ROM range DMA'd by Enemy_LoadAreaSet (Dma_ReadRom devAddr) */
    /* 0x04 */ u8 *end;
    /* 0x08 */ u8 **unk8; /* -> enemy_anim_tables */
    /* 0x0C */ EnemyDef *unkC;
    /* 0x10 */ s32 unk10; /* -> enemy_names */
} EnemyAreaSet; /* 0x14 bytes */

/* One step of an enemy attack script (enemy_attack_scripts, Enemy_RunAttackScript). */
typedef struct EnemyScriptCmd {
    /* 0x00 */ u16 time;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 flags; /* 1: last, 2: at the player, 4: camera shake, 8: offset enemy_slots[0].unk20/24 */
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} EnemyScriptCmd; /* 0x18 bytes */

/* One enemy_slots entry (also boss_field_record). */
typedef struct Enemy {
    /* 0x000 */ u16 type; /* state, index into enemy_state_handlers */
    /* 0x002 */ s16 unk2; /* state timer */
    /* 0x004 */ u16 unk4;
    /* 0x006 */ u16 unk6;
    /* 0x008 */ u16 flags;
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 pad14[8];
    /* 0x01C */ EnemyAttack *unk1C; /* chosen attack */
    /* 0x020 */ f32 unk20;
    /* 0x024 */ f32 unk24;
    /* 0x028 */ EnemyDef *unk28;
    /* 0x02C */ Actor actor;
    /* 0x098 */ ActorBattle battle; /* actor.unk68 points here */
} Enemy; /* 0x130 bytes */

typedef void (*EnemyStateFunc)(Actor *, Enemy *, u8 *);

/* .bss 8007B900..8007C0B0, in address order (unreferenced gaps included) */
extern s32 enemy_count;
extern s32 D_8007B904;
extern Enemy enemy_slots[6];
extern Enemy *enemy_turn_current;
extern s32 enemy_drawn_count;
extern Actor *enemy_drawn_list[6];
extern u8 **enemy_anim_tables;
extern s32 enemy_names;
extern u16 enemy_turn_order[6];
extern EnemyAreaSet *enemy_area_set;
extern u16 enemy_script_time;
extern EnemyScriptCmd *enemy_script_cmd;
extern Enemy *enemy_script_enemy;
extern Actor *enemy_script_obj;
extern struct Vec3f enemy_temp_vec;
extern struct CollResult enemy_coll;
extern s32 D_8007C09C;
extern s32 D_8007C0A0[4];

/* .data */
extern EnemyStateFunc enemy_state_handlers[6];
extern s32 enemy_element_bits[5];

void Enemy_InitForArea(void);
void Enemy_LoadAreaSet(void);
void Enemy_UpdateAll(void);
void Enemy_DrawAll(struct GfxFrameData *arg0);
void Enemy_RemoveAll(void);
void Enemy_Spawn(s32 idx, f32 x, f32 z, f32 angle, Actor *obj, Enemy *e);
void Enemy_SortTurnOrder(void);
void Enemy_StartTurn(void);
void Enemy_StateIdle(Actor *obj, Enemy *e, struct AnimSet *arg2);
void Enemy_StateApproach(Actor *obj, Enemy *e, struct AnimSet *arg2);
void Enemy_StateHurt(Actor *obj, Enemy *ai, s32 arg2);
void Enemy_StateFacePlayer(Actor *obj, Enemy *ai, s32 arg2);
void Enemy_StateMeleeAttack(Actor *obj, Enemy *e, struct AnimSet *anims);
void Enemy_StateCastSpell(Actor *obj, Enemy *e, struct AnimSet *anims);
EnemyAttack *Enemy_ChooseAttack(Enemy *e, Actor *obj);
void Enemy_StartAttack(Enemy *e, Actor *obj, EnemyAttack *arg2);
void Enemy_TurnToward(Actor *obj, f32 x, f32 z);
void Enemy_Move(s32 clamp, f32 dx, f32 dz, Actor *obj, Enemy *ai);
void Enemy_GetAnimStep(Actor *obj, struct Vec3f *out);
void Enemy_ResolveCollisions(f32 *dx, f32 *dz, Actor *obj);
s32 Enemy_RollHitOnPlayer(Actor *obj);
u16 Enemy_CalcAttackDamage(Enemy *arg0);
u16 Enemy_TakeDamage(s32 idx, u16 dmg, u16 elem, u16 flags, Actor *src);
void Enemy_PlayMissEffect(Actor *obj);
s32 Enemy_GetSlotIndex(Actor *arg0);
void Enemy_SpawnDeathEffects(Actor *obj);
void Enemy_ClearAttackScript(void);
void Enemy_StartAttackScript(s32 arg0, s32 arg1);
void Enemy_RunAttackScript(void);

#endif
