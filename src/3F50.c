#include "common.h"

/*
 * Player actor: init/spawn, per-frame update and draw, the state machine (move, talk, chest,
 * item, exits, melee attack, spell input and casting, hurt, death, battle start/won),
 * movement and collision, damage taken and dealt, stat growth from XP.
 * Folder: src/game/player/   (proposed for round 4)
 */

typedef struct {
    f32 x;
    f32 z;
    f32 unk8;
} Vec2f;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[0x38 - 0x24];
} ActorStats;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2[0x84 - 0x2];
    /* 0x84 */ u16 unk84;
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u8 unk88[0x94 - 0x88];
    /* 0x94 */ f32 unk94;
} ActorSub68;

/* animation table entry (size 0xC) */
typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u8 unk4[0x8];
} AnimEntry;

/* a moving object: the player (D_8007AA20, inside D_8007AA08) and others */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 rot;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 vz;
    /* 0x24 */ f32 scale;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38[0x44 - 0x38];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ ActorStats *unk64;
    /* 0x68 */ ActorSub68 *unk68;
} Actor; /* size 0x6C */

typedef struct {
    /* 0x00 */ u8 unk0[0x4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA[0x18 - 0xA];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0x24 - 0x1C];
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
} PlayerStateSub14;

/* D_8007B908: monsters, size 0x130 */
typedef struct {
    /* 0x00 */ u8 unk0[0xA];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC[0x2C - 0xC];
    /* 0x2C */ Actor actor;
    /* 0x98 */ u8 unk98[0x130 - 0x98];
} Monster;

typedef struct {
    /* 0x0 */ u8 *start;
    /* 0x4 */ u8 *end;
} RomRange;

/* D_8007AA08 */
typedef struct {
    /* 0x000 */ u16 unk0; /* state, index into D_8004DCB0 */
    /* 0x002 */ u16 unk2;
    /* 0x004 */ u16 unk4; /* state timer */
    /* 0x006 */ u16 unk6;
    /* 0x008 */ s32 unk8; /* flags */
    /* 0x00C */ f32 unkC;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ PlayerStateSub14 *unk14;
    /* 0x018 */ Actor actor;
    /* 0x084 */ u16 unk84;
    /* 0x086 */ u16 unk86;
    /* 0x088 */ u8 unk88[0x108 - 0x88];
    /* 0x108 */ u16 unk108;
    /* 0x10A */ u16 unk10A;
    /* 0x10C */ u16 unk10C;
    /* 0x10E */ u16 unk10E;
    /* 0x110 */ u16 unk110;
    /* 0x112 */ u16 unk112;
    /* 0x114 */ f32 unk114;
    /* 0x118 */ u8 unk118[0x11C - 0x118];
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 unk11D[0x120 - 0x11D];
    /* 0x120 */ u16 unk120;
    /* 0x122 */ u16 unk122;
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u16 unk126;
    /* 0x128 */ u16 unk128;
    /* 0x12A */ u16 unk12A;
    /* 0x12C */ f32 unk12C;
    /* 0x130 */ f32 unk130;
    /* 0x134 */ f32 unk134;
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 unk13C[4];
} PlayerState; /* size 0x140 */

/* per-character data, from the player_char_data table */
typedef struct {
    /* 0x000 */ u8 unk0[0x56];
    /* 0x056 */ s16 unk56;
    /* 0x058 */ u8 unk58[0x7A - 0x58];
    /* 0x07A */ s16 unk7A;
    /* 0x07C */ u8 unk7C[0x86 - 0x7C];
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 unk88[0xC2 - 0x88];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 unkC4[0xDA - 0xC4];
    /* 0x0DA */ s16 unkDA;
    /* 0x0DC */ u8 unkDC[0x116 - 0xDC];
    /* 0x116 */ s16 unk116;
    /* 0x118 */ u8 unk118[0x122 - 0x118];
    /* 0x122 */ s16 unk122;
} CharData;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 unk1A[0x44 - 0x1A];
} Unk800C185C; /* size 0x44 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
} Unk80084300;

typedef struct {
    /* 0x00 */ u8 unk0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ u8 unk50[0x58 - 0x50];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ u8 unk5C[0x70 - 0x5C];
    /* 0x70 */ f32 unk70;
} Unk80085E48;

typedef struct {
    /* 0x0 */ void *unk0;
    /* 0x4 */ u8 unk4[0x80];
} Unk8007AC70; /* size 0x84 */

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u8 unk2[0xA];
} Unk803AAAA2; /* size 0xC */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

/* collision query result (Coll_ResolveFloorAndWalls) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 unk1A[0x60 - 0x1A]; /* not referenced; the next label is 8007A988 */
} Unk8007A928;

