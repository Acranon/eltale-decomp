#include "common.h"

typedef struct {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s16 unk4;
    /* 0x006 */ s16 unk6;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 unkE;
    /* 0x00F */ u8 unkF;
    /* 0x010 */ u8 unk10;
    /* 0x012 */ s16 unk12;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17[32];
    /* 0x038 */ s16 unk38;
    /* 0x03A */ s16 unk3A;
    /* 0x03C */ u8 unk3C[4][24];
    /* 0x09C */ u8 unk9C[0x4B0];
    /* 0x54C */ u8 unk54C[0x4B0];
} Unk80090470; /* size = 0x9FC */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} Unk800616A8;

typedef struct {
    /* 0x00 */ s32 n;
    /* 0x04 */ s32 m;
    /* 0x08 */ u8 *rows[4];
} Unk80090458;

typedef struct {
    /* 0x0 */ u8 v[8];
} Unk8Bytes;

typedef struct {
    /* 0x00 */ u8 v[32];
} Bytes32;

typedef struct {
    /* 0x00 */ u8 *p[5];
} TexPtrs5;

typedef struct {
    /* 0x00 */ s32 w;
    /* 0x04 */ s32 h;
    /* 0x08 */ s32 cms;
    /* 0x0C */ s32 cmt;
    /* 0x10 */ s32 masks;
    /* 0x14 */ s32 maskt;
} TexParam; /* size = 0x18 */

typedef struct {
    /* 0x00 */ TexParam e[5];
} TexParams5;

extern Gfx *D_8007A184;
extern TexPtrs5 D_800616D0;
extern TexParams5 D_800616E4;
extern Unk8Bytes D_800616B8;
extern Unk8Bytes D_800616C0;
extern Unk8Bytes D_800616C8;
extern u16 D_80061850[];
extern Unk800616A8 D_800616A8;
extern Unk800616A8 D_80061668[];
extern s8 D_80061660;
extern s8 D_800616B0;
extern u8 D_8007B8E0[32];
extern u8 D_8007B430[0x4B0];
extern s32 D_80090450;
extern Unk80090458 D_80090458;
extern s32 D_8004DCA0;
extern Unk80090470 D_80090470[4];
extern u8 D_80092C60;
extern u16 D_80092C62;
extern s8 D_80092C81;
extern s8 D_80092C82;

void func_80032BF8(s32 arg0, u8 arg1);
void func_80034C9C(s32, s32, s32, s32, s32);
void func_80035350(s32, s32, u8 *);
void func_8003521C(void);

void func_80032BB0(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80032BF8(i, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80032BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80032D20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80033050.s")

s32 func_8003403C(s32 idx) {
    Unk80090470 *p = &D_80090470[idx];
    s32 ret;
    s32 ww;
    s32 hh;
    s32 x;
    s32 y;
    s16 cx;
    s16 cy;
    u32 steps;

    ret = 0;
    cx = p->unk4 + (p->unk8 >> 1);
    cy = p->unk6 + (p->unkA >> 1);
    if (p->unk0 & 0x10000000) {
        steps = 10;
        ww = p->unk8 / steps;
        ww = p->unkC * ww;
        hh = p->unkA / steps;
        hh = p->unkC * hh;
    } else {
        steps = 8;
        ww = p->unk8 / steps;
        ww = (9 - p->unkC) * ww;
        hh = p->unkA / steps;
        hh = (9 - p->unkC) * hh;
    }
    x = cx - (ww >> 1);
    y = cy - (hh >> 1);
    func_80034C9C(0, x, y, ww, hh);
    func_80034C9C(3, x + ww, y + 3, 3, hh);
    func_80034C9C(3, x + 3, y + hh, ww, 3);
    func_80034C9C(3, x, y, ww, 1);
    func_80034C9C(3, x, y + hh - 1, ww, 1);
    func_80034C9C(3, x, y, 1, hh);
    func_80034C9C(3, x + ww - 1, y, 1, hh);
    p->unkC++;
    if (p->unkC > steps) {
        ret = -1;
    }
    return ret;
}

void func_80034274(s32 arg0) {
    s32 x;
    s32 y;

    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xCC);
    if (D_80090470[arg0].unk17[0] != 0xFF) {
        x = D_80090470[arg0].unk4;
        y = D_80090470[arg0].unk6;
        func_80034C9C(1, x + 27, y + 4, 40, 13);
        x = D_80090470[arg0].unk4;
        y = D_80090470[arg0].unk6;
        func_80035350(x + 73, y + 4, D_80090470[arg0].unk17);
        x = D_80090470[arg0].unk4;
        y = D_80090470[arg0].unk6;
        func_80035350(x + 10, y + 20, D_80090470[arg0].unk54C);
    } else {
        x = D_80090470[arg0].unk4;
        x = x + 10;
        y = D_80090470[arg0].unk6;
        y = y + 12;
        func_80035350(x, y, D_80090470[arg0].unk54C);
    }
}

void func_80034380(s32 idx) {
    Unk80090470 *p;
    s32 x;
    s32 y;

    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xCC);
    p = &D_80090470[idx];
    func_80034C9C(0, p->unk4, p->unk6, p->unk8, p->unkA);
    func_80034C9C(3, p->unk8 + p->unk4, p->unk6 + 2, 2, p->unkA);
    func_80034C9C(3, p->unk4 + 2, p->unkA + p->unk6, p->unk8, 2);
    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
    x = p->unk4;
    y = p->unk6;
    func_80034C9C(3, x, y, p->unk8, 1);
    func_80034C9C(3, x, p->unkA + y - 1, p->unk8, 1);
    func_80034C9C(3, x, y, 1, p->unkA);
    func_80034C9C(3, p->unk8 + x - 1, y, 1, p->unkA);
}

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_8003453C.s")

