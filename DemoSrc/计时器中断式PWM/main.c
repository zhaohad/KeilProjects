#include <reg51.h>

sbit p01 = P0 ^ 1;

unsigned char g_timercnt;
 
void initPWMTimer() {
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xFF;		//���ö�ʱ��ʼֵ
	TH1 = 0xFF;		//���ö�ʱ��ʼֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;
	EA = 1;
	g_timercnt = 0;
}

/*
 * 12T 8λ�Զ�����
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
