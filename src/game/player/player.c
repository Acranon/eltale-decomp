#include "common.h"
#include "game/player/player.h"
#include "game/actor/anim.h"
#include "game/audio/audio.h"
#include "game/audio/sound.h"
#include "game/battle/battle.h"
#include "game/camera/camera.h"
#include "game/core/dma.h"
#include "game/core/main.h"
#include "game/enemy/boss.h"
#include "game/enemy/enemy.h"
#include "game/env/env.h"
#include "game/gfx/effect.h"
#include "game/gfx/fade.h"
#include "game/gfx/shadow.h"
#include "game/gfx/sprite_effect.h"
#include "game/input/input.h"
#include "game/item/item.h"
#include "game/magic/magic.h"
#include "game/map/chest.h"
#include "game/map/collision.h"
#include "game/map/map.h"
#include "game/map/spirit.h"
#include "game/map/textspot.h"
#include "game/math/math.h"
#include "game/npc/npc.h"
#include "game/text/text_window.h"
#include "game/ui/hud.h"
#include "game/ui/menu.h"

/*
 * Player actor: init/spawn, per-frame update and draw, the state machine (move, talk, chest,
 * item, exits, melee attack, spell input and casting, hurt, death, battle start/won),
 * movement and collision, damage taken and dealt, stat growth from XP.
 *
 * A player_char_data entry is an AnimSet array that PlayerAnimTable reads as one record; the
 * (AnimSet *) casts of it reinterpret it back. player_temp_vec is a Vec3f whose x,y pair is a
 * ground-plane (x, z) vector for Math_RotateVec2 (the (Vec2f *) casts).
 * Original file: 3F50.c (ROM 0x3F50).
 */

/* The player data block: ROM symbols, the anim buffer and the display list Player_Init and
 * Player_Draw use (no C module declares them). */
extern u8 D_869620[];
extern u8 D_86F6F0[];
extern u8 D_80206000[];
extern u8 D_10000A0[];
/* The item table (item.c's D_803AAAA0: a fixed address in the item block, item.h does not
 * declare it). */
extern ItemDef D_803AAAA0[];

/* This file's .bss, 8007A8F0..8007AB70, in address order. IDO lays .bss out
 * in the order names are first declared: that is player.h's extern list, which
 * keeps the same order. Labels inside these objects (fields of player_stats,
 * player_state, ...) are aliases in undefined_syms.txt. D_8007A90E, D_8007A914,
 * D_8007A924, D_8007A944/48, D_8007A9B2, D_8007AB54..5C are unreferenced gaps. */
f32 player_mp_regen_dist;
f32 D_8007A8F4;
f32 D_8007A8F8;
f32 player_agility_dist_enemy_area;
f32 player_agility_dist_npc_area;
s32 player_near_boss;
s32 player_boss_text_delay;
u16 player_run_sfx_timer;
u16 D_8007A90E;
s32 player_idle_anim;
s32 D_8007A914;
Vec3f player_temp_vec;
s32 D_8007A924;
CollResult player_coll;
s32 D_8007A944;
u8 D_8007A948[0x40]; /* not referenced; the next label is 8007A988 */
f32 player_battle_move_dist;
f32 player_spawn_x;
f32 player_spawn_z;
f32 player_spawn_rot;
s32 player_spawn_type; /* bit 3: start in state 3; bits 8-10: entry kind (Player_Spawn) */
s32 player_spawn_obj;
f32 player_move_dx;
f32 player_move_dz;
f32 player_move_dist;
u16 player_respawn_map;
u16 player_respawn_subarea;
u16 player_respawn_entry;
u16 D_8007A9B2;
s32 player_battle_exp;
s32 player_battle_extra_reward;
s32 player_battle_drop_item;
s32 player_talk_npc;
SpiritObj *player_front_spirit;
Actor *player_front_chest;
TextSpot *player_front_text_spot;
ActorStats player_stats;
Player player_state;
Vec3f player_shadow_pos;
s32 D_8007AB54;
s32 D_8007AB58;
s32 D_8007AB5C;
s32 player_light_slot;



void Player_Init(void) {
    Dma_ReadRom(D_869620, D_80206000, D_86F6F0 - D_869620);
    player_stats = player_default_stats;
    player_state.actor.scale = player_stats.scale;
    player_state.actor.collisionRadius = player_stats.body_radius;
    player_state.actor.animSetIndex = player_stats.anim_set_index;
    player_state.stats = (ActorStats *)&player_stats;
    player_state.unk6 = 0;
    player_state.flags = 0;
    player_state.spell_input_count = 0;
    player_state.actor.animIndex = -1;
    player_state.actor.frame = 0;
    player_state.actor.animStep = 1;
    player_state.actor.stats = &player_stats;
    player_state.actor.battle = &player_state.battle;
    player_state.actor.typeFlags = 0;
    player_state.actor.animFlags = 0;
    player_spawn_type = 0x108;
    player_respawn_map = 0xD;
    player_respawn_subarea = 0x11;
    player_respawn_entry = 0;
    player_battle_move_dist = 0.0f;
    D_8007A8F4 = D_8007A8F8 = 0.0f;
    player_agility_dist_enemy_area = player_agility_dist_npc_area = 0.0f;
}

void Player_Spawn(void) {
    s32 n;
    s32 pad;
    Player *p = &player_state;
    PlayerAnimTable *cd;
    MapObj *pos;

    core_flags &= ~0x10000;
    cd = player_char_data[player_state.actor.animSetIndex];
    player_state.state = 0;
    player_state.unk128 = 0;
    player_state.actor.x = player_spawn_x;
    player_state.actor.y = 0.0f;
    player_state.actor.z = player_spawn_z;
    player_state.actor.rotX = 0.0f;
    player_state.actor.rotZ = 0.0f;
    player_state.actor.rot = player_spawn_rot;
    player_state.actor.vx = 0.0f;
    player_state.actor.unk1C = 0.0f;
    player_state.actor.vz = 0.0f;
    Coll_ResolveFloorAndWalls(player_spawn_x, 0.0f, player_spawn_z, 0xA00, &player_coll);
    p->actor.y = player_coll.y;
    p->actor.nx = player_coll.nx;
    p->actor.ny = player_coll.ny;
    p->actor.nz = player_coll.nz;
    if (player_coll.flags & 0x8000) {
        p->actor.floorFlags = 0;
    } else {
        p->actor.floorFlags = player_coll.flags;
    }
    Anim_SetCurrentAndNext(&player_state.actor, p->unk6 ? p->unk6 : player_idle_anim, 1, player_idle_anim, 1, 1);
    if (player_spawn_type & 8) {
        p->state = 3;
        p->state_timer = 0xF;
        p->actor.animFlags = 1;
    } else {
        switch ((player_spawn_type >> 8) & 7) {
            case 1:
            case 4:
                p->state = 8;
                p->state_timer = 0xF;
                player_temp_vec.x = 0.0f;
                player_temp_vec.y = 20.0f;
                Math_RotateVec2(p->actor.rot, (Vec2f *)&player_temp_vec);
                p->move_step_x = player_temp_vec.x;
                p->move_step_z = player_temp_vec.y;
                p->actor.animFlags = 1;
                Sfx_Play(5, 0x21, 0xFF);
                Sfx_Play(0xF, 0x21, 0xFF);
                break;
            case 2:
                p->state = 10;
                pos = &map_objs[player_spawn_obj];
                p->finish_angle = p->actor.rot = pos->angle * 0.017453292519943295;
                if (player_spawn_type & 1) {
                    p->state_timer = 0x15;
                    p->actor.frame = 0x55;
                    player_temp_vec.x = -115.61f;
                    player_temp_vec.y = 15.746f;
                    n = 0xE;
                } else {
                    p->state_timer = 0x1F;
                    p->finish_angle = p->finish_angle + 3.141592653589793;
                    p->actor.frame = 0x3C;
                    player_temp_vec.x = -132.831f;
                    player_temp_vec.y = -120.681f;
                    n = 0x14;
                }
                Math_RotateVec2(-pos->angle * 0.017453292519943295, (Vec2f *)&player_temp_vec);
                p->actor.x = pos->x - player_temp_vec.x * p->actor.scale;
                p->actor.z = pos->z + player_temp_vec.y * p->actor.scale;
                p->actor.animFlags = 1;
                Player_LoadAnim(&player_state.actor);
                Anim_UpdateRootMotion(&player_state.actor, p->actor.animIndex * 0xC + (s32) cd, p->actor.scale);
                MapObjAnim_Start(1, p->actor.frame, player_spawn_type, pos);
                Sfx_Play(n, 8, 0xFF);
                break;
            case 3:
                p->state = 8;
                p->state_timer = 0xF;
                player_temp_vec.x = 0.0f;
                player_temp_vec.y = 20.0f;
                Math_RotateVec2(p->actor.rot, (Vec2f *)&player_temp_vec);
                p->move_step_x = player_temp_vec.x;
                p->move_step_z = player_temp_vec.y;
                p->actor.animFlags = 1;
                Player_LoadAnim(&player_state.actor);
                Anim_UpdateRootMotion(&player_state.actor, p->actor.animIndex * 0xC + (s32) cd, p->actor.scale);
                MapObjAnim_Start(1, p->actor.frame, player_spawn_type, pos);
                Sfx_Play(5, 0x21, 0xFF);
                Sfx_Play(0xF, 0x21, 0xFF);
                break;
        }
    }
    p->flags = 0;
    if (exit_destination.entry == -1) {
        p->flags |= 0x10;
    }
    if (core_flags & 0x800) {
        p->actor.stats->hp = 1;
        p->actor.stats->mp = p->actor.stats->max_mp;
        p->actor.battle->status_bits = 0;
    }
    p->actor.battle->status_bits = 0;
    player_move_dist = player_mp_regen_dist = 0.0f;
    player_run_sfx_timer = 0;
    player_battle_drop_item = 0xFF;
    player_talk_npc = 0;
    player_front_spirit = 0;
    player_front_chest = 0;
    player_front_text_spot = 0;
    if (p->stats->element_levels[0] == 50) {
        p->flags |= 0x1000;
    }
    if (p->stats->element_levels[1] == 50) {
        p->flags |= 0x2000;
    }
    if (p->stats->element_levels[2] == 50) {
        p->flags |= 0x4000;
    }
    if (p->stats->element_levels[3] == 50) {
        p->flags |= 0x8000;
    }
    if ((p->flags & 0xF000) == 0xF000) {
        p->flags |= 0x10000;
    }
}



