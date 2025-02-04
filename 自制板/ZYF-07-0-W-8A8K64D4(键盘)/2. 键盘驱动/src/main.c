#include "stc8a8k64d4.H"
#include "stc8a_gpio.h"
#include "STC8A_UART.h"
#include "STC8A_Switch.h"
#include "STC8A_NVIC.h"
#include "CH9239.h"
#include "delay.h"

#include "typedef.h"
#include "74HC595.h"
#include "74HC165.h"

void UART_Debuging_Config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	UART1_SW(UART1_SW_P30_P31);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

void	UART_9239_config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	UART2_SW(UART2_SW_P10_P11);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	UART_Configuration(UART2, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART2_Init(ENABLE,Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
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

bit is_changed(u8 * new_k, u8 new_k_l, u8 * last_k, u8 last_k_l) {
	xdata u8 i;
	if (new_k_l != last_k_l) {
		return 1;
	}
	for (i = 0; i < new_k_l; ++i) {
		if (new_k[i] != last_k[i]) {
			return 1;
		}
	}
	return 0;
}

void copy_keys(u8 * new_k, u8 * last_k, u8 l) {
	xdata u8 i;
	for (i = 0; i < l; ++i) {
		last_k[i] = new_k[i];
	}
}

void show_sys_led() {
	if (g_KeyBoardStatus.isCapsLockOn) {
		write_byte_595(0xfe);
		flush_595();
	} else {
		write_byte_595(0xff);
		flush_595();
	}
}

xdata u8 g_ack_done;
void on_ch9329_dat_rec(u8 dat) {
	if (ch9239_uart_stream(dat)) {
		g_ack_done = 1;
		show_sys_led();
	} else {
		g_ack_done = 0;
	}
}

void delay() {
	u8 i;
	for (i = 0; i < 1; ++i) {
		delay_ms(254);
	}
}

void main() {
	xdata u8 led, ledg, ledb, ledr;
	xdata u8 keys_l, keys[CNT_MAX_READ_NORM_KEY], last_keys_l, last_keys[CNT_MAX_READ_NORM_KEY];
	xdata u8 t;

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
	
	// TX1_write2buff(0x1);
	// key_board_get_sys_info();
	// TX2_write2buffs(cmd_key_general_data, 14);.
	// TX1_write2buff(0x2);

	/*g_9329_rec_len = 0;
	key_arr[0] = 0x04;*/
	
	// TX1_write2buff(0x3);
	// TX2_write2buffs(cmd_key_general_data, 14);
	// ch9329_key_down(0, key_arr, 1);
	/*for (i = 0; i < 10; ++i) {
		delay_ms(254);
	}
	TX1_write2buff(g_9329_rec_len);
	TX1_write2buffs(g_9329_rec, g_9329_rec_len);
	TX1_write2buff(0x04);
	
	ch9329_all_key_up();*/
	ch9239_get_sys_info();
	TX1_write2buff(ch9239_ready());
	delay_ms(254);
	delay_ms(254);
	delay_ms(254);

	t = 0;
	while(1) {
		keys_l = read_keys(keys);
		if (ch9239_ready() && is_changed(keys, keys_l, last_keys, last_keys_l)) {
			ch9239_key_down(0, keys, keys_l);
			last_keys_l = keys_l;
			copy_keys(keys, last_keys, keys_l);
		}
		
		/*load_data_165();
		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);

		t = read_byte_165();
		TX1_write2buff(t);
		
		delay();*/
	}
}