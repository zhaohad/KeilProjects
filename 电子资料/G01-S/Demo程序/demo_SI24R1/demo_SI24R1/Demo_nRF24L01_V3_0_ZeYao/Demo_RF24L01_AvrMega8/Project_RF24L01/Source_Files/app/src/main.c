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



#include "main.h"						//main.h 中含有TX/RX、软件SPI/硬件SPI选择配置选项


const char *g_Ashining = "gisemi";
uint8_t g_TxMode = 0, g_UartRxFlag = 0;
uint8_t g_UartRxBuffer[ 100 ] = { 0 };
uint8_t g_RF24L01RxBuffer[ 32 ] = { 0 }; 
uint8_t g_test[ 8 ] = { 1, 2, 3, 4, 5, 6, 7, 8 };


/**
  * @brief :主函数 
  * @param :无
  * @note  :无
  * @retval:无
  */ 
int main( void )
{	
 	uint8_t i = 0;
 
 	//串口初始化
 	drv_uart_init( );	

 	//LED初始化
 	drv_led_init( );
  	
 	//SPI初始化
 	drv_spi_init( );
 	
 	//RF24L01引脚初始化
 	NRF24L01_Gpio_Init( );
 	
 	//检测nRF24L01
 	NRF24L01_check( );	
	RF24L01_Init( );			

 	for( i = 0; i < 6; i++ )
 	{
 		led_red_flashing( );
 		led_green_flashing( );
 		drv_delay_ms( 500 );
 	}

	led_red_off( );
	led_green_off( );

	
 #ifdef	__RF24L01_TX_TEST__		
 //=========================================================================================//	
 //*****************************************************************************************//
 //************************************* 发送 **********************************************//
 //*****************************************************************************************//
 //=========================================================================================//	
 	
 	//按键初始化
 	drv_button_init( );
 	
 	RF24L01_Set_Mode( MODE_TX );		//发送模式
 	while( 1 )	
 	{
 		//模式切换
 		if( BUTOTN_PRESS_DOWN == drv_button_check( ))
 		{
 			g_TxMode = 1 - g_TxMode;		//模式会在 TX_MODE_1( 0 ),TX_MODE_2( 1 )之间切换
 			
 			//状态显示清零
 			led_green_off( );
 			led_red_off( );
 			
 			if( TX_MODE_1 == g_TxMode )
 			{
 				for( i = 0; i < 6; i++ )		
 				{
 					led_red_flashing( );	//固定发送模式，红灯闪烁3次
 					drv_delay_ms( 500 );		
 				}
 			}
 			else
 			{
 				for( i = 0; i < 6; i++ )
 				{
 					led_green_flashing( );	//串口发送模式，绿灯闪烁3次
 					drv_delay_ms( 500 );
 				}
 			}
 		}
 		
 		//发送
 		if( TX_MODE_1 == g_TxMode )
 		{
 			NRF24L01_TxPacket( (uint8_t *)g_Ashining, 8 );		//模式1发送固定字符,1S一包	
 			drv_delay_ms( 1000 );	
 			led_red_flashing( );			
 		}
 		else
 		{	
 			//查询串口数据
 			i = drv_uart_rx_bytes( g_UartRxBuffer );
 			
 			if( 0 != i )
 			{
 				NRF24L01_TxPacket( g_UartRxBuffer, i );
 				led_red_flashing( );
 			}
 		}
 	}
 	

 #else		


 //=========================================================================================//	
 //*****************************************************************************************//
 //************************************* 接收 **********************************************//
 //*****************************************************************************************//
 //=========================================================================================//	
 	
 	RF24L01_Set_Mode( MODE_RX );		//接收模式
 	while( 1 )
 	{
 		i = NRF24L01_RxPacket( g_RF24L01RxBuffer );		//接收字节
 		if( 0 != i )
 		{
			led_green_flashing( );
 			drv_uart_tx_bytes( g_RF24L01RxBuffer,i);	//输出接收到的字节
 			
 		}
 	}
 	
 #endif
	
}

