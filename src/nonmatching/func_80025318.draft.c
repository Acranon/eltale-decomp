/* Unmatched research draft for func_80025318. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80025318_volatile_n_742words.c
 * Snapshot SHA-256: f1579fdc231611e3e7c7b6a4e32c2b4b807737585f9265de788c9bda6a7a5dc1
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80025318(void) {
    volatile s32 n;
    u8* list;
    s32 count;
    s32 changed;
    u8* slot;
    s32 k;
    s32 x;
    s32 hl;
    u8* p;
    u8* tex;
    u8* fp;
    u8 freeSlots[8];
    s32 y;
    s32 b;

    gSPDisplayList(D_8007A184++, D_803AA7C0);
    func_80026430(0x46, 0x7F, 0xB2, 0x16);
    func_80026430(0x48, 0x44, 0xAD, 0x36);
    gSPDisplayList(D_8007A184++, D_803AA940);
    gSPDisplayList(D_8007A184++, D_803AA998);
    x = D_80092C81;
    if (x > 5) {
        x -= 5;
    } else if (x < -5) {
        x += 5;
    } else {
        x = 0;
    }
    list = &D_8008C9B8[D_8008C19C];
    p = list;
    n = 8;
    while (n != 0 && *p != 0xFF) {
        n--;
        p++;
    }
    count = 8 - n;
    if (count != 0) {
        changed = 0;
        if (x != 0) {
            if (D_8008C1A4 != 0 && (x ^ D_8008C1A4) < 0) {
                D_8008C1A4 = 0;
            } else {
                D_8008C1A4 += x;
                if (D_8008C1A4 > 250) {
                    D_8008C1A4 = 0;
                    changed++;
                    if (++D_8008C1A0 >= count) {
                        D_8008C1A0 = count - 1;
                        if (D_8008C19C < 0x96 - count) {
                            D_8008C19C++;
                            if (D_8008C9B8[D_8008C19C + count - 1] == 0xFF) {
                                D_8008C19C--;
                                changed--;
                            }
                        }
                    }
                } else if (D_8008C1A4 < -250) {
                    D_8008C1A4 = 0;
                    changed++;
                    if (--D_8008C1A0 < 0) {
                        D_8008C1A0 = 0;
                        if (D_8008C19C > 0) {
                            D_8008C19C--;
                        } else {
                            changed--;
                        }
                    }
                }
                if (changed) {
                    func_8002A7C8(0, 3, 0xFF);
                }
            }
            list = &D_8008C9B8[D_8008C19C];
            p = list;
        } else {
            D_8008C1A4 = 0;
            p = list;
        }
        fp = freeSlots;
        slot = D_8008C1B0;
        n = 8;
        do {
            k = count;
            while (k != 0 && *slot != *p) {
                k--;
                p++;
            }
            slot++;
            if (k == 0) {
                *fp++ = 8 - n;
                list = &D_8008C9B8[D_8008C19C];
            }
            n--;
            p = list;
        } while (n != 0);
        x = 0x1AC;
        gSPDisplayList(D_8007A184++, D_803AA9F0);
        hl = 0;
        n = count;
        while (n != 0 && *p != 0xFF) {
            k = 8;
            slot = D_8008C1B0;
            while (k != 0 && *p != *slot) {
                k--;
                slot++;
            }
            if (k == 0) {
                k = *--fp;
                D_8008C1B0[k] = *p;
                tex = ((u8 (*)[0x100])D_8008C1B8)[k];
                func_80028120(&D_D384B0[(*p << 8) + 0x400], tex, 0x100);
            } else {
                tex = ((u8 (*)[0x100])D_8008C1B8)[8 - k];
            }
            gDPLoadTextureBlock(D_8007A184++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            p++;
            if (D_8008C1A0 == count - n) {
                gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, 0xFF);
                gDPLoadTLUT_pal256(D_8007A184++, D_803AC460);
                hl = 1;
            } else if (hl) {
                gDPSetEnvColor(D_8007A184++, 0x7F, 0x7F, 0x7F, 0xFF);
                gDPLoadTLUT_pal256(D_8007A184++, D_803AC660);
                hl = 0;
            }
            gSPTextureRectangle(D_8007A184++, x, 0x20C, x + 0x40, 0x24C, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
            x += 0x44;
            n--;
        }
        x = D_8008C1A0 * 0x44 + 0x1D4;
        y = 0x1F0 - (u16)((sins(D_8004F4C0 & 0x7FFF) >> 13) << 2);
        gSPDisplayList(D_8007A184++, D_803AA828);
        gSPTextureRectangle(D_8007A184++, x, y, x + 0x30, y + 0x30, G_TX_RENDERTILE, 0x9C0, 0, 0x400, 0x400);
        if (count == 8) {
            b = sins((D_8004F4C0 * 2) & 0x7FFF);
            gDPLoadTextureTile(D_8007A184++, D_8039AFB0, G_IM_FMT_CI, G_IM_SIZ_8b, 176, 0, 90, 0, 146, 13, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            if (D_8008C19C != 0) {
                gSPTextureRectangle(D_8007A184++, 0x218, 0x250, 0x234, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(D_8007A184++, (0x77 - (b >> 13)) * 4, 0x248, (0x85 - (b >> 13)) * 4, 0x274,
                                    G_TX_RENDERTILE, 0xEE0, 0, 0x400, 0x400);
            }
            if (D_8008C9B8[D_8008C19C + 8] != 0xFF) {
                gSPTextureRectangle(D_8007A184++, 0x348, 0x250, 0x364, 0x26C, G_TX_RENDERTILE, 0xE00, 0, 0x400, 0x400);
                gSPTextureRectangle(D_8007A184++, ((b >> 13) + 0xDA) * 4, 0x248, ((b >> 13) + 0xE8) * 4, 0x274,
                                    G_TX_RENDERTILE, 0x10A0, 0, 0x400, 0x400);
            }
        }
        gSPDisplayList(D_8007A184++, D_1000388);
        func_80035350(0x77, 0x48, D_803AB288[D_8008C9B8[D_8008C19C + D_8008C1A0]]);
        func_80035350(0x4E, 0x5A, D_803AB2F0[D_8008C9B8[D_8008C19C + D_8008C1A0]]);
        if ((D_80092C86 & 0xA000) && func_800250D8(D_8008C9B8[D_8008C19C + D_8008C1A0])) {
            p = &D_8008C9B8[D_8008C19C + D_8008C1A0];
            for (n = 0x95 - D_8008C19C - D_8008C1A0; n != 0; n--) {
                *p = p[1];
                p++;
            }
            *p = 0xFF;
            D_8004DCA0 &= ~1;
            func_800269B8(6, 4, D_8004F5B4);
            list = &D_8008C9B8[D_8008C19C];
            if (list[D_8008C1A0] == 0xFF) {
                if (D_8008C19C > 0) {
                    D_8008C19C--;
                } else if (D_8008C1A0 > 0) {
                    D_8008C1A0--;
                }
            } else if (list[7] == 0xFF && D_8008C19C > 0) {
                D_8008C19C--;
            }
        }
        D_8004F4C0 += 0x300;
    }
}
