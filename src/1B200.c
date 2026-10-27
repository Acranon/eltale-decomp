#include "common.h"

/*
 * Sprite particles, model effects, floating numbers, streaks, and terrain rings.
 * Folder: src/game/gfx/
 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk1B200Pos;

typedef struct {
    /* 0x00 */ s32 timer;
    /* 0x04 */ Unk1B200Pos* pos;
} Unk80086400; // size = 0x8

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void* unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ void* unk10;
    /* 0x14 */ void* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 pad3D[3];
} Unk8004EE20;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk1B200Vec2;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Unk1B200Particle;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Unk1B200Pos* unk14;
} Unk80086440; // size = 0x18

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u8 padE[0xE];
} Unk800865DC; // size = 0x1C

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk800866D8; // size = 0x18

extern Gfx* gfx_dl_head;
extern s16 D_800865CC;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
    /* 0x18 */ f32 vz;
    /* 0x1C */ f32 x0;
    /* 0x20 */ f32 y0;
    /* 0x24 */ f32 z0;
} Unk80087298; // size = 0x28

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk1B200Vec3;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Unk1B200Vec3 pts[16];
    /* 0xD4 */ Unk1B200Vec3 norms[16];
} Unk800877A8; // size = 0x194

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
} Unk80087798; // size = 0x4

typedef struct {
    /* 0x00 */ void* target;
    /* 0x04 */ u8 digits[8];
    /* 0x0C */ u16 timer;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 numDigits;
    /* 0x18 */ s32 unk18;
} Unk800865C0; // size = 0x1C

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
} Unk1B200Spark;

extern u8 D_800EB5E4[][4];
extern s32 D_80084B6C;
extern s32 D_80084B70;
extern s32 D_80084B74;
typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 eyeX;
    /* 0x10 */ f32 eyeY;
    /* 0x14 */ f32 eyeZ;
    /* 0x18 */ u8 pad18[0x14];
    /* 0x2C */ f32 yaw;
} Unk80085E48;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ void* unk8;
} Unk800EB2B4; // size = 0xC

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 mask;
    /* 0x04 */ u16 shift;
    /* 0x06 */ u16 tlut;
    /* 0x08 */ s32 img;
    /* 0x0C */ s16 s;
    /* 0x0E */ s16 t;
    /* 0x10 */ s16 ds;
    /* 0x12 */ s16 dt;
} Unk800DA0F0; // size = 0x14

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ Unk800EB2B4 unk38;
    /* 0x44 */ Unk800DA0F0 unk44;
} Unk80086798b; // size = 0x58

/* This file's .bss, 800863F0..80087E30 (in address order; first declaration
 * fixes the order). 800865C0..80087E00 is the 16-byte-aligned run that holds effect_stat_marker_slots (Effect_ResetStatUpMarkers shares a lui between its pairs only when it
 * is defined here). Labels splat put inside these arrays (D_800865CC..,
 * D_8008779C.., D_8008793C) are gone; no asm uses them now. */

extern Unk80085E48 camera_state;
extern s32 gfx_frame_index;
extern Unk800EB2B4 D_800EB2B4[];
extern u8 D_800CADA8[][4];
extern Unk800DA0F0 D_800DA0F0[];
typedef struct {
    f32 mf[4][4];
} MtxF;

extern Gfx D_800EB6D0[];
s32 Effect_DrawModelEffectGeometry(Unk80086798b*, s32);
s32 Effect_ConfigureModelEffectTexture(Unk80086798b*);
void Math_MtxFRotate(MtxF*, f32, f32, f32);
f32 Math_Atan2(f32, f32);
u32 Math_Rand(u32);
s32 Text_FormatNumber(s32, u8*, u16);
extern s32 gfx_mtx_index;
void Math_MtxFRotScaleTrans(MtxF*, f32, f32, f32, f32, f32, f32, f32);
void Math_MtxFAlignYToVector(MtxF*, f32, f32, f32);
void Math_MtxFScaleAxes(MtxF*, f32, f32, f32);
f32 sqrtf(f32);
typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000_1B200;
extern Unk2000000_1B200 D_2000000;
extern Gfx D_800EB880[];
extern Gfx D_800EB8E8[];

void Effect_UpdateFootParticle(Unk1B200Particle* arg0);
void Effect_UpdateMapObjParticle(Unk1B200Particle* arg0);
void Effect_UpdateFlipbookSprite(Unk1B200Particle* arg0);
void Effect_UpdateConvergeParticle(Unk1B200Spark* arg0);
void Effect_UpdateBurstParticle(Unk1B200Spark* arg0);