void Player_GetAnimMotion(Actor *arg0, s32 arg1, Vec2f *arg2);
void Player_MoveAndCollide(u16 arg0, Actor *arg1, PlayerState *arg2);
void Player_MoveWalk(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3);
void Player_LoadAnim(Actor *arg0);
void Player_AddTurnMoveAgilityXP(PlayerState *arg0);
void Npc_EndTalk(s32 arg0);
void Item_BuildMessage(s32 arg0);
void Magic_CreateCastEffect(Actor *arg0, u16 arg1, s32 arg2, u16 arg3);
s32 Magic_IsAnyEffectActive(void);
void Effect_StartFootEmitter(Actor *arg0);
void Battle_EndTurn(Actor *arg0);
void Anim_SetCurrentAndNext(Actor *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void Anim_UpdateRootMotion(Actor *arg0, s32 arg1, f32 arg2);
void Hud_ClearActorStatusIndicators(Actor *arg0);
void Item_AddToInventory(u8 arg0);
void Item_ApplyEffect(u8 arg0, Actor *arg1);
void Math_RotateVec2(f32 arg0, Vec2f *arg1);
void Audio_StartSeqFadeOut(s32 arg0);
void Bgm_Play(s32 arg0);
void Sfx_Play(u8 arg0, s8 arg1, u8 arg2);
s32 Text_OpenWindow(s32 arg0);
s32 Player_RollHitOnEnemy(s32 arg0, Actor *arg1);
u16 Player_CalcMeleeDamage(PlayerState *arg0);
void Player_MoveIdle(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3);
void Player_MoveRun(f32 sx, f32 sz, Actor *a, PlayerState *p);
void Player_ApplyFloorEffect(PlayerState *arg0, Actor *arg1);
void Player_UpdateStatGrowth(PlayerState *arg0, Actor *arg1);
void Player_MoveIdle(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3);
void Player_MoveRun(f32 sx, f32 sz, Actor *a, PlayerState *p);
void Player_ApplyFloorEffect(PlayerState *arg0, Actor *arg1);
void Player_UpdateStatGrowth(PlayerState *arg0, Actor *arg1);
#ifdef NON_MATCHING
/* retail: the damage argument is masked with 0xFFFF on entry */
s32 Player_TakeDamage(u16 dmg, u16 arg1, Actor *arg2);
#else
s32 Player_TakeDamage(s32 arg0, u16 arg1, Actor *arg2);
#endif
void Camera_StartBattleFocus(s32 arg0, Actor *arg1);
u32 Math_Rand(s32 arg0);
f32 Math_Atan2(f32 arg0, f32 arg1);
void Dma_ReadRom(u8 *romStart, void *dest, u32 size);
void Hud_ShowActorPopup(Actor *arg0);
f32 sqrtf(f32 x);

extern s32 D_8004DCA0;
extern u16 D_800842E8;
extern u16 input_pressed_buttons;
extern CharData *player_char_data[];
extern RomRange player_anim_rom_ranges[];
extern Monster D_8007B908[];
extern u16 battle_flags;
extern u16 battle_turn_delay;
extern f32 battle_active_enemy_x;
extern f32 battle_active_enemy_z;
extern s16 hud_melee_hint_timer;
extern Unk800C185C *D_800C185C[];
extern u16 D_800C186E[];
extern s32 D_8007A174;
extern u16 D_8007A178;
extern s16 D_8007A17A;
extern Unk8007AC70 D_8007AC70[];
extern Unk80084300 D_80084300;
extern s32 D_800842BC;
extern s32 D_800842C0;
extern Unk80085E48 D_80085E48;
extern s16 hud_panel_transition_frame;
extern u16 hud_panel_transition_state;
extern s32 text_active_window_count;
extern s32 text_last_choice_index;
extern Unk803AAAA2 D_803AAAA2[];
extern u8 D_869620[];
extern u8 D_86F6F0[];
extern u8 D_80206000[];
extern ActorStats player_default_stats;

/* This file's .bss, 8007A8F0..8007AB70, in address order. IDO lays .bss out
 * in the order names are first declared, so this block comes before any other
 * mention of these names. IDO also numbers symbols in blocks of 256 (typedefs,
 * struct tags and data declarations count, prototypes don't) and emits the
 * later block first, so the whole list must sit inside one block: the externs
 * above are here to push it past a boundary. Labels inside these objects
 * (fields of D_8007A9D0, D_8007AA08, ...) are aliases in undefined_syms.txt.
 * D_8007A90E, D_8007A914, D_8007A924, D_8007A9B2, D_8007AB54..5C are
 * unreferenced gaps. */
f32 D_8007A8F0;
f32 D_8007A8F4;
f32 D_8007A8F8;
f32 D_8007A8FC;
f32 D_8007A900;
s32 D_8007A904;
s32 D_8007A908;
u16 D_8007A90C;
u16 D_8007A90E;
s32 D_8007A910;
s32 D_8007A914;
Vec2f D_8007A918;
s32 D_8007A924;
Unk8007A928 D_8007A928;
f32 D_8007A988;
f32 D_8007A98C;
f32 D_8007A990;
f32 D_8007A994;
s32 D_8007A998;
s32 D_8007A99C;
f32 D_8007A9A0;
f32 D_8007A9A4;
f32 D_8007A9A8;
u16 D_8007A9AC;
u16 D_8007A9AE;
u16 D_8007A9B0;
u16 D_8007A9B2;
s32 D_8007A9B4;
s32 D_8007A9B8;
s32 D_8007A9BC;
s32 D_8007A9C0;
void *D_8007A9C4;
Actor *D_8007A9C8;
void *D_8007A9CC;
ActorStats D_8007A9D0;
PlayerState D_8007AA08;
Vec3f D_8007AB48;
s32 D_8007AB54;
s32 D_8007AB58;
s32 D_8007AB5C;
s32 D_8007AB60;

extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern u16 D_8007A90C;
extern f32 D_8007A988;
extern PlayerState D_8007AA08;
extern Actor D_8007AA20;
extern s32 D_8007A910;
extern Vec2f D_8007A918;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern u16 D_8007A9AC;
extern u16 D_8007A9AE;
extern u16 D_8007A9B0;
extern s32 D_8007A9C0;
extern s16 D_8007AA0E;

extern ActorStats D_8007A9D0;
extern ActorSub68 D_8007AA8C;
extern f32 D_8007A8F4;
extern f32 D_8007A8F8;
extern f32 D_8007A8FC;
extern f32 D_8007A900;

void Player_Init(void) {
    Dma_ReadRom(D_869620, D_80206000, D_86F6F0 - D_869620);
    D_8007A9D0 = player_default_stats;
    D_8007AA08.actor.scale = D_8007A9D0.unk20;
    D_8007AA08.actor.unk28 = D_8007A9D0.unk18;
    D_8007AA08.actor.unk50 = D_8007A9D0.unk2;
    D_8007AA08.unk14 = (PlayerStateSub14 *)&D_8007A9D0;
    D_8007AA08.unk6 = 0;
    D_8007AA08.unk8 = 0;
    D_8007AA08.unk120 = 0;
    D_8007AA08.actor.unk52 = -1;
    D_8007AA08.actor.unk54 = 0;
    D_8007AA08.actor.unk58 = 1;
    D_8007AA08.actor.unk64 = &D_8007A9D0;
    D_8007AA08.actor.unk68 = &D_8007AA8C;
    D_8007AA08.actor.unk5E = 0;
    D_8007AA08.actor.unk60 = 0;
    D_8007A998 = 0x108;
    D_8007A9AC = 0xD;
    D_8007A9AE = 0x11;
    D_8007A9B0 = 0;
    D_8007A988 = 0.0f;
    D_8007A8F4 = D_8007A8F8 = 0.0f;
    D_8007A8FC = D_8007A900 = 0.0f;
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rot; /* degrees */
    /* 0x10 */ u8 unk10[0x18 - 0x10];
} Unk8007C290; /* size 0x18 */

extern Unk8007C290 *D_8007C290;
extern s32 D_8007A99C;
extern f32 D_8007A8F0;
extern s32 D_8007A9BC;
extern void *D_8007A9C4;
extern Actor *D_8007A9C8;
extern void *D_8007A9CC;
void Coll_ResolveFloorAndWalls(f32 x, f32 y, f32 z, u16 flags, void *out);
void MapObjAnim_Start(s32 arg0, s32 arg1, s32 arg2, Unk8007C290 *arg3);

void Player_Spawn(void) {
    s32 n;
    s32 pad;
    PlayerState *p = &D_8007AA08;
    CharData *cd;
    Unk8007C290 *pos;

    D_8004DCA0 &= ~0x10000;
    cd = player_char_data[D_8007AA08.actor.unk50];
    D_8007AA08.unk0 = 0;
    D_8007AA08.unk128 = 0;
    D_8007AA08.actor.x = D_8007A98C;
    D_8007AA08.actor.y = 0.0f;
    D_8007AA08.actor.z = D_8007A990;
    D_8007AA08.actor.unkC = 0.0f;
    D_8007AA08.actor.unk14 = 0.0f;
    D_8007AA08.actor.rot = D_8007A994;
    D_8007AA08.actor.vx = 0.0f;
    D_8007AA08.actor.unk1C = 0.0f;
    D_8007AA08.actor.vz = 0.0f;
    Coll_ResolveFloorAndWalls(D_8007A98C, 0.0f, D_8007A990, 0xA00, &D_8007A928);
    p->actor.y = D_8007A928.unk4;
    p->actor.unk2C = D_8007A928.unkC;
    p->actor.unk30 = D_8007A928.unk10;
    p->actor.unk34 = D_8007A928.unk14;
    if (D_8007A928.unk18 & 0x8000) {
        p->actor.unk62 = 0;
    } else {
        p->actor.unk62 = D_8007A928.unk18;
    }
    Anim_SetCurrentAndNext(&D_8007AA20, p->unk6 ? p->unk6 : D_8007A910, 1, D_8007A910, 1, 1);
    if (D_8007A998 & 8) {
        p->unk0 = 3;
        p->unk4 = 0xF;
        p->actor.unk60 = 1;
    } else {
        switch ((D_8007A998 >> 8) & 7) {
            case 1:
            case 4:
                p->unk0 = 8;
                p->unk4 = 0xF;
                D_8007A918.x = 0.0f;
                D_8007A918.z = 20.0f;
                Math_RotateVec2(p->actor.rot, &D_8007A918);
                p->unk12C = D_8007A918.x;
                p->unk130 = D_8007A918.z;
                p->actor.unk60 = 1;
                Sfx_Play(5, 0x21, 0xFF);
                Sfx_Play(0xF, 0x21, 0xFF);
                break;
            case 2:
                p->unk0 = 10;
                pos = &D_8007C290[D_8007A99C];
                p->unk138 = p->actor.rot = pos->rot * 0.017453292519943295;
                if (D_8007A998 & 1) {
                    p->unk4 = 0x15;
                    p->actor.unk54 = 0x55;
                    D_8007A918.x = -115.61f;
                    D_8007A918.z = 15.746f;
                    n = 0xE;
                } else {
                    p->unk4 = 0x1F;
                    p->unk138 = p->unk138 + 3.141592653589793;
                    p->actor.unk54 = 0x3C;
                    D_8007A918.x = -132.831f;
                    D_8007A918.z = -120.681f;
                    n = 0x14;
                }
                Math_RotateVec2(-pos->rot * 0.017453292519943295, &D_8007A918);
                p->actor.x = pos->x - D_8007A918.x * p->actor.scale;
                p->actor.z = pos->z + D_8007A918.z * p->actor.scale;
                p->actor.unk60 = 1;
                Player_LoadAnim(&D_8007AA20);
                Anim_UpdateRootMotion(&D_8007AA20, p->actor.unk52 * 0xC + (s32) cd, p->actor.scale);
                MapObjAnim_Start(1, (u16) p->actor.unk54, D_8007A998, pos);
                Sfx_Play(n, 8, 0xFF);
                break;
            case 3:
                p->unk0 = 8;
                p->unk4 = 0xF;
                D_8007A918.x = 0.0f;
                D_8007A918.z = 20.0f;
                Math_RotateVec2(p->actor.rot, &D_8007A918);
                p->unk12C = D_8007A918.x;
                p->unk130 = D_8007A918.z;
                p->actor.unk60 = 1;
                Player_LoadAnim(&D_8007AA20);
                Anim_UpdateRootMotion(&D_8007AA20, p->actor.unk52 * 0xC + (s32) cd, p->actor.scale);
                MapObjAnim_Start(1, (u16) p->actor.unk54, D_8007A998, pos);
                Sfx_Play(5, 0x21, 0xFF);
                Sfx_Play(0xF, 0x21, 0xFF);
                break;
        }
    }
    p->unk8 = 0;
    if (D_80084300.unk8 == -1) {
        p->unk8 |= 0x10;
    }
    if (D_8004DCA0 & 0x800) {
        p->actor.unk64->unk4 = 1;
        p->actor.unk64->unk8 = p->actor.unk64->unkA;
        p->actor.unk68->unk0 = 0;
    }
    p->actor.unk68->unk0 = 0;
    D_8007A9A8 = D_8007A8F0 = 0.0f;
    D_8007A90C = 0;
    D_8007A9BC = 0xFF;
    D_8007A9C0 = 0;
    D_8007A9C4 = 0;
    D_8007A9C8 = 0;
    D_8007A9CC = 0;
    if (p->unk14->unk24[0] == 50) {
        p->unk8 |= 0x1000;
    }
    if (p->unk14->unk24[1] == 50) {
        p->unk8 |= 0x2000;
    }
    if (p->unk14->unk24[2] == 50) {
        p->unk8 |= 0x4000;
    }
    if (p->unk14->unk24[3] == 50) {
        p->unk8 |= 0x8000;
    }
    if ((p->unk8 & 0xF000) == 0xF000) {
        p->unk8 |= 0x10000;
    }
}



typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 x;
    /* 0x8 */ f32 y;
    /* 0xC */ f32 rot;
} Unk80056088; /* size 0x10 */

extern Unk80056088 player_save_spawn_points[];
extern Unk80056088 D_80056198[];
extern s32 D_800842C4;
extern s32 D_800842C8;

void Player_SetSpawnFromSaveTable(void) {
    s32 i;

    D_8007AA08.unk14->unk18 = 50.0f;
    D_800842C4 = D_800842BC;
    D_800842C8 = D_800842C0;
    D_80084300.unk8 = 0;
    for (i = 0; i < 17; i++) {
        if (D_800842BC == player_save_spawn_points[i].unk0 && D_800842C0 == player_save_spawn_points[i].unk2) {
            D_8007A98C = player_save_spawn_points[i].x;
            D_8007A990 = player_save_spawn_points[i].y;
            D_8007A994 = player_save_spawn_points[i].rot;
            D_80084300.unk8 = -1;
            break;
        }
    }
    D_800842BC = -1;
    D_800842C0 = -1;
}

/* D_8007A9C4: Spirit_FindInFront's result */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
} Unk8007A9C4;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ s32 unk18;
} Unk8007A9CCEntry;

/* D_8007A9CC: TextSpot_FindInFront's result */
typedef struct {
    /* 0x00 */ Unk8007A9CCEntry *entry;
} Unk8007A9CC;

extern void *D_8007A9C4;
extern Actor *D_8007A9C8;
extern void *D_8007A9CC;
extern s32 D_8007A904;
extern s32 D_8007A908;
extern f32 D_8007A9A0;
extern f32 D_8007A9A4;
extern s32 D_8007A9B4;
extern s32 D_8007A9B8;
extern s32 D_8007A9BC;
extern f32 D_8007A8F0;
extern s32 hud_npc_marker_screen_y;
extern s16 hud_element_input_timer;
extern u8 fade_black_ramp[];
extern u8 fade_black_ramp_dim[];
extern void (*D_8004DCB0[])(Actor *, PlayerState *, CharData *);
#ifdef NON_MATCHING
/* retail returns the unmasked index + 1 in v0 */
s32 Player_FindMeleeTarget(Actor *arg0);
#else
u16 Player_FindMeleeTarget(Actor *arg0);
#endif
s32 Player_FindNpcToTalk(PlayerState *arg0, Actor *arg1);
void *Spirit_FindInFront(Actor *arg0);
Actor *Chest_FindInFront(Actor *arg0);
void *TextSpot_FindInFront(Actor *arg0);
s32 Boss_CheckPlayerNear(void);
void Boss_BeginEncounter(s32 arg0);
void Npc_StartTalk(s32 idx);
void Spirit_SetCollected(u16 arg0);
s32 Item_HasInventoryRoom(void);
void Chest_Open(Actor *arg0);
void TextSpot_LoadMessage(void *arg0);
s32 Player_CanAct(PlayerState *arg0, Actor *arg1);
void Fade_Start(s32 arg0, u16 arg1, void *arg2);
s32 Player_HandleSpellInput(PlayerState *arg0);
void Player_StartCastSpell(PlayerState *p, Actor *a, AnimEntry *anims);
s32 Item_CountInInventory(u8 arg0);
s32 Item_GetInventoryCount(void);
void Player_StartMeleeAttack(PlayerState *arg0, Actor *arg1, CharData *arg2);
void Player_StartOpenChest(PlayerState *arg0, Actor *arg1, s32 arg2);

