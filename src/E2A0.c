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
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

/* Part of this file's .bss, 80082860..800842F0 (the run 80082030..80082860
 * comes first: see D_80082030). These objects are declared here, before the
 * file's 256th declaration, and IDO emits the later declaration block (with
 * D_80082030..D_80082858) first. */
Unk8000FA9C *D_80082860[0x100];
Unk8000FA9C *D_80082C60[0x100];
u16 *D_80083060;
Unk8000FA9C *D_80083068[0x100];
u16 *D_80083468;
Unk80083470 D_80083470[8];
u16 *D_80083550;
Unk80083470 D_80083558[8];
Vec3f D_80083638[0x100];
Unk80084238 D_80084238[4];
u16 D_800842A8;
f32 D_800842AC;
s32 D_800842B0;
s32 D_800842B4;
u16 D_800842B8;
s32 D_800842BC;
s32 D_800842C0;
s32 D_800842C4;
s32 D_800842C8;
s32 D_800842CC;
s32 D_800842D0;
s32 D_800842D4;
s32 D_800842D8;
s32 D_800842DC;
s32 D_800842E0;
s32 D_800842E4;
u16 D_800842E8;

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
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ u8 *unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 unk3C;
} SpriteObj; /* size 0x40 */

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

u32 func_80026E90(u32);
void func_80026A00(AnimInfo *, Unk80082020 *, s32);
void func_800271B4(f32, f32 *);
void func_8001D9A8(SpriteObj *);
void func_800273C0(Mtx *, f32, f32, f32, f32, f32, f32, f32);

extern AnimInfo D_800579F8;
extern AnimInfo D_80057F80;
extern AnimInfo D_80058008;
extern Unk80082020 D_80082020;
extern s32 D_8007C6A8;
extern s32 D_8007C6AC;
extern s32 D_8007A17C;
extern Gfx *D_8007A184;

extern u8 D_8005E9F8[];
extern f32 D_80081FF0[2];
extern u16 D_80081AB0[];
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
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
    /* 0x08 */ f32 originX;
    /* 0x0C */ f32 originZ;
    /* 0x10 */ f32 cellW;
    /* 0x14 */ f32 cellD;
    /* 0x18 */ Unk8000FA9C *objs;
    /* 0x1C */ u16 *cells;
    /* 0x20 */ u16 *lists;
    /* 0x24 */ u16 *unk24;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u8 pad2A[2];
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
void func_800107F0(f32, f32, f32, u16, CollResult *);
extern Unk8007C284 D_80056BB0[];
extern Unk80057540 D_80057540[];
extern Unk8007C288 *D_8007C288;
extern Unk8007C28C *D_8007C28C;
extern u16 D_8007C280;
extern u16 D_8007C282;
extern s32 D_8007C298;
extern s32 D_8007C29C;
extern s32 D_80084308;
extern f32 D_8007A98C;
extern f32 D_8007A990;
extern f32 D_8007A994;
extern s32 D_8007A99C;
extern u16 D_80081B78[];
extern u16 D_80081B7A[];
extern CollResult D_80082000;
extern Unk8004DD98 D_80081CE8[32];
extern u8 D_753F0[];
extern u8 D_851F0[];
/* Same address as D_851F0: the end of the ROM block that starts at D_753F0 (a separate linker symbol in the original). */
extern u8 D_851F0_end[];
extern u8 D_C8DE0[];
extern u8 D_D86170[];
extern u8 D_D86770[];
extern u8 D_3E1090[];
extern u8 D_3F1BA0[];
extern u8 D_80100000[];
extern u8 D_8010FE00[];
extern u8 D_801E0000[];
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
void func_80010104(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list);
/* Part of this file's .bss, 80082030..80082860 (the 16-byte-aligned run that
 * holds func_800104C0's static at 80082858). Nothing names 80082030..80082048
 * (splat's D_80082030 is func_8000D6A0's loop end), so it is a placeholder. */
u8 D_80082030[0x18];
Unk80082048 D_80082048[4];
u16 D_80082058[0x200];
u16 D_80082458[0x200];
void func_8001A948(f32, f32, f32, Unk8000FA9C *);
void func_8000FA9C(Unk8000FA9C *);
void func_8000FC50(Unk8000FA9C *);
void func_8000FDA8(f32, f32, f32, f32, Unk8000FA9C *);
extern f32 D_80085F50;
f32 sqrtf(f32);
f32 func_800270D0(f32, f32);
void func_80027220(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32);
void guMtxF2L(f32 (*)[4], Mtx *);
void func_800131F0(f32, f32, f32, f32, f32, f32, f32);
extern u8 **D_8005E5AC[];
extern f32 D_80085E74;

