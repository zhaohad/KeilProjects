#include <reg51.h>

sbit p01 = P0 ^ 1;

unsigned char g_timercnt;
 
void initPWMTimer() {
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xFF;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 1;
	EA = 1;
	g_timercnt = 0;
}

/*
 * 12T 8位自动重载
 * 10us
 */
 
unsigned char DutyRatio = 10;
sbit P_PWM = P0 ^ 0;

void main() {
	P_PWM = 0;
	p01 = 1;
	initPWMTimer();
	while (1) {
		P2 = 0xff;
	}
}

void tm1_isr() interrupt 3 {
	++g_timercnt;
	if (g_timercnt <= 4) {
		P_PWM = 1;
	} else {
		P_PWM = 0;
	}
	
	if (g_timercnt >= 5) {
		g_timercnt = 0;
	}
}
