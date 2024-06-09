#include "stc8a8k64d4.H"
#include "stc8a_gpio.h"
#include "STC8A_UART.h"
#include "STC8A_Switch.h"
#include "STC8A_NVIC.h"
#include "CH9239.h"
#include "delay.h"
#include "key_board.h"

#include "typedef.h"
#include "74HC595.h"
#include "74HC165.h"

u8 a0 = 0;
u8 a1[30];

void UART_Debuging_Config() {
	COMx_InitDefine COMx_InitStructure; //�ṹ����
	UART1_SW(UART1_SW_P30_P31);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure); //��ʼ������2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1); //�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

void	UART_9239_config() {
	COMx_InitDefine COMx_InitStructure; //�ṹ����
	UART2_SW(UART2_SW_P10_P11);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2; //ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //��������,   ENABLE��DISABLE
	UART_Configuration(UART2, &COMx_InitStructure); //��ʼ������2 USART1,USART2,USART3,USART4
	NVIC_UART2_Init(ENABLE,Priority_1); //�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

void CH9239_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P5, &conf);
	
	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P1, &conf);
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P1, &conf);
}

void C595_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);

	conf.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P3, &conf);
	
	conf.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);
}

void C165_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;

	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P4, &conf);	
	
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P2, &conf);
	
	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	xdata u8 led, ledg, ledb, ledr;
	xdata u8 keys;
	xdata u8 i;
	xdata u8 key_arr[1];

	C595_GPIO_Config();
	C165_GPIO_Config();
	CH9239_GPIO_Config();

	UART_Debuging_Config();
	UART_9239_config();
	
	ledg = 0x7f;
	ledr = 0xbf;
	ledb = 0xdf;
	led = ledr & ledb & ledg;

	stop_595();
	clear_595();
	keep_595();
	
	write_byte_595(led);
	flush_595();
	
	// TX1_write2buff(0x1);
	// key_board_get_sys_info();
	// TX2_write2buffs(cmd_key_general_data, 14);.
	// TX1_write2buff(0x2);
	
	for (i = 0; i < 10; ++i) {
		delay_ms(254);
	}
	TX1_write2buff(0x1);
	TX1_write2buffs(g_9329_rec, g_9329_rec_len);
	TX1_write2buff(0x2);

	g_9329_rec_len = 0;
	key_arr[0] = 0x04;
	
	TX1_write2buff(0x3);
	// TX2_write2buffs(cmd_key_general_data, 14);
	key_board_key_down(0, key_arr, 1);
	TX1_write2buffs(cmd_key_general_data, 14);
	for (i = 0; i < 10; ++i) {
		delay_ms(254);
	}
	TX1_write2buff(g_9329_rec_len);
	TX1_write2buffs(g_9329_rec, g_9329_rec_len);
	TX1_write2buff(0x04);
	
	key_board_all_key_up();

	while(1) {
		// load_data_165();
		// keys = read_byte_165();
		// TX1_write2buff(keys);
	}
}