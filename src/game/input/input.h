#ifndef GAME_INPUT_INPUT_H
#define GAME_INPUT_INPUT_H

#include "common.h"

/* One port's Controller Pak scan (Pak_ScanGameFiles): unk0 flags (low nibble = this game's
 * note count, 0x2000 full, 0x4000 has a game note, 0x8000 pak present), unk2 each note's
 * ext_name[0] (0x7F other game, -1 empty), unk12 port state, unk13 free pages. */
typedef struct PakFileScan {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2[16];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 unk13;
} PakFileScan; /* 0x14 bytes */

/* A note's ext_name (osPfsAllocateFile/osPfsDeleteFile). */
typedef struct PakExtName {
    /* 0x00 */ u8 b[4];
} PakExtName; /* 0x4 bytes */

/* .bss 80092C80..80092ED0, in address order (the order of these declarations fixes it). */
extern s8 input_primary_port;
extern s8 input_stick_x;
extern s8 input_stick_y;
extern u16 input_held_buttons;
extern u16 input_pressed_buttons;
extern u16 input_previous_button_inverse;
extern OSMesgQueue input_si_queue;
extern OSPfs pak_port_states[4];
extern PakFileScan pak_game_file_scans[4];
extern u8 input_connected_port_bits;
extern OSContStatus input_controller_statuses[4];
extern OSMesg input_si_mesg;
extern OSContPad input_pad_states[4];

/* .data */
extern u8 pak_game_name[16];
extern char D_80061820[];
extern PakExtName pak_allocate_extension_template;
extern PakExtName pak_delete_extension_template;

s32 Input_InitControllers(void);
void Input_ReadController(s32 cont);
s32 Pak_ScanGameFiles(s32 cont);
u8 func_80035CC8(s32 arg0);
u8 Pak_AllocateGameFile(s32 arg0, u8 arg1);
u8 Pak_DeleteGameFile(s32 arg0, u8 arg1);
s32 Pak_ReadFile(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf);
s32 Pak_WriteFile(s32 arg0, s32 file_no, s32 offset, s32 nbytes, u8 *buf);
s32 Pak_TryRepair(s32 arg0, s32 arg1);
s32 Pak_ClassifyError(s32 arg0);
s32 Pak_CompareNameBytes(u8 *a, u8 *b, s32 n);
void func_80036124(void);
void Input_StartControllerQuery(OSMesgQueue *mq);
void Input_GetControllerQuery(OSContStatus *status);
void func_80036184(void);

#endif
