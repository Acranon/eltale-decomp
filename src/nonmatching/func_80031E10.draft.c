/* Unmatched research draft for func_80031E10. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/30600.unmatched.c
 * Snapshot SHA-256: dd034ae018369ae3d4a07eae226fd5ae74f39d224d09112c64727dc911383974
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80031E10(void) {
    s32 err;
    s32 n;
    s32 id;
    s32 i;
    s32 idx;
    Unk8008FB80 *p;
    s32 k;
    s32 cont;

    idx = D_8008FB7A;
    p = &D_8008FB80[idx];

    if (p->unk0 == -2) {
        cont = D_80092C80;
        n = D_80092E48[cont].unk0 & 0xF;
        id = 0xF;
        do {
            i = 0;
            id++;
            do {
                if (id == D_8008FB80[i].unk1) {
                    i = 0x7F;
                    break;
                }
                i++;
            } while (i < n);
            if (i != 0x7F) {
                n = id;
                id = -1;
            }
        } while (id >= 0);
        p->unk1 = n;
        if (idx + 1 < 16) {
            p[1].unk1 = -2;
        }
        err = func_80035D58(cont, n);
        if (err >= 0) {
            idx = D_8008FB7A;
            D_8008FB80[idx].unk0 = err;
        } else {
            idx = D_8008FB7A;
        }
        func_800327BC(idx);
    } else {
        func_800327BC(idx);
    }
    id = D_8008FB7A;
    err = func_80035F0C(D_80092C80, D_8008FB80[id].unk0, 0, 0x80, &D_8008FBA8[id]);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
            case 1:
                D_8008FB72 = 13;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 14;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        return;
    }
    err = func_80035F0C(D_80092C80, D_8008FB80[D_8008FB7A].unk0, 0x80, 0xE0, &D_80090228);
    if (err != 0) {
        D_8008FB74 = err;
        switch (-func_8003609C(err)) {
            case 1:
                D_8008FB72 = 13;
                D_8008FB79 = 10;
                break;
            case 4:
                D_8008FB72 = 14;
                D_8008FB79 = 10;
                break;
            default:
                D_8008FB72 = 17;
                D_8008FB79 = 10;
                break;
        }
        D_8008FB70 &= 0xFFF8;
        D_8008FB70 |= 5;
        D_8008FB70 &= ~0x2000;
        return;
    }
    D_8008FB70 &= 0xFFF8;
    D_8008FB70 |= 5;
    D_8008FB70 &= ~0x2000;
    D_8008FB72 = 23;
    D_8008FB79 = 10;
}
