#include "common.h"

void func_80036AC0(void);
void osCreatePiManager(s32, OSMesgQueue *, OSMesg *, s32);
void func_800004B0(void *);
void func_80000C70(void *);

/* This file's .bss, 80070D20..80077160, in address order. D_80070D20 is the
 * boot stack: the entry code (asm/1000.s) clears bss from its address and starts
 * sp at its end, D_80072D20. Thread stacks are passed by their top, which is the
 * next object's address: thread 1 runs on D_80073080 (top D_80074080), thread 6
 * on D_80074080 (top D_80077080). */
u64 D_80070D20[0x2000 / sizeof(u64)];
OSThread D_80072D20;
OSThread D_80072ED0;
u64 D_80073080[0x1000 / sizeof(u64)];
u64 D_80074080[0x3000 / sizeof(u64)];
OSMesgQueue D_80077080;
OSMesg D_80077098[0x32];

void func_80000450(s32 arg0) {
    func_80036AC0();
    osCreateThread(&D_80072D20, 1, func_800004B0, NULL, D_80074080, 1);
    osStartThread(&D_80072D20);
}

void func_800004B0(void *arg0) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_80077080, D_80077098, 0x32);
    osCreateThread(&D_80072ED0, 6, func_80000C70, arg0, &D_80077080, 5);
    osStartThread(&D_80072ED0);
    for (;;) {}
}
