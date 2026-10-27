#include "game/actor/anim.h"
#include "game/camera/camera.h"

/*
 * Actor model animation: state changes, root motion, frame advance, and node drawing.
 * Original file: 20DA0.c (ROM 0x20DA0).
 */

/*
 * Local copy of Actor (game/actor/actor.h, h_actors) until H2. The shared actor-model base: position, rotation, scale, root motion and animation state.
 * The player (inside player_state), NPCs, enemies, the boss, chests and the camera's focus
 * target are all this layout. Anim_* drive it.
 */
typedef struct Actor {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx; /* rotation passed to Math_MtxFRotScaleTrans by Anim_DrawModel */
    /* 0x10 */ f32 ry; /* the heading */
    /* 0x14 */ f32 rz;
    /* 0x18 */ f32 unk18; /* chest: half width of the open box */
    /* 0x1C */ f32 unk1C; /* chest: facing angle of the open box */
    /* 0x20 */ f32 unk20; /* chest: half depth of the open box */
    /* 0x24 */ f32 scale;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 nx; /* floor normal (chest: from CollResult, passed to Shadow_Queue) */
    /* 0x30 */ f32 ny;
    /* 0x34 */ f32 nz;
    /* 0x38 */ f32 rootX; /* root node position * scale, from Anim_UpdateRootMotion */
    /* 0x3C */ f32 rootY;
    /* 0x40 */ f32 rootZ;
    /* 0x44 */ f32 rootDx; /* root motion since the last update */
    /* 0x48 */ f32 rootDy;
    /* 0x4C */ f32 rootDz;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 anim; /* current AnimSet index */
    /* 0x54 */ u16 frame; /* frame within the current animation */
    /* 0x56 */ u16 ticks; /* frames since the animation was set (+1 per Anim_AdvanceFrame) */
    /* 0x58 */ u16 animStep; /* frames per Anim_AdvanceFrame */
    /* 0x5A */ s16 nextAnim; /* played when the current one ends */
    /* 0x5C */ u16 nextAnimStep;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 flags; /* 0x200 looped this frame, 0x400 animation changed */
    /* 0x62 */ u16 unk62;
    /* 0x64 */ void *unk64; /* per kind: player stats, enemy definition */
    /* 0x68 */ void *unk68; /* per kind: player data, enemy stats */
} Actor; /* 0x6C bytes */

/* This file's .bss, 8008BFC0..8008C040, in address order. */
Vec3f anim_node_world_positions[4];
s32 anim_node_position_count;
MtxF anim_billboard_mtx_scratch;

void Anim_SetCurrentAndNext(Actor* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    if (arg1 != -1) {
        if (arg1 != arg0->anim) {
            arg0->anim = arg1;
            arg0->flags = arg0->flags | 0x400;
            arg0->flags = arg0->flags & 0xFDFF;
        }

        arg0->animStep = arg2;
        if (arg5 & 1) {
            arg0->frame = arg0->ticks = 0;
        }
    }

    if (arg3 != -1) {
        if (arg3 != arg0->nextAnim) {
            arg0->nextAnim = arg3;
        }
        arg0->nextAnimStep = arg4;
    }
}

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ Vec3f unk18;
} Struct_80020568_xf;

void Anim_UpdateRootMotion(Actor* arg0, AnimSet* arg1, f32 scale) {
    s32 i;
    s16 count;
    u16 cur;
    s32 frame;
    Keyframe* kf;
    f32 x;
    f32 y;
    Struct_80020568_xf pos;
    AnimNode* anim;
    f32 z;

    count = arg1->nodeCount;
    cur = arg0->frame;
    anim = arg1->nodes;
    i = 0;
    while (i < count && anim->parent != 0) {
        i++;
        anim++;
    }
    frame = anim->track.last;
    if (frame != 0) {
        frame = cur % frame;
    } else {
        frame = 0;
    }
    Math_EvalTcbSpline(&anim->track, (f32*)&pos, frame);
    if (arg0->flags & 0x200) {
        kf = anim->track.kfs;
        frame = anim->track.last;
        while (kf->frame != frame) {
            kf++;
        }
        x = kf->v[0];
        y = kf->v[1];
        z = kf->v[2];
        arg0->rootDx = (pos.unk0.x + x) * scale - arg0->rootX;
        arg0->rootDy = (pos.unk0.y + y) * scale - arg0->rootY;
        arg0->rootDz = (pos.unk0.z + z) * scale - arg0->rootZ;
        arg0->rootX = pos.unk0.x * scale;
        arg0->rootY = pos.unk0.y * scale;
        arg0->rootZ = pos.unk0.z * scale;
    } else if (arg0->flags & 0x400) {
        arg0->rootDx = 0.0f;
        arg0->rootDy = 0.0f;
        arg0->rootDz = 0.0f;
        arg0->rootX = pos.unk0.x * scale;
        arg0->rootY = pos.unk0.y * scale;
        arg0->rootZ = pos.unk0.z * scale;
    } else {
        arg0->rootDx = pos.unk0.x * scale - arg0->rootX;
        arg0->rootDy = pos.unk0.y * scale - arg0->rootY;
        arg0->rootDz = pos.unk0.z * scale - arg0->rootZ;
        arg0->rootX = pos.unk0.x * scale;
        arg0->rootY = pos.unk0.y * scale;
        arg0->rootZ = pos.unk0.z * scale;
    }
}

