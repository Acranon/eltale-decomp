#include "common.h"

extern u16 D_8008FB3C;
extern u16 D_8008FB3E;
extern u16 D_8008FB70;

void func_8002A930(void) {
    D_8008FB3E = 0x8000;
    D_8008FB70 = 0;
    D_8008FB3C = 0;
}

void func_8002A954(void) {
    D_8008FB3E = (D_8008FB3E & 3) | 0x8000;
    D_8008FB70 = 0;
    D_8008FB3C = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002A984.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002AC1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002AE58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002B844.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002C598.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002D7CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002DECC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002E42C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002E9DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002EED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002F2E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002F6D8.s")

typedef struct { s8 a; s8 b; } Unk80060F30;
extern Unk80060F30 D_80060F30[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern s32 D_8008FB50;
extern s32 D_8008FB54;
extern f32 D_80060F28;
extern f32 D_80060F2C;
extern s16 D_800614B4[];
extern s16 D_800614CC[];
extern f32 D_8008FB48;
extern f32 D_8008FB4C;

#pragma GLOBAL_ASM("asm/nonmatchings/2B530/func_8002F87C.s")
