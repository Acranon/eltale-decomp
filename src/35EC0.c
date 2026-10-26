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
/* This file's .data, 80061760..80061810. */
Font D_80061760[1] = {
    { 10, 13, 10, 14 },
};
Gfx D_80061770[20] = {
    {{ 0xE7000000, 0x00000000 }},
    {{ 0xBA001402, 0x00000000 }},
    {{ 0xBA001301, 0x00000000 }},
    {{ 0xB900031D, 0x0F0A4000 }},
    {{ 0xB6000000, 0x000F3205 }},
    {{ 0xB7000000, 0x00000004 }},
    {{ 0xBA000903, 0x00000C00 }},
    {{ 0xB9000002, 0x00000001 }},
    {{ 0xBA000402, 0x00000030 }},
    {{ 0xF9000000, 0x00000001 }},
    {{ 0xFCFFFFFF, 0xFFFCF279 }},
    {{ 0xBA000C02, 0x00002000 }},
    {{ 0xBB000001, 0x00800080 }},
    {{ 0xBA000E02, 0x00000000 }},
    {{ 0xB8000000, 0x00000000 }},
    {{ 0x00000000, 0xFFFFFEC0 }},
    {{ 0x00000140, 0xFFFFFEC0 }},
    {{ 0xFFFFFEC0, 0x00000000 }},
    {{ 0x00000000, 0xFFFFFFFF }},
    {{ 0x00000000, 0x00000000 }},
};
/* .bss 80092C70..80092C80 */
s32 D_80092C70;
s32 D_80092C74;

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