typedef struct {
    /* 0x00 */ s32 start;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 id;
} Unk8004DE98; /* size 0x8 */

extern u16 D_800810B0[];
extern u16 D_800814B0[][0x100];
extern s32 D_80084980;

/* This file's .data, 8004DD70..8004DED0, in source order: these tables, then
 * the static sprite descriptors of func_8000FA9C (8004DE04) and func_8000FC50
 * (8004DE44), then the tables defined after func_8000FC50. IDO stores a
 * function-static descriptor's fields with lui/%lo (sharing the lui inside a
 * 16-byte line), which both functions need. D_8004DD8B (func_8000DE54's asm
 * name for D_8004DD88 + 3) is an alias in undefined_syms.txt. */
u16 D_8004DD70 = 0;
s32 D_8004DD74[4] = { 0x00000000, 0x01600160, 0x01600160, 0x01600100 };
s32 D_8004DD84 = 0x00500050;
s32 D_8004DD88[4] = { 0x19, 0x1B, 0x1E, 0x20 };
Unk8004DD98 D_8004DD98 = { { 0 } };
u16 D_8004DDB0 = 0;
u8 *D_8004DDB4[5] = {
    (u8 *)0x801093B0, (u8 *)0x8010A3B0, (u8 *)0x80129D10, (u8 *)0x80160B30, (u8 *)0x8014DA40,
};
u16 D_8004DDC8[6] = { 0x40, 0x40, 0x20, 0x40, 0x20, 0 };
f32 D_8004DDD4[4] = { 0.0f, 5000.0f, 1000.0f, 3000.0f };
f32 D_8004DDE4[4] = { 0.0f, 30000.0f, 30000.0f, 48000.0f };
f32 D_8004DDF4[4] = { 0.0f, 1000.0f, 5000.0f, 3000.0f };

