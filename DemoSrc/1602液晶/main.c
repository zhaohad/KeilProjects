#include <reg52.h>
#include <stdio.h>
#include <math.h>
#include "1602.h"
#include "delay.h"

#define MAX_S 10

void main() {
	int s = MAX_S;
	LCD_Init();
	LCD_Write_String(0,1,"zhaohad");
	while(1) {
		int i = 2;
		unsigned char DisTempData[16];

		sprintf(DisTempData,"s = %d", s);
		// LCD_Write_String(0, 0, DisTempData);
		LCD_Write_String_And_Clear_Line(0, 0, DisTempData);
		while (i--) {
			DelayMs(250);
		}
		if (s-- < -MAX_S) {
			s = MAX_S;
		}
	}
}
