#include "common.h"

/*
 * Battle setup, encounter placement, turn order, camera transition, and completion.
 * Folder: src/game/battle/
 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ char unk8[0x18 - 0x8];
} Struct_8001FD44;

typedef struct {
    /* 0x00 */ Struct_8001FD44* unk0;
    /* 0x04 */ s32 unk4;
} Struct_8007C284_30;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} Struct_8001FE08;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Struct_8001FF10_C;

typedef struct {
    /* 0x00 */ Struct_8001FF10_C* unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
} Struct_8001FF10_8;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} Struct_8001FF10_Pos;

typedef struct {
    /* 0x00 */ Struct_8001FF10_Pos** unk0;
    /* 0x04 */ Struct_8001FF10_8* unk4;
    /* 0x08 */ Struct_8001FE08* unk8;
    /* 0x0C */ s32 unkC;
} Struct_8007C284_34;

typedef struct {
    char unk0[0x30];
    Struct_8007C284_30* unk30;
    Struct_8007C284_34* unk34;
} Struct_8007C284;

extern Struct_8007C284* map_area_def;

/* This file's .bss, 8008BE40..8008BFC0, in address order (first declaration fixes the order). */
Struct_8001FF10_Pos battle_rotated_offset_scratch;
u16 battle_camera_phase;
u16 battle_camera_phase_timer;
u16 battle_camera_enemy_index;
u16 battle_flags; /* bit 0x1: in battle; 0x2: enemy turn; 0x100: boss encounter */
u16 battle_turn_delay;
s16 D_8008BE56;
u16 battle_turn_order_index;
u16 battle_enemy_count;
f32 battle_center_x;
f32 battle_center_z;
f32 battle_active_enemy_x;
f32 battle_active_enemy_z;
f32 battle_arena_radius;
u8 D_8008BE70[0x100]; /* unreferenced */
void* battle_spawned_actor_ptrs[8];
u32 battle_spawned_actor_count;
s16 battle_outer_ring_slot;
u16 battle_turn_ring_slot;
Struct_8007C284_30* battle_encounter_region_table;
Struct_8007C284_34* battle_encounter_group_table;
void* D_8008BFA0;
void* D_8008BFA4;
s32 battle_boss_index_plus_one;
f32 battle_travel_accumulator;
u16 battle_encounter_roll_limit;
extern s32 map_subarea;
extern u16 map_subarea_flags;

u32 Math_Rand(u32);

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x000 */ char unk0[0xA];
    /* 0x00A */ u16 unkA;
    /* 0x00C */ char unkC[0x10 - 0xC];
    /* 0x010 */ f32 unk10;
    /* 0x014 */ char unk14[0x28 - 0x14];
    /* 0x028 */ struct Struct_Stats* unk28;
    /* 0x02C */ char unk2C[0x7C - 0x2C];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ char unk7E[0x130 - 0x7E];
} Struct_8007B908;

extern Struct_8007B908 enemy_slots[];
extern u16 enemy_turn_order[];

void Magic_StepActorStatusTimers(Vec3f*);
void Effect_FadeRing(u16, f32, f32, f32);


extern f32 battle_boss_arena_radii[];
extern s32 enemy_count;
extern Struct_8007B908 enemy_slots[];
extern void* enemy_anim_tables;
extern void* enemy_names;
extern s32 boss_field_index;
extern f32 D_8007C174;
extern f32 D_8007C178;
extern f32 D_8007C17C;
extern f32 D_8007C184;
extern u8 D_803ABA58[];
extern u8 D_803AC3F8[];

void Player_InitBattle(void);
void Enemy_SortTurnOrder(void);
void Enemy_ClearAttackScript(void);
void Boss_Spawn(s32, f32, f32, f32, Struct_8007B908*);
s16 Effect_CreateTerrainRing(u16, f32, f32, f32, f32);
void Hud_ResetPopups(void);
void Bgm_Play(s8);

void Battle_ResetState(void) {
    battle_flags &= 0x8000;
    battle_travel_accumulator = 0.0f;
    battle_encounter_roll_limit = 0;
    if (map_subarea_flags & 1) {
        if (map_area_def->unk30 != NULL) {
            battle_encounter_region_table = &map_area_def->unk30[map_subarea];
            battle_encounter_group_table = &map_area_def->unk34[map_subarea];
            return;
        }
        battle_encounter_region_table = NULL;
        battle_encounter_group_table = NULL;
    }
}

typedef struct Struct_Stats {
    /* 0x00 */ char unk0[0xC];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ char unkE[0x34 - 0xE];
    /* 0x34 */ u8 unk34;
} Struct_Stats;

typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ char unk10[0x14 - 0x10];
    /* 0x14 */ Struct_Stats* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Struct_8007AA08;

extern Struct_8007AA08 player_state;
extern f32 player_move_dist;
extern u16 D_8007AA80;
Struct_8001FD44* Battle_FindEncounterRegion(f32 x, f32 y, Struct_8007C284_30* list);
Struct_8001FE08* Battle_ChooseNearbyEncounterPoint(f32 x, f32 y);
void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16* list);
f32 Math_Atan2(f32, f32);

void Battle_TryStartRandomEncounter(void) {
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 ang;
    Struct_8001FD44* area;
    Struct_8001FE08* pt;

    if (!(battle_flags & 1) && !(battle_flags & 0x8000) && !(D_8007AA80 & 1) && (player_move_dist != 0.0f)) {
        battle_travel_accumulator += player_move_dist;
        if (battle_travel_accumulator >= 50.0) {
            battle_encounter_roll_limit += 50;
            if (Math_Rand(2000) < battle_encounter_roll_limit) {
                x = player_state.unk18;
                y = player_state.unk20;
                pt = Battle_ChooseNearbyEncounterPoint(x, y);
                if (pt != NULL) {
                    area = Battle_FindEncounterRegion(x, y, battle_encounter_region_table);
                    if (area != NULL) {
                        battle_encounter_roll_limit = 0;
                        dx = x - pt->unk0;
                        dy = y - pt->unk2;
                        ang = Math_Atan2(dx, dy);
                        Battle_SpawnEncounterGroup(pt->unk0, pt->unk2, ang, (u16*)area->unk8);
                        battle_center_x = pt->unk0;
                        battle_center_z = pt->unk2;
                        battle_flags = 0x205;
                        D_8008BE56 = 0;
                        battle_turn_delay = 20;
                        if (player_state.unk14->unkC < enemy_slots[enemy_turn_order[0]].unk28->unkC) {
                            battle_turn_order_index = 0;
                            battle_flags |= 2;
                        } else {
                            battle_turn_order_index = battle_enemy_count - 1;
                        }
                        Player_InitBattle();
                        Hud_ResetPopups();
                        battle_arena_radius = 100.0f;
                        battle_outer_ring_slot = Effect_CreateTerrainRing(0, battle_center_x, player_state.unk1C, battle_center_z, battle_arena_radius * 1.04);
                        battle_camera_phase = 0;
                        battle_camera_phase_timer = 1;
                        battle_camera_enemy_index = Math_Rand(enemy_count);
                        Bgm_Play(13);
                    }
                }
            }
            battle_travel_accumulator = 0.0f;
        }
    }
}

void Battle_StartBossEncounter(void) {
    s32 v;

    if (boss_field_index == 7) {
        battle_center_x = 0.0f;
        battle_center_z = 0.0f;
    } else {
        battle_center_x = D_8007C174;
        battle_center_z = D_8007C17C;
    }
    battle_flags = 0x305;
    D_8008BE56 = 0;
    battle_turn_delay = 0;
    D_8008BFA0 = enemy_anim_tables;
    D_8008BFA4 = enemy_names;
    battle_boss_index_plus_one = boss_field_index;
    enemy_anim_tables = D_803ABA58;
    enemy_names = D_803AC3F8;
    Boss_Spawn(boss_field_index - 1, battle_center_x, battle_center_z, D_8007C184, enemy_slots);
    Enemy_ClearAttackScript();
    boss_field_index = 0;
    battle_enemy_count = enemy_count = 1;
    Enemy_SortTurnOrder();
    battle_spawned_actor_count = 1;
    battle_spawned_actor_ptrs[0] = enemy_slots[0].unk2C;
    battle_camera_phase = 1;
    battle_camera_phase_timer = 1;
    battle_camera_enemy_index = 0;
    battle_turn_order_index = battle_enemy_count - 1;
    if (battle_boss_index_plus_one != 8) {
        v = 0;
    } else {
        v = 0x29;
    }
    Bgm_Play(v);
    Player_InitBattle();
    Hud_ResetPopups();
    battle_arena_radius = battle_boss_arena_radii[battle_boss_index_plus_one - 1];
    battle_outer_ring_slot = Effect_CreateTerrainRing(0, battle_center_x, D_8007C178, battle_center_z, battle_arena_radius * 1.04);
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x2C - 0x18];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ char unk30[0x3C - 0x30];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ char unk50[0x58 - 0x50];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ char unk60[0x70 - 0x60];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ char unk74[0x80 - 0x74];
    /* 0x80 */ void* unk80;
} Struct_80085E48;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Struct_8004F0B0;

