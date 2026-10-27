#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 unk18;
} CollResult;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ u16 *unk1C;
    /* 0x20 */ u16 *unk20;
    /* 0x24 */ u16 *unk24;
    /* 0x28 */ u16 unk28;
} Unk8007C28C;

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6;
} CollVert;

typedef struct {
    /* 0x00 */ s16 v0;
    /* 0x02 */ s16 v1;
    /* 0x04 */ s16 v2;
    /* 0x06 */ u16 flags;
    /* 0x08 */ f32 nx;
    /* 0x0C */ f32 ny;
    /* 0x10 */ f32 nz;
} CollTri; /* size 0x14 */

typedef struct {
    /* 0x00 */ s16 minX;
    /* 0x02 */ s16 maxX;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 minZ;
    /* 0x0A */ s16 maxZ;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ CollTri *tris;
    /* 0x18 */ u16 ntris;
    /* 0x1C */ CollVert *verts;
} CollMesh; /* size 0x20 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 scale;
    /* 0x14 */ s16 mesh;
    /* 0x16 */ u16 unk16;
} CollObj; /* size 0x18 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} Vec2f;

typedef struct {
    /* 0x00 */ s32 start;
    /* 0x04 */ s32 count;
} CollRange;

typedef struct {
    /* 0x00 */ Vec2f *verts;
    /* 0x04 */ s32 *idx;
    /* 0x08 */ CollRange *ranges;
    /* 0x0C */ s32 count;
} CollWalls; /* size 0x10 */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 angle;
    /* 0x0C */ f32 halfW;
    /* 0x10 */ f32 halfD;
    /* 0x14 */ u16 flags;
    /* 0x16 */ u16 id;
    /* 0x18 */ u8 pad18[0xC];
} Unk24; /* size 0x24 */

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Unk24 *list;
    /* 0x08 */ s32 count;
} Unk8007C288;

s32 func_80010A4C(f32, f32, u16, u16, CollResult *);
s32 func_80010BC8(f32, f32, f32, u16, CollMesh *, CollResult *);
s32 func_80010F34(f32, f32, f32, f32, f32, f32);
s32 func_80011034(f32 *, f32 *, f32, f32, f32, f32, f32);
f32 sqrtf(f32);
s32 func_8001164C(f32, f32, CollWalls *, CollResult *);
s32 func_800118E4(f32);
s32 func_80011978(Unk24 *);
void func_80011A10(Unk24 *);
void func_800271B4(f32, f32 *);

extern Unk8007C288 *D_8007C288;
extern Unk8007C28C *D_8007C28C;
extern CollObj *D_8007C290;
extern CollMesh *D_8007C294;
extern CollWalls *D_8007C298;
extern CollWalls *D_8007C29C;
extern s32 D_800842C0;
/* This file's .bss, 800842F0..80084300. */
f32 D_800842F0;
extern Vec2f D_80084320;
extern u16 D_8008BE52;
extern u8 D_8008C9B8[];

void func_800107F0(f32 x, f32 y, f32 z, u16 flags, CollResult *out) {
    u16 *list;
    s32 ix;
    s32 iz;
    s32 i;
    s32 n;

    D_800842F0 = out->x;
    out->x = x;
    out->y = y;
    out->z = z;
    out->unk18 = 0x8000;
    out->nx = 0.0f;
    out->nz = 0.0f;
    out->ny = 1.0f;
    if (flags & 1) {
        if (D_8007C298 != NULL && func_8001164C(x, z, &D_8007C298[D_800842C0], out)) {
            x = out->x;
            z = out->z;
        }
    } else if (flags & 2) {
        if (D_8007C29C != NULL && func_8001164C(x, z, &D_8007C29C[D_800842C0], out)) {
            x = out->x;
            z = out->z;
        }
    }
    ix = 0;
    iz = 0;
    if (D_8007C28C->unk28 == 0) {
        list = D_8007C28C->unk20;
    } else {
        ix = (x - D_8007C28C->unk8) / D_8007C28C->unk10;
        iz = (z - D_8007C28C->unkC) / D_8007C28C->unk14;
        i = D_8007C28C->unk4 * iz + ix;
        list = &D_8007C28C->unk20[D_8007C28C->unk1C[i]];
    }
    if (ix >= 0 && ix < D_8007C28C->unk4 && iz >= 0 && iz < D_8007C28C->unk6) {
        for (n = *list++; n != 0; n--) {
            if (func_80010A4C(x, z, flags, *list++, out)) {
                return;
            }
        }
    }
    list = D_8007C28C->unk24;
    for (n = D_8007C28C->unk2; n != 0; n--) {
        if (func_80010A4C(x, z, flags, *list++, out)) {
            return;
        }
    }
}

