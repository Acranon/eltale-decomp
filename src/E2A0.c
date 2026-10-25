#include "common.h"

typedef struct {
    /* 0x00 */ s32 timer;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 frame;
    /* 0x0C */ s32 type;
    /* 0x10 */ s32 id;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 z;
} Unk80084238; /* size 0x1C */

typedef struct {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} AnimInfo;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 w;
} Unk80082020;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ struct Unk8000FA9C *unk18;
} Unk80083470; /* size 0x1C */

typedef struct Unk8000FA9C {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 scale;
    /* 0x14 */ s16 timer;
    /* 0x16 */ u16 unk16;
} Unk8000FA9C;

typedef struct {
    /* 0x00 */ u16 alpha;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ f32 vx;
    /* 0x34 */ f32 vy;
    /* 0x38 */ f32 vz;
} Particle;

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
} SpriteObj;

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0x14];
    /* 0x2C */ f32 angle;
} Unk80085E48;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ s32 unk1C;
} Unk80084994; /* size 0x20 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ Gfx *dl;
} Unk80060C48;

typedef struct {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0x0C */ Mtx mtx[1];
} MtxBuf;

u32 func_80026E90(s32);
void func_80026A00(AnimInfo *, Unk80082020 *, s32);
void func_800271B4(f32, f32 *);
void func_8001D9A8(SpriteObj *);
void func_800273C0(Mtx *, f32, f32, f32, f32, f32, f32, f32);

extern Unk80084238 D_80084238[4];
extern AnimInfo D_800579F8;
extern AnimInfo D_80057F80;
extern AnimInfo D_80058008;
extern Unk80082020 D_80082020;
extern s32 D_8007C6A8;
extern s32 D_8007C6AC;
extern s32 D_8007A17C;
extern Unk80083470 D_80083470[8];
extern Unk80083470 D_80083558[8];
extern Gfx *D_8007A184;
extern u16 D_800842A8;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

extern SpriteObj D_8004DE04;
extern u8 *D_8004DE14;
extern f32 D_8004DE1C;
typedef struct {
    f32 y;
    f32 z;
} Unk8004DE20;
extern Unk8004DE20 D_8004DE20;
extern f32 D_8004DE2C;
extern f32 D_8004DE30;
typedef struct {
    f32 a;
    f32 pad;
    f32 b;
} Unk8004DE34;
extern Unk8004DE34 D_8004DE34;
extern f32 D_8004DE3C;
extern f32 D_8004DE5C;
extern f32 D_8004DE60;
extern f32 D_8004DE64;
extern f32 D_8004DE6C;
extern f32 D_8004DE70;
extern SpriteObj D_8004DE44;
extern u8 D_8005E9F8[];
extern f32 D_80081FF0[2];
extern s32 D_8004DEC8;
extern u16 D_80081AB0[];
extern s32 D_800842BC;
extern u16 D_80124E00[];
extern s32 D_8007A180;
extern Unk80085E48 D_80085E48;
extern s32 D_80084B60;
extern s32 D_80084B64;
extern s32 D_80084B68;
extern Unk80084994 *D_80084994;
extern Unk80060C48 D_80060C48[];
extern MtxBuf D_2000000;

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ Gfx *dl;
    /* 0x14 */ u8 pad14[0xC];
} Unk8007C294; /* size 0x20 */

extern Unk8007C294 *D_8007C294;
extern s32 D_8007C2A0;

typedef struct {
    /* 0x00 */ Gfx *a;
    /* 0x04 */ Gfx *b;
} Unk8005E518;

extern Unk8005E518 D_8005E51C[];
extern Unk8005E518 D_8005E5A0[];

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[4];
} Unk8007C288C; /* size 0x14 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ Unk8007C288C *unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[2];
} Unk8007C288; /* size 0x18 */

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ Unk8000FA9C *objs;
    /* 0x1C */ u8 pad1C[0x10];
} Unk8007C28C; /* size 0x2C */

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u32 romStart;
    /* 0x08 */ u32 romEnd;
    /* 0x0C */ void *dst;
    /* 0x10 */ Unk8007C294 *unk10;
    /* 0x14 */ Unk8007C28C *unk14;
    /* 0x18 */ Unk8007C288 *unk18;
    /* 0x1C */ Unk80084994 *unk1C;
    /* 0x20 */ Unk8005E518 *unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 pad30[0xC];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 pad40[4];
} Unk8007C284; /* size 0x44 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ void *dst;
} Unk80057540; /* size 0xC */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

