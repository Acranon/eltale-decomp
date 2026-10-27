#include "common.h"

/*
 * Battle enemies (6 slots, D_8007B908): load the area's enemy set, spawn, per-frame
 * state machine (idle, approach, hurt/death, attack, spell), turn order, movement and
 * collision inside the battle circle, hit/damage rolls both ways, boss attack scripts.
 * Folder: src/game/enemy/   (proposed for round 4)
 */

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
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

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

/* This file's .bss, 8007B900..8007C0B0, in address order. D_8007B904 and
 * D_8007C09C/D_8007C0A0 are unreferenced gaps. Splat's labels inside the enemy
 * table (D_8007B918..D_8007BB5C, fields of D_8007B908[0] and [1]) and D_8007C074
 * (D_8007C070.y) are aliases in undefined_syms.txt. Enemy_StartAttackScript treats
 * D_8007C060..D_8007C06C as one Unk8007C060; they are kept as the scalars the
 * other functions use. */
s32 D_8007B900;
s32 D_8007B904;
Enemy D_8007B908[6];
Enemy *D_8007C028;
s32 D_8007C02C;
Obj *D_8007C030[6];
u8 **D_8007C048;
s32 D_8007C04C;
u16 D_8007C050[6];
Unk800561A0 *D_8007C05C;
u16 D_8007C060;
SpawnScript *D_8007C064;
Enemy *D_8007C068;
Obj *D_8007C06C;
Vec3f D_8007C070;
CollResult D_8007C080;
s32 D_8007C09C;
s32 D_8007C0A0[4];

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


void Coll_ResolveFloorAndWalls(f32, f32, f32, s32, CollResult *);

void Enemy_LoadAreaSet(void);
Unk8000BA20 *Enemy_ChooseAttack(Enemy *, Obj *);
void Enemy_StartAttack(Enemy *, Obj *, Unk8000BA20 *);
extern s16 D_8008C162;
void Anim_DrawModel(s32, Obj *, u8 *, s32);
void Anim_AdvanceFrame(s32, Obj *, u8 *);
void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
extern Gfx *D_8007A184;
void Enemy_StartAttackScript(s32, s32);
f32 Math_Atan2(f32, f32);
void Anim_SetCurrentAndNext(Obj *, s32, s32, s32, s32, u16);
void Camera_StartBattleFocus(s32, Obj *);
void Enemy_TurnToward(Obj *, f32, f32);
void Enemy_Move(s32, f32, f32, Obj *, EnemyAI *);
void Enemy_GetAnimStep(Obj *, Vec3f *);
void Enemy_SpawnDeathEffects(Obj *);
void Enemy_RunAttackScript(void);
void Magic_CreateVisualEffect(u16, u16, f32, f32, f32, f32, Unk800C18D8 *, Vec3f *, Obj *);
void Effect_StartBurstEmitter(s32, s32, f32, f32, f32, f32);
void Battle_EndTurn(Obj *);
void Anim_UpdateRootMotion(Obj *, u8 *, f32, Vec3f *);
void Hud_ClearActorStatusIndicators(Obj *);
void Hud_ShowActorPopup(void);
void Fade_Start(s32, u16, void *);
u32 Math_Rand(u32);
void Math_RotateVec2(f32, Vec3f *);
void Dma_ReadRom();
void Sfx_Play(u8, s8, u8);
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
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x24];
} Unk800C185C; /* size 0x44 */

extern Unk80056718 D_80056718;
extern u16 D_8005685A;
extern u16 D_8005685C;
extern Unk800C185C *D_800C185C[];
extern f32 D_8007AA20;
extern f32 D_8007AA24;
extern f32 D_8007AA28;
extern f32 D_8007B928;
extern f32 D_8007B92C;
void Camera_Shake(s32);
void Enemy_ResolveCollisions(f32 *, f32 *, Obj *);
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

void Magic_CreateCastEffect(Obj *, s32, s32, s32);
s32 Enemy_RollHitOnPlayer(Obj *obj);
u16 Enemy_CalcAttackDamage(Enemy *arg0);
s32 Player_TakeDamage(u16, s32, Obj *);
void Effect_SpawnStreakBurst(f32, f32, f32);
void Effect_AddFloatingNumber(Obj *, s32, s32);
void Hud_StartActorStatusIndicator(Obj *, u16, u16, s16);
void Player_StartDodge(void);
extern f32 D_8007C074;
extern s32 D_8007A9B4;
extern s32 D_8007A9B8;
extern Unk8007AA08 D_8007AA08;
extern EnemyStats *D_8007AA88;
extern Unk8007C288 *D_8007C288;
extern u16 D_800842E8;
extern u16 D_8008BE52;
extern u16 D_8008BE58;
extern Unk800C18D8 D_800C18D8[];
extern u8 D_8020E6F0[];

