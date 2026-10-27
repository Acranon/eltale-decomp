#include "common.h"

/*
 * Camera: per-map presets, the mode handlers (follow, fixed eye, battle, delayed turn),
 * shake and sway, and the projection/view matrices for each frame.
 * Folder: src/game/camera/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f_15150;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f_15150;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} Unk15150Model;

typedef struct {
    /* 0x00 */ u8 pad0[0x94];
    /* 0x94 */ f32 unk94;
} Unk15150Model2;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x36];
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u8 pad60[4];
    /* 0x64 */ Unk15150Model* unk64;
    /* 0x68 */ Unk15150Model2* unk68;
} Unk15150Target;

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u16 flags;
    /* 0x0C */ f32 eyeX;
    /* 0x10 */ f32 eyeY;
    /* 0x14 */ f32 eyeZ;
    /* 0x18 */ f32 atX;
    /* 0x1C */ f32 atY;
    /* 0x20 */ f32 atZ;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ Unk15150Target* target;
    /* 0x84 */ f32 unk84;
} Camera15150; // size = 0x88

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 mode;
    /* 0x0C */ u16 flags;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} Unk80085F68;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk8007ABB0;

typedef struct 
{
  f32 x;
  f32 y;
  f32 z;
  u8 padC[0xC];
  u16 flags;
} Coll15150;

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
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
    /* 0x34 */ f32 unk34;
} Camera15150Preset; // size = 0x38

/* 15150 .bss, 80085B80..80085F90, in address order (first declaration fixes the order). */
Camera15150 D_80085B80;
s32 D_80085C08[2];
Vec2f_15150 D_80085C10;
u8 D_80085C18[8];
Coll15150 D_80085C20;
u16 D_80085C3C;
Unk15150Target D_80085C40;
s32 D_80085CAC;
f32 D_80085CB0;
f32 D_80085CB4;
s32 D_80085CB8[100];
Camera15150 D_80085E48;
f32 D_80085ED0[4][4];
f32 D_80085F10[4][4];
f32 D_80085F50;
f32 D_80085F54;
f32 D_80085F58;
f32 D_80085F5C;
s32 D_80085F60;
Camera15150Preset* D_80085F64;
Unk80085F68 D_80085F68;
f32 D_80085F84;
u16 D_80085F88;

extern s32 D_8007ABA8;
extern Unk8007ABB0* D_8007ABB0[];

typedef struct {
    /* 0x00 */ Camera15150Preset* presets;
    /* 0x04 */ u16 count;
} Unk15150PresetSet; // size = 0x8

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ Unk15150PresetSet* unk24;
} Unk8007C284;

extern Mtx D_80301098;
extern Mtx D_8030EB68;
extern s32 D_80084308;
extern u16 D_8007AA82;
extern Unk8007C284* D_8007C284;
extern s32 D_800842BC;
extern s32 D_800842C0;
extern Vec3f_15150 D_8007AA20;
extern f32 D_8007A994;
void guOrtho(Mtx*, f32, f32, f32, f32, f32, f32, f32);

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u16 unk14;
} Unk8007C288;

typedef struct {
    /* 0x0000 */ Mtx proj;
    /* 0x0040 */ Mtx unk40;
    /* 0x0080 */ Mtx view;
    /* 0x00C0 */ Mtx unkC0[0x226];
    /* 0x8A40 */ LookAt lookAt;
} Unk15150Dyn;

extern Unk8007C288* D_8007C288;
extern u16 D_8008BE52;
extern s32 D_8004DCA0;
extern s32 D_8008C168;
extern u16 D_80092C86;
extern s32 D_8007A180;
extern Gfx* D_8007A184;
extern Unk15150Dyn D_2000000;
void Camera_UpdateSway(Vec3f_15150*);

f32 func_800270D0(f32, f32);
void func_800271B4(f32, Vec2f_15150*);
f32 sinf(f32);
f32 cosf(f32);
f32 sqrtf(f32);
void Camera_FollowTarget(Camera15150*);
void Camera_SetPreset(s32);
void Camera_UpdateFixedEye(Camera15150*);
void Camera_UpdateHeading(Camera15150*);
void Camera_UpdateBattle(Camera15150*);
void Camera_UpdateDelayedTurn(Camera15150*);

