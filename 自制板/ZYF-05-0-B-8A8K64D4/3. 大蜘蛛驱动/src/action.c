#include "action.h"
#include "action_def.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"

#include "servo_t0.h"
#include "servo_t1.h"

u8 (* g_cur_action)[CNT_ITEM_PER_ACTION] = ACT_FORWORD;
u8 g_cur_action_max_step = 0;
u8 g_cur_step = 0;
u8 g_step_speed = 1;
u8 g_timer_cnt = 0;
xdata u8 g_action_cmd = 0;
xdata u8 g_action_cmd_v = 0;
xdata u8 g_action_cmd_next = 0;
xdata u8 g_action_cmd_v_next = 0;


void Action_Timer_Init() {
	TIM_InitTypeDef TIM_InitStructure;
	// TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Run       = ENABLE;					//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer2,&TIM_InitStructure);					//初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	T2L = 0xB0;				//设置定时初始值
	T2H = 0x3C;				//设置定时初始值
	NVIC_Timer2_Init(ENABLE, NULL);		//中断使能, ENABLE/DISABLE; 无优先级

	EA = 1;
}

// 30.000 MHZ 20ms一周期
void Action_Timer_Callback() {
	xdata u8 step_done = 0;
	xdata u8 stride = 0;

	switch (g_action_cmd) {
		case ACTION_FORWARD: {
			g_cur_action = ACT_FORWORD;
			g_cur_action_max_step = CNT_ACTION_FORWARD;
			stride = g_action_cmd_v;
			break;
		}
		case ACTION_BACKWARD: {
			g_cur_action = ACT_BACKWORD;
			g_cur_action_max_step = CNT_ACTION_BACKWARD;
			stride = g_action_cmd_v;
			break;
		}
		case ACTION_TO_INIT: {
			g_cur_action = ACT_TO_INIT;
			g_cur_action_max_step = CNT_ACTION_TO_INIT;
			break;
		}
		case ACTION_TURN_LEFT: {
			g_cur_action = ACT_TURN_LEFT;
			g_cur_action_max_step = CNT_ACTION_TURN_LEFT;
			break;
		}
		case ACTION_TURN_RIGHT: {
			g_cur_action = ACT_TURN_RIGHT;
			g_cur_action_max_step = CNT_ACTION_TURN_RIGHT;
			break;
		}
		case ACTION_DANCE: {
			g_cur_action = ACT_DANCE;
			g_cur_action_max_step = CNT_ACTION_DANCE;
			break;
		}
		case ACTION_ROCK: {
			g_cur_action = ACT_ROCK;
			g_cur_action_max_step = CNT_ACTION_ROCK;
			break;
		}
		case ACTION_WANGTIAN: {
			g_cur_action = ACT_WANGTIAN;
			g_cur_action_max_step = CNT_ACTION_WANGTIAN;
			break;
		}
		case ACTION_TO_ASSEMBLE: {
			g_cur_action = ACT_TO_ASSEMBLE;
			g_cur_action_max_step = CNT_ACTION_TO_ASSEMBLE;
			break;
		}
		default: {
			g_cur_action = NULL;
			g_action_cmd = g_action_cmd_next;
			g_action_cmd_v = g_action_cmd_v_next;
			g_cur_action_max_step = 0;
			break;
		}
	}
	
	if (g_cur_action == NULL) {
		return;
	}

	if (stride == 0 || stride > g_cur_action[g_cur_step][ACTION_STRIDE_INDEX]) {
		stride = g_cur_action[g_cur_step][ACTION_STRIDE_INDEX];
	}
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
	} else {
		g_cur_step = 0;
		if (g_action_cmd == ACTION_WANGTIAN && g_action_cmd_next == ACTION_WANGTIAN) {
			g_cur_step = CNT_ACTION_WANGTIAN;
		} else if (g_action_cmd_next != ACTION_NONE) {
			g_action_cmd = g_action_cmd_next;
			g_action_cmd_v = g_action_cmd_v_next;
		} else {
			g_action_cmd = ACTION_TO_INIT;
			g_action_cmd_v = 5;
		}
	}
}