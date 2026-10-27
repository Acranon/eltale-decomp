#ifndef GAME_GFX_EFFECT_H
#define GAME_GFX_EFFECT_H

#include "common.h"
#include "game/math/math.h"
#include "game/actor/anim.h"
#include "game/map/collision.h"
#include "game/gfx/sprite_effect.h"

struct GfxFrameData;
struct Actor; /* game/actor/actor.h (h_actors) */
struct MapObj; /* game/map/map.h */

/* A footstep dust emitter: spawns a particle every other frame at the actor's feet. */
typedef struct EffectFootEmitter {
    /* 0x00 */ s32 timer;
    /* 0x04 */ struct Actor *actor;
} EffectFootEmitter; /* 0x8 bytes */

/* A map object's particle emitter, queued each frame by Effect_QueueMapObjEmitter (double-buffered). */
typedef struct EffectMapObjEmitter {
    /* 0x00 */ s32 particleCountdown; /* frames to the next particle */
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 particleScale; /* the object's scale, the particle's size */
    /* 0x14 */ struct MapObj *mapObj; /* the object, to find it again next frame */
} EffectMapObjEmitter; /* 0x18 bytes */

/* A damage/heal number shown over an actor. */
typedef struct EffectFloatingNumber {
    /* 0x00 */ struct Actor *target;
    /* 0x04 */ u8 digits[8];
    /* 0x0C */ u16 timer;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ s32 styleAndColor; /* bit 15: large digits; low 4 bits: index into effect_floating_number_colors */
    /* 0x14 */ s32 numDigits;
    /* 0x18 */ s32 stackIndex; /* how many numbers the target already shows (stacks them) */
} EffectFloatingNumber; /* 0x1C bytes */

/* Spawns particles on a sphere that move to its centre (Effect_StartConvergeEmitter). */
typedef struct EffectConvergeEmitter {
    /* 0x00 */ s32 framesLeft; /* frames left */
    /* 0x04 */ s32 colorIndex; /* colour index of the particles (EffectSprite.unk3C) */
    /* 0x08 */ f32 centerX; /* the centre */
    /* 0x0C */ f32 centerY;
    /* 0x10 */ f32 centerZ;
    /* 0x14 */ f32 radius; /* the radius */
} EffectConvergeEmitter; /* 0x18 bytes */

/* A model effect's scrolling/animated texture (copied from a table by Effect_CreateModelEffect). */
typedef struct EffectTexAnim {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 mask;
    /* 0x04 */ u16 shift;
    /* 0x06 */ u16 tlut;
    /* 0x08 */ s32 img;
    /* 0x0C */ s16 s;
    /* 0x0E */ s16 t;
    /* 0x10 */ s16 ds;
    /* 0x12 */ s16 dt;
} EffectTexAnim; /* 0x14 bytes */

/* A model effect: an animated model drawn with Anim_DrawNode (Effect_CreateModelEffect). */
typedef struct EffectModel {
    /* 0x00 */ u16 framesLeft; /* frames left */
    /* 0x02 */ u16 loopLength; /* the model's loop length (restart value) */
    /* 0x04 */ u16 age; /* frames since start */
    /* 0x06 */ u16 colorIndex; /* colour index */
    /* 0x08 */ u16 flags; /* flags */
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 x; /* position */
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 rotationY; /* rotation about y */
    /* 0x1C */ f32 scaleX; /* scale */
    /* 0x20 */ f32 scaleY;
    /* 0x24 */ f32 scaleZ;
    /* 0x28 */ f32 upX; /* the up vector with flags bit 2 */
    /* 0x2C */ f32 upY;
    /* 0x30 */ f32 upZ;
    /* 0x34 */ s32 animFrame; /* animation frame */
    /* 0x38 */ AnimSet anim;
    /* 0x44 */ EffectTexAnim tex;
} EffectModel; /* 0x58 bytes */

/* A light streak (Effect_SpawnStreakBurst). */
typedef struct EffectStreak {
    /* 0x00 */ u16 framesLeft; /* frames left */
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
    /* 0x18 */ f32 vz;
    /* 0x1C */ f32 x0; /* the start */
    /* 0x20 */ f32 y0;
    /* 0x24 */ f32 z0;
} EffectStreak; /* 0x28 bytes */

typedef struct EffectStatUpMarker {
    /* 0x00 */ u16 framesLeft; /* frames left */
    /* 0x02 */ s16 unk2;
} EffectStatUpMarker; /* 0x4 bytes */

