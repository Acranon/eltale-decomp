/* Unmatched research draft for func_8020E108_ovl_intro. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/d1-overlay/func_8020E108_ovl_intro_23words.c
 * Snapshot SHA-256: f30153240cc1b752691108033100c33ff5162d83ae85b6d67f47e7cc7ca54321
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8020E108_ovl_intro(s32 arg0) {
    s32 i;
    IntroRect r;
    s32 k;
    IntroSprite *p;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 changed;
    s32 j;
    s32 unused1;
    s32 unused2;
    SortEnt ents[150];
    SortEnt tmp;

    for (i = 0, p = D_802684E0; i < 150; i++, p++) {
        ents[i].idx = i;
        ents[i].key = p->unk3C;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (ents[j + 1].key < ents[j].key) {
                tmp = ents[j];
                ents[j] = ents[j + 1];
                ents[j + 1] = tmp;
            }
        }
    }
    gDPPipeSync(D_8007A184++);
    GFX_WORDS(0xB900031D, 0x504240);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    for (k = 0; k < 150; k++) {
        idx = ents[k].idx;
        p = &D_802684E0[idx];
        changed = 0;
        fade = 0;
        if (p->unk0.w & 0x80000000) {
        if (arg0 == 1) {
            if (!(p->unk0.w & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0 && (p->unk0.w & 0x800000)) {
            continue;
        }
        flags = p->unk0.w;
        if ((flags & 0x800) && func_8020DAF0_ovl_intro(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && func_8020DDA0_ovl_intro(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && func_8020DF20_ovl_intro(idx, flags)) {
            flags &= ~0x8000;
        }
        r.unk0 = p->unk4;
        r.unk4 = p->unk6;
        r.unk8 = p->unkC;
        r.unkC = p->unkE;
        r.unk10 = p->unk8;
        r.unk14 = p->unkA;
        r.unk18 = p->unk8;
        r.unk1C = p->unkA;
        r.unk20 = 0x400;
        r.unk24 = 0x400;
        r.unk28 = r.unk8 << 5;
        r.unk2C = r.unkC << 5;
        if ((flags & 0x20000000) && func_8020D5EC_ovl_intro(idx, flags, &r)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && func_8020D750_ovl_intro(idx, flags, &r)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade |= 0x10;
            if (func_8020D8E8_ovl_intro(idx, 0)) {
                flags &= ~0x10;
                changed = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (func_8020D8E8_ovl_intro(idx, 1)) {
                flags &= ~0x20;
                changed = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (func_8020D9EC_ovl_intro(idx, 0)) {
                flags &= ~0x40;
                changed = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (func_8020D9EC_ovl_intro(idx, 1)) {
                flags &= ~0x80;
                changed = 1;
            }
        }
        if ((flags & 0x1000) && func_8020E0A0_ovl_intro(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (func_8020E0A0_ovl_intro(idx)) {
                flags &= ~0x10000000;
            }
            p->unk0.w = flags;
            continue;
        }
        if (r.unk0 < D_802684B0 && r.unk4 < D_802684B4 && D_802684B0 + D_802684B8 < r.unk0 + r.unk10 &&
            D_802684B4 + D_802684BC < r.unk4 + r.unk14) {
            p->unk0.w = flags;
            continue;
        }
        if (r.unk0 + r.unk10 < D_802684B0 || r.unk4 + r.unk14 < D_802684B4) {
            p->unk0.w = flags;
            continue;
        }
        if (D_802684B0 + D_802684B8 < r.unk0 || D_802684B4 + D_802684BC < r.unk4) {
            p->unk0.w = flags;
            continue;
        }
        {
            if (D_802684B0 + D_802684B8 < r.unk0 + r.unk10) {
                r.unk10 = D_802684B0 + D_802684B8 - r.unk0;
            }
            if (D_802684B4 + D_802684BC < r.unk4 + r.unk14) {
                r.unk14 = D_802684B4 + D_802684BC - r.unk4;
            }
            if (r.unk0 < D_802684B0) {
                r.unk10 = r.unk10 + r.unk0 - D_802684B0;
                r.unk8 = p->unkC;
                r.unk28 = ((D_802684B0 - r.unk0) << 5) + r.unk28;
                r.unk0 = D_802684B0;
            }
            if (p->unk6 < D_802684B4) {
                r.unk14 = r.unk14 + r.unk4 - D_802684B4;
                r.unkC = p->unkE;
                r.unk2C = ((D_802684B4 - r.unk4) << 5) + r.unk2C;
                r.unk4 = D_802684B4;
            }
            if (fade == 0) {
                r.unk34 = 0xFF;
                r.unk30 = 0xFF;
            } else if (fade & 0x30) {
                r.unk34 = 0xFF;
                r.unk30 = p->unk4E;
            } else if (fade & 0xC0) {
                r.unk34 = p->unk4E;
                r.unk30 = 0xFF;
            }
            gDPPipeSync(D_8007A184++);
            if ((flags & 0xF0) || changed) {
                gSPDisplayList(D_8007A184++, D_802122E0_ovl_intro);
                gDPSetEnvColor(D_8007A184++, r.unk34, r.unk34, r.unk34, r.unk30);
            } else {
                gSPDisplayList(D_8007A184++, D_802122C8_ovl_intro);
            }
            gDPPipeSync(D_8007A184++);
            if (p->unk0.w & 0x0C000000) {
                gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
                if (p->unk0.w & 0x08000000) {
                    gDPLoadTLUT_pal256(D_8007A184++, p->unk14);
                    gDPLoadTextureTile(D_8007A184++, p->unk18, G_IM_FMT_CI, G_IM_SIZ_8b, p->unk10, 0, r.unk8, r.unkC,
                                       r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (p->unk0.w & 0x04000000) {
                    gDPLoadTLUT_pal16(D_8007A184++, 0, p->unk14);
                    gDPLoadTextureTile_4b(D_8007A184++, p->unk18, G_IM_FMT_CI, p->unk10, 0, r.unk8, r.unkC,
                                          r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
                gDPLoadTextureTile(D_8007A184++, p->unk18, G_IM_FMT_RGBA, G_IM_SIZ_16b, p->unk10, 0, r.unk8, r.unkC,
                                   r.unk8 + r.unk18 - 1, r.unkC + r.unk1C - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (p->unk0.w & 0x60000) {
                if (p->unk0.w & 0x20000) {
                    r.unk20 = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                        (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, (r.unk8 + r.unk18 - 1) << 5, r.unk2C,
                                        r.unk20, r.unk24);
                }
                if (p->unk0.w & 0x40000) {
                    r.unk24 = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                        (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, r.unk28, (r.unkC + r.unk1C - 1) << 5,
                                        r.unk20, r.unk24);
                }
            } else {
                gSPTextureRectangle(D_8007A184++, r.unk0 << 2, r.unk4 << 2, (r.unk0 + r.unk10) << 2,
                                    (r.unk4 + r.unk14) << 2, G_TX_RENDERTILE, r.unk28, r.unk2C, r.unk20, r.unk24);
            }
            if (changed) {
                p->unk4E = 0xFF;
            }
        }
        p->unk0.w = flags;
        }
    }
}
