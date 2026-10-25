#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk0[0xC8];
} Unk80090228; /* size = 0xC8 */

extern Gfx D_80061770[];
extern s16 D_8007A170;
extern Gfx *D_8007A184;
extern u16 D_8008FB3E;
extern u16 D_8008FB70;
extern s8 D_8008FB72;
extern s8 D_8008FB73;
extern s32 D_8008FB74;
extern u8 D_8008FB78;
extern s8 D_8008FB79;
extern s8 D_8008FB7A;
extern s8 D_8008FB7B;
extern u8 D_8008FB7C;
extern s8 D_8008FB80[];
extern u8 D_8008FB81[];
extern Unk80090228 D_80090228;
extern u8 D_80090370[];
extern s8 D_80092C80;

void func_8002FBE0(void);
void func_8002FDB8(void);
void func_800301DC(void);
void func_80030D5C(s32);
void func_80031B28(void);
void func_80031B68(void);
void func_80031C9C(void);
void func_80031E10(void);
void func_80032134(void);
void func_80032558(void);
void func_800329B0(s32);
u8 func_80035E24(s32, u8);
s32 func_80035EA8(s32, s32, s32, s32, u8 *);
s32 func_80035F94(s32, s32);
s32 func_8003609C(s32);
void func_8003D8EC(const char *, ...);

void func_8002FA00(s32 arg0) {
    D_8007A170 = 2;
    D_8008FB3E = D_8008FB3E | arg0 | 0x4000;
    D_8008FB70 = 0x1000;
    D_8008FB78 = 0xFF;
    D_8008FB7A = 0;
    D_8008FB79 = 0;
    D_8008FB72 = 0;
    D_8008FB7B = 0;
    D_8008FB7C = 0;
}

void func_8002FA6C(void) {
    func_80032558();
    if (!(D_8008FB70 & 0x4000)) {
        if (D_8008FB70 & 0x2000) {
            func_8002FDB8();
            D_8008FB70 |= 0x4000;
            D_8008FB70 &= ~0x2000;
            D_8008FB7C = 0;
        } else {
            D_8008FB70 |= 0x2000;
            D_8008FB73 = 0;
        }
    }
    if (D_8008FB70 & 0x4000) {
        switch (D_8008FB70 & 7) {
            case 5:
                func_800301DC();
                break;
            case 0:
                func_80030D5C(0);
                break;
            case 4:
                func_80031B68();
                break;
            case 2:
                func_80031C9C();
                break;
            case 3:
                func_80031E10();
                break;
            case 1:
                func_80032134();
                break;
            case 6:
                func_80031B28();
                break;
        }
    }
    if (D_8008FB70 & 0x2000) {
        func_8002FBE0();
    }
    if (D_8008FB70 & 0x8000) {
        D_8008FB3E &= 0x7FFF;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_8002FBE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_8002FDB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_800301DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_80030D5C.s")

void func_80031B28(void) {
    D_8008FB79--;
    if (D_8008FB79 < 0) {
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 0;
    }
}

void func_80031B68(void) {
    s32 err = func_80035E24(D_80092C80, D_8008FB81[D_8008FB7A * 2]);

    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 12;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
    } else {
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        D_8008FB72 = 22;
        D_8008FB79 = 10;
        ((s8 *)D_8008FB81)[D_8008FB7A * 2] = -1;
    }
}

void func_80031C9C(void) {
    s32 err = func_80035EA8(D_80092C80, D_8008FB80[D_8008FB7A * 2], 0x80, 0xE0, D_80090370);

    D_80090228 = *(Unk80090228 *)D_80090370;
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 11;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
    } else {
        func_800329B0(D_8008FB7A);
        D_8008FB70 |= 0x80;
        D_8008FB70 |= 0x8000;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_80031E10.s")

void func_80032134(void) {
    s32 err;

    func_8003D8EC("Repair Info %d %d\n", D_8008FB7A, D_8008FB74);
    err = func_80035F94(D_8008FB80[D_8008FB7A * 2], D_8008FB74);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 3:
                D_8008FB72 = 16;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 &= ~0x4000;
        D_8008FB70 |= 0x1000;
    } else {
        D_8008FB70 &= ~0x2000;
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 &= ~0x4000;
        D_8008FB70 |= 0x1000;
        D_8008FB7C++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_8003226C.s")

void func_800324F4(void) {
    gSPDisplayList(D_8007A184++, D_80061770);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    D_8008FB3E &= ~0x10;
}

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_80032558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_800327BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_800329B0.s")