extern Struct_80085E48 camera_state;
extern Struct_8004F0B0 battle_camera_offsets[];
extern f32 D_80085F78;
extern f32 camera_battle_angle_offset;
extern s32 camera_preset_index;
extern s32 map_id;
void Math_RotateVec2(f32, Struct_8001FF10_Pos*);
void Camera_SetPreset(s32);

typedef struct Actor {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x24 - 0xC];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x60 - 0x28];
    /* 0x60 */ u16 unk60;
    /* 0x64 */ struct { char unk0[0x18]; f32 unk18; f32 unk1C; }* unk64;
    /* 0x68 */ struct { char unk0[0x90]; f32 unk90; }* unk68;
} Actor;

extern Actor D_8007AA20;

void Battle_UpdateStartCamera(void) {
    f32 dx;
    f32 dz;
    f32 ang;
    Actor* a;

    switch (battle_camera_phase) {
        case 0:
            a = (Actor*)enemy_slots[battle_camera_enemy_index].unk2C;
            dx = a->unk0 - player_state.unk18;
            dz = a->unk8 - player_state.unk20;
            ang = Math_Atan2(dx, dz);
            if (Math_Rand(100) > 50) {
                ang += 3.141592653589793;
                if (ang < -3.141592653589793) {
                    ang += 6.283185307179586;
                } else if (ang > 3.141592653589793) {
                    ang -= 6.283185307179586;
                }
            }
            ang += 0.39269908169872414;
            if (ang < -3.141592653589793) {
                ang += 6.283185307179586;
            } else if (ang > 3.141592653589793) {
                ang -= 6.283185307179586;
            }
            battle_rotated_offset_scratch.unk0 = 0.0f;
            if (a->unk64->unk1C < a->unk64->unk18) {
                battle_rotated_offset_scratch.unk4 = a->unk64->unk18 * a->unk24 * 2.0 + 15.0;
            } else {
                battle_rotated_offset_scratch.unk4 = a->unk64->unk1C * a->unk24 * 2.0 + 15.0;
            }
            camera_state.unk4C = battle_rotated_offset_scratch.unk4 * 1.5;
            Math_RotateVec2(ang, &battle_rotated_offset_scratch);
            camera_state.unkC = a->unk0 + battle_rotated_offset_scratch.unk0;
            camera_state.unk14 = a->unk8 + battle_rotated_offset_scratch.unk4;
            camera_state.unk10 = a->unk4 + 15.0;
            if (camera_state.unk10 < player_state.unk1C) {
                camera_state.unk10 = player_state.unk1C;
            }
            camera_state.unk48 = 0.0f;
            camera_state.unk0 = 0;
            camera_state.unk3C = 0.0f;
            camera_state.unk44 = camera_state.unk48;
            camera_state.unk40 = camera_state.unk44;
            camera_state.unk58 = 15.0f;
            camera_state.unk80 = a;
            camera_state.unk70 = 0.01f;
            D_80085F78 = camera_state.unk2C;
            battle_camera_phase++;
            battle_camera_phase_timer = 60;
            break;
        case 1:
            if (--battle_camera_phase_timer == 0) {
                battle_flags &= ~0x200;
                Camera_SetPreset(camera_preset_index);
                dx = battle_center_x - player_state.unk18;
                dz = battle_center_z - player_state.unk20;
                ang = Math_Atan2(dx, dz) + 3.141592653589793;
                if (ang > 3.141592653589793) {
                    ang -= 6.283185307179586;
                } else if (ang < -3.141592653589793) {
                    ang += 6.283185307179586;
                }
                battle_rotated_offset_scratch.unk0 = 0.0f;
                battle_rotated_offset_scratch.unk4 = 50.0f;
                Math_RotateVec2(ang, &battle_rotated_offset_scratch);
                camera_state.unk0 = 4;
                camera_state.unk8 |= 0x10;
                camera_state.unkC = player_state.unk18 + battle_rotated_offset_scratch.unk0;
                camera_state.unk48 = 0.0f;
                camera_state.unk10 = player_state.unk1C + 30.0;
                camera_state.unk14 = player_state.unk20 + battle_rotated_offset_scratch.unk4;
                camera_state.unk44 = camera_state.unk48;
                camera_state.unk3C = 0.0f;
                camera_state.unk40 = camera_state.unk44;
                if ((battle_flags & 0x100) && battle_boss_index_plus_one == 8) {
                    camera_state.unk58 = 50.0f;
                    camera_state.unk5C = 28.0f;
                    camera_state.unk4C = 180.0f;
                } else {
                    camera_state.unk58 += battle_camera_offsets[map_id].unk0;
                    camera_state.unk4C += battle_camera_offsets[map_id].unk4;
                }
                camera_state.unk80 = &D_8007AA20;
                camera_state.unk70 = 0.02f;
                camera_battle_angle_offset = 0.0f;
            }
            break;
    }
}


