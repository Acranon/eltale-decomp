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
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8 pad6[6];
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

extern Unk80085F98 D_80085F98[];
extern Unk80086358 D_80086358[];
extern s32 D_80085F90;
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
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk17360Vec2;

extern Unk17360Vec2 D_800863B8;
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
    /* 0x18 */ u8 pad18[0xF8];
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
s32 func_80007E04(s32, Actor17360*);
s32 func_8000C3FC(Actor17360*, Actor17360*);
s32 func_8000CAB8(Actor17360*);
s32 func_8000C528(s32, s32, s32, s32, s32);
void func_80007FD8(u16, s32, s32);
void func_80023D28(Actor17360*);
u32 func_80026E90(u32);
f32 sqrtf(f32);
void func_800271B4(f32, Unk17360Vec2*);

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

void func_80016EA8(Unk17360Cam* arg0, Actor17360* arg1) {
    arg0->x = arg1->x;
    arg0->z = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        arg0->y = arg1->unk68->unk94 + arg1->unk64->unk18 * arg1->scale + arg0->cfg->unk1C;
    } else {
        arg0->y = arg1->y + 2.0 * arg1->unk64->unk1C * arg1->scale + arg0->cfg->unk1C;
    }
}

void func_80016F3C(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_80017028(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_80017134(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_80017244(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_800172D0(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_8001744C(Unk17360Cam* arg0, Actor17360* arg1) {
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

void func_80017590(Unk17360Cam* arg0, Actor17360* arg1) {
    D_800863B8.x = 0.0f;
    D_800863B8.y = 380.0f;
    func_800271B4(arg1->ry, &D_800863B8);
    arg0->x = arg1->x + D_800863B8.x * arg1->scale;
    arg0->y = arg1->y + 380.0f * arg1->scale;
    arg0->z = arg1->z + D_800863B8.y * arg1->scale;
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80017630.s")

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

void func_80018AAC(Unk17360Cam* arg0, Actor17360* arg1) {
    if (arg0->cfg->unk18 != 2) {
        if (arg1->unk5E & 1) {
            func_8000C528(func_8000CAB8(arg1), 0, 0, 4, arg0->unk24);
            D_8007AA1C->unk2A++;
        } else {
            func_80007FD8(0, 4, arg0->unk24);
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

void func_80018C14(Unk17360Cam* arg0, Actor17360* arg1) {
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
        func_80007FD8(arg1->unk64->unk4 * 4, 4, arg0->unk24);
    }
}

void func_80018CD8(s32 arg0, Actor17360* arg1) {
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

void func_80018D88(s32 arg0, Actor17360* arg1) {
    func_80018480(arg0, arg1);
    func_80018CD8(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80018DC0.s")

void func_80018FB0(Unk80018FB0* arg0) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800195FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019820.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_800199C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019BFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/17360/func_80019FC8.s")

void func_8001A1A4(Actor17360* arg0) {
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

void func_8001A340(s32 arg0) {
    s32 i;

    D_8007AA08.unk110 &= ~D_8004ED34[arg0];
    for (i = 0; i < 6; i++) {
        D_8007B908[i].unk124 &= ~D_8004ED34[arg0];
    }
}

s32 func_8001A3EC(Unk8001A3EC* arg0, Actor17360* arg1) {
    s32 ret;

    if (arg0->unkA & 4) {
        ret = 2;
    } else {
        ret = func_80026E90(100) < arg0->unk2C->unkE;
        if (ret != 0) {
            if (arg1 != arg0->unk24) {
                if (arg1->unk5E & 1) {
                    ret = func_80007E04(func_8000CAB8(arg1), arg0->unk24);
                } else {
                    ret = func_8000C3FC(arg0->unk24, arg1);
                }
            }
            ret++;
        }
    }
    return D_8004EDA4[ret];
}

s32 func_8001A4AC(Unk8001A3EC* arg0, Actor17360* arg1, s32 arg2) {
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

void func_8001A56C(Unk8001A3EC* arg0, Actor17360* arg1, s32 arg2) {
    if (arg1 != arg0->unk24) {
        arg1->unk68->timers[arg2] = func_80026E90(D_8004EDBC[arg2]) + 2;
    } else {
        arg1->unk68->timers[arg2] = func_80026E90(D_8004EDEC[arg2]) + 3;
    }
}
