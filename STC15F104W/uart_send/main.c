#include "uart.h"
#include <reg51.h>
#include "delay.h"

sbit P32 = P3 ^ 2;
sbit P33 = P3 ^ 3;

void main() {
	P32 = 0;
	while (1) {
		delay_ms(1000);
		UART_sendByte(0x12);
		P32 = ~P32;
	}
}