void Anim_DrawModel(s32 arg0, Actor* arg1, AnimSet* arg2, s32 arg3) {
    s32 i;
    u16 frame;
    AnimNode* anims;
    u16 total;
    MtxF mtx;
    Vec3f scale;

    anim_node_position_count = 0;
    Math_MtxFRotScaleTrans(&mtx, arg1->rx, arg1->ry, arg1->rz, arg1->scale, arg1->x, arg1->y, arg1->z);
    scale.x = arg1->scale;
    scale.y = arg1->scale;
    scale.z = arg1->scale;
    anims = arg2->nodes;
    frame = arg1->frame;
    total = arg1->ticks;
    for (i = 0; i < arg2->nodeCount; i++) {
        if (anims[i].parent == 0) {
            Anim_DrawNode(&mtx, scale, arg0, i, frame, total, arg2, anims, arg3);
        }
    }
}

typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

extern Gfx* gfx_dl_head;
extern s32 gfx_mtx_index;
extern Unk2000000 D_2000000;

void Anim_DrawNode(MtxF* parent, Vec3f scale, s32 flags, s32 idx, s32 frame, s32 total, AnimSet* set,
                   AnimNode* anims, s32 buf) {
    s32 fr;
    s32 i;
    Gfx** dls;
    s32* tbl;
    MtxF mtx;
    Struct_80020568_xf xf;
    AnimNode* anim;

    anim = &anims[idx];
    fr = anim->track.last;
    if (fr != 0) {
        fr = frame % fr;
    } else {
        fr = 0;
    }
    Math_EvalTcbSpline(&anim->track, (f32*)&xf, fr);
    if (anim->parent == 0) {
        if (flags & 1) {
            xf.unk0.x = 0.0f;
            xf.unk0.z = 0.0f;
        }
        if (flags & 2) {
            xf.unk0.y = 0.0f;
        }
    }
    Math_MtxFRotDegScaleTrans(&mtx, xf.unk0.x, xf.unk0.y, xf.unk0.z, xf.unkC.y, xf.unkC.x, xf.unkC.z, xf.unk18.x, xf.unk18.y,
                  xf.unk18.z);
    Anim_ApplyPivotOffset(&mtx, anim);
    scale.x *= xf.unk18.x;
    scale.y *= xf.unk18.y;
    scale.z *= xf.unk18.z;
    if (anim->flags & 1) {
        Math_MtxFMul(parent, &mtx, &mtx);
        Math_MtxFAimAt(&anim_billboard_mtx_scratch, mtx.mf[3][0], mtx.mf[3][1], mtx.mf[3][2], camera_state.eyeX, camera_state.eyeY,
                      camera_state.eyeZ);
        Math_MtxFScaleAxes(&anim_billboard_mtx_scratch, scale.x, scale.y, scale.z);
        guMtxF2L(anim_billboard_mtx_scratch.mf, &((Unk2000000*)buf)->unkC0[gfx_mtx_index]);
    } else {
        Math_MtxFMul(parent, &mtx, &mtx);
        guMtxF2L(mtx.mf, &((Unk2000000*)buf)->unkC0[gfx_mtx_index]);
    }
    gSPMatrix(gfx_dl_head++, &D_2000000.unkC0[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    if (anim->flags & 2) {
        anim_node_world_positions[anim_node_position_count].x = mtx.mf[3][0];
        anim_node_world_positions[anim_node_position_count].y = mtx.mf[3][1];
        anim_node_world_positions[anim_node_position_count].z = mtx.mf[3][2];
        anim_node_position_count++;
    }
    dls = set->dls;
    tbl = anim->dlSeq;
    if (tbl == NULL) {
        i = anim->dl;
        if (i != -1) {
            if (dls[i] != NULL) {
                gSPDisplayList(gfx_dl_head++, dls[i]);
            }
        }
    } else {
        gSPDisplayList(gfx_dl_head++, dls[tbl[total % anim->dlSeqLen]]);
    }
    for (i = 0; i < set->nodeCount; i++) {
        if (anims[i].parent == idx + 1) {
            Anim_DrawNode(&mtx, scale, flags, i, frame, total, set, anims, buf);
        }
    }
}

void Anim_AdvanceFrame(s32 arg0, Actor* arg1, AnimSet* arg2) {
    s32 temp_v0 = arg1->frame += arg0;

    if (temp_v0 >= arg2->length) {
        if (arg1->anim != arg1->nextAnim) {
            arg1->anim = arg1->nextAnim;
            arg1->frame = 0U;
            arg1->ticks = 0U;
            arg1->animStep = arg1->nextAnimStep;
            arg1->flags |= 0x400;
        } else {
            arg1->frame = temp_v0 - arg2->length;
            arg1->flags |= 0x200;
        }
    } else {
        arg1->flags &= ~0x600;
    }
    arg1->ticks++;
}

void Anim_ApplyPivotOffset(MtxF* arg0, AnimNode* arg1) {
    f32 x, y, z;
    x = arg0->mf[0][0];
    y = arg0->mf[1][0];
    z = arg0->mf[2][0];
    arg0->mf[3][0] -= x * arg1->pivot.x + y * arg1->pivot.y + z * arg1->pivot.z;
    x = arg0->mf[0][1];
    y = arg0->mf[1][1];
    z = arg0->mf[2][1];
    arg0->mf[3][1] -= x * arg1->pivot.x + y * arg1->pivot.y + z * arg1->pivot.z;
    x = arg0->mf[0][2];
    y = arg0->mf[1][2];
    z = arg0->mf[2][2];
    arg0->mf[3][2] -= x * arg1->pivot.x + y * arg1->pivot.y + z * arg1->pivot.z;
}
