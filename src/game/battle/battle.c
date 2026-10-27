#include "common.h"
#include "game/battle/battle.h"
#include "game/actor/actor.h"
#include "game/math/math.h"
#include "game/map/map.h"
#include "game/camera/camera.h"
#include "game/player/player.h"
#include "game/enemy/enemy.h"
#include "game/enemy/boss.h"
#include "game/magic/magic.h"
#include "game/gfx/effect.h"
#include "game/ui/hud.h"
#include "game/audio/sound.h"

/*
 * Battle setup, encounter placement, turn order, camera transition, and completion.
 * Original file: 1FA00.c (ROM 0x1FA00).
 */

/* This file's .bss, 8008BE40..8008BFC0, in address order (first declaration fixes the order). */
Vec3f battle_temp_vec;
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
f32 battle_turn_origin_x;
f32 battle_turn_origin_z;
f32 battle_arena_radius;
u8 D_8008BE70[0x100]; /* unreferenced */
void* D_8008BF70[8];
u32 D_8008BF90;
s16 battle_outer_ring_slot;
u16 battle_turn_ring_slot;
EncounterRegionList* battle_encounter_region_table;
EncounterGroupTable* battle_encounter_group_table;
void* battle_saved_enemy_anim_tables;
void* battle_saved_enemy_names;
s32 battle_boss_index_plus_one;
f32 battle_travel_accumulator;
u16 battle_encounter_roll_limit;

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

