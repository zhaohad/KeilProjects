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



#include "drv_delay.h"



/**
  * @brief :1MS��ʱ����
  * @param :
  * @note  :12MHz ��1MS��ʱ
  * @retval:��
  */
static void drv_delay_1ms( void )
{
	uint16_t Ms = 1;
	uint32_t j = 30;
	
	while( Ms-- )
	{
		while( j-- );
	}
}

/**
  * @brief :MS��ʱ����
  * @param :
  *			@Ms:��ʱ��MS��
  * @note  :��
  * @retval:��
  */
void drv_delay_ms( uint16_t Ms )
{
	while( Ms-- )
	{
		drv_delay_1ms( );
	}
}

