#include "common.h"

/*
 * Keyframe animation: evaluates 9-channel keyframe tracks with Kochanek-Bartels (TCB)
 * Hermite splines or linear segments.
 * Folder: src/game/math/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ f32 v[9];
    /* 0x24 */ f32 tension;
    /* 0x28 */ f32 continuity;
    /* 0x2C */ f32 bias;
    /* 0x30 */ u16 linear;
    /* 0x32 */ u16 frame;
} Keyframe; /* size = 0x34 */

typedef struct {
    /* 0x00 */ Keyframe* kfs;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 last;
} KfAnim;

void func_80026E20(f32 t, f32* a, f32* b, f32* c, f32* d);

void func_80026A00(KfAnim* anim, f32* out, s32 frame) {
    Keyframe* k0;
    Keyframe* k1;
    s32 i;
    f32 h00;
    f32 h01;
    f32 h10;
    f32 h11;
    f32 m0;
    f32 m1;
    f32 a0;
    f32 b0;
    f32 a1;
    f32 b1;
    f32 s0;
    f32 s1;
    s32 pad;
    f32* o;
    f32 d;
    s32 len;

    if (anim->count == 1) {
        for (i = 0; i < 9; i++) {
            out[(u32)i] = anim->kfs->v[i];
        }
        return;
    }
    for (k1 = anim->kfs + 1; k1->frame < frame; k1++) {
    }
    frame -= k1[-1].frame;
    len = k1->frame - k1[-1].frame;
    k0 = k1 - 1;
    if (k1->linear == 0) {
        func_80026E20(frame / (f32)len, &h00, &h01, &h10, &h11);
        a0 = (1.0 - k0->tension) * (1.0 + k0->continuity) * (1.0 + k0->bias);
        b0 = (1.0 - k0->tension) * (1.0 - k0->continuity) * (1.0 - k0->bias);
        a1 = (1.0 - k1->tension) * (1.0 - k1->continuity) * (1.0 + k1->bias);
        b1 = (1.0 - k1->tension) * (1.0 + k1->continuity) * (1.0 - k1->bias);
        if (k0->frame != 0) {
            s0 = (f32)len / (k1->frame - k0[-1].frame);
        }
        if (k1->frame != anim->last) {
            s1 = (f32)len / (k1[1].frame - k0->frame);
        }
    }
    o = out;
    for (i = 0; i < 9; i++, o++) {
        d = k1->v[i] - k0->v[i];
        if (k1->linear == 0) {
            if (k0->frame == 0) {
                m0 = (a0 + b0) * 0.5 * d;
            } else {
                m0 = ((k0->v[i] - k0[-1].v[i]) * a0 + b0 * d) * s0;
            }
            if (k1->frame == anim->last) {
                m1 = (a1 + b1) * 0.5 * d;
            } else {
                m1 = ((k1[1].v[i] - k1->v[i]) * b1 + a1 * d) * s1;
            }
            *o = k0->v[i] * h00 + k1->v[i] * h01 + m0 * h10 + m1 * h11;
        } else {
            *o = k0->v[i] + ((f32)frame / (f32)len) * d;
        }
    }
}

void func_80026E20(f32 t, f32* a, f32* b, f32* c, f32* d) {
    f32 t2 = t * t;
    f32 t3 = t * t2;
    f32 h1 = 3.0 * t2 - t3 - t3;
    f32 h3 = t3 - t2;

    *a = 1.0 - h1;
    *b = h1;
    *c = h3 - t2 + t;
    *d = h3;
}
