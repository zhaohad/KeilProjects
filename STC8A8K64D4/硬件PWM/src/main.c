#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "stc8a_pwm15bit.h"
#include "typedef.h"

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
}

void PWM15bit_init() {
	GPIO_InitTypeDef GPIO_InitStructure; //�ṹ����
	PWM15_InitTypeDef PWM15_InitStructure;

	GPIO_InitStructure.Pin  = GPIO_Pin_All; //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp; //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure); //��ʼ��

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWMʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 24920;		//PWM����,  0~0x7fff // ʹ��20.000 MHZ��50HZPWM���
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS; //ʱ��Դѡ��,  PWM_CLK_SYS, PWM_CLK_TM2
	// PWM15_InitStructure.PWM_Clock_PS  = 0;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_Clock_PS  = 15;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//�����������ж�ʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//������ʹ��,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	PWM15Duty(PWM15_0, 0, 99);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWMChannelCtrl(PWM15_0,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	// ��������л��� PWM15_PWM0_SW()��Ĭ��P20
}


bit debug = 1;


void main() {
	int a = 99, f = 1;
	GPIO_Config();
	PWM15bit_init();
	
	if (debug) {
		PWM15Duty(PWM15_0, 1875, 0); // ʹ��20.000MHZ��1.5ms�ߵ�ƽ��������ƶ��90����ת
		while(1);
	}
	
	while (1) {
		// P_MOTOR_A = 0;
		// P_MOTOR_B = 1;
		int i = 0;
		if (a >= 99) {
			f = -1;;
		} else if (a <= 1) {
			f = 1;
		}
		a += f;
		for (i = 0; i < 1000; ++i) {
			PWM15Duty(PWM15_0, 0, a);
		}
	}
}