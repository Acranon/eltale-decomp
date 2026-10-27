#include "game/core/main.h"
#include "game/core/dma.h"
#include "game/core/overlay_load.h"
#include "game/audio/audio.h"
#include "game/audio/sound.h"
#include "game/input/input.h"
#include "game/env/env.h"
#include "game/math/math.h"
#include "game/camera/camera.h"
#include "game/map/map.h"
#include "game/map/collision.h"
#include "game/map/chest.h"
#include "game/map/spirit.h"
#include "game/map/textspot.h"
#include "game/actor/actor.h"
#include "game/actor/anim.h"
#include "game/player/player.h"
#include "game/npc/npc.h"
#include "game/enemy/enemy.h"
#include "game/enemy/boss.h"
#include "game/battle/battle.h"
#include "game/magic/magic.h"
#include "game/gfx/shadow.h"
#include "game/gfx/shadow_reset.h"
#include "game/gfx/effect.h"
#include "game/gfx/sprite_effect.h"
#include "game/gfx/fade.h"
#include "game/item/item.h"
#include "game/ui/hud.h"
#include "game/ui/menu.h"
#include "game/save/save_menu.h"
#include "game/text/text.h"
#include "game/text/text_window.h"
#include "game/event/cutscene.h"
#include "game/event/scene.h"

/*
 * Main runtime: game-state loops, graphics frame setup and submission,
 * plus the transition fades (style fade_transition_style).
 * Original file: 1870.c (ROM 0x1870).
 */

/* This file's .bss, 8007A170..8007A8C0, in address order (see 3F50.c's block
 * for IDO's ordering rules). nnsc_retrace_count just before it (the retrace counter
 * that 1130.c increments) and 8007A8C0..8007A8F0 stay in the asm slab.
 * D_8007A254 (a queue inside core_sched) and the low words D_8007A8AC and
 * D_8007A8BC are aliases in undefined_syms.txt. D_8007A194..D_8007A19C,
 * D_8007A1A4, D_8007A1CE, D_8007A1DC and D_8007A864 are
 * unreferenced gaps. core_sched (NNSched) is 8-aligned, so its size is 0x680:
 * 8007A85C is its tail padding. */
u16 core_game_mode; /* loop: 1 gameplay, 2 menu, 3 title, 4 intro, 5 ending, 6/7 cutscenes (0 = 1) */
u16 D_8007A172;
s32 core_transition_timer;
u16 fade_transition_style;
u16 core_fade_out_time;
s32 gfx_frame_index;
s32 gfx_mtx_index;
Gfx *gfx_dl_head;
s32 gfx_clear_r;
s32 gfx_clear_g;
u32 gfx_clear_b;
s32 D_8007A194;
s32 D_8007A198;
s32 D_8007A19C;
s16 gfx_fog_near;
s16 gfx_fog_far;
s32 D_8007A1A4;
OSMesgQueue dma_mesg_queue;
OSMesg dma_mesg;
s32 D_8007A1C4;
s32 gfx_scene_light_slot;
u8 title_menu_choice;
s8 D_8007A1CD;
s16 D_8007A1CE;
s32 gfx_frame_sent;
s32 gfx_dl_peak_len;
void *gfx_segment1_base;
s32 D_8007A1DC;
NNSched core_sched;
OSMesgQueue *gfx_sched_mq;
s32 D_8007A864;
NNScClient gfx_sched_client;
OSMesgQueue gfx_mesg_queue;
OSMesg gfx_mesgs[8];
u64 core_frame_start_time;
u64 core_frame_end_time;
u64 D_8007A8B8;

/* Not declared by any module header (H2b):
 * - the PakMenu overlay's entry (PakMenu_Run, ovl_DA4570 at 0x80100000) and the title,
 *   intro and ending overlays' entry and per-frame functions, called by address: the
 *   three overlays share 0x8020C0D0 (overlay_load.c);
 * - ROM addresses (linker symbols), the RSP microcode (SDK binaries), segment symbols
 *   and the fixed RAM buffers (segment 1 data, framebuffers, depth buffer, RSP stacks). */
s32 func_801009EC(OSMesgQueue *mq, OSMesgQueue *arg1); /* PakMenu_Run */
void func_8020C0D0(void);  /* Title_Init / Intro_Init / Ending_Init */
s32 func_8020C11C(void);   /* Title_Update */
s32 func_8020C15C(void);   /* Ending_Update */
s32 func_8020C16C(void);   /* Intro_Update */

