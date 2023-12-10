#include "CarCtrl.h"
#include "delay.h"
#include "timer.h"

#define MAX_MOTOR_STEP 2965
#define ROLL_BACK_STEP 900
#define TURN_RIGHT_STEP 900
#define TURN_LEFT_STEP 900
#define MOTOR_CYCLE_STEP 8
#define STATUS_TURN_NONE 0
#define STATUS_TURN_BACK 1
#define STATUS_TURN_RIGHT 2
#define STATUS_TURN_LEFT 3

#define SPEED_MAX 10
#define SPEED_MIN 4

#define GO_STOP 0
#define GO_FORWARD 1
#define GO_BACKWARD 2

xdata u8 gcarctrl_status_turn = STATUS_TURN_NONE;
xdata u8 gcarctrl_speed = 5;
xdata u8 gcarctrl_pwm_counter = 0;
xdata u8 gcarctrl_goward = GO_STOP;

void Timer2Callback() {
	gcarctrl_pwm_counter = (gcarctrl_pwm_counter + 1) % SPEED_MAX;
	if (gcarctrl_pwm_counter < gcarctrl_speed) {
		if (gcarctrl_goward == GO_FORWARD) {
			M1 = 1;
			M2 = 0;
		} else if (gcarctrl_goward == GO_BACKWARD) {
			M1 = 0;
			M2 = 1;
		}
	} else {
		M1 = 0;
		M2 = 0;
	}
}

void Timer_Config() {
	TIM_InitTypeDef TIM_InitStructure; //结构定义
	TIM_InitStructure.TIM_Interrupt = ENABLE; //中断是否允许, ENABLE或DISABLE. (注意: Timer2固定为16位自动重装, 中断固定为低优先级)
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T; //指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut = DISABLE; //是否输出高速脉冲, ENABLE或DISABLE
	// TIM_InitStructure.TIM_Value = 65536UL - (MAIN_Fosc / 1000); //初值
	TIM_InitStructure.TIM_Value = 65536UL - 1000; //初值
	TIM_InitStructure.TIM_Run = ENABLE; //是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer2, &TIM_InitStructure); //初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	
	SET_INTERRUPT_CALLBACK(Timer2Callback);
}

void CarControl_Init() {
	Timer_Config();
}

void Motor_Step(unsigned int step, bit forward) {
	u8 i = 0;
	u8 n;
	while(1) {
		for (n = 0; n < 200; ++n) {
			_nop_();_nop_();_nop_();_nop_();_nop_();
		}
		if (step == 0) {
			break;
		}
		--step;
		if ((i % MOTOR_CYCLE_STEP) == 0) {
			M_A1 = 1;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 0;
		} else if ((i % MOTOR_CYCLE_STEP) == 1) {
			M_A1 = 1;
			M_B1 = 1;
			M_A2 = 0;
			M_B2 = 0;
		} else if ((i % MOTOR_CYCLE_STEP) == 2) {
			M_A1 = 0;
			M_B1 = 1;
			M_A2 = 0;
			M_B2 = 0;
		} else if ((i % MOTOR_CYCLE_STEP) == 3) {
			M_A1 = 0;
			M_B1 = 1;
			M_A2 = 1;
			M_B2 = 0;
		} else if ((i % MOTOR_CYCLE_STEP) == 4) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 1;
			M_B2 = 0;
		} else if ((i % MOTOR_CYCLE_STEP) == 5) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 1;
			M_B2 = 1;
		} else if ((i % MOTOR_CYCLE_STEP) == 6) {
			M_A1 = 0;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 1;
		} else if ((i % MOTOR_CYCLE_STEP) == 7) {
			M_A1 = 1;
			M_B1 = 0;
			M_A2 = 0;
			M_B2 = 1;
		}
		if (forward) {
			--i;
			if (i < 0 || i > MOTOR_CYCLE_STEP) {
				i = MOTOR_CYCLE_STEP - 1;
			}
		} else {
			++i;
			if (i >= MOTOR_CYCLE_STEP) {
				i = 0;
			}
		}
	}
	M_A1 = 0;
	M_A2 = 0;
	M_B1 = 0;
	M_B2 = 0;
}

void TurnBack() {
	if (gcarctrl_status_turn == STATUS_TURN_LEFT) {
		Motor_Step(TURN_LEFT_STEP, 1);
	} else if (gcarctrl_status_turn == STATUS_TURN_RIGHT) {
		Motor_Step(TURN_RIGHT_STEP, 0);
	} else {
		Motor_Step(ROLL_BACK_STEP * 2, 1);
		Motor_Step(ROLL_BACK_STEP, 0);
	}

	M_A1 = 0;
	M_B1 = 0;
	M_A2 = 0;
	M_B2 = 0;
	gcarctrl_status_turn = STATUS_TURN_BACK;
}

void TurnRight() {	
	if (gcarctrl_status_turn == STATUS_TURN_BACK) {
		Motor_Step(TURN_RIGHT_STEP, 1);
	} else if (gcarctrl_status_turn == STATUS_TURN_LEFT) {
		TurnBack();
		Motor_Step(TURN_RIGHT_STEP, 1);
	}

	M_A1 = 0;
	M_B1 = 0;
	M_A2 = 0;
	M_B2 = 0;
	gcarctrl_status_turn = STATUS_TURN_RIGHT;
}

void TurnLeft() {
	if (gcarctrl_status_turn == STATUS_TURN_BACK) {
		Motor_Step(TURN_LEFT_STEP, 0);
	} else if (gcarctrl_status_turn == STATUS_TURN_RIGHT) {
		TurnBack();
		Motor_Step(TURN_LEFT_STEP, 0);
	}

	M_A1 = 0;
	M_B1 = 0;
	M_A2 = 0;
	M_B2 = 0;
	gcarctrl_status_turn = STATUS_TURN_LEFT;
}

void Motor_Go(bit forward) {
	gcarctrl_goward = forward ? GO_FORWARD : GO_BACKWARD;
	M1 = forward;
	M2 = !M1;
}

void Motor_Stop() {
	gcarctrl_goward = GO_STOP;
	M1 = 0;
	M2 = 0;
}

void SetSpeed(u8 speed) {
	if (speed < SPEED_MIN) {
		gcarctrl_speed = SPEED_MIN;
	} else if (speed > SPEED_MAX) {
		gcarctrl_speed = SPEED_MAX;
	} else {
		gcarctrl_speed = speed;
	}
}