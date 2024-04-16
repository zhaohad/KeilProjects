#include "key_board.h"
#include "74HC595.h"
#include "STC8A_UART.h"
#include "CH9239.h"

xdata KeyBoardStatus g_KeyBoardStatus;

#define BUF_LEN_595 2
xdata u8 g_buf_595[BUF_LEN_595];

void turn_led_on_off(u8 led, bit on) {
	if (on) {
		g_buf_595[1] = g_buf_595[1] & ~led;
	} else {
		g_buf_595[1] = g_buf_595[1] | led;
	}
}

void sys_info_led() {
	turn_led_on_off(0x01, g_KeyBoardStatus.isNumLockOn);
	turn_led_on_off(0x08, g_KeyBoardStatus.isCapsLockOn);
	key_board_refresh_led();
}

void key_board_resolve_ch9239(u8 * buf, u8 buf_l) {
	switch (buf[CH9239_INDEX_CMD]) {
		case CH9239_CMD_SYS_INFO: {
			g_KeyBoardStatus.version = buf[5];
			g_KeyBoardStatus.isConnected = buf[6];
			g_KeyBoardStatus.isNumLockOn = buf[7] & 0x01;
			g_KeyBoardStatus.isCapsLockOn = buf[7] & 0x02;
			g_KeyBoardStatus.isScrollLockOn = buf[7] & 0x04;
			sys_info_led();
			break;
		}
	}
}

void key_board_led_off() {
	g_buf_595[0] = 0xff;
	g_buf_595[1] = 0xff;
	key_board_refresh_led();
}

void key_board_refresh_led() {
	write_byte_595(g_buf_595[0]);
	write_byte_595(g_buf_595[1]);
	flush_595();
}

void key_board_get_sys_info() {
	xdata u8 cmd_get_info[6] = {0x57, 0xAB, 0x00, 0x01, 0x00, 0x03};
	TX1_write2buffs(cmd_get_info, 6);
}

xdata u8 cmd_key_general_data[14] = {0};

void key_board_key_down(u8 fun_keys, u8 norm_key[MAX_NORM_KEY], u8 norm_key_len) {
	xdata u8 i;
	// xdata u8 cmd_key_general_data[14] = {0x57, 0xAB, 0x00, 0x02, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
	cmd_key_general_data[13] = 0;
	for (i = 0; i < norm_key_len && i < MAX_NORM_KEY; ++i) {
		cmd_key_general_data[7 + i] = norm_key[i];
	}
	cmd_key_general_data[13] = ch9239_sum(cmd_key_general_data, 13);
	TX1_write2buffs(cmd_key_general_data, 14);
}