void Player_SetSpawnFromSaveTable(void) {
    s32 i;

    player_state.stats->body_radius = 50.0f;
    map_next_id = map_id;
    map_next_subarea = map_subarea;
    exit_destination.entry = 0;
    for (i = 0; i < 17; i++) {
        if (map_id == player_save_spawn_points[i].map_id && map_subarea == player_save_spawn_points[i].subarea) {
            player_spawn_x = player_save_spawn_points[i].x;
            player_spawn_z = player_save_spawn_points[i].y;
            player_spawn_rot = player_save_spawn_points[i].rot;
            exit_destination.entry = -1;
            break;
        }
    }
    map_id = -1;
    map_subarea = -1;
}


void Player_Update(void) {
    Player *p = &player_state;
    s32 pad;
    PlayerAnimTable *cd;
    u8 *s;

    cd = player_char_data[p->actor.animSetIndex];
    if (p->stats->hp * 3 < p->stats->max_hp) {
        player_idle_anim = 0x19;
    } else {
        player_idle_anim = (battle_flags & 1) ? 0x11 : 0;
    }
    player_move_dx = player_move_dz = 0.0f;
    if (!(core_flags & 0x87)) {
        if (battle_flags & 1) {
            if (!(battle_flags & 2) && !(p->actor.animFlags & 1)) {
                p->melee_target_plus_one = Player_FindMeleeTarget(&player_state.actor);
            }
        } else if (!(p->actor.animFlags & 1)) {
            player_talk_npc = Player_FindNpcToTalk(&player_state, &player_state.actor);
            if (player_talk_npc == 0) {
                player_front_spirit = Spirit_FindInFront(&player_state.actor);
                if (player_front_spirit == NULL) {
                    player_front_chest = Chest_FindInFront(&player_state.actor);
                    if (player_front_chest == NULL) {
                        player_front_text_spot = TextSpot_FindInFront(&player_state.actor);
                        if (player_front_text_spot == NULL) {
                            if ((player_near_boss = Boss_CheckPlayerNear()) != 0) {
                                Boss_BeginEncounter(player_near_boss - 1);
                                player_boss_text_delay = 0x1E;
                                core_flags |= 2;
                                p->flags |= 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!(core_flags & 0xF)) {
        if (input_pressed_buttons & 0xA000) {
            if ((battle_flags & 1) && !(p->actor.animFlags & 1)) {
                if (!(battle_flags & 6) && Magic_IsAnyEffectActive() == 0) {
                    if (p->melee_target_plus_one != 0) {
                        Player_StartMeleeAttack(&player_state, &player_state.actor, cd);
                    } else {
                        Player_AddTurnMoveAgilityXP(&player_state);
                        p->melee_target_plus_one = 0;
                        Battle_EndTurn(&player_state.actor);
                    }
                }
            } else if (!(p->actor.animFlags & 1)) {
                if (player_talk_npc != 0) {
                    player_talk_npc--;
                    p->state = 7;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.rotZ = 0.0f;
                    p->actor.rotX = 0.0f;
                    Anim_SetCurrentAndNext(&player_state.actor, player_idle_anim, 1, player_idle_anim, 1, 1);
                    Npc_StartTalk(player_talk_npc);
                    Text_OpenWindow(hud_npc_marker_screen_y < 70 ? 0 : 1);
                    core_flags |= 2;
                } else if (player_front_spirit != NULL) {
                    s = p->stats->element_levels;
                    if (s[0] == 50 && s[1] == 50 && s[2] == 50 && s[3] == 50) {
                    } else {
                        core_flags |= 8;
                        p->state = 0;
                        Spirit_SetCollected(player_front_spirit->flagId);
                        player_front_spirit->collected |= 1;
                        hud_element_input_timer = 8;
                        Sfx_Play(0, 1, 0xFF);
                    }
                } else if (Item_HasInventoryRoom() != 0 && player_front_chest != NULL) {
                    Chest_Open(player_front_chest);
                    player_temp_vec.x = 0.0f;
                    player_temp_vec.y = p->actor.scale * 171.0f;
                    Math_RotateVec2(player_front_chest->rot, (Vec2f *)&player_temp_vec);
                    p->actor.x = player_front_chest->x + player_temp_vec.x;
                    p->actor.z = player_front_chest->z + player_temp_vec.y;
                    p->actor.rot = player_front_chest->rot;
                    p->finish_angle = player_front_chest->rot + 3.141592653589793;
                    p->item_id = player_front_chest->animSetIndex;
                    Player_StartOpenChest(&player_state, &player_state.actor, (s32) cd);
                    player_front_chest = NULL;
                } else if (player_front_text_spot != NULL) {
                    TextSpot_LoadMessage(player_front_text_spot);
                    p->state = 0x11;
                    p->actor.animFlags |= 1;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.rotZ = 0.0f;
                    p->actor.rotX = 0.0f;
                    if (player_front_text_spot->entry->flags & 2) {
                        p->state_timer = 0xF;
                        p->flags |= 0x200;
                        Anim_SetCurrentAndNext(&player_state.actor, 0x1B, 1, player_idle_anim, 1, 1);
                    } else {
                        p->state_timer = 0xF;
                        Anim_SetCurrentAndNext(&player_state.actor, 0xC, 1, 0xD, 1, 1);
                    }
                    player_front_text_spot = NULL;
                } else {
                    p->state = 3;
                    p->state_timer = 0xF;
                    p->actor.vz = 0.0f;
                    p->actor.vx = 0.0f;
                    p->actor.rotZ = 0.0f;
                    p->actor.rotX = 0.0f;
                    p->actor.animFlags |= 1;
                    Anim_SetCurrentAndNext(&player_state.actor, 0x1B, 1, player_idle_anim, 1, 1);
                }
            }
        } else if (Player_CanAct(&player_state, &player_state.actor) != 0) {
            if (!(core_flags & 4) && (input_pressed_buttons & 0x10)) {
                core_flags ^= 1;
                Fade_Start(6, 2, fade_black_ramp);
                Sfx_Play(0, 1, 0xFF);
                p->actor.animFlags |= 1;
            }
            if (!(core_flags & 1) && !(p->actor.battle->status_bits & 0x40) && Player_HandleSpellInput(&player_state) != 0) {
                Player_StartCastSpell(&player_state, &player_state.actor, (AnimSet *) cd);
            }
        }
    } else if (core_flags & 4) {
        if (Player_HandleSpellInput(&player_state) != 0) {
            Player_StartCastSpell(&player_state, &player_state.actor, (AnimSet *) cd);
        }
    } else if (core_flags & 1) {
        if (input_pressed_buttons & 0x4010) {
            core_flags ^= 1;
            Fade_Start(6, 4, fade_black_ramp_dim);
            Sfx_Play(0, 2, 0xFF);
            p->actor.animFlags &= ~1;
        }
    }
    if (battle_flags & 8) {
        battle_flags &= ~8;
        p->actor.stats->exp += player_battle_exp;
        p->actor.stats->unk14 += player_battle_extra_reward;
        if (player_battle_drop_item != 0xFF) {
            if ((u32) Item_CountInInventory(player_battle_drop_item) >= 3 || (u32) Item_GetInventoryCount() >= 0x8D) {
                player_battle_drop_item = 0xFF;
            }
        }
        Hud_ClearActorStatusIndicators(&player_state.actor);
        player_state.battle.status_bits = 0;
        p->state = 0xF;
        p->state_timer = cd->unkC2;
        p->actor.animFlags |= 1;
        p->actor.vz = 0.0f;
        p->actor.vx = 0.0f;
        p->actor.rotZ = 0.0f;
        p->actor.rotX = 0.0f;
        Anim_SetCurrentAndNext(&player_state.actor, 0x10, 1, player_idle_anim, 1, 1);
    } else if (battle_flags & 0x10) {
        Hud_ClearActorStatusIndicators(&player_state.actor);
        player_state.battle.status_bits = 0;
    }
    player_state_handlers[p->state](&player_state.actor, &player_state, cd);
    player_move_dist = sqrtf(player_move_dx * player_move_dx + player_move_dz * player_move_dz);
    if (!(battle_flags & 1) && p->actor.stats->mp < p->actor.stats->max_mp) {
        player_mp_regen_dist += player_move_dist;
        if (player_mp_regen_dist > 60.0) {
            player_mp_regen_dist -= 60.0;
            p->actor.stats->mp++;
        }
    }
}




s32 D_8007A944;
u8 D_8007A948[0x40]; /* not referenced; the next label is 8007A988 */


/* Player_Draw reads player_state.actor through its labels (D_8007AA20.., player.h): retail
 * addresses them as their own symbols. */
void Player_Draw(struct GfxFrameData *arg0) {
    s32 flag;
    s32 pad[2];
    AnimSet *anims;
    Player *p = &player_state;

    gSPDisplayList(gfx_dl_head++, D_10000A0);
    Env_ApplyLightSlot(player_light_slot);
    if (player_state.state == 0xA || p->state == 0xB) {
        flag = 1;
    } else {
        flag = 0;
    }
    anims = (AnimSet *)player_char_data[D_8007AA70];
    Player_LoadAnim(&D_8007AA20);
    Anim_DrawModel(flag, &D_8007AA20, &anims[D_8007AA72], arg0);
    Anim_AdvanceFrame(D_8007AA78, &D_8007AA20, &anims[D_8007AA72]);
    Player_LoadAnim(&D_8007AA20);
    Coll_ResolveFloorAndWalls(anim_node_world_positions[0].x, D_8007AA24, anim_node_world_positions[0].z, 0xA00, &player_coll);
    player_shadow_pos.x = anim_node_world_positions[0].x;
    player_shadow_pos.y = player_coll.y;
    player_shadow_pos.z = anim_node_world_positions[0].z;
    Shadow_Queue(player_shadow_pos.x, player_shadow_pos.y, player_shadow_pos.z, p->actor.nx, p->actor.ny, p->actor.nz,
                  p->actor.collisionRadius * p->actor.scale);
}


void Player_InitBattle(void) {
    Player *p = &player_state;
    ActorStats *stats;
    PlayerAnimTable *cd;
    s32 quarter;
    s32 i;

    player_battle_exp = player_battle_extra_reward = 0;
    stats = player_state.actor.stats;
    cd = player_char_data[player_state.actor.animSetIndex];
    player_state.unkC = (f32)(u32)stats->agility * 0.2857 + 17.0;
    player_state.battle.status_bits = 0;
    player_state.battle.magic_hit_slot_bits = 0;
    player_state.battle.attack_power = player_state.stats->element_levels[0] + player_state.stats->element_levels[1] + player_state.stats->element_levels[2] +
                        player_state.stats->element_levels[3];
    player_state.battle.damage_scale_16ths = 0x10;
    player_state.battle.agility = stats->agility;
    player_state.battle.defense = stats->defense;
    player_state.unk10 = player_state.battle.attack_power;
    player_state.battle.unk90 = 1.0f;
    quarter = player_state.battle.attack_power >> 2;
    for (i = 0; i < 4; i++) {
        if (quarter < p->stats->element_levels[i]) {
            p->unk10 = p->unk10 - p->stats->element_levels[i] + quarter;
        }
    }
    p->unk10 = p->unk10 / 10 + 1;
    if (p->unk10 > 16) {
        p->unk10 = 16;
    }
    p->state = 3;
    p->state_timer = cd->unkDA;
    p->melee_target_plus_one = 0;
    p->turn_target_angle = p->actor.rot;
    p->flags &= ~0x20;
    p->actor.animFlags |= 1;
    if (player_idle_anim != 0x19) {
        player_idle_anim = 0x11;
    }
    Anim_SetCurrentAndNext(&p->actor, 0x12, 1, player_idle_anim, 1, 1);
}


void Player_StateMove(Actor *a, Player *p, PlayerAnimTable *cd) {
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
        player_temp_vec.x = x;
        player_temp_vec.y = z;
        Math_RotateVec2(camera_state.followYaw, (Vec2f *)&player_temp_vec);
        x = player_temp_vec.x;
        z = player_temp_vec.y;
    }
    Player_UpdateStatGrowth(p, a);
    if (D_8008C168 != 0) {
        x = z = 0.0f;
    } else if (D_8008C16C != 0) {
        x = z = 0.0f;
    } else if (core_flags & 0x300F) {
        x = z = 0.0f;
    } else if (p->battle.status_bits & 8) {
        x = z = 0.0f;
    }
    if ((battle_flags & 1) && (battle_flags & 0x202)) {
        z = 0.0f;
        x = 0.0f;
    } else if (battle_turn_delay != 0) {
        z = 0.0f;
        x = 0.0f;
    }
    if (p->flags & 1) {
        if (player_boss_text_delay != 0) {
            if (--player_boss_text_delay == 0) {
                Text_OpenWindow(0);
            }
        } else if (text_active_window_count == 0) {
            p->flags &= ~1;
            core_flags &= ~2;
            Battle_StartBossEncounter();
        }
    } else if (p->flags & 2) {
        if (text_active_window_count == 0) {
            p->flags &= ~2;
            core_flags &= ~2;
        }
    } else if (p->flags & 0x10) {
        if (text_active_window_count == 0) {
            p->flags &= ~0x10;
            core_flags &= ~2;
        }
    }
    switch (p->state) {
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
    if (p->state == 2) {
        player_run_sfx_timer += a->animStep;
        if (player_run_sfx_timer >= 0x97) {
            player_run_sfx_timer = 0;
            Sfx_Play(0, 0x21, 0xFF);
        }
        if (p->state_timer != 0) {
            if (!(p->state_timer & 3)) {
                effect_foot_particle_template.x = a->x;
                effect_foot_particle_template.y = a->y + 1.0f;
                effect_foot_particle_template.z = a->z;
                effect_foot_particle_template.vecX = 0.0f;
                effect_foot_particle_template.vecY = 0.2f;
                effect_foot_particle_template.vecZ = 0.0f;
                Effect_AllocateSprite(&effect_foot_particle_template);
            }
            p->state_timer--;
        }
    }
    Player_ApplyFloorEffect(p, a);
}

void Player_StateWait(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->state_timer == 0) {
        arg1->state = 0;
        arg0->animFlags &= 0xFFFC;
    }
}

void Player_StateBrake(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    Player_MoveAndCollide(0xA01, arg0, arg1);
    arg0->vx *= 0.68;
    arg0->vz *= 0.68;
    if (--arg1->state_timer == 0) {
        arg1->state = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->animFlags &= 0xFFFE;
    }
}

void Player_StateHurt(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->state_timer == 0) {
        ActorStats *sub = arg1->stats;

        arg0->vx = 0.0f;
        arg0->vz = 0.0f;
        if (sub->hp == 0) {
            arg1->state = 6;
            arg1->state_timer = 0xE6;
            Anim_SetCurrentAndNext(arg0, 9, 1, player_idle_anim, 1, 1);
            Hud_ClearActorStatusIndicators(arg0);
            Bgm_Play(0x1E);
            core_flags |= 0x880;
            core_transition_timer = arg1->state_timer;
            fade_transition_style = 2;
            core_fade_out_time = 0x5A;
            arg1->unk124 = 0xC8;
            exit_destination.map = player_respawn_map;
            exit_destination.subarea = player_respawn_subarea;
            exit_destination.entry = player_respawn_entry;
            player_spawn_x = 0.0f;
            player_spawn_z = 0.0f;
            player_spawn_rot = 0.0f;
            player_spawn_type = 0x108;
            player_state.unk6 = 0;
            hud_panel_transition_state = 1;
            hud_panel_transition_frame = 0xC;
        } else {
            arg1->state = 0;
            arg0->animFlags &= 0xFFFC;
        }
    }
}

void Player_StateDying(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    Player_GetAnimMotion(arg0, (AnimSet *)arg2, &player_temp_vec); /* the table as its AnimSet array */
    arg0->vx = player_temp_vec.x;
    arg0->vz = player_temp_vec.y;
    Player_MoveAndCollide(0xA01, arg0, arg1);
    if (--arg1->state_timer == arg1->unk124) {
        camera_state.distance = 250.0f;
        camera_state.eyeHeight = 150.0f;
        camera_state.followGain = 0.01f;
    }
}

void Player_StateTalk(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (text_active_window_count == 0) {
        Npc_EndTalk(player_talk_npc);
        arg1->state = 0;
        arg0->animFlags &= 0xFFFE;
        core_flags &= ~2;
        if (core_flags & 0x10) {
            core_flags &= ~0x10;
            if (npc_slots[player_talk_npc].def->talk_kind == 6 && text_last_choice_index == 0) {
                core_flags |= 0x480;
                core_transition_timer = 0x23;
                core_fade_out_time = 0x1E;
                player_respawn_map = map_id;
                player_respawn_subarea = map_subarea;
                arg1->state = 3;
                arg1->state_timer = 0x41;
                arg0->animFlags |= 1;
                Audio_StartSeqFadeOut(0x3C);
            }
        } else if (arg1->flags & 0x40) {
            arg1->flags &= ~0x40;
            Sfx_Play(0, 0x3B, 0xFF);
        }
        player_talk_npc = 0;
    }
}

void Player_StateAutoWalk(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    Player_MoveWalk(arg1->move_step_x, arg1->move_step_z, arg0, arg1);
    Player_MoveAndCollide(0xA01, arg0, arg1);
    if (--arg1->state_timer == 0) {
        arg1->state = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->animFlags &= 0xFFFE;
    }
}

void Player_StateMeleeAttack(Actor *a, Player *p, PlayerAnimTable *cd) {
    u16 dmg;
    s32 flags;
    s32 t;

    a->vz = 0.0f;
    a->vx = 0.0f;
    if (--p->state_timer == 0) {
        if (Player_RollHitOnEnemy(p->melee_target_plus_one - 1, a) != 0) {
            dmg = Player_CalcMeleeDamage(p);
            if (p->state == 0x10) {
                dmg *= 0.5;
            }
            flags = 0x8004;
            if (p->flags & 0x400) {
                flags = 0xC004;
                p->flags &= ~0x400;
            }
            dmg = Enemy_TakeDamage(p->melee_target_plus_one - 1, dmg, (p->spell_id >> 8) & 0xF, flags, a);
            if (dmg != 0) {
                a->stats->mp++;
                if (a->stats->max_mp < a->stats->mp) {
                    a->stats->mp = a->stats->max_mp;
                }
                if (p->battle.status_bits & 2) {
                    t = ((dmg + 3) >> 2) + 1;
                    dmg = t;
                    a->stats->hp += dmg;
                    if (a->stats->max_hp < a->stats->hp) {
                        a->stats->hp = a->stats->max_hp;
                    }
                    Effect_AddFloatingNumber(a, 1, dmg);
                    Hud_StartActorStatusIndicator(a, 2, 1, 0x1E);
                }
                player_temp_vec.x = 0.0f;
                player_temp_vec.y = 2.0f * (a->stats->body_radius * a->scale);
                Math_RotateVec2(a->rot, (Vec2f *)&player_temp_vec);
                Effect_SpawnStreakBurst(a->x + player_temp_vec.x, a->y + a->stats->body_height * a->scale * 0.7f, a->z + player_temp_vec.y);
            }
            p->stats->hp_xp++;
        } else {
            Enemy_PlayMissEffect(&enemy_slots[p->melee_target_plus_one - 1].actor);
        }
        if (enemy_slots[p->melee_target_plus_one - 1].hp == 0) {
            p->flags &= ~0x100;
        }
        if (p->state == 0xD && (p->flags & 0x100)) {
            p->state = 0x10;
            p->state_timer = 0x12;
            p->flags &= ~0x100;
            a->animFlags |= 1;
            Anim_SetCurrentAndNext(a, 0xB, 1, player_idle_anim, 1, 1);
            camera_state.focusFramesLeft = 0x23;
            return;
        }
        p->state = 3;
        if (p->state == 0xD) {
            p->state_timer = cd->unk7A - 0x14;
        } else {
            p->state_timer = cd->unk86 - 0x16;
        }
        p->melee_target_plus_one = 0;
        p->flags &= ~0x100;
        Player_AddTurnMoveAgilityXP(p);
        p->melee_target_plus_one = 0;
        Battle_EndTurn(a);
    } else if (p->state == 0xD && p->unk10 >= p->state_timer && (input_pressed_buttons & 0xA000)) {
        p->flags |= 0x100;
    }
}

void Player_StateCastSpell(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->unk124 != 0) {
        if (--arg1->unk124 == 0) {
            Magic_CreateCastEffect(arg0, arg1->spell_id, 0, (arg1->flags & 0x10000) ? 0x10 : 0);
        }
    } else if (--arg1->state_timer == 0) {
        if (Magic_IsAnyEffectActive() != 0) {
            arg1->state_timer = 8;
            return;
        }
        arg0->animFlags &= 0xFFFE;
        if (arg1->flags & 4) {
            arg1->state = 3;
            arg1->state_timer = arg2->unk122;
            arg1->flags &= ~4;
            Anim_SetCurrentAndNext(arg0, 0x18, 1, player_idle_anim, 1, 1);
        } else {
            arg1->state = 0;
        }
        Player_AddTurnMoveAgilityXP(arg1);
        arg1->melee_target_plus_one = 0;
        Battle_EndTurn(arg0);
    }
}

void Player_StateWalkToExitObject(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    rot = arg0->rot;
    arg0->x += arg1->move_step_x;
    arg0->z += arg1->move_step_z;
    d = arg1->turn_target_angle - rot;
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
    if (--arg1->state_timer == 0) {
        arg1->state = 0xA;
        arg1->state_timer = 0x50;
        Anim_SetCurrentAndNext(arg0, arg1->unk6, 1, player_idle_anim, 1, 1);
        Player_LoadAnim(arg0);
        Anim_UpdateRootMotion(arg0, arg0->animIndex + (AnimSet *)arg2, arg0->scale); /* the table as its AnimSet array */
        arg0->rot = arg1->finish_angle;
        Sfx_Play(0x1A, 8, 0xFF);
    }
}

void Player_StateAnimMove(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    Player_GetAnimMotion(arg0, (AnimSet *)arg2, &player_temp_vec); /* the table as its AnimSet array */
    arg0->vx = player_temp_vec.x;
    arg0->vz = player_temp_vec.y;
    Player_MoveAndCollide(0xA00, arg0, arg1);
    if (--arg1->state_timer == 0) {
        arg1->state = 0;
        arg0->animFlags &= 0xFFFE;
        arg0->rot = arg1->finish_angle;
    }
}

void Player_StateOpenChest(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    if (arg1->state_timer != 0) {
        Player_GetAnimMotion(arg0, (AnimSet *)arg2, &player_temp_vec); /* the table as its AnimSet array */
        arg0->vx = player_temp_vec.x;
        arg0->vz = player_temp_vec.y;
        Player_MoveAndCollide(0xA00, arg0, arg1);
        if (arg1->state_timer == 0x20) {
            Item_BuildMessage(arg1->item_id);
            Text_OpenWindow(1);
            Item_AddToInventory(arg1->item_id);
            core_flags |= 2;
            Sfx_Play(0, 0x3B, 0xFF);
        }
        if (--arg1->state_timer == 0) {
            arg0->rot = arg1->finish_angle;
            Anim_SetCurrentAndNext(arg0, player_idle_anim, 1, player_idle_anim, 1, 1);
        }
    } else if (text_active_window_count == 0) {
        arg1->state = 0;
        arg0->animFlags &= 0xFFFE;
        core_flags &= ~2;
        player_talk_npc = 0;
    }
}

void Player_StateUseItem(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    if (--arg1->state_timer == 0) {
        Item_ApplyEffect(arg1->item_id, arg0);
        if (D_803AAAA0[arg1->item_id].handler_index == 2) {
            Player_AddTurnMoveAgilityXP(arg1);
            arg1->melee_target_plus_one = 0;
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
        arg1->state = 3;
        arg1->state_timer = 0xF;
        Anim_SetCurrentAndNext(arg0, 0x18, 1, player_idle_anim, 1, 1);
        arg1->melee_target_plus_one = 0;
        Battle_EndTurn(arg0);
    }
}



void Player_StateBattleWon(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->state_timer < 0x26) {
        rot = arg0->rot;
        d = arg1->turn_target_angle - rot;
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
    if (--arg1->state_timer == 0) {
        arg1->state = 0;
        arg0->animFlags &= 0xFFFD;
        if (D_8007A172 != 4) {
            Bgm_PlayForMap(map_id, map_subarea, 0x1E);
        }
    }
}


void Player_StateExamine(Actor *arg0, Player *arg1, PlayerAnimTable *arg2) {
    f32 rot;
    f32 d;

    rot = arg0->rot;
    d = arg1->turn_target_angle - rot;
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
    if (arg1->state_timer != 0) {
        if (--arg1->state_timer == 0) {
            Text_OpenWindow(1);
            core_flags |= 2;
        }
    } else if (text_active_window_count == 0) {
        arg1->state = 3;
        if (arg1->flags & 0x200) {
            arg1->state_timer = 2;
        } else {
            arg1->state_timer = 8;
            Anim_SetCurrentAndNext(arg0, 0xE, 1, player_idle_anim, 1, 1);
        }
        arg1->flags &= ~0x200;
        core_flags &= ~2;
        player_talk_npc = 0;
    }
}


void Player_MoveIdle(f32 arg0, f32 arg1, Actor *arg2, Player *arg3) {
    f32 speed;

    arg2->vz = 0.0f;
    arg2->vx = 0.0f;
    if (arg0 != 0.0f || arg1 != 0.0f) {
        speed = sqrtf(arg0 * arg0 + arg1 * arg1) * 0.025;
        if (speed > 2.0) {
            speed = 2.0f;
        }
        if (speed > 1.5) {
            arg3->state = 2;
            arg3->state_timer = 0x1E;
            player_run_sfx_timer = 0;
        } else {
            arg3->state = 1;
        }
    } else if (player_idle_anim != arg2->animIndex && player_idle_anim != arg2->nextAnim) {
        Anim_SetCurrentAndNext(arg2, player_idle_anim, 1, player_idle_anim, 1, 1);
    }
}


void Player_MoveWalk(f32 sx, f32 sz, Actor *a, Player *p) {
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
        player_temp_vec.x = 0.0f;
        player_temp_vec.y = cur + (spd - cur) * 0.85;
        Math_RotateVec2(a->rot, (Vec2f *)&player_temp_vec);
        a->vx = player_temp_vec.x;
        a->vz = player_temp_vec.y;
        anim = 1;
        next = 1;
        flag = 0;
        speed = spd * 14.0f + 3.0f;
        if (spd > 1.5 || (f32)(cur + (spd - cur) * 0.85) > 1.5) {
            p->state = 2;
            p->state_timer = 0x1E;
            player_run_sfx_timer = 0;
        }
    } else {
        a->vx *= 0.82;
        a->vz *= 0.82;
        if (cur > 1.0) {
            anim = 0xF;
            next = player_idle_anim;
            mode = 3;
            p->state = 4;
            p->state_timer = 8;
            a->rotX = 0.0f;
            a->rotZ = 0.0f;
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
                p->state = 0;
                a->vx = 0.0f;
                a->vz = 0.0f;
            }
        }
    }
    if (anim != a->animIndex && anim != a->nextAnim) {
        Anim_SetCurrentAndNext(a, anim, speed, next, speed, flag);
        a->frame = mode;
    } else {
        a->animStep = speed;
    }
}


void Player_MoveRun(f32 sx, f32 sz, Actor *a, Player *p) {
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
        player_temp_vec.x = 0.0f;
        player_temp_vec.y = newspd = cur + (spd - cur) * 0.2;
        Math_RotateVec2(a->rot, (Vec2f *)&player_temp_vec);
        a->vx = player_temp_vec.x;
        a->vz = player_temp_vec.y;
        anim = 2;
        next = 2;
        mode = 0;
        speed = spd * 14.0f + 3.0f;
        flag = 0;
        if (newspd < 1.0 && spd < 1.0) {
            p->state = 1;
        }
    } else {
        anim = 0xF;
        next = player_idle_anim;
        mode = 3;
        p->state = 4;
        p->state_timer = 8;
        a->rotX = 0.0f;
        a->rotZ = 0.0f;
        a->vx *= 0.9;
        a->vz *= 0.9;
        speed = 1;
        flag = 1;
        Effect_StartFootEmitter(a);
    }
    if (anim != a->animIndex && anim != a->nextAnim) {
        Anim_SetCurrentAndNext(a, anim, speed, next, speed, flag);
        a->frame = mode;
    } else {
        a->animStep = speed;
    }
}

void Player_GetAnimMotion(Actor *arg0, AnimSet *arg1, Vec3f *arg2) {
    Player_LoadAnim(arg0);
    Anim_UpdateRootMotion(arg0, &arg1[arg0->animIndex], arg0->scale);
    arg2->x = -arg0->unk44;
    arg2->y = arg0->unk4C;
    Math_RotateVec2(arg0->rot, (Vec2f *)arg2); /* x,y: a ground-plane (x, z) vector */
}

void func_80006A50(void) {
}


void Player_MoveAndCollide(u16 arg0, Actor *arg1, Player *arg2) {
    f32 dx;
    f32 dz;
    f32 max;
    f32 dist;

    if ((battle_flags & 1) && !(battle_flags & 6)) {
        dx = arg1->x + arg1->vx - battle_turn_origin_x;
        dz = arg1->z + arg1->vz - battle_turn_origin_z;
        dist = sqrtf(dx * dx + dz * dz);
        max = arg2->unkC * arg2->battle.unk90;
        if (max < dist) {
            arg1->vx = max * dx / dist - arg1->x + battle_turn_origin_x;
            arg1->vz = max * dz / dist - arg1->z + battle_turn_origin_z;
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
            arg2->flags |= 0x20;
        } else {
            arg2->flags &= ~0x20;
        }
    }
    Player_PushOutOfObjects(&arg1->vx, &arg1->vz, arg1);
    player_move_dx = arg1->vx;
    player_move_dz = arg1->vz;
    dx = arg1->x + arg1->vx;
    dz = arg1->z + arg1->vz;
    player_coll.x = arg1->stats->body_radius * arg1->stats->scale;
    Coll_ResolveFloorAndWalls(dx, arg1->y, dz, arg0, &player_coll);
    arg1->vx = player_coll.x - arg1->x;
    arg1->vz = player_coll.z - arg1->z;
    arg1->x = player_coll.x;
    arg1->y = player_coll.y;
    arg1->z = player_coll.z;
    arg1->nx = player_coll.nx;
    arg1->ny = player_coll.ny;
    arg1->nz = player_coll.nz;
    arg1->floorFlags = player_coll.flags;
}


s32 Player_FindNpcToTalk(Player *arg0, Actor *arg1) {
    s32 ret;
    s32 n;
    Actor **list;
    Actor *a;
    Npc *it;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 r;

    ret = 0;
    if (!(core_flags & 0x448D) && !(arg0->flags & 0x10)) {
        list = npc_drawn_list;
        for (n = npc_drawn_count; n != 0 && ret == 0; n--) {
            a = *list++;
            dx = a->x - arg1->x;
            dy = a->y - arg1->y;
            dz = a->z - arg1->z;
            if (dy > -15.0 && dy < 15.0) {
                if (a->animFlags & 0x1000) {
                    r = 625.0f;
                } else {
                    r = 225.0f;
                }
                if (dx * dx + dz * dz < r) {
                    player_temp_vec.x = dx;
                    player_temp_vec.y = dz;
                    Math_RotateVec2(arg1->rot, (Vec2f *)&player_temp_vec);
                    if (player_temp_vec.y >= 0.0f && player_temp_vec.x > -6.0 && player_temp_vec.x < 6.0) {
                        ret++;
                        for (it = npc_slots; &it->actor != a; it++) {
                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
}


void Player_PushOutOfObjects(f32 *arg0, f32 *arg1, Actor *arg2) {
    f32 size;
    f32 x;
    f32 z;
    s32 hit;
    s32 n;
    Actor **list;
    Actor *a;
    MapObj **list2;
    MapObj *o;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;
    f32 k;

    hit = 0;
    size = arg2->collisionRadius * arg2->scale;
    x = *arg0 + arg2->x;
    z = *arg1 + arg2->z;
    n = enemy_drawn_count;
    if (n != 0) {
        for (list = enemy_drawn_list; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->collisionRadius * a->scale + size;
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
    n = npc_drawn_count;
    if (n != 0) {
        for (list = npc_drawn_list; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->collisionRadius * a->scale + size;
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
    n = mapobj_billboard_count;
    if (n != 0) {
        for (list2 = mapobj_billboard_list; !hit && n != 0; n--) {
            o = *list2++;
            dx = x - o->x;
            dz = z - o->z;
            r = size + 2.0 * o->scale;
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

void Player_ApplyFloorEffect(Player *arg0, Actor *arg1) {
    f32 dx;
    f32 dz;
    f32 k = 2.0f;

    switch ((u16)(arg1->floorFlags >> 6) & 7) {
        case 0:
            break;
        case 1:
            if (arg0->unk128 == 0) {
                Player_TakeDamage(1, 4, arg1);
            }
            arg0->unk128--;
            break;
        case 2:
            dx = arg1->nx * k;
            arg1->x += dx;
            dz = arg1->nz * k;
            arg1->z += dz;
            arg1->vx += dx;
            arg1->vz += dz;
            break;
    }
}



void Player_StartAreaExit(void) {
    Player *p = &player_state;
    s32 kind = (exit_destination.flags >> 8) & 0xF;
    f32 r;
    MapObj *pos;

    player_spawn_type = exit_destination.flags;
    if (exit_destination.flags & 4) {
        p->state = 3;
        p->state_timer = 0x1E;
        p->unk6 = 0;
        p->actor.animFlags |= 1;
        Anim_SetCurrentAndNext(&p->actor, player_idle_anim, 1, player_idle_anim, 1, 1);
        core_transition_timer = 0x13;
        return;
    }
    switch (kind) {
        case 1:
            p->state = 8;
            p->state_timer = 0x1E;
            p->unk6 = 0;
            r = exit_destination.angle;
            p->actor.rotZ = 0.0f;
            p->actor.rotX = 0.0f;
            player_temp_vec.x = 0.0f;
            player_temp_vec.y = 40.0f;
            p->actor.rot = r;
            Math_RotateVec2(r, (Vec2f *)&player_temp_vec);
            p->move_step_x = player_temp_vec.x;
            p->move_step_z = player_temp_vec.y;
            p->actor.animFlags |= 1;
            Sfx_Play(5, 0x21, 0xFF);
            Sfx_Play(0xF, 0x21, 0xFF);
            core_transition_timer = 0x13;
            break;
        case 2:
        case 3:
            Player_StartObjectExit(p, &p->actor);
            if (exit_destination.flags & 1) {
                core_transition_timer = 0x32;
            } else {
                core_transition_timer = 0x32;
            }
            p->actor.animFlags |= 1;
            break;
        case 4:
            pos = &map_objs[exit_destination.mapObj];
            MapObjAnim_Start(1, 0, exit_destination.flags, pos);
            p->state = 3;
            p->state_timer = 0x1E;
            p->unk6 = 0;
            p->actor.animFlags |= 1;
            Anim_SetCurrentAndNext(&p->actor, player_idle_anim, 1, player_idle_anim, 1, 1);
            core_transition_timer = 0x19;
            break;
    }
}

void Player_StartObjectExit(Player *arg0, Actor *arg1) {
    s32 pad[2];
    f32 rot;
    u16 hi;
    MapObj *pos;
    s16 n;

    pos = &map_objs[exit_destination.mapObj];
    MapObjAnim_Start(0, 0, exit_destination.flags, pos);
    hi = exit_destination.flags >> 8;
    if ((hi & 0xF) == 3) {
        arg0->unk6 = 0;
        Anim_SetCurrentAndNext(arg1, 0x1A, 1, 1, 0xA, 1);
        arg0->state = 3;
        arg0->state_timer = 0x4B;
        arg1->rotX = 0.0f;
        arg1->rotZ = 0.0f;
        arg1->vx = 0.0f;
        arg1->vz = 0.0f;
        Sfx_Play(0x1E, 9, 0xFF);
    } else {
        arg0->state = 9;
        arg0->state_timer = 8;
        Anim_SetCurrentAndNext(arg1, 1, 0xA, 1, 0xA, 1);
        if (exit_destination.flags & 1) {
            n = 0x15;
            player_temp_vec.x = -133.0f;
            player_temp_vec.y = -92.0f;
            player_temp_vec.z = 4.0f;
        } else {
            n = 0x14;
            player_temp_vec.x = -119.0f;
            player_temp_vec.y = 125.0f;
            player_temp_vec.z = 162.0f;
        }
        arg0->unk6 = n;
        rot = pos->angle * 0.017453292519943295;
        Math_RotateVec2(-rot, (Vec2f *)&player_temp_vec);
        arg0->move_step_x = (pos->x - player_temp_vec.x * arg1->scale - arg1->x) / arg0->state_timer;
        arg0->move_step_z = (pos->z + player_temp_vec.y * arg1->scale - arg1->z) / arg0->state_timer;
        arg0->finish_angle = rot;
        rot = rot + player_temp_vec.z * 0.017453292519943295;
        if (rot > 3.141592653589793) {
            rot -= 6.283185307179586;
        } else if (rot < -3.141592653589793) {
            rot += 6.283185307179586;
        }
        arg0->turn_target_angle = rot;
        arg1->rotX = 0.0f;
        arg1->rotZ = 0.0f;
    }
    arg1->animFlags |= 1;
}

void Player_StartOpenChest(Player *arg0, Actor *arg1, s32 arg2) {
    Anim_SetCurrentAndNext(arg1, 0x1C, 1, 0x1D, 1, 1);
    Player_LoadAnim(arg1);
    Anim_UpdateRootMotion(arg1, arg1->animIndex * 0xC + arg2, arg1->scale);
    arg0->state = 0xB;
    arg0->state_timer = 0x5A;
    arg1->animFlags |= 1;
}

void Player_StartUseItem(u8 arg0) {
    PlayerAnimTable *cd = player_char_data[player_state.actor.animSetIndex];

    player_state.item_id = arg0;
    player_state.state = 0xC;
    player_state.state_timer = cd->unk116;
    player_state.actor.animFlags |= 1;
    Anim_SetCurrentAndNext(&player_state.actor, 0x17, 1, 0x16, 1, 1);
}

/* .data 8004DCB0..8004DD10 in source order: this table (after the functions it
 * points to), Player_LoadAnim's static cache (8004DCF8), player_melee_damage_scale (end of file). */
PlayerStateFunc player_state_handlers[18] = {
    Player_StateMove,
    Player_StateMove,
    Player_StateMove,
    Player_StateWait,
    Player_StateBrake,
    Player_StateHurt,
    Player_StateDying,
    Player_StateTalk,
    Player_StateAutoWalk,
    Player_StateWalkToExitObject,
    Player_StateAnimMove,
    Player_StateOpenChest,
    Player_StateUseItem,
    Player_StateMeleeAttack,
    Player_StateCastSpell,
    Player_StateBattleWon,
    Player_StateMeleeAttack,
    Player_StateExamine,
};

void Player_LoadAnim(Actor *arg0) {
    static s32 player_loaded_anim = -1;
    MenuRomRange *r;

    if (player_loaded_anim != arg0->animIndex) {
        player_loaded_anim = arg0->animIndex;
        r = &player_anim_rom_ranges[player_loaded_anim];
        Dma_ReadRom(r->start, (void *) 0x80200000, r->end - r->start);
    }
}


#ifdef NON_MATCHING
/* -1 and 0x130 swapped between s5/s7, one addu operand order (register allocation tie); code is equivalent */
s32 Player_FindMeleeTarget(Actor *arg0) {
    Enemy *m;
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

    radius = arg0->stats->body_radius * arg0->scale;
    ret = 0;
    idx = enemy_turn_order;
    i = 0;
    for (; i < battle_enemy_count; i++, idx++) {
        m = enemy_slots + *idx;
        a = &m->actor;
        if (m->actor.animSetIndex != -1) {
            dx = a->x - arg0->x;
            dz = a->z - arg0->z;
            dist = sqrtf(dx * dx + dz * dz);
            r = a->stats->body_radius * a->scale;
            if (dist < radius + r + 10.0) {
                player_temp_vec.x = dx;
                player_temp_vec.y = dz;
                stats = a->stats;
                if (stats->unk0 == 1) {
                    dx = a->battle->unk94 - arg0->y;
                    dz = 2.0 * stats->body_radius;
                } else if (stats->unk0 == 2) {
                    dz = 0.0f;
                    dx = 0.0f;
                } else {
                    dz = stats->body_height;
                    dx = a->y - arg0->y;
                }
                if (dx < 0.0f) {
                    dx = -dx;
                }
                dx -= dz * a->scale + arg0->stats->body_height * arg0->scale;
                if (dx <= 0.0f) {
                    Math_RotateVec2(arg0->rot, (Vec2f *)&player_temp_vec);
                    r = r * 1.5;
                    if (player_temp_vec.y >= 0.0f && -r < player_temp_vec.x && player_temp_vec.x < r) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game/player/player/Player_FindMeleeTarget.s")
#endif

void Player_StartMeleeAttack(Player *arg0, Actor *arg1, PlayerAnimTable *arg2) {
    Enemy *mon;
    f32 dx;

    arg0->state = 0xD;
    arg0->state_timer = 0x14;
    arg0->flags &= ~0x400;
    arg1->animFlags |= 1;
    Anim_SetCurrentAndNext(arg1, 0xA, 1, player_idle_anim, 1, 1);
    mon = &enemy_slots[arg0->melee_target_plus_one];
    dx = mon[-1].actor.x - arg1->x;
    arg1->rot = Math_Atan2(dx, mon[-1].actor.z - arg1->z);
    Camera_StartBattleFocus(0x23, arg1);
}

s32 Player_RollHitOnEnemy(s32 arg0, Actor *arg1) {
    s16 chance;
    Enemy *m = &enemy_slots[arg0];

    chance = (arg1->battle->agility * 100) / (arg1->battle->agility + ((m->actor.battle->agility + 7) >> 3));
    return Math_Rand(100) < chance;
}


u16 Player_CalcMeleeDamage(Player *arg0) {
    s32 n;
    s32 i;
    u16 val;
    u16 quarter;
    u16 sum;

    n = 0;
    val = arg0->battle.attack_power;
    quarter = arg0->battle.attack_power >> 2;
    sum = arg0->battle.attack_power;
    for (i = 0; i < 4; i++) {
        if (quarter < arg0->stats->element_levels[i]) {
            sum = sum - arg0->stats->element_levels[i] + quarter;
            n++;
        }
    }
    val = (val >> 1) + sum;
    if (n != 0) {
        val = (player_melee_damage_scale[n] * val) >> 6;
    }
    val = (val * arg0->battle.damage_scale_16ths) >> 4;
    if (Math_Rand((arg0->flags & 0x10000) ? 4 : 0x20) == 0) {
        val += val >> 1;
        Fade_Start(4, 0, fade_damage_flash);
        arg0->flags |= 0x400;
    }
    if (arg0->battle.status_bits & 1) {
        val >>= 1;
    }
    return val;
}

#ifdef NON_MATCHING

/* frame 0x50 vs 0x48: damage kept in an extra saved register, arg2 kept live (register allocation); code is equivalent */
u16 Player_TakeDamage(u16 dmg, u16 arg1, Actor *arg2) {
    Player *p = &player_state;
    PlayerAnimTable *cd;
    f32 angle;
    s32 d;
    s32 flags;

    if (p->state != 6) {
        cd = player_char_data[p->actor.animSetIndex];
        if (dmg != 0) {
            if (arg1 & 0x8000) {
                angle = Math_Atan2(arg2->x - player_state.actor.x, arg2->z - player_state.actor.z) - player_state.actor.rot;
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
            dmg = dmg * ((f32) arg2->battle->attack_power / (f32) (arg2->battle->attack_power + p->battle.defense));
            dmg += Math_Rand((u32) (sqrtf(dmg) * 0.75 + 1.0));
            if (dmg == 0) {
                dmg++;
            }
            d = dmg;
            if (p->actor.stats->hp < dmg) {
                p->actor.stats->hp = 0;
            } else {
                p->actor.stats->hp -= d;
            }
            if (p->battle.status_bits & 0x200) {
                p->actor.stats->mp += d;
                if (p->actor.stats->max_mp < p->actor.stats->mp) {
                    p->actor.stats->mp = p->actor.stats->max_mp;
                }
                Hud_StartActorStatusIndicator(&player_state.actor, 0x200, 2, 0x1E);
            }
            flags = 0;
            p->stats->hp_xp++;
            p->stats->defense_xp++;
            if (arg1 & 0x4000) {
                flags = 0x8003;
            }
            Effect_AddFloatingNumber(&player_state.actor, flags, d);
        }
        p->state = 5;
        p->state_timer = *(s16 *) ((u8 *) cd + 0x62); /* PlayerAnimTable field 0x62 (lh) */
        player_state.actor.animFlags |= 1;
        d = arg1 & 0x8000;
        if (arg1 & 4) {
            player_state.actor.animFlags |= 2;
        }
        Anim_SetCurrentAndNext(&player_state.actor, 8, 1, player_idle_anim, 1, 1);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game/player/player/Player_TakeDamage.s")
#endif


void Player_StartMissReaction(void) {
    Player *p = &player_state;
    PlayerAnimTable *cd;

    if (p->state != 6) {
        if (p->stats->hp != 0) {
            cd = player_char_data[p->actor.animSetIndex];
            p->state = 3;
            p->state_timer = cd->unk56;
            p->actor.animFlags |= 3;
            Anim_SetCurrentAndNext(&p->actor, 7, 1, player_idle_anim, 1, 1);
            Hud_ShowActorPopup(&p->actor);
            Sfx_Play(0, 0x17, 0xFF);
        }
    }
}

s32 Player_CanAct(Player *arg0, Actor *arg1) {
    s32 ret = 0;

    if (!(arg1->animFlags & 1) && !(core_flags & 0x80) && !(battle_flags & 8)) {
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

s32 Player_HandleSpellInput(Player *arg0) {
    s32 dir;
    s32 pad;
    s32 ret;
    u32 prev;
    s32 sfx;

    ret = 0;
    if (arg0->spell_input_count < 3 && (input_pressed_buttons & 0xF)) {
        prev = arg0->spell_input_count;
        if (input_pressed_buttons & 8) {
            dir = 0;
        } else if (input_pressed_buttons & 4) {
            dir = 2;
        } else if (input_pressed_buttons & 2) {
            dir = 1;
        } else if (input_pressed_buttons & 1) {
            dir = 3;
        }
        arg0->spell_input_dirs[arg0->spell_input_count] = dir;
        arg0->spell_input_count++;
        if (Magic_GetSpellRestrictionFlags(Magic_LookupSpellSequence(arg0->spell_input_count, arg0->spell_input_dirs), arg0->stats->mp) & 5) {
            sfx = 0x13;
            arg0->spell_input_count--;
        } else if (!(core_flags & 4)) {
            core_flags |= 4;
            sfx = 0x17;
        } else {
            sfx = 0x17;
        }
        Sfx_Play(0, sfx, 0xFF);
        if (prev != arg0->spell_input_count) {
            hud_spell_input_anim_timer = 8;
            hud_spell_input_anim_flags |= 1;
            if (arg0->spell_input_count == 1) {
                hud_spell_input_anim_flags |= 2;
            } else {
                hud_spell_input_anim_flags &= 0xFFFD;
            }
        }
    } else if (arg0->spell_input_count && (input_pressed_buttons & 0xA000)) {
        arg0->spell_id = Magic_LookupSpellSequence(arg0->spell_input_count, arg0->spell_input_dirs);
        if (Magic_GetSpellRestrictionFlags(arg0->spell_id, arg0->stats->mp) == 0) {
            core_flags &= ~4;
            ret = 1;
        }
    } else if ((input_pressed_buttons & 0x4000) && (core_flags & 4)) {
        if (arg0->spell_input_count) {
            arg0->spell_input_count--;
            hud_spell_input_anim_timer = 8;
            hud_spell_input_anim_flags &= 0xFFFE;
        }
        if (!arg0->spell_input_count) {
            core_flags &= ~4;
        }
        Sfx_Play(0, 0x13, 0xFF);
    }
    return ret;
}

void Player_StartCastSpell(Player *p, Actor *a, AnimSet *anims) {
    SpellDef *e;
    s32 anim;
    s32 next;
    u16 t;

    a->stats->mp -= D_800C186E[p->spell_input_count];
    e = &D_800C185C[(p->spell_id >> 8) & 0xF][p->spell_id & 0xFF];
    if (e->target_select_handler_index == 2) {
        p->flags |= 4;
        anim = 0x17;
        next = 0x16;
    } else {
        anim = 3;
        next = player_idle_anim;
    }
    t = anims[anim].length;
    p->state = 0xE;
    p->unk124 = 0x12;
    p->spell_input_count = 0;
    p->state_timer = t;
    a->vx = a->vz = 0.0f;
    a->animFlags |= 1;
    Anim_SetCurrentAndNext(a, anim, 1, next, 1, 1);
    Camera_StartBattleFocus(0x2D, a);
    hud_spell_name_timer = 0x1E;
}

void Player_AddTurnMoveAgilityXP(Player *arg0) {
    f32 dx;
    f32 dz;

    if (battle_flags & 1) {
        dx = arg0->actor.x - battle_turn_origin_x;
        dz = arg0->actor.z - battle_turn_origin_z;
        player_battle_move_dist += sqrtf(dx * dx + dz * dz);
        while (player_battle_move_dist > 35.0) {
            player_battle_move_dist -= 35.0;
            arg0->stats->agility_xp++;
        }
    }
}

void Player_UpdateStatGrowth(Player *p, Actor *a) {
    u16 cost;
    s32 count;
    u8 *lv;

    count = 0;
    if (!(battle_flags & 1)) {
        if (map_subarea_flags & 1) {
            player_agility_dist_enemy_area += player_move_dist;
            if (player_agility_dist_enemy_area > 800.0) {
                player_agility_dist_enemy_area -= 800.0;
                p->stats->agility_xp++;
            }
        } else {
            player_agility_dist_npc_area += player_move_dist;
            if (player_agility_dist_npc_area > 1500.0) {
                player_agility_dist_npc_area -= 1500.0;
                p->stats->agility_xp++;
            }
        }
    }
    if (a->stats->max_hp < 500) {
        if (p->stats->hp_xp >= player_stat_xp_costs[p->stats->hp_growth_rank]) {
            p->stats->hp_xp -= player_stat_xp_costs[p->stats->hp_growth_rank];
            a->stats->max_hp++;
            a->stats->hp++;
            if (p->stats->hp_growth_rank < 0x36) {
                p->stats->hp_growth_rank++;
            }
            Effect_StartStatUpMarker(0);
            count++;
        }
    } else {
        p->stats->hp_xp = 0;
    }
    if (a->stats->max_mp < 500) {
        cost = player_stat_xp_costs[p->stats->mp_growth_rank];
        if (p->flags & 0x4000) {
            cost *= 3;
        } else {
            cost *= 4;
        }
        if (p->stats->mp_xp >= cost) {
            p->stats->mp_xp -= cost;
            a->stats->max_mp++;
            a->stats->mp++;
            if (p->stats->mp_growth_rank < 0x36) {
                p->stats->mp_growth_rank++;
            }
            Effect_StartStatUpMarker(2);
            count++;
        }
    } else {
        p->stats->mp_xp = 0;
    }
    if (a->stats->agility < 0xFF) {
        cost = player_stat_xp_costs[p->stats->agility_growth_rank];
        if (p->flags & 0x8000) {
            cost = (f32)cost * 0.8;
        }
        if (p->stats->agility_xp >= cost) {
            p->stats->agility_xp -= cost;
            a->stats->agility++;
            if (p->stats->agility_growth_rank < 0x36) {
                p->stats->agility_growth_rank++;
            }
            Effect_StartStatUpMarker(3);
            count++;
        }
    } else {
        p->stats->agility_xp = 0;
    }
    if (a->stats->defense < 0xFF) {
        cost = player_stat_xp_costs[p->stats->defense_growth_rank];
        if (p->flags & 0x2000) {
            cost = (f32)cost * 0.8;
        }
        if (p->stats->defense_xp >= cost) {
            p->stats->defense_xp -= cost;
            a->stats->defense++;
            if (p->stats->defense_growth_rank < 0x36) {
                p->stats->defense_growth_rank++;
            }
            Effect_StartStatUpMarker(1);
            count++;
        }
    } else {
        p->stats->defense_xp = 0;
    }
    if (!(core_flags & 8)) {
        if (p->stats->level >= 0x62) {
            a->stats->exp = 0;
        } else if (a->stats->exp >= player_level_exp_table[p->stats->level]) {
            a->stats->exp -= player_level_exp_table[p->stats->level];
            if (p->stats->level < 0x62) {
                p->stats->level++;
            }
            lv = p->stats->element_levels;
            if (lv[0] != 0x32 || lv[1] != 0x32 || lv[2] != 0x32 || lv[3] != 0x32) {
                core_flags |= 8;
                p->state = 0;
                hud_element_input_timer = 8;
                Sfx_Play(0, 1, 0xFF);
            }
        }
    }
    if (count != 0) {
        Sfx_Play(4, 0x35, 0xFF);
    }
    if (!(core_flags & 0xA) && player_battle_drop_item != 0xFF) {
        Item_BuildMessage(player_battle_drop_item);
        Text_OpenWindow(1);
        Item_AddToInventory(player_battle_drop_item);
        player_battle_drop_item = 0xFF;
        p->flags |= 2;
        core_flags |= 2;
        Sfx_Play(0, 0x3B, 0xFF);
    }
    if (!(core_flags & 0xA)) {
        a->animFlags &= 0xFFFE;
    }
}

s32 player_melee_damage_scale[4] = { 0x40, 0x40, 0x39, 0x3C };
