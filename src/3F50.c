#include "common.h"

typedef struct {
    f32 x;
    f32 z;
    f32 unk8;
} Vec2f;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u8 unk14[0x18 - 0x14];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24[0x38 - 0x24];
} ActorStats;

typedef struct {
    /* 0x00 */ u8 unk0[0x84];
    /* 0x84 */ u16 unk84;
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u8 unk88[0x94 - 0x88];
    /* 0x94 */ f32 unk94;
} ActorSub68;

/* animation table entry (size 0xC) */
typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u8 unk4[0x8];
} AnimEntry;

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
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ u16 unk62;
    /* 0x64 */ ActorStats *unk64;
    /* 0x68 */ ActorSub68 *unk68;
} Actor; /* size 0x6C */

typedef struct {
    /* 0x00 */ u8 unk0[0x4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 unkA[0x18 - 0xA];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C[0x24 - 0x1C];
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
} PlayerStateSub14;

/* D_8007B908: monsters, size 0x130 */
typedef struct {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ Actor actor;
    /* 0x98 */ u8 unk98[0x130 - 0x98];
} Monster;

typedef struct {
    /* 0x0 */ u8 *start;
    /* 0x4 */ u8 *end;
} RomRange;

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
    /* 0x084 */ u16 unk84;
    /* 0x086 */ u16 unk86;
    /* 0x088 */ u8 unk88[0x108 - 0x88];
    /* 0x108 */ u16 unk108;
    /* 0x10A */ u16 unk10A;
    /* 0x10C */ u16 unk10C;
    /* 0x10E */ u16 unk10E;
    /* 0x110 */ u16 unk110;
    /* 0x112 */ u16 unk112;
    /* 0x114 */ f32 unk114;
    /* 0x118 */ u8 unk118[0x11C - 0x118];
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 unk11D[0x120 - 0x11D];
    /* 0x120 */ u16 unk120;
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
    /* 0x000 */ u8 unk0[0x56];
    /* 0x056 */ s16 unk56;
    /* 0x058 */ u8 unk58[0x7A - 0x58];
    /* 0x07A */ s16 unk7A;
    /* 0x07C */ u8 unk7C[0x86 - 0x7C];
    /* 0x086 */ s16 unk86;
    /* 0x088 */ u8 unk88[0xC2 - 0x88];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 unkC4[0xDA - 0xC4];
    /* 0x0DA */ s16 unkDA;
    /* 0x0DC */ u8 unkDC[0x116 - 0xDC];
    /* 0x116 */ s16 unk116;
    /* 0x118 */ u8 unk118[0x122 - 0x118];
    /* 0x122 */ s16 unk122;
} CharData;

typedef struct {
    /* 0x00 */ u8 unk0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 unk1A[0x44 - 0x1A];
} Unk800C185C; /* size 0x44 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
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
void func_8002A7C8(u8 arg0, s8 arg1, u8 arg2);
void func_80032D20(s32 arg0);
s32 func_80007FD8(s32 arg0, u16 arg1, Actor *arg2);
void func_80015F44(s32 arg0, Actor *arg1);
u32 func_80026E90(s32 arg0);
f32 func_800270D0(f32 arg0, f32 arg1);
void func_80028120(u8 *romStart, void *dest, u32 size);
void func_8002433C(Actor *arg0);
f32 sqrtf(f32 x);

extern s32 D_8004DCA0;
extern s32 D_8004DCF8;
extern CharData *D_80055D40[];
extern RomRange D_80055F98[];
extern f32 D_8007A988;
extern PlayerState D_8007AA08;
extern Actor D_8007AA20;
extern Monster D_8007B908[];
extern u16 D_8008BE52;
extern u16 D_8008BE54;
extern f32 D_8008BE64;
extern f32 D_8008BE68;
extern s16 D_8008C15E;
extern Unk800C185C *D_800C185C[];
extern u16 D_800C186E[];
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

extern u8 D_869620[];
extern u8 D_86F6F0[];
extern u8 D_80206000[];
extern ActorStats D_80055D44;
extern ActorStats D_8007A9D0;
extern ActorSub68 D_8007AA8C;
extern f32 D_8007A8F4;
extern f32 D_8007A8F8;
extern f32 D_8007A8FC;
extern f32 D_8007A900;

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003494.s")


typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 x;
    /* 0x8 */ f32 y;
    /* 0xC */ f32 rot;
} Unk80056088; /* size 0x10 */

