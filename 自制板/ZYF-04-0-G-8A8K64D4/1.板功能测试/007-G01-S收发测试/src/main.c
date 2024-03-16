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
#include "stc8a_adc.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P0, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P2, &conf);
}

void LED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
}

void G01_S_GPIO_config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);
	
	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P3, &conf);
	
	NRF24L01_Gpio_Init();
}

void RZ7899_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P2, &conf);
}

void KEY_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_3 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P2, &conf);

	conf.Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P1, &conf);
	
	conf.Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P0, &conf);
	
	conf.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P3, &conf);
}

void GOPI_Config() {
	OLED_GPIO_Config();
	
	LED_GPIO_Config();

	G01_S_GPIO_config();
	
	RZ7899_GPIO_Config();
}

void ADC_Init() {
	ADC_InitTypeDef ADC_InitStructure;		//结构定义
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);						//ADC电源开关, ENABLE或DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

bit g_Rec = 0;
u8 outL = 0;

void main() {
	bit exist;
	GOPI_Config();

	OLED_Init();

	OLED_ShowString8(0, outL, "CHECK MODULE...");
	outL++;
	exist = NRF24L01_check();
	
	if (exist) {
		OLED_ShowString8(0, outL, "DONE");
	} else {
		OLED_ShowString8(0, outL, "NOT EXIST");
	}
	outL++;
	
	RF24L01_Init();
	_nop_();_nop_();_nop_();_nop_();_nop_();

	if (g_Rec) {
		OLED_ShowString8(0, outL, "Set MODE_RX");
		RF24L01_Set_Mode(MODE_RX); //接收模式
	} else {
		OLED_ShowString8(0, outL, "Set MODE_TX");
		RF24L01_Set_Mode(MODE_TX); //发送模式
	}
	_nop_();_nop_();_nop_();_nop_();_nop_();
	outL++;

	while(1) {
		xdata u8 outLL = outL;
		xdata uint8_t numStr[10];
		xdata uint8_t str[20];

		if (g_Rec) {
			xdata uint8_t rx;
			xdata uint8_t g_rece[8];
			xdata u8 i;
			sprintf(str, "Receiving...");
			OLED_ShowString8(0, outLL, str);
			outLL++;
			rx = NRF24L01_RxPacket(g_rece); //接收字节

			if (rx != 0) {
				uintToS(rx, numStr, 10);
				sprintf(str, "Received: %s   ", numStr);
				OLED_ShowString8(0, outLL, str);
				outLL++;
				
				sprintf(str, "d: ");
				for (i = 0; i < rx; ++i) {
					u8 d = g_rece[i];
					uintToS(d, numStr, 10);
					sprintf(str, "%s %s", str, numStr);
				}
				sprintf(str, "%s    ", str);
				OLED_ShowString8(0, outLL, str);
				outLL++;
			}
		} else {
			xdata uint8_t tx[1];
			xdata int someNumber = 253;
			xdata uint8_t res;
			tx[0] = someNumber;
			intToS(tx[0], numStr, 10);
			sprintf(str, "Sending %s   ", numStr);
			OLED_ShowString8(0, outLL, str);
			outLL++;
			res = NRF24L01_TxPacket((uint8_t *) tx, 1);
			if (res == TX_OK) {
				sprintf(str, "SUCCEES");
			} else {
				sprintf(str, "Failed");
			}
			OLED_ShowString8(0, outLL, str);
			outLL++;

			someNumber++;
			if (someNumber > 100) {
				someNumber = 0;
			}
			
			delay_ms(3000);
		}
	}
}