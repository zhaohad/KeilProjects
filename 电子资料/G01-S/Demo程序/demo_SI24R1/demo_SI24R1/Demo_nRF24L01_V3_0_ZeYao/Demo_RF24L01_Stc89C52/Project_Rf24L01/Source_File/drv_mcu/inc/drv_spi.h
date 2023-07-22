﻿/**
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


#include <reg52.h>
#include <intrins.h>
#include "typedef.h"


//SPI接口定义
sbit	SPI_SCK						=P1^7;
sbit	SPI_MOSI					=P1^5;
sbit	SPI_MISO					=P1^6;
sbit	SPI_NSS						=P1^3;

//IO在端口对应的Bit位置
#define SPI_SCK_PIN_BIT				7
#define SPI_MOSI_PIN_BIT			5
#define SPI_MISO_PIN_BIT			6
#define SPI_NSS_PIN_BIT				3

//IO配置寄存器
#define SPI_SCK_PxM0				P1M0
#define SPI_SCK_PxM1				P1M1

#define SPI_MOSI_PxM0				P1M0
#define SPI_MOSI_PxM1				P1M1

#define SPI_MISO_PxM0				P1M0
#define SPI_MISO_PxM1				P1M1

#define SPI_NSS_PxM0				P1M0
#define SPI_NSS_PxM1				P1M1



//操作函数定义
#define spi_set_clk_high( )			SPI_SCK = 1		//时钟置高
#define spi_set_clk_low( )			SPI_SCK = 0		//时钟置低

#define spi_set_mosi_hight( )		SPI_MOSI = 1	//发送脚置高
#define spi_set_mosi_low( )			SPI_MOSI = 0	//发送脚置低

#define spi_get_miso( )				(( 1 != SPI_MISO ) ? 0 : 1 )

#define spi_set_nss_high( )			SPI_NSS = 1		//片选置高
#define spi_set_nss_low( )			SPI_NSS = 0		//片选置低


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

#endif

