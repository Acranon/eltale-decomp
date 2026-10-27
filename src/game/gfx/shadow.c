#include "game/gfx/shadow.h"
#include "game/core/main.h"
#include "game/math/math.h"

/*
 * Shadows: a 64-entry queue of floor-aligned quads under objects, drawn in one pass.
 * Original file: 13DF0.c (ROM 0x13DF0).
 */

/* This file's .bss, 80084B80..80085290 (13DE0 also uses shadow_count). */
ShadowEntry shadow_queue[0x40];
s32 shadow_count;

/* Segment symbols (no module defines them). */
extern Gfx D_1000270[];
extern Vtx D_1000230[];
extern GfxFrameData D_2000000;

void Shadow_Queue(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale) {
    ShadowEntry* p;

    if ((u32)shadow_count < 0x40) {
        p = &shadow_queue[shadow_count++];
        p->x = x;
        p->y = y;
        p->z = z;
        p->rx = rx;
        p->ry = ry;
        p->rz = rz;
        p->scale = scale;
    }
}

void Shadow_DrawAll(GfxFrameData* arg0) {
    s32 n = shadow_count;
    ShadowEntry* p = shadow_queue;
    MtxF mf;

    if (n != 0) {
        gSPDisplayList(gfx_dl_head++, D_1000270);
        gSPFogPosition(gfx_dl_head++, gfx_fog_far, gfx_fog_near);
    }
    while (n != 0) {
        Math_MtxFAlignYToVector(&mf, p->rx, p->ry, p->rz);
        mf.mf[3][0] = p->x;
        mf.mf[3][1] = p->y;
        mf.mf[3][2] = p->z;
        Math_MtxFScaleAxes(&mf, p->scale, p->scale, p->scale);
        guMtxF2L(mf.mf, &arg0->mtx[gfx_mtx_index]);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gfx_mtx_index++;
        gSPVertex(gfx_dl_head++, D_1000230, 4, 0);
        gSP2Triangles(gfx_dl_head++, 0, 1, 2, 0, 1, 3, 2, 0);
        n--;
        p++;
    }
}
