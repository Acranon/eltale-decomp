#include "common.h"

/*
 * Controller Pak save/load menu: file discovery, UI states, and game-state
 * capture and restoration.
 * Folder: src/game/save/
 */

typedef struct {
    u8 b[0x20];
} Bytes20;

typedef struct {
    u8 b[0x10];
} Bytes10;

typedef struct {
    u8 b[0x97];
} Bytes97;

typedef struct {
    u8 b[1];
} Bytes1;

typedef struct {
    /* 0x00 */ Bytes20 unk0;
    /* 0x20 */ Bytes10 unk20;
    /* 0x30 */ Bytes97 unk30;
    /* 0xC7 */ Bytes1 unkC7;
} Unk80090228; /* size = 0xC8 */

#ifdef NON_MATCHING
/* the fields SaveMenu_UpdateSlotList reads (same size and alignment as the retail-build view) */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ s32 unkC[6];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ s32 unk28[4];
} Unk8007A9D0; /* size = 0x38 */

typedef struct {
    u8 b[14];
} Bytes14;
#else
typedef struct {
    s32 unk0[14];
} Unk8007A9D0; /* size = 0x38 */
#endif

typedef struct {
    /* 0x00 */ Unk8007A9D0 unk0;
    /* 0x38 */ u16 unk38;
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ s8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ u16 unk64;
} Unk8008FBA8; /* size = 0x68 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2[16];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 unk13;
} Unk80092E48; /* size = 0x14 */

typedef struct {
    s8 unk0;
    s8 unk1;
} Unk8008FB80;

/* .bss 8008FB70..80090450 */
u16 D_8008FB70;
u8 D_8008FB72;
u8 D_8008FB73;
s32 D_8008FB74;
u8 D_8008FB78;
s8 D_8008FB79;
s8 D_8008FB7A;
#ifdef NON_MATCHING
u8 D_8008FB7B; /* SaveMenu_UpdateSlotList reads it with lbu */
#else
s8 D_8008FB7B;
#endif
u8 D_8008FB7C;
Unk8008FB80 D_8008FB80[17];
Unk8008FBA8 D_8008FBA8[16];
Unk80090228 D_80090228;
Unk8008FBA8 D_800902F0; /* Pak_ReadFile reads 0x80 bytes into it */
u8 D_80090358[0x18];    /* the rest of that 0x80-byte buffer: unreferenced */
u8 D_80090370[0xE0];

extern s32 D_8004DCA0;
extern s8 D_80060CB0;
extern s8 D_800616B0;
extern u16 D_8007A9AC;
extern u16 D_8007A9AE;
extern u16 D_8007A9B0;
extern Unk8007A9D0 D_8007A9D0;
extern u8 D_8007C13C[];
extern s32 D_800842BC;
extern s32 D_800842C0;
extern s32 D_800842D0;
extern s32 D_800842D4;
extern s32 D_800842D8;
extern s32 D_800842DC;
extern s32 D_800842E0;
extern s32 D_800842E4;
extern u16 D_80084990;
extern u16 D_80084992;
extern u8 D_80085988[];
extern u8 D_80085A98[];
extern u8 D_8008C9B8[];
extern Unk80092E48 D_80092E48[];
extern Gfx D_80061770[];
extern s16 D_8007A170;
extern Gfx *D_8007A184;
extern u16 D_8008FB3E;
extern s16 D_8006C90C[][4];
extern u8 *D_8006C8F8[];
extern u8 D_8008FB81[];
extern u8 D_80090248[];
extern u8 D_80090258[];
extern u8 D_800902EF[];
extern s8 D_80092C80;

