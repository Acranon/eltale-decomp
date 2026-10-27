#include "common.h"

/*
 * Actor model animation: state changes, root motion, frame advance, and node drawing.
 * Folder: src/game/actor/
 */

typedef struct {
    f32 mf[4][4];
} MtxF;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ char unk18[0x24 - 0x18];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x38 - 0x28];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
} Struct_800201A0;

typedef struct {
    s16 unk0;
    s16 unk2;
    void* unk4;
    void* unk8;
} Struct_8002099C;

typedef struct {
    void* unk0;
    u16 unk4;
    u16 unk6;
    Vec3f unk8;
    s8 unk14;
    s8 unk15;
    u8 unk16;
    char unk17;
    s32* unk18;
    u16 unk1C;
    char unk1E[2];
} Struct_80020A28;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x32 - 0xC];
    /* 0x32 */ u16 unk32;
} Struct_80020214_kf;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x04 */ Struct_80020A28* unk4;
    /* 0x08 */ Gfx** unk8;
} Struct_80020214_set;

/* This file's .bss, 8008BFC0..8008C040, in address order. */
Vec3f D_8008BFC0[4];
s32 D_8008BFF0;
MtxF D_8008BFF8;

void Math_EvalTcbSpline(Struct_80020A28*, Vec3f*, s32);
void Math_MtxFRotScaleTrans(MtxF*, f32, f32, f32, f32, f32, f32, f32);
void Anim_DrawNode(MtxF*, Vec3f, s32, s32, s32, s32, Struct_80020214_set*, Struct_80020A28*, s32);

void Anim_SetCurrentAndNext(Struct_800201A0* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    if (arg1 != -1) {
        if (arg1 != arg0->unk52) {
            arg0->unk52 = arg1;
            arg0->unk60 = arg0->unk60 | 0x400;
            arg0->unk60 = arg0->unk60 & 0xFDFF;
        }

        arg0->unk58 = arg2;
        if (arg5 & 1) {
            arg0->unk54 = arg0->unk56 = 0;
        }
    }

    if (arg3 != -1) {
        if (arg3 != arg0->unk5A) {
            arg0->unk5A = arg3;
        }
        arg0->unk5C = arg4;
    }
}

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ Vec3f unk18;
} Struct_80020568_xf;

void Anim_UpdateRootMotion(Struct_800201A0* arg0, Struct_80020214_set* arg1, f32 scale) {
    s32 i;
    s16 count;
    u16 cur;
    s32 frame;
    Struct_80020214_kf* kf;
    f32 x;
    f32 y;
    Struct_80020568_xf pos;
    Struct_80020A28* anim;
    f32 z;

    count = arg1->unk0;
    cur = arg0->unk54;
    anim = arg1->unk4;
    i = 0;
    while (i < count && anim->unk14 != 0) {
        i++;
        anim++;
    }
    frame = anim->unk6;
    if (frame != 0) {
        frame = cur % frame;
    } else {
        frame = 0;
    }
    Math_EvalTcbSpline(anim, (Vec3f*)&pos, frame);
    if (arg0->unk60 & 0x200) {
        kf = anim->unk0;
        frame = anim->unk6;
        while (kf->unk32 != frame) {
            kf++;
        }
        x = kf->unk0;
        y = kf->unk4;
        z = kf->unk8;
        arg0->unk44 = (pos.unk0.x + x) * scale - arg0->unk38;
        arg0->unk48 = (pos.unk0.y + y) * scale - arg0->unk3C;
        arg0->unk4C = (pos.unk0.z + z) * scale - arg0->unk40;
        arg0->unk38 = pos.unk0.x * scale;
        arg0->unk3C = pos.unk0.y * scale;
        arg0->unk40 = pos.unk0.z * scale;
    } else if (arg0->unk60 & 0x400) {
        arg0->unk44 = 0.0f;
        arg0->unk48 = 0.0f;
        arg0->unk4C = 0.0f;
        arg0->unk38 = pos.unk0.x * scale;
        arg0->unk3C = pos.unk0.y * scale;
        arg0->unk40 = pos.unk0.z * scale;
    } else {
        arg0->unk44 = pos.unk0.x * scale - arg0->unk38;
        arg0->unk48 = pos.unk0.y * scale - arg0->unk3C;
        arg0->unk4C = pos.unk0.z * scale - arg0->unk40;
        arg0->unk38 = pos.unk0.x * scale;
        arg0->unk3C = pos.unk0.y * scale;
        arg0->unk40 = pos.unk0.z * scale;
    }
}

