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
#include	"STC8A_SPI.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Switch.h"

/*************   功能说明   ***************

UART_BMM, M2M_BMM, SPI_BMM 综合使用演示例程.

通过串口发送数据给MCU1，MCU1将接收到的数据由SPI发送给MCU2，MCU2再通过串口发送出去.

通过串口发送数据给MCU2，MCU2将接收到的数据由SPI发送给MCU1，MCU1再通过串口发送出去.

MCU1/MCU2: UART接收 -> UART Rx BMM -> M2M -> SPI Tx BMM -> SPI发送

MCU2/MCU1: SPI接收 -> SPI Rx BMM -> M2M -> UART Tx BMM -> UART发送

         MCU1                          MCU2
  |-----------------|           |-----------------|
  |            MISO |-----------| MISO            |
--| TX         MOSI |-----------| MOSI         TX |--
  |            SCLK |-----------| SCLK            |
--| RX           SS |-----------| SS           RX |--
  |-----------------|           |-----------------|


下载时, 选择时钟 22.1184MHz (可以在配置文件"config.h"中修改).

******************************************/

/*************	本地常量声明	**************/

#define BUF_LENGTH          107			//n+1

/*************	本地变量声明	**************/

bit	SpiTxFlag;
bit	SpiRxFlag;
bit	BmmTx1Flag;
bit	BmmRx1Flag;

bit	u2sFlag;    //UART to SPI
bit	s2uFlag;    //SPI to UART

bit	SpiSendFlag;
bit	UartSendFlag;

u8 xdata UartTxBuffer[256];
u8 xdata UartRxBuffer[256];
u8 xdata SpiTxBuffer[256];
u8 xdata SpiRxBuffer[256];


/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/


/******************** IO口配置 ********************/
void	GPIO_config(void)
{
	P2_MODE_IO_PU(GPIO_Pin_All);		//P2 设置为准双向口
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);		//P3.0,P3.1 设置为准双向口

	SPI_SW(SPI_P22_P23_P24_P25);	//SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P74_P75_P76_P77,SPI_P35_P34_P33_P32
	SPI_SS_2 = 1;
}

