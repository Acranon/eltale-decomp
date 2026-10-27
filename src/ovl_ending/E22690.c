#include "common.h"

/*
 * Ending overlay: entry and per-frame update, the same scripted sprite engine as the intro,
 * and the scrolling, cross-fading backdrop.
 * Folder: src/game/ending/   (proposed for round 4)
 */

extern Gfx* D_8007A184;
extern Gfx D_8020F6C0_ovl_ending[];

s32 func_8020C254_ovl_ending(void);

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u16 unk32;
    s16 unk34;
    char unk36[2];
    s32 unk38;
    u32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u16 unk4C;
    s16 unk4E;
} UnkStruct_8022BB38;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 s;
    s32 t;
    s32 unk10;
    s32 unk14;
    s32 sw;
    s32 th;
    s32 dsdx;
    s32 dtdy;
    s32 sfrac;
    s32 tfrac;
    s32 env;
    s32 prim;
} UnkArg_8020CE70;

typedef struct {
    u32 key;
    u16 idx;
} UnkSortEntry_8020D98C;

typedef struct {
    u16 unk0;
    s16 unk2;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    u16 unk24;
    char unk26[2];
} UnkStruct_802107F0_inner;

typedef struct {
    u32 flags;
    s16 x;
    s16 y;
    s32 duration;
} UnkStep_8020F880;

typedef struct {
    UnkStep_8020F880* steps;
    u32 count;
} UnkAnim_8020F880;

typedef struct {
    UnkStruct_802107F0_inner* unk0;
    u32 unk4;
} UnkStruct_802107F0;

/* ovl_ending .bss 8022BB10..80238660: all of it is this file's (source order). */
s32 D_8022BB10_ovl_ending;
s32 D_8022BB14_ovl_ending;
s32 D_8022BB18_ovl_ending;
s32 D_8022BB1C_ovl_ending;
u32 D_8022BB20_ovl_ending;
s32 D_8022BB24_ovl_ending;
s32 D_8022BB28_ovl_ending;
u32 D_8022BB2C_ovl_ending;
u32 D_8022BB30_ovl_ending;
s32 D_8022BB34_ovl_ending;
UnkStruct_8022BB38 D_8022BB38_ovl_ending[150];
Gfx D_8022EA18_ovl_ending[2][2500];
Gfx* D_80238658_ovl_ending;
/* 8023865C..80238660: func_8020C254's static */

/* ovl_ending .data 8020F690..8020F6C0 (8020F6C0.. is E25C80.c's). */
u32 D_8020F690_ovl_ending = 0;
s32 D_8020F694_ovl_ending = 0;
s32 D_8020F698_ovl_ending = 0;

extern UnkStruct_802107F0 D_802107F0_ovl_ending[];
extern u32 D_802107F8_ovl_ending;
extern UnkAnim_8020F880 D_8020F880_ovl_ending[];
extern Gfx D_8020F718_ovl_ending[];
extern Gfx D_8020F748_ovl_ending[];

#ifdef NON_MATCHING
/* gSPTextureRectangle with the RDPHALF_2 step word built as ((dsdx & 0xFFFF) << 13) << 3
   (func_8020D98C's flipped texrects) */
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

/* func_8020E9C8's picture table (E25C80.c's D_80210800, 16-byte entries) */
typedef struct {
    void* img;
    void* tlut;
    u32 width;
    s32 unkC;
} UnkPic_80210800;

extern Gfx D_8020F730_ovl_ending[];
extern UnkPic_80210800 D_80210800_ovl_ending[];
extern f32 D_8022BAF0_ovl_ending;
extern f64 D_8022BAF8_ovl_ending;
void func_8002A338(s32);
#endif

void func_8020CA60_ovl_ending(void);

void func_8020C0D0_ovl_ending(void) {
    func_8020CA60_ovl_ending();
    D_8022BB10_ovl_ending = 0xA;
    D_8022BB14_ovl_ending = 1;
    D_8022BB18_ovl_ending = 0x12C;
    D_8022BB1C_ovl_ending = 0xDF;
    D_8022BB2C_ovl_ending = 0;
    D_8022BB30_ovl_ending = 0;
    D_8022BB20_ovl_ending = 0;
    D_8022BB24_ovl_ending = 0;
    D_8022BB34_ovl_ending = 0;
    D_8020F690_ovl_ending = 0;
    D_8020F694_ovl_ending = 0;
    D_8022BB28_ovl_ending = 0;
}

s32 func_8020C15C_ovl_ending(void) {
    s32 idx;
    s32 ret;

    idx = (D_8020F698_ovl_ending + 1) & 1;
    D_80238658_ovl_ending = D_8007A184;
    D_8007A184 = D_8022EA18_ovl_ending[idx];
    gSPDisplayList(D_8007A184++, D_8020F6C0_ovl_ending);
    // D_8020F698 is a function static in the original: IDO does not keep its address
    // in a register. Until D2 moves the data into C, write it through the neighbouring
    // symbol so this extern's address is not CSE'd either.
    (&D_8020F694_ovl_ending)[1] = idx;
    ret = func_8020C254_ovl_ending();
    idx = D_8020F698_ovl_ending;
    gSPEndDisplayList(D_8007A184++);
    D_8007A184 = D_80238658_ovl_ending;
    gSPDisplayList(D_8007A184++, D_8022EA18_ovl_ending[idx]);
    return ret;
}

