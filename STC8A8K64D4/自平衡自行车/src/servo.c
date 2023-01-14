#include "servo.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"

xdata int g_servo_timer;
xdata int g_target_timer = -1;
xdata int g_future_timer;

// 11.0592 MHz 8bit auto load. value: 0x91 for 10us
void Timer_config() {
	TIM_InitTypeDef TIM_InitStructure;						//结构定义
	TIM_InitStructure.TIM_Mode = TIM_8BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 100000UL);		//初值,
	TIM_InitStructure.TIM_Run = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0, &TIM_InitStructure);					//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	TL0 = 0x91;
	TH0 = 0x91;
	NVIC_Timer0_Init(ENABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
	EA = 1;
}

void Servo_Init() {
	Timer_config();
	g_target_timer = 0;
	g_servo_timer = 0;
}

void Servo_Set_Target_Degree(int td) {
	g_future_timer = td * 10 / 9.0f + 50 + 0.000001f;
	if (g_target_timer < 0) {
		g_target_timer = g_future_timer;
	}
}

void Servo_Timer_10us_Callback() {
	if (g_servo_timer < g_target_timer) {
		SET_CONTROL();
	} else {
		CLR_CONTROL();
	}

	g_servo_timer++;
	if (g_servo_timer > MAX_SERVO_TIMER_10US) {
		g_target_timer = g_future_timer;
		g_servo_timer = 0;
	}
}