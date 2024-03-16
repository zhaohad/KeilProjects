#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P0, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P2, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void LED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
}

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void main() {
	u8 buf[] = {0xfe, 0x12, 0x34, 0x56, 0x70, 0x9a, 0xbc, 0xd0};
	OLED12864_Init();
	OLED_ShowString(0, 0, "121212121212");
	OLED_ShowString8(0, 2, "123ABC.,m<>?abcdefghijkl");
	OLED_ShowHexBuf8(0, 4, buf, 8);
	
	LED_GPIO_Config();
	
	P_LED_1 = 0;
	P_LED_2 = 0;
	P_LED_3 = 0;

	while(1) {
	}
}