void Player_Update(void) {
    PlayerState *p = &D_8007AA08;
    s32 pad;
    CharData *cd;
    u8 *s;

    cd = player_char_data[p->actor.unk50];
    if (p->unk14->unk4 * 3 < p->unk14->unk6) {
        D_8007A910 = 0x19;
    } else {
        D_8007A910 = (battle_flags & 1) ? 0x11 : 0;
    }
    D_8007A9A0 = D_8007A9A4 = 0.0f;
    if (!(D_8004DCA0 & 0x87)) {
        if (battle_flags & 1) {
            if (!(battle_flags & 2) && !(p->actor.unk60 & 1)) {
                p->unk2 = Player_FindMeleeTarget(&D_8007AA20);
            }
        } else if (!(p->actor.unk60 & 1)) {
            D_8007A9C0 = Player_FindNpcToTalk(&D_8007AA08, &D_8007AA20);
            if (D_8007A9C0 == 0) {
                D_8007A9C4 = Spirit_FindInFront(&D_8007AA20);
                if (D_8007A9C4 == NULL) {
                    D_8007A9C8 = Chest_FindInFront(&D_8007AA20);
                    if (D_8007A9C8 == NULL) {
                        D_8007A9CC = TextSpot_FindInFront(&D_8007AA20);
                        if (D_8007A9CC == NULL) {
                            if ((D_8007A904 = Boss_CheckPlayerNear()) != 0) {
                                Boss_BeginEncounter(D_8007A904 - 1);
                                D_8007A908 = 0x1E;
                                D_8004DCA0 |= 2;
                                p->unk8 |= 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!(D_8004DCA0 & 0xF)) {
        if (input_pressed_buttons & 0xA000) {
            if ((battle_flags & 1) && !(p->actor.unk60 & 1)) {
                if (!(battle_flags & 6) && Magic_IsAnyEffectActive() == 0) {
                    if (p->unk2 != 0) {
                        Player_StartMeleeAttack(&D_8007AA08, &D_8007AA20, cd);
                    } else {
                        Player_AddTurnMoveAgilityXP(&D_8007AA08);
                        p->unk2 = 0;
                        Battle_EndTurn(&D_8007AA20);
                    }
                }
            } else if (!(p->actor.unk60 & 1)) {
                if (D_8007A9C0 != 0) {
                    D_8007A9C0--;
                    p->unk0 = 7;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.unk14 = 0.0f;
                    p->actor.unkC = 0.0f;
                    Anim_SetCurrentAndNext(&D_8007AA20, D_8007A910, 1, D_8007A910, 1, 1);
                    Npc_StartTalk(D_8007A9C0);
                    Text_OpenWindow(hud_npc_marker_screen_y < 70 ? 0 : 1);
                    D_8004DCA0 |= 2;
                } else if (D_8007A9C4 != NULL) {
                    s = p->unk14->unk24;
                    if (s[0] == 50 && s[1] == 50 && s[2] == 50 && s[3] == 50) {
                    } else {
                        D_8004DCA0 |= 8;
                        p->unk0 = 0;
                        Spirit_SetCollected(((Unk8007A9C4 *) D_8007A9C4)->unk14);
                        ((Unk8007A9C4 *) D_8007A9C4)->unk10 |= 1;
                        hud_element_input_timer = 8;
                        Sfx_Play(0, 1, 0xFF);
                    }
                } else if (Item_HasInventoryRoom() != 0 && D_8007A9C8 != NULL) {
                    Chest_Open(D_8007A9C8);
                    D_8007A918.x = 0.0f;
                    D_8007A918.z = p->actor.scale * 171.0f;
                    Math_RotateVec2(D_8007A9C8->rot, &D_8007A918);
                    p->actor.x = D_8007A9C8->x + D_8007A918.x;
                    p->actor.z = D_8007A9C8->z + D_8007A918.z;
                    p->actor.rot = D_8007A9C8->rot;
                    p->unk138 = D_8007A9C8->rot + 3.141592653589793;
                    p->unk11C = D_8007A9C8->unk50;
                    Player_StartOpenChest(&D_8007AA08, &D_8007AA20, (s32) cd);
                    D_8007A9C8 = NULL;
                } else if (D_8007A9CC != NULL) {
                    TextSpot_LoadMessage(D_8007A9CC);
                    p->unk0 = 0x11;
                    p->actor.unk60 |= 1;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.unk14 = 0.0f;
                    p->actor.unkC = 0.0f;
                    if (((Unk8007A9CC *) D_8007A9CC)->entry->unk18 & 2) {
                        p->unk4 = 0xF;
                        p->unk8 |= 0x200;
                        Anim_SetCurrentAndNext(&D_8007AA20, 0x1B, 1, D_8007A910, 1, 1);
                    } else {
                        p->unk4 = 0xF;
                        Anim_SetCurrentAndNext(&D_8007AA20, 0xC, 1, 0xD, 1, 1);
                    }
                    D_8007A9CC = NULL;
                } else {
                    p->unk0 = 3;
                    p->unk4 = 0xF;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.unk14 = 0.0f;
                    p->actor.unkC = 0.0f;
                    p->actor.unk60 |= 1;
                    Anim_SetCurrentAndNext(&D_8007AA20, 0x1B, 1, D_8007A910, 1, 1);
                }
            }
        } else if (Player_CanAct(&D_8007AA08, &D_8007AA20) != 0) {
            if (!(D_8004DCA0 & 4) && (input_pressed_buttons & 0x10)) {
                D_8004DCA0 ^= 1;
                Fade_Start(6, 2, fade_black_ramp);
                Sfx_Play(0, 1, 0xFF);
                p->actor.unk60 |= 1;
            }
            if (!(D_8004DCA0 & 1) && !(p->actor.unk68->unk0 & 0x40) && Player_HandleSpellInput(&D_8007AA08) != 0) {
                Player_StartCastSpell(&D_8007AA08, &D_8007AA20, (AnimEntry *) cd);
            }
        }
    } else if (D_8004DCA0 & 4) {
        if (Player_HandleSpellInput(&D_8007AA08) != 0) {
            Player_StartCastSpell(&D_8007AA08, &D_8007AA20, (AnimEntry *) cd);
        }
    } else if (D_8004DCA0 & 1) {
        if (input_pressed_buttons & 0x4010) {
            D_8004DCA0 ^= 1;
            Fade_Start(6, 4, fade_black_ramp_dim);
            Sfx_Play(0, 2, 0xFF);
            p->actor.unk60 &= ~1;
        }
    }
    if (battle_flags & 8) {
        battle_flags &= ~8;
        p->actor.unk64->unk10 += D_8007A9B4;
        p->actor.unk64->unk14 += D_8007A9B8;
        if (D_8007A9BC != 0xFF) {
            if ((u32) Item_CountInInventory(D_8007A9BC) >= 3 || (u32) Item_GetInventoryCount() >= 0x8D) {
                D_8007A9BC = 0xFF;
            }
        }
        Hud_ClearActorStatusIndicators(&D_8007AA20);
        D_8007AA8C.unk0 = 0;
        p->unk0 = 0xF;
        p->unk4 = cd->unkC2;
        p->actor.unk60 |= 1;
        p->actor.vz = 0.0f;
        p->actor.vx = 0.0f;
        p->actor.unk14 = 0.0f;
        p->actor.unkC = 0.0f;
        Anim_SetCurrentAndNext(&D_8007AA20, 0x10, 1, D_8007A910, 1, 1);
    } else if (battle_flags & 0x10) {
        Hud_ClearActorStatusIndicators(&D_8007AA20);
        D_8007AA8C.unk0 = 0;
    }
    D_8004DCB0[p->unk0](&D_8007AA20, &D_8007AA08, cd);
    D_8007A9A8 = sqrtf(D_8007A9A0 * D_8007A9A0 + D_8007A9A4 * D_8007A9A4);
    if (!(battle_flags & 1) && p->actor.unk64->unk8 < p->actor.unk64->unkA) {
        D_8007A8F0 += D_8007A9A8;
        if (D_8007A8F0 > 60.0) {
            D_8007A8F0 -= 60.0;
            p->actor.unk64->unk8++;
        }
    }
}



extern Gfx *D_8007A184;
extern s32 D_8007AB60;
extern u8 D_10000A0[];

extern Unk8007A928 D_8007A928;
extern f32 D_8007A92C;
extern Vec3f D_8007AB48;
extern Vec3f anim_node_world_positions;
void Coll_ResolveFloorAndWalls(f32 x, f32 y, f32 z, u16 flags, void *out);
void Env_ApplyLightSlot(s32 arg0);
void Shadow_Queue(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale);
void Anim_DrawModel(s32 arg0, Actor *arg1, AnimEntry *arg2, void *arg3);
void Anim_AdvanceFrame(u16 arg0, Actor *arg1, AnimEntry *arg2);

/* fields of D_8007AA08.actor under their own names */
extern f32 D_8007AA24;
extern f32 D_8007AA44;
extern f32 D_8007AA48;
extern f32 D_8007AA4C;
extern f32 D_8007AA50;
extern f32 D_8007AA54;
extern s16 D_8007AA70;
extern s16 D_8007AA72;
extern u16 D_8007AA78;

void Player_Draw(void *arg0) {
    s32 flag;
    s32 pad[2];
    AnimEntry *anims;
    PlayerState *p = &D_8007AA08;

    gSPDisplayList(D_8007A184++, D_10000A0);
    Env_ApplyLightSlot(D_8007AB60);
    if (D_8007AA08.unk0 == 0xA || p->unk0 == 0xB) {
        flag = 1;
    } else {
        flag = 0;
    }
    anims = (AnimEntry *)player_char_data[D_8007AA70];
    Player_LoadAnim(&D_8007AA20);
    Anim_DrawModel(flag, &D_8007AA20, &anims[D_8007AA72], arg0);
    Anim_AdvanceFrame(D_8007AA78, &D_8007AA20, &anims[D_8007AA72]);
    Player_LoadAnim(&D_8007AA20);
    Coll_ResolveFloorAndWalls(anim_node_world_positions.x, D_8007AA24, anim_node_world_positions.z, 0xA00, &D_8007A928);
    D_8007AB48.x = anim_node_world_positions.x;
    D_8007AB48.y = D_8007A92C;
    D_8007AB48.z = anim_node_world_positions.z;
    Shadow_Queue(D_8007AB48.x, D_8007AB48.y, D_8007AB48.z, p->actor.unk2C, p->actor.unk30, p->actor.unk34,
                  p->actor.unk28 * p->actor.scale);
}

extern s32 D_8007A9B4;
extern s32 D_8007A9B8;
extern s32 D_8007AA10; /* .unk8 */
extern s32 D_8007AA18; /* .unk10 */
extern PlayerStateSub14 *D_8007AA1C; /* .unk14 */
extern f32 D_8007AA30; /* .actor.rot */
extern u16 D_8007AA80; /* .actor.unk60 */
extern f32 D_8007AB3C;

void Player_InitBattle(void) {
    PlayerState *p = &D_8007AA08;
    ActorStats *stats;
    CharData *cd;
    s32 quarter;
    s32 i;

    D_8007A9B4 = D_8007A9B8 = 0;
    stats = D_8007AA08.actor.unk64;
    cd = player_char_data[D_8007AA08.actor.unk50];
    D_8007AA08.unkC = (f32)(u32)stats->unkC * 0.2857 + 17.0;
    D_8007AA08.unk84 = 0;
    D_8007AA08.unk110 = 0;
    D_8007AA08.unk108 = D_8007AA08.unk14->unk24[0] + D_8007AA08.unk14->unk24[1] + D_8007AA08.unk14->unk24[2] +
                        D_8007AA08.unk14->unk24[3];
    D_8007AA08.unk10E = 0x10;
    D_8007AA08.unk10A = stats->unkC;
    D_8007AA08.unk10C = stats->unkE;
    D_8007AA08.unk10 = D_8007AA08.unk108;
    D_8007AA08.unk114 = 1.0f;
    quarter = D_8007AA08.unk108 >> 2;
    for (i = 0; i < 4; i++) {
        if (quarter < p->unk14->unk24[i]) {
            p->unk10 = p->unk10 - p->unk14->unk24[i] + quarter;
        }
    }
    p->unk10 = p->unk10 / 10 + 1;
    if (p->unk10 > 16) {
        p->unk10 = 16;
    }
    p->unk0 = 3;
    p->unk4 = cd->unkDA;
    p->unk2 = 0;
    p->unk134 = p->actor.rot;
    p->unk8 &= ~0x20;
    p->actor.unk60 |= 1;
    if (D_8007A910 != 0x19) {
        D_8007A910 = 0x11;
    }
    Anim_SetCurrentAndNext(&p->actor, 0x12, 1, D_8007A910, 1, 1);
}

/* particle/effect spawn parameters */
typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[0x30 - 0x24];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Unk8004EE20;

extern Unk8004EE20 effect_foot_particle_template;
extern s32 D_8007A908;
extern f32 D_80085E70;
extern s32 D_8008C168;
extern s32 D_8008C16C;
extern s8 input_stick_x;
extern s8 input_stick_y;
void Effect_AllocateSprite(Unk8004EE20 *arg0);
void Battle_StartBossEncounter(void);

void Player_StateMove(Actor *a, PlayerState *p, CharData *cd) {
    f32 x;
    f32 z;

    x = -(f32)input_stick_x;
    z = -(f32)input_stick_y;
    if (x > -8.0f && x < 8.0f) {
        x = 0.0f;
    }
    if (z > -8.0f && z < 8.0f) {
        z = 0.0f;
    }
    if (x != 0.0f || z != 0.0f) {
        D_8007A918.x = x;
        D_8007A918.z = z;
        Math_RotateVec2(D_80085E70, &D_8007A918);
        x = D_8007A918.x;
        z = D_8007A918.z;
    }
    Player_UpdateStatGrowth(p, a);
    if (D_8008C168 != 0) {
        x = z = 0.0f;
    } else if (D_8008C16C != 0) {
        x = z = 0.0f;
    } else if (D_8004DCA0 & 0x300F) {
        x = z = 0.0f;
    } else if (p->unk84 & 8) {
        x = z = 0.0f;
    }
    if ((battle_flags & 1) && (battle_flags & 0x202)) {
        z = 0.0f;
        x = 0.0f;
    } else if (battle_turn_delay != 0) {
        z = 0.0f;
        x = 0.0f;
    }
    if (p->unk8 & 1) {
        if (D_8007A908 != 0) {
            if (--D_8007A908 == 0) {
                Text_OpenWindow(0);
            }
        } else if (text_active_window_count == 0) {
            p->unk8 &= ~1;
            D_8004DCA0 &= ~2;
            Battle_StartBossEncounter();
        }
    } else if (p->unk8 & 2) {
        if (text_active_window_count == 0) {
            p->unk8 &= ~2;
            D_8004DCA0 &= ~2;
        }
    } else if (p->unk8 & 0x10) {
        if (text_active_window_count == 0) {
            p->unk8 &= ~0x10;
            D_8004DCA0 &= ~2;
        }
    }
    switch (p->unk0) {
        case 2:
            Player_MoveRun(x, z, a, p);
            break;
        case 1:
            Player_MoveWalk(x, z, a, p);
            break;
        default:
            Player_MoveIdle(x, z, a, p);
            break;
    }
    Player_MoveAndCollide(0xA01, a, p);
    if (p->unk0 == 2) {
        D_8007A90C += a->unk58;
        if (D_8007A90C >= 0x97) {
            D_8007A90C = 0;
            Sfx_Play(0, 0x21, 0xFF);
        }
        if (p->unk4 != 0) {
            if (!(p->unk4 & 3)) {
                effect_foot_particle_template.unk18 = a->x;
                effect_foot_particle_template.unk1C = a->y + 1.0f;
                effect_foot_particle_template.unk20 = a->z;
                effect_foot_particle_template.unk30 = 0.0f;
                effect_foot_particle_template.unk34 = 0.2f;
                effect_foot_particle_template.unk38 = 0.0f;
                Effect_AllocateSprite(&effect_foot_particle_template);
            }
            p->unk4--;
        }
    }
    Player_ApplyFloorEffect(p, a);
}

void Player_StateWait(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFC;
    }
}

void Player_StateBrake(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    Player_MoveAndCollide(0xA01, arg0, arg1);
    arg0->vx *= 0.68;
    arg0->vz *= 0.68;
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->unk60 &= 0xFFFE;
    }
}

void Player_StateHurt(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->unk4 == 0) {
        PlayerStateSub14 *sub = arg1->unk14;

        arg0->vx = 0.0f;
        arg0->vz = 0.0f;
        if (sub->unk4 == 0) {
            arg1->unk0 = 6;
            arg1->unk4 = 0xE6;
            Anim_SetCurrentAndNext(arg0, 9, 1, D_8007A910, 1, 1);
            Hud_ClearActorStatusIndicators(arg0);
            Bgm_Play(0x1E);
            D_8004DCA0 |= 0x880;
            D_8007A174 = arg1->unk4;
            D_8007A178 = 2;
            D_8007A17A = 0x5A;
            arg1->unk124 = 0xC8;
            D_80084300.unk0 = D_8007A9AC;
            D_80084300.unk4 = D_8007A9AE;
            D_80084300.unk8 = D_8007A9B0;
            D_8007A98C = 0.0f;
            D_8007A990 = 0.0f;
            D_8007A994 = 0.0f;
            D_8007A998 = 0x108;
            D_8007AA0E = 0;
            hud_panel_transition_state = 1;
            hud_panel_transition_frame = 0xC;
        } else {
            arg1->unk0 = 0;
            arg0->unk60 &= 0xFFFC;
        }
    }
}

void Player_StateDying(Actor *arg0, PlayerState *arg1, s32 arg2) {
    Player_GetAnimMotion(arg0, arg2, &D_8007A918);
    arg0->vx = D_8007A918.x;
    arg0->vz = D_8007A918.z;
    Player_MoveAndCollide(0xA01, arg0, arg1);
    if (--arg1->unk4 == arg1->unk124) {
        D_80085E48.unk4C = 250.0f;
        D_80085E48.unk58 = 150.0f;
        D_80085E48.unk70 = 0.01f;
    }
}

void Player_StateTalk(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (text_active_window_count == 0) {
        Npc_EndTalk(D_8007A9C0);
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        D_8004DCA0 &= ~2;
        if (D_8004DCA0 & 0x10) {
            D_8004DCA0 &= ~0x10;
            if (*(u16 *)((u8 *)D_8007AC70[D_8007A9C0].unk0 + 2) == 6 && text_last_choice_index == 0) {
                D_8004DCA0 |= 0x480;
                D_8007A174 = 0x23;
                D_8007A17A = 0x1E;
                D_8007A9AC = D_800842BC;
                D_8007A9AE = D_800842C0;
                arg1->unk0 = 3;
                arg1->unk4 = 0x41;
                arg0->unk60 |= 1;
                Audio_StartSeqFadeOut(0x3C);
            }
        } else if (arg1->unk8 & 0x40) {
            arg1->unk8 &= ~0x40;
            Sfx_Play(0, 0x3B, 0xFF);
        }
        D_8007A9C0 = 0;
    }
}

void Player_StateAutoWalk(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    Player_MoveWalk(arg1->unk12C, arg1->unk130, arg0, arg1);
    Player_MoveAndCollide(0xA01, arg0, arg1);
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->unk60 &= 0xFFFE;
    }
}

extern s32 D_80085E4C;
void Enemy_PlayMissEffect(Actor *arg0);
void Effect_AddFloatingNumber(Actor *arg0, s32 arg1, s32 arg2);
void Effect_SpawnStreakBurst(f32 x, f32 y, f32 z);
void Hud_StartActorStatusIndicator(Actor *arg0, u16 arg1, u16 arg2, s16 arg3);

u16 Enemy_TakeDamage(s32 target, u16 dmg, u16 elem, u16 flags, Actor *arg4);
void Player_StateMeleeAttack(Actor *a, PlayerState *p, CharData *cd) {
    u16 dmg;
    s32 flags;
    s32 t;

    a->vz = 0.0f;
    a->vx = 0.0f;
    if (--p->unk4 == 0) {
        if (Player_RollHitOnEnemy(p->unk2 - 1, a) != 0) {
            dmg = Player_CalcMeleeDamage(p);
            if (p->unk0 == 0x10) {
                dmg *= 0.5;
            }
            flags = 0x8004;
            if (p->unk8 & 0x400) {
                flags = 0xC004;
                p->unk8 &= ~0x400;
            }
            dmg = Enemy_TakeDamage(p->unk2 - 1, dmg, (p->unk122 >> 8) & 0xF, flags, a);
            if (dmg != 0) {
                a->unk64->unk8++;
                if (a->unk64->unkA < a->unk64->unk8) {
                    a->unk64->unk8 = a->unk64->unkA;
                }
                if (p->unk84 & 2) {
                    t = ((dmg + 3) >> 2) + 1;
                    dmg = t;
                    a->unk64->unk4 += dmg;
                    if (a->unk64->unk6 < a->unk64->unk4) {
                        a->unk64->unk4 = a->unk64->unk6;
                    }
                    Effect_AddFloatingNumber(a, 1, dmg);
                    Hud_StartActorStatusIndicator(a, 2, 1, 0x1E);
                }
                D_8007A918.x = 0.0f;
                D_8007A918.z = 2.0f * (a->unk64->unk18 * a->scale);
                Math_RotateVec2(a->rot, &D_8007A918);
                Effect_SpawnStreakBurst(a->x + D_8007A918.x, a->y + a->unk64->unk1C * a->scale * 0.7f, a->z + D_8007A918.z);
            }
            p->unk14->unk28++;
        } else {
            Enemy_PlayMissEffect(&D_8007B908[p->unk2 - 1].actor);
        }
        if (D_8007B908[p->unk2 - 1].unkA == 0) {
            p->unk8 &= ~0x100;
        }
        if (p->unk0 == 0xD && (p->unk8 & 0x100)) {
            p->unk0 = 0x10;
            p->unk4 = 0x12;
            p->unk8 &= ~0x100;
            a->unk60 |= 1;
            Anim_SetCurrentAndNext(a, 0xB, 1, D_8007A910, 1, 1);
            D_80085E4C = 0x23;
            return;
        }
        p->unk0 = 3;
        if (p->unk0 == 0xD) {
            p->unk4 = cd->unk7A - 0x14;
        } else {
            p->unk4 = cd->unk86 - 0x16;
        }
        p->unk2 = 0;
        p->unk8 &= ~0x100;
        Player_AddTurnMoveAgilityXP(p);
        p->unk2 = 0;
        Battle_EndTurn(a);
    } else if (p->unk0 == 0xD && p->unk10 >= p->unk4 && (input_pressed_buttons & 0xA000)) {
        p->unk8 |= 0x100;
    }
}

void Player_StateCastSpell(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->unk124 != 0) {
        if (--arg1->unk124 == 0) {
            Magic_CreateCastEffect(arg0, arg1->unk122, 0, (arg1->unk8 & 0x10000) ? 0x10 : 0);
        }
    } else if (--arg1->unk4 == 0) {
        if (Magic_IsAnyEffectActive() != 0) {
            arg1->unk4 = 8;
            return;
        }
        arg0->unk60 &= 0xFFFE;
        if (arg1->unk8 & 4) {
            arg1->unk0 = 3;
            arg1->unk4 = arg2->unk122;
            arg1->unk8 &= ~4;
            Anim_SetCurrentAndNext(arg0, 0x18, 1, D_8007A910, 1, 1);
        } else {
            arg1->unk0 = 0;
        }
        Player_AddTurnMoveAgilityXP(arg1);
        arg1->unk2 = 0;
        Battle_EndTurn(arg0);
    }
}

void Player_StateWalkToExitObject(Actor *arg0, PlayerState *arg1, s32 arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    rot = arg0->rot;
    arg0->x += arg1->unk12C;
    arg0->z += arg1->unk130;
    d = arg1->unk134 - rot;
    if (d > 3.141592653589793) {
        d -= 6.283185307179586;
    } else if (d < -3.141592653589793) {
        d += 6.283185307179586;
    }
    arg0->rot = rot + d * 0.3;
    rot = arg0->rot;
    if (arg0->rot > 3.141592653589793) {
        arg0->rot -= 6.283185307179586;
    } else if (arg0->rot < -3.141592653589793) {
        arg0->rot += 6.283185307179586;
    }
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0xA;
        arg1->unk4 = 0x50;
        Anim_SetCurrentAndNext(arg0, arg1->unk6, 1, D_8007A910, 1, 1);
        Player_LoadAnim(arg0);
        Anim_UpdateRootMotion(arg0, arg0->unk52 * 0xC + arg2, arg0->scale);
        arg0->rot = arg1->unk138;
        Sfx_Play(0x1A, 8, 0xFF);
    }
}