s32 func_80010A4C(f32 x, f32 z, u16 flags, u16 idx, CollResult *out) {
    s32 ret;
    s32 pad;
    CollMesh *mesh;
    CollObj *obj;
    f32 ang;
    f32 v[2];

    obj = &D_8007C290[idx];
    x -= obj->x;
    z -= obj->z;
    ang = obj->angle * 0.017453292519943295;
    ret = 0;
    mesh = &D_8007C294[obj->mesh];
    if (ang != 0.0f) {
        v[0] = x;
        v[1] = z;
        func_800271B4(ang, v);
        x = -v[0];
        z = v[1];
    }
    if ((obj->unk16 & 0xFF) < 0x10) {
        ret = func_80010BC8(x, z, obj->scale, flags, mesh, out);
        if (ret) {
            out->y += obj->y;
            if (ang != 0.0f) {
                v[0] = out->nx;
                v[1] = out->nz;
                func_800271B4(-ang, v);
                out->nx = -v[0];
                out->nz = v[1];
            }
        }
    }
    return ret;
}

s32 func_80010BC8(f32 x, f32 z, f32 scale, u16 flags, CollMesh *mesh, CollResult *out) {
    CollTri *tri;
    s32 ret;
    CollVert *verts;
    CollVert *va;
    CollVert *vb;
    CollVert *vc;
    f32 ax;
    f32 az;
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    f32 bx;
    f32 bz;
    f32 cx;
    f32 cz;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 ay;
    s32 c;
    s32 n;
    s32 i0;
    s32 i1;
    s32 i2;

    ret = 0;
    tri = mesh->tris;
    verts = mesh->verts;
    if (tri != NULL) {
        ax = mesh->minX * scale;
        bx = mesh->maxX * scale;
        az = mesh->minZ * scale;
        bz = mesh->maxZ * scale;
        if (x < ax || bx < x || z < az || bz < z) {
            return 0;
        }
        for (n = mesh->ntris; n != 0; n--, tri++) {
            if (tri->flags & flags) {
                i0 = tri->v0;
                i1 = tri->v1;
                i2 = tri->v2;
                va = (CollVert *)((u8 *)verts + i0 * 8);
                vb = (CollVert *)((u8 *)verts + i1 * 8);
                vc = (CollVert *)((u8 *)verts + i2 * 8);
                ax = va->x * scale;
                az = va->z * scale;
                bx = vb->x * scale;
                bz = vb->z * scale;
                cx = vc->x * scale;
                cz = vc->z * scale;
                if (x == ax && z == az) {
                    c = 1;
                } else if (x == bx && z == bz) {
                    c = 1;
                } else if (x == cx && z == cz) {
                    c = 1;
                } else {
                    if (0) {
                    }
                    c = func_80010F34(x, z, ax, az, bx, bz);
                    c += func_80010F34(x, z, bx, bz, cx, cz);
                    c += func_80010F34(x, z, ax, az, cx, cz);
                }
                if (c == 1) {
                    ny = tri->ny;
                    nx = tri->nx;
                    nz = tri->nz;
                    ay = va->y * scale;
                    if (ny != 0.0f) {
                        out->y = -((nx * x + nz * z) - (nx * ax + ny * ay + nz * az)) / ny;
                        out->unk18 = tri->flags;
                    } else {
                        out->unk18 = tri->flags;
                    }
                    out->nx = nx;
                    out->ny = ny;
                    out->nz = nz;
                    ret = 1;
                    break;
                }
            }
        }
    }
    return ret;
}

