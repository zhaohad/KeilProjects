#include <intrins.h>
#include "spi.h"

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t spi_read_write_byte(uint8_t TxByte) {
	xdata uint8_t i = 0, Data = 0;
	
	spi_set_clk_low();

	for(i = 0; i < 8; i++ ) { //一个字节8byte需要循环8次
		/** 发送 */
		if(0x80 == (TxByte & 0x80)) {
			spi_set_mosi_hight(); //如果即将要发送的位为 1 则置高IO引脚
		} else {
			spi_set_mosi_low(); //如果即将要发送的位为 0 则置低IO引脚
		}
		TxByte <<= 1; //数据左移一位，先发送的是最高位
		spi_set_clk_high(); //时钟线置高
		_nop_();

		/** 接收 */
		Data <<= 1; //接收数据左移一位，先接收到的是最高位
		if(1 == spi_get_miso()) {
			Data |= 0x01; //如果接收时IO引脚为高则认为接收到 1
		}

		spi_set_clk_low(); //时钟线置低
		_nop_();
	}

	return Data;		//返回接收到的字节
}