#include "common.h"
#include "game/magic/magic.h"
#include "game/audio/sound.h"
#include "game/battle/battle.h"
#include "game/camera/camera.h"
#include "game/core/main.h"
#include "game/enemy/enemy.h"
#include "game/env/env.h"
#include "game/gfx/effect.h"
#include "game/gfx/fade.h"
#include "game/map/collision.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/player/player.h"
#include "game/ui/hud.h"

/*
 * Spell effect system: spell lookup, effect instances, target selection,
 * hit/status callbacks, and visual presentation.
 * Original file: 17360.c (ROM 0x17360).
 *
 * magic_temp_vec is a Vec3f whose x,y pair is a ground-plane (x, z) vector for
 * Math_RotateVec2: the (Vec2f *) casts below reinterpret it so.
 */

/* This file's .bss, 80085F90..800863F0, in address order (first declaration fixes
 * the order). Splat's D_80085F9C, D_80086370/88/A0, D_800863BC and D_800863CC are
 * fields of magic_effects[0], magic_cast_repeats[1..3], magic_temp_vec and magic_coll. */
s32 magic_cast_state; /* 1 cast running, 2 ending (magic_cast_state_timer frames left) */
s32 magic_cast_state_timer;
MagicEffect magic_effects[16];
MagicCastRepeat magic_cast_repeats[4];
Vec3f magic_temp_vec;
struct Enemy* magic_target_enemy_rec;
CollResult magic_coll;

/* The light colour tables Magic_CreateCastEffect / Magic_UpdateEffects pass to
 * Env_SetSlotLightAnim: fixed addresses outside the C objects. */
extern s32 D_800EB700[];
extern s32 D_800EB7C0[];

void Magic_ResetEffectSystem(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        magic_effects[i].unk4 = 0;
    }
    for (i = 0; i < 4; i++) {
        magic_cast_repeats[i].casts_left = 0;
    }
    magic_cast_state = 0;
}

s32 Magic_LookupSpellSequence(u16 n, u8* arg1) {
    s32 grp;
    u32 i;
    SpellDef* rec;
    u8 t;
    u8 buf[4];
    u32 k;

    grp = arg1[0];
    for (i = 0; i != n; i++) {
        buf[i] = arg1[i];
    }
    if (n >= 3) {
        if (buf[2] < buf[1]) {
            t = buf[2];
            buf[2] = buf[1];
            buf[1] = t;
        }
    }
    rec = D_800C185C[grp];
    for (i = 15; i != 0; i--, rec++) {
        if (n == rec->input_length) {
            for (k = 0; k < rec->input_length; k++) {
                if (buf[k] != rec->input_sequence[k]) {
                    break;
                }
            }
            if (k == rec->input_length) {
                break;
            }
        }
    }
    if (i == 0) {
        i = 15;
    }
    return (grp << 8) - i + 15;
}