void func_8000D6A0(void) {
    u32 *q;
    u32 start;
    u32 end;
    u16 *src;
    u16 *dst;
    s32 i;
    Unk8007C288C *sp;
    u32 n;
    Unk8000FA9C *s;
    Vec3f *v;
    s32 k;
    s32 kind;
    Unk80082048 *z;

    D_8007C284 = &D_80056BB0[D_800842C4];
    if (D_800842BC != -1) {
        if (D_800842C4 == 11) {
            if (D_800842C0 == 2 && D_800842C8 == 0) {
                D_800842D0 = D_800842C4;
                D_800842D4 = D_800842C8;
                D_800842D8 = D_80084308;
            }
        } else if (D_800842C4 == 6) {
            D_800842D0 = D_800842C4;
            D_800842D4 = D_800842C8;
            D_800842D8 = D_80084308;
        } else if ((D_800842B8 & 1) && (D_8007C284->flags & 4)) {
            D_800842D0 = D_800842C4;
            D_800842D4 = D_800842C8;
            D_800842D8 = D_80084308;
        } else if (D_800842C4 != D_800842BC && (D_8007C284->flags & 8)) {
            D_800842DC = D_800842C4;
            D_800842E0 = D_800842C8;
            D_800842E4 = D_80084308;
            if (D_800842DC == 0x1A && D_800842E0 == 4) {
                D_800842E0 = 2;
                D_800842E4 = 1;
            }
        }
    }
    if (D_800842BC == -1) {
        func_80028120(D_753F0, D_80100000, D_851F0_end - D_753F0);
        func_80028120(D_D86170, D_800814B0, 0x600);
        func_80028120(D_D86770, D_80081AB0, 0x200);
    }
    if (D_800842BC != D_800842C4) {
        D_800842CC = D_800842BC;
        D_800842BC = D_800842C4;
        D_800842B8 = D_8007C284->flags;
        if (D_800842B8 & 7) {
            if (D_800842B8 & 2) {
                func_80028120(D_851F0, D_8010FE00, D_C8DE0 - D_851F0);
            }
            q = &((u32 *)D_80057540)[D_8007C284->unk3C * 3];
            start = *q++;
            end = *q++;
            func_80028120(start, *q, end - start);
        }
        func_80028120(D_8007C284->romStart, D_8007C284->dst, D_8007C284->romEnd - D_8007C284->romStart);
        switch (D_800842BC) {
            case 3:
            case 5:
            case 7:
            case 12:
                func_80028120(D_3E1090, D_801E0000, D_3F1BA0 - D_3E1090);
                break;
        }
    }
    n = 0x65;
    src = D_80081B78;
    dst = D_80081B7A;
    do {
        *dst++ = *src--;
        n--;
    } while (n != 0);
    k = D_800842C0 = D_800842C8;
    D_8007C288 = &D_8007C284->unk18[k];
    D_8007C294 = D_8007C284->unk10;
    D_8007C28C = &D_8007C284->unk14[D_8007C288->unk0];
    D_80084994 = &D_8007C284->unk1C[D_8007C288->unk2];
    D_8007C290 = D_8007C28C->objs;
    D_8007C298 = D_8007C284->unk2C;
    D_8007C29C = D_8007C284->unk28;
    D_800842E8 = D_8007C288->unk14;
    D_8007C280 = D_80084994->unk18;
    if (D_8007C282 != D_80084994->unk1C) {
        D_8007C282 = D_80084994->unk1C;
        func_80028120(D_80060C48[D_8007C282].start, D_800808B0, 0x800);
        func_80028120(D_80060C48[D_8007C282].start + 0x800, D_8007C6B0, 0x4000);
    }
    if (D_80084308 != -1) {
        sp = &D_8007C288->unkC[D_80084308];
        D_8007A98C = sp->x;
        D_8007A990 = sp->y;
        D_8007A994 = sp->z;
        D_8007A99C = sp->unkE;
    }
    n = D_8007C28C->count;
    s = D_8007C290;
    D_8007C2A4 = k = 0;
    v = D_80083638;
    for (; n != 0; n--, s++) {
        if (s->unk16 & 0x8000) {
            func_800107F0(s->x, s->y, s->z, 0xA00, &D_80082000);
            s->y = D_80082000.y;
        }
        kind = s->unk16 & 0xFF;
        if (kind == 0x10) {
            v->x = D_80082000.nx;
            v->y = D_80082000.ny;
            v->z = D_80082000.nz;
            s->angle = k++;
            v++;
        } else if (kind == 0x83) {
            s->timer = 0;
        } else if (kind == 0x84) {
            s->timer = func_80026E90(150) + 150;
        } else if (s->unk16 >= 0x11 && s->unk16 < 0x15) {
            s->timer = func_80026E90(16);
        }
    }
    for (z = D_80082048; z < &D_80082048[4]; z++) {
        z->a = 0;
        z->b = 0;
    }
    for (i = 0; i < 32; i++) {
        D_80081CE8[i] = D_8004DD98;
    }
    D_80081CE0 = 1;
    func_8000F4A0();
    func_8000FD54();
    D_800842B4 = -1;
}

void func_8000DDBC(void) {
    s32 i;
    s32 tmp;
    u16 *p;

    D_8007C6AC = 0;
    if (D_800842BC == 0x1D) {
        i = 18; p = D_80124E00 + i; tmp = *p;
        for (; i != 0; i--, p--) { *p = *(p - 1); }
        *p = tmp;
        D_800842A8++;
    }
}

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

