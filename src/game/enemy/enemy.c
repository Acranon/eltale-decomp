#include "common.h"
#include "game/enemy/enemy.h"

/*
 * Battle enemies (6 slots, enemy_slots): load the area's enemy set, spawn, per-frame
 * state machine (idle, approach, hurt/death, attack, spell), turn order, movement and
 * collision inside the battle circle, hit/damage rolls both ways, boss attack scripts.
 * Original file: AEA0.c (ROM 0xAEA0).
 */

typedef struct {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u16 unk12;
} Unk8007C288;

/* local copy of game/math/math.h's Vec3f until H2 */
typedef struct Vec3f {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f;

/* local copy of game/map/collision.h's CollResult until H2 */
typedef struct CollResult {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

/* This file's .bss, 8007B900..8007C0B0, in address order. D_8007B904 and
 * D_8007C09C/D_8007C0A0 are unreferenced gaps. Splat's labels inside the enemy
 * table (D_8007B918..D_8007BB5C, fields of enemy_slots[0] and [1]) and D_8007C074
 * (enemy_temp_vec.y) are aliases in undefined_syms.txt. Enemy_StartAttackScript treats
 * enemy_script_time..enemy_script_obj as one Unk8007C060; they are kept as the scalars the
 * other functions use. */
s32 enemy_count;
s32 D_8007B904;
Enemy enemy_slots[6];
Enemy *enemy_turn_current;
s32 enemy_drawn_count;
Actor *enemy_drawn_list[6];
u8 **enemy_anim_tables;
s32 enemy_names;
u16 enemy_turn_order[6];
EnemyAreaSet *enemy_area_set;
u16 enemy_script_time;
EnemyScriptCmd *enemy_script_cmd;
Enemy *enemy_script_enemy;
Actor *enemy_script_obj;
Vec3f enemy_temp_vec;
CollResult enemy_coll;
s32 D_8007C09C;
s32 D_8007C0A0[4];

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ Actor *unkC;
} Unk8007C060;

typedef struct {
    /* 0x000 */ u8 pad0[0x140];
    /* 0x140 */ s16 unk140;
    /* 0x142 */ u16 unk142;
    /* 0x144 */ u16 unk144;
    /* 0x146 */ u8 pad146[2];
    /* 0x148 */ f32 unk148;
    /* 0x14C */ f32 unk14C;
} Unk80056718;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ struct Unk8007AA84 *unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[0x18];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x34];
    /* 0x78 */ u16 unk78;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk8007C2A8;

extern s32 mapobj_billboard_count;
extern Unk8007C2A8 *mapobj_billboard_list[];

typedef struct Unk8007AA84 {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x10];
    /* 0x2C */ u16 unk2C;
} Unk8007AA84;

f32 sqrtf(f32);
extern Unk8007AA84 *D_8007AA84;

typedef struct {
    /* 0x00 */ u8 pad0[10];
} Unk800C18D8;


void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, CollResult *);

extern s16 hud_enemy_info_timer;
void Anim_DrawModel(s32, Actor *, u8 *, struct GfxFrameData *);
void Anim_AdvanceFrame(s32, Actor *, u8 *);
void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
extern Gfx *gfx_dl_head;
f32 Math_Atan2(f32, f32);
void Anim_SetCurrentAndNext(Actor *, s32, s32, s32, s32, u16);
void Camera_StartBattleFocus(s32, Actor *);
void Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, Unk800C18D8 *, Vec3f *, Actor *);
void Effect_StartConvergeEmitter(s32, s32, f32, f32, f32, f32);
void Battle_EndTurn(Actor *);
void Anim_UpdateRootMotion(Actor *, u8 *, f32, Vec3f *);
void Hud_ClearActorStatusIndicators(Actor *);
void Hud_ShowActorPopup(Actor *);
void Fade_Start(s32, u16, void *);
u32 Math_Rand(u32);
void Math_RotateVec2(f32, Vec3f *);
void Dma_ReadRom();
void Sfx_Play(u8, s8, u8);

extern u8 fade_damage_flash[];
extern EnemyAreaSet enemy_area_sets[];
extern u32 enemy_attack_scripts[];
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} SpawnDef; /* size 0x10 */

typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x24];
} Unk800C185C; /* size 0x44 */

extern Unk80056718 enemy_effect_defs;
extern u16 D_8005685A;
extern u16 D_8005685C;
extern Unk800C185C *D_800C185C[];
extern f32 D_8007AA20;
extern f32 D_8007AA24;
extern f32 D_8007AA28;
extern f32 D_8007B928;
extern f32 D_8007B92C;
void Camera_Shake(s32);
extern f32 battle_center_x;
extern f32 battle_center_z;
extern f32 battle_turn_origin_x;
extern f32 battle_turn_origin_z;
extern f32 battle_arena_radius;

