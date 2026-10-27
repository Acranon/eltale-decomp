#ifndef GAME_ENEMY_BOSS_H
#define GAME_ENEMY_BOSS_H

#include "common.h"
#include "game/actor/actor.h"
#include "game/enemy/enemy.h"

struct CollResult;

/* .bss 8007C0B0..8007C280, in address order (unreferenced gaps included) */
extern struct CollResult boss_spawn_coll;
extern s32 D_8007C0CC;
extern Actor boss_camera_target;
extern u8 boss_defeated_bits[4];
extern s32 boss_field_index;
extern s32 D_8007C144;
extern Enemy boss_field_record; /* the boss standing on the field map */
extern s32 D_8007C278[2];

/* .data */
extern u16 boss_reward_max_hp[8];
extern u16 boss_reward_max_mp[8];

void Boss_ClearDefeated(void);
void Boss_LoadForArea(void);
void Boss_Draw(struct GfxFrameData *arg0);
s32 Boss_CheckPlayerNear(void);
void Boss_Spawn(s32 arg0, f32 arg1, f32 arg2, f32 arg3, Enemy *arg4);
u8 Boss_IsDefeated(u32 arg0);
void Boss_SetDefeated(u16 arg0);
void Boss_BeginEncounter(s32 arg0);
void Boss_HandleDefeat(s32 arg0);

#endif
