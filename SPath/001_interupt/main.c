#include <reg51.h>

sbit P10 = P1 ^ 0;

int led = 1;

void setLed();

int main() {
	setLed();
	
	EA = 1;
	IT0 = 1;
	EX0 = 1;
	
	while(1);
	return 0;
}

void setLed() {
	P10 = led;
}

void int0() interrupt 0 {
	led = !led;
	setLed();
}