void func_8000EEA8(s32 count, u16 *ids) {
    Unk8000FA9C *s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    u16 kind;

    for (; count != 0; count--) {
        s = &D_8007C290[*ids++];
        if (s->unk16 & 0x1000) {
            dx = s->x - D_8007AA08.x;
            dy = s->y - D_8007AA08.y;
            dz = s->z - D_8007AA08.z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            if (d < D_800842AC) {
                D_800842AC = d;
                D_800842B0 = (s->unk16 & 0xF00) >> 8;
            }
        }
        kind = s->unk16;
        if (s->unk16 & 0x2000) {
            kind = 0;
        } else {
            kind = (u8)kind;
        }
        if (!kind || kind == 8) {
            if (s->unk16 & 0x4000) {
                *D_80081CCC++ = s;
                D_80081CB4++;
            } else {
                *D_80081CC8++ = s;
                D_80081CB0++;
            }
        } else if (kind < 4) {
            if (D_80081CE0 != 0) {
                *D_80081FE8 = *s;
            }
            s->x = sins(D_80082048[kind].a + 0xA000) / D_8004DDD4[kind] + D_80081FE8->x;
            s->z = sins(D_80082048[kind].a + 0x2000) / D_8004DDF4[kind] + D_80081FE8->z;
            s->y = sins(D_80082048[kind].b) / D_8004DDE4[kind] + D_80081FE8->y;
            *D_80081CD4++ = s;
            D_80081CBC++;
            D_80081FE8++;
        } else if (kind == 0x11 || kind == 0x12) {
            *D_80081CD8++ = s;
            D_80081CC0++;
        } else if (kind == 0x10) {
            *D_80081CD0++ = s;
            D_80081CB8++;
            D_8007C2A4++;
        } else if (kind == 0x7F || kind == 0x80) {
            *D_80081CD4++ = s;
            D_80081CBC++;
        } else if (kind == 0x81) {
            func_8001A948(s->x, s->y, s->z, s);
        } else if (kind == 0x83) {
            func_8000FA9C(s);
        } else if (kind == 0x84) {
            func_8000FC50(s);
        } else if (kind == 0x82) {
            func_8000FDA8(s->x, s->y, s->z, s->angle, s);
        } else if (kind >= 0x40 && kind < 0x46) {
            *D_80081CDC++ = s;
            D_80081CC4++;
        }
    }
}

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

void func_8000F50C(s32 state, s32 frame, s32 type, s32 id) {
    Unk80084238 *p;
    s32 i;
    AnimInfo *anim;

    i = 3;
    p = D_80084238;
    // D_80084238[0].timer, read through the preceding array so IDO does not share its address with p
    if (*(s32 *)&D_80083638[256] != 0) {
        do {
            i--;
            p++;
            if (i == 0) {
                break;
            }
        } while (p->timer != 0);
    }
    p->state = state;
    p->frame = frame;
    p->type = type;
    p->id = id;
    p->z = 0.0f;
    p->x = 0.0f;
    if (state != 0) {
        switch ((type >> 8) & 0xF) {
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
        p->timer = anim->unk6 - frame + 1;
    } else {
        p->timer = 7;
    }
}

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

void func_8000FBB4(Particle *arg0);
void func_8000FCE0(Particle *arg0);
extern u8 D_80060A38[];
extern u8 D_80060AB8[];
extern u8 D_80060BF8[];

void func_8000FA9C(Unk8000FA9C *arg0) {
    static SpriteObj D_8004DE04 = {
        0x23, 0, (void *)func_8000FBB4, 0x07202000, 0, D_8005E9F8, D_80060A38,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 15.0f, 0.0f, 0,
    };

    arg0->timer++;
    if (arg0->timer >= 0) {
        D_8004DE04.x = arg0->x;
        D_8004DE04.y = arg0->y;
        D_8004DE04.z = arg0->z;
        D_8004DE04.unk28 = D_8004DE04.unk2C = arg0->scale * 10.0;
        D_80081FF0[0] = arg0->scale * 2.0;
        D_80081FF0[1] = 0.0f;
        func_800271B4(arg0->angle, D_80081FF0);
        D_8004DE04.unk30 = D_80081FF0[0];
        D_8004DE04.unk38 = D_80081FF0[1];
        D_8004DE04.unk10 = &D_8005E9F8[arg0->timer << 10];
        func_8001D9A8(&D_8004DE04);
        if (arg0->timer >= 7) {
            arg0->timer = func_80026E90(0x3C) - 0x78;
        }
    }
}

void func_8000FBB4(Particle *arg0) {
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    arg0->vy -= 0.9;
    gDPSetEnvColor(D_8007A184++, 255, 255, 255, (D_800842A8 & 1) ? 0xDC : 0x78);
}

void func_8000FC50(Unk8000FA9C *arg0) {
    static SpriteObj D_8004DE44 = {
        0xF, 0, (void *)func_8000FCE0, 0x00081000, 0, D_80060AB8, D_80060BF8,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0,
    };

    arg0->timer--;
    if (arg0->timer == 0) {
        D_8004DE44.x = arg0->x;
        D_8004DE44.y = arg0->y;
        D_8004DE44.z = arg0->z;
        D_8004DE44.unk28 = D_8004DE44.unk2C = arg0->scale;
        func_8001D9A8(&D_8004DE44);
        arg0->timer = func_80026E90(0x96) + 0x96;
    }
}

/* The rest of this file's .data. */
u16 D_8004DE84[2] = { 0x10, 0x10 };
u8 D_8004DE88[4] = { 0x82, 0xDC, 0x78, 0xF0 };
extern Unk8004DE98 D_8004DE98[];

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

void func_8000FDA8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Unk8000FA9C *arg4) {
    Unk80083470 *prev;
    Unk80083470 *cur;
    s32 i;

    cur = D_8007A17C ? D_80083470 : D_80083558;
    prev = D_8007A17C ? D_80083558 : D_80083470;
    if (D_8007C6AC < 8) {
        cur += D_8007C6AC;
        i = D_8007C6A8;
        while (i != 0 && arg4 != prev->unk18) {
            i--;
            prev++;
        }
        if (i != 0) {
            cur->unk0 = prev->unk0;
            cur->unk14 = prev->unk14;
        } else {
            cur->unk0 = 1;
            cur->unk14 = (f32)func_80026E90(8) * 3.141592653589793 / 4.0f;
        }
        cur->unk4 = arg0;
        cur->unk8 = arg1;
        cur->unkC = arg2;
        cur->unk10 = arg3;
        cur->unk18 = arg4;
        D_8007C6AC++;
    }
}

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

