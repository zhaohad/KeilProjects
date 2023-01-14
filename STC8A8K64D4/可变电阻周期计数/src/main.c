#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "rotationCounter.h"

bit forward = 1;

void ADC_config();
void ADC_GPIO_Config();
void SPI_Config();
void OLED_Config();
void OLED_GPIO_Config();
void MOTOR_GPIO_Config();

void GPIO_T() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_6;
	GPIO_Inilize(GPIO_P3, &conf);
}

void main() {
	GPIO_T();
	P36 = 0;
	MOTOR_GPIO_Config();
	OLED_Config();
	ADC_config();
	if (forward) {
		P_MOTOR_A = 0;
		P_MOTOR_B = 1;
	} else {
		P_MOTOR_A = 1;
		P_MOTOR_B = 0;
	}

	delay_ms(255);
	P36 = 1;
	while(1) {
		u16 adc = Get_ADCResult(ADC_CHANEL);
		float r;
		int cnt;
		u8 str[20];
		r = adc / 4096.f * 100.f;
		intToS(adc, str, 20);
		OLED_ShowString(0, 0, str);
		floatToSS(r, str, 20, 3);
		OLED_ShowString(0, 2, str);
		countRotation((unsigned char) r);
		cnt = getRotationCount();
		intToS(cnt, str, 20);
		OLED_ShowString(0, 4, str);
	}
}

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED_Config() {
	OLED_GPIO_Config();
	OLED_Init();
}

void SPI_Config() {
	SPI_InitTypeDef conf;
	conf.SPI_Enable = ENABLE; //SPI���� ENABLE, DISABLE
	conf.SPI_SSIG = ENABLE; //Ƭѡλ ENABLE, DISABLE
	conf.SPI_FirstBit = SPI_MSB; //��λ���� SPI_MSB, SPI_LSB
	conf.SPI_Mode = SPI_Mode_Master; //����ѡ�� SPI_Mode_Master, SPI_Mode_Slave
	conf.SPI_CPOL = SPI_CPOL_Low; //ʱ����λ   SPI_CPOL_High,   SPI_CPOL_Low
	conf.SPI_CPHA = SPI_CPHA_2Edge; //���ݱ���   SPI_CPHA_1Edge, SPI_CPHA_2Edge
	conf.SPI_Speed = SPI_Speed_64; //SPI�ٶ�    SPI_Speed_4, SPI_Speed_16, SPI_Speed_64, SPI_Speed_2
	SPI_Init(&conf);
	
	P_SW1 = 0x00; // ʹ�� SS:P12 MOSI:P13 MISO:P14 SCLK:P15
	NVIC_SPI_Init(ENABLE, Priority_0); //�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void ADC_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P0, &conf);
}

void ADC_config(void) {
	ADC_InitTypeDef ADC_InitStructure;		//�ṹ����
	ADC_GPIO_Config();
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void MOTOR_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P0, &conf);
}