/* Unmatched research draft for func_80011EF4. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80011EF4_325words.c
 * Snapshot SHA-256: 0b95e70f942012795be5ad0fa1a0e23d798fe42d139b0cc6ed7d8437abc53414
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

void func_80011EF4(s32 t, Unk80084994 *arg1) {
    KeyTrack *track = (KeyTrack *)arg1;
    Keyframe *k;
    Keyframe *prev;
    s32 span;
    s32 off;
    s32 rem;
    Color3 *ambient = (Color3*)D_80084B18;
    Color3 *light;
    FogSet *fog = (FogSet*)D_80084B78;
    Color3 *before;
    Color3 *after;

    k = track->frames;
    if (track->count == 1) {
        *ambient = k->amb;
        light = (Color3*)((u32)D_80084B24.l / 1);
        *light++ = k->lights.l[0];
        *light++ = k->lights.l[1];
        *light++ = k->lights.l[2];
        *fog = k->fog;
        return;
    }
    while (t >= k->time) {
        k++;
    }
    prev = k - 1;
    span = k->time - prev->time;
    off = t - prev->time;
    rem = span - off;
    light = (Color3*)((u32)D_80084B24.l / 1);
    before = &prev->amb;
    after = &k->amb;
    ambient->r = (before->r * rem + after->r * off) / span;
    ambient->g = (before->g * rem + after->g * off) / span;
    ambient->b = (before->b * rem + after->b * off) / span;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    light++;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    light++;
    before++;
    after++;
    light->r = (before->r * rem + after->r * off) / span;
    light->g = (before->g * rem + after->g * off) / span;
    light->b = (before->b * rem + after->b * off) / span;
    fog->near = (prev->fog.near * rem + k->fog.near * off) / span;
    fog->far = (prev->fog.far * rem + k->fog.far * off) / span;
}
