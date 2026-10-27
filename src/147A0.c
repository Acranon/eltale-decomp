#include "common.h"

/*
 * Spirits: per-map placement, collected flags, the pick-up test and the sparkle particles.
 * Folder: src/game/map/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
} Unk800859B8; // size = 0x18

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ u8 unk8;
} Unk147A0Def; // size = 0xC

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 count;
    /* 0x08 */ Unk147A0Def* defs;
} Unk8004DFC0; // size = 0xC

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u16 unk18;
} Unk80085A78; // size = 0x1C (Coll_ResolveFloorAndWalls's result)

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f_147A0;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk80013D08Arg;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f_147A0;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
} Unk80013FA4Arg;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void* unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ void* unk10;
    /* 0x14 */ void* unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 pad3D[3];
} Unk8004E658; // size = 0x40

typedef struct {
    u8 r, g, b, a;
} Color_147A0;

/* This file's .bss, 800859B0..80085AB0, in address order (first declaration fixes
 * the order). Splat's D_80085AA8 is Spirit_ClearCollectedFlags's loop end, &D_80085A98[0x10]. */
s32 D_800859B0;
Unk800859B8 D_800859B8[8];
Unk80085A78 D_80085A78;
u8 D_80085A98[0x10];

extern u8 D_8004F770[];
extern s32 D_800842BC;
extern s32 D_800842C0;

extern Gfx* D_8007A184;

void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, Unk80085A78*);
u8 Spirit_IsCollected(u16);
void func_800271B4(f32, Vec2f_147A0*);
void Effect_AllocateSprite(void*);
s32 func_80026E90(s32);
f32 sinf(f32);
void Spirit_MoveSparkle(Unk80013FA4Arg*);

Unk8004DFC0 D_8004DFC0[0x2B] = {
    { 0x0, 0x0, 1, (Unk147A0Def*)0x80154860 },
    { 0x0, 0x1, 1, (Unk147A0Def*)0x80154870 },
    { 0x1, 0x0, 1, (Unk147A0Def*)0x80141CB0 },
    { 0x2, 0x0, 2, (Unk147A0Def*)0x80146140 },
    { 0x3, 0x0, 3, (Unk147A0Def*)0x8013E480 },
    { 0x4, 0x2, 3, (Unk147A0Def*)0x8014C1F0 },
    { 0x5, 0x0, 3, (Unk147A0Def*)0x8015AD50 },
    { 0x6, 0x0, 3, (Unk147A0Def*)0x801348C0 },
    { 0x7, 0x0, 4, (Unk147A0Def*)0x801419F0 },
    { 0x8, 0x0, 4, (Unk147A0Def*)0x8015DB70 },
    { 0x8, 0x1, 1, (Unk147A0Def*)0x8015DBA0 },
    { 0x9, 0x0, 6, (Unk147A0Def*)0x8015F1F0 },
    { 0xA, 0x0, 2, (Unk147A0Def*)0x80135DD0 },
    { 0xA, 0x1, 2, (Unk147A0Def*)0x80135DF0 },
    { 0xB, 0x1, 1, (Unk147A0Def*)0x8016DA10 },
    { 0xB, 0x2, 4, (Unk147A0Def*)0x8016DA20 },
    { 0xC, 0x0, 4, (Unk147A0Def*)0x80127990 },
    { 0x1A, 0x0, 6, (Unk147A0Def*)0x8016DAE0 },
    { 0x1A, 0x2, 1, (Unk147A0Def*)0x8016DB30 },
    { 0x1B, 0x0, 2, (Unk147A0Def*)0x8016EFF0 },
    { 0x1C, 0x0, 5, (Unk147A0Def*)0x8016A0D0 },
    { 0x1D, 0x0, 2, (Unk147A0Def*)0x80133AF0 },
    { 0x1E, 0x8, 1, (Unk147A0Def*)0x80152BD0 },
    { 0x1E, 0xF, 1, (Unk147A0Def*)0x80152BE0 },
    { 0x1F, 0x0, 4, (Unk147A0Def*)0x8014C410 },
    { 0x1F, 0x2, 1, (Unk147A0Def*)0x8014C440 },
    { 0x20, 0x0, 6, (Unk147A0Def*)0x8013D9C0 },
    { 0x21, 0x0, 3, (Unk147A0Def*)0x80143680 },
    { 0x21, 0x1, 1, (Unk147A0Def*)0x801436B0 },
    { 0xE, 0xF, 1, (Unk147A0Def*)0x801A3BD0 },
    { 0xE, 0xC, 1, (Unk147A0Def*)0x801A3BE0 },
    { 0x10, 0x15, 1, (Unk147A0Def*)0x80183190 },
    { 0x15, 0x0, 2, (Unk147A0Def*)0x801A6C80 },
    { 0x15, 0x6, 1, (Unk147A0Def*)0x801A6CA0 },
    { 0x16, 0x1, 1, (Unk147A0Def*)0x801832D0 },
    { 0x16, 0x17, 2, (Unk147A0Def*)0x801832E0 },
    { 0x17, 0x13, 1, (Unk147A0Def*)0x8018CC80 },
    { 0x17, 0x17, 1, (Unk147A0Def*)0x8018CC90 },
    { 0x18, 0x0, 4, (Unk147A0Def*)0x80166620 },
    { 0x18, 0x2, 2, (Unk147A0Def*)0x80166650 },
    { 0x19, 0x1, 1, (Unk147A0Def*)0x801717F0 },
    { 0x19, 0x4, 1, (Unk147A0Def*)0x80171800 },
    { 0x19, 0x9, 1, (Unk147A0Def*)0x80171810 },
};
Vtx D_8004E1C8[4] = {
    { 1, 1, 1, 0, 0x3C0, 0, 0, 0, 0, 0 },
    { -1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, -1, 1, 0, 0x3C0, 0x3C0, 0, 0, 0, 0 },
    { -1, -1, 1, 0, 0, 0x3C0, 0, 0, 0, 0 },
};
Gfx D_8004E208[10] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00100000 }},
    {{ 0xB900031D, 0x0C184A50 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000005 }},
    {{ 0xFC629BFF, 0x1FFCFE38 }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0x0400103F, (u32)D_8004E1C8 }},
    {{ 0xB1000204, 0x00020604 }},
    {{ 0xB8000000, 0x00000000 }},
};
u8 D_8004E258[4][0x100] = {
#include "assets/D_8004E258.inc.c"
};

