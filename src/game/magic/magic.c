#include "common.h"
#include "game/magic/magic.h"

/*
 * Spell effect system: spell lookup, effect instances, target selection,
 * hit/status callbacks, and visual presentation.
 * Original file: 17360.c (ROM 0x17360).
 */

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

/* the model effect Effect_CreateModelEffect returns; local view of game/gfx/effect.h's
 * EffectModel until H2 */
typedef struct EffectModel {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0x10];
    /* 0x28 */ f32 vx;
    /* 0x2C */ f32 vy;
    /* 0x30 */ f32 vz;
} EffectModel;

typedef struct {
    /* 0x000 */ u8 pad0[0xA];
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[0x1E];
    /* 0x02C */ u8 unk2C[0x50];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ u8 pad7E[0xB2];
} Unk8007B908_b; // size = 0x130

extern u8 D_8007AA20[];

typedef struct {
    /* 0x000 */ u8 pad0[0x124];
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u8 pad126[0xA];
} Unk8007B908; // size = 0x130

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
extern u16 D_8007AB18;
extern Unk8007B908 enemy_slots[];
extern u16 battle_flags;
extern SpellDef* D_800C185C[];
extern u16 D_800C186E[];

extern ActorStats* D_8007AA1C;
extern s32 enemy_count;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Unk80084300;

typedef struct {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ ActorStats* unk14;
    /* 0x18 */ u8 pad18[0x64];
    /* 0x7C */ ActorStats* unk7C;
    /* 0x80 */ u8 pad80[0x90];
    /* 0x110 */ u16 unk110;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u16 unk14;
} Unk8007C288;

extern u16 map_flags;
extern s32 map_id;
extern s32 map_flag4_return_map;
extern s32 map_flag4_return_subarea;
extern s32 map_flag4_return_entry;
extern s32 map_flag8_return_map;
extern s32 map_flag8_return_subarea;
extern s32 map_flag8_return_entry;
extern Unk80084300 exit_destination;
extern s32 player_spawn_type;
extern Unk8007AA08 player_state;
extern s32 core_flags;
extern s32 core_transition_timer;
extern Unk8007C288* map_subarea_def;
s32 Player_RollHitOnEnemy(s32, Actor*);
s32 Enemy_RollHitOnPlayer(Actor*);
s32 Enemy_GetSlotIndex(Actor*);
u16 Enemy_TakeDamage(s32, u16, u16, u16, Actor*);
u16 Player_TakeDamage(u16, u16, Actor*);
void Hud_ClearActorStatusIndicators(Actor*);
u32 Math_Rand(u32);
f32 sqrtf(f32);
void Math_RotateVec2(f32, Vec3f*);

void Hud_StartActorStatusIndicator(Actor*, s32, u16, s32);
void Hud_ShowActorPopup(Actor*);