extern u8 D_71920[];
extern u8 D_753F0[];
extern u8 D_D490C0[];
extern u8 D_D74AC0[];
extern u8 D_D86170[];
extern u8 D_DA4570[];
extern u8 D_DAB5F0[];
extern u8 D_E420D0[];
extern u8 D_E43780[];
extern u8 D_E5BF60[];
extern u8 D_E5ED70[];
extern u8 D_E98330[];
extern u8 D_ECB7B0[];
extern u8 D_ECD470[];

extern u64 D_8004B980[]; /* rspboot text */
extern u64 D_8004BA50[]; /* gfx ucode text (= rspboot end) */
extern u64 D_80070260[]; /* gfx ucode data */

extern u8 D_1000010[];

extern u8 D_80095AF0[];
extern u8 D_800C0000[];
extern u8 D_80100000[];
extern u8 D_801C0000[];
extern u16 D_802DA800[];
extern u64 D_80300000[];
extern u64 D_80300400[];
extern u64 D_8031C5A0[];
extern u64 D_803245A0[];
extern u8 D_8039ADB0[];
extern u16 D_803B5000[];
extern u16 D_803DA800[];

/* Bits seen in this file: 1 run Item_UpdateInventoryMenu, 2 run Text_UpdateAndDrawWindows,
 * 0x20 fade in at loop start, 0x40 load the area at loop start, 0x80 transition countdown,
 * 0x100 start the map's BGM, 0x200 stop sequence 0 at loop end, 0x4000 hide the HUD,
 * 0x8000 leave the mode loop and reinitialise, 0x10000 don't draw the player. */
s32 core_flags = 0;

void Core_MainThread(void *arg0) {
    osCreateViManager(0xFE);
    osCreateMesgQueue(&dma_mesg_queue, &dma_mesg, 1);
    Audio_Init();
    /* the ROM end symbols don't exist yet: ends are written start + size */
    Audio_InitSeqPlayers(D_E5BF60, D_E5BF60 + 0x2E10, D_E98330, D_E98330 + 0x33480, D_E5ED70);
    Audio_InitSoundPlayer(D_ECB7B0, D_ECB7B0 + 0x1CC0, D_ECD470);
    nnScCreateScheduler(&core_sched, 1);
    Input_InitControllers();
    if (osTvType == OS_TV_NTSC) {
        osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    } else {
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
    }
    osViBlack(1);
    Dma_ReadRom(D_DA4570, D_80100000, D_DAB5F0 - D_DA4570);
    Text_LoadFontAssets();
    func_801009EC(&input_si_queue, &core_sched.retraceMQ);
    osViBlack(1);
    osViSetSpecialFeatures(0x5A);
    nnScStartScheduler(&core_sched);
    Audio_StartThread(&core_sched);
    osCreateMesgQueue(&gfx_mesg_queue, gfx_mesgs, 8);
    nnScAddClient(&core_sched, &gfx_sched_client, &gfx_mesg_queue);
    gfx_sched_mq = nnScGetGfxMQ(&core_sched);
    Gfx_InitFrames();

    while (1) {
        Boss_ClearDefeated();
        Chest_ClearOpenedFlags();
        Spirit_ClearCollectedFlags();
        Player_Init();
        Item_InitInventory();
        Env_InitClock();
        Text_LoadFontAssets();
        Bgm_Init();
        Core_ResetGameState();
        Menu_Init();
    loop:
        core_flags &= ~3;
        if (core_game_mode == 0) {
            core_game_mode = 1;
        }
        switch (core_game_mode) {
            case 1:
                Core_RunGameplayLoop();
                break;
            case 6:
                Core_RunMessageCutsceneLoop();
                break;
            case 7:
                Core_RunCameraCutsceneLoop();
                break;
            case 2:
                Core_RunMenuLoop();
                break;
            case 3:
                Core_RunTitleLoop();
                break;
            case 4:
                Core_RunIntroLoop();
                break;
            case 5:
                Core_RunEndingLoop();
                break;
        }
        if (!(core_flags & 0x8000)) {
            goto loop;
        }
    }
}

