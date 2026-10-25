#include "common.h"

void func_80036AC0(void);
void func_80037020(s32, OSMesgQueue *, OSMesg *, s32);
void func_800004B0(void *);
void func_80000C70(void *);

extern OSThread D_80072D20;
extern OSThread D_80072ED0;
extern u8 D_80074080[];
extern OSMesgQueue D_80077080;
extern OSMesg D_80077098[];

void func_80000450(s32 arg0) {
    func_80036AC0();
    osCreateThread(&D_80072D20, 1, func_800004B0, NULL, D_80074080, 1);
    osStartThread(&D_80072D20);
}

void func_800004B0(void *arg0) {
    func_80037020(OS_PRIORITY_PIMGR, &D_80077080, D_80077098, 0x32);
    osCreateThread(&D_80072ED0, 6, func_80000C70, arg0, &D_80077080, 5);
    osStartThread(&D_80072ED0);
    for (;;) {}
}
