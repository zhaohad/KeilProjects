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

#define MAX_REC_LEN 100

extern xdata u8 g_9329_cmd_len;
extern xdata u8 g_state_9329_rec;
extern xdata u8 g_9329_rec_len;
extern xdata u8 g_9329_rec[MAX_REC_LEN];

bit ch9239_uart_stream(u8 d);
u8 ch9239_sum(u8 * buf, u8 l);

#endif