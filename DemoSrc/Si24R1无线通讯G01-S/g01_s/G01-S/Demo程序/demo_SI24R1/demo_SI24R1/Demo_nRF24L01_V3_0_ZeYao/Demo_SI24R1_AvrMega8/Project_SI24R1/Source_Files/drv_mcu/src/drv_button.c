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
  * @brief :������ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void drv_button_init( void )
{
	//���ð���Ϊ���� ����
	BUTTON_GPIO_ODR |= (uint8_t)( ~( 0x01 << BUTTOND_GPIO_BIT ));		
	BUTTON_GPIO_PORT |= 1 << BUTTOND_GPIO_BIT;	
}

/**
  * @brief :������ѯ
  * @param :��
  * @note  :��
  * @retval:
  *			0:����û�а���
  *			1:��⵽��������
  */
uint8_t drv_button_check( void )
{
	if( 0x00 == (( BUTTON_GPIO_PIN >> BUTTOND_GPIO_BIT ) & 0x01 ))		//��ⰴ������״̬
	{
		drv_delay_ms( 40 );			//����
		if( 0x00 == (( BUTTON_GPIO_PIN >> BUTTOND_GPIO_BIT ) & 0x01 ))
		{
			return 1;				//�������£����ذ���״̬
		}
	}
	
	return 0;
}
