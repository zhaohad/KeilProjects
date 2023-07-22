#include "STC8A8K64D4.H"
#include "STC8A_GPIO.H"
#include "typedef.h"
#include "G01_S.h"

void GPIO_LED() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	bit exist;
	GPIO_LED();
	NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();
	
	exist = NRF24L01_check();
	
	P_LED1 = 1;
	P_LED2 = 1;
	if (exist) {
		P_LED2 = 0;
	}
	
	P_LED1 = 0;
	while(1) {
	}
}