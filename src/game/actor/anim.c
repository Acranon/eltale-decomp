#include "game/actor/anim.h"
#include "game/camera/camera.h"
#include "game/actor/actor.h"
#include "game/core/main.h"
#include "game/math/math.h"

/*
 * Actor model animation: state changes, root motion, frame advance, and node drawing.
 * Original file: 20DA0.c (ROM 0x20DA0).
 */

/* This file's .bss, 8008BFC0..8008C040, in address order. */
Vec3f anim_node_world_positions[4];
s32 anim_node_position_count;
MtxF anim_billboard_mtx_scratch;

void Anim_SetCurrentAndNext(Actor* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    if (arg1 != -1) {
        if (arg1 != arg0->animIndex) {
            arg0->animIndex = arg1;
            arg0->animFlags = arg0->animFlags | 0x400;
            arg0->animFlags = arg0->animFlags & 0xFDFF;
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
    /* 0x00 */ Vec3f translation;
    /* 0x0C */ Vec3f rotation;
    /* 0x18 */ Vec3f scale;
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
    if (arg0->animFlags & 0x200) {
        kf = anim->track.kfs;
        frame = anim->track.last;
        while (kf->frame != frame) {
            kf++;
        }
        x = kf->v[0];
        y = kf->v[1];
        z = kf->v[2];
        arg0->unk44 = (pos.translation.x + x) * scale - arg0->rootX;
        arg0->unk48 = (pos.translation.y + y) * scale - arg0->rootY;
        arg0->unk4C = (pos.translation.z + z) * scale - arg0->rootZ;
        arg0->rootX = pos.translation.x * scale;
        arg0->rootY = pos.translation.y * scale;
        arg0->rootZ = pos.translation.z * scale;
    } else if (arg0->animFlags & 0x400) {
        arg0->unk44 = 0.0f;
        arg0->unk48 = 0.0f;
        arg0->unk4C = 0.0f;
        arg0->rootX = pos.translation.x * scale;
        arg0->rootY = pos.translation.y * scale;
        arg0->rootZ = pos.translation.z * scale;
    } else {
        arg0->unk44 = pos.translation.x * scale - arg0->rootX;
        arg0->unk48 = pos.translation.y * scale - arg0->rootY;
        arg0->unk4C = pos.translation.z * scale - arg0->rootZ;
        arg0->rootX = pos.translation.x * scale;
        arg0->rootY = pos.translation.y * scale;
        arg0->rootZ = pos.translation.z * scale;
    }
}

void Anim_DrawModel(s32 flags, Actor* arg1, AnimSet* arg2, struct GfxFrameData* frameData) {
    s32 i;
    u16 frame;
    AnimNode* anims;
    u16 total;
    MtxF mtx;
    Vec3f scale;

    anim_node_position_count = 0;
    Math_MtxFRotScaleTrans(&mtx, arg1->rotX, arg1->rot, arg1->rotZ, arg1->scale, arg1->x, arg1->y, arg1->z);
    scale.x = arg1->scale;
    scale.y = arg1->scale;
    scale.z = arg1->scale;
    anims = arg2->nodes;
    frame = arg1->frame;
    total = arg1->ticks;
    for (i = 0; i < arg2->nodeCount; i++) {
        if (anims[i].parent == 0) {
            Anim_DrawNode(&mtx, scale, flags, i, frame, total, arg2, anims, frameData);
        }
    }
}

void Anim_DrawNode(MtxF* parent, Vec3f scale, s32 flags, s32 idx, s32 frame, s32 total, AnimSet* set,
                   AnimNode* anims, struct GfxFrameData* buf) {
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
            xf.translation.x = 0.0f;
            xf.translation.z = 0.0f;
        }
        if (flags & 2) {
            xf.translation.y = 0.0f;
        }
    }
    Math_MtxFRotDegScaleTrans(&mtx, xf.translation.x, xf.translation.y, xf.translation.z, xf.rotation.y, xf.rotation.x, xf.rotation.z, xf.scale.x, xf.scale.y,
                  xf.scale.z);
    Anim_ApplyPivotOffset(&mtx, anim);
    scale.x *= xf.scale.x;
    scale.y *= xf.scale.y;
    scale.z *= xf.scale.z;
    if (anim->flags & 1) {
        Math_MtxFMul(parent, &mtx, &mtx);
        Math_MtxFAimAt(&anim_billboard_mtx_scratch, mtx.mf[3][0], mtx.mf[3][1], mtx.mf[3][2], camera_state.eyeX, camera_state.eyeY,
                      camera_state.eyeZ);
        Math_MtxFScaleAxes(&anim_billboard_mtx_scratch, scale.x, scale.y, scale.z);
        guMtxF2L(anim_billboard_mtx_scratch.mf, &buf->mtx[gfx_mtx_index]);
    } else {
        Math_MtxFMul(parent, &mtx, &mtx);
        guMtxF2L(mtx.mf, &buf->mtx[gfx_mtx_index]);
    }
    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
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
        if (arg1->animIndex != arg1->nextAnim) {
            arg1->animIndex = arg1->nextAnim;
            arg1->frame = 0U;
            arg1->ticks = 0U;
            arg1->animStep = arg1->nextAnimStep;
            arg1->animFlags |= 0x400;
        } else {
            arg1->frame = temp_v0 - arg2->length;
            arg1->animFlags |= 0x200;
        }
    } else {
        arg1->animFlags &= ~0x600;
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
