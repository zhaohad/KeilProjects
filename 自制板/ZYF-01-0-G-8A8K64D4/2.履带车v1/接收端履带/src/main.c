#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "uart.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "G01_S.h"
#include "command.h"

#define TEST

bit g_Mode = MODE_LVDAI;
xdata u8 g_recvBuf[18];

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void MOTOR_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2, &conf);
}

void process_command(u8 cmd, u8 value) {
	switch (cmd) {
		case ADC_COMMAND_0:
			if (value > FORWARD_THRESHOLD) {
				P_VM2_RZ7899_I1 = 1;
				P_VM2_RZ7899_I2 = 0;
				// OLED_ShowString8(0, 0, "R  F");
			}else if (value < BACKWARD_THRESHOLD) {
				P_VM2_RZ7899_I1 = 0;
				P_VM2_RZ7899_I2 = 1;
				// OLED_ShowString8(0, 0, "R  B");
			} else {
				P_VM2_RZ7899_I1 = 0;
				P_VM2_RZ7899_I2 = 0;
				// OLED_ShowString8(0, 0, "R  S");
			}
			break;
		case ADC_COMMAND_2:
			if (value > FORWARD_THRESHOLD) {
				P_VM1_RZ7899_I1 = 1;
				P_VM1_RZ7899_I2 = 0;
				// OLED_ShowString8(0, 1, "L  F");
			}else if (value < BACKWARD_THRESHOLD) {
				P_VM1_RZ7899_I1 = 0;
				P_VM1_RZ7899_I2 = 1;
				// OLED_ShowString8(0, 1, "L  B");
			} else {
				P_VM1_RZ7899_I1 = 0;
				P_VM1_RZ7899_I2 = 0;
				// OLED_ShowString8(0, 1, "L  S");
			}
			break;
	}
}

void main() {
	bit exist;

#ifdef TEST
	xdata u8 outL = 0;
	OLED12864_Init();
	// OLED_Clear();
#endif

	NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();
	MOTOR_GPIO_Config();

#ifdef TEST
	OLED_ShowString8(0, 0, "CHECK MODULE...");
#endif

	exist = NRF24L01_check();
	
#ifdef TEST
	if (exist) {
		OLED_ShowString8(0, outL, "G01-S Online");
	} else {
		OLED_ShowString8(0, outL, "G01-S Offline");
		while (1);
	}
	outL++;
	
	_nop_();_nop_();_nop_();_nop_();_nop_();

	OLED_ShowString8(0, outL, "Set MODE_RX");
	_nop_();_nop_();_nop_();_nop_();_nop_();
	outL++;
	OLED_Clear();
#endif
	
	RF24L01_Init();
	RF24L01_Set_Mode(MODE_RX); //接收模式

	while(1) {
		xdata uint8_t rx;

#ifdef TEST
		outL = 0;
#endif

		rx = NRF24L01_RxPacket(g_recvBuf); //接收字节
		
		if (rx == 0) {
#ifdef TEST
			OLED_Clear();
			OLED_ShowString(0, 0, "Received 0 !!!");
#endif
		} else {
			xdata u8 readPos;
			
			readPos = 0;
			while (readPos < rx) {

#ifdef TEST
				xdata uint8_t s1[10];
				xdata uint8_t s2[10];
				xdata uint8_t str[10];
#endif

				xdata u8 cmd;
				xdata u8 value;

				cmd = g_recvBuf[readPos++];
				value = g_recvBuf[readPos++];
				if (cmd == value && cmd == MODE_COMMAND) {
					break;
				}

#ifdef TEST
				uintToS(cmd, s1, 10);
				uintToS(value, s2, 10);
				sprintf(str, "%s:%s", s1, s2);
				OLED_ShowString8(0, outL++, str);
#endif

				process_command(cmd, value);
			}
		}
	}
}