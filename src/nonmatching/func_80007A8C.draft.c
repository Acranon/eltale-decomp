/* Unmatched research draft for func_80007A8C. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80007A8C_5words.c
 * Snapshot SHA-256: 9fd87d61003e52cb4d08848882a1126088853f6ba9f2c716ee0161554b7e63ed
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_80007A8C(Actor *arg0) {
    Monster *m;
    s32 ret;
    u16 *idx;
    u32 i;
    f32 radius;
    Actor *a;
    ActorStats *stats;
    f32 dx;
    f32 dz;
    f32 r;
    f32 dist;

    radius = arg0->unk64->unk18 * arg0->scale;
    ret = 0;
    idx = D_8007C050;
    i = 0;
    for (; i < D_8008BE5A; i++, idx++) {
        m = D_8007B908 + *idx;
        a = &m->actor;
        if (m->actor.unk50 != -1) {
            dx = a->x - arg0->x;
            dz = a->z - arg0->z;
            dist = sqrtf(dx * dx + dz * dz);
            r = a->unk64->unk18 * a->scale;
            if (dist < radius + r + 10.0) {
                D_8007A918.x = dx;
                D_8007A918.z = dz;
                stats = a->unk64;
                if (stats->unk0 == 1) {
                    dx = a->unk68->unk94 - arg0->y;
                    dz = 2.0 * stats->unk18;
                } else if (stats->unk0 == 2) {
                    dz = 0.0f;
                    dx = 0.0f;
                } else {
                    dz = stats->unk1C;
                    dx = a->y - arg0->y;
                }
                if (dx < 0.0f) {
                    dx = -dx;
                }
                dx -= dz * a->scale + arg0->unk64->unk1C * arg0->scale;
                if (dx <= 0.0f) {
                    func_800271B4(arg0->rot, &D_8007A918);
                    r = r * 1.5;
                    if (D_8007A918.z >= 0.0f && -r < D_8007A918.x && D_8007A918.x < r) {
                        ret = *idx + 1;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}
