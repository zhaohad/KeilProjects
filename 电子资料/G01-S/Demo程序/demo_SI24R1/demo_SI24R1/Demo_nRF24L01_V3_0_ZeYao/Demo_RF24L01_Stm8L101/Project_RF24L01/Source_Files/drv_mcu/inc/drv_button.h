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


#include "stm8l10x_gpio.h"


//按键硬件接口定义
#define BUTOTN_GPIO_PORT			GPIOC									
#define BUTTON_GPIO_PIN				GPIO_Pin_1


/** 鎸夐敭鐘舵�佸畾涔?*/
enum
{
	BUTOTN_UP = 0,		//按键没有按下
	BUTOTN_PRESS_DOWN	//按键按下
};



void drv_button_init( void );
uint8_t drv_button_check( void );

#endif

