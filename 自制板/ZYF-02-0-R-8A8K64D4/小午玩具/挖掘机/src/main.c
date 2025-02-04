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
#include "ActionCMD.h"

u8 outL = 0;

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
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC 模拟信号采样时间控制, 0#define CMD_ARM_2_UP 17~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);						//ADC电源开关, ENABLE或DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

void doCmd(u8 cmd, u8 v) {
	switch (cmd) {
		case CMD_AWAIT:
			P_VM1_RZ7899_I1 = 0;
			P_VM1_RZ7899_I2 = 0;
			P_VM1_DRV8833_I1 = 0;
			P_VM1_DRV8833_I2 = 0;
			P_VM1_DRV8833_I3 = 0;
			P_VM1_DRV8833_I4 = 0;
			P_VM2_RZ7899_I1 = 0;
			P_VM2_RZ7899_I2 = 0;
			P_VM2_DRV8833_I1 = 0;
			P_VM2_DRV8833_I2 = 0;
			P_VM2_DRV8833_I3 = 0;
			P_VM2_DRV8833_I4 = 0;
			break;
		case CMD_ARM_1_UP:
			P_VM2_DRV8833_I1 = v;
			P_VM2_DRV8833_I2 = 0;
			break;
		case CMD_ARM_1_DOWN:
			P_VM2_DRV8833_I1 = 0;
			P_VM2_DRV8833_I2 = v;
			break;
		case CMD_ARM_2_UP:
			P_VM2_DRV8833_I3 = 0;
			P_VM2_DRV8833_I4 = v;
			break;
		case CMD_ARM_2_DOWN:
			P_VM2_DRV8833_I3 = v;
			P_VM2_DRV8833_I4 = 0;
			break;
		case CMD_ARM_3_UP:
			P_VM1_DRV8833_I3 = 0;
			P_VM1_DRV8833_I4 = v;
			break;
		case CMD_ARM_3_DOWN:
			P_VM1_DRV8833_I3 = v;
			P_VM1_DRV8833_I4 = 0;
			break;
		case CMD_PLATFORM_TURN_LEFT:
			P_VM1_DRV8833_I1 = 0;
			P_VM1_DRV8833_I2 = v;
			break;
		case CMD_PLATFORM_TURN_RIGHT:
			P_VM1_DRV8833_I1 = v;
			P_VM1_DRV8833_I2 = 0;
			break;
		case CMD_LEFT_WHEEL:
			if (v > 50) {
				P_VM1_RZ7899_I1 = 0;
				P_VM1_RZ7899_I2 = 1;
			} else if (v < 50) {
				P_VM1_RZ7899_I1 = 1;
				P_VM1_RZ7899_I2 = 0;
			} else {
				P_VM1_RZ7899_I1 = 0;
				P_VM1_RZ7899_I2 = 0;
			}
			break;
		case CMD_RIGHT_WHEEL:
			if (v > 50) {
				P_VM2_RZ7899_I1 = 0;
				P_VM2_RZ7899_I2 = 1;
			} else if (v < 50) {
				P_VM2_RZ7899_I1 = 1;
				P_VM2_RZ7899_I2 = 0;
			} else {
				P_VM2_RZ7899_I1 = 0;
				P_VM2_RZ7899_I2 = 0;
			}
			break;
	}
}

void main() {
	int someNumber = 0;
	bit exist;
	MOTOR_GPIO_Config();
	
	OLED12864_Init();

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

	OLED_ShowString8(0, outL, "Set MODE_RX");
	RF24L01_Set_Mode(MODE_RX); //接收模式
	_nop_();_nop_();_nop_();_nop_();_nop_();

	outL++;

	while(1) {
		u8 i;
		u8 outLL = outL;
		xdata uint8_t numStr[10];
		xdata uint8_t str[20];
		xdata uint8_t rx;
		xdata uint8_t g_rece[8];
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
			for (i = 0; i < rx; i += 2) {
				u8 d = g_rece[i];
				uintToS(d, numStr, 10);
				sprintf(str, "%s %s", str, numStr);
			}
			sprintf(str, "%s    ", str);
			OLED_ShowString8(0, outLL, str);
			outLL++;
			
			for (i = 0; i < rx; ++i) {
				doCmd(g_rece[i], g_rece[i + 1]);
			}
		}
	}
}