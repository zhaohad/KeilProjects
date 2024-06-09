#ifndef __CH9239_H__
#define __CH9239_H__
#include "typedef.h"

#define D_9239_HEAD_57 0
#define D_9239_HEAD_AB 1
#define D_9239_ADDR_CODE 2
#define D_9329_CMD_CODE 3
#define D_9329_LEN 4
#define D_9329_DATA 5
#define D_9329_SUM 6

#define CH9239_CMD_SYS_INFO 0x81

#define MAX_REC_LEN 100
#define MAX_NORM_KEY 6

typedef struct {
	u8 version;
	u8 isConnected;
	u8 isNumLockOn;
	u8 isCapsLockOn;
	u8 isScrollLockOn;
} KeyBoardStatus;

extern xdata KeyBoardStatus g_KeyBoardStatus;

extern xdata u8 g_9329_cmd_len;
extern xdata u8 g_state_9329_rec;
extern xdata u8 g_9329_rec_len;
extern xdata u8 g_9329_rec[MAX_REC_LEN];

bit ch9239_uart_stream(u8 d);
u8 ch9239_sum(u8 * buf, u8 l);
bit ch9239_ready();

void ch9239_resolve(u8 * buf, u8 buf_l);
void ch9239_get_sys_info();
void ch9239_key_down(u8 fun_keys, u8 norm_key[MAX_NORM_KEY], u8 norm_key_len);
void ch9239_one_key_down(u8 norm_key);
void ch9239_all_key_up();

#endif