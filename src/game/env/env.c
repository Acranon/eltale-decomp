#include "game/env/env.h"
#include "game/map/map.h"
#include "game/camera/camera.h"
#include "game/core/main.h"
#include "game/battle/battle.h"
#include "game/ui/hud.h"

/*
 * World clock and environment: day counter, day-phase palette fades, the lighting/fog
 * keyframe track, and the light slots that emit env colour, Lights3 and fog colour.
 * Original file: 12610.c (ROM 0x12610).
 */

/* This file's .bss, 80084300..80084B80, in address order (first declaration fixes
 * the order). exit_local_offset is used only by 113F0 (it sits between this file's
 * objects). The asm's interior labels (D_80084308.., D_80084B1C..D_80084B44,
 * D_80084B24, D_80084B60..D_80084B74, D_80084B7C) are aliases in undefined_syms.txt. */
ExitDestination exit_destination;
u16 *exit_destination_src;
Vec2f exit_local_offset;
u8 D_80084328[8]; /* unreferenced */
s32 env_next_phase;
s32 env_last_phase_start;
u16 env_play_time_ticks;
s32 env_palette_fade_timer;
s32 env_palette_fade_length;
u16 *env_palette_fade_target;
u16 *env_palette_fade_dest;
u16 env_palette_fade_start[0x100];
f32 env_light_rot_mtx[4][4];
Lights3 env_lights_frame0;
Lights3 env_lights_frame1;
Lights3 env_slot_lights_frame0[8];
Lights3 env_slot_lights_frame1[8];
s32 env_clock;
s32 env_day_length;
s32 env_light_time;
s32 env_light_period;
u16 env_day_count;
u16 env_play_time;
EnvAreaSettings *env_area_settings;
EnvLightSlot env_light_slots[8];
s32 env_light_colors[4][3];
s32 env_light_dirs[4][3];
s32 env_fog_range[2];

/* This file's .data, 8004DED0..8004DF00: the day-phase table (env_day_phase_last is
 * its last entry, named separately by the asm). */
EnvDayPhase env_day_phases[3] = {
    { 0x15F9, 0, 0x80 },
    { 0x2328, 1, 0x80 },
    { 0x4AB5, 2, 0x80 },
};
EnvDayPhase env_day_phase_last[1] = {
    { 0x537F, 3, 0x80 },
};

extern s32 D_80084B60;
extern s32 D_80084B64;
extern s32 D_80084B68;
extern s32 D_80084B6C;
extern s32 D_80084B70;
extern s32 D_80084B74;

void Exit_SetDestination(MapExit *arg0) {
    exit_destination_src = arg0->dest;
    exit_destination.map = exit_destination_src[0];
    exit_destination.subarea = exit_destination_src[1];
    exit_destination.entry = exit_destination_src[2];
    exit_destination.flags = arg0->flags;
    exit_destination.mapObj = arg0->mapObj;
    exit_destination.angle = arg0->angle;
}

void Env_InitClock(void) {
    s32 i;

    env_clock = 0x1EC3;
    env_day_length = 0x6978;
    env_day_count = 1;
    D_8008C164 = 7;
    for (i = 0; i < 4; i++) {
        env_light_colors[i][0] = 0;
        env_light_colors[i][1] = 0;
        env_light_colors[i][2] = 0;
    }
}