void Core_ResetGameState(void) {
    core_flags &= 0x20000;
    core_flags |= 0x160;
    core_game_mode = 4;
    map_id = -1;
    map_flag4_return_map = -1;
    map_flag8_return_map = -1;
    map_backdrop_id = 0xFFFF;
    camera_state.unk84 = 0.0f;
    env_play_time = 0;
    map_next_id = 0xD;
    map_next_subarea = 0x11;
    exit_destination.entry = -1;
    player_respawn_map = 0xD;
    player_respawn_subarea = 0x11;
    player_respawn_entry = 0;
    player_spawn_x = -26.0f;
    player_spawn_z = 0.0f;
    player_spawn_rot = 1.5707964f;
    player_spawn_type = 0x108;
    player_state.unk6 = 0;
    hud_panel_transition_state = 1;
    hud_panel_transition_frame = 0xC;
    hud_mp_meter_width *= 0;
    hud_hp_meter_width = 0;
    D_8007A172 = 1;
    fade_transition_style = 0;
    title_menu_choice = 0;
    D_8007A1CD = 0;
}

void Gfx_InitFrames(void) {
    u16 *b;
    u16 *a;
    u32 i;

    Dma_ReadRom(D_71920, D_80095AF0, D_753F0 - D_71920);
    gfx_segment1_base = D_80095AF0;
    Dma_ReadRom(D_D490C0, D_800C0000, D_D74AC0 - D_D490C0);
    a = D_8039ADB0;
    Dma_ReadRom(D_D74AC0, a, D_D86170 - D_D74AC0);
    D_80301000[0].data.msg = 2;
    D_80301000[0].data.framebuffer = D_803B5000;
    Gfx_InitFrameTask(&D_80301000[0]);
    D_80301000[1].data.msg = 2;
    D_80301000[1].data.framebuffer = D_803DA800;
    Gfx_InitFrameTask(&D_80301000[1]);
    gfx_frame_index = 0;
    i = 320 * 240;
    b = D_803B5000;
    a = D_803DA800;
    while (i != 0) {
        *a = 0;
        *b = 0;
        b++;
        a++;
        i--;
    }
}

void Gfx_InitFrameTask(GfxFrame *arg0) {
    arg0->task.list.t.type = M_GFXTASK;
    arg0->task.list.t.flags = 0;
    arg0->task.list.t.ucode_boot = D_8004B980;
    arg0->task.list.t.ucode_boot_size = (u32)&D_8004B980[0xD0 / 8] - (u32)D_8004B980;
    arg0->task.list.t.ucode = D_8004BA50;
    arg0->task.list.t.ucode_data = D_80070260;
    arg0->task.list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    arg0->task.list.t.dram_stack = D_80300000;
    arg0->task.list.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    arg0->task.list.t.output_buff = D_8031C5A0;
    arg0->task.list.t.output_buff_size = D_803245A0;
    arg0->task.list.t.yield_data_ptr = D_80300400;
    arg0->task.list.t.yield_data_size = OS_YIELD_DATA_SIZE;
    arg0->task.next = NULL;
    arg0->task.flags = NN_SC_SWAPBUFFER;
    arg0->task.msgQ = &gfx_mesg_queue;
    arg0->task.msg = &arg0->data.msg;
    arg0->task.framebuffer = arg0->data.framebuffer;
}

s32 D_8004DCA4 = 0;

