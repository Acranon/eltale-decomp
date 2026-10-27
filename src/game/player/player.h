#ifndef GAME_PLAYER_PLAYER_H
#define GAME_PLAYER_PLAYER_H

#include "common.h"
#include "game/actor/actor.h"

struct Vec3f;
struct GfxFrameData; /* game/core/main.h */
struct CollResult;
struct AnimSet;
struct SpiritObj; /* game/map/spirit.h */
struct TextSpot; /* game/map/textspot.h */

/* player_state: the player's state machine around its Actor. */
typedef struct Player {
    /* 0x000 */ u16 state; /* state, index into player_state_handlers */
    /* 0x002 */ u16 melee_target_plus_one; /* melee target: enemy_slots index + 1 */
    /* 0x004 */ u16 state_timer; /* state timer */
    /* 0x006 */ u16 unk6;
    /* 0x008 */ s32 flags; /* flags */
    /* 0x00C */ f32 unkC;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ ActorStats *stats; /* &player_stats (Player_Init) */
    /* 0x018 */ Actor actor;
    /* 0x084 */ ActorBattle battle; /* actor.unk68 points here */
    /* 0x11C */ u8 item_id; /* item id (chest, use item) */
    /* 0x11D */ u8 spell_input_dirs[3]; /* spell input directions */
    /* 0x120 */ u16 spell_input_count; /* spell input count */
    /* 0x122 */ u16 spell_id; /* spell id (Magic_LookupSpellSequence) */
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u16 unk126;
    /* 0x128 */ u16 unk128;
    /* 0x12A */ u16 unk12A;
    /* 0x12C */ f32 unk12C;
    /* 0x130 */ f32 unk130;
    /* 0x134 */ f32 unk134;
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 unk13C[4];
} Player; /* 0x140 bytes */

/* The player's anim set table (a player_char_data entry) read as one record: every field
 * is the s16 at +2 of a 0xC-byte AnimSet entry (entry n at 0xC * n + 2), the length that
 * the state timers are set from. */
typedef struct PlayerAnimTable {
    /* 0x000 */ u8 unk0[0x56];
    /* 0x056 */ s16 unk56; /* anim 7 */
    /* 0x058 */ u8 unk58[0x62 - 0x58];
    /* 0x062 */ s16 unk62; /* anim 8 */
    /* 0x064 */ u8 unk64[0x7A - 0x64];
    /* 0x07A */ s16 unk7A; /* anim 10 */
    /* 0x07C */ u8 unk7C[0x86 - 0x7C];
    /* 0x086 */ s16 unk86; /* anim 11 */
    /* 0x088 */ u8 unk88[0xC2 - 0x88];
    /* 0x0C2 */ s16 unkC2; /* anim 16 */
    /* 0x0C4 */ u8 unkC4[0xDA - 0xC4];
    /* 0x0DA */ s16 unkDA; /* anim 18 */
    /* 0x0DC */ u8 unkDC[0x116 - 0xDC];
    /* 0x116 */ s16 unk116; /* anim 23 */
    /* 0x118 */ u8 unk118[0x122 - 0x118];
    /* 0x122 */ s16 unk122; /* anim 24 */
} PlayerAnimTable;

typedef void (*PlayerStateFunc)(Actor *, Player *, PlayerAnimTable *);

/* .bss 8007A8F0..8007AB70, in address order (unreferenced gaps included) */
extern f32 player_mp_regen_dist;
extern f32 D_8007A8F4;
extern f32 D_8007A8F8;
extern f32 player_agility_dist_enemy_area;
extern f32 player_agility_dist_npc_area;
extern s32 player_near_boss;
extern s32 player_boss_text_delay;
extern u16 player_run_sfx_timer;
extern u16 D_8007A90E;
extern s32 player_idle_anim;
extern s32 D_8007A914;
extern struct Vec3f player_temp_vec;
extern s32 D_8007A924;
extern struct CollResult player_coll;
extern s32 D_8007A944;
extern u8 D_8007A948[0x40];
extern f32 player_battle_move_dist;
extern f32 player_spawn_x;
extern f32 player_spawn_z;
extern f32 player_spawn_rot;
extern s32 player_spawn_type; /* bit 3: start in state 3; bits 8-10: entry kind (Player_Spawn) */
extern s32 player_spawn_obj;
extern f32 player_move_dx;
extern f32 player_move_dz;
extern f32 player_move_dist;
extern u16 player_respawn_map;
extern u16 player_respawn_subarea;
extern u16 player_respawn_entry;
extern u16 D_8007A9B2;
extern s32 player_battle_exp;
extern s32 D_8007A9B8;
extern s32 player_battle_drop_item;
extern s32 player_talk_npc;
extern struct SpiritObj *player_front_spirit;
extern Actor *player_front_chest;
extern struct TextSpot *player_front_text_spot;
extern ActorStats player_stats;
extern Player player_state;
extern struct Vec3f player_shadow_pos;
extern s32 D_8007AB54;
extern s32 D_8007AB58;
extern s32 D_8007AB5C;
extern s32 player_light_slot;

/* Labels inside player_state (aliases in undefined_syms.txt). Some retail functions address
 * these fields as their own symbols: through player_state.actor uopt shares one player_state
 * base register between them and the code differs. Use them only where that is so
 * (Player_Draw, Enemy_ChooseAttack, Enemy_ResolveCollisions, Npc_PushOutOfObjects). */
