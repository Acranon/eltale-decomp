#include "game/actor/anim.h"
#include "game/audio/sound.h"
#include "game/core/main.h"
#include "game/env/env.h"
#include "game/gfx/effect.h"
#include "game/gfx/shadow.h"
#include "game/gfx/sprite_effect.h"
#include "game/player/player.h"

/*
 * Field map: area loading (ROM blocks, area/sub-area tables, map objects), drawing the
 * map objects in the grid cells around the camera (opaque, translucent, billboards,
 * spinning and texture-animated objects, sprite emitters), animated-object slots,
 * the nearest ambient sound, colour-table blends/cycles.
 * Original file: E2A0.c (ROM 0xE2A0).
 */

/* map.h comes after the headers above on purpose (.bss order). Its .bss externs fix this file's
 * .bss order (first declaration; IDO sorts by declaration number mod 256, later blocks first on
 * a tie), and Map_BlendPaletteByClock's static map_clock_blend_len only lands at 80082858 (after
 * mapobj_noanim_list) if the number of declarations (typedefs, tags, used externs) between
 * map.h's externs and the static stays as it is now: measured margin 2 more or 2 fewer (a
 * tagged struct typedef counts 2). That is why menu.h (which includes map.h), camera.h and
 * dma.h come right after map.h: H2c dropped menu.h's MapObjAnimDef (2 fewer) and moved dma.h
 * here from the top (2 more) to keep the margin centred. Above map.h about 96 more
 * declarations still work. */
#include "game/map/map.h"
#include "game/ui/menu.h"
#include "game/camera/camera.h"
#include "game/core/dma.h"

/* Not defined by a module: overlay data, ROM addresses and fixed RAM addresses. */
extern u16 D_80124E00[];
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
/* menu.c's mapobj_animtex_frame_tables / mapobj_kind12_setup_dl read with a base biased by
 * the first animated kind (0x11): mapobj_animtex_dls + 0xC, mapobj_kind12_setup_dl + 0x14. */
extern u8 **D_8005E5AC[];
extern struct MapDlPair D_8005E51C[];
/* Labels inside this file's D_80081AB0 (undefined_syms.txt); Map_LoadArea needs them as symbols. */
extern u16 D_80081B78[];
extern u16 D_80081B7A[];

/* This file's .bss starts here: 8007C280..80082030 in address order, then
 * D_80082030.. below. mapobj_billboard_list is a pointer table other files use.
 * D_80081CE4, D_80081FEC, D_80081FF8 and D_8008201C are
 * unreferenced. Splat's labels inside D_80081AB0 (D_80081B78..D_80081C42) and
 * mapobj_wave_base (D_80081D00..D_80081D30) are aliases in undefined_syms.txt. */
u16 map_env_flags; /* bit 0: own light cycle, bit 1: world clock time (Env_*) */
u16 map_backdrop_id;
MapAreaDef *map_area_def;
MapSubareaDef *map_subarea_def;
MapGrid *map_subarea_grid;
MapObj *map_objs;
MapModel *map_obj_models;
CollWalls *map_actor_walls;
CollWalls *map_camera_walls;
s32 D_8007C2A0;
s32 mapobj_billboard_count;
MapObj *mapobj_billboard_list[0x100];
s32 mapobj_spinner_prev_count;
s32 mapobj_spinner_count;
u8 map_backdrop_tex[0x4000];
u16 map_backdrop_tlut[0x100];
u16 map_backdrop_phase_tluts[4][0x100]; /* the four day-phase backdrop palettes */
u16 map_clock_tlut[0x200];
u16 map_clock_tlut_srcs[3][0x100];
u16 D_80081AB0[0x100];
s32 mapobj_opaque_count;
s32 mapobj_noanim_count;
s32 mapobj_billboard_draw_count;
s32 mapobj_translucent_count;
s32 mapobj_animtex_count;
s32 mapobj_scrolltex_count;
MapObj **mapobj_opaque_cursor;
MapObj **mapobj_noanim_cursor;
MapObj **mapobj_billboard_cursor;
MapObj **mapobj_translucent_cursor;
MapObj **mapobj_animtex_cursor;
MapObj **mapobj_scrolltex_cursor;
s32 mapobj_wave_capture;
s32 D_80081CE4;
MapObjWaveBase mapobj_wave_base[32];
MapObj *mapobj_wave_base_cursor;
s32 D_80081FEC;
f32 mapobj_temp_vec[2];
s32 D_80081FF8[2];
CollResult map_load_coll;
s32 D_8008201C;
MapObjSplineOut mapobj_spline_out;

