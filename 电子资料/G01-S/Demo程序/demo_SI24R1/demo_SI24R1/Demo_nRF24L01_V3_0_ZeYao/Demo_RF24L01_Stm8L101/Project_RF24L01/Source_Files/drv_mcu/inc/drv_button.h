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


//����Ӳ���ӿڶ���
#define BUTOTN_GPIO_PORT			GPIOC									
#define BUTTON_GPIO_PIN				GPIO_Pin_1


/** 按键状态定�?*/
enum
{
	BUTOTN_UP = 0,		//����û�а���
	BUTOTN_PRESS_DOWN	//��������
};



void drv_button_init( void );
uint8_t drv_button_check( void );

#endif