void SaveMenu_DrawOperationPanel(void);
void SaveMenu_CheckControllerPak(void);
void SaveMenu_UpdateDialog(void);
void SaveMenu_UpdateSlotList(s32);
void SaveMenu_UpdateDelay(void);
void SaveMenu_DeleteSelectedFile(void);
void SaveMenu_LoadSelectedFile(void);
void SaveMenu_SaveSelectedFile(void);
void SaveMenu_RepairPak(void);
void SaveMenu_DrawBackground(void);
void SaveMenu_CaptureGameState(s32);
void SaveMenu_RestoreGameState(s32);
void func_8002DECC(s32, s32, s32, s32, s32);
void Text_DrawEncodedString(s32, s32, u8 *);
void SaveMenu_SetTextDrawState(void);
s8 Pak_AllocateGameFile(s32, u8);
u8 Pak_DeleteGameFile(s32, u8);
s32 Pak_WriteFile(s32, s32, s32, s32, void *);
s32 Pak_ReadFile(s32, s32, s32, s32, u8 *);
s32 Pak_TryRepair(s32, s32);
s32 Pak_ClassifyError(s32);
void func_8003D8EC(const char *, ...);
extern OSMesgQueue D_80092C90;
extern OSPfs D_80092CA8[4];
s32 func_8003D0F0(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D554(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D6B0(OSMesgQueue *, OSPfs *, s32);
s32 Pak_ScanGameFiles(s32);
void SaveMenu_RefreshFileList(void);
extern s16 D_8006C9FC[][4];
extern u8 *D_8006C934[];
extern u8 *D_8006C998[];
extern s16 D_8006CAC4[][2];
extern s8 D_80092C82;
extern u16 D_80092C86;
void func_8002A7C8(s32, s32, s32);

#ifdef NON_MATCHING
extern u8 *D_8006CC28[];
extern s8 D_80060D64[];
extern s32 D_8008FB44;
void func_8002EED8(s32, s32, s32, u32, s32);
void func_8002F2E4(s32, s32, s32, u32, s32);
void func_8002F6D8(s32, s32, s32, u32);
#endif

void SaveMenu_Init(s32 arg0) {
    D_8007A170 = 2;
    D_8008FB3E = D_8008FB3E | arg0 | 0x4000;
    D_8008FB70 = 0x1000;
    D_8008FB78 = 0xFF;
    D_8008FB7A = 0;
    D_8008FB79 = 0;
    D_8008FB72 = 0;
    D_8008FB7B = 0;
    D_8008FB7C = 0;
}

void SaveMenu_Update(void) {
    SaveMenu_DrawBackground();
    if (!(D_8008FB70 & 0x4000)) {
        if (D_8008FB70 & 0x2000) {
            SaveMenu_CheckControllerPak();
            D_8008FB70 |= 0x4000;
            D_8008FB70 &= ~0x2000;
            D_8008FB7C = 0;
        } else {
            D_8008FB70 |= 0x2000;
            D_8008FB73 = 0;
        }
    }
    if (D_8008FB70 & 0x4000) {
        switch (D_8008FB70 & 7) {
            case 5:
                SaveMenu_UpdateDialog();
                break;
            case 0:
                SaveMenu_UpdateSlotList(0);
                break;
            case 4:
                SaveMenu_DeleteSelectedFile();
                break;
            case 2:
                SaveMenu_LoadSelectedFile();
                break;
            case 3:
                SaveMenu_SaveSelectedFile();
                break;
            case 1:
                SaveMenu_RepairPak();
                break;
            case 6:
                SaveMenu_UpdateDelay();
                break;
        }
    }
    if (D_8008FB70 & 0x2000) {
        SaveMenu_DrawOperationPanel();
    }
    if (D_8008FB70 & 0x8000) {
        D_8008FB3E &= 0x7FFF;
    }
}

void SaveMenu_DrawOperationPanel(void) {
    u8 unused[4];
    s16 *r = D_8006C90C[D_8008FB73];
    s16 x = r[0];
    s16 y = r[1];
    s16 w = r[2];
    s16 h = r[3];

    func_8002DECC(0, x, y, w, h);
    func_8002DECC(0x37, x + 3, y + h, w, 3);
    func_8002DECC(0x37, x + w + 1, y + 6, 2, h - 5);
    func_8002DECC(0x37, x - 1, y - 1, w + 2, 1);
    func_8002DECC(0x37, x - 1, y + h, w + 2, 1);
    func_8002DECC(0x37, x - 1, y, 1, h);
    func_8002DECC(0x37, x + w, y, 1, h);
    func_8002DECC(0x38, x + 1, y + 1, w - 3, 1);
    func_8002DECC(0x38, x + 1, y + 2, 1, h - 4);
    func_8002DECC(0x39, x + 1, y + h - 2, w - 2, 1);
    func_8002DECC(0x39, x + w - 2, y + 1, 1, h - 3);
    Text_DrawEncodedString(x + 6, y + 6, D_8006C8F8[D_8008FB73]);
    SaveMenu_SetTextDrawState();
}

void SaveMenu_CheckControllerPak(void) {
    s32 mode = D_8008FB3E & 0xC;
    s32 err;
    Unk80092E48 *p;

    if (D_8008FB70 & 0x1000) {
        err = func_8003D0F0(&D_80092C90, &D_80092CA8[D_80092C80], D_80092C80);
        if (err == 2) {
            err = 0;
        } else if (err == 10) {
            if (func_8003D554(&D_80092C90, &D_80092CA8[D_80092C80], D_80092C80) == 0) {
                err = 1;
            } else if (func_8003D6B0(&D_80092C90, &D_80092CA8[D_80092C80], D_80092C80) == 0) {
                err = 1;
            } else {
                err = 10;
            }
        }
        D_8008FB70 &= ~0x1000;
    }
    if (err == 0) {
        err = Pak_ScanGameFiles(D_80092C80);
    }
    if (err != 0) {
        D_8008FB74 = err;
        if (-Pak_ClassifyError(err) == 1) {
            if (mode == 4) {
                D_8008FB72 = 13;
                D_8008FB79 = 10;
            } else {
                D_8008FB72 = 8;
                D_8008FB79 = 10;
            }
        } else {
            D_8008FB72 = 17;
            D_8008FB79 = 10;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
    } else {
        if (mode == 4) {
            p = &D_80092E48[D_80092C80];
            if (p->unk13 < 2) {
                if (p->unk0 & 0x4000) {
                    D_8008FB72 = 21;
                } else {
                    D_8008FB72 = 20;
                }
                D_8008FB79 = 10;
                D_8008FB70 &= 0xFFF8;
                D_8008FB70 |= 5;
                return;
            }
            if (p->unk0 & 0x2000) {
                if (p->unk0 & 0x4000) {
                    D_8008FB72 = 21;
                    D_8008FB7A = 0;
                    D_8008FB70 &= ~0x20;
                } else {
                    D_8008FB72 = 20;
                }
                D_8008FB79 = 10;
                D_8008FB70 &= 0xFFF8;
                D_8008FB70 |= 5;
                return;
            }
        } else if (D_8008FB7C != 0 && ((p = &D_80092E48[D_80092C80])->unk13 < 2 || p->unk0 & 0x2000)) {
            D_8008FB72 = 24;
            D_8008FB79 = 10;
            SaveMenu_RefreshFileList();
            D_8008FB70 &= 0xFFF8;
            D_8008FB70 |= 5;
            D_8008FB7A = 0;
            D_8008FB70 &= ~0x20;
            return;
        } else if (!(D_80092E48[D_80092C80].unk0 & 0x4000)) {
            if (mode == 0) {
                D_8008FB72 = 9;
                D_8008FB79 = 10;
            } else {
                D_8008FB72 = 10;
                D_8008FB79 = 10;
            }
            D_8008FB70 &= 0xFFF8;
            D_8008FB70 |= 5;
            return;
        }
        SaveMenu_RefreshFileList();
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 0;
        D_8008FB7A = 0;
        D_8008FB70 &= ~0x20;
    }
}

void SaveMenu_UpdateDialog(void) {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u8 *msg;

    if (D_8008FB72 == 4 || D_8008FB72 == 5 || D_8008FB72 == 22 || D_8008FB72 == 23) {
        SaveMenu_UpdateSlotList(1);
    }
    x = D_8006C9FC[D_8008FB72][0];
    y = D_8006C9FC[D_8008FB72][1];
    w = D_8006C9FC[D_8008FB72][2];
    h = D_8006C9FC[D_8008FB72][3];
    if (D_8008FB3E & 4) {
        msg = D_8006C934[D_8008FB72];
    } else {
        msg = D_8006C998[D_8008FB72];
    }
    func_8002DECC(0, x, y, w, h);
    func_8002DECC(0x37, x + 3, y + h, w, 3);
    func_8002DECC(0x37, x + w + 1, y + 6, 2, h - 5);
    func_8002DECC(0x37, x - 1, y - 1, w + 2, 1);
    func_8002DECC(0x37, x - 1, y + h, w + 2, 1);
    func_8002DECC(0x37, x - 1, y, 1, h);
    func_8002DECC(0x37, x + w, y, 1, h);
    func_8002DECC(0x38, x + 1, y + 1, w - 3, 1);
    func_8002DECC(0x38, x + 1, y + 2, 1, h - 4);
    func_8002DECC(0x39, x + 1, y + h - 2, w - 2, 1);
    func_8002DECC(0x39, x + w - 2, y + 1, 1, h - 3);
    Text_DrawEncodedString(x + 6, y + 6, msg);
    SaveMenu_SetTextDrawState();
    if (D_8008FB79 >= 0) {
        D_8008FB79--;
    }
    if (D_8008FB79 < 0 && !(D_8008FB70 & 0x800)) {
        if (D_80092C86 & 0x8000) {
            switch (D_8008FB72) {
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 16:
                case 20:
                    D_8008FB70 |= 0x8000;
                    func_8002A7C8(0, 1, 0xFF);
                    break;
                case 24:
                    D_8008FB70 = 0x1000;
                    break;
            }
        }
        if (D_80092C86 & 0xC000) {
            switch (D_8008FB72) {
                case 19:
                    D_8008FB70 &= ~0x2000;
                    D_8008FB70 &= 0xFFF8;
                    D_8008FB70 &= ~0x4000;
                    D_8008FB70 &= ~0x20;
                    D_8008FB7A = 0;
                    D_8008FB70 |= 0x1000;
                    func_8002A7C8(0, 1, 0xFF);
                    break;
                case 17:
                    D_8008FB70 |= 0x10;
                    D_8008FB70 |= 0x800;
                    D_8008FB78 = 0;
                    D_8008FB79 = 10;
                    func_8002A7C8(0, 1, 0xFF);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 13:
                case 14:
                case 15:
                case 21:
                case 22:
                case 23:
                    D_8008FB70 &= ~0x10;
                    D_8008FB70 |= 0x800;
                    if (D_8008FB72 == 4 || D_8008FB72 == 5 || D_8008FB72 == 6) {
                        D_8008FB78 = 0;
                    } else {
                        D_8008FB78 = 1;
                    }
                    D_8008FB79 = 10;
                    func_8002A7C8(0, 1, 0xFF);
                    break;
            }
        } else {
            switch (D_8008FB72) {
                case 17:
                    D_8008FB70 |= 0x10;
                    D_8008FB70 |= 0x800;
                    D_8008FB78 = 0;
                    D_8008FB79 = 10;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 13:
                case 14:
                case 15:
                case 18:
                case 21:
                case 22:
                case 23:
                    D_8008FB70 &= ~0x10;
                    D_8008FB70 |= 0x800;
                    if (D_8008FB72 == 4 || D_8008FB72 == 5 || D_8008FB72 == 6 || D_8008FB72 == 18) {
                        D_8008FB78 = 0;
                    } else {
                        D_8008FB78 = 1;
                    }
                    D_8008FB79 = 10;
                    break;
            }
        }
    }
    if (D_8008FB70 & 0x800) {
        if (D_8008FB70 & 0x10) {
            x = D_8006C9FC[0][0];
            y = D_8006C9FC[0][1];
            w = D_8006C9FC[0][2];
            h = D_8006C9FC[0][3];
        } else {
            x = D_8006C9FC[2][0];
            y = D_8006C9FC[2][1];
            w = D_8006C9FC[2][2];
            h = D_8006C9FC[2][3];
        }
        func_8002DECC(0, x, y, w, h);
        func_8002DECC(0x37, x + 3, y + h, w, 3);
        func_8002DECC(0x37, x + w + 1, y + 6, 2, h - 5);
        func_8002DECC(0x37, x - 1, y - 1, w + 2, 1);
        func_8002DECC(0x37, x - 1, y + h, w + 2, 1);
        func_8002DECC(0x37, x - 1, y, 1, h);
        func_8002DECC(0x37, x + w, y, 1, h);
        func_8002DECC(0x38, x + 1, y + 1, w - 3, 1);
        func_8002DECC(0x38, x + 1, y + 2, 1, h - 4);
        func_8002DECC(0x39, x + 1, y + h - 2, w - 2, 1);
        func_8002DECC(0x39, x + w - 2, y + 1, 1, h - 3);
        if (D_8008FB70 & 0x10) {
            msg = D_8006C934[1];
            Text_DrawEncodedString(x + 6, y + 6, msg);
            Text_DrawEncodedString(x + 6, y + 19, D_8006C934[0]);
        } else {
            msg = D_8006C934[2];
            Text_DrawEncodedString(x + 6, y + 6, msg);
            Text_DrawEncodedString(x + 6, y + 19, D_8006C934[3]);
        }
        SaveMenu_SetTextDrawState();
        if (D_8008FB79 < 0) {
            if (D_80092C82 < -20 || D_80092C82 > 20) {
                if (!(D_8008FB70 & 8)) {
                    D_8008FB78 ^= 1;
                    D_8008FB70 |= 8;
                    func_8002A7C8(0, 0, 0xFF);
                }
            } else {
                D_8008FB70 &= ~8;
            }
            SaveMenu_SetTextDrawState();
            if (D_8008FB70 & 0x10) {
                func_8002DECC(4, D_8006CAC4[D_8008FB78 + 2][0], D_8006CAC4[D_8008FB78 + 2][1], 12, 12);
            } else {
                func_8002DECC(4, D_8006CAC4[D_8008FB78][0], D_8006CAC4[D_8008FB78][1], 12, 12);
            }
            if (D_80092C86 & 0x8000) {
                if (D_8008FB78 == 0) {
                    func_8002A7C8(0, 1, 0xFF);
                    switch (D_8008FB72) {
                        case 17:
                            D_8008FB72 = 18;
                            D_8008FB79 = 10;
                            break;
                        case 5:
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 |= 4;
                            D_8008FB70 |= 0x2000;
                            D_8008FB73 = 3;
                            break;
                        case 4:
                            D_8008FB70 |= 0x2000;
                            D_8008FB73 = 2;
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 |= 3;
                            break;
                        case 6:
                            D_8008FB70 |= 0x2000;
                            D_8008FB73 = 4;
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 |= 1;
                            break;
                        case 21:
                            SaveMenu_RefreshFileList();
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 |= 0;
                            break;
                        case 14:
                        case 15:
                        case 18:
                        case 22:
                        case 23:
                            D_8008FB70 &= ~0x2000;
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 &= ~0x4000;
                            D_8008FB70 |= 0x1000;
                            break;
                        case 13:
                            D_8008FB70 |= 0x8000;
                            break;
                        case 7:
                            D_8008FB70 |= 0x8000;
                            break;
                    }
                } else {
                    func_8002A7C8(0, 2, 0xFF);
                    switch (D_8008FB72) {
                        case 17:
                            D_8008FB72 = 6;
                            break;
                        case 15:
                        case 18:
                        case 22:
                        case 23:
                            D_8008FB70 |= 0x8000;
                            break;
                        case 13:
                            D_8008FB70 &= ~0x2000;
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 &= ~0x4000;
                            D_8008FB70 |= 0x1000;
                            break;
                        case 14:
                        case 21:
                            D_8008FB72 = 15;
                            D_8008FB79 = 10;
                            break;
                        case 4:
                        case 5:
                        case 7:
                            D_8008FB70 &= 0xFFF8;
                            if (D_8008FB70 & 0x1000) {
                                D_8008FB70 &= ~0x4000;
                                D_8008FB70 |= 0x2000;
                            } else {
                                D_8008FB70 |= 0;
                            }
                            break;
                        case 6:
                            D_8008FB70 &= ~0x2000;
                            D_8008FB70 &= 0xFFF8;
                            D_8008FB70 |= 0x1005;
                            D_8008FB72 = 7;
                            break;
                    }
                }
                D_8008FB70 &= ~0x800;
            } else if (D_80092C86 & 0x4000) {
                switch (D_8008FB72) {
                    case 6:
                    case 7:
                    case 13:
                    case 14:
                    case 15:
                    case 17:
                    case 18:
                    case 21:
                    case 22:
                    case 23:
                        break;
                    default:
                        D_8008FB70 &= ~0x800;
                        D_8008FB79 = 2;
                        D_8008FB70 &= 0xFFF8;
                        D_8008FB70 |= 0;
                        break;
                }
            }
        }
    }
}

/* .data 80061650..80061660: SaveMenu_UpdateSlotList's local message (an initialized u8[14]
 * that IDO copies to the stack); becomes its initializer when the function is C. */
#ifdef NON_MATCHING
Bytes14 D_80061650 = { {
#include "assets/D_80061650.inc.c"
} };
#else
u8 D_80061650[0xE] = {
#include "assets/D_80061650.inc.c"
};
#endif

#ifdef NON_MATCHING
/* stack homes and flag/cursor lifetimes differ (code 0x18 bytes short); code is equivalent */
void SaveMenu_UpdateSlotList(s32 arg0) {
    s32 idx;
    s32 flag;
    s32 secs;
    s32 n;
    s32 pad_x;
    s32 colors[1];
    Bytes14 buf;
    Unk8008FB80 *ptr[1];

    flag = 0;
    buf = D_80061650;
    if (D_8008FB70 & 0x20) {
        if (D_8008FB7A == 0) {
            idx = D_8008FB7A;
            D_8008FB70 &= 0xFFDF;
        } else {
            idx = D_8008FB7A - 1;
        }
    } else {
        idx = D_8008FB7A;
    }
    ptr[0] = &D_8008FB80[idx];
    if (ptr[0]->unk0 != -2) {
        if (ptr[0]->unk1 != -1) {
            if (idx == D_8008FB7A) {
                func_8002EED8(2, 0x6F, 0x36, idx, 0xA);
                func_8002DECC(0x36, 0x53, 0x35, 0x1C, 0xD);
                func_8002DECC(0x19, 0x92, 0x36, 8, 0xA);
                func_8002DECC(0x43, 0xD9, 0x35, 0x1C, 0xE);
                colors[0] = 0xA;
            } else {
                func_8002EED8(2, 0x6F, 0x36, idx, 0x48);
                func_8002DECC(0x45, 0x53, 0x35, 0x1C, 0xD);
                func_8002DECC(0x52, 0x92, 0x36, 8, 0xA);
                func_8002DECC(0x44, 0xD9, 0x35, 0x1C, 0xE);
                colors[0] = 0x48;
            }
            func_8002EED8(2, 0x65, 0x6C, D_8008FBA8[idx].unk0.unk24, 0xA);
            func_8002EED8(2, 0x8A, 0x6C, D_8008FBA8[idx].unk0.unk25, 0xA);
            func_8002EED8(2, 0xAF, 0x6C, D_8008FBA8[idx].unk0.unk26, 0xA);
            func_8002EED8(2, 0xD4, 0x6C, D_8008FBA8[idx].unk0.unk27, 0xA);
            switch (D_8008FBA8[idx].unk3C) {
                case 15:
                    if (D_8008FBA8[idx].unk40 == 5) {
                        n = 0;
                    } else {
                        n = 0x10;
                    }
                    break;
                case 16:
                    if (D_8008FBA8[idx].unk40 == 7) {
                        n = 1;
                    } else {
                        n = 2;
                    }
                    break;
                case 17:
                    n = 4;
                    break;
                case 18:
                    if (D_8008FBA8[idx].unk40 == 6) {
                        n = 3;
                    } else {
                        n = 5;
                    }
                    break;
                case 20:
                    n = 6;
                    break;
                case 22:
                    if (D_8008FBA8[idx].unk40 == 0x16) {
                        n = 7;
                    } else {
                        n = 8;
                    }
                    break;
                case 23:
                    switch (D_8008FBA8[idx].unk40) {
                        case 0:
                            n = 9;
                            break;
                        case 8:
                            n = 0xC;
                            break;
                        case 19:
                            n = 0xA;
                            break;
                        case 22:
                            n = 0xB;
                            break;
                    }
                    break;
                case 25:
                    n = 0xE;
                    break;
                case 26:
                    n = 0xD;
                    break;
                case 30:
                    n = 0xF;
                    break;
            }
            Text_DrawEncodedString(0x51, 0x48, D_8006CC28[n]);
            SaveMenu_SetTextDrawState();
            n = 0;
            secs = D_8008FBA8[idx].unk38;
            while (secs >= 60) {
                secs -= 60;
                n++;
            }
            func_8002EED8(3, 0x7E, 0x36, n, colors[0]);
            func_8002F2E4(2, 0x9A, 0x36, secs, colors[0]);
            func_8002EED8(3, 0xC0, 0x36, D_8008FBA8[idx].unk3A, colors[0]);
            func_8002F6D8(3, 0x70, 0x58, D_8008FBA8[idx].unk0.unk4);
            func_8002F6D8(3, 0xC0, 0x58, D_8008FBA8[idx].unk0.unk8);
        }
    } else {
        flag = 1;
        Text_DrawEncodedString(0x82, 0x33, buf.b);
    }
    SaveMenu_SetTextDrawState();
    idx++;
    ptr[0]++;
    if (ptr[0]->unk0 != -1 && flag == 0) {
        if (ptr[0]->unk0 != -2) {
            if (ptr[0]->unk1 != -1) {
                    if (idx == D_8008FB7A) {
                    func_8002EED8(2, 0x6F, 0x83, idx, 0xA);
                    func_8002DECC(0x36, 0x53, 0x82, 0x1C, 0xD);
                    func_8002DECC(0x19, 0x92, 0x83, 8, 0xA);
                    func_8002DECC(0x43, 0xD9, 0x82, 0x1C, 0xE);
                    colors[0] = 0xA;
                } else {
                    func_8002EED8(2, 0x6F, 0x83, idx, 0x48);
                    func_8002DECC(0x45, 0x53, 0x82, 0x1C, 0xD);
                    func_8002DECC(0x52, 0x92, 0x83, 8, 0xA);
                    func_8002DECC(0x44, 0xD9, 0x82, 0x1C, 0xE);
                    colors[0] = 0x48;
                }
                func_8002EED8(2, 0x65, 0xBA, D_8008FBA8[idx].unk0.unk24, 0xA);
                func_8002EED8(2, 0x8A, 0xBA, D_8008FBA8[idx].unk0.unk25, 0xA);
                func_8002EED8(2, 0xAF, 0xBA, D_8008FBA8[idx].unk0.unk26, 0xA);
                func_8002EED8(2, 0xD4, 0xBA, D_8008FBA8[idx].unk0.unk27, 0xA);
                switch (D_8008FBA8[idx].unk3C) {
                    case 15:
                        if (D_8008FBA8[idx].unk40 == 5) {
                            n = 0;
                        } else {
                            n = 0x10;
                        }
                        break;
                    case 16:
                        if (D_8008FBA8[idx].unk40 == 7) {
                            n = 1;
                        } else {
                            n = 2;
                        }
                        break;
                    case 17:
                        n = 4;
                        break;
                    case 18:
                        if (D_8008FBA8[idx].unk40 == 6) {
                            n = 3;
                        } else {
                            n = 5;
                        }
                        break;
                    case 20:
                        n = 6;
                        break;
                    case 22:
                        if (D_8008FBA8[idx].unk40 == 0x16) {
                            n = 7;
                        } else {
                            n = 8;
                        }
                        break;
                    case 23:
                        switch (D_8008FBA8[idx].unk40) {
                            case 0:
                                n = 9;
                                break;
                            case 8:
                                n = 0xC;
                                break;
                            case 19:
                                n = 0xA;
                                break;
                            case 22:
                                n = 0xB;
                                break;
                        }
                        break;
                    case 25:
                        n = 0xE;
                        break;
                    case 26:
                        n = 0xD;
                        break;
                    case 30:
                        n = 0xF;
                        break;
                }
                Text_DrawEncodedString(0x51, 0x96, D_8006CC28[n]);
                SaveMenu_SetTextDrawState();
                n = 0;
                secs = D_8008FBA8[idx].unk38;
                while (secs >= 60) {
                    secs -= 60;
                    n++;
                }
                func_8002EED8(3, 0x7E, 0x83, n, colors[0]);
                func_8002F2E4(2, 0x9A, 0x83, secs, colors[0]);
                func_8002EED8(3, 0xC0, 0x83, D_8008FBA8[idx].unk3A, colors[0]);
                func_8002F6D8(3, 0x70, 0xA6, D_8008FBA8[idx].unk0.unk4);
                func_8002F6D8(3, 0xC0, 0xA6, D_8008FBA8[idx].unk0.unk8);
            }
        } else {
            Text_DrawEncodedString(0x82, 0x7F, buf.b);
        }
    }
    SaveMenu_SetTextDrawState();
    flag = D_80060D64[(D_8008FB44 >> 2) & 0xF];
    if (D_8008FB7A >= 2) {
        func_8002DECC(5, 0x38, 0x4D, 7, 7);
        func_8002DECC(0x53, 0x36, flag + 0x3F, 0xC, 0x10);
    } else if (D_8008FB7A == 1 && !(D_8008FB70 & 0x20)) {
        func_8002DECC(5, 0x38, 0x4D, 7, 7);
        func_8002DECC(0x53, 0x36, flag + 0x3F, 0xC, 0x10);
    }
    if (ptr[0] < &D_8008FB80[16] && ptr[0][1].unk0 != -1) {
        func_8002DECC(5, 0x38, 0xA4, 7, 7);
        func_8002DECC(0x54, 0x36, 0xAC - flag, 0xE, 0xB);
    }
    if (D_8008FB70 & 0x20) {
        func_8002DECC(1, flag + 0x42, 0x80, 0x10, 0xD);
    } else {
        func_8002DECC(1, flag + 0x42, 0x37, 0x10, 0xD);
    }
    if (arg0 != 1) {
        n = 0;
        if (D_80092C82 < -20) {
            if (D_8008FB7B == 0) {
                func_8002A7C8(0, 0, 0xFF);
                D_8008FB7A++;
                if (D_8008FB80[D_8008FB7A].unk0 == -1) {
                    D_8008FB7A--;
                    n = 1;
                }
                if (!(D_8008FB70 & 0x20) && n == 0) {
                    D_8008FB70 |= 0x20;
                } else if (n == 0) {
                    D_8008FB70 &= 0xFFF8;
                    D_8008FB70 |= 6;
                    D_8008FB79 = 4;
                }
            }
            D_8008FB7B++;
            D_8008FB7B &= 0xF;
        } else if (D_80092C82 > 20) {
            if (D_8008FB7B == 0) {
                func_8002A7C8(0, 0, 0xFF);
                D_8008FB7A--;
                if (D_8008FB7A < 0) {
                    D_8008FB7A = 0;
                    n = 1;
                }
                if (D_8008FB70 & 0x20) {
                    D_8008FB70 &= 0xFFDF;
                } else if (n == 0) {
                    D_8008FB70 &= 0xFFF8;
                    D_8008FB70 |= 6;
                    D_8008FB79 = 4;
                }
            }
            D_8008FB7B++;
            D_8008FB7B &= 0xF;
        } else {
            D_8008FB7B = 0;
        }
        if (D_80092C86 & 0x8000) {
            idx = D_8008FB3E & 0xC;
            func_8002A7C8(0, 1, 0xFF);
            switch (idx) {
                case 0:
                    D_8008FB70 |= 0x2000;
                    D_8008FB73 = 1;
                    D_8008FB70 &= ~7;
                    D_8008FB70 |= 2;
                    break;
                case 8:
                    D_8008FB72 = 5;
                    D_8008FB79 = 10;
                    D_8008FB70 &= ~7;
                    D_8008FB70 |= 5;
                    break;
                case 4:
                    if (D_8008FB80[D_8008FB7A].unk0 == -2) {
                        D_8008FB70 |= 0x2000;
                        D_8008FB73 = 2;
                        D_8008FB70 &= ~7;
                        D_8008FB70 |= 3;
                    } else {
                        D_8008FB72 = 4;
                        D_8008FB79 = 10;
                        D_8008FB70 &= ~7;
                        D_8008FB70 |= 5;
                    }
                    break;
            }
        } else if (D_80092C86 & 0x5000) {
            D_8008FB72 = 7;
            D_8008FB79 = 10;
            D_8008FB70 &= ~7;
            D_8008FB70 |= 5;
            func_8002A7C8(0, 2, 0xFF);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/30600/SaveMenu_UpdateSlotList.s")
#endif

void SaveMenu_UpdateDelay(void) {
    D_8008FB79--;
    if (D_8008FB79 < 0) {
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 0;
    }
}

void SaveMenu_DeleteSelectedFile(void) {
    s32 err = Pak_DeleteGameFile(D_80092C80, D_8008FB81[D_8008FB7A * 2]);

    if (err != 0) {
        D_8008FB74 = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 12;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
    } else {
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        D_8008FB72 = 22;
        D_8008FB79 = 10;
        ((s8 *)D_8008FB81)[D_8008FB7A * 2] = -1;
    }
}

void SaveMenu_LoadSelectedFile(void) {
    s32 err = Pak_ReadFile(D_80092C80, D_8008FB80[D_8008FB7A].unk0, 0x80, 0xE0, D_80090370);

    D_80090228 = *(Unk80090228 *)D_80090370;
    if (err != 0) {
        D_8008FB74 = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 11;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
    } else {
        SaveMenu_RestoreGameState(D_8008FB7A);
        D_8008FB70 |= 0x80;
        D_8008FB70 |= 0x8000;
    }
}

#ifdef NON_MATCHING
/* register-only: index/pointer a3/t0 colouring differs; code is equivalent */
void SaveMenu_SaveSelectedFile(void) {
    s32 err;
    s32 n;
    s32 id;
    s32 i;
    s32 idx;
    Unk8008FB80 *p;
    s32 k;
    s32 cont;

    idx = D_8008FB7A;
    p = &D_8008FB80[idx];

    if (p->unk0 == -2) {
        cont = D_80092C80;
        n = D_80092E48[cont].unk0 & 0xF;
        id = 0xF;
        do {
            i = 0;
            id++;
            do {
                if (id == D_8008FB80[i].unk1) {
                    i = 0x7F;
                    break;
                }
                i++;
            } while (i < n);
            if (i != 0x7F) {
                n = id;
                id = -1;
            }
        } while (id >= 0);
        p->unk1 = n;
        if (idx + 1 < 16) {
            p[1].unk1 = -2;
        }
        err = Pak_AllocateGameFile(cont, n);
        if (err >= 0) {
            idx = D_8008FB7A;
            D_8008FB80[idx].unk0 = err;
        } else {
            idx = D_8008FB7A;
        }
        SaveMenu_CaptureGameState(idx);
    } else {
        SaveMenu_CaptureGameState(idx);
    }
    id = D_8008FB7A;
    err = Pak_WriteFile(D_80092C80, D_8008FB80[id].unk0, 0, 0x80, &D_8008FBA8[id]);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                D_8008FB72 = 13;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 14;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        return;
    }
    err = Pak_WriteFile(D_80092C80, D_8008FB80[D_8008FB7A].unk0, 0x80, 0xE0, &D_80090228);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                D_8008FB72 = 13;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 14;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        return;
    }
    D_8008FB70 &= 0xFFF8;
    D_8008FB70 |= 5;
    D_8008FB70 &= ~0x2000;
    D_8008FB72 = 23;
    D_8008FB79 = 10;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/30600/SaveMenu_SaveSelectedFile.s")
#endif

void SaveMenu_RepairPak(void) {
    s32 err;

    func_8003D8EC("Repair Info %d %d\n", D_8008FB7A, D_8008FB74);
    err = Pak_TryRepair(D_8008FB80[D_8008FB7A].unk0, D_8008FB74);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-Pak_ClassifyError(err)) {
            case 1:
                D_8008FB72 = 8;
                D_8008FB79 = 10;
                break;
            case 3:
                D_8008FB72 = 16;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 &= ~0x4000;
        D_8008FB70 |= 0x1000;
    } else {
        D_8008FB70 &= ~0x2000;
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 &= ~0x4000;
        D_8008FB70 |= 0x1000;
        D_8008FB7C++;
    }
}

void SaveMenu_RefreshFileList(void) {
    Unk8008FB80 *p;
    s32 cont;
    s32 n;
    s32 err = 0;
    s32 i;
    Unk8008FBA8 *e;
    s32 ret;

    for (i = 0; i < 17; i++) {
        D_8008FB80[i].unk0 = -1;
        D_8008FB80[i].unk1 = -1;
    }
    cont = D_80092C80;
    n = 0;
    for (i = 0; i < 16; i++) {
        if (D_80092E48[cont].unk2[i] == 0x7F) {
            continue;
        }
        if (D_80092E48[cont].unk2[i] >= 0) {
            D_8008FB80[n].unk0 = i;
            D_8008FB80[n].unk1 = D_80092E48[cont].unk2[i];
            n++;
        }
    }
    if (D_8008FB3E & 4) {
        if (D_80092E48[cont].unk13 >= 2 && !(D_80092E48[cont].unk0 & 0x2000)) {
            D_8008FB80[n].unk0 = -2;
        }
    }
    D_8008FB7A = 0;
    for (i = 0; i < 16; i++) {
        if (D_8008FB80[i].unk0 >= 0) {
            e = &D_8008FBA8[i];
            ret = Pak_ReadFile(D_80092C80, D_8008FB80[i].unk0, 0, 0x80, (u8 *)&D_800902F0);
            *e = D_800902F0;
            if (ret != 0) {
                D_8008FB74 = err;
                err = -Pak_ClassifyError(err);
                if (err == 1) {
                    D_8008FB72 = 8;
                    D_8008FB79 = 10;
                } else {
                    D_8008FB72 = 17;
                    D_8008FB79 = 10;
                }
                D_8008FB70 &= 0xFFF8;
                D_8008FB70 |= 5;
            } else if (e->unk64 != 0) {
                D_8004DCA0 |= 0x20000;
            }
        }
    }
}

void SaveMenu_SetTextDrawState(void) {
    gSPDisplayList(D_8007A184++, D_80061770);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    D_8008FB3E &= ~0x10;
}

void SaveMenu_DrawBackground(void) {
    func_8002DECC(0, 0x3C, 0x22, 0xC8, 0xAB);
    func_8002DECC(0x37, 0x3F, 0xCE, 0xC8, 3);
    func_8002DECC(0x37, 0x105, 0x28, 2, 0xA9);
    func_8002DECC(0x37, 0x3B, 0x21, 0xCA, 1);
    func_8002DECC(0x37, 0x3B, 0xCD, 0xCA, 1);
    func_8002DECC(0x37, 0x3B, 0x21, 1, 0xAD);
    func_8002DECC(0x37, 0x104, 0x21, 1, 0xAD);
    func_8002DECC(0x38, 0x3D, 0x23, 0xC5, 1);
    func_8002DECC(0x38, 0x3D, 0x23, 1, 0xA8);
    func_8002DECC(0x39, 0x3D, 0xCB, 0xC6, 1);
    func_8002DECC(0x39, 0x102, 0x23, 1, 0xA9);
    func_8002DECC(0x3F, 0x5A, 0x2E, 0x96, 2);
    func_8002DECC(0x3F, 0x5A, 0x44, 0x96, 2);
    func_8002DECC(0x3F, 0x5A, 0x7B, 0x96, 2);
    func_8002DECC(0x3F, 0x5A, 0x91, 0x96, 2);
    func_8002DECC(0x42, 0x5E, 0x67, 0x7C, 0xC);
    func_8002DECC(0x42, 0x5E, 0xB5, 0x7C, 0xC);
    func_8002DECC(0x46, 0x55, 0x58, 0x14, 0xE);
    func_8002DECC(0x47, 0xA2, 0x58, 0x18, 0xE);
    func_8002DECC(0x46, 0x55, 0xA6, 0x14, 0xE);
    func_8002DECC(0x47, 0xA2, 0xA6, 0x18, 0xE);
}

void SaveMenu_CaptureGameState(s32 arg0) {
    Unk8008FBA8 *e = &D_8008FBA8[arg0];
    u8 *d;
    u8 *s;
    s32 n;

    e->unk0 = D_8007A9D0;
    e->unk38 = D_80084992;
    e->unk3A = D_80084990;
    e->unk3C = D_800842BC;
    e->unk40 = D_800842C0;
    e->unk44 = D_800842D0;
    e->unk48 = D_800842D4;
    e->unk4C = D_800842D8;
    e->unk50 = D_800842DC;
    e->unk54 = D_800842E0;
    e->unk58 = D_800842E4;
    e->unk5C = D_8007A9AC;
    e->unk5E = D_8007A9AE;
    e->unk60 = D_8007A9B0;
    e->unk62 = D_800616B0;
    e->unk63 = D_80060CB0;
    if (D_8004DCA0 & 0x20000) {
        e->unk64 = 1;
    } else {
        e->unk64 = 0;
    }
    d = D_80090228.unk0.b;
    for (s = D_80085988, n = sizeof(D_80090228.unk0); n != 0; n--) {
        *d++ = *s++;
    }
    d = D_80090248;
    for (s = D_80085A98, n = sizeof(D_80090228.unk20); n != 0; n--) {
        *d++ = *s++;
    }
    d = D_80090258;
    for (s = D_8008C9B8, n = sizeof(D_80090228.unk30); n != 0; n--) {
        *d++ = *s++;
    }
    d = D_800902EF;
    for (s = D_8007C13C, n = sizeof(D_80090228.unkC7); n != 0; n--) {
        *d++ = *s++;
    }
}

void SaveMenu_RestoreGameState(s32 arg0) {
    Unk8008FBA8 *e = &D_8008FBA8[arg0];
    u8 *d;
    u8 *s;
    s32 n;

    D_8007A9D0 = e->unk0;
    D_80084992 = e->unk38;
    D_80084990 = e->unk3A;
    D_800842BC = e->unk3C;
    D_800842C0 = e->unk40;
    D_800842D0 = e->unk44;
    D_800842D4 = e->unk48;
    D_800842D8 = e->unk4C;
    D_800842DC = e->unk50;
    D_800842E0 = e->unk54;
    D_800842E4 = e->unk58;
    D_8007A9AC = e->unk5C;
    D_8007A9AE = e->unk5E;
    D_8007A9B0 = e->unk60;
    D_800616B0 = e->unk62;
    D_80060CB0 = e->unk63;
    if (e->unk64 != 0) {
        D_8004DCA0 |= 0x20000;
    }
    for (s = D_80090228.unk0.b, d = D_80085988, n = sizeof(D_80090228.unk0); n != 0; n--) {
        *d++ = *s++;
    }
    s = D_80090248;
    for (d = D_80085A98, n = sizeof(D_80090228.unk20); n != 0; n--) {
        *d++ = *s++;
    }
    s = D_80090258;
    for (d = D_8008C9B8, n = sizeof(D_80090228.unk30); n != 0; n--) {
        *d++ = *s++;
    }
    s = D_800902EF;
    for (d = D_8007C13C, n = sizeof(D_80090228.unkC7); n != 0; n--) {
        *d++ = *s++;
    }
}
