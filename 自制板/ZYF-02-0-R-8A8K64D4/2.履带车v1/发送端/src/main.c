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


bit g_Rec = 0;
bit g_Mode = MODE_LVDAI;
xdata u8 g_sendBuf[18];

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

void MOTOR_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	// conf.Mode = GPIO_OUT_PP;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P6, &conf);
	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P7, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
}

void KEY_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P7, &conf);
}

void ADC_Init(void) {
	xdata ADC_InitTypeDef ADC_InitStructure;		//结构定义
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);						//ADC电源开关, ENABLE或DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

void showBootIMG() {
	u8 i;
	OLED_ShowBootIMG();
	for (i = 0; i < 5; ++i) {
		delay_ms(255);
	}
	OLED_Clear();
}

void main() {
	xdata u8 outL = 0;
	bit exist;
	ADC_Init();
	OLED12864_Init();
	showBootIMG();

	NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();

	OLED_ShowString8(0, 0, "CHECK MODULE...");
	exist = NRF24L01_check();
	
	exist = NRF24L01_check();
	if (exist) {
		OLED_ShowString8(0, outL, "G01-S Online");
	} else {
		OLED_ShowString8(0, outL, "G01-S Offline");
		while (1);
	}
	outL++;
	
	RF24L01_Init();
	_nop_();_nop_();_nop_();_nop_();_nop_();

	if (g_Rec) {
		OLED_ShowString8(0, outL, "Set MODE_RX");
		RF24L01_Set_Mode(MODE_RX); //接收模式
		_nop_();_nop_();_nop_();_nop_();_nop_();
	} else {
		OLED_ShowString8(0, outL, "Set MODE_TX");
		RF24L01_Set_Mode(MODE_TX); //发送模式
		_nop_();_nop_();_nop_();_nop_();_nop_();
	}
	outL++;
	OLED_Clear();

	while(1) {
		xdata u16 adc;
		xdata u8 adcV1, adcV2, adcV3, adcV4;
		xdata u8 strP[10];
		xdata u8 strD[20];
		outL = 0;

		adc = Get_ADCResult(CHANEL_ADC1);
		adcV1 = (u8) (adc / 4096.f * 100.f);
		uintToS(adcV1, strP, 10);
		sprintf(strD, "CHANEL1: %s", strP);
		// OLED_ShowString8(0, outL, strD);
		outL++;

		adc = Get_ADCResult(CHANEL_ADC2);
		adcV2 = (u8) (adc / 4096.f * 100.f);
		uintToS(adcV2, strP, 10);
		sprintf(strD, "CHANEL2: %s", strP);
		// OLED_ShowString8(0, outL, strD);
		outL++;

		adc = Get_ADCResult(CHANEL_ADC3);
		adcV3 = (u8) (adc / 4096.f * 100.f);
		uintToS(adcV3, strP, 10);
		sprintf(strD, "CHANEL3: %s", strP);
		// OLED_ShowString8(0, outL, strD);
		outL++;

		adc = Get_ADCResult(CHANEL_ADC4);
		adcV4 = (u8) (adc / 4096.f * 100.f);
		uintToS(adcV4, strP, 10);
		sprintf(strD, "CHANEL4: %s", strP);
		// OLED_ShowString8(0, outL, strD);
		outL++;

		{
			xdata uint8_t sendResult;
			xdata u8 sendPos = 0;
			xdata u8 readPos = 0;
			g_sendBuf[sendPos++] = MODE_COMMAND;
			g_sendBuf[sendPos++] = g_Mode;
			g_sendBuf[sendPos++] = ADC_COMMAND_0;
			g_sendBuf[sendPos++] = adcV1;
			g_sendBuf[sendPos++] = ADC_COMMAND_1;
			g_sendBuf[sendPos++] = adcV2;
			g_sendBuf[sendPos++] = ADC_COMMAND_2;
			g_sendBuf[sendPos++] = adcV3;
			g_sendBuf[sendPos++] = ADC_COMMAND_3;
			g_sendBuf[sendPos++] = adcV4;
			
			outL = 0;
			while (readPos < sendPos) {
				xdata u8 cmd;
				xdata u8 value;
				xdata uint8_t s1[10];
				xdata uint8_t s2[10];
				xdata uint8_t str[10];
				cmd = g_sendBuf[readPos++];
				value = g_sendBuf[readPos++];
				uintToS(cmd, s1, 10);
				uintToS(value, s2, 10);
				sprintf(str, "%s:%s", s1, s2);
				OLED_ShowString8(0, outL++, str);
			}

			sendResult = NRF24L01_TxPacket((uint8_t *) g_sendBuf, sendPos);
			if (sendResult == TX_OK) {
				OLED_ShowString8(0, outL++, "SUCCEES");
			} else {
				OLED_ShowString8(0, outL++, "Failed");
			}
		}
	}

	/*while(1) {
		u8 outLL = outL;
		xdata uint8_t res;
		xdata uint8_t tx[1];
		xdata uint8_t numStr[10];
		xdata uint8_t str[20];

		if (g_Rec) {
			xdata uint8_t rx;
			xdata uint8_t g_rece[8];
			u8 i;
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
	}*/
}