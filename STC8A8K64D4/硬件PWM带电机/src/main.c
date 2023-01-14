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

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWM使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x7fff;		//PWM周期,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS; //时钟源选择,  PWM_CLK_SYS, PWM_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//计数器归零中断使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//计数器使能,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	// PWM15Duty(PWM15_1, 0, 999);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWMChannelCtrl(PWM15_1,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
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