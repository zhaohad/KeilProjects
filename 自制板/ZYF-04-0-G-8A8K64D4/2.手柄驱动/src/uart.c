#include "uart.h"

bit busyT;
xdata u8 g_buf1[20];
xdata u8 g_buf2[20];
xdata u8 * g_buf;

UART_onRec g_UART_callback = 0;

// 4800bps@24.000MHz 8λ�Զ���װ
void UART_Init(UART_onRec cb) {
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xF3;		//���ö�ʱ��ʼֵ
	TH1 = 0xF3;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��%d�ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	
	EA = 1;
	ES = 1;
	g_UART_callback = cb;
}

void UART_sendByte(char c) {
	while(busyT);
	SBUF = c;
	busyT = 1;
}

void UART_sendStr(char * s) {
	while(*s) {
		UART_sendByte(*s++);
	}
}

void s_interruption() interrupt 4 {
	if (RI) {
		RI = 0;
		P2 = SBUF;
		SBUF = P2;
		busyT = 1;
		
		g_buf1[0] = P2;
		if (g_UART_callback) {
			g_UART_callback(g_buf1, 1);
		}
	}
	if (TI) {
		TI = 0;
		busyT = 0;
	}
}