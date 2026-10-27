#include "common.h"

/*
 * Load the title, intro, and ending ROM overlays into the shared overlay region.
 * Folder: src/game/core/
 */

extern u8 D_DAB5F0[];
extern u8 D_DC62B0[];
extern u8 D_E22690[];
extern u8 D_E420D0[];
void func_8020C0D0(void);
void func_80028120(void *romStart, void *vram, s32 size);

void func_800361B0(void) {
    func_80028120(D_DAB5F0, func_8020C0D0, D_DC62B0 - D_DAB5F0);
}

void func_800361E8(void) {
    func_80028120(D_DC62B0, func_8020C0D0, D_E22690 - D_DC62B0);
}

void func_80036220(void) {
    func_80028120(D_E22690, func_8020C0D0, D_E420D0 - D_E22690);
}
