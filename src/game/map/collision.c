#include "game/map/collision.h"
#include "game/map/map.h"
#include "game/battle/battle.h"
#include "game/env/env.h"
#include "game/item/item.h"
#include "game/math/math.h"

/*
 * Map collision: floor height and normal from the room's triangle meshes (grid lookup),
 * pushing positions out of wall segments, and the map exits the player walks into.
 * Original file: 113F0.c (ROM 0x113F0).
 */

/* This file's .bss, 800842F0..80084300. */
f32 coll_push_radius;

void Coll_ResolveFloorAndWalls(f32 x, f32 y, f32 z, u16 flags, CollResult *out) {
    u16 *list;
    s32 ix;
    s32 iz;
    s32 i;
    s32 n;

    coll_push_radius = out->x;
    out->x = x;
    out->y = y;
    out->z = z;
    out->flags = 0x8000;
    out->nx = 0.0f;
    out->nz = 0.0f;
    out->ny = 1.0f;
    if (flags & 1) {
        if (map_actor_walls != NULL && Coll_PushFromWalls(x, z, &map_actor_walls[map_subarea], out)) {
            x = out->x;
            z = out->z;
        }
    } else if (flags & 2) {
        if (map_camera_walls != NULL && Coll_PushFromWalls(x, z, &map_camera_walls[map_subarea], out)) {
            x = out->x;
            z = out->z;
        }
    }
    ix = 0;
    iz = 0;
    if (map_subarea_grid->searchPattern == 0) {
        list = map_subarea_grid->lists;
    } else {
        ix = (x - map_subarea_grid->originX) / map_subarea_grid->cellW;
        iz = (z - map_subarea_grid->originZ) / map_subarea_grid->cellD;
        i = map_subarea_grid->w * iz + ix;
        list = &map_subarea_grid->lists[map_subarea_grid->cells[i]];
    }
    if (ix >= 0 && ix < map_subarea_grid->w && iz >= 0 && iz < map_subarea_grid->h) {
        for (n = *list++; n != 0; n--) {
            if (Coll_TestObjectFloor(x, z, flags, *list++, out)) {
                return;
            }
        }
    }
    list = map_subarea_grid->alwaysList;
    for (n = map_subarea_grid->alwaysCount; n != 0; n--) {
        if (Coll_TestObjectFloor(x, z, flags, *list++, out)) {
            return;
        }
    }
}

s32 Coll_TestObjectFloor(f32 x, f32 z, u16 flags, u16 idx, CollResult *out) {
    s32 ret;
    s32 pad;
    MapModel *mesh;
    MapObj *obj;
    f32 ang;
    Vec2f v;

    obj = &map_objs[idx];
    x -= obj->x;
    z -= obj->z;
    ang = obj->angle * 0.017453292519943295;
    ret = 0;
    mesh = &map_obj_models[obj->model];
    if (ang != 0.0f) {
        v.x = x;
        v.y = z;
        Math_RotateVec2(ang, &v);
        x = -v.x;
        z = v.y;
    }
    if ((obj->kind & 0xFF) < 0x10) {
        ret = Coll_TestMeshFloor(x, z, obj->scale, flags, mesh, out);
        if (ret) {
            out->y += obj->y;
            if (ang != 0.0f) {
                v.x = out->nx;
                v.y = out->nz;
                Math_RotateVec2(-ang, &v);
                out->nx = -v.x;
                out->nz = v.y;
            }
        }
    }
    return ret;
}

s32 Coll_TestMeshFloor(f32 x, f32 z, f32 scale, u16 flags, MapModel *mesh, CollResult *out) {
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
                    c = Coll_RayCrossesEdge(x, z, ax, az, bx, bz);
                    c += Coll_RayCrossesEdge(x, z, bx, bz, cx, cz);
                    c += Coll_RayCrossesEdge(x, z, ax, az, cx, cz);
                }
                if (c == 1) {
                    ny = tri->ny;
                    nx = tri->nx;
                    nz = tri->nz;
                    ay = va->y * scale;
                    if (ny != 0.0f) {
                        out->y = -((nx * x + nz * z) - (nx * ax + ny * ay + nz * az)) / ny;
                        out->flags = tri->flags;
                    } else {
                        out->flags = tri->flags;
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

s32 Coll_RayCrossesEdge(f32 px, f32 pz, f32 ax, f32 az, f32 bx, f32 bz) {
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
s32 Coll_PushFromSegment(f32 *px, f32 *pz, f32 r, f32 ax, f32 az, f32 bx, f32 bz) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/game/map/collision/Coll_PushFromSegment.s")
#endif

s32 Coll_PushFromWalls(f32 x, f32 z, CollWalls *walls, CollResult *out) {
    s32 n;
    CollWallRange *range;
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
            az = a->y;
            a = &walls->verts[idx[1]];
            bx = a->x;
            bz = a->y;
            idx++;
            hit |= Coll_PushFromSegment(&x, &z, coll_push_radius, ax, az, bx, bz);
        }
    }
    out->x = x;
    out->z = z;
    return hit;
}

s32 Exit_CheckEnter(f32 x, f32 z, f32 angle) {
    s32 pad;
    s32 ret = 0;
    s32 n;
    MapExit *p;
    f32 dx;
    f32 dz;
    if (map_subarea_def->exitCount == 0 || (battle_flags & 1)) {
        return 0;
    }
    n = map_subarea_def->exitCount;
    for (p = map_subarea_def->exits; n != 0; n--, p++) {
        if (Exit_IsEnabled(p)) {
            exit_local_offset.x = x - p->x;
            exit_local_offset.y = z - p->z;
            Math_RotateVec2(p->angle, &exit_local_offset);
            dx = exit_local_offset.x;
            if (dx < 0.0f) {
                dx = -dx;
            }
            dz = exit_local_offset.y;
            if (dz < 0.0f) {
                dz = -dz;
            }
            if (dx < p->halfW && dz < p->halfD) {
                if ((p->flags & 2) || Exit_IsFacing(angle - p->angle)) {
                    Exit_SetDestination(p);
                    ret = 1;
                }
                break;
            }
        }
    }
    return ret;
}

s32 Exit_IsFacing(f32 angle) {
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

s32 Exit_IsEnabled(MapExit *arg0) {
    s32 i;
    s32 ret;
    s32 flags = arg0->flags;

    if (flags & 0x30) {
        for (i = 0; i < 0x96; i++) {
            if (arg0->id == item_inventory[i]) {
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
