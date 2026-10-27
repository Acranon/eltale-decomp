#include "game/gfx/effect.h"
#include "game/actor/actor.h"
#include "game/camera/camera.h"
#include "game/map/map.h"
#include "game/actor/anim.h"
#include "game/core/dma.h"
#include "game/core/main.h"
#include "game/env/env.h"
#include "game/math/math.h"
#include "game/player/player.h"

/*
 * Sprite particles, model effects, floating numbers, streaks, and terrain rings.
 * Original file: 1B200.c (ROM 0x1B200).
 */

/* Not defined by a module: overlay data at fixed addresses. */
extern u8 D_800EB5E4[][4];
extern AnimSet D_800EB2B4[];
extern u8 D_800CADA8[][4];
extern EffectTexAnim D_800DA0F0[];
extern Gfx D_800EB6D0[];
extern Gfx D_800EB880[];
extern Gfx D_800EB8E8[];

/* This file's .bss, 800863F0..80087E30 (in address order; first declaration
 * fixes the order). 800865C0..80087E00 is the 16-byte-aligned run that holds effect_stat_up_marker_slots (Effect_ResetStatUpMarkers shares a lui between its pairs only when it
 * is defined here). Labels splat put inside these arrays (D_800865CC..,
 * D_8008779C.., D_8008793C) are gone; no asm uses them now. */


/* This file's .data, 8004EE20..8004F060: effect descriptors (EffectSprite,
 * 0x40 bytes each) and their tables, in source order: these first, then
 * Effect_UpdateMapObjEmitters's static descriptor (8004EE9C), effect_mapobj_particle_alpha_anim, Effect_SpawnFlipbookSprite's
 * static descriptor (8004EF0C) and the tables after Effect_SpawnFlipbookSprite. Both
 * descriptors must be function statics: IDO then stores their fields through
 * lui/%lo instead of the descriptor's address register. */
EffectSprite effect_foot_particle_template = {
    0x0C, 0, 0, Effect_UpdateFootParticle, 0x02, 0x10, 0x10, 0x00, 0, { 0 }, (u8*)0x800C3650, (Gfx*)0x800C3790,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0,
};
f32 effect_foot_particle_scale_anim[12] = {
    3.25f, 3.24f, 3.23f, 3.22f, 3.21f, 3.2f, 3.0f, 2.8f, 2.6f, 2.4f, 2.2f, 2.0f,
};
u8 effect_foot_particle_alpha_anim[12] = { 0x10, 0x20, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xB0, 0xA0, 0x80, 0x40 };
s32 effect_mapobj_emitter_count;
u16 effect_model_frame_counter;
s32 effect_mapobj_emitter_prev_count;
EffectFootEmitter effect_foot_emitter_slots[8];
EffectMapObjEmitter effect_mapobj_emitter_buf1[8];
EffectMapObjEmitter effect_mapobj_emitter_buf0[8];
EffectFloatingNumber effect_floating_number_slots[10];
EffectConvergeEmitter effect_converge_emitter_slots[8];
EffectModel effect_model_slots[32];
EffectStreak effect_streak_slots[32];
EffectStatUpMarker effect_stat_up_marker_slots[4];
EffectRing effect_ring_slots[4];
u16 effect_loaded_tlut_index;
Vec2f effect_temp_vec;
u8 D_80087E08[8]; /* unreferenced */
CollResult effect_ring_coll;


void Effect_ResetAll(void) {
    Effect_ResetFootEmitters();
    Effect_ResetMapObjEmitters();
    Effect_ResetConvergeEmitters();
    Effect_ResetStreaks();
    Effect_ResetStatUpMarkers();
    Effect_ResetFloatingNumbers();
    Effect_ResetModelEffects();
    Effect_ResetRings();
}

void Effect_UpdateAndDrawAll(struct GfxFrameData* arg0) {
    Effect_UpdateFootEmitters();
    Effect_UpdateMapObjEmitters();
    Effect_UpdateConvergeEmitters();
    Effect_UpdateAndDrawStreaks(arg0);
    Effect_DrawStatUpMarkers(arg0);
    Effect_UpdateAndDrawRings(arg0);
    Effect_UpdateAndDrawModelEffects(arg0);
    Effect_DrawFloatingNumbers();
}

