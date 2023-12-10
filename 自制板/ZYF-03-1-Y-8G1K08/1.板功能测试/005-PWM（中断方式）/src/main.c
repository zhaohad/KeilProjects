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
	xdata COMx_InitDefine config; //�ṹ����
	config.UART_Mode = UART_8bit_BRTx; //ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	config.UART_BRT_Use = BRT_Timer1; //ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
  config.UART_BaudRate = 9600ul;	//������, һ�� 110 ~ 115200
  config.UART_RxEnable = ENABLE; //��������, ENABLE��DISABLE
  config.BaudRateDouble = DISABLE; //�����ʼӱ�, ENABLE��DISABLE
  config.UART_Interrupt = ENABLE; //�ж�����, ENABLE��DISABLE
  config.UART_Polity = Polity_0; //ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
  // config.UART_P_SW = UART1_SW_P30_P31; //�л��˿�, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	config.UART_P_SW = UART1_SW_P16_P17; //�л��˿�, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
  UART_Configuration(UART1, &config); //��ʼ������1 UART1,UART2,UART3,UART4
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
	TIM_InitTypeDef TIM_InitStructure; //�ṹ����
	TIM_InitStructure.TIM_Interrupt = ENABLE; //�ж��Ƿ�����, ENABLE��DISABLE. (ע��: Timer2�̶�Ϊ16λ�Զ���װ, �жϹ̶�Ϊ�����ȼ�)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T; //ָ��ʱ��Դ, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE; //�Ƿ������������, ENABLE��DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 1000); //��ֵ
	TIM_InitStructure.TIM_Value = 65536UL - 10; //��ֵ
	TIM_InitStructure.TIM_Run = ENABLE; //�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer2, &TIM_InitStructure); //��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	
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