#ifdef NON_MATCHING
/* &env_day_phase_last held in a register instead of separate %hi/%lo loads, temporaries rotated (register allocation); code is equivalent */
void Env_InitForMap(void) {
    EnvDayPhase *p;
    s32 i;
    s32 n;
    u16 *src;
    u16 *dst;
    EnvKeyframe *e;

    /* env_day_phases[0..2] and env_day_phase_last form one 4-entry table; the walk goes back from its last entry */
    env_last_phase_start = env_day_phase_last[0].unk0;
    p = env_day_phase_last;
    i = 3;
    if (env_clock < env_day_phase_last[0].unk0) {
        do {
            p--;
            n = i--;
            if (n == 0) {
                break;
            }
        } while (env_clock < p->unk0);
    }
    if (i < 0) {
        p = env_day_phase_last;
        env_next_phase = 3;
    } else {
        env_next_phase = i;
    }
    /* map.h declares the four phase palettes as u8[0x800]; they are u16[4][0x100] (D3_HINTS). */
    src = map_backdrop_phase_tluts[p->unk4];
    dst = map_backdrop_tlut;
    i = 0x100;
    do {
        *dst++ = *src++;
        i--;
    } while (i != 0);
    env_palette_fade_timer = 0;
    if (++env_next_phase >= 4) {
        env_next_phase = 0;
    }
    if (map_env_flags & 2) {
        env_light_time = env_clock;
        env_light_period = env_day_length;
    } else {
        e = &env_area_settings->frames[env_area_settings->count - 1];
        env_light_time = 0;
        env_light_period = e->time;
    }
    Env_ClearLightSlots();
    env_play_time_ticks = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/env/env/Env_InitForMap.s")
#endif

void Env_Update(void) {
    EnvDayPhase *p;

    Env_InterpolateLighting(env_light_time, env_area_settings);
    if (env_palette_fade_timer != 0) {
        if (--env_palette_fade_timer < 0) {
            env_palette_fade_timer = 0;
        }
        Env_StepPaletteFade(env_palette_fade_timer);
    } else {
        p = &env_day_phases[env_next_phase];
        if (env_light_time >= p->unk0 && (env_next_phase != 0 || env_light_time < env_last_phase_start)) {
            /* row p->unk4 written as an offset: map_backdrop_phase_tluts[p->unk4] DIFFs (55 words) */
            Env_StartPaletteFade(p->unk8, map_backdrop_phase_tluts[0] + p->unk4 * 256, map_backdrop_tlut);
            if (++env_next_phase >= 4) {
                env_next_phase = 0;
            }
        }
    }
    if (map_flags & 5) {
        if (!(battle_flags & 1) && !(core_flags & 3) && D_8008C168 == 0) {
            if (++env_clock >= env_day_length) {
                env_clock -= env_day_length;
                if (env_day_count < 999) {
                    env_day_count++;
                }
            }
            env_light_time = env_clock;
        }
    } else if ((map_env_flags & 1) && D_8008C168 == 0) {
        if (++env_light_time >= env_light_period) {
            env_light_time -= env_light_period;
        }
    }
    if (++env_play_time_ticks >= 1501) {
        env_play_time_ticks = 0;
        if (env_play_time < 59939) {
            env_play_time++;
        }
    }
}

void Env_SetClock(s32 arg0) {
    env_clock = arg0;
    if (env_day_length <= env_clock) {
        env_clock = env_clock - env_day_length;
        if (env_day_count < 9999) {
            env_day_count++;
        }
    }
    env_light_time = env_clock;
}

#ifdef NON_MATCHING
/* 8-byte frame with one saved register where retail is a no-frame leaf, light pointers rematerialized differently (register allocation); code is equivalent */
void Env_InterpolateLighting(s32 t, EnvAreaSettings *arg1) {
    EnvKeyframe *k;
    EnvKeyframe *prev;
    s32 span;
    s32 off;
    s32 rem;
    EnvColor *ambient = (EnvColor *) env_light_colors[0];
    EnvColor *light;
    EnvFogRange *fog = (EnvFogRange *) env_fog_range;
    EnvColor *before;
    EnvColor *after;

    k = arg1->frames;
    if (arg1->count == 1) {
        *ambient = k->amb;
        light = (EnvColor *) env_light_colors[1]; /* D_80084B24 */
        *light++ = k->lights[0];
        *light++ = k->lights[1];
        *light++ = k->lights[2];
        *fog = k->fog;
        return;
    }
    while (t >= k->time) {
        k++;
    }
    prev = k - 1;
    span = k->time - prev->time;
    off = t - prev->time;
    rem = span - off;
    light = (EnvColor *) env_light_colors[1]; /* D_80084B24 */
    before = &prev->amb;
    after = &k->amb;
    ambient->r = (before->r * rem + after->r * off) / span;
    ambient->g = (before->g * rem + after->g * off) / span;
    ambient->b = (before->b * rem + after->b * off) / span;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    light++;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    light++;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    fog->near = (prev->fog.near * rem + k->fog.near * off) / span;
    fog->far = (prev->fog.far * rem + k->fog.far * off) / span;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/env/env/Env_InterpolateLighting.s")
#endif

void Env_PrepareFrameLighting(void) {
    Lights3 *l;

    l = gfx_frame_index ? &env_lights_frame1 : &env_lights_frame0;
    Env_ComputeLightDirs();
    Env_FillLights3(l, env_light_colors, env_light_dirs);
    gfx_fog_near = env_fog_range[0];
    gfx_fog_far = env_fog_range[1];
    gSPFogPosition(gfx_dl_head++, gfx_fog_near, gfx_fog_far);
    gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, 255);
}

void Env_ComputeLightDirs(void) {
    s32 pad;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;

    if (map_env_flags & 1) {
        angle = (f32)env_light_time * 3.141592653589793 * 2 / (f32)env_light_period - 3.141592653589793;
        Math_MtxFRotate((MtxF *)env_light_rot_mtx, 0.0f, 0.0f, angle);
        guMtxXFMF(env_light_rot_mtx, 0.0f, 90.0f, 50.0f, &x, &y, &z);
        env_light_dirs[0][0] = x;
        env_light_dirs[0][1] = y;
        env_light_dirs[0][2] = z;
    } else if (env_area_settings->unk8 != 0) {
        env_light_dirs[0][0] = env_area_settings->unkC;
        env_light_dirs[0][1] = env_area_settings->unk10;
        env_light_dirs[0][2] = env_area_settings->unk14;
    } else {
        env_light_dirs[0][0] = -89;
        env_light_dirs[0][1] = 89;
        env_light_dirs[0][2] = 20;
    }
    Math_MtxFMulVecTransposed(&camera_view_mtx, -89.0f, 89.0f, 20.0f, &x, &y, &z);
    env_light_dirs[1][0] = x;
    env_light_dirs[1][1] = y;
    env_light_dirs[1][2] = z;
}

void Env_StartPaletteFade(s32 arg0, u16 *arg1, u16 *arg2) {
    u16 *dst;
    u32 i;

    env_palette_fade_timer = env_palette_fade_length = arg0;
    env_palette_fade_target = arg1;
    env_palette_fade_dest = arg2;
    dst = env_palette_fade_start;
    i = 0x100;
    while (i--) {
        *dst++ = *arg2++;
    }
}

void Env_StepPaletteFade(s32 arg0) {
    u16 *src;
    u16 *src2;
    u16 *dst;
    u32 i;
    u16 r1;
    u16 g1;
    u16 b1;
    u16 r2;
    u16 g2;
    u16 b2;

    src = env_palette_fade_target;
    src2 = env_palette_fade_start;
    dst = env_palette_fade_dest;
    i = 0x100;
    if (arg0 != 0) {
        while (i--) {
            r1 = (*src & 0xF800) >> 11;
            g2 = *src;
            g1 = (g2 & 0x7C0) >> 6;
            b1 = (g2 & 0x3E) >> 1;
            r2 = (*src2 & 0xF800) >> 11;
            g2 = (*src2 & 0x7C0) >> 6;
            b2 = (*src2 & 0x3E) >> 1;
            src++;
            src2++;
            r1 = (r1 * (env_palette_fade_length - arg0) + r2 * arg0) / env_palette_fade_length;
            g1 = (g1 * (env_palette_fade_length - arg0) + g2 * arg0) / env_palette_fade_length;
            b1 = (b1 * (env_palette_fade_length - arg0) + b2 * arg0) / env_palette_fade_length;
            *dst++ = (r1 << 11) | (g1 << 6) | (b1 << 1);
        }
    } else {
        while (i--) {
            *dst = *src;
            src++;
            dst++;
        }
    }
}

void Env_ClearLightSlots(void) {
    EnvLightSlot *p = env_light_slots;
    s32 i = 8;

    do {
        p->unk0 = 0;
        p++;
        i--;
    } while (i != 0);
}

s32 Env_AllocateLightSlot(void) {
    EnvLightSlot *p = &env_light_slots[7];
    s32 i = 7;

    while (p->unk0 != 0) {
        i--;
        p--;
        if (i == 0) {
            break;
        }
    }
    p->unk0 = 1;
    p->unk4 = 0;
    p->unk18 = 0;
    p->unk2C = 0;
    return i;
}

void Env_FreeLightSlot(s32 arg0) {
    env_light_slots[arg0].unk0 = 0;
}

void Env_SetSlotEnvAnim(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    EnvLightSlot *p = &env_light_slots[arg0];

    p->unk4 = arg1;
    p->unk8 = p->unkC = arg2;
    p->unk10 = p->unk14 = arg3;
}

void Env_SetSlotLightAnim(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    EnvLightSlot *p = &env_light_slots[arg0];

    p->unk18 = arg1;
    p->unk20 = p->unk1C = arg2;
    p->unk24 = p->unk28 = arg3;
}

void Env_SetSlotLightDirs(s32 arg0, s32 *arg1) {
    env_light_slots[arg0].unk2C = arg1;
}

void Env_ApplyLightSlot(s32 idx) {
    s32 *f;
    s32 i;
    s32 (*src)[3];
    s32 r;
    s32 g;
    Lights3 *l;
    s32 (*cols)[3];
    EnvLightSlot *p;
    s32 pad; /* Retain the original -g3 local stack home. */
    s32 (*dirs)[3];
    s32 tmp[4][3];
    s32 b;

    p = &env_light_slots[idx];
    if (gfx_frame_index != 0) {
        l = &env_slot_lights_frame1[idx];
    } else {
        l = &env_slot_lights_frame0[idx];
    }
    if (p->unk4 != 0) {
        cols = (s32 (*)[3])p->unk10;
        r = (*cols)[0];
        g = (*cols)[1];
        b = (*cols)[2];
        switch (p->unk4) {
            case 1:
                p->unk10 += 3;
                if (--p->unk8 == 0) {
                    p->unk4 = 0;
                }
                break;
            case 2:
                if (p->unk8 != 0) {
                    if (--p->unk8 != 0) {
                        p->unk10 += 3;
                    }
                }
                break;
            case 3:
                if (--p->unk8 == 0) {
                    p->unk8 = p->unkC;
                    p->unk10 = p->unk14;
                } else {
                    p->unk10 += 3;
                }
                break;
        }
    } else {
        r = g = b = 0;
    }
    gDPSetEnvColor(gfx_dl_head++, r, g, b, 0xB4);
    if (p->unk18 != 0) {
        f = p->unk24;
        tmp[0][0] = (f[0] * env_light_colors[0][0]) >> 8;
        tmp[0][1] = (f[1] * env_light_colors[0][1]) >> 8;
        tmp[0][2] = (f[2] * env_light_colors[0][2]) >> 8;
        f += 3;
        src = &env_light_colors[1];
        cols = &tmp[1];
        i = 3;
        do {
            (*cols)[0] = (f[0] * (*src)[0]) >> 8;
            (*cols)[1] = (f[1] * (*src)[1]) >> 8;
            (*cols)[2] = (f[2] * (*src)[2]) >> 8;
            i--;
            src++;
            cols++;
        } while (i != 0);
        D_80084B60 = f[0];
        D_80084B64 = f[1];
        D_80084B68 = f[2];
        cols = tmp;
        switch (p->unk18) {
            case 1:
                p->unk24 += 6;
                if (--p->unk20 == 0) {
                    p->unk18 = 0;
                }
                break;
            case 2:
                if (p->unk20 != 0) {
                    if (--p->unk20 != 0) {
                        p->unk24 += 6;
                    }
                }
                break;
            case 3:
                if (--p->unk20 == 0) {
                    p->unk20 = p->unk1C;
                    p->unk24 = p->unk28;
                } else {
                    p->unk24 += 6;
                }
                break;
        }
    } else {
        D_80084B60 = D_80084B64 = D_80084B68 = 0xFF;
        cols = env_light_colors;
    }
    dirs = (s32 (*)[3])p->unk2C;
    if (dirs == NULL) {
        dirs = env_light_dirs;
    }
    if (p->unk0 == 2) {
        src = cols;
        cols = tmp;
        i = 3;
        do {
            (*cols)[0] = (*src)[0] - ((*src)[0] >> 2) + 0x3F;
            (*cols)[1] = (*src)[1] - ((*src)[1] >> 2) + 0x3F;
            (*cols)[2] = (*src)[2] - ((*src)[2] >> 2) + 0x3F;
            i--;
            cols++;
            src++;
        } while (i != 0);
        (*cols)[0] = (*src)[0];
        (*cols)[1] = (*src)[1];
        (*cols)[2] = (*src)[2];
        cols = tmp;
    }
    Env_FillLights3(l, cols, dirs);
    gSPSetLights3(gfx_dl_head++, (*l));
    gDPSetFogColor(gfx_dl_head++, cols[3][0], cols[3][1], cols[3][2], 0xFF);
    if (map_flags & 0x80) {
        gfx_clear_r = cols[3][0];
        gfx_clear_g = cols[3][1];
        gfx_clear_b = cols[3][2];
    } else {
        gfx_clear_r = gfx_clear_g = gfx_clear_b = 0;
    }
    D_80084B6C = cols[3][0];
    D_80084B70 = cols[3][1];
    D_80084B74 = cols[3][2];
}


void Env_FillLights3(Lights3 *arg0, s32 (*arg1)[3], s32 (*arg2)[3]) {
    arg0->l[1].l.dir[0] = (*arg2)[0];
    arg0->l[1].l.dir[1] = (*arg2)[1];
    arg0->l[1].l.dir[2] = (*arg2)[2];
    arg2++;
    arg0->l[2].l.dir[0] = arg0->l[0].l.dir[0] = (*arg2)[0];
    arg0->l[2].l.dir[1] = arg0->l[0].l.dir[1] = (*arg2)[1];
    arg0->l[2].l.dir[2] = arg0->l[0].l.dir[2] = (*arg2)[2];
    arg0->a.l.col[0] = arg0->a.l.colc[0] = (*arg1)[0];
    arg0->a.l.col[1] = arg0->a.l.colc[1] = (*arg1)[1];
    arg0->a.l.col[2] = arg0->a.l.colc[2] = (*arg1)[2];
    arg1++;
    arg0->l[1].l.col[0] = arg0->l[1].l.colc[0] = (*arg1)[0];
    arg0->l[1].l.col[1] = arg0->l[1].l.colc[1] = (*arg1)[1];
    arg0->l[1].l.col[2] = arg0->l[1].l.colc[2] = (*arg1)[2];
    arg1++;
    arg0->l[0].l.col[0] = arg0->l[0].l.colc[0] = (*arg1)[0];
    arg0->l[0].l.col[1] = arg0->l[0].l.colc[1] = (*arg1)[1];
    arg0->l[0].l.col[2] = arg0->l[0].l.colc[2] = (*arg1)[2];
    arg0->l[2].l.col[0] = arg0->l[2].l.colc[0] = (*arg1)[0];
    arg0->l[2].l.col[1] = arg0->l[2].l.colc[1] = (*arg1)[1];
    arg0->l[2].l.col[2] = arg0->l[2].l.colc[2] = (*arg1)[2];
}