typedef struct {
    /* 0x00 */ s32 v[6];
} Unk8004DD98; /* size 0x18 */

void func_80028120();
void func_8000F4A0(void);
void func_8000FD54(void);
void func_800107F0(f32, f32, f32, s32, CollResult *);
extern Unk8007C284 D_80056BB0[];
extern Unk80057540 D_80057540[];
extern Unk8007C288 *D_8007C288;
extern Unk8007C28C *D_8007C28C;
extern u16 D_8007C280;
extern u16 D_8007C282;
extern s32 D_8007C298;
extern s32 D_8007C29C;
extern s32 D_800842B4;
extern u16 D_800842B8;
extern s32 D_800842C0;
extern s32 D_800842C4;
extern s32 D_800842C8;
extern s32 D_800842CC;
extern s32 D_800842D0;
extern s32 D_800842D4;
extern s32 D_800842D8;
extern s32 D_800842DC;
extern s32 D_800842E0;
extern s32 D_800842E4;
extern s32 D_80084308;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A99C;
extern u16 D_80081B78[];
extern u16 D_80081B7A[];
extern CollResult D_80082000;
extern Unk8004DD98 D_8004DD98;
extern Unk8004DD98 D_80081CE8[32];
extern u8 D_753F0[];
extern u8 D_851F0[];
extern u8 D_C8DE0[];
extern u8 D_D86170[];
extern u8 D_D86770[];
extern u8 D_3E1090[];
extern u8 D_3F1BA0[];
extern u8 D_80100000[];
extern u8 D_8010FE00[];
extern u8 D_801E0000[];
extern u16 D_800842E8;
extern u8 D_800808B0[];
extern u8 D_8007C6B0[];

extern Unk8007C284 *D_8007C284;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08;

typedef struct {
    /* 0x00 */ u16 a;
    /* 0x02 */ u16 b;
} Unk80082048;

extern Unk8007AA08 D_8007AA08;
extern Unk8000FA9C *D_8007C290;
extern s32 D_8007C2A4;
extern f32 D_800842AC;
extern s32 D_800842B0;
extern s32 D_80081CB0;
extern s32 D_80081CB4;
extern s32 D_80081CB8;
extern s32 D_80081CBC;
extern s32 D_80081CC0;
extern s32 D_80081CC4;
extern Unk8000FA9C **D_80081CC8;
extern Unk8000FA9C **D_80081CCC;
extern Unk8000FA9C **D_80081CD0;
extern Unk8000FA9C **D_80081CD4;
extern Unk8000FA9C **D_80081CD8;
extern Unk8000FA9C **D_80081CDC;
extern s32 D_80081CE0;
extern Unk8000FA9C *D_80081FE8;
extern u8 D_80060C88[];
extern u16 D_8004DD70;
extern u16 D_8004DDB0;
extern u8 *D_8004DDB4[];
extern u16 D_8004DDC8[];
extern Unk8000FA9C *D_80082860[];
extern Unk8000FA9C *D_80082C60[];
extern Unk8000FA9C *D_80083068[];
void func_80010104(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list);
extern Unk80082048 D_80082048[];
extern f32 D_8004DDD4[];
extern f32 D_8004DDE4[];
extern f32 D_8004DDF4[];
void func_8001A948(f32, f32, f32, Unk8000FA9C *);
void func_8000FA9C(Unk8000FA9C *);
void func_8000FC50(Unk8000FA9C *);
void func_8000FDA8(f32, f32, f32, f32, Unk8000FA9C *);
extern Vec3f D_80083638[];
extern f32 D_80085F50;
f32 sqrtf(f32);
f32 func_800270D0(f32, f32);
void func_80027220(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32);
void guMtxF2L(f32 (*)[4], Mtx *);
void func_800131F0(f32, f32, f32, f32, f32, f32, f32);
extern u16 D_8004DE62[];
extern u8 **D_8005E5AC[];
extern u16 D_8004DE84[];
extern u8 D_8004DE88[];
extern f32 D_80085E74;

typedef struct {
    /* 0x00 */ s32 start;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 id;
} Unk8004DE98; /* size 0x8 */

extern Unk8004DE98 D_8004DE98[];
extern s32 D_8004DE8C;
extern s32 D_8004DE90;
extern s32 D_8004DE94;
extern u16 D_800810B0[];
extern u16 D_800814B0[][0x100];
extern s32 D_80082858;
extern u16 *D_80083060;
extern u16 *D_80083468;
extern u16 *D_80083550;
extern s32 D_80084980;

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000D6A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000DDBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000DE54.s")