Camera15150Preset D_8004EB70[3] = {
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 15.0f, 65.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 72.0f, 144.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
    { 0, 0.0f, 0.0f, 0.0f, 11.0f, 2e+01f, 55.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 15.0f, 2.5e+03f },
};
void (*D_8004EC18[6])(Camera15150*) = {
    Camera_FollowTarget, Camera_UpdateFixedEye, Camera_FollowTarget, Camera_UpdateHeading, Camera_UpdateBattle, Camera_UpdateDelayedTurn,
};
s32 D_8004EC30[7][2] = {
    { 25, 2 }, { 25, 3 }, { 25, 4 }, { 25, 5 }, { 25, 8 }, { 25, 9 }, { 12, 2 },
};
f32 D_8004EC68[8] = { 0.0f, -0.1f, 0.0f, -0.05f, 0.1f, -0.1f, -0.05f, 0.08f };
f32 D_8004EC88 = 0.0f;
f32 D_8004EC8C = 0.0f;

void Camera_InitForMap(void) {
    s32 pad[2];
    Camera15150* cam = &D_80085E48;
    Vec3f_15150* pos = &D_8007AA20;
    Camera15150Preset* p;
    s32 i;

    guOrtho(&D_80301098, -159.0f, 159.0f, 119.0f, -119.0f, 10.0f, 200.0f, 1.0f);
    guOrtho(&D_8030EB68, -159.0f, 159.0f, 119.0f, -119.0f, 10.0f, 200.0f, 1.0f);
    if (D_80084308 < 0) {
        cam->unk84 = 3.1415927f;
    }
    D_80085F60 = (D_8007AA82 >> 1) & 7;
    if (D_8007C284->unk24 != NULL) {
        D_80085F64 = D_8007C284->unk24[D_800842C0].presets;
        D_80085C08[0] = D_8007C284->unk24[D_800842C0].count;
    } else {
        D_80085F64 = D_8004EB70;
        D_80085C08[0] = 1;
    }
    p = &D_80085F64[D_80085F60];
    cam->mode = p->mode;
    cam->flags = 1;
    cam->unk4 = 0;
    cam->target = (Unk15150Target*)pos;
    cam->unk60 = p->unk1C;
    cam->unk64 = p->unk20;
    cam->unk68 = p->unk24;
    cam->unk6C = p->unk28;
    cam->unk4C = p->unk18;
    cam->unk50 = 0.0f;
    cam->unk58 = p->unk14;
    cam->unk5C = p->unk10;
    switch (cam->mode) {
        case 0:
        case 2:
            D_80085C10.x = 0.0f;
            D_80085C10.y = cam->unk4C * 0.8;
            cam->eyeY = pos->y + p->unk14;
            func_800271B4(cam->unk84 + D_8007A994, &D_80085C10);
            cam->eyeX = pos->x - D_80085C10.x;
            cam->eyeZ = pos->z - D_80085C10.y;
            cam->unk54 = 0.0f;
            break;
        case 1:
            cam->eyeX = p->unk4;
            cam->eyeY = p->unk8;
            cam->eyeZ = p->unkC;
            cam->unk54 = 0.0f;
            break;
    }
    cam->unk24 = 0.0f;
    cam->unk2C = 0.0f;
    cam->unk28 = 0.0f;
    cam->atX = pos->x;
    cam->atY = pos->y + cam->unk5C;
    cam->atZ = pos->z;
    cam->unk30 = 0.0f;
    cam->unk34 = 0.0f;
    cam->unk38 = 0.0f;
    cam->unk40 = cam->unk44 = cam->unk48 = 0.0f;
    cam->unk3C = 0.0f;
    if (cam) {}
    cam->unk70 = 0.02f;
    if (cam) {}
    cam->unk74 = 0.8f;
    cam->unk78 = 0.005f;
    cam->unk7C = 0.8f;
    D_80085CAC = 0;
    D_80085C3C = 0;
    D_80085F50 = p->unk2C;
    D_80085F54 = p->unk30;
    D_80085F58 = p->unk34;
    D_80085F84 = 0.0f;
    D_80085CB8[0] = 0;
    for (i = 0; i < 7; i++) {
        if (D_800842BC == D_8004EC30[i][0] && D_800842C0 == D_8004EC30[i][1]) {
            D_80085CB8[0]++;
            break;
        }
    }
}

