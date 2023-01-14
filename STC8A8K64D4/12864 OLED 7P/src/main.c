#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void main() {
	u8 buf[] = {0xfe, 0x12, 0x34, 0x56, 0x70, 0x9a, 0xbc, 0xd0};
	OLED12864_Init();
	OLED_ShowString(0, 0, "121212121212");
	OLED_ShowString8(0, 2, "123ABC.,m<>?abcdefghijkl");
	OLED_ShowHexBuf8(0, 4, buf, 8);
	while(1) {
	}
}