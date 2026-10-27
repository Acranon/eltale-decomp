#ifndef GAME_EVENT_SCENE_H
#define GAME_EVENT_SCENE_H

#include "common.h"

typedef struct SceneMessage {
    /* 0x00 */ u8 *text;
    /* 0x04 */ u8 *speaker_name;
    /* 0x08 */ u8 window_type;
} SceneMessage; /* 0xC bytes */

typedef struct SceneEntry {
    /* 0x00 */ s32 map_id;
    /* 0x04 */ s32 subarea;
    /* 0x08 */ f32 camera_eye_x;
    /* 0x0C */ f32 camera_eye_y;
    /* 0x10 */ f32 camera_eye_z;
    /* 0x14 */ f32 camera_pitch_deg;
    /* 0x18 */ f32 camera_yaw_deg;
    /* 0x1C */ f32 camera_fovy;
    /* 0x20 */ f32 spawn_x;
    /* 0x24 */ f32 spawn_z;
    /* 0x28 */ f32 spawn_rot;
    /* 0x2C */ s32 npc_defs_addr;
    /* 0x30 */ s32 npc_count;
    /* 0x34 */ SceneMessage *messages;
    /* 0x38 */ s32 message_count;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ s16 unk3E;
} SceneEntry; /* 0x40 bytes */

extern u8 D_8007A8C0[0x20];
extern s32 cutscene_message_wait_frames;
extern s32 cutscene_messages_remaining;
extern SceneMessage *cutscene_next_message;
extern s32 D_8007A8EC;

void Cutscene_StartEntry(s32 arg0);
s32 Cutscene_UpdateMessageSequence(void);
void Cutscene_StartAudioFadeForEntry(u32 arg0);
void Cutscene_CopyMessageBuffers(u8 *arg0, u8 *arg1);

#endif
