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
  * @brief :LED��ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void drv_led_init( void )
{
	//��������Ϊ�������ʼ״̬�øߣ�LED��
	LED_RED_GPIO_ODR |= (uint8_t)GPIO_MODE_OUT << LED_RED_GPIO_BIT;		
	LED_RED_GPIO_PORT |= 1 << LED_RED_GPIO_BIT;	
	
	LED_GREEN_GPIO_ODR |= (uint8_t)GPIO_MODE_OUT << LED_GREEN_GPIO_BIT;		
	LED_GREEN_GPIO_PORT |= 1 << LED_GREEN_GPIO_BIT;	
	
}

/**
  * @brief :LED��
  * @param :
  *			@LedPort:LEDѡ�񣬺�ɫ����ɫ
  * @note  :��
  * @retval:��
  */
void drv_led_on( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		LED_RED_GPIO_PORT &= (uint8_t)(~( 0x01 << LED_RED_GPIO_BIT ));	//��ɫLED�����õͣ���ɫLED��
	}
	else						//LED_BLUE
	{
		LED_GREEN_GPIO_PORT &= (uint8_t)(~( 0x01 << LED_GREEN_GPIO_BIT ));//��ɫLED�����õͣ���ɫLED��
	}
	
}

/**
  * @brief :LED��
  * @param :
  *			@LedPort:LEDѡ�񣬺�ɫ����ɫ
  * @note  :��
  * @retval:��
  */
void drv_led_off( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		LED_RED_GPIO_PORT |= 0x01 << LED_RED_GPIO_BIT;		//��ɫLED�����øߣ���ɫLED��
	}
	else						//LED_BLUE
	{
		LED_GREEN_GPIO_PORT |= 0x01 << LED_GREEN_GPIO_BIT;	//��ɫLED�����øߣ���ɫLED��
	}
	
}

/**
  * @brief :LED��˸
  * @param :
  *			@LedPort:LEDѡ�񣬺�ɫ����ɫ
  * @note  :��
  * @retval:��
  */
void drv_led_flashing( LedPortType LedPort )
{
	//���ŷ�ת��LED��˸
	if( LED_RED == LedPort )
	{
		LED_RED_GPIO_PORT ^= (uint8_t)( 0x01 << LED_RED_GPIO_BIT );	
	}
	else
	{
		LED_GREEN_GPIO_PORT ^= (uint8_t)( 0x01 << LED_GREEN_GPIO_BIT );
	}
}

