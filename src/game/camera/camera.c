#include "game/camera/camera.h"
#include "game/actor/actor.h"

/*
 * Camera: per-map presets, the mode handlers (follow, fixed eye, battle, delayed turn),
 * shake, the eye-height oscillation, and the projection/view matrices for each frame.
 * Original file: 15150.c (ROM 0x15150).
 */






typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk8007ABB0;



/* 15150 .bss, 80085B80..80085F90, in address order (first declaration fixes the order). */
Camera camera_saved_state;
s32 camera_preset_count[2];
Vec2f camera_temp_vec;
u8 D_80085C18[8];
CollResult camera_eye_coll;
u16 D_80085C3C;
Actor camera_focus_target;
s32 camera_shake_timer;
f32 camera_shake_x;
f32 camera_shake_y;
s32 camera_height_osc_enabled[100];
Camera camera_state;
MtxF camera_proj_mtx;
MtxF camera_view_mtx;
f32 camera_fovy;
f32 camera_near;
f32 camera_far;
f32 camera_tan_half_fovy;
s32 camera_preset_index;
CameraPreset* camera_presets;
CameraDelayedTurn camera_delayed_turn;
f32 camera_battle_angle_offset;
u16 camera_persp_norm;

extern s32 npc_drawn_count;
extern Unk8007ABB0* npc_drawn_list[];


typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ CameraPresetSet* unk24;
} Unk8007C284;

extern Mtx D_80301098;
extern Mtx D_8030EB68;
extern s32 D_80084308;
extern u16 D_8007AA82;
extern Unk8007C284* map_area_def;
extern s32 map_id;
extern s32 map_subarea;
extern Vec3f D_8007AA20;
extern f32 player_spawn_rot;
void guOrtho(Mtx*, f32, f32, f32, f32, f32, f32, f32);

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u16 unk14;
} Unk8007C288;

/* Local view of GfxFrameData (game/core/main.h, h_core) until H2. */
typedef struct GfxFrameData {
    /* 0x0000 */ Mtx proj;
    /* 0x0040 */ Mtx unk40;
    /* 0x0080 */ Mtx view;
    /* 0x00C0 */ Mtx unkC0[0x226];
    /* 0x8A40 */ LookAt lookAt;
} Unk15150Dyn;

extern Unk8007C288* map_subarea_def;
extern u16 battle_flags;
extern s32 core_flags;
extern s32 D_8008C168;
extern u16 input_pressed_buttons;
extern s32 gfx_mtx_index;
extern Gfx* gfx_dl_head;
extern Unk15150Dyn D_2000000;
void Camera_UpdateHeightOscillation(Vec3f*);

f32 sinf(f32);
f32 cosf(f32);
f32 sqrtf(f32);
void Camera_FollowTarget(Camera*);
void Camera_SetPreset(s32);
void Camera_UpdateFixedEye(Camera*);
void Camera_UpdateHeading(Camera*);
void Camera_UpdateBattle(Camera*);
void Camera_UpdateDelayedTurn(Camera*);

CameraPreset camera_default_presets[3] = {
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 15.0f, 65.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 72.0f, 144.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 2e+01f, 55.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
};
void (*camera_mode_handlers[6])(Camera*) = {
    Camera_FollowTarget, Camera_UpdateFixedEye, Camera_FollowTarget, Camera_UpdateHeading, Camera_UpdateBattle, Camera_UpdateDelayedTurn,
};
s32 camera_height_osc_areas[7][2] = {
    { 25, 2 }, { 25, 3 }, { 25, 4 }, { 25, 5 }, { 25, 8 }, { 25, 9 }, { 12, 2 },
};
f32 camera_shake_offsets[8] = { 0.0f, -0.1f, 0.0f, -0.05f, 0.1f, -0.1f, -0.05f, 0.08f };
f32 camera_height_osc_phase_a = 0.0f;
f32 camera_height_osc_phase_b = 0.0f;