void Effect_ResetFootEmitters(void) {
    s32 i = 8;
    EffectFootEmitter* p = effect_foot_emitter_slots;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void Effect_StartFootEmitter(Actor* arg0) {
    s32 i = 7;
    EffectFootEmitter* p = effect_foot_emitter_slots;

    while (i != 0 && p->timer != 0) {
        i--;
        p++;
    }
    p->timer = 4;
    p->actor = arg0;
}

void Effect_UpdateFootEmitters(void) {
    s32 i;
    EffectFootEmitter* p;
    Actor* pos;

    i = 8;
    p = effect_foot_emitter_slots;
    do {
        if (p->timer != 0) {
            p->timer--;
            if (p->timer & 1) {
                pos = p->actor;
                effect_foot_particle_template.x = pos->x;
                effect_foot_particle_template.y = pos->y + 1.0f;
                effect_foot_particle_template.z = pos->z;
                effect_temp_vec.x = 0.0f;
                effect_temp_vec.y = 0.7f;
                Math_RotateVec2(pos->rot, &effect_temp_vec);
                effect_foot_particle_template.unk34 = 0.2f;
                effect_foot_particle_template.unk30 = effect_temp_vec.x;
                effect_foot_particle_template.unk38 = effect_temp_vec.y;
                Effect_AllocateSprite(&effect_foot_particle_template);
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void Effect_UpdateFootParticle(EffectSprite* arg0) {
    arg0->x += arg0->unk30;
    arg0->y += arg0->unk34;
    arg0->z += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.8;
    arg0->scaleX = arg0->scaleY = effect_foot_particle_scale_anim[arg0->life];
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, effect_foot_particle_alpha_anim[arg0->life]);
}

void Effect_ResetMapObjEmitters(void) {
    s32 i;
    EffectMapObjEmitter* a;
    EffectMapObjEmitter* b;

    effect_mapobj_emitter_prev_count = 0;
    i = 8;
    a = effect_mapobj_emitter_buf1;
    b = effect_mapobj_emitter_buf0;
    do {
        i--;
        b->particleCountdown = 0;
        a->particleCountdown = 0;
        a++;
        b++;
    } while (i != 0);
}

void Effect_QueueMapObjEmitter(f32 x, f32 y, f32 z, MapObj* arg3) {
    s32 pad[4];
    EffectMapObjEmitter* cur;
    EffectMapObjEmitter* prev;
    f32 angle;
    s32 n;

    cur = gfx_frame_index ? effect_mapobj_emitter_buf1 : effect_mapobj_emitter_buf0;
    prev = gfx_frame_index ? effect_mapobj_emitter_buf0 : effect_mapobj_emitter_buf1;
    angle = Math_Atan2(x - camera_state.eyeX, z - camera_state.eyeZ) - camera_state.yaw + 3.141592653589793;
    if (angle < -3.141592653589793) {
        angle += 6.283185307179586;
    } else if (angle > 3.141592653589793) {
        angle -= 6.283185307179586;
    }
    if (angle > -1.5707963267948966 && angle < 1.5707963267948966 && effect_mapobj_emitter_count < 8) {
        n = effect_mapobj_emitter_prev_count;
        cur += effect_mapobj_emitter_count;
        while (n != 0 && arg3 != prev->mapObj) {
            n--;
            prev++;
        }
        if (n != 0) {
            cur->particleCountdown = prev->particleCountdown;
        } else {
            cur->particleCountdown = Math_Rand(4) * 4 + 1;
        }
        cur->x = x;
        cur->y = y;
        cur->z = z;
        cur->particleScale = arg3->scale;
        cur->mapObj = arg3;
        effect_mapobj_emitter_count++;
    }
}

void Effect_UpdateMapObjEmitters(void) {
    static EffectSprite effect_mapobj_particle_template = {
        0x2D, 0, 0, Effect_UpdateMapObjParticle, 0x02, 0x10, 0x10, 0x00, 0, { 0 }, (u8*)0x800C3650, (Gfx*)0x800C37E0,
        0.0f, 0.0f, 0.0f, 0.0f, 4.0f, 4.0f, 0.1f, 0.25f, 0.05f, 0,
    };
    EffectMapObjEmitter* p;
    s32 n;

    effect_mapobj_emitter_prev_count = effect_mapobj_emitter_count;
    p = gfx_frame_index ? effect_mapobj_emitter_buf1 : effect_mapobj_emitter_buf0;
    n = effect_mapobj_emitter_prev_count;
    while (n != 0) {
        if (p->particleCountdown != 0 && --p->particleCountdown == 0) {
            effect_mapobj_particle_template.x = p->x;
            effect_mapobj_particle_template.y = p->y;
            effect_mapobj_particle_template.z = p->z;
            effect_mapobj_particle_template.scaleX = effect_mapobj_particle_template.scaleY = p->particleScale;
            Effect_AllocateSprite(&effect_mapobj_particle_template);
            p->particleCountdown = 0x19;
        }
        n--;
        p++;
    }
}

/* Effect_UpdateMapObjParticle's table sits between the two function statics. */
u8 effect_mapobj_particle_alpha_anim[48] = {
    0x08, 0x1C, 0x30, 0x44, 0x58, 0x6C, 0x80, 0x94, 0xA8, 0xBC, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0,
    0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00, 0x00, 0x00,
};

void Effect_UpdateMapObjParticle(EffectSprite* arg0) {
    s32 r;
    s32 g;
    s32 b;

    arg0->x += arg0->unk30;
    arg0->y += arg0->unk34;
    arg0->z += arg0->unk38;
    arg0->scaleX += 0.08;
    arg0->scaleY += 0.08;
    r = D_80084B6C + 0x40;
    g = D_80084B70 + 0x40;
    b = D_80084B74 + 0x40;
    if (r >= 0x100) {
        r = 0xFF;
    }
    if (g >= 0x100) {
        g = 0xFF;
    }
    if (b >= 0x100) {
        b = 0xFF;
    }
    gDPSetEnvColor(gfx_dl_head++, r, g, b, effect_mapobj_particle_alpha_anim[arg0->life]);
}

void Effect_SpawnFlipbookSprite(f32 x, f32 y, f32 z) {
    static EffectSprite effect_flipbook_sprite_template = {
        0x0C, 0, 0, Effect_UpdateFlipbookSprite, 0x04, 0x20, 0x20, 0x00, 0, { 0 }, (u8*)0x800C3830, (Gfx*)0x800C4070,
        0.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f, 0,
    };

    effect_flipbook_sprite_template.x = x;
    effect_flipbook_sprite_template.y = y;
    effect_flipbook_sprite_template.z = z;
    Effect_AllocateSprite(&effect_flipbook_sprite_template);
}

/* The rest of this file's .data (each table belongs to one of the functions below). */
s32 effect_flipbook_frame_ptrs[3] = { 0x800C3E30, 0x800C3C30, 0x800C3A30 };
f32 effect_flipbook_scale_anim[12] = {
    0.88f, 0.88f, 0.84f, 0.84f, 0.82f, 0.82f, 0.8f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f,
};
u8 effect_flipbook_alpha_anim[12] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0xA0, 0xC0, 0xC8, 0x80, 0x60 };
u8 effect_floating_number_colors[4][4] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xC8, 0xFF, 0xC8, 0xFF }, { 0xC8, 0xC8, 0xFF, 0xFF }, { 0xFF, 0x7F, 0x7F, 0xFF },
};
EffectSprite effect_converge_particle_template = {
    0x14, 0, 0, Effect_UpdateConvergeParticle, 0x02, 0x10, 0x10, 0x00, 0, { 0 }, (u8*)0x800C4128, (Gfx*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
EffectSprite effect_burst_particle_template = {
    0x14, 0, 0, Effect_UpdateBurstParticle, 0x02, 0x10, 0x10, 0x00, 0, { 0 }, (u8*)0x800C4128, (Gfx*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
u16 effect_ring_grow_frames[4] = { 0x14, 0xC, 0xC, 0 };
u8 effect_ring_colors[3][4] = { { 0xC8, 0xC8, 0x00, 0x00 }, { 0xC8, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xC8, 0x00 } };
u8 effect_ring_alpha_values[4] = { 0xFF, 0x96, 0x00, 0x00 };
s32 effect_model_tlut_ptrs[4] = { 0x800CAE68, 0x800CB068, 0x800CB268, 0x800CB468 };
u8 effect_stat_up_marker_colors[5][4] = {
    { 0xFF, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0xFF, 0x00 }, { 0x00, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },
};

void Effect_UpdateFlipbookSprite(EffectSprite* arg0) {
    u16 v = arg0->life;

    if (!(v & 3)) {
        arg0->tex = (u8*)effect_flipbook_frame_ptrs[v >> 2];
    }
    arg0->scaleX = arg0->scaleY = effect_flipbook_scale_anim[v];
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, effect_flipbook_alpha_anim[arg0->life]);
}

void Effect_ResetFloatingNumbers(void) {
    s32 i = 10;
    EffectFloatingNumber* p = effect_floating_number_slots;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void Effect_AddFloatingNumber(Actor* arg0, s32 arg1, s32 arg2) {
    s32 pad[2];
    EffectFloatingNumber* var_t0;
    s32 var_v1;
    s32 i;

    i = 9;
    var_t0 = effect_floating_number_slots;
    while ((i != 0) && (var_t0->timer != 0)) {
        i--;
        var_t0++;
    }
    var_t0->timer = 0x2D;
    var_t0->target = arg0;
    var_t0->styleAndColor = arg1;

    if (arg2 < 0) {
        arg2 = -arg2;
    }

    var_t0->numDigits = Text_FormatNumber(arg2, var_t0->digits, 1U);
    var_v1 = 0;

    for (i = 0; i < 10; i++) {
        if ((effect_floating_number_slots[i].timer != 0) && (arg0 == effect_floating_number_slots[i].target)) {
            var_v1++;
        }
    }
    var_t0->stackIndex = var_v1 - 1;
}


/* Not defined by a module: overlay data and a buffer at fixed addresses. */
extern Gfx D_800C40C0[];
extern u8 D_8039E290[];

void Effect_DrawFloatingNumbers(void) {
    s32 n;
    EffectFloatingNumber* d;
    s32 first;
    Actor* actor;
    s32 sx;
    s32 sy;
    f32 y;
    s16 dsdx;
    s16 dtdy;
    s32 w;
    s32 h;
    s32 k;
    u8* dp;
    u8* c;

    first = 0;
    n = 10;
    d = effect_floating_number_slots;
    do {
        if (d->timer) {
            actor = d->target;
            if (actor->stats->unk0 == 0) {
                y = actor->y + actor->stats->unk1C * actor->scale;
            } else if (actor->stats->unk0 == 1) {
                y = actor->battle->unk94;
            } else {
                y = actor->y + 600.0 * actor->scale;
            }
            if (Camera_WorldToScreen(actor->x, y, actor->z, &sx, &sy)) {
                if (!first) {
                    gSPDisplayList(gfx_dl_head++, D_800C40C0);
                    gDPLoadTextureBlock(gfx_dl_head++, D_8039E290, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
                    first++;
                }
                if (d->styleAndColor & 0x8000) {
                    dsdx = 0x280;
                    dtdy = 0x280;
                    w = 6;
                    h = 8;
                } else {
                    dsdx = 0x400;
                    dtdy = 0x400;
                    w = 4;
                    h = 5;
                }
                if (d->timer >= 30) {
                    s32 a = sins((45 - d->timer) << 12) >> 11;
                    if (a < 0) {
                        a = -a;
                    }
                    sy -= a;
                }
                sx -= d->stackIndex * w;
                sy = sy - d->stackIndex * 5 - 8;
                c = effect_floating_number_colors[d->styleAndColor & 0xF];
                gDPPipeSync(gfx_dl_head++);
                gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 255);
                dp = d->digits;
                sx -= (k = d->numDigits) * 4;
                while (k) {
                    k--;
                    if (*dp != 0x20) {
                        gSPTextureRectangle(gfx_dl_head++, (sx - w) << 2, (sy - h) << 2, (sx + w) << 2, (sy + h) << 2, G_TX_RENDERTILE, *dp << 8, 0, dtdy, dsdx);
                        sx += w * 2;
                    }
                    dp++;
                }
            }
            d->timer--;
        }
        n--;
        d++;
    } while (n);
}


void Effect_ResetConvergeEmitters(void) {
    EffectConvergeEmitter* p = effect_converge_emitter_slots;
    s32 i = 8;

    do {
        i--;
        p->framesLeft = 0;
        p++;
    } while (i != 0);
}

void Effect_StartConvergeEmitter(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    EffectConvergeEmitter* p = effect_converge_emitter_slots;
    s32 i = 7;

    while (i != 0 && p->framesLeft != 0) {
        i--;
        p++;
    }
    p->framesLeft = arg1;
    p->colorIndex = arg0;
    p->centerX = arg2;
    p->centerY = arg3;
    p->centerZ = arg4;
    p->radius = arg5;
}

void Effect_UpdateConvergeEmitters(void) {
    EffectConvergeEmitter* p;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    f32 a;
    MtxF mtx;
    f32 b;
    EffectSprite spawn;

    spawn = effect_converge_particle_template;
    p = effect_converge_emitter_slots;
    i = 8;
    do {
        if (p->framesLeft != 0) {
            if (p->framesLeft & 1) {
                a = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
                b = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
                Math_MtxFRotate(&mtx, a, b, 0.0f);
                guMtxXFMF(mtx.mf, 0.0f, 0.0f, p->radius, &x, &y, &z);
                spawn.x = p->centerX + x;
                spawn.y = p->centerY + y;
                spawn.z = p->centerZ + z;
                spawn.unk30 = x * -0.03;
                spawn.unk34 = y * -0.03;
                spawn.unk38 = z * -0.03;
                spawn.unk3C = p->colorIndex;
                Effect_AllocateSprite(&spawn);
            }
            p->framesLeft--;
        }
        i--;
        p++;
    } while (i != 0);
}

void Effect_UpdateConvergeParticle(EffectSprite* arg0) {
    u8* c;

    arg0->x += arg0->unk30;
    arg0->y += arg0->unk34;
    arg0->z += arg0->unk38;
    arg0->unk30 *= 0.9;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.9;
    arg0->roll += 0.39269908169872414;
    if (arg0->life < 10) {
        arg0->scaleX = arg0->scaleY = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->life & 1) {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0xDC);
    } else {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0x20);
    }
}

void Effect_SpawnBurst(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    f32 a;
    f32 b;
    f32 c;
    MtxF mtx;
    EffectSprite spawn;
    spawn = effect_burst_particle_template;
    i = 15;
    do {
        a = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
        b = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
        Math_MtxFRotate(&mtx, a, b, 0.0f);
        guMtxXFMF(mtx.mf, 0.0f, 0.0f, arg4, &a, &b, &c);
        spawn.x = arg1;
        spawn.y = arg2;
        spawn.z = arg3;
        spawn.unk30 = a;
        spawn.unk34 = b;
        spawn.unk38 = c;
        spawn.unk3C = arg0;
        Effect_AllocateSprite(&spawn);
        i--;
    } while (i != 0);
}

void Effect_UpdateBurstParticle(EffectSprite* arg0) {
    u8* c;

    arg0->x += arg0->unk30;
    arg0->y += arg0->unk34;
    arg0->z += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.8;
    arg0->unk38 *= 0.8;
    arg0->roll += 0.39269908169872414;
    if (arg0->life < 10) {
        arg0->scaleX = arg0->scaleY = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->life & 1) {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0xDC);
    } else {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0x20);
    }
}

void Effect_ResetStreaks(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        effect_streak_slots[i].framesLeft = 0;
    }
}

