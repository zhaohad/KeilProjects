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
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void MOTOR_GPIO_Config() {
	GPIO_InitTypeDef conf;
	// conf.Mode = GPIO_OUT_PP;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P6, &conf);
	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P7, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
}

void KEY_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P7, &conf);
}

void main() {
	OLED12864_Init();
	KEY_GPIO_Config();
	OLED_ShowString8(0, 0, "KEYS TEST");

	while(1) {		
		if (!P_KEY1) {
			OLED_ShowString8(0, 1, "KEY1 DOWN");
		} else {
			OLED_ShowString8(0, 1, "         ");
		}
		if (!P_KEY2) {
			OLED_ShowString8(0, 2, "KEY2 DOWN");
		} else {
			OLED_ShowString8(0, 2, "         ");
		}
		if (!P_KEY3) {
			OLED_ShowString8(0, 3, "KEY3 DOWN");
		} else {
			OLED_ShowString8(0, 3, "         ");
		}
		if (!P_KEY4) {
			OLED_ShowString8(0, 4, "KEY4 DOWN");
		} else {
			OLED_ShowString8(0, 4, "         ");
		}
		if (!P_KEY5) {
			OLED_ShowString8(0, 5, "KEY5 DOWN");
		} else {
			OLED_ShowString8(0, 5, "         ");
		}
	}
}