#include "common.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2[16];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 unk13;
} Unk80092E48; /* size = 0x14 */

typedef struct {
    u8 b[4];

} Ext4;

extern s8 D_80092C80;
extern s8 D_80092C81;
extern s8 D_80092C82;
extern u16 D_80092C84;
extern u16 D_80092C86;
extern u16 D_80092C88;
extern OSMesgQueue D_80092C90;
extern OSPfs D_80092CA8[4];
extern Unk80092E48 D_80092E48[4];
extern u8 D_80092E98;
extern OSContStatus D_80092EA0[4];
extern OSMesg D_80092EB0;
extern OSContPad D_80092EB8[4];
extern u8 D_80061810[];
extern Ext4 D_80061840;
extern Ext4 D_80061844;

s32 func_8003D910();
s32 func_8003DD44();
s32 func_8003E220();
s32 func_8003E6A0();
s32 func_8003E9E4();
s32 func_8003E080();
s32 func_8003D554();
s32 func_8003D6B0();
s32 func_8003D0F0();
s32 func_8003ED60();
s32 func_8003EDC0();
s32 func_8003DEA0();
s32 func_800360F8();
s32 func_8003E080();

#pragma GLOBAL_ASM("asm/nonmatchings/363B0/func_800357B0.s")

void func_80035970(s32 cont) {
    OSContPad *pad;
    u16 button;

    osContSetCh(4);
    osContStartReadData(&D_80092C90);
    if (osRecvMesg(&D_80092C90, NULL, 1) != -1) {
        func_8003DD44(D_80092EB8);
    }
    pad = &D_80092EB8[cont];
    button = pad->button;
    D_80092C84 = button;
    D_80092C81 = pad->stick_x;
    D_80092C82 = pad->stick_y;
    D_80092C86 = button & D_80092C88;
    D_80092C88 = ~button;
}

#pragma GLOBAL_ASM("asm/nonmatchings/363B0/func_80035A24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/363B0/func_80035CC8.s")

u8 func_80035D58(s32 arg0, u8 arg1) {
    u8 unused[4];
    s32 file_no;
    Ext4 ext;
    s32 ret;

    ext = D_80061840;
    file_no = -1;
    ext.b[0] = arg1;
    ret = func_8003E220(&D_80092CA8[arg0], 0x3943, 0x4E45544A, D_80061810, &ext, 0x200, &file_no);
    if (ret == 0) {
        ret = file_no;
        D_80092E48[arg0].unk2[ret] = arg1;
    } else {
        ret = -ret;
    }
    return ret;
}

u8 func_80035E24(s32 arg0, u8 arg1) {
    u8 unused[4];
    Ext4 ext;

    ext = D_80061844;
    ext.b[0] = arg1;
    return func_8003E6A0(&D_80092CA8[arg0], 0x3943, 0x4E45544A, D_80061810, &ext);
}

void func_80035EA8(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    func_8003E9E4(&D_80092CA8[arg0], file_no, 0, offset, nbytes, buf);
}

s32 func_80035F0C(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf) {
    s32 ret;
    s32 bytes;

    ret = func_8003E080(&D_80092CA8[arg0], &bytes);
    if (ret != 0) {
        return ret;
    }
    return func_8003E9E4(&D_80092CA8[arg0], file_no, 1, offset, nbytes, buf);
}

s32 func_80035F94(s32 arg0, s32 arg1) {
    s32 err;
    s32 cont = D_80092C80;

    if (arg1 == 10) {
        if (func_8003D554(&D_80092C90, &D_80092CA8[cont], cont) != 0) {
            if (func_8003D6B0(&D_80092C90, &D_80092CA8[cont], cont) != 0) {
                err = func_8003D0F0(&D_80092C90, &D_80092CA8[cont], cont);
                if (err != 11 && err != 1 && err != 2) {
                    err = func_8003ED60(&D_80092CA8[cont]);
                }
            } else {
                err = 4;
            }
        } else {
            err = 4;
        }
    } else {
        err = func_8003D0F0(&D_80092C90, &D_80092CA8[cont], cont);
    }
    return err;
}

s32 func_8003609C(s32 arg0) {
    s32 ret;

    switch (arg0) {
        case 1:
            ret = -1;
            break;
        case 4:
        case 11:
            ret = -2;
            break;
        case 3:
        case 10:
            ret = -3;
            break;
        case 2:
            ret = -4;
            break;
        case 9:
            ret = -5;
            break;
        default:
            ret = -6;
            break;
    }
    return ret;
}

s32 func_800360F8(u8 *a, u8 *b, s32 n) {
    do {
        if (*a++ != *b++) {
            break;
        }
    } while (n--);
    return n;
}

void func_80036124(void) {
    func_8003EDC0();
}

void func_80036144(OSMesgQueue *mq) {
    osContStartQuery(mq);
}

void func_80036164(OSContStatus *status) {
    osContGetQuery(status);
}

void func_80036184(void) {
    func_8003D6B0();
}
