#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 scale;
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
    /* 0x64 */ u8 unk64[0x8];
} Unk80085290; // size = 0x6C

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 ry;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
} Unk140D0Def; // size = 0x24

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x04 */ Unk140D0Def* defs;
} Unk140D0Group; // size = 0x8

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ Unk140D0Group* groups;
} Unk8004DF1C; // size = 0x8

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Unk80085968;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk80085958;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk80013808Arg;

typedef struct {
    u8 unk0[0xC];
} Unk8010FDC4;

extern u8 D_80085988[];
extern u8 D_800859A8[];
extern u8 D_8004F770[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern s32 D_80085950;
extern Unk80085290 D_80085290[];
extern Unk80085968 D_80085968;
extern Unk80085958 D_80085958;
extern Unk8010FDC4 D_8010FDC4[];
/* Message text around the name in func_80013A50. */
u8 D_8004DF00[8] = {
#include "assets/D_8004DF00.inc.c"
};
u8 D_8004DF08[20] = {
#include "assets/D_8004DF08.inc.c"
};
/* Per-map placement groups (the group arrays are in the map overlays). */
Unk8004DF1C D_8004DF1C[19] = {
    { 0x0D, (Unk140D0Group*) 0x80199140 },
    { 0x0E, (Unk140D0Group*) 0x801A3B44 },
    { 0x0F, (Unk140D0Group*) 0x801697A4 },
    { 0x11, (Unk140D0Group*) 0x8016AA24 },
    { 0x13, (Unk140D0Group*) 0x8015EB40 },
    { 0x15, (Unk140D0Group*) 0x801A6C18 },
    { 0x16, (Unk140D0Group*) 0x80183200 },
    { 0x17, (Unk140D0Group*) 0x8018CBAC },
    { 0x18, (Unk140D0Group*) 0x80166608 },
    { 0x19, (Unk140D0Group*) 0x80171794 },
    { 0x1A, (Unk140D0Group*) 0x8016D584 },
    { 0x1B, (Unk140D0Group*) 0x8016E9E4 },
    { 0x1C, (Unk140D0Group*) 0x80169D7C },
    { 0x1D, (Unk140D0Group*) 0x80133504 },
    { 0x1E, (Unk140D0Group*) 0x801527CC },
    { 0x1F, (Unk140D0Group*) 0x8014C030 },
    { 0x20, (Unk140D0Group*) 0x8013D5D4 },
    { 0x21, (Unk140D0Group*) 0x80143378 },
    { 0x09, (Unk140D0Group*) 0x8015F1E4 },
};
extern u8 D_8007B430[];
extern u8 D_8007B8E0;
extern u8* D_803AB288[];

void func_800107F0(f32, f32, f32, s32, Unk80085968*);
u8 func_80013B20(u16);
void func_80013B60(u16);
void func_800131F0(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale);
void func_800201A0(Unk80085290*, s32, s32, s32, s32, u16);
void func_80020428(s32, Unk80085290*, Unk8010FDC4*, s32);
void func_8002099C(u16, Unk80085290*, Unk8010FDC4*);
void func_800271B4(f32, Unk80085958*);
void func_8002A7C8(u8, s8, u8);

void func_800134D0(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80085988[i] = 0;
    }
}

void func_80013500(void) {
    Unk8004DF1C* entry;
    Unk140D0Group* group;
    Unk140D0Def* def;
    Unk80085290* p;
    u32 i;
    s32 id;
    s32 mode;

    for (id = D_800842BC, entry = D_8004DF1C, i = 0; i < 19; i++, entry++) {
        if (id == entry->id) {
            break;
        }
    }
    if (i != 19) {
        group = &entry->groups[D_800842C0];
        D_80085950 = group->count;
        i = D_80085950;
        def = group->defs;
        p = D_80085290;
        while (i != 0) {
            p->x = def->x;
            p->z = def->z;
            p->rx = 0.0f;
            p->rz = 0.0f;
            p->ry = def->ry;
            func_800107F0(p->x, 0.0f, p->z, 0xA00, &D_80085968);
            p->y = D_80085968.unk4;
            p->unk2C = D_80085968.unkC;
            p->unk30 = D_80085968.unk10;
            p->unk34 = D_80085968.unk14;
            p->unk1C = def->unk14;
            p->unk18 = def->unk18;
            p->unk20 = def->unk1C;
            p->unk44 = def->unkC;
            p->unk4C = def->unk10;
            p->scale = 0.07f;
            p->unk62 = def->unk20;
            p->unk50 = def->unk21;
            p->unk60 = 0;
            if (func_80013B20(p->unk62)) {
                mode = 3;
            } else {
                mode = 0;
            }
            func_800201A0(p, mode, 1, mode, 1, 1);
            i--;
            p++;
            def++;
        }
    } else {
        D_80085950 = 0;
    }
}

void func_800136B8(s32 arg0) {
    s32 n;
    Unk80085290* p;
    u16 t;

    n = D_80085950;
    p = D_80085290;
    while (n != 0) {
        if (p->unk60 & 0x8000) {
            t = p->unk60 & ~0x8000;
            t--;
            if (!t) {
                p->unk60 = 0;
                func_800201A0(p, 3, 1, 3, 1, 1);
            } else {
                p->unk60 = t | 0x8000;
            }
        }
        func_80020428(0, p, &D_8010FDC4[p->unk52], arg0);
        func_8002099C(p->unk58, p, &D_8010FDC4[p->unk52]);
        func_800131F0(p->x, p->y, p->z, p->unk2C, p->unk30, p->unk34, 6.0f);
        n--;
        p++;
    }
}

Unk80085290* func_80013808(Unk80013808Arg* arg0) {
    s32 n = D_80085950;
    Unk80085290* obj = D_80085290;
    f32 d;
    f32 dx;
    f32 dz;

    while (n != 0) {
        if (func_80013B20(obj->unk62) == 0) {
            d = arg0->unk10 - obj->unk1C;
            if (d > 3.141592653589793) {
                d = d - 3.141592653589793;
            } else if (d < -3.141592653589793) {
                d = d + 3.141592653589793;
            }
            if (d < 0.7853981633974483 && d > -0.7853981633974483) {
                dx = arg0->x - obj->unk44;
                dz = arg0->z - obj->unk4C;
                if (dx * dx + dz * dz < 300.0f) {
                    D_80085958.x = dx;
                    D_80085958.y = dz;
                    func_800271B4(obj->unk1C, &D_80085958);
                    dx = D_80085958.x;
                    dz = D_80085958.y;
                    if (dx < 0.0f) {
                        dx = -dx;
                    }
                    if (dz < 0.0f) {
                        dz = -dz;
                    }
                    if (dx < obj->unk18 && dz < obj->unk20) {
                        break;
                    }
                }
            }
        }
        n--;
        obj++;
    }
    if (n == 0) {
        obj = NULL;
    }
    return obj;
}

void func_800139EC(Unk80085290* arg0) {
    func_80013B60(arg0->unk62);
    arg0->unk60 = 0x805B;
    func_800201A0(arg0, 1, 1, 2, 1, 1);
    func_8002A7C8(0x1A, 8, 0xFF);
}

void func_80013A50(s32 arg0) {
    u8* src;
    u8* dst;

    src = D_8004DF00;
    dst = D_8007B430;
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    src = D_803AB288[arg0];
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    src = D_8004DF08;
    while (*src != 0xFF) {
        *dst++ = *src++;
    }
    *dst = *src;
    D_8007B8E0 = 0xFF;
}

u8 func_80013B20(u16 arg0) {
    return D_80085988[arg0 >> 3] & D_8004F770[arg0 & 7];
}