void Enemy_InitForArea(void) {
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
        Enemy_LoadAreaSet();
    }
}

void Enemy_UpdateAll(void) {
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
        Enemy_RunAttackScript();
    }
}

void Enemy_DrawAll(s32 arg0) {
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
            Anim_DrawModel(1, obj, &anims[obj->unk52 * 12], arg0);
            Anim_AdvanceFrame(obj->unk58, obj, &anims[obj->unk52 * 12]);
            obj->y = y;
            if (obj->unk64->unk0 != 2 && !(obj->unk62 & 0x8000)) {
                Shadow_Queue(obj->x, obj->y, obj->z, obj->unk2C, obj->unk30, obj->unk34, obj->unk28 * obj->unk24);
            }
            *list++ = obj;
            n--;
            D_8007C02C++;
        }
        e++;
    }
}

void Enemy_LoadAreaSet(void) {
    u32 start;
    u32 end;

    D_8007C05C = &D_800561A0[D_8007C288->unk12];
    D_8007C048 = D_8007C05C->unk8;
    D_8007C04C = D_8007C05C->unk10;
    start = D_8007C05C->start;
    end = D_8007C05C->end;
    Dma_ReadRom(start, D_8020E6F0, end - start, &D_8007C05C);
}

void Enemy_RemoveAll(void) {
    Enemy *e;
    s32 i;
    Obj *obj;

    for (e = D_8007B908, i = 6; i != 0; i--, e++) {
        obj = &e->obj;
        if (e->obj.unk50 != -1) {
            Hud_ClearActorStatusIndicators(obj);
            obj->unk50 = -1;
        }
    }
    D_8007B900 = 0;
}

