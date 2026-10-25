#include "common.h"

typedef struct {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} Unk80092EDC;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Unk80092EDC *unk18;
    /* 0x1C */ void *unk1C;
} Unk801D8620; /* size = 0x20 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x04 */ void *unk4;
} Unk80092EE8; /* size = 0x8 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk80085E48;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
} Unk8007A9D0;

extern s32 D_8004DCA0;
extern s16 D_8007A170;
extern s32 D_8007A174;
extern s16 D_8007A178;
extern s16 D_8007A17A;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern Unk8007A9D0 D_8007A9D0;
extern s16 D_8007AA0E;
extern s32 D_8007ABA4;
extern s32 D_8007B900;
extern s32 D_800842BC;
extern s32 D_800842C4;
extern s32 D_800842C8;
extern s32 D_80084308;
extern s32 D_80084980;
extern Unk80085E48 D_80085E48;
extern f32 D_80085F50;
extern s32 D_80090450;
extern s32 D_80092ED0;
extern s32 D_80092ED4;
extern s32 D_80092ED8;
extern Unk80092EDC *D_80092EDC;
extern s32 D_80092EE0;
extern void *D_80092EE4;
extern Unk80092EE8 D_80092EE8[32];
extern Unk801D8620 D_801D8620[];

void func_80003494(void);
void func_8000D6A0(void);
void func_80014550(void);
void func_8002A338(s32);
void func_80026A00(Unk80092EDC *, f32 *, s32);
void func_80027430(f32 (*)[4], f32, f32, f32);
void func_80027834(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_80032BB0(s32, Unk80092EDC **);
void func_80036544(Unk80092EDC *arg0, s32 frame);

void func_80036260(void) {
    D_80092ED0 = 0;
    D_80084980 = 0x34BC;
}

void func_8003627C(void) {
    Unk801D8620 *e = &D_801D8620[D_80092ED0++];
    s32 i;

    D_80092EDC = e->unk18;
    D_80092ED4 = 0;
    D_80092ED8 = D_80092EDC->unk6;
    D_800842BC = -1;
    D_800842C4 = e->unk0;
    D_800842C8 = e->unk4;
    func_80032BB0(0, &D_80092EDC);
    D_80090450 = 0;
    D_80084308 = -1;
    func_8000D6A0();
    if (e->unk8 & 1) {
        D_8007A98C = e->unkC;
        D_8007A990 = e->unk10;
        D_8007A994 = e->unk14;
        D_8007A998 = 0x108;
        D_8007A9D0.unk4 = D_8007A9D0.unk6;
        D_8007AA0E = 0;
        func_80003494();
    } else {
        D_8004DCA0 |= 0x10000;
    }
    func_80014550();
    D_80085E48.unk0 = 3;
    D_80085F50 = 35.0f;
    func_80036544(D_80092EDC, D_80092ED4);
    D_8007ABA4 = 0;
    D_8007B900 = 0;
    D_80092EE0 = 0;
    D_80092EE4 = e->unk1C;
    for (i = 0; i < 32; i++) {
        D_80092EE8[i].unk0 = 0;
    }
}

void func_8003642C(void) {
    func_80036544(D_80092EDC, D_80092ED4++);
    if (D_80092ED8 - D_80092ED4 == 0x31) {
        if (!(D_8004DCA0 & 0x80)) {
            D_8004DCA0 |= 0x80;
            D_8007A178 = 2;
            if (D_80092ED0 >= 14) {
                D_8007A174 = 0x14E;
                D_8007A17A = 0x14C;
                func_8002A338(0x12C);
            } else {
                D_8007A174 = 0x31;
                D_8007A17A = 0x2F;
            }
        }
    }
}

void func_800364F4(void) {
    if (D_80092ED0 < 14) {
        D_8004DCA0 |= 0x60;
    } else {
        D_8007A170 = 0;
        D_8004DCA0 |= 0x8240;
    }
}

void func_80036544(Unk80092EDC *arg0, s32 frame) {
    f32 buf[9];
    f32 m[4][4];

    if (arg0->unk6 < frame) {
        frame = arg0->unk6;
    }
    func_80026A00(arg0, buf, frame);
    D_80085E48.unkC = buf[0];
    D_80085E48.unk10 = buf[1];
    D_80085E48.unk14 = buf[2];
    func_80027430(m, -buf[4] * 0.0174532925199432955, -buf[3] * 0.0174532925199432955, buf[5] * 0.0174532925199432955);
    func_80027834(m, 0.0f, 0.0f, -100.0f, &D_80085E48.unk18, &D_80085E48.unk1C, &D_80085E48.unk20);
    D_80085E48.unk18 += D_80085E48.unkC;
    D_80085E48.unk1C += D_80085E48.unk10;
    D_80085E48.unk20 = D_80085E48.unk14 - D_80085E48.unk20;
}

#pragma GLOBAL_ASM("asm/nonmatchings/36E60/func_80036664.s")
