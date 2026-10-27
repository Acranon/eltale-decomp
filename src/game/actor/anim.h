#ifndef GAME_ACTOR_ANIM_H
#define GAME_ACTOR_ANIM_H

#include "common.h"
#include "game/math/math.h"
#include "game/math/keyframe.h"

/* The actor-model base type is Actor (game/actor/actor.h, h_actors). */
struct Actor;

/* One node of a model: its keyframe track, pivot, parent and display list. */
typedef struct AnimNode {
    /* 0x00 */ KfAnim track;
    /* 0x08 */ Vec3f pivot; /* subtracted in the node's frame by Anim_ApplyPivotOffset */
    /* 0x14 */ s8 parent; /* parent node index + 1, 0 = a root node */
    /* 0x15 */ s8 dl; /* index into AnimSet.dls, -1 = none */
    /* 0x16 */ u8 flags; /* 1 billboard, 2 record the world position */
    /* 0x17 */ u8 pad17;
    /* 0x18 */ s32 *dlSeq; /* if set: display list indices cycled by Actor.ticks */
    /* 0x1C */ u16 dlSeqLen;
    /* 0x1E */ u8 pad1E[2];
} AnimNode; /* 0x20 bytes */

/* A model: its nodes and display lists, and the loop length of its animation. */
typedef struct AnimSet {
    /* 0x00 */ s16 nodeCount;
    /* 0x02 */ s16 length; /* Anim_AdvanceFrame wraps Actor.frame here */
    /* 0x04 */ AnimNode *nodes;
    /* 0x08 */ Gfx **dls;
} AnimSet; /* 0xC bytes */

/* .bss 8008BFC0..8008C040 */
extern Vec3f anim_node_world_positions[4];
extern s32 anim_node_position_count;
extern MtxF anim_billboard_mtx_scratch;

void Anim_SetCurrentAndNext(struct Actor *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5);
void Anim_UpdateRootMotion(struct Actor *arg0, AnimSet *arg1, f32 scale);
void Anim_DrawModel(s32 arg0, struct Actor *arg1, AnimSet *arg2, s32 arg3);
void Anim_DrawNode(MtxF *parent, Vec3f scale, s32 flags, s32 idx, s32 frame, s32 total, AnimSet *set, AnimNode *anims,
                   s32 buf);
void Anim_AdvanceFrame(s32 arg0, struct Actor *arg1, AnimSet *arg2);
void Anim_ApplyPivotOffset(MtxF *arg0, AnimNode *arg1);

#endif
