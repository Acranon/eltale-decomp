/* Unmatched research draft for func_8000CC78. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_8000CC78_30words.c
 * Snapshot SHA-256: 25d989fb6e13ddb8d63310dff0b5b36ea1b320113c334b82fe864dc986ea5329
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_8000CC78(void) {
    SpawnScript *e;
    f32 x;
    f32 y;
    f32 z;
    f32 s;
    u16 m;
    s32 pad2;
    Obj *obj;
    s32 pad3;
    s32 pad4;
    SpawnDef *d;
    Unk800C18D8 *t;
    Enemy *en = D_8007B908;
    Unk8007C060 *p = (Unk8007C060 *) &D_8007C060;

    if (p->unk4 != 0) {
        e = (SpawnScript *) p->unk4;
        if (e->time < ++p->unk0) {
            obj = p->unkC;
            if (e->flags & 8) {
                D_8007C070.x = e->unk8;
                D_8007C070.y = e->unk10;
                func_800271B4(obj->angle, &D_8007C070);
                en->unk20 = D_8007C070.x;
                en->unk24 = D_8007C070.y;
            } else {
                d = &((SpawnDef *) &D_80056718)[e->unk2];
                t = &D_800C18D8[d->unk0];
                D_8007C070.x = e->unk8;
                D_8007C070.y = e->unk10;
                func_800271B4(obj->angle + e->unk14, &D_8007C070);
                if (e->flags & 2) {
                    x = D_8007AA20;
                    y = D_8007AA24;
                    z = D_8007AA28;
                } else {
                    x = obj->x;
                    y = obj->y;
                    z = obj->z;
                }
                s = obj->unk24;
                x += D_8007C070.x * s;
                y += e->unkC * s;
                z += D_8007C070.y * s;
                D_8007C070.x = d->unk8;
                D_8007C070.y = d->unkC;
                m = ((Enemy *) p->unk8)->unk1C->unk0;
                if (m & 0x8000) {
                    D_8007C070.z = D_800C185C[(m >> 8) & 0xF][m & 0xFF].unk1C;
                } else {
                    gfx_cc78_dummy:;
                    D_8007C070.z = obj->unk28;
                }
                func_80019820(d->unk2, d->unk4, x, y, z, obj->angle + e->unk14, t, &D_8007C070, obj);
            }
            if (e->flags & 4) {
                func_80015D78(1);
            }
            if (e->flags & 1) {
                p->unk4 = 0;
            } else {
                p->unk4 += sizeof(SpawnScript);
            }
        }
    }
}
