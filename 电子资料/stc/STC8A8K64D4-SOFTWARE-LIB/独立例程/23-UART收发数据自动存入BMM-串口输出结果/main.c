/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include	"config.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"

/*************   功能说明   ***************

通过PC向MCU发送数据, MCU将收到的数据自动存入BMM空间.

当BMM空间存满设置大小的内容后，通过串口的BMM自动发送功能把存储空间的数据原样返回.

用定时器做波特率发生器，建议使用1T模式(除非低波特率用12T)，并选择可被波特率整除的时钟频率，以提高精度.

下载时, 选择时钟 22.1184MHz (可以在配置文件"config.h"中修改).

******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/

bit	BmmTx1Flag;
bit	BmmRx1Flag;
bit	BmmTx2Flag;
bit	BmmRx2Flag;
bit	BmmTx3Flag;
bit	BmmRx3Flag;
bit	BmmTx4Flag;
bit	BmmRx4Flag;
u8 xdata BmmBuffer[256];	//收发共用缓存，同时使用多路串口时每个串口需分别定义缓存，以免相互干扰

/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/


/******************** IO口配置 ********************/
void	GPIO_config(void)
{
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 设置为准双向口
}

/******************** UART配置 ********************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;		//结构定义

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口  USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART2, &COMx_InitStructure);		//初始化串口 USART1,USART2,USART3,USART4
//	NVIC_UART2_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART3, &COMx_InitStructure);		//初始化串口 USART1,USART2,USART3,USART4
//	NVIC_UART3_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART4, &COMx_InitStructure);		//初始化串口 USART1,USART2,USART3,USART4
//	NVIC_UART4_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** BMM 配置 ********************/
void	BMM_config(void)
{
	BMM_UART_InitTypeDef		BMM_UART_InitStructure;		//结构定义

	BMM_UART_InitStructure.BMM_TX_Length = 255;				//BMM传输总字节数  	(0~255) + 1
	BMM_UART_InitStructure.BMM_TX_Buffer = BmmBuffer;	//发送数据存储地址
	BMM_UART_InitStructure.BMM_RX_Length = 255;				//BMM传输总字节数  	(0~255) + 1
	BMM_UART_InitStructure.BMM_RX_Buffer = BmmBuffer;	//接收数据存储地址
	BMM_UART_InitStructure.BMM_TX_Enable = ENABLE;		//BMM使能  	ENABLE,DISABLE
	BMM_UART_InitStructure.BMM_RX_Enable = ENABLE;		//BMM使能  	ENABLE,DISABLE
	BMM_UART_Inilize(UART1, &BMM_UART_InitStructure);	//初始化
//	BMM_UART_Inilize(UART2, &BMM_UART_InitStructure);	//初始化
//	BMM_UART_Inilize(UART3, &BMM_UART_InitStructure);	//初始化
//	BMM_UART_Inilize(UART4, &BMM_UART_InitStructure);	//初始化

	NVIC_BMM_UART1_Tx_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3
	NVIC_BMM_UART1_Rx_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3
//	NVIC_BMM_UART2_Tx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART2_Rx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART3_Tx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART3_Rx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART4_Tx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART4_Rx_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** task A **************************/
void main(void)
{
	u16	i;

	GPIO_config();
	UART_config();
	BMM_config();
	EA = 1;

	printf("STC8A8K64D4 UART BMM Test Programme!\r\n");  //UART发送一个字符串
	
	BmmTx1Flag = 0;
	BmmRx1Flag = 0;
	BmmTx2Flag = 0;
	BmmRx2Flag = 0;
	BmmTx3Flag = 0;
	BmmRx3Flag = 0;
	BmmTx4Flag = 0;
	BmmRx4Flag = 0;
	for(i=0; i<256; i++)
	{
		BmmBuffer[i] = i;
	}
	BMM_UR1T_TRIG();	//触发UART1发送功能
	BMM_UR1R_TRIG();	//触发UART1接收功能
//	BMM_UR2T_TRIG();	//触发UART2发送功能
//	BMM_UR2R_TRIG();	//触发UART2接收功能
//	BMM_UR3T_TRIG();	//触发UART3发送功能
//	BMM_UR3R_TRIG();	//触发UART3接收功能
//	BMM_UR4T_TRIG();	//触发UART4发送功能
//	BMM_UR4R_TRIG();	//触发UART4接收功能

	while (1)
	{
		if((BmmTx1Flag) && (BmmRx1Flag))
		{
			BmmTx1Flag = 0;
			BmmRx1Flag = 0;
			BMM_UR1T_TRIG();	//重新触发UART1发送功能
			BMM_UR1R_TRIG();	//重新触发UART1接收功能
		}

		if((BmmTx2Flag) && (BmmRx2Flag))
		{
			BmmTx2Flag = 0;
			BmmRx2Flag = 0;
			BMM_UR2T_TRIG();	//重新触发UART2发送功能
			BMM_UR2R_TRIG();	//重新触发UART2接收功能
		}

		if((BmmTx3Flag) && (BmmRx3Flag))
		{
			BmmTx3Flag = 0;
			BmmRx3Flag = 0;
			BMM_UR3T_TRIG();	//重新触发UART3发送功能
			BMM_UR3R_TRIG();	//重新触发UART3接收功能
		}

		if((BmmTx4Flag) && (BmmRx4Flag))
		{
			BmmTx4Flag = 0;
			BmmRx4Flag = 0;
			BMM_UR4T_TRIG();	//重新触发UART4发送功能
			BMM_UR4R_TRIG();	//重新触发UART4接收功能
		}
	}
}