void Anim_DrawModel(s32 arg0, Struct_800201A0* arg1, Struct_80020214_set* arg2, s32 arg3) {
    s32 i;
    u16 frame;
    Struct_80020A28* anims;
    u16 total;
    MtxF mtx;
    Vec3f scale;

    D_8008BFF0 = 0;
    Math_MtxFRotScaleTrans(&mtx, arg1->unkC.x, arg1->unkC.y, arg1->unkC.z, arg1->unk24, arg1->unk0.x, arg1->unk0.y, arg1->unk0.z);
    scale.x = arg1->unk24;
    scale.y = arg1->unk24;
    scale.z = arg1->unk24;
    anims = arg2->unk4;
    frame = arg1->unk54;
    total = arg1->unk56;
    for (i = 0; i < arg2->unk0; i++) {
        if (anims[i].unk14 == 0) {
            Anim_DrawNode(&mtx, scale, arg0, i, frame, total, arg2, anims, arg3);
        }
    }
}

typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

typedef struct {
    /* 0x00 */ char unk0[0xC];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Struct_80085E48;

extern Gfx* D_8007A184;
extern s32 D_8007A180;
extern Unk2000000 D_2000000;
extern Struct_80085E48 D_80085E48;
void Math_MtxFRotDegScaleTrans(MtxF*, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Math_MtxFMul(MtxF*, MtxF*, MtxF*);
void Math_MtxFAimAt(MtxF*, f32, f32, f32, f32, f32, f32);
void Math_MtxFScaleAxes(MtxF*, f32, f32, f32);
void Anim_ApplyPivotOffset(MtxF* arg0, Struct_80020A28* arg1);

void Anim_DrawNode(MtxF* parent, Vec3f scale, s32 flags, s32 idx, s32 frame, s32 total, Struct_80020214_set* set,
                   Struct_80020A28* anims, s32 buf) {
    s32 fr;
    s32 i;
    Gfx** dls;
    s32* tbl;
    MtxF mtx;
    Struct_80020568_xf xf;
    Struct_80020A28* anim;

    anim = &anims[idx];
    fr = anim->unk6;
    if (fr != 0) {
        fr = frame % fr;
    } else {
        fr = 0;
    }
    Math_EvalTcbSpline(anim, (Vec3f*)&xf, fr);
    if (anim->unk14 == 0) {
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
    if (anim->unk16 & 1) {
        Math_MtxFMul(parent, &mtx, &mtx);
        Math_MtxFAimAt(&D_8008BFF8, mtx.mf[3][0], mtx.mf[3][1], mtx.mf[3][2], D_80085E48.unkC, D_80085E48.unk10,
                      D_80085E48.unk14);
        Math_MtxFScaleAxes(&D_8008BFF8, scale.x, scale.y, scale.z);
        guMtxF2L(D_8008BFF8.mf, &((Unk2000000*)buf)->unkC0[D_8007A180]);
    } else {
        Math_MtxFMul(parent, &mtx, &mtx);
        guMtxF2L(mtx.mf, &((Unk2000000*)buf)->unkC0[D_8007A180]);
    }
    gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180++], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    if (anim->unk16 & 2) {
        D_8008BFC0[D_8008BFF0].x = mtx.mf[3][0];
        D_8008BFC0[D_8008BFF0].y = mtx.mf[3][1];
        D_8008BFC0[D_8008BFF0].z = mtx.mf[3][2];
        D_8008BFF0++;
    }
    dls = set->unk8;
    tbl = anim->unk18;
    if (tbl == NULL) {
        i = anim->unk15;
        if (i != -1) {
            if (dls[i] != NULL) {
                gSPDisplayList(D_8007A184++, dls[i]);
            }
        }
    } else {
        gSPDisplayList(D_8007A184++, dls[tbl[total % anim->unk1C]]);
    }
    for (i = 0; i < set->unk0; i++) {
        if (anims[i].unk14 == idx + 1) {
            Anim_DrawNode(&mtx, scale, flags, i, frame, total, set, anims, buf);
        }
    }
}

void Anim_AdvanceFrame(s32 arg0, Struct_800201A0* arg1, Struct_8002099C* arg2) {
    s32 temp_v0 = arg1->unk54 += arg0;

    if (temp_v0 >= arg2->unk2) {
        if (arg1->unk52 != arg1->unk5A) {
            arg1->unk52 = arg1->unk5A;
            arg1->unk54 = 0U;
            arg1->unk56 = 0U;
            arg1->unk58 = arg1->unk5C;
            arg1->unk60 |= 0x400;
        } else {
            arg1->unk54 = temp_v0 - arg2->unk2;
            arg1->unk60 |= 0x200;
        }
    } else {
        arg1->unk60 &= ~0x600;
    }
    arg1->unk56++;
}

void Anim_ApplyPivotOffset(MtxF* arg0, Struct_80020A28* arg1) {
    f32 x, y, z;
    x = arg0->mf[0][0];
    y = arg0->mf[1][0];
    z = arg0->mf[2][0];
    arg0->mf[3][0] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
    x = arg0->mf[0][1];
    y = arg0->mf[1][1];
    z = arg0->mf[2][1];
    arg0->mf[3][1] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
    x = arg0->mf[0][2];
    y = arg0->mf[1][2];
    z = arg0->mf[2][2];
    arg0->mf[3][2] -= x * arg1->unk8.x + y * arg1->unk8.y + z * arg1->unk8.z;
}
