#ifndef GAME_UI_HUD_H
#define GAME_UI_HUD_H

#include "common.h"
#include "game/actor/actor.h"
#include "game/player/player.h"
#include "game/math/math.h"

struct GfxFrameData;

typedef struct HudPopup {
    /* 0x00 */ u16 remaining_frames;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ Actor *actor;
    /* 0x08 */ f32 offset_x;
    /* 0x0C */ f32 offset_y;
    /* 0x10 */ f32 offset_z;
    /* 0x14 */ u16 texture_s;
    /* 0x16 */ u16 texture_t;
    /* 0x18 */ u16 width;
    /* 0x1A */ u16 height;
} HudPopup; /* 0x1C bytes */

typedef struct HudTextureDesc {
    /* 0x00 */ void *img;
    /* 0x04 */ u16 is4b;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ u32 width;
} HudTextureDesc; /* 0xC bytes */

extern u16 hud_npc_marker_phase;
extern u16 hud_element_allocation_flags;
extern s32 hud_clip_left;
extern s32 hud_clip_top;
extern s32 hud_clip_right;
extern u16 hud_spirit_marker_phase;
extern s32 hud_clip_bottom;
extern HudPopup hud_popup_slots[8];
extern u32 hud_element_gain_flash_timer;
extern u32 hud_selected_element_index;
extern Vec3f hud_temp_vec;
extern u16 hud_chest_text_marker_phases[2];
extern u16 hud_melee_marker_phase;
extern u16 hud_panel_transition_frame;
extern u16 hud_panel_transition_state;
extern u16 hud_hp_meter_width;
extern u16 hud_mp_meter_width;
extern u16 hud_spell_input_anim_timer;
extern u16 hud_spell_input_anim_flags;
extern u16 hud_spell_name_timer;
extern u16 hud_element_input_timer;
extern u16 hud_enemy_info_timer;
extern s32 D_8008C164;
extern s32 D_8008C168;
extern s32 D_8008C16C;
extern s32 audio_pending_seq_id;
extern s32 hud_draw_origin_x;
extern s32 hud_draw_origin_y;
extern s32 hud_npc_marker_screen_y;
extern u16 hud_element_pulse_phase;
extern s32 D_8004F2C0;
extern u8 hud_spell_locked_label[8];
extern u8 hud_element_colors[4][4];
extern u16 hud_actor_status_masks[8];
extern u16 hud_actor_status_effect_masks[4];
extern s32 hud_element_max_level_masks[4];
extern Vec2f hud_spell_input_icon_positions[4];
extern Vec2f hud_element_icon_positions[4];
extern s32 hud_element_max_level_set_masks[4];
extern s32 D_8004F354[77];
extern u8 D_8004F488[0x10];
extern u8 hud_spell_label_palettes[8];

void Hud_ResetState(void);
void Hud_Draw(struct GfxFrameData* buf);
void Hud_DrawPlayerMeters(Actor* arg0);
void Hud_DrawElementLevels(struct GfxFrameData* buf, s32 arg1);
void Hud_DrawCompass(struct GfxFrameData* buf);
void Hud_DrawSpellInput(struct GfxFrameData* buf, Player* arg1);
void Hud_DrawSpellName(void* arg0);
void Hud_UpdateElementAllocation(struct GfxFrameData* buf, Player* pl);
void Hud_DrawNpcTalkMarker(void);
void Hud_DrawSpiritMarker(void);
void Hud_DrawChestMarker(void);
void Hud_DrawTextSpotMarker(void);
void Hud_DrawMeleeTargetMarker(u16 arg0);
void Hud_DrawOutOfRangeIcon(void);
void Hud_StartActorStatusIndicator(Actor* arg0, u16 mask, u16 idx, s16 val);
void Hud_UpdateAndDrawActorStatusIndicators(Actor* arg0);
void Hud_ClearActorStatusIndicators(Actor* arg0);
void func_80023DEC(void);
void func_80023DF4(void);
void func_80023DFC(void);
void func_80023E04(void);
void func_80023E0C(void);
void Hud_DrawEnemyInfoPanel(void);
void Hud_ResetPopups(void);
void Hud_ShowActorPopup(Actor* arg0);
void Hud_DrawPopups(void);
void Hud_DrawSpellLabel(s32 arg0, s32 arg1, u8* arg2, s32 arg3, u16 arg4);
void Hud_DrawGlyphString(s32 x, s32 y, s32 pal, u8* str);
s32 Hud_MeasureGlyphString(u8* str);
void Hud_DrawNumber(u16 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80024A4C(void);
void Hud_LoadTextureTile(HudTextureDesc* tex, s32 x, s32 y, s32 w, s32 h);
void Hud_DrawClippedTextureRect(s32 x, s32 y, s32 x2, s32 y2, s32 s, s32 t, s32 dsdx, s32 dtdy);
void Hud_DrawTextureTile(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

#endif
