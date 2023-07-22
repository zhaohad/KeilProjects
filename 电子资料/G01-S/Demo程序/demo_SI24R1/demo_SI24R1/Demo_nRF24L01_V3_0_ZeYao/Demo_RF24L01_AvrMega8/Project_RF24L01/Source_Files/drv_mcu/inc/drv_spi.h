/**
  ******************************************************************************
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  * 
  * 
  ******************************************************************************
  */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__



#include <avr/io.h>
#include "main.h"



//SPI���Ŷ���
#define SPI_CLK_GPIO_PORT			PORTB		//����Ĵ���
#define SPI_CLK_GPIO_ODR			DDRB		//����Ĵ���
#define SPI_CLK_GPIO_PIN			PINB		//����Ĵ���
#define SPI_CLK_GPIO_BIT			PB5			//�����ڶ˿ڵ�λ��

#define SPI_MISO_GPIO_PORT			PORTB
#define SPI_MISO_GPIO_ODR			DDRB
#define SPI_MISO_GPIO_PIN			PINB
#define SPI_MISO_GPIO_BIT			PB4

#define SPI_MOSI_GPIO_PORT			PORTB
#define SPI_MOSI_GPIO_ODR			DDRB
#define SPI_MOSI_GPIO_PIN			PINB
#define SPI_MOSI_GPIO_BIT			PB3

#define SPI_NSS_GPIO_PORT			PORTB
#define SPI_NSS_GPIO_ODR			DDRB
#define SPI_NSS_GPIO_PIN			PINB
#define SPI_NSS_GPIO_BIT			PB2


#define spi_set_nss_high( )			SPI_NSS_GPIO_PORT |= 0x01 << SPI_NSS_GPIO_BIT					//Ƭѡ�ø�
#define spi_set_nss_low( )			SPI_NSS_GPIO_PORT &= (uint8_t)( ~(0x01 << SPI_NSS_GPIO_BIT ))	//Ƭѡ�õ�


#ifdef __USE_SOFT_SPI_INTERFACE__			/** ֻ��ʹ�����SPI����Ҫ�ķ�װ */		


#define spi_set_clk_high( )			SPI_CLK_GPIO_PORT |= 0x01 << SPI_CLK_GPIO_BIT					//ʱ���ø�
#define spi_set_clk_low( )			SPI_CLK_GPIO_PORT &= (uint8_t)( ~(0x01 << SPI_CLK_GPIO_BIT ))	//ʱ���õ�

#define spi_set_mosi_hight( )		SPI_MOSI_GPIO_PORT |= 0x01 << SPI_MOSI_GPIO_BIT					//���ͽ��ø�
#define spi_set_mosi_low( )			SPI_MOSI_GPIO_PORT &= (uint8_t)( ~(0x01 << SPI_MOSI_GPIO_BIT ))	//���ͽ��õ�

#define spi_get_miso( )				(( SPI_MISO_GPIO_PIN & (0x01 << SPI_MISO_GPIO_BIT)) != (0x01 << SPI_MISO_GPIO_BIT) ) ? 0 : 1 // ����Ӧ����λΪ����õ�0����Ӧ����λΪ����õ�1

#endif


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );



#endif

