#include "common.h"

/*
 * Field map: area loading (ROM blocks, area/sub-area tables, map objects), drawing the
 * map objects in the grid cells around the camera (opaque, translucent, billboards,
 * spinning and texture-animated objects, sprite emitters), animated-object slots,
 * the nearest ambient sound, colour-table blends/cycles.
 * Folder: src/game/map/   (proposed for round 4)
 */

typedef struct {
    /* 0x00 */ s32 timer;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 frame;
    /* 0x0C */ s32 type;
    /* 0x10 */ s32 id;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 z;
} Unk80084238; /* size 0x1C */

typedef struct {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
} AnimInfo;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 w;
} Unk80082020;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ struct Unk8000FA9C *unk18;
} Unk80083470; /* size 0x1C */

typedef struct Unk8000FA9C {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 scale;
    /* 0x14 */ s16 timer;
    /* 0x16 */ u16 unk16;
} Unk8000FA9C;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

/* Part of this file's .bss, 80082860..800842F0 (the run 80082030..80082860
 * comes first: see D_80082030). These objects are declared here, before the
 * file's 256th declaration, and IDO emits the later declaration block (with
 * D_80082030..map_clock_blend_len) first. */
Unk8000FA9C *mapobj_translucent_list[0x100];
Unk8000FA9C *mapobj_animtex_list[0x100];
u16 *map_clock_blend_from;
Unk8000FA9C *mapobj_scrolltex_list[0x100];
u16 *map_clock_blend_to;
Unk80083470 mapobj_spinner_buf1[8];
u16 *map_clock_blend_out;
Unk80083470 mapobj_spinner_buf0[8];
Vec3f mapobj_billboard_normals[0x100];
Unk80084238 mapobj_anim_slots[4];
u16 mapobj_arc_flicker_tick;
f32 mapobj_ambient_dist;
s32 mapobj_ambient_type;
s32 mapobj_ambient_prev_type;
u16 map_flags;
s32 map_id;
s32 map_subarea;
s32 map_next_id;
s32 map_next_subarea;
s32 D_800842CC;
s32 map_flag4_return_map;
s32 map_flag4_return_subarea;
s32 map_flag4_return_entry;
s32 map_flag8_return_map;
s32 map_flag8_return_subarea;
s32 map_flag8_return_entry;
u16 map_subarea_flags; /* bit 0: enemy area (enemy set, random encounters, no NPCs) */

typedef struct {
    /* 0x00 */ u16 alpha;
    /* 0x02 */ u8 pad2[0x16];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ u8 pad24[0xC];
    /* 0x30 */ f32 vx;
    /* 0x34 */ f32 vy;
    /* 0x38 */ f32 vz;
} Particle;

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ u8 *unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 unk3C;
} SpriteObj; /* size 0x40 */

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ u8 pad18[0x14];
    /* 0x2C */ f32 angle;
} Unk80085E48;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ s32 unk1C;
} Unk80084994; /* size 0x20 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ Gfx *dl;
} Unk80060C48;

typedef struct {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0x0C */ Mtx mtx[1];
} MtxBuf;

u32 Math_Rand(u32);
void Math_EvalTcbSpline(AnimInfo *, Unk80082020 *, s32);
void Math_RotateVec2(f32, f32 *);
void Effect_AllocateSprite(SpriteObj *);
void Math_MtxRotScaleTrans(Mtx *, f32, f32, f32, f32, f32, f32, f32);

extern AnimInfo mapobjanim_type23_anim;
extern AnimInfo mapobjanim_type23_odd_anim;
extern AnimInfo mapobjanim_type4_anim;
extern s32 gfx_frame_index;
extern Gfx *gfx_dl_head;

extern u8 mapobj_arc_sprite_tex[];
extern u16 D_80124E00[];
extern s32 gfx_mtx_index;
extern Unk80085E48 camera_state;
extern s32 D_80084B60;
extern s32 D_80084B64;
extern s32 D_80084B68;
extern Unk80084994 *env_area_settings;
extern Unk80060C48 map_backdrop_defs[];
extern MtxBuf D_2000000;

typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ Gfx *dl;
    /* 0x14 */ u8 pad14[0xC];
} Unk8007C294; /* size 0x20 */


typedef struct {
    /* 0x00 */ Gfx *a;
    /* 0x04 */ Gfx *b;
} Unk8005E518;

extern Unk8005E518 D_8005E51C[];
extern Unk8005E518 mapobj_animtex_dls[];

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 pad10[4];
} Unk8007C288C; /* size 0x14 */

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ Unk8007C288C *unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[2];
} Unk8007C288; /* size 0x18 */

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
    /* 0x08 */ f32 originX;
    /* 0x0C */ f32 originZ;
    /* 0x10 */ f32 cellW;
    /* 0x14 */ f32 cellD;
    /* 0x18 */ Unk8000FA9C *objs;
    /* 0x1C */ u16 *cells;
    /* 0x20 */ u16 *lists;
    /* 0x24 */ u16 *unk24;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u8 pad2A[2];
} Unk8007C28C; /* size 0x2C */

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u32 romStart;
    /* 0x08 */ u32 romEnd;
    /* 0x0C */ void *dst;
    /* 0x10 */ Unk8007C294 *unk10;
    /* 0x14 */ Unk8007C28C *unk14;
    /* 0x18 */ Unk8007C288 *unk18;
    /* 0x1C */ Unk80084994 *unk1C;
    /* 0x20 */ Unk8005E518 *unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 pad30[0xC];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 pad40[4];
} Unk8007C284; /* size 0x44 */

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ void *dst;
} Unk80057540; /* size 0xC */

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 nx;
    /* 0x10 */ f32 ny;
    /* 0x14 */ f32 nz;
    /* 0x18 */ u16 flags;
} CollResult;

typedef struct {
    /* 0x00 */ s32 v[6];
} Unk8004DD98; /* size 0x18 */

