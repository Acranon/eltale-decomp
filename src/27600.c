#include "common.h"

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

#pragma GLOBAL_ASM("asm/nonmatchings/27600/func_80026A00.s")

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
