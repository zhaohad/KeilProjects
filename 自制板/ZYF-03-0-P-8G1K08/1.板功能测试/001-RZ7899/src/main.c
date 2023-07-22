#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "STC8A_UART.h"


xdata u8 g_received_buf[MAX_CHAR8_COL];

void OLED_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
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

void UART_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);
}

void UART_config() {
	xdata COMx_InitDefine COMx_InitStructure; //结构定义
	UART1_SW(P_UART);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE

	UART_Configuration(UART1, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE, Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

void on_UART_Rec_1Byte(u8 d) {
	COM1.B_RX_OK = 0;
	COM1.RX_TimeOut = TimeOutSet1;
	RX1_Buffer[COM1.RX_Cnt++] = d;
	if(COM1.RX_Cnt >= COM_RX1_Lenth) {
		COM1.RX_Cnt = 0;
	}
	COM1.B_RX_OK = 1;
}

void UART_Init() {
	COM1.TX_read = 0;
	COM1.RX_Cnt = 0;
	COM1.B_RX_OK = 0;
	COM1.RX_TimeOut = TimeOutSet1;
	
	UART_GPIO_Config();
	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	UART_config();
}

void boot_delay() {
	xdata u8 t;
	for (t = 0; t < 20; ++t) {
		delay_ms(100);
	}
}

void copy_buf(u8 * dst, u8 l) {
	xdata u8 i;
	--l;
	for (i = 0; i < l; ++i) {
		if (i < COM1.RX_Cnt) {
			dst[i] = RX1_Buffer[i];
		} else {
			dst[i] = ' ';
		}
	}
	dst[l] = 0;
	COM1.RX_Cnt = 0;
	COM1.B_RX_OK = 0;
}

void main() {	
	OLED12864_Init();
	OLED_ShowString(0, 0, "Init...");
	
	UART_Init();
	EA = 1;
	
	boot_delay();
	OLED_ShowString(0, 0, "Init Done");
	PrintString1("AT\r\n");

	while(1) {
		delay_ms(1);
		if (COM1.B_RX_OK && COM1.RX_TimeOut-- <= 0) {
			copy_buf(g_received_buf, MAX_CHAR8_COL);
			OLED_ShowString(0, 2, g_received_buf);
			PrintString1(g_received_buf);
		}
	}
}