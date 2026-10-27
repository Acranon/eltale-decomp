#include "common.h"

/*
 * Intro overlay: entry and per-frame update (boot pak check, splashes), and the
 * scripted sprite engine (150 slots with move/clip/fade/wait effects) that plays the intro.
 * Folder: src/game/intro/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ s32 active : 1;
    /* 0x00 */ u32 flags : 31;
} SpriteFlags;

typedef union {
    SpriteFlags b;
    s32 w;
} SpriteFlagsU;

typedef struct {
    /* 0x00 */ SpriteFlagsU unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C;
    /* 0x4E */ s16 unk4E;
} IntroSprite; /* size = 0x50 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 unk24;
} Unk28; /* size = 0x28 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 unk8;
} AnimFrame; /* size = 0xC */

typedef struct {
    /* 0x00 */ AnimFrame *unk0;
    /* 0x04 */ u32 unk4;
} AnimTbl;

typedef struct {
    /* 0x00 */ Unk28 *unk0;
    /* 0x04 */ u32 unk4;
} Unk802170E8;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} IntroRect; /* size = 0x38 */

typedef struct {
    /* 0x00 */ u32 key;
    /* 0x04 */ u16 idx;
} SortEnt; /* size = 0x8 */

#define GFX_WORDS(a, b)                    \
    {                                      \
        Gfx *_g = D_8007A184++;            \
        _g->words.w0 = (a);                \
        _g->words.w1 = (b);                \
    }

#ifdef NON_MATCHING
/* gSPTextureRectangle with the RDPHALF_2 step word built as ((dsdx & 0xFFFF) << 13) << 3
   (func_8020E108's flipped texrects) */
#define GFX_TEXRECT_STEPS(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                                       \
    {                                                                                                     \
        Gfx *_g = (Gfx *) (pkt);                                                                          \
                                                                                                          \
        _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(xh, 12, 12) | _SHIFTL(yh, 0, 12));            \
        _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12));                 \
        gImmp1(pkt, G_RDPHALF_1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16)));                               \
        gImmp1(pkt, G_RDPHALF_2,                                                                          \
               (((unsigned int) ((((unsigned int) (dsdx)) & ((0x01 << 16) - 1)) << 13) << 3) |             \
                _SHIFTL(dtdy, 0, 16)));                                                                   \
    }
#endif

/* ovl_intro .data 80212230..80212250 (80212250.. is DC9350.c's): 230, then
   func_8020C16C's statics 234..240. */
s32 D_80212230_ovl_intro = 0;

/* ovl_intro .bss 802684B0..80277080 (80277080.. is DC9350.c's). */
s32 D_802684B0_ovl_intro;
s32 D_802684B4_ovl_intro;
s32 D_802684B8_ovl_intro;
s32 D_802684BC_ovl_intro;
s32 D_802684C0_ovl_intro;
s32 D_802684C4_ovl_intro;
s32 D_802684C8_ovl_intro;
s32 D_802684CC_ovl_intro;
s32 D_802684D0_ovl_intro;
s32 D_802684D4_ovl_intro;
s32 D_802684D8_ovl_intro;
s32 D_802684DC_ovl_intro;
IntroSprite D_802684E0_ovl_intro[150];
Gfx D_8026B3C0_ovl_intro[2][0xBB8];
Gfx *D_80276F40_ovl_intro;
s32 D_80276F44_ovl_intro;
u8 D_80276F48_ovl_intro[0x12C]; /* not referenced */
s32 D_80277074_ovl_intro;
u8 D_80277078_ovl_intro;

extern s32 D_80212250_ovl_intro;
extern s32 D_80212254_ovl_intro;
extern Unk802170E8 D_802170E8_ovl_intro[];
extern u32 D_802170F0_ovl_intro;
extern AnimTbl D_80212810_ovl_intro[];
extern Gfx D_802122E0_ovl_intro[];
extern u16 D_80217A80_ovl_intro[];
extern u8 D_80217C80_ovl_intro[];
void func_8020E108_ovl_intro(s32);
void func_8002A338(s32);
s32 func_8020D454_ovl_intro();
s32 func_8020D078_ovl_intro(s32 id, u32 *outIdx);
void func_8020D0F4_ovl_intro(s16 idx, s32 flags, s16 x, s16 y, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8,
                             s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13);
void func_8020D300_ovl_intro(s32 idx);
s16 func_8020D504_ovl_intro(void);
void func_8020D8AC_ovl_intro(s32 idx);
void func_8020DD6C_ovl_intro(s32 idx, s32 arg1, s32 arg2);
void func_8020E0EC_ovl_intro(s32 idx);
extern Gfx D_802122C8_ovl_intro[];
s32 func_8020D5EC_ovl_intro(s32 idx, s32 flags, IntroRect *r);
s32 func_8020D750_ovl_intro(s32 idx, s32 flags, IntroRect *r);
s32 func_8020D8E8_ovl_intro(s32 idx, s32 arg1);
s32 func_8020D9EC_ovl_intro(s32 idx, s32 arg1);
s32 func_8020DAF0_ovl_intro(s32 idx, s32 flags);
s32 func_8020DDA0_ovl_intro(s32 idx, s32 flags);
s32 func_8020DF20_ovl_intro(s32 idx, s32 flags);
s32 func_8020E0A0_ovl_intro(s32 idx);

