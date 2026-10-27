#include "common.h"

/*
 * Boot: the entry point's first C function and the idle thread, which starts the PI
 * manager and the main game thread.
 * Folder: src/game/core/   (proposed for round 4)
 */

void func_80036AC0(void);
void osCreatePiManager(s32, OSMesgQueue *, OSMesg *, s32);
void Boot_IdleThread(void *);
void Core_MainThread(void *);

/* This file's .bss, 80070D20..80077160, in address order. boot_stack is the
 * boot stack: the entry code (asm/1000.s) clears bss from its address and starts
 * sp at its end, boot_idle_thread. Thread stacks are passed by their top (the end of the
 * array, which is the next object's address): thread 1 runs on boot_idle_thread_stack, thread 6
 * on boot_main_thread_stack. */
u64 boot_stack[0x2000 / sizeof(u64)];
OSThread boot_idle_thread;
OSThread boot_main_thread;
u64 boot_idle_thread_stack[0x1000 / sizeof(u64)];
u64 boot_main_thread_stack[0x3000 / sizeof(u64)];
OSMesgQueue boot_pi_mesg_queue;
OSMesg boot_pi_mesgs[0x32];

void Boot_Main(s32 arg0) {
    func_80036AC0();
    osCreateThread(&boot_idle_thread, 1, Boot_IdleThread, NULL, boot_idle_thread_stack + ARRAY_COUNT(boot_idle_thread_stack), 1);
    osStartThread(&boot_idle_thread);
}

void Boot_IdleThread(void *arg0) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &boot_pi_mesg_queue, boot_pi_mesgs, 0x32);
    osCreateThread(&boot_main_thread, 6, Core_MainThread, arg0, boot_main_thread_stack + ARRAY_COUNT(boot_main_thread_stack), 5);
    osStartThread(&boot_main_thread);
    for (;;) {}
}