s32 Magic_GetSpellRestrictionFlags(u32 arg0, u16 arg1) {
    s32 flags = 0;
    SpellDef* rec;
    s32 grp = (arg0 >> 8) & 0xF;
    arg0 &= 0xFF;
    rec = &D_800C185C[grp][arg0];
    if (player_state.stats->unk24[grp] < rec->required_level) {
        flags = 4;
    }
    if (!(((battle_flags & 1) ? 1 : 2) & rec->flags)) {
        flags |= 2;
    }
    if (arg1 < D_800C186E[rec->input_length]) {
        flags |= 1;
    }
    return flags;
}
void Magic_CreateCastEffect(Actor* arg0, u32 arg1, s32 arg2, u16 arg3) {
    MagicCastRepeat* r;
    SpellFxDef* def2;
    MagicEffect* p;
    s32 i;
    SpellDef* def;
    s32 boost;
    MagicSpeedTable sizes;

    sizes = magic_launch_speeds;
    if (arg2 == 0) {
        Env_SetSlotLightAnim(gfx_scene_light_slot, 2, 8, D_800EB700);
        magic_cast_state |= 1;
        magic_cast_state_timer = 8;
    }
    def = &D_800C185C[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    def2 = &D_800C3268[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    if (arg2 == 0 && def->cast_count >= 2) {
        r = (MagicCastRepeat*)magic_cast_repeats;
        i = 3;
        while (i != 0 && r->casts_left != 0) {
            i--;
            r++;
        }
        r->casts_left = def->cast_count - 1;
        if (arg3 & 0x10) {
            r->casts_left *= 2;
        }
        r->frames_until_next_cast = def->repeat_interval + 1;
        r->casts_done = 0;
        r->spell_id = arg1;
        r->cast_flags = arg3;
        r->spell_def = (SpellDef*)def;
        r->caster = arg0;
    }
    p = (MagicEffect*)magic_effects;
    i = 15;
    while (i != 0 && p->unk4 != 0) {
        i--;
        p++;
    }
    p->unk0 = (arg1 >> 8) & 0xF;
    p->unk2 = arg1 & 0xFF;
    p->unk24 = arg0;
    p->target = NULL;
    p->cfg = (SpellDef*)def;
    p->def = def2;
    p->unk4 = def->effect_lifetime;
    p->unk8 = def->start_delay;
    p->unk6 = 100;
    p->unkA = arg3;
    Magic_ClearSlotHitTracking(15 - i);
    switch (def->move_handler_index) {
        case 0:
            magic_temp_vec.x = D_800C1878[(def->launch_direction_index + arg2) & 7].x * sizes.v[def->launch_speed_index];
            magic_temp_vec.y = D_800C1878[(def->launch_direction_index + arg2) & 7].z * sizes.v[def->launch_speed_index];
            boost = arg3 & 0x10;
            Math_RotateVec2(((Actor*)arg0)->rot, (Vec2f*)&magic_temp_vec);
            p->vx = magic_temp_vec.x;
            p->vz = magic_temp_vec.y;
            if (def->launch_flags & 2) {
                p->vy = 0.0f;
            } else {
                p->vy = D_800C1878[(def->launch_direction_index + arg2) & 7].y * sizes.v[def->launch_speed_index];
            }
            if (boost) {
                p->unk4 += p->unk4 >> 1;
            }
            break;
        case 1:
        case 2:
            p->vx = p->vy = p->vz = 0.0f;
            break;
    }
    magic_target_select_handlers[def->target_select_handler_index](p);
    if (p->target != NULL) {
        magic_place_handlers[def->place_handler_index](p, (Actor*)arg0);
        if (def->floor_collision_mode == 2) {
            Coll_ResolveFloorAndWalls(p->x, p->y, p->z, 0xA00, &magic_coll);
            p->y = magic_coll.y;
        }
        Magic_CreateCastPresentation(p, p->unk24);
    } else {
        p->unk4 = 0;
    }
}

void Magic_PlaceEffectAtActorLowerPoint(MagicEffect* arg0, Actor* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 - arg1->stats->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtActorMiddlePoint(MagicEffect* arg0, Actor* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94;
    } else {
        arg0->y = arg1->y + arg1->stats->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAtActorUpperPoint(MagicEffect* arg0, Actor* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 + arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->stats->unk1C * arg1->scale + arg0->cfg->hit_range;
    }
}

void Magic_PlaceEffectAheadAtMiddlePoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    Math_RotateVec2(arg1->rot, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94;
    } else {
        arg0->y = arg1->y + arg1->stats->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAheadAtUpperPoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    Math_RotateVec2(arg1->rot, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 + arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->stats->unk1C * arg1->scale + arg0->cfg->hit_range;
    }
}

void Magic_PlaceEffectBehindAtUpperPoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = -arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    Math_RotateVec2(arg1->rot, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 + arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->stats->unk1C * arg1->scale + arg0->cfg->hit_range;
    }
}

void Magic_PlaceEffectAtSelectedTarget(MagicEffect* arg0, Actor* arg1) {
    if (arg0->target != NULL) {
        arg1 = arg0->target;
    }
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 - arg1->stats->unk18 * arg1->scale;
    } else if (arg1->stats->unk0 == 2) {
        arg0->y = arg1->y + 100.0f * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtRandomOffset(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = (f32)Math_Rand(20) + 20.0;
    Math_RotateVec2((f32)Math_Rand(16) * 3.141592653589793 / 8.0f - 3.141592653589793, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 + arg1->stats->unk18 * arg1->scale + arg0->cfg->hit_range;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->stats->unk1C * arg1->scale + arg0->cfg->hit_range;
    }
}

void Magic_PlaceEffectAtDiagonalOffset(MagicEffect* arg0, Actor* arg1) {
    f32 dist;
    f32 dz;

    if (arg1->typeFlags & 1) {
        dist = arg0->target->x - arg1->x;
        dz = arg0->target->z - arg1->z;
        dist = sqrtf(dist * dist + dz * dz);
    } else {
        dist = arg1->stats->unk18 * 10.0 * arg1->scale;
    }
    magic_temp_vec.y = dist;
    magic_temp_vec.x = dist * 1.5;
    Math_RotateVec2(arg1->rot, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->stats->unk0 == 1) {
        arg0->y = arg1->battle->unk94 - arg1->stats->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtFixedForwardOffset(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = 380.0f;
    Math_RotateVec2(arg1->rot, (Vec2f*)&magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x * arg1->scale;
    arg0->y = arg1->y + 380.0f * arg1->scale;
    arg0->z = arg1->z + magic_temp_vec.y * arg1->scale;
}

void Magic_UpdateEffects(void) {
    MagicCastRepeat* r;
    s32 i;
    MagicEffect* p;
    s32 active;
    Actor* a;
    s32 k;
    s32 hits;
    s32 tries;

    r = (MagicCastRepeat*)magic_cast_repeats;
    for (i = 4; i != 0; i--, r++) {
        if (r->casts_left != 0) {
            if (--r->frames_until_next_cast == 0) {
                r->casts_left--;
                r->casts_done++;
                Magic_CreateCastEffect(r->caster, r->spell_id, r->casts_done, r->cast_flags);
                r->frames_until_next_cast = r->spell_def->repeat_interval + 1;
            }
        }
    }
    p = (MagicEffect*)magic_effects;
    active = 0;
    for (i = 0; i != 16; i++, p++) {
        if (p->unk4 == 0) {
            continue;
        }
        active++;
        if (p->unk8 != 0) {
            p->unk8--;
        } else {
            p->unk4--;
            magic_move_handlers[p->cfg->move_handler_index](p);
            a = magic_find_target_handlers[p->cfg->find_target_handler_index](p, i);
            if (a != NULL) {
                Magic_MarkActorHitBySlot(i, a);
                if (!(a->battle->status_bits & 0x100) || p->cfg->target_select_handler_index == 2) {
                    if (Magic_GetHitOutcome(p, a)) {
                        if (a == p->unk24) {
                            Hud_ShowActorPopup(p->unk24);
                        } else if (a->typeFlags & 1) {
                            Enemy_PlayMissEffect(a);
                        } else {
                            Player_StartMissReaction();
                        }
                    } else {
                        magic_hit_handlers[p->cfg->hit_handler_index](p, a);
                        hits = 0;
                        for (tries = 0, k = 0; k != 12; k++) {
                            if (p->cfg->status_args[k] != 0) {
                                tries++;
                                if (Magic_ShouldApplyStatus(p, p->unk24, k)) {
                                    Magic_StartStatusTimer(p, a, k);
                                    magic_status_handlers[k](p->cfg->status_args[k], a);
                                    hits++;
                                }
                            }
                        }
                        if (p->cfg->hit_handler_index == 5 && tries != 0 && hits == 0) {
                            Hud_ShowActorPopup(a);
                        }
                    }
                }
                Magic_CreateHitPresentation(p, a);
                if (!(p->cfg->flags & 4)) {
                    p->unk4 = 0;
                    if (p->unk34 != NULL && (p->unk34->flags & 1)) {
                        p->unk34->framesLeft = 7;
                        p->unk34->flags &= ~1;
                    }
                } else {
                    p->unkA |= 2;
                }
            }
        }
        if (p->unk34 != NULL) {
            p->unk34->x = p->x;
            p->unk34->y = p->y;
            p->unk34->z = p->z;
            p->unk34->upX = p->vx;
            p->unk34->upY = p->vy;
            p->unk34->upZ = p->vz;
            if (p->unk4 == 0 && (p->unk34->flags & 1)) {
                p->unk34->framesLeft = 7;
                p->unk34->flags &= ~1;
            }
        }
        if (((s16 *)p->def)[8] >= 0) {
            k = (u16)((s16 *)p->def)[9];
            if (p->unk6 >= (u32)(k >> 8)) {
                Magic_CreateTimedPresentation(p, p->target);
                p->unk6 = 0;
            } else {
                p->unk6++;
            }
        }
    }
    if ((magic_cast_state & 1) && active == 0) {
        magic_cast_state = 2;
        magic_cast_state_timer = 30;
    } else if (magic_cast_state & 2) {
        if (--magic_cast_state_timer == 0) {
            magic_cast_state = 0;
            Env_SetSlotLightAnim(gfx_scene_light_slot, 2, 8, D_800EB7C0);
        }
    }
}

s32 Magic_IsAnyEffectActive(void) {
    s32 i;
    MagicEffect* p;

    i = 16;
    p = magic_effects;
    while (i != 0 && p->unk4 == 0) {
        i--;
        p++;
    }
    return i;
}

void Magic_MoveHomingEffect(MagicEffect* arg0) {
    u16 flags;
    f32 dx;
    f32 dy;
    f32 dz;
    Actor* t;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 d;
    s32 pad[2];
    MagicSpeedTable speeds;
    MagicSpeedTable turns;

    speeds = magic_homing_strengths;
    turns = magic_homing_accels;
    flags = arg0->unkA;
    t = arg0->target;
    if (flags & 1) {
        return;
    }
    if (t != NULL) {
        if ((flags & 2) || t->animSetIndex == -1) {
            dz = 0.0f;
            dy = 0.0f;
            dx = 0.0f;
        } else {
            dx = t->x - arg0->x;
            if (t->stats->unk0 == 1) {
                dy = t->battle->unk94 - arg0->y;
            } else {
                dy = t->y + t->stats->unk1C * t->scale * 0.5 - arg0->y;
            }
            dz = t->z - arg0->z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            dx = speeds.v[arg0->cfg->homing_strength_index] * dx / d;
            dy = speeds.v[arg0->cfg->homing_strength_index] * dy / d;
            dz = speeds.v[arg0->cfg->homing_strength_index] * dz / d;
        }
        vx = arg0->vx;
        vy = arg0->vy;
        vz = arg0->vz;
        d = sqrtf(vx * vx + vy * vy + vz * vz);
        if (d != 0.0f) {
            vx /= (f64)d;
            vy /= (f64)d;
            vz /= (f64)d;
            dx += vx;
            dy += vy;
            dz += vz;
        }
        d = sqrtf(dx * dx + dy * dy + dz * dz);
        dx = turns.v[arg0->cfg->homing_accel_index] * dx / d;
        dy = turns.v[arg0->cfg->homing_accel_index] * dy / d;
        dz = turns.v[arg0->cfg->homing_accel_index] * dz / d;
        arg0->vx = arg0->vx * 0.9 + dx;
        arg0->vy = arg0->vy * 0.9 + dy;
        arg0->vz = arg0->vz * 0.9 + dz;
    }
    if (arg0->cfg->launch_flags & 1) {
        arg0->vy -= 0.3;
    }
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    if (arg0->cfg->floor_collision_mode != 0) {
        Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &magic_coll);
        switch (arg0->cfg->floor_collision_mode) {
            case 1:
                if (arg0->y < magic_coll.y) {
                    arg0->unkA |= 1;
                    arg0->unk4 = 8;
                    arg0->vz = 0.0f;
                    arg0->vy = 0.0f;
                    arg0->vx = 0.0f;
                    if (arg0->unk34 != NULL) {
                        arg0->unk34->framesLeft = 15;
                        arg0->unk34->flags &= ~1;
                    }
                    Camera_Shake(1);
                    if (((s16 *)arg0->def)[0x10] >= 0) {
                        Magic_CreateGroundHitPresentation(arg0, arg0->target);
                    }
                }
                break;
            case 2:
                arg0->y = magic_coll.y;
                break;
        }
    }
}

void Magic_MoveVerticalEffect(MagicEffect* arg0) {
    if (!(arg0->unkA & 1)) {
        if (arg0->cfg->launch_flags & 1) {
            arg0->vy -= 0.3;
        }
        arg0->y += arg0->vy;
        if (arg0->cfg->floor_collision_mode == 1) {
            Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &magic_coll);
            if (arg0->y < magic_coll.y) {
                arg0->y = magic_coll.y;
                arg0->unkA |= 1;
                arg0->unk4 = 8;
                arg0->vz = 0.0f;
                arg0->vy = 0.0f;
                arg0->vx = 0.0f;
                if (arg0->unk34 != NULL) {
                    arg0->unk34->framesLeft = 15;
                    arg0->unk34->flags &= ~1;
                }
                Camera_Shake(1);
                Magic_CreateGroundHitPresentation(arg0, arg0->target);
            }
        }
        if (arg0->cfg->target_select_handler_index == 0 && !(arg0->target->animFlags & 1)) {
            arg0->x = arg0->target->x;
            arg0->z = arg0->target->z;
        }
    }
}

Actor* Magic_FindTargetInRange(MagicEffect* arg0, s32 arg1) {
    Actor* a;
    Enemy* p;
    s32 n;
    f32 dx;
    f32 dy;
    Actor* ret;
    f32 dz;
    f32 dist;
    Actor* target;

    target = arg0->target;
    if (target != NULL) {
        if (!(target->typeFlags & 1)) {
            ret = &player_state.actor;
            if (Magic_WasActorHitBySlot(arg1, target)) {
                ret = NULL;
            } else {
                dx = ret->x - arg0->x;
                dz = ret->z - arg0->z;
                dy = (ret->y + ret->stats->unk1C * ret->scale * 0.5 - arg0->y) * 0.5;
                dist = sqrtf(dx * dx + dy * dy + dz * dz);
                if (arg0->cfg->hit_range + ret->stats->unk18 * ret->scale < dist) {
                    ret = NULL;
                }
            }
        } else {
            n = enemy_count;
            p = enemy_slots;
            while (n != 0) {
                if (p->actor.animSetIndex != -1) {
                    a = &p->actor;
                    ret = a;
                    if (!Magic_WasActorHitBySlot(arg1, a)) {
                        dx = a->x - arg0->x;
                        dz = a->z - arg0->z;
                        switch (a->stats->unk0) {
                            default:
                                dy = 0.0f;
                                break;
                            case 0:
                                dy = (a->y + a->stats->unk1C * a->scale * 0.5 - arg0->y) * 0.5;
                                break;
                            case 1:
                                dy = (a->battle->unk94 - arg0->y) * 0.5;
                                break;
                        }
                        dist = sqrtf(dx * dx + dy * dy + dz * dz);
                        if (dist < arg0->cfg->hit_range + a->stats->unk18 * a->scale) {
                            break;
                        }
                    }
                    n--;
                }
                p++;
            }
            if (n == 0) {
                ret = NULL;
            } else {
                magic_target_enemy_rec = p;
            }
        }
    } else {
        ret = NULL;
    }
    return ret;
}

Actor* Magic_FindEligibleTarget(MagicEffect* arg0, s32 arg1) {
    Actor* ret;
    Enemy* p;
    s32 n;

    if (!(arg0->target->typeFlags & 1)) {
        ret = &player_state.actor;
        if (Magic_WasActorHitBySlot(arg1, &player_state.actor)) {
            ret = NULL;
        }
    } else if ((ret = arg0->target) == NULL || Magic_WasActorHitBySlot(arg1, ret)) {
        n = enemy_count;
        ret = NULL;
        p = enemy_slots;
        while (n != 0) {
            if (p->actor.animSetIndex != -1) {
                if (!Magic_WasActorHitBySlot(arg1, &p->actor)) {
                    ret = &p->actor;
                    magic_target_enemy_rec = p;
                }
                n--;
            }
            p++;
        }
    }
    return ret;
}

Actor* Magic_FindTargetInRangeIfLanded(MagicEffect* arg0, s32 arg1) {
    Actor* ret = NULL;

    if (arg0->unkA & 1) {
        ret = Magic_FindTargetInRange(arg0, arg1);
    }
    return ret;
}

void Magic_ApplyEffectDamage(MagicEffect* arg0, Actor* arg1) {
    u16 dmg;
    u16 flag;

    flag = 0;
    dmg = Magic_CalculateEffectDamage(arg0->cfg, arg0->unk24);
    if (arg0->unk24->battle->status_bits & 1) {
        dmg >>= 1;
    }
    if (arg1->typeFlags & 1) {
        if (player_state.flags & 0x1000) {
            if (Math_Rand((player_state.flags & 0x10000) ? 4 : 0x20) == 0) {
                dmg += (dmg + 1) >> 1;
                Fade_Start(4, 0, fade_damage_flash);
                flag = 0x4000;
            }
        }
        if (Enemy_TakeDamage(Enemy_GetSlotIndex(arg1), dmg, arg0->cfg->input_sequence[0], arg0->cfg->flags | flag, arg0->unk24) != 0) {
            player_state.stats->unk2A++;
        }
    } else {
        if (Math_Rand(0x20) == 0) {
            dmg += (dmg + 1) >> 1;
            Fade_Start(4, 0, fade_damage_flash);
            flag = 0x4000;
        }
        Player_TakeDamage(dmg, arg0->cfg->flags | flag, arg0->unk24);
    }
}

void Magic_HealTarget(MagicEffect* arg0, Actor* arg1) {
    u16 amt;
    s32 pad;

    if (arg1->typeFlags & 1) {
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        amt = arg1->stats->unk6 * arg0->cfg->unkC / 100;
        amt += Math_Rand(amt >> 2);
        magic_target_enemy_rec->unkA += amt;
        if (magic_target_enemy_rec->unkA > arg1->stats->unk6) {
            magic_target_enemy_rec->unkA = arg1->stats->unk6;
        }
    } else {
        amt = (player_state.stats->unk24[arg0->cfg->input_sequence[0]] >> 1) + arg1->stats->unk6 * arg0->cfg->unkC / 100;
        amt += Math_Rand(amt >> 2);
        if (arg1->stats->unk4 != arg1->stats->unk6) {
            arg1->stats->unk4 += amt;
            if (arg1->stats->unk4 > arg1->stats->unk6) {
                arg1->stats->unk4 = arg1->stats->unk6;
            }
            player_state.stats->unk2A++;
        }
    }
    Effect_AddFloatingNumber(arg1, 1, amt);
}

void Magic_TransferTargetResource(MagicEffect* arg0, Actor* arg1) {
    u16 amt;
    Actor* pl;

    pl = &player_state.actor;
    if (arg1->typeFlags & 1) {
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        amt = (magic_target_enemy_rec->unkC * 11 + 63) >> 6;
        magic_target_enemy_rec->unkC -= amt;
        if (player_state.actor.stats->unk8 != player_state.actor.stats->unkA) {
            pl->stats->unk8 += amt;
            if (pl->stats->unk8 > pl->stats->unkA) {
                pl->stats->unk8 = pl->stats->unkA;
            }
            player_state.stats->unk2A++;
        }
    } else {
        amt = (arg1->stats->unk8 * 11 + 63) >> 6;
        arg1->stats->unk8 -= amt;
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        magic_target_enemy_rec->unkC += amt;
        if (magic_target_enemy_rec->unkC > arg0->unk24->stats->unkA) {
            magic_target_enemy_rec->unkC = arg0->unk24->stats->unkA;
        }
    }
    Effect_AddFloatingNumber(arg1, 1, amt);
}

void func_80018968(s32 arg0, Actor* arg1) {
    if (arg1->typeFlags & 1) {
        arg1->animSetIndex = -1;
        enemy_count--;
    } else if (!(battle_flags & 0x100)) {
        battle_flags |= 0x10;
        player_state.stats->unk2A++;
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_800189F0(s32 arg0, Actor* arg1) {
    if (map_flags == 4 && map_flag4_return_map != -1 && !(map_subarea_def->flags & 4)) {
        exit_destination.map = map_flag4_return_map;
        exit_destination.subarea = map_flag4_return_subarea;
        exit_destination.entry = map_flag4_return_entry;
        player_spawn_type = 0x108;
        player_state.unk6 = 0;
        player_state.stats->unk2A++;
        core_flags |= 0x80;
        core_transition_timer = 0x1E;
    }
}

void Magic_ApplyZeroDamageHit(MagicEffect* arg0, Actor* arg1) {
    if (arg0->cfg->target_select_handler_index != 2) {
        if (arg1->typeFlags & 1) {
            Enemy_TakeDamage(Enemy_GetSlotIndex(arg1), 0, 0, 4, arg0->unk24);
            player_state.stats->unk2A++;
        } else {
            Player_TakeDamage(0, 4, arg0->unk24);
        }
    }
}

void func_80018B40(s32 arg0, Actor* arg1) {
    if ((map_flags & 8) && map_flag8_return_map != -1 && !(map_subarea_def->flags & 8) && map_id != 0x1E &&
        map_id != 0x22) {
        exit_destination.map = map_flag8_return_map;
        exit_destination.subarea = map_flag8_return_subarea;
        exit_destination.entry = map_flag8_return_entry;
        player_spawn_type = 0x108;
        player_state.unk6 = 0;
        player_state.stats->unk2A++;
        core_flags |= 0x80;
        core_transition_timer = 0x1E;
    }
}

void Magic_RemoveEnemyOrDamagePlayer(MagicEffect* arg0, Actor* arg1) {
    if (arg1->typeFlags & 1) {
        if (!(battle_flags & 0x100)) {
            Hud_ClearActorStatusIndicators(arg1);
            arg1->animSetIndex = -1;
            arg1->animFlags &= ~1;
            enemy_count--;
            player_state.stats->unk2A++;
        } else {
            Hud_ShowActorPopup(arg1);
        }
    } else {
        Player_TakeDamage(arg1->stats->unk4 * 4, 4, arg0->unk24);
    }
}

void Magic_ClearActorStatuses(s32 arg0, Actor* arg1) {
    if (arg1->battle->status_bits != 0) {
        arg1->battle->status_bits = 0;
        if (arg1->typeFlags & 1) {
            Enemy_GetSlotIndex(arg1);
        }
        arg1->battle->unk8A = 0x10;
        arg1->battle->unk88 = arg1->stats->unkE;
        arg1->battle->unk86 = arg1->stats->unkC;
        arg1->battle->unk90 = 1.0f;
        if (!(arg1->typeFlags & 1)) {
            player_state.stats->unk2A++;
        }
    }
}

void Magic_DamageAndClearStatuses(s32 arg0, Actor* arg1) {
    Magic_ApplyEffectDamage((void*)arg0, arg1);
    Magic_ClearActorStatuses(arg0, arg1);
}

void Magic_SelectClosestAimTarget(MagicEffect* arg0) {
    f32 angle;
    f32 best;
    f32 d;
    s32 n;
    Enemy* p;
    Actor* caster;

    caster = arg0->unk24;
    if (caster->typeFlags & 1) {
        arg0->target = &player_state.actor;
        return;
    }
    if ((arg0->cfg->flags & 8) && (arg0->vx != 0.0f || arg0->vz != 0.0f)) {
        angle = Math_Atan2(arg0->vx, arg0->vz);
    } else {
        angle = caster->rot;
    }
    caster = arg0->unk24;
    best = 9.424778f;
    n = enemy_count;
    p = enemy_slots;
    while (n != 0) {
        if (p->actor.animSetIndex != -1) {
            magic_temp_vec.x = p->actor.x - caster->x;
            magic_temp_vec.y = p->actor.z - caster->z;
            Math_RotateVec2(angle, (Vec2f*)&magic_temp_vec);
            d = Math_Atan2(magic_temp_vec.x, magic_temp_vec.y);
            if (d > 3.141592653589793) {
                d -= 6.283185307179586;
            } else if (d < -3.141592653589793) {
                d += 6.283185307179586;
            }
            if (d < 0.0f) {
                d = -d;
            }
            if (d < best) {
                best = d;
                arg0->target = &p->actor;
            }
            n--;
        }
        p++;
    }
}

void Magic_SelectFirstActiveTarget(MagicEffect* arg0) {
    s32 i;
    Enemy* p;

    if (arg0->unk24->typeFlags & 1) {
        arg0->target = &player_state.actor;
        return;
    }
    p = enemy_slots;
    i = 6;
    while (i != 0 && p->actor.animSetIndex == -1) {
        i--;
        p++;
    }
    if (i != 0) {
        arg0->target = &p->actor;
        return;
    }
    arg0->target = NULL;
}

void Magic_TargetCaster(MagicEffect* arg0) {
    arg0->target = arg0->unk24;
}

void Magic_ApplyShrinkStatus(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->battle->status_bits |= 1;
        arg1->scale = arg1->stats->scale * 0.5;
        Hud_StartActorStatusIndicator(arg1, 1, 4, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_800190BC(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 2;
    Hud_StartActorStatusIndicator(arg1, 2, 2, -1);
}

void func_80019104(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 4;
    switch (arg0) {
        case 1:
            arg1->battle->unk8A = 0x18;
            break;
        case 2:
            arg1->battle->unk8A = 0x20;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 4, 3, -1);
}

void func_80019184(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->battle->status_bits |= 8;
        arg1->animFlags |= 1;
        Hud_StartActorStatusIndicator(arg1, 8, arg0 - 1, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_8001920C(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x10;
    switch (arg0) {
        case 1:
            arg1->battle->unk90 = 0.5f;
            break;
        case 2:
            arg1->battle->unk90 = 2.0f;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 0x10, (arg1->battle->unk90 > 1.0) ? 8 : 9, -1);
}

void func_800192C8(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x20;
    switch (arg0) {
        case 1:
            arg1->battle->unk86 = arg1->stats->unkC * 2;
            Hud_StartActorStatusIndicator(arg1, 0x20, 7, -1);
            break;
        case 2:
            arg1->battle->unk86 = arg1->stats->unkC * 4;
            Hud_StartActorStatusIndicator(arg1, 0x20, 7, -1);
            break;
        case 3:
            arg1->battle->unk86 = arg1->stats->unkC >> 1;
            Hud_StartActorStatusIndicator(arg1, 0x20, 0xC, -1);
            break;
    }
}

void func_800193A4(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->battle->status_bits |= 0x40;
        Hud_StartActorStatusIndicator(arg1, 0x40, 0xB, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_80019408(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x80;
    Hud_StartActorStatusIndicator(arg1, 0x80, 0xA, -1);
}

void func_80019450(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x100;
    Hud_StartActorStatusIndicator(arg1, 0x100, 4, -1);
}

void func_80019498(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x200;
    Hud_StartActorStatusIndicator(arg1, 0x200, 3, -1);
}

void func_800194E0(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x400;
    switch (arg0) {
        case 1:
            arg1->battle->unk88 = arg1->stats->unkE >> 1;
            break;
        case 2:
            arg1->battle->unk88 = arg1->stats->unkE - (arg1->stats->unkE >> 2);
            break;
        case 3:
            arg1->battle->unk88 = arg1->stats->unkE + (arg1->stats->unkE >> 1);
            break;
        case 4:
            arg1->battle->unk88 = arg1->stats->unkE * 2;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 0x400, (arg1->stats->unkE < arg1->battle->unk88) ? 5 : 6, -1);
}

void func_800195E0(s32 arg0, Actor* arg1) {
    arg1->battle->status_bits |= 0x800;
}

u16 Magic_CalculateEffectDamage(SpellDef* arg0, Actor* arg1) {
    u16 lv;
    u16* p;
    f32 sum;
    f32 step;
    s32 i;

    if (arg1->typeFlags & 1) {
        lv = enemy_slots[Enemy_GetSlotIndex(arg1)].unk28->unk2A;
    } else {
        p = &magic_damage_bonus_stats[arg0->input_sequence[0] * 2];
        lv = player_stats.unk24[arg0->input_sequence[0]];
        lv += player_stats.unk24[*p++] >> 4;
        lv += player_stats.unk24[*p++] >> 3;
        lv += player_stats.unk24[*p] >> 3;
    }
    sum = arg0->unkC * 0.02;
    step = sum * 0.2;
    for (i = 0; i != lv; i++) {
        sum += step;
        step *= 1.03;
    }
    return (u32)sum;
}

EffectModel* Magic_CreateVisualEffect(u16 arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, MagicVisualDef* arg6, Vec3f* arg7, Actor* arg8) {
    f32 sx;
    f32 sy;

    switch (arg6->x_scale_source) {
        case 0:
            sx = arg8->stats->unk18 * arg8->scale * arg7->x;
            break;
        case 1:
            sx = arg8->stats->unk1C * arg8->scale * arg7->x;
            break;
        case 3:
            sx = arg7->z * arg7->x;
            break;
        default:
            do {} while (0);
            sx = arg7->x;
            break;
    }
    switch (arg6->y_scale_source) {
        case 0:
            sy = arg8->stats->unk18 * arg8->scale * arg7->y;
            break;
        case 1:
            sy = arg8->stats->unk1C * arg8->scale * arg7->y;
            break;
        case 3:
            sy = arg7->z * arg7->y;
            break;
        default:
            do {} while (0);
            sy = arg7->y;
            break;
    }
    return Effect_CreateModelEffect(arg6->anim_index, arg6->display_list_index, arg6->texture_index, arg0 & 0xFF, arg1, arg2, arg3, arg4, arg5, sx, sy, sx);
}

void Magic_CreateCastPresentation(MagicEffect* arg0, Actor* arg1) {
    EffectModel* ret;
    SpellDef* cfg;
    SpellParticleDef* fx;
    f32 h;
    SpellFxDef* def;
    MagicVisualDef* tbl;
    f32 y;
    f32 angle;

    def = arg0->def;
    cfg = arg0->cfg;
    if (def->cast_visual_index >= 0) {
        tbl = &D_800C18D8[def->cast_visual_index];
        magic_temp_vec.x = def->cast_scale_x;
        magic_temp_vec.y = def->cast_scale_y;
        magic_temp_vec.z = cfg->hit_range;
        if (arg0->vx != 0.0f || arg0->vz != 0.0f) {
            angle = Math_Atan2(arg0->vx, arg0->vz);
        } else {
            angle = arg1->rot;
        }
        arg0->unk34 = Magic_CreateVisualEffect(def->cast_color_index, def->cast_flags, arg0->x, arg0->y, arg0->z, angle, tbl, &magic_temp_vec, arg1);
        arg0->unk34->upX = arg0->vx;
        arg0->unk34->upY = arg0->vy;
        arg0->unk34->upZ = arg0->vz;
    } else {
        arg0->unk34 = NULL;
    }
    fx = &D_800C363C[arg0->unk0][arg0->unk2];
    if (fx->cast_kind != 0) {
        h = 2.0 * arg1->stats->unk18 * arg1->scale;
        y = arg1->y + arg1->stats->unk1C * arg1->scale;
        switch (fx->cast_kind) {
            case 1:
                Effect_StartConvergeEmitter(fx->cast_effect_arg, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->cast_effect_arg, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->cast_sound_id >= 0) {
        Sfx_Play(def->cast_sound_delay, def->cast_sound_id, 0xFF);
    }
}

void Magic_CreateTimedPresentation(MagicEffect* arg0, Actor* arg1) {
    EffectModel* ret;
    SpellDef* cfg;
    SpellFxDef* def;
    MagicVisualDef* tbl;
    f32 angle;

    def = arg0->def;
    cfg = arg0->cfg;
    tbl = &D_800C18D8[def->timed_visual_index];
    magic_temp_vec.x = def->timed_scale_x;
    magic_temp_vec.y = def->timed_scale_y;
    magic_temp_vec.z = cfg->hit_range;
    if (def->timed_flags & 0x10) {
        angle = arg0->unk4 * 3.141592653589793 / 10.0;
    } else {
        angle = arg1->rot;
    }
    ret = Magic_CreateVisualEffect(def->timed_color_index, def->timed_flags, arg0->x, arg0->y, arg0->z, angle, tbl, &magic_temp_vec, arg0->unk24);
    ret->upX = arg0->vx;
    ret->upY = arg0->vy;
    ret->upZ = arg0->vz;
    if (def->timed_sound_id >= 0) {
        Sfx_Play(def->timed_sound_delay, def->timed_sound_id, 0xFF);
    }
}

void Magic_CreateHitPresentation(MagicEffect* arg0, Actor* arg1) {
    SpellDef* cfg;
    MagicVisualDef* tbl;
    SpellParticleDef* fx;
    SpellFxDef* def;
    u16 flags;
    f32 y;
    f32 h;
    s32 pad[2];

    def = (SpellFxDef*)arg0->def;
    cfg = arg0->cfg;
    if (def->hit_visual_index >= 0) {
        tbl = &D_800C18D8[def->hit_visual_index];
        magic_temp_vec.x = def->hit_scale_x;
        magic_temp_vec.y = def->hit_scale_y;
        magic_temp_vec.z = cfg->hit_range;
        flags = def->hit_flags;
        if (flags & 0x40) {
            arg1 = arg0->unk24;
        }
        if (arg1->stats->unk0 == 1) {
            if (flags & 0x100) {
                y = arg1->battle->unk94;
            } else {
                y = arg1->y;
            }
        } else if (flags & 0x100) {
            y = arg1->y + arg1->stats->unk1C * 0.5 * arg1->scale;
        } else {
            y = arg1->y;
        }
        arg0->unk38 = Magic_CreateVisualEffect(def->hit_color_index, flags, arg1->x, y, arg1->z, arg1->rot, tbl, &magic_temp_vec, arg1);
        arg0->unk38->upX = arg0->vx;
        arg0->unk38->upY = arg0->vy;
        arg0->unk38->upZ = arg0->vz;
    } else {
        arg0->unk38 = NULL;
    }
    fx = &D_800C363C[arg0->unk0][arg0->unk2];
    if (fx->hit_kind != 0) {
        h = 2.0 * arg1->stats->unk18 * arg1->stats->scale;
        y = arg1->y + arg1->stats->unk1C * arg1->stats->scale;
        switch (fx->hit_kind) {
            case 1:
                Effect_StartConvergeEmitter(fx->hit_effect_arg, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->hit_effect_arg, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->hit_sound_id >= 0) {
        Sfx_Play(def->hit_sound_delay, def->hit_sound_id, 0xFF);
    } else if (arg0->unk24 != arg0->target) {
        Sfx_Play(0, 0x18, 0xFF);
    }
}

void Magic_CreateGroundHitPresentation(MagicEffect* arg0, Actor* arg1) {
    EffectModel* ret;
    SpellDef* cfg;
    SpellParticleDef* fx;
    SpellFxDef* def;
    f32 h;
    f32 y;
    MagicVisualDef* tbl;

    def = (SpellFxDef*)arg0->def;
    cfg = arg0->cfg;
    if (def->ground_hit_visual_index >= 0) {
        tbl = &D_800C18D8[def->ground_hit_visual_index];
        magic_temp_vec.x = def->ground_hit_scale_x;
        magic_temp_vec.y = def->ground_hit_scale_y;
        magic_temp_vec.z = cfg->hit_range;
        ret = Magic_CreateVisualEffect(def->ground_hit_color_index, def->ground_hit_flags, arg0->x, arg0->y, arg0->z, arg1->rot, tbl, &magic_temp_vec, arg0->unk24);
        ret->upX = arg0->vx;
        ret->upY = arg0->vy;
        ret->upZ = arg0->vz;
    }
    fx = &D_800C363C[arg0->unk0][arg0->unk2];
    if (fx->ground_hit_kind != 0) {
        h = 2.0 * arg1->stats->unk18 * arg1->scale;
        y = arg1->y + arg1->stats->unk1C * arg1->scale;
        switch (fx->ground_hit_kind) {
            case 1:
                Effect_StartConvergeEmitter(fx->ground_hit_effect_arg, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->ground_hit_effect_arg, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->ground_hit_sound_id >= 0) {
        Sfx_Play(def->ground_hit_sound_delay, def->ground_hit_sound_id, 0xFF);
    }
}

void Magic_StepActorStatusTimers(Actor* arg0) {
    ActorBattle* data = arg0->battle;
    s32 bit = 1;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (data->status_bits & bit) {
            if (--data->timers[i] == 0) {
                data->status_bits ^= bit;
                if (bit & 1) {
                    arg0->scale = arg0->stats->scale;
                } else if (bit & 4) {
                    arg0->battle->unk8A = 0x10;
                } else if (bit & 0x10) {
                    arg0->battle->unk90 = 1.0f;
                } else if (bit & 0x20) {
                    arg0->battle->unk86 = arg0->stats->unkC;
                } else if (bit & 0x400) {
                    arg0->battle->unk88 = arg0->stats->unkE;
                } else if (bit & 8) {
                    arg0->animFlags &= ~1;
                }
            }
        }
        bit <<= 1;
    }
}

s32 Magic_WasActorHitBySlot(s32 arg0, Actor* arg1) {
    return magic_slot_bits[arg0] & arg1->battle->magic_hit_slot_bits;
}

void Magic_MarkActorHitBySlot(s32 arg0, Actor* arg1) {
    arg1->battle->magic_hit_slot_bits |= magic_slot_bits[arg0];
}

void Magic_ResetHitTracking(void) {
    s32 i;

    player_state.battle.magic_hit_slot_bits = 0;
    for (i = 0; i < 6; i++) {
        enemy_slots[i].battle.magic_hit_slot_bits = 0;
    }
}

void Magic_ClearSlotHitTracking(s32 arg0) {
    s32 i;

    player_state.battle.magic_hit_slot_bits &= ~magic_slot_bits[arg0];
    for (i = 0; i < 6; i++) {
        enemy_slots[i].battle.magic_hit_slot_bits &= ~magic_slot_bits[arg0];
    }
}

s32 Magic_GetHitOutcome(MagicEffect* arg0, Actor* arg1) {
    s32 ret;

    if (arg0->unkA & 4) {
        ret = 2;
    } else {
        ret = Math_Rand(100) < arg0->cfg->hit_chance;
        if (ret != 0) {
            if (arg1 != arg0->unk24) {
                if (arg1->typeFlags & 1) {
                    ret = Player_RollHitOnEnemy(Enemy_GetSlotIndex(arg1), arg0->unk24);
                } else {
                    ret = Enemy_RollHitOnPlayer(arg0->unk24);
                }
            }
            ret++;
        }
    }
    return magic_hit_outcomes[ret];
}

s32 Magic_ShouldApplyStatus(MagicEffect* arg0, Actor* arg1, s32 arg2) {
    s32 ret;
    s32 n;
    SpellDef* cfg;

    if (arg0->unkA & 4) {
        ret = 1;
    } else if (cfg = arg0->cfg, cfg->target_select_handler_index == 2) {
        ret = 1;
    } else if (arg1->typeFlags & 1) {
        ret = Math_Rand(64) < magic_status_chances[arg2];
    } else {
        n = (player_state.flags & 0x8000) ? 28 : 32;
        ret = Math_Rand(n) < magic_status_chances[arg2];
    }
    return ret;
}

void Magic_StartStatusTimer(MagicEffect* arg0, Actor* arg1, s32 arg2) {
    if (arg1 != arg0->unk24) {
        arg1->battle->timers[arg2] = Math_Rand(magic_status_time_range_other[arg2]) + 2;
    } else {
        arg1->battle->timers[arg2] = Math_Rand(magic_status_time_range_self[arg2]) + 3;
    }
}

/* .data 8004EC90..8004EE20: the state tables, after the functions they point to. */
MagicPlaceFunc magic_place_handlers[10] = {
    (MagicPlaceFunc) Magic_PlaceEffectAtActorLowerPoint,
    (MagicPlaceFunc) Magic_PlaceEffectAtActorMiddlePoint,
    (MagicPlaceFunc) Magic_PlaceEffectAtActorUpperPoint,
    (MagicPlaceFunc) Magic_PlaceEffectAheadAtMiddlePoint,
    (MagicPlaceFunc) Magic_PlaceEffectAheadAtUpperPoint,
    (MagicPlaceFunc) Magic_PlaceEffectBehindAtUpperPoint,
    (MagicPlaceFunc) Magic_PlaceEffectAtSelectedTarget,
    (MagicPlaceFunc) Magic_PlaceEffectAtRandomOffset,
    (MagicPlaceFunc) Magic_PlaceEffectAtDiagonalOffset,
    (MagicPlaceFunc) Magic_PlaceEffectAtFixedForwardOffset,
};
MagicSelectFunc magic_target_select_handlers[3] = {
    (MagicSelectFunc) Magic_SelectClosestAimTarget,
    (MagicSelectFunc) Magic_SelectFirstActiveTarget,
    (MagicSelectFunc) Magic_TargetCaster,
};
MagicMoveFunc magic_move_handlers[3] = {
    (MagicMoveFunc) Magic_MoveHomingEffect,
    (MagicMoveFunc) Magic_MoveVerticalEffect,
    (MagicMoveFunc) Magic_MoveVerticalEffect,
};
MagicFindTargetFunc magic_find_target_handlers[3] = {
    Magic_FindTargetInRange,
    Magic_FindEligibleTarget,
    Magic_FindTargetInRangeIfLanded,
};
MagicHitFunc magic_hit_handlers[10] = {
    (MagicHitFunc) Magic_ApplyEffectDamage,
    (MagicHitFunc) Magic_HealTarget,
    (MagicHitFunc) Magic_TransferTargetResource,
    (MagicHitFunc) func_80018968,
    (MagicHitFunc) func_800189F0,
    (MagicHitFunc) Magic_ApplyZeroDamageHit,
    (MagicHitFunc) func_80018B40,
    (MagicHitFunc) Magic_RemoveEnemyOrDamagePlayer,
    (MagicHitFunc) Magic_ClearActorStatuses,
    (MagicHitFunc) Magic_DamageAndClearStatuses,
};
MagicStatusFunc magic_status_handlers[12] = {
    (MagicStatusFunc) Magic_ApplyShrinkStatus,
    (MagicStatusFunc) func_800190BC,
    (MagicStatusFunc) func_80019104,
    (MagicStatusFunc) func_80019184,
    (MagicStatusFunc) func_8001920C,
    (MagicStatusFunc) func_800192C8,
    (MagicStatusFunc) func_800193A4,
    (MagicStatusFunc) func_80019408,
    (MagicStatusFunc) func_80019450,
    (MagicStatusFunc) func_80019498,
    (MagicStatusFunc) func_800194E0,
    (MagicStatusFunc) func_800195E0,
};
u16 magic_slot_bits[16] = {
    0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
};
MagicSpeedTable magic_launch_speeds = { { 2.0f, 3.0f, 4.0f, 6.0f, 7.0f } };
MagicSpeedTable magic_homing_strengths = { { 0.0f, 1.0f, 2.0f, 10.0f, 10.0f } };
MagicSpeedTable magic_homing_accels = { { 0.4f, 0.5f, 0.7f, 1.0f, 1.2f } };
u16 magic_damage_bonus_stats[10] = { 2, 1, 3, 2, 0, 3, 1, 0, 2, 0 };
s32 magic_hit_outcomes[3] = { 1, 2, 0 };
u8 magic_status_chances[12] = { 24, 24, 24, 16, 24, 24, 16, 24, 24, 24, 24, 24 };
s32 magic_status_time_range_other[12] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
s32 magic_status_time_range_self[12] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
