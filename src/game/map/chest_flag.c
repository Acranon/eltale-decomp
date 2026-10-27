#include "common.h"

/*
 * Chests: sets an opened flag (the rest is in 140D0).
 * Original file: 14760.c (ROM 0x14760).
 */

extern u8 chest_opened_flags[];
extern u8 math_bit_masks[];

void Chest_SetOpened(u16 arg0) {
    chest_opened_flags[arg0 >> 3] |= math_bit_masks[arg0 & 7];
}
