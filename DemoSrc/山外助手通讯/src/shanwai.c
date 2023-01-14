#include "shanwai.h"

void SHANWAI_sendWaveValue(void * d, u8 sized, u8 len) {
	int i, s;
	u8 * v = (u8 *) d;
	
	UART_sendByte(SHANWAI_CMD_WAVEVALUE);
	UART_sendByte(SHANWAI_CMD_WAVEVALUE_INV);
	for (i = 0; i < len; ++i) {
		for (s = 1; s <= sized; ++s) {
			UART_sendByte(*(v + (i + 1) * sized - s));
		}
	}
	UART_sendByte(SHANWAI_CMD_WAVEVALUE_INV);
	UART_sendByte(SHANWAI_CMD_WAVEVALUE);
}