#include "stc8a8k64d4.h"
#include "typedef.h"
#include "uart.h"
#include "shanwai.h"

void main() {
	int d1 = 0;
	int d2 = 0;
	
	UART_config();
	EA = 1;
	
	/*while(1) {
		// UART_writeByte(0xab);
		UART_writeStr("123kjl\n");
	}*/

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