s32 func_80010F34(f32 px, f32 pz, f32 ax, f32 az, f32 bx, f32 bz) {
    if ((az <= pz && pz < bz) || (bz <= pz && pz < az)) {
        if (ax <= px && bx < px) {
            return 1;
        }
        if (px <= ax && px < bx) {
            return 0;
        }
        if (az != bz) {
            if ((pz - az) * ((ax - bx) / (az - bz)) + ax < px) {
                return 1;
            }
        }
    }
    return 0;
}

#ifdef NON_MATCHING
/* FP register allocation and stack homes differ, two extra instructions; code is equivalent.
 * Both endpoint cases push away from (ax, az), as retail does. */
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
                /* retail: (ax, az) here too, not (bx, bz) */
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/113F0/func_80011034.s")
#endif

s32 func_8001164C(f32 x, f32 z, CollWalls *walls, CollResult *out) {
    s32 n;
    CollRange *range;
    s32 hit;
    s32 m;
    s32 *idx;
    Vec2f *a;
    f32 ax;
    f32 az;
    f32 bx;
    f32 bz;

    n = walls->count;
    range = walls->ranges;
    hit = 0;
    for (; n != 0; n--, range++) {
        m = range->count;
        idx = &walls->idx[range->start];
        for (; m != 0; m--) {
            a = &walls->verts[idx[0]];
            ax = a->x;
            az = a->z;
            a = &walls->verts[idx[1]];
            bx = a->x;
            bz = a->z;
            idx++;
            hit |= func_80011034(&x, &z, D_800842F0, ax, az, bx, bz);
        }
    }
    out->x = x;
    out->z = z;
    return hit;
}

s32 func_80011770(f32 x, f32 z, f32 angle) {
    s32 pad;
    s32 ret = 0;
    s32 n;
    Unk24 *p;
    f32 dx;
    f32 dz;
    if (D_8007C288->count == 0 || (D_8008BE52 & 1)) {
        return 0;
    }
    n = D_8007C288->count;
    for (p = D_8007C288->list; n != 0; n--, p++) {
        if (func_80011978(p)) {
            D_80084320.x = x - p->x;
            D_80084320.z = z - p->z;
            func_800271B4(p->angle, &D_80084320.x);
            dx = D_80084320.x;
            if (dx < 0.0f) {
                dx = -dx;
            }
            dz = D_80084320.z;
            if (dz < 0.0f) {
                dz = -dz;
            }
            if (dx < p->halfW && dz < p->halfD) {
                if ((p->flags & 2) || func_800118E4(angle - p->angle)) {
                    func_80011A10(p);
                    ret = 1;
                }
                break;
            }
        }
    }
    return ret;
}

s32 func_800118E4(f32 angle) {
    if (angle > 3.141592653589793) {
        angle -= 6.283185307179586;
    } else if (angle < -3.141592653589793) {
        angle += 6.283185307179586;
    }
    if (angle < 0.0f) {
        angle = -angle;
    }
    return angle < 0.39269908169872414;
}

s32 func_80011978(Unk24 *arg0) {
    s32 i;
    s32 ret;
    s32 flags = arg0->flags;

    if (flags & 0x30) {
        for (i = 0; i < 0x96; i++) {
            if (arg0->id == D_8008C9B8[i]) {
                break;
            }
        }
        if (flags & 0x10) {
            if (i < 0x96) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            if (i < 0x96) {
                ret = 0;
            } else {
                ret = 1;
            }
        }
    } else {
        ret = 1;
    }
    return ret;
}
