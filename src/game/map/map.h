#ifndef GAME_MAP_MAP_H
#define GAME_MAP_MAP_H

#include "common.h"
#include "game/math/math.h"
#include "game/map/collision.h"

struct GfxFrameData;
struct EnvAreaSettings; /* game/env/env.h (h_core) */
struct CameraPresetSet; /* game/camera/camera.h */
struct EffectSprite; /* game/gfx/sprite_effect.h */

/* A placed map object (MapGrid.objs, map_objs). */
typedef struct MapObj {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 angle; /* degrees */
    /* 0x10 */ f32 scale;
    /* 0x14 */ s16 model; /* index into map_obj_models; emitter kinds use it as a timer */
    /* 0x16 */ u16 kind; /* low byte: kind (< 0x10 has collision); 0x1000..0x8000: flags */
} MapObj; /* 0x18 bytes */

/* A map object model: bounds, display list and collision mesh (map_obj_models). */
typedef struct MapModel {
    /* 0x00 */ s16 minX;
    /* 0x02 */ s16 maxX;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 minZ;
    /* 0x0A */ s16 maxZ;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ Gfx *dl;
    /* 0x14 */ CollTri *tris;
    /* 0x18 */ u16 ntris;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ CollVert *verts;
} MapModel; /* 0x20 bytes */

/* A sub-area's object grid: objects by cell, plus a list tested everywhere (map_subarea_grid). */
typedef struct MapGrid {
    /* 0x00 */ u16 count; /* objects in objs */
    /* 0x02 */ u16 alwaysCount;
    /* 0x04 */ s16 w; /* cells */
    /* 0x06 */ s16 h;
    /* 0x08 */ f32 originX;
    /* 0x0C */ f32 originZ;
    /* 0x10 */ f32 cellW;
    /* 0x14 */ f32 cellD;
    /* 0x18 */ MapObj *objs;
    /* 0x1C */ u16 *cells; /* per cell: offset into lists */
    /* 0x20 */ u16 *lists; /* per cell: count, then object indices */
    /* 0x24 */ u16 *alwaysList;
    /* 0x28 */ u16 unk28; /* 0: one list for the whole grid */
    /* 0x2A */ u8 pad2A[2];
} MapGrid; /* 0x2C bytes */

/*
 * A map exit: a box the player walks into (Exit_CheckEnter). Exit_SetDestination (env.c)
 * copies dest[0..2] to exit_destination.unk0..unk8 (next map, next subarea, ...), flags to
 * exit_destination.unkC, unk1A to unk10 and angle to unk14. env.h/env.c (h_core) and
 * collision.c use this one type (env.h used to forward-declare it as struct ExitDef).
 */
typedef struct MapExit {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 angle;
    /* 0x0C */ f32 halfW;
    /* 0x10 */ f32 halfD;
    /* 0x14 */ u16 flags; /* 2: any direction; 0x10/0x20: needs / must not have the item id */
    /* 0x16 */ u16 id;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u16 dest[3]; /* the destination (Exit_SetDestination): next map, next subarea, [2] */
} MapExit; /* 0x24 bytes */

/* A sub-area entry point (MapSubareaDef.entries). */
typedef struct MapEntryPoint {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[4];
} MapEntryPoint; /* 0x14 bytes */

/* One sub-area of a map area (MapAreaDef.subareas, map_subarea_def). */
typedef struct MapSubareaDef {
    /* 0x00 */ u16 grid; /* index into MapAreaDef.grids */
    /* 0x02 */ u16 env; /* index into MapAreaDef.envSettings */
    /* 0x04 */ MapExit *exits;
    /* 0x08 */ s32 exitCount;
    /* 0x0C */ MapEntryPoint *entries;
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 flags; /* copied to map_subarea_flags; bit 1: camera preset follows the player */
    /* 0x16 */ u8 pad16[2];
} MapSubareaDef; /* 0x18 bytes */

/* Two display lists (MapAreaDef.animTexDls, mapobj_animtex_dls). */
typedef struct MapDlPair {
    /* 0x00 */ Gfx *a;
    /* 0x04 */ Gfx *b;
} MapDlPair; /* 0x8 bytes */