extern Actor D_8007AA20;
extern s32 player_battle_drop_item;
extern s32 camera_preset_index;
extern s32 map_id;
extern s16 hud_battle_message_timer;

void Boss_SetDefeated(u16);
void Boss_HandleDefeat(s32);
void Enemy_RemoveAll(void);
void Camera_SetPresetDelayedTurn(s32);
void Enemy_StartTurn(void);
s32 func_800200F8(void);
void Bgm_PlayDelayed(s32, s32);
void Bgm_PlayForMap(s32, s32, s32);

void Battle_UpdateTurnTransition(void) {
    s32 done;
    f32 f;
    Actor* a;

    if (battle_flags & 4) {
        if (battle_turn_delay != 0) {
            battle_turn_delay--;
            return;
        }
        if (battle_flags & 2) {
            a = (Actor*)enemy_slots[enemy_turn_order[battle_turn_order_index]].unk2C;
        } else {
            a = &D_8007AA20;
        }
        if (!(a->unk60 & 1)) {
            done = 0;
            if (enemy_count == 0 || (battle_flags & 0x400)) {
                battle_flags |= 8;
                done = 1;
                if (battle_flags & 0x100) {
                    Boss_SetDefeated(battle_boss_index_plus_one - 1);
                    Boss_HandleDefeat(battle_boss_index_plus_one - 1);
                    enemy_anim_tables = D_8008BFA0;
                    enemy_names = D_8008BFA4;
                }
                player_battle_drop_item = func_800200F8();
            } else if (battle_flags & 0x10) {
                done = 1;
            } else if (!(battle_flags & 0x100) && (player_state.unk8 & 0x20)) {
                battle_flags |= 0x10;
                done = 1;
            }
            if (done) {
                battle_flags &= ~1;
                hud_battle_message_timer = 0;
                Effect_FadeRing(battle_outer_ring_slot, player_state.unk18, player_state.unk1C, player_state.unk20);
                Enemy_RemoveAll();
                Camera_SetPresetDelayedTurn(camera_preset_index);
                if (battle_flags & 0x100) {
                    battle_flags &= ~0x100;
                }
                if (battle_flags & 0x10) {
                    Bgm_PlayForMap(map_id, map_subarea, 0);
                } else {
                    Bgm_PlayDelayed(0x2B, 8);
                }
                return;
            }
            battle_flags &= ~4;
            if (battle_flags & 2) {
                Enemy_StartTurn();
            }
            battle_active_enemy_x = a->unk0;
            battle_active_enemy_z = a->unk8;
            if (battle_flags & 2) {
                f = enemy_slots[enemy_turn_order[battle_turn_order_index]].unk10;
            } else {
                f = player_state.unkC;
            }
            if (battle_flags & 2) {
                a = (Actor*)enemy_slots[enemy_turn_order[battle_turn_order_index]].unk2C;
            } else {
                a = &D_8007AA20;
            }
            f *= a->unk68->unk90;
            f += a->unk64->unk18 * a->unk24;
            battle_turn_ring_slot = Effect_CreateTerrainRing((battle_flags & 2) ? 1 : 2, battle_active_enemy_x, a->unk4, battle_active_enemy_z, f * 1.04);
        }
    }
}

void Battle_EndTurn(Vec3f* arg0) {
    s32 n;
    s32 max; s32 id;
    Struct_8007B908* e;

    Magic_StepActorStatusTimers(arg0);
    if (battle_flags & 1) {
        if (!(battle_flags & 2)) {
            n = battle_enemy_count;
            while (n != 0) {
                battle_turn_order_index++;
                max = battle_enemy_count;
                if (battle_turn_order_index >= max) {
                    battle_turn_order_index = 0;
                }
                e = &enemy_slots[id = enemy_turn_order[battle_turn_order_index]];
                if (e->unkA != 0 && e->unk7C != -1) {
                    break;
                }
                n--;
            }
            if (n == 0) {
                battle_flags |= 0x400;
            }
            battle_turn_delay = 0x14;
        } else {
            battle_turn_delay = 0;
        }
        Effect_FadeRing(battle_turn_ring_slot, arg0->x, arg0->y, arg0->z);
        battle_flags ^= 2;
        battle_flags |= 4;
    }
}

