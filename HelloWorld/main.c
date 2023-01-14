#include <reg51.h>

sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;
sbit P12 = P1 ^ 2;
sbit P13 = P1 ^ 3;
sbit P14 = P1 ^ 4;
sbit P15 = P1 ^ 5;
sbit P16 = P1 ^ 6;
sbit P17 = P1 ^ 7;

sbit P00 = P0 ^ 0;
sbit P01 = P0 ^ 1;
sbit P02 = P0 ^ 2;
sbit P03 = P0 ^ 3;
sbit P04 = P0 ^ 4;
sbit P05 = P0 ^ 5;
sbit P06 = P0 ^ 6;
sbit P07 = P0 ^ 7;

sbit P20 = P2 ^ 0;
sbit P21 = P2 ^ 1;
sbit P22 = P2 ^ 2;
sbit P23 = P2 ^ 3;
sbit P24 = P2 ^ 4;
sbit P25 = P2 ^ 5;
sbit P26 = P2 ^ 6;
sbit P27 = P2 ^ 7;

void main() {
	while (1) {
		/*P10 = 0;
		P11 = 1;
		P12 = 0;
		P13 = 1;
		P14 = 0;
		P15 = 1;
		P16 = 0;
		P17 = 1;*/
		
		/*P20 = 0;
		P21 = 1;
		P22 = 0;
		P10 = P20;
		P11 = P21;
		P1 = P2;*/
		P1 = 0x55;
		P0 = 0xff;
	}
}