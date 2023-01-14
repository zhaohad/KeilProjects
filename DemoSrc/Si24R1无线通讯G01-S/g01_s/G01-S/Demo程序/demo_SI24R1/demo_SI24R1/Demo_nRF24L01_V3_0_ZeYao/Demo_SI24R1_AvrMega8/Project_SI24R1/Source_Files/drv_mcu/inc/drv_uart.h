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


//串口引脚定义
//泽耀科技 AS06-AVR地板两个红色LED等分别为PD0 PD1,LED和串口不能同时使用
#define UART_TX_GPIO_PORT			PORTD		//输出寄存器
#define UART_TX_GPIO_ODR			DDRD		//方向寄存器
#define UART_TX_GPIO_PIN			PIND		//输入寄存器
#define UART_TX_GPIO_BIT			PD1			//引脚在端口的位置

#define UART_RX_GPIO_PORT			PORTD		
#define UART_RX_GPIO_ODR			DDRD		
#define UART_RX_GPIO_PIN			PIND		
#define UART_RX_GPIO_BIT			PD0			


void drv_uart_init( );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );



#endif



