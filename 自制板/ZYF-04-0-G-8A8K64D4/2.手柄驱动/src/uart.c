#include "uart.h"

bit busyT;
xdata u8 g_buf1[20];
xdata u8 g_buf2[20];
xdata u8 * g_buf;

UART_onRec g_UART_callback = 0;

// 4800bps@24.000MHz 8位自动重装
void UART_Init(UART_onRec cb) {
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	
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