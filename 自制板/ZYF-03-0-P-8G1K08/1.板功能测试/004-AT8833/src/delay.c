#include "delay.h"

void Delay1ms() {
	xdata unsigned char i, j;
	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do {
		while (--j);
	} while (--i);
}

void delay_ms(unsigned char ms) {
	while (ms--) {
		Delay1ms();
	}
}