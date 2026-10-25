#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ s16 unk3E;
} Unk801C14E4; /* size 0x40 */

typedef struct {
    /* 0x0 */ u8 *unk0;
    /* 0x4 */ u8 *unk4;
    /* 0x8 */ u8 unk8;
} Unk8007A8E8; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 unk4[0x8];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk80085E48;

typedef struct {
    /* 0x0 */ u8 unk0[0x4];
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
} Unk8007A9D0;

typedef struct {
    /* 0x00 */ u8 unk0[0x12];
    /* 0x12 */ u16 unk12;
} Unk8007C288;

void func_80003494(void);
void func_800032E4(u8 *arg0, u8 *arg1);
void func_80009764(u16 arg0);
void func_800097F8(s32 arg0, s32 arg1);
void func_8000D6A0(void);
void func_80014550(void);
void func_80027430(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3);
void func_80027834(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);
void func_8002A338(s32 arg0);
void func_8002A6B8(s8 arg0);
void func_80032BB0(s32 arg0, s32 arg1);
void func_80032D20(u8 arg0);

extern s32 D_8004DCA0;
extern s32 D_8007A174;
extern u16 D_8007A178;
extern s16 D_8007A17A;
extern s32 D_8007A8E0;
extern s32 D_8007A8E4;
extern Unk8007A8E8 *D_8007A8E8;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A998;
extern Unk8007A9D0 D_8007A9D0;
extern s16 D_8007AA0E;
extern s32 D_8007ABA4;
extern u8 D_8007B430[];
extern u8 D_8007B8E0[];
extern s32 D_8007B900;
extern Unk8007C288 *D_8007C288;
extern s32 D_800842BC;
extern s32 D_800842C4;
extern s32 D_800842C8;
extern s32 D_80084308;
extern Unk80085E48 D_80085E48;
extern f32 D_80085E54;
extern f32 D_80085E58;
extern f32 D_80085E5C;
extern f32 D_80085E60;
extern f32 D_80085E64;
extern f32 D_80085E68;
extern f32 D_80085F50;
extern s32 D_80090450;
extern Unk801C14E4 D_801C14E4[];

void func_80002F40(s32 arg0) {
    Unk801C14E4 *entry = &D_801C14E4[arg0];
    f32 mtx[4][4];

    D_8007A8E8 = entry->unk34;
    D_8007A8E4 = entry->unk38;
    D_8007A8E0 = 0x3C;
    D_800842BC = -1;
    D_800842C4 = entry->unk0;
    D_800842C8 = entry->unk4;
    func_80032BB0(0, arg0);
    D_80090450 = 0;
    D_80084308 = -1;
    func_8000D6A0();
    D_8007A98C = entry->unk20;
    D_8007A990 = entry->unk24;
    D_8007A994 = entry->unk28;
    D_8007A998 = 0x108;
    D_8007AA0E = 0;
    D_8007A9D0.unk4 = D_8007A9D0.unk6;
    func_80003494();
    if (!(entry->unk3C & 1)) {
        D_8004DCA0 |= 0x10000;
    }
    D_8007ABA4 = 0;
    func_80009764(D_8007C288->unk12);
    func_800097F8(entry->unk2C, entry->unk30);
    D_8007B900 = 0;
    func_80014550();
    D_80085E48.unk0 = 3;
    D_80085E54 = entry->unk8;
    D_80085E58 = entry->unkC;
    D_80085E5C = entry->unk10;
    func_80027430(mtx, -entry->unk14 * 0.017453292519943295, -entry->unk18 * 0.017453292519943295, 0.0f);
    func_80027834(mtx, 0.0f, 0.0f, -100.0f, &D_80085E60, &D_80085E64, &D_80085E68);
    D_80085E48.unk18 = D_80085E48.unk18 + D_80085E48.unkC;
    D_80085E48.unk1C = D_80085E48.unk1C + D_80085E48.unk10;
    D_80085E48.unk20 = D_80085E48.unk14 - D_80085E48.unk20;
    D_80085F50 = entry->unk1C;
    func_8002A6B8(((s8 *)&entry->unk3E)[1]);
}

s32 func_80003184(void) {
    s32 ret = 0;

    if (D_8007A8E0 == 0) {
        if (D_8007A8E4 != 0) {
            func_800032E4(D_8007A8E8->unk0, D_8007A8E8->unk4);
            func_80032D20(D_8007A8E8->unk8);
            D_8007A8E0 = 0xF;
            D_8007A8E8++;
            D_8007A8E4--;
        } else {
            D_8004DCA0 |= 0x80;
            D_8007A174 = 0x31;
            D_8007A178 = 2;
            D_8007A17A = 0x2F;
            D_8007A8E0 = 0x32;
            ret = 1;
        }
    } else if (D_80090450 == 0) {
        D_8007A8E0--;
    }
    return ret;
}

void func_8000328C(u32 arg0) {
    Unk801C14E4 *entry;

    if (arg0 > 6) {
        func_8002A338(0x40);
    } else {
        entry = &D_801C14E4[arg0];
        if (entry->unk3E != (entry - 1)->unk3E) {
            func_8002A338(0x40);
        }
    }
}

void func_800032E4(u8 *arg0, u8 *arg1) {
    s32 i;
    u8 *dst;

    dst = D_8007B430;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *arg0++;
    }
    dst = D_8007B8E0;
    for (i = 0x20; i != 0; i--) {
        *dst++ = *arg1++;
    }
}
