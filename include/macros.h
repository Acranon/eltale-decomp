#ifndef MACROS_H
#define MACROS_H

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define ALIGNED(x) __attribute__((aligned(x)))
#define UNUSED __attribute__((unused))

#endif