void Player_StateAnimMove(Actor *arg0, PlayerState *arg1, s32 arg2) {
    Player_GetAnimMotion(arg0, arg2, &D_8007A918);
    arg0->vx = D_8007A918.x;
    arg0->vz = D_8007A918.z;
    Player_MoveAndCollide(0xA00, arg0, arg1);
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        arg0->rot = arg1->unk138;
    }
}

void Player_StateOpenChest(Actor *arg0, PlayerState *arg1, s32 arg2) {
    if (arg1->unk4 != 0) {
        Player_GetAnimMotion(arg0, arg2, &D_8007A918);
        arg0->vx = D_8007A918.x;
        arg0->vz = D_8007A918.z;
        Player_MoveAndCollide(0xA00, arg0, arg1);
        if (arg1->unk4 == 0x20) {
            Item_BuildMessage(arg1->unk11C);
            Text_OpenWindow(1);
            Item_AddToInventory(arg1->unk11C);
            D_8004DCA0 |= 2;
            Sfx_Play(0, 0x3B, 0xFF);
        }
        if (--arg1->unk4 == 0) {
            arg0->rot = arg1->unk138;
            Anim_SetCurrentAndNext(arg0, D_8007A910, 1, D_8007A910, 1, 1);
        }
    } else if (text_active_window_count == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        D_8004DCA0 &= ~2;
        D_8007A9C0 = 0;
    }
}

