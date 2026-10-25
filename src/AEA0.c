#include "common.h"

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[2];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ struct Unk8000BA20 *unk30;
    /* 0x34 */ u8 pad34[4];
} EnemyDef; /* size 0x38 */

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ u16 unk84;
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u8 pad88[0xC];
    /* 0x94 */ f32 unk94;
} EnemyStats;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ f32 angle;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 pad38[0xC];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 pad48[4];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 pad56[2];
    /* 0x58 */ u16 unk58;
    /* 0x5A */ u8 pad5A[4];
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ EnemyDef *unk64;
    /* 0x68 */ EnemyStats *unk68;
} Obj; /* size 0x6C */

typedef struct {
    /* 0x000 */ u16 type;
    /* 0x002 */ s16 unk2;
    /* 0x004 */ u16 unk4;
    /* 0x006 */ u16 unk6;
    /* 0x008 */ u16 flags;
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[2];
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 pad14[8];
    /* 0x01C */ struct Unk8000BA20 *unk1C;
    /* 0x020 */ f32 unk20;
    /* 0x024 */ f32 unk24;
    /* 0x028 */ EnemyDef *unk28;
    /* 0x02C */ Obj obj;
    /* 0x098 */ u16 unk98;
    /* 0x09A */ u8 pad9A[0x82];
    /* 0x11C */ u16 unk11C;
    /* 0x11E */ u16 unk11E;
    /* 0x120 */ u16 unk120;
    /* 0x122 */ u16 unk122;
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u8 pad126[2];
    /* 0x128 */ f32 unk128;
    /* 0x12C */ f32 unk12C;
} Enemy; /* size 0x130 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[6];
    /* 0x0A */ u16 unkA;
} EnemyAI;

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u8 **unk8;
    /* 0x0C */ EnemyDef *unkC;
    /* 0x10 */ s32 unk10;
} Unk800561A0; /* size 0x14 */

typedef struct {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u16 unk12;
} Unk8007C288;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ Obj *unkC;
} Unk8007C060;

typedef struct {
    /* 0x000 */ u8 pad0[0x140];
    /* 0x140 */ s16 unk140;
    /* 0x142 */ u16 unk142;
    /* 0x144 */ u16 unk144;
    /* 0x146 */ u8 pad146[2];
    /* 0x148 */ f32 unk148;
    /* 0x14C */ f32 unk14C;
} Unk80056718;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ struct Unk8007AA84 *unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[0x18];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x34];
    /* 0x78 */ u16 unk78;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk8007C2A8;

extern s32 D_8007C2A4;
extern Unk8007C2A8 *D_8007C2A8[];

typedef struct Unk8007AA84 {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x10];
    /* 0x2C */ u16 unk2C;
} Unk8007AA84;

f32 sqrtf(f32);
extern Unk8007AA84 *D_8007AA84;

typedef struct {
    /* 0x00 */ u8 pad0[10];
} Unk800C18D8;

typedef struct Unk8000BA20 {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk8000BA20; /* size 0x18 */

typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ s16 unkE;
} Unk8000AA74;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

void func_800107F0(f32, f32, f32, s32, CollResult *);
extern CollResult D_8007C080;

void func_8000A5E4(void);
Unk8000BA20 *func_8000B7A4(Enemy *, Obj *);
void func_8000BA20(Enemy *, Obj *, Unk8000BA20 *);
extern Enemy *D_8007C028;
extern s16 D_8008C162;
void func_80020428(s32, Obj *, u8 *, s32);
void func_8002099C(s32, Obj *, u8 *);
void func_800131F0(f32, f32, f32, f32, f32, f32, f32);
extern Obj *D_8007C030[];
extern Gfx *D_8007A184;
void func_8000CC40(s32, s32);
f32 func_800270D0(f32, f32);
void func_800201A0(Obj *, s32, s32, s32, s32, u16);
void func_80015F44(s32, Obj *);
void func_8000BB90(Obj *, f32, f32);
void func_8000BCA4(s32, f32, f32, Obj *, EnemyAI *);
void func_8000BFE0(Obj *, Vec3f *);
void func_8000CAE8(Obj *);
void func_8000CC78(void);
void func_80019820(u16, u16, f32, f32, f32, f32, Unk800C18D8 *, Vec3f *, Obj *);
void func_8001B3FC(s32, s32, f32, f32, f32, f32);
void func_8001FC14(Obj *);
void func_80020214(Obj *, u8 *, f32, Vec3f *);
void func_80023D28(Obj *);
void func_8002433C(void);
void func_800269B8(s32, u16, void *);
u32 func_80026E90(u32);
void func_800271B4(f32, Vec3f *);
void func_80028120();
void func_8002A7C8(u8, s8, u8);
extern s32 D_8004DD38[];

