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

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char unkC[0x64 - 0xC];
    /* 0x64 */ Struct_80026054_64* unk64;
} Struct_80026140;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AB36C;

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} Struct_803AAA40;

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Struct_80084300;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    char unk0[0xA];
} Struct_803AB358;

extern s32 D_8004DCA0;
extern s32 D_8007A174;
extern s16 D_8007A178;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern s16 D_8007AA0E;
extern Struct_80084300 D_80084300;
extern Vec3f D_8008C190;
extern Struct_803AAA40 D_803AAA40[];
extern Struct_803AB358 D_803AB358[];
extern Struct_803AB36C D_803AB36C[];

void func_8001AE24(Struct_80026140*, s32, s32);
void func_80019820(u16, u16, f32, f32, f32, f32, Struct_803AB358*, Vec3f*, Struct_80026140*);
void func_8002A7C8(s32, s32, s32);

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

void func_80025094(u8 arg0) {
    s32 i;

    for (i = 0; i < 0x96; i++) {
        if (D_8008C9B8[i] == 0xFF) {
            break;
        }
    }
    D_8008C9B8[i] = arg0;
}

s32 func_800250D8(u8 arg0) {
    s32 ret = 0;
    Struct_803AAAA0* item = &D_803AAAA0[arg0];

    if ((D_8008BE52 & 1) && (item->unk0 & 2)) {
        ret = 1;
    } else if (!(D_8008BE52 & 1) && (item->unk0 & 1)) {
        ret = 1;
    }
    if (ret) {
        ret = D_8004F4A0[item->unk2](D_8007AA20, item, arg0);
    }
    if (ret) {
        func_800079B4(arg0);
    }
    return ret;
}

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

void func_80026140(Struct_80026140* arg0, Struct_803AAAA0* arg1) {
    u16 amt;
    Struct_80026054_64* st = arg0->unk64;
    Struct_803AB358* fx;

    if (arg1->unk4 != 0) {
        amt = st->unk6 - st->unk4;
        if (arg1->unk4 < amt) {
            amt = arg1->unk4;
        }
        st->unk4 += amt;
        func_8001AE24(arg0, 1, amt);
    }
    if (arg1->unk6 != 0) {
        amt = st->unkA - st->unk8;
        if (arg1->unk6 < amt) {
            amt = arg1->unk6;
        }
        st->unk8 += amt;
        func_8001AE24(arg0, 2, amt);
    }
    D_8008C190.x = D_803AB36C[0].unk8;
    D_8008C190.y = D_803AB36C[0].unkC;
    fx = &D_803AB358[D_803AB36C[0].unk0];
    D_8008C190.z = 1.0f;
    func_80019820(D_803AB36C[0].unk2, D_803AB36C[0].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &D_8008C190, arg0);
    func_8002A7C8(0, 0xB, 0xFF);
}

void func_80026284(Struct_80026140* arg0, Struct_803AAAA0* arg1) {
    Struct_803AB358* fx;

    D_8004DCA0 |= 0x80;
    D_8007A174 = 0x16;
    D_80084300.unk0 = D_803AAA40[arg1->unk4].unk0;
    D_80084300.unk4 = D_803AAA40[arg1->unk4].unk2;
    D_80084300.unk8 = -1;
    D_8007A98C = D_803AAA40[arg1->unk4].unk4;
    D_8007A990 = D_803AAA40[arg1->unk4].unk8;
    D_8007A994 = D_803AAA40[arg1->unk4].unkC;
    D_8007A998 = 0x108;
    D_8007AA0E = 0;
    D_8007A178 = 1;
    D_8008C190.x = D_803AB36C[1].unk8;
    D_8008C190.y = D_803AB36C[1].unkC;
    fx = &D_803AB358[D_803AB36C[1].unk0];
    D_8008C190.z = 1.0f;
    func_80019820(D_803AB36C[1].unk2, D_803AB36C[1].unk4, arg0->unk0, arg0->unk4, arg0->unk8, 0.0f, fx, &D_8008C190, arg0);
    func_8002A7C8(0, 0x3B, 0xFF);
}

void func_80026400(s32 arg0, Struct_803AAAA0* arg1) {
    func_800169B8(arg0, arg1->unk4, 0, 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/25B20/func_80026430.s")
