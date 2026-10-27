#include "common.h"

/*
 * Shadows: clears the shadow queue (the queue and drawing are in 13DF0).
 * Original file: 13DE0.c (ROM 0x13DE0).
 */

extern s32 shadow_count;

void Shadow_ClearQueue(void) {
    shadow_count = 0;
}
