#include "STC8A8K64D4.H"
#include "STC8A_GPIO.H"
#include "typedef.h"
#include "G01_S.h"
#include "oled12864.h"
#include "stdio.h"
#include "dtos.h"

bit g_Rec = 1;
u8 outL = 0;

void GPIO_LED() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	int someNumber = 0;
	bit exist;
	GPIO_LED();
	NRF24L01_GPIO_config();
	NRF24L01_Gpio_Init();
	
	OLED_Init();
	
	exist = NRF24L01_check();
	if (exist) {
		P_LED1 = 0;
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
		P_LED2 = 0;
	} else {
		OLED_ShowString8(0, outL, "Set MODE_TX");
		RF24L01_Set_Mode(MODE_TX); //发送模式
		_nop_();_nop_();_nop_();_nop_();_nop_();
	}
	outL++;

	while(1) {
		u8 outLL = outL;
		uint8_t res;
		uint8_t tx[1];
		uint8_t numStr[10];
		uint8_t str[20];

		if (g_Rec) {
			uint8_t rx;
			uint8_t g_rece[8];
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
	}
}