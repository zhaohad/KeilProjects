#include <reg51.h>

sbit P32 = P3 ^ 2;
sbit P33 = P3 ^ 3;

void main() {
	while (1) {
		P32 = 0;
		P33 = 0;
	}
}