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
  * @brief :���ڳ�ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void drv_uart_init( )
{
	/** �������ų�ʼ�� */
	//TX ����Ϊ��� RX ����Ϊ����
	UART_TX_GPIO_ODR |= 0x01 << UART_TX_GPIO_BIT;
	UART_RX_GPIO_ODR &= (uint8_t)( ~( 0x01 << UART_RX_GPIO_BIT ));
	
	UART_TX_GPIO_PORT |= 0x01 << UART_TX_GPIO_BIT;	//TX ����Ĭ���ø�
	UART_RX_GPIO_PORT |= 0x01 << UART_RX_GPIO_BIT;	//RX ��������
	
	/** ���������ʼ�� */
	
	UCSRB = 0x00;	
	UCSRB |= ( 0x01 << RXEN ) | ( 0x01 << TXEN );	//ʹ�ܽ��� ����
	
	UCSRC |= ( 0x01 << UCSZ1 ) | ( 0x01 << UCSZ0 );	//8λ����λ 1��ֹͣλ ��У�� �첽ͨ��
	
	UCSRC &= (uint8_t)( ~( 0x01 << URSEL ));		//����UBRRH
	UBRRH &= (uint8_t)( ~0x0F ); 
	UBRRL = 49;		//������9600  8MHz����������Ӧ��Ϊ51 ʵ�ʵ�����ΪRC����Ϊ49
}

/**
  * @brief :���ڷ�������
  * @param :
  *			@TxBuffer:���������׵�ַ
  *			@Length:���ݳ���
  * @note  :��
  * @retval:��
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
  * @brief :���ڽ�������
  * @param :
  *			@RxBuffer:���������׵�ַ
  * @note  :��
  * @retval:���յ����ֽڸ���
  */
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer )
{
	uint8_t l_RxLength = 0;
	uint16_t l_UartRxTimOut = 0x7FFF;
	
	while( l_UartRxTimOut-- )			//�ȴ���ѯ��������
	{
		if( 0x00 != ( UCSRA & ( 0x01 << RXC )))
		{
			*RxBuffer = (uint8_t)UDR;
			RxBuffer++;
			l_RxLength++;
			l_UartRxTimOut = 0x7FFF;	//���յ�һ���ַ����ظ��ȴ�ʱ��
		}
		if( 100 == l_RxLength )
		{
			break;			//���ܳ���100���ֽ�
		}
	}
	
	return l_RxLength;					//�ȴ���ʱ�����ݽ������
}

