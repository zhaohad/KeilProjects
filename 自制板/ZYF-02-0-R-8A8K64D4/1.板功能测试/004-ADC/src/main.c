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

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
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
	GPIO_InitTypeDef conf;
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
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P7, &conf);
}

void ADC_Init(void) {
	ADC_InitTypeDef ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void main() {
	ADC_Init();
	OLED12864_Init();

	while(1) {
		xdata u16 adc = Get_ADCResult(CHANEL_ADC1);
		xdata float percentage;
		xdata u8 strP[10];
		xdata u8 strD[20];
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL1: %s", strP);
		// sprintf(strD, "CHANEL1");
		OLED_ShowString(0, 0, strD);

		adc = Get_ADCResult(CHANEL_ADC2);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL2: %s", strP);
		OLED_ShowString(0, 2, strD);

		adc = Get_ADCResult(CHANEL_ADC3);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL3: %s", strP);
		OLED_ShowString(0, 4, strD);

		adc = Get_ADCResult(CHANEL_ADC4);
		percentage = adc / 4096.f * 100.f;
		floatToSS(percentage, strP, 10, 2);
		sprintf(strD, "CHANEL4: %s", strP);
		OLED_ShowString(0, 6, strD);
	}
}