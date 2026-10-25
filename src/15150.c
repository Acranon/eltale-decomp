#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f_15150;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f_15150;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} Unk15150Model;

typedef struct {
    /* 0x00 */ u8 pad0[0x94];
    /* 0x94 */ f32 unk94;
} Unk15150Model2;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ f32 scale;
    /* 0x28 */ u8 pad28[0x36];
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u8 pad60[4];
    /* 0x64 */ Unk15150Model* unk64;
    /* 0x68 */ Unk15150Model2* unk68;
} Unk15150Target;

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u16 flags;
    /* 0x0C */ f32 eyeX;
    /* 0x10 */ f32 eyeY;
    /* 0x14 */ f32 eyeZ;
    /* 0x18 */ f32 atX;
    /* 0x1C */ f32 atY;
    /* 0x20 */ f32 atZ;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ Unk15150Target* target;
    /* 0x84 */ f32 unk84;
} Camera15150; // size = 0x88

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 mode;
    /* 0x0C */ u16 flags;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} Unk80085F68;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Unk8007ABB0;

extern Camera15150 D_80085E48;
extern Unk80085F68 D_80085F68;
extern s32 D_80085CAC;
extern f32 D_80085CB0;
extern f32 D_80085CB4;
extern f32 D_8004EC68[];
extern f32 D_8004EC88;
extern f32 D_8004EC8C;
extern Vec2f_15150 D_80085C10;
extern s32 D_8007ABA8;
extern Unk8007ABB0* D_8007ABB0[];