void Camera_Update(Unk15150Dyn* arg0) {
    Camera15150* cam = &D_80085E48;
    f32 a;
    s32 idx;
    s32 pad;

    if ((D_8007C288->unk14 & 2) && !(D_8008BE52 & 1) && cam->mode != 3) {
        idx = (D_8007AA82 >> 1) & 7;
        if (idx != D_80085F60) {
            Camera_SetPreset(idx);
        }
    }
    D_8004EC18[cam->mode](cam);
    if (!(D_8004DCA0 & 0x82) && D_8008C168 == 0 && !(D_8008BE52 & 1) && !(D_8007C288->unk14 & 2) &&
        (D_80092C86 & 0x20) && D_80085C08[0] >= 2) {
        D_80085F60++;
        if (D_80085F60 >= D_80085C08[0]) {
            D_80085F60 = 0;
        }
        Camera_SetPreset(D_80085F60);
    }
    D_80085C10.y = 0.0f;
    if (D_80085CB8[0] != 0) {
        Camera_UpdateSway((Vec3f_15150*)&D_80085C10);
    }
    guPerspectiveF(D_80085ED0, &D_80085F88, D_80085F50, 1.3333334f, D_80085F54, D_80085F58, 1.0f);
    guLookAtReflectF(D_80085F10, &arg0->lookAt, cam->eyeX, cam->eyeY + D_80085C10.y, cam->eyeZ, cam->atX, cam->atY,
                     cam->atZ, 0.0f, 1.0f, 0.0f);
    guMtxF2L(D_80085ED0, &arg0->proj);
    guMtxF2L(D_80085F10, &arg0->view);
    if (D_80085CAC != 0) {
        guTranslate(&arg0->unkC0[D_8007A180], D_80085CB0, D_80085CB4, 0.0f);
        D_80085CB0 *= -0.8;
        D_80085CB4 *= -0.8;
        D_80085CAC--;
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        D_8007A180++;
        gSPMatrix(D_8007A184++, &D_2000000.proj, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    } else {
        gSPMatrix(D_8007A184++, &D_2000000.proj, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    }
    gSPMatrix(D_8007A184++, &D_2000000.view, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPLookAt(D_8007A184++, &D_2000000.lookAt);
    gSPPerspNormalize(D_8007A184++, D_80085F88);
    a = D_80085F50 * 0.017453292519943295 / 2;
    D_80085F5C = sinf(a) / cosf(a);
}

extern s32 D_8004DCA0;
extern u16 D_80092C84;
extern u16 D_8008BE52;
extern f32 D_8007AA24;
void func_80015B88(Camera15150 *arg0);
void Camera_UpdateLookAt(Camera15150 *arg0, Unk15150Target *arg1);
void Camera_OrbitTarget(Camera15150 *arg0, Unk15150Target *arg1);
f32 Camera_RaiseOverObjects(Camera15150 *arg0, f32 arg1);
void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, Coll15150 *);
void Camera_FollowTarget(Camera15150 *arg0)
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
  Unk15150Target *target;
  target = arg0->target;
  func_80015B88(arg0);
  if (((!(D_8004DCA0 & 0x82)) && (!(D_8008BE52 & 0x200))) && (!(arg0->flags & 0x40)))
  {
    if ((D_80092C84 & 0x4000) || (arg0->mode == 2))
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
    if (arg0->unk4C < dist)
    {
      a = arg0->unk4C / dist;
      vx = (dx - (dx * a)) * arg0->unk70;
      vz = (dz - (dz * a)) * arg0->unk70;
    }
    else
      if (dist <= arg0->unk4C)
    {
      a = arg0->unk4C / dist;
      vx = ((dx - (dx * a)) * arg0->unk70) * 0.5;
      vz = ((dz - (dz * a)) * arg0->unk70) * 0.5;
    }
  }
  else
  {
    vz = 0.0f;
    vx = 0.0f;
  }
  arg0->unk40 += vx;
  arg0->unk48 += vz;
  arg0->eyeX += arg0->unk40;
  arg0->eyeZ += arg0->unk48;
  arg0->unk40 *= arg0->unk74;
  arg0->unk48 *= arg0->unk74;
  locked = 0;
  if ((dist < 25.0f) && (!(D_8004DCA0 & 0x80)))
  {
    a = target->ry - arg0->unk28;
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
      arg0->unk54 = ((a < 0.0f) ? (1.5707963267948966) : (-1.5707963267948966)) + target->ry;
    }
    arg0->flags |= 4;
    locked = 1;
  }
  else
    if (arg0->flags & 0x20)
  {
    arg0->unk54 = target->ry + 3.141592653589793;
    if (arg0->unk54 > 3.141592653589793)
    {
      arg0->unk54 -= 6.283185307179586;
    }
    else
      if (arg0->unk54 < (-3.141592653589793))
    {
      arg0->unk54 += 6.283185307179586;
    }
  }
  Camera_OrbitTarget(arg0, target);
  D_80085C20.x = 4.0f;
  Coll_ResolveFloorAndWalls(arg0->eyeX, arg0->eyeY, arg0->eyeZ, 0x602, &D_80085C20);
  arg0->eyeX = D_80085C20.x;
  arg0->eyeZ = D_80085C20.z;
  if (D_80085C20.flags & 0x8000)
  {
    y = target->y;
  }
  else
  {
    y = D_80085C20.y;
  }
  D_80085C3C = D_80085C20.flags;
  dz = target->y + arg0->unk58;
  if (y < dz)
  {
    y = dz;
  }
  y = Camera_RaiseOverObjects(arg0, y);
  if ((D_8008BE52 & 1) && (y < D_8007AA24))
  {
    y = D_8007AA24;
  }
  ny = y - arg0->eyeY;
  ny *= arg0->unk70 * ((ny < 0.0f) ? (0.2) : (0.8));
  arg0->unk44 += ny;
  arg0->eyeY += arg0->unk44;
  arg0->unk44 *= arg0->unk74;
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
    arg0->unk24 = func_800270D0(y, dist);
  }
  if ((dx != 0.0f) || (dz != 0.0f))
  {
    arg0->unk2C = func_800270D0(dx, dz);
    if (!locked)
    {
      arg0->unk28 = arg0->unk2C;
    }
  }
}



