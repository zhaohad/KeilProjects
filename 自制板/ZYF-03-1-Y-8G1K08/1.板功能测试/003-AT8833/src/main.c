#include "typedef.h"
#include "dtos.h"
#include "STC8xxxx.h"
#include "GPIO.h"
#include "UART.h"

void RZ7899_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P1, &conf);
}

void DRV8833_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P1, &conf);
}

void main() {
	RZ7899_GPIO_Config();
	DRV8833_GPIO_Config();
	EA = 1;
	
	P_VM1_RZ7899_I1 = 0;
	P_VM1_RZ7899_I2 = 1;

	P_VM1_DRV8833_I1 = 0;
	P_VM1_DRV8833_I2 = 1;
	P_VM1_DRV8833_I3 = 0;
	P_VM1_DRV8833_I4 = 1;
	while(1) {
	}
}