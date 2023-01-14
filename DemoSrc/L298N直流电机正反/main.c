#include <reg51.h>

sbit Ven = P2 ^ 0;
sbit C = P2 ^ 1;
sbit D = P2 ^ 2;

void main() {
	Ven = 1;
	C = 0;
	D = 1;
	P1 = P2;
	while(1);
}