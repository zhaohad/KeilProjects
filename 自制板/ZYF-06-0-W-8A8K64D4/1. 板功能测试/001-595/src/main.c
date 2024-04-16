#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"
#include "74HC595.h"

#define BUF_LEN_595 2
u8 g_buf_595[BUF_LEN_595];

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED_12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void LED_GPIO_Init() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P0, &conf);
}

void C595_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P3, &conf);
	
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
	
	
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);
}

void C165_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);
	
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void main() {
	LED_GPIO_Init();
	C595_GPIO_Config();
	C165_GPIO_Config();
	
	
	g_buf_595[0] = 0xff - 0x04 - 0x02;
	g_buf_595[1] = 0xff;

	stop_595();
	// clear_595();
	// keep_595();
	
	write_byte_595(g_buf_595[0]);
	write_byte_595(g_buf_595[1]);
	flush_595();
	

	while(1) {
	}
}