void Gfx_BuildFrameDisplayList(GfxFrame *arg0) {
    s32 count;
    s32 one = 1;
    GfxFrameData *sub;

    gfx_dl_head = arg0->data.dl;

    gSPSegment(gfx_dl_head++, 0x00, 0x00000000);
    gSPSegment(gfx_dl_head++, 0x01, osVirtualToPhysical(gfx_segment1_base));
    gSPSegment(gfx_dl_head++, 0x02, osVirtualToPhysical(sub = &arg0->data));
    gSPDisplayList(gfx_dl_head++, D_1000010);
    gDPSetDepthImage(gfx_dl_head++, osVirtualToPhysical(D_802DA800));
    gDPPipeSync(gfx_dl_head++);
    gDPSetCycleType(gfx_dl_head++, G_CYC_FILL);
    gDPSetColorImage(gfx_dl_head++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_802DA800));
    gDPSetFillColor(gfx_dl_head++, 0xFFFCFFFC);
    gDPFillRectangle(gfx_dl_head++, 8, 8, 311, 231);
    gDPPipeSync(gfx_dl_head++);
    gDPSetColorImage(gfx_dl_head++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(arg0->data.framebuffer));

    if (core_game_mode == 1 || core_game_mode == 6 || core_game_mode == 7) {
        gDPSetFillColor(gfx_dl_head++, (GPACK_RGBA5551(gfx_clear_r, gfx_clear_g, gfx_clear_b, 1) << 16) |
                                          GPACK_RGBA5551(gfx_clear_r, gfx_clear_g, gfx_clear_b, 1));
        gDPFillRectangle(gfx_dl_head++, 8, 8, 311, 231);
    } else {
        gDPSetFillColor(gfx_dl_head++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(gfx_dl_head++, 8, 8, 311, 231);
    }
    gDPPipeSync(gfx_dl_head++);
    gDPSetCycleType(gfx_dl_head++, G_CYC_2CYCLE);

    if (core_game_mode == 1 || core_game_mode == 6 || core_game_mode == 7) {
        Camera_Update(sub);
        Env_PrepareFrameLighting();
        if (map_env_flags & 4) {
            Env_ApplyLightSlot(gfx_scene_light_slot);
            Map_DrawBackdrop(sub);
        }
        Env_ApplyLightSlot(gfx_scene_light_slot);
        MapObj_UpdateAndDrawNearby(sub);
        if (!(core_flags & 0x10000)) {
            Player_Draw(sub);
        }
        Npc_DrawAll(sub);
        Chest_UpdateAll(sub);
        MapObj_DrawTranslucent(sub);
        Enemy_DrawAll(sub);
        Boss_Draw(sub);
        Spirit_SpawnSparkles();
        Env_ApplyLightSlot(player_light_slot);
        Shadow_DrawAll(sub);
        Effect_UpdateAndDrawSprites(sub);
        Effect_UpdateAndDrawAll(sub);
        Fade_UpdateAndDraw(sub);
        if (core_flags & 2) {
            Text_UpdateAndDrawWindows();
        }
        if (!(core_flags & 0x4000) && (D_8007A172 != 4)) {
            Hud_Draw(sub);
        }
        if (core_flags & 1) {
            Item_UpdateInventoryMenu();
        }
        if (core_game_mode == 7) {
            Cutscene_UpdateAndDrawImageCues();
        }
    } else if (core_game_mode == 2) {
        Menu_Update(sub);
    } else if (core_game_mode == 3) {
        switch (func_8020C11C()) {
            case 0:
                switch (title_menu_choice & 0xF0) {
                    case 0x10:
                        core_game_mode = 1;
                        core_flags &= ~0x400;
                        break;
                    case 0x20:
                        core_flags |= 0x400;
                        SaveMenu_Init(0);
                        break;
                    case 0x30:
                        core_flags |= 0x400;
                        SaveMenu_Init(8);
                        break;
                    default:
                        core_game_mode = 1;
                        break;
                }
                break;
            case 1:
                core_game_mode = 4;
                break;
        }
    } else if (core_game_mode == 4) {
        switch (func_8020C16C()) {
            case 0:
                D_8006CC80[0] = 0;
                core_game_mode = 3;
                break;
            case 1:
                D_8006CC80[0] = one;
                core_game_mode = 3;
                break;
            default:
                D_8006CC80[0] = 0;
        }
    } else if (core_game_mode == 5) {
        count = func_8020C15C();
        Fade_UpdateAndDraw(sub);
        if (count == 0) {
            core_game_mode = 7;
        }
    }
    gDPFullSync(gfx_dl_head++);
    gSPEndDisplayList(gfx_dl_head++);
    osWritebackDCache(&D_2000000, 0xDA70);

    count = gfx_dl_head - arg0->data.dl;
    if (gfx_dl_peak_len < count) {
        gfx_dl_peak_len = count;
    }
    D_8004DCA4 = count;

    arg0->task.list.t.data_ptr = (u64 *)sub->dl;
    arg0->task.list.t.data_size = (gfx_dl_head - sub->dl) * sizeof(Gfx);
}