/* anim table entry; local view of anim.h's AnimSet until H2 */
typedef struct AnimSet {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[8];
} AnimSet; /* size 0xC */

void Magic_CreateCastEffect(Actor *, u32, s32, u16);
u16 Player_TakeDamage(u16, u16, Actor *);
void Effect_SpawnStreakBurst(f32, f32, f32);
void Effect_AddFloatingNumber(Actor *, s32, s32);
void Hud_StartActorStatusIndicator(Actor *, u16, u16, s16);
void Player_StartMissReaction(void);
extern f32 D_8007C074;
extern s32 player_battle_exp;
extern s32 D_8007A9B8;
extern Unk8007AA08 player_state;
extern ActorBattle *D_8007AA88;
extern Unk8007C288 *map_subarea_def;
extern u16 map_subarea_flags;
extern u16 battle_flags;
extern u16 battle_turn_order_index;
extern Unk800C18D8 D_800C18D8[];
extern u8 D_8020E6F0[];

void Enemy_InitForArea(void) {
    s32 i;
    Enemy *e;

    enemy_count = 0;
    enemy_drawn_count = 0;
    e = enemy_slots;
    i = 6;
    do {
        e->actor.unk50 = -1;
        e++;
        i--;
    } while (i != 0);
    if (map_subarea_flags & 1) {
        Enemy_LoadAreaSet();
    }
}

void Enemy_UpdateAll(void) {
    s32 n;
    Enemy *e;
    Actor *obj;

    n = enemy_count;
    if (n != 0) {
        for (e = enemy_slots; n != 0; e++) {
            obj = &e->actor;
            if (e->actor.unk50 != -1) {
                enemy_state_handlers[e->type](obj, e, enemy_anim_tables[obj->unk50]);
                n--;
            }
        }
    }
    if (battle_flags & 0x100) {
        Enemy_RunAttackScript();
    }
}

void Enemy_DrawAll(struct GfxFrameData *arg0) {
    Enemy *e;
    s32 n;
    Actor **list;
    Actor *obj;
    u8 *anims;
    f32 y;
    f32 h;

    enemy_drawn_count = 0;
    list = enemy_drawn_list;
    gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
    n = enemy_count;
    e = enemy_slots;
    while (n != 0) {
        obj = &e->actor;
        if (e->actor.unk50 != -1) {
            y = obj->y;
            anims = enemy_anim_tables[obj->unk50];
            if (obj->unk64->unk0 == 1) {
                h = obj->unk64->unk1C * obj->scale;
                if (y < player_state.y) {
                    obj->y = player_state.y;
                }
                obj->y += h;
                obj->unk68->unk94 = obj->y;
            }
            Anim_DrawModel(1, obj, &anims[obj->unk52 * 12], arg0);
            Anim_AdvanceFrame(obj->unk58, obj, &anims[obj->unk52 * 12]);
            obj->y = y;
            if (obj->unk64->unk0 != 2 && !(obj->unk62 & 0x8000)) {
                Shadow_Queue(obj->x, obj->y, obj->z, obj->nx, obj->ny, obj->nz, obj->unk28 * obj->scale);
            }
            *list++ = obj;
            n--;
            enemy_drawn_count++;
        }
        e++;
    }
}

void Enemy_LoadAreaSet(void) {
    u8 *start;
    u8 *end;

    enemy_area_set = &enemy_area_sets[map_subarea_def->unk12];
    enemy_anim_tables = enemy_area_set->unk8;
    enemy_names = enemy_area_set->unk10;
    start = enemy_area_set->start;
    end = enemy_area_set->end;
    Dma_ReadRom(start, D_8020E6F0, end - start);
}

void Enemy_RemoveAll(void) {
    Enemy *e;
    s32 i;
    Actor *obj;

    for (e = enemy_slots, i = 6; i != 0; i--, e++) {
        obj = &e->actor;
        if (e->actor.unk50 != -1) {
            Hud_ClearActorStatusIndicators(obj);
            obj->unk50 = -1;
        }
    }
    enemy_count = 0;
}

