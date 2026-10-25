#include "common.h"

typedef struct {
    u8 unk0;
    s8 unk1;
    u8 unk2;
} BgmFade;

typedef struct {
    s16 unk0;
    s16 unk2;
    s8 unk4;
} BgmMapEntry;

extern s8 D_8008FAF0;
extern s8 D_8008FAF1;
extern u16 D_8008FAF2;
extern u8 D_8008FAF4;
extern u16 D_8008FAF6;
extern BgmFade D_8008FAF8[16];
extern BgmMapEntry D_80055B40[];
extern u8 D_80055CF8[];
extern u8 D_80055CF0[];
extern s8 D_80060CB0;

void func_80029198(s32 slot, s32 seqNo);
s32 func_80029224(s32 slot);
void func_800292DC(s32 slot);
s32 func_80029328(s32 slot);
void func_80029A88(s32 arg0, s32 arg1, s32 arg2);
s32 func_8002A458(s32 vol);
void func_8002A900(void);

void func_8002A4F0(void) {
    s32 i;
    BgmFade* p;

    D_8008FAF2 = 0;
    D_8008FAF6 = 0;
    D_8008FAF0 = D_8008FAF1 = -1;
    D_8008FAF4 = 0xFF;
    i = 16;
    p = D_8008FAF8;
    do {
        p->unk0 = 0;
        p++;
    } while (--i);
}

void func_8002A558(void) {
    BgmFade* var_s0;
    s32 i;

    if ((D_8008FAF2 & 1) != 0) {
        if (D_8008FAF6 == 0) {
            if (D_8008FAF0 != -1) {
                D_8008FAF2 = D_8008FAF2 | 2;
            } else {
                D_8008FAF2 = D_8008FAF2 | 4;
            }
            D_8008FAF2 = D_8008FAF2 & ~0x1;
        } else {
            D_8008FAF6--;
        }
    }
    if (D_8008FAF2 & 2) {
        D_8008FAF2 = D_8008FAF2 & 0xFFFD;
        D_8008FAF2 = D_8008FAF2 | 4;
        func_800292DC(0);
    } else if ((D_8008FAF2 & 4) && !(func_80029328(0))) {
        D_8008FAF2 &= ~0x4;
        D_8008FAF0 = D_8008FAF1;
        if (D_8008FAF0 != -1) {
            func_80029198(0, D_8008FAF0);
            func_8002A900();
            func_80029224(0);
        }
    }

    i = 16;
    var_s0 = &D_8008FAF8[0];

    for (i; i > 0; i--) {
        if (var_s0->unk0) {
            if (!--var_s0->unk0) {
                func_80029A88(var_s0->unk1, var_s0->unk2, 64);
            }
        }
        var_s0++;
    }
}

void func_8002A6B8(s8 bgm) {
    if (bgm != D_8008FAF0) {
        D_8008FAF1 = bgm;
        D_8008FAF2 |= 1;
    }
}

void func_8002A6F4(s8 bgm, u16 delay) {
    if (bgm != D_8008FAF0) {
        D_8008FAF1 = bgm;
        D_8008FAF2 |= 1;
        D_8008FAF6 = delay;
    }
}

void func_8002A744(s32 arg0, s32 arg1, u16 delay) {
    BgmMapEntry* entry = D_80055B40;
    s32 i;
    s8 bgm;

    for (i = 0x48; i != 0; i--, entry++) {
        if (arg0 == entry->unk0 && (arg1 == entry->unk2 || entry->unk2 == -1)) {
            break;
        }
    }
    if (i != 0) {
        bgm = entry->unk4;
        if (bgm != D_8008FAF0) {
            D_8008FAF1 = bgm;
            D_8008FAF2 |= 1;
            D_8008FAF6 = delay;
        }
    }
}

void func_8002A7C8(u8 arg0, s8 arg1, u8 arg2) {
    s32 var_v0;
    s32 temp_t2;
    BgmFade* var_v1;

    temp_t2 = (u32) ((D_80055CF8)[arg1] * (arg2) * D_8008FAF4) / 65536;
    if (arg0 == 0) {
        func_80029A88(arg1, temp_t2, 0x40);
    } else {
        var_v0 = 0xF;
        var_v1 = D_8008FAF8;

        while (var_v0 != 0 && var_v1->unk0 != 0) {
            var_v0--;
            var_v1++;
        }

        var_v1->unk0 = arg0;
        var_v1->unk1 = arg1;
        var_v1->unk2 = temp_t2;
    }
}

void func_8002A890(s8 arg0, u8 arg1) {
    u32 result = D_80055CF8[arg0] * arg1 * D_8008FAF4;
    result >>= 16;
    if (result != 0) {
        func_80029A88(arg0, result, 0x40);
    }
}

void func_8002A900(void) {
    func_8002A458(*(&D_80055CF0[0] + D_80060CB0));
}
