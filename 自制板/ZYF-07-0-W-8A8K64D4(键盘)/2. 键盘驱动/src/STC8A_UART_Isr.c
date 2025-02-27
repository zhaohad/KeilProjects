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

#include "STC8A_UART.h"
#include "typedef.h"
#include "global.h"

//========================================================================
// 函数: UART1_ISR_Handler
// 描述: UART1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================

CB_1Byte g_onURAT_1Byte_CB = NULL;
#ifdef UART1
void UART1_ISR_Handler (void) interrupt UART1_VECTOR
{
	if(RI)
	{
		xdata u8 buf;
		RI = 0;
		/*if(COM1.B_RX_OK == 0)
		{
			if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
			RX1_Buffer[COM1.RX_Cnt++] = SBUF;
			COM1.RX_TimeOut = TimeOutSet1;
		}*/
		buf = SBUF;
		if (g_onURAT_1Byte_CB != NULL) {
			g_onURAT_1Byte_CB(buf);
		}
	}

	if(TI)
	{
		P00 = 0;
		TI = 0;
		COM1.B_TX_busy = 0;
		
//		if(COM1.TX_read != COM1.TX_write)
//		{
//		 	SBUF = TX1_Buffer[COM1.TX_read];
//			if(++COM1.TX_read >= COM_TX1_Lenth)		COM1.TX_read = 0;
//		}
//		else	COM1.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART2_ISR_Handler
// 描述: UART2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART2
void UART2_ISR_Handler (void) interrupt UART2_VECTOR
{
	if(RI2)
	{
		u8 d;
		CLR_RI2();
		/*if(COM2.B_RX_OK == 0)
		{
			if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
			RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
			COM2.RX_TimeOut = TimeOutSet2;
		}*/
		d = S2BUF;
		on_ch9329_dat_rec(d);
	}

	if(TI2)
	{
		CLR_TI2();
		COM2.B_TX_busy = 0;
		
//		if(COM2.TX_read != COM2.TX_write)
//		{
//		 	S2BUF = TX2_Buffer[COM2.TX_read];
//			if(++COM2.TX_read >= COM_TX2_Lenth)		COM2.TX_read = 0;
//		}
//		else	COM2.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART3_ISR_Handler
// 描述: UART3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART3
void UART3_ISR_Handler (void) interrupt UART3_VECTOR
{
	if(RI3)
	{
		xdata u8 buf;
		CLR_RI3();
		buf = S3BUF;
		if (g_onURAT_1Byte_CB != NULL) {
			g_onURAT_1Byte_CB(buf);
		}
		/*CLR_RI3();
		if(COM3.B_RX_OK == 0)
		{
			if(COM3.RX_Cnt >= COM_RX3_Lenth)	COM3.RX_Cnt = 0;
			RX3_Buffer[COM3.RX_Cnt++] = S3BUF;
			COM3.RX_TimeOut = TimeOutSet3;
		}*/
	}

	if(TI3)
	{
		CLR_TI3();
		COM3.B_TX_busy = 0;
		
//		if(COM3.TX_read != COM3.TX_write)
//		{
//		 	S3BUF = TX3_Buffer[COM3.TX_read];
//			if(++COM3.TX_read >= COM_TX3_Lenth)		COM3.TX_read = 0;
//		}
//		else	COM3.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART4_ISR_Handler
// 描述: UART4中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART4
void UART4_ISR_Handler (void) interrupt UART4_VECTOR
{
	if(RI4)
	{
		CLR_RI4();
		if(COM4.B_RX_OK == 0)
		{
			if(COM4.RX_Cnt >= COM_RX4_Lenth)	COM4.RX_Cnt = 0;
			RX4_Buffer[COM4.RX_Cnt++] = S4BUF;
			COM4.RX_TimeOut = TimeOutSet4;
		}
	}

	if(TI4)
	{
		CLR_TI4();
		COM4.B_TX_busy = 0;
		
//		if(COM4.TX_read != COM4.TX_write)
//		{
//		 	S4BUF = TX4_Buffer[COM4.TX_read];
//			if(++COM4.TX_read >= COM_TX4_Lenth)		COM4.TX_read = 0;
//		}
//		else	COM4.B_TX_busy = 0;
	}
}
#endif