void func_80015B88(Camera15150* arg0);
void Camera_UpdateLookAt(Camera15150* arg0, Unk15150Target* arg1);
void Camera_UpdateFixedEye(Camera15150* arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    Unk15150Target* target;

    target = arg0->target;
    func_80015B88(arg0);
    Camera_UpdateLookAt(arg0, target);
    dx = arg0->eyeX - arg0->atX;
    dy = arg0->eyeY - arg0->atY;
    dz = arg0->eyeZ - arg0->atZ;
    dist = sqrtf(dx * dx + dz * dz);
    if (dy != 0.0f || dist != 0.0f) {
        arg0->unk24 = func_800270D0(dy, dist);
    }
    if (dx != 0.0f || dz != 0.0f) {
        arg0->unk28 = func_800270D0(dx, dz);
    }
    if (arg0->unk60 != 0.0f || arg0->unk64 != 0.0f) {
        if (arg0->unk24 < arg0->unk60) {
            arg0->unk24 = arg0->unk60;
            dx = dist / cosf(arg0->unk60);
            arg0->atY = arg0->eyeY - sinf(arg0->unk60) * dx;
        } else if (arg0->unk64 < arg0->unk24) {
            arg0->unk24 = arg0->unk64;
            dx = dist / cosf(arg0->unk64);
            arg0->atY = arg0->eyeY - sinf(arg0->unk64) * dx;
        }
    }
    if (arg0->unk68 < arg0->unk6C) {
        if (arg0->unk28 < arg0->unk68) {
            arg0->unk28 = arg0->unk68;
            D_80085C10.x = 0.0f;
            D_80085C10.y = -dist;
            func_800271B4(arg0->unk28, &D_80085C10);
            arg0->atX = arg0->eyeX + D_80085C10.x;
            arg0->atZ = arg0->eyeZ + D_80085C10.y;
        } else if (arg0->unk6C < arg0->unk28) {
            arg0->unk28 = arg0->unk6C;
            D_80085C10.x = 0.0f;
            D_80085C10.y = -dist;
            func_800271B4(arg0->unk28, &D_80085C10);
            arg0->atX = arg0->eyeX + D_80085C10.x;
            arg0->atZ = arg0->eyeZ + D_80085C10.y;
        }
    } else if (arg0->unk6C < arg0->unk68) {
        if (arg0->unk28 < 0.0) {
            if (arg0->unk6C < arg0->unk28) {
                arg0->unk28 = arg0->unk6C;
                D_80085C10.x = 0.0f;
                D_80085C10.y = -dist;
                func_800271B4(arg0->unk28, &D_80085C10);
                arg0->atX = arg0->eyeX + D_80085C10.x;
                arg0->atZ = arg0->eyeZ + D_80085C10.y;
            }
        } else if (arg0->unk28 < arg0->unk68) {
            arg0->unk28 = arg0->unk68;
            D_80085C10.x = 0.0f;
            D_80085C10.y = -dist;
            func_800271B4(arg0->unk28, &D_80085C10);
            arg0->atX = arg0->eyeX + D_80085C10.x;
            arg0->atZ = arg0->eyeZ + D_80085C10.y;
        }
    }
    arg0->unk2C = arg0->unk28;
}