/* This file's .data, 8004EE20..8004F060: effect descriptors (Unk8004EE20,
 * 0x40 bytes each) and their tables, in source order: these first, then
 * Effect_UpdateMapObjEmitters's static descriptor (8004EE9C), effect_mapobj_particle_alpha_anim, Effect_SpawnFlipbookSprite's
 * static descriptor (8004EF0C) and the tables after Effect_SpawnFlipbookSprite. Both
 * descriptors must be function statics: IDO then stores their fields through
 * lui/%lo instead of the descriptor's address register. */
Unk8004EE20 effect_foot_particle_template = {
    0x000C, 0, (void*)Effect_UpdateFootParticle, 0x02101000, 0, (void*)0x800C3650, (void*)0x800C3790,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0,
};
f32 effect_foot_particle_scale_anim[12] = {
    3.25f, 3.24f, 3.23f, 3.22f, 3.21f, 3.2f, 3.0f, 2.8f, 2.6f, 2.4f, 2.2f, 2.0f,
};
u8 effect_foot_particle_alpha_anim[12] = { 0x10, 0x20, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xB0, 0xA0, 0x80, 0x40 };
typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 y;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ Unk1B200Vec3 normal;
    /* 0x18 */ u16 flags;
} Coll1B200;

s32 effect_mapobj_emitter_count;
u16 effect_model_frame_counter;
s32 effect_mapobj_previous_count;
Unk80086400 effect_foot_emitter_slots[8];
Unk80086440 effect_mapobj_emitter_buffer_a[8];
Unk80086440 effect_mapobj_emitter_buffer_b[8];
Unk800865C0 effect_floating_number_slots[10];
Unk800866D8 effect_converge_emitter_slots[8];
Unk80086798b effect_model_slots[32];
Unk80087298 effect_streak_slots[32];
Unk80087798 effect_stat_marker_slots[4];
Unk800877A8 effect_ring_slots[4];
u16 effect_loaded_tlut_index;
Unk1B200Vec2 effect_rotated_offset_scratch;
u8 D_80087E08[8]; /* unreferenced */
Coll1B200 effect_floor_collision_scratch;

void Effect_ResetFootEmitters(void);
void Effect_ResetMapObjEmitters(void);
void Effect_ResetFloatingNumbers(void);
void Effect_ResetConvergeEmitters(void);
void Effect_ResetStreaks(void);
void Effect_ResetRings(void);
void Effect_ResetModelEffects(void);
void Effect_ResetStatUpMarkers(void);
void Effect_UpdateFootEmitters(void);
void Effect_UpdateMapObjEmitters(void);
void Effect_DrawFloatingNumbers(void);
void Effect_UpdateConvergeEmitters(void);
void Effect_UpdateAndDrawStreaks(void*);
void Effect_UpdateAndDrawRings(void*);
void Effect_UpdateAndDrawModelEffects(void*);
void Effect_DrawStatUpMarkers(void*);
s32 Effect_AllocateSprite(void*);
void Math_RotateVec2(f32, Unk1B200Vec2*);

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

