/* Unmatched research draft for func_8002C598. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/2B530.b844-c598.draft.c
 * Snapshot SHA-256: 51131a3a841d98c58a67b22dc9fdafb9ad1a5727aed73b139ea268b03d846706
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8002C598(s32 arg0) {
    static s32 D_800615E0 = -1;
    s32 cx;
    s32 cy;
    s32 x;
    f32 f;
    s32 s;
    s32 n;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;
    s32 ox;
    s32 w;
    s32 h;
    s32 y;
    s32 i;

    s = 0;
    if (D_8008FB50 < 6) {
        if (D_8008FB50 != D_800615E0) {
            func_80028120(D_800614E4[D_8008FB50].romStart, D_800614E4[D_8008FB50].dest,
                          D_800614E4[D_8008FB50].romEnd - D_800614E4[D_8008FB50].romStart);
            D_800615E0 = D_8008FB50;
        }
        w = 0xF4;
        h = 8;
        x = arg0 + 0x27;
        y = 0x1D;
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPPipeSync(D_8007A184++);
            gDPLoadTLUT_pal256(D_8007A184++, D_8006125C[D_8008FB50]);
            for (i = 0; i < 24; i++) {
                if (i == 23) {
                    h = 1;
                }
                gDPLoadTextureTile(D_8007A184++, D_80061274[D_8008FB50][i], G_IM_FMT_CI, G_IM_SIZ_8b, 244, h, 0, 0,
                                   243, h - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                    1 << 10, 1 << 10);
                gDPPipeSync(D_8007A184++);
                y += h;
            }
            func_800324F4();
        }
    } else {
        func_8002DECC(0, arg0 + 0x28, 0x1E, 0xF0, 0xB4);
        func_8002DECC(0x38, arg0 + 0x29, 0x1F, 0xED, 1);
        func_8002DECC(0x38, arg0 + 0x29, 0x20, 1, 0xB1);
        func_8002DECC(0x39, arg0 + 0x29, 0xD0, 0xEE, 1);
        func_8002DECC(0x39, arg0 + 0x117, 0x1F, 1, 0xB2);
        func_8002DECC(0x37, arg0 + 0x2C, 0xD4, 0xF0, 3);
        func_8002DECC(0x37, arg0 + 0x11A, 0x25, 2, 0xB2);
        func_8002DECC(0x37, arg0 + 0x27, 0x1D, 0xF2, 1);
        func_8002DECC(0x37, arg0 + 0x27, 0xD3, 0xF2, 1);
        func_8002DECC(0x37, arg0 + 0x27, 0x1E, 1, 0xB3);
        func_8002DECC(0x37, arg0 + 0x119, 0x1E, 1, 0xB3);
        if (D_8008FB50 != D_800615E0) {
            func_80028120(D_800614E4[D_8008FB50].romStart, D_800614E4[D_8008FB50].dest,
                          D_800614E4[D_8008FB50].romEnd - D_800614E4[D_8008FB50].romStart);
            D_800615E0 = D_8008FB50;
        }
        n = D_8008FB50 - 6;
        w = D_8006158C[n].w;
        h = D_8006158C[n].h1;
        x = D_80061598[n].x + arg0;
        y = D_80061598[n].y;
        if (x < 0) {
            if (x + w < 0) {
                h = 0;
            } else {
                s = -x;
                w -= s;
                s <<= 5;
                x = 0;
            }
        }
        if (x > 320) {
            h = 0;
        } else if (x + w > 320) {
            w = w - (x + w) + 320;
            s = 0;
        }
        if (h != 0) {
            gDPLoadTLUT_pal256(D_8007A184++, D_8006155C[n]);
            D_8008FB3E &= ~0x10;
            gDPLoadTextureTile(D_8007A184++, D_8006156C[n].top, G_IM_FMT_CI, G_IM_SIZ_8b, D_8006158C[n].w, D_8006158C[n].h1, 0, 0,
                               D_8006158C[n].w - 1, D_8006158C[n].h1 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, 0,
                                1 << 10, 1 << 10);
            gDPPipeSync(D_8007A184++);
            gDPLoadTextureTile(D_8007A184++, D_8006156C[n].bottom, G_IM_FMT_CI, G_IM_SIZ_8b, D_8006158C[n].w, D_8006158C[n].h2, 0, 0,
                               D_8006158C[n].w - 1, D_8006158C[n].h2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(D_8007A184++, x << 2, (y + D_8006158C[n].h1) << 2, (x + w) << 2, (y + h + D_8006158C[n].h2) << 2,
                                G_TX_RENDERTILE, s, 0, 1 << 10, 1 << 10);
            func_800324F4();
        }
    }
    func_8002DECC(5, arg0 + 0x45, 0x1C, 7, 7);
    func_8002DECC(5, arg0 + 0xF3, 0x1C, 7, 7);
    n = (D_8008FB44 >> 2) & 0xF;
    n = D_80060D64[n];
    func_8002DECC(6, arg0 + n + 0x36, 0x1A, 0xE, 0xB);
    func_8002DECC(7, arg0 - n + 0xFB, 0x1A, 0xE, 0xB);
    func_8002DECC(0x2B, arg0 + 0x83, 0x18, 0x3A, 0x10);
    if (D_8008FB50 < 6) {
        if (D_8008FB54 < 0) {
            cx = (s32) D_8007AA08.x / D_800614B4[D_8008FB50] + D_800614CC[D_8008FB50];
            cy = (s32) D_8007AA08.z / D_800614B4[D_8008FB50 + 6] + D_800614CC[D_8008FB50 + 6];
        } else {
            cx = D_80061184[D_8008FB50][D_8008FB54].x;
            cy = D_80061184[D_8008FB50][D_8008FB54].y;
        }
        if (D_8008FB44 & 0x20) {
            func_8002DECC(0x2C, arg0 + cx + 0x23, cy + 0xD, 0xC, 0x10);
        }
        if (D_8008FB54 < 0) {
            sx = D_800614B4[D_8008FB50];
            sy = D_800614B4[D_8008FB50 + 6];
            px = D_800614CC[D_8008FB50];
            py = D_800614CC[D_8008FB50 + 6];
            if (D_80060F28 == -1.0f) {
                D_80060F28 = cx;
                D_80060F2C = cy;
            }
            if (D_8008FB3C != 0) {
                f = D_80092C81;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                D_80060F28 += f * 0.08;
                f = D_80092C82;
                if (f > 0.0f) {
                    f -= 5.0f;
                    if (f < 0.0f) {
                        f = 0.0f;
                    }
                } else {
                    f += 5.0f;
                    if (f > 0.0f) {
                        f = 0.0f;
                    }
                }
                D_80060F2C -= f * 0.08;
                if (D_80060F28 < 6.0f) {
                    D_80060F28 = 6.0f;
                } else if (D_80060F28 > 236.0f) {
                    D_80060F28 = 236.0f;
                }
                if (D_80060F2C < 6.0f) {
                    D_80060F2C = 6.0f;
                } else if (D_80060F2C > 178.0f) {
                    D_80060F2C = 178.0f;
                }
            }
            D_8008FB48 = sx * ((s32) D_80060F28 - px);
            D_8008FB4C = sy * ((s32) D_80060F2C - py);
            y = 0;
            h = 5;
            ox = -2;
            if (D_8008FB3C != 0) {
                y = -2;
                h = 6;
            }
            func_8002DECC(0x55, arg0 + D_80060F28 + 39.0f + ox, D_80060F2C + 29.0f - 1.0f, h, 1);
            func_8002DECC(4, arg0 + D_80060F28 + 39.0f - 2.0f, D_80060F2C + 29.0f - 12.0f + y, 0xC, 0xC);
        }
    }
    if (!(D_8008FB3E & 0x2000)) {
        if (D_8008FB3C == 0) {
            if (D_80092C81 > 20 || (D_80092C84 & 0x10)) {
                D_8008FB3E |= 0x2000;
                D_8008FB38 = 31;
                func_8002A7C8(0, 0, 0xFF);
            } else if (D_80092C81 < -20 || (D_80092C84 & 0x2000)) {
                D_8008FB3E |= 0x3000;
                D_8008FB38 = 31;
                func_8002A7C8(0, 0, 0xFF);
            }
        }
        if (D_8008FB50 < 6 && D_8008FB54 < 0) {
            if (D_8008FB3C == 0) {
                D_8008FB5C = D_80060F28;
                D_8008FB60 = D_80060F2C;
            }
            if (D_80092C86 & 0x8000) {
                D_8008FB3C ^= 1;
                D_8008FB3E ^= 0x20;
                func_8002A7C8(0, 0x17, 0xFF);
            } else if ((D_80092C86 & 0x4000) && D_8008FB3C != 0) {
                D_80060F28 = D_8008FB5C;
                D_80060F2C = D_8008FB60;
                func_8002A7C8(0, 0x13, 0xFF);
            }
        }
    }
}