/* This file's .bss starts here: 8007C280..80082030 in address order, then
 * D_80082030.. below. mapobj_billboard_list is a pointer table other files use.
 * D_80081CE4, D_80081FEC, D_80081FF8 and D_8008201C are
 * unreferenced. Splat's labels inside D_80081AB0 (D_80081B78..D_80081C42) and
 * mapobj_wave_base (D_80081D00..D_80081D30) are aliases in undefined_syms.txt. */
u16 map_env_flags; /* bit 0: own light cycle, bit 1: world clock time (Env_*) */
u16 map_backdrop_id;
Unk8007C284 *map_area_def;
Unk8007C288 *map_subarea_def;
Unk8007C28C *map_subarea_grid;
Unk8000FA9C *map_objs;
Unk8007C294 *map_obj_models;
s32 map_actor_walls;
s32 map_camera_walls;
s32 D_8007C2A0;
s32 mapobj_billboard_count;
void *mapobj_billboard_list[0x100];
s32 mapobj_spinner_prev_count;
s32 mapobj_spinner_count;
u8 map_backdrop_tex[0x4000];
u16 map_backdrop_tlut[0x100];
u8 map_backdrop_phase_tluts[0x800];
u16 map_clock_tlut[0x200];
u16 map_clock_tlut_srcs[3][0x100];
u16 D_80081AB0[0x100];
s32 mapobj_opaque_count;
s32 mapobj_noanim_count;
s32 mapobj_billboard_draw_count;
s32 mapobj_translucent_count;
s32 mapobj_animtex_count;
s32 mapobj_scrolltex_count;
Unk8000FA9C **mapobj_opaque_cursor;
Unk8000FA9C **mapobj_noanim_cursor;
Unk8000FA9C **mapobj_billboard_cursor;
Unk8000FA9C **mapobj_translucent_cursor;
Unk8000FA9C **mapobj_animtex_cursor;
Unk8000FA9C **mapobj_scrolltex_cursor;
s32 mapobj_wave_capture;
s32 D_80081CE4;
Unk8004DD98 mapobj_wave_base[32];
Unk8000FA9C *mapobj_wave_base_cursor;
s32 D_80081FEC;
f32 mapobj_temp_vec[2];
s32 D_80081FF8[2];
CollResult map_load_coll;
s32 D_8008201C;
Unk80082020 mapobj_spline_out;

void Dma_ReadRom();
void MapObjAnim_ClearAll(void);
void MapObj_ClearSpinners(void);
void Coll_ResolveFloorAndWalls(f32, f32, f32, u16, CollResult *);
extern Unk8007C284 map_area_defs[];
extern Unk80057540 map_extra_rom_ranges[];
extern s32 D_80084308;
extern f32 player_spawn_x;
extern f32 player_spawn_z;
extern f32 player_spawn_rot;
extern s32 player_spawn_obj;
extern u16 D_80081B78[];
extern u16 D_80081B7A[];
extern u8 D_753F0[];
extern u8 D_851F0[];
/* Same address as D_851F0: the end of the ROM block that starts at D_753F0 (a separate linker symbol in the original). */
extern u8 D_851F0_end[];
extern u8 D_C8DE0[];
extern u8 D_D86170[];
extern u8 D_D86770[];
extern u8 D_3E1090[];
extern u8 D_3F1BA0[];
extern u8 D_80100000[];
extern u8 D_8010FE00[];
extern u8 D_801E0000[];



typedef struct {
    /* 0x00 */ u16 a;
    /* 0x02 */ u16 b;
} Unk80082048;

extern u8 mapobj_translucent_alpha[];
void MapObj_DrawAnimTexBillboards(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list);
/* The rest of this file's .bss, 80082030..80082860 (the 16-byte-aligned run that
 * holds Map_BlendPaletteByClock's static at 80082858). Nothing names 80082030..80082048
 * (splat's D_80082030 is Map_LoadArea's loop end), so it is a placeholder. */
u8 D_80082030[0x18];
Unk80082048 mapobj_wave_phase[4];
u16 mapobj_opaque_list[0x200];
u16 mapobj_noanim_list[0x200];
/* Declared after the definitions above: IDO orders a file's .bss by declaration
 * number mod 256 (later blocks first on a tie), and these declarations keep
 * Map_BlendPaletteByClock's static map_clock_blend_len after mapobj_noanim_list. */
typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
} Unk8007AA08;
extern Unk8007AA08 player_state;
void Effect_QueueMapObjEmitter(f32, f32, f32, Unk8000FA9C *);
void MapObj_EmitArcSprite(Unk8000FA9C *);
void MapObj_EmitDropSprite(Unk8000FA9C *);
void MapObj_QueueSpinner(f32, f32, f32, f32, Unk8000FA9C *);
extern f32 camera_fovy;
f32 sqrtf(f32);
f32 Math_Atan2(f32, f32);
void Math_MtxFRotScaleTrans(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32);
void guMtxF2L(f32 (*)[4], Mtx *);
void Shadow_Queue(f32, f32, f32, f32, f32, f32, f32);
extern u8 **D_8005E5AC[];
extern f32 D_80085E74;

typedef struct {
    /* 0x00 */ s32 start;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 id;
} Unk8004DE98; /* size 0x8 */

extern s32 env_clock;

/* This file's .data, 8004DD70..8004DED0, in source order: these tables, then
 * the static sprite descriptors of MapObj_EmitArcSprite (8004DE04) and MapObj_EmitDropSprite
 * (8004DE44), then the tables defined after MapObj_EmitDropSprite. IDO stores a
 * function-static descriptor's fields with lui/%lo (sharing the lui inside a
 * 16-byte line), which both functions need. D_8004DD8B (MapObj_UpdateAndDrawNearby's asm
 * name for mapobj_ambient_sfx + 3) is an alias in undefined_syms.txt. */