void Battle_TryStartRandomEncounter(void) {
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 ang;
    EncounterRegion* area;
    EncounterPoint* pt;

    if (!(battle_flags & 1) && !(battle_flags & 0x8000) && !(player_state.actor.unk60 & 1) && (player_move_dist != 0.0f)) {
        battle_travel_accumulator += player_move_dist;
        if (battle_travel_accumulator >= 50.0) {
            battle_encounter_roll_limit += 50;
            if (Math_Rand(2000) < battle_encounter_roll_limit) {
                x = player_state.actor.x;
                y = player_state.actor.z;
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
                        battle_outer_ring_slot = Effect_CreateTerrainRing(0, battle_center_x, player_state.actor.y, battle_center_z, battle_arena_radius * 1.04);
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
        battle_center_x = boss_field_record.actor.x;
        battle_center_z = boss_field_record.actor.z;
    }
    battle_flags = 0x305;
    D_8008BE56 = 0;
    battle_turn_delay = 0;
    battle_saved_enemy_anim_tables = enemy_anim_tables;
    battle_saved_enemy_names = enemy_names;
    battle_boss_index_plus_one = boss_field_index;
    enemy_anim_tables = D_803ABA58;
    enemy_names = D_803AC3F8;
    Boss_Spawn(boss_field_index - 1, battle_center_x, battle_center_z, boss_field_record.actor.rot, enemy_slots);
    Enemy_ClearAttackScript();
    boss_field_index = 0;
    battle_enemy_count = enemy_count = 1;
    Enemy_SortTurnOrder();
    D_8008BF90 = 1;
    D_8008BF70[0] = &enemy_slots[0].actor;
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
    battle_outer_ring_slot = Effect_CreateTerrainRing(0, battle_center_x, boss_field_record.actor.y, battle_center_z, battle_arena_radius * 1.04);
}

void Battle_UpdateStartCamera(void) {
    f32 dx;
    f32 dz;
    f32 ang;
    Actor* a;

    switch (battle_camera_phase) {
        case 0:
            a = &enemy_slots[battle_camera_enemy_index].actor;
            dx = a->x - player_state.actor.x;
            dz = a->z - player_state.actor.z;
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
            battle_temp_vec.x = 0.0f;
            if (a->unk64->unk1C < a->unk64->unk18) {
                battle_temp_vec.y = a->unk64->unk18 * a->scale * 2.0 + 15.0;
            } else {
                battle_temp_vec.y = a->unk64->unk1C * a->scale * 2.0 + 15.0;
            }
            camera_state.distance = battle_temp_vec.y * 1.5;
            Math_RotateVec2(ang, (Vec2f*)&battle_temp_vec);
            camera_state.eyeX = a->x + battle_temp_vec.x;
            camera_state.eyeZ = a->z + battle_temp_vec.y;
            camera_state.eyeY = a->y + 15.0;
            if (camera_state.eyeY < player_state.actor.y) {
                camera_state.eyeY = player_state.actor.y;
            }
            camera_state.eyeVelZ = 0.0f;
            camera_state.mode = 0;
            camera_state.orbitSpeed = 0.0f;
            camera_state.eyeVelY = camera_state.eyeVelZ;
            camera_state.eyeVelX = camera_state.eyeVelY;
            camera_state.eyeHeight = 15.0f;
            camera_state.target = a;
            camera_state.unk70 = 0.01f;
            camera_delayed_turn.orbitAngle = camera_state.yaw;
            battle_camera_phase++;
            battle_camera_phase_timer = 60;
            break;
        case 1:
            if (--battle_camera_phase_timer == 0) {
                battle_flags &= ~0x200;
                Camera_SetPreset(camera_preset_index);
                dx = battle_center_x - player_state.actor.x;
                dz = battle_center_z - player_state.actor.z;
                ang = Math_Atan2(dx, dz) + 3.141592653589793;
                if (ang > 3.141592653589793) {
                    ang -= 6.283185307179586;
                } else if (ang < -3.141592653589793) {
                    ang += 6.283185307179586;
                }
                battle_temp_vec.x = 0.0f;
                battle_temp_vec.y = 50.0f;
                Math_RotateVec2(ang, (Vec2f*)&battle_temp_vec);
                camera_state.mode = 4;
                camera_state.flags |= 0x10;
                camera_state.eyeX = player_state.actor.x + battle_temp_vec.x;
                camera_state.eyeVelZ = 0.0f;
                camera_state.eyeY = player_state.actor.y + 30.0;
                camera_state.eyeZ = player_state.actor.z + battle_temp_vec.y;
                camera_state.eyeVelY = camera_state.eyeVelZ;
                camera_state.orbitSpeed = 0.0f;
                camera_state.eyeVelX = camera_state.eyeVelY;
                if ((battle_flags & 0x100) && battle_boss_index_plus_one == 8) {
                    camera_state.eyeHeight = 50.0f;
                    camera_state.atHeight = 28.0f;
                    camera_state.distance = 180.0f;
                } else {
                    camera_state.eyeHeight += battle_camera_offsets[map_id].unk0;
                    camera_state.distance += battle_camera_offsets[map_id].unk4;
                }
                camera_state.target = &player_state.actor;
                camera_state.unk70 = 0.02f;
                camera_battle_angle_offset = 0.0f;
            }
            break;
    }
}

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
            a = &enemy_slots[enemy_turn_order[battle_turn_order_index]].actor;
        } else {
            a = &player_state.actor;
        }
        if (!(a->unk60 & 1)) {
            done = 0;
            if (enemy_count == 0 || (battle_flags & 0x400)) {
                battle_flags |= 8;
                done = 1;
                if (battle_flags & 0x100) {
                    Boss_SetDefeated(battle_boss_index_plus_one - 1);
                    Boss_HandleDefeat(battle_boss_index_plus_one - 1);
                    enemy_anim_tables = battle_saved_enemy_anim_tables;
                    enemy_names = battle_saved_enemy_names;
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
                hud_enemy_info_timer = 0;
                Effect_FadeRing((u16)battle_outer_ring_slot, player_state.actor.x, player_state.actor.y, player_state.actor.z);
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
            battle_turn_origin_x = a->x;
            battle_turn_origin_z = a->z;
            if (battle_flags & 2) {
                f = enemy_slots[enemy_turn_order[battle_turn_order_index]].unk10;
            } else {
                f = player_state.unkC;
            }
            if (battle_flags & 2) {
                a = &enemy_slots[enemy_turn_order[battle_turn_order_index]].actor;
            } else {
                a = &player_state.actor;
            }
            f *= a->unk68->unk90;
            f += a->unk64->unk18 * a->scale;
            battle_turn_ring_slot = Effect_CreateTerrainRing((battle_flags & 2) ? 1 : 2, battle_turn_origin_x, a->y, battle_turn_origin_z, f * 1.04);
        }
    }
}

void Battle_EndTurn(Actor* arg0) {
    s32 n;
    s32 max; s32 id;
    Enemy* e;

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
                if (e->unkA != 0 && e->actor.unk50 != -1) {
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

EncounterRegion* Battle_FindEncounterRegion(f32 x, f32 y, EncounterRegionList* list) {
    EncounterRegion* r = NULL;
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

EncounterPoint* Battle_ChooseNearbyEncounterPoint(f32 x, f32 y) {
    s32 n;
    EncounterPoint* p;
    s32 cnt;
    f32 dx;
    f32 dy;
    f32 d;
    EncounterPoint* cands[6];

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


void Battle_SpawnEncounterGroup(f32 x, f32 y, f32 z, u16* list) {
    EncounterGroup* e;
    s32 n;
    EncounterGroupEntry* p;
    Vec3f* pos;
    Enemy* actor;
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
    D_8008BF90 = 0;
    while (n != 0) {
        cnt = p->unk4;
        if (p->unk8 != 0) {
            cnt += Math_Rand(p->unk8 + 1);
        }
        (*o)[0] = p->unk0;
        (*o)[1] = cnt;
        o++;
        enemy_count += cnt;
        D_8008BF70[D_8008BF90++] = &actor->actor;
        while (cnt != 0) {
            battle_temp_vec.x = pos->x;
            battle_temp_vec.y = pos->y;
            Math_RotateVec2(z, (Vec2f*)&battle_temp_vec);
            Enemy_Spawn(p->unk0, x + battle_temp_vec.x, y + battle_temp_vec.y, z, &actor->actor, actor);
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
BattleCameraOffset battle_camera_offsets[36] = {
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