void Player_StateUseItem(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    if (--arg1->unk4 == 0) {
        Item_ApplyEffect(arg1->unk11C, arg0);
        if (D_803AAAA2[arg1->unk11C].unk0 == 2) {
            Player_AddTurnMoveAgilityXP(arg1);
            arg1->unk2 = 0;
            Battle_EndTurn(arg0);
        } else {
            arg1->unk124 = 0xF;
            Player_AddTurnMoveAgilityXP(arg1);
        }
    } else if (--arg1->unk124 == 0) {
        if (Magic_IsAnyEffectActive() != 0) {
            arg1->unk124 = 8;
            return;
        }
        arg1->unk0 = 3;
        arg1->unk4 = 0xF;
        Anim_SetCurrentAndNext(arg0, 0x18, 1, D_8007A910, 1, 1);
        arg1->unk2 = 0;
        Battle_EndTurn(arg0);
    }
}


extern u16 D_8007A172;
void Bgm_PlayForMap(s32 arg0, s32 arg1, s32 arg2);

void Player_StateBattleWon(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->unk4 < 0x26) {
        rot = arg0->rot;
        d = arg1->unk134 - rot;
        if (d < -3.141592653589793) {
            d += 6.283185307179586;
        } else if (d > 3.141592653589793) {
            d -= 6.283185307179586;
        }
        arg0->rot = rot + d * 0.2;
        rot = arg0->rot;
        if (arg0->rot < -3.141592653589793) {
            arg0->rot += 6.283185307179586;
        } else if (arg0->rot > 3.141592653589793) {
            arg0->rot -= 6.283185307179586;
        }
    }
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFD;
        if (D_8007A172 != 4) {
            Bgm_PlayForMap(D_800842BC, D_800842C0, 0x1E);
        }
    }
}


void Player_StateExamine(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    f32 rot;
    f32 d;

    rot = arg0->rot;
    d = arg1->unk134 - rot;
    if (d < -3.141592653589793) {
        d += 6.283185307179586;
    } else if (d > 3.141592653589793) {
        d -= 6.283185307179586;
    }
    arg0->rot = rot + d * 0.2;
    rot = arg0->rot;
    if (arg0->rot < -3.141592653589793) {
        arg0->rot += 6.283185307179586;
    } else if (arg0->rot > 3.141592653589793) {
        arg0->rot -= 6.283185307179586;
    }
    if (arg1->unk4 != 0) {
        if (--arg1->unk4 == 0) {
            Text_OpenWindow(1);
            D_8004DCA0 |= 2;
        }
    } else if (text_active_window_count == 0) {
        arg1->unk0 = 3;
        if (arg1->unk8 & 0x200) {
            arg1->unk4 = 2;
        } else {
            arg1->unk4 = 8;
            Anim_SetCurrentAndNext(arg0, 0xE, 1, D_8007A910, 1, 1);
        }
        arg1->unk8 &= ~0x200;
        D_8004DCA0 &= ~2;
        D_8007A9C0 = 0;
    }
}

extern u16 D_8007A90C;

void Player_MoveIdle(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3) {
    f32 speed;

    arg2->vz = 0.0f;
    arg2->vx = 0.0f;
    if (arg0 != 0.0f || arg1 != 0.0f) {
        speed = sqrtf(arg0 * arg0 + arg1 * arg1) * 0.025;
        if (speed > 2.0) {
            speed = 2.0f;
        }
        if (speed > 1.5) {
            arg3->unk0 = 2;
            arg3->unk4 = 0x1E;
            D_8007A90C = 0;
        } else {
            arg3->unk0 = 1;
        }
    } else if (D_8007A910 != arg2->unk52 && D_8007A910 != arg2->unk5A) {
        Anim_SetCurrentAndNext(arg2, D_8007A910, 1, D_8007A910, 1, 1);
    }
}

extern u16 D_8007A90C;

void Player_MoveWalk(f32 sx, f32 sz, Actor *a, PlayerState *p) {
    s32 anim;
    s32 next;
    s32 speed;
    s32 mode;
    s32 flag;
    f32 d;
    f32 unused;
    f32 spd;
    f32 cur;

    cur = sqrtf(a->vx * a->vx + a->vz * a->vz);
    mode = 0;
    if (sx != 0.0f || sz != 0.0f) {
        spd = sqrtf(sx * sx + sz * sz) * 0.025;
        if (spd > 2.0) {
            sx = sx * 2.0 / spd;
            sz = sz * 2.0 / spd;
            spd = 2.0f;
        }
        d = Math_Atan2(sx, sz) - a->rot;
        if (d > 3.141592653589793) {
            d -= 6.283185307179586;
        } else if (d < -3.141592653589793) {
            d += 6.283185307179586;
        }
        if (d > 0.7853981633974483) {
            d = 0.7853982f;
        } else if (d < -0.7853981633974483) {
            d = -0.7853982f;
        }
        spd *= 1.0 - ((d >= 0.0f) ? d : -d) / 0.7853981633974483;
        a->rot = a->rot + d * 0.5;
        if (a->rot > 3.141592653589793) {
            a->rot -= 6.283185307179586;
        } else if (a->rot < -3.141592653589793) {
            a->rot += 6.283185307179586;
        }
        D_8007A918.x = 0.0f;
        D_8007A918.z = cur + (spd - cur) * 0.85;
        Math_RotateVec2(a->rot, &D_8007A918);
        a->vx = D_8007A918.x;
        a->vz = D_8007A918.z;
        anim = 1;
        next = 1;
        flag = 0;
        speed = spd * 14.0f + 3.0f;
        if (spd > 1.5 || (f32)(cur + (spd - cur) * 0.85) > 1.5) {
            p->unk0 = 2;
            p->unk4 = 0x1E;
            D_8007A90C = 0;
        }
    } else {
        a->vx *= 0.82;
        a->vz *= 0.82;
        if (cur > 1.0) {
            anim = 0xF;
            next = D_8007A910;
            mode = 3;
            p->unk0 = 4;
            p->unk4 = 8;
            a->unkC = 0.0f;
            a->unk14 = 0.0f;
            a->vx *= 0.9;
            a->vz *= 0.9;
            speed = 1;
            flag = 1;
            Effect_StartFootEmitter(a);
        } else {
            anim = 1;
            next = 1;
            flag = 0;
            speed = cur * 14.0f + 3.0f;
            if (cur < 0.1) {
                p->unk0 = 0;
                a->vx = 0.0f;
                a->vz = 0.0f;
            }
        }
    }
    if (anim != a->unk52 && anim != a->unk5A) {
        Anim_SetCurrentAndNext(a, anim, speed, next, speed, flag);
        a->unk54 = mode;
    } else {
        a->unk58 = speed;
    }
}


