#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "typedef.h"
#include "servo_t0.h"
#include "servo_t1.h"
#include "delay.h"
#include "action_def.h"
#include "action.h"

#define CNT_SERVOS 6
#define DMS_MIN 10
#define DMS_NORM 32
#define INIT_ANGLES 90, 90, 135, 135, 0, 0
#define INTER_ANGLE 30

void SERVO_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);

	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P0, &conf);

	conf.Pin = GPIO_Pin_7 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P3, &conf);
	
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);
}
xdata u8 ens[CNT_SERVOS] = {1, 1, 1, 1, 1, 1};

void initing_delay() {
	u8 i = 0;
	for (i = 0; i < 5; ++i) {
		delay_ms(254);
	}
}

void delay_per_degree(u8 dms) {
	u8 i;
	for (i = 0; i < 1; ++i) {
		// delay_ms(32);
		delay_ms(dms);
	}
}

void to_initial_pos() {
	xdata u8 initial_pos[CNT_SERVOS];
	initial_pos[0] = 90;
	initial_pos[1] = 90;
	initial_pos[2] = 135;
	initial_pos[3] = 135;
	initial_pos[4] = 0;
	initial_pos[5] = 0;
	Servo_T0_Set_Target_Degree(initial_pos);
	Servo_T1_Set_Target_Degree(initial_pos);
}

double pow(double a, u8 b) {
	u8 i;
	double r = 1;
	for (i = 0; i < b; ++i) {
		r *= a;
	}
	return r;
}

// Ê¹ÓÃ 30.000 MHzÉÕÂ¼
void main() {
	u8 i;
	xdata int angles_t0[CNT_SERVOS], angles_t1[CNT_SERVOS];
	xdata u8 ens_t0[CNT_SERVOS], ens_t1[CNT_SERVOS];

	for (i = 0; i < CNT_SERVOS; ++i) {
		angles_t0[i] = 0;
		ens_t0[i] = 0;

		angles_t1[i] = 0;
		ens_t1[i] = 0;
	}
	
	SERVO_GPIO_Config();
	Servo_T0_Init();
	Servo_T1_Init();
	to_initial_pos();
	initing_delay();
	Action_Timer_Init();
	
	while (1) {
	}
}