extern Unk80056088 D_80056088[];
extern Unk80056088 D_80056198[];
extern s32 D_800842C4;
extern s32 D_800842C8;

void func_80003B20(void) {
    s32 i;

    D_8007AA08.unk14->unk18 = 50.0f;
    D_800842C4 = D_800842BC;
    D_800842C8 = D_800842C0;
    D_80084300.unk8 = 0;
    for (i = 0; i < 17; i++) {
        if (D_800842BC == D_80056088[i].unk0 && D_800842C0 == D_80056088[i].unk2) {
            D_8007A98C = D_80056088[i].x;
            D_8007A990 = D_80056088[i].y;
            D_8007A994 = D_80056088[i].rot;
            D_80084300.unk8 = -1;
            break;
        }
    }
    D_800842BC = -1;
    D_800842C0 = -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80003BE0.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

extern Gfx *D_8007A184;
extern s32 D_8007AB60;
extern u8 D_10000A0[];
/* collision query result (func_800107F0) */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u16 unk18;
} Unk8007A928;

extern Unk8007A928 D_8007A928;
extern f32 D_8007A92C;
extern Vec3f D_8007AB48;
extern Vec3f D_8008BFC0;
void func_800107F0(f32 x, f32 y, f32 z, s32 flags, void *out);
void func_80012B88(s32 arg0);
void func_800131F0(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale);
void func_80020428(s32 arg0, Actor *arg1, AnimEntry *arg2, void *arg3);
void func_8002099C(u16 arg0, Actor *arg1, AnimEntry *arg2);

/* fields of D_8007AA08.actor under their own names */
extern f32 D_8007AA24;
extern f32 D_8007AA44;
extern f32 D_8007AA48;
extern f32 D_8007AA4C;
extern f32 D_8007AA50;
extern f32 D_8007AA54;
extern s16 D_8007AA70;
extern s16 D_8007AA72;
extern u16 D_8007AA78;

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000464C.s")

extern s32 D_8007A9B4;
extern s32 D_8007A9B8;
extern s32 D_8007AA10; /* .unk8 */
extern s32 D_8007AA18; /* .unk10 */
extern PlayerStateSub14 *D_8007AA1C; /* .unk14 */
extern f32 D_8007AA30; /* .actor.rot */
extern u16 D_8007AA80; /* .actor.unk60 */
extern f32 D_8007AB3C;

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

void func_80005850(Actor *arg0, PlayerState *arg1, s32 arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    rot = arg0->rot;
    arg0->x += arg1->unk12C;
    arg0->z += arg1->unk130;
    d = arg1->unk134 - rot;
    if (d > 3.141592653589793) {
        d -= 6.283185307179586;
    } else if (d < -3.141592653589793) {
        d += 6.283185307179586;
    }
    arg0->rot = rot + d * 0.3;
    rot = arg0->rot;
    if (arg0->rot > 3.141592653589793) {
        arg0->rot -= 6.283185307179586;
    } else if (arg0->rot < -3.141592653589793) {
        arg0->rot += 6.283185307179586;
    }
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0xA;
        arg1->unk4 = 0x50;
        func_800201A0(arg0, arg1->unk6, 1, D_8007A910, 1, 1);
        func_80007A38(arg0);
        func_80020214(arg0, arg0->unk52 * 0xC + arg2, arg0->scale);
        arg0->rot = arg1->unk138;
        func_8002A7C8(0x1A, 8, 0xFF);
    }
}

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


extern u16 D_8007A172;
void func_8002A744(s32 arg0, s32 arg1, s32 arg2);

void func_80005D18(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    f32 rot;
    f32 d;

    arg0->vz = 0.0f;
    arg0->vx = 0.0f;
    if (arg1->unk4 < 0x26) {
        rot = arg0->rot;
        d = arg1->unk134 - rot;
        if (d < -3.141592653589793) {
            d += 6.283185307179586;
        } else if (d > 3.141592653589793) {
            d -= 6.283185307179586;
        }
        arg0->rot = rot + d * 0.2;
        rot = arg0->rot;
        if (arg0->rot < -3.141592653589793) {
            arg0->rot += 6.283185307179586;
        } else if (arg0->rot > 3.141592653589793) {
            arg0->rot -= 6.283185307179586;
        }
    }
    if (--arg1->unk4 == 0) {
        arg1->unk0 = 0;
        arg0->unk60 &= 0xFFFD;
        if (D_8007A172 != 4) {
            func_8002A744(D_800842BC, D_800842C0, 0x1E);
        }
    }
}


