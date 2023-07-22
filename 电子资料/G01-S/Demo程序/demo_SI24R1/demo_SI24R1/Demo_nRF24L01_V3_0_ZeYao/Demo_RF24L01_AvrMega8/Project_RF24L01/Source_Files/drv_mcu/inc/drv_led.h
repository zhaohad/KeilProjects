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


#ifndef	__DRV_LED_H__
#define __DRV_LED_H__


#include <avr/io.h>


//LED硬件定义 
//泽耀科技 AS06-AVR地板两个红色LED等分别为PD0 PD1,串口TX RX也为这两个引脚 所以在AS06-AVR底板上LED和串口不能同时使用
#define LED_RED_GPIO_PORT			PORTC	//输出寄存器		
#define LED_RED_GPIO_ODR			DDRC	//方向寄存器
#define LED_RED_GPIO_PIN			PINC	//输入寄存器
#define LED_RED_GPIO_BIT			PC0		//引脚在端口的位置

#define LED_GREEN_GPIO_PORT			PORTC								
#define LED_GREEN_GPIO_ODR			DDRC
#define LED_GREEN_GPIO_PIN			PINC
#define LED_GREEN_GPIO_BIT			PC1




/** LED定义 */
typedef enum LedPort
{
	LED_RED = 0,			//红色LED
	LED_GREEN				//绿色LED
}LedPortType;

/** GPIO模式定义 */
typedef enum GpioMode
{
	GPIO_MODE_IN = 0,		//输入
	GPIO_MODE_OUT			//输出
}GpioModeType;


void drv_led_init( void );
void drv_led_on( LedPortType LedPort );
void drv_led_off( LedPortType LedPort );
void drv_led_flashing( LedPortType LedPort );

//红色LED操作函数
#define led_red_on( )				drv_led_on( LED_RED )
#define led_red_off( )				drv_led_off( LED_RED )
#define led_red_flashing( )			drv_led_flashing( LED_RED )
//蓝色LED操作函数
#define led_green_on( )				drv_led_on( LED_GREEN )
#define led_green_off( )			drv_led_off( LED_GREEN )
#define led_green_flashing( )		drv_led_flashing( LED_GREEN )


#endif

