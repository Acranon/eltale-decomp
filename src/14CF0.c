#include "common.h"

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
} Unk8004E6A0; // size = 0x20

typedef struct {
    /* 0x00 */ Unk8004E6A0* entry;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
} Unk80085AC0; // size = 0xC

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Unk80085AB0;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} Unk80014318Arg;

extern u8 D_80085A98[];
extern u8 D_8004F770[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern Unk8004E6A0 D_8004E6A0[];
extern s32 D_80085ABC;
extern Unk80085AC0 D_80085AC0[];
extern Unk80085AB0 D_80085AB0;
extern u8 D_D37700[];
extern u8 D_8007B8E0[];
extern u8 D_8007B430[];
extern f32 D_8007AB3C;

void func_800271B4(f32, Unk80085AB0*);
f32 func_800270D0(f32, f32);
f32 sqrtf(f32);
void func_80028120(u8*, void*, s32);

void func_800140F0(u16 arg0) {
    D_80085A98[arg0 >> 3] |= D_8004F770[arg0 & 7];
}

void func_80014130(void) {
    Unk80085AC0* out = D_80085AC0;
    s32 i;

    D_80085ABC = 0;
    for (i = 0; i < 0x26; i++) {
        if (D_800842BC == D_8004E6A0[i].unk0 && D_800842C0 == D_8004E6A0[i].unk4) {
            out->entry = &D_8004E6A0[i];
            out->unk8 = 0;
            out++;
            D_80085ABC++;
        }
    }
}

Unk80085AC0* func_80014318(Unk80014318Arg* arg0) {
    s32 n = D_80085ABC;
    Unk80085AC0* out = D_80085AC0;
    f32 dx;
    f32 dz;
    f32 angle;

    while (n != 0) {
        dx = arg0->x - out->entry->x;
        dz = arg0->z - out->entry->z;
        if (sqrtf(dx * dx + dz * dz) < out->entry->unk14) {
            D_80085AB0.x = -dx;
            D_80085AB0.y = -dz;
            func_800271B4(arg0->unk10, &D_80085AB0);
            angle = func_800270D0(D_80085AB0.x, D_80085AB0.y);
            if (angle < 0.7853981633974483 && angle > -0.7853981633974483) {
                out->unk4 = arg0->unk10 - angle;
                if (out->entry->unk18 & 1) {
                    break;
                }
                D_80085AB0.x = dx;
                D_80085AB0.y = dz;
                func_800271B4(-out->entry->unk10, &D_80085AB0);
                angle = func_800270D0(D_80085AB0.x, D_80085AB0.y);
                if (angle < 0.7853981633974483 && angle > -0.7853981633974483) {
                    break;
                }
            }
        }
        n--;
        out++;
    }
    if (n == 0) {
        out = NULL;
    }
    return out;
}

void func_800144B4(Unk80085AC0* arg0) {
    func_80028120(&D_D37700[arg0->entry->unk1C], D_8007B8E0, 0x20);
    func_80028120(&D_D37700[arg0->entry->unk1E], D_8007B430, 0x200);
    if (D_8007B8E0[2] == 0xFF) {
        D_8007B8E0[0] = 0xFF;
    }
    D_8007AB3C = arg0->unk4;
}
