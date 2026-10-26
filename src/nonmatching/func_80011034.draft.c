/* Unmatched research draft for func_80011034. Not compiled by the retail build.
 * Source snapshot: /home/sean/eltale-notes/codex/gfx-resume/func_80011034_164words.c
 * Snapshot SHA-256: bf071c71ac2bd20fa7c13d7c4a8438fde44e283d890e47e925ca79c0105d3530
 * Function body only; replay in its live source module with the required
 * local types, declarations, macros and data layout from that snapshot.
 * This is not an exact ROM match.
 */

s32 func_80011034(f32 *px, f32 *pz, f32 r, f32 ax, f32 az, f32 bx, f32 bz) {
    s32 ret;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 dist;
    f32 k;
    f32 ix;
    f32 iz;
    f32 dx;
    f32 dz;
    f32 cx;
    f32 cz;

    ret = 0;
    a = (ax <= bx) ? ax : bx;
    b = (bx < ax) ? ax : bx;
    c = (az <= bz) ? az : bz;
    d = (bz < az) ? az : bz;
    if (*px < a - r || b + r < *px || *pz < c - r || d + r < *pz) {
        return 0;
    }
    if (ax == bx) {
        a = 1.0f;
        b = 0.0f;
        c = -ax;
    } else if (az == bz) {
        a = 0.0f;
        b = 1.0f;
        c = -az;
    } else {
        b = 1.0f;
        a = -(bz - az) / (bx - ax);
        c = -a * ax - az;
    }
    d = a * *px + b * *pz + c;
    if (d < 0.0f) {
        d = -d;
    }
    dist = d / sqrtf(a * a + b * b);
    if (dist < r) {
        if (a == 0.0f) {
            a2 = 1.0f;
            b2 = 0.0f;
            cx = *px;
            cz = *pz;
            c2 = -cx;
        } else if (b == 0.0f) {
            a2 = 0.0f;
            b2 = 1.0f;
            cz = *pz;
            cx = *px;
            c2 = -cz;
        } else {
            a2 = -1.0f / a;
            cx = *px;
            cz = *pz;
            b2 = 1.0f;
            c2 = -a2 * cx - cz;
        }
        ix = (c2 * b - c * b2) / (a * b2 - a2 * b);
        iz = (a2 * c - a * c2) / (a * b2 - a2 * b);
        a = (ax <= bx) ? ax : bx;
        b = (bx < ax) ? ax : bx;
        dz = az;
        c = (dz <= bz) ? dz : bz;
        d = (bz < dz) ? dz : bz;
        if (ix < a || b < ix || iz < c || d < iz) {
            a = ax - cx;
            b = dz - cz;
            c = sqrtf(a * a + b * b);
            if (c < r) {
                dx = ax - *px;
                dz = dz - *pz;
                k = ((r + 0.1) - c) / sqrtf(dx * dx + dz * dz);
                *px -= dx * k;
                *pz -= dz * k;
                return 1;
            }
            a = bx - *px;
            b = bz - *pz;
            c = sqrtf(a * a + b * b);
            if (c < r) {
                dx = ax - *px;
                dz = dz - *pz;
                k = ((r + 0.1) - c) / sqrtf(dx * dx + dz * dz);
                *px -= dx * k;
                *pz -= dz * k;
                return 1;
            }
            return 0;
        }
        dx = ix - cx;
        dz = iz - cz;
        if (dist != 0.0f) {
            ix = dx * dx + dz * dz;
            k = ((r + 0.1) - dist) / sqrtf(ix);
            *px -= dx * k;
            *pz -= dz * k;
        }
        ret = 1;
    }
    return ret;
}