/* One map area (map_area_defs entry, map_area_def). */
typedef struct MapAreaDef {
    /* 0x00 */ u16 flags; /* copied to map_flags */
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u32 romStart; /* the area's ROM block, read to dst */
    /* 0x08 */ u32 romEnd;
    /* 0x0C */ void *dst;
    /* 0x10 */ MapModel *models;
    /* 0x14 */ MapGrid *grids;
    /* 0x18 */ MapSubareaDef *subareas;
    /* 0x1C */ struct EnvAreaSettings *envSettings;
    /* 0x20 */ MapDlPair *animTexDls;
    /* 0x24 */ struct CameraPresetSet *cameraPresets; /* per sub-area, or NULL */
    /* 0x28 */ CollWalls *cameraWalls; /* per sub-area */
    /* 0x2C */ CollWalls *actorWalls; /* per sub-area */
    /* 0x30 */ void *unk30; /* battle.c's view */
    /* 0x34 */ void *unk34; /* battle.c's view */
    /* 0x38 */ void *unk38; /* the area's NPC list (npc.c's view) */
    /* 0x3C */ s32 unk3C; /* index into map_extra_rom_ranges */
    /* 0x40 */ u8 pad40[4];
} MapAreaDef; /* 0x44 bytes */

/* A ROM range and its RAM destination (map_extra_rom_ranges). */
typedef struct MapRomRange {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ void *dst;
} MapRomRange; /* 0xC bytes */

/* A backdrop (map_backdrop_defs). */
typedef struct MapBackdropDef {
    /* 0x00 */ u32 start;
    /* 0x04 */ Gfx *dl;
} MapBackdropDef; /* 0x8 bytes */

/* mapobj_spline_out: the first four channels of a Math_EvalTcbSpline result. */
typedef struct MapObjSplineOut {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 w;
} MapObjSplineOut; /* 0x10 bytes */

typedef struct MapObjWaveBase {
    /* 0x00 */ s32 v[6];
} MapObjWaveBase; /* 0x18 bytes */

typedef struct MapObjWavePhase {
    /* 0x00 */ u16 a;
    /* 0x02 */ u16 b;
} MapObjWavePhase; /* 0x4 bytes */

/* map_clock_tlut_schedule entry. */
typedef struct MapClockTlutStep {
    /* 0x00 */ s32 start;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 id;
} MapClockTlutStep; /* 0x8 bytes */

/* .data 8004DD70..8004DED0 */
extern u16 D_8004DD70;
extern s32 mapobj_wave_phase_step[4];
extern s32 D_8004DD84;
extern s32 mapobj_ambient_sfx[4];
extern MapObjWaveBase mapobj_wave_base_init;
extern u16 mapobj_scrolltex_offset;
extern u8 *mapobj_scrolltex_tex[5];
extern u16 mapobj_scrolltex_height[6];
extern f32 mapobj_wave_x_div[4];
extern f32 mapobj_wave_y_div[4];
extern f32 mapobj_wave_z_div[4];
extern u16 mapobj_animtex_width[2];
extern u8 mapobj_animtex_alpha[4];
extern MapClockTlutStep map_clock_tlut_schedule[6];
extern s32 D_8004DEC8;

/* .bss 8007C280..80082030 */
extern u16 map_env_flags; /* bit 0: own light cycle, bit 1: world clock time (Env_*) */
extern u16 map_backdrop_id;
extern MapAreaDef *map_area_def;
extern MapSubareaDef *map_subarea_def;
extern MapGrid *map_subarea_grid;
extern MapObj *map_objs;
extern MapModel *map_obj_models;
extern CollWalls *map_actor_walls;
extern CollWalls *map_camera_walls;
extern s32 D_8007C2A0;
extern s32 mapobj_billboard_count;
extern MapObj *mapobj_billboard_list[0x100];
extern s32 mapobj_spinner_prev_count;
extern s32 mapobj_spinner_count;
extern u8 map_backdrop_tex[0x4000];
extern u16 map_backdrop_tlut[0x100];
extern u8 map_backdrop_phase_tluts[0x800];
extern u16 map_clock_tlut[0x200];
extern u16 map_clock_tlut_srcs[3][0x100];
extern u16 D_80081AB0[0x100];
extern s32 mapobj_opaque_count;
extern s32 mapobj_noanim_count;
extern s32 mapobj_billboard_draw_count;
extern s32 mapobj_translucent_count;
extern s32 mapobj_animtex_count;
extern s32 mapobj_scrolltex_count;
extern MapObj **mapobj_opaque_cursor;
extern MapObj **mapobj_noanim_cursor;
extern MapObj **mapobj_billboard_cursor;
extern MapObj **mapobj_translucent_cursor;
extern MapObj **mapobj_animtex_cursor;
extern MapObj **mapobj_scrolltex_cursor;
extern s32 mapobj_wave_capture;
extern s32 D_80081CE4;
extern MapObjWaveBase mapobj_wave_base[32];
extern MapObj *mapobj_wave_base_cursor;
extern s32 D_80081FEC;
extern f32 mapobj_temp_vec[2];
extern s32 D_80081FF8[2];
extern CollResult map_load_coll;
extern s32 D_8008201C;
extern MapObjSplineOut mapobj_spline_out;

