#include "game/core/overlay_load.h"

/*
 * Load the title, intro, and ending ROM overlays into the shared overlay region.
 * Original file: 36DB0.c (ROM 0x36DB0).
 */

extern u8 D_DAB5F0[];
extern u8 D_DC62B0[];
extern u8 D_E22690[];
extern u8 D_E420D0[];
void func_8020C0D0(void);
void Dma_ReadRom(void *romStart, void *vram, s32 size);

void Overlay_LoadTitle(void) {
    Dma_ReadRom(D_DAB5F0, func_8020C0D0, D_DC62B0 - D_DAB5F0);
}

void Overlay_LoadIntro(void) {
    Dma_ReadRom(D_DC62B0, func_8020C0D0, D_E22690 - D_DC62B0);
}

void Overlay_LoadEnding(void) {
    Dma_ReadRom(D_E22690, func_8020C0D0, D_E420D0 - D_E22690);
}
