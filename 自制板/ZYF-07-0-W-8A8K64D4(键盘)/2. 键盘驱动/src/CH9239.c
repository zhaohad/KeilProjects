#include "CH9239.h"
#include "STC8A_UART.h"

xdata u8 g_ready;
xdata u8 g_9329_cmd_len = 0;
xdata u8 g_state_9329_rec = 0;
xdata u8 g_9329_rec_len = 0;
xdata u8 g_9329_rec[MAX_REC_LEN];
xdata KeyBoardStatus g_KeyBoardStatus;

void ch9239_resolve(u8 * buf, u8 buf_l) {
	switch (buf[D_9329_CMD_CODE]) {
		case CH9239_CMD_SYS_INFO: {
			g_KeyBoardStatus.version = buf[5];
			g_KeyBoardStatus.isConnected = buf[6];
			g_KeyBoardStatus.isNumLockOn = buf[7] & 0x01;
			g_KeyBoardStatus.isCapsLockOn = buf[7] & 0x02;
			g_KeyBoardStatus.isScrollLockOn = buf[7] & 0x04;
			break;
		}
	}
}

bit ch9239_uart_stream(u8 d) {
	bit err = 0;
	bit finish = 0;

	g_ready = 0;
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
		g_ready = 1;
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
			ch9239_resolve(g_9329_rec, g_9329_rec_len);
			g_ready = 1;
		}
	}
	return finish;
}

bit ch9239_ready() {
	return g_ready;
}

u8 ch9239_sum(u8 * buf, u8 l) {
	u8 sum = 0;
	u8 i;
	for (i = 0; i < l; i++) {
		sum = sum + buf[i];
	}
	return sum;
}

void ch9239_get_sys_info() {
	TX2_write2buff(0x57);
	TX2_write2buff(0xAB);
	TX2_write2buff(0x0);
	TX2_write2buff(0x01);
	TX2_write2buff(0x00);
	TX2_write2buff(0x03);
	g_ready = 0;
}

void ch9239_key_down(u8 fun_keys, u8 norm_key[MAX_NORM_KEY], u8 norm_key_len) {
	xdata u8 i;
	xdata u8 cmd_key_general_data[14];
	cmd_key_general_data[0] = 0x57;
	cmd_key_general_data[1] = 0xAB;
	cmd_key_general_data[2] = 0;
	cmd_key_general_data[3] = 0x02;
	cmd_key_general_data[4] = 8;
	cmd_key_general_data[5] = fun_keys;
	cmd_key_general_data[6] = 0;
	cmd_key_general_data[7] = 0;
	cmd_key_general_data[8] = 0;
	cmd_key_general_data[9] = 0;
	cmd_key_general_data[10] = 0;
	cmd_key_general_data[11] = 0;
	cmd_key_general_data[12] = 0;
	for (i = 0; i < norm_key_len && i < MAX_NORM_KEY; ++i) {
 		cmd_key_general_data[7 + i] = norm_key[i];
	}
	cmd_key_general_data[13] = ch9239_sum(cmd_key_general_data, 13);
	TX2_write2buffs(cmd_key_general_data, 14);
	g_ready = 0;
}

void ch9239_one_key_down(u8 norm_key) {
	xdata u8 keys[1];
	keys[0] = norm_key;
	ch9239_key_down(0, keys, 1);
}

void ch9239_all_key_up() {
	TX2_write2buff(0x57);
	TX2_write2buff(0xAB);
	TX2_write2buff(0x0);
	TX2_write2buff(0x02);
	TX2_write2buff(0x08);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0);
	TX2_write2buff(0x0C);
	g_ready = 0;
}