u16 D_8004DD70 = 0;
s32 mapobj_wave_phase_step[4] = { 0x00000000, 0x01600160, 0x01600160, 0x01600100 };
s32 D_8004DD84 = 0x00500050;
s32 mapobj_ambient_sfx[4] = { 0x19, 0x1B, 0x1E, 0x20 };
Unk8004DD98 mapobj_wave_base_init = { { 0 } };
u16 mapobj_scrolltex_offset = 0;
u8 *mapobj_scrolltex_tex[5] = {
    (u8 *)0x801093B0, (u8 *)0x8010A3B0, (u8 *)0x80129D10, (u8 *)0x80160B30, (u8 *)0x8014DA40,
};
u16 mapobj_scrolltex_height[6] = { 0x40, 0x40, 0x20, 0x40, 0x20, 0 };
f32 mapobj_wave_x_div[4] = { 0.0f, 5000.0f, 1000.0f, 3000.0f };
f32 mapobj_wave_y_div[4] = { 0.0f, 30000.0f, 30000.0f, 48000.0f };
f32 mapobj_wave_z_div[4] = { 0.0f, 1000.0f, 5000.0f, 3000.0f };

void Map_LoadArea(void) {
    u32 *q;
    u32 start;
    u32 end;
    u16 *src;
    u16 *dst;
    s32 i;
    Unk8007C288C *sp;
    u32 n;
    Unk8000FA9C *s;
    Vec3f *v;
    s32 k;
    s32 kind;
    Unk80082048 *z;

    map_area_def = &map_area_defs[map_next_id];
    if (map_id != -1) {
        if (map_next_id == 11) {
            if (map_subarea == 2 && map_next_subarea == 0) {
                map_flag4_return_map = map_next_id;
                map_flag4_return_subarea = map_next_subarea;
                map_flag4_return_entry = D_80084308;
            }
        } else if (map_next_id == 6) {
            map_flag4_return_map = map_next_id;
            map_flag4_return_subarea = map_next_subarea;
            map_flag4_return_entry = D_80084308;
        } else if ((map_flags & 1) && (map_area_def->flags & 4)) {
            map_flag4_return_map = map_next_id;
            map_flag4_return_subarea = map_next_subarea;
            map_flag4_return_entry = D_80084308;
        } else if (map_next_id != map_id && (map_area_def->flags & 8)) {
            map_flag8_return_map = map_next_id;
            map_flag8_return_subarea = map_next_subarea;
            map_flag8_return_entry = D_80084308;
            if (map_flag8_return_map == 0x1A && map_flag8_return_subarea == 4) {
                map_flag8_return_subarea = 2;
                map_flag8_return_entry = 1;
            }
        }
    }
    if (map_id == -1) {
        Dma_ReadRom(D_753F0, D_80100000, D_851F0_end - D_753F0);
        Dma_ReadRom(D_D86170, map_clock_tlut_srcs, 0x600);
        Dma_ReadRom(D_D86770, D_80081AB0, 0x200);
    }
    if (map_id != map_next_id) {
        D_800842CC = map_id;
        map_id = map_next_id;
        map_flags = map_area_def->flags;
        if (map_flags & 7) {
            if (map_flags & 2) {
                Dma_ReadRom(D_851F0, D_8010FE00, D_C8DE0 - D_851F0);
            }
            q = &((u32 *)map_extra_rom_ranges)[map_area_def->unk3C * 3];
            start = *q++;
            end = *q++;
            Dma_ReadRom(start, *q, end - start);
        }
        Dma_ReadRom(map_area_def->romStart, map_area_def->dst, map_area_def->romEnd - map_area_def->romStart);
        switch (map_id) {
            case 3:
            case 5:
            case 7:
            case 12:
                Dma_ReadRom(D_3E1090, D_801E0000, D_3F1BA0 - D_3E1090);
                break;
        }
    }
    n = 0x65;
    src = D_80081B78;
    dst = D_80081B7A;
    do {
        *dst++ = *src--;
        n--;
    } while (n != 0);
    k = map_subarea = map_next_subarea;
    map_subarea_def = &map_area_def->unk18[k];
    map_obj_models = map_area_def->unk10;
    map_subarea_grid = &map_area_def->unk14[map_subarea_def->unk0];
    env_area_settings = &map_area_def->unk1C[map_subarea_def->unk2];
    map_objs = map_subarea_grid->objs;
    map_actor_walls = map_area_def->unk2C;
    map_camera_walls = map_area_def->unk28;
    map_subarea_flags = map_subarea_def->unk14;
    map_env_flags = env_area_settings->unk18;
    if (map_backdrop_id != env_area_settings->unk1C) {
        map_backdrop_id = env_area_settings->unk1C;
        Dma_ReadRom(map_backdrop_defs[map_backdrop_id].start, map_backdrop_phase_tluts, 0x800);
        Dma_ReadRom(map_backdrop_defs[map_backdrop_id].start + 0x800, map_backdrop_tex, 0x4000);
    }
    if (D_80084308 != -1) {
        sp = &map_subarea_def->unkC[D_80084308];
        player_spawn_x = sp->x;
        player_spawn_z = sp->y;
        player_spawn_rot = sp->z;
        player_spawn_obj = sp->unkE;
    }
    n = map_subarea_grid->count;
    s = map_objs;
    mapobj_billboard_count = k = 0;
    v = mapobj_billboard_normals;
    for (; n != 0; n--, s++) {
        if (s->unk16 & 0x8000) {
            Coll_ResolveFloorAndWalls(s->x, s->y, s->z, 0xA00, &map_load_coll);
            s->y = map_load_coll.y;
        }
        kind = s->unk16 & 0xFF;
        if (kind == 0x10) {
            v->x = map_load_coll.nx;
            v->y = map_load_coll.ny;
            v->z = map_load_coll.nz;
            s->angle = k++;
            v++;
        } else if (kind == 0x83) {
            s->timer = 0;
        } else if (kind == 0x84) {
            s->timer = Math_Rand(150) + 150;
        } else if (s->unk16 >= 0x11 && s->unk16 < 0x15) {
            s->timer = Math_Rand(16);
        }
    }
    for (z = mapobj_wave_phase; z < &mapobj_wave_phase[4]; z++) {
        z->a = 0;
        z->b = 0;
    }
    for (i = 0; i < 32; i++) {
        mapobj_wave_base[i] = mapobj_wave_base_init;
    }
    mapobj_wave_capture = 1;
    MapObjAnim_ClearAll();
    MapObj_ClearSpinners();
    mapobj_ambient_prev_type = -1;
}

