#include "typedef.h"
#include "dtos.h"
#include "STC8xxxx.h"
#include "GPIO.h"

void RZ7899_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P1, &conf);
}

void main() {
	RZ7899_GPIO_Config();
	
	P_VM1_RZ7899_I1 = 1;
	P_VM1_RZ7899_I2 = 0;

	while(1) {
	}
}