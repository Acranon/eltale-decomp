#include "common.h"

/*
 * Spell effect system: spell lookup, effect instances, target selection,
 * hit/status callbacks, and visual presentation.
 * Folder: src/game/magic/
 */

typedef struct {
    /* 0x00 */ u8 pad0[0x5E];
    /* 0x5E */ u16 unk5E;
} Unk80018FB0Sub;

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ Unk80018FB0Sub* unk24;
    /* 0x28 */ void* unk28;
} Unk80018FB0;

typedef struct {
    /* 0x000 */ u8 pad0[0xA];
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 unkC;
    /* 0x00E */ u8 padE[0x1E];
    /* 0x02C */ u8 unk2C[0x50];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ u8 pad7E[0xB2];
} Unk8007B908_b; // size = 0x130

extern u8 D_8007AA20[];

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk17360Model;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 timers[12];
    /* 0x0E */ u8 padE[0x78];
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u16 unk88;
    /* 0x8A */ u16 unk8A;
    /* 0x8C */ u16 unk8C;
    /* 0x8E */ u8 pad8E[2];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ f32 unk94;
} Unk17360Data;

typedef struct Actor17360 {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x28];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0xC];
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ Unk17360Model* unk64;
    /* 0x68 */ Unk17360Data* unk68;
} Actor17360;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[0x36];
} Unk80085F98; // size = 0x3C

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
} Unk80086358; // size = 0x18

typedef struct {
    /* 0x000 */ u8 pad0[0x124];
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u8 pad126[0xA];
} Unk8007B908; // size = 0x130

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
} Unk80016DE0;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u16 unkA;
} Unk80018444;

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} Unk80019024;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk17360Vec2;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} Coll17360; // size = 0x1C (Coll_ResolveFloorAndWalls's result)

/* This file's .bss, 80085F90..800863F0, in address order (first declaration fixes
 * the order). Splat's D_80085F9C, D_80086370/88/A0, D_800863BC and D_800863CC are
 * fields of D_80085F98[0], D_80086358[1..3], D_800863B8 and D_800863C8. */
s32 D_80085F90;
s32 D_80085F94;
Unk80085F98 D_80085F98[16];
Unk80086358 D_80086358[4];
Unk17360Vec2 D_800863B8;
Unk8007B908_b* D_800863C4;
Coll17360 D_800863C8;
extern u16 D_8004ED34[];
extern u16 D_8007AB18;
extern Unk8007B908 D_8007B908[];
extern u16 D_8008BE52;
typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 unk1C;
} Unk17360CamCfg;

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ struct Actor17360* target;
    /* 0x2C */ Unk17360CamCfg* cfg;
} Unk17360Cam;

typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 unk24[6];
    /* 0x2A */ u16 unk2A;
} Unk8007AA1C;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 unk6[0x3E];
} Unk800C185C; // size = 0x44

extern Unk800C185C* D_800C185C[];
extern u16 D_800C186E[];

extern Unk8007AA1C* D_8007AA1C;
extern s32 D_8007B900;
typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 unk18;
} Unk8001A3ECCfg;

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 padC[0x18];
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ u8 pad28[4];
    /* 0x2C */ Unk8001A3ECCfg* unk2C;
} Unk8001A3EC;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Unk80084300;

typedef struct {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ Unk8007AA1C* unk14;
    /* 0x18 */ u8 pad18[0x64];
    /* 0x7C */ Unk17360Model* unk7C;
    /* 0x80 */ u8 pad80[0x90];
    /* 0x110 */ u16 unk110;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u16 unk14;
} Unk8007C288;

extern s32 D_8004EDA4[];
extern u16 D_800842B8;
extern s32 D_800842BC;
extern s32 D_800842D0;
extern s32 D_800842D4;
extern s32 D_800842D8;
extern s32 D_800842DC;
extern s32 D_800842E0;
extern s32 D_800842E4;
extern Unk80084300 D_80084300;
extern s32 D_8007A998;
extern Unk8007AA08 D_8007AA08;
extern s32 D_8004DCA0;
extern s32 D_8007A174;
extern Unk8007C288* D_8007C288;
extern u8 D_8004EDB0[];
extern s32 D_8004EDBC[];
extern s32 D_8004EDEC[];
s32 Player_RollMeleeHit(s32, Actor17360*);
s32 func_8000C3FC(Actor17360*, Actor17360*);
s32 func_8000CAB8(Actor17360*);
s32 func_8000C528(s32, u16, s32, u16, s32);
void Player_TakeDamage(u16, u16, s32);
void func_80023D28(Actor17360*);
u32 func_80026E90(u32);
f32 sqrtf(f32);
void func_800271B4(f32, Unk17360Vec2*);

void Magic_ApplyEffectDamage();
void Magic_ClearActorStatuses(s32, Actor17360*);
s32 Magic_FindTargetInRange();
void func_8002373C(Actor17360*, s32, u16, s32);
void func_8002433C(Actor17360*);

void Magic_ResetEffectSystem(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80085F98[i].unk4 = 0;
    }
    for (i = 0; i < 4; i++) {
        D_80086358[i].unk0 = 0;
    }
    D_80085F90 = 0;
}

s32 Magic_LookupSpellSequence(u16 n, u8* arg1) {
    s32 grp;
    u32 i;
    Unk800C185C* rec;
    u8 t;
    u8 buf[4];
    u32 k;

    grp = arg1[0];
    for (i = 0; i != n; i++) {
        buf[i] = arg1[i];
    }
    if (n >= 3) {
        if (buf[2] < buf[1]) {
            t = buf[2];
            buf[2] = buf[1];
            buf[1] = t;
        }
    }
    rec = D_800C185C[grp];
    for (i = 15; i != 0; i--, rec++) {
        if (n == rec->unk4) {
            for (k = 0; k < rec->unk4; k++) {
                if (buf[k] != rec->unk6[k]) {
                    break;
                }
            }
            if (k == rec->unk4) {
                break;
            }
        }
    }
    if (i == 0) {
        i = 15;
    }
    return (grp << 8) - i + 15;
}

s32 Magic_GetSpellRestrictionFlags(u32 arg0, u16 arg1) {
    s32 flags = 0;
    Unk800C185C* rec;
    s32 grp = (arg0 >> 8) & 0xF;
    arg0 &= 0xFF;
    rec = &D_800C185C[grp][arg0];
    if (D_8007AA1C->unk24[grp] < rec->unk0) {
        flags = 4;
    }
    if (!(((D_8008BE52 & 1) ? 1 : 2) & rec->unk2)) {
        flags |= 2;
    }
    if (arg1 < D_800C186E[rec->unk4]) {
        flags |= 1;
    }
    return flags;
}


typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[8];
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 pad30[2];
    /* 0x32 */ u8 unk32[12];
} Unk80017F48Cfg;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[6];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0x10];
    /* 0x28 */ f32 vx;
    /* 0x2C */ f32 vy;
    /* 0x30 */ f32 vz;
} Unk80017F48Sub;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 vy;
    /* 0x20 */ f32 vz;
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ Actor17360* target;
    /* 0x2C */ Unk80017F48Cfg* cfg;
    /* 0x30 */ s16* unk30;
    /* 0x34 */ Unk80017F48Sub* unk34;
    /* 0x38 */ u8 pad38[4];
} Unk80017F48;
void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, Coll17360*);
void Camera_Shake(s32);
void Magic_CreateGroundHitPresentation();
typedef struct {
    /* 0x00 */ u8 pad0[0x22];
    /* 0x22 */ u16 unk22;
} Unk80086358Cfg;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ Unk80086358Cfg* unk10;
    /* 0x14 */ s32 unk14;
} Unk80086358_b; // size = 0x18
extern void (*D_8004ECC4[])(Unk80017F48*);
extern Actor17360* (*D_8004ECD0[])(Unk80017F48*, s32);
extern void (*D_8004ECDC[])(Unk80017F48*, Actor17360*);
extern void (*D_8004ED04[])(u8, Actor17360*);
extern s32 D_8007A1C8;
extern u8 D_800EB7C0[];
void Magic_CreateCastEffect(s32, u32, s32, u16);
void Magic_MarkActorHitBySlot(s32, Actor17360*);
s32 Magic_GetHitOutcome();
s32 Magic_ShouldApplyStatus();
void Magic_StartStatusTimer();
void func_8000CA88(Actor17360*);
void Player_StartDodge(void);
void Env_SetSlotLightAnim(s32, s32, s32, u8*);
void Magic_CreateHitPresentation();
void Magic_CreateTimedPresentation();
typedef struct {
    /* 0x00 */ f32 v[5];
} Unk8004ED68;
extern Unk8004ED68 D_8004ED68;
extern Unk8004ED68 D_8004ED7C;
typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 padC[6];
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[6];
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u8 pad28[2];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 pad32[0x12];
} Unk800169B8Def; // size = 0x44
typedef struct {
    /* 0x00 */ s16 unk0[0x24];
} Unk800169B8Def2; // size = 0x48
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk800C1878;
extern Unk800169B8Def* D_800C185C_b[];
extern Unk800169B8Def2* D_800C3268[];
extern Unk800C1878 D_800C1878[];
extern Unk8004ED68 D_8004ED54;
extern u8 D_800EB700[];
extern Unk80017F48 D_80085F98_b[];
extern void (*D_8004ECB8[])(Unk80017F48*);
extern void (*D_8004EC90[])(Unk80017F48*, Actor17360*);
void Magic_ClearSlotHitTracking(s32);
void Magic_CreateCastPresentation();
void Magic_CreateCastEffect(s32 arg0, u32 arg1, s32 arg2, u16 arg3) {
    Unk80086358_b* r;
    Unk800169B8Def2* def2;
    Unk80017F48* p;
    s32 i;
    Unk800169B8Def* def;
    s32 boost;
    Unk8004ED68 sizes;

    sizes = D_8004ED54;
    if (arg2 == 0) {
        Env_SetSlotLightAnim(D_8007A1C8, 2, 8, D_800EB700);
        D_80085F90 |= 1;
        D_80085F94 = 8;
    }
    def = &((Unk800169B8Def**)D_800C185C)[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    def2 = &D_800C3268[(arg1 >> 8) & 0xF][arg1 & 0xFF];
    if (arg2 == 0 && def->unk20 >= 2) {
        r = (Unk80086358_b*)D_80086358;
        i = 3;
        while (i != 0 && r->unk0 != 0) {
            i--;
            r++;
        }
        r->unk0 = def->unk20 - 1;
        if (arg3 & 0x10) {
            r->unk0 *= 2;
        }
        r->unk2 = def->unk22 + 1;
        r->unk4 = 0;
        r->unk8 = arg1;
        r->unkC = arg3;
        r->unk10 = (Unk80086358Cfg*)def;
        r->unk14 = arg0;
    }
    p = (Unk80017F48*)D_80085F98;
    i = 15;
    while (i != 0 && p->unk4 != 0) {
        i--;
        p++;
    }
    p->unk0 = (arg1 >> 8) & 0xF;
    p->unk2 = arg1 & 0xFF;
    p->unk24 = (Actor17360*)arg0;
    p->target = NULL;
    p->cfg = (Unk80017F48Cfg*)def;
    p->unk30 = (s16*)def2;
    p->unk4 = def->unkA;
    p->unk8 = def->unk24;
    p->unk6 = 100;
    p->unkA = arg3;
    Magic_ClearSlotHitTracking(15 - i);
    switch (def->unk12) {
        case 0:
            D_800863B8.x = D_800C1878[(def->unk2C + arg2) & 7].x * sizes.v[def->unk30];
            D_800863B8.y = D_800C1878[(def->unk2C + arg2) & 7].z * sizes.v[def->unk30];
            boost = arg3 & 0x10;
            func_800271B4(((Actor17360*)arg0)->ry, &D_800863B8);
            p->vx = D_800863B8.x;
            p->vz = D_800863B8.y;
            if (def->unk2A & 2) {
                p->vy = 0.0f;
            } else {
                p->vy = D_800C1878[(def->unk2C + arg2) & 7].y * sizes.v[def->unk30];
            }
            if (boost) {
                p->unk4 += p->unk4 >> 1;
            }
            break;
        case 1:
        case 2:
            p->vx = p->vy = p->vz = 0.0f;
            break;
    }
    D_8004ECB8[def->unk18](p);
    if (p->target != NULL) {
        D_8004EC90[def->unk26](p, (Actor17360*)arg0);
        if (def->unk14 == 2) {
            Coll_ResolveFloorAndWalls(p->x, p->y, p->z, 0xA00, &D_800863C8);
            p->y = D_800863C8.y;
        }
        Magic_CreateCastPresentation(p, p->unk24);
    } else {
        p->unk4 = 0;
    }
}

void Magic_PlaceEffectAtActorLowerPoint(Unk80016DE0* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtActorMiddlePoint(Unk80016DE0* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94;
    } else {
        arg0->y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAtActorUpperPoint(Unk17360Cam* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAheadAtMiddlePoint(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x;
    arg0->z = arg1->z + D_800863B8.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94;
    } else {
        arg0->y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
    }
}

void Magic_PlaceEffectAheadAtUpperPoint(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x;
    arg0->z = arg1->z + D_800863B8.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectBehindAtUpperPoint(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = -arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x;
    arg0->z = arg1->z + D_800863B8.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAtSelectedTarget(Unk17360Cam* arg0, Actor17360* arg1) {
    if (arg0->target != NULL) {
        arg1 = arg0->target;
    }
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else if (arg1->unk64->unk0 == 2) {
        arg0->y = arg1->y + 100.0f * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtRandomOffset(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = (f32)func_80026E90(20) + 20.0;
    func_800271B4((f32)func_80026E90(16) * 3.141592653589793 / 8.0f - 3.141592653589793, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x;
    arg0->z = arg1->z + D_800863B8.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void Magic_PlaceEffectAtDiagonalOffset(Unk17360Cam* arg0, Actor17360* arg1) {
    f32 dist;
    f32 dz;

    if (arg1->unk5E & 1) {
        dist = arg0->target->x - arg1->x;
        dz = arg0->target->z - arg1->z;
        dist = sqrtf(dist * dist + dz * dz);
    } else {
        dist = arg1->unk64->unk18 * 10.0 * arg1->scale;
    }
    D_800863B8.y = dist;
    D_800863B8.x = dist * 1.5;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x;
    arg0->z = arg1->z + D_800863B8.y;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void Magic_PlaceEffectAtFixedForwardOffset(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = 380.0f;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x * arg1->scale;
    arg0->y = arg1->y + 380.0f * arg1->scale;
    arg0->z = arg1->z + D_800863B8.y * arg1->scale;
}

void Magic_UpdateEffects(void) {
    Unk80086358_b* r;
    s32 i;
    Unk80017F48* p;
    s32 active;
    Actor17360* a;
    s32 k;
    s32 hits;
    s32 tries;

    r = (Unk80086358_b*)D_80086358;
    for (i = 4; i != 0; i--, r++) {
        if (r->unk0 != 0) {
            if (--r->unk2 == 0) {
                r->unk0--;
                r->unk4++;
                Magic_CreateCastEffect(r->unk14, r->unk8, r->unk4, r->unkC);
                r->unk2 = r->unk10->unk22 + 1;
            }
        }
    }
    p = (Unk80017F48*)D_80085F98;
    active = 0;
    for (i = 0; i != 16; i++, p++) {
        if (p->unk4 == 0) {
            continue;
        }
        active++;
        if (p->unk8 != 0) {
            p->unk8--;
        } else {
            p->unk4--;
            D_8004ECC4[p->cfg->unk12](p);
            a = D_8004ECD0[p->cfg->unk16](p, i);
            if (a != NULL) {
                Magic_MarkActorHitBySlot(i, a);
                if (!(a->unk68->unk0 & 0x100) || p->cfg->unk18 == 2) {
                    if (Magic_GetHitOutcome(p, a)) {
                        if (a == p->unk24) {
                            func_8002433C(p->unk24);
                        } else if (a->unk5E & 1) {
                            func_8000CA88(a);
                        } else {
                            Player_StartDodge();
                        }
                    } else {
                        D_8004ECDC[p->cfg->unk10](p, a);
                        hits = 0;
                        for (tries = 0, k = 0; k != 12; k++) {
                            if (p->cfg->unk32[k] != 0) {
                                tries++;
                                if (Magic_ShouldApplyStatus(p, p->unk24, k)) {
                                    Magic_StartStatusTimer(p, a, k);
                                    D_8004ED04[k](p->cfg->unk32[k], a);
                                    hits++;
                                }
                            }
                        }
                        if (p->cfg->unk10 == 5 && tries != 0 && hits == 0) {
                            func_8002433C(a);
                        }
                    }
                }
                Magic_CreateHitPresentation(p, a);
                if (!(p->cfg->unk2 & 4)) {
                    p->unk4 = 0;
                    if (p->unk34 != NULL && (p->unk34->unk8 & 1)) {
                        p->unk34->unk0 = 7;
                        p->unk34->unk8 &= ~1;
                    }
                } else {
                    p->unkA |= 2;
                }
            }
        }
        if (p->unk34 != NULL) {
            p->unk34->x = p->x;
            p->unk34->y = p->y;
            p->unk34->z = p->z;
            p->unk34->vx = p->vx;
            p->unk34->vy = p->vy;
            p->unk34->vz = p->vz;
            if (p->unk4 == 0 && (p->unk34->unk8 & 1)) {
                p->unk34->unk0 = 7;
                p->unk34->unk8 &= ~1;
            }
        }
        if (p->unk30[8] >= 0) {
            k = (u16)p->unk30[9];
            if (p->unk6 >= (u32)(k >> 8)) {
                Magic_CreateTimedPresentation(p, p->target);
                p->unk6 = 0;
            } else {
                p->unk6++;
            }
        }
    }
    if ((D_80085F90 & 1) && active == 0) {
        D_80085F90 = 2;
        D_80085F94 = 30;
    } else if (D_80085F90 & 2) {
        if (--D_80085F94 == 0) {
            D_80085F90 = 0;
            Env_SetSlotLightAnim(D_8007A1C8, 2, 8, D_800EB7C0);
        }
    }
}

s32 func_80017AB0(void) {
    s32 i;
    Unk80085F98* p;

    i = 16;
    p = D_80085F98;
    while (i != 0 && p->unk4 == 0) {
        i--;
        p++;
    }
    return i;
}

void Magic_MoveHomingEffect(Unk80017F48* arg0) {
    u16 flags;
    f32 dx;
    f32 dy;
    f32 dz;
    Actor17360* t;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 d;
    s32 pad[2];
    Unk8004ED68 speeds;
    Unk8004ED68 turns;

    speeds = D_8004ED68;
    turns = D_8004ED7C;
    flags = arg0->unkA;
    t = arg0->target;
    if (flags & 1) {
        return;
    }
    if (t != NULL) {
        if ((flags & 2) || t->unk50 == -1) {
            dz = 0.0f;
            dy = 0.0f;
            dx = 0.0f;
        } else {
            dx = t->x - arg0->x;
            if (t->unk64->unk0 == 1) {
                dy = t->unk68->unk94 - arg0->y;
            } else {
                dy = t->y + t->unk64->unk1C * t->scale * 0.5 - arg0->y;
            }
            dz = t->z - arg0->z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            dx = speeds.v[arg0->cfg->unk28] * dx / d;
            dy = speeds.v[arg0->cfg->unk28] * dy / d;
            dz = speeds.v[arg0->cfg->unk28] * dz / d;
        }
        vx = arg0->vx;
        vy = arg0->vy;
        vz = arg0->vz;
        d = sqrtf(vx * vx + vy * vy + vz * vz);
        if (d != 0.0f) {
            vx /= (f64)d;
            vy /= (f64)d;
            vz /= (f64)d;
            dx += vx;
            dy += vy;
            dz += vz;
        }
        d = sqrtf(dx * dx + dy * dy + dz * dz);
        dx = turns.v[arg0->cfg->unk2E] * dx / d;
        dy = turns.v[arg0->cfg->unk2E] * dy / d;
        dz = turns.v[arg0->cfg->unk2E] * dz / d;
        arg0->vx = arg0->vx * 0.9 + dx;
        arg0->vy = arg0->vy * 0.9 + dy;
        arg0->vz = arg0->vz * 0.9 + dz;
    }
    if (arg0->cfg->unk2A & 1) {
        arg0->vy -= 0.3;
    }
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    if (arg0->cfg->unk14 != 0) {
        Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &D_800863C8);
        switch (arg0->cfg->unk14) {
            case 1:
                if (arg0->y < D_800863C8.y) {
                    arg0->unkA |= 1;
                    arg0->unk4 = 8;
                    arg0->vz = 0.0f;
                    arg0->vy = 0.0f;
                    arg0->vx = 0.0f;
                    if (arg0->unk34 != NULL) {
                        arg0->unk34->unk0 = 15;
                        arg0->unk34->unk8 &= ~1;
                    }
                    Camera_Shake(1);
                    if (arg0->unk30[0x10] >= 0) {
                        Magic_CreateGroundHitPresentation(arg0, arg0->target);
                    }
                }
                break;
            case 2:
                arg0->y = D_800863C8.y;
                break;
        }
    }
}

void Magic_MoveVerticalEffect(Unk80017F48* arg0) {
    if (!(arg0->unkA & 1)) {
        if (arg0->cfg->unk2A & 1) {
            arg0->vy -= 0.3;
        }
        arg0->y += arg0->vy;
        if (arg0->cfg->unk14 == 1) {
            Coll_ResolveFloorAndWalls(arg0->x, arg0->y, arg0->z, 0xA00, &D_800863C8);
            if (arg0->y < D_800863C8.y) {
                arg0->y = D_800863C8.y;
                arg0->unkA |= 1;
                arg0->unk4 = 8;
                arg0->vz = 0.0f;
                arg0->vy = 0.0f;
                arg0->vx = 0.0f;
                if (arg0->unk34 != NULL) {
                    arg0->unk34->unk0 = 15;
                    arg0->unk34->unk8 &= ~1;
                }
                Camera_Shake(1);
                Magic_CreateGroundHitPresentation(arg0, arg0->target);
            }
        }
        if (arg0->cfg->unk18 == 0 && !(arg0->target->unk60 & 1)) {
            arg0->x = arg0->target->x;
            arg0->z = arg0->target->z;
        }
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0x10];
    /* 0x28 */ Actor17360* unk28;
    /* 0x2C */ Unk17360CamCfg* cfg;
} Unk8001809C;
extern f32 D_8007AA24;
extern f32 D_8007AA28;
extern f32 D_8007AA44;
extern Unk17360Model* D_8007AA84;
s32 Magic_WasActorHitBySlot(s32, Actor17360*);
s32 Magic_FindTargetInRange(arg0, arg1)
    Unk8001809C* arg0;
    s32 arg1;
{
    Actor17360* a;
    Unk8007B908_b* p;
    s32 n;
    f32 dx;
    f32 dy;
    Actor17360* ret;
    f32 dz;
    f32 dist;
    Actor17360* target;

    target = arg0->unk28;
    if (target != NULL) {
        if (!(target->unk5E & 1)) {
            ret = (Actor17360*)D_8007AA20;
            if (Magic_WasActorHitBySlot(arg1, target)) {
                ret = NULL;
            } else {
                dx = ret->x - arg0->x;
                dz = ret->z - arg0->z;
                dy = (ret->y + ret->unk64->unk1C * ret->scale * 0.5 - arg0->y) * 0.5;
                dist = sqrtf(dx * dx + dy * dy + dz * dz);
                if (arg0->cfg->unk1C + ret->unk64->unk18 * ret->scale < dist) {
                    ret = NULL;
                }
            }
        } else {
            n = D_8007B900;
            p = (Unk8007B908_b*)D_8007B908;
            while (n != 0) {
                if (p->unk7C != -1) {
                    a = (Actor17360*)p->unk2C;
                    ret = a;
                    if (!Magic_WasActorHitBySlot(arg1, a)) {
                        dx = a->x - arg0->x;
                        dz = a->z - arg0->z;
                        switch (a->unk64->unk0) {
                            default:
                                dy = 0.0f;
                                break;
                            case 0:
                                dy = (a->y + a->unk64->unk1C * a->scale * 0.5 - arg0->y) * 0.5;
                                break;
                            case 1:
                                dy = (a->unk68->unk94 - arg0->y) * 0.5;
                                break;
                        }
                        dist = sqrtf(dx * dx + dy * dy + dz * dz);
                        if (dist < arg0->cfg->unk1C + a->unk64->unk18 * a->scale) {
                            break;
                        }
                    }
                    n--;
                }
                p++;
            }
            if (n == 0) {
                ret = NULL;
            } else {
                D_800863C4 = p;
            }
        }
    } else {
        ret = NULL;
    }
    return (s32)ret;
}

typedef struct {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ Actor17360* unk28;
} Unk80018348;
s32 Magic_WasActorHitBySlot(s32, Actor17360*);
Actor17360* Magic_FindEligibleTarget(Unk80018348* arg0, s32 arg1) {
    Actor17360* ret;
    Unk8007B908_b* p;
    s32 n;

    if (!(arg0->unk28->unk5E & 1)) {
        ret = (Actor17360*)D_8007AA20;
        if (Magic_WasActorHitBySlot(arg1, (Actor17360*)D_8007AA20)) {
            ret = NULL;
        }
    } else if ((ret = arg0->unk28) == NULL || Magic_WasActorHitBySlot(arg1, ret)) {
        n = D_8007B900;
        ret = NULL;
        p = (Unk8007B908_b*)D_8007B908;
        while (n != 0) {
            if (p->unk7C != -1) {
                if (!Magic_WasActorHitBySlot(arg1, (Actor17360*)p->unk2C)) {
                    ret = (Actor17360*)p->unk2C;
                    D_800863C4 = p;
                }
                n--;
            }
            p++;
        }
    }
    return ret;
}

s32 Magic_FindTargetWhenEnabled(Unk80018444* arg0) {
    s32 ret = 0;

    if (arg0->unkA & 1) {
        ret = Magic_FindTargetInRange(arg0);
    }
    return ret;
}

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[2];
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 pad7[5];
    /* 0x0C */ u16 unkC;
} Unk80018480Cfg;
typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ u8 pad28[4];
    /* 0x2C */ Unk80018480Cfg* cfg;
} Unk80018480;
extern s32 D_8007AA10;
extern u8 D_8004F760[];
u16 Magic_CalculateEffectDamage(Unk80018480Cfg*, Actor17360*);
void func_800269B8(s32, s32, u8*);
void Magic_ApplyEffectDamage(Unk80018480* arg0, Actor17360* arg1) {
    u16 dmg;
    u16 flag;

    flag = 0;
    dmg = Magic_CalculateEffectDamage(arg0->cfg, arg0->unk24);
    if (arg0->unk24->unk68->unk0 & 1) {
        dmg >>= 1;
    }
    if (arg1->unk5E & 1) {
        if (D_8007AA10 & 0x1000) {
            if (func_80026E90((D_8007AA10 & 0x10000) ? 4 : 0x20) == 0) {
                dmg += (dmg + 1) >> 1;
                func_800269B8(4, 0, D_8004F760);
                flag = 0x4000;
            }
        }
        if (func_8000C528(func_8000CAB8(arg1), dmg, arg0->cfg->unk6, arg0->cfg->unk2 | flag, (s32)arg0->unk24) != 0) {
            D_8007AA1C->unk2A++;
        }
    } else {
        if (func_80026E90(0x20) == 0) {
            dmg += (dmg + 1) >> 1;
            func_800269B8(4, 0, D_8004F760);
            flag = 0x4000;
        }
        Player_TakeDamage(dmg, arg0->cfg->unk2 | flag, (s32)arg0->unk24);
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ u16 unkA;
} Unk8001860CRec;
void func_8001AE24(Actor17360*, s32, s32);
void Magic_HealTarget(Unk80018480* arg0, Actor17360* arg1) {
    u16 amt;
    s32 pad;

    if (arg1->unk5E & 1) {
        D_800863C4 = (Unk8007B908_b*)&D_8007B908[func_8000CAB8(arg1)];
        amt = arg1->unk64->unk6 * arg0->cfg->unkC / 100;
        amt += func_80026E90(amt >> 2);
        ((Unk8001860CRec*)D_800863C4)->unkA += amt;
        if (((Unk8001860CRec*)D_800863C4)->unkA > arg1->unk64->unk6) {
            ((Unk8001860CRec*)D_800863C4)->unkA = arg1->unk64->unk6;
        }
    } else {
        amt = (D_8007AA1C->unk24[arg0->cfg->unk6] >> 1) + arg1->unk64->unk6 * arg0->cfg->unkC / 100;
        amt += func_80026E90(amt >> 2);
        if (arg1->unk64->unk4 != arg1->unk64->unk6) {
            arg1->unk64->unk4 += amt;
            if (arg1->unk64->unk4 > arg1->unk64->unk6) {
                arg1->unk64->unk4 = arg1->unk64->unk6;
            }
            D_8007AA1C->unk2A++;
        }
    }
    func_8001AE24(arg1, 1, amt);
}

void Magic_TransferTargetResource(Unk80018480* arg0, Actor17360* arg1) {
    u16 amt;
    Actor17360* pl;

    pl = (Actor17360*)D_8007AA20;
    if (arg1->unk5E & 1) {
        D_800863C4 = (Unk8007B908_b*)&D_8007B908[func_8000CAB8(arg1)];
        amt = (D_800863C4->unkC * 11 + 63) >> 6;
        D_800863C4->unkC -= amt;
        if (D_8007AA08.unk7C->unk8 != D_8007AA08.unk7C->unkA) {
            pl->unk64->unk8 += amt;
            if (pl->unk64->unk8 > pl->unk64->unkA) {
                pl->unk64->unk8 = pl->unk64->unkA;
            }
            D_8007AA08.unk14->unk2A++;
        }
    } else {
        amt = (arg1->unk64->unk8 * 11 + 63) >> 6;
        arg1->unk64->unk8 -= amt;
        D_800863C4 = (Unk8007B908_b*)&D_8007B908[func_8000CAB8(arg1)];
        D_800863C4->unkC += amt;
        if (D_800863C4->unkC > arg0->unk24->unk64->unkA) {
            D_800863C4->unkC = arg0->unk24->unk64->unkA;
        }
    }
    func_8001AE24(arg1, 1, amt);
}

void func_80018968(s32 arg0, Actor17360* arg1) {
    if (arg1->unk5E & 1) {
        arg1->unk50 = -1;
        D_8007B900--;
    } else if (!(D_8008BE52 & 0x100)) {
        D_8008BE52 |= 0x10;
        D_8007AA1C->unk2A++;
    } else {
        func_8002433C(arg1);
    }
}

void func_800189F0(s32 arg0, Actor17360* arg1) {
    if (D_800842B8 == 4 && D_800842D0 != -1 && !(D_8007C288->unk14 & 4)) {
        D_80084300.unk0 = D_800842D0;
        D_80084300.unk4 = D_800842D4;
        D_80084300.unk8 = D_800842D8;
        D_8007A998 = 0x108;
        D_8007AA08.unk6 = 0;
        D_8007AA08.unk14->unk2A++;
        D_8004DCA0 |= 0x80;
        D_8007A174 = 0x1E;
    }
}

void Magic_ApplyZeroDamageHit(Unk17360Cam* arg0, Actor17360* arg1) {
    if (arg0->cfg->unk18 != 2) {
        if (arg1->unk5E & 1) {
            func_8000C528(func_8000CAB8(arg1), 0, 0, 4, arg0->unk24);
            D_8007AA1C->unk2A++;
        } else {
            Player_TakeDamage(0, 4, arg0->unk24);
        }
    }
}

void func_80018B40(s32 arg0, Actor17360* arg1) {
    if ((D_800842B8 & 8) && D_800842DC != -1 && !(D_8007C288->unk14 & 8) && D_800842BC != 0x1E &&
        D_800842BC != 0x22) {
        D_80084300.unk0 = D_800842DC;
        D_80084300.unk4 = D_800842E0;
        D_80084300.unk8 = D_800842E4;
        D_8007A998 = 0x108;
        D_8007AA08.unk6 = 0;
        D_8007AA08.unk14->unk2A++;
        D_8004DCA0 |= 0x80;
        D_8007A174 = 0x1E;
    }
}

void Magic_RemoveEnemyOrDamagePlayer(Unk17360Cam* arg0, Actor17360* arg1) {
    if (arg1->unk5E & 1) {
        if (!(D_8008BE52 & 0x100)) {
            func_80023D28(arg1);
            arg1->unk50 = -1;
            arg1->unk60 &= ~1;
            D_8007B900--;
            D_8007AA1C->unk2A++;
        } else {
            func_8002433C(arg1);
        }
    } else {
        Player_TakeDamage(arg1->unk64->unk4 * 4, 4, arg0->unk24);
    }
}

void Magic_ClearActorStatuses(s32 arg0, Actor17360* arg1) {
    if (arg1->unk68->unk0 != 0) {
        arg1->unk68->unk0 = 0;
        if (arg1->unk5E & 1) {
            func_8000CAB8(arg1);
        }
        arg1->unk68->unk8A = 0x10;
        arg1->unk68->unk88 = arg1->unk64->unkE;
        arg1->unk68->unk86 = arg1->unk64->unkC;
        arg1->unk68->unk90 = 1.0f;
        if (!(arg1->unk5E & 1)) {
            D_8007AA1C->unk2A++;
        }
    }
}

void Magic_DamageAndClearStatuses(s32 arg0, Actor17360* arg1) {
    Magic_ApplyEffectDamage((void*)arg0, arg1);
    Magic_ClearActorStatuses(arg0, arg1);
}

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ f32 x;
    /* 0x30 */ f32 y;
    /* 0x34 */ f32 z;
    /* 0x38 */ u8 pad38[0x44];
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ u8 pad7E[0xB2];
} Unk80018DC0Rec; // size = 0x130
typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 unk2;
} Unk80018DC0Cfg;
typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ void* unk28;
    /* 0x2C */ Unk80018DC0Cfg* cfg;
} Unk80018DC0;
f32 func_800270D0(f32, f32);
void Magic_SelectClosestAimTarget(Unk80018DC0* arg0) {
    f32 angle;
    f32 best;
    f32 d;
    s32 n;
    Unk80018DC0Rec* p;
    Actor17360* caster;

    caster = arg0->unk24;
    if (caster->unk5E & 1) {
        arg0->unk28 = D_8007AA20;
        return;
    }
    if ((arg0->cfg->unk2 & 8) && (arg0->unk18 != 0.0f || arg0->unk20 != 0.0f)) {
        angle = func_800270D0(arg0->unk18, arg0->unk20);
    } else {
        angle = caster->ry;
    }
    caster = arg0->unk24;
    best = 9.424778f;
    n = D_8007B900;
    p = (Unk80018DC0Rec*)D_8007B908;
    while (n != 0) {
        if (p->unk7C != -1) {
            D_800863B8.x = p->x - caster->x;
            D_800863B8.y = p->z - caster->z;
            func_800271B4(angle, &D_800863B8);
            d = func_800270D0(D_800863B8.x, D_800863B8.y);
            if (d > 3.141592653589793) {
                d -= 6.283185307179586;
            } else if (d < -3.141592653589793) {
                d += 6.283185307179586;
            }
            if (d < 0.0f) {
                d = -d;
            }
            if (d < best) {
                best = d;
                arg0->unk28 = &p->x;
            }
            n--;
        }
        p++;
    }
}

void Magic_SelectFirstActiveTarget(Unk80018FB0* arg0) {
    s32 i;
    Unk8007B908_b* p;

    if (arg0->unk24->unk5E & 1) {
        arg0->unk28 = D_8007AA20;
        return;
    }
    p = (Unk8007B908_b*)D_8007B908;
    i = 6;
    while (i != 0 && p->unk7C == -1) {
        i--;
        p++;
    }
    if (i != 0) {
        arg0->unk28 = p->unk2C;
        return;
    }
    arg0->unk28 = NULL;
}

void Magic_TargetCaster(Unk80019024* arg0) {
    arg0->unk28 = arg0->unk24;
}

void Magic_ApplyShrinkStatus(s32 arg0, Actor17360* arg1) {
    if (!(D_8008BE52 & 0x100)) {
        arg1->unk68->unk0 |= 1;
        arg1->scale = arg1->unk64->unk20 * 0.5;
        func_8002373C(arg1, 1, 4, -1);
    } else {
        func_8002433C(arg1);
    }
}

void func_800190BC(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 2;
    func_8002373C(arg1, 2, 2, -1);
}

void func_80019104(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 4;
    switch (arg0) {
        case 1:
            arg1->unk68->unk8A = 0x18;
            break;
        case 2:
            arg1->unk68->unk8A = 0x20;
            break;
    }
    func_8002373C(arg1, 4, 3, -1);
}

void func_80019184(s32 arg0, Actor17360* arg1) {
    if (!(D_8008BE52 & 0x100)) {
        arg1->unk68->unk0 |= 8;
        arg1->unk60 |= 1;
        func_8002373C(arg1, 8, arg0 - 1, -1);
    } else {
        func_8002433C(arg1);
    }
}

void func_8001920C(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x10;
    switch (arg0) {
        case 1:
            arg1->unk68->unk90 = 0.5f;
            break;
        case 2:
            arg1->unk68->unk90 = 2.0f;
            break;
    }
    func_8002373C(arg1, 0x10, (arg1->unk68->unk90 > 1.0) ? 8 : 9, -1);
}

void func_800192C8(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x20;
    switch (arg0) {
        case 1:
            arg1->unk68->unk86 = arg1->unk64->unkC * 2;
            func_8002373C(arg1, 0x20, 7, -1);
            break;
        case 2:
            arg1->unk68->unk86 = arg1->unk64->unkC * 4;
            func_8002373C(arg1, 0x20, 7, -1);
            break;
        case 3:
            arg1->unk68->unk86 = arg1->unk64->unkC >> 1;
            func_8002373C(arg1, 0x20, 0xC, -1);
            break;
    }
}

void func_800193A4(s32 arg0, Actor17360* arg1) {
    if (!(D_8008BE52 & 0x100)) {
        arg1->unk68->unk0 |= 0x40;
        func_8002373C(arg1, 0x40, 0xB, -1);
    } else {
        func_8002433C(arg1);
    }
}

void func_80019408(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x80;
    func_8002373C(arg1, 0x80, 0xA, -1);
}

void func_80019450(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x100;
    func_8002373C(arg1, 0x100, 4, -1);
}

void func_80019498(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x200;
    func_8002373C(arg1, 0x200, 3, -1);
}

void func_800194E0(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x400;
    switch (arg0) {
        case 1:
            arg1->unk68->unk88 = arg1->unk64->unkE >> 1;
            break;
        case 2:
            arg1->unk68->unk88 = arg1->unk64->unkE - (arg1->unk64->unkE >> 2);
            break;
        case 3:
            arg1->unk68->unk88 = arg1->unk64->unkE + (arg1->unk64->unkE >> 1);
            break;
        case 4:
            arg1->unk68->unk88 = arg1->unk64->unkE * 2;
            break;
    }
    func_8002373C(arg1, 0x400, (arg1->unk64->unkE < arg1->unk68->unk88) ? 5 : 6, -1);
}

void func_800195E0(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x800;
}

typedef struct {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
} Unk800195FCStats;
typedef struct {
    /* 0x000 */ u8 pad0[0x28];
    /* 0x028 */ Unk800195FCStats* unk28;
    /* 0x02C */ u8 pad2C[0x104];
} Unk800195FCRec; // size = 0x130
typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 stats[1];
} Unk8007A9D0;
extern u16 D_8004ED90[];
extern Unk8007A9D0 D_8007A9D0;
u16 Magic_CalculateEffectDamage(Unk80018480Cfg* arg0, Actor17360* arg1) {
    u16 lv;
    u16* p;
    f32 sum;
    f32 step;
    s32 i;

    if (arg1->unk5E & 1) {
        lv = ((Unk800195FCRec*)D_8007B908)[func_8000CAB8(arg1)].unk28->unk2A;
    } else {
        p = &D_8004ED90[arg0->unk6 * 2];
        lv = D_8007A9D0.stats[arg0->unk6];
        lv += D_8007A9D0.stats[*p++] >> 4;
        lv += D_8007A9D0.stats[*p++] >> 3;
        lv += D_8007A9D0.stats[*p] >> 3;
    }
    sum = arg0->unkC * 0.02;
    step = sum * 0.2;
    for (i = 0; i != lv; i++) {
        sum += step;
        step *= 1.03;
    }
    return (u32)sum;
}

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x26];
    /* 0x46 */ s8 unk46;
    /* 0x47 */ u8 unk47;
} Unk80019BFCDef;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ Actor17360* unk28;
    /* 0x2C */ Unk17360CamCfg* cfg;
    /* 0x30 */ Unk80019BFCDef* def;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ struct Unk80019BFCRet* unk38;
} Unk80019BFC;
typedef struct Unk80019BFCRet {
    /* 0x00 */ u8 pad0[0x28];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} Unk80019BFCRet;
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ f32 unk10;
} Unk80019BFCArg1;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
} Unk800C18D8; // size = 0xA
extern Unk800C18D8 D_800C18D8[];
Unk80019BFCRet* Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, Unk800C18D8*, Unk17360Vec2*, Actor17360*);
void func_8002A7C8(u8, s8, s32);


