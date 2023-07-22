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



#include "drv_spi.h"


#ifndef __USE_SOFT_SPI_INTERFACE__
/** 硬件SPI */


/**
  * @brief :SPI初始化(硬件)
  * @param :无
  * @note  :无
  * @retval:无
  */ 
void drv_spi_init( void )
{
	/** 引脚属性配置 */
	//SCK MOSI NSS配置为输出 MISO配置为输入
	SPI_CLK_GPIO_ODR |= 0x01 << SPI_CLK_GPIO_BIT;						//置位相应的ODR 配置为输出
	SPI_MOSI_GPIO_ODR |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_ODR |= 0x01 << SPI_NSS_GPIO_BIT;
	SPI_MISO_GPIO_ODR &= (uint8_t)( ~( 0x01 << SPI_MISO_GPIO_BIT ));	//清零相应的ODR 配置为输入
	
	//SCK初始状态设置为低 MOSI NSS初始状态设置为高
	SPI_CLK_GPIO_PORT &= (uint8_t)( ~( 0x01 << SPI_CLK_GPIO_BIT ));		//零0 PORT输出低
	SPI_MOSI_GPIO_PORT |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_PORT |= 0x01 << SPI_NSS_GPIO_BIT;						//置1 PORT输出高
	
	/** SPI外设配置 */
	SPCR &= (uint8_t)( ~( 0x01 << SPE ));	//关闭SPI
	SPCR &= (uint8_t)( ~(( 0x01 << SPIE ) | ( 0x01 << DORD ) | ( 0x01 << CPOL ) | ( 0x01 << CPHA )));	//关中断 MSB在前 CPOL = CPHA = 0( 空闲低电平 第一个沿采集数据 )
	//时钟4分频
	SPCR &= (uint8_t)( ~(( 0x01 << SPR0 ) | ( 0x01 << SPR1 )));
	SPSR  = 0x00;							
	SPCR |= 0x01 << MSTR;					//主机模式
	SPCR |= 0x01 << SPE;					//使能SPI
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :无
  * @retval:接收到的字节
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	SPDR = TxByte;					//发送数据
	while( 0x00 == ( SPSR & ( 0x01 << SPIF )));	//等待数据传输完成
	return ( (uint8_t)SPDR );		//返回接收到的数据
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :无
  * @retval:无
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	spi_set_nss_low( );			//拉低片选
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//收发数据
		ReadBuffer++;
		WriteBuffer++;			//读写地址加1
	}
	spi_set_nss_high( );		//拉高片选
}

/** 硬件SPI */



#else



/** 软件SPI */


/**
  * @brief :SPI初始化(软件)
  * @param :无
  * @note  :无
  * @retval:无
  */
void drv_spi_init( void )
{
	//SCK MOSI NSS配置为输出 MISO配置为输入
	SPI_CLK_GPIO_ODR |= 0x01 << SPI_CLK_GPIO_BIT;						//置位相应的ODR 配置为输出
	SPI_MOSI_GPIO_ODR |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_ODR |= 0x01 << SPI_NSS_GPIO_BIT;
	SPI_MISO_GPIO_ODR &= (uint8_t)( ~( 0x01 << SPI_MISO_GPIO_BIT ));	//清零相应的ODR 配置为输入
	
	//SCK初始状态设置为低 MOSI NSS初始状态设置为高
	SPI_CLK_GPIO_PORT &= (uint8_t)( ~( 0x01 << SPI_CLK_GPIO_BIT ));		//零0 PORT输出低
	SPI_MOSI_GPIO_PORT |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_PORT |= 0x01 << SPI_NSS_GPIO_BIT;						//置1 PORT输出高
	
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t i = 0, Data = 0;
	
	spi_set_clk_low( );
	
	for( i = 0; i < 8; i++ )			//一个字节8byte需要循环8次
	{
		/** 发送 */
		if( 0x80 == ( TxByte & 0x80 ))
		{
			spi_set_mosi_hight( );		//如果即将要发送的位为 1 则置高IO引脚
		}
		else
		{
			spi_set_mosi_low( );		//如果即将要发送的位为 0 则置低IO引脚
		}
		TxByte <<= 1;					//数据左移一位，先发送的是最高位
		
		spi_set_clk_high( );			//时钟线置高
//		__nop( );
//		__nop( );
		
		/** 接收 */
		Data <<= 1;						//接收数据左移一位，先接收到的是最高位
		if( 1 == spi_get_miso( ))
		{
			Data |= 0x01;				//如果接收时IO引脚为高则认为接收到 1
		}
		
		spi_set_clk_low( );				//时钟线置低
//		__nop( );
//		__nop( );
	}
	
	return Data;		//返回接收到的字节
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	spi_set_nss_low( );			//片选拉低
	
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//收发数据
		ReadBuffer++;
		WriteBuffer++;			//读写地址加1
	}
	
	spi_set_nss_high( );		//片选拉高
}


/** 软件SPI */
#endif


