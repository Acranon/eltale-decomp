/* Unmatched research draft for func_8020E9C8_ovl_ending. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/claude/d2r2/e9c8_statics_757.c
 * Snapshot SHA-256: 05d0d0a397362b07e3c71c451d40eae8675f5c2cfa13280e9b1e5c3e514ef32f
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_8020E9C8_ovl_ending(s32 arg0, s32 arg1) {
    static f32 D_8020F69C_ovl_ending = 32767.0f;
    static s32 D_8020F6A0_ovl_ending = 0;
    static f32 D_8020F6A4_ovl_ending = 0.0f;
    static f32 D_8020F6A8_ovl_ending = 0.0f;
    static u8 D_8020F6AC_ovl_ending = 1;
    static u8 D_8020F6B0_ovl_ending = 0;
    static u8 D_8020F6B4_ovl_ending = 0;
    u32 width;
    f32 alpha;
    f32 delta;
    s32 x;
    s32 y;
    UnkPic_80210800* pic;
    f32 scroll;
    s32 frame;

    if (arg0 == 0) {
        D_8020F69C_ovl_ending = D_8022BAF0_ovl_ending;
        D_8020F6B4_ovl_ending = 0;
        return 0;
    }
    if (D_8020F6B4_ovl_ending == 2) {
        return 1;
    }
    gDPPipeSync(D_8007A184++);
    gDPSetRenderMode(D_8007A184++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPDisplayList(D_8007A184++, D_8020F730_ovl_ending);
    gDPSetTextureLUT(D_8007A184++, G_TT_RGBA16);
    if (D_8020F6A0_ovl_ending == 0x26AC) {
        D_8020F6AC_ovl_ending = 2;
        D_8020F6B0_ovl_ending = 1;
    } else if (D_8020F6A0_ovl_ending == D_8022BAF8_ovl_ending) {
        D_8020F6B0_ovl_ending = 2;
        func_8002A338(0x1E0);
    }

    switch (D_8020F6AC_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 1.0666667f;
            break;
        case 2:
            delta = -0.7111111f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = D_8020F6A4_ovl_ending + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6AC_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6AC_ovl_ending = 0;
    }
    D_8020F6A4_ovl_ending = alpha;
    if (D_8020F6A0_ovl_ending < 0x2814) {
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &D_80210800_ovl_ending[arg0];
        width = pic->width;
        gDPLoadTLUT_pal256(D_8007A184++, pic->tlut);
        D_8020F6A4_ovl_ending = alpha;
        x = (s32) D_8020F69C_ovl_ending % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(D_8007A184++, pic->img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(D_8007A184++, pic->img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }

    scroll = D_8020F69C_ovl_ending;
    switch (D_8020F6B0_ovl_ending) {
        case 0:
            delta = 0.0f;
            break;
        case 1:
            delta = 0.7111111f;
            break;
        case 2:
            delta = -0.42666668f;
            break;
        default:
            delta = 0.0f;
            break;
    }
    alpha = D_8020F6A8_ovl_ending + delta;
    if (alpha > 255.0f) {
        alpha = 255.0f;
        D_8020F6B0_ovl_ending = 0;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
        D_8020F6B0_ovl_ending = 0;
        if (D_8020F6B4_ovl_ending == 1) {
            D_8020F6B4_ovl_ending = 2;
        }
    }
    D_8020F6A8_ovl_ending = alpha;
    if (D_8020F6A0_ovl_ending >= 0x26AC) {
        gDPPipeSync(D_8007A184++);
        gDPSetEnvColor(D_8007A184++, 0xFF, 0xFF, 0xFF, (s32) alpha);
        pic = &D_80210800_ovl_ending[arg0 + 1];
        width = pic->width;
        gDPLoadTLUT_pal256(D_8007A184++, pic->tlut);
        D_8020F6A8_ovl_ending = alpha;
        x = (s32) scroll % width;
        for (y = 0; y < 222; y += 6) {
            gDPLoadTextureTile(D_8007A184++, pic->img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, x, y, 303, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, 0, y << 2, (304 - x) << 2, (y + 6) << 2, G_TX_RENDERTILE, x << 5, y << 5,
                                0x400, 0x400);
            gDPLoadTextureTile(D_8007A184++, pic->img, G_IM_FMT_CI, G_IM_SIZ_8b, width, 0, 0, y, x - 1, y + 5, 0, 0, 0, 0, 0,
                               0, 0);
            gSPTextureRectangle(D_8007A184++, (304 - x) << 2, y << 2, 304 << 2, (y + 6) << 2, G_TX_RENDERTILE, 0, y << 5,
                                0x400, 0x400);
        }
    }
    frame = D_8020F6A0_ovl_ending + 1;
    D_8020F6A0_ovl_ending = frame;
    if ((frame >= 240.0) && (frame < 0x26E8)) {
        D_8020F69C_ovl_ending = scroll - (f32) width / (f32) arg1;
        return 0;
    }
    if (D_8020F6A0_ovl_ending == 0x26E8) {
        D_8020F6B4_ovl_ending = 1;
    }
    return 0;
}