/******************** UART配置 ********************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;		//结构定义

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** SPI 配置 ********************/
void	SPI_config(void)
{
	SPI_InitTypeDef		SPI_InitStructure;

	SPI_InitStructure.SPI_Enable    = ENABLE;						//SPI启动    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = ENABLE;						//片选位     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;					//移位方向   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Slave;		//主从选择   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;			//时钟相位   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;		//数据边沿   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_64;			//SPI速度    SPI_Speed_4, SPI_Speed_16, SPI_Speed_64, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	NVIC_SPI_Init(DISABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** BMM 配置 ********************/
void	BMM_config(void)
{
	BMM_M2M_InitTypeDef		BMM_M2M_InitStructure;		//结构定义
	BMM_SPI_InitTypeDef		BMM_SPI_InitStructure;		//结构定义
	BMM_UART_InitTypeDef		BMM_UART_InitStructure;		//结构定义

	//----------------------------------------------
	BMM_UART_InitStructure.BMM_TX_Length = BUF_LENGTH;	//BMM传输总字节数  	(0~255) + 1
	BMM_UART_InitStructure.BMM_TX_Buffer = UartTxBuffer;	//发送数据存储地址
	BMM_UART_InitStructure.BMM_RX_Length = BUF_LENGTH;	//BMM传输总字节数  	(0~255) + 1
	BMM_UART_InitStructure.BMM_RX_Buffer = UartRxBuffer;	//接收数据存储地址
	BMM_UART_InitStructure.BMM_TX_Enable = ENABLE;		//BMM使能  	ENABLE,DISABLE
	BMM_UART_InitStructure.BMM_RX_Enable = ENABLE;		//BMM使能  	ENABLE,DISABLE
	BMM_UART_Inilize(UART1, &BMM_UART_InitStructure);	//初始化

	NVIC_BMM_UART1_Tx_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3
	NVIC_BMM_UART1_Rx_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3
	BMM_UR1R_TRIG();	//触发UART1接收功能

	//----------------------------------------------
	BMM_M2M_InitStructure.BMM_Enable = ENABLE;			//BMM使能  	ENABLE,DISABLE
	BMM_M2M_InitStructure.BMM_Length = BUF_LENGTH;			//BMM传输总字节数  	(0~255) + 1
	BMM_M2M_InitStructure.BMM_Tx_Buffer = UartRxBuffer;	//发送数据存储地址
	BMM_M2M_InitStructure.BMM_Rx_Buffer = SpiTxBuffer;	//接收数据存储地址
	BMM_M2M_InitStructure.BMM_SRC_Dir = M2M_ADDR_INC;		//数据源地址改变方向  	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_InitStructure.BMM_DEST_Dir = M2M_ADDR_INC;	//数据目标地址改变方向 	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_Inilize(&BMM_M2M_InitStructure);		//初始化
	NVIC_BMM_M2M_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3

	//----------------------------------------------
	BMM_SPI_InitStructure.BMM_Enable = DISABLE;					//BMM使能  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Tx_Enable = ENABLE;				//BMM发送数据使能  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Rx_Enable = ENABLE;				//BMM接收数据使能  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Length = BUF_LENGTH;			//BMM传输总字节数  	(0~255) + 1
	BMM_SPI_InitStructure.BMM_Tx_Buffer = SpiTxBuffer;	//发送数据存储地址
	BMM_SPI_InitStructure.BMM_Rx_Buffer = SpiRxBuffer;	//接收数据存储地址
	BMM_SPI_InitStructure.BMM_SS_Sel = SPI_SS_P22;			//自动控制SS脚选择 	SPI_SS_P12,SPI_SS_P22,SPI_SS_P74,SPI_SS_P35
	BMM_SPI_InitStructure.BMM_AUTO_SS = DISABLE;				//自动控制SS脚使能  	ENABLE,DISABLE
	BMM_SPI_Inilize(&BMM_SPI_InitStructure);		//初始化
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_S | CLR_FIFO);	//bit7 1:使能 SPI_BMM, bit5 1:开始 SPI_BMM 从机模式, bit0 1:清除 SPI_BMM FIFO
	NVIC_BMM_SPI_Init(ENABLE,Priority_0,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0~Priority_3; 总线优先级(低到高) Priority_0~Priority_3
}

void M2M_UART_SPI(void)
{
	BMM_M2M_CLR_STA();
	SET_M2M_TX_FIFO(UartRxBuffer);
	SET_M2M_RX_FIFO(SpiTxBuffer);
	BMM_M2M_TRIG();
}

void M2M_SPI_UART(void)
{
	BMM_M2M_CLR_STA();
	SET_M2M_TX_FIFO(SpiRxBuffer);
	SET_M2M_RX_FIFO(UartTxBuffer);
	BMM_M2M_TRIG();
}

void UART_BMM_Tx(void)
{
	BMM_UR1T_TRIG();
}

void UART_BMM_Rx(void)
{
	BMM_UR1R_TRIG();
}

void SPI_BMM_Master(void)
{
	SET_BMM_SPI_CR(0);
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPI_SS_2 = 0;
	SPCTL = 0xd2;   //使能 SPI 主机模式，忽略SS引脚功能
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_M);	//bit7 1:使能 SPI_BMM, bit6 1:开始 SPI_BMM 主机模式
}

void SPI_BMM_Slave(void)
{
	SET_BMM_SPI_CR(0);
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPCTL = 0x42;  //重新设置为从机待机
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_S);	//bit7 1:使能 SPI_BMM, bit5 1:开始 SPI_BMM 从机模式
}

/******************** task A **************************/
void main(void)
{
	GPIO_config();
	UART_config();
	SPI_config();
	BMM_config();
	EA = 1;

	printf("STC8A8K64D4 UART1-BMM-SPI互为主从透传程序.\r\n");
	
	while (1)
	{
		//UART接收 -> UART BMM -> SPI BMM -> SPI发送
		if(BmmRx1Flag)
		{
			BmmRx1Flag = 0;
			u2sFlag = 1;
			M2M_UART_SPI();			//UART Memory -> SPI Memory
		}

		if(SpiSendFlag)
		{
			SpiSendFlag = 0;
			UART_BMM_Rx();			//UART Recive Continue
			SPI_BMM_Master();		//SPI Send Memory
		}

		if(SpiTxFlag)
		{
			SpiTxFlag = 0;
			SPI_BMM_Slave();		//SPI Slave Mode
		}

		
		//SPI接收 -> SPI BMM -> UART BMM -> UART发送
		if(SpiRxFlag)
		{
			SpiRxFlag = 0;
			s2uFlag = 1;
			M2M_SPI_UART();			//SPI Memory -> UART Memory
		}

		if(UartSendFlag)
		{
			UartSendFlag = 0;
			SPI_BMM_Slave();		//SPI Slave Mode
			UART_BMM_Tx();			//UART Send Memory
		}
	}
}



