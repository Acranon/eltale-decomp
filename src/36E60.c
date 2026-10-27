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
    /* 0x00 */ u16 frame;
    /* 0x02 */ u16 dur;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 w;
    /* 0x0A */ s16 h;
    /* 0x0C */ u16 *tlut;
    /* 0x10 */ u8 *img;
} Cue; /* size = 0x14 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x04 */ Cue *unk4;
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
/* .bss 80092ED0..80092FF0 */
s32 D_80092ED0;
s32 D_80092ED4;
s32 D_80092ED8;
Unk80092EDC *D_80092EDC;
s32 D_80092EE0;
Cue *D_80092EE4;
Unk80092EE8 D_80092EE8[32];
extern Gfx *D_8007A184;
/* This file's .data, 80061850..8006CD00: textures and palettes (assets; the
 * converter put a gsSPEndDisplayList word after most images), message text
 * (assets), the message pointer tables and layouts, flags and a display list. */
u16 D_80061850[0x100] = {
#include "assets/D_80061850.inc.c"
};
u8 D_80061A50[0x100] = {
#include "assets/D_80061A50.inc.c"
};
u8 D_80061B50[0x208] = {
#include "assets/D_80061B50.inc.c"
};
u8 D_80061D58[0x90] = {
#include "assets/D_80061D58.inc.c"
};
u8 D_80061DE8[0x10] = {
#include "assets/D_80061DE8.inc.c"
};
u8 D_80061DF8[0xA0] = {
#include "assets/D_80061DF8.inc.c"
};
u16 D_80061E98[0x104] = {
#include "assets/D_80061E98.inc.c"
};
u8 D_800620A0[0x108] = {
#include "assets/D_800620A0.inc.c"
};
u8 D_800621A8[0xD8] = {
#include "assets/D_800621A8.inc.c"
};
u8 D_80062280[0x10] = {
#include "assets/D_80062280.inc.c"
};
u8 D_80062290[0x10] = {
#include "assets/D_80062290.inc.c"
};
u8 D_800622A0[0x98] = {
#include "assets/D_800622A0.inc.c"
};
u8 D_80062338[0x48] = {
#include "assets/D_80062338.inc.c"
};
u8 D_80062380[0xB8] = {
#include "assets/D_80062380.inc.c"
};
u8 D_80062438[0xB8] = {
#include "assets/D_80062438.inc.c"
};
u8 D_800624F0[0x10] = {
#include "assets/D_800624F0.inc.c"
};
u8 D_80062500[0x10] = {
#include "assets/D_80062500.inc.c"
};
u8 D_80062510[0x58] = {
#include "assets/D_80062510.inc.c"
};
u8 D_80062568[0x58] = {
#include "assets/D_80062568.inc.c"
};
u8 D_800625C0[0x58] = {
#include "assets/D_800625C0.inc.c"
};
u8 D_80062618[0x58] = {
#include "assets/D_80062618.inc.c"
};
u8 D_80062670[0x58] = {
#include "assets/D_80062670.inc.c"
};
u8 D_800626C8[0x58] = {
#include "assets/D_800626C8.inc.c"
};
u8 D_80062720[0x58] = {
#include "assets/D_80062720.inc.c"
};
u8 D_80062778[0x58] = {
#include "assets/D_80062778.inc.c"
};
u8 D_800627D0[0x58] = {
#include "assets/D_800627D0.inc.c"
};
u8 D_80062828[0x58] = {
#include "assets/D_80062828.inc.c"
};
u8 D_80062880[0x58] = {
#include "assets/D_80062880.inc.c"
};
u8 D_800628D8[0x58] = {
#include "assets/D_800628D8.inc.c"
};
u8 D_80062930[0x58] = {
#include "assets/D_80062930.inc.c"
};
u8 D_80062988[0x58] = {
#include "assets/D_80062988.inc.c"
};
u8 D_800629E0[0x58] = {
#include "assets/D_800629E0.inc.c"
};
u8 D_80062A38[0x58] = {
#include "assets/D_80062A38.inc.c"
};
u8 D_80062A90[0x438] = {
#include "assets/D_80062A90.inc.c"
};
u8 D_80062EC8[0x170] = {
#include "assets/D_80062EC8.inc.c"
};
u8 D_80063038[0x178] = {
#include "assets/D_80063038.inc.c"
};
u8 D_800631B0[0x228] = {
#include "assets/D_800631B0.inc.c"
};
u8 D_800633D8[0x1B0] = {
#include "assets/D_800633D8.inc.c"
};
u8 D_80063588[0x10] = {
#include "assets/D_80063588.inc.c"
};
u8 D_80063598[0xE8] = {
#include "assets/D_80063598.inc.c"
};
u8 D_80063680[0x4C0] = {
#include "assets/D_80063680.inc.c"
};
u8 D_80063B40[0x290] = {
#include "assets/D_80063B40.inc.c"
};
u8 D_80063DD0[0x200] = {
#include "assets/D_80063DD0.inc.c"
};
u8 D_80063FD0[0x258] = {
#include "assets/D_80063FD0.inc.c"
};
u8 D_80064228[0xF8] = {
#include "assets/D_80064228.inc.c"
};
u8 D_80064320[0x60] = {
#include "assets/D_80064320.inc.c"
};
u8 D_80064380[0x60] = {
#include "assets/D_80064380.inc.c"
};
u8 D_800643E0[0x60] = {
#include "assets/D_800643E0.inc.c"
};
u8 D_80064440[0xF8] = {
#include "assets/D_80064440.inc.c"
};
u8 D_80064538[0xF8] = {
#include "assets/D_80064538.inc.c"
};
u8 D_80064630[0x3A8] = {
#include "assets/D_80064630.inc.c"
};
u8 D_800649D8[0xC8] = {
#include "assets/D_800649D8.inc.c"
};
u8 D_80064AA0[0x468] = {
#include "assets/D_80064AA0.inc.c"
};
u8 D_80064F08[0x98] = {
#include "assets/D_80064F08.inc.c"
};
u8 D_80064FA0[0x98] = {
#include "assets/D_80064FA0.inc.c"
};
u8 D_80065038[0x98] = {
#include "assets/D_80065038.inc.c"
};
u8 D_800650D0[0x98] = {
#include "assets/D_800650D0.inc.c"
};
u8 D_80065168[0x1E8] = {
#include "assets/D_80065168.inc.c"
};
u8 D_80065350[0xA8] = {
#include "assets/D_80065350.inc.c"
};
u8 D_800653F8[0x10] = {
#include "assets/D_800653F8.inc.c"
};
u8 D_80065408[0x10] = {
#include "assets/D_80065408.inc.c"
};
u8 D_80065418[0x178] = {
#include "assets/D_80065418.inc.c"
};
u8 D_80065590[0x18] = {
#include "assets/D_80065590.inc.c"
};
u8 D_800655A8[0x18] = {
#include "assets/D_800655A8.inc.c"
};
u8 D_800655C0[0x18] = {
#include "assets/D_800655C0.inc.c"
};
u8 D_800655D8[0x18] = {
#include "assets/D_800655D8.inc.c"
};
u8 D_800655F0[0x18] = {
#include "assets/D_800655F0.inc.c"
};
u8 D_80065608[0x18] = {
#include "assets/D_80065608.inc.c"
};
u8 D_80065620[0x18] = {
#include "assets/D_80065620.inc.c"
};
u8 D_80065638[0x10] = {
#include "assets/D_80065638.inc.c"
};
u8 D_80065648[0x138] = {
#include "assets/D_80065648.inc.c"
};
u8 D_80065780[0x10] = {
#include "assets/D_80065780.inc.c"
};
u8 D_80065790[0x10] = {
#include "assets/D_80065790.inc.c"
};
u8 D_800657A0[0x5D8] = {
#include "assets/D_800657A0.inc.c"
};
u8 D_80065D78[0x190] = {
#include "assets/D_80065D78.inc.c"
};
u8 D_80065F08[0x190] = {
#include "assets/D_80065F08.inc.c"
};
u8 D_80066098[0x178] = {
#include "assets/D_80066098.inc.c"
};
u8 D_80066210[0x120] = {
#include "assets/D_80066210.inc.c"
};
u8 D_80066330[0x158] = {
#include "assets/D_80066330.inc.c"
};
u8 D_80066488[0x58] = {
#include "assets/D_80066488.inc.c"
};
u8 D_800664E0[0x58] = {
#include "assets/D_800664E0.inc.c"
};
u8 D_80066538[0x58] = {
#include "assets/D_80066538.inc.c"
};
u8 D_80066590[0x58] = {
#include "assets/D_80066590.inc.c"
};
u8 D_800665E8[0x58] = {
#include "assets/D_800665E8.inc.c"
};
u8 D_80066640[0x58] = {
#include "assets/D_80066640.inc.c"
};
u8 D_80066698[0x58] = {
#include "assets/D_80066698.inc.c"
};
u8 D_800666F0[0x58] = {
#include "assets/D_800666F0.inc.c"
};
u8 D_80066748[0x58] = {
#include "assets/D_80066748.inc.c"
};
u8 D_800667A0[0x58] = {
#include "assets/D_800667A0.inc.c"
};
u8 D_800667F8[0x58] = {
#include "assets/D_800667F8.inc.c"
};
u8 D_80066850[0xC8] = {
#include "assets/D_80066850.inc.c"
};
u8 D_80066918[0xC8] = {
#include "assets/D_80066918.inc.c"
};
u8 D_800669E0[0x10] = {
#include "assets/D_800669E0.inc.c"
};
u8 D_800669F0[0xF8] = {
#include "assets/D_800669F0.inc.c"
};
u8 D_80066AE8[0x3A0] = {
#include "assets/D_80066AE8.inc.c"
};
u16 D_80066E88[0x104] = {
#include "assets/D_80066E88.inc.c"
};
u8 D_80067090[0x808] = {
#include "assets/D_80067090.inc.c"
};
u8 D_80067898[0x808] = {
#include "assets/D_80067898.inc.c"
};
u8 D_800680A0[0x808] = {
#include "assets/D_800680A0.inc.c"
};
u8 D_800688A8[0x608] = {
#include "assets/D_800688A8.inc.c"
};
u16 D_80068EB0[0x104] = {
#include "assets/D_80068EB0.inc.c"
};
u8 D_800690B8[0x4F0] = {
#include "assets/D_800690B8.inc.c"
};
u8 D_800695A8[0x4F0] = {
#include "assets/D_800695A8.inc.c"
};
u16 D_80069A98[0x104] = {
#include "assets/D_80069A98.inc.c"
};
u8 D_80069CA0[0x628] = {
#include "assets/D_80069CA0.inc.c"
};
u8 D_8006A2C8[0x628] = {
#include "assets/D_8006A2C8.inc.c"
};
u16 D_8006A8F0[0x104] = {
#include "assets/D_8006A8F0.inc.c"
};
u8 D_8006AAF8[0x4F0] = {
#include "assets/D_8006AAF8.inc.c"
};
u8 D_8006AFE8[0x4F0] = {
#include "assets/D_8006AFE8.inc.c"
};
u16 D_8006B4D8[0x104] = {
#include "assets/D_8006B4D8.inc.c"
};
u8 D_8006B6E0[0x4F0] = {
#include "assets/D_8006B6E0.inc.c"
};
u8 D_8006BBD0[0x4F0] = {
#include "assets/D_8006BBD0.inc.c"
};
u8 D_8006C0C0[0x2C] = {
#include "assets/D_8006C0C0.inc.c"
};
u8 D_8006C0EC[0x20] = {
#include "assets/D_8006C0EC.inc.c"
};
u8 D_8006C10C[0x1C] = {
#include "assets/D_8006C10C.inc.c"
};
u8 D_8006C128[0x1C] = {
#include "assets/D_8006C128.inc.c"
};
u8 D_8006C144[0x28] = {
#include "assets/D_8006C144.inc.c"
};
u8 D_8006C16C[0x8] = {
#include "assets/D_8006C16C.inc.c"
};
u8 D_8006C174[0xC] = {
#include "assets/D_8006C174.inc.c"
};
u8 D_8006C180[0x8] = {
#include "assets/D_8006C180.inc.c"
};
u8 D_8006C188[0x8] = {
#include "assets/D_8006C188.inc.c"
};
u8 D_8006C190[0x2C] = {
#include "assets/D_8006C190.inc.c"
};
u8 D_8006C1BC[0x24] = {
#include "assets/D_8006C1BC.inc.c"
};
u8 D_8006C1E0[0x78] = {
#include "assets/D_8006C1E0.inc.c"
};
u8 D_8006C258[0x28] = {
#include "assets/D_8006C258.inc.c"
};
u8 D_8006C280[0x4C] = {
#include "assets/D_8006C280.inc.c"
};
u8 D_8006C2CC[0xA4] = {
#include "assets/D_8006C2CC.inc.c"
};
u8 D_8006C370[0x20] = {
#include "assets/D_8006C370.inc.c"
};
u8 D_8006C390[0x28] = {
#include "assets/D_8006C390.inc.c"
};
u8 D_8006C3B8[0x50] = {
#include "assets/D_8006C3B8.inc.c"
};
u8 D_8006C408[0x50] = {
#include "assets/D_8006C408.inc.c"
};
u8 D_8006C458[0x6C] = {
#include "assets/D_8006C458.inc.c"
};
u8 D_8006C4C4[0x4] = {
#include "assets/D_8006C4C4.inc.c"
};
u8 D_8006C4C8[0x44] = {
#include "assets/D_8006C4C8.inc.c"
};
u8 D_8006C50C[0x54] = {
#include "assets/D_8006C50C.inc.c"
};
u8 D_8006C560[0x4] = {
#include "assets/D_8006C560.inc.c"
};
u8 D_8006C564[0x94] = {
#include "assets/D_8006C564.inc.c"
};
u8 D_8006C5F8[0x44] = {
#include "assets/D_8006C5F8.inc.c"
};
u8 D_8006C63C[0x1C] = {
#include "assets/D_8006C63C.inc.c"
};
u8 D_8006C658[0x20] = {
#include "assets/D_8006C658.inc.c"
};
u8 D_8006C678[0x54] = {
#include "assets/D_8006C678.inc.c"
};
u8 D_8006C6CC[0x18C] = {
#include "assets/D_8006C6CC.inc.c"
};
u8 D_8006C858[0x28] = {
#include "assets/D_8006C858.inc.c"
};
u8 D_8006C880[0x78] = {
#include "assets/D_8006C880.inc.c"
};
u8 *D_8006C8F8[5] = {
    D_8006C0C0, D_8006C0EC, D_8006C10C, D_8006C128, D_8006C144,
};
s16 D_8006C90C[5][4] = {
    { 44, 107, 232, 25 }, { 79, 107, 162, 25 }, { 84, 107, 152, 25 }, { 84, 107, 152, 25 }, { 54, 107, 212, 25 },
};
u8 *D_8006C934[1] = {
    D_8006C16C,
};
u8 *D_8006C938[1] = {
    D_8006C174,
};
u8 *D_8006C93C[1] = {
    D_8006C180,
};
u8 *D_8006C940[22] = {
    D_8006C188, D_8006C190, D_8006C1BC, D_8006C1E0, D_8006C858, D_8006C280,
    D_8006C2CC, D_8006C2CC, D_8006C370, D_8006C390, D_8006C3B8, D_8006C408,
    D_8006C458, D_8006C4C4, D_8006C4C8, D_8006C50C, D_8006C560, D_8006C564,
    D_8006C5F8, D_8006C63C, D_8006C658, D_8006C6CC,
};
u8 *D_8006C998[25] = {
    D_8006C16C, D_8006C174, D_8006C180, D_8006C188, D_8006C190, D_8006C1BC,
    D_8006C880, D_8006C258, D_8006C280, D_8006C2CC, D_8006C2CC, D_8006C370,
    D_8006C390, D_8006C3B8, D_8006C408, D_8006C458, D_8006C4C4, D_8006C4C8,
    D_8006C678, D_8006C560, D_8006C564, D_8006C5F8, D_8006C63C, D_8006C658,
    D_8006C6CC,
};
s16 D_8006C9FC[25][4] = {
    { 220, 160, 42, 38 }, { 220, 160, 42, 38 }, { 220, 160, 42, 38 }, { 220, 160, 42, 38 },
    { 44, 107, 232, 25 }, { 64, 107, 192, 25 }, { 54, 94, 212, 51 }, { 59, 107, 202, 25 },
    { 59, 101, 202, 38 }, { 49, 101, 222, 38 }, { 49, 101, 222, 38 }, { 79, 107, 162, 25 },
    { 54, 107, 212, 25 }, { 54, 101, 212, 38 }, { 34, 101, 252, 38 }, { 14, 101, 292, 38 },
    { 46, 89, 228, 62 }, { 64, 101, 192, 38 }, { 49, 101, 222, 38 }, { 49, 76, 228, 54 },
    { 49, 86, 222, 68 }, { 64, 101, 192, 38 }, { 84, 107, 152, 25 }, { 84, 107, 152, 25 },
    { 29, 37, 262, 166 },
};
s16 D_8006CAC4[4][2] = {
    { 258, 163 }, { 258, 176 }, { 258, 162 }, { 258, 175 },
};
u8 D_8006CAD4[0x14] = {
#include "assets/D_8006CAD4.inc.c"
};
u8 D_8006CAE8[0x10] = {
#include "assets/D_8006CAE8.inc.c"
};
u8 D_8006CAF8[0x18] = {
#include "assets/D_8006CAF8.inc.c"
};
u8 D_8006CB10[0x1C] = {
#include "assets/D_8006CB10.inc.c"
};
u8 D_8006CB2C[0x14] = {
#include "assets/D_8006CB2C.inc.c"
};
u8 D_8006CB40[0x14] = {
#include "assets/D_8006CB40.inc.c"
};
u8 D_8006CB54[0x14] = {
#include "assets/D_8006CB54.inc.c"
};
u8 D_8006CB68[0x20] = {
#include "assets/D_8006CB68.inc.c"
};
u8 D_8006CB88[0x14] = {
#include "assets/D_8006CB88.inc.c"
};
u8 D_8006CB9C[0x10] = {
#include "assets/D_8006CB9C.inc.c"
};
u8 D_8006CBAC[0x14] = {
#include "assets/D_8006CBAC.inc.c"
};
u8 D_8006CBC0[0x18] = {
#include "assets/D_8006CBC0.inc.c"
};
u8 D_8006CBD8[0x14] = {
#include "assets/D_8006CBD8.inc.c"
};
u8 D_8006CBEC[0x10] = {
#include "assets/D_8006CBEC.inc.c"
};
u8 D_8006CBFC[0xC] = {
#include "assets/D_8006CBFC.inc.c"
};
u8 D_8006CC08[0x10] = {
#include "assets/D_8006CC08.inc.c"
};
u8 D_8006CC18[0x10] = {
#include "assets/D_8006CC18.inc.c"
};
u8 *D_8006CC28[19] = {
    D_8006CAD4, D_8006CAE8, D_8006CAF8, D_8006CB10, D_8006CB2C, D_8006CB40,
    D_8006CB54, D_8006CB68, D_8006CB88, D_8006CB9C, D_8006CBAC, D_8006CBC0,
    D_8006CBD8, D_8006CBEC, D_8006CBFC, D_8006CC08, D_8006CC18, NULL,
    NULL,
};
u8 D_8006CC74 = 0;
u8 D_8006CC78 = 0;
u8 D_8006CC7C = 0;
s8 D_8006CC80[0x10] = { 0 };
Gfx D_8006CC90[14] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000004 }},
    {{ 0xBA000402, 0x00000030 }},
    {{ 0xB9000002, 0x00000000 }},
    {{ 0xB900031D, 0x00504240 }},
    {{ 0xFCFF9BFF, 0xFF34FE7F }},
    {{ 0xBB000001, 0x80008000 }},
    {{ 0xBA000C02, 0x00000000 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xBA000E02, 0x00008000 }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0x00000000, 0x00000000 }},
};
extern Unk801D8620 D_801D8620[];

