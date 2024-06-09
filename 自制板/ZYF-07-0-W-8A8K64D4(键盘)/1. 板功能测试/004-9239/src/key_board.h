#ifndef __KEY_BOARD_H__
#define __KEY_BOARD_H__
#include "typedef.h"

#define CH9239_INDEX_CMD 3
#define CH9239_CMD_SYS_INFO 0x81

#define MAX_NORM_KEY 6

typedef struct {
	u8 version;
	u8 isConnected;
	u8 isNumLockOn;
	u8 isCapsLockOn;
	u8 isScrollLockOn;
} KeyBoardStatus;

extern xdata KeyBoardStatus g_KeyBoardStatus;

void key_board_resolve_ch9239(u8 * buf, u8 buf_l);
void key_board_led_off();
void key_board_refresh_led();
void key_board_get_sys_info();
void key_board_key_down(u8 fun_keys, u8 norm_key[MAX_NORM_KEY], u8 norm_key_len);
void key_board_all_key_up();

#endif