void Effect_UpdateAndDrawStreaks(struct GfxFrameData* arg0) {
    s32 n;
    EffectStreak* p;
    s32 first;
    u32 alpha;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    MtxF mtx;

    first = 0;
    p = effect_streak_slots;
    n = 32;
    do {
        if (p->framesLeft != 0) {
            p->x += p->vx;
            p->y += p->vy;
            p->z += p->vz;
            if (gfx_mtx_index < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(gfx_dl_head++, D_800EB880);
                    first++;
                }
                if (p->framesLeft & 1) {
                    alpha = 250;
                } else {
                    alpha = 150;
                }
                if (p->framesLeft < 8) {
                    alpha = (p->framesLeft * alpha) >> 3;
                }
                Math_MtxFAlignYToVector(&mtx, p->vx, p->vy, p->vz);
                dx = p->x - p->x0;
                dy = p->y - p->y0;
                dz = p->z - p->z0;
                dist = sqrtf(dx * dx + dy * dy + dz * dz);
                Math_MtxFScaleAxes(&mtx, 0.35f, dist * 0.1, 0.35f);
                mtx.mf[3][0] = p->x;
                mtx.mf[3][1] = p->y;
                mtx.mf[3][2] = p->z;
                guMtxF2L(mtx.mf, &arg0->mtx[gfx_mtx_index]);
                gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, alpha);
                gSPDisplayList(gfx_dl_head++, D_800EB8E8);
            }
            p->framesLeft--;
            p->vx *= 0.6;
            p->vy *= 0.6;
            p->vz *= 0.6;
        }
        n--;
        p++;
    } while (n != 0);
}