void func_80005E78(Actor *arg0, PlayerState *arg1, CharData *arg2) {
    f32 rot;
    f32 d;

    rot = arg0->rot;
    d = arg1->unk134 - rot;
    if (d < -3.141592653589793) {
        d += 6.283185307179586;
    } else if (d > 3.141592653589793) {
        d -= 6.283185307179586;
    }
    arg0->rot = rot + d * 0.2;
    rot = arg0->rot;
    if (arg0->rot < -3.141592653589793) {
        arg0->rot += 6.283185307179586;
    } else if (arg0->rot > 3.141592653589793) {
        arg0->rot -= 6.283185307179586;
    }
    if (arg1->unk4 != 0) {
        if (--arg1->unk4 == 0) {
            func_80032D20(1);
            D_8004DCA0 |= 2;
        }
    } else if (D_80090450 == 0) {
        arg1->unk0 = 3;
        if (arg1->unk8 & 0x200) {
            arg1->unk4 = 2;
        } else {
            arg1->unk4 = 8;
            func_800201A0(arg0, 0xE, 1, D_8007A910, 1, 1);
        }
        arg1->unk8 &= ~0x200;
        D_8004DCA0 &= ~2;
        D_8007A9C0 = 0;
    }
}

extern s16 D_8007A90C;

void func_80006040(f32 arg0, f32 arg1, Actor *arg2, PlayerState *arg3) {
    f32 speed;

    arg2->vz = 0.0f;
    arg2->vx = 0.0f;
    if (arg0 != 0.0f || arg1 != 0.0f) {
        speed = sqrtf(arg0 * arg0 + arg1 * arg1) * 0.025;
        if (speed > 2.0) {
            speed = 2.0f;
        }
        if (speed > 1.5) {
            arg3->unk0 = 2;
            arg3->unk4 = 0x1E;
            D_8007A90C = 0;
        } else {
            arg3->unk0 = 1;
        }
    } else if (D_8007A910 != arg2->unk52 && D_8007A910 != arg2->unk5A) {
        func_800201A0(arg2, D_8007A910, 1, D_8007A910, 1, 1);
    }
}

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

extern f32 D_8007A9A0;
extern f32 D_8007A9A4;
extern f32 D_8008BE5C;
extern f32 D_8008BE60;
extern f32 D_8008BE6C;
void func_80006F80(f32 *vx, f32 *vz, Actor *arg2);

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80006A58.s")

/* D_8007ABF0: objects of 0x84 bytes with an Actor at +0x14 */
typedef struct {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ Actor actor;
    /* 0x80 */ u8 unk80[0x84 - 0x80];
} Unk8007ABF0;

extern s32 D_8007ABA8;
extern Actor *D_8007ABB0[];
extern Unk8007ABF0 D_8007ABF0[];