void Camera_UpdateHeading(Camera15150* arg0) {
    f32 dx = arg0->eyeX - arg0->atX;
    f32 dz = arg0->eyeZ - arg0->atZ;

    if (dx != 0.0f || dz != 0.0f) {
        arg0->unk28 = arg0->unk2C = func_800270D0(dx, dz);
    }
}

extern f32 D_8008BE5C;
extern f32 D_8008BE60;
extern u16 D_80092C86;
void Camera_UpdateBattle(Camera15150* arg0) {
    f32 a;

    if (arg0->flags & 0x40) {
        if (--arg0->unk4 == 0) {
            arg0->flags &= ~0x40;
            *arg0 = D_80085B80;
        }
    } else {
        a = func_800270D0(D_8008BE5C - arg0->target->x, D_8008BE60 - arg0->target->z) + 3.141592653589793;
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
        a += D_80085F84;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        arg0->unk54 = a;
        if (D_80092C86 & 0x20) {
            D_80085F84 += 0.7853981633974483;
            if (D_80085F84 > 3.141592653589793) {
                D_80085F84 -= 6.283185307179586;
            } else if (D_80085F84 < -3.141592653589793) {
                D_80085F84 += 6.283185307179586;
            }
        }
    }
    Camera_FollowTarget(arg0);
}

void Camera_UpdateDelayedTurn(Camera15150* arg0) {
    switch (D_80085F68.state) {
        case 0:
            if (--D_80085F68.timer == 0) {
                D_80085F68.state++;
                D_80085F68.timer = 75;
                arg0->flags |= 0x10;
            }
            break;
        case 1:
            if (--D_80085F68.timer == 0) {
                arg0->mode = D_80085F68.mode;
                arg0->flags = D_80085F68.flags;
                D_80085E48.unk78 = D_80085F68.unk14;
                D_80085E48.unk7C = D_80085F68.unk18;
            }
            break;
    }
    Camera_FollowTarget(arg0);
}

void func_80015B88(Camera15150* arg0) {
}

void Camera_UpdateLookAt(Camera15150* arg0, Unk15150Target* arg1) {
    f32 y;

    arg0->atX = arg1->x;
    arg0->atZ = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        y = arg1->unk68->unk94;
    } else {
        y = arg1->y;
    }
    y += arg0->unk5C - arg0->atY;
    arg0->unk34 += y * arg0->unk70 * 2;
    arg0->atY += arg0->unk34;
    arg0->unk34 = arg0->unk34 * (arg0->unk74 * 0.8);
}

