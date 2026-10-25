#include "common.h"

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
} Unk80085A78;

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
    u8 r, g, b, a;
} Color_147A0;

extern u8 D_80085A98[];
extern u8 D_8004F770[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern Unk8004DFC0 D_8004DFC0[];
extern s32 D_800859B0;
extern Unk800859B8 D_800859B8[];
extern Unk80085A78 D_80085A78;
extern u8 D_8004E658[];
extern u8* D_8004E668;
extern f32 D_8004E670[3];

extern u8 D_8004E258[][0x100];
extern Color_147A0 D_8004E698[];
extern Gfx* D_8007A184;

void func_800107F0(f32, f32, f32, s32, Unk80085A78*);
u8 func_800140B0(u16);
void func_800271B4(f32, Vec2f_147A0*);
void func_8001D9A8(void*);
s32 func_80026E90(s32);
f32 sinf(f32);

void func_80013BA0(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_80085A98[i] = 0;
    }
}

void func_80013BD0(void) {
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
            obj->unk10 = func_800140B0(def->unk8);
            obj->x = def->x;
            obj->z = -def->z;
            func_800107F0(obj->x, 0.0f, obj->z, 0xA00, &D_80085A78);
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

Unk800859B8* func_80013D08(Unk80013D08Arg* arg0) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/147A0/func_80013E4C.s")

void func_80013FA4(Unk80013FA4Arg* arg0) {
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

u8 func_800140B0(u16 arg0) {
    return D_80085A98[arg0 >> 3] & D_8004F770[arg0 & 7];
}
