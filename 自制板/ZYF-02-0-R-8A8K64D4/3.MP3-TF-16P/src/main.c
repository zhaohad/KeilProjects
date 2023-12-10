#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "STC8A_UART.h"


xdata u8 g_received_buf[MAX_CHAR8_COL];

void OLED_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void UART_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0, &conf);
}


void UART_config() {
	xdata COMx_InitDefine COMx_InitStructure; //结构定义
	//UART3_SW(P_UART);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE

	UART_Configuration(UART3, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART3_Init(ENABLE, Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

xdata u8 recCnt = 0;
xdata u8 rec[10];
xdata u8 rec1[10];
xdata u8 str[10];
xdata u8 num[10];
void on_UART_Rec_1Byte(u8 d) {
	COM3.B_RX_OK = 0;
	COM3.RX_TimeOut = TimeOutSet1;
	RX3_Buffer[COM3.RX_Cnt++] = d;
	if(COM3.RX_Cnt >= COM_RX3_Lenth) {
		COM3.RX_Cnt = 0;
	}
	COM3.B_RX_OK = 1;
	
	if (recCnt < 8) {
		rec[recCnt] = d;
		OLED_ShowHexBuf8(0, 2, rec, recCnt + 1);
	} else {
		rec1[recCnt - 8] = d;
		OLED_ShowHexBuf8(0, 3, rec1, recCnt - 8 + 1);
	}
	++recCnt;
	
	uintToS(recCnt, num, 10);
	sprintf(str, "%s", num);
	OLED_ShowString(0, 6, str);
}

xdata u8 sentCnt = 0;
void on_UART_Send_1Byte(u8 d) {
	xdata u8 a[10];
	xdata u8 b[10];
	sentCnt++;
	uintToS(sentCnt, b, 10);
	sprintf(a, "Sent %s", b);
	OLED_ShowString(0, 4, a);
}

void UART_Init() {
	COM3.TX_read = 0;
	COM3.RX_Cnt = 0;
	COM3.B_RX_OK = 0;
	COM3.RX_TimeOut = TimeOutSet1;

	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	g_onSend_1Byte_CB = on_UART_Send_1Byte;
	UART_config();
}

void boot_delay() {
	xdata u8 t, i;
	for (i = 0; i < 1; ++i) {
		for (t = 0; t < 250; ++t) {
			delay_ms(10);
		}
	}
}

void copy_buf(u8 * dst, u8 l) {
	xdata u8 i;
	--l;
	for (i = 0; i < l; ++i) {
		if (i < COM3.RX_Cnt) {
			dst[i] = RX3_Buffer[i];
		} else {
			dst[i] = ' ';
		}
	}
	dst[l] = 0;
	COM3.RX_Cnt = 0;
	COM3.B_RX_OK = 0;
}

unsigned int check_sum(u8 * d, u8 cnt) {
	u8 i;
	unsigned int sum = 0;
	for (i = 0; i < cnt; ++i) {
		sum += d[i];
	}
	return -sum;
}

void main() {
	u8 i;
	xdata u8 cmd[] = {0x7e, 0xff, 0x06, 0x09, 0x00, 0x00, 0x02, 0xfe, 0xf0, 0xef};
	xdata u8 d[] = {0xff, 0x06, 0x03, 0x00, 0x00, 0x01};
	xdata char str[] = {0, 0, 0};
	unsigned int checksum = check_sum(d, 6);
	str[0] = (u8) (checksum >> 8);
	str[1] = (u8) checksum;
	OLED12864_Init();
	OLED_ShowString(0, 0, "Init...");
	
	OLED_ShowHexBuf8(0, 2, str, 2);
	
	UART_Init();
	EA = 1;
	
	boot_delay();
	OLED_ShowString(0, 0, "Init Done");
	
	for (i = 0; i < 10; ++i) {
		TX3_write2buff(cmd[i]);
	}

	while(1) {
	}
}