extern void (*D_8004DD20[])(Obj *, Enemy *, u8 *);
extern u8 D_8004F760[];
extern Unk800561A0 D_800561A0[];
extern u32 D_800566C8[];
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} SpawnDef; /* size 0x10 */

typedef struct {
    /* 0x00 */ u16 time;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} SpawnScript; /* size 0x18 */

typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x24];
} Unk800C185C; /* size 0x44 */

extern Unk80056718 D_80056718;
extern u16 D_8005685A;
extern u16 D_8005685C;
extern Unk800C185C *D_800C185C[];
extern Enemy *D_8007C068;
extern Obj *D_8007C06C;
extern f32 D_8007AA20;
extern f32 D_8007AA24;
extern f32 D_8007AA28;
extern f32 D_8007B928;
extern f32 D_8007B92C;
void func_80015D78(s32);
void func_8000C05C(f32 *, f32 *, Obj *);
extern f32 D_8008BE5C;
extern f32 D_8008BE60;
extern f32 D_8008BE64;
extern f32 D_8008BE68;
extern f32 D_8008BE6C;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[8];
} AnimDef; /* size 0xC */

void func_800169B8(Obj *, s32, s32, s32);
s32 func_8000C3FC(Obj *obj);
u16 func_8000C48C(Enemy *arg0);
s32 func_80007FD8(s32, s32, Obj *);
void func_8001BE2C(f32, f32, f32);
void func_8001AE24(Obj *, s32, s32);
void func_8002373C(Obj *, u16, u16, s16);
void func_8000847C(void);
extern f32 D_8007C074;
extern s32 D_8007A9B4;
extern s32 D_8007A9B8;
extern Unk8007AA08 D_8007AA08;
extern EnemyStats *D_8007AA88;
extern s32 D_8007B900;
extern Enemy D_8007B908[6];
extern s32 D_8007C02C;
extern u8 **D_8007C048;
extern s32 D_8007C04C;
extern u16 D_8007C050[];
extern Unk800561A0 *D_8007C05C;
extern u16 D_8007C060;
extern SpawnScript *D_8007C064;
extern Vec3f D_8007C070;
extern Unk8007C288 *D_8007C288;
extern u16 D_800842E8;
extern u16 D_8008BE52;
extern u16 D_8008BE58;
extern Unk800C18D8 D_800C18D8[];
extern u8 D_8020E6F0[];

void func_8000A2A0(void) {
    s32 i;
    Enemy *e;

    D_8007B900 = 0;
    D_8007C02C = 0;
    e = D_8007B908;
    i = 6;
    do {
        e->obj.unk50 = -1;
        e++;
        i--;
    } while (i != 0);
    if (D_800842E8 & 1) {
        func_8000A5E4();
    }
}

void func_8000A310(void) {
    s32 n;
    Enemy *e;
    Obj *obj;

    n = D_8007B900;
    if (n != 0) {
        for (e = D_8007B908; n != 0; e++) {
            obj = &e->obj;
            if (e->obj.unk50 != -1) {
                D_8004DD20[e->type](obj, e, D_8007C048[obj->unk50]);
                n--;
            }
        }
    }
    if (D_8008BE52 & 0x100) {
        func_8000CC78();
    }
}

