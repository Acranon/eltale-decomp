#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 rz;
    /* 0x18 */ f32 scale;
} Unk84B80; // size = 0x1C

extern s32 D_80085280;
extern Unk84B80 D_80084B80[];
extern Gfx* D_8007A184;
extern s32 D_8007A180;
extern s16 D_8007A1A0;
extern s16 D_8007A1A2;
extern Gfx D_1000270[];
extern Vtx D_1000230[];
typedef struct {
    /* 0x00 */ Mtx unk0[3];
    /* 0xC0 */ Mtx unkC0[1];
} Unk2000000;

extern Unk2000000 D_2000000;

void func_800278C8(f32 (*mf)[4], f32, f32, f32);
void func_80027CB4(f32 (*mf)[4], f32, f32, f32);

void func_800131F0(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale) {
    Unk84B80* p;

    if ((u32)D_80085280 < 0x40) {
        p = &D_80084B80[D_80085280++];
        p->x = x;
        p->y = y;
        p->z = z;
        p->rx = rx;
        p->ry = ry;
        p->rz = rz;
        p->scale = scale;
    }
}

void func_80013264(Unk2000000* arg0) {
    s32 n = D_80085280;
    Unk84B80* p = D_80084B80;
    f32 mf[4][4];

    if (n != 0) {
        gSPDisplayList(D_8007A184++, D_1000270);
        gSPFogPosition(D_8007A184++, D_8007A1A2, D_8007A1A0);
    }
    while (n != 0) {
        func_800278C8(mf, p->rx, p->ry, p->rz);
        mf[3][0] = p->x;
        mf[3][1] = p->y;
        mf[3][2] = p->z;
        func_80027CB4(mf, p->scale, p->scale, p->scale);
        guMtxF2L(mf, &arg0->unkC0[D_8007A180]);
        gSPMatrix(D_8007A184++, &D_2000000.unkC0[D_8007A180], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        D_8007A180++;
        gSPVertex(D_8007A184++, D_1000230, 4, 0);
        gSP2Triangles(D_8007A184++, 0, 1, 2, 0, 1, 3, 2, 0);
        n--;
        p++;
    }
}
