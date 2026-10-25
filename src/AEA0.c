#include "common.h"

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} EnemyDef;

typedef struct {
    /* 0x00 */ u8 pad0[0x86];
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
    /* 0x14 */ u8 pad14[0x10];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[0x18];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ u8 pad48[4];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ u8 pad54[0xC];
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u8 pad62[2];
    /* 0x64 */ EnemyDef *unk64;
    /* 0x68 */ EnemyStats *unk68;
} Obj; /* size 0x6C */

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u16 unkC;
} Unk28;

typedef struct {
    /* 0x000 */ u16 type;
    /* 0x002 */ u8 pad2[6];
    /* 0x008 */ u16 flags;
    /* 0x00A */ u8 padA[0x1E];
    /* 0x028 */ Unk28 *unk28;
    /* 0x02C */ Obj obj;
    /* 0x098 */ u16 unk98;
    /* 0x09A */ u8 pad9A[0x82];
    /* 0x11C */ u16 unk11C;
    /* 0x11E */ u8 pad11E[4];
    /* 0x122 */ u16 unk122;
    /* 0x124 */ u8 pad124[0xC];
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
    /* 0x0C */ u8 padC[4];
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
    /* 0x00 */ s16 unk0;
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
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u8 pad0[10];
} Unk800C18D8;

void func_8000A5E4(void);
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
void func_800269B8(s32, s32, void *);
u32 func_80026E90(s32);
void func_800271B4(f32, Vec3f *);
void func_80028120(u32, void *, u32);
void func_8002A7C8(s32, s32, s32);

extern void (*D_8004DD20[])(Obj *, Enemy *, u8 *);
extern u8 D_8004F760[];
extern Unk800561A0 D_800561A0[];
extern u32 D_800566C8[];
extern Unk80056718 D_80056718;
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
extern Unk8007C060 D_8007C060;
extern s32 D_8007C064;
extern Vec3f D_8007C070;
extern Unk8007C288 *D_8007C288;
extern u16 D_800842E8;
extern u16 D_8008BE52;
extern u16 D_8008BE58;
extern Unk800C18D8 D_800C18D8[];
extern u8 D_8020E6F0[];

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A2A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A310.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A3E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A5E4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A6D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000A95C.s")

void func_8000AA28(void) {
    D_8007B908[D_8007C050[D_8008BE58]].flags |= 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000AA74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000AC84.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000B508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000B7A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000BA20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000BB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000BCA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000BFE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000C05C.s")

s32 func_8000C3FC(Obj *obj) {
    s16 chance;

    chance = (obj->unk68->unk86 * 100) / (obj->unk68->unk86 + ((D_8007AA88->unk86 + 7) >> 3));
    return func_80026E90(100) < chance;
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000C48C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000CAE8.s")

void func_8000CC30(void) {
    D_8007C064 = 0;
}

void func_8000CC40(s32 arg0, s32 arg1) {
    D_8007C060.unk0 = 0;
    D_8007C060.unk4 = D_800566C8[arg0];
    D_8007C060.unk8 = arg1;
    D_8007C060.unkC = &D_8007B908[0].obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/AEA0/func_8000CC78.s")