void Player_MoveRun(f32 sx, f32 sz, Actor *a, PlayerState *p) {
    s32 anim;
    s32 next;
    s32 speed;
    s32 mode;
    s32 flag;
    f32 d;
    f32 pad;
    f32 spd;
    f32 cur;
    f32 newspd;

    cur = sqrtf(a->vx * a->vx + a->vz * a->vz);
    if (sx != 0.0f || sz != 0.0f) {
        spd = sqrtf(sx * sx + sz * sz) * 0.025;
        if (spd > 2.0) {
            sx = sx * 2.0 / spd;
            sz = sz * 2.0 / spd;
            spd = 2.0f;
        }
        d = Math_Atan2(sx, sz) - a->rot;
        if (d > 3.141592653589793) {
            d -= 6.283185307179586;
        } else if (d < -3.141592653589793) {
            d += 6.283185307179586;
        }
        a->rot = a->rot + d * 0.4;
        if (a->rot > 3.141592653589793) {
            a->rot -= 6.283185307179586;
        } else if (a->rot < -3.141592653589793) {
            a->rot += 6.283185307179586;
        }
        D_8007A918.x = 0.0f;
        D_8007A918.z = newspd = cur + (spd - cur) * 0.2;
        Math_RotateVec2(a->rot, &D_8007A918);
        a->vx = D_8007A918.x;
        a->vz = D_8007A918.z;
        anim = 2;
        next = 2;
        mode = 0;
        speed = spd * 14.0f + 3.0f;
        flag = 0;
        if (newspd < 1.0 && spd < 1.0) {
            p->unk0 = 1;
        }
    } else {
        anim = 0xF;
        next = D_8007A910;
        mode = 3;
        p->unk0 = 4;
        p->unk4 = 8;
        a->unkC = 0.0f;
        a->unk14 = 0.0f;
        a->vx *= 0.9;
        a->vz *= 0.9;
        speed = 1;
        flag = 1;
        Effect_StartFootEmitter(a);
    }
    if (anim != a->unk52 && anim != a->unk5A) {
        Anim_SetCurrentAndNext(a, anim, speed, next, speed, flag);
        a->unk54 = mode;
    } else {
        a->unk58 = speed;
    }
}

void Player_GetAnimMotion(Actor *arg0, s32 arg1, Vec2f *arg2) {
    Player_LoadAnim(arg0);
    Anim_UpdateRootMotion(arg0, arg0->unk52 * 0xC + arg1, arg0->scale);
    arg2->x = -arg0->unk44;
    arg2->z = arg0->unk4C;
    Math_RotateVec2(arg0->rot, arg2);
}

void func_80006A50(void) {
}

extern f32 D_8007A9A0;
extern f32 D_8007A9A4;
extern f32 battle_center_x;
extern f32 battle_center_z;
extern f32 battle_arena_radius;
void Player_PushOutOfObjects(f32 *vx, f32 *vz, Actor *arg2);

void Player_MoveAndCollide(u16 arg0, Actor *arg1, PlayerState *arg2) {
    f32 dx;
    f32 dz;
    f32 max;
    f32 dist;

    if ((battle_flags & 1) && !(battle_flags & 6)) {
        dx = arg1->x + arg1->vx - battle_active_enemy_x;
        dz = arg1->z + arg1->vz - battle_active_enemy_z;
        dist = sqrtf(dx * dx + dz * dz);
        max = arg2->unkC * arg2->unk114;
        if (max < dist) {
            arg1->vx = max * dx / dist - arg1->x + battle_active_enemy_x;
            arg1->vz = max * dz / dist - arg1->z + battle_active_enemy_z;
        }
        dx = arg1->x + arg1->vx - battle_center_x;
        dz = arg1->z + arg1->vz - battle_center_z;
        dist = sqrtf(dx * dx + dz * dz);
        if (battle_flags & 0x100) {
            if (battle_arena_radius < dist) {
                arg1->vx = battle_arena_radius * dx / dist - arg1->x + battle_center_x;
                arg1->vz = battle_arena_radius * dz / dist - arg1->z + battle_center_z;
            }
        } else if (battle_arena_radius < dist) {
            arg2->unk8 |= 0x20;
        } else {
            arg2->unk8 &= ~0x20;
        }
    }
    Player_PushOutOfObjects(&arg1->vx, &arg1->vz, arg1);
    D_8007A9A0 = arg1->vx;
    D_8007A9A4 = arg1->vz;
    dx = arg1->x + arg1->vx;
    dz = arg1->z + arg1->vz;
    D_8007A928.unk0 = arg1->unk64->unk18 * arg1->unk64->unk20;
    Coll_ResolveFloorAndWalls(dx, arg1->y, dz, arg0, &D_8007A928);
    arg1->vx = D_8007A928.unk0 - arg1->x;
    arg1->vz = D_8007A928.unk8 - arg1->z;
    arg1->x = D_8007A928.unk0;
    arg1->y = D_8007A928.unk4;
    arg1->z = D_8007A928.unk8;
    arg1->unk2C = D_8007A928.unkC;
    arg1->unk30 = D_8007A928.unk10;
    arg1->unk34 = D_8007A928.unk14;
    arg1->unk62 = D_8007A928.unk18;
}

/* D_8007ABF0: objects of 0x84 bytes with an Actor at +0x14 */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ Actor actor;
    /* 0x80 */ u8 unk80[0x84 - 0x80];
} Unk8007ABF0;

extern s32 D_8007ABA8;
extern Actor *D_8007ABB0[];
extern Unk8007ABF0 D_8007ABF0[];

s32 Player_FindNpcToTalk(PlayerState *arg0, Actor *arg1) {
    s32 ret;
    s32 n;
    Actor **list;
    Actor *a;
    Unk8007ABF0 *it;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 r;

    ret = 0;
    if (!(D_8004DCA0 & 0x448D) && !(arg0->unk8 & 0x10)) {
        list = D_8007ABB0;
        for (n = D_8007ABA8; n != 0 && ret == 0; n--) {
            a = *list++;
            dx = a->x - arg1->x;
            dy = a->y - arg1->y;
            dz = a->z - arg1->z;
            if (dy > -15.0 && dy < 15.0) {
                if (a->unk60 & 0x1000) {
                    r = 625.0f;
                } else {
                    r = 225.0f;
                }
                if (dx * dx + dz * dz < r) {
                    D_8007A918.x = dx;
                    D_8007A918.z = dz;
                    Math_RotateVec2(arg1->rot, &D_8007A918);
                    if (D_8007A918.z >= 0.0f && D_8007A918.x > -6.0 && D_8007A918.x < 6.0) {
                        ret++;
                        for (it = D_8007ABF0; &it->actor != a; it++) {
                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 radius;
} Unk8007C2A8;

extern s32 D_8007C02C;
extern Actor *D_8007C030[];
extern s32 D_8007C2A4;
extern Unk8007C2A8 *D_8007C2A8[];

void Player_PushOutOfObjects(f32 *arg0, f32 *arg1, Actor *arg2) {
    f32 size;
    f32 x;
    f32 z;
    s32 hit;
    s32 n;
    Actor **list;
    Actor *a;
    Unk8007C2A8 **list2;
    Unk8007C2A8 *o;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;
    f32 k;

    hit = 0;
    size = arg2->unk28 * arg2->scale;
    x = *arg0 + arg2->x;
    z = *arg1 + arg2->z;
    n = D_8007C02C;
    if (n != 0) {
        for (list = D_8007C030; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->unk28 * a->scale + size;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = a->x + dx - arg2->x;
                    *arg1 = a->z + dz - arg2->z;
                }
            }
        }
    }
    n = D_8007ABA8;
    if (n != 0) {
        for (list = D_8007ABB0; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->unk28 * a->scale + size;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = a->x + dx - arg2->x;
                    *arg1 = a->z + dz - arg2->z;
                }
            }
        }
    }
    n = D_8007C2A4;
    if (n != 0) {
        for (list2 = D_8007C2A8; !hit && n != 0; n--) {
            o = *list2++;
            dx = x - o->x;
            dz = z - o->z;
            r = size + 2.0 * o->radius;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = o->x + dx - arg2->x;
                    *arg1 = o->z + dz - arg2->z;
                }
            }
        }
    }
}

void Player_ApplyFloorEffect(PlayerState *arg0, Actor *arg1) {
    f32 dx;
    f32 dz;
    f32 k = 2.0f;

    switch ((u16)(arg1->unk62 >> 6) & 7) {
        case 0:
            break;
        case 1:
            if (arg0->unk128 == 0) {
                Player_TakeDamage(1, 4, arg1);
            }
            arg0->unk128--;
            break;
        case 2:
            dx = arg1->unk2C * k;
            arg1->x += dx;
            dz = arg1->unk34 * k;
            arg1->z += dz;
            arg1->vx += dx;
            arg1->vz += dz;
            break;
    }
}


extern f32 D_8007AA2C; /* .actor.unkC */
extern f32 D_8007AA34; /* .actor.unk14 */
extern f32 D_8007AB34;
extern f32 D_8007AB38;
extern Unk8007C290 *D_8007C290;
void Player_StartObjectExit(PlayerState *arg0, Actor *arg1);
void MapObjAnim_Start(s32 arg0, s32 arg1, s32 arg2, Unk8007C290 *arg3);

void Player_StartAreaExit(void) {
    PlayerState *p = &D_8007AA08;
    s32 kind = (D_80084300.unkC >> 8) & 0xF;
    f32 r;
    Unk8007C290 *pos;

    D_8007A998 = D_80084300.unkC;
    if (D_80084300.unkC & 4) {
        p->unk0 = 3;
        p->unk4 = 0x1E;
        p->unk6 = 0;
        p->actor.unk60 |= 1;
        Anim_SetCurrentAndNext(&p->actor, D_8007A910, 1, D_8007A910, 1, 1);
        D_8007A174 = 0x13;
        return;
    }
    switch (kind) {
        case 1:
            p->unk0 = 8;
            p->unk4 = 0x1E;
            p->unk6 = 0;
            r = D_80084300.unk14;
            p->actor.unk14 = 0.0f;
            p->actor.unkC = 0.0f;
            D_8007A918.x = 0.0f;
            D_8007A918.z = 40.0f;
            p->actor.rot = r;
            Math_RotateVec2(r, &D_8007A918);
            p->unk12C = D_8007A918.x;
            p->unk130 = D_8007A918.z;
            p->actor.unk60 |= 1;
            Sfx_Play(5, 0x21, 0xFF);
            Sfx_Play(0xF, 0x21, 0xFF);
            D_8007A174 = 0x13;
            break;
        case 2:
        case 3:
            Player_StartObjectExit(p, &p->actor);
            if (D_80084300.unkC & 1) {
                D_8007A174 = 0x32;
            } else {
                D_8007A174 = 0x32;
            }
            p->actor.unk60 |= 1;
            break;
        case 4:
            pos = &D_8007C290[D_80084300.unk10];
            MapObjAnim_Start(1, 0, D_80084300.unkC, pos);
            p->unk0 = 3;
            p->unk4 = 0x1E;
            p->unk6 = 0;
            p->actor.unk60 |= 1;
            Anim_SetCurrentAndNext(&p->actor, D_8007A910, 1, D_8007A910, 1, 1);
            D_8007A174 = 0x19;
            break;
    }
}

