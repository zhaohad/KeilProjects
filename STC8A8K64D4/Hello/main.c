#include "stc/stc8a8k64d4.H"
#include "stc/stc8a_gpio.H"

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	GPIO_Config();
	P00 = 0;
	while(1) {
	}
}