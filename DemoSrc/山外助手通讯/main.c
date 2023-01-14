#include <reg51.h>
#include "src/uart.h"
#include "src/shanwai.h"
#include "src/delay.h"

bit hasR = 0;

void UART_onReceived(u8 c);

void main() {
	int d1 = 0;
	int d2 = 0;
	UART_Init_110592MHz_9600bps(UART_onReceived);

	while(1) {
		float sends[2];
		sends[0] = d1;
		sends[1] = d2;
		SHANWAI_sendWaveValue(&sends, sizeof(sends[0]), 2);
		if (d1++ > 100) {
			d1 = 0;
		}
		if (d2-- < -100) {
			d2 = 0;
		}
	}
}

void UART_onReceived(u8 c) {
	hasR = 1;
}