void Core_RunGameplayLoop(void) {
    OSMesg msg;
    GfxFrame *frame;

    gfx_frame_sent = 0;
    core_transition_timer = 0;
    msg = NULL;
    if (core_flags & 0x40) {
        if (core_flags & 0x800) {
            map_id = player_respawn_map;
            map_subarea = player_respawn_subarea;
            Player_SetSpawnFromSaveTable();
        }
        Text_ResetAllWindows(0);
        text_active_window_count = 0;
        Map_LoadArea();
        Chest_LoadForMap();
        Spirit_LoadForMap();
        TextSpot_LoadForMap();
        Menu_FindMapPageLocation();
        Player_Spawn();
        Npc_InitArea();
        Enemy_InitForArea();
        Boss_LoadForArea();
        Camera_InitForMap();
        Env_InitForMap();
        gfx_scene_light_slot = Env_AllocateLightSlot();
        D_8007A1C4 = Env_AllocateLightSlot();
        player_light_slot = Env_AllocateLightSlot();
        env_light_slots[player_light_slot].unk0 = 2;
        Battle_ResetState();
        Magic_ResetEffectSystem();
        Effect_ResetAll();
        Effect_ResetSpritePool();
        Fade_Init();
        Hud_ResetState();
        core_flags &= ~0x840;
    }
    if (core_flags & 0x400) {
        Anim_SetCurrentAndNext(&player_state.actor, 0, 1, 0, 1, 1);
    }
    if (core_flags & 0x20) {
        core_flags &= ~0x20;
        Fade_StartTransitionIn();
    }
    if (core_flags & 0x100) {
        Bgm_PlayForMap(map_id, map_subarea, 0);
        core_flags &= ~0x100;
    }
    core_flags &= ~0x480;
    fade_transition_style = 0;
    core_fade_out_time = 0x12;
    D_8007A172 = 0;
    while (core_game_mode == 1) {
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        effect_mapobj_emitter_count = 0;
        Shadow_ClearQueue();
        if (map_subarea_flags & 1) {
            Battle_TryStartRandomEncounter();
        }
        if (battle_flags & 1) {
            if (battle_flags & 0x200) {
                Battle_UpdateStartCamera();
            } else {
                Battle_UpdateTurnTransition();
                Enemy_UpdateAll();
            }
        }
        Player_Update();
        Npc_UpdateAll();
        Magic_UpdateEffects();
        Env_Update();
        Map_StartFrame();
        MapObjAnim_UpdateAll();
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (!(core_flags & 0x87)) {
            if (!(player_state.actor.animFlags & 1) && Exit_CheckEnter(player_state.actor.x, player_state.actor.z, player_state.actor.rot) != 0) {
                core_flags |= 0x80;
                Camera_TurnForExit();
                Player_StartAreaExit();
                fade_transition_style = 0;
            } else if (!(core_flags & 0x1000) && !(player_state.actor.animFlags & 1) && (input_pressed_buttons & 0x1000) &&
                       !(battle_flags & 1) && !(input_held_buttons & 0x2000) && !(core_flags & 1)) {
                core_game_mode = 2;
                Sfx_Play(0, 1, 0xFF);
            }
        } else if ((core_flags & 0x80) && !(core_flags & 2)) {
            if (--core_transition_timer == 0) {
                if (D_8007A172 == 4) {
                    core_game_mode = 6;
                } else {
                    core_game_mode = 0;
                }
                core_flags |= 0x20;
                if (!(core_flags & 0x400)) {
                    core_flags |= 0x40;
                }
                map_next_id = exit_destination.map;
                map_next_subarea = exit_destination.subarea;
                if (core_flags & 0x400) {
                    player_state.unk14->unk4 = player_state.unk14->unk6;
                    player_state.unk14->unk8 = player_state.unk14->unkA;
                    env_clock += 0x2328;
                    Env_SetClock(env_clock);
                    player_respawn_map = map_id;
                    player_respawn_subarea = map_subarea;
                    player_respawn_entry = exit_destination.entry;
                    fade_transition_style = 2;
                }
                core_flags |= 0x100;
                Sfx_StopAllChannels();
            } else if (core_transition_timer == core_fade_out_time) {
                Fade_StartTransitionOut();
            }
        }
        Bgm_Update();
        if (audio_pending_seq_id != -1 && Audio_GetSeqState(0) == 0) {
            Audio_LoadSeq(0, audio_pending_seq_id);
            Audio_PlaySeq(0);
            audio_pending_seq_id = -1;
        }
        core_frame_end_time = osGetTime();
        D_8007A8B8 = (core_frame_end_time - core_frame_start_time) * 64 / 3000;
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
            while (nnsc_retrace_count < 2) {
                osRecvMesg(&gfx_mesg_queue, &msg, OS_MESG_BLOCK);
            }
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        nnsc_retrace_count = 0;
        gfx_frame_index ^= 1;
        core_frame_start_time = osGetTime();
    }
    if (core_flags & 0x200) {
        Audio_StopSeq(0);
    }
    Gfx_WaitForFrameMessage(2);
    if (core_flags & 0x200) {
        core_flags &= ~0x200;
        while (Audio_GetSeqState(0) != 0) {
        }
    }
    if (core_flags & 0x400) {
        SaveMenu_Init(4);
    }
}

