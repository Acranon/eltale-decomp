#ifndef GAME_CORE_BOOT_H
#define GAME_CORE_BOOT_H

#include "common.h"

extern u64 boot_stack[0x2000 / sizeof(u64)];
extern OSThread boot_idle_thread;
extern OSThread boot_main_thread;
extern u64 boot_idle_thread_stack[0x1000 / sizeof(u64)];
extern u64 boot_main_thread_stack[0x3000 / sizeof(u64)];
extern OSMesgQueue boot_pi_mesg_queue;
extern OSMesg boot_pi_mesgs[0x32];

void Boot_Main(s32 arg0);
void Boot_IdleThread(void *arg0);

#endif
