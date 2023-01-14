#include <reg51.h>
#include "src/uart.h"

bit hasR = 0;

void UART_onReceived(u8 c);

void send0f() {
	UART_sendByte(0x0f);
}

void main() {
	UART_Init_110592MHz_9600bps(UART_onReceived);
	send0f();
	while(1) {
		while(!hasR);
		hasR = 0;
		UART_sendStr("Some thing\r\n");
	}
}

void UART_onReceived(u8 c) {
	hasR = 1;
}