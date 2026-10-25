#include "common.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ char unk8[0x18 - 0x8];
} Struct_8001FD44;

typedef struct {
    /* 0x00 */ Struct_8001FD44* unk0;
    /* 0x04 */ s32 unk4;
} Struct_8007C284_30;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} Struct_8001FE08;

typedef struct {
    /* 0x00 */ char unk0[8];
    /* 0x08 */ Struct_8001FE08* unk8;
    /* 0x0C */ s32 unkC;
} Struct_8007C284_34;

typedef struct {
    char unk0[0x30];
    Struct_8007C284_30* unk30;
    Struct_8007C284_34* unk34;
} Struct_8007C284;

extern Struct_8007C284* D_8007C284;
extern s32 D_800842C0;
extern u16 D_800842E8;
extern u16 D_8008BE52;
extern Struct_8007C284_30* D_8008BF98;
extern Struct_8007C284_34* D_8008BF9C;

s32 func_80026E90(s32);
extern f32 D_8008BFAC;
extern s16 D_8008BFB0;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    /* 0x000 */ char unk0[0xA];
    /* 0x00A */ u16 unkA;
    /* 0x00C */ char unkC[0x7C - 0xC];
    /* 0x07C */ s16 unk7C;
    /* 0x07E */ char unk7E[0x130 - 0x7E];
} Struct_8007B908;

extern Struct_8007B908 D_8007B908[];
extern u16 D_8007C050[];
extern s16 D_8008BE54;
extern u16 D_8008BE58;
extern u16 D_8008BE5A;
extern u16 D_8008BF96;

void func_8001A1A4(Vec3f*);
void func_8001C298(u16, f32, f32, f32);

void func_8001EE00(void) {
    D_8008BE52 &= 0x8000;
    D_8008BFAC = 0.0f;
    D_8008BFB0 = 0;
    if (D_800842E8 & 1) {
        if (D_8007C284->unk30 != NULL) {
            D_8008BF98 = &D_8007C284->unk30[D_800842C0];
            D_8008BF9C = &D_8007C284->unk34[D_800842C0];
            return;
        }
        D_8008BF98 = NULL;
        D_8008BF9C = NULL;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001EE94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F36C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001F888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FC14.s")

Struct_8001FD44* func_8001FD44(f32 x, f32 y, Struct_8007C284_30* list) {
    Struct_8001FD44* r = NULL;
    s32 n;

    if (list != NULL) {
        n = list->unk4;
        r = list->unk0;
        while (n != 0) {
            if (r->unk0 <= x && r->unk2 <= y && x - r->unk0 <= r->unk4 && y - r->unk2 <= r->unk6) {
                break;
            }
            n--;
            r++;
        }
        if (n == 0) {
            r = NULL;
        }
    }
    return r;
}

Struct_8001FE08* func_8001FE08(f32 x, f32 y) {
    s32 n;
    Struct_8001FE08* p;
    s32 cnt;
    f32 dx;
    f32 dy;
    f32 d;
    Struct_8001FE08* cands[6];

    n = 0;

    if (D_8008BF9C != NULL) {
        cnt = D_8008BF9C->unkC;
        p = D_8008BF9C->unk8;
        while (n < 6 && cnt != 0) {
            cnt--;
            dx = p->unk0 - x;
            dy = p->unk2 - y;
            d = dx * dx + dy * dy;
            if (d >= 2500.0f && d <= 8100.0f) {
                cands[n++] = p;
            }
            p++;
        }
        if (n == 0) {
            p = NULL;
        } else {
            p = cands[func_80026E90(n)];
        }
    } else {
        p = NULL;
    }
    return p;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_8001FF10.s")

void func_800200F0(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/1FA00/func_800200F8.s")