void Enemy_Spawn(s32 idx, f32 x, f32 z, f32 angle, Actor *obj, Enemy *e) {
    s32 pad;
    EnemyDef *def;

    def = &enemy_area_set->unkC[idx];
    obj->unk50 = def->unk2;
    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
    obj->frame = Math_Rand(16);
    obj->scale = def->unk20;
    obj->unk28 = def->unk18;
    obj->unk68 = &e->battle;
    obj->unk64 = (ActorStats *)def;
    e->unk28 = def;
    e->unkA = def->unk6;
    e->unkC = def->unk6;
    e->type = 0;
    e->flags = 0;
    e->unk10 = (f32)def->unkC * 0.2857 + 17.0;
    e->unk20 = e->unk24 = 0;
    enemy_coll.x = obj->unk64->unk18 * obj->unk64->unk20;
    Coll_ResolveFloorAndWalls(x, 0.0f, z, 0xA01, &enemy_coll);
    if (enemy_coll.flags & 0x8000) {
        if (obj->unk64->unk0 == 0) {
            Coll_ResolveFloorAndWalls(x + 0.5, 0.0f, z + 0.5, 0xA01, &enemy_coll);
            if (enemy_coll.flags & 0x8000) {
                enemy_coll.y = player_state.y;
            }
        } else {
            enemy_coll.y = player_state.y;
        }
    }
    obj->x = enemy_coll.x;
    obj->y = enemy_coll.y;
    obj->z = enemy_coll.z;
    obj->rot = angle;
    obj->nx = enemy_coll.nx;
    obj->ny = enemy_coll.ny;
    obj->nz = enemy_coll.nz;
    obj->unk62 = enemy_coll.flags;
    obj->unk5E = 1;
    obj->unk60 = 0;
    e->battle.unk0 = 0;
    e->battle.unk8C = 0;
    e->battle.unk84 = e->unk28->unk2A;
    e->battle.unk8A = 16;
    e->battle.unk86 = obj->unk64->unkC;
    e->battle.unk88 = obj->unk64->unkE;
    e->battle.unk90 = 1.0f;
    e->battle.unk94 = obj->y;
}

void Enemy_SortTurnOrder(void) {
    u32 i;
    s32 swapped;
    u16 tmp;
    u16 keys[6];

    for (i = 0; i < enemy_count; i++) {
        enemy_turn_order[i] = i;
        keys[i] = enemy_slots[i].unk28->unkC;
    }
    do {
        swapped = 0;
        for (i = 0; i < enemy_count - 1; i++) {
            if (keys[i] < keys[i + 1]) {
                tmp = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = tmp;
                swapped++;
                tmp = enemy_turn_order[i];
                enemy_turn_order[i] = enemy_turn_order[i + 1];
                enemy_turn_order[i + 1] = tmp;
            }
        }
    } while (swapped);
}

void Enemy_StartTurn(void) {
    enemy_slots[enemy_turn_order[battle_turn_order_index]].flags |= 1;
}

void Enemy_StateIdle(Actor *obj, Enemy *e, AnimSet *arg2) {
    EnemyAttack *v;

    Enemy_GetAnimStep(obj, &enemy_temp_vec);
    Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
    if (e->flags & 1) {
        enemy_turn_current = e;
        hud_enemy_info_timer = 60;
        e->flags &= 0xFFFC;
        if (e->battle.unk0 & 8) {
            Battle_EndTurn(obj);
            return;
        }
        v = Enemy_ChooseAttack(e, obj);
        if (v != NULL) {
            if (!(e->flags & 0x10)) {
                Enemy_StartAttack(e, obj, v);
                return;
            }
            e->type = 1;
            e->unk4 = 4;
            if (battle_flags & 0x100) {
                e->unk2 = arg2[1].unk2;
                Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2[1].unk2 / 10;
                Anim_SetCurrentAndNext(obj, 1, 10, 1, 10, 1);
            }
        } else {
            e->type = 1;
            e->unk4 = 4;
            if (battle_flags & 0x100) {
                e->unk2 = arg2[1].unk2;
                Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2[1].unk2 / 10;
                Anim_SetCurrentAndNext(obj, 1, 10, 1, 10, 1);
            }
        }
    }
}

void Enemy_StateApproach(Actor *obj, Enemy *e, AnimSet *arg2) {
    EnemyAttack *v;
    f32 dx;
    f32 dz;
    f32 d;

    Enemy_TurnToward(obj, player_state.x, player_state.z);
    if (battle_flags & 0x100) {
        enemy_temp_vec.x = 0.0f;
        enemy_temp_vec.y = 0.4f;
        Math_RotateVec2(obj->rot, &enemy_temp_vec);
    } else {
        Enemy_GetAnimStep(obj, &enemy_temp_vec);
    }
    Enemy_Move(1, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
    e->unk2--;
    if (e->unk2 == 0) {
        e->unk4--;
        if (e->unk1C != NULL) {
            dx = player_state.x - obj->x;
            dz = player_state.z - obj->z;
            d = sqrtf(dx * dx + dz * dz) - D_8007AA84->unk18 * player_state.unk3C;
            if (d < e->unk1C->unk10 * obj->scale) {
                Enemy_StartAttack(e, obj, e->unk1C);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                Enemy_StartAttack(e, obj, e->unk1C);
                return;
            }
            if (battle_flags & 0x100) {
                e->unk2 = arg2[1].unk2;
            } else {
                e->unk2 = arg2[1].unk2 / 10;
            }
        } else {
            v = Enemy_ChooseAttack(e, obj);
            if (v != NULL) {
                Enemy_StartAttack(e, obj, v);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                e->type = 0;
                Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                Battle_EndTurn(obj);
                return;
            }
            if (battle_flags & 0x100) {
                e->unk2 = arg2[1].unk2;
            } else {
                e->unk2 = arg2[1].unk2 / 10;
            }
        }
    }
}

void Enemy_StateHurt(Actor *obj, Enemy *ai, s32 arg2) {
    Enemy_GetAnimStep(obj, &enemy_temp_vec);
    Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        if (ai->unkA == 0) {
            Hud_ClearActorStatusIndicators(obj);
            Enemy_SpawnDeathEffects(obj);
            obj->unk50 = -1;
            obj->unk60 &= 0xFFFE;
            enemy_count--;
            player_battle_exp += obj->unk64->unk10;
            D_8007A9B8 += obj->unk64->unk14;
            Sfx_Play(0, 10, 0xFF);
        } else {
            ai->type = 0;
            obj->unk60 &= 0xFFFC;
        }
    }
}