f32 func_800270D0(f32, f32);
void func_800271B4(f32, Vec2f_15150*);
f32 sinf(f32);
f32 cosf(f32);
f32 sqrtf(f32);
void func_80014E04(Camera15150*);
void func_80015DB4(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_80014550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_80014994.s")

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_80014E04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_80015494.s")

void func_80015810(Camera15150* arg0) {
    f32 dx = arg0->eyeX - arg0->atX;
    f32 dz = arg0->eyeZ - arg0->atZ;

    if (dx != 0.0f || dz != 0.0f) {
        arg0->unk28 = arg0->unk2C = func_800270D0(dx, dz);
    }
}

extern Camera15150 D_80085B80;
extern f32 D_80085F84;
extern f32 D_8008BE5C;
extern f32 D_8008BE60;
extern u16 D_80092C86;
void func_80015878(Camera15150* arg0) {
    f32 a;

    if (arg0->flags & 0x40) {
        if (--arg0->unk4 == 0) {
            arg0->flags &= ~0x40;
            *arg0 = D_80085B80;
        }
    } else {
        a = func_800270D0(D_8008BE5C - arg0->target->x, D_8008BE60 - arg0->target->z) + 3.141592653589793;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        a = (s32)(a / 0.39269908169872414) * 0.39269908169872414 - 0.19634954084936207;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        a += D_80085F84;
        if (a > 3.141592653589793) {
            a -= 6.283185307179586;
        } else if (a < -3.141592653589793) {
            a += 6.283185307179586;
        }
        arg0->unk54 = a;
        if (D_80092C86 & 0x20) {
            D_80085F84 += 0.7853981633974483;
            if (D_80085F84 > 3.141592653589793) {
                D_80085F84 -= 6.283185307179586;
            } else if (D_80085F84 < -3.141592653589793) {
                D_80085F84 += 6.283185307179586;
            }
        }
    }
    func_80014E04(arg0);
}

void func_80015AD8(Camera15150* arg0) {
    switch (D_80085F68.state) {
        case 0:
            if (--D_80085F68.timer == 0) {
                D_80085F68.state++;
                D_80085F68.timer = 75;
                arg0->flags |= 0x10;
            }
            break;
        case 1:
            if (--D_80085F68.timer == 0) {
                arg0->mode = D_80085F68.mode;
                arg0->flags = D_80085F68.flags;
                D_80085E48.unk78 = D_80085F68.unk14;
                D_80085E48.unk7C = D_80085F68.unk18;
            }
            break;
    }
    func_80014E04(arg0);
}

void func_80015B88(Camera15150* arg0) {
}

void func_80015B94(Camera15150* arg0, Unk15150Target* arg1) {
    f32 y;

    arg0->atX = arg1->x;
    arg0->atZ = arg1->z;
    if (arg1->unk64->unk0 == 1) {
        y = arg1->unk68->unk94;
    } else {
        y = arg1->y;
    }
    y += arg0->unk5C - arg0->atY;
    arg0->unk34 += y * arg0->unk70 * 2;
    arg0->atY += arg0->unk34;
    arg0->unk34 = arg0->unk34 * (arg0->unk74 * 0.8);
}

void func_80015C38(Camera15150* arg0, Unk15150Target* arg1) {
    f32 dx;
    f32 dz;
    f32 angle;
    f32 speed;

    dx = arg0->eyeX - arg1->x;
    dz = arg0->eyeZ - arg1->z;
    if (arg0->flags & 0x14) {
        angle = func_800270D0(dx, dz) - arg0->unk54;
        if (angle > 3.141592653589793) {
            angle -= 6.283185307179586;
        } else if (angle < -3.141592653589793) {
            angle += 6.283185307179586;
        }
        speed = arg0->unk78 * angle + arg0->unk3C;
    } else {
        speed = arg0->unk3C;
    }
    arg0->unk3C = arg0->unk7C * speed;
    D_80085C10.x = dx;
    D_80085C10.y = dz;
    func_800271B4(speed, &D_80085C10);
    arg0->eyeX = arg1->x - D_80085C10.x;
    arg0->eyeZ = arg1->z + D_80085C10.y;
}

void func_80015D78(s32 arg0) {
    D_80085CAC = 15;
    D_80085CB0 = D_8004EC68[arg0 * 2];
    D_80085CB4 = D_8004EC68[arg0 * 2 + 1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_80015DB4.s")

extern Unk15150Target D_80085C40;
extern f32 D_8007AA24;
extern u16 D_8008BE52;
void func_80015F44(s32 arg0, Unk15150Target* arg1) {
    f32 h;

    if (!(D_8008BE52 & 1)) {
        return;
    }
    if (!(D_80085E48.flags & 0x40)) {
        D_80085B80 = D_80085E48;
    }
    D_80085C40.x = arg1->x;
    D_80085C40.z = arg1->z;
    if (arg1->unk5E & 4) {
        D_80085C40.y = D_8007AA24;
    } else if (arg1->unk64->unk0 == 1) {
        D_80085C40.y = arg1->unk68->unk94;
    } else {
        D_80085C40.y = arg1->y;
    }
    D_80085C40.scale = arg1->scale;
    D_80085C40.unk64 = arg1->unk64;
    D_80085C40.unk68 = arg1->unk68;
    if (arg1->unk5E & 4) {
        h = arg1->unk64->unk1C * arg1->scale + 40.0;
    } else if (arg1->unk64->unk1C < arg1->unk64->unk18) {
        h = arg1->unk64->unk18 * arg1->scale * 2.0 + 40.0;
    } else {
        h = arg1->unk64->unk1C * arg1->scale * 2.0 + 40.0;
    }
    D_80085E48.mode = 4;
    D_80085E48.flags |= 0x40;
    D_80085E48.target = &D_80085C40;
    D_80085E48.unk58 = (arg1->unk5E & 4) ? 20.0 : 15.0;
    D_80085E48.unk48 = 0.0f;
    D_80085E48.unk4C = h;
    D_80085E48.unk4 = arg0;
    D_80085E48.unk44 = D_80085E48.unk48;
    D_80085E48.unk3C = 0.0f;
    D_80085C10.x = 0.0f;
    D_80085E48.unk40 = D_80085E48.unk44;
    D_80085C10.y = h + 10.0;
    func_800271B4(D_80085E48.unk54, &D_80085C10);
    D_80085E48.eyeX = arg1->x + D_80085C10.x;
    D_80085E48.eyeY = D_80085C40.y + D_80085E48.unk58 * 1.1;
    D_80085E48.eyeZ = arg1->z + D_80085C10.y;
    if (D_80085E48.eyeY < D_8007AA24) {
        D_80085E48.eyeY = D_8007AA24;
    }
}

void func_80016218(s32 arg0) {
    func_80015DB4(arg0);
    D_80085F68.state = 0;
    D_80085F68.timer = 15;
    D_80085F68.mode = D_80085E48.mode;
    D_80085F68.flags = D_80085E48.flags;
    D_80085F68.unk14 = 0.005f;
    D_80085F68.unk18 = 0.9f;
    D_80085E48.mode = 5;
    D_80085E48.unk54 = D_80085F68.unk10;
}

typedef struct {
    /* 0x00 */ s32 mode;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} Unk8001628C;
void func_8001628C(Unk8001628C* arg0, Unk15150Target* arg1) {
    D_80085E48.mode = arg0->mode;
    D_80085E48.flags = 0x40;
    D_80085E48.unk4C = arg0->unk18;
    D_80085E48.unk58 = arg0->unk14;
    D_80085E48.unk5C = arg0->unk10;
    D_80085E48.unk6C = 0.0f;
    D_80085E48.unk64 = 0.0f;
    D_80085E48.unk68 = D_80085E48.unk6C;
    D_80085E48.unk60 = D_80085E48.unk64;
    D_80085E48.target = arg1;
    switch (arg0->mode) {
        case 0:
            D_80085C10.x = 0.0f;
            D_80085C10.y = arg0->unk18 + 20.0;
            func_800271B4(arg1->ry - 3.141592653589793 + 0.39269908169872414, &D_80085C10);
            D_80085E48.eyeX = arg1->x - D_80085C10.x;
            D_80085E48.eyeZ = arg1->z - D_80085C10.y;
            D_80085E48.eyeY = arg1->y + arg0->unk14;
            break;
        case 1:
            D_80085E48.eyeX = arg0->x;
            D_80085E48.eyeY = arg0->y;
            D_80085E48.eyeZ = arg0->z;
            break;
    }
    D_80085E48.unk48 = 0.0f;
    D_80085E48.unk34 = 0.0f;
    D_80085E48.unk3C = 0.0f;
    D_80085E48.unk44 = D_80085E48.unk48;
    D_80085E48.unk40 = D_80085E48.unk44;
}

extern f32 D_8007AA30;
extern f32 D_80084314;
void func_800163F4(void) {
    f32 a;

    a = D_80085E48.unk28 - D_8007AA30;
    if (a < -3.141592653589793) {
        a += 6.283185307179586;
    } else if (a > 3.141592653589793) {
        a -= 6.283185307179586;
    }
    if (a > 0.7853981633974483) {
        a = 0.7853981633974483f;
    }
    if (a < -0.7853981633974483) {
        a = -0.7853981633974483f;
    }
    a += 3.141592653589793;
    if (a < -3.141592653589793) {
        a += 6.283185307179586;
    } else if (a > 3.141592653589793) {
        a -= 6.283185307179586;
    }
    D_80085E48.unk84 = a;
    D_80085E48.unk54 = D_80084314 + 3.141592653589793;
    if (D_80085E48.unk54 > 3.141592653589793) {
        D_80085E48.unk54 -= 6.283185307179586;
    } else if (D_80085E48.unk54 < -3.141592653589793) {
        D_80085E48.unk54 += 6.283185307179586;
    }
    D_80085E48.flags |= 0x10;
}

f32 func_80016578(Camera15150* arg0, f32 arg1) {
    s32 n = D_8007ABA8;
    Unk8007ABB0** p;
    Unk8007ABB0* obj;
    f32 dx;
    f32 dz;

    if (D_8007ABA8 != 0) {
        p = D_8007ABB0;
        while (n != 0) {
            obj = *p++;
            dx = obj->y - arg1;
            if (dx < 20.0) {
                dx = obj->x - arg0->eyeX;
                dz = obj->z - arg0->eyeZ;
                if (sqrtf(dx * dx + dz * dz) < 30.0) {
                    arg1 = obj->y + 30.0;
                    break;
                }
            }
            n--;
        }
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/15150/func_8001668C.s")
