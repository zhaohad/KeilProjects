#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "stc8a_pwm15bit.h"
#include "typedef.h"

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
	GPIO_Inilize(GPIO_P1, &conf);
	GPIO_Inilize(GPIO_P2, &conf);
}

void PWM15bit_init() {
	PWM15_InitTypeDef PWM15_InitStructure;

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWMʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x7fff;		//PWM����,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS; //ʱ��Դѡ��,  PWM_CLK_SYS, PWM_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//�����������ж�ʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//������ʹ��,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	// PWM15Duty(PWM15_1, 0, 999);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWMChannelCtrl(PWM15_1,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
}

void main() {
	GPIO_Config();
	PWM15bit_init();
	PWM15Duty(PWM15_1, 0, 0x7fff / 2);
	P_MOTOR_B = 0;
	// P_MOTOR_A = 1;

	while (1) {
	}
}