Struct_8001FD44* Battle_FindEncounterRegion(f32 x, f32 y, Struct_8007C284_30* list) {
    Struct_8001FD44* r = NULL;
    s32 n;

    if (list != NULL) {
        n = list->unk4;
        r = list->unk0;
        while (n != 0) {
            if (r->unk0 <= x && r->unk2 <= y && x - r->unk0 <= r->unk4 && y - r->unk2 <= r->unk6) {
                break;
            }
            n--;
            r++;
        }
        if (n == 0) {
            r = NULL;
        }
    }
    return r;
}

Struct_8001FE08* Battle_ChooseNearbyEncounterPoint(f32 x, f32 y) {
    s32 n;
    Struct_8001FE08* p;
    s32 cnt;
    f32 dx;
    f32 dy;
    f32 d;
    Struct_8001FE08* cands[6];

    n = 0;

    if (battle_encounter_group_table != NULL) {
        cnt = battle_encounter_group_table->unkC;
        p = battle_encounter_group_table->unk8;
        while (n < 6 && cnt != 0) {
            cnt--;
            dx = p->unk0 - x;
            dy = p->unk2 - y;
            d = dx * dx + dy * dy;
            if (d >= 2500.0f && d <= 8100.0f) {
                cands[n++] = p;
            }
            p++;
        }
        if (n == 0) {
            p = NULL;
        } else {
            p = cands[Math_Rand(n)];
        }
    } else {
        p = NULL;
    }
    return p;
}

void Math_RotateVec2(f32, Struct_8001FF10_Pos*);
void Enemy_Spawn(s32, f32, f32, f32, void*, Struct_8007B908*);

void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16* list) {
    Struct_8001FF10_8* e;
    s32 n;
    Struct_8001FF10_C* p;
    Struct_8001FF10_Pos* pos;
    Struct_8007B908* actor;
    s32 (*o)[2];
    s32 cnt;
    s32 out[8][2];

    cnt = Math_Rand(*list++);
    e = &battle_encounter_group_table->unk4[list[cnt]];
    pos = &(*battle_encounter_group_table->unk0)[e->unk6];
    n = e->unk4;
    p = e->unk0;
    actor = enemy_slots;
    o = out;
    battle_spawned_actor_count = 0;
    while (n != 0) {
        cnt = p->unk4;
        if (p->unk8 != 0) {
            cnt += Math_Rand(p->unk8 + 1);
        }
        (*o)[0] = p->unk0;
        (*o)[1] = cnt;
        o++;
        enemy_count += cnt;
        battle_spawned_actor_ptrs[battle_spawned_actor_count++] = &actor->unk2C;
        while (cnt != 0) {
            battle_rotated_offset_scratch.unk0 = pos->unk0;
            battle_rotated_offset_scratch.unk4 = pos->unk4;
            Math_RotateVec2(z, &battle_rotated_offset_scratch);
            Enemy_Spawn(p->unk0, x + battle_rotated_offset_scratch.unk0, y + battle_rotated_offset_scratch.unk4, z, &actor->unk2C, actor);
            cnt--;
            actor++;
            pos++;
        }
        n--;
        p++;
    }
    Enemy_SortTurnOrder();
    battle_enemy_count = enemy_count;
}

void func_800200F0(void) {
}

s32 func_800200F8(void) {
    s32 r;

    if (player_state.unk8 & 0x2000) {
        r = 3;
    } else {
        r = 4;
    }
    if ((battle_flags & 0x100) || Math_Rand(r) == 0) {
        r = enemy_slots[Math_Rand(battle_enemy_count)].unk28->unk34;
    } else {
        r = 0xFF;
    }
    return r;
}

void func_8002018C(void) {
}

/* .data 8004F0B0..8004F2C0 */
Struct_8004F0B0 battle_camera_offsets[36] = {
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 40.0f, 50.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
    { 30.0f, 40.0f, 0.0f },
};
/* Two message strings that nothing references by address. */
u8 D_8004F260[0x24] = {
#include "assets/D_8004F260.inc.c"
};
u8 D_8004F284[0x1C] = {
#include "assets/D_8004F284.inc.c"
};
f32 battle_boss_arena_radii[8] = { 85.0f, 140.0f, 100.0f, 150.0f, 150.0f, 100.0f, 100.0f, 190.0f };