void Effect_SpawnStreakBurst(f32 x, f32 y, f32 z) {
    s32 n;
    EffectStreak* p;
    s32 count;
    f32 a;
    f32 b;
    f32 r;
    MtxF mtx;

    p = effect_streak_slots;
    n = 31;
    count = 16;
    do {
        while (n != 0 && p->framesLeft != 0) {
            n--;
            p++;
        }
        p->framesLeft = Math_Rand(8) + 10;
        p->x = x;
        p->x0 = x;
        p->y = y;
        p->y0 = y;
        p->z0 = z;
        p->z = z;
        a = Math_Rand(20) * 3.141592653589793 / 10.0;
        b = Math_Rand(20) * 3.141592653589793 / 10.0;
        r = (f32)Math_Rand(10) / 3.0 + 3.0;
        Math_MtxFRotate(&mtx, a, b, 0.0f);
        guMtxXFMF(mtx.mf, 0.0f, 0.0f, r, &p->vx, &p->vy, &p->vz);
        count--;
    } while (count != 0 && n != 0);
}

void Effect_ResetRings(void) {
    s32 i = 4;
    EffectRing* p = effect_ring_slots;

    do {
        i--;
        p->state = 0;
        p++;
    } while (i != 0);
}

s32 Effect_CreateTerrainRing(u16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    EffectRing* p;
    Vec3f* pt;
    Vec3f* n;
    s32 j;
    f32 angle;
    f32 dy;

    p = effect_ring_slots;
    for (i = 0; i != 3; i++, p++) {
        if (p->state == 0) {
            break;
        }
    }
    p->colorIndex = arg0;
    p->state = 1;
    p->stateFrames = 0;
    p->stateLength = effect_ring_grow_frames[arg0];
    p->centerX = arg1;
    p->centerY = arg2;
    p->centerZ = arg3;
    pt = p->pts; n = p->norms; j = 16;
    angle = 0.0f;
    do {
        effect_temp_vec.x = 0.0f;
        effect_temp_vec.y = arg4;
        Math_RotateVec2(angle, &effect_temp_vec);
        pt->x = effect_temp_vec.x + arg1;
        pt->z = effect_temp_vec.y + arg3;
        Coll_ResolveFloorAndWalls(pt->x, player_state.actor.y, pt->z, 0xA00, &effect_ring_coll);
        if (effect_ring_coll.flags & 0x8000) {
            pt->y = arg2;
            n->x = 0.0f;
            n->y = 1.0f;
            n->z = 0.0f;
        } else {
            dy = effect_ring_coll.y - arg2;
            if (dy < -40.0 || dy > 40.0) {
                pt->y = arg2;
                n->x = 0.0f;
                n->y = 1.0f;
                n->z = 0.0f;
            } else {
                pt->y = effect_ring_coll.y;
                n->x = effect_ring_coll.nx;
                n->y = effect_ring_coll.ny;
                n->z = effect_ring_coll.nz;
            }
        }
        angle += 0.39269908169872414;
        pt++;
        n++;
    } while (--j != 0);
    return i;
}

