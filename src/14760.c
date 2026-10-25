#include "common.h"

extern u8 D_80085988[];
extern u8 D_8004F770[];

void func_80013B60(u16 arg0) {
    D_80085988[arg0 >> 3] |= D_8004F770[arg0 & 7];
}
