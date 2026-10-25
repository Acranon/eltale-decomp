#include "common.h"

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
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ u8 unk2C[0x50];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ u8 pad7E[0xB2];
} Unk8007B908_b; // size = 0x130

extern u8 D_8007AA20[];

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk17360Model;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x88];
    /* 0x8A */ u16 unk8A;
    /* 0x8C */ u16 unk8C;
    /* 0x8E */ u8 pad8E[6];
    /* 0x94 */ f32 unk94;
} Unk17360Data;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x38];
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

extern Unk80085F98 D_80085F98[];
extern Unk80086358 D_80086358[];
extern s32 D_80085F90;
extern u16 D_8004ED34[];
extern u16 D_8007AB18;
extern Unk8007B908 D_8007B908[];
extern u16 D_8008BE52;

void func_80018480(s32, Actor17360*);
void func_80018CD8(s32, Actor17360*);
s32 func_8001809C(Unk80018444*);
void func_8002373C(Actor17360*, s32, u16, s32);
void func_8002433C(Actor17360*);

void func_80016760(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80085F98[i].unk4 = 0;
    }
    for (i = 0; i < 4; i++) {
        D_80086358[i].unk0 = 0;
    }
    D_80085F90 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800167B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800168F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800169B8.s")

void func_80016DE0(Unk80016DE0* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 - arg1->unk64->unk18 * arg1->scale;
    } else {
        arg0->y = arg1->y;
    }
}

void func_80016E34(Unk80016DE0* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94;
    } else {
        arg0->y = arg1->y + arg1->unk64->unk1C * 0.5 * arg1->scale;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80016EA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80016F3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017028.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017134.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017244.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800172D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001744C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017590.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017AB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017AEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001809C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018348.s")

s32 func_80018444(Unk80018444* arg0) {
    s32 ret = 0;

    if (arg0->unkA & 1) {
        ret = func_8001809C(arg0);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018480.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001860C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800187C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018968.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800189F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018AAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018C14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018CD8.s")

void func_80018D88(s32 arg0, Actor17360* arg1) {
    func_80018480(arg0, arg1);
    func_80018CD8(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018DC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018FB0.s")

void func_80019024(Unk80019024* arg0) {
    arg0->unk28 = arg0->unk24;
}

void func_80019034(s32 arg0, Actor17360* arg1) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001920C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800192C8.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800194E0.s")

void func_800195E0(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk0 |= 0x800;
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800195FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019820.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800199C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019BFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019FC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001A1A4.s")

s32 func_8001A2A0(s32 arg0, Actor17360* arg1) {
    return D_8004ED34[arg0] & arg1->unk68->unk8C;
}

void func_8001A2C4(s32 arg0, Actor17360* arg1) {
    arg1->unk68->unk8C |= D_8004ED34[arg0];
}

void func_8001A2EC(void) {
    s32 i;

    D_8007AB18 = 0;
    for (i = 0; i < 6; i++) {
        D_8007B908[i].unk124 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001A340.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001A3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001A4AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_8001A56C.s")
