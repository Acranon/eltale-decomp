/* Unmatched research draft for func_8020C6A8_ovl_intro. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/overlay-oct26/c6_2words.full.c
 * Snapshot SHA-256: ff4622b99e946b3188e3e98f355af7eb38d69e2140aa012219085e8801b1a9a7
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_8020C6A8_ovl_intro(void) {
    Unk28* entries;
    AnimFrame* steps;
    u32 listIdx;
    IntroSprite* obj;
    s32 slot;
    s32 dx;
    s32 dy;
    Unk28 *new_var;
    s32 i;
    s32 j;
    s32 flags;
    Gfx *g;
    static s32 D_80276F44_ovl_intro;
    static u8 D_80276F48_ovl_intro[0x12C];
    extern s32 D_80277074_ovl_intro;
    extern u8 D_80277078_ovl_intro;
    if (D_80277074_ovl_intro) {}

    if (D_802684C8_ovl_intro == 0) {
        D_80276F44_ovl_intro = 0;
        D_802684C0_ovl_intro = 0;
        D_80277078_ovl_intro = 0;
        D_80277074_ovl_intro = 0;
        D_802684C8_ovl_intro = 1;
    }
    D_802684C0_ovl_intro++;
    D_80276F44_ovl_intro++;
    D_802684D4_ovl_intro++;
    if ((D_802684D4_ovl_intro >= D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0[D_802684CC_ovl_intro].unk2) &&
        (D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0[D_802684CC_ovl_intro].unk22 == -1) && (D_802684DC_ovl_intro == 0)) {
        do {
            slot = func_8020D504_ovl_intro();
            if (slot != -1) {
            entries = D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk0;
            entries[D_802684CC_ovl_intro].unk20 = 0;
            entries[D_802684CC_ovl_intro].unk22 = slot;
            steps = D_80212810_ovl_intro[entries[D_802684CC_ovl_intro].unk0].unk0;
            func_8020D0F4_ovl_intro(slot, 0x80000000 | entries[D_802684CC_ovl_intro].unk4 | steps[entries[D_802684CC_ovl_intro].unk20].unk0,
                                     entries[D_802684CC_ovl_intro].unk8, entries[D_802684CC_ovl_intro].unkA, entries[D_802684CC_ovl_intro].unk10,
                                     entries[D_802684CC_ovl_intro].unk12, entries[D_802684CC_ovl_intro].unkC, entries[D_802684CC_ovl_intro].unkE,
                                     entries[D_802684CC_ovl_intro].unk14, entries[D_802684CC_ovl_intro].unk16, entries[D_802684CC_ovl_intro].unk18,
                                     entries[D_802684CC_ovl_intro].unk1C, steps[entries[D_802684CC_ovl_intro].unk20].unk8, D_802684C4_ovl_intro);
            D_802684C4_ovl_intro++;
            if (entries[D_802684CC_ovl_intro].unk2 == 0) {
                entries[D_802684CC_ovl_intro].unk24 = D_802684D0_ovl_intro;
            } else {
                D_802684D0_ovl_intro = D_802684CC_ovl_intro;
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0xC800) {
                if (entries[D_802684CC_ovl_intro].unk2 == 0) {
                    dx = entries[D_802684CC_ovl_intro].unk8 - entries[D_802684D0_ovl_intro].unk8;
                    dy = entries[D_802684CC_ovl_intro].unkA - entries[D_802684D0_ovl_intro].unkA;
                } else {
                    dx = 0;
                    dy = 0;
                }
                func_8020DD6C_ovl_intro(slot, steps[entries[D_802684CC_ovl_intro].unk20].unk4 + dx, steps[entries[D_802684CC_ovl_intro].unk20].unk6 + dy);
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0x1000) {
                func_8020E0EC_ovl_intro(slot);
            }
            if (steps[entries[D_802684CC_ovl_intro].unk20].unk0 & 0x60000000) {
                func_8020D8AC_ovl_intro(slot);
            }
            D_802684CC_ovl_intro++;
            if (D_802684CC_ovl_intro >= D_802170E8_ovl_intro[D_802684D8_ovl_intro].unk4) {
                D_802684CC_ovl_intro = 0;
                D_802684DC_ovl_intro = 1;
                D_802684D4_ovl_intro = 0;
                break;
            }
            D_802684D4_ovl_intro = 0;
            } else {
                break;
            }
        } while (entries[D_802684CC_ovl_intro].unk2 == 0);
    }
    if (D_802684C0_ovl_intro == 0x1E00) {
        func_8002A338(0x5A);
    }
    func_8020E108_ovl_intro(1);
    func_8020E108_ovl_intro(0);
    for (i = 0, obj = D_802684E0_ovl_intro; i < 150; i++, obj++) {
        if (i) {
        }
        if (obj->unk0.w & 0x80000000) {
            j = func_8020D078_ovl_intro(i, &listIdx);
            if (j != -1) {
                flags = obj->unk0.w;
                entries = D_802170E8_ovl_intro[listIdx].unk0;
                steps = D_80212810_ovl_intro[entries[j].unk0].unk0;
                if (flags & 0x800000) {
                    flags &= ~0x800000;
                }
                if (!(steps[entries[j].unk20].unk0 & flags)) {
                    if (D_802684D8_ovl_intro) {
                    }
                    new_var = entries;
                    entries[j].unk20++;
                    if (new_var[j].unk20 >= D_80212810_ovl_intro[new_var[j].unk0].unk4) {
                        func_8020D300_ovl_intro(i);
                        entries[j].unk22 = -1;
                    } else {
                        obj->unk0.w &= ~0x800000;
                        obj->unk0.w |= steps[new_var[j].unk20].unk0;
                        obj->unk38 = steps[new_var[j].unk20].unk8;
                        if (steps[new_var[j].unk20].unk0 & 0xC800) {
                            if (new_var[j].unk2 == 0) {
                                dx = new_var[j].unk8 - new_var[new_var[j].unk24].unk8;
                                dy = new_var[j].unkA - new_var[new_var[j].unk24].unkA;
                            } else {
                                dx = 0;
                                dy = 0;
                            }
                            func_8020DD6C_ovl_intro(i, steps[new_var[j].unk20].unk4 + dx, steps[new_var[j].unk20].unk6 + dy);
                        }
                        if (steps[new_var[j].unk20].unk0 & 0x1000) {
                            func_8020E0EC_ovl_intro(i);
                        }
                        if (steps[new_var[j].unk20].unk0 & 0x60000000) {
                            func_8020D8AC_ovl_intro(i);
                        }
                    }
                }
            }
        }
    }
    if (D_80092C86 & 0x1000) {
        D_80277078_ovl_intro = 1;
    }
    if (D_80277078_ovl_intro != 0) {
        D_80277074_ovl_intro += 10;
        if (D_80277074_ovl_intro >= 0x100) {
            D_80277074_ovl_intro = 0xFF;
        }
        g = D_8007A184++; g->words.w0 = _SHIFTL(G_RDPPIPESYNC, 24, 8); g->words.w1 = 0;
        g = D_8007A184++; g->words.w0 = (_SHIFTL(G_DL, 24, 8) | _SHIFTL(G_DL_PUSH, 16, 8)); g->words.w1 = (u32)D_802122E0_ovl_intro;
        g = D_8007A184++; g->words.w0 = (_SHIFTL(G_SETOTHERMODE_H,24,8) | _SHIFTL(G_MDSFT_TEXTLUT,8,8) | _SHIFTL(2,0,8)); g->words.w1 = G_TT_RGBA16;
        gDPSetRenderMode(D_8007A184++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetEnvColor(D_8007A184++, 255, 255, 255, D_80277074_ovl_intro);
        gDPLoadTLUT_pal256(D_8007A184++, D_80217A80_ovl_intro);
        for (i = 0; i < 40; i++) {
            gDPLoadTextureTile(D_8007A184++, D_80217C80_ovl_intro, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 6, 0, 0, 319, 5, 0, 0, 0, 0, 0, 0, 0);
            gSPTextureRectangle(D_8007A184++, 0, (i * 6) << 2, 320 << 2, (i * 6 + 6) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        if (D_80277074_ovl_intro >= 0xFF) {
            return 1;
        }
    }
    if ((func_8020D454_ovl_intro() == 0) && (D_802684DC_ovl_intro != 0)) {
        D_802684DC_ovl_intro = 0;
        D_802684D8_ovl_intro++;
        if (D_802684D8_ovl_intro >= D_802170F0_ovl_intro) {
            D_802684D8_ovl_intro = 0;
            return 0;
        }
    }
    return 2;
}