void Enemy_StateFacePlayer(Actor *obj, Enemy *ai, s32 arg2) {
    Enemy_TurnToward(obj, player_state.x, player_state.z);
    Enemy_GetAnimStep(obj, &enemy_temp_vec);
    Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        ai->type = 0;
        obj->unk60 &= 0xFFFE;
        Battle_EndTurn(obj);
    }
}

void Enemy_StateMeleeAttack(Actor *obj, Enemy *e, AnimSet *anims) {
    u16 n;
    f32 dx;
    f32 dz;
    f32 d;
    u16 atk;
    EnemyAttack *a;
    u16 attr;

    switch (e->unk6) {
        case 0:
            attr = e->unk1C->unk2;
            if (attr & 2) {
                Enemy_GetAnimStep(obj, &enemy_temp_vec);
                Enemy_Move(0, enemy_temp_vec.x, D_8007C074, obj, (Enemy *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                e->unk6++;
                e->unk2 = e->unk1C->unk6;
            }
            break;
        case 1:
            attr = e->unk1C->unk2;
            if (attr & 0xA) {
                Enemy_GetAnimStep(obj, &enemy_temp_vec);
                Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
            }
            if (!(player_state.unk78 & 2) && !(e->flags & 8)) {
                dx = player_state.x - obj->x;
                dz = player_state.z - obj->z;
                d = sqrtf(dx * dx + dz * dz) - player_state.unk3C * player_state.unk14->unk18;
                if (d < e->unk1C->unk14 * obj->scale) {
                    if (Enemy_RollHitOnPlayer(obj) != 0) {
                        n = Enemy_CalcAttackDamage(e);
                        atk = 0x8004;
                        if (e->flags & 0x20) {
                            atk = 0xC004;
                        }
                        n = Player_TakeDamage(n, atk, obj);
                        enemy_temp_vec.x = 0.0f;
                        enemy_temp_vec.y = 2.0f * (obj->unk64->unk18 * obj->scale);
                        Math_RotateVec2(obj->rot, &enemy_temp_vec);
                        Effect_SpawnStreakBurst(obj->x + enemy_temp_vec.x, obj->y + obj->unk64->unk1C * obj->scale * 0.7f, obj->z + enemy_temp_vec.y);
                        if (e->battle.unk0 & 2) {
                            n = ((n + 3) >> 2) + 1;
                            e->unkA += n;
                            if (obj->unk64->unk6 < e->unkA) {
                                e->unkA = obj->unk64->unk6;
                            }
                            Effect_AddFloatingNumber(obj, 1, n);
                            Hud_StartActorStatusIndicator(obj, 2, 1, 30);
                        }
                    } else {
                        Player_StartMissReaction();
                        player_state.unk14->unk2C++;
                    }
                    e->flags |= 8;
                }
            }
            e->unk2--;
            if (e->unk2 == 0) {
                a = e->unk1C;
                e->unk6++;
                if (a->unkA == -1) {
                    e->unk2 = anims[a->unk8].unk2 - a->unk4;
                } else {
                    e->unk2 = anims[a->unkC].unk2;
                    Anim_SetCurrentAndNext(obj, a->unkC, 1, 0, 1, 1);
                    Enemy_GetAnimStep(obj, &enemy_temp_vec);
                }
                if (e->unk2 <= 0) {
                    e->unk2 = 1;
                }
                Battle_EndTurn(obj);
            }
            break;
        case 2:
            Enemy_GetAnimStep(obj, &enemy_temp_vec);
            Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
            e->unk2--;
            if (e->unk2 == 0) {
                e->type = 0;
                obj->unk60 &= 0xFFFE;
            }
            break;
    }
}

void Enemy_StateCastSpell(Actor *obj, Enemy *e, AnimSet *anims) {
    EnemyAttack *a;

    switch (e->unk6) {
        case 0:
            if (e->unk1C->unk2 & 2) {
                Enemy_GetAnimStep(obj, &enemy_temp_vec);
                Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                Magic_CreateCastEffect(obj, e->unk1C->unk0 & ~0x8000, 0, 0);
                a = e->unk1C;
                e->unk6++;
                if (a->unkA == -1) {
                    e->unk2 = anims[a->unk8].unk2 - a->unk4;
                } else {
                    e->unk6++;
                    e->unk2 = a->unk6;
                }
                if (e->unk2 <= 0) {
                    e->unk2 = 15;
                }
                Battle_EndTurn(obj);
            }
            break;
        case 1:
            if (e->unk1C->unk2 & 0xA) {
                Enemy_GetAnimStep(obj, &enemy_temp_vec);
                Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                e->type = 0;
                obj->unk60 &= 0xFFFE;
                e->unk20 = e->unk24 = 0.0f;
            }
            break;
        case 2:
            if (e->unk1C->unk2 & 0xA) {
                Enemy_GetAnimStep(obj, &enemy_temp_vec);
                Enemy_Move(0, enemy_temp_vec.x, enemy_temp_vec.y, obj, (Enemy *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                a = e->unk1C;
                e->unk6--;
                e->unk2 = anims[a->unkC].unk2;
                Anim_SetCurrentAndNext(obj, a->unkC, 1, 0, 1, 1);
            }
            if (e->unk2 <= 0) {
                e->unk2 = 15;
            }
            break;
    }
}

EnemyAttack *Enemy_ChooseAttack(Enemy *e, Actor *obj) {
    f32 dist;
    f32 r;
    f32 range;
    f32 d;
    f32 d2;
    s32 swapped;
    s32 cont;
    u32 i;
    EnemyAttack *sel;
    EnemyAttack *b;
    EnemyAttack *list[5];
    EnemyAttack *a;

    e->flags &= ~0x10;
    dist = sqrtf((player_state.x - obj->x) * (player_state.x - obj->x) + (player_state.z - obj->z) * (player_state.z - obj->z)) - D_8007AA84->unk18 * player_state.unk3C;
    sel = e->unk28->unk30;
    for (i = 0; i < e->unk28->unk2C; i++) {
        list[i] = sel++;
    }
    swapped = 0;
    do {
        for (i = 0; i < e->unk28->unk2C - 1; i++) {
            b = list[i];
            a = list[i + 1];
            if (b->unk10 > a->unk10) {
                list[i] = a;
                list[i + 1] = b;
                swapped++;
            }
        }
        cont = swapped != 0;
        swapped = 0;
    } while (cont);
    for (i = 0; i < e->unk28->unk2C; i++) {
        sel = list[i];
        if (i < e->unk28->unk2C - 1) {
            d = sel->unk10 * obj->scale;
            d2 = e->unk10 * e->battle.unk90 + d;
            if (dist < d) {
                swapped = 1;
                break;
            }
            if (dist < d2) {
                b = list[i + 1];
                d = b->unk10 * obj->scale;
                if (dist < d) {
                    if (Math_Rand(2) == 0) {
                        sel = b;
                    }
                    swapped = 1;
                    if (sel != b) {
                        e->flags |= 0x10;
                    }
                    break;
                }
            }
        } else {
            d = sel->unk10 * obj->scale;
            d2 = e->unk10 * e->battle.unk90 + d;
            if (dist < d2) {
                if (d < dist) {
                    e->flags |= 0x10;
                }
                swapped = 1;
                break;
            }
        }
    }
    if (!swapped) {
        sel = NULL;
    }
    if (e->unk28->unk24 & 4) {
        sel = &e->unk28->unk30[Math_Rand(e->unk28->unk2C)];
    }
    e->unk1C = sel;
    return sel;
}

void Enemy_StartAttack(Enemy *e, Actor *obj, EnemyAttack *arg2) {
    s32 t = arg2->unk0 & 0x8000;

    if (t && (e->battle.unk0 & 0x40)) {
        e->type = 0;
        Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
        Battle_EndTurn(obj);
        return;
    }
    if (t) {
        e->type = 5;
    } else {
        e->type = 4;
    }
    e->unk6 = 0;
    e->unk2 = arg2->unk4;
    e->flags &= 0xFFD7;
    obj->unk60 = 1;
    obj->rot = Math_Atan2(player_state.x - obj->x, player_state.z - obj->z);
    Anim_SetCurrentAndNext(obj, arg2->unk8, 1, arg2->unkA == -1 ? 0 : arg2->unkA, 1, 1);
    Camera_StartBattleFocus(arg2->unk4 + 0xF, obj);
    if (e->unk2 == 0) {
        e->unk2 = 1;
    }
    if (battle_flags & 0x100) {
        Enemy_StartAttackScript(arg2->unk0 & 0xFF, (s32)e);
    }
}

void Enemy_TurnToward(Actor *obj, f32 x, f32 z) {
    f32 diff;

    x -= obj->x;
    z -= obj->z;
    diff = Math_Atan2(x, z) - obj->rot;
    if (diff > 3.141592653589793) {
        diff -= 6.283185307179586;
    } else if (diff < -3.141592653589793) {
        diff += 6.283185307179586;
    }
    obj->rot += diff * 0.05;
    if (obj->rot > 3.141592653589793) {
        obj->rot -= 6.283185307179586;
    } else if (obj->rot < -3.141592653589793) {
        obj->rot += 6.283185307179586;
    }
}

void Enemy_Move(s32 clamp, f32 dx, f32 dz, Actor *obj, Enemy *ai) {
    Enemy *e = (Enemy *)ai;
    f32 x;
    f32 z;
    f32 d;
    f32 r;
    s32 flags;

    if (e->unk20 != 0.0f || e->unk24 != 0.0f) {
        dx += e->unk20;
        dz += e->unk24;
        e->unk20 *= 0.9f;
        e->unk24 *= 0.9f;
    }
    if (clamp) {
        x = obj->x + obj->vx - battle_turn_origin_x;
        z = obj->z + obj->vz - battle_turn_origin_z;
        d = sqrtf(x * x + z * z);
        r = e->unk10 * e->battle.unk90;
        if (r < d) {
            dx = r * x / d - obj->x + battle_turn_origin_x;
            dz = r * z / d - obj->z + battle_turn_origin_z;
            e->flags |= 2;
        }
    }
    x = obj->x + obj->vx - battle_center_x;
    z = obj->z + obj->vz - battle_center_z;
    d = sqrtf(x * x + z * z);
    if (battle_arena_radius < d) {
        dx = (battle_arena_radius - 0.5) * x / d - obj->x + battle_center_x;
        dz = (battle_arena_radius - 0.5) * z / d - obj->z + battle_center_z;
    }
    Enemy_ResolveCollisions(&dx, &dz, obj);
    obj->vx = dx;
    obj->vz = dz;
    obj->x += dx;
    obj->z += dz;
    flags = 0xA00;
    if (obj->unk64->unk0 == 0 && e->type != 0) {
        flags = 0xA01;
    }
    enemy_coll.x = obj->unk64->unk18 * obj->unk64->unk20;
    Coll_ResolveFloorAndWalls(obj->x, obj->y, obj->z, flags, &enemy_coll);
    obj->x = enemy_coll.x;
    obj->y = enemy_coll.y;
    obj->z = enemy_coll.z;
    if (e->flags & 4) {
        obj->y -= 30.0;
    }
    obj->nx = enemy_coll.nx;
    obj->ny = enemy_coll.ny;
    obj->nz = enemy_coll.nz;
    obj->unk62 = enemy_coll.flags;
}

void Enemy_GetAnimStep(Actor *obj, Vec3f *out) {
    u8 *anims;

    anims = enemy_anim_tables[obj->unk50];
    Anim_UpdateRootMotion(obj, anims + obj->unk52 * 0xC, obj->scale, out);
    out->x = -obj->unk44;
    out->y = obj->unk4C;
    Math_RotateVec2(obj->rot, out);
}

void Enemy_ResolveCollisions(f32 *dx, f32 *dz, Actor *obj) {
    f32 nx;
    f32 nz;
    f32 ddx;
    f32 ddz;
    f32 r;
    f32 d;
    s32 hit;
    f32 radius;
    s32 i;
    Actor **list;
    Actor *other;
    Unk8007C2A8 **list2;
    Unk8007C2A8 *other2;

    nx = *dx + obj->x;
    nz = *dz + obj->z;
    radius = obj->unk28 * obj->scale;
    hit = 0;
    ddx = nx - player_state.x;
    ddz = nz - player_state.z;
    r = player_state.unk40 * player_state.unk3C + radius;
    if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
        d = sqrtf(ddx * ddx + ddz * ddz);
        if (d < r) {
            d = r / d;
            hit = 1;
            ddx *= d;
            ddz *= d;
            *dx = D_8007AA20 + ddx - obj->x;
            *dz = D_8007AA28 + ddz - obj->z;
        }
    }
    i = enemy_drawn_count;
    if (i != 0) {
        for (list = enemy_drawn_list; !hit && i != 0; i--) {
            other = *list++;
            if (other != obj) {
                ddx = nx - other->x;
                ddz = nz - other->z;
                r = other->unk28 * other->scale + radius;
                if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                    d = sqrtf(ddx * ddx + ddz * ddz);
                    if (d != 0.0f && d < r) {
                        d = r / d;
                        hit++;
                        ddx *= d;
                        ddz *= d;
                        *dx = other->x + ddx - obj->x;
                        *dz = other->z + ddz - obj->z;
                    }
                }
            }
        }
    }
    i = mapobj_billboard_count;
    if (i != 0) {
        for (list2 = mapobj_billboard_list; !hit && i != 0; i--) {
            other2 = *list2++;
            ddx = nx - other2->x;
            ddz = nz - other2->z;
            r = radius + other2->unk10 * 2.0;
            if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                d = sqrtf(ddx * ddx + ddz * ddz);
                if (d < r) {
                    d = r / d;
                    hit++;
                    ddx *= d;
                    ddz *= d;
                    *dx = other2->x + ddx - obj->x;
                    *dz = other2->z + ddz - obj->z;
                }
            }
        }
    }
}

s32 Enemy_RollHitOnPlayer(Actor *obj) {
    s16 chance;

    chance = (obj->unk68->unk86 * 100) / (obj->unk68->unk86 + ((D_8007AA88->unk86 + 7) >> 3));
    return Math_Rand(100) < chance;
}

u16 Enemy_CalcAttackDamage(Enemy *arg0) {
    u16 dmg;

    dmg = arg0->battle.unk84;
    dmg = (dmg * arg0->battle.unk8A) >> 4;
    if (Math_Rand(32) == 0) {
        dmg = dmg + (dmg >> 1);
        Fade_Start(4, 0, fade_damage_flash);
        arg0->flags |= 0x20;
    }
    if (arg0->battle.unk0 & 1) {
        dmg >>= 1;
    }
    return dmg;
}

u16 Enemy_TakeDamage(s32 idx, u16 dmg, u16 elem, u16 flags, Actor *src) {
    f32 q;
    Actor *obj;
    f32 a;
    u8 *anims;
    Enemy *enemies;

    obj = &enemy_slots[idx].actor;
    anims = enemy_anim_tables[enemy_slots[idx].actor.unk50];
    if (enemy_slots[idx].unkA) {
        if (dmg) {
            if (!(flags & 0x8000)) {
                switch (enemy_element_bits[enemy_slots[idx].unk28->unk26] | enemy_element_bits[elem]) {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                        dmg >>= 1;
                        break;
                    case 5:
                    case 10:
                        dmg += dmg >> 2;
                        break;
                }
            } else {
                a = Math_Atan2(src->x - obj->x, src->z - obj->z) - obj->rot;
                if (a > 3.141592653589793) {
                    a -= 6.283185307179586;
                } else if (a < -3.141592653589793) {
                    a += 6.283185307179586;
                }
                if (a < 0.0f) {
                    a = -a;
                }
                if (a > 2.356194490192345) {
                    dmg += dmg >> 1;
                }
            }
            a = src->unk68->unk84;
            a /= (f32)(src->unk68->unk84 + enemy_slots[idx].battle.unk88);
            dmg = dmg * a;
            q = sqrtf(dmg);
            dmg += Math_Rand(q * 0.75 + 1.0);
            if (!dmg) {
                dmg++;
            }
            if (enemy_slots[idx].unkA < dmg) {
                enemy_slots[idx].unkA = 0;
            } else {
                enemy_slots[idx].unkA -= dmg;
            }
            if (enemy_slots[idx].battle.unk0 & 0x200) {
                enemy_slots[idx].unkC += dmg;
                enemies = enemy_slots;
                if (obj->unk64->unkA < enemies[idx].unkC) {
                    enemy_slots[idx].unkC = obj->unk64->unkA;
                }
                Hud_StartActorStatusIndicator(obj, 0x200, 2, 30);
            }
            Effect_AddFloatingNumber(obj, (flags & 0x4000) ? 0x8003 : 0, dmg);
        }
        enemy_slots[idx].type = 2;
        obj->unk60 |= 1;
        if (flags & 4) {
            obj->unk60 |= 2;
        }
        if (battle_flags & 0x100) {
            enemy_slots[idx].unk2 = ((AnimSet *)anims)[enemy_slots[idx].unk28->unk28].unk2;
            Anim_SetCurrentAndNext(obj, enemy_slots[idx].unk28->unk28, 1, 0, 1, 1);
        } else {
            enemy_slots[idx].unk2 = ((AnimSet *)anims)[enemy_slots[idx].unk28->unk28].unk2 / 10;
            Anim_SetCurrentAndNext(obj, enemy_slots[idx].unk28->unk28, 10, 0, 1, 1);
        }
    }
    if (flags & 0x8000) {
        Sfx_Play(0, 0x18, 0xFF);
    }
    return dmg;
}


void Enemy_PlayMissEffect(Actor *obj) {
    Hud_ShowActorPopup(obj);
    Sfx_Play(0, 0x17, 0xFF);
}

s32 Enemy_GetSlotIndex(Actor *arg0) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (arg0 == &enemy_slots[i].actor) {
            break;
        }
    }
    return i;
}

