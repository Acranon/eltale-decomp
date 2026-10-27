#include "common.h"

/*
 * Encoded text and font rendering: string copying, font DMA, and glyph drawing.
 * Folder: src/game/text/
 */

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

void Text_CopyTerminatedBytes(u8 *dst, u8 *src) {
    s32 i = 0;

    while (src[i] != 0xFF) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0xFF;
}

void Text_LoadFontAssets(void) {
    func_80028120(D_D3A8B0, D_80332D30, 0x80);
    func_80028120(D_D3A930, D_803245A0, 0xE790);
}

void Text_DrawEncodedString(s32 x0, s32 y0, u8 *str) {
    s32 x = x0;
    s32 y = y0;
    s32 c;

    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    for (; *str != 0xFF; str++) {
        if (*str & 0x80) {
            c = *str & 0x1F;
            switch (*str & 0x60) {
                case 0x00:
                    gDPLoadTextureTile_4b(D_8007A184++, D_803245A0 + c * 0x7B8, G_IM_FMT_CI, 304, 13, 0, 0, 303, 12, 0, 0, 0, 0, 0, 0, 0);
                    break;
                case 0x20:
                    gDPLoadTLUT_pal16(D_8007A184++, 0, (u16 *) D_80332D30 + c * 16);
                    break;
                case 0x40:
                    if (c < 16) {
                        D_80092C70 = c;
                    } else {
                        D_80092C74 = c;
                    }
                    break;
                case 0x60:
                    switch (c) {
                        case 0x13:
                            break;
                        case 0x14:
                            break;
                        case 0x1E:
                            gSPDisplayList(D_8007A184++, D_80061770);
                            break;
                        case 0:
                            x = x0;
                            y += D_80061760[D_80092C70].unkC;
                            break;
                    }
                    break;
            }
        } else {
            c = *str & 0x7F;
            if (*str == 0x7F) {
                x += D_80061760[D_80092C70].unk8 + D_80092C74;
            } else {
                gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + D_80061760[D_80092C70].unk0) << 2, (D_80061760[D_80092C70].unk4 + y) << 2, G_TX_RENDERTILE,
                                    (D_80061760[D_80092C70].unk0 * c) << 5, 0, 1 << 10, 1 << 10);
                x += D_80061760[D_80092C70].unk8 + D_80092C74;
            }
        }
    }
    gDPPipeSync(D_8007A184++);
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
}
