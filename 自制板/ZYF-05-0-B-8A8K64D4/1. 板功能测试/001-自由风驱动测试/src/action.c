#include "action.h"
#include "action_def.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"

#include "servo_t0.h"
#include "servo_t1.h"

u8 (* g_cur_action)[CNT_ITEM_PER_ACTION] = ACT_FORWORD;
u8 g_cur_action_max_step = CNT_ACTION_FORWARD;
u8 g_cur_step = 0;
u8 g_step_speed = 1;
u8 g_timer_cnt = 0;
xdata u8 t[CNT_SERVOS] = {90, 90, 135, 135, 0, 0};


void Action_Timer_Init() {
	TIM_InitTypeDef TIM_InitStructure;
	// TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer2,&TIM_InitStructure);					//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	T2L = 0xB0;				//���ö�ʱ��ʼֵ
	T2H = 0x3C;				//���ö�ʱ��ʼֵ
	NVIC_Timer2_Init(ENABLE, NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�

	EA = 1;
}

// 30.000 MHZ 20msһ����
void Action_Timer_Callback() {
	u8 step_done = 0;
	u8 stride = g_cur_action[g_cur_step][ACTION_STRIDE_INDEX];
	++g_timer_cnt;
	if (g_cur_step < g_cur_action_max_step) {
		g_step_speed = g_cur_action[g_cur_step][ACTION_SPEED_INDEX];
		if (g_timer_cnt >= g_step_speed) {
			g_timer_cnt = 0;
			step_done = Servo_T0_Step_One(g_cur_action[g_cur_step], stride);
			step_done &= Servo_T1_Step_One((u8 *) g_cur_action[g_cur_step] + CNT_SERVOS, stride);
		}
		if (step_done) {
			++g_cur_step;
		}
	}
}