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
static void drv_delay_1ms( )
{	
 	uint16_t Delay_Ms = 60;
 	uint32_t Delay_j = 1;

	while( Delay_Ms-- )
	{
	    Delay_j = 1;
		while( Delay_j-- );
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