void Effect_FadeRing(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    EffectRing* p = &effect_ring_slots[arg0];

    p->state = 3;
    p->stateFrames = 0;
    p->stateLength = 10;
    p->centerX = arg1;
    p->centerY = arg2;
    p->centerZ = arg3;
}

extern Gfx D_800C4780[];
extern u8 D_800C47C0[];
extern Gfx D_800C4840[];

void Effect_UpdateAndDrawRings(struct GfxFrameData* arg0) {
    s32 cnt;
    EffectRing* p;
    s32 first;
    u8 alpha;
    s32 j;
    Vec3f* pt;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 len;
    f32 scale;
    u8* color;
    f32 dx;
    f32 dy;
    f32 dz;
    MtxF mtx;

    first = 0;
    p = effect_ring_slots;
    cnt = 4;
    do {
        if (p->state) {
            if (first == 0) {
                gSPDisplayList(gfx_dl_head++, D_800C4780);
                gDPLoadTextureBlock(gfx_dl_head++, D_800C47C0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_WRAP, G_TX_WRAP, 3, 0, G_TX_NOLOD, G_TX_NOLOD);
                first++;
            }
            p->stateFrames++;
            alpha = effect_ring_alpha_values[p->stateFrames & 1];
            switch (p->state) {
                case 1:
                    if (p->stateFrames < 4) {
                        alpha = (alpha * p->stateFrames) >> 2;
                    }
                    if (p->stateLength < p->stateFrames) {
                        p->state++;
                    } else {
                        scale = sinf(p->stateFrames * 3.141592653589793 / (p->stateLength * 2));
                    }
                    break;
                case 3:
                    alpha = (alpha * (p->stateLength - p->stateFrames)) / p->stateLength;
                    if (!(p->stateFrames < p->stateLength)) {
                        p->state = 0;
                    }
                    break;
            }
            color = effect_ring_colors[p->colorIndex];
            gDPSetEnvColor(gfx_dl_head++, color[0], color[1], color[2], alpha);
            pt = p->pts;
            j = 16;
            do {
                x0 = pt->x;
                y0 = pt->y + 5.0f;
                z0 = pt->z;
                pt++;
                if (--j == 0) {
                    pt = p->pts;
                }
                x1 = pt->x;
                y1 = pt->y + 5.0f;
                z1 = pt->z;
                if (p->state == 1) {
                    x0 = (x0 - p->centerX) * scale + p->centerX;
                    y0 = (y0 - p->centerY) * scale + p->centerY;
                    z0 = (z0 - p->centerZ) * scale + p->centerZ;
                    x1 = (x1 - p->centerX) * scale + p->centerX;
                    y1 = (y1 - p->centerY) * scale + p->centerY;
                    z1 = (z1 - p->centerZ) * scale + p->centerZ;
                }
                dx = x1 - x0;
                dy = y1 - y0;
                dz = z1 - z0;
                len = sqrtf(dx * dx + dy * dy + dz * dz);
                if (len != 0.0f) {
                    Math_MtxFAlignYToVector(&mtx, dx, dy, dz);
                    Math_MtxFScaleAxes(&mtx, 2.0f, len, 1.5f);
                    mtx.mf[3][0] = x0;
                    mtx.mf[3][1] = y0;
                    mtx.mf[3][2] = z0;
                    guMtxF2L(mtx.mf, &arg0->mtx[gfx_mtx_index]);
                    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                    gSPDisplayList(gfx_dl_head++, D_800C4840);
                }
            } while (j != 0);
        }
        p++;
    } while (--cnt != 0);
}

