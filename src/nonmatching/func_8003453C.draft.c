/* Unmatched research draft for func_8003453C. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex-ui-resume/337B0.unmatched.c
 * Snapshot SHA-256: e55ea00712e5e50cfdb80e6a3b365fbaf398022f087263d1addc98ec8bebb2a0
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8003453C(s32 idx) {
    Unk80090470 *p = &D_80090470[idx];
    s32 cols = (p->unk8 - 20) / 10 + 1;
    s32 rows = (p->unkA - 20) / 13;
    s32 k = 0;
    s32 dst = -1;
    s32 src = -1;
    s32 row;
    s32 col;
    s32 j;
    s32 n;
    u8 c;

    for (row = 1; row <= rows; row++) {
        for (col = 0; col < cols;) {
            D_80090470[idx].unk54C[++dst] = D_80090470[idx].unk9C[++src];
            c = D_80090470[idx].unk54C[dst];
            if (c & 0x80) {
                if (c == 0xE0 || c == 0xFF || (c == 0xF0 && k != 0)) {
                    break;
                }
            } else {
                col++;
                k++;
            }
        }
        c = D_80090470[idx].unk54C[dst];
        if (c == 0xFF) {
            break;
        }
        if (c == 0xF0) {
            p->unk0 |= 0x4000000;
            break;
        }
        if (c != 0xE0 && c != 0xE0) {
            n = -1;
            for (j = src + 1; D_80090470[idx].unk9C[j] >= 0x80; j++) {
                if (D_80090470[idx].unk9C[j] == 0xE0) {
                    for (n = j - src; n > 0; n--) {
                        D_80090470[idx].unk54C[++dst] = D_80090470[idx].unk9C[++src];
                    }
                    D_80090470[idx].unk54C[++dst] = D_80090470[idx].unk9C[++src];
                    n = 0;
                    break;
                }
            }
            if (n != 0) {
                D_80090470[idx].unk54C[++dst] = 0xE0;
            }
        }
    }
    c = D_80090470[idx].unk54C[dst];
    if (c != 0xFF && c != 0xF0) {
        p->unk0 |= 0x4000000;
        p->unk54C[dst + 1] = 0xFF;
        if (p->unk14 != 0xFF) {
            p->unk9C[(u16)p->unk12] = p->unk14;
            p->unk12 = src + 1;
            p->unk14 = p->unk9C[src + 1];
            p->unk9C[src + 1] = 0xFF;
        } else {
            p->unk0 |= 0x2000000;
            p->unk0 &= ~0x8000000;
            func_8003521C();
        }
    }
}