/* The rest of this file's .bss, 80082030..80082860 (the 16-byte-aligned run that
 * holds Map_BlendPaletteByClock's static at 80082858). Nothing names 80082030..80082048
 * (splat's D_80082030 is Map_LoadArea's loop end), so it is a placeholder. */
u8 D_80082030[0x18];
MapObjWavePhase mapobj_wave_phase[4];
u16 mapobj_opaque_list[0x200];
u16 mapobj_noanim_list[0x200];

/* The last part of this file's .bss, 80082860..800842F0. */
MapObj *mapobj_translucent_list[0x100];
MapObj *mapobj_animtex_list[0x100];
u16 *map_clock_blend_from;
MapObj *mapobj_scrolltex_list[0x100];
u16 *map_clock_blend_to;
MapObjSpinner mapobj_spinner_buf1[8];
u16 *map_clock_blend_out;
MapObjSpinner mapobj_spinner_buf0[8];
Vec3f mapobj_billboard_normals[0x100];
MapObjAnimSlot mapobj_anim_slots[4];
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
MapObjWaveBase mapobj_wave_base_init = { { 0 } };
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
    MapEntryPoint *sp;
    u32 n;
    MapObj *s;
    Vec3f *v;
    s32 k;
    s32 kind;
    MapObjWavePhase *z;

    map_area_def = &map_area_defs[map_next_id];
    if (map_id != -1) {
        if (map_next_id == 11) {
            if (map_subarea == 2 && map_next_subarea == 0) {
                map_flag4_return_map = map_next_id;
                map_flag4_return_subarea = map_next_subarea;
                map_flag4_return_entry = exit_destination.entry;
            }
        } else if (map_next_id == 6) {
            map_flag4_return_map = map_next_id;
            map_flag4_return_subarea = map_next_subarea;
            map_flag4_return_entry = exit_destination.entry;
        } else if ((map_flags & 1) && (map_area_def->flags & 4)) {
            map_flag4_return_map = map_next_id;
            map_flag4_return_subarea = map_next_subarea;
            map_flag4_return_entry = exit_destination.entry;
        } else if (map_next_id != map_id && (map_area_def->flags & 8)) {
            map_flag8_return_map = map_next_id;
            map_flag8_return_subarea = map_next_subarea;
            map_flag8_return_entry = exit_destination.entry;
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
            q = &((u32 *)map_extra_rom_ranges)[map_area_def->extraRomRangeIndex * 3];
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
    map_subarea_def = &map_area_def->subareas[k];
    map_obj_models = map_area_def->models;
    map_subarea_grid = &map_area_def->grids[map_subarea_def->grid];
    env_area_settings = &map_area_def->envSettings[map_subarea_def->env];
    map_objs = map_subarea_grid->objs;
    map_actor_walls = map_area_def->actorWalls;
    map_camera_walls = map_area_def->cameraWalls;
    map_subarea_flags = map_subarea_def->flags;
    map_env_flags = env_area_settings->mapFlags;
    if (map_backdrop_id != env_area_settings->backdropId) {
        map_backdrop_id = env_area_settings->backdropId;
        Dma_ReadRom(map_backdrop_defs[map_backdrop_id].start, map_backdrop_phase_tluts, 0x800);
        Dma_ReadRom(map_backdrop_defs[map_backdrop_id].start + 0x800, map_backdrop_tex, 0x4000);
    }
    if (exit_destination.entry != -1) {
        sp = &map_subarea_def->entries[exit_destination.entry];
        player_spawn_x = sp->x;
        player_spawn_z = sp->y;
        player_spawn_rot = sp->z;
        player_spawn_obj = sp->spawnObj;
    }
    n = map_subarea_grid->count;
    s = map_objs;
    mapobj_billboard_count = k = 0;
    v = mapobj_billboard_normals;
    for (; n != 0; n--, s++) {
        if (s->kind & 0x8000) {
            Coll_ResolveFloorAndWalls(s->x, s->y, s->z, 0xA00, &map_load_coll);
            s->y = map_load_coll.y;
        }
        kind = s->kind & 0xFF;
        if (kind == 0x10) {
            v->x = map_load_coll.nx;
            v->y = map_load_coll.ny;
            v->z = map_load_coll.nz;
            s->angle = k++;
            v++;
        } else if (kind == 0x83) {
            s->model = 0;
        } else if (kind == 0x84) {
            s->model = Math_Rand(150) + 150;
        } else if (s->kind >= 0x11 && s->kind < 0x15) {
            s->model = Math_Rand(16);
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
extern Gfx D_10000E8[]; /* segment 1 (no module defines it) */

/* &mapobj_opaque_list kept in a saved register instead of rematerialized, 8 bytes short, register allocation; code is equivalent */
void MapObj_UpdateAndDrawNearby(GfxFrameData *arg0) {
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
    MapObj *s;
    u16 flags;
    f32 x;
    f32 y;
    f32 z;
    f32 rot;
    AnimNode *anim;
    s32 i;
    MapObjWavePhase *a;
    MapObjWavePhase *b;
    f64 d;
    s32 k;
    s32 *pCB4 = &mapobj_noanim_count;
    s32 *pCB8 = &mapobj_billboard_draw_count;
    MapObj ***pCD0 = &mapobj_billboard_cursor;
    f32 *pAC = &mapobj_ambient_dist;
    s32 *pB0 = &mapobj_ambient_type;

    *pCB4 = 0;
    mapobj_opaque_count = 0;
    *pCB8 = 0;
    mapobj_translucent_count = 0;
    mapobj_animtex_count = 0;
    mapobj_scrolltex_count = 0;
    mapobj_billboard_count = 0;
    mapobj_opaque_cursor = (MapObj **) mapobj_opaque_list;
    mapobj_noanim_cursor = (MapObj **) mapobj_noanim_list;
    *pCD0 = (MapObj **) mapobj_billboard_list;
    mapobj_translucent_cursor = mapobj_translucent_list;
    mapobj_animtex_cursor = mapobj_animtex_list;
    mapobj_scrolltex_cursor = mapobj_scrolltex_list;
    mapobj_wave_base_cursor = (MapObj *) mapobj_wave_base;
    *pAC = 600.0f;
    *pB0 = -1;
    px = camera_state.eyeX;
    pz = camera_state.eyeZ;
    switch (map_subarea_grid->searchPattern) {
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
    if (map_subarea_grid->alwaysCount != 0) {
        t = map_subarea_grid->alwaysCount;
        MapObj_CollectCell(t, map_subarea_grid->alwaysList);
    }
    gSPDisplayList(gfx_dl_head++, D_10000E8);
    gSPFogPosition(gfx_dl_head++, gfx_fog_near, gfx_fog_far);
    D_8007C2A0 = 0;
    mapobj_opaque_cursor = (MapObj **) mapobj_opaque_list;
    for (n = mapobj_opaque_count; n != 0; n--) {
        s = *mapobj_opaque_cursor++;
        flags = s->kind;
        x = s->x;
        y = s->y;
        z = s->z;
        rot = s->angle;
        if (flags & 0x2000) {
            anim = &mapobj_loop_anims[(flags & 0xF00) >> 8];
            t = flags;
            t = (t & 0xFF) + 1;
            Math_EvalTcbSpline(&anim->track, (f32 *)&mapobj_spline_out, flags & 0xFF);
            x += mapobj_spline_out.x * s->scale;
            y += mapobj_spline_out.y * s->scale;
            z += mapobj_spline_out.z * s->scale;
            flags = t;
            if (t >= anim->track.last) {
                flags = 0;
            }
            s->kind = (s->kind & 0xFF00) | flags;
        } else if (flags & 0x100) {
            i = MapObjAnim_Find(s);
            if (i != 0) {
                mapobj_temp_vec[1] = 0.0f;
                mapobj_temp_vec[0] = mapobj_anim_slots[i - 1].x;
                Math_RotateVec2(s->angle * 0.017453292519943295, (Vec2f *)mapobj_temp_vec);
                x -= mapobj_temp_vec[0];
                z -= mapobj_temp_vec[1];
                rot += mapobj_anim_slots[i - 1].z;
            }
        }
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, rot, 0.0f, s->scale, x, y, z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gSPDisplayList(gfx_dl_head++, map_obj_models[s->model].dl);
        D_8007C2A0++;
    }
    mapobj_opaque_cursor = (MapObj **) mapobj_noanim_list;
    for (n = *pCB4; n != 0; n--) {
        s = *mapobj_opaque_cursor++;
        guPosition(&arg0->mtx[gfx_mtx_index], 0.0f, s->angle, 0.0f, s->scale, s->x, s->y, s->z);
        gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
        gfx_mtx_index++;
        gSPDisplayList(gfx_dl_head++, map_obj_models[s->model].dl);
        D_8007C2A0++;
    }
    MapObj_DrawSpinners(arg0);
    if (*pCB8 != 0) {
        gDPPipeSync(gfx_dl_head++);
        gDPSetRenderMode(gfx_dl_head++, 0xC8113078, 0);
        *pCD0 = (MapObj **) mapobj_billboard_list;
        MapObj_DrawBillboards(arg0, *pCB8, 0, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 1, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 2, *pCD0);
        MapObj_DrawBillboards(arg0, *pCB8, 3, *pCD0);
    }
    gDPSetTextureFilter(gfx_dl_head++, G_TF_BILERP);
    gDPSetTextureLUT(gfx_dl_head++, G_TT_NONE);
    /* mapobj_wave_phase_step is read as four u16 pairs */
    a = mapobj_wave_phase;
    b = (MapObjWavePhase *) mapobj_wave_phase_step;
    for (;;) {
        u16 ta = a->a + b->a;
        u16 tb = a->b + b->b;
        b++;
        k = b < ((MapObjWavePhase *) mapobj_wave_phase_step) + 4;
        a++;
        a[-1].a = ta;
        a[-1].b = tb;
        if (!k) {
            break;
        }
    }
    mapobj_wave_capture = 0;
    Map_BlendPaletteByClock();
    Map_RotateHalfwordBuffer();
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
#pragma GLOBAL_ASM("asm/nonmatchings/game/map/map/MapObj_UpdateAndDrawNearby.s")
#endif

void MapObj_DrawTranslucent(GfxFrameData *arg0) {
    MapObj *s;
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
        idx = s->model;
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
        k = (s->kind & 0xFF) - 0x40;
        idx = s->model;
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
    MapObj *s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    u16 kind;

    for (; count != 0; count--) {
        s = &map_objs[*ids++];
        if (s->kind & 0x1000) {
            dx = s->x - player_state.actor.x;
            dy = s->y - player_state.actor.y;
            dz = s->z - player_state.actor.z;
            d = sqrtf(dx * dx + dy * dy + dz * dz);
            if (d < mapobj_ambient_dist) {
                mapobj_ambient_dist = d;
                mapobj_ambient_type = (s->kind & 0xF00) >> 8;
            }
        }
        kind = s->kind;
        if (s->kind & 0x2000) {
            kind = 0;
        } else {
            kind = (u8)kind;
        }
        if (!kind || kind == 8) {
            if (s->kind & 0x4000) {
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

void Map_DrawBackdrop(GfxFrameData *arg0) {
    Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, 0.0f, 0.0f, 1.0f, camera_state.eyeX, camera_state.eyeY - 10.0f, camera_state.eyeZ);
    gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
    gfx_mtx_index++;
    gDPSetEnvColor(gfx_dl_head++, D_80084B60, D_80084B64, D_80084B68, 255);
    gSPDisplayList(gfx_dl_head++, map_backdrop_defs[env_area_settings->backdropId].dl);
}

void MapObjAnim_ClearAll(void) {
    MapObjAnimSlot *p = mapobj_anim_slots;
    u32 i = 4;

    while (i--) {
        p->timer = 0;
        p++;
    }
}

s32 MapObjAnim_Find(MapObj *obj) {
    MapObjAnimSlot *p;
    s32 i;

    i = 4;
    p = mapobj_anim_slots;
    for (; i != 0; i--, p++) {
        if (p->timer != 0 && obj == p->obj) {
            i = 5 - i;
            break;
        }
    }
    return i;
}

void MapObjAnim_Start(s32 state, s32 frame, s32 type, MapObj *obj) {
    MapObjAnimSlot *p;
    s32 i;
    AnimNode *anim;

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
    p->obj = obj;
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
        p->timer = anim->track.last - frame + 1;
    } else {
        p->timer = 7;
    }
}

void MapObjAnim_UpdateAll(void) {
    MapObjAnimSlot *p;
    s32 i;
    AnimNode *anim;

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
                    Math_EvalTcbSpline(&anim->track, (f32 *)&mapobj_spline_out, p->frame++);
                    p->x = mapobj_spline_out.x;
                    p->z = mapobj_spline_out.w;
                    break;
            }
        }
        i--;
        p++;
    } while (i != 0);
}

void MapObj_DrawBillboards(GfxFrameData *arg0, s32 count, s32 type, MapObj **list) {
    MapObj *s;
    f32 dx;
    f32 dz;
    f32 a;
    f32 mf[4][4];
    s32 first;
    MapDlPair *e;
    Gfx *dl1;
    Gfx *dl2;
    Vec3f *c;

    first = 0;
    e = map_area_def->animTexDls;
    dl1 = e[type].a;
    dl2 = e[type].b;
    for (; count != 0; count--) {
        s = *list++;
        if (type == s->model) {
            dx = s->x - camera_state.eyeX;
            dz = s->z - camera_state.eyeZ;
            if (sqrtf(dx * dx + dz * dz) < 1500.0f) {
                a = Math_Atan2(dx, dz) - camera_state.yaw + 3.141592653589793;
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
                    Math_MtxFRotScaleTrans((MtxF *)mf, 0.0f, camera_state.yaw, 0.0f, s->scale, s->x, s->y, s->z);
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


void MapObj_EmitArcSprite(MapObj *arg0) {
    static EffectSprite mapobj_arc_sprite_template = {
        0x23, 0, 0, MapObj_StepArcSprite, 7, 0x20, 0x20, 0, 0, { 0 }, mapobj_arc_sprite_tex, mapobj_arc_sprite_dl,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 15.0f, 0.0f, 0,
    };

    arg0->model++;
    if (arg0->model >= 0) {
        mapobj_arc_sprite_template.x = arg0->x;
        mapobj_arc_sprite_template.y = arg0->y;
        mapobj_arc_sprite_template.z = arg0->z;
        mapobj_arc_sprite_template.scaleX = mapobj_arc_sprite_template.scaleY = arg0->scale * 10.0;
        mapobj_temp_vec[0] = arg0->scale * 2.0;
        mapobj_temp_vec[1] = 0.0f;
        Math_RotateVec2(arg0->angle, (Vec2f *)mapobj_temp_vec);
        mapobj_arc_sprite_template.vecX = mapobj_temp_vec[0];
        mapobj_arc_sprite_template.vecZ = mapobj_temp_vec[1];
        mapobj_arc_sprite_template.tex = &mapobj_arc_sprite_tex[arg0->model << 10];
        Effect_AllocateSprite(&mapobj_arc_sprite_template);
        if (arg0->model >= 7) {
            arg0->model = Math_Rand(0x3C) - 0x78;
        }
    }
}

void MapObj_StepArcSprite(EffectSprite *arg0) {
    arg0->x += arg0->vecX;
    arg0->y += arg0->vecY;
    arg0->z += arg0->vecZ;
    arg0->vecY -= 0.9;
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, (mapobj_arc_flicker_tick & 1) ? 0xDC : 0x78);
}

void MapObj_EmitDropSprite(MapObj *arg0) {
    static EffectSprite mapobj_drop_sprite_template = {
        0xF, 0, 0, MapObj_StepDropSprite, 0, 0x08, 0x10, 0, 0, { 0 }, mapobj_drop_sprite_tex, mapobj_drop_sprite_dl,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0,
    };

    arg0->model--;
    if (arg0->model == 0) {
        mapobj_drop_sprite_template.x = arg0->x;
        mapobj_drop_sprite_template.y = arg0->y;
        mapobj_drop_sprite_template.z = arg0->z;
        mapobj_drop_sprite_template.scaleX = mapobj_drop_sprite_template.scaleY = arg0->scale;
        Effect_AllocateSprite(&mapobj_drop_sprite_template);
        arg0->model = Math_Rand(0x96) + 0x96;
    }
}

/* The rest of this file's .data. */
u16 mapobj_animtex_width[2] = { 0x10, 0x10 };
u8 mapobj_animtex_alpha[4] = { 0x82, 0xDC, 0x78, 0xF0 };

void MapObj_StepDropSprite(EffectSprite *arg0) {
    arg0->y = arg0->y + arg0->vecY / 2;
    arg0->vecY -= 0.2;
    gDPSetEnvColor(gfx_dl_head++, 255, 255, 255, arg0->life * 5);
}

void MapObj_ClearSpinners(void) {
    s32 i;
    MapObjSpinner *q;
    MapObjSpinner *p;

    mapobj_spinner_prev_count = 0;
    i = 8;
    q = mapobj_spinner_buf1;
    p = mapobj_spinner_buf0;
    do {
        p->active = 0;
        q->active = 0;
        i--;
        q++;
        p++;
    } while (i != 0);
}

void MapObj_QueueSpinner(f32 arg0, f32 arg1, f32 arg2, f32 arg3, MapObj *arg4) {
    MapObjSpinner *prev;
    MapObjSpinner *cur;
    s32 i;

    cur = gfx_frame_index ? mapobj_spinner_buf1 : mapobj_spinner_buf0;
    prev = gfx_frame_index ? mapobj_spinner_buf0 : mapobj_spinner_buf1;
    if (mapobj_spinner_count < 8) {
        cur += mapobj_spinner_count;
        i = mapobj_spinner_prev_count;
        while (i != 0 && arg4 != prev->obj) {
            i--;
            prev++;
        }
        if (i != 0) {
            cur->active = prev->active;
            cur->spinAngle = prev->spinAngle;
        } else {
            cur->active = 1;
            cur->spinAngle = (f32)Math_Rand(8) * 3.141592653589793 / 4.0f;
        }
        cur->unk4 = arg0;
        cur->unk8 = arg1;
        cur->unkC = arg2;
        cur->yawDegrees = arg3;
        cur->obj = arg4;
        mapobj_spinner_count++;
    }
}

void MapObj_DrawSpinners(GfxFrameData *arg0) {
    MapObjSpinner *p;
    u32 i;
    MapObj *s;

    mapobj_spinner_prev_count = mapobj_spinner_count;
    p = gfx_frame_index ? mapobj_spinner_buf1 : mapobj_spinner_buf0;
    i = mapobj_spinner_prev_count;
    while (i--) {
        if (p->active != 0) {
            s = p->obj;
            p->spinAngle -= 0.015707963267948967;
            Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, p->yawDegrees * 0.017453292519943295, p->spinAngle, s->scale, s->x, s->y, s->z);
            gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
            gfx_mtx_index++;
            gSPDisplayList(gfx_dl_head++, map_obj_models[s->model].dl);
            D_8007C2A0++;
        }
        p++;
    }
}

void MapObj_DrawAnimTexBillboards(GfxFrameData *arg0, s32 count, s32 type, MapObj **list) {
    s32 pad1;
    s32 idx;
    s32 pad;
    u8 **tex;
    Gfx *dl;
    s32 first;
    MapObj *s;

    idx = type - 0x11;
    dl = D_8005E51C[type].a;
    tex = D_8005E5AC[type];
    first = 0;
    for (; count != 0; count--) {
        s = *list++;
        if (type == (s->kind & 0xFF)) {
            if (first == 0) {
                gSPDisplayList(gfx_dl_head++, mapobj_animtex_dls[idx].a);
                first++;
            }
            gDPLoadTextureBlock(gfx_dl_head++, tex[(s->model >> 1) & 7], G_IM_FMT_CI, G_IM_SIZ_8b, mapobj_animtex_width[type - 0x11], 32, 0, 0, 0, 0, 0, 0, 0);
            Math_MtxRotScaleTrans(&arg0->mtx[gfx_mtx_index], 0.0f, camera_state.yaw, 0.0f, s->scale, s->x, s->y, s->z);
            gSPMatrix(gfx_dl_head++, &D_2000000.mtx[gfx_mtx_index], G_MTX_LOAD);
            gfx_mtx_index++;
            gDPSetEnvColor(gfx_dl_head++, 0, 0, 0, mapobj_animtex_alpha[s->model & 3]);
            gSPDisplayList(gfx_dl_head++, dl);
            s->model++;
            D_8007C2A0++;
        }
    }
}

void Map_BlendPaletteByClock(void) {
    /* first: with map.h's .bss externs this puts it at 80082858 (see map.h) */
    static s32 map_clock_blend_len;
    static s32 map_clock_tlut_id = 0;
    static s32 map_clock_blend_left = 1;
    static s32 map_clock_tlut_prev_id = 1;
    MapClockTlutStep *p;
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
        map_clock_blend_left = map_clock_blend_len = p->blendFrames;
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
MapClockTlutStep map_clock_tlut_schedule[6] = {
    { 0, 0x1C, 2 }, { 0x15F9, 0x80, 0 }, { 0x4F1A, 0x1C, 1 },
    { 0x6513, 0x1C, 2 }, { 0x6977, 0x1C, 2 }, { 0x6979, 0xFF, 0xFF },
};
s32 map_halfword_rotation_counter = 0;

extern u16 D_80081C40;
extern u16 D_80081C42;

void Map_RotateHalfwordBuffer(void) {
    s32 *cnt = &map_halfword_rotation_counter;
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