s32 func_8020C8FC_ovl_ending(s32 arg0, u32* arg1);
void func_8020C978_ovl_ending(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD);
void func_8020CB84_ovl_ending(s32 arg0);
s32 func_8020CCD8_ovl_ending(void);
s16 func_8020CD88_ovl_ending(void);
void func_8020D130_ovl_ending(s32 arg0);
void func_8020D5F0_ovl_ending(s32 arg0, s32 arg1, s32 arg2);
void func_8020D970_ovl_ending(s32 arg0);
void func_8020D98C_ovl_ending(s32 arg0);
s32 func_8020E9C8_ovl_ending(s32 arg0, s32 arg1);

s32 func_8020C254_ovl_ending(void) {
    UnkStruct_802107F0_inner* entries;
    UnkStep_8020F880* steps;
    u32 listIdx;
    UnkStruct_8022BB38* obj;
    s32 slot;
    s32 dx;
    s32 dy;
    s32 i;
    u32 j;
    s32 flags;
    static s32 D_8023865C_ovl_ending;

    if (D_8022BB28_ovl_ending == 0) {
        D_8023865C_ovl_ending = 0;
        D_8022BB20_ovl_ending = 0;
        D_8022BB28_ovl_ending = 1;
    }
    D_8022BB20_ovl_ending++;
    D_8023865C_ovl_ending++;
    D_8022BB34_ovl_ending++;
    if ((D_8022BB34_ovl_ending >= D_802107F0_ovl_ending[D_8020F690_ovl_ending].unk0[D_8022BB2C_ovl_ending].unk2) &&
        (D_802107F0_ovl_ending[D_8020F690_ovl_ending].unk0[D_8022BB2C_ovl_ending].unk22 == -1) && (D_8020F694_ovl_ending == 0)) {
        do {
            slot = func_8020CD88_ovl_ending();
            if (slot == -1) {
                break;
            }
            entries = D_802107F0_ovl_ending[D_8020F690_ovl_ending].unk0;
            entries[D_8022BB2C_ovl_ending].unk20 = 0;
            entries[D_8022BB2C_ovl_ending].unk22 = slot;
            steps = D_8020F880_ovl_ending[entries[D_8022BB2C_ovl_ending].unk0].steps;
            func_8020C978_ovl_ending(slot, 0x80000000 | entries[D_8022BB2C_ovl_ending].unk4 | steps[entries[D_8022BB2C_ovl_ending].unk20].flags,
                                     entries[D_8022BB2C_ovl_ending].unk8, entries[D_8022BB2C_ovl_ending].unkA, entries[D_8022BB2C_ovl_ending].unk10,
                                     entries[D_8022BB2C_ovl_ending].unk12, entries[D_8022BB2C_ovl_ending].unkC, entries[D_8022BB2C_ovl_ending].unkE,
                                     entries[D_8022BB2C_ovl_ending].unk14, entries[D_8022BB2C_ovl_ending].unk16, entries[D_8022BB2C_ovl_ending].unk18,
                                     entries[D_8022BB2C_ovl_ending].unk1C, steps[entries[D_8022BB2C_ovl_ending].unk20].duration, D_8022BB24_ovl_ending);
            D_8022BB24_ovl_ending++;
            if (entries[D_8022BB2C_ovl_ending].unk2 == 0) {
                entries[D_8022BB2C_ovl_ending].unk24 = D_8022BB30_ovl_ending;
            } else {
                D_8022BB30_ovl_ending = D_8022BB2C_ovl_ending;
            }
            if (steps[entries[D_8022BB2C_ovl_ending].unk20].flags & 0xC800) {
                if (entries[D_8022BB2C_ovl_ending].unk2 == 0) {
                    dx = entries[D_8022BB2C_ovl_ending].unk8 - entries[D_8022BB30_ovl_ending].unk8;
                    dy = entries[D_8022BB2C_ovl_ending].unkA - entries[D_8022BB30_ovl_ending].unkA;
                } else {
                    dx = 0;
                    dy = 0;
                }
                func_8020D5F0_ovl_ending(slot, steps[entries[D_8022BB2C_ovl_ending].unk20].x + dx, steps[entries[D_8022BB2C_ovl_ending].unk20].y + dy);
            }
            if (steps[entries[D_8022BB2C_ovl_ending].unk20].flags & 0x1000) {
                func_8020D970_ovl_ending(slot);
            }
            if (steps[entries[D_8022BB2C_ovl_ending].unk20].flags & 0x60000000) {
                func_8020D130_ovl_ending(slot);
            }
            D_8022BB2C_ovl_ending++;
            if (D_8022BB2C_ovl_ending >= D_802107F0_ovl_ending[D_8020F690_ovl_ending].unk4) {
                D_8022BB2C_ovl_ending = 0;
                D_8020F694_ovl_ending = 1;
                D_8022BB34_ovl_ending = 0;
                break;
            }
            D_8022BB34_ovl_ending = 0;
        } while (entries[D_8022BB2C_ovl_ending].unk2 == 0);
    }
    func_8020D98C_ovl_ending(1);
    if (D_8022BB20_ovl_ending >= 0xF78) {
        func_8020E9C8_ovl_ending(1, 0x4C2);
    }
    func_8020D98C_ovl_ending(0);
    for (i = 0, obj = D_8022BB38_ovl_ending; i < 150; i++, obj++) {
        if (i) {
        }
        if (obj->unk0 & 0x80000000) {
            j = func_8020C8FC_ovl_ending(i, &listIdx);
            if (j != -1) {
                flags = obj->unk0;
                entries = D_802107F0_ovl_ending[listIdx].unk0;
                steps = D_8020F880_ovl_ending[entries[j].unk0].steps;
                if (flags & 0x800000) {
                    flags &= ~0x800000;
                }
                if (!(steps[entries[j].unk20].flags & flags)) {
                    // Fake: an empty use of D_8020F690 here stops IDO keeping its address in a
                    // register for the increment at the end of the function (found by the permuter).
                    if (D_8020F690_ovl_ending) {
                    }
                    entries[j].unk20++;
                    if (entries[j].unk20 >= D_8020F880_ovl_ending[entries[j].unk0].count) {
                        func_8020CB84_ovl_ending(i);
                        entries[j].unk22 = -1;
                    } else {
                        obj->unk0 &= ~0x800000;
                        obj->unk0 |= steps[entries[j].unk20].flags;
                        obj->unk38 = steps[entries[j].unk20].duration;
                        if (steps[entries[j].unk20].flags & 0xC800) {
                            if (entries[j].unk2 == 0) {
                                dx = entries[j].unk8 - entries[(s32)entries[j].unk24].unk8;
                                dy = entries[j].unkA - entries[(s32)entries[j].unk24].unkA;
                            } else {
                                dx = 0;
                                dy = 0;
                            }
                            func_8020D5F0_ovl_ending(i, steps[entries[j].unk20].x + dx, steps[entries[j].unk20].y + dy);
                        }
                        if (steps[entries[j].unk20].flags & 0x1000) {
                            func_8020D970_ovl_ending(i);
                        }
                        if (steps[entries[j].unk20].flags & 0x60000000) {
                            func_8020D130_ovl_ending(i);
                        }
                    }
                }
            }
        }
    }
    if ((func_8020CCD8_ovl_ending() == 0) && (D_8020F694_ovl_ending != 0)) {
        D_8020F694_ovl_ending = 0;
        D_8020F690_ovl_ending++;
        if (D_8020F690_ovl_ending >= D_802107F8_ovl_ending) {
            D_8020F690_ovl_ending = 0;
            return 0;
        }
    }
    return 1;
}