void Enemy_SpawnDeathEffects(Actor *obj) {
    f32 y;
    Unk800C18D8 *t;

    enemy_temp_vec.x = enemy_effect_defs.unk148;
    enemy_temp_vec.y = enemy_effect_defs.unk14C;
    t = &D_800C18D8[enemy_effect_defs.unk140];
    enemy_temp_vec.z = obj->unk28;
    if (obj->unk64->unk0 == 1) {
        y = obj->unk68->unk94;
    } else {
        y = obj->y + obj->unk64->unk1C * 0.5 * obj->scale;
    }
    Magic_CreateVisualEffect(D_8005685A, D_8005685C, obj->x, y, obj->z, obj->rot, t, &enemy_temp_vec, obj);
    Effect_StartConvergeEmitter(2, 0x1E, obj->x, obj->unk64->unk1C * obj->scale + y, obj->z,
                  obj->unk64->unk18 * obj->scale * 3.6);
}

void Enemy_ClearAttackScript(void) {
    enemy_script_cmd = 0;
}

void Enemy_StartAttackScript(s32 arg0, s32 arg1) {
    ((Unk8007C060 *)&enemy_script_time)->unk0 = 0;
    ((Unk8007C060 *)&enemy_script_time)->unk4 = enemy_attack_scripts[arg0];
    ((Unk8007C060 *)&enemy_script_time)->unk8 = arg1;
    ((Unk8007C060 *)&enemy_script_time)->unkC = &enemy_slots[0].actor;
}