void Camera_OrbitTarget(Camera15150* arg0, Unk15150Target* arg1) {
    f32 dx;
    f32 dz;
    f32 angle;
    f32 speed;

    dx = arg0->eyeX - arg1->x;
    dz = arg0->eyeZ - arg1->z;
    if (arg0->flags & 0x14) {
        angle = func_800270D0(dx, dz) - arg0->unk54;
        if (angle > 3.141592653589793) {
            angle -= 6.283185307179586;
        } else if (angle < -3.141592653589793) {
            angle += 6.283185307179586;
        }
        speed = arg0->unk78 * angle + arg0->unk3C;
    } else {
        speed = arg0->unk3C;
    }
    arg0->unk3C = arg0->unk7C * speed;
    D_80085C10.x = dx;
    D_80085C10.y = dz;
    func_800271B4(speed, &D_80085C10);
    arg0->eyeX = arg1->x - D_80085C10.x;
    arg0->eyeZ = arg1->z + D_80085C10.y;
}

void Camera_Shake(s32 arg0) {
    D_80085CAC = 15;
    D_80085CB0 = D_8004EC68[arg0 * 2];
    D_80085CB4 = D_8004EC68[arg0 * 2 + 1];
}

void Camera_SetPreset(s32 arg0) {
    Camera15150* cam = &D_80085E48;

    D_80085F60 = arg0;
    if (cam->flags & 0x40) {
        cam->target = D_80085B80.target;
    }
    cam->mode = D_80085F64[arg0].mode;
    if (cam->mode != 0 && cam->mode != 2) {
        cam->eyeX = D_80085F64[arg0].unk4;
        cam->eyeY = D_80085F64[arg0].unk8;
        cam->eyeZ = D_80085F64[arg0].unkC;
    }
    cam->flags &= 0xFFAF;
    cam->unk4C = D_80085F64[arg0].unk18;
    cam->unk58 = D_80085F64[arg0].unk14;
    cam->unk5C = D_80085F64[arg0].unk10;
    cam->unk68 = D_80085F64[arg0].unk24;
    cam->unk6C = D_80085F64[arg0].unk28;
    cam->unk60 = D_80085F64[arg0].unk1C;
    cam->unk64 = D_80085F64[arg0].unk20;
    D_80085F50 = D_80085F64[arg0].unk2C;
    D_80085F54 = D_80085F64[arg0].unk30;
    D_80085F58 = D_80085F64[arg0].unk34;
    cam->unk40 = cam->unk44 = cam->unk48 = 0.0f;
    cam->unk3C = 0.0f;
}

extern f32 D_8007AA24;
extern u16 D_8008BE52;
void Camera_StartBattleFocus(s32 arg0, Unk15150Target* arg1) {
    f32 h;

    if (!(D_8008BE52 & 1)) {
        return;
    }
    if (!(D_80085E48.flags & 0x40)) {
        D_80085B80 = D_80085E48;
    }
    D_80085C40.x = arg1->x;
    D_80085C40.z = arg1->z;
    if (arg1->unk5E & 4) {
        D_80085C40.y = D_8007AA24;
    } else if (arg1->unk64->unk0 == 1) {
        D_80085C40.y = arg1->unk68->unk94;
    } else {
        D_80085C40.y = arg1->y;
    }
    D_80085C40.scale = arg1->scale;
    D_80085C40.unk64 = arg1->unk64;
    D_80085C40.unk68 = arg1->unk68;
    if (arg1->unk5E & 4) {
        h = arg1->unk64->unk1C * arg1->scale + 40.0;
    } else if (arg1->unk64->unk1C < arg1->unk64->unk18) {
        h = arg1->unk64->unk18 * arg1->scale * 2.0 + 40.0;
    } else {
        h = arg1->unk64->unk1C * arg1->scale * 2.0 + 40.0;
    }
    D_80085E48.mode = 4;
    D_80085E48.flags |= 0x40;
    D_80085E48.target = &D_80085C40;
    D_80085E48.unk58 = (arg1->unk5E & 4) ? 20.0 : 15.0;
    D_80085E48.unk48 = 0.0f;
    D_80085E48.unk4C = h;
    D_80085E48.unk4 = arg0;
    D_80085E48.unk44 = D_80085E48.unk48;
    D_80085E48.unk3C = 0.0f;
    D_80085C10.x = 0.0f;
    D_80085E48.unk40 = D_80085E48.unk44;
    D_80085C10.y = h + 10.0;
    func_800271B4(D_80085E48.unk54, &D_80085C10);
    D_80085E48.eyeX = arg1->x + D_80085C10.x;
    D_80085E48.eyeY = D_80085C40.y + D_80085E48.unk58 * 1.1;
    D_80085E48.eyeZ = arg1->z + D_80085C10.y;
    if (D_80085E48.eyeY < D_8007AA24) {
        D_80085E48.eyeY = D_8007AA24;
    }
}

