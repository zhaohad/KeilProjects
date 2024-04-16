#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "74HC165.h"
#include "STC8A_UART.h"
#include "STC8A_Switch.h"
#include "CH9239.h"
#include "key_board.h"

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P0, &conf);
}

void OLED_12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void LED_GPIO_Init() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P0, &conf);
}

void C595_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P3, &conf);
	
	
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
	
	
	conf.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);
}

void C165_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P1, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P1, &conf);
	
	
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void	UART_config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	// UART1_SW(UART1_SW_P30_P31);
	UART1_SW(UART1_SW_P36_P37);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

void UART_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);
}

void on_UART_Rec_1Byte(u8 d) {
	bit a = ch9239_uart_stream(d);
	if (a/*ch9239_uart_stream(d)*/) {		
		key_board_resolve_ch9239(g_9329_rec, g_9329_rec_len);
			//OLED_Clear();

		{
			
			{
				u8 s[6] = {0,0,0,0,0,0};
				s[0] = g_KeyBoardStatus.version;
				s[1] = g_KeyBoardStatus.isConnected;
				s[2] = g_9329_rec_len;
				s[3] = g_9329_cmd_len;
				s[4] = g_state_9329_rec;
				s[5] = a;
				OLED_ShowHexBuf8(0, 0, s, 6);
			}

			{
				u8 * b = g_9329_rec;
				u8 l = g_9329_rec_len;
				u8 sl = 1;
				while (l > 8) {
					OLED_ShowHexBuf8(0, sl, b, 8);
					b += 8;
					l -= 8;
					sl += 1;
				}
				OLED_ShowHexBuf8(0, sl, b, l);
			}
		}

		{
			u8 * b = cmd_key_general_data;
			u8 l = 14;
			u8 sl = 3;
			while (l > 8) {
				OLED_ShowHexBuf8(0, sl, b, 8);
				b += 8;
				l -= 8;
				sl += 1;
			}
			OLED_ShowHexBuf8(0, sl, b, l);
			
			{
				u8 s[5] = {0,0,0,0,0};
				s[0] = g_KeyBoardStatus.version;
				s[1] = g_KeyBoardStatus.isConnected;
				s[2] = g_KeyBoardStatus.isNumLockOn;
				s[3] = g_KeyBoardStatus.isCapsLockOn;
				s[4] = g_KeyBoardStatus.isScrollLockOn;
				OLED_ShowHexBuf8(0, 0, s, 5);
			}
		}
	}
}

void send_keys(u8 * keys, u8 l) {
	xdata u8 lasti, lastl;
	xdata u8 i = 0;
	{
		u8 s[] = {1, 1};
		s[0] = i;
		s[1] = l;
		OLED_ShowHexBuf8(0, 7, s, 2);
	}
	for (i = 4; i < l; ++i) {
		xdata u8 k[1];
		xdata u8 n[1] = {0};
		k[0] = keys[i];
		key_board_key_down(0, k, 1);
		delay_ms(200);
		/*n[0] = 0;
		key_board_key_down(0, n, 1);
		delay_ms(200);*/
		if (i > 13) {
			xdata u8 s[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			s[0] = i;
			s[1] = l;
			OLED_ShowHexBuf8(0, 6, s, 8);
			P00 = 0;
			while (1) {
			}

		} else if (l != 13) {
			xdata u8 s[] = {1, 2, 1, 1, 1};
			s[0] = i;
			s[1] = l;
			s[2] = 13;
			s[3] = lasti;
			s[4] = lastl;
			OLED_ShowHexBuf8(0, 6, s, 5);
			P00 = 0;
			while (1) {
			}
		} else {
			lasti = i;
			lastl = l;
		}
	}
}


void main() {
	xdata last_sent = 1;
	xdata last_not_sent = 0;

	LED_GPIO_Init();
	C595_GPIO_Config();
	C165_GPIO_Config();	
	
	OLED_12864_Init();

	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	UART_GPIO_Config();
	UART_config();
	key_board_get_sys_info();

	key_board_led_off();
	

	while(1) {
		u8 buf[] = {0xfe, 0x12, 0};
		bit key_down = 0;
		load_data_165();
		buf[0] = read_byte_165();
		buf[1] = read_byte_165();
		
		buf[2] = ~(buf[1]) & 0x0f;
		if (buf[2]) {
			u8 s[] = {1};
			s[0] = 1;
			OLED_ShowHexBuf8(0, 5, s, 1);
			if (last_sent) {
				u8 k1[] = {0x04, 0x12, 0x0D, 0x0C, 0x04, 0x12, 0x0B, 0x04, 0x11, 0x1A, 0x08, 0x0C, 0x28};
				send_keys(k1, 13);
				// P00 = 0;
			}
			last_not_sent = 1;
			last_sent = 0;
		} else {
			u8 s[] = {0};
			s[0] = 2;
			OLED_ShowHexBuf8(0, 5, s, 1);
			last_sent = 1;
			// P00 = 1;
			if (last_not_sent) {
				u8 k[] = {0x00};
				key_board_key_down(0, k, 1);
				last_not_sent = 0;
			}
		}

		// OLED_ShowHexBuf8(0, 4, buf, 3);
	}
}