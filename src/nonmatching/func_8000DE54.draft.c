/* Unmatched research draft for func_8000DE54. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_8000DE54_438words.c
 * Snapshot SHA-256: 0ec099a6fe47a584f0a50b4fa903aaaa9afdbb6430624551df94f6591c1179b0
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8000DE54(MtxBuf *arg0) {
    CellOffset *off;
    s32 n;
    s32 cx;
    s32 cz;
    s32 gx;
    s32 gz;
    s32 idx;
    u16 *list;
    u16 t;
    f32 px;
    f32 pz;
    Unk8000FA9C *s;
    u16 flags;
    f32 x;
    f32 y;
    f32 z;
    f32 rot;
    AnimInfo20 *anim;
    u16 frame;
    s32 i;
    Unk80082048 *a;
    Unk80082048 *b;
    f64 d;
    s32 k;
    s32 *pCB4 = &D_80081CB4;
    s32 *pCB8 = &D_80081CB8;
    Unk8000FA9C ***pCD0 = &D_80081CD0;
    f32 *pAC = &D_800842AC;
    s32 *pB0 = &D_800842B0;

    *pCB4 = 0;
    D_80081CB0 = 0;
    *pCB8 = 0;
    D_80081CBC = 0;
    D_80081CC0 = 0;
    D_80081CC4 = 0;
    D_8007C2A4 = 0;
    D_80081CC8 = (Unk8000FA9C **)D_80082058;
    D_80081CCC = (Unk8000FA9C **)D_80082458;
    *pCD0 = (Unk8000FA9C **)D_8007C2A8;
    D_80081CD4 = D_80082860;
    D_80081CD8 = D_80082C60;
    D_80081CDC = D_80083068;
    D_80081FE8 = (Unk8000FA9C *)D_80081CE8;
    *pAC = 600.0f;
    *pB0 = -1;
    px = D_80085E48.x;
    pz = D_80085E48.z;
    switch (D_8007C28C->unk28) {
        case 1:
            off = D_8005758C;
            n = 0x9D;
            cx = (px - D_8007C28C->originX) / D_8007C28C->cellW;
            cz = (pz - D_8007C28C->originZ) / D_8007C28C->cellD;
            break;
        case 2:
            off = D_800576C8;
            n = 0x59;
            cx = (px - D_8007C28C->originX) / D_8007C28C->cellW;
            cz = (pz - D_8007C28C->originZ) / D_8007C28C->cellD;
            break;
        case 3:
            off = D_8005777C;
            n = 9;
            cx = (px - D_8007C28C->originX) / D_8007C28C->cellW;
            cz = (pz - D_8007C28C->originZ) / D_8007C28C->cellD;
            break;
        case 4:
            off = D_80057790;
            n = 0x15;
            cx = (px - D_8007C28C->originX) / D_8007C28C->cellW;
            cz = (pz - D_8007C28C->originZ) / D_8007C28C->cellD;
            break;
        default:
            off = D_80057588;
            cx = 0;
            cz = 0;
            n = 1;
            break;
    }
    for (; n != 0; n--) {
        gx = off->dx + cx;
        gz = off->dz + cz;
        off++;
        if (gx >= 0 && gz >= 0 && gx < D_8007C28C->w && gz < D_8007C28C->h) {
            idx = D_8007C28C->w * gz + gx;
            list = &D_8007C28C->lists[D_8007C28C->cells[idx]];
            t = *list;
            func_8000EEA8(t, list + 1);
        }
    }
    if (D_8007C28C->unk2 != 0) {
        t = D_8007C28C->unk2;
        func_8000EEA8(t, D_8007C28C->unk24);
    }
    gSPDisplayList(D_8007A184++, D_10000E8);
    gSPFogPosition(D_8007A184++, D_8007A1A0, D_8007A1A2);
    D_8007C2A0 = 0;
    D_80081CC8 = (Unk8000FA9C **)D_80082058;
    for (n = D_80081CB0; n != 0; n--) {
        s = *D_80081CC8++;
        flags = s->unk16;
        x = s->x;
        y = s->y;
        z = s->z;
        rot = s->angle;
        if (flags & 0x2000) {
            anim = &D_8005839C[(flags & 0xF00) >> 8];
            t = flags;
            t = (t & 0xFF) + 1;
            func_80026A00((AnimInfo *)anim, &D_80082020, flags & 0xFF);
            x += D_80082020.x * s->scale;
            y += D_80082020.y * s->scale;
            z += D_80082020.z * s->scale;
            flags = t;
            if (t >= anim->unk6) {
                flags = 0;
            }
            s->unk16 = (s->unk16 & 0xFF00) | flags;
        } else if (flags & 0x100) {
            i = func_8000F4C8((s32)s);
            if (i != 0) {
                D_80081FF0[1] = 0.0f;
                D_80081FF0[0] = D_80084238[i - 1].x;
                func_800271B4(s->angle * 0.017453292519943295, D_80081FF0);
                x -= D_80081FF0[0];
                z -= D_80081FF0[1];
                rot += D_80084238[i - 1].z;
            }
        }
        guPosition(&arg0->mtx[D_8007A180], 0.0f, rot, 0.0f, s->scale, x, y, z);
        gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
        D_8007A180++;
        gSPDisplayList(D_8007A184++, D_8007C294[s->timer].dl);
        D_8007C2A0++;
    }
    D_80081CC8 = D_80082458;
    for (n = *pCB4; n != 0; n--) {
        s = (D_80081CC8)++[0];
        guPosition(&arg0->mtx[D_8007A180], 0.0f, s->angle, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(D_8007A184++, &D_2000000.mtx[D_8007A180], G_MTX_LOAD);
        D_8007A180++;
        gSPDisplayList(D_8007A184++, D_8007C294[s->timer].dl);
        D_8007C2A0++;
    }
    func_8000FF18(arg0);
    if (*pCB8 != 0) {
        gDPPipeSync(D_8007A184++);
        gDPSetRenderMode(D_8007A184++, 0xC8113078, 0);
        *pCD0 = (Unk8000FA9C **)D_8007C2A8;
        func_8000F740(arg0, *pCB8, 0, *pCD0);
        func_8000F740(arg0, *pCB8, 1, *pCD0);
        func_8000F740(arg0, *pCB8, 2, *pCD0);
        func_8000F740(arg0, *pCB8, 3, *pCD0);
    }
    gDPSetTextureFilter(D_8007A184++, G_TF_BILERP);
    gDPSetTextureLUT(D_8007A184++, G_TT_NONE);
    a = D_80082048; b = (Unk80082048 *)D_8004DD74;
    for (;;) {
        u16 ta = a->a + b->a;
        u16 tb = a->b + b->b;
        b++;
        k = b < ((Unk80082048 *)D_8004DD74) + 4;
        a++;
        a[-1].a = ta;
        a[-1].b = tb;
        if (!k) break;
    }
    D_80081CE0 = 0;
    func_800104C0();
    func_80010768();
    if (D_800842B0 == -1) {
        if (D_800842B4 != D_800842B0) {
            func_8002A410();
        }
    } else {
        d = D_800842AC;
        if (d > 200.0) {
            n = (600.0 - d) * 0.6375;
        } else {
            n = 0xFF;
        }
        if (n >= 2) {
            func_8002A890(((Unk8004DD88 *)D_8004DD88)[D_800842B0].sfx, n);
        } else {
            func_8002A410();
            D_800842B0 = D_800842B4 = -1;
        }
    }
    D_800842B4 = D_800842B0;
}
