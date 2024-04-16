#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"
#include "LCD_2_4_240320.h"

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

void LCD_2_4_240320_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	u8 buf[] = {0xfe, 0x12, 0x34, 0x56, 0x70, 0x9a, 0xbc, 0xd0};
	OLED12864_Init();
	LCD_2_4_240320_GPIO_Config();
	
	OLED_ShowBootIMG();
	LCD_Init();

	//循环进行各项测试	
	while(1) {
		LCD_Clear(RED);delay_ms(1000);	delay_ms(1000);	
		LCD_Clear(GREEN);delay_ms(1000);	delay_ms(1000);	
		LCD_Clear(BLUE);delay_ms(1000);	delay_ms(1000);	
	}
}