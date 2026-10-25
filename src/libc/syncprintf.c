#include "stdarg.h"
#include "PR/os.h"
#include "PR/os_internal.h"

/* _FINALROM build: both are empty. IDO -O3 emits functions in reverse source
 * order, so ultralib's osSyncPrintf, rmonPrintf come out as rmonPrintf
 * (0x8003D8D0, currently named osSyncPrintf) then osSyncPrintf (0x8003D8EC).
 * The two are byte-identical, so the order can't be proven from the code. */

void func_8003D8EC(const char* fmt, ...) {
    int ans;
    va_list ap;
}

void osSyncPrintf(const char* fmt, ...) {
    int ans;
    va_list ap;
}