void Effect_ResetModelEffects(void) {
    s32 i = 32;
    EffectModel* p = effect_model_slots;

    do {
        i--;
        p->framesLeft = 0;
        p++;
    } while (i != 0);
}

EffectModel* Effect_CreateModelEffect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    s32 i;
    EffectModel* p;

    i = 31;
    p = effect_model_slots;
    while (i != 0 && p->framesLeft != 0) {
        i--;
        p++;
    }
    p->x = arg5;
    p->y = arg6;
    p->z = arg7;
    p->rotationY = arg8;
    p->scaleX = arg9;
    p->scaleY = arg10;
    p->scaleZ = arg11;
    p->upX = 0.0f;
    p->upY = 0.0f;
    p->upZ = 1.0f;
    p->anim = D_800EB2B4[arg0];
    p->age = 0;
    p->colorIndex = arg3;
    p->anim.dls = (Gfx**)D_800CADA8[arg1];
    p->framesLeft = p->loopLength = p->anim.length;
    p->flags = arg4;
    p->animFrame = 0;
    p->tex = D_800DA0F0[arg2];
    return p;
}

void Effect_UpdateAndDrawModelEffects(struct GfxFrameData* arg0) {
    EffectModel* p;
    s32 i;
    u32 alpha;
    u8* col;
    u16* cnt;

    cnt = &effect_model_frame_counter;
    gSPDisplayList(gfx_dl_head++, D_800EB6D0);
    effect_loaded_tlut_index = 0xFFFF;
    i = 32;
    p = effect_model_slots;
    do {
        if (p->framesLeft != 0) {
            Effect_ConfigureModelEffectTexture(p);
            if (p->flags & 2) {
                if (*cnt & 1) {
                    alpha = 240;
                } else {
                    alpha = 150;
                }
            } else {
                alpha = 250;
            }
            if (!(p->flags & 1) && p->framesLeft < 8) {
                alpha = (p->framesLeft * alpha) >> 3;
            } else if ((p->flags & 0x80) && p->age < 8) {
                alpha = (p->age * alpha) >> 3;
            }
            col = D_800EB5E4[p->colorIndex & 0xFF];
            gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], alpha);
            if (p->flags & 8) {
                gSPSetGeometryMode(gfx_dl_head++, G_CULL_BACK);
            } else {
                gSPClearGeometryMode(gfx_dl_head++, G_CULL_BACK);
            }
            Effect_DrawModelEffectGeometry(p, arg0);
            p->animFrame++;
            if (--p->framesLeft == 0) {
                if (p->flags & 1) {
                    p->framesLeft = p->loopLength;
                }
            }
            p->age++;
        }
        i--;
        p++;
    } while (i != 0);
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    (*cnt)++;
}


