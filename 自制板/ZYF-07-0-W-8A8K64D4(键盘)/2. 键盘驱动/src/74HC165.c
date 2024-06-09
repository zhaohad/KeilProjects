#include "74hc165.h"
#include "code_lib.h"
#include "STC8A_UART.h"

u8 read_keys(u8 keys[CNT_MAX_READ_NORM_KEY]) {
	xdata u8 dat_165[CNT_MAX_165], keys_l;
	xdata u8 i;
	load_data_165();
	for (i = 0; i < CNT_165; ++i) {
		dat_165[i] = read_byte_165();
	}
	
	keys_l = 0;
	for (i = 0; i < CNT_165; ++i) {
		if (dat_165[i] != 0xff) {
			xdata u8 f = 0x01;
			while (f) {
				if ((dat_165[i] & f) == 0) {
					keys[keys_l++] = code_165_to_9239(i, f);
					if (keys_l >= CNT_MAX_READ_NORM_KEY) {
						return keys_l;
					}
				}
				f = f << 1;
			}
		}
	}
	return keys_l;
}

void load_data_165() {
	P_165_PL = 0;
}

u8 read_byte_165() {
	u8 d = 0;
	P_165_PL = 1;
	P_165_CE = 0;
	
	
	
	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	_nop_();
	P_165_CP = 1;
	
	P_165_CE = 1;
	return d;
}
