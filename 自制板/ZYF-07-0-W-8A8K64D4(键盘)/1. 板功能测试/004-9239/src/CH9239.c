#include "CH9239.h"

xdata u8 g_9329_cmd_len = 0;
xdata u8 g_state_9329_rec = 0;
xdata u8 g_9329_rec_len = 0;
xdata u8 g_9329_rec[MAX_REC_LEN];

bit ch9239_uart_stream(u8 d) {
	bit err = 0;
	bit finish = 0;
	switch (g_state_9329_rec) {
		case D_9239_HEAD_57: // HEAD 0x57
			err = (d != 0x57);
			g_state_9329_rec = D_9239_HEAD_AB;
			g_9329_rec_len = 0;
			break;
		case D_9239_HEAD_AB: // HEAD 0xAB
			err = (d != 0xAB);
			g_state_9329_rec = D_9239_ADDR_CODE;
			break;
		case D_9239_ADDR_CODE: // ADDR CODE
			g_state_9329_rec = D_9329_CMD_CODE;
			err = 0;
			break;
		case D_9329_CMD_CODE: // CMD CODE
			g_state_9329_rec = D_9329_LEN;
			err = 0;
			break;
		case D_9329_LEN: // DATA LEN
			g_state_9329_rec = D_9329_DATA;
			g_9329_cmd_len = d;
			err = 0;
			break;
		case D_9329_DATA:
			err = 0;
			--g_9329_cmd_len;
			if (g_9329_cmd_len == 0) {
				g_state_9329_rec = D_9329_SUM;
			}
			break;
		case D_9329_SUM:
			g_state_9329_rec = D_9239_HEAD_57;
			finish = 1;
			err = 0;
			break;
		default:
			err = 1;
			break;
	}

	if (err) {
		g_state_9329_rec = 0;
		g_9329_cmd_len = 0;
		g_9329_rec_len = 0;
	} else {
		g_9329_rec[g_9329_rec_len++] = d;
		if (finish) {
			u8 sum = ch9239_sum(g_9329_rec, g_9329_rec_len - 1);
			if (d != sum) {
				g_state_9329_rec = 0;
				g_9329_cmd_len = 0;
				g_9329_rec_len = 0;
				finish = 0;
			}
		}
	}
	return finish;
}

u8 ch9239_sum(u8 * buf, u8 l) {
	u8 sum = 0;
	u8 i;
	for (i = 0; i < l; i++) {
		sum = sum + buf[i];
	}
	return sum;
}