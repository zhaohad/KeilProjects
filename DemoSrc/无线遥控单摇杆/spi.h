#ifndef __SPI_H__
#define __SPI_H__

#include "typedef.h" 

/** hanwei **/
#define SPI_NSS 								G01S_0_CSN
#define SPI_SCK 								G01S_0_SCK
#define SPI_MOSI 								G01S_0_MOSI
#define SPI_MISO								G01S_0_MISO

#define spi_set_nss_high()			SPI_NSS = 1 //Ƭѡ�ø�
#define spi_set_nss_low()				SPI_NSS = 0 //Ƭѡ�õ�

//������������
#define spi_set_clk_high()			SPI_SCK = 1 //ʱ���ø�
#define spi_set_clk_low()				SPI_SCK = 0 //ʱ���õ�

#define spi_set_mosi_hight()		SPI_MOSI = 1 //���ͽ��ø�
#define spi_set_mosi_low()			SPI_MOSI = 0 //���ͽ��õ�
#define spi_get_miso()					SPI_MISO

uint8_t spi_read_write_byte(uint8_t TxByte);

#endif