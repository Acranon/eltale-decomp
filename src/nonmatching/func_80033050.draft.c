/* Unmatched research draft for func_80033050. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/337B0.unmatched.c
 * Snapshot SHA-256: e55ea00712e5e50cfdb80e6a3b365fbaf398022f087263d1addc98ec8bebb2a0
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80033050(void) {
    Gfx *gfx;
    s32 w;
    s32 idx;
    s32 i;
    s32 j;
    s32 m;
    u8 c;
    s32 x;
    s32 y;
    s32 col;
    Bytes4 order;
    s32 tab;
    s32 max;
    s32 flagD8 = 0;
    s32 flagD4 = 0;
    s32 n = 0;
    s32 cnt = 0;

    order.w = D_800616B4;
    gSPDisplayList(D_8007A184++, D_80061770);
    gDPSetBlendColor(D_8007A184++, 0, 0, 0, 1);
    for (j = 0; j < 4; j++) {
        c = D_80090470[j].unk0 & 7;
        switch (c) {
            case 1: order.s.a = j; break;
            case 2: order.s.b = j; break;
            case 3: order.s.c = j; break;
            case 4: order.s.d = j; break;
        }
        if (c != 0) {
            n++;
        }
    }
    for (w = 0; w < 4; w++) {
        gDPPipeSync(D_8007A184++);
        gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
        gDPPipeSync(D_8007A184++);
        gDPLoadTLUT_pal256(D_8007A184++, D_80061850);
        idx = order.v[w];
        if (idx >= 0) {
            if (D_80090470[idx].unk0 & 0x10000000) {
                if (func_8003403C(idx) < 0) {
                    D_80090470[idx].unk0 &= ~0x10000000;
                    D_80090470[idx].unk0 |= 0xA8000000;
                }
            } else if (D_80090470[idx].unk0 & 0x01000000) {
                if (func_8003403C(idx) < 0) {
                    D_80090470[idx].unk0 = 0;
                    for (j = 0; j < 4; j++) {
                        if ((c = D_80090470[j].unk0 & 7) != 0) {
                            c = c + 1;
                            D_80090470[j].unk0 &= ~7;
                            D_80090470[j].unk0 |= c;
                            if (c >= 4) {
                                D_80090470[j].unk0 &= ~0x400000;
                                D_80090470[j].unk0 |= 0x80000000;
                                if (D_80090470[idx].unk0 & 0x80000) {
                                    func_80032BF8(j, 1);
                                    D_80090470[j].unk0 |= 0x01000000;
                                    D_80090470[j].unk0 &= ~0x80000000;
                                }
                            }
                        }
                    }
                    func_80032BF8(idx, 0);
                    D_80090450--;
                    if (n <= 0) {
                        D_8004DCA0 &= ~2;
                    }
                }
            } else {
                if (D_80090470[idx].unk0 & 0x20000000) {
                    func_80034380(idx);
                    if (D_80090470[idx].unk0 & 0x40000000) {
                        gDPPipeSync(D_8007A184++);
                        gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xCC);
                        x = D_80090470[idx].unk4 + 12;
                        y = D_80090470[idx].unk6 + 6;
                        for (i = 0; i < D_80090470[idx].unk38; i++) {
                            func_80035350(x, y, D_80090470[idx].unk3C[i]);
                            y += 13;
                        }
                        if (D_80090470[idx].unk0 & 0x80000000) {
                            if (D_80092C86 & 0xA000) {
                                func_8002A7C8(0, 1, 0xFF);
                                if (D_80090470[idx].unk0 & 0x80000) {
                                    D_8008FB78 = D_80090470[idx].unk15;
                                } else {
                                    D_80090454 = D_80090470[idx].unk15;
                                }
                                func_80032BF8(idx, 1);
                                D_80090470[idx].unk0 |= 0x01000000;
                            } else {
                                if (D_80092C82 > 20) {
                                    if (D_80090470[idx].unk16 == 0) {
                                        D_80090470[idx].unk15--;
                                        D_80090470[idx].unk16 = 1;
                                        func_8002A7C8(0, 0, 0xFF);
                                    }
                                } else if (D_80092C82 < -20) {
                                    if (D_80090470[idx].unk16 == 0) {
                                        D_80090470[idx].unk15++;
                                        D_80090470[idx].unk16 = 1;
                                        func_8002A7C8(0, 0, 0xFF);
                                    }
                                } else {
                                    D_80090470[idx].unk16 = 0;
                                }
                                if (D_80090470[idx].unk15 >= D_80090470[idx].unk38) {
                                    D_80090470[idx].unk15 = 0;
                                } else if (D_80090470[idx].unk15 < 0) {
                                    D_80090470[idx].unk15 = D_80090470[idx].unk38 - 1;
                                }
                            }
                            if (!(D_80090470[idx].unk0 & 0x01000000)) {
                                gDPPipeSync(D_8007A184++);
                                gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
                                x = D_80090470[idx].unk4 - 2;
                                y = D_80090470[idx].unk6 + D_80090470[idx].unk15 * 13 + 2;
                                gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
                                gDPLoadTLUT_pal256(D_8007A184++, D_80061850);
                                func_80034C9C(4, x, y, 12, 12);
                            }
                        }
                    } else if (D_80090470[idx].unk0 & 0x80000000) {
                        if (D_80090470[idx].unk0 & 0x08000000) {
                            if (D_80090470[idx].unk0 & 0x04000000) {
                                flagD8 = 1;
                                m = -1;
                                if (D_80092C86 & 0xA000) {
                                    j = D_80090470[idx].unk12;
                                    tab = 0;
                                    D_80090470[idx].unk9C[j] = D_80090470[idx].unk14;
                                    max = j;
                                    do {
                                        c = D_80090470[idx].unk9C[max];
                                        max--;
                                        if (c >= 0xC0 && c < 0xE0 && !(tab & 1)) {
                                            D_80090470[idx].unk9C[++m] = c;
                                            tab |= 1;
                                        }
                                        if (c >= 0x80 && c < 0xA0 && !(tab & 2)) {
                                            D_80090470[idx].unk9C[++m] = c;
                                            tab |= 2;
                                        }
                                        if (c >= 0xA0 && c < 0xB0 && !(tab & 4)) {
                                            D_80090470[idx].unk9C[++m] = c;
                                            tab |= 4;
                                        }
                                    } while (max >= 0);
                                    do {
                                        D_80090470[idx].unk9C[++m] = D_80090470[idx].unk9C[j++];
                                    } while (D_80090470[idx].unk9C[m] != 0xFF);
                                    D_80090470[idx].unk12 = 1;
                                    D_80090470[idx].unk14 = D_80090470[idx].unk9C[1];
                                    D_80090470[idx].unk9C[1] = 0xFF;
                                    D_80090470[idx].unk0 &= ~0x04000000;
                                    for (j = 0; j < 0x4B0; j++) {
                                        D_80090470[idx].unk54C[j] = 0xFF;
                                    }
                                }
                            } else {
                                if (D_800616B0 != 0) {
                                    if (!(D_80090470[idx].unk0 & 0x100000) && (D_80092C86 & 0xA000)) {
                                        D_80090470[idx].unk0 |= 0x100000;
                                    }
                                } else {
                                    D_80090470[idx].unk0 |= 0x100000;
                                }
                                if (!(D_80090470[idx].unk0 & 0x100000)) {
                                    D_80090470[idx].unk10--;
                                    if (D_80090470[idx].unk10 <= 0) {
                                        D_80090470[idx].unk10 = D_80090470[idx].unkF;
                                        col = D_80090470[idx].unk12++;
                                        D_80090470[idx].unk9C[col++] = D_80090470[idx].unk14;
                                        c = D_80090470[idx].unk14;
                                        D_80090470[idx].unk14 = D_80090470[idx].unk9C[col];
                                        *(D_80090470[idx].unk9C + col) = 0xFF;
                                        switch (c) {
                                            case 0xF2:
                                                D_80090470[idx].unk0 |= 0x400000;
                                                flagD4 = 1;
                                                func_80034B30(idx);
                                                D_80090470[idx].unk0 |= 0x40000;
                                                break;
                                            case 0xF0:
                                                if (cnt != 0) {
                                                    D_80090470[idx].unk0 |= 0x04000000;
                                                }
                                                break;
                                            case 0xFF:
                                                D_80090470[idx].unk0 |= 0x02000000;
                                                D_80090470[idx].unk0 &= ~0x08000000;
                                                func_8003521C();
                                                break;
                                            case 0xE1:
                                            case 0xE2:
                                            case 0xE3:
                                            case 0xE4:
                                            case 0xE5:
                                            case 0xE6:
                                            case 0xE7:
                                            case 0xE8:
                                                col = D_80061660[c & 7] * D_800616B0;
                                                D_80090470[idx].unk10 = D_80090470[idx].unkF = col;
                                            default:
                                                cnt++;
                                                func_8002A7C8(0, 3, 0xFF);
                                                while (c >= 0x80) {
                                                    j = D_80090470[idx].unk12++;
                                                    D_80090470[idx].unk9C[j++] = D_80090470[idx].unk14;
                                                    c = D_80090470[idx].unk14;
                                                    D_80090470[idx].unk14 = D_80090470[idx].unk9C[j];
                                                    *(D_80090470[idx].unk9C + j) = 0xFF;
                                                }
                                                break;
                                        }
                                    }
                                } else {
                                    j = D_80090470[idx].unk12;
                                    D_80090470[idx].unk9C[j] = D_80090470[idx].unk14;
                                    tab = 0;
                                    col = 0;
                                    max = ((D_80090470[idx].unk8 - 20) / 10) * 4;
                                    while (TRUE) {
                                        if (D_80090470[idx].unk9C[j] & 0x80) {
                                            if (D_80090470[idx].unk9C[j] == 0xE0) {
                                                tab += (D_80090470[idx].unk8 - 20) / 10;
                                                if (tab < col) {
                                                    col -= tab;
                                                    col += tab;
                                                } else {
                                                    col = tab;
                                                }
                                                if (col >= max) {
                                                    D_80090470[idx].unk0 |= 0x04000000;
                                                    D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                                    D_80090470[idx].unk9C[j] = 0xFF;
                                                    D_80090470[idx].unk12++;
                                                    break;
                                                }
                                            }
                                        } else {
                                            col++;
                                            if (col >= max) {
                                                D_80090470[idx].unk0 |= 0x04000000;
                                                D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                                D_80090470[idx].unk9C[j] = 0xFF;
                                                D_80090470[idx].unk12++;
                                                break;
                                            } else if (max < col) {
                                                D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                                D_80090470[idx].unk9C[j] = 0xFF;
                                                D_80090470[idx].unk12++;
                                                D_80090470[idx].unk0 |= 0x04000000;
                                                break;
                                            }
                                        }
                                        if (D_80090470[idx].unk9C[j] == 0xF2) {
                                            D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                            D_80090470[idx].unk9C[j] = 0xFF;
                                            D_80090470[idx].unk12++;
                                            break;
                                        } else if (D_80090470[idx].unk9C[j] == 0xF0) {
                                            D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                            D_80090470[idx].unk9C[j] = 0xFF;
                                            D_80090470[idx].unk12++;
                                            D_80090470[idx].unk0 |= 0x04000000;
                                            break;
                                        } else if (D_80090470[idx].unk9C[j] == 0xFF) {
                                            D_80090470[idx].unk14 = D_80090470[idx].unk9C[++j];
                                            D_80090470[idx].unk9C[j] = 0xFF;
                                            D_80090470[idx].unk9C[j + 1] = 0xFF;
                                            break;
                                        }
                                        j++;
                                        D_80090470[idx].unk12++;
                                    }
                                    switch (D_80090470[idx].unk9C[j - 1]) {
                                        case 0xF2:
                                            D_80090470[idx].unk0 |= 0x400000;
                                            func_80034B30(idx);
                                            flagD4 = 1;
                                            D_80090470[idx].unk0 |= 0x40000;
                                            break;
                                        case 0xF0:
                                            D_80090470[idx].unk0 |= 0x04000000;
                                            break;
                                        case 0xFF:
                                            D_80090470[idx].unk0 |= 0x02000000;
                                            D_80090470[idx].unk0 &= ~0x08000000;
                                            func_8003521C();
                                            break;
                                    }
                                    D_80090470[idx].unk0 &= ~0x100000;
                                }
                            }
                            func_8003453C(idx);
                            func_80034274(idx);
                        } else if (D_80090470[idx].unk0 & 0x02000000) {
                            if ((D_80092C86 & 0xA000) || func_8003522C() != 0) {
                                func_80032BF8(idx, 1);
                                D_80090470[idx].unk0 |= 0x01000000;
                            } else {
                                if (D_80090470[idx].unk0 & 0x40000) {
                                    D_80090470[idx].unk0 &= ~0x40000;
                                    func_80032BF8(idx, 1);
                                    D_80090470[idx].unk0 |= 0x01000000;
                                }
                                func_80034274(idx);
                            }
                        }
                    } else {
                        func_80034274(idx);
                    }
                }
                if (flagD8) {
                    func_800348B8(idx);
                }
            }
        }
    }
    if (flagD4) {
        if (D_80090470[idx].unk0 & 0x80000) {
            func_80032D20(-3);
        } else {
            func_80032D20(-1);
        }
    }
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
    gDPPipeSync(D_8007A184++);
    gfx = D_8007A184++; gfx->words.w0 = 0xF9000000; gfx->words.w1 = 1;
    gfx = D_8007A184++; gfx->words.w0 = 0xE7000000; gfx->words.w1 = 0;
}
