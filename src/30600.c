#include "common.h"

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

typedef struct {
    s32 unk0[14];
} Unk8007A9D0; /* size = 0x38 */

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
extern Unk8008FBA8 D_8008FBA8[];
extern Unk8008FBA8 D_800902F0;
extern Unk80092E48 D_80092E48[];
extern Gfx D_80061770[];
extern s16 D_8007A170;
extern Gfx *D_8007A184;
extern u16 D_8008FB3E;
extern u16 D_8008FB70;
extern u8 D_8008FB72;
extern u8 D_8008FB73;
extern s16 D_8006C90C[][4];
extern u8 *D_8006C8F8[];
extern s32 D_8008FB74;
extern u8 D_8008FB78;
extern s8 D_8008FB79;
extern s8 D_8008FB7A;
extern s8 D_8008FB7B;
extern u8 D_8008FB7C;
extern Unk8008FB80 D_8008FB80[17];
extern u8 D_8008FB81[];
extern Unk80090228 D_80090228;
extern u8 D_80090248[];
extern u8 D_80090258[];
extern u8 D_800902EF[];
extern u8 D_80090370[];
extern s8 D_80092C80;

void func_8002FBE0(void);
void func_8002FDB8(void);
void func_800301DC(void);
void func_80030D5C(s32);
void func_80031B28(void);
void func_80031B68(void);
void func_80031C9C(void);
void func_80031E10(void);
void func_80032134(void);
void func_80032558(void);
void func_800327BC(s32);
void func_800329B0(s32);
void func_8002DECC(s32, s32, s32, s32, s32);
void func_80035350(s32, s32, u8 *);
void func_800324F4(void);
s8 func_80035D58(s32, u8);
u8 func_80035E24(s32, u8);
s32 func_80035F0C(s32, s32, s32, s32, void *);
s32 func_80035EA8(s32, s32, s32, s32, u8 *);
s32 func_80035F94(s32, s32);
s32 func_8003609C(s32);
void func_8003D8EC(const char *, ...);
extern OSMesgQueue D_80092C90;
extern OSPfs D_80092CA8[4];
s32 func_8003D0F0(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D554(OSMesgQueue *, OSPfs *, s32);
s32 func_8003D6B0(OSMesgQueue *, OSPfs *, s32);
s32 func_80035A24(s32);
void func_8003226C(void);
extern s16 D_8006C9FC[][4];
extern u8 *D_8006C934[];
extern u8 *D_8006C998[];
extern s16 D_8006CAC4[][2];
extern s8 D_80092C82;
extern u16 D_80092C86;
void func_8002A7C8(s32, s32, s32);

void func_8002FA00(s32 arg0) {
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

void func_8002FA6C(void) {
    func_80032558();
    if (!(D_8008FB70 & 0x4000)) {
        if (D_8008FB70 & 0x2000) {
            func_8002FDB8();
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
                func_800301DC();
                break;
            case 0:
                func_80030D5C(0);
                break;
            case 4:
                func_80031B68();
                break;
            case 2:
                func_80031C9C();
                break;
            case 3:
                func_80031E10();
                break;
            case 1:
                func_80032134();
                break;
            case 6:
                func_80031B28();
                break;
        }
    }
    if (D_8008FB70 & 0x2000) {
        func_8002FBE0();
    }
    if (D_8008FB70 & 0x8000) {
        D_8008FB3E &= 0x7FFF;
    }
}

void func_8002FBE0(void) {
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
    func_80035350(x + 6, y + 6, D_8006C8F8[D_8008FB73]);
    func_800324F4();
}

void func_8002FDB8(void) {
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
        err = func_80035A24(D_80092C80);
    }
    if (err != 0) {
        D_8008FB74 = err;
        if (-func_8003609C(err) == 1) {
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
            func_8003226C();
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
        func_8003226C();
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 0;
        D_8008FB7A = 0;
        D_8008FB70 &= ~0x20;
    }
}

void func_800301DC(void) {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u8 *msg;

    if (D_8008FB72 == 4 || D_8008FB72 == 5 || D_8008FB72 == 22 || D_8008FB72 == 23) {
        func_80030D5C(1);
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
    func_80035350(x + 6, y + 6, msg);
    func_800324F4();
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
            func_80035350(x + 6, y + 6, msg);
            func_80035350(x + 6, y + 19, D_8006C934[0]);
        } else {
            msg = D_8006C934[2];
            func_80035350(x + 6, y + 6, msg);
            func_80035350(x + 6, y + 19, D_8006C934[3]);
        }
        func_800324F4();
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
            func_800324F4();
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
                            func_8003226C();
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

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_80030D5C.s")

void func_80031B28(void) {
    D_8008FB79--;
    if (D_8008FB79 < 0) {
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 0;
    }
}

void func_80031B68(void) {
    s32 err = func_80035E24(D_80092C80, D_8008FB81[D_8008FB7A * 2]);

    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
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

void func_80031C9C(void) {
    s32 err = func_80035EA8(D_80092C80, D_8008FB80[D_8008FB7A].unk0, 0x80, 0xE0, D_80090370);

    D_80090228 = *(Unk80090228 *)D_80090370;
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
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
        func_800329B0(D_8008FB7A);
        D_8008FB70 |= 0x80;
        D_8008FB70 |= 0x8000;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_80031E10.s")

void func_80032134(void) {
    s32 err;

    func_8003D8EC("Repair Info %d %d\n", D_8008FB7A, D_8008FB74);
    err = func_80035F94(D_8008FB80[D_8008FB7A].unk0, D_8008FB74);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/30600/func_8003226C.s")

void func_800324F4(void) {
    gSPDisplayList(D_8007A184++, D_80061770);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    D_8008FB3E &= ~0x10;
}

void func_80032558(void) {
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

void func_800327BC(s32 arg0) {
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

void func_800329B0(s32 arg0) {
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
