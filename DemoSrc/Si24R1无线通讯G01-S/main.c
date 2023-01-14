#include <reg51.h>
#include <intrins.h>
#include "G01_S.h"
#include "delay.h"

sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;

bit g_TX = 1;

uint8_t g_send[8] = {~0x01, ~0x02, ~0x04, ~0x08, ~0x10, ~0x20, ~0x40, ~0x80};
uint8_t g_rece[8];

void main() {
	bit exist;
	P1 = 0xFF;
	NRF24L01_Gpio_Init();

	//检测nRF24L01
	exist = NRF24L01_check();
	if (exist) {
		P10 = 0;

		RF24L01_Init();
		
		_nop_();_nop_();_nop_();_nop_();_nop_();
		
		if (g_TX) {
			int i = 0;
			RF24L01_Set_Mode(MODE_TX); //发送模式
			for (i = 0; i < 8; ++i) {
				uint8_t res;
				uint8_t tx[1];
				tx[0] = g_send[i];
				P1 = tx[0];
				_nop_();_nop_();_nop_();_nop_();_nop_();
				res = NRF24L01_TxPacket((uint8_t *) tx, 1);
				delay_ms(3000);
				if (res != TX_OK) {
					P1 = res;
					delay_ms(3000);
				}
			}
		} else {
			RF24L01_Set_Mode(MODE_RX); //接收模式
			_nop_();_nop_();_nop_();_nop_();_nop_();
			P11 = 0;
			while(1) {
				uint8_t rx;
				rx = NRF24L01_RxPacket(g_rece); //接收字节
				if(0 != rx) {
					P1 = g_rece[0];
				}
			}
		}
	} else {
		P11 = 0;
	}

	while(1);
}