void Effect_UpdateAndDrawAll(void* arg0) {
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
    Unk80086400* p = effect_foot_emitter_slots;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void Effect_StartFootEmitter(Unk1B200Pos* arg0) {
    s32 i = 7;
    Unk80086400* p = effect_foot_emitter_slots;

    while (i != 0 && p->timer != 0) {
        i--;
        p++;
    }
    p->timer = 4;
    p->pos = arg0;
}

void Effect_UpdateFootEmitters(void) {
    s32 i;
    Unk80086400* p;
    Unk1B200Pos* pos;

    i = 8;
    p = effect_foot_emitter_slots;
    do {
        if (p->timer != 0) {
            p->timer--;
            if (p->timer & 1) {
                pos = p->pos;
                effect_foot_particle_template.unk18 = pos->x;
                effect_foot_particle_template.unk1C = pos->y + 1.0f;
                effect_foot_particle_template.unk20 = pos->z;
                effect_rotated_offset_scratch.x = 0.0f;
                effect_rotated_offset_scratch.y = 0.7f;
                Math_RotateVec2(pos->unk10, &effect_rotated_offset_scratch);
                effect_foot_particle_template.unk34 = 0.2f;
                effect_foot_particle_template.unk30 = effect_rotated_offset_scratch.x;
                effect_foot_particle_template.unk38 = effect_rotated_offset_scratch.y;
                Effect_AllocateSprite(&effect_foot_particle_template);
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void Effect_UpdateFootParticle(Unk1B200Particle* arg0) {
    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.8;
    arg0->unk28 = arg0->unk2C = effect_foot_particle_scale_anim[arg0->unk0];
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, effect_foot_particle_alpha_anim[arg0->unk0]);
}

void Effect_ResetMapObjEmitters(void) {
    s32 i;
    Unk80086440* a;
    Unk80086440* b;

    effect_mapobj_previous_count = 0;
    i = 8;
    a = effect_mapobj_emitter_buffer_a;
    b = effect_mapobj_emitter_buffer_b;
    do {
        i--;
        b->unk0 = 0;
        a->unk0 = 0;
        a++;
        b++;
    } while (i != 0);
}

void Effect_QueueMapObjEmitter(f32 x, f32 y, f32 z, Unk1B200Pos* arg3) {
    s32 pad[4];
    Unk80086440* cur;
    Unk80086440* prev;
    f32 angle;
    s32 n;

    cur = gfx_frame_index ? effect_mapobj_emitter_buffer_a : effect_mapobj_emitter_buffer_b;
    prev = gfx_frame_index ? effect_mapobj_emitter_buffer_b : effect_mapobj_emitter_buffer_a;
    angle = Math_Atan2(x - camera_state.eyeX, z - camera_state.eyeZ) - camera_state.yaw + 3.141592653589793;
    if (angle < -3.141592653589793) {
        angle += 6.283185307179586;
    } else if (angle > 3.141592653589793) {
        angle -= 6.283185307179586;
    }
    if (angle > -1.5707963267948966 && angle < 1.5707963267948966 && effect_mapobj_emitter_count < 8) {
        n = effect_mapobj_previous_count;
        cur += effect_mapobj_emitter_count;
        while (n != 0 && arg3 != prev->unk14) {
            n--;
            prev++;
        }
        if (n != 0) {
            cur->unk0 = prev->unk0;
        } else {
            cur->unk0 = Math_Rand(4) * 4 + 1;
        }
        cur->x = x;
        cur->y = y;
        cur->z = z;
        cur->unk10 = arg3->unk10;
        cur->unk14 = arg3;
        effect_mapobj_emitter_count++;
    }
}

void Effect_UpdateMapObjEmitters(void) {
    static Unk8004EE20 effect_mapobj_particle_template = {
        0x002D, 0, (void*)Effect_UpdateMapObjParticle, 0x02101000, 0, (void*)0x800C3650, (void*)0x800C37E0,
        0.0f, 0.0f, 0.0f, 0.0f, 4.0f, 4.0f, 0.1f, 0.25f, 0.05f, 0,
    };
    Unk80086440* p;
    s32 n;

    effect_mapobj_previous_count = effect_mapobj_emitter_count;
    p = gfx_frame_index ? effect_mapobj_emitter_buffer_a : effect_mapobj_emitter_buffer_b;
    n = effect_mapobj_previous_count;
    while (n != 0) {
        if (p->unk0 != 0 && --p->unk0 == 0) {
            effect_mapobj_particle_template.unk18 = p->x;
            effect_mapobj_particle_template.unk1C = p->y;
            effect_mapobj_particle_template.unk20 = p->z;
            effect_mapobj_particle_template.unk28 = effect_mapobj_particle_template.unk2C = p->unk10;
            Effect_AllocateSprite(&effect_mapobj_particle_template);
            p->unk0 = 0x19;
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

void Effect_UpdateMapObjParticle(Unk1B200Particle* arg0) {
    s32 r;
    s32 g;
    s32 b;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk28 += 0.08;
    arg0->unk2C += 0.08;
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
    gDPSetEnvColor(gfx_dl_head++, r, g, b, effect_mapobj_particle_alpha_anim[arg0->unk0]);
}

void Effect_SpawnFlipbookSprite(f32 x, f32 y, f32 z) {
    static Unk8004EE20 effect_flipbook_sprite_template = {
        0x000C, 0, (void*)Effect_UpdateFlipbookSprite, 0x04202000, 0, (void*)0x800C3830, (void*)0x800C4070,
        0.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f, 0,
    };

    effect_flipbook_sprite_template.unk18 = x;
    effect_flipbook_sprite_template.unk1C = y;
    effect_flipbook_sprite_template.unk20 = z;
    Effect_AllocateSprite(&effect_flipbook_sprite_template);
}

/* The rest of this file's .data (each table belongs to one of the functions below). */
s32 effect_flipbook_frame_ptrs[3] = { 0x800C3E30, 0x800C3C30, 0x800C3A30 };
f32 effect_flipbook_scale_anim[12] = {
    0.88f, 0.88f, 0.84f, 0.84f, 0.82f, 0.82f, 0.8f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f,
};
u8 effect_flipbook_alpha_anim[12] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0xA0, 0xC0, 0xC8, 0x80, 0x60 };
u8 effect_converge_colors[4][4] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xC8, 0xFF, 0xC8, 0xFF }, { 0xC8, 0xC8, 0xFF, 0xFF }, { 0xFF, 0x7F, 0x7F, 0xFF },
};
Unk8004EE20 effect_converge_particle_template = {
    0x0014, 0, (void*)Effect_UpdateConvergeParticle, 0x02101000, 0, (void*)0x800C4128, (void*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
Unk8004EE20 effect_burst_particle_template = {
    0x0014, 0, (void*)Effect_UpdateBurstParticle, 0x02101000, 0, (void*)0x800C4128, (void*)0x800C4268,
    0.0f, 0.0f, 0.0f, 0.0f, 1.3f, 1.3f, 0.0f, 0.0f, 0.0f, 0,
};
u16 effect_ring_lifetimes[4] = { 0x14, 0xC, 0xC, 0 };
u8 effect_ring_colors[3][4] = { { 0xC8, 0xC8, 0x00, 0x00 }, { 0xC8, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xC8, 0x00 } };
u8 effect_ring_alpha_values[4] = { 0xFF, 0x96, 0x00, 0x00 };
s32 effect_model_tlut_ptrs[4] = { 0x800CAE68, 0x800CB068, 0x800CB268, 0x800CB468 };
u8 effect_ring_segment_colors[5][4] = {
    { 0xFF, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0xFF, 0x00 }, { 0x00, 0xFF, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x00 },
};

void Effect_UpdateFlipbookSprite(Unk1B200Particle* arg0) {
    u16 v = arg0->unk0;

    if (!(v & 3)) {
        arg0->unk10 = effect_flipbook_frame_ptrs[v >> 2];
    }
    arg0->unk28 = arg0->unk2C = effect_flipbook_scale_anim[v];
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, effect_flipbook_alpha_anim[arg0->unk0]);
}

void Effect_ResetFloatingNumbers(void) {
    s32 i = 10;
    Unk800865C0* p = effect_floating_number_slots;

    do {
        i--;
        p->timer = 0;
        p++;
    } while (i != 0);
}

void Effect_AddFloatingNumber(void* arg0, s32 arg1, s32 arg2) {
    s32 pad[2];
    Unk800865C0* var_t0;
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
    var_t0->unk10 = arg1;

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
    var_t0->unk18 = var_v1 - 1;
}

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pad2[0x1A];
    /* 0x1C */ f32 height;
} Unk1B200DmgModel;

typedef struct {
    /* 0x00 */ u8 pad0[0x94];
    /* 0x94 */ f32 top;
} Unk1B200DmgModel2;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[0x18];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x3C];
    /* 0x64 */ Unk1B200DmgModel* model;
    /* 0x68 */ Unk1B200DmgModel2* model2;
} Unk1B200DmgActor;

extern Gfx D_800C40C0[];
extern u8 D_8039E290[];
s32 Camera_WorldToScreen(f32, f32, f32, s32*, s32*);
s16 sins(u16);

void Effect_DrawFloatingNumbers(void) {
    s32 n;
    Unk800865C0* d;
    s32 first;
    Unk1B200DmgActor* actor;
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
            if (actor->model->type == 0) {
                y = actor->y + actor->model->height * actor->scale;
            } else if (actor->model->type == 1) {
                y = actor->model2->top;
            } else {
                y = actor->y + 600.0 * actor->scale;
            }
            if (Camera_WorldToScreen(actor->x, y, actor->z, &sx, &sy)) {
                if (!first) {
                    gSPDisplayList(gfx_dl_head++, D_800C40C0);
                    gDPLoadTextureBlock(gfx_dl_head++, D_8039E290, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
                    first++;
                }
                if (d->unk10 & 0x8000) {
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
                sx -= d->unk18 * w;
                sy = sy - d->unk18 * 5 - 8;
                c = effect_converge_colors[d->unk10 & 0xF];
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
    Unk800866D8* p = effect_converge_emitter_slots;
    s32 i = 8;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

void Effect_StartConvergeEmitter(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Unk800866D8* p = effect_converge_emitter_slots;
    s32 i = 7;

    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unk0 = arg1;
    p->unk4 = arg0;
    p->unk8 = arg2;
    p->unkC = arg3;
    p->unk10 = arg4;
    p->unk14 = arg5;
}

void Effect_UpdateConvergeEmitters(void) {
    Unk800866D8* p;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    f32 a;
    MtxF mtx;
    f32 b;
    Unk8004EE20 spawn;

    spawn = effect_converge_particle_template;
    p = effect_converge_emitter_slots;
    i = 8;
    do {
        if (p->unk0 != 0) {
            if (p->unk0 & 1) {
                a = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
                b = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
                Math_MtxFRotate(&mtx, a, b, 0.0f);
                guMtxXFMF(mtx.mf, 0.0f, 0.0f, p->unk14, &x, &y, &z);
                spawn.unk18 = p->unk8 + x;
                spawn.unk1C = p->unkC + y;
                spawn.unk20 = p->unk10 + z;
                spawn.unk30 = x * -0.03;
                spawn.unk34 = y * -0.03;
                spawn.unk38 = z * -0.03;
                spawn.unk3C = p->unk4;
                Effect_AllocateSprite(&spawn);
            }
            p->unk0--;
        }
        i--;
        p++;
    } while (i != 0);
}

void Effect_UpdateConvergeParticle(Unk1B200Spark* arg0) {
    u8* c;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.9;
    arg0->unk34 *= 0.9;
    arg0->unk38 *= 0.9;
    arg0->unk24 += 0.39269908169872414;
    if (arg0->unk0 < 10) {
        arg0->unk28 = arg0->unk2C = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->unk0 & 1) {
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
    Unk8004EE20 spawn;
    spawn = effect_burst_particle_template;
    i = 15;
    do {
        a = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
        b = (f32)Math_Rand(32) * 3.141592653589793 / 16.0f;
        Math_MtxFRotate(&mtx, a, b, 0.0f);
        guMtxXFMF(mtx.mf, 0.0f, 0.0f, arg4, &a, &b, &c);
        spawn.unk18 = arg1;
        spawn.unk1C = arg2;
        spawn.unk20 = arg3;
        spawn.unk30 = a;
        spawn.unk34 = b;
        spawn.unk38 = c;
        spawn.unk3C = arg0;
        Effect_AllocateSprite(&spawn);
        i--;
    } while (i != 0);
}

void Effect_UpdateBurstParticle(Unk1B200Spark* arg0) {
    u8* c;

    arg0->unk18 += arg0->unk30;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38;
    arg0->unk30 *= 0.8;
    arg0->unk34 *= 0.8;
    arg0->unk38 *= 0.8;
    arg0->unk24 += 0.39269908169872414;
    if (arg0->unk0 < 10) {
        arg0->unk28 = arg0->unk2C = 1.0f;
    }
    c = D_800EB5E4[arg0->unk3C];
    if (arg0->unk0 & 1) {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0xDC);
    } else {
        gDPSetEnvColor(gfx_dl_head++, c[0], c[1], c[2], 0x20);
    }
}

void Effect_ResetStreaks(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        effect_streak_slots[i].unk0 = 0;
    }
}

void Effect_UpdateAndDrawStreaks(void* arg0) {
    s32 n;
    Unk80087298* p;
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
        if (p->unk0 != 0) {
            p->x += p->vx;
            p->y += p->vy;
            p->z += p->vz;
            if (gfx_mtx_index < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(gfx_dl_head++, D_800EB880);
                    first++;
                }
                if (p->unk0 & 1) {
                    alpha = 250;
                } else {
                    alpha = 150;
                }
                if (p->unk0 < 8) {
                    alpha = (p->unk0 * alpha) >> 3;
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
                guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[gfx_mtx_index]);
                gSPMatrix(gfx_dl_head++, &D_2000000.unkC0[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, alpha);
                gSPDisplayList(gfx_dl_head++, D_800EB8E8);
            }
            p->unk0--;
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
    Unk80087298* p;
    s32 count;
    f32 a;
    f32 b;
    f32 r;
    MtxF mtx;

    p = effect_streak_slots;
    n = 31;
    count = 16;
    do {
        while (n != 0 && p->unk0 != 0) {
            n--;
            p++;
        }
        p->unk0 = Math_Rand(8) + 10;
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
    Unk800877A8* p = effect_ring_slots;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ f32 unk1C;
} Unk8007AA08_1B200;
extern Unk8007AA08_1B200 player_state;
void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, Coll1B200*);
s32 Effect_CreateTerrainRing(u16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 i;
    Unk800877A8* p;
    Unk1B200Vec3* pt;
    Unk1B200Vec3* n;
    s32 j;
    f32 angle;
    f32 dy;

    p = effect_ring_slots;
    for (i = 0; i != 3; i++, p++) {
        if (p->unk0 == 0) {
            break;
        }
    }
    p->unk6 = arg0;
    p->unk0 = 1;
    p->unk2 = 0;
    p->unk4 = effect_ring_lifetimes[arg0];
    p->unk8 = arg1;
    p->unkC = arg2;
    p->unk10 = arg3;
    pt = p->pts; n = p->norms; j = 16;
    angle = 0.0f;
    do {
        effect_rotated_offset_scratch.x = 0.0f;
        effect_rotated_offset_scratch.y = arg4;
        Math_RotateVec2(angle, &effect_rotated_offset_scratch);
        pt->x = effect_rotated_offset_scratch.x + arg1;
        pt->z = effect_rotated_offset_scratch.y + arg3;
        Coll_ResolveFloorAndWalls(pt->x, player_state.unk1C, pt->z, 0xA00, &effect_floor_collision_scratch);
        if (effect_floor_collision_scratch.flags & 0x8000) {
            pt->y = arg2;
            n->x = 0.0f;
            n->y = 1.0f;
            n->z = 0.0f;
        } else {
            dy = effect_floor_collision_scratch.y - arg2;
            if (dy < -40.0 || dy > 40.0) {
                pt->y = arg2;
                n->x = 0.0f;
                n->y = 1.0f;
                n->z = 0.0f;
            } else {
                pt->y = effect_floor_collision_scratch.y;
                n->x = effect_floor_collision_scratch.normal.x;
                n->y = effect_floor_collision_scratch.normal.y;
                n->z = effect_floor_collision_scratch.normal.z;
            }
        }
        angle += 0.39269908169872414;
        pt++;
        n++;
    } while (--j != 0);
    return i;
}

void Effect_FadeRing(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Unk800877A8* p = &effect_ring_slots[arg0];

    p->unk0 = 3;
    p->unk2 = 0;
    p->unk4 = 10;
    p->unk8 = arg1;
    p->unkC = arg2;
    p->unk10 = arg3;
}

extern Gfx D_800C4780[];
extern u8 D_800C47C0[];
extern Gfx D_800C4840[];

void Effect_UpdateAndDrawRings(void* arg0) {
    s32 cnt;
    Unk800877A8* p;
    s32 first;
    u8 alpha;
    s32 j;
    Unk1B200Vec3* pt;
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
        if (p->unk0) {
            if (first == 0) {
                gSPDisplayList(gfx_dl_head++, D_800C4780);
                gDPLoadTextureBlock(gfx_dl_head++, D_800C47C0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_WRAP, G_TX_WRAP, 3, 0, G_TX_NOLOD, G_TX_NOLOD);
                first++;
            }
            p->unk2++;
            alpha = effect_ring_alpha_values[p->unk2 & 1];
            switch (p->unk0) {
                case 1:
                    if (p->unk2 < 4) {
                        alpha = (alpha * p->unk2) >> 2;
                    }
                    if (p->unk4 < p->unk2) {
                        p->unk0++;
                    } else {
                        scale = sinf(p->unk2 * 3.141592653589793 / (p->unk4 * 2));
                    }
                    break;
                case 3:
                    alpha = (alpha * (p->unk4 - p->unk2)) / p->unk4;
                    if (!(p->unk2 < p->unk4)) {
                        p->unk0 = 0;
                    }
                    break;
            }
            color = effect_ring_colors[p->unk6];
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
                if (p->unk0 == 1) {
                    x0 = (x0 - p->unk8) * scale + p->unk8;
                    y0 = (y0 - p->unkC) * scale + p->unkC;
                    z0 = (z0 - p->unk10) * scale + p->unk10;
                    x1 = (x1 - p->unk8) * scale + p->unk8;
                    y1 = (y1 - p->unkC) * scale + p->unkC;
                    z1 = (z1 - p->unk10) * scale + p->unk10;
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
                    guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[gfx_mtx_index]);
                    gSPMatrix(gfx_dl_head++, &D_2000000.unkC0[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                    gSPDisplayList(gfx_dl_head++, D_800C4840);
                }
            } while (j != 0);
        }
        p++;
    } while (--cnt != 0);
}

void Effect_ResetModelEffects(void) {
    s32 i = 32;
    Unk80086798b* p = effect_model_slots;

    do {
        i--;
        p->unk0 = 0;
        p++;
    } while (i != 0);
}

Unk80086798b* Effect_CreateModelEffect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    s32 i;
    Unk80086798b* p;

    i = 31;
    p = effect_model_slots;
    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unkC = arg5;
    p->unk10 = arg6;
    p->unk14 = arg7;
    p->unk18 = arg8;
    p->unk1C = arg9;
    p->unk20 = arg10;
    p->unk24 = arg11;
    p->unk28 = 0.0f;
    p->unk2C = 0.0f;
    p->unk30 = 1.0f;
    p->unk38 = D_800EB2B4[arg0];
    p->unk4 = 0;
    p->unk6 = arg3;
    p->unk38.unk8 = D_800CADA8[arg1];
    p->unk0 = p->unk2 = p->unk38.unk2;
    p->unk8 = arg4;
    p->unk34 = 0;
    p->unk44 = D_800DA0F0[arg2];
    return p;
}

void Effect_UpdateAndDrawModelEffects(void* arg0) {
    Unk80086798b* p;
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
        if (p->unk0 != 0) {
            Effect_ConfigureModelEffectTexture(p);
            if (p->unk8 & 2) {
                if (*cnt & 1) {
                    alpha = 240;
                } else {
                    alpha = 150;
                }
            } else {
                alpha = 250;
            }
            if (!(p->unk8 & 1) && p->unk0 < 8) {
                alpha = (p->unk0 * alpha) >> 3;
            } else if ((p->unk8 & 0x80) && p->unk4 < 8) {
                alpha = (p->unk4 * alpha) >> 3;
            }
            col = D_800EB5E4[p->unk6 & 0xFF];
            gDPSetEnvColor(gfx_dl_head++, col[0], col[1], col[2], alpha);
            if (p->unk8 & 8) {
                gSPSetGeometryMode(gfx_dl_head++, G_CULL_BACK);
            } else {
                gSPClearGeometryMode(gfx_dl_head++, G_CULL_BACK);
            }
            Effect_DrawModelEffectGeometry(p, (s32)arg0);
            p->unk34++;
            if (--p->unk0 == 0) {
                if (p->unk8 & 1) {
                    p->unk0 = p->unk2;
                }
            }
            p->unk4++;
        }
        i--;
        p++;
    } while (i != 0);
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    (*cnt)++;
}


typedef struct {
    f32 x, y, z;
} Vec3f_1B200;
typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ s8 unk14;
    /* 0x15 */ u8 pad15[0xB];
} Anim1B200; // size = 0x20
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ Anim1B200* unk4;
} AnimSet1B200;
extern s32 anim_node_position_count;
void Anim_DrawNode(MtxF*, Vec3f_1B200, s32, s32, s32, s32, AnimSet1B200*, Anim1B200*, s32);
s32 Effect_DrawModelEffectGeometry(Unk80086798b* arg0, s32 arg1) {
    u32 i;
    Anim1B200* anims;
    s32 frame;
    MtxF mtx;
    Vec3f_1B200 scale;

    anim_node_position_count = 0;
    if (arg0->unk8 & 4) {
        Math_MtxFAlignYToVector(&mtx, arg0->unk28, arg0->unk2C, arg0->unk30);
        mtx.mf[3][0] = arg0->unkC;
        mtx.mf[3][1] = arg0->unk10;
        mtx.mf[3][2] = arg0->unk14;
        Math_MtxFScaleAxes(&mtx, arg0->unk1C * 0.01, arg0->unk20 * 0.01, arg0->unk24 * 0.01);
    } else {
        Math_MtxFRotScaleTrans(&mtx, 0.0f, arg0->unk18, 0.0f, 0.01f, arg0->unkC, arg0->unk10, arg0->unk14);
        Math_MtxFScaleAxes(&mtx, arg0->unk1C, arg0->unk20, arg0->unk24);
    }
    scale.x = arg0->unk1C * 0.01;
    scale.y = arg0->unk20 * 0.01;
    scale.z = arg0->unk24 * 0.01;
    anims = ((AnimSet1B200*)&arg0->unk38)->unk4;
    frame = arg0->unk34;
    if (gfx_mtx_index < 0x1E6) {
        for (i = 0; i < ((AnimSet1B200*)&arg0->unk38)->unk0; i++) {
            if (anims[i].unk14 == 0) {
                Anim_DrawNode(&mtx, scale, 0, i, frame, 0, (AnimSet1B200*)&arg0->unk38, anims, arg1);
            }
        }
    }
}

s32 Effect_ConfigureModelEffectTexture(Unk80086798b* arg0) {
    Unk800DA0F0* t;
    u32 mask;
    u32 size;
    s32 geom = 0;
    s32 img;
    s32 clamp;

    if (arg0->unk44.img != 0) {
        t = &arg0->unk44;
        if (arg0->unk8 & 0x20) {
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
            img += (arg0->unk4 >> t->shift) * size * size;
        } else if (t->flags & 8) {
            img += ((arg0->unk4 >> t->shift) & t->mask) * size * size;
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
                if (arg0->unk8 & 0x20) {
                    gDPSetCombine(gfx_dl_head++, 0x629A04, 0x1F10FFFF);
                } else {
                    gDPSetCombine(gfx_dl_head++, 0x629BFF, 0x1F10FE3F);
                }
            } else if (arg0->unk8 & 0x20) {
                gDPSetCombine(gfx_dl_head++, 0x62FE04, 0x1F10FBFF);
            } else {
                gDPSetCombine(gfx_dl_head++, 0x62FFFF, 0x1F10FA3F);
            }
        } else {
            gDPLoadTextureBlock(gfx_dl_head++, img, G_IM_FMT_CI, G_IM_SIZ_8b, size, size, 0, clamp, clamp, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTextureLUT(gfx_dl_head++, G_TT_RGBA16);
            if (arg0->unk8 & 0x20) {
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
        effect_stat_marker_slots[i].unk0 = 0;
    }
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk8007AB48;
extern Unk8007AB48 player_shadow_pos;
extern f32 D_8007AA44;
extern Gfx D_800EB9C8[];
extern Gfx D_800EB990[];
void Math_MtxFAimAt(MtxF*, f32, f32, f32, f32, f32, f32);
void Effect_DrawStatUpMarkers(void* arg0) {
    s32 first;
    s32 i;
    Unk80087798* p;
    u32 alpha;
    f32 x;
    f32 y;
    f32 z;
    MtxF mtx;
    Gfx* gfx;

    first = 0;
    for (i = 0, p = effect_stat_marker_slots; i < 4; i++, p++) {
        if (p->unk0 != 0) {
            if (gfx_mtx_index < 0x1E6) {
                if (first == 0) {
                    gSPDisplayList(gfx_dl_head++, D_800EB990);
                    first++;
                }
                alpha = 200 - Math_Rand(32);
                if (p->unk0 < 8) {
                    alpha = (p->unk0 * alpha) >> 3;
                } else if (p->unk0 >= 22) {
                    alpha = ((25 - p->unk0) * alpha) >> 2;
                }
                x = player_shadow_pos.x;
                y = D_8007AA44 * 70.0 + player_shadow_pos.y;
                z = player_shadow_pos.z;
                Math_MtxFAimAt(&mtx, x, y, z, camera_state.eyeX, camera_state.eyeY, camera_state.eyeZ);
                Math_MtxFScaleAxes(&mtx, D_8007AA44, D_8007AA44, D_8007AA44);
                guMtxF2L(mtx.mf, &((Unk2000000_1B200*)arg0)->unkC0[gfx_mtx_index]);
                /* Keep the index update in the matrix command's scope for IDO scheduling. */
                {
                    Gfx* _g = gfx_dl_head++;
                    _g->words.w0 = 0x01020040;
                    _g->words.w1 = (u32)&D_2000000.unkC0[gfx_mtx_index];
                    gfx_mtx_index++;
                }
                gDPSetEnvColor(gfx_dl_head++, effect_ring_segment_colors[i / 1][0], effect_ring_segment_colors[i / 1][1], effect_ring_segment_colors[i / 1][2], alpha);
                gSPDisplayList(gfx_dl_head++, D_800EB9C8);
            }
            p->unk0--;
        }
    }
}


void Effect_StartStatUpMarker(s32 arg0) {
    effect_stat_marker_slots[arg0].unk0 = 25;
}
