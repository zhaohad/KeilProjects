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

void main() {
	bit exist;
	GOPI_Config();

	OLED_Init();

	OLED_ShowString(0, 0, "CHECK MODULE...");
	exist = NRF24L01_check();
	
	ADC_Init();
	
	if (exist) {
		OLED_ShowString(0, 2, "DONE");
	} else {
		OLED_ShowString(0, 2, "NOT EXIST");
	}
	
	P_MOTOR = 0;

	while(1) {
		xdata u16 adc = 0;
		xdata float percentage;
		xdata u8 strP[10];
		xdata u8 strD[20];
		
		xdata u8 k0 = P_KEY_0 ? 1 : 0;
		xdata u8 k1 = P_KEY_1 ? 1 : 0;
		xdata u8 k2 = P_KEY_2 ? 1 : 0;
		xdata u8 k3 = P_KEY_3 ? 1 : 0;
		
		/*adc = Get_ADCResult(CHANEL_ADC0);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL1: %s", strP);
		OLED_ShowString(0, 0, strD);
		
		adc = Get_ADCResult(CHANEL_ADC1);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL1: %s", strP);
		OLED_ShowString(0, 2, strD);
		
		adc = Get_ADCResult(CHANEL_ADC2);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL1: %s", strP);
		OLED_ShowString(0, 4, strD);
		
		adc = Get_ADCResult(CHANEL_ADC3);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL1: %s", strP);
		OLED_ShowString(0, 6, strD);*/
		sprintf(strD, "K0:0 K1:0 K2:0");
		strD[3] = P_KEY_0 ? '1' : '0';
		strD[8] = P_KEY_1 ? '1' : '0';
		strD[13] = P_KEY_2 ? '1' : '0';
		OLED_ShowString(0, 0, strD);

		sprintf(strD, "K3:0 K4:0 K5:0");
		strD[3] = P_KEY_3 ? '1' : '0';
		strD[8] = P_KEY_4 ? '1' : '0';
		strD[13] = P_KEY_5 ? '1' : '0';
		OLED_ShowString(0, 2, strD);
		
		sprintf(strD, "K6:0 K7:0 K8:0");
		strD[3] = P_KEY_6 ? '1' : '0';
		strD[8] = P_KEY_7 ? '1' : '0';
		strD[13] = P_KEY_8 ? '1' : '0';
		OLED_ShowString(0, 4, strD);
		
		sprintf(strD, "K9:0 KA:0 KB:0");
		strD[3] = P_KEY_9 ? '1' : '0';
		strD[8] = P_KEY_10 ? '1' : '0';
		strD[13] = P_KEY_11 ? '1' : '0';
		OLED_ShowString(0, 6, strD);
		
		P_LED_1 = P_KEY_YG0;
		P_LED_2 = P_KEY_YG1;
	}
}