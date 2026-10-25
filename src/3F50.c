#include "common.h"

typedef struct {
    f32 x;
    f32 z;
} Vec2f;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} ActorStats;

/* a moving object: the player (D_8007AA20, inside D_8007AA08) and others */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 rot;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 vz;
    /* 0x24 */ f32 scale;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38[0x44 - 0x38];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u8 unk5C[0x60 - 0x5C];
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ ActorStats *unk64;
    /* 0x68 */ void *unk68;
} Actor; /* size 0x6C */

typedef struct {
    /* 0x00 */ u8 unk0[0x4];
    /* 0x04 */ u16 unk4;
} PlayerStateSub14;

/* D_8007AA08 */
typedef struct {
    /* 0x000 */ u16 unk0; /* state, index into D_8004DCB0 */
    /* 0x002 */ u16 unk2;
    /* 0x004 */ u16 unk4; /* state timer */
    /* 0x006 */ u16 unk6;
    /* 0x008 */ s32 unk8; /* flags */
    /* 0x00C */ f32 unkC;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ PlayerStateSub14 *unk14;
    /* 0x018 */ Actor actor;
    /* 0x084 */ s32 unk84;
    /* 0x088 */ u8 unk88[0x108 - 0x88];
    /* 0x108 */ u16 unk108;
    /* 0x10A */ u16 unk10A;
    /* 0x10C */ u16 unk10C;
    /* 0x10E */ u16 unk10E;
    /* 0x110 */ s32 unk110;
    /* 0x114 */ f32 unk114;
    /* 0x118 */ u8 unk118[0x11C - 0x118];
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 unk11D[0x122 - 0x11D];
    /* 0x122 */ u16 unk122;
    /* 0x124 */ u16 unk124;
    /* 0x126 */ u16 unk126;
    /* 0x128 */ u16 unk128;
    /* 0x12A */ u16 unk12A;
    /* 0x12C */ f32 unk12C;
    /* 0x130 */ f32 unk130;
    /* 0x134 */ f32 unk134;
    /* 0x138 */ f32 unk138;
} PlayerState;

/* per-character data, from the D_80055D40 table */
typedef struct {
    /* 0x000 */ u8 unk0[0x7A];
    /* 0x07A */ s16 unk7A;
    /* 0x07C */ u8 unk7C[0x86 - 0x7C];
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 unk88[0xC2 - 0x88];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 unkC4[0xDA - 0xC4];
    /* 0x0DA */ s16 unkDA;
    /* 0x0DC */ u8 unkDC[0x122 - 0xDC];
    /* 0x122 */ s16 unk122;
} CharData;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
} Unk80084300;

typedef struct {
    /* 0x00 */ u8 unk0[0x4C];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ u8 unk50[0x58 - 0x50];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ u8 unk5C[0x70 - 0x5C];
    /* 0x70 */ f32 unk70;
} Unk80085E48;

typedef struct {
    /* 0x0 */ void *unk0;
    /* 0x4 */ u8 unk4[0x80];
} Unk8007AC70; /* size 0x84 */

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u8 unk2[0xA];
} Unk803AAAA2; /* size 0xC */