s32 func_80006D24(PlayerState *arg0, Actor *arg1) {
    s32 ret;
    s32 n;
    Actor **list;
    Actor *a;
    Unk8007ABF0 *it;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 r;

    ret = 0;
    if (!(D_8004DCA0 & 0x448D) && !(arg0->unk8 & 0x10)) {
        list = D_8007ABB0;
        for (n = D_8007ABA8; n != 0 && ret == 0; n--) {
            a = *list++;
            dx = a->x - arg1->x;
            dy = a->y - arg1->y;
            dz = a->z - arg1->z;
            if (dy > -15.0 && dy < 15.0) {
                if (a->unk60 & 0x1000) {
                    r = 625.0f;
                } else {
                    r = 225.0f;
                }
                if (dx * dx + dz * dz < r) {
                    D_8007A918.x = dx;
                    D_8007A918.z = dz;
                    func_800271B4(arg1->rot, &D_8007A918);
                    if (D_8007A918.z >= 0.0f && D_8007A918.x > -6.0 && D_8007A918.x < 6.0) {
                        ret++;
                        for (it = D_8007ABF0; &it->actor != a; it++) {
                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 radius;
} Unk8007C2A8;

extern s32 D_8007C02C;
extern Actor *D_8007C030[];
extern s32 D_8007C2A4;
extern Unk8007C2A8 *D_8007C2A8[];

void func_80006F80(f32 *arg0, f32 *arg1, Actor *arg2) {
    f32 size;
    f32 x;
    f32 z;
    s32 hit;
    s32 n;
    Actor **list;
    Actor *a;
    Unk8007C2A8 **list2;
    Unk8007C2A8 *o;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;
    f32 k;

    hit = 0;
    size = arg2->unk28 * arg2->scale;
    x = *arg0 + arg2->x;
    z = *arg1 + arg2->z;
    n = D_8007C02C;
    if (n != 0) {
        for (list = D_8007C030; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->unk28 * a->scale + size;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = a->x + dx - arg2->x;
                    *arg1 = a->z + dz - arg2->z;
                }
            }
        }
    }
    n = D_8007ABA8;
    if (n != 0) {
        for (list = D_8007ABB0; !hit && n != 0; n--) {
            a = *list++;
            dx = x - a->x;
            dz = z - a->z;
            r = a->unk28 * a->scale + size;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = a->x + dx - arg2->x;
                    *arg1 = a->z + dz - arg2->z;
                }
            }
        }
    }
    n = D_8007C2A4;
    if (n != 0) {
        for (list2 = D_8007C2A8; !hit && n != 0; n--) {
            o = *list2++;
            dx = x - o->x;
            dz = z - o->z;
            r = size + 2.0 * o->radius;
            if (dx < r && -r < dx && dz < r && -r < dz) {
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < r) {
                    k = r / dist;
                    hit = 1;
                    dx *= k;
                    dz *= k;
                    *arg0 = o->x + dx - arg2->x;
                    *arg1 = o->z + dz - arg2->z;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007320.s")

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rot; /* degrees */
    /* 0x10 */ u8 unk10[0x18 - 0x10];
} Unk8007C290; /* size 0x18 */

extern f32 D_8007AA2C; /* .actor.unkC */
extern f32 D_8007AA34; /* .actor.unk14 */
extern f32 D_8007AB34;
extern f32 D_8007AB38;
extern Unk8007C290 *D_8007C290;
void func_80007658(PlayerState *arg0, Actor *arg1);
void func_8000F50C(s32 arg0, s32 arg1, u16 arg2, Unk8007C290 *arg3);

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800073E8.s")

void func_80007658(PlayerState *arg0, Actor *arg1) {
    s32 pad[2];
    f32 rot;
    u16 hi;
    Unk8007C290 *pos;
    s16 n;

    pos = &D_8007C290[D_80084300.unk10];
    func_8000F50C(0, 0, D_80084300.unkC, pos);
    hi = D_80084300.unkC >> 8;
    if ((hi & 0xF) == 3) {
        arg0->unk6 = 0;
        func_800201A0(arg1, 0x1A, 1, 1, 0xA, 1);
        arg0->unk0 = 3;
        arg0->unk4 = 0x4B;
        arg1->unkC = 0.0f;
        arg1->unk14 = 0.0f;
        arg1->vx = 0.0f;
        arg1->vz = 0.0f;
        func_8002A7C8(0x1E, 9, 0xFF);
    } else {
        arg0->unk0 = 9;
        arg0->unk4 = 8;
        func_800201A0(arg1, 1, 0xA, 1, 0xA, 1);
        if (D_80084300.unkC & 1) {
            n = 0x15;
            D_8007A918.x = -133.0f;
            D_8007A918.z = -92.0f;
            D_8007A918.unk8 = 4.0f;
        } else {
            n = 0x14;
            D_8007A918.x = -119.0f;
            D_8007A918.z = 125.0f;
            D_8007A918.unk8 = 162.0f;
        }
        arg0->unk6 = n;
        rot = pos->rot * 0.017453292519943295;
        func_800271B4(-rot, &D_8007A918);
        arg0->unk12C = (pos->x - D_8007A918.x * arg1->scale - arg1->x) / arg0->unk4;
        arg0->unk130 = (pos->z + D_8007A918.z * arg1->scale - arg1->z) / arg0->unk4;
        arg0->unk138 = rot;
        rot = rot + D_8007A918.unk8 * 0.017453292519943295;
        if (rot > 3.141592653589793) {
            rot -= 6.283185307179586;
        } else if (rot < -3.141592653589793) {
            rot += 6.283185307179586;
        }
        arg0->unk134 = rot;
        arg1->unkC = 0.0f;
        arg1->unk14 = 0.0f;
    }
    arg1->unk60 |= 1;
}

void func_8000791C(PlayerState *arg0, Actor *arg1, s32 arg2) {
    func_800201A0(arg1, 0x1C, 1, 0x1D, 1, 1);
    func_80007A38(arg1);
    func_80020214(arg1, arg1->unk52 * 0xC + arg2, arg1->scale);
    arg0->unk0 = 0xB;
    arg0->unk4 = 0x5A;
    arg1->unk60 |= 1;
}

void func_800079B4(u8 arg0) {
    CharData *cd = D_80055D40[D_8007AA08.actor.unk50];

    D_8007AA08.unk11C = arg0;
    D_8007AA08.unk0 = 0xC;
    D_8007AA08.unk4 = cd->unk116;
    D_8007AA08.actor.unk60 |= 1;
    func_800201A0(&D_8007AA20, 0x17, 1, 0x16, 1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007A38.s")

extern u16 D_8007C050[];
extern u16 D_8008BE5A;

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007A8C.s")

void func_80007D30(PlayerState *arg0, Actor *arg1, CharData *arg2) {
    Monster *mon;
    f32 dx;

    arg0->unk0 = 0xD;
    arg0->unk4 = 0x14;
    arg0->unk8 &= ~0x400;
    arg1->unk60 |= 1;
    func_800201A0(arg1, 0xA, 1, D_8007A910, 1, 1);
    mon = &D_8007B908[arg0->unk2];
    dx = mon[-1].actor.x - arg1->x;
    arg1->rot = func_800270D0(dx, mon[-1].actor.z - arg1->z);
    func_80015F44(0x23, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007E04.s")

extern s32 D_8004DCFC[];
extern u8 D_8004F760[];
void func_800269B8(s32 arg0, s32 arg1, void *arg2);

u16 func_80007EAC(PlayerState *arg0) {
    s32 n;
    s32 i;
    u16 val;
    u16 quarter;
    u16 sum;

    n = 0;
    val = arg0->unk108;
    quarter = arg0->unk108 >> 2;
    sum = arg0->unk108;
    for (i = 0; i < 4; i++) {
        if (quarter < arg0->unk14->unk24[i]) {
            sum = sum - arg0->unk14->unk24[i] + quarter;
            n++;
        }
    }
    val = (val >> 1) + sum;
    if (n != 0) {
        val = (D_8004DCFC[n] * val) >> 6;
    }
    val = (val * arg0->unk10E) >> 4;
    if (func_80026E90((arg0->unk8 & 0x10000) ? 4 : 0x20) == 0) {
        val += val >> 1;
        func_800269B8(4, 0, D_8004F760);
        arg0->unk8 |= 0x400;
    }
    if (arg0->unk84 & 1) {
        val >>= 1;
    }
    return val;
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80007FD8.s")

/* these are fields of D_8007AA08; some functions use them by their own names */
extern u16 D_8007AA0C;    /* .unk4 */
extern PlayerStateSub14 *D_8007AA1C; /* .unk14 */
extern s16 D_8007AA70;    /* .actor.unk50 */
extern u16 D_8007AA80;    /* .actor.unk60 */

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_8000847C.s")

s32 func_80008540(PlayerState *arg0, Actor *arg1) {
    s32 ret = 0;

    if (!(arg1->unk60 & 1) && !(D_8004DCA0 & 0x80) && !(D_8008BE52 & 8)) {
        if (D_8008BE52 & 1) {
            if (!(D_8008BE52 & 0x202)) {
                if (func_80017AB0() == 0 && D_8008BE54 == 0) {
                    ret = 1;
                }
            }
        } else {
            ret = 1;
        }
    }
    return ret;
}

extern s16 D_8008C15A;
extern u16 D_8008C15C;
extern u16 D_80092C86;

s32 func_800168F0(s32 arg0, u16 arg1);
s32 func_800167B0(u16 count, u8 *seq);
#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_800085D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008840.s")

void func_80008970(PlayerState *arg0) {
    f32 dx;
    f32 dz;

    if (D_8008BE52 & 1) {
        dx = arg0->actor.x - D_8008BE64;
        dz = arg0->actor.z - D_8008BE68;
        D_8007A988 += sqrtf(dx * dx + dz * dz);
        while (D_8007A988 > 35.0) {
            D_8007A988 -= 35.0;
            arg0->unk14->unk2C++;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/3F50/func_80008A40.s")
