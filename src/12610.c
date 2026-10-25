#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
} Unk80084300;

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[4];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u16 unk1E[3];
} Unk80011A10Arg;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 *unk10;
    /* 0x14 */ s32 *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 *unk24;
    /* 0x28 */ s32 *unk28;
    /* 0x2C */ s32 *unk2C;
} Unk80084998; /* size 0x30 */

extern Unk80084300 D_80084300;
extern u16 *D_80084318;
extern s32 D_80084340;
extern s32 D_8008433C;
extern u16 *D_80084344;
extern u16 *D_80084348;
extern u16 D_80084350[];
extern s32 D_80084980;
extern s32 D_80084984;
extern s32 D_80084988;
extern u16 D_80084990;
extern Unk80084998 D_80084998[8];
extern s32 D_80084B18[4][3];
extern s32 D_8008C164;

void func_80011A10(Unk80011A10Arg *arg0) {
    D_80084318 = arg0->unk1E;
    D_80084300.unk0 = D_80084318[0];
    D_80084300.unk4 = D_80084318[1];
    D_80084300.unk8 = D_80084318[2];
    D_80084300.unkC = arg0->unk14;
    D_80084300.unk10 = arg0->unk1A;
    D_80084300.unk14 = arg0->unk8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80011A60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80011AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80011C60.s")

void func_80011EA0(s32 arg0) {
    D_80084980 = arg0;
    if (D_80084984 <= D_80084980) {
        D_80084980 = D_80084980 - D_80084984;
        if (D_80084990 < 9999) {
            D_80084990++;
        }
    }
    D_80084988 = D_80084980;
}

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80011EF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_800124E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_8001263C.s")

void func_80012800(s32 arg0, u16 *arg1, u16 *arg2) {
    u16 *dst;
    u32 i;

    D_8008433C = D_80084340 = arg0;
    D_80084344 = arg1;
    D_80084348 = arg2;
    dst = D_80084350;
    i = 0x100;
    while (i--) {
        *dst++ = *arg2++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80012854.s")

void func_80012A60(void) {
    Unk80084998 *p = D_80084998;
    s32 i = 8;

    do {
        p->unk0 = 0;
        p++;
        i--;
    } while (i != 0);
}

s32 func_80012A90(void) {
    Unk80084998 *p = &D_80084998[7];
    s32 i = 7;

    while (p->unk0 != 0) {
        i--;
        p--;
        if (i == 0) {
            break;
        }
    }
    p->unk0 = 1;
    p->unk4 = 0;
    p->unk18 = 0;
    p->unk2C = 0;
    return i;
}

void func_80012AE0(s32 arg0) {
    D_80084998[arg0].unk0 = 0;
}

void func_80012B00(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    Unk80084998 *p = &D_80084998[arg0];

    p->unk4 = arg1;
    p->unk8 = p->unkC = arg2;
    p->unk10 = p->unk14 = arg3;
}

void func_80012B34(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    Unk80084998 *p = &D_80084998[arg0];

    p->unk18 = arg1;
    p->unk20 = p->unk1C = arg2;
    p->unk24 = p->unk28 = arg3;
}

void func_80012B68(s32 arg0, s32 *arg1) {
    D_80084998[arg0].unk2C = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/12610/func_80012B88.s")

void func_800130F8(Lights3 *arg0, s32 (*arg1)[3], s32 (*arg2)[3]) {
    arg0->l[1].l.dir[0] = (*arg2)[0];
    arg0->l[1].l.dir[1] = (*arg2)[1];
    arg0->l[1].l.dir[2] = (*arg2)[2];
    arg2++;
    arg0->l[2].l.dir[0] = arg0->l[0].l.dir[0] = (*arg2)[0];
    arg0->l[2].l.dir[1] = arg0->l[0].l.dir[1] = (*arg2)[1];
    arg0->l[2].l.dir[2] = arg0->l[0].l.dir[2] = (*arg2)[2];
    arg0->a.l.col[0] = arg0->a.l.colc[0] = (*arg1)[0];
    arg0->a.l.col[1] = arg0->a.l.colc[1] = (*arg1)[1];
    arg0->a.l.col[2] = arg0->a.l.colc[2] = (*arg1)[2];
    arg1++;
    arg0->l[1].l.col[0] = arg0->l[1].l.colc[0] = (*arg1)[0];
    arg0->l[1].l.col[1] = arg0->l[1].l.colc[1] = (*arg1)[1];
    arg0->l[1].l.col[2] = arg0->l[1].l.colc[2] = (*arg1)[2];
    arg1++;
    arg0->l[0].l.col[0] = arg0->l[0].l.colc[0] = (*arg1)[0];
    arg0->l[0].l.col[1] = arg0->l[0].l.colc[1] = (*arg1)[1];
    arg0->l[0].l.col[2] = arg0->l[0].l.colc[2] = (*arg1)[2];
    arg0->l[2].l.col[0] = arg0->l[2].l.colc[0] = (*arg1)[0];
    arg0->l[2].l.col[1] = arg0->l[2].l.colc[1] = (*arg1)[1];
    arg0->l[2].l.col[2] = arg0->l[2].l.colc[2] = (*arg1)[2];
}
