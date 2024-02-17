#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "typedef.h"
#include "servo_t0.h"
#include "servo_t1.h"
#include "delay.h"


#define INIT_ANGLES 90, 90, 135, 135, 0, 0
#define INTER_ANGLE 30

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
	GPIO_Inilize(GPIO_P1, &conf);
	GPIO_Inilize(GPIO_P3, &conf);
}

xdata int angles[CNT_SERVOS] = {INIT_ANGLES};
xdata u8 ens[CNT_SERVOS] = {1, 1, 1, 1, 1, 1};

void initing_delay() {
	u8 i = 0;
	for (i = 0; i < 10; ++i) {
		delay_ms(254);
	}
}

void delay_per_degree() {
	delay_ms(32);
}


void init_position(int a[CNT_SERVOS], u8 e[CNT_SERVOS]) {
	u8 i;
	for (i = 0; i < CNT_SERVOS; ++i) {
		e[i] = 1;
		if (i < 4) {
			a[i] = angles[i] - INTER_ANGLE;
			Servo_T0_Set_Target_Degree(a, e);
			initing_delay();
		}
		
		a[i] = angles[i] + INTER_ANGLE;
		Servo_T0_Set_Target_Degree(a, e);
		initing_delay();
		
		a[i] = angles[i];
		Servo_T0_Set_Target_Degree(a, e);
		initing_delay();
	}
}

void to_initial_pos() {
	xdata int initial_pos[CNT_SERVOS];
	initial_pos[0] = 90;
	initial_pos[1] = 90;
	initial_pos[2] = 135;
	initial_pos[3] = 135;
	initial_pos[4] = 0;
	initial_pos[5] = 0;
	Servo_T0_Set_Target_Degree(initial_pos, ens);
	Servo_T1_Set_Target_Degree(initial_pos, ens);
}

void to_flat_pos() {
	xdata int initial_pos[CNT_SERVOS];
	initial_pos[0] = 0;
	initial_pos[1] = 180;
	initial_pos[2] = 100;
	initial_pos[3] = 100;
	initial_pos[4] = 135;
	initial_pos[5] = 135;
	Servo_T0_Set_Target_Degree(initial_pos, ens);
	initial_pos[0] = 180;
	initial_pos[1] = 0;
	initial_pos[2] = 100;
	initial_pos[3] = 100;
	initial_pos[4] = 135;
	initial_pos[5] = 135;
	Servo_T1_Set_Target_Degree(initial_pos, ens);
}

void to_jump_initial() {
	xdata int initial_pos[CNT_SERVOS];
	initial_pos[0] = 90;
	initial_pos[1] = 90;
	initial_pos[2] = 160;
	initial_pos[3] = 160;
	initial_pos[4] = 0;
	initial_pos[5] = 0;
	Servo_T0_Set_Target_Degree(initial_pos, ens);
	Servo_T1_Set_Target_Degree(initial_pos, ens);
}

void to_jump_space() {
	xdata int initial_pos[CNT_SERVOS];
	initial_pos[0] = 90;
	initial_pos[1] = 90;
	initial_pos[2] = 0;
	initial_pos[3] = 0;
	initial_pos[4] = 130;
	initial_pos[5] = 130;
	Servo_T0_Set_Target_Degree(initial_pos, ens);
	Servo_T1_Set_Target_Degree(initial_pos, ens);
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
	
	GPIO_Config();
	Servo_T0_Init();
	Servo_T1_Init();
	
	while (1) {
		to_initial_pos();
		for (i = 0; i < 20; ++i) {
			delay_ms(254);
		}
		to_jump_space();

		for (i = 0; i < 20; ++i) {
			delay_ms(254);
		}
	}
	
	// init_position(angles_t0, ens_t0);
	// init_position(angles_t1, ens_t1);
	
	/*ens_t0[0] = 1;
	ens_t0[2] = 1;
	ens_t0[4] = 1;

	angles_t0[0] = 89;
	angles_t0[2] = 136;
	angles_t0[4] = 1;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 87;
	angles_t0[2] = 137;
	angles_t0[4] = 2;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 86;
	angles_t0[2] = 138;
	angles_t0[4] = 3;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 85;
	angles_t0[2] = 139;
	angles_t0[4] = 4;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 84;
	angles_t0[2] = 140;
	angles_t0[4] = 5;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 83;
	angles_t0[2] = 141;
	angles_t0[4] = 6;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 82;
	angles_t0[2] = 142;
	angles_t0[4] = 7;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 81;
	angles_t0[2] = 143;
	angles_t0[4] = 8;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 80;
	angles_t0[2] = 144;
	angles_t0[4] = 9;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 79;
	angles_t0[2] = 145;
	angles_t0[4] = 10;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 78;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 77;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 76;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 75;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 74;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 73;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 72;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 71;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 70;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 69;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	
	delay_per_degree();
	angles_t0[0] = 68;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 67;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 66;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 65;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 64;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 63;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 62;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 61;
	Servo_T0_Set_Target_Degree(angles_t0, ens_t0);
	delay_per_degree();
	angles_t0[0] = 60;
	
	initing_delay();
	Servo_T0_Set_Target_Degree(angles, ens_t0);*/
	
	while (1) {
	}
}