#ifdef NON_MATCHING
/* &enemy_script_time kept in a register for the ++ shifts the temporaries by one (register allocation); code is equivalent */
void Enemy_RunAttackScript(void) {
    EnemyScriptCmd *e;
    f32 x;
    f32 y;
    f32 z;
    f32 s;
    u16 m;
    s32 pad2;
    Actor *obj;
    s32 pad3;
    s32 pad4;
    SpawnDef *d;
    Unk800C18D8 *t;
    Enemy *en = enemy_slots;

    if (enemy_script_cmd != NULL) {
        e = enemy_script_cmd;
        if (e->time < ++enemy_script_time) {
            obj = enemy_script_obj;
            if (e->flags & 8) {
                enemy_temp_vec.x = e->unk8;
                enemy_temp_vec.y = e->unk10;
                Math_RotateVec2(obj->rot, &enemy_temp_vec);
                en->unk20 = enemy_temp_vec.x;
                en->unk24 = enemy_temp_vec.y;
            } else {
                d = &((SpawnDef *) &enemy_effect_defs)[e->unk2];
                t = &D_800C18D8[d->unk0];
                enemy_temp_vec.x = e->unk8;
                enemy_temp_vec.y = e->unk10;
                Math_RotateVec2(obj->rot + e->unk14, &enemy_temp_vec);
                if (e->flags & 2) {
                    x = D_8007AA20;
                    y = D_8007AA24;
                    z = D_8007AA28;
                } else {
                    x = obj->x;
                    y = obj->y;
                    z = obj->z;
                }
                s = obj->scale;
                x += enemy_temp_vec.x * s;
                y += e->unkC * s;
                z += enemy_temp_vec.y * s;
                enemy_temp_vec.x = d->unk8;
                enemy_temp_vec.y = d->unkC;
                m = enemy_script_enemy->unk1C->unk0;
                if (m & 0x8000) {
                    enemy_temp_vec.z = D_800C185C[(m >> 8) & 0xF][m & 0xFF].unk1C;
                } else {
                    enemy_temp_vec.z = obj->unk28;
                }
                Magic_CreateVisualEffect(d->unk2, d->unk4, x, y, z, obj->rot + e->unk14, t, &enemy_temp_vec, obj);
            }
            if (e->flags & 4) {
                Camera_Shake(1);
            }
            if (e->flags & 1) {
                enemy_script_cmd = NULL;
            } else {
                enemy_script_cmd++;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/enemy/enemy/Enemy_RunAttackScript.s")
#endif

/* .data 8004DD20..8004DD50 */
EnemyStateFunc enemy_state_handlers[6] = {
    (EnemyStateFunc) Enemy_StateIdle,
    (EnemyStateFunc) Enemy_StateApproach,
    (EnemyStateFunc) Enemy_StateHurt,
    (EnemyStateFunc) Enemy_StateFacePlayer,
    (EnemyStateFunc) Enemy_StateMeleeAttack,
    (EnemyStateFunc) Enemy_StateCastSpell,
};
s32 enemy_element_bits[5] = { 1, 2, 4, 8, 0x10 };
