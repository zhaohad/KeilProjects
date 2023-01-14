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


#include "drv_uart.h"


/**
  * @brief :串口初始化
  * @param :无
  * @note  :无
  * @retval:无
  */
void drv_uart_init( )
{
	/** 串口引脚初始化 */
	//TX 配置为输出 RX 配置为输入
	UART_TX_GPIO_ODR |= 0x01 << UART_TX_GPIO_BIT;
	UART_RX_GPIO_ODR &= (uint8_t)( ~( 0x01 << UART_RX_GPIO_BIT ));
	
	UART_TX_GPIO_PORT |= 0x01 << UART_TX_GPIO_BIT;	//TX 引脚默认置高
	UART_RX_GPIO_PORT |= 0x01 << UART_RX_GPIO_BIT;	//RX 引脚上拉
	
	/** 串口外设初始化 */
	
	UCSRB = 0x00;	
	UCSRB |= ( 0x01 << RXEN ) | ( 0x01 << TXEN );	//使能接收 发送
	
	UCSRC |= ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 );	//8位数据位 1个停止位 无校验 异步通信
	
	UCSRC &= (uint8_t)( ~( 0x01 << URSEL ));		//更新UBRRH
	UBRRH &= (uint8_t)( ~0x0F ); 
	UBRRL = 49;		//波特率9600  8MHz晶振是理论应该为51 实际调试因为RC误差改为49
}

/**
  * @brief :串口发送数据
  * @param :
  *			@TxBuffer:发送数据首地址
  *			@Length:数据长度
  * @note  :无
  * @retval:无
  */
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length )
{
	while( Length-- )
	{
		while( 0x00 == ( UCSRA & ( 0x01 << UDRE )));  
		UDR = *TxBuffer;
		TxBuffer++;
	}
}

/**
  * @brief :串口接收数据
  * @param :
  *			@RxBuffer:发送数据首地址
  * @note  :无
  * @retval:接收到的字节个数
  */
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer )
{
	uint8_t l_RxLength = 0;
	uint16_t l_UartRxTimOut = 0x7FFF;
	
	while( l_UartRxTimOut-- )			//等待查询串口数据
	{
		if( 0x00 != ( UCSRA & ( 0x01 << RXC )))
		{
			*RxBuffer = (uint8_t)UDR;
			RxBuffer++;
			l_RxLength++;
			l_UartRxTimOut = 0x7FFF;	//接收到一个字符，回复等待时间
		}
		if( 100 == l_RxLength )
		{
			break;			//不能超过100个字节
		}
	}
	
	return l_RxLength;					//等待超时，数据接收完成
}