void func_800348B8(s32 idx) {
    s32 x;
    s32 y;
    s32 i;
    Unk8Bytes a = D_800616B8;
    Unk8Bytes b = D_800616C0;
    Unk8Bytes c = D_800616C8;

    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    gDPPipeSync(D_8007A184++);
    gDPLoadTLUT_pal256(D_8007A184++, D_80061850);
    D_80090470[idx].unkC++;
    i = (D_80090470[idx].unkC >> 1) & 7;
    x = D_80090470[idx].unk4 + D_80090470[idx].unk8 - 11;
    y = D_80090470[idx].unk6 + D_80090470[idx].unkA - 3;
    x -= c.v[i];
    func_80034C9C(3, x, y, b.v[i], 1);
    x = D_80090470[idx].unk4 + D_80090470[idx].unk8 - 12;
    y = D_80090470[idx].unk6 + D_80090470[idx].unkA - 15;
    x = a.v[i] + x;
    y -= a.v[i];
    func_80034C9C(2, x, y, 12, 12);
}

void func_80034B30(s32 arg0) {
    s32 max = 0;
    s32 n = D_80090470[arg0].unk38;
    s32 i;
    s32 j;
    s32 cnt;

    D_800616A8.unk6 = n * 13 + 12;
    for (i = 0; i < n; i++) {
        j = 0;
        cnt = 0;
        while (D_80090470[arg0].unk3C[i][j] != 0xFF) {
            if (D_80090470[arg0].unk3C[i][j] < 0x80) {
                cnt++;
            }
            j++;
        }
        if (max < cnt) {
            max = cnt;
        }
    }
    D_800616A8.unk4 = max * 10 + 24;
}

s32 func_80034C18(s32 arg0, s32 arg1) {
    s32 ret = -1;
    s32 i;

    if (arg0 >= 0) {
        for (i = 0; i < 4; i++) {
            if (arg0 == D_80090470[i].unkE) {
                ret = i;
                break;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (arg1 == (D_80090470[i].unk0 & 7)) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/337B0/func_80034C9C.s")

void func_8003509C(s32 x, s32 y, s32 w, s32 h) {
    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xCC);
    func_80034C9C(0, x, y, w, h);
    func_80034C9C(3, x + w, y + 2, 2, h);
    func_80034C9C(3, x + 2, y + h, w, 2);
    gDPPipeSync(D_8007A184++);
    gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
    func_80034C9C(3, x, y, w, 1);
    func_80034C9C(3, x, y + h - 1, w, 1);
    func_80034C9C(3, x, y, 1, h);
    func_80034C9C(3, x + w - 1, y, 1, h);
}

void func_8003521C(void) {
    D_80092C62 = 0;
}

s32 func_8003522C(void) {
    s32 ret = 0;
    u32 sum;

    if (D_80092C60 != 0) {
        sum = D_80092C81 * D_80092C81 + D_80092C82 * D_80092C82;
        if (sum > 60 * 60) {
            D_80092C62++;
            if (D_80092C62 >= 5) {
                ret = 1;
            }
        } else {
            D_80092C62 = 0;
        }
    }
    return ret;
}
