#include <reg51.h>

sbit P00 = P0 ^ 0;
sbit P01 = P0 ^ 1;
sbit P02 = P0 ^ 2;
sbit P03 = P0 ^ 3;

sfr AUXR = 0x8E;

int busyT;
int hasR;

/*void initUART() {
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xFD;
	TR1 = 1;
	EA = 1;
	ES = 1;
}*/

// 9600bps@11.0592MHz
void initUART(void) {
	PCON &= 0x7F; //�����ʲ�����
	SCON = 0x50; //8λ����,�ɱ䲨����
	AUXR &= 0xBF; //��ʱ��ʱ��12Tģʽ
	AUXR &= 0xFE; //����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F; //���ö�ʱ��ģʽ
	TMOD |= 0x20; //���ö�ʱ��ģʽ
	TL1 = 0xFD; //���ö�ʱ��ʼֵ
	TH1 = 0xFD; //���ö�ʱ����ֵ
	ET1 = 0; //��ֹ��ʱ��%d�ж�
	TR1 = 1; //��ʱ��1��ʼ��ʱ
	EA = 1;
	ES = 1;
}


void sendByte(char c) {
	while(busyT);
	SBUF = c;
	busyT = 1;
}

void sendStr(char * s) {
	while(*s) {
		sendByte(*s++);
	}
}

void s_interruption() interrupt 4 {
	
	if (RI) {
		RI = 0;
		P03 = 0;
		hasR = 1;
		P2 = SBUF;
		SBUF = P2;
		busyT = 1;
	}
	if (TI) {
		TI = 0;
		busyT = 0;
		P00 = 0;
	}
}

void send0f() {
	SBUF = 0x0f;
	P2 = SBUF;
	busyT = 1;
	while(busyT);
}

void main() {
	P00 = 1;
	P01 = 1;
	P02 = 1;
	P03 = 1;
	initUART();
	send0f();
	while(1) {
		while(!hasR);
		hasR = 0;
		sendStr("Some thing\r\n");
	}
}