void func_8000E81C(MtxBuf *arg0) {
    Unk8000FA9C *s;
    s32 n;
    s32 k;
    s16 idx;
    s32 t;
    f32 rot;

    D_80081CD4 = D_80082860;
    n = D_80081CBC;
    if (n != 0) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x0C1849D8, 0);
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, D_80060C88[D_800842BC]);
        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
    }
    for (; n != 0; n--) {
        s = *D_80081CD4++;
        idx = s->timer;
        guPosition(&arg0->mtx[D_8007A180], 0.0f, s->angle, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
        D_8007A180++;
        gSPDisplayList(D_8007A184++, D_8007C294[idx].dl);
        D_8007C2A0++;
    }
    if (D_80081CC4 != 0) {
        gDPSetEnvColor(D_8007A184++, 0, 0, 0, D_80060C88[D_800842BC]);
        gDPSetRenderMode(D_8007A184++, 0xC81049D8, 0);
        gDPSetCombine(D_8007A184++, 0x121A04, 0xFFFFFFF8);
    }
    D_80081CDC = D_80083068;
    n = D_80081CC4;
    for (; n != 0; n--) {
        s = *D_80081CDC++;
        rot = s->angle;
        k = (s->unk16 & 0xFF) - 0x40;
        idx = s->timer;
        guPosition(&arg0->mtx[D_8007A180], 0.0f, rot, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
        D_8007A180++;
        gDPLoadTextureTile(D_8007A184++, D_8004DDB4[k], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, D_8004DDC8[k], 0, 0, 31,
                           D_8004DDC8[k] - 1, 0, G_TX_WRAP, G_TX_WRAP, 5, (D_8004DDC8[k] == 32) ? 5 : 6, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(D_8007A184++, G_TX_RENDERTILE, 0, (t = D_8004DDB0 % 256) << 2, 32 << 2, (D_8004DDC8[k] + t) << 2);
        gSPDisplayList(D_8007A184++, D_8007C294[idx].dl);
        D_8007C2A0++;
    }
    if (D_80081CC0 != 0) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x0C1849D8, 0);
        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
        D_80081CD8 = D_80082C60;
        func_80010104(arg0, D_80081CC0, 0x11, D_80081CD8);
        func_80010104(arg0, D_80081CC0, 0x12, D_80081CD8);
    }
    D_8004DD70++;
    gDPPipeSync(D_8007A184++);
    gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
    D_8004DDB0 += 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000EEA8.s")

void func_8000F34C(MtxBuf *arg0) {
    func_800273C0(&arg0->mtx[D_8007A180], 0.0f, 0.0f, 0.0f, 1.0f, D_80085E48.x, D_80085E48.y - 10.0f, D_80085E48.z);
    gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
    D_8007A180++;
    gDPSetEnvColor(D_8007A184++, D_80084B60, D_80084B64, D_80084B68, 255);
    gSPDisplayList(D_8007A184++, D_80060C48[D_80084994->unk1C].dl);
}

void func_8000F4A0(void) {
    Unk80084238 *p = D_80084238;
    u32 i = 4;

    while (i--) {
        p->timer = 0;
        p++;
    }
}

s32 func_8000F4C8(s32 id) {
    Unk80084238 *p;
    s32 i;

    i = 4;
    p = D_80084238;
    for (; i != 0; i--, p++) {
        if (p->timer != 0 && id == p->id) {
            i = 5 - i;
            break;
        }
    }
    return i;
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000F50C.s")

void func_8000F5DC(void) {
    Unk80084238 *p;
    s32 i;
    AnimInfo *anim;

    i = 4;
    p = D_80084238;
    do {
        if (p->timer != 0) {
            switch (p->state) {
                case 0:
                    if (--p->timer == 0) {
                        p->timer = 80;
                        p->state++;
                    }
                    break;
                case 1:
                    p->timer--;
                    switch ((p->type >> 8) & 0xF) {
                        case 2:
                        case 3:
                            if (p->type & 1) {
                                anim = &D_80057F80;
                            } else {
                                anim = &D_800579F8;
                            }
                            break;
                        case 4:
                            anim = &D_80058008;
                            break;
                    }
                    func_80026A00(anim, &D_80082020, p->frame++);
                    p->x = D_80082020.x;
                    p->z = D_80082020.w;
                    break;
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void func_8000F740(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list) {
    Unk8000FA9C *s;
    f32 dx;
    f32 dz;
    f32 a;
    f32 mf[4][4];
    s32 first;
    Unk8005E518 *e;
    Gfx *dl1;
    Gfx *dl2;
    Vec3f *c;

    first = 0;
    e = D_8007C284->unk20;
    dl1 = e[type].a;
    dl2 = e[type].b;
    for (; count != 0; count--) {
        s = *list++;
        if (type == s->timer) {
            dx = s->x - D_80085E48.x;
            dz = s->z - D_80085E48.z;
            if (sqrtf(dx * dx + dz * dz) < 1500.0f) {
                a = func_800270D0(dx, dz) - D_80085E48.angle + 3.141592653589793;
                if (a < -3.141592653589793) {
                    a += 6.283185307179586;
                } else if (a > 3.141592653589793) {
                    a -= 6.283185307179586;
                }
                if (a < 0.0f) {
                    a = -a;
                }
                a = a * 57.29577951308232;
                if (a < D_80085F50) {
                    if (first == 0) {
                        gSPDisplayList(D_8007A184++, dl1);
                        first++;
                        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
                    }
                    func_80027220(mf, 0.0f, D_80085E48.angle, 0.0f, s->scale, s->x, s->y, s->z);
                    guMtxF2L(mf, &arg0->mtx[D_8007A180]);
                    gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
                    D_8007A180++;
                    gSPDisplayList(D_8007A184++, dl2);
                    c = &D_80083638[(s32)s->angle];
                    func_800131F0(s->x, s->y, s->z, c->x, c->y, c->z, 8.0f);
                    D_8007C2A0++;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000FA9C.s")

void func_8000FBB4(Particle *arg0) {
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    arg0->vy -= 0.9;
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, (D_800842A8 & 1) ? 0xDC : 0x78);
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000FC50.s")

void func_8000FCE0(Particle *arg0) {
    arg0->y = arg0->y + arg0->vy / 2;
    arg0->vy -= 0.2;
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, arg0->alpha * 5);
}

void func_8000FD54(void) {
    s32 i;
    Unk80083470 *q;
    Unk80083470 *p;

    D_8007C6A8 = 0;
    i = 8;
    q = D_80083470;
    p = D_80083558;
    do {
        p->unk0 = 0;
        q->unk0 = 0;
        i--;
        q++;
        p++;
    } while (i != 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_8000FDA8.s")

void func_8000FF18(MtxBuf *arg0) {
    Unk80083470 *p;
    u32 i;
    Unk8000FA9C *s;

    D_8007C6A8 = D_8007C6AC;
    p = D_8007A17C ? D_80083470 : D_80083558;
    i = D_8007C6A8;
    while (i--) {
        if (p->unk0 != 0) {
            s = p->unk18;
            p->unk14 -= 0.015707963267948967;
            func_800273C0(&arg0->mtx[D_8007A180], 0.0f, p->unk10 * 0.017453292519943295, p->unk14, s->scale, s->x, s->y, s->z);
            gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
            D_8007A180++;
            gSPDisplayList(D_8007A184++, D_8007C294[s->timer].dl);
            D_8007C2A0++;
        }
        p++;
    }
}

void func_80010104(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list) {
    s32 pad1;
    s32 idx;
    s32 pad;
    u8 **tex;
    Gfx *dl;
    s32 first;
    Unk8000FA9C *s;

    idx = type - 0x11;
    dl = D_8005E51C[type].a;
    tex = D_8005E5AC[type];
    first = 0;
    for (; count != 0; count--) {
        s = *list++;
        if (type == (s->unk16 & 0xFF)) {
            if (first == 0) {
                gSPDisplayList(D_8007A184++, D_8005E5A0[idx].a);
                first++;
            }
            gDPLoadTextureBlock(D_8007A184++, tex[(s->timer >> 1) & 7], G_IM_FMT_CI, G_IM_SIZ_8b, D_8004DE84[type - 0x11], 32, 0, 0, 0, 0, 0, 0, 0);
            func_800273C0(&arg0->mtx[D_8007A180], 0.0f, D_80085E74, 0.0f, s->scale, s->x, s->y, s->z);
            gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
            D_8007A180++;
            gDPSetEnvColor(D_8007A184++, 0, 0, 0, D_8004DE88[s->timer & 3]);
            gSPDisplayList(D_8007A184++, dl);
            s->timer++;
            D_8007C2A0++;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_800104C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/func_80010768.s")
