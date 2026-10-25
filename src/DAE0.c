#include "common.h"

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
void func_80028120();
void func_8000D19C(s32, f32, f32, f32, Unk8007C148 *);
u8 func_8000D398(u32);
void func_80020428(s32, Unk8007C174 *, void *, s32);
void func_8002099C(u16, Unk8007C174 *, void *);
void func_800131F0(f32, f32, f32, f32, f32, f32, f32);
void func_800201A0(Unk8007C174 *, s32, s32, s32, s32, s32);
void func_800107F0(f32, f32, f32, s32, Unk8007C0B0 *);

extern u8 D_8004F770[];
extern Gfx *D_8007A184;
extern Unk8007AA08 D_8007AA08;
extern Unk8007C0B0 D_8007C0B0;
extern u8 D_8007C13C[];
extern s32 D_8007C140;
extern Unk8007C148 D_8007C148;
extern Unk8007C174 D_8007C174;
extern s16 D_8007C1C6;
extern u16 D_8007C1CC;
extern u16 *D_8007C1D8;
extern f32 D_8007C178;
extern f32 D_8007C17C;
typedef struct {
    f32 unk24;
    f32 unk28;
} Unk8007C198;
extern Unk8007C198 D_8007C198;
extern f32 D_8007C1A0;
extern f32 D_8007C1A4;
extern f32 D_8007C1A8;
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
extern Unk8007C174 D_8007C0D0;
extern Unk803AB820 D_803AB4B0[];
extern s32 D_8004DCA0;
extern s16 D_8007A172;
extern s32 D_8007A174;
extern s16 D_8007A178;
extern s16 D_8007A17A;
extern u16 D_8004DD50[];
extern u16 D_8004DD60[];
extern Unk8007A9D0 D_8007A9D0;
void func_8001628C(Unk803AB820 *, Unk8007C174 *);
void func_80032D20(s32);

void func_8000CEE0(void) {
    D_8007C13C[0] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/DAE0/func_8000CEF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/DAE0/func_8000CFD8.s")

s32 func_8000D100(void) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/DAE0/func_8000D19C.s")

u8 func_8000D398(u32 arg0) {
    return D_8007C13C[arg0 >> 3] & D_8004F770[arg0 & 7];
}

void func_8000D3CC(u16 arg0) {
    D_8007C13C[arg0 >> 3] |= D_8004F770[arg0 & 7];
}

void func_8000D40C(s32 arg0) {
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
    func_8001628C(&D_803AB4B0[arg0], &D_8007C0D0);
}

void func_8000D528(s32 arg0) {
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
        func_80032D20(1);
        D_8007AA08.unk8 |= 0x10;
        D_8004DCA0 |= 0x80;
        D_8007A174 = 0x40;
        D_8007A178 = 3;
        D_8007A17A = 0x3E;
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