void Spirit_ClearCollectedFlags(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_80085A98[i] = 0;
    }
}

void Spirit_LoadForMap(void) {
    Unk8004DFC0* entry;
    Unk147A0Def* def;
    Unk800859B8* obj;
    u32 i;
    s32 id;

    id = D_800842BC; entry = D_8004DFC0; for (i = 0; i < 0x2B; i++, entry++) {
        if (id == entry->unk0 && D_800842C0 == entry->unk2) {
            break;
        }
    }
    if (i < 0x2B) {
        obj = D_800859B8;
        def = entry->defs;
        D_800859B0 = entry->count;
        i = D_800859B0;
        while (i != 0) {
            obj->unk12 = -1;
            obj->unk10 = Spirit_IsCollected(def->unk8);
            obj->x = def->x;
            obj->z = -def->z;
            Coll_ResolveFloorAndWalls(obj->x, 0.0f, obj->z, 0xA00, &D_80085A78);
            obj->y = D_80085A78.unk4;
            obj->unkC = 0.0f;
            obj->unk14 = def->unk8;
            i--;
            def++;
            obj++;
        }
    } else {
        D_800859B0 = 0;
    }
}

Unk800859B8* Spirit_FindInFront(Unk80013D08Arg* arg0) {
    s32 n = D_800859B0;
    Unk800859B8* obj;
    f32 dx;
    f32 dz;
    Unk800859B8* found = NULL;
    f32 dist;
    Vec2f_147A0 v;

    obj = D_800859B8;
    while (n != 0) {
        if (obj->unk10 == 0) {
            dx = obj->x - arg0->x;
            dz = obj->z - arg0->z;
            if (dx * dx + dz * dz < 400.0f) {
                v.x = dx;
                v.y = dz;
                func_800271B4(arg0->unk10, &v);
                if (v.y >= 0.0f && v.x > -5.0 && v.x < 5.0) {
                    found = obj;
                    break;
                }
            }
        }
        n--;
        obj++;
    }
    return found;
}

void Spirit_SpawnSparkles(void) {
    static Unk8004E658 D_8004E658 = {
        0x001E, 0, (void*)Spirit_MoveSparkle, 0x02101000, 0, D_8004E258, D_8004E208,
        0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.3f, 0.0f, 0,
    };
    s32 n;
    Unk800859B8* obj;
    s32 pad;
    Vec2f_147A0 v;

    n = D_800859B0;
    obj = D_800859B8;
    while (n != 0) {
        if (obj->unk10 == 0) {
            obj->unk12++;
            if (obj->unk12 >= 0 && (obj->unk12 & 1)) {
                v.x = 0.0f;
                v.y = 1.0f;
                func_800271B4(obj->unkC, &v);
                D_8004E658.unk18 = obj->x + v.x;
                D_8004E658.unk1C = obj->y;
                D_8004E658.unk20 = obj->z + v.y;
                D_8004E658.unk10 = D_8004E258[obj->unk12 >> 1];
                Effect_AllocateSprite(&D_8004E658);
                if (obj->unk12 >= 6) {
                    obj->unk12 = func_80026E90(30) - 60;
                    obj->unkC += 0.39269908169872414;
                }
            }
        }
        n--;
        obj++;
    }
}

Color_147A0 D_8004E698[2] = { { 0x8C, 0x00, 0xFF, 0xDC }, { 0x8C, 0x00, 0xFF, 0x78 } };

void Spirit_MoveSparkle(Unk80013FA4Arg* arg0) {
    f32 s;
    u8* c;

    s = sinf((f32)arg0->unk3C * 0.09817477042468103) * 0.1;
    arg0->unk3C += 4;
    c = (u8*)&D_8004E698[arg0->unk0 & 1];
    arg0->unk18 += arg0->unk30 + s;
    arg0->unk1C += arg0->unk34;
    arg0->unk20 += arg0->unk38 + s;
    gDPSetEnvColor(D_8007A184++, c[0], c[1], c[2], c[3]);
}

u8 Spirit_IsCollected(u16 arg0) {
    return D_80085A98[arg0 >> 3] & D_8004F770[arg0 & 7];
}
