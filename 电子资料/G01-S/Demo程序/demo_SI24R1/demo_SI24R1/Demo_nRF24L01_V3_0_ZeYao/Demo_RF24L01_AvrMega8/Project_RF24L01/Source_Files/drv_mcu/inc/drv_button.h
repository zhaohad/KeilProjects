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


//����Ӳ������ KEY0
#define BUTTON_GPIO_PORT			PORTD	//����Ĵ���								
#define BUTTON_GPIO_ODR				DDRD	//����Ĵ���
#define BUTTON_GPIO_PIN				PIND	//����Ĵ���
#define BUTTOND_GPIO_BIT			PD2		//�����ڶ˿ڵ�λ��

/** ����״̬���� */
enum
{
	BUTOTN_UP = 0,		//����δ����
	BUTOTN_PRESS_DOWN	//��������
};



void drv_button_init( void );
uint8_t drv_button_check( void );

#endif