/* .bss 80082030..80082860 */
extern u8 D_80082030[0x18];
extern MapObjWavePhase mapobj_wave_phase[4];
extern u16 mapobj_opaque_list[0x200];
extern u16 mapobj_noanim_list[0x200];

/* The types of the last .bss run are declared here, between the runs: the gap in declaration
 * numbers is where map.c's function static map_clock_blend_len (80082858) sorts (IDO orders
 * .bss by declaration number mod 256). */
/* A spinning object queued by MapObj_QueueSpinner (mapobj_spinner_buf0/1). */
typedef struct MapObjSpinner {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ MapObj *obj;
} MapObjSpinner; /* 0x1C bytes */

/* An animated-object slot (mapobj_anim_slots, MapObjAnim_*). */
typedef struct MapObjAnimSlot {
    /* 0x00 */ s32 timer;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 frame;
    /* 0x0C */ s32 type;
    /* 0x10 */ MapObj *obj; /* the object it moves (MapObj_UpdateAndDrawNearby looks it up) */
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 z;
} MapObjAnimSlot; /* 0x1C bytes */

/* .bss 80082860..800842F0 */
extern MapObj *mapobj_translucent_list[0x100];
extern MapObj *mapobj_animtex_list[0x100];
extern u16 *map_clock_blend_from;
extern MapObj *mapobj_scrolltex_list[0x100];
extern u16 *map_clock_blend_to;
extern MapObjSpinner mapobj_spinner_buf1[8];
extern u16 *map_clock_blend_out;
extern MapObjSpinner mapobj_spinner_buf0[8];
extern Vec3f mapobj_billboard_normals[0x100];
extern MapObjAnimSlot mapobj_anim_slots[4];
extern u16 mapobj_arc_flicker_tick;
extern f32 mapobj_ambient_dist;
extern s32 mapobj_ambient_type;
extern s32 mapobj_ambient_prev_type;
extern u16 map_flags;
extern s32 map_id;
extern s32 map_subarea;
extern s32 map_next_id;
extern s32 map_next_subarea;
extern s32 D_800842CC;
extern s32 map_flag4_return_map;
extern s32 map_flag4_return_subarea;
extern s32 map_flag4_return_entry;
extern s32 map_flag8_return_map;
extern s32 map_flag8_return_subarea;
extern s32 map_flag8_return_entry;
extern u16 map_subarea_flags; /* bit 0: enemy area (enemy set, random encounters, no NPCs) */

void Map_LoadArea(void);
void Map_StartFrame(void);
void MapObj_UpdateAndDrawNearby(struct GfxFrameData *arg0);
void MapObj_DrawTranslucent(struct GfxFrameData *arg0);
void MapObj_CollectCell(s32 count, u16 *ids);
void Map_DrawBackdrop(struct GfxFrameData *arg0);
void MapObjAnim_ClearAll(void);
s32 MapObjAnim_Find(MapObj *obj);
void MapObjAnim_Start(s32 state, s32 frame, s32 type, MapObj *obj);
void MapObjAnim_UpdateAll(void);
void MapObj_DrawBillboards(struct GfxFrameData *arg0, s32 count, s32 type, MapObj **list);
void MapObj_EmitArcSprite(MapObj *arg0);
void MapObj_StepArcSprite(struct EffectSprite *arg0);
void MapObj_EmitDropSprite(MapObj *arg0);
void MapObj_StepDropSprite(struct EffectSprite *arg0);
void MapObj_ClearSpinners(void);
void MapObj_QueueSpinner(f32 arg0, f32 arg1, f32 arg2, f32 arg3, MapObj *arg4);
void MapObj_DrawSpinners(struct GfxFrameData *arg0);
void MapObj_DrawAnimTexBillboards(struct GfxFrameData *arg0, s32 count, s32 type, MapObj **list);
void Map_BlendPaletteByClock(void);
void func_80010768(void);

#endif
