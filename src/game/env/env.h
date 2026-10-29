#ifndef GAME_ENV_ENV_H
#define GAME_ENV_ENV_H

#include "common.h"
#include "game/math/math.h"

/* An exit record: map.h's MapExit (h_world). */
struct MapExit;

/* Where the current exit leads: Exit_SetDestination fills it from the exit record (the
 * player code also writes a respawn point into map/subarea/entry; entry -1: a save spawn
 * point). The gameplay loop takes the next map and subarea; Player_StartAreaExit uses
 * flags (the exit's flags; bits 8..11 the exit kind), angle (the player's heading for the
 * walk out) and mapObj (the door object, map_objs[mapObj]). */
typedef struct ExitDestination {
    /* 0x00 */ s32 map;
    /* 0x04 */ s32 subarea;
    /* 0x08 */ s32 entry;
    /* 0x0C */ u16 flags;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s32 mapObj;
    /* 0x14 */ f32 angle;
} ExitDestination; /* 0x18 bytes */

/* An RGB triple of the lighting track (ambient or one light), 0..255 per channel. */
typedef struct EnvColor {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
} EnvColor; /* 0xC bytes */

typedef struct EnvFogRange {
    /* 0x00 */ s32 near;
    /* 0x04 */ s32 far;
} EnvFogRange; /* 0x8 bytes */

/* One key of an area's lighting track (Env_InterpolateLighting). */
typedef struct EnvKeyframe {
    /* 0x00 */ s32 time;
    /* 0x04 */ EnvColor amb;
    /* 0x10 */ EnvColor lights[3];
    /* 0x34 */ EnvFogRange fog;
} EnvKeyframe; /* 0x3C bytes */

/* A subarea's environment record (map_area_def->envSettings[]); env_area_settings points at the
 * current one. hasLightDirection selects lightDirX/Y/Z. */
typedef struct EnvAreaSettings {
    /* 0x00 */ EnvKeyframe *frames;
    /* 0x04 */ s32 count;
    /* 0x08 */ s32 hasLightDirection;
    /* 0x0C */ s32 lightDirX;
    /* 0x10 */ s32 lightDirY;
    /* 0x14 */ s32 lightDirZ;
    /* 0x18 */ u16 mapFlags;
    /* 0x1A */ u8 unk1A[2];
    /* 0x1C */ s32 backdropId;
} EnvAreaSettings; /* 0x20 bytes */

/* A light slot (Env_AllocateLightSlot): env colour animation (envAnimMode..envFramesStart), light colour
 * animation (lightAnimMode..lightFramesStart) and light directions (lightDirs). */
typedef struct EnvLightSlot {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 envAnimMode;
    /* 0x08 */ s32 envFramesLeft;
    /* 0x0C */ s32 envFrameCount;
    /* 0x10 */ s32 *envFrame;
    /* 0x14 */ s32 *envFramesStart;
    /* 0x18 */ s32 lightAnimMode;
    /* 0x1C */ s32 lightFrameCount;
    /* 0x20 */ s32 lightFramesLeft;
    /* 0x24 */ s32 *lightFrame;
    /* 0x28 */ s32 *lightFramesStart;
    /* 0x2C */ s32 *lightDirs;
} EnvLightSlot; /* 0x30 bytes */

/* A day phase: start time (env_clock), backdrop palette index, palette fade length. */
typedef struct EnvDayPhase {
    /* 0x00 */ s32 startTime;
    /* 0x04 */ s32 paletteIndex;
    /* 0x08 */ s32 fadeFrames;
} EnvDayPhase; /* 0xC bytes */

/* .bss 80084300..80084B80, in address order (the order of these declarations fixes it). */
extern ExitDestination exit_destination;
extern u16 *exit_destination_src;
extern Vec2f exit_local_offset;
extern u8 D_80084328[8];
extern s32 env_next_phase;
extern s32 env_last_phase_start;
extern u16 env_play_time_ticks;
extern s32 env_palette_fade_timer;
extern s32 env_palette_fade_length;
extern u16 *env_palette_fade_target;
extern u16 *env_palette_fade_dest;
extern u16 env_palette_fade_start[0x100];
extern f32 env_light_rot_mtx[4][4];
extern Lights3 env_lights_frame0;
extern Lights3 env_lights_frame1;
extern Lights3 env_slot_lights_frame0[8];
extern Lights3 env_slot_lights_frame1[8];
extern s32 env_clock;
extern s32 env_day_length;
extern s32 env_light_time;
extern s32 env_light_period;
extern u16 env_day_count;
extern u16 env_play_time;
extern EnvAreaSettings *env_area_settings;
extern EnvLightSlot env_light_slots[8];
extern s32 env_light_colors[4][3];
extern s32 env_light_dirs[4][3];
/* Labels of env_light_dirs[2][0..2] and [3][0..2] (aliases in undefined_syms.txt): env.c,
 * map.c and effect.c address them as their own symbols (each its own lui in retail; through
 * env_light_dirs[n][i] they would share one base). */
extern s32 D_80084B60;
extern s32 D_80084B64;
extern s32 D_80084B68;
extern s32 D_80084B6C;
extern s32 D_80084B70;
extern s32 D_80084B74;
extern s32 env_fog_range[2];

/* .data */
extern EnvDayPhase env_day_phases[4];

void Exit_SetDestination(struct MapExit *arg0);
void Env_InitClock(void);
void Env_InitForMap(void);
void Env_Update(void);
void Env_SetClock(s32 arg0);
void Env_InterpolateLighting(s32 t, EnvAreaSettings *arg1);
void Env_PrepareFrameLighting(void);
void Env_ComputeLightDirs(void);
void Env_StartPaletteFade(s32 arg0, u16 *arg1, u16 *arg2);
void Env_StepPaletteFade(s32 arg0);
void Env_ClearLightSlots(void);
s32 Env_AllocateLightSlot(void);
void Env_FreeLightSlot(s32 arg0);
void Env_SetSlotEnvAnim(s32 arg0, s32 arg1, s32 arg2, s32 *arg3);
void Env_SetSlotLightAnim(s32 arg0, s32 arg1, s32 arg2, s32 *arg3);
void Env_SetSlotLightDirs(s32 arg0, s32 *arg1);
void Env_ApplyLightSlot(s32 idx);
void Env_FillLights3(Lights3 *arg0, s32 (*arg1)[3], s32 (*arg2)[3]);

#endif
