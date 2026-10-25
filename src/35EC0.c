#include "common.h"

extern u8 D_D3A8B0[];
extern u8 D_D3A930[];
extern u8 D_80332D30[];
extern u8 D_803245A0[];
void func_80028120(void *romStart, void *vram, s32 size);

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} Font;

extern Gfx *D_8007A184;
extern Font D_80061760[];
extern Gfx D_80061770[];
extern s32 D_80092C70;
extern s32 D_80092C74;

void func_800352C0(u8 *dst, u8 *src) {
    s32 i = 0;

    while (src[i] != 0xFF) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0xFF;
}

void func_80035308(void) {
    func_80028120(D_D3A8B0, D_80332D30, 0x80);
    func_80028120(D_D3A930, D_803245A0, 0xE790);
}

#pragma GLOBAL_ASM("asm/nonmatchings/35EC0/func_80035350.s")
