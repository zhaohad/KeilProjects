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



#ifndef __MAIN_H__
#define __MAIN_H__


#include "drv_button.h"
#include "drv_delay.h"
#include "drv_led.h"
#include "drv_spi.h"
#include "drv_uart.h"
#include "drv_RF24L01.h"


#define 	__RF24L01_TX_TEST__							//**@@ 如果测试发送功能则需要定义该宏，如果测试接收则需要屏蔽该宏 **@@//
//#define 	__USE_SOFT_SPI_INTERFACE__					//**@@ 如果使用软件SPI则需要定义该宏，反之如果使用硬件SPI则需要屏蔽该宏 **@@//


/** 发送模式定义 */
enum
{
	TX_MODE_1 = 0,		//鍙戦�佹ā寮?锛屽彂閫佸浐瀹氱殑瀛楃涓?
	TX_MODE_2			//鍙戦�佹ā寮?锛屽彂閫佷覆鍙ｆ帴鏀跺埌鐨勬暟鎹?
};


#endif