/* A ring of 16 points laid on the floor around a centre (Effect_CreateTerrainRing). */
typedef struct EffectRing {
    /* 0x00 */ u16 state; /* state: 0 free, 1 growing, 2 shown, 3 fading */
    /* 0x02 */ u16 stateFrames; /* frames in the state */
    /* 0x04 */ u16 stateLength; /* the state's length */
    /* 0x06 */ u16 colorIndex; /* colour index */
    /* 0x08 */ f32 centerX; /* the centre */
    /* 0x0C */ f32 centerY;
    /* 0x10 */ f32 centerZ;
    /* 0x14 */ Vec3f pts[16];
    /* 0xD4 */ Vec3f norms[16];
} EffectRing; /* 0x194 bytes */

/* .data 8004EE20..8004F060 */
extern EffectSprite effect_foot_particle_template;
extern f32 effect_foot_particle_scale_anim[12];
extern u8 effect_foot_particle_alpha_anim[12];
extern u8 effect_mapobj_particle_alpha_anim[48];
extern s32 effect_flipbook_frame_ptrs[3];
extern f32 effect_flipbook_scale_anim[12];
extern u8 effect_flipbook_alpha_anim[12];
extern u8 effect_floating_number_colors[4][4];
extern EffectSprite effect_converge_particle_template;
extern EffectSprite effect_burst_particle_template;
extern u16 effect_ring_grow_frames[4];
extern u8 effect_ring_colors[3][4];
extern u8 effect_ring_alpha_values[4];
extern s32 effect_model_tlut_ptrs[4];
extern u8 effect_stat_up_marker_colors[5][4];

/* .bss 800863F0..80087E30 */
extern s32 effect_mapobj_emitter_count;
extern u16 effect_model_frame_counter;
extern s32 effect_mapobj_emitter_prev_count;
extern EffectFootEmitter effect_foot_emitter_slots[8];
extern EffectMapObjEmitter effect_mapobj_emitter_buf1[8];
extern EffectMapObjEmitter effect_mapobj_emitter_buf0[8];
extern EffectFloatingNumber effect_floating_number_slots[10];
extern EffectConvergeEmitter effect_converge_emitter_slots[8];
extern EffectModel effect_model_slots[32];
extern EffectStreak effect_streak_slots[32];
extern EffectStatUpMarker effect_stat_up_marker_slots[4];
extern EffectRing effect_ring_slots[4];
extern u16 effect_loaded_tlut_index;
extern Vec2f effect_temp_vec;
extern u8 D_80087E08[8]; /* unreferenced */
extern CollResult effect_ring_coll;

void Effect_ResetAll(void);
void Effect_UpdateAndDrawAll(struct GfxFrameData *arg0);
void Effect_ResetFootEmitters(void);
void Effect_StartFootEmitter(struct Actor *arg0);
void Effect_UpdateFootEmitters(void);
void Effect_UpdateFootParticle(EffectSprite *arg0);
void Effect_ResetMapObjEmitters(void);
void Effect_QueueMapObjEmitter(f32 x, f32 y, f32 z, struct MapObj *arg3);
void Effect_UpdateMapObjEmitters(void);
void Effect_UpdateMapObjParticle(EffectSprite *arg0);
void Effect_SpawnFlipbookSprite(f32 x, f32 y, f32 z);
void Effect_UpdateFlipbookSprite(EffectSprite *arg0);
void Effect_ResetFloatingNumbers(void);
void Effect_AddFloatingNumber(struct Actor *arg0, s32 arg1, s32 arg2);
void Effect_DrawFloatingNumbers(void);
void Effect_ResetConvergeEmitters(void);
void Effect_StartConvergeEmitter(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void Effect_UpdateConvergeEmitters(void);
void Effect_UpdateConvergeParticle(EffectSprite *arg0);
void Effect_SpawnBurst(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void Effect_UpdateBurstParticle(EffectSprite *arg0);
void Effect_ResetStreaks(void);
void Effect_UpdateAndDrawStreaks(struct GfxFrameData *arg0);
void Effect_SpawnStreakBurst(f32 x, f32 y, f32 z);
void Effect_ResetRings(void);
s32 Effect_CreateTerrainRing(u16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void Effect_FadeRing(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void Effect_UpdateAndDrawRings(struct GfxFrameData *arg0);
void Effect_ResetModelEffects(void);
EffectModel *Effect_CreateModelEffect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                                      f32 arg9, f32 arg10, f32 arg11);
void Effect_UpdateAndDrawModelEffects(struct GfxFrameData *arg0);
s32 Effect_DrawModelEffectGeometry(EffectModel *arg0, struct GfxFrameData *arg1);
s32 Effect_ConfigureModelEffectTexture(EffectModel *arg0);
void Effect_ResetStatUpMarkers(void);
void Effect_DrawStatUpMarkers(struct GfxFrameData *arg0);
void Effect_StartStatUpMarker(s32 arg0);

#endif
