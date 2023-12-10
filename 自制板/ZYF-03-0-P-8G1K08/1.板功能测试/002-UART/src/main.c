#include "typedef.h"
#include "dtos.h"
#include "STC8xxxx.h"
#include "GPIO.h"
#include "UART.h"

void OLED_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P1, &conf);
}

void UART_Config() {
	xdata COMx_InitDefine config; //�ṹ����
	config.UART_Mode = UART_8bit_BRTx; //ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	config.UART_BRT_Use = BRT_Timer2; //ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
  config.UART_BaudRate = 9600ul;	//������, һ�� 110 ~ 115200
  config.UART_RxEnable = ENABLE; //��������, ENABLE��DISABLE
  config.BaudRateDouble = DISABLE; //�����ʼӱ�, ENABLE��DISABLE
  config.UART_Interrupt = ENABLE; //�ж�����, ENABLE��DISABLE
  config.UART_Polity = Polity_0; //ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
  config.UART_P_SW = UART1_SW_P30_P31; //�л��˿�, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
  UART_Configuration(UART1, &config); //��ʼ������1 UART1,UART2,UART3,UART4
}

void main() {
	OLED_GPIO_Config();
	UART_Config();
	EA = 1;
	
	PrintString1("STC8H8K64U UART1 Test Programme!\r\n");	//UART1����һ���ַ���

	while(1) {
		delay_ms(1);
		if (COM1.RX_TimeOut > 0) {
			if (--COM1.RX_TimeOut == 0) {
				u8 i;
				if (COM1.RX_Cnt > 0) {
					for (i = 0; i < COM1.RX_Cnt; ++i) {
						TX1_write2buff(RX1_Buffer[i]);
					}
					COM1.RX_Cnt = 0;
				}
			}
		}
	}
}