void Player_StartObjectExit(PlayerState *arg0, Actor *arg1) {
    s32 pad[2];
    f32 rot;
    u16 hi;
    Unk8007C290 *pos;
    s16 n;

    pos = &D_8007C290[D_80084300.unk10];
    MapObjAnim_Start(0, 0, D_80084300.unkC, pos);
    hi = D_80084300.unkC >> 8;
    if ((hi & 0xF) == 3) {
        arg0->unk6 = 0;
        Anim_SetCurrentAndNext(arg1, 0x1A, 1, 1, 0xA, 1);
        arg0->unk0 = 3;
        arg0->unk4 = 0x4B;
        arg1->unkC = 0.0f;
        arg1->unk14 = 0.0f;
        arg1->vx = 0.0f;
        arg1->vz = 0.0f;
        Sfx_Play(0x1E, 9, 0xFF);
    } else {
        arg0->unk0 = 9;
        arg0->unk4 = 8;
        Anim_SetCurrentAndNext(arg1, 1, 0xA, 1, 0xA, 1);
        if (D_80084300.unkC & 1) {
            n = 0x15;
            D_8007A918.x = -133.0f;
            D_8007A918.z = -92.0f;
            D_8007A918.unk8 = 4.0f;
        } else {
            n = 0x14;
            D_8007A918.x = -119.0f;
            D_8007A918.z = 125.0f;
            D_8007A918.unk8 = 162.0f;
        }
        arg0->unk6 = n;
        rot = pos->rot * 0.017453292519943295;
        Math_RotateVec2(-rot, &D_8007A918);
        arg0->unk12C = (pos->x - D_8007A918.x * arg1->scale - arg1->x) / arg0->unk4;
        arg0->unk130 = (pos->z + D_8007A918.z * arg1->scale - arg1->z) / arg0->unk4;
        arg0->unk138 = rot;
        rot = rot + D_8007A918.unk8 * 0.017453292519943295;
        if (rot > 3.141592653589793) {
            rot -= 6.283185307179586;
        } else if (rot < -3.141592653589793) {
            rot += 6.283185307179586;
        }
        arg0->unk134 = rot;
        arg1->unkC = 0.0f;
        arg1->unk14 = 0.0f;
    }
    arg1->unk60 |= 1;
}

void Player_StartOpenChest(PlayerState *arg0, Actor *arg1, s32 arg2) {
    Anim_SetCurrentAndNext(arg1, 0x1C, 1, 0x1D, 1, 1);
    Player_LoadAnim(arg1);
    Anim_UpdateRootMotion(arg1, arg1->unk52 * 0xC + arg2, arg1->scale);
    arg0->unk0 = 0xB;
    arg0->unk4 = 0x5A;
    arg1->unk60 |= 1;
}

void Player_StartUseItem(u8 arg0) {
    CharData *cd = player_char_data[D_8007AA08.actor.unk50];

    D_8007AA08.unk11C = arg0;
    D_8007AA08.unk0 = 0xC;
    D_8007AA08.unk4 = cd->unk116;
    D_8007AA08.actor.unk60 |= 1;
    Anim_SetCurrentAndNext(&D_8007AA20, 0x17, 1, 0x16, 1, 1);
}

/* .data 8004DCB0..8004DD10 in source order: this table (after the functions it
 * points to), Player_LoadAnim's static cache (8004DCF8), D_8004DCFC (end of file). */
typedef void (*Fn8004DCB0)(Actor*, PlayerState*, CharData*);
Fn8004DCB0 D_8004DCB0[18] = {
    (Fn8004DCB0) Player_StateMove,
    (Fn8004DCB0) Player_StateMove,
    (Fn8004DCB0) Player_StateMove,
    (Fn8004DCB0) Player_StateWait,
    (Fn8004DCB0) Player_StateBrake,
    (Fn8004DCB0) Player_StateHurt,
    (Fn8004DCB0) Player_StateDying,
    (Fn8004DCB0) Player_StateTalk,
    (Fn8004DCB0) Player_StateAutoWalk,
    (Fn8004DCB0) Player_StateWalkToExitObject,
    (Fn8004DCB0) Player_StateAnimMove,
    (Fn8004DCB0) Player_StateOpenChest,
    (Fn8004DCB0) Player_StateUseItem,
    (Fn8004DCB0) Player_StateMeleeAttack,
    (Fn8004DCB0) Player_StateCastSpell,
    (Fn8004DCB0) Player_StateBattleWon,
    (Fn8004DCB0) Player_StateMeleeAttack,
    (Fn8004DCB0) Player_StateExamine,
};

void Player_LoadAnim(Actor *arg0) {
    static s32 D_8004DCF8 = -1;
    RomRange *r;

    if (D_8004DCF8 != arg0->unk52) {
        D_8004DCF8 = arg0->unk52;
        r = &player_anim_rom_ranges[D_8004DCF8];
        Dma_ReadRom(r->start, (void *) 0x80200000, r->end - r->start);
    }
}

extern u16 D_8007C050[];
extern u16 battle_enemy_count;