Unk80019BFCRet* func_8001C818(u16, u16, u16, s32, u16, f32, f32, f32, f32, f32, f32, f32);
Unk80019BFCRet* Magic_CreateVisualEffect(u16 arg0, u16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Unk800C18D8* arg6, Unk17360Vec2* arg7, Actor17360* arg8) {
    f32 sx;
    f32 sy;

    switch (arg6->unk0) {
        case 0:
            sx = arg8->unk64->unk18 * arg8->scale * arg7->x;
            break;
        case 1:
            sx = arg8->unk64->unk1C * arg8->scale * arg7->x;
            break;
        case 3:
            sx = arg7->z * arg7->x;
            break;
        default:
            do {} while (0);
            sx = arg7->x;
            break;
    }
    switch (arg6->unk2) {
        case 0:
            sy = arg8->unk64->unk18 * arg8->scale * arg7->y;
            break;
        case 1:
            sy = arg8->unk64->unk1C * arg8->scale * arg7->y;
            break;
        case 3:
            sy = arg7->z * arg7->y;
            break;
        default:
            do {} while (0);
            sy = arg7->y;
            break;
    }
    return func_8001C818(arg6->unk8, arg6->unk4, arg6->unk6, arg0 & 0xFF, arg1, arg2, arg3, arg4, arg5, sx, sy, sx);
}