void Core_RunMessageCutsceneLoop(void) {
    s32 count;
    GfxFrame *frame;
    OSMesg msg;

    count = 0;
    msg = NULL;
    Dma_ReadRom(D_E420D0, D_801C0000, D_E43780 - D_E420D0);
    core_transition_timer = 0;
    fade_transition_style = 3;
    env_clock = 0x41EB;
    while (core_game_mode == 6) {
        if (core_flags & 0x40) {
            gfx_frame_sent = 0;
            Cutscene_StartEntry(count++);
            Env_InitForMap();
            gfx_scene_light_slot = Env_AllocateLightSlot();
            D_8007A1C4 = Env_AllocateLightSlot();
            player_light_slot = Env_AllocateLightSlot();
            env_light_slots[player_light_slot].unk0 = 2;
            Fade_Init();
            fade_flags |= 8;
            if (core_flags & 0x20) {
                core_flags &= ~0x20;
                Fade_StartTransitionIn();
            }
            core_flags &= ~0x1C0;
        }
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        effect_mapobj_emitter_count = 0;
        Shadow_ClearQueue();
        if (Cutscene_UpdateMessageSequence() != 0) {
            Cutscene_StartAudioFadeForEntry(count);
        }
        Env_Update();
        Map_StartFrame();
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (core_flags & 0x80) {
            if (--core_transition_timer == 0) {
                Sfx_StopAllChannels();
                if (count >= 7) {
                    core_game_mode = 5;
                    core_flags |= 0x160;
                } else {
                    core_flags |= 0x160;
                }
            } else if (core_transition_timer == core_fade_out_time) {
                Fade_StartTransitionOut();
            }
        }
        Bgm_Update();
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
            while (nnsc_retrace_count < 2) {
                osRecvMesg(&gfx_mesg_queue, &msg, OS_MESG_BLOCK);
            }
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        nnsc_retrace_count = 0;
        gfx_frame_index ^= 1;
        if (core_flags & 0x40) {
            Gfx_WaitForFrameMessage(2);
            gfx_frame_sent = 0;
        }
    }
    if (core_flags & 0x200) {
        Audio_StopSeq(0);
    }
    if (core_flags & 0x200) {
        core_flags &= ~0x200;
        while (Audio_GetSeqState(0) != 0) {
        }
    }
}

void Core_RunCameraCutsceneLoop(void) {
    s32 count;
    OSMesg msg;
    GfxFrame *frame;

    msg = NULL;
    Dma_ReadRom(D_E43780, D_801C0000, D_E5BF60 - D_E43780);
    core_transition_timer = 0;
    fade_transition_style = 2;
    sfx_master_volume = 0;
    Cutscene_ResetSequence();
    while (core_game_mode == 7) {
        if (core_flags & 0x40) {
            gfx_frame_sent = 0;
            Cutscene_StartNextScene();
            Env_InitForMap();
            gfx_scene_light_slot = Env_AllocateLightSlot();
            D_8007A1C4 = Env_AllocateLightSlot();
            player_light_slot = Env_AllocateLightSlot();
            env_light_slots[player_light_slot].unk0 = 2;
            Fade_Init();
            fade_flags |= 8;
            if (core_flags & 0x20) {
                core_flags &= ~0x20;
                Fade_StartTransitionIn();
            }
            core_flags &= ~0xC0;
        }
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        effect_mapobj_emitter_count = 0;
        Shadow_ClearQueue();
        Cutscene_UpdateScene();
        Env_Update();
        Map_StartFrame();
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (core_flags & 0x80) {
            if (--core_transition_timer == 0) {
                Sfx_StopAllChannels();
                Cutscene_EndScene();
            } else if (core_transition_timer == core_fade_out_time) {
                Fade_StartTransitionOut();
            }
        }
        Bgm_Update();
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
            while (nnsc_retrace_count < 2) {
                osRecvMesg(&gfx_mesg_queue, &msg, OS_MESG_BLOCK);
            }
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        nnsc_retrace_count = 0;
        gfx_frame_index ^= 1;
        if (core_flags & 0x40) {
            Gfx_WaitForFrameMessage(2);
            gfx_frame_sent = 0;
        }
    }
    if (core_flags & 0x200) {
        Audio_StopSeq(0);
    }
    if (core_flags & 0x200) {
        core_flags &= ~0x200;
        while (Audio_GetSeqState(0) != 0) {
        }
    }
    core_flags |= 0x20000;
}

