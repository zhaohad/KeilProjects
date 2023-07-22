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
	GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);
}

void	UART_config() {
	xdata COMx_InitDefine COMx_InitStructure; //�ṹ����
	UART1_SW(P_UART);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 115200ul; //������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //��������,   ENABLE��DISABLE

	UART_Configuration(UART1, &COMx_InitStructure); //��ʼ������2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE, Priority_1); //�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void on_UART_Rec_1Byte(u8 d) {
	if(COM1.B_RX_OK == 0) {
		RX1_Buffer[COM1.RX_Cnt++] = d;
		if(COM1.RX_Cnt >= COM_RX1_Lenth) {
			COM1.RX_Cnt = 0;
		}
		COM1.RX_TimeOut = TimeOutSet1;
	}
}

void UART_Init() {
	COM1.TX_read = 0;
	COM1.RX_Cnt = 0;
	UART_GPIO_Config();
	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	UART_config();
}

void main() {
	OLED12864_Init();
	OLED_ShowString(0, 0, "Init...");
	
	UART_Init();
	EA = 1;

	while(1) {
		if (COM1.TX_read != COM1.RX_Cnt) {
			TX1_write2buff(RX1_Buffer[COM1.TX_read++]);
			if (COM1.TX_read >= COM_RX1_Lenth) {
				COM1.TX_read = 0;
			}
		}
	}
}