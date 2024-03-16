#include "servo_t1.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"

#define PERIODIC_T1 20000
#define DEFAULT_INT_T1 500

u8 g_timer_step_t1 = 0;

u16 g_timer_vs_t1[CNT_SERVOS];
u16 g_timer_vs_target_t1[CNT_SERVOS];
u8 g_degree_t1[CNT_SERVOS];
u16 g_remain_timer_t1 = 0;

// 30.000 MHz 16bit auto load. 10 um
void Timer_config_T1() {
	TIM_InitTypeDef TIM_InitStructure;						//结构定义
	TIM_InitStructure.TIM_Mode = TIM_16Bit;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Run = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1, &TIM_InitStructure);					//初始化Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	TL1 = 0;
	TH1 = 0;
	NVIC_Timer1_Init(ENABLE, Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
	EA = 1;
}


// Unit: um
u16 Cal_Degree_T1(u8 d) {
	return (u16) 100 * (u16) d / 9u + (u16) 500;
}

// 30.000 MHz 16bit auto load. 10 um
void Reset_Timer_T1(u16 um) {
	u16 thtl = (u16) (65536 - (um / 2 * 5)) + 10;
	TL1 += thtl % 256;
	TH1 = thtl / 256;
}

void Servo_T1_Init() {
	xdata u8 angles[CNT_SERVOS] = {0, 0, 0, 0, 0, 0};
	Timer_config_T1();
	Servo_T1_Set_Target_Degree(angles);
}

void Servo_T1_Set_Target_Degree(u8 tds[CNT_SERVOS]) {
	u8 i;
	for (i = 0; i < CNT_SERVOS; ++i) {
		g_degree_t1[i] = tds[i];
		g_timer_vs_target_t1[i] = Cal_Degree_T1(tds[i]);
	}
}

u8 Servo_T1_Step_One(u8 tds[CNT_SERVOS], u8 stride) {
	u8 res = 1;
	u8 i;
	for (i = 0; i < CNT_SERVOS; ++i) {
		if (g_degree_t1[i] < tds[i]) {
			g_degree_t1[i] += stride;
			if (g_degree_t1[i] > tds[i]) {
				g_degree_t1[i] = tds[i];
			}
			g_timer_vs_target_t1[i] = Cal_Degree_T1(g_degree_t1[i]);
			res = 0;
		} else if (g_degree_t1[i] > tds[i]) {
			g_degree_t1[i] -= stride;
			if (g_degree_t1[i] < tds[i] || g_degree_t1[i] > 180) {
				g_degree_t1[i] = tds[i];
			}
			g_timer_vs_target_t1[i] = Cal_Degree_T1(g_degree_t1[i]);
			res = 0;
		}
	}
	return res;
}

void copy_target_t1() {
	u8 i;
	for (i = 0; i < CNT_SERVOS; ++i) {
		g_timer_vs_t1[i] = g_timer_vs_target_t1[i];
	}
}

void Servo_T1_Timer_Callback() {
	u16 timer_vs = g_timer_vs_t1[g_timer_step_t1];
	switch (g_timer_step_t1) {
		case 0:
			SET_CONTROL7(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 1;
			break;
		case 1:
			SET_CONTROL7(0);

			SET_CONTROL8(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 2;
			break;
		case 2:
			SET_CONTROL8(0);
		
			SET_CONTROL9(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 3;
			break;
		case 3:
			SET_CONTROL9(0); 

			SET_CONTROL10(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 4;
			break;
		case 4:
			SET_CONTROL10(0);

			SET_CONTROL11(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 5;
			break;
		case 5:
			SET_CONTROL11(0);
			
			SET_CONTROL12(1);
			Reset_Timer_T1(timer_vs);
			g_remain_timer_t1 = g_remain_timer_t1 - timer_vs;
			g_timer_step_t1 = 6;
			break;
		case 6:
			copy_target_t1();
			SET_CONTROL12(0);
			Reset_Timer_T1(g_remain_timer_t1);
			g_timer_step_t1 = 0;
			g_remain_timer_t1 = PERIODIC_T1;
			break;
			
	}
}