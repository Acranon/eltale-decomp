#include "common.h"

typedef struct {
    char unk00[0xC0];
    Mtx unkC0[1];
} Struct_80026774;

extern Mtx D_2000000[];
extern Mtx D_2000040[];
extern Gfx D_8004F510[];
extern Gfx D_8004F550[];
extern s32 D_8007A180;
extern Gfx* D_8007A184;
extern u16 D_8008CA50;
extern u8 D_8008CA58[0x100][4];
extern s32 D_8008CE58;
typedef struct { u8 r, g, b, a; } Color_RGBA8;
extern Color_RGBA8* D_8008CE5C;

void func_800266D0(void) {
    u32 i;

    D_8008CA50 = 0;
    D_8008CE58 = 0;
    for (i = 0; i < 0x100; i++) {
        D_8008CA58[i][0] = 0xDC;
        D_8008CA58[i][1] = 0xDC;
        D_8008CA58[i][2] = 0xDC;
        D_8008CA58[i][3] = (i * 0xFF) >> 8;
    }
}

void func_80026774(Struct_80026774* arg0) {
    if (D_8008CA50 & 8) {
        gSPDisplayList(D_8007A184++, D_8004F550);
    }
    if (D_8008CA50 & 1) {
        gDPPipeSync(D_8007A184++);
        gSPMatrix(D_8007A184++, D_2000040, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        guMtxIdent(&arg0->unkC0[D_8007A180]);
        gSPMatrix(D_8007A184++, &D_2000000[D_8007A180 + 3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        D_8007A180++;
        gDPSetEnvColor(D_8007A184++, D_8008CE5C->r, D_8008CE5C->g, D_8008CE5C->b, D_8008CE5C->a);
        if (D_8008CE5C->a == 0xFF) {
            gDPSetRenderMode(D_8007A184++, 0x0F0A4000, 0);
        } else {
            gDPSetRenderMode(D_8007A184++, 0x00504340, 0);
        }
        gSPDisplayList(D_8007A184++, D_8004F510);
        if (D_8008CE58) {
            if (D_8008CA50 & 4) {
                D_8008CE5C--;
            } else {
                D_8008CE5C++;
            }
            D_8008CE58--;
            if (!D_8008CE58 & !(D_8008CA50 & 2)) {
                D_8008CA50 &= ~1;
            }
        }
    }
}

void func_800269B8(s32 arg0, u16 arg1, Color_RGBA8* arg2) {
    D_8008CE58 = arg0;
    D_8008CA50 = (arg1 | 1) | (D_8008CA50 & 8);
    D_8008CE5C = arg2;
}
