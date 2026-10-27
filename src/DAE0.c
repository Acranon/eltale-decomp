#include "common.h"

/*
 * Bosses (8, one per map/sub-area in D_803AB3D0): defeated bits, the boss standing on
 * the field map (load, draw, proximity trigger, encounter start), its battle record
 * init, and the defeat handling (stat reward, or boss 7's exit to the ending).
 * Folder: src/game/enemy/   (proposed for round 4)
 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[0x10];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 pad38[0x18];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u8 pad54[4];
    /* 0x58 */ u16 unk58;
    /* 0x5A */ u8 pad5A[4];
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ s16 unk60;
    /* 0x62 */ u8 pad62[2];
    /* 0x64 */ u16 *unk64;
    /* 0x68 */ void *unk68;
} Unk8007C174; /* size 0x6C */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[2];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[6];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad2C[0xC];
} Unk803AB820; /* size 0x38 */

typedef struct {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[6];
    /* 0x008 */ u16 unk8;
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 pad14[0x14];
    /* 0x028 */ Unk803AB820 *unk28;
    /* 0x02C */ Unk8007C174 unk2C;
    /* 0x098 */ s16 unk98;
    /* 0x09A */ u8 pad9A[0x82];
    /* 0x11C */ u16 unk11C;
    /* 0x11E */ u16 unk11E;
    /* 0x120 */ u16 unk120;
    /* 0x122 */ u8 pad122[6];
    /* 0x128 */ f32 unk128;
} Unk8007C148;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk803AB3D0; /* size 0x18 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
} RomRange;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk8007C0B0;

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
} Unk8007A9D0;

f32 sqrtf(f32);
void Dma_ReadRom();
void Boss_Spawn(s32, f32, f32, f32, Unk8007C148 *);
u8 Boss_IsDefeated(u32);
void Anim_DrawModel(s32, Unk8007C174 *, void *, s32);
void Anim_AdvanceFrame(s32, Unk8007C174 *, void *);
void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
void Anim_SetCurrentAndNext(Unk8007C174 *, s32, s32, s32, s32, u16);
void Coll_ResolveFloorAndWalls(f32, f32, f32, u16, Unk8007C0B0 *);

/* This file's .bss, 8007C0B0..8007C280, in address order. D_8007C0C8,
 * D_8007C144, D_8007C274 and D_8007C278 are unreferenced gaps (D_8007C148 is
 * probably an Enemy-like record of 0x130 bytes, like AEA0's D_8007B908[]).
 * Splat's labels inside D_8007C148 (D_8007C174..D_8007C1D8, its unk2C object)
 * are aliases in undefined_syms.txt. */
Unk8007C0B0 D_8007C0B0;
s32 D_8007C0C8[2];
Unk8007C174 D_8007C0D0;
u8 D_8007C13C[4];
s32 D_8007C140;
s32 D_8007C144;
Unk8007C148 D_8007C148;
s32 D_8007C274;
s32 D_8007C278[2];