void func_800069E0(Actor *arg0, s32 arg1, Vec2f *arg2);
void func_80006A58(u16 arg0, Actor *arg1, PlayerState *arg2);
void func_80006168(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3);
void func_80007A38(Actor *arg0);
void func_80008970(PlayerState *arg0);
void func_8000A040(s32 arg0);
void func_80013A50(u8 arg0);
void func_800169B8(Actor *arg0, u16 arg1, s32 arg2, u16 arg3);
s32 func_80017AB0(void);
void func_8001FC14(Actor *arg0);
void func_800201A0(Actor *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_80020214(Actor *arg0, s32 arg1, f32 arg2);
void func_80023D28(Actor *arg0);
void func_80025094(u8 arg0);
void func_800251CC(u8 arg0, Actor *arg1);
void func_800271B4(f32 arg0, Vec2f *arg1);
void func_8002A338(s32 arg0);
void func_8002A6B8(s32 arg0);
void func_8002A7C8(s32 arg0, s32 arg1, s32 arg2);
void func_80032D20(s32 arg0);

extern s32 D_8004DCA0;
extern s32 D_8007A174;
extern u16 D_8007A178;
extern s16 D_8007A17A;
extern s32 D_8007A910;
extern Vec2f D_8007A918;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern u16 D_8007A9AC;
extern u16 D_8007A9AE;
extern u16 D_8007A9B0;
extern s32 D_8007A9C0;
extern s16 D_8007AA0E;
extern Unk8007AC70 D_8007AC70[];
extern Unk80084300 D_80084300;
extern s32 D_800842BC;
extern s32 D_800842C0;
extern Unk80085E48 D_80085E48;
extern s16 D_8008C152;
extern u16 D_8008C154;
extern s32 D_80090450;
extern s32 D_80090454;
extern Unk803AAAA2 D_803AAAA2[];

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000464C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800047F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800049F4.s")

void func_80004DEC(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFC;
    }
}

void func_80004E28(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    func_80006A58(0xA01, arg0, arg1);
    arg0->vx *= 0.68;
    arg0->vz *= 0.68;
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->unk60 &= 0xFFFE;
    }
}

void func_80004ED0(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (--arg1->unk4 == 0) {
        PlayerStateSub14 *sub = arg1->unk14;

        arg0->vx = 0.0f;
        arg0->vz = 0.0f;
        if (sub->unk4 == 0) {
            arg1->unk0 = 6;
            arg1->unk4 = 0xE6;
            func_800201A0(arg0, 9, 1, D_8007A910, 1, 1);
            func_80023D28(arg0);
            func_8002A6B8(0x1E);
            D_8004DCA0 |= 0x880;
            D_8007A174 = arg1->unk4;
            D_8007A178 = 2;
            D_8007A17A = 0x5A;
            arg1->unk124 = 0xC8;
            D_80084300.unk0 = D_8007A9AC;
            D_80084300.unk4 = D_8007A9AE;
            D_80084300.unk8 = D_8007A9B0;
            D_8007A98C = 0.0f;
            D_8007A990 = 0.0f;
            D_8007A994 = 0.0f;
            D_8007A998 = 0x108;
            D_8007AA0E = 0;
            D_8008C154 = 1;
            D_8008C152 = 0xC;
        } else {
            arg1->unk0 = 0;
            arg0->unk60 &= 0xFFFC;
        }
    }
}

void func_8000503C(Actor *arg0, PlayerState *arg1, s32 arg2) {
    func_800069E0(arg0, arg2, &D_8007A918);
    arg0->vx = D_8007A918.x;
    arg0->vz = D_8007A918.z;
    func_80006A58(0xA01, arg0, arg1);
    if (--arg1->unk4 == arg1->unk124) {
        D_80085E48.unk4C = 250.0f;
        D_80085E48.unk58 = 150.0f;
        D_80085E48.unk70 = 0.01f;
    }
}

void func_800050E8(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (D_80090450 == 0) {
        func_8000A040(D_8007A9C0);
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        D_8004DCA0 &= ~2;
        if (D_8004DCA0 & 0x10) {
            D_8004DCA0 &= ~0x10;
            if (*(u16 *)((u8 *)D_8007AC70[D_8007A9C0].unk0 + 2) == 6 && D_80090454 == 0) {
                D_8004DCA0 |= 0x480;
                D_8007A174 = 0x23;
                D_8007A17A = 0x1E;
                D_8007A9AC = D_800842BC;
                D_8007A9AE = D_800842C0;
                arg1->unk0 = 3;
                arg1->unk4 = 0x41;
                arg0->unk60 |= 1;
                func_8002A338(0x3C);
            }
        } else if (arg1->unk8 & 0x40) {
            arg1->unk8 &= ~0x40;
            func_8002A7C8(0, 0x3B, 0xFF);
        }
        D_8007A9C0 = 0;
    }
}

