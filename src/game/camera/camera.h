#ifndef GAME_CAMERA_CAMERA_H
#define GAME_CAMERA_CAMERA_H

#include "common.h"
#include "game/math/math.h"
struct Actor; /* game/actor/actor.h (h_actors) */
#include "game/map/collision.h"

struct GfxFrameData;

/* The camera (camera_state; camera_saved_state holds a copy during a battle focus). */
typedef struct Camera {
    /* 0x00 */ s32 mode; /* index into camera_mode_handlers */
    /* 0x04 */ s32 focusFramesLeft; /* battle focus: frames until camera_saved_state is restored */
    /* 0x08 */ u16 flags; /* 0x40 battle focus active */
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 eyeX;
    /* 0x10 */ f32 eyeY;
    /* 0x14 */ f32 eyeZ;
    /* 0x18 */ f32 atX;
    /* 0x1C */ f32 atY;
    /* 0x20 */ f32 atZ;
    /* 0x24 */ f32 pitch; /* Math_Atan2(eye - at height, ground distance) */
    /* 0x28 */ f32 followYaw; /* the heading clamped to yawMin..yawMax (fixed eye) */
    /* 0x2C */ f32 yaw; /* Math_Atan2(eye - at, x and z) */
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 atVelY;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 orbitSpeed;
    /* 0x40 */ f32 eyeVelX;
    /* 0x44 */ f32 eyeVelY;
    /* 0x48 */ f32 eyeVelZ;
    /* 0x4C */ f32 distance; /* follow distance from the target */
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 orbitAngle; /* Camera_OrbitTarget turns the eye toward this angle */
    /* 0x58 */ f32 eyeHeight; /* minimum eye height above the target */
    /* 0x5C */ f32 atHeight; /* look-at height above the target */
    /* 0x60 */ f32 pitchMin;
    /* 0x64 */ f32 pitchMax;
    /* 0x68 */ f32 yawMin;
    /* 0x6C */ f32 yawMax;
    /* 0x70 */ f32 followGain; /* follow gain */
    /* 0x74 */ f32 velocityDamping; /* velocity damping */
    /* 0x78 */ f32 orbitGain; /* orbit gain */
    /* 0x7C */ f32 orbitDamping; /* orbit damping */
    /* 0x80 */ struct Actor *target;
    /* 0x84 */ f32 spawnHeadingOffset; /* angle added to the spawn heading by Camera_InitForMap */
} Camera; /* 0x88 bytes */

/* One camera preset (a map sub-area's list, or camera_default_presets). */
typedef struct CameraPreset {
    /* 0x00 */ s32 mode;
    /* 0x04 */ f32 x; /* the eye, for fixed-eye modes */
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 atHeight;
    /* 0x14 */ f32 eyeHeight;
    /* 0x18 */ f32 distance;
    /* 0x1C */ f32 pitchMin;
    /* 0x20 */ f32 pitchMax;
    /* 0x24 */ f32 yawMin;
    /* 0x28 */ f32 yawMax;
    /* 0x2C */ f32 fovy;
    /* 0x30 */ f32 near;
    /* 0x34 */ f32 far;
} CameraPreset; /* 0x38 bytes */

/* A sub-area's presets (MapAreaDef.cameraPresets[subarea]). */
typedef struct CameraPresetSet {
    /* 0x00 */ CameraPreset *presets;
    /* 0x04 */ u16 count;
    /* 0x06 */ u8 pad6[2];
} CameraPresetSet; /* 0x8 bytes */

/* Camera_SetPresetDelayedTurn's pending switch: wait, turn, then restore mode and flags. */
typedef struct CameraDelayedTurn {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 mode;
    /* 0x0C */ u16 flags;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 orbitAngle;
    /* 0x14 */ f32 orbitGain; /* Camera.orbitGain to restore */
    /* 0x18 */ f32 orbitDamping; /* Camera.orbitDamping to restore */
} CameraDelayedTurn; /* 0x1C bytes */

/* .bss 80085B80..80085F90 */
extern Camera camera_saved_state;
extern s32 camera_preset_count[2];
extern Vec2f camera_temp_vec;
extern u8 D_80085C18[8];
extern CollResult camera_eye_coll;
extern u16 D_80085C3C;
extern struct Actor camera_focus_target;
extern s32 camera_shake_timer;
extern f32 camera_shake_x;
extern f32 camera_shake_y;
extern s32 camera_height_osc_enabled[100];
extern Camera camera_state;
extern MtxF camera_proj_mtx;
extern MtxF camera_view_mtx;
extern f32 camera_fovy;
extern f32 camera_near;
extern f32 camera_far;
extern f32 camera_tan_half_fovy;
extern s32 camera_preset_index;
extern CameraPreset *camera_presets;
extern CameraDelayedTurn camera_delayed_turn;
extern f32 camera_battle_angle_offset;
extern u16 camera_persp_norm;

/* .data */
extern CameraPreset camera_default_presets[3];
extern void (*camera_mode_handlers[6])(Camera *);
extern s32 camera_height_osc_areas[7][2];
extern f32 camera_shake_offsets[8];
extern f32 camera_height_osc_phase_a;
extern f32 camera_height_osc_phase_b;

void Camera_InitForMap(void);
void Camera_Update(struct GfxFrameData *arg0);
void Camera_FollowTarget(Camera *arg0);
void Camera_UpdateFixedEye(Camera *arg0);
void Camera_UpdateHeading(Camera *arg0);
void Camera_UpdateBattle(Camera *arg0);
void Camera_UpdateDelayedTurn(Camera *arg0);
void func_80015B88(Camera *arg0);
void Camera_UpdateLookAt(Camera *arg0, struct Actor *arg1);
void Camera_OrbitTarget(Camera *arg0, struct Actor *arg1);
void Camera_Shake(s32 arg0);
void Camera_SetPreset(s32 arg0);
void Camera_StartBattleFocus(s32 arg0, struct Actor *arg1);
void Camera_SetPresetDelayedTurn(s32 arg0);
void Camera_SetTargetView(CameraPreset *arg0, struct Actor *arg1);
void Camera_TurnForExit(void);
f32 Camera_RaiseOverNpcs(Camera *arg0, f32 arg1);
void Camera_UpdateHeightOscillation(Vec3f *arg0);

#endif