void Map_StartFrame(void) {
    s32 i;
    s32 tmp;
    u16 *p;

    mapobj_spinner_count = 0;
    if (map_id == 0x1D) {
        i = 18; p = D_80124E00 + i; tmp = *p;
        for (; i != 0; i--, p--) { *p = *(p - 1); }
        *p = tmp;
        mapobj_arc_flicker_tick++;
    }
}

#ifdef NON_MATCHING
typedef struct {
    /* 0x00 */ s8 dx;
    /* 0x01 */ s8 dz;
} CellOffset;

typedef struct {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u8 pad8[0x18];
} AnimInfo20; /* size 0x20 */

extern CellOffset mapobj_cell_single[];
extern CellOffset mapobj_cell_disc_r7[];
extern CellOffset mapobj_cell_disc_r5[];
extern CellOffset mapobj_cell_square_3x3[];
extern CellOffset mapobj_cell_disc_r2[];
extern AnimInfo20 mapobj_loop_anims[];
extern Gfx D_10000E8[];
extern s16 gfx_fog_near;
extern s16 gfx_fog_far;
void MapObj_CollectCell(s32, u16 *);
void MapObj_DrawSpinners(MtxBuf *);
void Map_BlendPaletteByClock(void);
void func_80010768(void);
void Sfx_StopChannel4(void);
void Sfx_PlayIfAudible(s8, u8);
s32 MapObjAnim_Find(s32);
void MapObj_DrawBillboards(MtxBuf *, s32, s32, Unk8000FA9C **);

/* &mapobj_opaque_list kept in a saved register instead of rematerialized, 8 bytes short, register allocation; code is equivalent */
void MapObj_UpdateAndDrawNearby(MtxBuf *arg0) {
    CellOffset *off;
    s32 n;
    s32 cx;
    s32 cz;
    s32 gx;
    s32 gz;
    s32 idx;
    u16 *list;
    u16 t;
    f32 px;
    f32 pz;
    Unk8000FA9C *s;
    u16 flags;
    f32 x;
    f32 y;
    f32 z;
    f32 rot;
    AnimInfo20 *anim;
    s32 i;
    Unk80082048 *a;
    Unk80082048 *b;
    f64 d;
    s32 k;
    s32 *pCB4 = &mapobj_noanim_count;
    s32 *pCB8 = &mapobj_billboard_draw_count;
    Unk8000FA9C ***pCD0 = &mapobj_billboard_cursor;
    f32 *pAC = &mapobj_ambient_dist;
    s32 *pB0 = &mapobj_ambient_type;

    *pCB4 = 0;
    mapobj_opaque_count = 0;
    *pCB8 = 0;
    mapobj_translucent_count = 0;
    mapobj_animtex_count = 0;
    mapobj_scrolltex_count = 0;
    mapobj_billboard_count = 0;
    mapobj_opaque_cursor = (Unk8000FA9C **) mapobj_opaque_list;
    mapobj_noanim_cursor = (Unk8000FA9C **) mapobj_noanim_list;
    *pCD0 = (Unk8000FA9C **) mapobj_billboard_list;
    mapobj_translucent_cursor = mapobj_translucent_list;
    mapobj_animtex_cursor = mapobj_animtex_list;
    mapobj_scrolltex_cursor = mapobj_scrolltex_list;
    mapobj_wave_base_cursor = (Unk8000FA9C *) mapobj_wave_base;
    *pAC = 600.0f;
    *pB0 = -1;
    px = camera_state.x;
    pz = camera_state.z;
    switch (map_subarea_grid->unk28) {
        case 1:
            off = mapobj_cell_disc_r7;
            n = 0x9D;
            cx = (px - map_subarea_grid->originX) / map_subarea_grid->cellW;
            cz = (pz - map_subarea_grid->originZ) / map_subarea_grid->cellD;
            break;
        case 2:
            off = mapobj_cell_disc_r5;
            n = 0x59;
            cx = (px - map_subarea_grid->originX) / map_subarea_grid->cellW;
            cz = (pz - map_subarea_grid->originZ) / map_subarea_grid->cellD;
            break;
        case 3:
            off = mapobj_cell_square_3x3;
            n = 9;
            cx = (px - map_subarea_grid->originX) / map_subarea_grid->cellW;
            cz = (pz - map_subarea_grid->originZ) / map_subarea_grid->cellD;
            break;
        case 4:
            off = mapobj_cell_disc_r2;
            n = 0x15;
            cx = (px - map_subarea_grid->originX) / map_subarea_grid->cellW;
            cz = (pz - map_subarea_grid->originZ) / map_subarea_grid->cellD;
            break;
        default:
            off = mapobj_cell_single;
            cx = 0;
            cz = 0;
            n = 1;
            break;
    }
    for (; n != 0; n--) {
        gx = off->dx + cx;
        gz = off->dz + cz;
        off++;
        if (gx >= 0 && gz >= 0 && gx < map_subarea_grid->w && gz < map_subarea_grid->h) {
            idx = map_subarea_grid->w * gz + gx;
            list = &map_subarea_grid->lists[map_subarea_grid->cells[idx]];
            t = *list;
            MapObj_CollectCell(t, list + 1);
        }
    }
    if (map_subarea_grid->unk2 != 0) {
        t = map_subarea_grid->unk2;
        MapObj_CollectCell(t, map_subarea_grid->unk24);
    }
    gSPDisplayList(gfx_dl_head++, D_10000E8);
    gSPFogPosition(gfx_dl_head++, gfx_fog_near, gfx_fog_far);
    D_8007C2A0 = 0;
    mapobj_opaque_cursor = (Unk8000FA9C **) mapobj_opaque_list;
    for (n = mapobj_opaque_count; n != 0; n--) {
        s = *mapobj_opaque_cursor++;
        flags = s->unk16;
        x = s->x;
        y = s->y;
        z = s->z;
        rot = s->angle;
        if (flags & 0x2000) {
            anim = &mapobj_loop_anims[(flags & 0xF00) >> 8];
            t = flags;
            t = (t & 0xFF) + 1;
            Math_EvalTcbSpline((AnimInfo *) anim, &mapobj_spline_out, flags & 0xFF);
            x += mapobj_spline_out.x * s->scale;
            y += mapobj_spline_out.y * s->scale;
            z += mapobj_spline_out.z * s->scale;
            flags = t;
            if (t >= anim->unk6) {
                flags = 0;
            }
            s->unk16 = (s->unk16 & 0xFF00) | flags;
        } else if (flags & 0x100) {
            i = MapObjAnim_Find((s32) s);
            if (i != 0) {
                mapobj_temp_vec[1] = 0.0f;
                mapobj_temp_vec[0] = mapobj_anim_slots[i - 1].x;
                Math_RotateVec2(s->angle * 0.017453292519943295, mapobj_temp_vec);
                x -= mapobj_temp_vec[0];
                z -= mapobj_temp_vec[1];
                rot += mapobj_anim_slots[i - 1].z;
            }
        }
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, rot, 0.0f, s->scale, x, y, z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gSPDisplayList(gfx_dl_head++, map_obj_models[s->timer].dl);
        D_8007C2A0++;
    }
    mapobj_opaque_cursor = (Unk8000FA9C **) mapobj_noanim_list;
    for (n = *pCB4; n != 0; n--) {
        s = *mapobj_opaque_cursor++;
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, s->angle, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gSPDisplayList(gfx_dl_head++, map_obj_models[s->timer].dl);
        D_8007C2A0++;
    }
    MapObj_DrawSpinners(arg0);
    if (*pCB8 != 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0xC8113078, 0);
        *pCD0 = (Unk8000FA9C **) mapobj_billboard_list;
        MapObj_DrawBillboards(arg0, *pCB8, 0, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 1, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 2, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 3, *pCD0);
    }
    gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    /* mapobj_wave_phase_step is read as four u16 pairs */
    a = mapobj_wave_phase;
    b = (Unk80082048 *) mapobj_wave_phase_step;
    for (;;) {
        u16 ta = a->a + b->a;
        u16 tb = a->b + b->b;
        b++;
        k = b < ((Unk80082048 *) mapobj_wave_phase_step) + 4;
        a++;
        a[-1].a = ta;
        a[-1].b = tb;
        if (!k) {
            break;
        }
    }
    mapobj_wave_capture = 0;
    Map_BlendPaletteByClock();
    func_80010768();
    if (mapobj_ambient_type == -1) {
        if (mapobj_ambient_prev_type != mapobj_ambient_type) {
            Sfx_StopChannel4();
        }
    } else {
        d = mapobj_ambient_dist;
        if (d > 200.0) {
            n = (600.0 - d) * 0.6375;
        } else {
            n = 0xFF;
        }
        if (n >= 2) {
            /* retail reads the low (last) byte of the word: lb mapobj_ambient_sfx + 4 * i + 3 */
            Sfx_PlayIfAudible((s8) mapobj_ambient_sfx[mapobj_ambient_type], n);
        } else {
            Sfx_StopChannel4();
            mapobj_ambient_type = mapobj_ambient_prev_type = -1;
        }
    }
    mapobj_ambient_prev_type = mapobj_ambient_type;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/E2A0/MapObj_UpdateAndDrawNearby.s")
