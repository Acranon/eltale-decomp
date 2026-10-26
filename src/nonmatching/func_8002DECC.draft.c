/* Unmatched research draft for func_8002DECC. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/decc-review/base.c
 * Snapshot SHA-256: bc6255cd0bbb643e69643a85014208d8e9c627ea7abfe688050d8a6745d716cb
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8002DECC(s32 id, s32 x, s32 y, s32 w, s32 h) {
    s32 ret;
    s32 alpha;
    s32 xr;
    s32 masks;
    s32 maskt;
    s32 ult;
    s32 uls;
    s32 s;
    s32 t;
    s32 dsdx;
    s32 dtdy;
    s32 texH;
    s32 d;
    s32 lrs;
    s32 lrt;
    u8* tex;
    s32 texW;
    s32 pad[2];

    tex = D_80060D74[id];
    texW = D_80060CB4[id][0];
    texH = D_80060CB4[id][1];
    lrs = texW - 1;
    lrt = texH - 1;
    alpha = 0;
    ret = 0;
    maskt = 0;
    masks = 0;
    s = 0;
    t = 0;
    uls = 0;
    ult = 0;
    dtdy = 0x400;
    dsdx = 0x400;

    switch (id) {
        case 0:
            maskt = 4;
            masks = 4;
            s = (x & 0xF) << 5;
            t = (y & 0xF) << 5;
            break;
        case 0x3C:
            alpha = -0x80;
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3E:
            alpha = 0x50;
            break;
        case 0x37:
        case 0x38:
        case 0x39:
            dtdy = 0;
            dsdx = 0;
            break;
        case 0x3D:
            dsdx = 0;
            break;
    }
    if (x < 0) {
        if (x + w < 0) {
            ret = -1;
        } else {
            d = -x;
            s += d << 5;
            x = 0;
            w -= d;
        }
    }
    if (x > 320) {
        ret = -1;
    } else if ((xr = x + w) > 320) {
        w = w - xr + 320;
    }
    if (w <= 0 || h <= 0) {
        ret = -1;
    }
    if (ret >= 0) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0x504240, 0);
        gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
        gDPPipeSync(D_8007A184++);
        if (alpha == 0) {
            gSPDisplayList(D_8007A184++, D_80060ED8);
        } else {
            gSPDisplayList(D_8007A184++, D_80060EF0);
            gDPPipeSync(D_8007A184++);
            gDPSetEnvColor(D_8007A184++, 255, 255, 255, alpha);
        }
        if (!(D_8008FB3E & 0x10)) {
            gDPPipeSync(D_8007A184++);
            gDPLoadTLUT_pal256(D_8007A184++, D_80061E98);
            D_8008FB3E |= 0x10;
        }
        gDPLoadTextureTile(D_8007A184++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, texW, 0, uls, ult, lrs, lrt, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(D_8007A184++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, s, t, dsdx,
                            dtdy);
        gDPPipeSync(D_8007A184++);
    }
}