extern u8 math_bit_masks[];
extern Gfx *gfx_dl_head;
extern Unk8007AA08 D_8007AA08;
extern u8 D_802A7BC0[];
extern RomRange D_803AB390[];
extern Unk803AB3D0 D_803AB3D0[];
extern f32 D_803AB48C[];
extern Unk803AB820 D_803AB820[];
extern Unk803AB820 D_803AB9A8;
extern u8 *D_803ABA58[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern u8 D_8007B8E0[];
extern u8 D_8007B430[];
extern u8 *D_803AC418[];
extern u8 *D_803AC438[];
extern u8 D_803AC328[];
extern Unk803AB820 D_803AB4B0[];
extern s32 core_flags;
extern s16 D_8007A172;
extern s32 core_transition_timer;
extern s16 fade_transition_style;
extern s16 core_fade_out_time;
u16 D_8004DD50[8] = { 10, 10, 15, 20, 20, 25, 25, 0 };
u16 D_8004DD60[8] = { 5, 5, 5, 10, 10, 15, 15, 0 };
extern Unk8007A9D0 D_8007A9D0;
void Camera_SetTargetView(Unk803AB820 *, Unk8007C174 *);
void Text_OpenWindow(s32);

void Boss_ClearDefeated(void) {
    D_8007C13C[0] = 0;
}

void Boss_LoadForArea(void) {
    s32 start;
    s32 end;
    s32 i;
    s32 size;
    Unk803AB3D0 *p;

    D_8007C140 = 0;
    for (i = 0; i < 8; i++) {
        p = &D_803AB3D0[i];
        if (D_800842BC == p->unk0 && D_800842C0 == p->unk2) {
            if (Boss_IsDefeated(i) == 0) {
                start = D_803AB390[p->unk4].start;
                end = D_803AB390[p->unk4].end;
                size = end - start;
                Dma_ReadRom(start, D_802A7BC0, size);
                Boss_Spawn(i, p->unkC, p->unk10, p->unk14, &D_8007C148);
                D_8007C140 = i + 1;
            }
            return;
        }
    }
}

void Boss_Draw(s32 arg0) {
    Unk8007C148 *p = &D_8007C148;
    s32 pad;
    u8 *temp;

    if (D_8007C140 != 0) {
        temp = D_803ABA58[D_8007C148.unk2C.unk50];
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
        Anim_DrawModel(1, &p->unk2C, temp + D_8007C148.unk2C.unk52 * 0xC, arg0);
        Anim_AdvanceFrame(p->unk2C.unk58, &p->unk2C, temp + p->unk2C.unk52 * 0xC);
        if (*p->unk2C.unk64 != 2) {
            Shadow_Queue(p->unk2C.x, p->unk2C.y, p->unk2C.z, p->unk2C.unk2C, p->unk2C.unk30, p->unk2C.unk34,
                          p->unk2C.unk28 * p->unk2C.unk24);
        }
    }
}

s32 Boss_CheckPlayerNear(void) {
    s32 ret = 0;
    f32 dx;
    f32 dz;

    if (D_8007C140 != 0) {
        dx = D_8007C148.unk2C.x - D_8007AA08.x;
        dz = D_8007C148.unk2C.z - D_8007AA08.z;
        if (sqrtf(dx * dx + dz * dz) < D_803AB48C[D_8007C140]) {
            ret = D_8007C140;
        }
    }
    return ret;
}

void Boss_Spawn(s32 arg0, f32 arg1, f32 arg2, f32 arg3, Unk8007C148 *arg4) {
    Unk803AB820 *s2 = &D_803AB820[arg0];
    Unk8007C174 *s1 = &arg4->unk2C;
    s16 flags;

    arg4->unk2C.unk50 = s2->unk2;
    Anim_SetCurrentAndNext(s1, 0, 1, 0, 1, 1);
    s1->unk24 = s2->unk20;
    s1->unk28 = s2->unk18;
    s1->unk64 = (u16 *)s2;
    s1->unk68 = &arg4->unk98;
    arg4->unk28 = s2;
    arg4->unkA = s2->unk6;
    arg4->unkC = s2->unk6;
    arg4->unk0 = 0;
    arg4->unk8 = 0;
    arg4->unk10 = sqrtf((u32)s2->unkC) * 3.846 + 17.838;
    arg4->unk98 = 0;
    arg4->unk11C = arg4->unk28->unk2A;
    arg4->unk11E = ((Unk803AB820 *)s1->unk64)->unkC;
    arg4->unk120 = ((Unk803AB820 *)s1->unk64)->unkE;
    arg4->unk128 = 1.0f;
    Coll_ResolveFloorAndWalls(arg1, 0.0f, arg2, 0xA00, &D_8007C0B0);
    s1->x = D_8007C0B0.x;
    s1->y = D_8007C0B0.y;
    s1->z = D_8007C0B0.z;
    if (arg0 == 7) {
        arg4->unk8 |= 4;
        s1->y -= 30.0;
    }
    s1->unk10 = arg3;
    s1->unk2C = D_8007C0B0.unkC;
    s1->unk30 = D_8007C0B0.unk10;
    s1->unk34 = D_8007C0B0.unk14;
    s1->unk5E = 1;
    s1->unk60 = 0;
    if (s2 == &D_803AB9A8) {
        s1->unk5E |= 4;
    }
}

u8 Boss_IsDefeated(u32 arg0) {
    return D_8007C13C[arg0 >> 3] & math_bit_masks[arg0 & 7];
}

void Boss_SetDefeated(u16 arg0) {
    D_8007C13C[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}

void Boss_BeginEncounter(s32 arg0) {
    u8 *src;
    u8 *dst;
    s32 i;

    src = D_803AC418[arg0];
    dst = D_8007B8E0;
    for (i = 0x20; i != 0; i--) {
        *dst++ = *src++;
    }
    src = D_803AC438[arg0];
    dst = D_8007B430;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *src++;
    }
    D_8007C0D0 = D_8007C148.unk2C;
    if (arg0 == 7) {
        D_8007C0D0.x = -31.0f;
        D_8007C0D0.y = 139.0f;
        D_8007C0D0.z = -328.0f;
    }
    Camera_SetTargetView(&D_803AB4B0[arg0], &D_8007C0D0);
}

void Boss_HandleDefeat(s32 arg0) {
    u8 *src;
    u8 *dst;
    s32 i;

    if (arg0 == 7) {
        src = D_803AC418[arg0];
        dst = D_8007B8E0;
        for (i = 0x20; i != 0; i--) {
            *dst++ = *src++;
        }
        src = D_803AC328;
        dst = D_8007B430;
        for (i = 0x4B0; i != 0; i--) {
            *dst++ = *src++;
        }
        Text_OpenWindow(1);
        D_8007AA08.unk8 |= 0x10;
        core_flags |= 0x80;
        core_transition_timer = 0x40;
        fade_transition_style = 3;
        core_fade_out_time = 0x3E;
        D_8007A172 = 4;
    } else {
        D_8007A9D0.unk6 += D_8004DD50[arg0];
        if (D_8007A9D0.unk6 > 500) {
            D_8007A9D0.unk6 = 500;
        }
        D_8007A9D0.unk4 = D_8007A9D0.unk6;
        D_8007A9D0.unkA += D_8004DD60[arg0];
        if (D_8007A9D0.unkA > 500) {
            D_8007A9D0.unkA = 500;
        }
        D_8007A9D0.unk8 = D_8007A9D0.unkA;
    }
}