#endif

void MapObj_DrawTranslucent(MtxBuf *arg0) {
    Unk8000FA9C *s;
    s32 n;
    s32 k;
    s16 idx;
    s32 t;
    f32 rot;

    mapobj_translucent_cursor = mapobj_translucent_list;
    n = mapobj_translucent_count;
    if (n != 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0x0C1849D8, 0);
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, mapobj_translucent_alpha[map_id]);
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
    }
    for (; n != 0; n--) {
        s = *mapobj_translucent_cursor++;
        idx = s->timer;
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, s->angle, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gSPDisplayList(gfx_dl_head++, map_obj_models[idx].dl);
        D_8007C2A0++;
    }
    if (mapobj_scrolltex_count != 0) {
        gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, mapobj_translucent_alpha[map_id]);
        gDPSetRenderMode(gfx_dl_head++, 0xC81049D8, 0);
        gDPSetCombine(gfx_dl_head++, 0x121A04, 0xFFFFFFF8);
    }
    mapobj_scrolltex_cursor = mapobj_scrolltex_list;
    n = mapobj_scrolltex_count;
    for (; n != 0; n--) {
        s = *mapobj_scrolltex_cursor++;
        rot = s->angle;
        k = (s->unk16 & 0xFF) - 0x40;
        idx = s->timer;
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, rot, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gDPLoadTextureTile(gfx_dl_head++, mapobj_scrolltex_tex[k], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, mapobj_scrolltex_height[k], 0, 0, 31,
                           mapobj_scrolltex_height[k] - 1, 0, G_TX_WRAP, G_TX_WRAP, 5, (mapobj_scrolltex_height[k] == 32) ? 5 : 6, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx_dl_head++, G_TX_RENDERTILE, 0, (t = mapobj_scrolltex_offset % 256) << 2, 32 << 2, (mapobj_scrolltex_height[k] + t) << 2);
        gSPDisplayList(gfx_dl_head++, map_obj_models[idx].dl);
        D_8007C2A0++;
    }
    if (mapobj_animtex_count != 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0x0C1849D8, 0);
        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
        mapobj_animtex_cursor = mapobj_animtex_list;
        MapObj_DrawAnimTexBillboards(arg0, mapobj_animtex_count, 0x11, mapobj_animtex_cursor);
        MapObj_DrawAnimTexBillboards(arg0, mapobj_animtex_count, 0x12, mapobj_animtex_cursor);
    }
    D_8004DD70++;
    gDPPipeSync(gfx_dl_head++);
    gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    mapobj_scrolltex_offset += 2;
}

