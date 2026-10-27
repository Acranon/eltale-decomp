#include "common.h"

/*
 * Scripted scene entry setup, timed messages, and transition audio.
 * Original file: 3B40.c (ROM 0x3B40).
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ s16 unk3E;
} Unk801C14E4; /* size 0x40 */

typedef struct {
    /* 0x0 */ u8 *unk0;
    /* 0x4 */ u8 *unk4;
    /* 0x8 */ u8 unk8;
} Unk8007A8E8; /* size 0xC */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 unk4[0x8];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Unk80085E48;

typedef struct {
    /* 0x0 */ u8 unk0[0x4];
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
} Unk8007A9D0;

typedef struct {
    /* 0x00 */ u8 unk0[0x12];
    /* 0x12 */ u16 unk12;
} Unk8007C288;

void Player_Spawn(void);
void Cutscene_CopyMessageBuffers(u8 *arg0, u8 *arg1);
void func_80009764(u16 arg0);
void Npc_SpawnForArea(s32 arg0, s32 arg1);
void Map_LoadArea(void);
void Camera_InitForMap(void);
void Math_MtxFRotate(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3);
void Math_MtxFMulVecNegZ(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6);
void Audio_StartSeqFadeOut(s32 arg0);
void Bgm_Play(s8 arg0);
void Text_ResetAllWindows(s32 arg0, s32 arg1);
void Text_OpenWindow(u8 arg0);

/* This file's .bss, 8007A8C0..8007A8F0, in address order. D_8007A8C0 and
 * D_8007A8EC are unreferenced gaps (D_8007A8C0 could as well be 1870.c's tail). */
u8 D_8007A8C0[0x20];
s32 cutscene_message_wait_frames;
s32 cutscene_messages_remaining;
Unk8007A8E8 *cutscene_next_message;
s32 D_8007A8EC;

extern s32 core_flags;
extern s32 core_transition_timer;
extern u16 fade_transition_style;
extern s16 core_fade_out_time;
extern f32 player_spawn_x;
extern f32 player_spawn_z;
extern f32 player_spawn_rot;
extern s32 player_spawn_type;
extern Unk8007A9D0 player_stats;
extern s16 D_8007AA0E;
extern s32 npc_count;
extern u8 text_message_buf[];
extern u8 text_speaker_name[];
extern s32 enemy_count;
extern Unk8007C288 *map_subarea_def;
extern s32 map_id;
extern s32 map_next_id;
extern s32 map_next_subarea;
extern s32 D_80084308;
extern Unk80085E48 camera_state;
extern f32 D_80085E54;
extern f32 D_80085E58;
extern f32 D_80085E5C;
extern f32 D_80085E60;
extern f32 D_80085E64;
extern f32 D_80085E68;
extern f32 camera_fovy;
extern s32 text_active_window_count;
extern Unk801C14E4 D_801C14E4[];

void Cutscene_StartEntry(s32 arg0) {
    Unk801C14E4 *entry = &D_801C14E4[arg0];
    f32 mtx[4][4];

    cutscene_next_message = entry->unk34;
    cutscene_messages_remaining = entry->unk38;
    cutscene_message_wait_frames = 0x3C;
    map_id = -1;
    map_next_id = entry->unk0;
    map_next_subarea = entry->unk4;
    Text_ResetAllWindows(0, arg0);
    text_active_window_count = 0;
    D_80084308 = -1;
    Map_LoadArea();
    player_spawn_x = entry->unk20;
    player_spawn_z = entry->unk24;
    player_spawn_rot = entry->unk28;
    player_spawn_type = 0x108;
    D_8007AA0E = 0;
    player_stats.unk4 = player_stats.unk6;
    Player_Spawn();
    if (!(entry->unk3C & 1)) {
        core_flags |= 0x10000;
    }
    npc_count = 0;
    func_80009764(map_subarea_def->unk12);
    Npc_SpawnForArea(entry->unk2C, entry->unk30);
    enemy_count = 0;
    Camera_InitForMap();
    camera_state.unk0 = 3;
    D_80085E54 = entry->unk8;
    D_80085E58 = entry->unkC;
    D_80085E5C = entry->unk10;
    Math_MtxFRotate(mtx, -entry->unk14 * 0.017453292519943295, -entry->unk18 * 0.017453292519943295, 0.0f);
    Math_MtxFMulVecNegZ(mtx, 0.0f, 0.0f, -100.0f, &D_80085E60, &D_80085E64, &D_80085E68);
    camera_state.unk18 = camera_state.unk18 + camera_state.unkC;
    camera_state.unk1C = camera_state.unk1C + camera_state.unk10;
    camera_state.unk20 = camera_state.unk14 - camera_state.unk20;
    camera_fovy = entry->unk1C;
    Bgm_Play(((s8 *)&entry->unk3E)[1]);
}

s32 Cutscene_UpdateMessageSequence(void) {
    s32 ret = 0;

    if (cutscene_message_wait_frames == 0) {
        if (cutscene_messages_remaining != 0) {
            Cutscene_CopyMessageBuffers(cutscene_next_message->unk0, cutscene_next_message->unk4);
            Text_OpenWindow(cutscene_next_message->unk8);
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
    Unk801C14E4 *entry;

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
