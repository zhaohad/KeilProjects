#include "stc8a8k64d4.H"
#include "stc8a_gpio.h"
#include "STC8A_UART.h"
#include "STC8A_Switch.h"
#include "STC8A_NVIC.h"
#include "delay.h"

#include "typedef.h"
#include "74HC595.h"
#include "74HC165.h"

void UART_Debuging_Config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	UART1_SW(UART1_SW_P30_P31);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void C595_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P3, &conf);
	
	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);
}

void C165_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;

	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P4, &conf);	
	
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P2, &conf);
	
	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	u8 led, ledg, ledb, ledr;
	u8 keys;
	UART_Debuging_Config();

	C595_GPIO_Config();
	C165_GPIO_Config();
	
	ledg = 0x7f;
	ledr = 0xbf;
	ledb = 0xdf;
	led = ledr & ledb & ledg;

	stop_595();
	clear_595();
	keep_595();
	
	write_byte_595(led);
	flush_595();

	while(1) {
		load_data_165();
		keys = read_byte_165();
		TX1_write2buff(keys);
	}
}