void MapObj_CollectCell(s32 count, u16 *ids) {
    Unk8000FA9C *s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    u16 kind;

    for (; count != 0; count--) {
        s = &map_objs[*ids++];
        if (s->unk16 & 0x1000) {
            dx = s->x - player_state.x;
            dy = s->y - player_state.y;
            dz = s->z - player_state.z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            if (d < mapobj_ambient_dist) {
                mapobj_ambient_dist = d;
                mapobj_ambient_type = (s->unk16 & 0xF00) >> 8;
            }
        }
        kind = s->unk16;
        if (s->unk16 & 0x2000) {
            kind = 0;
        } else {
            kind = (u8)kind;
        }
        if (!kind || kind == 8) {
            if (s->unk16 & 0x4000) {
                *mapobj_noanim_cursor++ = s;
                mapobj_noanim_count++;
            } else {
                *mapobj_opaque_cursor++ = s;
                mapobj_opaque_count++;
            }
        } else if (kind < 4) {
            if (mapobj_wave_capture != 0) {
                *mapobj_wave_base_cursor = *s;
            }
            s->x = sins(mapobj_wave_phase[kind].a + 0xA000) / mapobj_wave_x_div[kind] + mapobj_wave_base_cursor->x;
            s->z = sins(mapobj_wave_phase[kind].a + 0x2000) / mapobj_wave_z_div[kind] + mapobj_wave_base_cursor->z;
            s->y = sins(mapobj_wave_phase[kind].b) / mapobj_wave_y_div[kind] + mapobj_wave_base_cursor->y;
            *mapobj_translucent_cursor++ = s;
            mapobj_translucent_count++;
            mapobj_wave_base_cursor++;
        } else if (kind == 0x11 || kind == 0x12) {
            *mapobj_animtex_cursor++ = s;
            mapobj_animtex_count++;
        } else if (kind == 0x10) {
            *mapobj_billboard_cursor++ = s;
            mapobj_billboard_draw_count++;
            mapobj_billboard_count++;
        } else if (kind == 0x7F || kind == 0x80) {
            *mapobj_translucent_cursor++ = s;
            mapobj_translucent_count++;
        } else if (kind == 0x81) {
            Effect_QueueMapObjEmitter(s->x, s->y, s->z, s);
        } else if (kind == 0x83) {
            MapObj_EmitArcSprite(s);
        } else if (kind == 0x84) {
            MapObj_EmitDropSprite(s);
        } else if (kind == 0x82) {
            MapObj_QueueSpinner(s->x, s->y, s->z, s->angle, s);
        } else if (kind >= 0x40 && kind < 0x46) {
            *mapobj_scrolltex_cursor++ = s;
            mapobj_scrolltex_count++;
        }
    }
}

void Map_DrawBackdrop(MtxBuf *arg0) {
    Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, 0.0f, 0.0f, 1.0f, camera_state.x, camera_state.y - 10.0f, camera_state.z);
    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
    gfx_mtx_index++;
    gDPSetEnvColor(gfx_dl_head++, D_80084B60, D_80084B64, D_80084B68, 255);
    gSPDisplayList(gfx_dl_head++, map_backdrop_defs[env_area_settings->unk1C].dl);
}

void MapObjAnim_ClearAll(void) {
    Unk80084238 *p = mapobj_anim_slots;
    u32 i = 4;

    while (i--) {
        p->timer = 0;
        p++;
    }
}

s32 MapObjAnim_Find(s32 id) {
    Unk80084238 *p;
    s32 i;

    i = 4;
    p = mapobj_anim_slots;
    for (; i != 0; i--, p++) {
        if (p->timer != 0 && id == p->id) {
            i = 5 - i;
            break;
        }
    }
    return i;
}

void MapObjAnim_Start(s32 state, s32 frame, s32 type, s32 id) {
    Unk80084238 *p;
    s32 i;
    AnimInfo *anim;

    i = 3;
    p = mapobj_anim_slots;
    // mapobj_anim_slots[0].timer, read through the preceding array so IDO does not share its address with p
    if (*(s32 *)&mapobj_billboard_normals[256] != 0) {
        do {
            i--;
            p++;
            if (i == 0) {
                break;
            }
        } while (p->timer != 0);
    }
    p->state = state;
    p->frame = frame;
    p->type = type;
    p->id = id;
    p->z = 0.0f;
    p->x = 0.0f;
    if (state != 0) {
        switch ((type >> 8) & 0xF) {
            case 2:
            case 3:
                if (p->type & 1) {
                    anim = &mapobjanim_type23_odd_anim;
                } else {
                    anim = &mapobjanim_type23_anim;
                }
                break;
            case 4:
                anim = &mapobjanim_type4_anim;
                break;
        }
        p->timer = anim->unk6 - frame + 1;
    } else {
        p->timer = 7;
    }
}

