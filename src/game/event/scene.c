#include "game/event/scene.h"
#include "game/env/env.h"
#include "game/audio/audio.h"
#include "game/audio/sound.h"
#include "game/camera/camera.h"
#include "game/core/main.h"
#include "game/enemy/enemy.h"
#include "game/map/map.h"
#include "game/math/math.h"
#include "game/npc/npc.h"
#include "game/player/player.h"
#include "game/text/text_window.h"

/*
 * Scripted scene entry setup, timed messages, and transition audio.
 * Original file: 3B40.c (ROM 0x3B40).
 */





/* This file's .bss, 8007A8C0..8007A8F0, in address order. D_8007A8C0 and
 * D_8007A8EC are unreferenced gaps (D_8007A8C0 could as well be 1870.c's tail). */
u8 D_8007A8C0[0x20];
s32 cutscene_message_wait_frames;
s32 cutscene_messages_remaining;
SceneMessage *cutscene_next_message;
s32 D_8007A8EC;

extern SceneEntry D_801C14E4[];

void Cutscene_StartEntry(s32 arg0) {
    SceneEntry *entry = &D_801C14E4[arg0];
    f32 mtx[4][4];

    cutscene_next_message = entry->messages;
    cutscene_messages_remaining = entry->message_count;
    cutscene_message_wait_frames = 0x3C;
    map_id = -1;
    map_next_id = entry->unk0;
    map_next_subarea = entry->unk4;
    Text_ResetAllWindows(0);
    text_active_window_count = 0;
    exit_destination.entry = -1;
    Map_LoadArea();
    player_spawn_x = entry->unk20;
    player_spawn_z = entry->unk24;
    player_spawn_rot = entry->unk28;
    player_spawn_type = 0x108;
    player_state.unk6 = 0;
    player_stats.unk4 = player_stats.unk6;
    Player_Spawn();
    if (!(entry->unk3C & 1)) {
        core_flags |= 0x10000;
    }
    npc_count = 0;
    func_80009764(map_subarea_def->areaSetIndex);
    Npc_SpawnForArea(entry->unk2C, entry->unk30);
    enemy_count = 0;
    Camera_InitForMap();
    camera_state.mode = 3;
    camera_state.eyeX = entry->unk8;
    camera_state.eyeY = entry->unkC;
    camera_state.eyeZ = entry->unk10;
    Math_MtxFRotate(mtx, -entry->unk14 * 0.017453292519943295, -entry->unk18 * 0.017453292519943295, 0.0f);
    Math_MtxFMulVecNegZ(mtx, 0.0f, 0.0f, -100.0f, &camera_state.atX, &camera_state.atY, &camera_state.atZ);
    camera_state.atX = camera_state.atX + camera_state.eyeX;
    camera_state.atY = camera_state.atY + camera_state.eyeY;
    camera_state.atZ = camera_state.eyeZ - camera_state.atZ;
    camera_fovy = entry->unk1C;
    Bgm_Play(((s8 *)&entry->unk3E)[1]);
}

s32 Cutscene_UpdateMessageSequence(void) {
    s32 ret = 0;

    if (cutscene_message_wait_frames == 0) {
        if (cutscene_messages_remaining != 0) {
            Cutscene_CopyMessageBuffers(cutscene_next_message->text, cutscene_next_message->speaker_name);
            Text_OpenWindow(cutscene_next_message->window_type);
            cutscene_message_wait_frames = 0xF;
            cutscene_next_message++;
            cutscene_messages_remaining--;
        } else {
            core_flags |= 0x80;
            core_transition_timer = 0x31;
            fade_transition_style = 2;
            core_fade_out_time = 0x2F;
            cutscene_message_wait_frames = 0x32;
            ret = 1;
        }
    } else if (text_active_window_count == 0) {
        cutscene_message_wait_frames--;
    }
    return ret;
}

void Cutscene_StartAudioFadeForEntry(u32 arg0) {
    SceneEntry *entry;

    if (arg0 > 6) {
        Audio_StartSeqFadeOut(0x40);
    } else {
        entry = &D_801C14E4[arg0];
        if (entry->unk3E != (entry - 1)->unk3E) {
            Audio_StartSeqFadeOut(0x40);
        }
    }
}

void Cutscene_CopyMessageBuffers(u8 *arg0, u8 *arg1) {
    s32 i;
    u8 *dst;

    dst = text_message_buf;
    for (i = 0x4B0; i != 0; i--) {
        *dst++ = *arg0++;
    }
    dst = text_speaker_name;
    for (i = 0x20; i != 0; i--) {
        *dst++ = *arg1++;
    }
}
