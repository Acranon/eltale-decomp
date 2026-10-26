#include "common.h"

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

/* ovl_ending .data 8020F690..8020F6C0 (the rest of the slab is still asm). */
u32 D_8020F690_ovl_ending = 0;
s32 D_8020F694_ovl_ending = 0;
s32 D_8020F698_ovl_ending = 0;

extern UnkStruct_802107F0 D_802107F0_ovl_ending[];
extern u32 D_802107F8_ovl_ending;
extern UnkAnim_8020F880 D_8020F880_ovl_ending[];
extern Gfx D_8020F718_ovl_ending[];
extern Gfx D_8020F748_ovl_ending[];

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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020D98C_ovl_ending.s")

/* func_8020E9C8's function statics; globals here while it is asm. */
f32 D_8020F69C_ovl_ending = 32767.0f;
s32 D_8020F6A0_ovl_ending = 0;
f32 D_8020F6A4_ovl_ending = 0.0f;
f32 D_8020F6A8_ovl_ending = 0.0f;
u8 D_8020F6AC_ovl_ending = 1;
u8 D_8020F6B0_ovl_ending = 0;
u8 D_8020F6B4_ovl_ending = 0;

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_ending/E22690/func_8020E9C8_ovl_ending.s")