void MapObjAnim_UpdateAll(void) {
    Unk80084238 *p;
    s32 i;
    AnimInfo *anim;

    i = 4;
    p = mapobj_anim_slots;
    do {
        if (p->timer != 0) {
            switch (p->state) {
                case 0:
                    if (--p->timer == 0) {
                        p->timer = 80;
                        p->state++;
                    }
                    break;
                case 1:
                    p->timer--;
                    switch ((p->type >> 8) & 0xF) {
                        case 2:
                        case 3:
                            if (p->type & 1) {
                                anim = &mapobjanim_type23_odd_anim;
                            } else {
                                anim = &mapobjanim_type23_anim;
                            }
                            break;
                        case 4:
                            anim = &mapobjanim_type4_anim;
                            break;
                    }
                    Math_EvalTcbSpline(anim, &mapobj_spline_out, p->frame++);
                    p->x = mapobj_spline_out.x;
                    p->z = mapobj_spline_out.w;
                    break;
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void MapObj_DrawBillboards(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list) {
    Unk8000FA9C *s;
    f32 dx;
    f32 dz;
    f32 a;
    f32 mf[4][4];
    s32 first;
    Unk8005E518 *e;
    Gfx *dl1;
    Gfx *dl2;
    Vec3f *c;

    first = 0;
    e = map_area_def->unk20;
    dl1 = e[type].a;
    dl2 = e[type].b;
    for (; count != 0; count--) {
        s = *list++;
        if (type == s->timer) {
            dx = s->x - camera_state.x;
            dz = s->z - camera_state.z;
            if (sqrtf(dx * dx + dz * dz) < 1500.0f) {
                a = Math_Atan2(dx, dz) - camera_state.angle + 3.141592653589793;
                if (a < -3.141592653589793) {
                    a += 6.283185307179586;
                } else if (a > 3.141592653589793) {
                    a -= 6.283185307179586;
                }
                if (a < 0.0f) {
                    a = -a;
                }
                a = a * 57.29577951308232;
                if (a < camera_fovy) {
                    if (first == 0) {
                        gSPDisplayList(gfx_dl_head++, dl1);
                        first++;
                        gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
                    }
                    Math_MtxFRotScaleTrans(mf, 0.0f, camera_state.angle, 0.0f, s->scale, s->x, s->y, s->z);
                    guMtxF2L(mf, &arg0->mtx[gfx_mtx_index]);
                    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
                    gfx_mtx_index++;
                    gSPDisplayList(gfx_dl_head++, dl2);
                    c = &mapobj_billboard_normals[(s32)s->angle];
                    Shadow_Queue(s->x, s->y, s->z, c->x, c->y, c->z, 8.0f);
                    D_8007C2A0++;
                }
            }
        }
    }
}

void MapObj_StepArcSprite(Particle *arg0);
void MapObj_StepDropSprite(Particle *arg0);
extern u8 mapobj_arc_sprite_dl[];
extern u8 mapobj_drop_sprite_tex[];
extern u8 mapobj_drop_sprite_dl[];

void MapObj_EmitArcSprite(Unk8000FA9C *arg0) {
    static SpriteObj mapobj_arc_sprite_template = {
        0x23, 0, (void *)MapObj_StepArcSprite, 0x07202000, 0, mapobj_arc_sprite_tex, mapobj_arc_sprite_dl,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 15.0f, 0.0f, 0,
    };

    arg0->timer++;
    if (arg0->timer >= 0) {
        mapobj_arc_sprite_template.x = arg0->x;
        mapobj_arc_sprite_template.y = arg0->y;
        mapobj_arc_sprite_template.z = arg0->z;
        mapobj_arc_sprite_template.unk28 = mapobj_arc_sprite_template.unk2C = arg0->scale * 10.0;
        mapobj_temp_vec[0] = arg0->scale * 2.0;
        mapobj_temp_vec[1] = 0.0f;
        Math_RotateVec2(arg0->angle, mapobj_temp_vec);
        mapobj_arc_sprite_template.unk30 = mapobj_temp_vec[0];
        mapobj_arc_sprite_template.unk38 = mapobj_temp_vec[1];
        mapobj_arc_sprite_template.unk10 = &mapobj_arc_sprite_tex[arg0->timer << 10];
        Effect_AllocateSprite(&mapobj_arc_sprite_template);
        if (arg0->timer >= 7) {
            arg0->timer = Math_Rand(0x3C) - 0x78;
        }
    }
}

void MapObj_StepArcSprite(Particle *arg0) {
    arg0->x += arg0->vx;
    arg0->y += arg0->vy;
    arg0->z += arg0->vz;
    arg0->vy -= 0.9;
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, (mapobj_arc_flicker_tick & 1) ? 0xDC : 0x78);
}

void MapObj_EmitDropSprite(Unk8000FA9C *arg0) {
    static SpriteObj mapobj_drop_sprite_template = {
        0xF, 0, (void *)MapObj_StepDropSprite, 0x00081000, 0, mapobj_drop_sprite_tex, mapobj_drop_sprite_dl,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0,
    };

    arg0->timer--;
    if (arg0->timer == 0) {
        mapobj_drop_sprite_template.x = arg0->x;
        mapobj_drop_sprite_template.y = arg0->y;
        mapobj_drop_sprite_template.z = arg0->z;
        mapobj_drop_sprite_template.unk28 = mapobj_drop_sprite_template.unk2C = arg0->scale;
        Effect_AllocateSprite(&mapobj_drop_sprite_template);
        arg0->timer = Math_Rand(0x96) + 0x96;
    }
}

/* The rest of this file's .data. */
u16 mapobj_animtex_width[2] = { 0x10, 0x10 };
u8 mapobj_animtex_alpha[4] = { 0x82, 0xDC, 0x78, 0xF0 };
extern Unk8004DE98 map_clock_tlut_schedule[];

void MapObj_StepDropSprite(Particle *arg0) {
    arg0->y = arg0->y + arg0->vy / 2;
    arg0->vy -= 0.2;
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, arg0->alpha * 5);
}

void MapObj_ClearSpinners(void) {
    s32 i;
    Unk80083470 *q;
    Unk80083470 *p;

    mapobj_spinner_prev_count = 0;
    i = 8;
    q = mapobj_spinner_buf1;
    p = mapobj_spinner_buf0;
    do {
        p->unk0 = 0;
        q->unk0 = 0;
        i--;
        q++;
        p++;
    } while (i != 0);
}

void MapObj_QueueSpinner(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Unk8000FA9C *arg4) {
    Unk80083470 *prev;
    Unk80083470 *cur;
    s32 i;

    cur = gfx_frame_index ? mapobj_spinner_buf1 : mapobj_spinner_buf0;
    prev = gfx_frame_index ? mapobj_spinner_buf0 : mapobj_spinner_buf1;
    if (mapobj_spinner_count < 8) {
        cur += mapobj_spinner_count;
        i = mapobj_spinner_prev_count;
        while (i != 0 && arg4 != prev->unk18) {
            i--;
            prev++;
        }
        if (i != 0) {
            cur->unk0 = prev->unk0;
            cur->unk14 = prev->unk14;
        } else {
            cur->unk0 = 1;
            cur->unk14 = (f32)Math_Rand(8) * 3.141592653589793 / 4.0f;
        }
        cur->unk4 = arg0;
        cur->unk8 = arg1;
        cur->unkC = arg2;
        cur->unk10 = arg3;
        cur->unk18 = arg4;
        mapobj_spinner_count++;
    }
}

void MapObj_DrawSpinners(MtxBuf *arg0) {
    Unk80083470 *p;
    u32 i;
    Unk8000FA9C *s;

    mapobj_spinner_prev_count = mapobj_spinner_count;
    p = gfx_frame_index ? mapobj_spinner_buf1 : mapobj_spinner_buf0;
    i = mapobj_spinner_prev_count;
    while (i--) {
        if (p->unk0 != 0) {
            s = p->unk18;
            p->unk14 -= 0.015707963267948967;
            Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, p->unk10 * 0.017453292519943295, p->unk14, s->scale, s->x, s->y, s->z);
            gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
            gfx_mtx_index++;
            gSPDisplayList(gfx_dl_head++, map_obj_models[s->timer].dl);
            D_8007C2A0++;
        }
        p++;
    }
}

void MapObj_DrawAnimTexBillboards(MtxBuf *arg0, s32 count, s32 type, Unk8000FA9C **list) {
    s32 pad1;
    s32 idx;
    s32 pad;
    u8 **tex;
    Gfx *dl;
    s32 first;
    Unk8000FA9C *s;

    idx = type - 0x11;
    dl = D_8005E51C[type].a;
    tex = D_8005E5AC[type];
    first = 0;
    for (; count != 0; count--) {
        s = *list++;
        if (type == (s->unk16 & 0xFF)) {
            if (first == 0) {
                gSPDisplayList(gfx_dl_head++, mapobj_animtex_dls[idx].a);
                first++;
            }
            gDPLoadTextureBlock(gfx_dl_head++, tex[(s->timer >> 1) & 7], G_IM_FMT_CI, G_IM_SIZ_8b, mapobj_animtex_width[type - 0x11], 32, 0, 0, 0, 0, 0, 0, 0);
            Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, D_80085E74, 0.0f, s->scale, s->x, s->y, s->z);
            gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
            gfx_mtx_index++;
            gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, mapobj_animtex_alpha[s->timer & 3]);
            gSPDisplayList(gfx_dl_head++, dl);
            s->timer++;
            D_8007C2A0++;
        }
    }
}

