#include <reg51.h>

sbit p01 = P0 ^ 1;

#define TIMERCNT_20MS 200
#define TIMERCNT_0D 	5
#define TIMERCNT_180D 25
#define TIMERCNT_ANY(D) D * (TIMERCNT_180D - TIMERCNT_0D) / TIMERCNT_180D + TIMERCNT_0D

unsigned char g_timercnt;
unsigned char g_cntH = 25;

/*
 * 12T 8位自动重载
 * 100us
 */
void initPWMTimer() {
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

void setDegree(int d) {
	g_cntH = d / 9 + 5;
}
 
unsigned char DutyRatio = 10;
sbit P_PWM = P0 ^ 0;

void main() {
	int d = 0;
	int f = 1;
	P_PWM = 0;
	p01 = 0;
	initPWMTimer();
	
	setDegree(90);
	while (1) {
		/*int i;
		if (d >= 180) {
			f = -1;
		}
		if (d <= 0) {
			f = 1;
		}
		
		setDegree(d);
		d += f;
		for (i = 512; i > 0; --i);*/
	}
}

void tm1_isr() interrupt 3 {
	++g_timercnt;
	if (g_timercnt <= g_cntH) {
		P_PWM = 1;
	} else {
		P_PWM = 0;
	}
	
	if (g_timercnt >= TIMERCNT_20MS) {
		g_timercnt = 0;
		p01 = ~p01;
	}
}