extern Actor D_8007AA20; /* player_state.actor */
extern f32 D_8007AA24; /* player_state.actor.y */
extern f32 D_8007AA28; /* player_state.actor.z */
extern s16 D_8007AA70; /* player_state.actor.animSetIndex */
extern s16 D_8007AA72; /* player_state.actor.animIndex */
extern u16 D_8007AA78; /* player_state.actor.animStep */
extern ActorStats *D_8007AA84; /* player_state.actor.stats */

/* Labels inside player_stats and player_state (aliases in undefined_syms.txt) that the menu's
 * stats and elements pages address as their own symbols (through player_stats.x /
 * player_state.flags the code differs: Menu_UpdateStatsPage, Menu_UpdateElementsPage). */
extern u16 D_8007A9D4; /* player_stats.unk4 */
extern u16 D_8007A9D6; /* player_stats.unk6 */
extern u16 D_8007A9D8; /* player_stats.unk8 */
extern u16 D_8007A9DA; /* player_stats.unkA */
extern u16 D_8007A9DC; /* player_stats.unkC */
extern u16 D_8007A9DE; /* player_stats.unkE */
extern s32 D_8007A9E0; /* player_stats.unk10 */
extern u8 D_8007A9F4; /* player_stats.unk24[0] */
extern u8 D_8007A9F5; /* player_stats.unk24[1] */
extern u8 D_8007A9F6; /* player_stats.unk24[2] */
extern u8 D_8007A9F7; /* player_stats.unk24[3] */
extern u16 D_8007A9F8; /* player_stats.unk28 */
extern u16 D_8007A9FA; /* player_stats.unk2A */
extern u16 D_8007A9FC; /* player_stats.unk2C */
extern u16 D_8007A9FE; /* player_stats.unk2E */
extern u8 D_8007AA00; /* player_stats.unk30 */
extern u8 D_8007AA01; /* player_stats.unk31 */
extern u8 D_8007AA02; /* player_stats.unk32 */
extern u8 D_8007AA03; /* player_stats.unk33 */
extern u8 D_8007AA04; /* player_stats.unk34 */
extern s32 D_8007AA10; /* player_state.flags */

/* .data */
extern PlayerStateFunc player_state_handlers[18];
extern s32 player_melee_damage_scale[4];

void Player_Init(void);
void Player_Spawn(void);
void Player_SetSpawnFromSaveTable(void);
void Player_Update(void);
void Player_Draw(struct GfxFrameData *arg0);
void Player_InitBattle(void);
void Player_StateMove(Actor *a, Player *p, PlayerAnimTable *cd);
void Player_StateWait(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateBrake(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateHurt(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateDying(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateTalk(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateAutoWalk(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateMeleeAttack(Actor *a, Player *p, PlayerAnimTable *cd);
void Player_StateCastSpell(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateWalkToExitObject(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateAnimMove(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateOpenChest(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateUseItem(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateBattleWon(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_StateExamine(Actor *arg0, Player *arg1, PlayerAnimTable *arg2);
void Player_MoveIdle(f32 arg0, f32 arg1, Actor *arg2, Player *arg3);
void Player_MoveWalk(f32 sx, f32 sz, Actor *a, Player *p);
void Player_MoveRun(f32 sx, f32 sz, Actor *a, Player *p);
void Player_GetAnimMotion(Actor *arg0, struct AnimSet *arg1, struct Vec3f *arg2);
void func_80006A50(void); /* empty */
void Player_MoveAndCollide(u16 arg0, Actor *arg1, Player *arg2);
s32 Player_FindNpcToTalk(Player *arg0, Actor *arg1);
void Player_PushOutOfObjects(f32 *arg0, f32 *arg1, Actor *arg2);
void Player_ApplyFloorEffect(Player *arg0, Actor *arg1);
void Player_StartAreaExit(void);
void Player_StartObjectExit(Player *arg0, Actor *arg1);
void Player_StartOpenChest(Player *arg0, Actor *arg1, s32 arg2);
void Player_StartUseItem(u8 arg0);
void Player_LoadAnim(Actor *arg0);
/* returns the enemy_slots index + 1 of the target, 0: none (retail returns it unmasked) */
s32 Player_FindMeleeTarget(Actor *arg0);
void Player_StartMeleeAttack(Player *arg0, Actor *arg1, PlayerAnimTable *arg2);
s32 Player_RollHitOnEnemy(s32 arg0, Actor *arg1);
u16 Player_CalcMeleeDamage(Player *arg0);
/* returns the damage taken (dmg after the back-hit bonus, defence and random part) */
u16 Player_TakeDamage(u16 dmg, u16 arg1, Actor *arg2);
void Player_StartMissReaction(void);
s32 Player_CanAct(Player *arg0, Actor *arg1);
s32 Player_HandleSpellInput(Player *arg0);
void Player_StartCastSpell(Player *p, Actor *a, struct AnimSet *anims);
void Player_AddTurnMoveAgilityXP(Player *arg0);
void Player_UpdateStatGrowth(Player *p, Actor *a);

#endif
