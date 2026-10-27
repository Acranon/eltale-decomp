#ifndef GAME_SAVE_SAVE_MENU_H
#define GAME_SAVE_SAVE_MENU_H

#include "common.h"
#include "game/actor/actor.h"

typedef struct SaveBytes20 { /* 0x00 */ u8 b[0x20]; } SaveBytes20; /* 0x20 bytes */
typedef struct SaveBytes10 { /* 0x00 */ u8 b[0x10]; } SaveBytes10; /* 0x10 bytes */
typedef struct SaveBytes97 { /* 0x00 */ u8 b[0x97]; } SaveBytes97; /* 0x97 bytes */
typedef struct SaveBytes1 { /* 0x00 */ u8 b[1]; } SaveBytes1; /* 0x1 byte */
#ifdef NON_MATCHING
typedef struct SaveBytes14 { /* 0x00 */ u8 b[14]; } SaveBytes14; /* 0xE bytes */
#endif

typedef struct SaveGameStateBlock {
    /* 0x00 */ SaveBytes20 unk0;
    /* 0x20 */ SaveBytes10 unk20;
    /* 0x30 */ SaveBytes97 unk30;
    /* 0xC7 */ SaveBytes1 unkC7;
} SaveGameStateBlock; /* 0xC8 bytes */

typedef struct SaveHeader {
    /* 0x00 */ ActorStats unk0;
    /* 0x38 */ u16 unk38;
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ u16 unk60;
    /* 0x62 */ s8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ u16 unk64;
} SaveHeader; /* 0x68 bytes */

typedef struct SaveFileEntry {
    /* 0x00 */ s8 unk0;
    /* 0x01 */ s8 unk1;
} SaveFileEntry; /* 0x2 bytes */

extern u16 save_menu_flags;
extern u8 save_menu_dialog_index;
extern u8 save_menu_operation_panel_index;
extern s32 save_menu_pak_error;
extern u8 save_menu_choice_cursor;
extern s8 save_menu_delay_frames;
extern s8 save_menu_selected_slot;
#ifdef NON_MATCHING
extern u8 save_menu_stick_repeat_counter;
#else
extern s8 save_menu_stick_repeat_counter;
#endif
extern u8 save_menu_repair_count;
extern SaveFileEntry save_menu_file_entries[17];
extern SaveHeader save_menu_save_headers[16];
extern SaveGameStateBlock save_menu_game_state_block;
extern SaveHeader save_menu_header_read_scratch;
extern u8 D_80090358[0x18];
extern u8 save_menu_state_read_scratch[0xE0];

#ifdef NON_MATCHING
extern SaveBytes14 D_80061650;
#else
extern u8 D_80061650[0xE];
#endif

void SaveMenu_Init(s32 arg0);
void SaveMenu_Update(void);
void SaveMenu_DrawOperationPanel(void);
void SaveMenu_CheckControllerPak(void);
void SaveMenu_UpdateDialog(void);
void SaveMenu_UpdateSlotList(s32 arg0);
void SaveMenu_UpdateDelay(void);
void SaveMenu_DeleteSelectedFile(void);
void SaveMenu_LoadSelectedFile(void);
void SaveMenu_SaveSelectedFile(void);
void SaveMenu_RepairPak(void);
void SaveMenu_RefreshFileList(void);
void SaveMenu_SetTextDrawState(void);
void SaveMenu_DrawBackground(void);
void SaveMenu_CaptureGameState(s32 arg0);
void SaveMenu_RestoreGameState(s32 arg0);

#endif