void func_800104C0(void) {
    static s32 D_8004DE8C = 0;
    static s32 D_8004DE90 = 1;
    static s32 D_8004DE94 = 1;
    static s32 D_80082858;
    Unk8004DE98 *p;
    s32 inv;
    u16 *src;
    u16 *src2;
    u16 *dst;
    s32 i;
    u16 r1;
    u16 g1;
    u16 b1;
    u16 r2;
    u16 g2;
    u16 b2;

    p = D_8004DE98;
    while (p->id != 0xFF) {
        if (D_80084980 >= p->start && D_80084980 < p[1].start) {
            D_8004DE8C = p->id;
            break;
        }
        p++;
    }
    if (D_8004DE8C != D_8004DE94) {
        D_80083060 = (u16 *)D_800814B0 + D_8004DE94 * 0x100;
        D_8004DE90 = D_80082858 = p->unk4;
        D_80083468 = (u16 *)D_800814B0 + D_8004DE8C * 0x100;
        D_80083550 = D_800810B0;
    }
    if (D_8004DE90 != 0) {
        dst = D_80083550;
        src = D_80083060;
        src2 = D_80083468;
        inv = D_80082858 - D_8004DE90;
        i = 0x100;
        while (i--) {
            r1 = (*src & 0xF800) >> 11;
            g1 = (*src & 0x7C0) >> 6;
            b1 = (*src & 0x3E) >> 1;
            r2 = (*src2 & 0xF800) >> 11;
            g2 = (*src2 & 0x7C0) >> 6;
            b2 = (*src2 & 0x3E) >> 1;
            if (src) {
                /* empty: changes IDO's register colouring to retail's (permuter) */
            }
            src++;
            src2++;
            *dst++ = (((r1 * D_8004DE90 + r2 * inv) / D_80082858) << 11) | (((g1 * D_8004DE90 + g2 * inv) / D_80082858) << 6) | (((b1 * D_8004DE90 + b2 * inv) / D_80082858) << 1);
        }
        D_8004DE90--;
    }
    D_8004DE94 = D_8004DE8C;
}

/* func_800104C0's statics come first, then these. */
Unk8004DE98 D_8004DE98[6] = {
    { 0, 0x1C, 2 }, { 0x15F9, 0x80, 0 }, { 0x4F1A, 0x1C, 1 },
    { 0x6513, 0x1C, 2 }, { 0x6977, 0x1C, 2 }, { 0x6979, 0xFF, 0xFF },
};
s32 D_8004DEC8 = 0;

extern u16 D_80081AB0[];
extern u16 D_80081C40;
extern u16 D_80081C42;

void func_80010768(void) {
    s32 *cnt = &D_8004DEC8;
    s32 v;
    u16 *p;
    u16 tmp;

    v = *cnt;
    if (v >= 0) {
    lbl:;
        tmp = D_80081AB0[0xC9];
        *cnt = 0;
        D_80081C42 = D_80081C40;
        v = 200; p = D_80081AB0 + 199;
        for (; v != 0; v--, p--) { p[1] = p[0]; }
        D_80081AB0[0] = tmp;
    } else {
        v++; *cnt = v;
    }
}