void Player_Spawn(void);
void func_8000D6A0(void);
void Camera_InitForMap(void);
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
        Player_Spawn();
    } else {
        D_8004DCA0 |= 0x10000;
    }
    Camera_InitForMap();
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

void func_80036664(void) {
    Cue *cue;
    Unk80092EE8 *slot;
    s32 n;
    s32 a;
    u16 d;
    s32 xr;
    s32 t;

    n = 31;
    slot = D_80092EE8;
    if (D_80092EE0 == D_80092EE4->frame) {
        do {
            while (n != 0 && slot->unk0 != 0) {
                n--;
                slot++;
            }
            D_80092EE4->tlut[0] = 0;
            slot->unk0 = D_80092EE4->dur;
            slot->unk4 = D_80092EE4;
            D_80092EE4++;
        } while (D_80092EE0 == D_80092EE4->frame);
    }
    slot = D_80092EE8;
    gSPDisplayList(D_8007A184++, D_8006CC90);
    for (n = 32; n != 0; slot++) {
        n--;
        d = slot->unk0;
        if (slot->unk0) {
            cue = slot->unk4;
            if (d < 16) {
                a = d * 16;
            } else {
                t = cue->dur - d;
                if (t < 32) {
                    a = t * 8;
                } else {
                    a = 0xFF;
                }
            }
            gDPLoadTextureTile_4b(D_8007A184++, cue->img, G_IM_FMT_CI, (cue->w + 15) & ~15, cue->h, 0, 0, cue->w - 1, cue->h - 1, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadTLUT_pal16(D_8007A184++, 0, cue->tlut);
            gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, a);
            xr = (cue->x + cue->w) & ~1;
            gSPTextureRectangle(D_8007A184++, cue->x << 2, cue->y << 2, xr << 2, (cue->y + cue->h) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            slot->unk0--;
        }
    }
    D_80092EE0++;
}
