#include "common.h"

extern u8 D_D3A8B0[];
extern u8 D_D3A930[];
extern u8 D_80332D30[];
extern u8 D_803245A0[];
void func_80028120(void *romStart, void *vram, s32 size);

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
