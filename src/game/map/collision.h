#ifndef GAME_MAP_COLLISION_H
#define GAME_MAP_COLLISION_H

#include "common.h"
#include "game/math/math.h"

struct MapModel;
struct MapExit;

/*
 * A floor/wall query's result (Coll_ResolveFloorAndWalls). On input x holds the wall push
 * radius; on output x, z are the position after the wall push, y the floor height, n the
 * floor normal and flags the floor triangle's flags (0x8000: no floor found).
 */
typedef struct CollResult {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
    /* 0x1A */ u8 pad1A[2];
} CollResult; /* 0x1C bytes */

/* A collision mesh vertex (MapModel.verts). */
typedef struct CollVert {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6;
} CollVert; /* 0x8 bytes */

/* A collision mesh triangle (MapModel.tris): vertex indices, flags tested against the query's, normal. */
typedef struct CollTri {
    /* 0x00 */ s16 v0;
    /* 0x02 */ s16 v1;
    /* 0x04 */ s16 v2;
    /* 0x06 */ u16 flags;
    /* 0x08 */ f32 nx;
    /* 0x0C */ f32 ny;
    /* 0x10 */ f32 nz;
} CollTri; /* 0x14 bytes */

/* A run of wall segments in CollWalls.idx. */
typedef struct CollWallRange {
    /* 0x00 */ s32 start;
    /* 0x04 */ s32 count;
} CollWallRange; /* 0x8 bytes */

/* A sub-area's wall segments (map_actor_walls / map_camera_walls, one per sub-area). */
typedef struct CollWalls {
    /* 0x00 */ Vec2f *verts; /* ground plane: .y is the world z */
    /* 0x04 */ s32 *idx;
    /* 0x08 */ CollWallRange *ranges;
    /* 0x0C */ s32 count;
} CollWalls; /* 0x10 bytes */

/* .bss 800842F0..80084300 */
extern f32 coll_push_radius;

void Coll_ResolveFloorAndWalls(f32 x, f32 y, f32 z, u16 flags, CollResult *out);
s32 Coll_TestObjectFloor(f32 x, f32 z, u16 flags, u16 idx, CollResult *out);
s32 Coll_TestMeshFloor(f32 x, f32 z, f32 scale, u16 flags, struct MapModel *mesh, CollResult *out);
s32 Coll_RayCrossesEdge(f32 px, f32 pz, f32 ax, f32 az, f32 bx, f32 bz);
s32 Coll_PushFromSegment(f32 *px, f32 *pz, f32 r, f32 ax, f32 az, f32 bx, f32 bz);
s32 Coll_PushFromWalls(f32 x, f32 z, CollWalls *walls, CollResult *out);
s32 Exit_CheckEnter(f32 x, f32 z, f32 angle);
s32 Exit_IsFacing(f32 angle);
s32 Exit_IsEnabled(struct MapExit *arg0);

#endif