void Magic_ResetEffectSystem(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        magic_effects[i].unk4 = 0;
    }
    for (i = 0; i < 4; i++) {
        magic_cast_repeats[i].unk0 = 0;
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
        if (n == rec->unk4) {
            for (k = 0; k < rec->unk4; k++) {
                if (buf[k] != rec->unk6[k]) {
                    break;
                }
            }
            if (k == rec->unk4) {
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
    if (D_8007AA1C->unk24[grp] < rec->unk0) {
        flags = 4;
    }
    if (!(((battle_flags & 1) ? 1 : 2) & rec->unk2)) {
        flags |= 2;
    }
    if (arg1 < D_800C186E[rec->unk4]) {
        flags |= 1;
    }
    return flags;
}


void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, CollResult*);
void Camera_Shake(s32);
extern s32 gfx_scene_light_slot;
extern u8 D_800EB7C0[];
void Enemy_PlayMissEffect(Actor*);
void Player_StartMissReaction(void);
void Env_SetSlotLightAnim(s32, s32, s32, u8*);
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk800C1878;
extern SpellFxDef* D_800C3268[];
extern Unk800C1878 D_800C1878[];
extern u8 D_800EB700[];
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
    def = &((SpellDef**)D_800C185C)[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    def2 = &D_800C3268[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    if (arg2 == 0 && def->unk20 >= 2) {
        r = (MagicCastRepeat*)magic_cast_repeats;
        i = 3;
        while (i != 0 && r->unk0 != 0) {
            i--;
            r++;
        }
        r->unk0 = def->unk20 - 1;
        if (arg3 & 0x10) {
            r->unk0 *= 2;
        }
        r->unk2 = def->unk22 + 1;
        r->unk4 = 0;
        r->unk8 = arg1;
        r->unkC = arg3;
        r->unk10 = (SpellDef*)def;
        r->unk14 = arg0;
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
    p->unk4 = def->unkA;
    p->unk8 = def->unk24;
    p->unk6 = 100;
    p->unkA = arg3;
    Magic_ClearSlotHitTracking(15 - i);
    switch (def->unk12) {
        case 0:
            magic_temp_vec.x = D_800C1878[(def->unk2C + arg2) & 7].x * sizes.v[def->unk30];
            magic_temp_vec.y = D_800C1878[(def->unk2C + arg2) & 7].z * sizes.v[def->unk30];
            boost = arg3 & 0x10;
            Math_RotateVec2(((Actor*)arg0)->rot, &magic_temp_vec);
            p->vx = magic_temp_vec.x;
            p->vz = magic_temp_vec.y;
            if (def->unk2A & 2) {
                p->vy = 0.0f;
            } else {
                p->vy = D_800C1878[(def->unk2C + arg2) & 7].y * sizes.v[def->unk30];
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
    magic_target_select_handlers[def->unk18](p);
    if (p->target != NULL) {
        magic_place_handlers[def->unk26](p, (Actor*)arg0);
        if (def->unk14 == 2) {
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
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtActorMiddlePoint(MagicEffect* arg0, Actor* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94;
    } else {
        arg0->y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAtActorUpperPoint(MagicEffect* arg0, Actor* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAheadAtMiddlePoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    Math_RotateVec2(arg1->rot, &magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94;
    } else {
        arg0->y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAheadAtUpperPoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    Math_RotateVec2(arg1->rot, &magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectBehindAtUpperPoint(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = -arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    Math_RotateVec2(arg1->rot, &magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAtSelectedTarget(MagicEffect* arg0, Actor* arg1) {
    if (arg0->target != NULL) {
        arg1 = arg0->target;
    }
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else if (arg1->unk64->unk0 == 2) {
        arg0->y = arg1->y + 100.0f * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtRandomOffset(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = (f32)Math_Rand(20) + 20.0;
    Math_RotateVec2((f32)Math_Rand(16) * 3.141592653589793 / 8.0f - 3.141592653589793, &magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAtDiagonalOffset(MagicEffect* arg0, Actor* arg1) {
    f32 dist;
    f32 dz;

    if (arg1->unk5E & 1) {
        dist = arg0->target->x - arg1->x;
        dz = arg0->target->z - arg1->z;
        dist = sqrtf(dist * dist + dz * dz);
    } else {
        dist = arg1->unk64->unk18 * 10.0 * arg1->scale;
    }
    magic_temp_vec.y = dist;
    magic_temp_vec.x = dist * 1.5;
    Math_RotateVec2(arg1->rot, &magic_temp_vec);
    arg0->x = arg1->x + magic_temp_vec.x;
    arg0->z = arg1->z + magic_temp_vec.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtFixedForwardOffset(MagicEffect* arg0, Actor* arg1) {
    magic_temp_vec.x = 0.0f;
    magic_temp_vec.y = 380.0f;
    Math_RotateVec2(arg1->rot, &magic_temp_vec);
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
        if (r->unk0 != 0) {
            if (--r->unk2 == 0) {
                r->unk0--;
                r->unk4++;
                Magic_CreateCastEffect(r->unk14, r->unk8, r->unk4, r->unkC);
                r->unk2 = r->unk10->unk22 + 1;
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
            magic_move_handlers[p->cfg->unk12](p);
            a = magic_find_target_handlers[p->cfg->unk16](p, i);
            if (a != NULL) {
                Magic_MarkActorHitBySlot(i, a);
                if (!(a->unk68->unk0 & 0x100) || p->cfg->unk18 == 2) {
                    if (Magic_GetHitOutcome(p, a)) {
                        if (a == p->unk24) {
                            Hud_ShowActorPopup(p->unk24);
                        } else if (a->unk5E & 1) {
                            Enemy_PlayMissEffect(a);
                        } else {
                            Player_StartMissReaction();
                        }
                    } else {
                        magic_hit_handlers[p->cfg->unk10](p, a);
                        hits = 0;
                        for (tries = 0, k = 0; k != 12; k++) {
                            if (p->cfg->unk32[k] != 0) {
                                tries++;
                                if (Magic_ShouldApplyStatus(p, p->unk24, k)) {
                                    Magic_StartStatusTimer(p, a, k);
                                    magic_status_handlers[k](p->cfg->unk32[k], a);
                                    hits++;
                                }
                            }
                        }
                        if (p->cfg->unk10 == 5 && tries != 0 && hits == 0) {
                            Hud_ShowActorPopup(a);
                        }
                    }
                }
                Magic_CreateHitPresentation(p, a);
                if (!(p->cfg->unk2 & 4)) {
                    p->unk4 = 0;
                    if (p->unk34 != NULL && (p->unk34->unk8 & 1)) {
                        p->unk34->unk0 = 7;
                        p->unk34->unk8 &= ~1;
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
            p->unk34->vx = p->vx;
            p->unk34->vy = p->vy;
            p->unk34->vz = p->vz;
            if (p->unk4 == 0 && (p->unk34->unk8 & 1)) {
                p->unk34->unk0 = 7;
                p->unk34->unk8 &= ~1;
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
        if ((flags & 2) || t->unk50 == -1) {
            dz = 0.0f;
            dy = 0.0f;
            dx = 0.0f;
        } else {
            dx = t->x - arg0->x;
            if (t->unk64->unk0 == 1) {
                dy = t->unk68->unk94 - arg0->y;
            } else {
                dy = t->y + t->unk64->unk1C * t->scale * 0.5 - arg0->y;
            }
            dz = t->z - arg0->z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            dx = speeds.v[arg0->cfg->unk28] * dx / d;
            dy = speeds.v[arg0->cfg->unk28] * dy / d;
            dz = speeds.v[arg0->cfg->unk28] * dz / d;
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
        dx = turns.v[arg0->cfg->unk2E] * dx / d;
        dy = turns.v[arg0->cfg->unk2E] * dy / d;
        dz = turns.v[arg0->cfg->unk2E] * dz / d;
        arg0->vx = arg0->vx * 0.9 + dx;
        arg0->vy = arg0->vy * 0.9 + dy;
        arg0->vz = arg0->vz * 0.9 + dz;
    }
    if (arg0->cfg->unk2A & 1) {
        arg0->vy -= 0.3;
    }
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    if (arg0->cfg->unk14 != 0) {
        Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &magic_coll);
        switch (arg0->cfg->unk14) {
            case 1:
                if (arg0->y < magic_coll.y) {
                    arg0->unkA |= 1;
                    arg0->unk4 = 8;
                    arg0->vz = 0.0f;
                    arg0->vy = 0.0f;
                    arg0->vx = 0.0f;
                    if (arg0->unk34 != NULL) {
                        arg0->unk34->unk0 = 15;
                        arg0->unk34->unk8 &= ~1;
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
        if (arg0->cfg->unk2A & 1) {
            arg0->vy -= 0.3;
        }
        arg0->y += arg0->vy;
        if (arg0->cfg->unk14 == 1) {
            Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &magic_coll);
            if (arg0->y < magic_coll.y) {
                arg0->y = magic_coll.y;
                arg0->unkA |= 1;
                arg0->unk4 = 8;
                arg0->vz = 0.0f;
                arg0->vy = 0.0f;
                arg0->vx = 0.0f;
                if (arg0->unk34 != NULL) {
                    arg0->unk34->unk0 = 15;
                    arg0->unk34->unk8 &= ~1;
                }
                Camera_Shake(1);
                Magic_CreateGroundHitPresentation(arg0, arg0->target);
            }
        }
        if (arg0->cfg->unk18 == 0 && !(arg0->target->unk60 & 1)) {
            arg0->x = arg0->target->x;
            arg0->z = arg0->target->z;
        }
    }
}

extern f32 D_8007AA24;
extern f32 D_8007AA28;
extern f32 D_8007AA44;
extern ActorStats* D_8007AA84;
Actor* Magic_FindTargetInRange(MagicEffect* arg0, s32 arg1) {
    Actor* a;
    Unk8007B908_b* p;
    s32 n;
    f32 dx;
    f32 dy;
    Actor* ret;
    f32 dz;
    f32 dist;
    Actor* target;

    target = arg0->target;
    if (target != NULL) {
        if (!(target->unk5E & 1)) {
            ret = (Actor*)D_8007AA20;
            if (Magic_WasActorHitBySlot(arg1, target)) {
                ret = NULL;
            } else {
                dx = ret->x - arg0->x;
                dz = ret->z - arg0->z;
                dy = (ret->y + ret->unk64->unk1C * ret->scale * 0.5 - arg0->y) * 0.5;
                dist = sqrtf(dx * dx + dy * dy + dz * dz);
                if (arg0->cfg->unk1C + ret->unk64->unk18 * ret->scale < dist) {
                    ret = NULL;
                }
            }
        } else {
            n = enemy_count;
            p = (Unk8007B908_b*)enemy_slots;
            while (n != 0) {
                if (p->unk7C != -1) {
                    a = (Actor*)p->unk2C;
                    ret = a;
                    if (!Magic_WasActorHitBySlot(arg1, a)) {
                        dx = a->x - arg0->x;
                        dz = a->z - arg0->z;
                        switch (a->unk64->unk0) {
                            default:
                                dy = 0.0f;
                                break;
                            case 0:
                                dy = (a->y + a->unk64->unk1C * a->scale * 0.5 - arg0->y) * 0.5;
                                break;
                            case 1:
                                dy = (a->unk68->unk94 - arg0->y) * 0.5;
                                break;
                        }
                        dist = sqrtf(dx * dx + dy * dy + dz * dz);
                        if (dist < arg0->cfg->unk1C + a->unk64->unk18 * a->scale) {
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
                magic_target_enemy_rec = (struct Enemy*)p;
            }
        }
    } else {
        ret = NULL;
    }
    return ret;
}

Actor* Magic_FindEligibleTarget(MagicEffect* arg0, s32 arg1) {
    Actor* ret;
    Unk8007B908_b* p;
    s32 n;

    if (!(arg0->target->unk5E & 1)) {
        ret = (Actor*)D_8007AA20;
        if (Magic_WasActorHitBySlot(arg1, (Actor*)D_8007AA20)) {
            ret = NULL;
        }
    } else if ((ret = arg0->target) == NULL || Magic_WasActorHitBySlot(arg1, ret)) {
        n = enemy_count;
        ret = NULL;
        p = (Unk8007B908_b*)enemy_slots;
        while (n != 0) {
            if (p->unk7C != -1) {
                if (!Magic_WasActorHitBySlot(arg1, (Actor*)p->unk2C)) {
                    ret = (Actor*)p->unk2C;
                    magic_target_enemy_rec = (struct Enemy*)p;
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

extern s32 D_8007AA10;
extern u8 fade_damage_flash[];
void Fade_Start(s32, s32, u8*);
void Magic_ApplyEffectDamage(MagicEffect* arg0, Actor* arg1) {
    u16 dmg;
    u16 flag;

    flag = 0;
    dmg = Magic_CalculateEffectDamage(arg0->cfg, arg0->unk24);
    if (arg0->unk24->unk68->unk0 & 1) {
        dmg >>= 1;
    }
    if (arg1->unk5E & 1) {
        if (D_8007AA10 & 0x1000) {
            if (Math_Rand((D_8007AA10 & 0x10000) ? 4 : 0x20) == 0) {
                dmg += (dmg + 1) >> 1;
                Fade_Start(4, 0, fade_damage_flash);
                flag = 0x4000;
            }
        }
        if (Enemy_TakeDamage(Enemy_GetSlotIndex(arg1), dmg, arg0->cfg->unk6[0], arg0->cfg->unk2 | flag, arg0->unk24) != 0) {
            D_8007AA1C->unk2A++;
        }
    } else {
        if (Math_Rand(0x20) == 0) {
            dmg += (dmg + 1) >> 1;
            Fade_Start(4, 0, fade_damage_flash);
            flag = 0x4000;
        }
        Player_TakeDamage(dmg, arg0->cfg->unk2 | flag, arg0->unk24);
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u16 unkA;
} Unk8001860CRec;
void Effect_AddFloatingNumber(Actor*, s32, s32);
void Magic_HealTarget(MagicEffect* arg0, Actor* arg1) {
    u16 amt;
    s32 pad;

    if (arg1->unk5E & 1) {
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        amt = arg1->unk64->unk6 * arg0->cfg->unkC / 100;
        amt += Math_Rand(amt >> 2);
        ((Unk8001860CRec*)magic_target_enemy_rec)->unkA += amt;
        if (((Unk8001860CRec*)magic_target_enemy_rec)->unkA > arg1->unk64->unk6) {
            ((Unk8001860CRec*)magic_target_enemy_rec)->unkA = arg1->unk64->unk6;
        }
    } else {
        amt = (D_8007AA1C->unk24[arg0->cfg->unk6[0]] >> 1) + arg1->unk64->unk6 * arg0->cfg->unkC / 100;
        amt += Math_Rand(amt >> 2);
        if (arg1->unk64->unk4 != arg1->unk64->unk6) {
            arg1->unk64->unk4 += amt;
            if (arg1->unk64->unk4 > arg1->unk64->unk6) {
                arg1->unk64->unk4 = arg1->unk64->unk6;
            }
            D_8007AA1C->unk2A++;
        }
    }
    Effect_AddFloatingNumber(arg1, 1, amt);
}

void Magic_TransferTargetResource(MagicEffect* arg0, Actor* arg1) {
    u16 amt;
    Actor* pl;

    pl = (Actor*)D_8007AA20;
    if (arg1->unk5E & 1) {
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        amt = (((Unk8007B908_b*)magic_target_enemy_rec)->unkC * 11 + 63) >> 6;
        ((Unk8007B908_b*)magic_target_enemy_rec)->unkC -= amt;
        if (player_state.unk7C->unk8 != player_state.unk7C->unkA) {
            pl->unk64->unk8 += amt;
            if (pl->unk64->unk8 > pl->unk64->unkA) {
                pl->unk64->unk8 = pl->unk64->unkA;
            }
            player_state.unk14->unk2A++;
        }
    } else {
        amt = (arg1->unk64->unk8 * 11 + 63) >> 6;
        arg1->unk64->unk8 -= amt;
        magic_target_enemy_rec = (struct Enemy*)&enemy_slots[Enemy_GetSlotIndex(arg1)];
        ((Unk8007B908_b*)magic_target_enemy_rec)->unkC += amt;
        if (((Unk8007B908_b*)magic_target_enemy_rec)->unkC > arg0->unk24->unk64->unkA) {
            ((Unk8007B908_b*)magic_target_enemy_rec)->unkC = arg0->unk24->unk64->unkA;
        }
    }
    Effect_AddFloatingNumber(arg1, 1, amt);
}

void func_80018968(s32 arg0, Actor* arg1) {
    if (arg1->unk5E & 1) {
        arg1->unk50 = -1;
        enemy_count--;
    } else if (!(battle_flags & 0x100)) {
        battle_flags |= 0x10;
        D_8007AA1C->unk2A++;
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_800189F0(s32 arg0, Actor* arg1) {
    if (map_flags == 4 && map_flag4_return_map != -1 && !(map_subarea_def->unk14 & 4)) {
        exit_destination.unk0 = map_flag4_return_map;
        exit_destination.unk4 = map_flag4_return_subarea;
        exit_destination.unk8 = map_flag4_return_entry;
        player_spawn_type = 0x108;
        player_state.unk6 = 0;
        player_state.unk14->unk2A++;
        core_flags |= 0x80;
        core_transition_timer = 0x1E;
    }
}

void Magic_ApplyZeroDamageHit(MagicEffect* arg0, Actor* arg1) {
    if (arg0->cfg->unk18 != 2) {
        if (arg1->unk5E & 1) {
            Enemy_TakeDamage(Enemy_GetSlotIndex(arg1), 0, 0, 4, arg0->unk24);
            D_8007AA1C->unk2A++;
        } else {
            Player_TakeDamage(0, 4, arg0->unk24);
        }
    }
}

void func_80018B40(s32 arg0, Actor* arg1) {
    if ((map_flags & 8) && map_flag8_return_map != -1 && !(map_subarea_def->unk14 & 8) && map_id != 0x1E &&
        map_id != 0x22) {
        exit_destination.unk0 = map_flag8_return_map;
        exit_destination.unk4 = map_flag8_return_subarea;
        exit_destination.unk8 = map_flag8_return_entry;
        player_spawn_type = 0x108;
        player_state.unk6 = 0;
        player_state.unk14->unk2A++;
        core_flags |= 0x80;
        core_transition_timer = 0x1E;
    }
}

void Magic_RemoveEnemyOrDamagePlayer(MagicEffect* arg0, Actor* arg1) {
    if (arg1->unk5E & 1) {
        if (!(battle_flags & 0x100)) {
            Hud_ClearActorStatusIndicators(arg1);
            arg1->unk50 = -1;
            arg1->unk60 &= ~1;
            enemy_count--;
            D_8007AA1C->unk2A++;
        } else {
            Hud_ShowActorPopup(arg1);
        }
    } else {
        Player_TakeDamage(arg1->unk64->unk4 * 4, 4, arg0->unk24);
    }
}

void Magic_ClearActorStatuses(s32 arg0, Actor* arg1) {
    if (arg1->unk68->unk0 != 0) {
        arg1->unk68->unk0 = 0;
        if (arg1->unk5E & 1) {
            Enemy_GetSlotIndex(arg1);
        }
        arg1->unk68->unk8A = 0x10;
        arg1->unk68->unk88 = arg1->unk64->unkE;
        arg1->unk68->unk86 = arg1->unk64->unkC;
        arg1->unk68->unk90 = 1.0f;
        if (!(arg1->unk5E & 1)) {
            D_8007AA1C->unk2A++;
        }
    }
}

void Magic_DamageAndClearStatuses(s32 arg0, Actor* arg1) {
    Magic_ApplyEffectDamage((void*)arg0, arg1);
    Magic_ClearActorStatuses(arg0, arg1);
}

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ f32 x;
    /* 0x30 */ f32 y;
    /* 0x34 */ f32 z;
    /* 0x38 */ u8 pad38[0x44];
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ u8 pad7E[0xB2];
} Unk80018DC0Rec; // size = 0x130
f32 Math_Atan2(f32, f32);
void Magic_SelectClosestAimTarget(MagicEffect* arg0) {
    f32 angle;
    f32 best;
    f32 d;
    s32 n;
    Unk80018DC0Rec* p;
    Actor* caster;

    caster = arg0->unk24;
    if (caster->unk5E & 1) {
        arg0->target = (Actor*)D_8007AA20;
        return;
    }
    if ((arg0->cfg->unk2 & 8) && (arg0->vx != 0.0f || arg0->vz != 0.0f)) {
        angle = Math_Atan2(arg0->vx, arg0->vz);
    } else {
        angle = caster->rot;
    }
    caster = arg0->unk24;
    best = 9.424778f;
    n = enemy_count;
    p = (Unk80018DC0Rec*)enemy_slots;
    while (n != 0) {
        if (p->unk7C != -1) {
            magic_temp_vec.x = p->x - caster->x;
            magic_temp_vec.y = p->z - caster->z;
            Math_RotateVec2(angle, &magic_temp_vec);
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
                arg0->target = (Actor*)&p->x;
            }
            n--;
        }
        p++;
    }
}

void Magic_SelectFirstActiveTarget(MagicEffect* arg0) {
    s32 i;
    Unk8007B908_b* p;

    if (arg0->unk24->unk5E & 1) {
        arg0->target = (Actor*)D_8007AA20;
        return;
    }
    p = (Unk8007B908_b*)enemy_slots;
    i = 6;
    while (i != 0 && p->unk7C == -1) {
        i--;
        p++;
    }
    if (i != 0) {
        arg0->target = (Actor*)p->unk2C;
        return;
    }
    arg0->target = NULL;
}

void Magic_TargetCaster(MagicEffect* arg0) {
    arg0->target = arg0->unk24;
}

void Magic_ApplyShrinkStatus(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->unk68->unk0 |= 1;
        arg1->scale = arg1->unk64->unk20 * 0.5;
        Hud_StartActorStatusIndicator(arg1, 1, 4, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_800190BC(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 2;
    Hud_StartActorStatusIndicator(arg1, 2, 2, -1);
}

void func_80019104(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 4;
    switch (arg0) {
        case 1:
            arg1->unk68->unk8A = 0x18;
            break;
        case 2:
            arg1->unk68->unk8A = 0x20;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 4, 3, -1);
}

void func_80019184(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->unk68->unk0 |= 8;
        arg1->unk60 |= 1;
        Hud_StartActorStatusIndicator(arg1, 8, arg0 - 1, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_8001920C(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x10;
    switch (arg0) {
        case 1:
            arg1->unk68->unk90 = 0.5f;
            break;
        case 2:
            arg1->unk68->unk90 = 2.0f;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 0x10, (arg1->unk68->unk90 > 1.0) ? 8 : 9, -1);
}

void func_800192C8(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x20;
    switch (arg0) {
        case 1:
            arg1->unk68->unk86 = arg1->unk64->unkC * 2;
            Hud_StartActorStatusIndicator(arg1, 0x20, 7, -1);
            break;
        case 2:
            arg1->unk68->unk86 = arg1->unk64->unkC * 4;
            Hud_StartActorStatusIndicator(arg1, 0x20, 7, -1);
            break;
        case 3:
            arg1->unk68->unk86 = arg1->unk64->unkC >> 1;
            Hud_StartActorStatusIndicator(arg1, 0x20, 0xC, -1);
            break;
    }
}

void func_800193A4(s32 arg0, Actor* arg1) {
    if (!(battle_flags & 0x100)) {
        arg1->unk68->unk0 |= 0x40;
        Hud_StartActorStatusIndicator(arg1, 0x40, 0xB, -1);
    } else {
        Hud_ShowActorPopup(arg1);
    }
}

void func_80019408(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x80;
    Hud_StartActorStatusIndicator(arg1, 0x80, 0xA, -1);
}

void func_80019450(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x100;
    Hud_StartActorStatusIndicator(arg1, 0x100, 4, -1);
}

void func_80019498(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x200;
    Hud_StartActorStatusIndicator(arg1, 0x200, 3, -1);
}

void func_800194E0(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x400;
    switch (arg0) {
        case 1:
            arg1->unk68->unk88 = arg1->unk64->unkE >> 1;
            break;
        case 2:
            arg1->unk68->unk88 = arg1->unk64->unkE - (arg1->unk64->unkE >> 2);
            break;
        case 3:
            arg1->unk68->unk88 = arg1->unk64->unkE + (arg1->unk64->unkE >> 1);
            break;
        case 4:
            arg1->unk68->unk88 = arg1->unk64->unkE * 2;
            break;
    }
    Hud_StartActorStatusIndicator(arg1, 0x400, (arg1->unk64->unkE < arg1->unk68->unk88) ? 5 : 6, -1);
}

void func_800195E0(s32 arg0, Actor* arg1) {
    arg1->unk68->unk0 |= 0x800;
}

typedef struct {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
} Unk800195FCStats;
typedef struct {
    /* 0x000 */ u8 pad0[0x28];
    /* 0x028 */ Unk800195FCStats* unk28;
    /* 0x02C */ u8 pad2C[0x104];
} Unk800195FCRec; // size = 0x130
typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 stats[1];
} Unk8007A9D0;
extern Unk8007A9D0 player_stats;
u16 Magic_CalculateEffectDamage(SpellDef* arg0, Actor* arg1) {
    u16 lv;
    u16* p;
    f32 sum;
    f32 step;
    s32 i;

    if (arg1->unk5E & 1) {
        lv = ((Unk800195FCRec*)enemy_slots)[Enemy_GetSlotIndex(arg1)].unk28->unk2A;
    } else {
        p = &magic_damage_bonus_stats[arg0->unk6[0] * 2];
        lv = player_stats.stats[arg0->unk6[0]];
        lv += player_stats.stats[*p++] >> 4;
        lv += player_stats.stats[*p++] >> 3;
        lv += player_stats.stats[*p] >> 3;
    }
    sum = arg0->unkC * 0.02;
    step = sum * 0.2;
    for (i = 0; i != lv; i++) {
        sum += step;
        step *= 1.03;
    }
    return (u32)sum;
}

extern MagicVisualDef D_800C18D8[];
EffectModel* Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, MagicVisualDef*, Vec3f*, Actor*);
void Sfx_Play(u8, s8, s32);


EffectModel* Effect_CreateModelEffect(u16, u16, u16, s32, u16, f32, f32, f32, f32, f32, f32, f32);
EffectModel* Magic_CreateVisualEffect(u16 arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, MagicVisualDef* arg6, Vec3f* arg7, Actor* arg8) {
    f32 sx;
    f32 sy;

    switch (arg6->unk0) {
        case 0:
            sx = arg8->unk64->unk18 * arg8->scale * arg7->x;
            break;
        case 1:
            sx = arg8->unk64->unk1C * arg8->scale * arg7->x;
            break;
        case 3:
            sx = arg7->z * arg7->x;
            break;
        default:
            do {} while (0);
            sx = arg7->x;
            break;
    }
    switch (arg6->unk2) {
        case 0:
            sy = arg8->unk64->unk18 * arg8->scale * arg7->y;
            break;
        case 1:
            sy = arg8->unk64->unk1C * arg8->scale * arg7->y;
            break;
        case 3:
            sy = arg7->z * arg7->y;
            break;
        default:
            do {} while (0);
            sy = arg7->y;
            break;
    }
    return Effect_CreateModelEffect(arg6->unk8, arg6->unk4, arg6->unk6, arg0 & 0xFF, arg1, arg2, arg3, arg4, arg5, sx, sy, sx);
}

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[4];
} Unk800C363C; // size = 0xC
extern Unk800C363C* D_800C363C[];
void Effect_StartConvergeEmitter(s32, s32, f32, f32, f32, f32);
void Effect_SpawnBurst(s32, f32, f32, f32, f32);
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[8];
} Unk800C363C_c; // size = 0xC
f32 Math_Atan2(f32, f32);
void Magic_CreateCastPresentation(MagicEffect* arg0, Actor* arg1) {
    EffectModel* ret;
    SpellDef* cfg;
    Unk800C363C_c* fx;
    f32 h;
    SpellFxDef* def;
    MagicVisualDef* tbl;
    f32 y;
    f32 angle;

    def = arg0->def;
    cfg = arg0->cfg;
    if (def->unk0 >= 0) {
        tbl = &D_800C18D8[def->unk0];
        magic_temp_vec.x = def->unk8;
        magic_temp_vec.y = def->unkC;
        magic_temp_vec.z = cfg->unk1C;
        if (arg0->vx != 0.0f || arg0->vz != 0.0f) {
            angle = Math_Atan2(arg0->vx, arg0->vz);
        } else {
            angle = arg1->rot;
        }
        arg0->unk34 = Magic_CreateVisualEffect(def->unk2, def->unk4, arg0->x, arg0->y, arg0->z, angle, tbl, &magic_temp_vec, arg1);
        arg0->unk34->vx = arg0->vx;
        arg0->unk34->vy = arg0->vy;
        arg0->unk34->vz = arg0->vz;
    } else {
        arg0->unk34 = NULL;
    }
    fx = &((Unk800C363C_c**)D_800C363C)[arg0->unk0][arg0->unk2];
    if (fx->unk0 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->scale;
        y = arg1->y + arg1->unk64->unk1C * arg1->scale;
        switch (fx->unk0) {
            case 1:
                Effect_StartConvergeEmitter(fx->unk2, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->unk2, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk40 >= 0) {
        Sfx_Play(def->unk41, def->unk40, 0xFF);
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
    tbl = &D_800C18D8[def->unk10];
    magic_temp_vec.x = def->unk18;
    magic_temp_vec.y = def->unk1C;
    magic_temp_vec.z = cfg->unk1C;
    if (def->unk14 & 0x10) {
        angle = arg0->unk4 * 3.141592653589793 / 10.0;
    } else {
        angle = arg1->rot;
    }
    ret = Magic_CreateVisualEffect(def->unk12, def->unk14, arg0->x, arg0->y, arg0->z, angle, tbl, &magic_temp_vec, arg0->unk24);
    ret->vx = arg0->vx;
    ret->vy = arg0->vy;
    ret->vz = arg0->vz;
    if (def->unk46 >= 0) {
        Sfx_Play(def->unk47, def->unk46, 0xFF);
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
} Unk800C363C_b; // size = 0xC
void Magic_CreateHitPresentation(MagicEffect* arg0, Actor* arg1) {
    SpellDef* cfg;
    MagicVisualDef* tbl;
    Unk800C363C_b* fx;
    SpellFxDef* def;
    u16 flags;
    f32 y;
    f32 h;
    s32 pad[2];

    def = (SpellFxDef*)arg0->def;
    cfg = arg0->cfg;
    if (def->unk30 >= 0) {
        tbl = &D_800C18D8[def->unk30];
        magic_temp_vec.x = def->unk38;
        magic_temp_vec.y = def->unk3C;
        magic_temp_vec.z = cfg->unk1C;
        flags = def->unk34;
        if (flags & 0x40) {
            arg1 = arg0->unk24;
        }
        if (arg1->unk64->unk0 == 1) {
            if (flags & 0x100) {
                y = arg1->unk68->unk94;
            } else {
                y = arg1->y;
            }
        } else if (flags & 0x100) {
            y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
        } else {
            y = arg1->y;
        }
        arg0->unk38 = Magic_CreateVisualEffect(def->unk32, flags, arg1->x, y, arg1->z, arg1->rot, tbl, &magic_temp_vec, arg1);
        arg0->unk38->vx = arg0->vx;
        arg0->unk38->vy = arg0->vy;
        arg0->unk38->vz = arg0->vz;
    } else {
        arg0->unk38 = NULL;
    }
    fx = &((Unk800C363C_b**)D_800C363C)[arg0->unk0][arg0->unk2];
    if (fx->unk8 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->unk64->unk20;
        y = arg1->y + arg1->unk64->unk1C * arg1->unk64->unk20;
        switch (fx->unk8) {
            case 1:
                Effect_StartConvergeEmitter(fx->unkA, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->unkA, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk42 >= 0) {
        Sfx_Play(def->unk43, def->unk42, 0xFF);
    } else if (arg0->unk24 != arg0->target) {
        Sfx_Play(0, 0x18, 0xFF);
    }
}

void Magic_CreateGroundHitPresentation(MagicEffect* arg0, Actor* arg1) {
    EffectModel* ret;
    SpellDef* cfg;
    Unk800C363C* fx;
    SpellFxDef* def;
    f32 h;
    f32 y;
    MagicVisualDef* tbl;

    def = (SpellFxDef*)arg0->def;
    cfg = arg0->cfg;
    if (def->unk20 >= 0) {
        tbl = &D_800C18D8[def->unk20];
        magic_temp_vec.x = def->unk28;
        magic_temp_vec.y = def->unk2C;
        magic_temp_vec.z = cfg->unk1C;
        ret = Magic_CreateVisualEffect(def->unk22, def->unk24, arg0->x, arg0->y, arg0->z, arg1->rot, tbl, &magic_temp_vec, arg0->unk24);
        ret->vx = arg0->vx;
        ret->vy = arg0->vy;
        ret->vz = arg0->vz;
    }
    fx = &D_800C363C[arg0->unk0][arg0->unk2];
    if (fx->unk4 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->scale;
        y = arg1->y + arg1->unk64->unk1C * arg1->scale;
        switch (fx->unk4) {
            case 1:
                Effect_StartConvergeEmitter(fx->unk6, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                Effect_SpawnBurst(fx->unk6, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk44 >= 0) {
        Sfx_Play(def->unk45, def->unk44, 0xFF);
    }
}

void Magic_StepActorStatusTimers(Actor* arg0) {
    ActorBattle* data = arg0->unk68;
    s32 bit = 1;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (data->unk0 & bit) {
            if (--data->timers[i] == 0) {
                data->unk0 ^= bit;
                if (bit & 1) {
                    arg0->scale = arg0->unk64->unk20;
                } else if (bit & 4) {
                    arg0->unk68->unk8A = 0x10;
                } else if (bit & 0x10) {
                    arg0->unk68->unk90 = 1.0f;
                } else if (bit & 0x20) {
                    arg0->unk68->unk86 = arg0->unk64->unkC;
                } else if (bit & 0x400) {
                    arg0->unk68->unk88 = arg0->unk64->unkE;
                } else if (bit & 8) {
                    arg0->unk60 &= ~1;
                }
            }
        }
        bit <<= 1;
    }
}

s32 Magic_WasActorHitBySlot(s32 arg0, Actor* arg1) {
    return magic_slot_bits[arg0] & arg1->unk68->unk8C;
}

void Magic_MarkActorHitBySlot(s32 arg0, Actor* arg1) {
    arg1->unk68->unk8C |= magic_slot_bits[arg0];
}

void Magic_ResetHitTracking(void) {
    s32 i;

    D_8007AB18 = 0;
    for (i = 0; i < 6; i++) {
        enemy_slots[i].unk124 = 0;
    }
}

void Magic_ClearSlotHitTracking(s32 arg0) {
    s32 i;

    player_state.unk110 &= ~magic_slot_bits[arg0];
    for (i = 0; i < 6; i++) {
        enemy_slots[i].unk124 &= ~magic_slot_bits[arg0];
    }
}

s32 Magic_GetHitOutcome(MagicEffect* arg0, Actor* arg1) {
    s32 ret;

    if (arg0->unkA & 4) {
        ret = 2;
    } else {
        ret = Math_Rand(100) < arg0->cfg->unkE;
        if (ret != 0) {
            if (arg1 != arg0->unk24) {
                if (arg1->unk5E & 1) {
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
    } else if (cfg = arg0->cfg, cfg->unk18 == 2) {
        ret = 1;
    } else if (arg1->unk5E & 1) {
        ret = Math_Rand(64) < magic_status_chances[arg2];
    } else {
        n = (player_state.unk8 & 0x8000) ? 28 : 32;
        ret = Math_Rand(n) < magic_status_chances[arg2];
    }
    return ret;
}

void Magic_StartStatusTimer(MagicEffect* arg0, Actor* arg1, s32 arg2) {
    if (arg1 != arg0->unk24) {
        arg1->unk68->timers[arg2] = Math_Rand(magic_status_time_range_other[arg2]) + 2;
    } else {
        arg1->unk68->timers[arg2] = Math_Rand(magic_status_time_range_self[arg2]) + 3;
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
