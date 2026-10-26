/* Unmatched research draft for func_8020D98C_ovl_ending. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/d1-overlay/func_8020D98C_ovl_ending_25words.c
 * Snapshot SHA-256: 866f6f94c888dd7c8ec9819fb994083132383c5511a7f4d526fad6c1908e4a7e
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8020D98C_ovl_ending(s32 arg0) {
    s32 i;
    UnkArg_8020CE70 rect;
    UnkSortEntry_8020D98C* entry;
    UnkStruct_8022BB38* obj;
    s32 idx;
    s32 flags;
    s32 fade;
    s32 fadeDone;
    s32 j;
    s32 unused1;
    s32 unused2;
    UnkSortEntry_8020D98C list[150];
    UnkSortEntry_8020D98C tmp;
    s32 unused3;
    s32 unused4;

    for (i = 0; i < 150; i++) {
        list[i].idx = i;
        list[i].key = D_8022BB38[i].unk3C;
    }
    for (i = 0; i < 149; i++) {
        for (j = 0; j < 149 - i; j++) {
            if (list[j + 1].key < list[j].key) {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
    gDPSetRenderMode(D_8007A184++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(D_8007A184++, G_TF_POINT);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    for (entry = list; entry != &list[150]; entry++) {
        idx = entry->idx;
        obj = &D_8022BB38[idx];
        fadeDone = 0;
        fade = 0;
        if (!(obj->unk0 & 0x80000000)) {
            continue;
        }
        if (arg0 == 1) {
            if (!(obj->unk0 & 0x800000)) {
                continue;
            }
        } else if (arg0 == 0) {
            if (obj->unk0 & 0x800000) {
                continue;
            }
        }
        flags = obj->unk0;
        if ((flags & 0x800) && func_8020D374_ovl_ending(idx, flags)) {
            flags &= ~0x800;
        }
        if ((flags & 0x4000) && func_8020D624_ovl_ending(idx, flags)) {
            flags &= ~0x4000;
        }
        if ((flags & 0x8000) && func_8020D7A4_ovl_ending(idx, flags)) {
            flags &= ~0x8000;
        }
        rect.unk0 = obj->unk4;
        rect.unk4 = obj->unk6;
        rect.s = obj->unkC;
        rect.t = obj->unkE;
        rect.unk10 = obj->unk8;
        rect.unk14 = obj->unkA;
        rect.sw = obj->unk8;
        rect.th = obj->unkA;
        rect.dsdx = 0x400;
        rect.dtdy = 0x400;
        rect.sfrac = rect.s << 5;
        rect.tfrac = rect.t << 5;
        if ((flags & 0x20000000) && func_8020CE70_ovl_ending(idx, flags, &rect)) {
            flags &= ~0x20000100;
        }
        if ((flags & 0x40000000) && func_8020CFD4_ovl_ending(idx, flags, &rect)) {
            flags &= ~0x40000400;
        }
        if (flags & 0x10) {
            fade = 0x10;
            if (func_8020D16C_ovl_ending(idx, 0)) {
                flags &= ~0x10;
                fadeDone = 1;
            }
        }
        if (flags & 0x20) {
            fade |= 0x20;
            if (func_8020D16C_ovl_ending(idx, 1)) {
                flags &= ~0x20;
                fadeDone = 1;
            }
        }
        if (flags & 0x40) {
            fade |= 0x40;
            if (func_8020D270_ovl_ending(idx, 0)) {
                flags &= ~0x40;
                fadeDone = 1;
            }
        }
        if (flags & 0x80) {
            fade |= 0x80;
            if (func_8020D270_ovl_ending(idx, 1)) {
                flags &= ~0x80;
                fadeDone = 1;
            }
        }
        if ((flags & 0x1000) && func_8020D924_ovl_ending(idx)) {
            flags &= ~0x1000;
        }
        if (flags & 0x10000000) {
            if (func_8020D924_ovl_ending(idx)) {
                flags &= ~0x10000000;
            }
            obj->unk0 = flags;
            continue;
        }
        if ((rect.unk0 < D_8022BB10) && (rect.unk4 < D_8022BB14) && (D_8022BB10 + D_8022BB18 < rect.unk0 + rect.unk10) &&
            (D_8022BB14 + D_8022BB1C < rect.unk4 + rect.unk14)) {
            obj->unk0 = flags;
            continue;
        }
        if ((rect.unk0 + rect.unk10 < D_8022BB10) || (rect.unk4 + rect.unk14 < D_8022BB14)) {
            obj->unk0 = flags;
            continue;
        }
        if ((D_8022BB10 + D_8022BB18 < rect.unk0) || (D_8022BB14 + D_8022BB1C < rect.unk4)) {
            obj->unk0 = flags;
            continue;
        }
        {
            if (D_8022BB10 + D_8022BB18 < rect.unk0 + rect.unk10) {
                rect.unk10 = D_8022BB10 + D_8022BB18 - rect.unk0;
            }
            if (D_8022BB14 + D_8022BB1C < rect.unk4 + rect.unk14) {
                rect.unk14 = D_8022BB14 + D_8022BB1C - rect.unk4;
            }
            if (rect.unk0 < D_8022BB10) {
                rect.unk10 = rect.unk10 + rect.unk0 - D_8022BB10;
                rect.s = obj->unkC;
                rect.sfrac = ((D_8022BB10 - rect.unk0) << 5) + rect.sfrac;
                rect.unk0 = D_8022BB10;
            }
            if (obj->unk6 < D_8022BB14) {
                rect.unk14 = rect.unk14 + rect.unk4 - D_8022BB14;
                rect.t = obj->unkE;
                rect.tfrac = ((D_8022BB14 - rect.unk4) << 5) + rect.tfrac;
                rect.unk4 = D_8022BB14;
            }
            if (fade == 0) {
                rect.prim = 0xFF;
                rect.env = 0xFF;
            } else if (fade & 0x30) {
                rect.prim = 0xFF;
                rect.env = obj->unk4E;
            } else if (fade & 0xC0) {
                rect.prim = obj->unk4E;
                rect.env = 0xFF;
            }
            gDPPipeSync(D_8007A184++);
            if ((flags & 0xF0) || fadeDone) {
                gSPDisplayList(D_8007A184++, D_8020F748_ovl_ending);
                gDPSetEnvColor(D_8007A184++, rect.prim, rect.prim, rect.prim, rect.env);
            } else {
                gSPDisplayList(D_8007A184++, D_8020F718_ovl_ending);
            }
            gDPPipeSync(D_8007A184++);
            if (obj->unk0 & 0x0C000000) {
                if (obj->unk0 & 0x08000000) {
                    gDPLoadTLUT_pal256(D_8007A184++, obj->unk14);
                    gDPLoadTextureTile(D_8007A184++, obj->unk18, G_IM_FMT_CI, G_IM_SIZ_8b, obj->unk10, 0, rect.s, rect.t,
                                       rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                } else if (obj->unk0 & 0x04000000) {
                    gDPLoadTLUT_pal16(D_8007A184++, 0, obj->unk14);
                    gDPLoadTextureTile_4b(D_8007A184++, obj->unk18, G_IM_FMT_CI, obj->unk10, 0, rect.s, rect.t,
                                          rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
                }
            } else {
                gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
                gDPLoadTextureTile(D_8007A184++, obj->unk18, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->unk10, 0, rect.s, rect.t,
                                   rect.s + rect.sw - 1, rect.t + rect.th - 1, 0, 0, 0, 0, 0, 0, 0);
            }
            if (obj->unk0 & 0x60000) {
                if (obj->unk0 & 0x20000) {
                    rect.dsdx = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                        (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, (rect.s + rect.sw - 1) << 5,
                                        rect.tfrac, rect.dsdx, rect.dtdy);
                } else {
                    rect.dtdy = -0x400;
                    GFX_TEXRECT_STEPS(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                        (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, rect.sfrac,
                                        (rect.t + rect.th - 1) << 5, rect.dsdx, rect.dtdy);
                }
            } else {
                gSPTextureRectangle(D_8007A184++, rect.unk0 << 2, rect.unk4 << 2, (rect.unk0 + rect.unk10) << 2,
                                    (rect.unk4 + rect.unk14) << 2, G_TX_RENDERTILE, rect.sfrac, rect.tfrac, rect.dsdx,
                                    rect.dtdy);
            }
            if (fadeDone) {
                obj->unk4E = 0xFF;
            }
        }
        obj->unk0 = flags;
    }
}