s32 Effect_DrawModelEffectGeometry(EffectModel* arg0, struct GfxFrameData* arg1) {
    u32 i;
    AnimNode* anims;
    s32 frame;
    MtxF mtx;
    Vec3f scale;

    anim_node_position_count = 0;
    if (arg0->flags & 4) {
        Math_MtxFAlignYToVector(&mtx, arg0->upX, arg0->upY, arg0->upZ);
        mtx.mf[3][0] = arg0->x;
        mtx.mf[3][1] = arg0->y;
        mtx.mf[3][2] = arg0->z;
        Math_MtxFScaleAxes(&mtx, arg0->scaleX * 0.01, arg0->scaleY * 0.01, arg0->scaleZ * 0.01);
    } else {
        Math_MtxFRotScaleTrans(&mtx, 0.0f, arg0->rotationY, 0.0f, 0.01f, arg0->x, arg0->y, arg0->z);
        Math_MtxFScaleAxes(&mtx, arg0->scaleX, arg0->scaleY, arg0->scaleZ);
    }
    scale.x = arg0->scaleX * 0.01;
    scale.y = arg0->scaleY * 0.01;
    scale.z = arg0->scaleZ * 0.01;
    anims = arg0->anim.nodes;
    frame = arg0->animFrame;
    if (gfx_mtx_index < 0x1E6) {
        for (i = 0; i < arg0->anim.nodeCount; i++) {
            if (anims[i].parent == 0) {
                Anim_DrawNode(&mtx, scale, 0, i, frame, 0, &arg0->anim, anims, arg1);
            }
        }
    }
}

