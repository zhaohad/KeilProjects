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
	GPIO_InitTypeDef GPIO_InitStructure; //结构定义
	PWM15_InitTypeDef PWM15_InitStructure;

	GPIO_InitStructure.Pin  = GPIO_Pin_All; //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp; //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure); //初始化

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWM使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 24920;		//PWM周期,  0~0x7fff // 使用20.000 MHZ的50HZPWM输出
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS; //时钟源选择,  PWM_CLK_SYS, PWM_CLK_TM2
	// PWM15_InitStructure.PWM_Clock_PS  = 0;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_Clock_PS  = 15;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//计数器归零中断使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//计数器使能,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	PWM15Duty(PWM15_0, 0, 99);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWMChannelCtrl(PWM15_0,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
	// 输出引脚切换用 PWM15_PWM0_SW()，默认P20
}


bit debug = 1;


void main() {
	int a = 99, f = 1;
	GPIO_Config();
	PWM15bit_init();
	
	if (debug) {
		PWM15Duty(PWM15_0, 1875, 0); // 使用20.000MHZ的1.5ms高电平输出，控制舵机90度旋转
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