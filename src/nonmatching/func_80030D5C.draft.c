/* Unmatched research draft for func_80030D5C. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/30600.unmatched.c
 * Snapshot SHA-256: dd034ae018369ae3d4a07eae226fd5ae74f39d224d09112c64727dc911383974
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80030D5C(s32 arg0) {
    s32 idx;
    s32 flag;
    s32 secs;
    s32 n;
    s32 pad_x;
    s32 colors[1];
    Bytes14 buf;
    Unk8008FB80 *ptr[1];
    volatile s32 pad_y;

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
            func_80035350(0x51, 0x48, D_8006CC28[n]);
            func_800324F4();
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
        func_80035350(0x82, 0x33, buf.b);
    }
    func_800324F4();
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
                func_80035350(0x51, 0x96, D_8006CC28[n]);
                func_800324F4();
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
            func_80035350(0x82, 0x7F, buf.b);
        }
    }
    func_800324F4();
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
