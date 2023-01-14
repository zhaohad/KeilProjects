#include <reg51.h>

sbit P00 = P0 ^ 0;
sbit P01 = P0 ^ 1;

void reset_timer() {
	TL0 = 0;
	TH0 = 0;
}

void init_timer() {
	reset_timer();
	TMOD = 0x01;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void timer0_interruption() interrupt 1 {
	int s = 100000000;
	P00 = !P00;
	P01 = TF0;
	while (s--);
	reset_timer();
}

void main() {
	P00 = 0;
	P01 = 0;
	init_timer();
	while(1) {
		// P01 = TF0;
	}
}