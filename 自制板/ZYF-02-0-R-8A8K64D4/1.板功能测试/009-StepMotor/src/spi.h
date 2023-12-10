#ifndef __SPI_H__
#define __SPI_H__

#include "typedef.h" 

/** hanwei **/
#define SPI_NSS 								P_G01_S_CSN
#define SPI_SCK 								P_G01_S_SCK
#define SPI_MOSI 								P_G01_S_MOSI
#define SPI_MISO								P_G01_S_MISO

#define spi_set_nss_high()			SPI_NSS = 1 //片选置高
#define spi_set_nss_low()				SPI_NSS = 0 //片选置低

//操作函数定义
#define spi_set_clk_high()			SPI_SCK = 1 //时钟置高
#define spi_set_clk_low()				SPI_SCK = 0 //时钟置低

#define spi_set_mosi_hight()		SPI_MOSI = 1 //发送脚置高
#define spi_set_mosi_low()			SPI_MOSI = 0 //发送脚置低
#define spi_get_miso()					SPI_MISO

uint8_t spi_read_write_byte(uint8_t TxByte);

#endif