void Core_RunMenuLoop(void) {
    GfxFrame *frame;

    gfx_frame_sent = 0;
    menu_save_loaded = 0;
    if (core_flags & 0x400) {
        Bgm_Play(0x13);
    }
    while (core_game_mode == 2) {
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        Bgm_Update();
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        gfx_frame_index ^= 1;
    }
    if (core_flags & 0x400) {
        Bgm_Play(-1);
        while (bgm_current != -1) {
            Bgm_Update();
        }
    }
    if (menu_save_loaded != 0) {
        Player_SetSpawnFromSaveTable();
        D_8007A172 = 2;
        core_flags &= ~0x400;
    }
    Bgm_ApplyVolumeOption();
    Gfx_WaitForFrameMessage(2);
}

void Core_RunTitleLoop(void) {
    GfxFrame *frame;

    gfx_frame_sent = 0;
    Overlay_LoadTitle();
    func_8020C0D0();
    while (core_game_mode == 3) {
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        gfx_frame_index ^= 1;
    }
    Gfx_WaitForFrameMessage(2);
}

void Core_RunIntroLoop(void) {
    GfxFrame *frame;

    gfx_frame_sent = 0;
    Overlay_LoadIntro();
    func_8020C0D0();
    while (core_game_mode == 4) {
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        Bgm_Update();
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        gfx_frame_index ^= 1;
    }
    Bgm_Play(-1);
    Bgm_Update();
    Gfx_WaitForFrameMessage(2);
}

void Core_RunEndingLoop(void) {
    GfxFrame *frame;

    gfx_frame_sent = 0;
    Overlay_LoadEnding();
    func_8020C0D0();
    Fade_Init();
    fade_flags |= 8;
    Bgm_PlayDelayed(0x14, 0x3C);
    while (core_game_mode == 5) {
        Input_ReadController(input_primary_port);
        gfx_mtx_index = 0;
        Bgm_Update();
        Gfx_BuildFrameDisplayList(&D_80301000[gfx_frame_index]);
        frame = &D_80301000[gfx_frame_index];
        if (gfx_frame_sent == 0) {
            gfx_frame_sent++;
            Gfx_WaitForFrameMessage(1);
        } else {
            Gfx_WaitForFrameMessage(2);
        }
        osSendMesg(gfx_sched_mq, frame, OS_MESG_BLOCK);
        gfx_frame_index ^= 1;
    }
    Gfx_WaitForFrameMessage(2);
}

void Gfx_WaitForFrameMessage(s16 arg0) {
    OSMesg msg = NULL;

    do {
        osRecvMesg(&gfx_mesg_queue, &msg, OS_MESG_BLOCK);
    } while (arg0 != *(s16 *)msg);
}

void Fade_StartTransitionIn(void) {
    switch (fade_transition_style) {
        case 0:
            Fade_Start(0x10, 4, fade_black_ramp_end);
            break;
        case 1:
            Fade_Start(0x10, 4, fade_grey_ramp_end);
            break;
        case 2:
            Fade_Start(0x20, 4, fade_black_ramp_slow_end);
            break;
        case 3:
            Fade_Start(0x20, 4, fade_grey_ramp_slow_end);
            break;
        case 4:
            Fade_Start(0x100, 4, &fade_grey_ramp_256[0xFF]);
            break;
    }
}

void Fade_StartTransitionOut(void) {
    switch (fade_transition_style) {
        case 0:
            Fade_Start(0xF, 2, fade_black_ramp);
            break;
        case 1:
            Fade_Start(0xF, 2, fade_grey_ramp);
            break;
        case 2:
            Fade_Start(0x1F, 2, fade_black_ramp_slow);
            break;
        case 3:
            Fade_Start(0x1F, 2, fade_grey_ramp_slow);
            break;
        case 4:
            Fade_Start(0xFF, 2, fade_grey_ramp_256);
            break;
    }
}
