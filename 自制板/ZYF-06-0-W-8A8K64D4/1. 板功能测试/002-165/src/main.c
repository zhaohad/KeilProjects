#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"
#include "74HC595.h"
#include "74HC165.h"

#define BUF_LEN_595 2
u8 g_buf_595[BUF_LEN_595];

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P0, &conf);
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
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P1, &conf);
	
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void main() {
	u8 buf[] = {0xfe, 0x12};

	LED_GPIO_Init();
	C595_GPIO_Config();
	C165_GPIO_Config();	
	
	OLED_12864_Init();

	g_buf_595[0] = 0xff;
	g_buf_595[1] = 0xff;
	
	write_byte_595(g_buf_595[0]);
	write_byte_595(g_buf_595[1]);
	flush_595();
	

	while(1) {
		load_data_165();
		buf[0] = read_byte_165();
		buf[1] = read_byte_165();
		OLED_ShowHexBuf8(0, 0, buf, 2);
	}
}