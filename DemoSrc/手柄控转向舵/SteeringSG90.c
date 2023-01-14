#include <reg51.h>
#include "SteeringSG90.h"

#define TIMERCNT_20MS 200
#define TIMERCNT_0D 	5
#define TIMERCNT_180D 25
#define TIMERCNT_ANY(D) D * (TIMERCNT_180D - TIMERCNT_0D) / TIMERCNT_180D + TIMERCNT_0D

#define DEGREE_MIN 0
#define DEGREE_MAX 180

unsigned char g_timercnt;
unsigned char g_cntH = 25;

/*
 * 12T 8位自动重载
 * 100us
 */
void initSteeringPWMTimer() {
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0x9C;		//设置定时初始值
	TH1 = 0x9C;		//设置定时重载值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	ET1 = 1;
	EA = 1;
	g_timercnt = 0;
}

void setSteeringDegree(unsigned char d) {
	if (d > DEGREE_MAX) {
		d = DEGREE_MAX;
	}
	g_cntH = d / 9 + 5;
}

sbit P_PWM = P0 ^ 0;

void SteeringPWMTimerInterruption() {
	++g_timercnt;
	if (g_timercnt <= g_cntH) {
		P_PWM = 1;
	} else {
		P_PWM = 0;
	}
	
	if (g_timercnt >= TIMERCNT_20MS) {
		g_timercnt = 0;
	}
}
