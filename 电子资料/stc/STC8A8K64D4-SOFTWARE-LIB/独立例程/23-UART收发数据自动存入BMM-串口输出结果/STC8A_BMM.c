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

#include "STC8A_BMM.h"
#include "STC8A_UART.h"

//========================================================================
// 函数: void BMM_ADC_Inilize(BMM_ADC_InitTypeDef *BMM)
// 描述: BMM ADC 初始化程序.
// 参数: BMM: 结构参数,请参考BMM.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void BMM_ADC_Inilize(BMM_ADC_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	BMM_ADC_STA = 0x00;
	BMM_ADC_CHSW = BMM->BMM_Channel;
	BMM_ADC_RXA = BMM->BMM_Buffer;
	BMM_ADC_CFG2 = BMM->BMM_Times;

	if(BMM->BMM_Enable == ENABLE)		BMM_ADC_CR |= 0x80;	//使能ADC BMM
	else BMM_ADC_CR &= ~0x80;	//禁止ADC BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void BMM_M2M_Inilize(BMM_M2M_InitTypeDef *BMM)
// 描述: BMM M2M 初始化程序.
// 参数: BMM: 结构参数,请参考BMM.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void BMM_M2M_Inilize(BMM_M2M_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	BMM_M2M_STA = 0x00;
	BMM_M2M_RXA = BMM->BMM_Rx_Buffer;
	BMM_M2M_TXA = BMM->BMM_Tx_Buffer;
	BMM_M2M_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_SRC_Dir == M2M_ADDR_DEC)		BMM_M2M_CFG |= 0x20;	//数据读完后地址自减
	else BMM_M2M_CFG &= ~0x20;	//数据读完后地址自减
	if(BMM->BMM_DEST_Dir == M2M_ADDR_DEC)		BMM_M2M_CFG |= 0x10;	//数据写入后地址自减
	else BMM_M2M_CFG &= ~0x10;	//数据写入后地址自减
	
	if(BMM->BMM_Enable == ENABLE)		BMM_M2M_CR |= 0x80;	//使能M2M BMM
	else BMM_M2M_CR &= ~0x80;	//禁止M2M BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void BMM_SPI_Inilize(BMM_SPI_InitTypeDef *BMM)
// 描述: BMM SPI 初始化程序.
// 参数: BMM: 结构参数,请参考BMM.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void BMM_SPI_Inilize(BMM_SPI_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	BMM_SPI_STA = 0x00;
	BMM_SPI_RXA = BMM->BMM_Rx_Buffer;
	BMM_SPI_TXA = BMM->BMM_Tx_Buffer;
	BMM_SPI_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_SS_Sel <= SPI_SS_P35) BMM_SPI_CFG2 = (BMM_SPI_CFG2 & 0xfc) | BMM->BMM_SS_Sel;	//自动控制SS脚选择

	if(BMM->BMM_Tx_Enable == ENABLE)		BMM_SPI_CFG |= 0x40;	//使能SPI发送数据
	else BMM_SPI_CFG &= ~0x40;	//禁止SPI发送数据
	
	if(BMM->BMM_Rx_Enable == ENABLE)		BMM_SPI_CFG |= 0x20;	//使能SPI接收数据
	else BMM_SPI_CFG &= ~0x20;	//禁止SPI接收数据
	
	if(BMM->BMM_AUTO_SS == ENABLE)		BMM_SPI_CFG2 |= 0x04;	//使能SS自动控制
	else BMM_SPI_CFG2 &= ~0x04;	//禁止SS自动控制
	
	if(BMM->BMM_Enable == ENABLE)		BMM_SPI_CR |= 0x80;	//使能SPI BMM
	else BMM_SPI_CR &= ~0x80;	//禁止SPI BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void BMM_UART_Inilize(u8 UARTx, BMM_UART_InitTypeDef *BMM)
// 描述: BMM UART 初始化程序.
// 参数: UARTx: UART组号, BMM: 结构参数,请参考BMM.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void BMM_UART_Inilize(u8 UARTx, BMM_UART_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
#ifdef UART1
	if(UARTx == UART1)
	{
		BMM_UR1T_STA = 0x00;
		BMM_UR1R_STA = 0x00;
		BMM_UR1T_AMT = BMM->BMM_TX_Length;
		BMM_UR1T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR1R_AMT = BMM->BMM_RX_Length;
		BMM_UR1R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR1T_CR |= 0x80;	//使能ADC BMM
		else BMM_UR1T_CR &= ~0x80;	//禁止ADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR1R_CR |= 0x80;	//使能ADC BMM
		else BMM_UR1R_CR &= ~0x80;	//禁止ADC BMM
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		BMM_UR2T_STA = 0x00;
		BMM_UR2R_STA = 0x00;
		BMM_UR2T_AMT = BMM->BMM_TX_Length;
		BMM_UR2T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR2R_AMT = BMM->BMM_RX_Length;
		BMM_UR2R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR2T_CR |= 0x80;	//使能ADC BMM
		else BMM_UR2T_CR &= ~0x80;	//禁止ADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR2R_CR |= 0x80;	//使能ADC BMM
		else BMM_UR2R_CR &= ~0x80;	//禁止ADC BMM
	}
#endif
#ifdef UART3
	if(UARTx == UART3)
	{
		BMM_UR3T_STA = 0x00;
		BMM_UR3R_STA = 0x00;
		BMM_UR3T_AMT = BMM->BMM_TX_Length;
		BMM_UR3T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR3R_AMT = BMM->BMM_RX_Length;
		BMM_UR3R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR3T_CR |= 0x80;	//使能ADC BMM
		else BMM_UR3T_CR &= ~0x80;	//禁止ADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR3R_CR |= 0x80;	//使能ADC BMM
		else BMM_UR3R_CR &= ~0x80;	//禁止ADC BMM
	}
#endif
#ifdef UART4
	if(UARTx == UART4)
	{
		BMM_UR4T_STA = 0x00;
		BMM_UR4R_STA = 0x00;
		BMM_UR4T_AMT = BMM->BMM_TX_Length;
		BMM_UR4T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR4R_AMT = BMM->BMM_RX_Length;
		BMM_UR4R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR4T_CR |= 0x80;	//使能ADC BMM
		else BMM_UR4T_CR &= ~0x80;	//禁止ADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR4R_CR |= 0x80;	//使能ADC BMM
		else BMM_UR4R_CR &= ~0x80;	//禁止ADC BMM
	}
#endif
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void BMM_LCM_Inilize(BMM_LCM_InitTypeDef *BMM)
// 描述: BMM LCM 初始化程序.
// 参数: BMM: 结构参数,请参考BMM.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void BMM_LCM_Inilize(BMM_LCM_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	BMM_LCM_STA = 0x00;
	BMM_LCM_RXA = BMM->BMM_Rx_Buffer;
	BMM_LCM_TXA = BMM->BMM_Tx_Buffer;
	BMM_LCM_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_Enable == ENABLE)		BMM_LCM_CR |= 0x80;	//使能LCM BMM
	else BMM_LCM_CR &= ~0x80;	//禁止LCM BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}
