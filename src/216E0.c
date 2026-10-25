#include "common.h"

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x1C - 0x8];
    /* 0x1C */ f32 unk1C;
} Struct_80024338_64;

typedef struct {
    /* 0x00 */ char unk0[0x94];
    /* 0x94 */ f32 unk94;
} Struct_80024338_68;

typedef struct {
    /* 0x00 */ char unk0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0x24 - 0x8];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ char unk28[0x64 - 0x28];
    /* 0x64 */ u16* unk64;
    /* 0x68 */ Struct_80024338_68* unk68;
} Struct_8002433C_arg;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x04 */ Struct_8002433C_arg* unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} Struct_8008C058;

extern Struct_8008C058 D_8008C058[8];
extern u8** D_800C03D8[];
extern u8 D_8004F2C4[];
extern u8 D_8004F498[];

u32 func_800167B0(u16, s32);
s32 func_800168F0(u32, u16);
s32 func_800281F0(s32, u8*, u16);
void func_80024694(s32, s32, u8, u8*);
s32 func_80024904(u8*);
void func_80024A54(s32, s32, s32, s32, s32);
void func_80024D40(s32, s32, s32, s32, s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80020AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80020B78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800213A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80021C04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80022970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800230A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800231C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800232A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_8002338C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800235D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_8002373C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80023E14.s")

void func_8002430C(void) {
    Struct_8008C058* p = D_8008C058;
    s32 i = 8;

    while (i > 0) {
        p->unk0 = 0;
        p++;
        i--;
    }
}

void func_8002433C(Struct_8002433C_arg* arg0) {
    Struct_8008C058* p = D_8008C058;
    s32 i = 7;

    while (i != 0 && p->unk0 != 0) {
        i--;
        p++;
    }
    p->unk0 = 0x2D;
    p->unk4 = arg0;
    p->unk10 = 0.0f;
    p->unk8 = 0.0f;
    if (*arg0->unk64 == 0) {
        p->unkC = ((Struct_80024338_64*) arg0->unk64)->unk1C * arg0->unk24;
    } else if (*arg0->unk64 == 1) {
        p->unkC = arg0->unk68->unk94 - arg0->unk4;
    } else {
        p->unkC = arg0->unk24 * 600.0;
    }
    p->unk14 = 0x23;
    p->unk16 = 0x31;
    p->unk18 = 0x29;
    p->unk1A = 0xE;
}

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_8002440C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_800245D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80024694.s")

s32 func_80024904(u8* str) {
    s32 w = 0;

    while (*str != 0xFF) {
        if (!(*str & 0x80)) {
            w += 8;
        } else if (*str == 0x80 || *str == 0x81) {
            w += 1;
        } else if (*str == 0x82) {
            w += 4;
        }
        str++;
    }
    return w;
}

void func_80024974(u16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    u8* p;
    u8 buf[8];

    p = buf;
    for (n = func_800281F0(arg3, buf, arg0); n != 0; n--) {
        if (*p != 0x20) {
            func_80024D40(arg1, arg2, 8, 0xA, *p * 8 + 0x20, 0x1D, 0x400, 0x400);
            arg1 += 7;
        } else if (arg0 & 6) {
            arg1 += 7;
        }
        p++;
    }
}

void func_80024A4C(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80024A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/func_80024D40.s")

void func_80024EB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_80024A54(arg0, arg5, arg6, arg3, arg4);
    func_80024D40(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/216E0/D_8006F530.s")
