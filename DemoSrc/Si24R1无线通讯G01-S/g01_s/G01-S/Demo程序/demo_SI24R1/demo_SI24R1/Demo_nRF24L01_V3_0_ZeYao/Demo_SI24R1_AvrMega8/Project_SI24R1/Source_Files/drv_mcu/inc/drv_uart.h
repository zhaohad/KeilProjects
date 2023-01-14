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


#ifndef __DRV_UART_H__
#define __DRV_UART_H__


#include <avr/io.h>


//�������Ŷ���
//��ҫ�Ƽ� AS06-AVR�ذ�������ɫLED�ȷֱ�ΪPD0 PD1,LED�ʹ��ڲ���ͬʱʹ��
#define UART_TX_GPIO_PORT			PORTD		//����Ĵ���
#define UART_TX_GPIO_ODR			DDRD		//����Ĵ���
#define UART_TX_GPIO_PIN			PIND		//����Ĵ���
#define UART_TX_GPIO_BIT			PD1			//�����ڶ˿ڵ�λ��

#define UART_RX_GPIO_PORT			PORTD		
#define UART_RX_GPIO_ODR			DDRD		
#define UART_RX_GPIO_PIN			PIND		
#define UART_RX_GPIO_BIT			PD0			


void drv_uart_init( );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );



#endif



