#include "uart.h"
#include <reg51.h>
#include "delay.h"

sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;

void main() {
	P10 = 0;
	UART_Init(0);
	while (1) {
		delay_ms(1000);
		UART_sendByte(0x12);
		P10 = ~P10;
	}
}