void func_8000525C(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    func_80006168(arg1->unk12C, arg1->unk130, arg0, arg1);
    func_80006A58(0xA01, arg0, arg1);
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->vz = 0.0f;
        arg0->vx = 0.0f;
        arg0->unk60 &= 0xFFFE;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800052E0.s")

void func_8000571C(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->unk124 != 0) {
        if (--arg1->unk124 == 0) {
            func_800169B8(arg0, arg1->unk122, 0, (arg1->unk8 & 0x10000) ? 0x10 : 0);
        }
    } else if (--arg1->unk4 == 0) {
        if (func_80017AB0() != 0) {
            arg1->unk4 = 8;
            return;
        }
        arg0->unk60 &= 0xFFFE;
        if (arg1->unk8 & 4) {
            arg1->unk0 = 3;
            arg1->unk4 = arg2->unk122;
            arg1->unk8 &= ~4;
            func_800201A0(arg0, 0x18, 1, D_8007A910, 1, 1);
        } else {
            arg1->unk0 = 0;
        }
        func_80008970(arg1);
        arg1->unk2 = 0;
        func_8001FC14(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80005850.s")

void func_80005A18(Actor *arg0, PlayerState *arg1, s32 arg2) {
    func_800069E0(arg0, arg2, &D_8007A918);
    arg0->vx = D_8007A918.x;
    arg0->vz = D_8007A918.z;
    func_80006A58(0xA00, arg0, arg1);
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        arg0->rot = arg1->unk138;
    }
}

void func_80005AB4(Actor *arg0, PlayerState *arg1, s32 arg2) {
    if (arg1->unk4 != 0) {
        func_800069E0(arg0, arg2, &D_8007A918);
        arg0->vx = D_8007A918.x;
        arg0->vz = D_8007A918.z;
        func_80006A58(0xA00, arg0, arg1);
        if (arg1->unk4 == 0x20) {
            func_80013A50(arg1->unk11C);
            func_80032D20(1);
            func_80025094(arg1->unk11C);
            D_8004DCA0 |= 2;
            func_8002A7C8(0, 0x3B, 0xFF);
        }
        if (--arg1->unk4 == 0) {
            arg0->rot = arg1->unk138;
            func_800201A0(arg0, D_8007A910, 1, D_8007A910, 1, 1);
        }
    } else if (D_80090450 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFE;
        D_8004DCA0 &= ~2;
        D_8007A9C0 = 0;
    }
}

void func_80005C00(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    if (--arg1->unk4 == 0) {
        func_800251CC(arg1->unk11C, arg0);
        if (D_803AAAA2[arg1->unk11C].unk0 == 2) {
            func_80008970(arg1);
            arg1->unk2 = 0;
            func_8001FC14(arg0);
        } else {
            arg1->unk124 = 0xF;
            func_80008970(arg1);
        }
    } else if (--arg1->unk124 == 0) {
        if (func_80017AB0() != 0) {
            arg1->unk124 = 8;
            return;
        }
        arg1->unk0 = 3;
        arg1->unk4 = 0xF;
        func_800201A0(arg0, 0x18, 1, D_8007A910, 1, 1);
        arg1->unk2 = 0;
        func_8001FC14(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80005D18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80005E78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000665C.s")

void func_800069E0(Actor *arg0, s32 arg1, Vec2f *arg2) {
    func_80007A38(arg0);
    func_80020214(arg0, arg0->unk52 * 0xC + arg1, arg0->scale);
    arg2->x = -arg0->unk44;
    arg2->z = arg0->unk4C;
    func_800271B4(arg0->rot, arg2);
}

void func_80006A50(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006A58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006D24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800073E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000791C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800079B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007D30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007E04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007EAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007FD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000847C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800085D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008A40.s")