typedef struct {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[0x14];
    /* 0x44 */ s8 unk44;
    /* 0x45 */ u8 unk45;
} Unk80019FC8Def;
typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[4];
} Unk800C363C; // size = 0xC
extern Unk800C363C* D_800C363C[];
void func_8001B3FC(s32, s32, f32, f32, f32, f32);
void func_8001B7E0(s32, f32, f32, f32, f32);
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x30];
    /* 0x40 */ s8 unk40;
    /* 0x41 */ u8 unk41;
} Unk800199C0Def;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ Actor17360* unk24;
    /* 0x28 */ Actor17360* unk28;
    /* 0x2C */ Unk17360CamCfg* cfg;
    /* 0x30 */ Unk800199C0Def* def;
    /* 0x34 */ struct Unk80019BFCRet* unk34;
} Unk800199C0;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[8];
} Unk800C363C_c; // size = 0xC
f32 func_800270D0(f32, f32);
void Magic_CreateCastPresentation(Unk800199C0* arg0, Actor17360* arg1) {
    Unk80019BFCRet* ret;
    Unk17360CamCfg* cfg;
    Unk800C363C_c* fx;
    f32 h;
    Unk800199C0Def* def;
    Unk800C18D8* tbl;
    f32 y;
    f32 angle;

    def = arg0->def;
    cfg = arg0->cfg;
    if (def->unk0 >= 0) {
        tbl = &D_800C18D8[def->unk0];
        D_800863B8.x = def->unk8;
        D_800863B8.y = def->unkC;
        D_800863B8.z = cfg->unk1C;
        if (arg0->unk18 != 0.0f || arg0->unk20 != 0.0f) {
            angle = func_800270D0(arg0->unk18, arg0->unk20);
        } else {
            angle = arg1->ry;
        }
        arg0->unk34 = Magic_CreateVisualEffect(def->unk2, def->unk4, arg0->x, arg0->y, arg0->z, angle, tbl, &D_800863B8, arg1);
        arg0->unk34->unk28 = arg0->unk18;
        arg0->unk34->unk2C = arg0->unk1C;
        arg0->unk34->unk30 = arg0->unk20;
    } else {
        arg0->unk34 = NULL;
    }
    fx = &((Unk800C363C_c**)D_800C363C)[arg0->unk0][arg0->unk2];
    if (fx->unk0 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->scale;
        y = arg1->y + arg1->unk64->unk1C * arg1->scale;
        switch (fx->unk0) {
            case 1:
                func_8001B3FC(fx->unk2, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                func_8001B7E0(fx->unk2, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk40 >= 0) {
        func_8002A7C8(def->unk41, def->unk40, 0xFF);
    }
}

void Magic_CreateTimedPresentation(Unk80019BFC* arg0, Unk80019BFCArg1* arg1) {
    Unk80019BFCRet* ret;
    Unk17360CamCfg* cfg;
    Unk80019BFCDef* def;
    Unk800C18D8* tbl;
    f32 angle;

    def = arg0->def;
    cfg = arg0->cfg;
    tbl = &D_800C18D8[def->unk10];
    D_800863B8.x = def->unk18;
    D_800863B8.y = def->unk1C;
    D_800863B8.z = cfg->unk1C;
    if (def->unk14 & 0x10) {
        angle = arg0->unk4 * 3.141592653589793 / 10.0;
    } else {
        angle = arg1->unk10;
    }
    ret = Magic_CreateVisualEffect(def->unk12, def->unk14, arg0->x, arg0->y, arg0->z, angle, tbl, &D_800863B8, arg0->unk24);
    ret->unk28 = arg0->unk18;
    ret->unk2C = arg0->unk1C;
    ret->unk30 = arg0->unk20;
    if (def->unk46 >= 0) {
        func_8002A7C8(def->unk47, def->unk46, 0xFF);
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8 pad36[2];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[2];
    /* 0x42 */ s8 unk42;
    /* 0x43 */ u8 unk43;
} Unk80019D2CDef;
typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
} Unk800C363C_b; // size = 0xC
void Magic_CreateHitPresentation(Unk80019BFC* arg0, Actor17360* arg1) {
    Unk17360CamCfg* cfg;
    Unk800C18D8* tbl;
    Unk800C363C_b* fx;
    Unk80019D2CDef* def;
    u16 flags;
    f32 y;
    f32 h;
    s32 pad[2];

    def = (Unk80019D2CDef*)arg0->def;
    cfg = arg0->cfg;
    if (def->unk30 >= 0) {
        tbl = &D_800C18D8[def->unk30];
        D_800863B8.x = def->unk38;
        D_800863B8.y = def->unk3C;
        D_800863B8.z = cfg->unk1C;
        flags = def->unk34;
        if (flags & 0x40) {
            arg1 = arg0->unk24;
        }
        if (arg1->unk64->unk0 == 1) {
            if (flags & 0x100) {
                y = arg1->unk68->unk94;
            } else {
                y = arg1->y;
            }
        } else if (flags & 0x100) {
            y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
        } else {
            y = arg1->y;
        }
        arg0->unk38 = Magic_CreateVisualEffect(def->unk32, flags, arg1->x, y, arg1->z, arg1->ry, tbl, &D_800863B8, arg1);
        arg0->unk38->unk28 = arg0->unk18;
        arg0->unk38->unk2C = arg0->unk1C;
        arg0->unk38->unk30 = arg0->unk20;
    } else {
        arg0->unk38 = NULL;
    }
    fx = &((Unk800C363C_b**)D_800C363C)[arg0->unk0][arg0->unk2];
    if (fx->unk8 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->unk64->unk20;
        y = arg1->y + arg1->unk64->unk1C * arg1->unk64->unk20;
        switch (fx->unk8) {
            case 1:
                func_8001B3FC(fx->unkA, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                func_8001B7E0(fx->unkA, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk42 >= 0) {
        func_8002A7C8(def->unk43, def->unk42, 0xFF);
    } else if (arg0->unk24 != arg0->unk28) {
        func_8002A7C8(0, 0x18, 0xFF);
    }
}

void Magic_CreateGroundHitPresentation(Unk80019BFC* arg0, Actor17360* arg1) {
    Unk80019BFCRet* ret;
    Unk17360CamCfg* cfg;
    Unk800C363C* fx;
    Unk80019FC8Def* def;
    f32 h;
    f32 y;
    Unk800C18D8* tbl;

    def = (Unk80019FC8Def*)arg0->def;
    cfg = arg0->cfg;
    if (def->unk20 >= 0) {
        tbl = &D_800C18D8[def->unk20];
        D_800863B8.x = def->unk28;
        D_800863B8.y = def->unk2C;
        D_800863B8.z = cfg->unk1C;
        ret = Magic_CreateVisualEffect(def->unk22, def->unk24, arg0->x, arg0->y, arg0->z, arg1->ry, tbl, &D_800863B8, arg0->unk24);
        ret->unk28 = arg0->unk18;
        ret->unk2C = arg0->unk1C;
        ret->unk30 = arg0->unk20;
    }
    fx = &D_800C363C[arg0->unk0][arg0->unk2];
    if (fx->unk4 != 0) {
        h = 2.0 * arg1->unk64->unk18 * arg1->scale;
        y = arg1->y + arg1->unk64->unk1C * arg1->scale;
        switch (fx->unk4) {
            case 1:
                func_8001B3FC(fx->unk6, 30, arg1->x, y, arg1->z, h * 1.2);
                break;
            case 2:
                func_8001B7E0(fx->unk6, arg1->x, y, arg1->z, h * 0.2);
                break;
        }
    }
    if (def->unk44 >= 0) {
        func_8002A7C8(def->unk45, def->unk44, 0xFF);
    }
}

void Magic_TickActorStatuses(Actor17360* arg0) {
    Unk17360Data* data = arg0->unk68;
    s32 bit = 1;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (data->unk0 & bit) {
            if (--data->timers[i] == 0) {
                data->unk0 ^= bit;
                if (bit & 1) {
                    arg0->scale = arg0->unk64->unk20;
                } else if (bit & 4) {
                    arg0->unk68->unk8A = 0x10;
                } else if (bit & 0x10) {
                    arg0->unk68->unk90 = 1.0f;
                } else if (bit & 0x20) {
                    arg0->unk68->unk86 = arg0->unk64->unkC;
                } else if (bit & 0x400) {
                    arg0->unk68->unk88 = arg0->unk64->unkE;
                } else if (bit & 8) {
                    arg0->unk60 &= ~1;
                }
            }
        }
        bit <<= 1;
    }
}

s32 Magic_WasActorHitBySlot(s32 arg0, Actor17360* arg1) {
    return D_8004ED34[arg0] & arg1->unk68->unk8C;
}

void Magic_MarkActorHitBySlot(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk8C |= D_8004ED34[arg0];
}

void Magic_ResetHitTracking(void) {
    s32 i;

    D_8007AB18 = 0;
    for (i = 0; i < 6; i++) {
        D_8007B908[i].unk124 = 0;
    }
}

void Magic_ClearSlotHitTracking(s32 arg0) {
    s32 i;

    D_8007AA08.unk110 &= ~D_8004ED34[arg0];
    for (i = 0; i < 6; i++) {
        D_8007B908[i].unk124 &= ~D_8004ED34[arg0];
    }
}

s32 Magic_GetHitOutcome(Unk8001A3EC* arg0, Actor17360* arg1) {
    s32 ret;

    if (arg0->unkA & 4) {
        ret = 2;
    } else {
        ret = func_80026E90(100) < arg0->unk2C->unkE;
        if (ret != 0) {
            if (arg1 != arg0->unk24) {
                if (arg1->unk5E & 1) {
                    ret = Player_RollMeleeHit(func_8000CAB8(arg1), arg0->unk24);
                } else {
                    ret = func_8000C3FC(arg0->unk24, arg1);
                }
            }
            ret++;
        }
    }
    return D_8004EDA4[ret];
}

s32 Magic_ShouldApplyStatus(Unk8001A3EC* arg0, Actor17360* arg1, s32 arg2) {
    s32 ret;
    s32 n;
    Unk8001A3ECCfg* cfg;

    if (arg0->unkA & 4) {
        ret = 1;
    } else if (cfg = arg0->unk2C, cfg->unk18 == 2) {
        ret = 1;
    } else if (arg1->unk5E & 1) {
        ret = func_80026E90(64) < D_8004EDB0[arg2];
    } else {
        n = (D_8007AA08.unk8 & 0x8000) ? 28 : 32;
        ret = func_80026E90(n) < D_8004EDB0[arg2];
    }
    return ret;
}

void Magic_StartStatusTimer(Unk8001A3EC* arg0, Actor17360* arg1, s32 arg2) {
    if (arg1 != arg0->unk24) {
        arg1->unk68->timers[arg2] = func_80026E90(D_8004EDBC[arg2]) + 2;
    } else {
        arg1->unk68->timers[arg2] = func_80026E90(D_8004EDEC[arg2]) + 3;
    }
}

/* .data 8004EC90..8004EE20: the state tables, after the functions they point to. */
typedef void (*FnEC90)(Unk80017F48*, Actor17360*);
typedef void (*FnECB8)(Unk80017F48*);
typedef void (*FnECC4)(Unk80017F48*);
typedef Actor17360* (*FnECD0)(Unk80017F48*, s32);
typedef void (*FnECDC)(Unk80017F48*, Actor17360*);
typedef void (*FnED04)(u8, Actor17360*);
FnEC90 D_8004EC90[10] = {
    (FnEC90) Magic_PlaceEffectAtActorLowerPoint,
    (FnEC90) Magic_PlaceEffectAtActorMiddlePoint,
    (FnEC90) Magic_PlaceEffectAtActorUpperPoint,
    (FnEC90) Magic_PlaceEffectAheadAtMiddlePoint,
    (FnEC90) Magic_PlaceEffectAheadAtUpperPoint,
    (FnEC90) Magic_PlaceEffectBehindAtUpperPoint,
    (FnEC90) Magic_PlaceEffectAtSelectedTarget,
    (FnEC90) Magic_PlaceEffectAtRandomOffset,
    (FnEC90) Magic_PlaceEffectAtDiagonalOffset,
    (FnEC90) Magic_PlaceEffectAtFixedForwardOffset,
};
FnECB8 D_8004ECB8[3] = {
    (FnECB8) Magic_SelectClosestAimTarget,
    (FnECB8) Magic_SelectFirstActiveTarget,
    (FnECB8) Magic_TargetCaster,
};
FnECC4 D_8004ECC4[3] = {
    (FnECC4) Magic_MoveHomingEffect,
    (FnECC4) Magic_MoveVerticalEffect,
    (FnECC4) Magic_MoveVerticalEffect,
};
FnECD0 D_8004ECD0[3] = {
    (FnECD0) Magic_FindTargetInRange,
    (FnECD0) Magic_FindEligibleTarget,
    (FnECD0) Magic_FindTargetWhenEnabled,
};
FnECDC D_8004ECDC[10] = {
    (FnECDC) Magic_ApplyEffectDamage,
    (FnECDC) Magic_HealTarget,
    (FnECDC) Magic_TransferTargetResource,
    (FnECDC) func_80018968,
    (FnECDC) func_800189F0,
    (FnECDC) Magic_ApplyZeroDamageHit,
    (FnECDC) func_80018B40,
    (FnECDC) Magic_RemoveEnemyOrDamagePlayer,
    (FnECDC) Magic_ClearActorStatuses,
    (FnECDC) Magic_DamageAndClearStatuses,
};
FnED04 D_8004ED04[12] = {
    (FnED04) Magic_ApplyShrinkStatus,
    (FnED04) func_800190BC,
    (FnED04) func_80019104,
    (FnED04) func_80019184,
    (FnED04) func_8001920C,
    (FnED04) func_800192C8,
    (FnED04) func_800193A4,
    (FnED04) func_80019408,
    (FnED04) func_80019450,
    (FnED04) func_80019498,
    (FnED04) func_800194E0,
    (FnED04) func_800195E0,
};
u16 D_8004ED34[16] = {
    0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
};
Unk8004ED68 D_8004ED54 = { { 2.0f, 3.0f, 4.0f, 6.0f, 7.0f } };
Unk8004ED68 D_8004ED68 = { { 0.0f, 1.0f, 2.0f, 10.0f, 10.0f } };
Unk8004ED68 D_8004ED7C = { { 0.4f, 0.5f, 0.7f, 1.0f, 1.2f } };
u16 D_8004ED90[10] = { 2, 1, 3, 2, 0, 3, 1, 0, 2, 0 };
s32 D_8004EDA4[3] = { 1, 2, 0 };
u8 D_8004EDB0[12] = { 24, 24, 24, 16, 24, 24, 16, 24, 24, 24, 24, 24 };
s32 D_8004EDBC[12] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
s32 D_8004EDEC[12] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