void func_8000A3E4(s32 arg0) {
    Enemy *e;
    s32 n;
    Obj **list;
    Obj *obj;
    u8 *anims;
    f32 y;
    f32 h;

    D_8007C02C = 0;
    list = D_8007C030;
    gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
    n = D_8007B900;
    e = D_8007B908;
    while (n != 0) {
        obj = &e->obj;
        if (e->obj.unk50 != -1) {
            y = obj->y;
            anims = D_8007C048[obj->unk50];
            if (obj->unk64->unk0 == 1) {
                h = obj->unk64->unk1C * obj->unk24;
                if (y < D_8007AA08.y) {
                    obj->y = D_8007AA08.y;
                }
                obj->y += h;
                obj->unk68->unk94 = obj->y;
            }
            func_80020428(1, obj, &anims[obj->unk52 * 12], arg0);
            func_8002099C(obj->unk58, obj, &anims[obj->unk52 * 12]);
            obj->y = y;
            if (obj->unk64->unk0 != 2 && !(obj->unk62 & 0x8000)) {
                func_800131F0(obj->x, obj->y, obj->z, obj->unk2C, obj->unk30, obj->unk34, obj->unk28 * obj->unk24);
            }
            *list++ = obj;
            n--;
            D_8007C02C++;
        }
        e++;
    }
}

void func_8000A5E4(void) {
    u32 start;
    u32 end;

    D_8007C05C = &D_800561A0[D_8007C288->unk12];
    D_8007C048 = D_8007C05C->unk8;
    D_8007C04C = D_8007C05C->unk10;
    start = D_8007C05C->start;
    end = D_8007C05C->end;
    func_80028120(start, D_8020E6F0, end - start, &D_8007C05C);
}

void func_8000A65C(void) {
    Enemy *e;
    s32 i;
    Obj *obj;

    for (e = D_8007B908, i = 6; i != 0; i--, e++) {
        obj = &e->obj;
        if (e->obj.unk50 != -1) {
            func_80023D28(obj);
            obj->unk50 = -1;
        }
    }
    D_8007B900 = 0;
}

void func_8000A6D0(s32 idx, f32 x, f32 z, f32 angle, Obj *obj, Enemy *e) {
    s32 pad;
    EnemyDef *def;

    def = &D_8007C05C->unkC[idx];
    obj->unk50 = def->unk2;
    func_800201A0(obj, 0, 1, 0, 1, 1);
    obj->unk54 = func_80026E90(16);
    obj->unk24 = def->unk20;
    obj->unk28 = def->unk18;
    obj->unk68 = (EnemyStats *)&e->unk98;
    obj->unk64 = def;
    e->unk28 = def;
    e->unkA = def->unk6;
    e->unkC = def->unk6;
    e->type = 0;
    e->flags = 0;
    e->unk10 = (f32)def->unkC * 0.2857 + 17.0;
    e->unk20 = e->unk24 = 0;
    D_8007C080.x = obj->unk64->unk18 * obj->unk64->unk20;
    func_800107F0(x, 0.0f, z, 0xA01, &D_8007C080);
    if (D_8007C080.flags & 0x8000) {
        if (obj->unk64->unk0 == 0) {
            func_800107F0(x + 0.5, 0.0f, z + 0.5, 0xA01, &D_8007C080);
            if (D_8007C080.flags & 0x8000) {
                D_8007C080.y = D_8007AA08.y;
            }
        } else {
            D_8007C080.y = D_8007AA08.y;
        }
    }
    obj->x = D_8007C080.x;
    obj->y = D_8007C080.y;
    obj->z = D_8007C080.z;
    obj->angle = angle;
    obj->unk2C = D_8007C080.nx;
    obj->unk30 = D_8007C080.ny;
    obj->unk34 = D_8007C080.nz;
    obj->unk62 = D_8007C080.flags;
    obj->unk5E = 1;
    obj->unk60 = 0;
    e->unk98 = 0;
    e->unk124 = 0;
    e->unk11C = e->unk28->unk2A;
    e->unk122 = 16;
    e->unk11E = obj->unk64->unkC;
    e->unk120 = obj->unk64->unkE;
    e->unk128 = 1.0f;
    e->unk12C = obj->y;
}

void func_8000A95C(void) {
    u32 i;
    s32 swapped;
    u16 tmp;
    u16 keys[6];

    for (i = 0; i < D_8007B900; i++) {
        D_8007C050[i] = i;
        keys[i] = D_8007B908[i].unk28->unkC;
    }
    do {
        swapped = 0;
        for (i = 0; i < D_8007B900 - 1; i++) {
            if (keys[i] < keys[i + 1]) {
                tmp = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = tmp;
                swapped++;
                tmp = D_8007C050[i];
                D_8007C050[i] = D_8007C050[i + 1];
                D_8007C050[i + 1] = tmp;
            }
        }
    } while (swapped);
}