void func_8020D1DC_ovl_intro(void);

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[0x12];
} Unk80092E48; /* size = 0x14 */

extern Gfx *D_8007A184;
extern Gfx D_80212270_ovl_intro[];
extern s8 D_80092C80;
extern u16 D_80092C86;
extern OSMesgQueue D_80092C90;
extern OSPfs D_80092CA8[4];
extern Unk80092E48 D_80092E48[4];
extern u8 D_8006CC74;
extern u8 D_8006CC78;
extern u8 D_8006CC7C;

s32 func_80035A24(s32);
s32 func_8003609C(s32);
s32 func_8003D554(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D6B0(OSMesgQueue *, OSPfs *, s32);
void func_8003D8EC(char *, ...);
void func_80029A88(s32, s32, s32);
void func_8002A6B8(s32);
s32 func_8020C6A8_ovl_intro(void);
void func_8020F170_ovl_intro(void);
void func_8020F2DC_ovl_intro(void);
void func_8020F448_ovl_intro(void);
s32 func_80210140_ovl_intro(void);
void func_80210D38_ovl_intro(void);
s32 func_802111A4_ovl_intro(void);
s32 func_80211634_ovl_intro(void);

void func_8020C0D0_ovl_intro(void) {
    func_8020D1DC_ovl_intro();
    D_802684B0_ovl_intro = 10;
    D_802684B4_ovl_intro = 1;
    D_802684B8_ovl_intro = 300;
    D_802684BC_ovl_intro = 223;
    D_802684CC_ovl_intro = 0;
    D_802684D0_ovl_intro = 0;
    D_802684C0_ovl_intro = 0;
    D_802684C4_ovl_intro = 0;
    D_802684D4_ovl_intro = 0;
    D_802684D8_ovl_intro = 0;
    D_802684DC_ovl_intro = 0;
    D_80212230_ovl_intro = 0;
    D_80212250_ovl_intro = 0;
    D_802684C8_ovl_intro = 0;
}

s32 func_8020C16C_ovl_intro(void) {
    s32 ret;
    s32 err;
    static s32 D_80212234_ovl_intro = 0;
    static u8 D_80212238_ovl_intro = 0;
    static u8 D_8021223C_ovl_intro = 0;
    static s32 D_80212240_ovl_intro = 1;

    if (D_80092C80 == -1) {
        func_80210D38_ovl_intro();
        return 2;
    }
    if (D_8006CC7C == 0) {
        switch (D_80212238_ovl_intro) {
            case 0:
                err = func_8003609C(func_80035A24(D_80092C80));
                func_8003D8EC("pack_status = %d\n", err);
                if (err != -1 && err != -2 && err != -3) {
                    if (D_80092E48[D_80092C80].unk0 & 0x2000) {
                        D_80212238_ovl_intro = 1;
                        return 2;
                    }
                    D_8006CC7C = 1;
                    return 2;
                }
                if (err != -3) {
                    if (func_8003D554(&D_80092C90, &D_80092CA8[D_80092C80], D_80092C80) == 0) {
                        D_80212238_ovl_intro = 3;
                        return 2;
                    }
                    if (func_8003D6B0(&D_80092C90, &D_80092CA8[D_80092C80], D_80092C80) == 0) {
                        D_80212238_ovl_intro = 3;
                        return 2;
                    }
                    D_80212238_ovl_intro = 2;
                    return 2;
                }
                D_80212238_ovl_intro = 3;
                return 2;
            case 1:
                if (func_802111A4_ovl_intro() != 0) {
                    D_8006CC7C = 1;
                    return 2;
                }
                break;
            case 2:
                if (func_80210140_ovl_intro() != 0) {
                    D_8006CC7C = 1;
                    return 2;
                }
                break;
            case 3:
                if (func_80211634_ovl_intro() != 0) {
                    D_8006CC7C = 1;
                }
                break;
        }
        return 2;
    }
    ret = 2;
    if (D_8006CC78 == 0) {
        D_8006CC78++;
    } else {
        switch (D_80212240_ovl_intro) {
            case 0:
                func_8020F170_ovl_intro();
                if (D_80212230_ovl_intro == 0) {
                    D_80212230_ovl_intro = 150;
                    D_80212250_ovl_intro = 0;
                    D_80212254_ovl_intro = 0;
                    D_80212240_ovl_intro++;
                }
                break;
            case 1:
                func_8020F2DC_ovl_intro();
                if (D_80092C86 & 0x1000) {
                    func_80029A88(1, 0xFF, 0x40);
                    D_80212230_ovl_intro = 0;
                    D_8021223C_ovl_intro = 1;
                }
                if (D_80212230_ovl_intro == 0) {
                    D_80212250_ovl_intro = 0;
                    if (D_8021223C_ovl_intro != 0) {
                        D_80212230_ovl_intro = 10;
                        ret = 1;
                    } else {
                        D_80212230_ovl_intro = 150;
                        D_80212240_ovl_intro++;
                    }
                    D_8021223C_ovl_intro = 0;
                }
                break;
            case 2:
                func_8020F448_ovl_intro();
                if (D_80092C86 & 0x1000) {
                    func_80029A88(1, 0xFF, 0x40);
                    D_80212230_ovl_intro = 0;
                    D_8021223C_ovl_intro = 1;
                }
                if (D_80212230_ovl_intro == 0) {
                    D_80212250_ovl_intro = 0;
                    if (D_8021223C_ovl_intro != 0) {
                        D_80212230_ovl_intro = 10;
                        ret = 1;
                    } else {
                        D_80212230_ovl_intro = 45;
                        D_80212240_ovl_intro++;
                    }
                    D_8021223C_ovl_intro = 0;
                }
                break;
            case 3:
                if (--D_80212230_ovl_intro == 0) {
                    D_80212240_ovl_intro++;
                    func_8002A6B8(0x1B);
                }
                break;
            case 4:
                D_8006CC74 = 0xFF;
                D_80212234_ovl_intro = (D_80212234_ovl_intro + 1) & 1;
                D_80276F40_ovl_intro = D_8007A184;
                D_8007A184 = D_8026B3C0_ovl_intro[D_80212234_ovl_intro];
                gSPDisplayList(D_8007A184++, D_80212270_ovl_intro);
                ret = func_8020C6A8_ovl_intro();
                gSPEndDisplayList(D_8007A184);
                D_8007A184 = D_80276F40_ovl_intro;
                gSPDisplayList(D_8007A184++, D_8026B3C0_ovl_intro[D_80212234_ovl_intro]);
                break;
        }
    }
    return ret;
}

#ifdef NON_MATCHING
/* D_80276F44 is the module's global (the original's function static), so its address is kept in a register; v1 spill at sp+0x74 vs 0x70; code is equivalent */
s32 func_8020C6A8_ovl_intro(void) {
    Unk28* entries;
    AnimFrame* steps;
    u32 listIdx;
    IntroSprite* obj;
    s32 slot;
    s32 dx;
    s32 dy;
    Unk28 *new_var;
    s32 i;
    s32 j;
    s32 flags;
    Gfx *g;
    if (D_80277074_ovl_intro) {}

    if (D_802684C8_ovl_intro == 0) {
        D_80276F44_ovl_intro = 0;
        D_802684C0_ovl_intro = 0;
        D_80277078_ovl_intro = 0;
        D_80277074_ovl_intro = 0;
        D_802684C8_ovl_intro = 1;
    }
    D_802684C0_ovl_intro++;
    D_80276F44_ovl_intro++;
    D_802684D4_ovl_intro++;
    if ((D_802684D4_ovl_intro >= D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0[D_802684CC_ovl_intro].unk2) &&
        (D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0[D_802684CC_ovl_intro].unk22 == -1) && (D_802684DC_ovl_intro == 0)) {
        do {
            slot = func_8020D504_ovl_intro();
            if (slot != -1) {
            entries = D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0;
            entries[D_802684CC_ovl_intro].unk20 = 0;
            entries[D_802684CC_ovl_intro].unk22 = slot;
            steps = D_80212810_ovl_intro[entries[D_802684CC_ovl_intro].unk0].unk0;
            func_8020D0F4_ovl_intro(slot, 0x80000000 | entries[D_802684CC_ovl_intro].unk4 | steps[entries[D_802684CC_ovl_intro].unk20].unk0,
                                     entries[D_802684CC_ovl_intro].unk8, entries[D_802684CC_ovl_intro].unkA, entries[D_802684CC_ovl_intro].unk10,
                                     entries[D_802684CC_ovl_intro].unk12, entries[D_802684CC_ovl_intro].unkC, entries[D_802684CC_ovl_intro].unkE,
                                     entries[D_802684CC_ovl_intro].unk14, entries[D_802684CC_ovl_intro].unk16, entries[D_802684CC_ovl_intro].unk18,
                                     entries[D_802684CC_ovl_intro].unk1C, steps[entries[D_802684CC_ovl_intro].unk20].unk8, D_802684C4_ovl_intro);
            D_802684C4_ovl_intro++;
            if (entries[D_802684CC_ovl_intro].unk2 == 0) {
                entries[D_802684CC_ovl_intro].unk24 = D_802684D0_ovl_intro;
            } else {
                D_802684D0_ovl_intro = D_802684CC_ovl_intro;
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0xC800) {
                if (entries[D_802684CC_ovl_intro].unk2 == 0) {
                    dx = entries[D_802684CC_ovl_intro].unk8 - entries[D_802684D0_ovl_intro].unk8;
                    dy = entries[D_802684CC_ovl_intro].unkA - entries[D_802684D0_ovl_intro].unkA;
                } else {
                    dx = 0;
                    dy = 0;
                }
                func_8020DD6C_ovl_intro(slot, steps[entries[D_802684CC_ovl_intro].unk20].unk4 + dx, steps[entries[D_802684CC_ovl_intro].unk20].unk6 + dy);
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0x1000) {
                func_8020E0EC_ovl_intro(slot);
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0x60000000) {
                func_8020D8AC_ovl_intro(slot);
            }
            D_802684CC_ovl_intro++;
            if (D_802684CC_ovl_intro >= D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk4) {
                D_802684CC_ovl_intro = 0;
                D_802684DC_ovl_intro = 1;
                D_802684D4_ovl_intro = 0;
                break;
            }
            D_802684D4_ovl_intro = 0;
            } else {
                break;
            }
        } while (entries[D_802684CC_ovl_intro].unk2 == 0);
    }
    if (D_802684C0_ovl_intro == 0x1E00) {
        func_8002A338(0x5A);
    }
    func_8020E108_ovl_intro(1);
    func_8020E108_ovl_intro(0);
    for (i = 0, obj = D_802684E0_ovl_intro; i < 150; i++, obj++) {
        if (i) {
        }
        if (obj->unk0.w & 0x80000000) {
            j = func_8020D078_ovl_intro(i, &listIdx);
            if (j != -1) {
                flags = obj->unk0.w;
                entries = D_802170E8_ovl_intro[listIdx].unk0;
                steps = D_80212810_ovl_intro[entries[j].unk0].unk0;
                if (flags & 0x800000) {
                    flags &= ~0x800000;
                }
                if (!(steps[entries[j].unk20].unk0 & flags)) {
                    if (D_802684D8_ovl_intro) {
                    }
                    new_var = entries;
                    entries[j].unk20++;
                    if (new_var[j].unk20 >= D_80212810_ovl_intro[new_var[j].unk0].unk4) {
                        func_8020D300_ovl_intro(i);
                        entries[j].unk22 = -1;
                    } else {
                        obj->unk0.w &= ~0x800000;
                        obj->unk0.w |= steps[new_var[j].unk20].unk0;
                        obj->unk38 = steps[new_var[j].unk20].unk8;
                        if (steps[new_var[j].unk20].unk0 & 0xC800) {
                            if (new_var[j].unk2 == 0) {
                                dx = new_var[j].unk8 - new_var[new_var[j].unk24].unk8;
                                dy = new_var[j].unkA - new_var[new_var[j].unk24].unkA;
                            } else {
                                dx = 0;
                                dy = 0;
                            }
                            func_8020DD6C_ovl_intro(i, steps[new_var[j].unk20].unk4 + dx, steps[new_var[j].unk20].unk6 + dy);
                        }
                        if (steps[new_var[j].unk20].unk0 & 0x1000) {
                            func_8020E0EC_ovl_intro(i);
                        }
                        if (steps[new_var[j].unk20].unk0 & 0x60000000) {
                            func_8020D8AC_ovl_intro(i);
                        }
                    }
                }
            }
        }
    }
    if (D_80092C86 & 0x1000) {
        D_80277078_ovl_intro = 1;
    }
    if (D_80277078_ovl_intro != 0) {
        D_80277074_ovl_intro += 10;
        if (D_80277074_ovl_intro >= 0x100) {
            D_80277074_ovl_intro = 0xFF;
        }
        g = D_8007A184++; g->words.w0 = _SHIFTL(G_RDPPIPESYNC, 24, 8); g->words.w1 = 0;
        g = D_8007A184++; g->words.w0 = (_SHIFTL(G_DL, 24, 8) | _SHIFTL(G_DL_PUSH, 16, 8)); g->words.w1 = (u32)D_802122E0_ovl_intro;
        g = D_8007A184++; g->words.w0 = (_SHIFTL(G_SETOTHERMODE_H,24,8) | _SHIFTL(G_MDSFT_TEXTLUT,8,8) | _SHIFTL(2,0,8)); g->words.w1 = G_TT_RGBA16;
        gDPSetRenderMode(D_8007A184++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetEnvColor(D_8007A184++, 255, 255, 255, D_80277074_ovl_intro);
        gDPLoadTLUT_pal256(D_8007A184++, D_80217A80_ovl_intro);
        for (i = 0; i < 40; i++) {
            gDPLoadTextureTile(D_8007A184++, D_80217C80_ovl_intro, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 6, 0, 0, 319, 5, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(D_8007A184++, 0, (i * 6) << 2, 320 << 2, (i * 6 + 6) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        if (D_80277074_ovl_intro >= 0xFF) {
            return 1;
        }
    }
    if ((func_8020D454_ovl_intro() == 0) && (D_802684DC_ovl_intro != 0)) {
        D_802684DC_ovl_intro = 0;
        D_802684D8_ovl_intro++;
        if (D_802684D8_ovl_intro >= D_802170F0_ovl_intro) {
            D_802684D8_ovl_intro = 0;
            return 0;
        }
    }
    return 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020C6A8_ovl_intro.s")
#endif

s32 func_8020D078_ovl_intro(s32 id, u32 *outIdx) {
    u32 i;
    u32 j;

    for (i = 0; i < D_802170F0_ovl_intro; i++) {
        for (j = 0; j < D_802170E8_ovl_intro[i].unk4; j++) {
            if (id == D_802170E8_ovl_intro[i].unk0[j].unk22) {
                *outIdx = i;
                return j;
            }
        }
    }
    return -1;
}

void func_8020D0F4_ovl_intro(s16 idx, s32 flags, s16 x, s16 y, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8,
                             s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];

    p->unk0.w = flags;
    p->unk4 = x;
    p->unk6 = y;
    p->unkC = arg4;
    p->unkE = arg5;
    p->unk8 = arg6;
    p->unkA = arg7;
    if ((flags & 0x4000000) == 0x4000000) {
        p->unk10 = (arg8 + 15) & 0xFFF0;
    } else {
        p->unk10 = arg8;
    }
    p->unk12 = arg9;
    p->unk14 = arg11;
    p->unk18 = arg10;
    p->unk4C = 0;
    p->unk4E = 0xFF;
    p->unk32 = 0;
    p->unk24 = 0;
    p->unk34 = 0;
    p->unk40 = 0.0f;
    p->unk44 = 0.0f;
    p->unk48 = 0.0f;
    p->unk1C = 0.0f;
    p->unk20 = 0.0f;
    p->unk38 = arg12;
    p->unk3C = arg13;
    p->unk2E = p->unk30 = 0;
}

void func_8020D1DC_ovl_intro(void) {
    s32 i;
    IntroSprite *p = D_802684E0_ovl_intro;

    for (i = 0; i < 150; i++, p++) {
        p->unk0.w = 0;
        p->unk4 = 0;
        p->unk6 = 0;
        p->unkC = 0;
        p->unkE = 0;
        p->unk8 = 0;
        p->unkA = 0;
        p->unk10 = 0;
        p->unk12 = 0;
        p->unk14 = 0;
        p->unk18 = 0;
        p->unk48 = 0.0f;
        p->unk4E = 0xFF;
        p->unk32 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        p->unk24 = 0;
        p->unk2A = 0;
        p->unk2C = 0;
        p->unk26 = 0;
        p->unk28 = 0;
        p->unk2E = p->unk30 = 0;
        p->unk34 = 0;
        p->unk40 = 0.0f;
        p->unk44 = 1.0f;
        p->unk4C = 0;
        p->unk38 = 0;
        p->unk3C = 0;
    }
}

void func_8020D300_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];

    p->unk0.w = 0;
    p->unk4 = 0;
    p->unk6 = 0;
    p->unkC = 0;
    p->unkE = 0;
    p->unk8 = 0;
    p->unkA = 0;
    p->unk10 = 0;
    p->unk12 = 0;
    p->unk14 = 0;
    p->unk18 = 0;
    p->unk48 = 0.0f;
    p->unk4E = 0xFF;
    p->unk32 = 0;
    p->unk1C = 0.0f;
    p->unk20 = 0.0f;
    p->unk24 = 0;
    p->unk2A = 0;
    p->unk2C = 0;
    p->unk26 = 0;
    p->unk28 = 0;
    p->unk34 = 0;
    p->unk40 = 0.0f;
    p->unk44 = 1.0f;
    p->unk4C = 0;
    p->unk38 = 0;
    p->unk3C = 0;
    p->unk2E = p->unk30 = 0;
}

s32 func_8020D3A4_ovl_intro(s32 n) {
    s32 i;
    IntroSprite *p = D_802684E0_ovl_intro;

    n = 0;
    for (i = 0; i < 150; i++, p++) {
        if (!(p->unk0.w & 0x80000000)) {
            n++;
        }
    }
    return n;
}

s32 func_8020D454_ovl_intro(s32 n) {
    s32 i;
    IntroSprite *p = D_802684E0_ovl_intro;

    n = 0;
    for (i = 0; i < 150; i++, p++) {
        if (p->unk0.w & 0x80000000) {
            n++;
        }
    }
    return n;
}

s16 func_8020D504_ovl_intro(void) {
    s32 i;
    IntroSprite *p = D_802684E0_ovl_intro;

    for (i = 0; i < 150; i++, p++) {
        if (!(p->unk0.w & 0x80000000)) {
            return i;
        }
    }
    return -1;
}

s32 func_8020D5EC_ovl_intro(s32 arg0, s32 arg1, IntroRect* arg2) {
    IntroSprite* temp_v1;
    s32 v = 0;
    s32 x;
    s32 y;
    s32 flag;

    temp_v1 = &D_802684E0_ovl_intro[arg0];
    if (!(temp_v1->unk0.w & 0x80000000)) {
        return 0xFF;
    }
    x = temp_v1->unk8;
    y = temp_v1->unkA;
    flag = arg1 & 0x100;
    temp_v1->unk4C++;
    if (flag) {
        arg1 = temp_v1->unk38;
        temp_v1->unk40 += (f32) x / (f32) arg1;
        v = temp_v1->unk40;
        if ((v >= x) || (temp_v1->unk4C >= arg1)) {
            v = x;
        }
        arg2->unk0 = temp_v1->unk2E - v;
        arg2->unk10 = v;
    }
    if (!flag) {
        arg1 = temp_v1->unk38;
        temp_v1->unk44 += (f32) y / (f32) arg1;
        v = temp_v1->unk44;
        if ((v >= y) || (temp_v1->unk4C >= arg1)) {
            v = y;
        }
        arg2->unk4 = temp_v1->unk30 - v;
        arg2->unk14 = v;
    }
    if (temp_v1->unk4C >= temp_v1->unk38) {
        temp_v1->unk4C = 0;
        temp_v1->unk2E = 0;
        temp_v1->unk30 = 0;
        temp_v1->unk40 = 0.0f;
        temp_v1->unk44 = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 func_8020D750_ovl_intro(s32 idx, s32 flags, IntroRect *r) {
    IntroSprite *s = &D_802684E0_ovl_intro[idx];
    IntroSprite *p;
    s32 v;

    if (!(s->unk0.w & 0x80000000)) {
        return 0xFF;
    }
    p = s;
    idx = flags & 0x400;
    p->unk4C++;
    if (idx) {
        flags = p->unk8;
        p->unk40 += (f32) flags / p->unk38;
        v = flags - (s32) p->unk40;
        if (v <= 0 || p->unk4C >= p->unk38) {
            v = 0;
        }
        r->unk0 = p->unk2E - v;
        r->unk10 = v;
    }
    if (!idx) {
        idx = p->unkA;
        p->unk44 += (f32) idx / p->unk38;
        v = idx - (s32) p->unk44;
        if (v <= 0 || p->unk4C >= p->unk38) {
            v = 0;
        }
        r->unk4 = p->unk30 - v;
        r->unk14 = v;
    }
    if (p->unk4C >= p->unk38) {
        p->unk4C = 0;
        p->unk2E = 0;
        p->unk30 = 0;
        p->unk40 = 0.0f;
        p->unk44 = 0.0f;
        return 0xFF;
    }
    return 0;
}

void func_8020D8AC_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];

    p->unk2E = p->unk4 + p->unk8;
    p->unk30 = p->unk6 + p->unkA;
}

s32 func_8020D8E8_ovl_intro(s32 idx, s32 arg1) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];
    f32 step;

    if (!(p->unk0.w & 0x80000000)) {
        return 0;
    }
    p->unk32++;
    step = 255.0f / p->unk38;
    p->unk48 += step;
    if (p->unk48 >= 255.0f || p->unk32 >= p->unk38) {
        p->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        p->unk4E = p->unk48;
    } else {
        p->unk4E = 255.0f - p->unk48;
    }
    if (p->unk32 >= p->unk38) {
        p->unk32 = 0;
        p->unk48 = 0.0f;
        if (arg1 == 0) {
            p->unk4E = 0xFF;
        } else {
            p->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020D9EC_ovl_intro(s32 idx, s32 arg1) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];
    f32 step;

    if (!(p->unk0.w & 0x80000000)) {
        return 0;
    }
    p->unk32++;
    step = 255.0f / p->unk38;
    p->unk48 += step;
    if (p->unk48 >= 255.0f || p->unk32 >= p->unk38) {
        p->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        p->unk4E = p->unk48;
    } else {
        p->unk4E = 255.0f - p->unk48;
    }
    if (p->unk32 >= p->unk38) {
        p->unk32 = 0;
        p->unk48 = 0.0f;
        if (arg1 == 0) {
            p->unk4E = 0xFF;
        } else {
            p->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020DAF0_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];
    f32 step;
    s32 tx;
    s32 ty;
    s32 dx;
    s32 dy;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0;
    }
    p->unk24++;
    step = ((f32) p->unk2A - (f32) p->unk26) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk1C += step;
    dir = 2;
    tx = p->unk1C;
    step = ((f32) p->unk2C - (f32) p->unk28) / p->unk38;
    dx = tx;
    if (step < 0) {
        step = -step;
    }
    p->unk20 += step;
    ty = p->unk20;
    dy = ty;
    if (p->unk4 < p->unk2A) {
        dir = 1;
    } else {
        dx = -tx;
    }
    if (p->unk6 < p->unk2C) {
        dir |= 4;
    } else {
        dy = -ty;
        dir |= 8;
    }
    p->unk4 += dx;
    p->unk6 += dy;
    if (p->unk1C >= 1.0f) {
        p->unk1C -= tx;
    }
    if (p->unk20 >= 1.0f) {
        p->unk20 -= ty;
    }
    if (p->unk24 >= p->unk38) {
        p->unk4 = p->unk2A;
        p->unk6 = p->unk2C;
    }
    if (dir & 1) {
        if (p->unk4 >= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    } else if (dir & 2) {
        if (p->unk4 <= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    }
    if (dir & 4) {
        if (p->unk6 >= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    } else if (dir & 8) {
        if (p->unk6 <= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

void func_8020DD6C_ovl_intro(s32 idx, s32 arg1, s32 arg2) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];

    p->unk2A = arg1;
    p->unk2C = arg2;
    p->unk26 = p->unk4;
    p->unk28 = p->unk6;
}

s32 func_8020DDA0_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->unk24++;
    step = ((f32) p->unk2A - (f32) p->unk26) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk1C += step;
    dir = 2;
    t = p->unk1C;
    d = t;
    if (p->unk4 < p->unk2A) {
        dir = 1;
    } else {
        dir = 2;
        d = -t;
    }
    p->unk4 += d;
    if (p->unk1C >= 1.0f) {
        p->unk1C -= t;
    }
    if (p->unk24 >= p->unk38) {
        p->unk4 = p->unk2A;
    }
    if (dir & 1) {
        if (p->unk4 >= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    } else if (dir & 2) {
        if (p->unk4 <= p->unk2A) {
            p->unk4 = p->unk2A;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 func_8020DF20_ovl_intro(s32 idx, s32 flags) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];
    f32 step;
    s32 t;
    s32 d;
    s32 dir;

    if (!(flags & 0x80000000)) {
        return 0xFF;
    }
    p->unk24++;
    step = ((f32) p->unk2C - (f32) p->unk28) / p->unk38;
    if (step < 0) {
        step = -step;
    }
    p->unk20 += step;
    dir = 8;
    t = p->unk20;
    d = t;
    if (p->unk6 < p->unk2C) {
        dir = 4;
    } else {
        dir = 8;
        d = -t;
    }
    p->unk6 += d;
    if (p->unk20 >= 1.0f) {
        p->unk20 -= t;
    }
    if (p->unk24 >= p->unk38) {
        p->unk6 = p->unk2C;
    }
    if (dir & 4) {
        if (p->unk6 >= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    } else if (dir & 8) {
        if (p->unk6 <= p->unk2C) {
            p->unk6 = p->unk2C;
        }
    }
    if (p->unk24 >= p->unk38) {
        p->unk24 = 0;
        p->unk1C = 0.0f;
        p->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

s32 func_8020E0A0_ovl_intro(s32 idx) {
    IntroSprite *p = &D_802684E0_ovl_intro[idx];

    p->unk34++;
    if (p->unk34 >= p->unk38) {
        return 0xFF;
    }
    return 0;
}

void func_8020E0EC_ovl_intro(s32 idx) {
    D_802684E0_ovl_intro[idx].unk34 = 0;
}

#ifdef NON_MATCHING
/* 23 words: t3/t4 swapped in the flipped texrect block (allocation only); code is equivalent */
void func_8020E108_ovl_intro(s32 arg0) {
    s32 i;
    IntroRect r;
    s32 k;
    IntroSprite *p;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 changed;
    s32 j;
    s32 unused1;
    s32 unused2;
    SortEnt ents[150];
    SortEnt tmp;

    for (i = 0, p = D_802684E0_ovl_intro; i < 150; i++, p++) {
        ents[i].idx = i;
        ents[i].key = p->unk3C;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (ents[j + 1].key < ents[j].key) {
                tmp = ents[j];
                ents[j] = ents[j + 1];
                ents[j + 1] = tmp;
            }
        }
    }
    gDPPipeSync(D_8007A184++);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    for (k = 0; k < 150; k++) {
        idx = ents[k].idx;
        p = &D_802684E0_ovl_intro[idx];
        changed = 0;
        fade = 0;
        if (p->unk0.w & 0x80000000) {
        if (arg0 == 1) {
            if (!(p->unk0.w & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0 && (p->unk0.w & 0x800000)) {
            continue;
        }
        flags = p->unk0.w;
        if ((flags & 0x800) && func_8020DAF0_ovl_intro(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && func_8020DDA0_ovl_intro(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && func_8020DF20_ovl_intro(idx, flags)) {
            flags &= ~0x8000;
        }
        r.unk0 = p->unk4;
        r.unk4 = p->unk6;
        r.unk8 = p->unkC;
        r.unkC = p->unkE;
        r.unk10 = p->unk8;
        r.unk14 = p->unkA;
        r.unk18 = p->unk8;
        r.unk1C = p->unkA;
        r.unk20 = 0x400;
        r.unk24 = 0x400;
        r.unk28 = r.unk8 << 5;
        r.unk2C = r.unkC << 5;
        if ((flags & 0x20000000) && func_8020D5EC_ovl_intro(idx, flags, &r)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && func_8020D750_ovl_intro(idx, flags, &r)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade |= 0x10;
            if (func_8020D8E8_ovl_intro(idx, 0)) {
                flags &= ~0x10;
                changed = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (func_8020D8E8_ovl_intro(idx, 1)) {
                flags &= ~0x20;
                changed = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (func_8020D9EC_ovl_intro(idx, 0)) {
                flags &= ~0x40;
                changed = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (func_8020D9EC_ovl_intro(idx, 1)) {
                flags &= ~0x80;
                changed = 1;
            }
        }
        if ((flags & 0x1000) && func_8020E0A0_ovl_intro(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (func_8020E0A0_ovl_intro(idx)) {
                flags &= ~0x10000000;
            }
            p->unk0.w = flags;
            continue;
        }
        if (r.unk0 < D_802684B0_ovl_intro && r.unk4 < D_802684B4_ovl_intro && D_802684B0_ovl_intro + D_802684B8_ovl_intro < r.unk0 + r.unk10 &&
            D_802684B4_ovl_intro + D_802684BC_ovl_intro < r.unk4 + r.unk14) {
            p->unk0.w = flags;
            continue;
        }
        if (r.unk0 + r.unk10 < D_802684B0_ovl_intro || r.unk4 + r.unk14 < D_802684B4_ovl_intro) {
            p->unk0.w = flags;
            continue;
        }
        if (D_802684B0_ovl_intro + D_802684B8_ovl_intro < r.unk0 || D_802684B4_ovl_intro + D_802684BC_ovl_intro < r.unk4) {
            p->unk0.w = flags;
            continue;
        }
        {
            if (D_802684B0_ovl_intro + D_802684B8_ovl_intro < r.unk0 + r.unk10) {
                r.unk10 = D_802684B0_ovl_intro + D_802684B8_ovl_intro - r.unk0;
            }
            if (D_802684B4_ovl_intro + D_802684BC_ovl_intro < r.unk4 + r.unk14) {
                r.unk14 = D_802684B4_ovl_intro + D_802684BC_ovl_intro - r.unk4;
            }
            if (r.unk0 < D_802684B0_ovl_intro) {
                r.unk10 = r.unk10 + r.unk0 - D_802684B0_ovl_intro;
                r.unk8 = p->unkC;
                r.unk28 = ((D_802684B0_ovl_intro - r.unk0) << 5) + r.unk28;
                r.unk0 = D_802684B0_ovl_intro;
            }
            if (p->unk6 < D_802684B4_ovl_intro) {
                r.unk14 = r.unk14 + r.unk4 - D_802684B4_ovl_intro;
                r.unkC = p->unkE;
                r.unk2C = ((D_802684B4_ovl_intro - r.unk4) << 5) + r.unk2C;
                r.unk4 = D_802684B4_ovl_intro;
            }
            if (fade == 0) {
                r.unk34 = 0xFF;
                r.unk30 = 0xFF;
            } else if (fade & 0x30) {
                r.unk34 = 0xFF;
                r.unk30 = p->unk4E;
            } else if (fade & 0xC0) {
                r.unk34 = p->unk4E;
                r.unk30 = 0xFF;
            }
            gDPPipeSync(D_8007A184++);
            if ((flags & 0xF0) || changed) {
                gSPDisplayList(D_8007A184++, D_802122E0_ovl_intro);
                gDPSetEnvColor(D_8007A184++, r.unk34, r.unk34, r.unk34, r.unk30);
            } else {
                gSPDisplayList(D_8007A184++, D_802122C8_ovl_intro);
            }
            gDPPipeSync(D_8007A184++);
            if (p->unk0.w & 0x0C000000) {
                gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
                if (p->unk0.w & 0x08000000) {
                    gDPLoadTLUT_pal256(D_8007A184++, p->unk14);
                    gDPLoadTextureTile(D_8007A184++, p->unk18, G_IM_FMT_CI, G_IM_SIZ_8b, p->unk10, 0, r.unk8, r.unkC,
                                       r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (p->unk0.w & 0x04000000) {
                    gDPLoadTLUT_pal16(D_8007A184++, 0, p->unk14);
                    gDPLoadTextureTile_4b(D_8007A184++, p->unk18, G_IM_FMT_CI, p->unk10, 0, r.unk8, r.unkC,
                                          r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
                gDPLoadTextureTile(D_8007A184++, p->unk18, G_IM_FMT_RGBA, G_IM_SIZ_16b, p->unk10, 0, r.unk8, r.unkC,
                                   r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (p->unk0.w & 0x60000) {
                if (p->unk0.w & 0x20000) {
                    r.unk20 = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                        (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, (r.unk8 + r.unk18 - 1) << 5, r.unk2C,
                                        r.unk20, r.unk24);
                }
                if (p->unk0.w & 0x40000) {
                    r.unk24 = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                        (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, r.unk28, (r.unkC + r.unk1C - 1) << 5,
                                        r.unk20, r.unk24);
                }
            } else {
                gSPTextureRectangle(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                    (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, r.unk28, r.unk2C, r.unk20, r.unk24);
            }
            if (changed) {
                p->unk4E = 0xFF;
            }
        }
        p->unk0.w = flags;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl_intro/DC62B0/func_8020E108_ovl_intro.s")
#endif