void Camera_InitForMap(void) {
    s32 pad[2];
    Camera* cam = &camera_state;
    Vec3f* pos = &D_8007AA20;
    CameraPreset* p;
    s32 i;

    guOrtho(&D_80301098, -159.0f, 159.0f, 119.0f, -119.0f, 10.0f, 200.0f, 1.0f);
    guOrtho(&D_8030EB68, -159.0f, 159.0f, 119.0f, -119.0f, 10.0f, 200.0f, 1.0f);
    if (D_80084308 < 0) {
        cam->unk84 = 3.1415927f;
    }
    camera_preset_index = (D_8007AA82 >> 1) & 7;
    if (map_area_def->unk24 != NULL) {
        camera_presets = map_area_def->unk24[map_subarea].presets;
        camera_preset_count[0] = map_area_def->unk24[map_subarea].count;
    } else {
        camera_presets = camera_default_presets;
        camera_preset_count[0] = 1;
    }
    p = &camera_presets[camera_preset_index];
    cam->mode = p->mode;
    cam->flags = 1;
    cam->unk4 = 0;
    cam->target = (Actor*)pos;
    cam->pitchMin = p->pitchMin;
    cam->pitchMax = p->pitchMax;
    cam->yawMin = p->yawMin;
    cam->yawMax = p->yawMax;
    cam->distance = p->distance;
    cam->unk50 = 0.0f;
    cam->eyeHeight = p->eyeHeight;
    cam->atHeight = p->atHeight;
    switch (cam->mode) {
        case 0:
        case 2:
            camera_temp_vec.x = 0.0f;
            camera_temp_vec.y = cam->distance * 0.8;
            cam->eyeY = pos->y + p->eyeHeight;
            Math_RotateVec2(cam->unk84 + player_spawn_rot, &camera_temp_vec);
            cam->eyeX = pos->x - camera_temp_vec.x;
            cam->eyeZ = pos->z - camera_temp_vec.y;
            cam->orbitAngle = 0.0f;
            break;
        case 1:
            cam->eyeX = p->x;
            cam->eyeY = p->y;
            cam->eyeZ = p->z;
            cam->orbitAngle = 0.0f;
            break;
    }
    cam->pitch = 0.0f;
    cam->yaw = 0.0f;
    cam->unk28 = 0.0f;
    cam->atX = pos->x;
    cam->atY = pos->y + cam->atHeight;
    cam->atZ = pos->z;
    cam->unk30 = 0.0f;
    cam->atVelY = 0.0f;
    cam->unk38 = 0.0f;
    cam->eyeVelX = cam->eyeVelY = cam->eyeVelZ = 0.0f;
    cam->orbitSpeed = 0.0f;
    if (cam) {}
    cam->unk70 = 0.02f;
    if (cam) {}
    cam->unk74 = 0.8f;
    cam->unk78 = 0.005f;
    cam->unk7C = 0.8f;
    camera_shake_timer = 0;
    D_80085C3C = 0;
    camera_fovy = p->fovy;
    camera_near = p->near;
    camera_far = p->far;
    camera_battle_angle_offset = 0.0f;
    camera_height_osc_enabled[0] = 0;
    for (i = 0; i < 7; i++) {
        if (map_id == camera_height_osc_areas[i][0] && map_subarea == camera_height_osc_areas[i][1]) {
            camera_height_osc_enabled[0]++;
            break;
        }
    }
}

