/**
 * 使用30MHz烧录
 */
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
#include "global_status.h"
#include "joinstick.h"
#include "communication_protocol.h"

#define HEART_BEAT_RETRY_CNT 3
#define HEART_BEAT_INTERVAL 10

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
	
	KEY_GPIO_Config();
	
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

u8 outL = 0;

void All_init() {
	bit exist;
	xdata u8 someNumber = 0;
	GOPI_Config();
	
	ADC_Init();

	Global_Status_Timer_Init();
	// Global_Status_Hear_Beat_Timer_Init();

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

	OLED_ShowString8(0, outL, "Set MODE_TX");
	RF24L01_Set_Mode(MODE_TX); //发送模式
	_nop_();_nop_();_nop_();_nop_();_nop_();
	outL++;
	
	// Global_Status_Do_Heart_Beat(1);
}


/**
 * 使用30MHz烧录
 */
void main() {
	bit lastLH = 0, lastLV = 0, lastRH = 0, lastRV = 0;
	bit lastK0 = 0, lastK1 = 0, lastK2 = 0, lastK3 = 0;
	bit lastK4 = 0, lastK5 = 0, lastK6 = 0, lastK7 = 0;
	bit lastK8 = 0, lastK9 = 0, lastK10 = 0, lastK11 = 0;
	bit lastLK = 0, lastRK = 0;
	xdata u8 heartBeatRetryCnt = 0;
	xdata u8 heartBeatIntervalCnt = 0;
	All_init();

	while(1) {
		xdata u16 adc = 0;
		xdata float percentage;
		xdata u8 strP[10];
		xdata u8 strD[20];
		xdata u8 js;
		xdata u8 tx_buf[MAX_INTERACTIVE_CNT * 2];
		xdata u8 tx_len = 0;
		xdata u8 res = 0;
		xdata u8 curLine = 0;
		adc = Get_ADCResult(CHANEL_ADC0);
		percentage = adc / 4096.f * 100.f;
		js = JOIN_STICK_Pu_Yao_FJM10K_S_Cal(percentage);
		uintToS(js, strP, 10);
		sprintf(strD, "C1: %s ", strP);
		OLED_ShowString8(0, curLine++, strD);
		if (lastLH || js != 50) {
			tx_buf[tx_len++] = KEY_JOINSTICK_LEFT_H;
			tx_buf[tx_len++] = js;
		}
		lastLH = js != 50;
		
		adc = Get_ADCResult(CHANEL_ADC1);
		percentage = adc / 4096.f * 100.f;
		js = JOIN_STICK_Pu_Yao_FJM10K_S_Cal(percentage);
		uintToS(js, strP, 10);
		sprintf(strD, "C2: %s ", strP);
		OLED_ShowString8(0, curLine++, strD);
		if (lastLV || js != 50) {
			tx_buf[tx_len++] = KEY_JOINSTICK_LEFT_V;
			tx_buf[tx_len++] = js;
		}
		lastLV = js != 50;
		
		adc = Get_ADCResult(CHANEL_ADC2);
		percentage = adc / 4096.f * 100.f;
		js = JOIN_STICK_Pu_Yao_FJM10K_S_Cal(percentage);
		uintToS(js, strP, 10);
		sprintf(strD, "C3: %s ", strP);
		OLED_ShowString8(0, curLine++, strD);
		if (lastRH || js != 50) {
			tx_buf[tx_len++] = KEY_JOINSTICK_RIGHT_H;
			tx_buf[tx_len++] = js;
		}
		lastRH = js != 50;
		
		adc = Get_ADCResult(CHANEL_ADC3);
		percentage = adc / 4096.f * 100.f;
		js = JOIN_STICK_Pu_Yao_FJM10K_S_Cal(percentage);
		uintToS(js, strP, 10);
		sprintf(strD, "C4: %s ", strP);
		OLED_ShowString8(0, curLine++, strD);
		if (lastRV || js != 50) {
			tx_buf[tx_len++] = KEY_JOINSTICK_RIGHT_V;
			tx_buf[tx_len++] = js;
		}
		lastRV = js != 50;
		
		if (lastLK || !P_KEY_YG0) {
			tx_buf[tx_len++] = KEY_JOINSTICK_LEFT_K;
			tx_buf[tx_len++] = !P_KEY_YG0;
		}
		lastLK = !P_KEY_YG0;

		if (lastRK || !P_KEY_YG1) {
			tx_buf[tx_len++] = KEY_JOINSTICK_RIGHT_K;
			tx_buf[tx_len++] = !P_KEY_YG1;
		}
		lastRK = !P_KEY_YG1;
		
		if (lastK0 || !P_KEY_0) {
			tx_buf[tx_len++] = KEY_K0;
			tx_buf[tx_len++] = !P_KEY_0;
		}
		lastK0 = !P_KEY_0;
		
		if (lastK1 || !P_KEY_1) {
			tx_buf[tx_len++] = KEY_K1;
			tx_buf[tx_len++] = !P_KEY_1;
		}
		lastK1 = !P_KEY_1;
		
		if (lastK2 || !P_KEY_2) {
			tx_buf[tx_len++] = KEY_K2;
			tx_buf[tx_len++] = !P_KEY_2;
		}
		lastK2 = !P_KEY_2;
		
		if (lastK3 || !P_KEY_3) {
			tx_buf[tx_len++] = KEY_K3;
			tx_buf[tx_len++] = !P_KEY_3;
		}
		lastK3 = !P_KEY_3;
		
		if (lastK4 || !P_KEY_4) {
			tx_buf[tx_len++] = KEY_K4;
			tx_buf[tx_len++] = !P_KEY_4;
		}
		lastK4 = !P_KEY_4;
		
		if (lastK5 || !P_KEY_5) {
			tx_buf[tx_len++] = KEY_K5;
			tx_buf[tx_len++] = !P_KEY_5;
		}
		lastK5 = !P_KEY_5;
		
		if (lastK6 || !P_KEY_6) {
			tx_buf[tx_len++] = KEY_K6;
			tx_buf[tx_len++] = !P_KEY_6;
		}
		lastK6 = !P_KEY_6;
		
		if (lastK7 || !P_KEY_7) {
			tx_buf[tx_len++] = KEY_K7;
			tx_buf[tx_len++] = !P_KEY_7;
		}
		lastK7 = !P_KEY_7;
		
		if (lastK8 || !P_KEY_8) {
			tx_buf[tx_len++] = KEY_K8;
			tx_buf[tx_len++] = !P_KEY_8;
		}
		lastK8 = !P_KEY_8;
		
		if (lastK9 || !P_KEY_9) {
			tx_buf[tx_len++] = KEY_K9;
			tx_buf[tx_len++] = !P_KEY_9;
		}
		lastK9 = !P_KEY_9;
		
		if (lastK10 || !P_KEY_10) {
			tx_buf[tx_len++] = KEY_K10;
			tx_buf[tx_len++] = !P_KEY_10;
		}
		lastK10 = !P_KEY_10;
		
		if (lastK11 || !P_KEY_11) {
			tx_buf[tx_len++] = KEY_K11;
			tx_buf[tx_len++] = !P_KEY_11;
		}
		lastK11 = !P_KEY_11;

		if (tx_len > 0) {
			res = NRF24L01_TxPacket((uint8_t *) tx_buf, tx_len);
			if (res == TX_OK) {
				Global_Status_Set_Status(STATUS_CONNECTED);
				heartBeatRetryCnt = 0;
			} else {
				heartBeatRetryCnt++;
				P_LED_1 = !P_LED_1;
				if (heartBeatRetryCnt > HEART_BEAT_RETRY_CNT) {
					Global_Status_Set_Status(STATUS_CONNECTING);
				}
			}
		} else {
			if (heartBeatIntervalCnt++ > HEART_BEAT_INTERVAL) {
				heartBeatIntervalCnt = 0;
				res = NRF24L01_TxPacket((uint8_t *) COMMUICATION_HEART_BEAT, HEART_BEAT_LEN);
				if (res == TX_OK) {
					heartBeatRetryCnt = 0;
					Global_Status_Set_Status(STATUS_CONNECTED);
				} else {
					heartBeatRetryCnt++;
					if (heartBeatRetryCnt > HEART_BEAT_RETRY_CNT) {
						Global_Status_Set_Status(STATUS_CONNECTING);
					}
				}
			}
			
		}
		
		delay_ms(500);
	}
}