void Camera_SetPresetDelayedTurn(s32 arg0) {
    Camera_SetPreset(arg0);
    D_80085F68.state = 0;
    D_80085F68.timer = 15;
    D_80085F68.mode = D_80085E48.mode;
    D_80085F68.flags = D_80085E48.flags;
    D_80085F68.unk14 = 0.005f;
    D_80085F68.unk18 = 0.9f;
    D_80085E48.mode = 5;
    D_80085E48.unk54 = D_80085F68.unk10;
}

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} Unk8001628C;
void Camera_SetTargetView(Unk8001628C* arg0, Unk15150Target* arg1) {
    D_80085E48.mode = arg0->mode;
    D_80085E48.flags = 0x40;
    D_80085E48.unk4C = arg0->unk18;
    D_80085E48.unk58 = arg0->unk14;
    D_80085E48.unk5C = arg0->unk10;
    D_80085E48.unk6C = 0.0f;
    D_80085E48.unk64 = 0.0f;
    D_80085E48.unk68 = D_80085E48.unk6C;
    D_80085E48.unk60 = D_80085E48.unk64;
    D_80085E48.target = arg1;
    switch (arg0->mode) {
        case 0:
            D_80085C10.x = 0.0f;
            D_80085C10.y = arg0->unk18 + 20.0;
            func_800271B4(arg1->ry - 3.141592653589793 + 0.39269908169872414, &D_80085C10);
            D_80085E48.eyeX = arg1->x - D_80085C10.x;
            D_80085E48.eyeZ = arg1->z - D_80085C10.y;
            D_80085E48.eyeY = arg1->y + arg0->unk14;
            break;
        case 1:
            D_80085E48.eyeX = arg0->x;
            D_80085E48.eyeY = arg0->y;
            D_80085E48.eyeZ = arg0->z;
            break;
    }
    D_80085E48.unk48 = 0.0f;
    D_80085E48.unk34 = 0.0f;
    D_80085E48.unk3C = 0.0f;
    D_80085E48.unk44 = D_80085E48.unk48;
    D_80085E48.unk40 = D_80085E48.unk44;
}

extern f32 D_8007AA30;
extern f32 D_80084314;
void Camera_TurnForExit(void) {
    f32 a;

    a = D_80085E48.unk28 - D_8007AA30;
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
    D_80085E48.unk84 = a;
    D_80085E48.unk54 = D_80084314 + 3.141592653589793;
    if (D_80085E48.unk54 > 3.141592653589793) {
        D_80085E48.unk54 -= 6.283185307179586;
    } else if (D_80085E48.unk54 < -3.141592653589793) {
        D_80085E48.unk54 += 6.283185307179586;
    }
    D_80085E48.flags |= 0x10;
}

f32 Camera_RaiseOverObjects(Camera15150* arg0, f32 arg1) {
    s32 n = D_8007ABA8;
    Unk8007ABB0** p;
    Unk8007ABB0* obj;
    f32 dx;
    f32 dz;

    if (D_8007ABA8 != 0) {
        p = D_8007ABB0;
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

void Camera_UpdateSway(Vec3f_15150* arg0) {
    f32* pa;
    f32* pb;
    f32 a;
    f32 b;
    f32 s;

    pa = &D_8004EC88;
    pb = &D_8004EC8C;
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