#ifdef NON_MATCHING
/* -1 and 0x130 swapped between s5/s7, one addu operand order (register allocation tie); code is equivalent */
s32 Player_FindMeleeTarget(Actor *arg0) {
    Monster *m;
    s32 ret;
    u16 *idx;
    u32 i;
    f32 radius;
    Actor *a;
    ActorStats *stats;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;

    radius = arg0->unk64->unk18 * arg0->scale;
    ret = 0;
    idx = D_8007C050;
    i = 0;
    for (; i < battle_enemy_count; i++, idx++) {
        m = D_8007B908 + *idx;
        a = &m->actor;
        if (m->actor.unk50 != -1) {
            dx = a->x - arg0->x;
            dz = a->z - arg0->z;
            dist = sqrtf(dx * dx + dz * dz);
            r = a->unk64->unk18 * a->scale;
            if (dist < radius + r + 10.0) {
                D_8007A918.x = dx;
                D_8007A918.z = dz;
                stats = a->unk64;
                if (stats->unk0 == 1) {
                    dx = a->unk68->unk94 - arg0->y;
                    dz = 2.0 * stats->unk18;
                } else if (stats->unk0 == 2) {
                    dz = 0.0f;
                    dx = 0.0f;
                } else {
                    dz = stats->unk1C;
                    dx = a->y - arg0->y;
                }
                if (dx < 0.0f) {
                    dx = -dx;
                }
                dx -= dz * a->scale + arg0->unk64->unk1C * arg0->scale;
                if (dx <= 0.0f) {
                    Math_RotateVec2(arg0->rot, &D_8007A918);
                    r = r * 1.5;
                    if (D_8007A918.z >= 0.0f && -r < D_8007A918.x && D_8007A918.x < r) {
                        ret = *idx + 1;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/3F50/Player_FindMeleeTarget.s")
#endif

void Player_StartMeleeAttack(PlayerState *arg0, Actor *arg1, CharData *arg2) {
    Monster *mon;
    f32 dx;

    arg0->unk0 = 0xD;
    arg0->unk4 = 0x14;
    arg0->unk8 &= ~0x400;
    arg1->unk60 |= 1;
    Anim_SetCurrentAndNext(arg1, 0xA, 1, D_8007A910, 1, 1);
    mon = &D_8007B908[arg0->unk2];
    dx = mon[-1].actor.x - arg1->x;
    arg1->rot = Math_Atan2(dx, mon[-1].actor.z - arg1->z);
    Camera_StartBattleFocus(0x23, arg1);
}

s32 Player_RollHitOnEnemy(s32 arg0, Actor *arg1) {
    s16 chance;
    Monster *m = &D_8007B908[arg0];

    chance = (arg1->unk68->unk86 * 100) / (arg1->unk68->unk86 + ((m->actor.unk68->unk86 + 7) >> 3));
    return Math_Rand(100) < chance;
}

extern s32 D_8004DCFC[];
extern u8 fade_damage_flash[];
void Fade_Start(s32 arg0, u16 arg1, void *arg2);

u16 Player_CalcMeleeDamage(PlayerState *arg0) {
    s32 n;
    s32 i;
    u16 val;
    u16 quarter;
    u16 sum;

    n = 0;
    val = arg0->unk108;
    quarter = arg0->unk108 >> 2;
    sum = arg0->unk108;
    for (i = 0; i < 4; i++) {
        if (quarter < arg0->unk14->unk24[i]) {
            sum = sum - arg0->unk14->unk24[i] + quarter;
            n++;
        }
    }
    val = (val >> 1) + sum;
    if (n != 0) {
        val = (D_8004DCFC[n] * val) >> 6;
    }
    val = (val * arg0->unk10E) >> 4;
    if (Math_Rand((arg0->unk8 & 0x10000) ? 4 : 0x20) == 0) {
        val += val >> 1;
        Fade_Start(4, 0, fade_damage_flash);
        arg0->unk8 |= 0x400;
    }
    if (arg0->unk84 & 1) {
        val >>= 1;
    }
    return val;
}

#ifdef NON_MATCHING
void Camera_Shake(s32 arg0);

/* frame 0x50 vs 0x48: damage kept in an extra saved register, arg2 kept live (register allocation); code is equivalent */
s32 Player_TakeDamage(u16 dmg, u16 arg1, Actor *arg2) {
    PlayerState *p = &D_8007AA08;
    CharData *cd;
    f32 angle;
    s32 d;
    s32 flags;

    if (p->unk0 != 6) {
        cd = player_char_data[p->actor.unk50];
        if (dmg != 0) {
            if (arg1 & 0x8000) {
                angle = Math_Atan2(arg2->x - D_8007AA20.x, arg2->z - D_8007AA20.z) - D_8007AA20.rot;
                if (angle > 3.141592653589793) {
                    angle -= 6.283185307179586;
                } else if (angle < -3.141592653589793) {
                    angle += 6.283185307179586;
                }
                if (angle < 0.0f) {
                    angle = -angle;
                }
                if (angle > 2.356194490192345) {
                    dmg += dmg >> 1;
                }
            }
            dmg = dmg * ((f32) arg2->unk68->unk84 / (f32) (arg2->unk68->unk84 + p->unk10C));
            dmg += Math_Rand((u32) (sqrtf(dmg) * 0.75 + 1.0));
            if (dmg == 0) {
                dmg++;
            }
            d = dmg;
            if (p->actor.unk64->unk4 < dmg) {
                p->actor.unk64->unk4 = 0;
            } else {
                p->actor.unk64->unk4 -= d;
            }
            if (p->unk84 & 0x200) {
                p->actor.unk64->unk8 += d;
                if (p->actor.unk64->unkA < p->actor.unk64->unk8) {
                    p->actor.unk64->unk8 = p->actor.unk64->unkA;
                }
                Hud_StartActorStatusIndicator(&D_8007AA20, 0x200, 2, 0x1E);
            }
            flags = 0;
            p->unk14->unk28++;
            p->unk14->unk2E++;
            if (arg1 & 0x4000) {
                flags = 0x8003;
            }
            Effect_AddFloatingNumber(&D_8007AA20, flags, d);
        }
        p->unk0 = 5;
        p->unk4 = *(s16 *) ((u8 *) cd + 0x62); /* CharData field 0x62 (lh) */
        D_8007AA20.unk60 |= 1;
        d = arg1 & 0x8000;
        if (arg1 & 4) {
            D_8007AA20.unk60 |= 2;
        }
        Anim_SetCurrentAndNext(&D_8007AA20, 8, 1, D_8007A910, 1, 1);
        if (dmg != 0) {
            Camera_Shake(2);
        }
        if (d != 0) {
            Sfx_Play(0, 0x18, 0xFF);
        }
    }
    return dmg;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/3F50/Player_TakeDamage.s")
#endif

/* these are fields of D_8007AA08; some functions use them by their own names */
extern u16 D_8007AA0C;    /* .unk4 */
extern PlayerStateSub14 *D_8007AA1C; /* .unk14 */
extern s16 D_8007AA70;    /* .actor.unk50 */
extern u16 D_8007AA80;    /* .actor.unk60 */

void Player_StartMissReaction(void) {
    PlayerState *p = &D_8007AA08;
    CharData *cd;

    if (p->unk0 != 6) {
        if (p->unk14->unk4 != 0) {
            cd = player_char_data[p->actor.unk50];
            p->unk0 = 3;
            p->unk4 = cd->unk56;
            p->actor.unk60 |= 3;
            Anim_SetCurrentAndNext(&p->actor, 7, 1, D_8007A910, 1, 1);
            Hud_ShowActorPopup(&p->actor);
            Sfx_Play(0, 0x17, 0xFF);
        }
    }
}

s32 Player_CanAct(PlayerState *arg0, Actor *arg1) {
    s32 ret = 0;

    if (!(arg1->unk60 & 1) && !(D_8004DCA0 & 0x80) && !(battle_flags & 8)) {
        if (battle_flags & 1) {
            if (!(battle_flags & 0x202)) {
                if (Magic_IsAnyEffectActive() == 0 && battle_turn_delay == 0) {
                    ret = 1;
                }
            }
        } else {
            ret = 1;
        }
    }
    return ret;
}

extern s16 hud_element_allocation_timer;
extern u16 hud_element_allocation_mode_flags;
extern u16 input_pressed_buttons;

s32 Magic_GetSpellRestrictionFlags(s32 arg0, u16 arg1);
s32 Magic_LookupSpellSequence(u16 count, u8 *seq);
s32 Player_HandleSpellInput(PlayerState *arg0) {
    s32 dir;
    s32 pad;
    s32 ret;
    u32 prev;
    s32 sfx;

    ret = 0;
    if (arg0->unk120 < 3 && (input_pressed_buttons & 0xF)) {
        prev = arg0->unk120;
        if (input_pressed_buttons & 8) {
            dir = 0;
        } else if (input_pressed_buttons & 4) {
            dir = 2;
        } else if (input_pressed_buttons & 2) {
            dir = 1;
        } else if (input_pressed_buttons & 1) {
            dir = 3;
        }
        arg0->unk11D[arg0->unk120] = dir;
        arg0->unk120++;
        if (Magic_GetSpellRestrictionFlags(Magic_LookupSpellSequence(arg0->unk120, arg0->unk11D), arg0->unk14->unk8) & 5) {
            sfx = 0x13;
            arg0->unk120--;
        } else if (!(D_8004DCA0 & 4)) {
            D_8004DCA0 |= 4;
            sfx = 0x17;
        } else {
            sfx = 0x17;
        }
        Sfx_Play(0, sfx, 0xFF);
        if (prev != arg0->unk120) {
            hud_element_allocation_timer = 8;
            hud_element_allocation_mode_flags |= 1;
            if (arg0->unk120 == 1) {
                hud_element_allocation_mode_flags |= 2;
            } else {
                hud_element_allocation_mode_flags &= 0xFFFD;
            }
        }
    } else if (arg0->unk120 && (input_pressed_buttons & 0xA000)) {
        arg0->unk122 = Magic_LookupSpellSequence(arg0->unk120, arg0->unk11D);
        if (Magic_GetSpellRestrictionFlags(arg0->unk122, arg0->unk14->unk8) == 0) {
            D_8004DCA0 &= ~4;
            ret = 1;
        }
    } else if ((input_pressed_buttons & 0x4000) && (D_8004DCA0 & 4)) {
        if (arg0->unk120) {
            arg0->unk120--;
            hud_element_allocation_timer = 8;
            hud_element_allocation_mode_flags &= 0xFFFE;
        }
        if (!arg0->unk120) {
            D_8004DCA0 &= ~4;
        }
        Sfx_Play(0, 0x13, 0xFF);
    }
    return ret;
}

void Player_StartCastSpell(PlayerState *p, Actor *a, AnimEntry *anims) {
    Unk800C185C *e;
    s32 anim;
    s32 next;
    u16 t;

    a->unk64->unk8 -= D_800C186E[p->unk120];
    e = &D_800C185C[(p->unk122 >> 8) & 0xF][p->unk122 & 0xFF];
    if (e->unk18 == 2) {
        p->unk8 |= 4;
        anim = 0x17;
        next = 0x16;
    } else {
        anim = 3;
        next = D_8007A910;
    }
    t = anims[anim].unk2;
    p->unk0 = 0xE;
    p->unk124 = 0x12;
    p->unk120 = 0;
    p->unk4 = t;
    a->vx = a->vz = 0.0f;
    a->unk60 |= 1;
    Anim_SetCurrentAndNext(a, anim, 1, next, 1, 1);
    Camera_StartBattleFocus(0x2D, a);
    hud_melee_hint_timer = 0x1E;
}

void Player_AddTurnMoveAgilityXP(PlayerState *arg0) {
    f32 dx;
    f32 dz;

    if (battle_flags & 1) {
        dx = arg0->actor.x - battle_active_enemy_x;
        dz = arg0->actor.z - battle_active_enemy_z;
        D_8007A988 += sqrtf(dx * dx + dz * dz);
        while (D_8007A988 > 35.0) {
            D_8007A988 -= 35.0;
            arg0->unk14->unk2C++;
        }
    }
}

extern u32 player_level_exp_table[];
extern u16 player_stat_xp_costs[];
extern f32 D_8007A9A8;
extern s32 D_8007A9BC;
extern u8 D_8007A9BF;
extern s16 hud_element_input_timer;

void Effect_StartStatUpMarker(s32 arg0);
void Player_UpdateStatGrowth(PlayerState *p, Actor *a) {
    u16 cost;
    s32 count;
    u8 *lv;

    count = 0;
    if (!(battle_flags & 1)) {
        if (D_800842E8 & 1) {
            D_8007A8FC += D_8007A9A8;
            if (D_8007A8FC > 800.0) {
                D_8007A8FC -= 800.0;
                p->unk14->unk2C++;
            }
        } else {
            D_8007A900 += D_8007A9A8;
            if (D_8007A900 > 1500.0) {
                D_8007A900 -= 1500.0;
                p->unk14->unk2C++;
            }
        }
    }
    if (a->unk64->unk6 < 500) {
        if (p->unk14->unk28 >= player_stat_xp_costs[p->unk14->unk30]) {
            p->unk14->unk28 -= player_stat_xp_costs[p->unk14->unk30];
            a->unk64->unk6++;
            a->unk64->unk4++;
            if (p->unk14->unk30 < 0x36) {
                p->unk14->unk30++;
            }
            Effect_StartStatUpMarker(0);
            count++;
        }
    } else {
        p->unk14->unk28 = 0;
    }
    if (a->unk64->unkA < 500) {
        cost = player_stat_xp_costs[p->unk14->unk31];
        if (p->unk8 & 0x4000) {
            cost *= 3;
        } else {
            cost *= 4;
        }
        if (p->unk14->unk2A >= cost) {
            p->unk14->unk2A -= cost;
            a->unk64->unkA++;
            a->unk64->unk8++;
            if (p->unk14->unk31 < 0x36) {
                p->unk14->unk31++;
            }
            Effect_StartStatUpMarker(2);
            count++;
        }
    } else {
        p->unk14->unk2A = 0;
    }
    if (a->unk64->unkC < 0xFF) {
        cost = player_stat_xp_costs[p->unk14->unk32];
        if (p->unk8 & 0x8000) {
            cost = (f32)cost * 0.8;
        }
        if (p->unk14->unk2C >= cost) {
            p->unk14->unk2C -= cost;
            a->unk64->unkC++;
            if (p->unk14->unk32 < 0x36) {
                p->unk14->unk32++;
            }
            Effect_StartStatUpMarker(3);
            count++;
        }
    } else {
        p->unk14->unk2C = 0;
    }
    if (a->unk64->unkE < 0xFF) {
        cost = player_stat_xp_costs[p->unk14->unk33];
        if (p->unk8 & 0x2000) {
            cost = (f32)cost * 0.8;
        }
        if (p->unk14->unk2E >= cost) {
            p->unk14->unk2E -= cost;
            a->unk64->unkE++;
            if (p->unk14->unk33 < 0x36) {
                p->unk14->unk33++;
            }
            Effect_StartStatUpMarker(1);
            count++;
        }
    } else {
        p->unk14->unk2E = 0;
    }
    if (!(D_8004DCA0 & 8)) {
        if (p->unk14->unk34 >= 0x62) {
            a->unk64->unk10 = 0;
        } else if (a->unk64->unk10 >= player_level_exp_table[p->unk14->unk34]) {
            a->unk64->unk10 -= player_level_exp_table[p->unk14->unk34];
            if (p->unk14->unk34 < 0x62) {
                p->unk14->unk34++;
            }
            lv = p->unk14->unk24;
            if (lv[0] != 0x32 || lv[1] != 0x32 || lv[2] != 0x32 || lv[3] != 0x32) {
                D_8004DCA0 |= 8;
                p->unk0 = 0;
                hud_element_input_timer = 8;
                Sfx_Play(0, 1, 0xFF);
            }
        }
    }
    if (count != 0) {
        Sfx_Play(4, 0x35, 0xFF);
    }
    if (!(D_8004DCA0 & 0xA) && D_8007A9BC != 0xFF) {
        Item_BuildMessage(D_8007A9BC);
        Text_OpenWindow(1);
        Item_AddToInventory(D_8007A9BF);
        D_8007A9BC = 0xFF;
        p->unk8 |= 2;
        D_8004DCA0 |= 2;
        Sfx_Play(0, 0x3B, 0xFF);
    }
    if (!(D_8004DCA0 & 0xA)) {
        a->unk60 &= 0xFFFE;
    }
}

s32 D_8004DCFC[4] = { 0x40, 0x40, 0x39, 0x3C };