void Map_BlendPaletteByClock(void) {
    static s32 map_clock_tlut_id = 0;
    static s32 map_clock_blend_left = 1;
    static s32 map_clock_tlut_prev_id = 1;
    static s32 map_clock_blend_len;
    Unk8004DE98 *p;
    s32 inv;
    u16 *src;
    u16 *src2;
    u16 *dst;
    s32 i;
    u16 r1;
    u16 g1;
    u16 b1;
    u16 r2;
    u16 g2;
    u16 b2;

    p = map_clock_tlut_schedule;
    while (p->id != 0xFF) {
        if (env_clock >= p->start && env_clock < p[1].start) {
            map_clock_tlut_id = p->id;
            break;
        }
        p++;
    }
    if (map_clock_tlut_id != map_clock_tlut_prev_id) {
        map_clock_blend_from = (u16 *)map_clock_tlut_srcs + map_clock_tlut_prev_id * 0x100;
        map_clock_blend_left = map_clock_blend_len = p->unk4;
        map_clock_blend_to = (u16 *)map_clock_tlut_srcs + map_clock_tlut_id * 0x100;
        map_clock_blend_out = map_clock_tlut;
    }
    if (map_clock_blend_left != 0) {
        dst = map_clock_blend_out;
        src = map_clock_blend_from;
        src2 = map_clock_blend_to;
        inv = map_clock_blend_len - map_clock_blend_left;
        i = 0x100;
        while (i--) {
            r1 = (*src & 0xF800) >> 11;
            g1 = (*src & 0x7C0) >> 6;
            b1 = (*src & 0x3E) >> 1;
            r2 = (*src2 & 0xF800) >> 11;
            g2 = (*src2 & 0x7C0) >> 6;
            b2 = (*src2 & 0x3E) >> 1;
            if (src) {
                /* empty: changes IDO's register colouring to retail's (permuter) */
            }
            src++;
            src2++;
            *dst++ = (((r1 * map_clock_blend_left + r2 * inv) / map_clock_blend_len) << 11) | (((g1 * map_clock_blend_left + g2 * inv) / map_clock_blend_len) << 6) | (((b1 * map_clock_blend_left + b2 * inv) / map_clock_blend_len) << 1);
        }
        map_clock_blend_left--;
    }
    map_clock_tlut_prev_id = map_clock_tlut_id;
}

/* Map_BlendPaletteByClock's statics come first, then these. */
Unk8004DE98 map_clock_tlut_schedule[6] = {
    { 0, 0x1C, 2 }, { 0x15F9, 0x80, 0 }, { 0x4F1A, 0x1C, 1 },
    { 0x6513, 0x1C, 2 }, { 0x6977, 0x1C, 2 }, { 0x6979, 0xFF, 0xFF },
};
s32 D_8004DEC8 = 0;

extern u16 D_80081AB0[];
extern u16 D_80081C40;
extern u16 D_80081C42;

void func_80010768(void) {
    s32 *cnt = &D_8004DEC8;
    s32 v;
    u16 *p;
    u16 tmp;

    v = *cnt;
    if (v >= 0) {
    lbl:;
        tmp = D_80081AB0[0xC9];
        *cnt = 0;
        D_80081C42 = D_80081C40;
        v = 200; p = D_80081AB0 + 199;
        for (; v != 0; v--, p--) { p[1] = p[0]; }
        D_80081AB0[0] = tmp;
    } else {
        v++; *cnt = v;
    }
}
