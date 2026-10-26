/* Unmatched research draft for func_8002B844. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/2B530.b844-exact-layout-44words.c
 * Snapshot SHA-256: ece11e9e46071d1b2a50e2f985837e506a82530a2929f9b9944700c55c7df9d8
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8002B844(s32 x) {
    s32 wob;
    s32 sel;
    s32 y;
    u8 ids[3] = { 0x28, 0x27, 0x26 };
    static s32 D_8008FB58;

    D_800616B0 = 4 - D_800616B0;
    func_8002DECC(0, x + 0x28, 0x1E, 0xF0, 0x6C);
    func_8002DECC(0x37, x + 0x2B, 0x8B, 0xF0, 3);
    func_8002DECC(0x37, x + 0x119, 0x24, 2, 0x68);
    func_8002DECC(0x37, x + 0x27, 0x1D, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x8A, 0xF2, 1);
    func_8002DECC(0x37, x + 0x27, 0x1E, 1, 0x6D);
    func_8002DECC(0x37, x + 0x118, 0x1E, 1, 0x6D);
    func_8002DECC(0x38, x + 0x29, 0x1F, 0xED, 1);
    func_8002DECC(0x38, x + 0x29, 0x20, 1, 0x68);
    func_8002DECC(0x39, x + 0x29, 0x88, 0xEE, 1);
    func_8002DECC(0x39, x + 0x116, 0x1F, 1, 0x69);
    func_8002DECC(0x3C, x + 0x3A, 0x1E, 0x15, 0x6C);
    func_8002DECC(0x3D, x + 0x5D, 0x56, 0xA7, 2);
    func_8002DECC(0x24, x + 0x8D, 0x3E, 0x54, 7);
    func_8002DECC(0x24, x + 0x8D, 0x6C, 0x54, 7);
    func_8002DECC(0x57, x + 0xE9, 0x3C, 0x1A, 9);
    func_8002DECC(0x56, x + 0x6C, 0x3C, 0x1A, 9);
    func_8002DECC(0x29, x + 0xE9, 0x6B, 0x1A, 9);
    func_8002DECC(0x2A, x + 0x6C, 0x6B, 0x1A, 9);
    func_8002DECC(0x22, x + 0x31, 0x3B, 0x36, 0xC);
    func_8002DECC(0x23, x + 0x35, 0x68, 0x2A, 0xC);
    func_8002DECC(5, x + 0x45, 0x1C, 7, 7);
    func_8002DECC(5, x + 0xF3, 0x1C, 7, 7);
    wob = D_8008FB44;
    wob = (wob >> 2) & 0xF;
    wob = D_80060D64[wob];
    func_8002DECC(6, x + wob + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, x - wob + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x21, x + 0x75, 0x18, 0x56, 0xE);
    func_8002DECC(0x25, x + 0x8E, 0x3F, 0x50, 3);
    func_8002DECC(0x25, x + 0x8E, 0x6D, 0x50, 3);
    func_8002DECC(0x27, x + 0xB3, 0x39, 8, 0xB);
    func_8002DECC(0x27, x + 0xB3, 0x67, 8, 0xB);
    if (D_8008FB3E & 0x200) {
        switch (D_8008FB3E & 0x100) {
            case 0:
                func_8002DECC(ids[D_800615CC[D_80060CB0][1]], D_800615CC[D_80060CB0][0] + x, 0x67, 8, 0xB);
                break;
            case 0x100:
                func_8002DECC(ids[D_800615AC[D_800616B0][1]], D_800615AC[D_800616B0][0] + x, 0x39, 8, 0xB);
                break;
        }
    } else {
        func_8002DECC(ids[D_800615CC[D_80060CB0][1]], D_800615CC[D_80060CB0][0] + x, 0x67, 8, 0xB);
        func_8002DECC(ids[D_800615AC[D_800616B0][1]], D_800615AC[D_800616B0][0] + x, 0x39, 8, 0xB);
    }
    if (D_8008FB3E & 0x2000) {
        D_800616B0 = 4 - D_800616B0;
        return;
    }
    if (!(D_8008FB3E & 0x800)) {
        if (D_80092C81 > 0x14 || (D_80092C84 & 0x10)) {
            D_8008FB3E |= 0x2000;
            D_8008FB38 = 0x1F;
            func_8002A7C8(0, 0, 0xFF);
        } else if (D_80092C81 < -0x14 || (D_80092C84 & 0x2000)) {
            D_8008FB3E |= 0x3000;
            D_8008FB38 = 0x1F;
            func_8002A7C8(0, 0, 0xFF);
        }
        if (D_80092C86 & 0x8000) {
            D_8008FB3E |= 0x820;
            func_8002A7C8(0, 1, 0xFF);
        }
    } else {
        if ((D_80092C86 & 0x8000) && !(D_8008FB3E & 0x200)) {
            D_8008FB3E &= ~0x920;
            func_8002A7C8(0, 2, 0xFF);
            D_800616B0 = 4 - D_800616B0;
            return;
        }
        wob = D_8008FB44;
        wob = (wob >> 1) & 0xF;
        wob = D_80060D64[wob];
        sel = D_8008FB3E & 0x100;
        if (D_8008FB3E & 0x200) {
            switch (sel) {
                case 0:
                    if (D_8008FB58 < D_800615AC[D_800616B0][0]) {
                    } else if (D_800615AC[D_800616B0][0] < D_8008FB58) {
                    } else {
                        D_8008FB3E &= ~0x200;
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615AC[D_800616B0][1]];
                        if (D_80092C81 < 0x14 && D_80092C81 > -0x14) {
                            func_8002DECC(sel, D_8008FB58 + x, 0x39, 8, 0xB);
                        }
                        y = 0x3A;
                        sel = 0;
                    }
                    break;
                case 0x100:
                    if (D_8008FB58 < D_800615CC[D_80060CB0][0]) {
                    } else if (D_800615CC[D_80060CB0][0] < D_8008FB58) {
                    } else {
                        D_8008FB3E &= ~0x200;
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615CC[D_80060CB0][1]];
                        if (D_80092C81 < 0x14 && D_80092C81 > -0x14) {
                            func_8002DECC(sel, D_8008FB58 + x, 0x67, 8, 0xB);
                        }
                        y = 0x65;
                        sel = 0x100;
                    }
                    break;
            }
        }
        if (!(D_8008FB3E & 0x200)) {
            switch (sel) {
                case 0:
                    y = 0x3A;
                    if (D_80092C82 < -0x1E || D_80092C82 > 0x1E) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB3E &= ~0x100;
                            D_8008FB3E |= 0x100;
                            D_8008FB3E |= 0x400;
                            func_8002A7C8(0, 0, 0xFF);
                        }
                    } else if (D_80092C81 < -0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615AC[D_800616B0--][0];
                            if (D_800616B0 < 0) {
                                D_800616B0 = 0;
                            }
                            D_8008FB3E |= 0x600;
                        }
                    } else if (D_80092C81 > 0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615AC[D_800616B0++][0];
                            if (D_800616B0 > 4) {
                                D_800616B0 = 4;
                            }
                            D_8008FB3E |= 0x600;
                        }
                    } else {
                        D_8008FB3E &= ~0x400;
                    }
                    break;
                case 0x100:
                    y = 0x65;
                    if (D_80092C82 < -0x1E || D_80092C82 > 0x1E) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB3E &= ~0x100;
                            D_8008FB3E |= 0;
                            D_8008FB3E |= 0x400;
                            func_8002A7C8(0, 0, 0xFF);
                        }
                    } else if (D_80092C81 < -0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615CC[D_80060CB0--][0];
                            if (D_80060CB0 < 0) {
                                D_80060CB0 = 0;
                            }
                            D_8008FB3E |= 0x400;
                            D_8008FB3E |= 0x200;
                        }
                    } else if (D_80092C81 > 0x14) {
                        if (!(D_8008FB3E & 0x400)) {
                            D_8008FB58 = D_800615CC[D_80060CB0++][0];
                            if (D_80060CB0 > 4) {
                                D_80060CB0 = 4;
                            }
                            D_8008FB3E |= 0x400;
                            D_8008FB3E |= 0x200;
                        }
                    } else {
                        D_8008FB3E &= ~0x400;
                    }
                    break;
            }
        }
        if (D_8008FB3E & 0x200) {
            s32 pos;

            switch (sel) {
                case 0:
                    y = 0x3A;
                    pos = D_8008FB58 + x;
                    if (D_8008FB58 < D_800615AC[D_800616B0][0]) {
                        D_8008FB58++;
                        pos++;
                        sel = ids[D_800615AC[D_800616B0 - 1][1]];
                    } else if (D_800615AC[D_800616B0][0] < D_8008FB58) {
                        D_8008FB58--;
                        pos--;
                        sel = ids[D_800615AC[D_800616B0 + 1][1]];
                    } else {
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615AC[D_800616B0][1]];
                    }
                    func_8002DECC(sel, pos, 0x39, 8, 0xB);
                    break;
                case 0x100:
                    y = 0x65;
                    pos = D_8008FB58 + x;
                    if (D_8008FB58 < D_800615CC[D_80060CB0][0]) {
                        D_8008FB58++;
                        pos++;
                        sel = ids[D_800615CC[D_80060CB0 - 1][1]];
                    } else if (D_800615CC[D_80060CB0][0] < D_8008FB58) {
                        D_8008FB58--;
                        pos--;
                        sel = ids[D_800615CC[D_80060CB0 + 1][1]];
                    } else {
                        D_8008FB3E &= ~0x400;
                        sel = ids[D_800615CC[D_80060CB0][1]];
                    }
                    func_8002DECC(sel, pos, 0x67, 8, 0xB);
                    break;
            }
        }
        func_8002DECC(1, x - wob + 0x1E, y, 0x10, 0xD);
    }
    D_800616B0 = 4 - D_800616B0;
}