s32 func_8020C8FC_ovl_ending(s32 arg0, u32* arg1) {
    u32 i, j;

    for (i = 0; i < D_802107F8_ovl_ending; i++) {
        for (j = 0; j < D_802107F0_ovl_ending[i].unk4; j++) {
            if (arg0 == D_802107F0_ovl_ending[i].unk0[j].unk22) {
                *arg1 = i;
                return j;
            }
        }
    }

    return -1;
}

void func_8020C978_ovl_ending(s16 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk6 = arg3;
    temp_v0->unkC = arg4;
    temp_v0->unkE = arg5;
    temp_v0->unk8 = arg6;
    temp_v0->unkA = arg7;
    if ((arg1 & 0x04000000) == 0x04000000) {
        temp_v0->unk10 = (arg8 + 0xF) & 0xFFF0;
    } else {
        temp_v0->unk10 = arg8;
    }
    temp_v0->unk12 = arg9;
    temp_v0->unk14 = argB;
    temp_v0->unk18 = argA;
    temp_v0->unk4C = 0;
    temp_v0->unk4E = 0xFF;
    temp_v0->unk32 = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk34 = 0;
    temp_v0->unk40 = 0.0f;
    temp_v0->unk44 = 0.0f;
    temp_v0->unk48 = 0.0f;
    temp_v0->unk1C = 0.0f;
    temp_v0->unk20 = 0.0f;
    temp_v0->unk38 = argC;
    temp_v0->unk3C = argD;
    temp_v0->unk2E = temp_v0->unk30 = 0;
}

