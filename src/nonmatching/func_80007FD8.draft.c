/* Unmatched research draft for func_80007FD8. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80007FD8_235words.c
 * Snapshot SHA-256: cb8a6cd26d9496cd73af1dec6c50156334c38d79121132183c74cdbad3ed0736
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_80007FD8(u16 dmg, u16 arg1, Actor *arg2) {
    PlayerState *p = &D_8007AA08;
    CharData *cd;
    f32 angle;
    s32 d;
    s32 flags;

    if (p->unk0 != 6) {
        cd = D_80055D40[p->actor.unk50];
        if (dmg != 0) {
            if (arg1 & 0x8000) {
                angle = func_800270D0(arg2->x - D_8007AA20.x, arg2->z - D_8007AA20.z) - D_8007AA20.rot;
                if (angle > 3.141592653589793) {
                    angle -= 6.283185307179586;
                } else if (angle < -3.141592653589793) {
                    angle += 6.283185307179586;
                }
                if (angle < 0.0f) {
                    angle = -angle;
                }
                if (angle > 2.356194490192345) {
                    dmg += dmg >> 1;
                }
            }
            dmg = dmg * ((f32) arg2->unk68->unk84 / (f32) (arg2->unk68->unk84 + p->unk10C));
            dmg += func_80026E90((u32) (sqrtf(dmg) * 0.75 + 1.0));
            if (dmg == 0) {
                dmg++;
            }
            d = dmg;
            if (p->actor.unk64->unk4 < dmg) {
                p->actor.unk64->unk4 = 0;
            } else {
                p->actor.unk64->unk4 -= d;
            }
            if (p->unk84 & 0x200) {
                p->actor.unk64->unk8 += d;
                if (p->actor.unk64->unkA < p->actor.unk64->unk8) {
                    p->actor.unk64->unk8 = p->actor.unk64->unkA;
                }
                func_8002373C(&D_8007AA20, 0x200, 2, 0x1E);
            }
            flags = 0;
            p->unk14->unk28++;
            p->unk14->unk2E++;
            if (arg1 & 0x4000) {
                flags = 0x8003;
            }
            func_8001AE24(&D_8007AA20, flags, d);
        }
        p->unk0 = 5;
        p->unk4 = cd->unk62;
        D_8007AA20.unk60 |= 1;
        d = arg1 & 0x8000;
        if (arg1 & 4) {
            D_8007AA20.unk60 |= 2;
        }
        func_800201A0(&D_8007AA20, 8, 1, D_8007A910, 1, 1);
        if (dmg != 0) {
            func_80015D78(2);
        }
        if (d != 0) {
            func_8002A7C8(0, 0x18, 0xFF);
        }
    }
    return dmg;
}
