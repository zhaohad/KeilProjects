#include <reg51.h>

sbit a = P2 ^ 3;
sbit b = P2 ^ 2;
sbit c = P2 ^ 1;
sbit d = P2 ^ 0;

#define SPEED_VARIATION_RATIO 1.0f / 64.0f
#define STRIDE_ANGLE 5.625f / 64.0f

int cnt = 0;

void delay(int s);
bit OneStep(int step, bit positive);

void main() {
	int j;
	bit fi = 0;
	OneStep(0, 0);
	// for (j = 0; j < 64; ++j) {
	for (j = 0; 1; ++j) {
		int i;
		for (i = 8; !fi && i >= 1; --i) {
			fi = OneStep(i, 0);
			delay(100);
		}
	}
	
	while(1);
	
	/*OneStep(0, 1);
	while (1) {
		int i;
		for (i = 1; !fi && i < 9; ++i) {
			fi = OneStep(i, 1);
			delay(100);
		}
	}*/
	return;
}

void delay(int s) {
	while (s--);
}

bit OneStep(int step, bit positive) {
	switch (step) {
		case 0: // for init
			cnt = 0;
			a = b = c = d = 0;
			if (positive) {
				a = 1;
			} else {
				d = 1;
			}
			return 1;
			break;
		case 1:
			d = ~positive;
			break;
		case 2:
			b = positive;
			break;
		case 3:
			a = ~positive;
			break;
		case 4:
			c = positive;
			break;
		case 5:
			b = ~positive;
			break;
		case 6:
			d = positive;
			break;
		case 7:
			c = ~positive;
			break;
		case 8:
			a = positive;
			break;
		default:
			return 1;
			break;
	}
	cnt++;
	return cnt >= 64 * 64;
}