s32 Effect_ConfigureModelEffectTexture(EffectModel* arg0) {
    EffectTexAnim* t;
    u32 mask;
    u32 size;
    s32 geom = 0;
    s32 img;
    s32 clamp;

    if (arg0->tex.img != 0) {
        t = &arg0->tex;
        if (arg0->flags & 0x20) {
            geom = G_LIGHTING;
        }
        t->s += t->ds;
        t->t += t->dt;
        img = t->img;
        size = (t->flags & 1) ? 16 : 32;
        if (t->flags & 1) {
            mask = 4;
        } else {
            mask = 5;
        }
        if (t->flags & 4) {
            img += (arg0->age >> t->shift) * size * size;
        } else if (t->flags & 8) {
            img += ((arg0->age >> t->shift) & t->mask) * size * size;
        }
        if (t->flags & 0x10) {
            clamp = 1;
        } else {
            clamp = 0;
        }
        if (t->flags & 2) {
            gDPLoadTextureBlock(gfx_dl_head++, img, G_IM_FMT_I, G_IM_SIZ_8b, size, size, 0, clamp, clamp, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
            if (t->flags & 0x40) {
                if (arg0->flags & 0x20) {
                    gDPSetCombine(gfx_dl_head++, 0x629A04, 0x1F10FFFF);
                } else {
                    gDPSetCombine(gfx_dl_head++, 0x629BFF, 0x1F10FE3F);
                }
            } else if (arg0->flags & 0x20) {
                gDPSetCombine(gfx_dl_head++, 0x62FE04, 0x1F10FBFF);
            } else {
                gDPSetCombine(gfx_dl_head++, 0x62FFFF, 0x1F10FA3F);
            }
        } else {
            gDPLoadTextureBlock(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, size, size, 0, clamp, clamp, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
            if (arg0->flags & 0x20) {
                gDPSetCombine(gfx_dl_head++, 0x129804, 0xFF17FFFF);
            } else {
                gDPSetCombine(gfx_dl_head++, 0x1299FF, 0xFF17FE3F);
            }
            if (effect_loaded_tlut_index != t->tlut) {
                effect_loaded_tlut_index = t->tlut;
                gDPLoadTLUT_pal256(gfx_dl_head++, effect_model_tlut_ptrs[effect_loaded_tlut_index]);
            }
        }
        gDPSetTileSize(gfx_dl_head++, G_TX_RENDERTILE, t->s, t->t, t->s + size, t->t + size);
        if (t->flags & 0x20) {
            gSPTexture(gfx_dl_head++, size << 6, size << 6, 0, G_TX_RENDERTILE, G_ON);
            geom |= G_LIGHTING | G_TEXTURE_GEN;
        } else {
            gSPTexture(gfx_dl_head++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        }
    } else {
        gDPPipeSync(gfx_dl_head++);
        gDPSetCombine(gfx_dl_head++, 0x62CBFF, 0x4FFE7E38);
        gSPTexture(gfx_dl_head++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
    }
    gSPClearGeometryMode(gfx_dl_head++, G_LIGHTING | G_TEXTURE_GEN);
    if (geom) {
        gSPSetGeometryMode(gfx_dl_head++, geom);
    }
}

void Effect_ResetStatUpMarkers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        effect_stat_up_marker_slots[i].framesLeft = 0;
    }
}

/* Not defined by a module: overlay display lists. */
extern Gfx D_800EB9C8[];
extern Gfx D_800EB990[];
void Effect_DrawStatUpMarkers(struct GfxFrameData* arg0) {
    s32 first;
    s32 i;
    EffectStatUpMarker* p;
    u32 alpha;
    f32 x;
    f32 y;
    f32 z;
    MtxF mtx;
    Gfx* gfx;

    first = 0;
    for (i = 0, p = effect_stat_up_marker_slots; i < 4; i++, p++) {
        if (p->framesLeft != 0) {
            if (gfx_mtx_index < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(gfx_dl_head++, D_800EB990);
                    first++;
                }
                alpha = 200 - Math_Rand(32);
                if (p->framesLeft < 8) {
                    alpha = (p->framesLeft * alpha) >> 3;
                } else if (p->framesLeft >= 22) {
                    alpha = ((25 - p->framesLeft) * alpha) >> 2;
                }
                x = player_shadow_pos.x;
                y = player_state.actor.scale * 70.0 + player_shadow_pos.y;
                z = player_shadow_pos.z;
                Math_MtxFAimAt(&mtx, x, y, z, camera_state.eyeX, camera_state.eyeY, camera_state.eyeZ);
                Math_MtxFScaleAxes(&mtx, player_state.actor.scale, player_state.actor.scale, player_state.actor.scale);
                guMtxF2L(mtx.mf, &arg0->mtx[gfx_mtx_index]);
                /* Keep the index update in the matrix command's scope for IDO scheduling. */
                {
                    Gfx* _g = gfx_dl_head++;
                    _g->words.w0 = 0x01020040;
                    _g->words.w1 = (u32)&D_2000000.mtx[gfx_mtx_index];
                    gfx_mtx_index++;
                }
                gDPSetEnvColor(gfx_dl_head++, effect_stat_up_marker_colors[i / 1][0], effect_stat_up_marker_colors[i / 1][1], effect_stat_up_marker_colors[i / 1][2], alpha);
                gSPDisplayList(gfx_dl_head++, D_800EB9C8);
            }
            p->framesLeft--;
        }
    }
}


void Effect_StartStatUpMarker(s32 arg0) {
    effect_stat_up_marker_slots[arg0].framesLeft = 25;
}
