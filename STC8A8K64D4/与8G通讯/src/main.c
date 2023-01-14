#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include	"STC8A_UART.h"
#include "stc8a_switch.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P4, &conf);
}

void UART_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);
}


void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

u8 cnt = 0;
u8 se;

void on_UART_Rec_1Byte(u8 d) {
	u8 buf[2];
	cnt++;
	buf[0] = d;
	buf[1] = cnt;
	// buf[1] = se;
	OLED_ShowHexBuf8(0, 0, buf, 2);
}

void	UART_config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	UART_GPIO_Config();
	UART1_SW(P_UART);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 115200ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;
	UART_Configuration(UART1, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE, Priority_0); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

void delay1s() {
	u8 i;
	for (i = 0; i < 100; ++i) {
		delay_ms(100);
	}
}

void main() {
	OLED12864_Init();
	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	UART_config();
	se = 0;
	on_UART_Rec_1Byte(0x3d);
	EA = 1;
	while(1) {
		/*delay1s();
		++se;
		TX1_write2buff(se);*/
	}
}