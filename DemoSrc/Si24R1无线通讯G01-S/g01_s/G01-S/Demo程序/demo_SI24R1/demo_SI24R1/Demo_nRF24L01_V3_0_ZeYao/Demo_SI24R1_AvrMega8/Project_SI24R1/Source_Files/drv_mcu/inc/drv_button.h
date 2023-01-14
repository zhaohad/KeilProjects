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


#ifndef __DRV_BUTTON_H__
#define __DRV_BUTTON_H__


#include <avr/io.h>


//按键硬件定义 KEY0
#define BUTTON_GPIO_PORT			PORTD	//输出寄存器								
#define BUTTON_GPIO_ODR				DDRD	//方向寄存器
#define BUTTON_GPIO_PIN				PIND	//输入寄存器
#define BUTTOND_GPIO_BIT			PD2		//引脚在端口的位置

/** 按键状态定义 */
enum
{
	BUTOTN_UP = 0,		//按键未按下
	BUTOTN_PRESS_DOWN	//按键按下
};



void drv_button_init( void );
uint8_t drv_button_check( void );

#endif

