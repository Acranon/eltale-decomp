#include "PR/ultratypes.h"
#include "string.h"

/* The build uses -signed; ultralib's libc is built with IDO's default unsigned
 * char, so the char pointers here are spelled unsigned. */

/* IDO -O3 emits functions in reverse source order. */

char* strchr(const char* s, int c) {
    const unsigned char ch = c;
    while (*(const unsigned char*)s != ch) {
        if (*(const unsigned char*)s == 0) {
            return NULL;
        }
        s++;
    }
    return (char*)s;
}

size_t strlen(const char* s) {
    const unsigned char* sc = (const unsigned char*)s;
    while (*sc != 0) {
        sc++;
    }
    return sc - (const unsigned char*)s;
}

void* memcpy(void* s1, const void* s2, size_t n) {
    unsigned char* su1 = (unsigned char*)s1;
    const unsigned char* su2 = (const unsigned char*)s2;
    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }
    return (void*)s1;
}
