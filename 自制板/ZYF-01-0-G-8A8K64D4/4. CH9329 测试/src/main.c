#include "stc8a8k64d4.H"
#include "stc8a_gpio.H"
#include "stc8a_spi.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "stc8a_adc.h"
#include "stc8a_switch.h"
#include "dtos.h"
#include "G01_S.h"
#include	"STC8A_UART.h"
#include "delay.h"

bit g_Rec = 1;
xdata u8 outL = 0;

void OLED_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P4, &conf);
}

void OLED12864_Init() {
	OLED_GPIO_Config();
	OLED_Init();
}

void MOTOR_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2, &conf);
}

void UART_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);
}

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P0, &conf);
}

void	UART_config() {
	COMx_InitDefine COMx_InitStructure; //结构定义
	UART1_SW(UART3_SW_P00_P01);
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx; //模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer3; //使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 9600ul; //波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE; //接收允许,   ENABLE或DISABLE
	UART_Configuration(UART3, &COMx_InitStructure); //初始化串口2 USART1,USART2,USART3,USART4
	NVIC_UART3_Init(ENABLE,Priority_1); //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	EA = 1;
}

xdata u8 cnt = 0;
xdata u8 buf[20];
void on_UART_Rec_1Byte(u8 d) {
	buf[cnt++] = d;
	buf[cnt] = cnt;
	if (cnt > 8) {
		OLED_ShowHexBuf8(0, 2, buf, 8);
		OLED_ShowHexBuf8(0, 3, buf + 8, cnt - 7);
	} else {
		OLED_ShowHexBuf8(0, 2, buf, cnt + 1);
	}
}

void main() {
	/*int someNumber = 0;
	bit exist;*/
	xdata u8 cmd_get_info[6] = {0x57, 0xAB, 0x00, 0x01, 0x00, 0x03};
	xdata u8 send_empty[14] = {0x57, 0xAB, 0x00, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C};
	xdata u8 send_aaaaa[14] = {0x57, 0xAB, 0x00, 0x02, 0x08, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10};
	xdata u8 i = 0;
	GPIO_Config();
	UART_GPIO_Config();
	g_onURAT_1Byte_CB = on_UART_Rec_1Byte;
	UART_config();
	
	OLED12864_Init();
	OLED_ShowString8(0, 0, "Loading ...");
	for (i = 0; i < 3; ++i) {
		delay_ms(254);
	}
	OLED_ShowString8(0, 0, "Loaded     ");
	TX3_write2buffs(cmd_get_info, 6);
	OLED_ShowString8(0, 0, "Sent       ");
	P02 = 0;
	
	while(1) {
		/*P02 = P03;
		if (!P03) {
			TX3_write2buffs(send_aaaaa, 14);
		} else {
			TX3_write2buffs(send_empty, 14);
		}*/
	}

	/*NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();

	OLED_ShowString8(0, 0, "CHECK MODULE...");
	
	exist = NRF24L01_check();
	if (exist) {
		OLED_ShowString8(0, outL, "G01-S Online");
	} else {
		OLED_ShowString8(0, outL, "G01-S Offline");
		while (1);
	}
	outL++;
	
	RF24L01_Init();
	_nop_();_nop_();_nop_();_nop_();_nop_();

	if (g_Rec) {
		OLED_ShowString8(0, outL, "Set MODE_RX");
		RF24L01_Set_Mode(MODE_RX); //接收模式
		_nop_();_nop_();_nop_();_nop_();_nop_();
	} else {
		OLED_ShowString8(0, outL, "Set MODE_TX");
		RF24L01_Set_Mode(MODE_TX); //发送模式
		_nop_();_nop_();_nop_();_nop_();_nop_();
	}
	outL++;

	while(1) {
		u8 outLL = outL;
		xdata uint8_t res;
		xdata uint8_t tx[1];
		xdata uint8_t numStr[10];
		xdata uint8_t str[20];

		if (g_Rec) {
			xdata uint8_t rx;
			xdata uint8_t g_rece[8];
			u8 i;
			sprintf(str, "Receiving...");
			OLED_ShowString8(0, outLL, str);
			outLL++;
			rx = NRF24L01_RxPacket(g_rece); //接收字节

			if (rx != 0) {
				uintToS(rx, numStr, 10);
				sprintf(str, "Received: %s   ", numStr);
				OLED_ShowString8(0, outLL, str);
				outLL++;
				
				sprintf(str, "d: ");
				for (i = 0; i < rx; ++i) {
					u8 d = g_rece[i];
					uintToS(d, numStr, 10);
					sprintf(str, "%s %s", str, numStr);
				}
				sprintf(str, "%s    ", str);
				OLED_ShowString8(0, outLL, str);
				outLL++;
			}
		} else {
			tx[0] = someNumber;
			intToS(tx[0], numStr, 10);
			sprintf(str, "Sending %s   ", numStr);
			OLED_ShowString8(0, outLL, str);
			outLL++;
			res = NRF24L01_TxPacket((uint8_t *) tx, 1);
			if (res == TX_OK) {
				sprintf(str, "SUCCEES");
			} else {
				sprintf(str, "Failed");
			}
			OLED_ShowString8(0, outLL, str);
			outLL++;

			someNumber++;
			if (someNumber > 100) {
				someNumber = 0;
			}
			
			delay_ms(3000);
		}
	}*/
}