void Enemy_Spawn(s32 idx, f32 x, f32 z, f32 angle, Obj *obj, Enemy *e) {
    s32 pad;
    EnemyDef *def;

    def = &D_8007C05C->unkC[idx];
    obj->unk50 = def->unk2;
    Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
    obj->unk54 = Math_Rand(16);
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
    Coll_ResolveFloorAndWalls(x, 0.0f, z, 0xA01, &D_8007C080);
    if (D_8007C080.flags & 0x8000) {
        if (obj->unk64->unk0 == 0) {
            Coll_ResolveFloorAndWalls(x + 0.5, 0.0f, z + 0.5, 0xA01, &D_8007C080);
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

void Enemy_SortTurnOrder(void) {
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

void Enemy_StartTurn(void) {
    D_8007B908[D_8007C050[D_8008BE58]].flags |= 1;
}

void Enemy_StateIdle(Obj *obj, Enemy *e, Unk8000AA74 *arg2) {
    Unk8000BA20 *v;

    Enemy_GetAnimStep(obj, &D_8007C070);
    Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
    if (e->flags & 1) {
        D_8007C028 = e;
        D_8008C162 = 60;
        e->flags &= 0xFFFC;
        if (e->unk98 & 8) {
            Battle_EndTurn(obj);
            return;
        }
        v = Enemy_ChooseAttack(e, obj);
        if (v != NULL) {
            if (!(e->flags & 0x10)) {
                Enemy_StartAttack(e, obj, v);
                return;
            }
            e->type = 1;
            e->unk4 = 4;
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
                Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2->unkE / 10;
                Anim_SetCurrentAndNext(obj, 1, 10, 1, 10, 1);
            }
        } else {
            e->type = 1;
            e->unk4 = 4;
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
                Anim_SetCurrentAndNext(obj, 1, 1, 1, 1, 1);
            } else {
                e->unk2 = arg2->unkE / 10;
                Anim_SetCurrentAndNext(obj, 1, 10, 1, 10, 1);
            }
        }
    }
}

void Enemy_StateApproach(Obj *obj, Enemy *e, Unk8000AA74 *arg2) {
    Unk8000BA20 *v;
    f32 dx;
    f32 dz;
    f32 d;

    Enemy_TurnToward(obj, D_8007AA08.x, D_8007AA08.z);
    if (D_8008BE52 & 0x100) {
        D_8007C070.x = 0.0f;
        D_8007C070.y = 0.4f;
        Math_RotateVec2(obj->angle, &D_8007C070);
    } else {
        Enemy_GetAnimStep(obj, &D_8007C070);
    }
    Enemy_Move(1, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
    e->unk2--;
    if (e->unk2 == 0) {
        e->unk4--;
        if (e->unk1C != NULL) {
            dx = D_8007AA08.x - obj->x;
            dz = D_8007AA08.z - obj->z;
            d = sqrtf(dx * dx + dz * dz) - D_8007AA84->unk18 * D_8007AA08.unk3C;
            if (d < e->unk1C->unk10 * obj->unk24) {
                Enemy_StartAttack(e, obj, e->unk1C);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                Enemy_StartAttack(e, obj, e->unk1C);
                return;
            }
            if (D_8008BE52 & 0x100) {
                e->unk2 = arg2->unkE;
            } else {
                e->unk2 = arg2->unkE / 10;
            }
        } else {
            v = Enemy_ChooseAttack(e, obj);
            if (v != NULL) {
                Enemy_StartAttack(e, obj, v);
                return;
            }
            if (e->unk4 == 0 || (e->flags & 2)) {
                e->type = 0;
                Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
                Battle_EndTurn(obj);
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

void Enemy_StateHurt(Obj *obj, EnemyAI *ai, s32 arg2) {
    Enemy_GetAnimStep(obj, &D_8007C070);
    Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        if (ai->unkA == 0) {
            Hud_ClearActorStatusIndicators(obj);
            Enemy_SpawnDeathEffects(obj);
            obj->unk50 = -1;
            obj->unk60 &= 0xFFFE;
            D_8007B900--;
            D_8007A9B4 += obj->unk64->unk10;
            D_8007A9B8 += obj->unk64->unk14;
            Sfx_Play(0, 10, 0xFF);
        } else {
            ai->unk0 = 0;
            obj->unk60 &= 0xFFFC;
        }
    }
}

void Enemy_StateFacePlayer(Obj *obj, EnemyAI *ai, s32 arg2) {
    Enemy_TurnToward(obj, D_8007AA08.x, D_8007AA08.z);
    Enemy_GetAnimStep(obj, &D_8007C070);
    Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, ai);
    ai->unk2--;
    if (ai->unk2 == 0) {
        ai->unk0 = 0;
        obj->unk60 &= 0xFFFE;
        Battle_EndTurn(obj);
    }
}

void Enemy_StateMeleeAttack(Obj *obj, Enemy *e, AnimDef *anims) {
    u16 n;
    f32 dx;
    f32 dz;
    f32 d;
    s32 atk;
    Unk8000BA20 *a;
    u16 attr;

    switch (e->unk6) {
        case 0:
            attr = e->unk1C->unk2;
            if (attr & 2) {
                Enemy_GetAnimStep(obj, &D_8007C070);
                Enemy_Move(0, D_8007C070.x, D_8007C074, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                e->unk6++;
                e->unk2 = e->unk1C->unk6;
            }
            break;
        case 1:
            attr = e->unk1C->unk2;
            if (attr & 0xA) {
                Enemy_GetAnimStep(obj, &D_8007C070);
                Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            if (!(D_8007AA08.unk78 & 2) && !(e->flags & 8)) {
                dx = D_8007AA08.x - obj->x;
                dz = D_8007AA08.z - obj->z;
                d = sqrtf(dx * dx + dz * dz) - D_8007AA08.unk3C * D_8007AA08.unk14->unk18;
                if (d < e->unk1C->unk14 * obj->unk24) {
                    if (Enemy_RollHitOnPlayer(obj) != 0) {
                        n = Enemy_CalcAttackDamage(e);
                        atk = 0x8004;
                        if (e->flags & 0x20) {
                            atk = 0xC004;
                        }
                        n = Player_TakeDamage(n, atk, obj);
                        D_8007C070.x = 0.0f;
                        D_8007C070.y = 2.0f * (obj->unk64->unk18 * obj->unk24);
                        Math_RotateVec2(obj->angle, &D_8007C070);
                        Effect_SpawnStreakBurst(obj->x + D_8007C070.x, obj->y + obj->unk64->unk1C * obj->unk24 * 0.7f, obj->z + D_8007C070.y);
                        if (e->unk98 & 2) {
                            n = ((n + 3) >> 2) + 1;
                            e->unkA += n;
                            if (obj->unk64->unk6 < e->unkA) {
                                e->unkA = obj->unk64->unk6;
                            }
                            Effect_AddFloatingNumber(obj, 1, n);
                            Hud_StartActorStatusIndicator(obj, 2, 1, 30);
                        }
                    } else {
                        Player_StartDodge();
                        D_8007AA08.unk14->unk2C++;
                    }
                    e->flags |= 8;
                }
            }
            e->unk2--;
            if (e->unk2 == 0) {
                a = e->unk1C;
                e->unk6++;
                if (a->unkA == -1) {
                    e->unk2 = anims[a->unk8].unk2 - a->unk4;
                } else {
                    e->unk2 = anims[a->unkC].unk2;
                    Anim_SetCurrentAndNext(obj, a->unkC, 1, 0, 1, 1);
                    Enemy_GetAnimStep(obj, &D_8007C070);
                }
                if (e->unk2 <= 0) {
                    e->unk2 = 1;
                }
                Battle_EndTurn(obj);
            }
            break;
        case 2:
            Enemy_GetAnimStep(obj, &D_8007C070);
            Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            e->unk2--;
            if (e->unk2 == 0) {
                e->type = 0;
                obj->unk60 &= 0xFFFE;
            }
            break;
    }
}

void Enemy_StateCastSpell(Obj *obj, Enemy *e, AnimDef *anims) {
    Unk8000BA20 *a;

    switch (e->unk6) {
        case 0:
            if (e->unk1C->unk2 & 2) {
                Enemy_GetAnimStep(obj, &D_8007C070);
                Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                Magic_CreateCastEffect(obj, e->unk1C->unk0 & ~0x8000, 0, 0);
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
                Battle_EndTurn(obj);
            }
            break;
        case 1:
            if (e->unk1C->unk2 & 0xA) {
                Enemy_GetAnimStep(obj, &D_8007C070);
                Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
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
                Enemy_GetAnimStep(obj, &D_8007C070);
                Enemy_Move(0, D_8007C070.x, D_8007C070.y, obj, (EnemyAI *)e);
            }
            e->unk2--;
            if (e->unk2 == 0) {
                a = e->unk1C;
                e->unk6--;
                e->unk2 = anims[a->unkC].unk2;
                Anim_SetCurrentAndNext(obj, a->unkC, 1, 0, 1, 1);
            }
            if (e->unk2 <= 0) {
                e->unk2 = 15;
            }
            break;
    }
}

Unk8000BA20 *Enemy_ChooseAttack(Enemy *e, Obj *obj) {
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
                    if (Math_Rand(2) == 0) {
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
        sel = &e->unk28->unk30[Math_Rand(e->unk28->unk2C)];
    }
    e->unk1C = sel;
    return sel;
}

void Enemy_StartAttack(Enemy *e, Obj *obj, Unk8000BA20 *arg2) {
    s32 t = arg2->unk0 & 0x8000;

    if (t && (e->unk98 & 0x40)) {
        e->type = 0;
        Anim_SetCurrentAndNext(obj, 0, 1, 0, 1, 1);
        Battle_EndTurn(obj);
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
    obj->angle = Math_Atan2(D_8007AA08.x - obj->x, D_8007AA08.z - obj->z);
    Anim_SetCurrentAndNext(obj, arg2->unk8, 1, arg2->unkA == -1 ? 0 : arg2->unkA, 1, 1);
    Camera_StartBattleFocus(arg2->unk4 + 0xF, obj);
    if (e->unk2 == 0) {
        e->unk2 = 1;
    }
    if (D_8008BE52 & 0x100) {
        Enemy_StartAttackScript(arg2->unk0 & 0xFF, (s32)e);
    }
}

void Enemy_TurnToward(Obj *obj, f32 x, f32 z) {
    f32 diff;

    x -= obj->x;
    z -= obj->z;
    diff = Math_Atan2(x, z) - obj->angle;
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

void Enemy_Move(s32 clamp, f32 dx, f32 dz, Obj *obj, EnemyAI *ai) {
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
    Enemy_ResolveCollisions(&dx, &dz, obj);
    obj->unk18 = dx;
    obj->unk20 = dz;
    obj->x += dx;
    obj->z += dz;
    flags = 0xA00;
    if (obj->unk64->unk0 == 0 && e->type != 0) {
        flags = 0xA01;
    }
    D_8007C080.x = obj->unk64->unk18 * obj->unk64->unk20;
    Coll_ResolveFloorAndWalls(obj->x, obj->y, obj->z, flags, &D_8007C080);
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

void Enemy_GetAnimStep(Obj *obj, Vec3f *out) {
    u8 *anims;

    anims = D_8007C048[obj->unk50];
    Anim_UpdateRootMotion(obj, anims + obj->unk52 * 0xC, obj->unk24, out);
    out->x = -obj->unk44;
    out->y = obj->unk4C;
    Math_RotateVec2(obj->angle, out);
}

void Enemy_ResolveCollisions(f32 *dx, f32 *dz, Obj *obj) {
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

s32 Enemy_RollHitOnPlayer(Obj *obj) {
    s16 chance;

    chance = (obj->unk68->unk86 * 100) / (obj->unk68->unk86 + ((D_8007AA88->unk86 + 7) >> 3));
    return Math_Rand(100) < chance;
}

u16 Enemy_CalcAttackDamage(Enemy *arg0) {
    u16 dmg;

    dmg = arg0->unk11C;
    dmg = (dmg * arg0->unk122) >> 4;
    if (Math_Rand(32) == 0) {
        dmg = dmg + (dmg >> 1);
        Fade_Start(4, 0, D_8004F760);
        arg0->flags |= 0x20;
    }
    if (arg0->unk98 & 1) {
        dmg >>= 1;
    }
    return dmg;
}

u16 Enemy_TakeDamage(s32 idx, u16 dmg, u16 elem, u16 flags, Obj *src) {
    f32 q;
    Obj *obj;
    f32 a;
    u8 *anims;
    Enemy *enemies;

    obj = &D_8007B908[idx].obj;
    anims = D_8007C048[D_8007B908[idx].obj.unk50];
    if (D_8007B908[idx].unkA) {
        if (dmg) {
            if (!(flags & 0x8000)) {
                switch (D_8004DD38[D_8007B908[idx].unk28->unk26] | D_8004DD38[elem]) {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                        dmg >>= 1;
                        break;
                    case 5:
                    case 10:
                        dmg += dmg >> 2;
                        break;
                }
            } else {
                a = Math_Atan2(src->x - obj->x, src->z - obj->z) - obj->angle;
                if (a > 3.141592653589793) {
                    a -= 6.283185307179586;
                } else if (a < -3.141592653589793) {
                    a += 6.283185307179586;
                }
                if (a < 0.0f) {
                    a = -a;
                }
                if (a > 2.356194490192345) {
                    dmg += dmg >> 1;
                }
            }
            a = src->unk68->unk84;
            a /= (f32)(src->unk68->unk84 + D_8007B908[idx].unk120);
            dmg = dmg * a;
            q = sqrtf(dmg);
            dmg += Math_Rand(q * 0.75 + 1.0);
            if (!dmg) {
                dmg++;
            }
            if (D_8007B908[idx].unkA < dmg) {
                D_8007B908[idx].unkA = 0;
            } else {
                D_8007B908[idx].unkA -= dmg;
            }
            if (D_8007B908[idx].unk98 & 0x200) {
                D_8007B908[idx].unkC += dmg;
                enemies = D_8007B908;
                if (obj->unk64->unkA < enemies[idx].unkC) {
                    D_8007B908[idx].unkC = obj->unk64->unkA;
                }
                Hud_StartActorStatusIndicator(obj, 0x200, 2, 30);
            }
            Effect_AddFloatingNumber(obj, (flags & 0x4000) ? 0x8003 : 0, dmg);
        }
        D_8007B908[idx].type = 2;
        obj->unk60 |= 1;
        if (flags & 4) {
            obj->unk60 |= 2;
        }
        if (D_8008BE52 & 0x100) {
            D_8007B908[idx].unk2 = ((AnimDef *)anims)[D_8007B908[idx].unk28->unk28].unk2;
            Anim_SetCurrentAndNext(obj, D_8007B908[idx].unk28->unk28, 1, 0, 1, 1);
        } else {
            D_8007B908[idx].unk2 = ((AnimDef *)anims)[D_8007B908[idx].unk28->unk28].unk2 / 10;
            Anim_SetCurrentAndNext(obj, D_8007B908[idx].unk28->unk28, 10, 0, 1, 1);
        }
    }
    if (flags & 0x8000) {
        Sfx_Play(0, 0x18, 0xFF);
    }
    return dmg;
}


void Enemy_PlayMissEffect(void) {
    Hud_ShowActorPopup();
    Sfx_Play(0, 0x17, 0xFF);
}

s32 Enemy_GetSlotIndex(Obj *arg0) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (arg0 == &D_8007B908[i].obj) {
            break;
        }
    }
    return i;
}

void Enemy_SpawnDeathEffects(Obj *obj) {
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
    Magic_CreateVisualEffect(D_8005685A, D_8005685C, obj->x, y, obj->z, obj->angle, t, &D_8007C070, obj);
    Effect_StartBurstEmitter(2, 0x1E, obj->x, obj->unk64->unk1C * obj->unk24 + y, obj->z,
                  obj->unk64->unk18 * obj->unk24 * 3.6);
}

void Enemy_ClearAttackScript(void) {
    D_8007C064 = 0;
}

void Enemy_StartAttackScript(s32 arg0, s32 arg1) {
    ((Unk8007C060 *)&D_8007C060)->unk0 = 0;
    ((Unk8007C060 *)&D_8007C060)->unk4 = D_800566C8[arg0];
    ((Unk8007C060 *)&D_8007C060)->unk8 = arg1;
    ((Unk8007C060 *)&D_8007C060)->unkC = &D_8007B908[0].obj;
}

#ifdef NON_MATCHING
/* &D_8007C060 kept in a register for the ++ shifts the temporaries by one (register allocation); code is equivalent */
void Enemy_RunAttackScript(void) {
    SpawnScript *e;
    f32 x;
    f32 y;
    f32 z;
    f32 s;
    u16 m;
    s32 pad2;
    Obj *obj;
    s32 pad3;
    s32 pad4;
    SpawnDef *d;
    Unk800C18D8 *t;
    Enemy *en = D_8007B908;

    if (D_8007C064 != NULL) {
        e = D_8007C064;
        if (e->time < ++D_8007C060) {
            obj = D_8007C06C;
            if (e->flags & 8) {
                D_8007C070.x = e->unk8;
                D_8007C070.y = e->unk10;
                Math_RotateVec2(obj->angle, &D_8007C070);
                en->unk20 = D_8007C070.x;
                en->unk24 = D_8007C070.y;
            } else {
                d = &((SpawnDef *) &D_80056718)[e->unk2];
                t = &D_800C18D8[d->unk0];
                D_8007C070.x = e->unk8;
                D_8007C070.y = e->unk10;
                Math_RotateVec2(obj->angle + e->unk14, &D_8007C070);
                if (e->flags & 2) {
                    x = D_8007AA20;
                    y = D_8007AA24;
                    z = D_8007AA28;
                } else {
                    x = obj->x;
                    y = obj->y;
                    z = obj->z;
                }
                s = obj->unk24;
                x += D_8007C070.x * s;
                y += e->unkC * s;
                z += D_8007C070.y * s;
                D_8007C070.x = d->unk8;
                D_8007C070.y = d->unkC;
                m = D_8007C068->unk1C->unk0;
                if (m & 0x8000) {
                    D_8007C070.z = D_800C185C[(m >> 8) & 0xF][m & 0xFF].unk1C;
                } else {
                    D_8007C070.z = obj->unk28;
                }
                Magic_CreateVisualEffect(d->unk2, d->unk4, x, y, z, obj->angle + e->unk14, t, &D_8007C070, obj);
            }
            if (e->flags & 4) {
                Camera_Shake(1);
            }
            if (e->flags & 1) {
                D_8007C064 = NULL;
            } else {
                D_8007C064++;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/Enemy_RunAttackScript.s")
#endif

/* .data 8004DD20..8004DD50 */
typedef void (*Fn8004DD20)(Obj*, Enemy*, u8*);
Fn8004DD20 D_8004DD20[6] = {
    (Fn8004DD20) Enemy_StateIdle,
    (Fn8004DD20) Enemy_StateApproach,
    (Fn8004DD20) Enemy_StateHurt,
    (Fn8004DD20) Enemy_StateFacePlayer,
    (Fn8004DD20) Enemy_StateMeleeAttack,
    (Fn8004DD20) Enemy_StateCastSpell,
};
s32 D_8004DD38[5] = { 1, 2, 4, 8, 0x10 };
