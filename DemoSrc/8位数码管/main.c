#include <reg51.h>
#include "DigitalDisplay_8.h"

void main() {
	unsigned char n[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	unsigned char m[8] = {4, 5, 6, 7, 8, 9, 10, 11};
	DigitalDisplay_8_Set(n, 8);
	while (1) {
		// DigitalDisplay_8_Loop();
		DigitalDisplay_8_Display(m, 8);
	}
}