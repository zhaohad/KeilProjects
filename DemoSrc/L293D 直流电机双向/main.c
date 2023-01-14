#include <reg51.h>

sbit EN = P0 ^ 0;
sbit INPUT1 = P0 ^ 1;
sbit INPUT2 = P0 ^ 2;

void main() {
	EN = 1;
	INPUT1 = 0;
	INPUT2 = 1;
	P2 = 0xff;
	// P0 = 0xff;
	while(1);
}