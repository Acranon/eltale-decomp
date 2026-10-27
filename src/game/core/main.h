#ifndef GAME_CORE_MAIN_H
#define GAME_CORE_MAIN_H

#include "common.h"
#include "game/core/sched.h"

/* One graphics frame's segment 2 data (D_2000000 in segment 2) and display list.
 * proj and view come from camera_proj_mtx / camera_view_mtx (Camera_Update), ortho is the
 * 2D projection built by guOrtho (Camera_InitForMap; HUD and fade load it), mtx[] the
 * per-draw matrices handed out by gfx_mtx_index, lookAt Camera_Update's guLookAtReflectF. */
typedef struct GfxFrameData {
    /* 0x0000 */ Mtx proj;
    /* 0x0040 */ Mtx ortho;
    /* 0x0080 */ Mtx view;
    /* 0x00C0 */ Mtx mtx[0x226];
    /* 0x8A40 */ LookAt lookAt;
    /* 0x8A60 */ u8 unk8A60[0x10];
    /* 0x8A70 */ Gfx dl[(0xDA70 - 0x8A70) / sizeof(Gfx)];
    /* 0xDA70 */ s16 msg;
    /* 0xDA74 */ u16 *framebuffer;
} GfxFrameData; /* 0xDA78 bytes */

/* A graphics frame: the scheduler task followed by its data (D_80301000[2]). */
typedef struct GfxFrame {
    /* 0x0000 */ NNScTask task;
    /* 0x0058 */ GfxFrameData data;
} GfxFrame; /* 0xDAD0 bytes */

/* .bss 8007A170..8007A8C0, in address order (the order of these declarations fixes it). */
extern u16 core_game_mode;
extern u16 D_8007A172;
extern s32 core_transition_timer;
extern u16 fade_transition_style;
extern u16 core_fade_out_time;
extern s32 gfx_frame_index;
extern s32 gfx_mtx_index;
extern Gfx *gfx_dl_head;
extern s32 gfx_clear_r;
extern s32 gfx_clear_g;
extern u32 gfx_clear_b;
extern s32 D_8007A194;
extern s32 D_8007A198;
extern s32 D_8007A19C;
extern s16 gfx_fog_near;
extern s16 gfx_fog_far;
extern s32 D_8007A1A4;
extern OSMesgQueue dma_mesg_queue;
extern OSMesg dma_mesg;
extern s32 D_8007A1C4;
extern s32 gfx_scene_light_slot;
extern u8 title_menu_choice;
extern s8 D_8007A1CD;
extern s16 D_8007A1CE;
extern s32 gfx_frame_sent;
extern s32 gfx_dl_peak_len;
extern void *gfx_segment1_base;
extern s32 D_8007A1DC;
extern NNSched core_sched;
extern OSMesgQueue *gfx_sched_mq;
extern s32 D_8007A864;
extern NNScClient gfx_sched_client;
extern OSMesgQueue gfx_mesg_queue;
extern OSMesg gfx_mesgs[8];
extern u64 core_frame_start_time;
extern u64 core_frame_end_time;
extern u64 D_8007A8B8;

/* Not defined by a module: the two graphics frames at a fixed address, and the current
 * frame's data through segment 2. */
extern GfxFrame D_80301000[2];
extern GfxFrameData D_2000000;

/* .data */
extern s32 core_flags;
extern s32 D_8004DCA4;

void Core_MainThread(void *arg0);
void Core_ResetGameState(void);
void Gfx_InitFrames(void);
void Gfx_InitFrameTask(GfxFrame *arg0);
void Gfx_BuildFrameDisplayList(GfxFrame *arg0);
void Core_RunGameplayLoop(void);
void Core_RunMessageCutsceneLoop(void);
void Core_RunCameraCutsceneLoop(void);
void Core_RunMenuLoop(void);
void Core_RunTitleLoop(void);
void Core_RunIntroLoop(void);
void Core_RunEndingLoop(void);
void Gfx_WaitForFrameMessage(s16 arg0);
void Fade_StartTransitionIn(void);
void Fade_StartTransitionOut(void);

#endif
