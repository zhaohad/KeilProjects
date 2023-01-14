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


#include "drv_button.h"
#include "drv_delay.h"



/**
  * @brief :按键初始化
  * @param :无
  * @note  :无
  * @retval:无
  */ 
void drv_button_init( void )
{
	//配置按键为输入 上拉
	BUTTON_GPIO_ODR |= (uint8_t)( ~( 0x01 << BUTTOND_GPIO_BIT ));		
	BUTTON_GPIO_PORT |= 1 << BUTTOND_GPIO_BIT;	
}

/**
  * @brief :按键查询
  * @param :无
  * @note  :无
  * @retval:
  *			0:按键没有按下
  *			1:检测到按键动作
  */
uint8_t drv_button_check( void )
{
	if( 0x00 == (( BUTTON_GPIO_PIN >> BUTTOND_GPIO_BIT ) & 0x01 ))		//检测按键输入状态
	{
		drv_delay_ms( 40 );			//消抖
		if( 0x00 == (( BUTTON_GPIO_PIN >> BUTTOND_GPIO_BIT ) & 0x01 ))
		{
			return 1;				//按键按下，返回按键状态
		}
	}
	
	return 0;
}
