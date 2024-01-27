#include "servo_t0.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"

#define PERIODIC_T0 20000
#define DEFAULT_INT_T0 500

u8 g_timer_step_t0 = 0;

u16 g_timer_vs_t0[CNT_SERVOS];
u16 g_remain_timer_t0 = 0;
u8 g_enables_t0[CNT_SERVOS];

// 30.000 MHz 16bit auto load. 10 um
void Timer_config_T0() {
	TIM_InitTypeDef TIM_InitStructure;						//结构定义
	TIM_InitStructure.TIM_Mode = TIM_16Bit;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Run = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0, &TIM_InitStructure);					//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	TL0 = 0;
	TH0 = 0;
	NVIC_Timer0_Init(ENABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
	EA = 1;
}


// Unit: um
u16 Cal_Degree_T0(u8 d) {
	return (u16) 100 * (u16) d / 9u + (u16) 500;
}

// 30.000 MHz 16bit auto load. 10 um
void Reset_Timer_T0(u16 um) {
	u16 thtl = (u16) (65536 - (um / 2 * 5)) + 10;
	TL0 += thtl % 256;
	TH0 = thtl / 256;
}

void Servo_T0_Init() {
	xdata int angles[CNT_SERVOS] = {0, 0, 0, 0, 0, 0};
	xdata u8 ens[CNT_SERVOS] = {0, 0, 0, 0, 0, 0};
	Timer_config_T0();
	Servo_T0_Set_Target_Degree(angles, ens);
}

void Servo_T0_Set_Target_Degree(int tds[CNT_SERVOS], u8 ens[CNT_SERVOS]) {
	u8 i;
	for (i = 0; i < CNT_SERVOS; ++i) {
		g_timer_vs_t0[i] = Cal_Degree_T0(tds[i]);
		g_enables_t0[i] = ens[i];
	}
}

void Servo_T0_Timer_Callback() {
	u16 timer_vs = g_timer_vs_t0[g_timer_step_t0];
	u8 enable = g_enables_t0[g_timer_step_t0];
	switch (g_timer_step_t0) {
		case 0:
			SET_CONTROL1(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 1;
			break;
		case 1:
			SET_CONTROL1(0);

			SET_CONTROL2(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 2;
			break;
		case 2:
			SET_CONTROL2(0);
		
			SET_CONTROL3(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 3;
			break;
		case 3:
			SET_CONTROL3(0); 

			SET_CONTROL4(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 4;
			break;
		case 4:
			SET_CONTROL4(0);

			SET_CONTROL5(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 5;
			break;
		case 5:
			SET_CONTROL5(0);
			
			SET_CONTROL6(enable);
			Reset_Timer_T0(timer_vs);
			g_remain_timer_t0 = g_remain_timer_t0 - timer_vs;
			g_timer_step_t0 = 6;
			break;
		case 6:
			SET_CONTROL6(0);
			Reset_Timer_T0(g_remain_timer_t0);
			g_timer_step_t0 = 0;
			g_remain_timer_t0 = PERIODIC_T0;
			break;
	}
}