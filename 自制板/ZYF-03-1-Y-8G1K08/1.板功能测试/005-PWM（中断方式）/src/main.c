#include "dtos.h"
#include "STC8xxxx.h"
#include "GPIO.h"
#include "UART.h"
#include "timer.h"
#include "typedef.h"

#define MAX_TIMER_CNT 10
u8 g_TimerCnt = 0;

void RZ7899_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5;
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

void Timer2Callback() {
	g_TimerCnt = (g_TimerCnt + 1) % MAX_TIMER_CNT;
	if (g_TimerCnt < 1) {
		P_VM1_RZ7899_I2 = 0;
	} else {
		P_VM1_RZ7899_I2 = 1;
	}
}

void Timer_Config() {
	TIM_InitTypeDef TIM_InitStructure; //结构定义
	TIM_InitStructure.TIM_Interrupt = ENABLE; //中断是否允许, ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T; //指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE; //是否输出高速脉冲, ENABLE或DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 1000); //初值
	TIM_InitStructure.TIM_Value = 65536UL - 10; //初值
	TIM_InitStructure.TIM_Run = ENABLE; //是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer2, &TIM_InitStructure); //初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	
	SET_INTERRUPT_CALLBACK(Timer2Callback);
}

void main() {
	RZ7899_GPIO_Config();
	UART_Config();
	Timer_Config();
	EA = 1;
	
	P_VM1_RZ7899_I1 = 1;
	P_VM1_RZ7899_I2 = 1;

	while(1) {
		/*delay_ms(100);
		// PrintString1("STC8H8K64U UART1 Test Programme!\r\n");
		if (COM1.RX_TimeOut > 0) {
			if (--COM1.RX_TimeOut == 0) {
				u8 i;
				if (COM1.RX_Cnt > 0) {
					for (i = 0; i < COM1.RX_Cnt; ++i) {
						TX1_write2buff(RX1_Buffer[i]);
						if (RX1_Buffer[i] == '0') {
							P_VM1_RZ7899_I1 = 0;
							P_VM1_RZ7899_I2 = 0;
						} else if (RX1_Buffer[i] == '1') {
							P_VM1_RZ7899_I1 = 1;
							P_VM1_RZ7899_I2 = 0;
						} else if (RX1_Buffer[i] == '2') {
							P_VM1_RZ7899_I1 = 0;
							P_VM1_RZ7899_I2 = 1;
						} else if (RX1_Buffer[i] == '3') {
							P_VM1_RZ7899_I1 = 1;
							P_VM1_RZ7899_I2 = 1;
						}
					}
					COM1.RX_Cnt = 0;
				}
			}
		}*/
	}
}