void func_8020CA60_ovl_ending(void) {
    s32 i;
    UnkStruct_8022BB38* temp_v0 = D_8022BB38_ovl_ending;

    for (i = 0; i < 150; i++, temp_v0++) {
        temp_v0->unk0 = 0;
        temp_v0->unk4 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unkC = 0;
        temp_v0->unkE = 0;
        temp_v0->unk8 = 0;
        temp_v0->unkA = 0;
        temp_v0->unk10 = 0;
        temp_v0->unk12 = 0;
        temp_v0->unk14 = 0;
        temp_v0->unk18 = 0;
        temp_v0->unk48 = 0.0f;
        temp_v0->unk4E = 0xFF;
        temp_v0->unk32 = 0;
        temp_v0->unk1C = 0.0f;
        temp_v0->unk20 = 0.0f;
        temp_v0->unk24 = 0;
        temp_v0->unk2A = 0;
        temp_v0->unk2C = 0;
        temp_v0->unk26 = 0;
        temp_v0->unk28 = 0;
        temp_v0->unk34 = 0;
        temp_v0->unk40 = 0.0f;
        temp_v0->unk44 = 1.0f;
        temp_v0->unk4C = 0;
        temp_v0->unk38 = 0;
        temp_v0->unk3C = 0;
        temp_v0->unk2E = temp_v0->unk30 = 0;
    }
}

void func_8020CB84_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    temp_v0->unk0 = 0;
    temp_v0->unk4 = 0;
    temp_v0->unk6 = 0;
    temp_v0->unkC = 0;
    temp_v0->unkE = 0;
    temp_v0->unk8 = 0;
    temp_v0->unkA = 0;
    temp_v0->unk10 = 0;
    temp_v0->unk12 = 0;
    temp_v0->unk14 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk4E = 0xFF;
    temp_v0->unk32 = 0;
    temp_v0->unk24 = 0;
    temp_v0->unk2A = 0;
    temp_v0->unk2C = 0;
    temp_v0->unk26 = 0;
    temp_v0->unk28 = 0;
    temp_v0->unk34 = 0;
    temp_v0->unk4C = 0;
    temp_v0->unk38 = 0;
    temp_v0->unk3C = 0;
    temp_v0->unk48 = 0.0f;
    temp_v0->unk1C = 0.0f;
    temp_v0->unk20 = 0.0f;
    temp_v0->unk40 = 0.0f;
    temp_v0->unk44 = 1.0f;
    temp_v0->unk2E = temp_v0->unk30 = 0;
}

