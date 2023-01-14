#ifndef __MAIN_H__
#define __MAIN_H__



#include "drv_led.h"
#include "drv_spi.h"
#include "drv_delay.h"
#include "drv_button.h"
#include "drv_uart.h"
#include "drv_RF24L01.h"


#define __RF24L01_TX_TEST__				//发送模式，如果切换到接收模式屏蔽即可 -> "//#define __RF24L01_TX_TEST__"



/** 发送模式定义 */
enum
{
	TX_MODE_1 = 0,		//发送模式1，发送固定的字符串
	TX_MODE_2			//发送模式2，发送串口接收到的数据
};


#endif