void func_8000AA28(void) {
    D_8007B908[D_8007C050[D_8008BE58]].flags |= 1;
}

void func_8000AA74(Obj *obj, Enemy *e, Unk8000AA74 *arg2) {
    Unk8000BA20 *v;

    func_8000BFE0(obj, &D_8007C070);
    func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
    if (e->flags & 1) {
        D_8007C028 = e;
        D_8008C162 = 60;
        e->flags &= 0xFFFC;
        if (e->unk98 & 8) {
            func_8001FC14(obj);
            return;
        }
        v = func_8000B7A4(e, obj);
        if (v != NULL) {
            if (!(e->flags & 0x10)) {
                func_8000BA20(e, obj, v);
                return;
            }
            e->type = 1;
            e->unk4 = 4;
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
                func_800201A0(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2->unkE / 10;
                func_800201A0(obj, 1, 10, 1, 10, 1);
            }
        } else {
            e->type = 1;
            e->unk4 = 4;
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
                func_800201A0(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2->unkE / 10;
                func_800201A0(obj, 1, 10, 1, 10, 1);
            }
        }
    }
}

void func_8000AC84(Obj *obj, Enemy *e, Unk8000AA74 *arg2) {
    Unk8000BA20 *v;
    f32 dx;
    f32 dz;
    f32 d;

    func_8000BB90(obj, D_8007AA08.x, D_8007AA08.z);
    if (D_8008BE52 & 0x100) {
        D_8007C070.x = 0.0f;
        D_8007C070.y = 0.4f;
        func_800271B4(obj->angle, &D_8007C070);
    } else {
        func_8000BFE0(obj, &D_8007C070);
    }
    func_8000BCA4(1, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
    e->unk2--;
    if (e->unk2 == 0) {
        e->unk4--;
        if (e->unk1C != NULL) {
            dx = D_8007AA08.x - obj->x;
            dz = D_8007AA08.z - obj->z;
            d = sqrtf(dx * dx + dz * dz) - D_8007AA84->unk18 * D_8007AA08.unk3C;
            if (d < e->unk1C->unk10 * obj->unk24) {
                func_8000BA20(e, obj, e->unk1C);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                func_8000BA20(e, obj, e->unk1C);
                return;
            }
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
            } else {
                e->unk2 = arg2->unkE / 10;
            }
        } else {
            v = func_8000B7A4(e, obj);
            if (v != NULL) {
                func_8000BA20(e, obj, v);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                e->type = 0;
                func_800201A0(obj, 0, 1, 0, 1, 1);
                func_8001FC14(obj);
                return;
            }
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
            } else {
                e->unk2 = arg2->unkE / 10;
            }
        }
    }
}

void func_8000AF14(Obj *obj, EnemyAI *ai, s32 arg2) {
    func_8000BFE0(obj, &D_8007C070);
    func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        if (ai->unkA == 0) {
            func_80023D28(obj);
            func_8000CAE8(obj);
            obj->unk50 = -1;
            obj->unk60 &= 0xFFFE;
            D_8007B900--;
            D_8007A9B4 += obj->unk64->unk10;
            D_8007A9B8 += obj->unk64->unk14;
            func_8002A7C8(0, 10, 0xFF);
        } else {
            ai->unk0 = 0;
            obj->unk60 &= 0xFFFC;
        }
    }
}

