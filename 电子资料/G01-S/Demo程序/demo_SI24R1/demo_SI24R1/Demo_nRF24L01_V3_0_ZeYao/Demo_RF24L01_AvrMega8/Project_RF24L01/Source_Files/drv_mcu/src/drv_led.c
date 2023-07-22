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



#include "drv_led.h"



/**
  * @brief :LED初始化
  * @param :无
  * @note  :无
  * @retval:无
  */ 
void drv_led_init( void )
{
	//引脚配置为输出，初始状态置高，LED灭
	LED_RED_GPIO_ODR |= (uint8_t)GPIO_MODE_OUT << LED_RED_GPIO_BIT;		
	LED_RED_GPIO_PORT |= 1 << LED_RED_GPIO_BIT;	
	
	LED_GREEN_GPIO_ODR |= (uint8_t)GPIO_MODE_OUT << LED_GREEN_GPIO_BIT;		
	LED_GREEN_GPIO_PORT |= 1 << LED_GREEN_GPIO_BIT;	
	
}

/**
  * @brief :LED亮
  * @param :
  *			@LedPort:LED选择，红色或绿色
  * @note  :无
  * @retval:无
  */
void drv_led_on( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		LED_RED_GPIO_PORT &= (uint8_t)(~( 0x01 << LED_RED_GPIO_BIT ));	//红色LED引脚置低，红色LED亮
	}
	else						//LED_BLUE
	{
		LED_GREEN_GPIO_PORT &= (uint8_t)(~( 0x01 << LED_GREEN_GPIO_BIT ));//绿色LED引脚置低，蓝色LED亮
	}
	
}

/**
  * @brief :LED灭
  * @param :
  *			@LedPort:LED选择，红色或绿色
  * @note  :无
  * @retval:无
  */
void drv_led_off( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		LED_RED_GPIO_PORT |= 0x01 << LED_RED_GPIO_BIT;		//红色LED引脚置高，红色LED灭
	}
	else						//LED_BLUE
	{
		LED_GREEN_GPIO_PORT |= 0x01 << LED_GREEN_GPIO_BIT;	//绿色LED引脚置高，蓝色LED灭
	}
	
}

/**
  * @brief :LED闪烁
  * @param :
  *			@LedPort:LED选择，红色或绿色
  * @note  :无
  * @retval:无
  */
void drv_led_flashing( LedPortType LedPort )
{
	//引脚翻转，LED闪烁
	if( LED_RED == LedPort )
	{
		LED_RED_GPIO_PORT ^= (uint8_t)( 0x01 << LED_RED_GPIO_BIT );	
	}
	else
	{
		LED_GREEN_GPIO_PORT ^= (uint8_t)( 0x01 << LED_GREEN_GPIO_BIT );
	}
}