void Camera_Update(Unk15150Dyn* arg0) {
    Camera* cam = &camera_state;
    f32 a;
    s32 idx;
    s32 pad;

    if ((map_subarea_def->unk14 & 2) && !(battle_flags & 1) && cam->mode != 3) {
        idx = (D_8007AA82 >> 1) & 7;
        if (idx != camera_preset_index) {
            Camera_SetPreset(idx);
        }
    }
    camera_mode_handlers[cam->mode](cam);
    if (!(core_flags & 0x82) && D_8008C168 == 0 && !(battle_flags & 1) && !(map_subarea_def->unk14 & 2) &&
        (input_pressed_buttons & 0x20) && camera_preset_count[0] >= 2) {
        camera_preset_index++;
        if (camera_preset_index >= camera_preset_count[0]) {
            camera_preset_index = 0;
        }
        Camera_SetPreset(camera_preset_index);
    }
    camera_temp_vec.y = 0.0f;
    if (camera_height_osc_enabled[0] != 0) {
        Camera_UpdateHeightOscillation((Vec3f*)&camera_temp_vec);
    }
    guPerspectiveF(camera_proj_mtx.mf, &camera_persp_norm, camera_fovy, 1.3333334f, camera_near, camera_far, 1.0f);
    guLookAtReflectF(camera_view_mtx.mf, &arg0->lookAt, cam->eyeX, cam->eyeY + camera_temp_vec.y, cam->eyeZ, cam->atX, cam->atY,
                     cam->atZ, 0.0f, 1.0f, 0.0f);
    guMtxF2L(camera_proj_mtx.mf, &arg0->proj);
    guMtxF2L(camera_view_mtx.mf, &arg0->view);
    if (camera_shake_timer != 0) {
        guTranslate(&arg0->unkC0[gfx_mtx_index], camera_shake_x, camera_shake_y, 0.0f);
        camera_shake_x *= -0.8;
        camera_shake_y *= -0.8;
        camera_shake_timer--;
        gSPMatrix(gfx_dl_head++, &D_2000000.unkC0[gfx_mtx_index], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gfx_mtx_index++;
        gSPMatrix(gfx_dl_head++, &D_2000000.proj, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    } else {
        gSPMatrix(gfx_dl_head++, &D_2000000.proj, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    }
    gSPMatrix(gfx_dl_head++, &D_2000000.view, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPLookAt(gfx_dl_head++, &D_2000000.lookAt);
    gSPPerspNormalize(gfx_dl_head++, camera_persp_norm);
    a = camera_fovy * 0.017453292519943295 / 2;
    camera_tan_half_fovy = sinf(a) / cosf(a);
}

extern s32 core_flags;
extern u16 input_held_buttons;
extern u16 battle_flags;
extern f32 D_8007AA24;
void func_80015B88(Camera *arg0);
void Camera_UpdateLookAt(Camera *arg0, Actor *arg1);
void Camera_OrbitTarget(Camera *arg0, Actor *arg1);
f32 Camera_RaiseOverNpcs(Camera *arg0, f32 arg1);
void Camera_FollowTarget(Camera *arg0)
{
  u8 locked;
  f32 dx;
  f32 y;
  f32 dz;
  f32 dist;
  f32 a;
  f32 vx;
  f32 ny;
  f32 vz;
  Actor *target;
  target = arg0->target;
  func_80015B88(arg0);
  if (((!(core_flags & 0x82)) && (!(battle_flags & 0x200))) && (!(arg0->flags & 0x40)))
  {
    if ((input_held_buttons & 0x4000) || (arg0->mode == 2))
    {
      arg0->flags |= 0x24;
    }
    else
    {
      arg0->flags &= ~0x24;
    }
  }
  else
  {
    arg0->flags &= ~0x24;
  }
  dx = target->x - arg0->eyeX;
  dz = target->z - arg0->eyeZ;
  dist = sqrtf((dx * dx) + (dz * dz));
  if (dist != 0.0f)
  {
    if (arg0->distance < dist)
    {
      a = arg0->distance / dist;
      vx = (dx - (dx * a)) * arg0->unk70;
      vz = (dz - (dz * a)) * arg0->unk70;
    }
    else
      if (dist <= arg0->distance)
    {
      a = arg0->distance / dist;
      vx = ((dx - (dx * a)) * arg0->unk70) * 0.5;
      vz = ((dz - (dz * a)) * arg0->unk70) * 0.5;
    }
  }
  else
  {
    vz = 0.0f;
    vx = 0.0f;
  }
  arg0->eyeVelX += vx;
  arg0->eyeVelZ += vz;
  arg0->eyeX += arg0->eyeVelX;
  arg0->eyeZ += arg0->eyeVelZ;
  arg0->eyeVelX *= arg0->unk74;
  arg0->eyeVelZ *= arg0->unk74;
  locked = 0;
  if ((dist < 25.0f) && (!(core_flags & 0x80)))
  {
    a = target->rot - arg0->unk28;
    if (a > 3.141592653589793)
    {
      a -= 6.283185307179586;
    }
    else
      if (a < (-3.141592653589793))
    {
      a += 6.283185307179586;
    }
    if ((a < 1.5707963267948966) && (a > (-1.5707963267948966)))
    {
      arg0->orbitAngle = ((a < 0.0f) ? (1.5707963267948966) : (-1.5707963267948966)) + target->rot;
    }
    arg0->flags |= 4;
    locked = 1;
  }
  else
    if (arg0->flags & 0x20)
  {
    arg0->orbitAngle = target->rot + 3.141592653589793;
    if (arg0->orbitAngle > 3.141592653589793)
    {
      arg0->orbitAngle -= 6.283185307179586;
    }
    else
      if (arg0->orbitAngle < (-3.141592653589793))
    {
      arg0->orbitAngle += 6.283185307179586;
    }
  }
  Camera_OrbitTarget(arg0, target);
  camera_eye_coll.x = 4.0f;
  Coll_ResolveFloorAndWalls(arg0->eyeX, arg0->eyeY, arg0->eyeZ, 0x602, &camera_eye_coll);
  arg0->eyeX = camera_eye_coll.x;
  arg0->eyeZ = camera_eye_coll.z;
  if (camera_eye_coll.flags & 0x8000)
  {
    y = target->y;
  }
  else
  {
    y = camera_eye_coll.y;
  }
  D_80085C3C = camera_eye_coll.flags;
  dz = target->y + arg0->eyeHeight;
  if (y < dz)
  {
    y = dz;
  }
  y = Camera_RaiseOverNpcs(arg0, y);
  if ((battle_flags & 1) && (y < D_8007AA24))
  {
    y = D_8007AA24;
  }
  ny = y - arg0->eyeY;
  ny *= arg0->unk70 * ((ny < 0.0f) ? (0.2) : (0.8));
  arg0->eyeVelY += ny;
  arg0->eyeY += arg0->eyeVelY;
  arg0->eyeVelY *= arg0->unk74;
  Camera_UpdateLookAt(arg0, target);
  dx = arg0->eyeX - arg0->atX;
  y = arg0->eyeY - arg0->atY;
  dz = arg0->eyeZ - arg0->atZ;
  if ((((dx > (-0.5)) && (dx < 0.5)) && (dz > (-0.5))) && (dz < 0.5))
  {
    arg0->eyeX += 0.5;
    arg0->eyeZ += 0.5;
  }
  dist = sqrtf((dx * dx) + (dz * dz));
  if ((y != 0.0f) || (dist != 0.0f))
  {
    arg0->pitch = Math_Atan2(y, dist);
  }
  if ((dx != 0.0f) || (dz != 0.0f))
  {
    arg0->yaw = Math_Atan2(dx, dz);
    if (!locked)
    {
      arg0->unk28 = arg0->yaw;
    }
  }
}



void func_80015B88(Camera* arg0);
void Camera_UpdateLookAt(Camera* arg0, Actor* arg1);
void Camera_UpdateFixedEye(Camera* arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    Actor* target;

    target = arg0->target;
    func_80015B88(arg0);
    Camera_UpdateLookAt(arg0, target);
    dx = arg0->eyeX - arg0->atX;
    dy = arg0->eyeY - arg0->atY;
    dz = arg0->eyeZ - arg0->atZ;
    dist = sqrtf(dx * dx + dz * dz);
    if (dy != 0.0f || dist != 0.0f) {
        arg0->pitch = Math_Atan2(dy, dist);
    }
    if (dx != 0.0f || dz != 0.0f) {
        arg0->unk28 = Math_Atan2(dx, dz);
    }
    if (arg0->pitchMin != 0.0f || arg0->pitchMax != 0.0f) {
        if (arg0->pitch < arg0->pitchMin) {
            arg0->pitch = arg0->pitchMin;
            dx = dist / cosf(arg0->pitchMin);
            arg0->atY = arg0->eyeY - sinf(arg0->pitchMin) * dx;
        } else if (arg0->pitchMax < arg0->pitch) {
            arg0->pitch = arg0->pitchMax;
            dx = dist / cosf(arg0->pitchMax);
            arg0->atY = arg0->eyeY - sinf(arg0->pitchMax) * dx;
        }
    }
    if (arg0->yawMin < arg0->yawMax) {
        if (arg0->unk28 < arg0->yawMin) {
            arg0->unk28 = arg0->yawMin;
            camera_temp_vec.x = 0.0f;
            camera_temp_vec.y = -dist;
            Math_RotateVec2(arg0->unk28, &camera_temp_vec);
            arg0->atX = arg0->eyeX + camera_temp_vec.x;
            arg0->atZ = arg0->eyeZ + camera_temp_vec.y;
        } else if (arg0->yawMax < arg0->unk28) {
            arg0->unk28 = arg0->yawMax;
            camera_temp_vec.x = 0.0f;
            camera_temp_vec.y = -dist;
            Math_RotateVec2(arg0->unk28, &camera_temp_vec);
            arg0->atX = arg0->eyeX + camera_temp_vec.x;
            arg0->atZ = arg0->eyeZ + camera_temp_vec.y;
        }
    } else if (arg0->yawMax < arg0->yawMin) {
        if (arg0->unk28 < 0.0) {
            if (arg0->yawMax < arg0->unk28) {
                arg0->unk28 = arg0->yawMax;
                camera_temp_vec.x = 0.0f;
                camera_temp_vec.y = -dist;
                Math_RotateVec2(arg0->unk28, &camera_temp_vec);
                arg0->atX = arg0->eyeX + camera_temp_vec.x;
                arg0->atZ = arg0->eyeZ + camera_temp_vec.y;
            }
        } else if (arg0->unk28 < arg0->yawMin) {
            arg0->unk28 = arg0->yawMin;
            camera_temp_vec.x = 0.0f;
            camera_temp_vec.y = -dist;
            Math_RotateVec2(arg0->unk28, &camera_temp_vec);
            arg0->atX = arg0->eyeX + camera_temp_vec.x;
            arg0->atZ = arg0->eyeZ + camera_temp_vec.y;
        }
    }
    arg0->yaw = arg0->unk28;
}

void Camera_UpdateHeading(Camera* arg0) {
    f32 dx = arg0->eyeX - arg0->atX;
    f32 dz = arg0->eyeZ - arg0->atZ;

    if (dx != 0.0f || dz != 0.0f) {
        arg0->unk28 = arg0->yaw = Math_Atan2(dx, dz);
    }
}

extern f32 battle_center_x;
extern f32 battle_center_z;
extern u16 input_pressed_buttons;
void Camera_UpdateBattle(Camera* arg0) {
    f32 a;

    if (arg0->flags & 0x40) {
        if (--arg0->unk4 == 0) {
            arg0->flags &= ~0x40;
            *arg0 = camera_saved_state;
        }
    } else {
        a = Math_Atan2(battle_center_x - arg0->target->x, battle_center_z - arg0->target->z) + 3.141592653589793;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        a = (s32)(a / 0.39269908169872414) * 0.39269908169872414 - 0.19634954084936207;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        a += camera_battle_angle_offset;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        arg0->orbitAngle = a;
        if (input_pressed_buttons & 0x20) {
            camera_battle_angle_offset += 0.7853981633974483;
            if (camera_battle_angle_offset > 3.141592653589793) {
                camera_battle_angle_offset -= 6.283185307179586;
            } else if (camera_battle_angle_offset < -3.141592653589793) {
                camera_battle_angle_offset += 6.283185307179586;
            }
        }
    }
    Camera_FollowTarget(arg0);
}

void Camera_UpdateDelayedTurn(Camera* arg0) {
    switch (camera_delayed_turn.state) {
        case 0:
            if (--camera_delayed_turn.timer == 0) {
                camera_delayed_turn.state++;
                camera_delayed_turn.timer = 75;
                arg0->flags |= 0x10;
            }
            break;
        case 1:
            if (--camera_delayed_turn.timer == 0) {
                arg0->mode = camera_delayed_turn.mode;
                arg0->flags = camera_delayed_turn.flags;
                camera_state.unk78 = camera_delayed_turn.unk14;
                camera_state.unk7C = camera_delayed_turn.unk18;
            }
            break;
    }
    Camera_FollowTarget(arg0);
}

void func_80015B88(Camera* arg0) {
}

void Camera_UpdateLookAt(Camera* arg0, Actor* arg1) {
    f32 y;

    arg0->atX = arg1->x;
    arg0->atZ = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        y = arg1->unk68->unk94;
    } else {
        y = arg1->y;
    }
    y += arg0->atHeight - arg0->atY;
    arg0->atVelY += y * arg0->unk70 * 2;
    arg0->atY += arg0->atVelY;
    arg0->atVelY = arg0->atVelY * (arg0->unk74 * 0.8);
}

void Camera_OrbitTarget(Camera* arg0, Actor* arg1) {
    f32 dx;
    f32 dz;
    f32 angle;
    f32 speed;

    dx = arg0->eyeX - arg1->x;
    dz = arg0->eyeZ - arg1->z;
    if (arg0->flags & 0x14) {
        angle = Math_Atan2(dx, dz) - arg0->orbitAngle;
        if (angle > 3.141592653589793) {
            angle -= 6.283185307179586;
        } else if (angle < -3.141592653589793) {
            angle += 6.283185307179586;
        }
        speed = arg0->unk78 * angle + arg0->orbitSpeed;
    } else {
        speed = arg0->orbitSpeed;
    }
    arg0->orbitSpeed = arg0->unk7C * speed;
    camera_temp_vec.x = dx;
    camera_temp_vec.y = dz;
    Math_RotateVec2(speed, &camera_temp_vec);
    arg0->eyeX = arg1->x - camera_temp_vec.x;
    arg0->eyeZ = arg1->z + camera_temp_vec.y;
}

void Camera_Shake(s32 arg0) {
    camera_shake_timer = 15;
    camera_shake_x = camera_shake_offsets[arg0 * 2];
    camera_shake_y = camera_shake_offsets[arg0 * 2 + 1];
}

void Camera_SetPreset(s32 arg0) {
    Camera* cam = &camera_state;

    camera_preset_index = arg0;
    if (cam->flags & 0x40) {
        cam->target = camera_saved_state.target;
    }
    cam->mode = camera_presets[arg0].mode;
    if (cam->mode != 0 && cam->mode != 2) {
        cam->eyeX = camera_presets[arg0].x;
        cam->eyeY = camera_presets[arg0].y;
        cam->eyeZ = camera_presets[arg0].z;
    }
    cam->flags &= 0xFFAF;
    cam->distance = camera_presets[arg0].distance;
    cam->eyeHeight = camera_presets[arg0].eyeHeight;
    cam->atHeight = camera_presets[arg0].atHeight;
    cam->yawMin = camera_presets[arg0].yawMin;
    cam->yawMax = camera_presets[arg0].yawMax;
    cam->pitchMin = camera_presets[arg0].pitchMin;
    cam->pitchMax = camera_presets[arg0].pitchMax;
    camera_fovy = camera_presets[arg0].fovy;
    camera_near = camera_presets[arg0].near;
    camera_far = camera_presets[arg0].far;
    cam->eyeVelX = cam->eyeVelY = cam->eyeVelZ = 0.0f;
    cam->orbitSpeed = 0.0f;
}

extern f32 D_8007AA24;
extern u16 battle_flags;
void Camera_StartBattleFocus(s32 arg0, Actor* arg1) {
    f32 h;

    if (!(battle_flags & 1)) {
        return;
    }
    if (!(camera_state.flags & 0x40)) {
        camera_saved_state = camera_state;
    }
    camera_focus_target.x = arg1->x;
    camera_focus_target.z = arg1->z;
    if (arg1->unk5E & 4) {
        camera_focus_target.y = D_8007AA24;
    } else if (arg1->unk64->unk0 == 1) {
        camera_focus_target.y = arg1->unk68->unk94;
    } else {
        camera_focus_target.y = arg1->y;
    }
    camera_focus_target.scale = arg1->scale;
    camera_focus_target.unk64 = arg1->unk64;
    camera_focus_target.unk68 = arg1->unk68;
    if (arg1->unk5E & 4) {
        h = arg1->unk64->unk1C * arg1->scale + 40.0;
    } else if (arg1->unk64->unk1C < arg1->unk64->unk18) {
        h = arg1->unk64->unk18 * arg1->scale * 2.0 + 40.0;
    } else {
        h = arg1->unk64->unk1C * arg1->scale * 2.0 + 40.0;
    }
    camera_state.mode = 4;
    camera_state.flags |= 0x40;
    camera_state.target = &camera_focus_target;
    camera_state.eyeHeight = (arg1->unk5E & 4) ? 20.0 : 15.0;
    camera_state.eyeVelZ = 0.0f;
    camera_state.distance = h;
    camera_state.unk4 = arg0;
    camera_state.eyeVelY = camera_state.eyeVelZ;
    camera_state.orbitSpeed = 0.0f;
    camera_temp_vec.x = 0.0f;
    camera_state.eyeVelX = camera_state.eyeVelY;
    camera_temp_vec.y = h + 10.0;
    Math_RotateVec2(camera_state.orbitAngle, &camera_temp_vec);
    camera_state.eyeX = arg1->x + camera_temp_vec.x;
    camera_state.eyeY = camera_focus_target.y + camera_state.eyeHeight * 1.1;
    camera_state.eyeZ = arg1->z + camera_temp_vec.y;
    if (camera_state.eyeY < D_8007AA24) {
        camera_state.eyeY = D_8007AA24;
    }
}

void Camera_SetPresetDelayedTurn(s32 arg0) {
    Camera_SetPreset(arg0);
    camera_delayed_turn.state = 0;
    camera_delayed_turn.timer = 15;
    camera_delayed_turn.mode = camera_state.mode;
    camera_delayed_turn.flags = camera_state.flags;
    camera_delayed_turn.unk14 = 0.005f;
    camera_delayed_turn.unk18 = 0.9f;
    camera_state.mode = 5;
    camera_state.orbitAngle = camera_delayed_turn.orbitAngle;
}

void Camera_SetTargetView(CameraPreset* arg0, Actor* arg1) {
    camera_state.mode = arg0->mode;
    camera_state.flags = 0x40;
    camera_state.distance = arg0->distance;
    camera_state.eyeHeight = arg0->eyeHeight;
    camera_state.atHeight = arg0->atHeight;
    camera_state.yawMax = 0.0f;
    camera_state.pitchMax = 0.0f;
    camera_state.yawMin = camera_state.yawMax;
    camera_state.pitchMin = camera_state.pitchMax;
    camera_state.target = arg1;
    switch (arg0->mode) {
        case 0:
            camera_temp_vec.x = 0.0f;
            camera_temp_vec.y = arg0->distance + 20.0;
            Math_RotateVec2(arg1->rot - 3.141592653589793 + 0.39269908169872414, &camera_temp_vec);
            camera_state.eyeX = arg1->x - camera_temp_vec.x;
            camera_state.eyeZ = arg1->z - camera_temp_vec.y;
            camera_state.eyeY = arg1->y + arg0->eyeHeight;
            break;
        case 1:
            camera_state.eyeX = arg0->x;
            camera_state.eyeY = arg0->y;
            camera_state.eyeZ = arg0->z;
            break;
    }
    camera_state.eyeVelZ = 0.0f;
    camera_state.atVelY = 0.0f;
    camera_state.orbitSpeed = 0.0f;
    camera_state.eyeVelY = camera_state.eyeVelZ;
    camera_state.eyeVelX = camera_state.eyeVelY;
}

extern f32 D_8007AA30;
extern f32 D_80084314;
void Camera_TurnForExit(void) {
    f32 a;

    a = camera_state.unk28 - D_8007AA30;
    if (a < -3.141592653589793) {
        a += 6.283185307179586;
    } else if (a > 3.141592653589793) {
        a -= 6.283185307179586;
    }
    if (a > 0.7853981633974483) {
        a = 0.7853981633974483f;
    }
    if (a < -0.7853981633974483) {
        a = -0.7853981633974483f;
    }
    a += 3.141592653589793;
    if (a < -3.141592653589793) {
        a += 6.283185307179586;
    } else if (a > 3.141592653589793) {
        a -= 6.283185307179586;
    }
    camera_state.unk84 = a;
    camera_state.orbitAngle = D_80084314 + 3.141592653589793;
    if (camera_state.orbitAngle > 3.141592653589793) {
        camera_state.orbitAngle -= 6.283185307179586;
    } else if (camera_state.orbitAngle < -3.141592653589793) {
        camera_state.orbitAngle += 6.283185307179586;
    }
    camera_state.flags |= 0x10;
}

f32 Camera_RaiseOverNpcs(Camera* arg0, f32 arg1) {
    s32 n = npc_drawn_count;
    Unk8007ABB0** p;
    Unk8007ABB0* obj;
    f32 dx;
    f32 dz;

    if (npc_drawn_count != 0) {
        p = npc_drawn_list;
        while (n != 0) {
            obj = *p++;
            dx = obj->y - arg1;
            if (dx < 20.0) {
                dx = obj->x - arg0->eyeX;
                dz = obj->z - arg0->eyeZ;
                if (sqrtf(dx * dx + dz * dz) < 30.0) {
                    arg1 = obj->y + 30.0;
                    break;
                }
            }
            n--;
        }
    }
    return arg1;
}

void Camera_UpdateHeightOscillation(Vec3f* arg0) {
    f32* pa;
    f32* pb;
    f32 a;
    f32 b;
    f32 s;

    pa = &camera_height_osc_phase_a;
    pb = &camera_height_osc_phase_b;
    s = sinf(*pb + *pa);
    a = *pa;
    b = *pb;
    arg0->y = s;
    a += 0.0261799387799149415;
    if (a > 6.28318530717958623) {}
    b += 0.015707963267948967;
    *pa = a;
    if (a > 6.28318530717958623) {
        *pa = a - 6.28318530717958623;
    }
    *pb = b;
    if (b > 6.28318530717958623) {
        *pb = b - 6.28318530717958623;
    }
}