void func_8000B030(Obj *obj, EnemyAI *ai, s32 arg2) {
    func_8000BB90(obj, D_8007AA08.x, D_8007AA08.z);
    func_8000BFE0(obj, &D_8007C070);
    func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        ai->unk0 = 0;
        obj->unk60 &= 0xFFFE;
        func_8001FC14(obj);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000B0D8.s")

void func_8000B508(Obj *obj, Enemy *e, AnimDef *anims) {
    Unk8000BA20 *a;

    switch (e->unk6) {
        case 0:
            if (e->unk1C->unk2 & 2) {
                func_8000BFE0(obj, &D_8007C070);
                func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                func_800169B8(obj, e->unk1C->unk0 & ~0x8000, 0, 0);
                a = e->unk1C;
                e->unk6++;
                if (a->unkA == -1) {
                    e->unk2 = anims[a->unk8].unk2 - a->unk4;
                } else {
                    e->unk6++;
                    e->unk2 = a->unk6;
                }
                if (e->unk2 <= 0) {
                    e->unk2 = 15;
                }
                func_8001FC14(obj);
            }
            break;
        case 1:
            if (e->unk1C->unk2 & 0xA) {
                func_8000BFE0(obj, &D_8007C070);
                func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                e->type = 0;
                obj->unk60 &= 0xFFFE;
                e->unk20 = e->unk24 = 0.0f;
            }
            break;
        case 2:
            if (e->unk1C->unk2 & 0xA) {
                func_8000BFE0(obj, &D_8007C070);
                func_8000BCA4(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                a = e->unk1C;
                e->unk6--;
                e->unk2 = anims[a->unkC].unk2;
                func_800201A0(obj, a->unkC, 1, 0, 1, 1);
            }
            if (e->unk2 <= 0) {
                e->unk2 = 15;
            }
            break;
    }
}

Unk8000BA20 *func_8000B7A4(Enemy *e, Obj *obj) {
    f32 dist;
    f32 r;
    f32 range;
    f32 d;
    f32 d2;
    s32 swapped;
    s32 cont;
    u32 i;
    Unk8000BA20 *sel;
    Unk8000BA20 *b;
    Unk8000BA20 *list[5];
    Unk8000BA20 *a;

    e->flags &= ~0x10;
    dist = sqrtf((D_8007AA08.x - obj->x) * (D_8007AA08.x - obj->x) + (D_8007AA08.z - obj->z) * (D_8007AA08.z - obj->z)) - D_8007AA84->unk18 * D_8007AA08.unk3C;
    sel = e->unk28->unk30;
    for (i = 0; i < e->unk28->unk2C; i++) {
        list[i] = sel++;
    }
    swapped = 0;
    do {
        for (i = 0; i < e->unk28->unk2C - 1; i++) {
            b = list[i];
            a = list[i + 1];
            if (b->unk10 > a->unk10) {
                list[i] = a;
                list[i + 1] = b;
                swapped++;
            }
        }
        cont = swapped != 0;
        swapped = 0;
    } while (cont);
    for (i = 0; i < e->unk28->unk2C; i++) {
        sel = list[i];
        if (i < e->unk28->unk2C - 1) {
            d = sel->unk10 * obj->unk24;
            d2 = e->unk10 * e->unk128 + d;
            if (dist < d) {
                swapped = 1;
                break;
            }
            if (dist < d2) {
                b = list[i + 1];
                d = b->unk10 * obj->unk24;
                if (dist < d) {
                    if (func_80026E90(2) == 0) {
                        sel = b;
                    }
                    swapped = 1;
                    if (sel != b) {
                        e->flags |= 0x10;
                    }
                    break;
                }
            }
        } else {
            d = sel->unk10 * obj->unk24;
            d2 = e->unk10 * e->unk128 + d;
            if (dist < d2) {
                if (d < dist) {
                    e->flags |= 0x10;
                }
                swapped = 1;
                break;
            }
        }
    }
    if (!swapped) {
        sel = NULL;
    }
    if (e->unk28->unk24 & 4) {
        sel = &e->unk28->unk30[func_80026E90(e->unk28->unk2C)];
    }
    e->unk1C = sel;
    return sel;
}

void func_8000BA20(Enemy *e, Obj *obj, Unk8000BA20 *arg2) {
    s32 t = arg2->unk0 & 0x8000;

    if (t && (e->unk98 & 0x40)) {
        e->type = 0;
        func_800201A0(obj, 0, 1, 0, 1, 1);
        func_8001FC14(obj);
        return;
    }
    if (t) {
        e->type = 5;
    } else {
        e->type = 4;
    }
    e->unk6 = 0;
    e->unk2 = arg2->unk4;
    e->flags &= 0xFFD7;
    obj->unk60 = 1;
    obj->angle = func_800270D0(D_8007AA08.x - obj->x, D_8007AA08.z - obj->z);
    func_800201A0(obj, arg2->unk8, 1, arg2->unkA == -1 ? 0 : arg2->unkA, 1, 1);
    func_80015F44(arg2->unk4 + 0xF, obj);
    if (e->unk2 == 0) {
        e->unk2 = 1;
    }
    if (D_8008BE52 & 0x100) {
        func_8000CC40(arg2->unk0 & 0xFF, (s32)e);
    }
}

void func_8000BB90(Obj *obj, f32 x, f32 z) {
    f32 diff;

    x -= obj->x;
    z -= obj->z;
    diff = func_800270D0(x, z) - obj->angle;
    if (diff > 3.141592653589793) {
        diff -= 6.283185307179586;
    } else if (diff < -3.141592653589793) {
        diff += 6.283185307179586;
    }
    obj->angle += diff * 0.05;
    if (obj->angle > 3.141592653589793) {
        obj->angle -= 6.283185307179586;
    } else if (obj->angle < -3.141592653589793) {
        obj->angle += 6.283185307179586;
    }
}

void func_8000BCA4(s32 clamp, f32 dx, f32 dz, Obj *obj, EnemyAI *ai) {
    Enemy *e = (Enemy *)ai;
    f32 x;
    f32 z;
    f32 d;
    f32 r;
    s32 flags;

    if (e->unk20 != 0.0f || e->unk24 != 0.0f) {
        dx += e->unk20;
        dz += e->unk24;
        e->unk20 *= 0.9f;
        e->unk24 *= 0.9f;
    }
    if (clamp) {
        x = obj->x + obj->unk18 - D_8008BE64;
        z = obj->z + obj->unk20 - D_8008BE68;
        d = sqrtf(x * x + z * z);
        r = e->unk10 * e->unk128;
        if (r < d) {
            dx = r * x / d - obj->x + D_8008BE64;
            dz = r * z / d - obj->z + D_8008BE68;
            e->flags |= 2;
        }
    }
    x = obj->x + obj->unk18 - D_8008BE5C;
    z = obj->z + obj->unk20 - D_8008BE60;
    d = sqrtf(x * x + z * z);
    if (D_8008BE6C < d) {
        dx = (D_8008BE6C - 0.5) * x / d - obj->x + D_8008BE5C;
        dz = (D_8008BE6C - 0.5) * z / d - obj->z + D_8008BE60;
    }
    func_8000C05C(&dx, &dz, obj);
    obj->unk18 = dx;
    obj->unk20 = dz;
    obj->x += dx;
    obj->z += dz;
    flags = 0xA00;
    if (obj->unk64->unk0 == 0 && e->type != 0) {
        flags = 0xA01;
    }
    D_8007C080.x = obj->unk64->unk18 * obj->unk64->unk20;
    func_800107F0(obj->x, obj->y, obj->z, flags, &D_8007C080);
    obj->x = D_8007C080.x;
    obj->y = D_8007C080.y;
    obj->z = D_8007C080.z;
    if (e->flags & 4) {
        obj->y -= 30.0;
    }
    obj->unk2C = D_8007C080.nx;
    obj->unk30 = D_8007C080.ny;
    obj->unk34 = D_8007C080.nz;
    obj->unk62 = D_8007C080.flags;
}

void func_8000BFE0(Obj *obj, Vec3f *out) {
    u8 *anims;

    anims = D_8007C048[obj->unk50];
    func_80020214(obj, anims + obj->unk52 * 0xC, obj->unk24, out);
    out->x = -obj->unk44;
    out->y = obj->unk4C;
    func_800271B4(obj->angle, out);
}

void func_8000C05C(f32 *dx, f32 *dz, Obj *obj) {
    f32 nx;
    f32 nz;
    f32 ddx;
    f32 ddz;
    f32 r;
    f32 d;
    s32 hit;
    f32 radius;
    s32 i;
    Obj **list;
    Obj *other;
    Unk8007C2A8 **list2;
    Unk8007C2A8 *other2;

    nx = *dx + obj->x;
    nz = *dz + obj->z;
    radius = obj->unk28 * obj->unk24;
    hit = 0;
    ddx = nx - D_8007AA08.x;
    ddz = nz - D_8007AA08.z;
    r = D_8007AA08.unk40 * D_8007AA08.unk3C + radius;
    if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
        d = sqrtf(ddx * ddx + ddz * ddz);
        if (d < r) {
            d = r / d;
            hit = 1;
            ddx *= d;
            ddz *= d;
            *dx = D_8007AA20 + ddx - obj->x;
            *dz = D_8007AA28 + ddz - obj->z;
        }
    }
    i = D_8007C02C;
    if (i != 0) {
        for (list = D_8007C030; !hit && i != 0; i--) {
            other = *list++;
            if (other != obj) {
                ddx = nx - other->x;
                ddz = nz - other->z;
                r = other->unk28 * other->unk24 + radius;
                if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                    d = sqrtf(ddx * ddx + ddz * ddz);
                    if (d != 0.0f && d < r) {
                        d = r / d;
                        hit++;
                        ddx *= d;
                        ddz *= d;
                        *dx = other->x + ddx - obj->x;
                        *dz = other->z + ddz - obj->z;
                    }
                }
            }
        }
    }
    i = D_8007C2A4;
    if (i != 0) {
        for (list2 = D_8007C2A8; !hit && i != 0; i--) {
            other2 = *list2++;
            ddx = nx - other2->x;
            ddz = nz - other2->z;
            r = radius + other2->unk10 * 2.0;
            if (ddx < r && -r < ddx && ddz < r && -r < ddz) {
                d = sqrtf(ddx * ddx + ddz * ddz);
                if (d < r) {
                    d = r / d;
                    hit++;
                    ddx *= d;
                    ddz *= d;
                    *dx = other2->x + ddx - obj->x;
                    *dz = other2->z + ddz - obj->z;
                }
            }
        }
    }
}

