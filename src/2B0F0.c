#include "common.h"

/*
 * Music and sound requests: BGM change with delay (per map/submap table), the BGM volume
 * option, and sound-effect playback with per-sound volume and delayed triggers.
 * Folder: src/game/audio/   (proposed for round 4)
 */

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

/* .bss 8008FAF0..8008FB30 */
s8 D_8008FAF0;
s8 D_8008FAF1;
u16 D_8008FAF2; /* bit 0 change requested (after the delay), 1 stop the current sequence, 2 wait for the stop, then play the next */
u8 D_8008FAF4;
u16 D_8008FAF6;
BgmFade D_8008FAF8[16];

/* This file's .data, 80055B40..80055D40. */
BgmMapEntry D_80055B40[72] = {
    { 0, 2, 33 }, { 0, 3, 33 }, { 0, 4, 33 }, { 11, 4, -1 }, { 11, 3, -1 }, { 11, 5, -1 },
    { 11, 7, -1 }, { 11, 6, -1 }, { 0, -1, 2 }, { 1, -1, 25 }, { 2, -1, 21 }, { 3, -1, 21 },
    { 4, -1, 34 }, { 5, -1, 21 }, { 6, -1, 37 }, { 7, -1, 21 }, { 8, -1, 36 }, { 9, -1, 22 },
    { 10, -1, 5 }, { 11, -1, 39 }, { 12, -1, 26 }, { 14, 13, 33 }, { 15, 13, 33 }, { 22, 0, 12 },
    { 22, 1, 12 }, { 22, 24, 33 }, { 22, 25, 33 }, { 23, 0, 7 }, { 23, 1, 7 }, { 23, 2, 7 },
    { 23, 3, 7 }, { 23, 4, 7 }, { 23, 5, 7 }, { 23, 19, 7 }, { 23, 20, 7 }, { 23, 21, 7 },
    { 25, 6, 33 }, { 25, 7, 33 }, { 13, -1, 15 }, { 14, -1, 3 }, { 15, -1, 7 }, { 16, -1, 7 },
    { 17, -1, 7 }, { 18, -1, 7 }, { 19, -1, 7 }, { 20, -1, 7 }, { 21, -1, 8 }, { 22, -1, 7 },
    { 23, -1, 39 }, { 24, -1, 5 }, { 25, -1, 6 }, { 26, 2, 9 }, { 26, 3, 11 }, { 26, 4, 11 },
    { 30, 6, -1 }, { 31, 1, 35 }, { 31, 2, 24 }, { 32, 1, 12 }, { 32, 2, 12 }, { 33, 1, 12 },
    { 33, 2, 12 }, { 34, 1, 38 }, { 26, -1, 23 }, { 27, -1, 10 }, { 28, -1, 1 }, { 29, -1, 18 },
    { 30, -1, 31 }, { 31, -1, 12 }, { 32, -1, 24 }, { 33, -1, 24 }, { 34, -1, 33 }, { 35, -1, 14 },
};
u8 D_80055CF0[8] = {
    0, 0x78, 0xB4, 0xDC, 0xFF, 0, 0, 0,
};
u8 D_80055CF8[72] = {
    0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xC8, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA,
    0xFA, 0xFA, 0xFA, 0x96, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFF, 0xFA, 0xFF, 0xFA, 0xFA, 0xFF, 0xFA,
    0xFF, 0xB4, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xC8, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA,
    0xC8, 0xFA, 0xFA, 0xFA, 0xFA, 0xB4, 0xFA, 0xFA, 0xFA, 0xC8, 0xFA, 0xC8, 0xC8, 0xC8, 0xC8, 0xFA,
    0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0, 0,
};
extern s8 D_80060CB0;

void Audio_LoadSeq(s32 slot, s32 seqNo);
s32 Audio_PlaySeq(s32 slot);
void Audio_StopSeq(s32 slot);
s32 Audio_GetSeqState(s32 slot);
void Sfx_Enqueue(s32 arg0, s32 arg1, s32 arg2);
s32 Audio_SetSeqVolume(s32 vol);
void Bgm_ApplyVolumeOption(void);

void Bgm_Init(void) {
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

void Bgm_Update(void) {
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
        Audio_StopSeq(0);
    } else if ((D_8008FAF2 & 4) && !(Audio_GetSeqState(0))) {
        D_8008FAF2 &= ~0x4;
        D_8008FAF0 = D_8008FAF1;
        if (D_8008FAF0 != -1) {
            Audio_LoadSeq(0, D_8008FAF0);
            Bgm_ApplyVolumeOption();
            Audio_PlaySeq(0);
        }
    }

    i = 16;
    var_s0 = &D_8008FAF8[0];

    for (i; i > 0; i--) {
        if (var_s0->unk0) {
            if (!--var_s0->unk0) {
                Sfx_Enqueue(var_s0->unk1, var_s0->unk2, 64);
            }
        }
        var_s0++;
    }
}

void Bgm_Play(s8 bgm) {
    if (bgm != D_8008FAF0) {
        D_8008FAF1 = bgm;
        D_8008FAF2 |= 1;
    }
}

void Bgm_PlayDelayed(s8 bgm, u16 delay) {
    if (bgm != D_8008FAF0) {
        D_8008FAF1 = bgm;
        D_8008FAF2 |= 1;
        D_8008FAF6 = delay;
    }
}

void Bgm_PlayForMap(s32 arg0, s32 arg1, u16 delay) {
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

void Sfx_Play(u8 arg0, s8 arg1, u8 arg2) {
    s32 var_v0;
    s32 temp_t2;
    BgmFade* var_v1;

    temp_t2 = (u32) ((D_80055CF8)[arg1] * (arg2) * D_8008FAF4) / 65536;
    if (arg0 == 0) {
        Sfx_Enqueue(arg1, temp_t2, 0x40);
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

void Sfx_PlayIfAudible(s8 arg0, u8 arg1) {
    u32 result = D_80055CF8[arg0] * arg1 * D_8008FAF4;
    result >>= 16;
    if (result != 0) {
        Sfx_Enqueue(arg0, result, 0x40);
    }
}

void Bgm_ApplyVolumeOption(void) {
    Audio_SetSeqVolume(*(&D_80055CF0[0] + D_80060CB0));
}