s32 func_8020CC28_ovl_ending(void) {
    s32 count;
    UnkStruct_8022BB38* ptr = D_8022BB38_ovl_ending;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if ((ptr->unk0 & 0x80000000) == 0) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

s32 func_8020CCD8_ovl_ending(void) {
    s32 count;
    UnkStruct_8022BB38* ptr = D_8022BB38_ovl_ending;
    s32 i = 0;

    count = 0;
    while (i < 150) {
        if (ptr->unk0 & 0x80000000) {
            count++;
        }
        i++;
        ptr++;
    }
    return count;
}

s16 func_8020CD88_ovl_ending(void) {
    UnkStruct_8022BB38* ptr = D_8022BB38_ovl_ending;
    s32 i = 0;

    while (i < 150) {
        if ((ptr->unk0 & 0x80000000) == 0) {
            return i;
        }
        i++;
        ptr++;
    }
    return -1;
}

s32 func_8020CE70_ovl_ending(s32 arg0, s32 arg1, UnkArg_8020CE70* arg2) {
    UnkStruct_8022BB38* temp_v1;
    s32 v;
    s32 x;
    s32 y;
    s32 flag;

    temp_v1 = &D_8022BB38_ovl_ending[arg0];
    // Fake (permuter): a dead read of x here gives v the register retail uses.
    v = x;
    if (!(temp_v1->unk0 & 0x80000000)) {
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
            // Fake (permuter): a dead read of x here gives v the register retail uses.
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

s32 func_8020CFD4_ovl_ending(s32 arg0, s32 arg1, UnkArg_8020CE70* arg2) {
    UnkStruct_8022BB38* temp_v1;
    s32 v;
    s16 x;
    s16 y;
    s32 flag;

    temp_v1 = &D_8022BB38_ovl_ending[arg0];
    if (!(temp_v1->unk0 & 0x80000000)) {
        return 0xFF;
    }
    v = arg1 & 0x400;
    flag = v;
    temp_v1->unk4C++;
    if (flag) {
        x = temp_v1->unk8;
        temp_v1->unk40 += (f32) x / (f32) temp_v1->unk38;
        v = x - (s32) temp_v1->unk40;
        if ((v <= 0) || (temp_v1->unk4C >= temp_v1->unk38)) {
            v = 0;
        }
        arg2->unk0 = temp_v1->unk2E - v;
        arg2->unk10 = v;
    }
    if (!flag) {
        y = temp_v1->unkA;
        temp_v1->unk44 += (f32) y / (f32) temp_v1->unk38;
        v = y - (s32) temp_v1->unk44;
        if ((v <= 0) || (temp_v1->unk4C >= temp_v1->unk38)) {
            v = 0;
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

void func_8020D130_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    temp_v0->unk2E = temp_v0->unk4 + temp_v0->unk8;
    temp_v0->unk30 = temp_v0->unk6 + temp_v0->unkA;
}

s32 func_8020D16C_ovl_ending(s32 arg0, s32 arg1) {
    UnkStruct_8022BB38* temp_v0;
    f32 step;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    if (!(temp_v0->unk0 & 0x80000000)) {
        return 0;
    }
    temp_v0->unk32++;
    step = 255.0f / temp_v0->unk38;
    temp_v0->unk48 += step;
    if ((temp_v0->unk48 >= 255.0f) || (temp_v0->unk32 >= temp_v0->unk38)) {
        temp_v0->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        temp_v0->unk4E = temp_v0->unk48;
    } else {
        temp_v0->unk4E = 255.0f - temp_v0->unk48;
    }
    if (temp_v0->unk32 >= temp_v0->unk38) {
        temp_v0->unk32 = 0;
        temp_v0->unk48 = 0.0f;
        if (arg1 == 0) {
            temp_v0->unk4E = 0xFF;
        } else {
            temp_v0->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020D270_ovl_ending(s32 arg0, s32 arg1) {
    UnkStruct_8022BB38* temp_v0;
    f32 step;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    if (!(temp_v0->unk0 & 0x80000000)) {
        return 0;
    }
    temp_v0->unk32++;
    step = 255.0f / temp_v0->unk38;
    temp_v0->unk48 += step;
    if ((temp_v0->unk48 >= 255.0f) || (temp_v0->unk32 >= temp_v0->unk38)) {
        temp_v0->unk48 = 255.0f;
    }
    if (arg1 == 0) {
        temp_v0->unk4E = temp_v0->unk48;
    } else {
        temp_v0->unk4E = 255.0f - temp_v0->unk48;
    }
    if (temp_v0->unk32 >= temp_v0->unk38) {
        temp_v0->unk32 = 0;
        temp_v0->unk48 = 0.0f;
        if (arg1 == 0) {
            temp_v0->unk4E = 0xFF;
        } else {
            temp_v0->unk4E = 0;
        }
        return 0xFF;
    }
    return 0;
}

s32 func_8020D374_ovl_ending(s32 arg0, s32 arg1) {
    UnkStruct_8022BB38* temp_v1;
    f32 step;
    s32 dir;
    s32 dx;
    s32 dy;
    s32 deltaX;
    s32 deltaY;

    temp_v1 = &D_8022BB38_ovl_ending[arg0];
    if (!(arg1 & 0x80000000)) {
        return 0;
    }
    temp_v1->unk24++;
    step = ((f32) temp_v1->unk2A - (f32) temp_v1->unk26) / (f32) temp_v1->unk38;
    if (step < 0) {
        step = -step;
    }
    dir = 2;
    temp_v1->unk1C += step;
    dx = temp_v1->unk1C;
    step = ((f32) temp_v1->unk2C - (f32) temp_v1->unk28) / (f32) temp_v1->unk38;
    deltaX = dx;
    if (step < 0) {
        step = -step;
    }
    temp_v1->unk20 += step;
    dy = temp_v1->unk20;
    deltaY = dy;
    if (temp_v1->unk4 < temp_v1->unk2A) {
        dir = 1;
    } else {
        deltaX = -dx;
    }
    if (temp_v1->unk6 < temp_v1->unk2C) {
        dir |= 4;
    } else {
        deltaY = -dy;
        dir |= 8;
    }
    temp_v1->unk4 += deltaX;
    temp_v1->unk6 += deltaY;
    if (temp_v1->unk1C >= 1.0f) {
        temp_v1->unk1C -= dx;
    }
    if (temp_v1->unk20 >= 1.0f) {
        temp_v1->unk20 -= dy;
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk4 = temp_v1->unk2A;
        temp_v1->unk6 = temp_v1->unk2C;
    }
    if (dir & 1) {
        if (temp_v1->unk4 >= temp_v1->unk2A) {
            temp_v1->unk4 = temp_v1->unk2A;
        }
    } else if (dir & 2) {
        if (temp_v1->unk4 <= temp_v1->unk2A) {
            temp_v1->unk4 = temp_v1->unk2A;
        }
    }
    if (dir & 4) {
        if (temp_v1->unk6 >= temp_v1->unk2C) {
            temp_v1->unk6 = temp_v1->unk2C;
        }
    } else if (dir & 8) {
        if (temp_v1->unk6 <= temp_v1->unk2C) {
            temp_v1->unk6 = temp_v1->unk2C;
        }
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk24 = 0;
        temp_v1->unk1C = 0.0f;
        temp_v1->unk20 = 0.0f;
        return 0xFF;
    }
    return 0;
}

void func_8020D5F0_ovl_ending(s32 arg0, s32 arg1, s32 arg2) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    temp_v0->unk2A = (s16) arg1;
    temp_v0->unk2C = (s16) arg2;
    temp_v0->unk26 = temp_v0->unk4;
    temp_v0->unk28 = temp_v0->unk6;
}

s32 func_8020D624_ovl_ending(s32 arg0, s32 arg1) {
    UnkStruct_8022BB38* temp_v1;
    f32 step;
    s32 dir;
    s32 d;
    s32 delta;

    if (!(arg1 & 0x80000000)) {
        return 0xFF;
    }
    temp_v1 = &D_8022BB38_ovl_ending[arg0];
    temp_v1->unk24++;
    step = ((f32) temp_v1->unk2A - (f32) temp_v1->unk26) / (f32) temp_v1->unk38;
    if (step < 0) {
        step = -step;
    }
    temp_v1->unk1C += step;
    d = temp_v1->unk1C;
    delta = d;
    if (temp_v1->unk4 < temp_v1->unk2A) {
        dir = 1;
    } else {
        dir = 2;
        delta = -d;
    }
    temp_v1->unk4 += delta;
    if (temp_v1->unk1C >= 1.0f) {
        temp_v1->unk1C -= d;
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk4 = temp_v1->unk2A;
    }
    if (dir & 1) {
        if (temp_v1->unk4 >= temp_v1->unk2A) {
            temp_v1->unk4 = temp_v1->unk2A;
        }
    } else if (dir & 2) {
        if (temp_v1->unk4 <= temp_v1->unk2A) {
            temp_v1->unk4 = temp_v1->unk2A;
        }
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk24 = 0;
        temp_v1->unk1C = 0.0f;
        temp_v1->unk20 = 0.0f;
        return 0xFF;
    }
    if (!temp_v1) {
    }
    return 0;
}

s32 func_8020D7A4_ovl_ending(s32 arg0, s32 arg1) {
    UnkStruct_8022BB38* temp_v1;
    f32 step;
    s32 dir;
    s32 d;
    s32 delta;

    if (!(arg1 & 0x80000000)) {
        return 0xFF;
    }
    temp_v1 = &D_8022BB38_ovl_ending[arg0];
    temp_v1->unk24++;
    step = ((f32) temp_v1->unk2C - (f32) temp_v1->unk28) / (f32) temp_v1->unk38;
    if (step < 0) {
        step = -step;
    }
    temp_v1->unk20 += step;
    d = temp_v1->unk20;
    delta = d;
    if (temp_v1->unk6 < temp_v1->unk2C) {
        dir = 4;
    } else {
        dir = 8;
        delta = -d;
    }
    temp_v1->unk6 += delta;
    if (temp_v1->unk20 >= 1.0f) {
        temp_v1->unk20 -= d;
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk6 = temp_v1->unk2C;
    }
    if (dir & 4) {
        if (temp_v1->unk6 >= temp_v1->unk2C) {
            temp_v1->unk6 = temp_v1->unk2C;
        }
    } else if (dir & 8) {
        if (temp_v1->unk6 <= temp_v1->unk2C) {
            temp_v1->unk6 = temp_v1->unk2C;
        }
    }
    if (temp_v1->unk24 >= temp_v1->unk38) {
        temp_v1->unk24 = 0;
        temp_v1->unk1C = 0.0f;
        temp_v1->unk20 = 0.0f;
        return 0xFF;
    }
    if (!temp_v1) {
    }
    return 0;
}

s32 func_8020D924_ovl_ending(s32 arg0) {
    UnkStruct_8022BB38* temp_v0;

    temp_v0 = &D_8022BB38_ovl_ending[arg0];
    temp_v0->unk34 += 1;
    if (temp_v0->unk34 >= temp_v0->unk38) {
        return 0xFF;
    }
    return 0;
}

void func_8020D970_ovl_ending(s32 arg0) {
    D_8022BB38_ovl_ending[arg0].unk34 = 0;
}

s32 func_8020CE70_ovl_ending(s32 arg0, s32 arg1, UnkArg_8020CE70* arg2);

#ifdef NON_MATCHING
/* 25 words: t4/t9 and t3/t5 swapped in the flipped texrect block (allocation only); code is equivalent */
void func_8020D98C_ovl_ending(s32 arg0) {
    s32 i;
    UnkArg_8020CE70 rect;
    UnkSortEntry_8020D98C* entry;
    UnkStruct_8022BB38* obj;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 fadeDone;
    s32 j;
    s32 unused1;
    s32 unused2;
    UnkSortEntry_8020D98C list[150];
    UnkSortEntry_8020D98C tmp;
    s32 unused3;
    s32 unused4;

    for (i = 0; i < 150; i++) {
        list[i].idx = i;
        list[i].key = D_8022BB38_ovl_ending[i].unk3C;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (list[j + 1].key < list[j].key) {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
    gDPSetRenderMode(D_8007A184++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    for (entry = list; entry != &list[150]; entry++) {
        idx = entry->idx;
        obj = &D_8022BB38_ovl_ending[idx];
        fadeDone = 0;
        fade = 0;
        if (!(obj->unk0 & 0x80000000)) {
            continue;
        }
        if (arg0 == 1) {
            if (!(obj->unk0 & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0) {
            if (obj->unk0 & 0x800000) {
                continue;
            }
        }
        flags = obj->unk0;
        if ((flags & 0x800) && func_8020D374_ovl_ending(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && func_8020D624_ovl_ending(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && func_8020D7A4_ovl_ending(idx, flags)) {
            flags &= ~0x8000;
        }
        rect.unk0 = obj->unk4;
        rect.unk4 = obj->unk6;
        rect.s = obj->unkC;
        rect.t = obj->unkE;
        rect.unk10 = obj->unk8;
        rect.unk14 = obj->unkA;
        rect.sw = obj->unk8;
        rect.th = obj->unkA;
        rect.dsdx = 0x400;
        rect.dtdy = 0x400;
        rect.sfrac = rect.s << 5;
        rect.tfrac = rect.t << 5;
        if ((flags & 0x20000000) && func_8020CE70_ovl_ending(idx, flags, &rect)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && func_8020CFD4_ovl_ending(idx, flags, &rect)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade = 0x10;
            if (func_8020D16C_ovl_ending(idx, 0)) {
                flags &= ~0x10;
                fadeDone = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (func_8020D16C_ovl_ending(idx, 1)) {
                flags &= ~0x20;
                fadeDone = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (func_8020D270_ovl_ending(idx, 0)) {
                flags &= ~0x40;
                fadeDone = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (func_8020D270_ovl_ending(idx, 1)) {
                flags &= ~0x80;
                fadeDone = 1;
            }
        }
        if ((flags & 0x1000) && func_8020D924_ovl_ending(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (func_8020D924_ovl_ending(idx)) {
                flags &= ~0x10000000;
            }
            obj->unk0 = flags;
            continue;
        }
        if ((rect.unk0 < D_8022BB10_ovl_ending) && (rect.unk4 < D_8022BB14_ovl_ending) && (D_8022BB10_ovl_ending + D_8022BB18_ovl_ending < rect.unk0 + rect.unk10) &&
            (D_8022BB14_ovl_ending + D_8022BB1C_ovl_ending < rect.unk4 + rect.unk14)) {
            obj->unk0 = flags;
            continue;
        }
        if ((rect.unk0 + rect.unk10 < D_8022BB10_ovl_ending) || (rect.unk4 + rect.unk14 < D_8022BB14_ovl_ending)) {
            obj->unk0 = flags;
            continue;
        }
        if ((D_8022BB10_ovl_ending + D_8022BB18_ovl_ending < rect.unk0) || (D_8022BB14_ovl_ending + D_8022BB1C_ovl_ending < rect.unk4)) {
            obj->unk0 = flags;
            continue;
        }
        {
            if (D_8022BB10_ovl_ending + D_8022BB18_ovl_ending < rect.unk0 + rect.unk10) {
                rect.unk10 = D_8022BB10_ovl_ending + D_8022BB18_ovl_ending - rect.unk0;
            }
            if (D_8022BB14_ovl_ending + D_8022BB1C_ovl_ending < rect.unk4 + rect.unk14) {
                rect.unk14 = D_8022BB14_ovl_ending + D_8022BB1C_ovl_ending - rect.unk4;
            }
            if (rect.unk0 < D_8022BB10_ovl_ending) {
                rect.unk10 = rect.unk10 + rect.unk0 - D_8022BB10_ovl_ending;
                rect.s = obj->unkC;
                rect.sfrac = ((D_8022BB10_ovl_ending - rect.unk0) << 5) + rect.sfrac;
                rect.unk0 = D_8022BB10_ovl_ending;
            }
            if (obj->unk6 < D_8022BB14_ovl_ending) {
                rect.unk14 = rect.unk14 + rect.unk4 - D_8022BB14_ovl_ending;
                rect.t = obj->unkE;
                rect.tfrac = ((D_8022BB14_ovl_ending - rect.unk4) << 5) + rect.tfrac;
                rect.unk4 = D_8022BB14_ovl_ending;
            }
            if (fade == 0) {
                rect.prim = 0xFF;
                rect.env = 0xFF;
            } else if (fade & 0x30) {
                rect.prim = 0xFF;
                rect.env = obj->unk4E;
            } else if (fade & 0xC0) {
                rect.prim = obj->unk4E;
                rect.env = 0xFF;
            }
            gDPPipeSync(D_8007A184++);
            if ((flags & 0xF0) || fadeDone) {
                gSPDisplayList(D_8007A184++, D_8020F748_ovl_ending);
                gDPSetEnvColor(D_8007A184++, rect.prim, rect.prim, rect.prim, rect.env);
            } else {
                gSPDisplayList(D_8007A184++, D_8020F718_ovl_ending);
            }
            gDPPipeSync(D_8007A184++);
            if (obj->unk0 & 0x0C000000) {
                if (obj->unk0 & 0x08000000) {
                    gDPLoadTLUT_pal256(D_8007A184++, obj->unk14);
                    gDPLoadTextureTile(D_8007A184++, obj->unk18, G_IM_FMT_CI, G_IM_SIZ_8b, obj->unk10, 0, rect.s, rect.t,
                                       rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (obj->unk0 & 0x04000000) {
                    gDPLoadTLUT_pal16(D_8007A184++, 0, obj->unk14);
                    gDPLoadTextureTile_4b(D_8007A184++, obj->unk18, G_IM_FMT_CI, obj->unk10, 0, rect.s, rect.t,
                                          rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
                gDPLoadTextureTile(D_8007A184++, obj->unk18, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->unk10, 0, rect.s, rect.t,
                                   rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (obj->unk0 & 0x60000) {
                if (obj->unk0 & 0x20000) {
                    rect.dsdx = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                        (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, (rect.s + rect.sw - 1) << 5,
                                        rect.tfrac, rect.dsdx, rect.dtdy);
                } else {
                    rect.dtdy = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                        (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, rect.sfrac,
                                        (rect.t + rect.th - 1) << 5, rect.dsdx, rect.dtdy);
                }
            } else {
                gSPTextureRectangle(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                    (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, rect.sfrac, rect.tfrac, rect.dsdx,
                                    rect.dtdy);
            }
            if (fadeDone) {
                obj->unk4E = 0xFF;
            }
        }
        obj->unk0 = flags;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D98C_ovl_ending.s")
#endif

/* func_8020E9C8's function statics; globals here while it is asm. */
f32 D_8020F69C_ovl_ending = 32767.0f;
s32 D_8020F6A0_ovl_ending = 0;
f32 D_8020F6A4_ovl_ending = 0.0f;
f32 D_8020F6A8_ovl_ending = 0.0f;
u8 D_8020F6AC_ovl_ending = 1;
u8 D_8020F6B0_ovl_ending = 0;
u8 D_8020F6B4_ovl_ending = 0;

#ifdef NON_MATCHING
/* code 0xC70 vs 0xCBC, frame 0x198 vs 0x1A8: arg0/width homes, the B3/B4 hoists and allocation differ; the statics are the module's globals; code is equivalent */
s32 func_8020E9C8_ovl_ending(s32 arg0, s32 arg1) {
    u32 width;
    f32 alpha;
    f32 delta;
    s32 x;
    s32 y;
    UnkPic_80210800* pic;
    void* img;
    f32 scroll;
    s32 frame;

    if (arg0 == 0) {
        D_8020F69C_ovl_ending = D_8022BAF0_ovl_ending;
        D_8020F6B4_ovl_ending = 0;
        return 0;
    }
    if (D_8020F6B4_ovl_ending == 2) {
        return 1;
    }
    gDPPipeSync(D_8007A184++);
    gDPSetRenderMode(D_8007A184++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(D_8007A184++, D_8020F730_ovl_ending);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    if (D_8020F6A0_ovl_ending == 0x26AC) {
        D_8020F6AC_ovl_ending = 2;
        D_8020F6B0_ovl_ending = 1;
    } else if (D_8020F6A0_ovl_ending == D_8022BAF8_ovl_ending) {
        D_8020F6B0_ovl_ending = 2;
        func_8002A338(0x1E0);
    }

    switch (D_8020F6AC_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 1.0666667f;
            break;
        case 2:
            delta = -0.7111111f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = D_8020F6A4_ovl_ending + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6AC_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6AC_ovl_ending = 0;
    }
    D_8020F6A4_ovl_ending = alpha;
    if (D_8020F6A0_ovl_ending < 0x2814) {
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &D_80210800_ovl_ending[arg0];
        width = pic->width;
        img = pic->img;
        gDPLoadTLUT_pal256(D_8007A184++, pic->tlut);
        D_8020F6A4_ovl_ending = alpha;
        x = (s32) D_8020F69C_ovl_ending % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(D_8007A184++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(D_8007A184++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }

    scroll = D_8020F69C_ovl_ending;
    switch (D_8020F6B0_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 0.7111111f;
            break;
        case 2:
            delta = -0.42666668f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = D_8020F6A8_ovl_ending + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6B0_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6B0_ovl_ending = 0;
        if (D_8020F6B4_ovl_ending == 1) {
            D_8020F6B4_ovl_ending = 2;
        }
    }
    D_8020F6A8_ovl_ending = alpha;
    if (D_8020F6A0_ovl_ending >= 0x26AC) {
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &D_80210800_ovl_ending[arg0 + 1];
        width = pic->width;
        img = pic->img;
        gDPLoadTLUT_pal256(D_8007A184++, pic->tlut);
        D_8020F6A8_ovl_ending = alpha;
        x = (s32) scroll % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(D_8007A184++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(D_8007A184++, img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }
    frame = D_8020F6A0_ovl_ending + 1;
    D_8020F6A0_ovl_ending = frame;
    if ((frame >= 240.0) && (frame < 0x26E8)) {
        D_8020F69C_ovl_ending = scroll - (f32) width / (f32) arg1;
        return 0;
    }
    if (D_8020F6A0_ovl_ending == 0x26E8) {
        D_8020F6B4_ovl_ending = 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020E9C8_ovl_ending.s")
#endif
