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

void on_UART_Rec_1Byte(u8 d) {
	COM1.B_RX_OK = 0;
	COM1.RX_TimeOut = TimeOutSet1;
	RX1_Buffer[COM1.RX_Cnt++] = d;
	if(COM1.RX_Cnt >= COM_RX1_Lenth) {
		COM1.RX_Cnt = 0;
	}
	COM1.B_RX_OK = 1;
}

void OLED_GPIO_MOTOR_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P6, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);
	
	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);
	
		conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P7, &conf);
}

#define N 8

unsigned int cntStep = 2965; // 
void main() {
	u8 i = 0;
	bit forward = 0;
	OLED12864_Init();
	OLED_ShowString(0, 0, "Init...");
	
	delay_ms(250);
	OLED_ShowString(0, 0, "Init Done");
	/*PrintString1("AT\r\n");*/
	
	OLED_GPIO_MOTOR_Config();
	/*M_A1 = 0;
	M_B1 = 0;
	M_A2 = 0;
	M_B2 = 1;*/

	while(1) {
		if (cntStep == 0) {
			break;
		}
		--cntStep;
		if ((i % N) == 0) {
			M_A1 = 1;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 0;
		  OLED_ShowString(0, 4, "0");
		} else if ((i % N) == 1) {
			M_A1 = 1;
			M_B1 = 1;
			M_A2 = 0;
			M_B2 = 0;
			OLED_ShowString(0, 4, "1");
		} else if ((i % N) == 2) {
			M_A1 = 0;
			M_B1 = 1;
			M_A2 = 0;
			M_B2 = 0;
			OLED_ShowString(0, 4, "2");
		} else if ((i % N) == 3) {
			M_A1 = 0;
			M_B1 = 1;
			M_A2 = 1;
			M_B2 = 0;
			OLED_ShowString(0, 4, "3");
		} else if ((i % N) == 4) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 1;
			M_B2 = 0;
			OLED_ShowString(0, 4, "4");
		} else if ((i % N) == 5) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 1;
			M_B2 = 1;
			OLED_ShowString(0, 4, "5");
		} else if ((i % N) == 6) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 1;
			OLED_ShowString(0, 4, "6");
		} else if ((i % N) == 7) {
			M_A1 = 1;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 1;
			OLED_ShowString(0, 4, "7");
		}
		if (forward) {
			--i;
			if (i < 0 || i > N) {
				i = N - 1;
			}
		} else {
			++i;
			if (i >= N) {
				i = 0;
			}
		}
	}
	
	M_A1 = 0;
	M_B1 = 0;
	M_A2 = 0;
	M_B2 = 0;
	while (1);
}