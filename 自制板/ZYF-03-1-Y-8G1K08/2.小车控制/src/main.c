#include "typedef.h"
#include "dtos.h"
#include "STC8xxxx.h"
#include "GPIO.h"
#include "UART.h"
#include "CarCtrl.h"

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

void UART_Config() {
	xdata COMx_InitDefine config; //结构定义
	config.UART_Mode = UART_8bit_BRTx; //模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	config.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
  config.UART_BaudRate = 9600ul;	//波特率, 一般 110 ~ 115200
  config.UART_RxEnable = ENABLE; //接收允许, ENABLE或DISABLE
  config.BaudRateDouble = DISABLE; //波特率加倍, ENABLE或DISABLE
  config.UART_Interrupt = ENABLE; //中断允许, ENABLE或DISABLE
  config.UART_Polity = Polity_0; //指定中断优先级(低到高) Polity_0,Polity_1,Polity_2,Polity_3
  // config.UART_P_SW = UART1_SW_P30_P31; //切换端口, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	config.UART_P_SW = UART1_SW_P16_P17; //切换端口, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
  UART_Configuration(UART1, &config); //初始化串口1 UART1,UART2,UART3,UART4
}

void UART_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P3, &conf);
}

void main() {	
	RZ7899_GPIO_Config();

	DRV8833_GPIO_Config();

	UART_Config();
	
	CarControl_Init();

	EA = 1;
	
	TurnBack();

	while(1) {
		if (COM1.RX_TimeOut > 0) {
			if (--COM1.RX_TimeOut == 0) {
				u8 i;
				if (COM1.RX_Cnt > 0) {
					for (i = 0; i < COM1.RX_Cnt; ++i) {
						TX1_write2buff(RX1_Buffer[i]);
						if (RX1_Buffer[i] == '0') {
							TurnBack();
						} else if (RX1_Buffer[i] == '1') {
							TurnLeft();
						} else if (RX1_Buffer[i] == '2') {
							TurnRight();
						} else if (RX1_Buffer[i] == '3') {
							Motor_Go(1);
						} else if (RX1_Buffer[i] == '4') {
							Motor_Go(0);
						} else if (RX1_Buffer[i] == '5') {
							Motor_Stop();
						} else if (RX1_Buffer[i] == 'a') {
							SetSpeed(4);
						} else if (RX1_Buffer[i] == 'b') {
							SetSpeed(5);
						} else if (RX1_Buffer[i] == 'c') {
							SetSpeed(6);
						} else if (RX1_Buffer[i] == 'd') {
							SetSpeed(7);
						} else if (RX1_Buffer[i] == 'e') {
							SetSpeed(8);
						} else if (RX1_Buffer[i] == 'f') {
							SetSpeed(9);
						} else if (RX1_Buffer[i] == 'g') {
							SetSpeed(10);
						}
					}
					COM1.RX_Cnt = 0;
				}
			}
		}
	}
}