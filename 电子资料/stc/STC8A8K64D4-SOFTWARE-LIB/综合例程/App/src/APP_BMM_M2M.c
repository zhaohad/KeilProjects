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

#include	"APP_BMM_M2M.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"


/*************	功能说明	**************

本程序演示BMM Memory to Memory数据转移.

设置2个存储器空间，一个发送一个接收，分别初始化2个存储器空间内容.

设置M2M BMM，上电后自动将发送存储里的内容写入到接收存储器空间.

根据不同的读取顺序、写入顺序，接收到不同的数据结果.

通过串口(P3.0,P3.1)打印接收存储器数据(上电打印一次).

用定时器做波特率发生器，建议使用1T模式(除非低波特率用12T)，并选择可被波特率整除的时钟频率，以提高精度.

下载时, 选择时钟 22.1184MHz (可以在配置文件"config.h"中修改).

******************************************/


//========================================================================
//                               本地常量声明	
//========================================================================


//========================================================================
//                               本地变量声明
//========================================================================

bit BmmM2MFlag = 0;
u8 xdata BmmTxBuffer[256];
u8 xdata BmmRxBuffer[256];

//========================================================================
//                               本地函数声明
//========================================================================


//========================================================================
//                            外部函数和变量声明
//========================================================================


//========================================================================
// 函数: BMM_M2M_init
// 描述: 用户初始化程序.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2020-09-28
//========================================================================
void BMM_M2M_init(void)
{
	u16	i;
	COMx_InitDefine		COMx_InitStructure;		//结构定义
	BMM_M2M_InitTypeDef		BMM_M2M_InitStructure;		//结构定义

	//----------------------------------------------
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 设置为准双向口
	
	//----------------------------------------------
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	printf("STC8A8K64D4 Memory to Memory BMM Test Programme!\r\n");  //UART发送一个字符串

	//----------------------------------------------
	BMM_M2M_InitStructure.BMM_Enable = ENABLE;			//BMM使能  	ENABLE,DISABLE
	BMM_M2M_InitStructure.BMM_Length = 127;					//BMM传输总字节数  	(0~255) + 1
	BMM_M2M_InitStructure.BMM_Tx_Buffer = BmmTxBuffer;	//发送数据存储地址
	BMM_M2M_InitStructure.BMM_Rx_Buffer = (u16)&BmmRxBuffer[255];	//接收数据存储地址
	BMM_M2M_InitStructure.BMM_SRC_Dir = M2M_ADDR_INC;		//数据源地址改变方向  	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_InitStructure.BMM_DEST_Dir = M2M_ADDR_DEC;	//数据目标地址改变方向 	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_Inilize(&BMM_M2M_InitStructure);		//初始化
	NVIC_BMM_M2M_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3

	for(i=0; i<256; i++)
	{
		BmmTxBuffer[i] = i;
		BmmRxBuffer[i] = 0;
	}
	BMM_M2M_TRIG();		//触发启动转换
}

//========================================================================
// 函数: Sample_BMM_M2M
// 描述: 用户应用程序.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2020-09-24
//========================================================================
void Sample_BMM_M2M(void)
{
	u16	i;

	if(BmmM2MFlag)
	{
		BmmM2MFlag = 0;

		for(i=0; i<256; i++)
		{
			printf("%02bX ", BmmRxBuffer[i]);
			if((i & 0x0f) == 0x0f)
				printf("\r\n");
		}
	}
}

//========================================================================
// 函数: void M2M_BMM_Interrupt (void) interrupt 47
// 描述: M2M BMM中断函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-5-8
// 备注: 
//========================================================================
//void M2M_BMM_Interrupt(void) interrupt 13
//{
//	BMM_M2MIF_CLR();
//	BmmM2MFlag = 1;
//}


