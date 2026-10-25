#include "common.h"

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ char unk8[4];
} Struct_803AAAA0;

typedef struct {
    char unk0[4];
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} Struct_80026054_64;

typedef struct {
    char unk0[0x64];
    Struct_80026054_64* unk64;
} Struct_80026054;

typedef struct {
    char unk0[0x14];
    u16 unk14;
} Struct_8007C288;

typedef s32 (*ItemFunc)(void*, Struct_803AAAA0*, u8);

extern u8 D_D384B0[];
extern ItemFunc D_8004F4A0[];
extern ItemFunc D_8004F4B0[];
extern u8 D_8007AA20[];
extern Struct_8007C288* D_8007C288;
extern u16 D_800842B8;
extern u16 D_8008BE52;
extern s32 D_8008C19C;
extern s32 D_8008C1A0;
extern s32 D_8008C1A4;
extern u8 D_8008C1B0[8];
extern u8 D_8008C9B8[0x97];
extern u8 D_8008CA4E;
extern u8 D_803AC460[];
extern Struct_803AAAA0 D_803AAAA0[];

void func_80028120(void*, void*, s32);
void func_800079B4(u8);
void func_800169B8(s32, s32, s32, s32);

void func_80024F20(void) {
    s32 i;
    u8* p;

    func_80028120(D_D384B0, D_803AC460, 0x400);
    i = 8;
    p = D_8008C1B0;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    i = 0x97;
    p = D_8008C9B8;
    do {
        i--;
        *p = 0xFF;
        p++;
    } while (i != 0);
    D_8008C19C = 0;
    D_8008C1A0 = 0;
    D_8008C1A4 = 0;
}

s32 func_80024FC4(void) {
    s32 ret;

    if (D_8008C9B8[0x95] != 0xFF) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 func_80024FF0(u8 arg0) {
    s32 count = 0;
    s32 i = 0x96;
    u8* p = D_8008C9B8;

    while (i != 0 && *p != 0xFF) {
        i--;
        if (arg0 == *p) {
            count++;
        }
        p++;
    }
    return count;
}

s32 func_8002504C(void) {
    s32 count = 0;
    s32 i = 0x96;
    u8* p = D_8008C9B8;

    while (i != 0 && *p != 0xFF) {
        i--;
        count++;
        p++;
    }
    return count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80025094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_800250D8.s")

void func_800251CC(u8 arg0, void* arg1) {
    D_8004F4B0[D_803AAAA0[arg0].unk2](arg1, &D_803AAAA0[arg0], arg0);
}

s32 func_80025228(u16 arg0) {
    s32 found = 0;
    u8* p = D_8008C9B8;
    s32 i = 0x96;
    Struct_803AAAA0* e;

    while (!found && *p != 0xFF) {
        e = &D_803AAAA0[*p++];
        if (e->unk2 == 0xF) {
            found = (arg0 == e->unk4);
        }
        i--;
    }
    if (found) {
        p--;
        while (i != 0) {
            *p = *(p + 1);
            p++;
            i--;
        }
        *p = 0xFF;
    }
    return found;
}

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80025318.s")

s32 func_80026040(s32 arg0, Struct_803AAAA0* arg1) {
    return 0;
}

s32 func_80026054(Struct_80026054* arg0, Struct_803AAAA0* arg1) {
    s32 ret = 0;
    Struct_80026054_64* temp = arg0->unk64;

    if ((arg1->unk4 != 0) && (temp->unk6 != temp->unk4)) {
        ret = 1;
    }
    if ((arg1->unk6 != 0) && (temp->unkA != temp->unk8)) {
        ret = 1;
    }
    return ret;
}

s32 func_800260A8(s32 arg0, Struct_803AAAA0* arg1) {
    s32 ret;

    if ((D_800842B8 & 0xA) || (D_8007C288->unk14 & 4)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

s32 func_800260F4(s32 arg0, Struct_803AAAA0* arg1) {
    s32 ret = 1;

    if ((D_8008BE52 & 0x100) && (arg1->unk0 & 8)) {
        ret = 0;
    }
    return ret;
}

void func_80026130(s32 arg0, Struct_803AAAA0* arg1) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80026140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80026284.s")

void func_80026400(s32 arg0, Struct_803AAAA0* arg1) {
    func_800169B8(arg0, arg1->unk4, 0, 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80026430.s")
