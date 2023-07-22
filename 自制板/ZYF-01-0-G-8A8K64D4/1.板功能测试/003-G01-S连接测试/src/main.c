#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "G01_S.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void MOTOR_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2, &conf);
}

void main() {
	bit exist;
	
	OLED12864_Init();

	NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();

	OLED_ShowString(0, 0, "CHECK MODULE...");
	exist = NRF24L01_check();
	
	if (exist) {
		OLED_ShowString(0, 2, "DONE");
	} else {
		OLED_ShowString(0, 2, "NOT EXIST");
	}

	while(1) {
	}
}