s32 func_8000C3FC(Obj *obj) {
    s16 chance;

    chance = (obj->unk68->unk86 * 100) / (obj->unk68->unk86 + ((D_8007AA88->unk86 + 7) >> 3));
    return func_80026E90(100) < chance;
}

u16 func_8000C48C(Enemy *arg0) {
    u16 dmg;

    dmg = arg0->unk11C;
    dmg = (dmg * arg0->unk122) >> 4;
    if (func_80026E90(32) == 0) {
        dmg = dmg + (dmg >> 1);
        func_800269B8(4, 0, D_8004F760);
        arg0->flags |= 0x20;
    }
    if (arg0->unk98 & 1) {
        dmg >>= 1;
    }
    return dmg;
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000C528.s")

void func_8000CA88(void) {
    func_8002433C();
    func_8002A7C8(0, 0x17, 0xFF);
}

s32 func_8000CAB8(Obj *arg0) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (arg0 == &D_8007B908[i].obj) {
            break;
        }
    }
    return i;
}

void func_8000CAE8(Obj *obj) {
    f32 y;
    Unk800C18D8 *t;

    D_8007C070.x = D_80056718.unk148;
    D_8007C070.y = D_80056718.unk14C;
    t = &D_800C18D8[D_80056718.unk140];
    D_8007C070.z = obj->unk28;
    if (obj->unk64->unk0 == 1) {
        y = obj->unk68->unk94;
    } else {
        y = obj->y + obj->unk64->unk1C * 0.5 * obj->unk24;
    }
    func_80019820(D_8005685A, D_8005685C, obj->x, y, obj->z, obj->angle, t, &D_8007C070, obj);
    func_8001B3FC(2, 0x1E, obj->x, obj->unk64->unk1C * obj->unk24 + y, obj->z,
                  obj->unk64->unk18 * obj->unk24 * 3.6);
}

void func_8000CC30(void) {
    D_8007C064 = 0;
}

void func_8000CC40(s32 arg0, s32 arg1) {
    ((Unk8007C060 *)&D_8007C060)->unk0 = 0;
    ((Unk8007C060 *)&D_8007C060)->unk4 = D_800566C8[arg0];
    ((Unk8007C060 *)&D_8007C060)->unk8 = arg1;
    ((Unk8007C060 *)&D_8007C060)->unkC = &D_8007B908[0].obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000CC78.s")
