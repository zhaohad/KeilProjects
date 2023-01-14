#include <reg51.h>
#include "src/delay.h"
#include "src/oled12864.h"
#include "src/typedef.h"
#include "src/uart.h"

u8 buf[] = {0xfe, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xd0};

void main() {
	OLED_Init();
	OLED_ShowString(0, 0, "123ABC.,m<>?");
	OLED_ShowString8(0, 2, "123ABC.,m<>?abcdefghijkl");
	OLED_ShowHexBuf8(0, 4, buf, 8);
	while (1) {
	}
}