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
	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P2, &conf);
}

void G01_S_GPIO_config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P0, &conf);
	
	conf.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P4, &conf);
	
	NRF24L01_Gpio_Init();
}

void GOPI_Config() {
	OLED_GPIO_Config();

	G01_S_GPIO_config();
}

void main() {
	bit exist;
	GOPI_Config();

	OLED_Init();

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