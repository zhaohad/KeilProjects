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
#include "STC8A_SPI.h"
#include "STC8A_LCM.h"

//========================================================================
// 函数: BMM_ISR_Handler
// 描述: BMM中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2021-05-25
//========================================================================
void BMM_ISR_Handler (void) interrupt 13
{
	char store;
	
	store = P_SW2;
	P_SW2 |= 0x80;		//使能扩展SFR(XSFR)访问

	// TODO: 在此处添加用户代码
	
	//----------- BMM ADC --------------
	if(BMM_ADC_STA & 0x01)	//AD转换完成
	{
		BMM_ADC_STA &= ~0x01;	//清标志位
		BmmADCFlag = 1;
	}

	//----------- BMM M2M --------------
	if(BMM_M2M_STA & 0x01)	//M2M传输完成
	{
		BMM_M2M_STA &= ~0x01;	//清标志位
		BmmM2MFlag = 1;
		if(u2sFlag)
		{
			u2sFlag = 0;
			SpiSendFlag = 1;
		}
		if(s2uFlag)
		{
			s2uFlag = 0;
			UartSendFlag = 1;
		}
	}

	//---------- BMM UART1 -------------
	if (BMM_UR1T_STA & 0x01)	//发送完成
	{
		BMM_UR1T_STA &= ~0x01;	//清标志位
		BmmTx1Flag = 1;
	}
	if (BMM_UR1T_STA & 0x04)	//数据覆盖
	{
		BMM_UR1T_STA &= ~0x04;	//清标志位
	}
	
	if (BMM_UR1R_STA & 0x01)	//接收完成
	{
		BMM_UR1R_STA &= ~0x01;	//清标志位
		BmmRx1Flag = 1;
	}
	if (BMM_UR1R_STA & 0x02)	//数据丢弃
	{
		BMM_UR1R_STA &= ~0x02;	//清标志位
	}
	//---------- BMM UART2 -------------
	if (BMM_UR2T_STA & 0x01)	//发送完成
	{
		BMM_UR2T_STA &= ~0x01;	//清标志位
		BmmTx2Flag = 1;
	}
	if (BMM_UR2T_STA & 0x04)	//数据覆盖
	{
		BMM_UR2T_STA &= ~0x04;	//清标志位
	}
	
	if (BMM_UR2R_STA & 0x01)	//接收完成
	{
		BMM_UR2R_STA &= ~0x01;	//清标志位
		BmmRx2Flag = 1;
	}
	if (BMM_UR2R_STA & 0x02)	//数据丢弃
	{
		BMM_UR2R_STA &= ~0x02;	//清标志位
	}
	//---------- BMM UART3 -------------
	if (BMM_UR3T_STA & 0x01)	//发送完成
	{
		BMM_UR3T_STA &= ~0x01;	//清标志位
		BmmTx3Flag = 1;
	}
	if (BMM_UR3T_STA & 0x04)	//数据覆盖
	{
		BMM_UR3T_STA &= ~0x04;	//清标志位
	}
	
	if (BMM_UR3R_STA & 0x01)	//接收完成
	{
		BMM_UR3R_STA &= ~0x01;	//清标志位
		BmmRx3Flag = 1;
	}
	if (BMM_UR3R_STA & 0x02)	//数据丢弃
	{
		BMM_UR3R_STA &= ~0x02;	//清标志位
	}
	//---------- BMM UART4 -------------
	if (BMM_UR4T_STA & 0x01)	//发送完成
	{
		BMM_UR4T_STA &= ~0x01;	//清标志位
		BmmTx4Flag = 1;
	}
	if (BMM_UR4T_STA & 0x04)	//数据覆盖
	{
		BMM_UR4T_STA &= ~0x04;	//清标志位
	}
	
	if (BMM_UR4R_STA & 0x01)	//接收完成
	{
		BMM_UR4R_STA &= ~0x01;	//清标志位
		BmmRx4Flag = 1;
	}
	if (BMM_UR4R_STA & 0x02)	//数据丢弃
	{
		BMM_UR4R_STA &= ~0x02;	//清标志位
	}

	//---------- BMM SPI -------------
	if(BMM_SPI_STA & 0x01)	//通信完成
	{
		BMM_SPI_STA &= ~0x01;	//清标志位
		if(SPCTL & 0x10) 
		{ //主机模式
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //从机模式
			SpiRxFlag = 1;
		}
	}
	if(BMM_SPI_STA & 0x02)	//数据丢弃
	{
		BMM_SPI_STA &= ~0x02;	//清标志位
	}
	if(BMM_SPI_STA & 0x04)	//数据覆盖
	{
		BMM_SPI_STA &= ~0x04;	//清标志位
	}

	//------------- LCM --------------
	if(LCMIFSTA & 0x01)
	{
		LCMIFSTA = 0x00;
		LcmFlag = 0;
	}
	
	//---------- BMM LCM -------------
	if(BMM_LCM_STA & 0x01)
	{
		if(BmmLcmFlag)
		{
			BmmLcmFlag = 0;
			BMM_LCM_CR = 0;
		}
		else
		{
			LCM_Cnt--;
			if(LCM_Cnt == 0)
			{
				BMM_LCM_CR = 0;
				LCD_CS=1;
			}
			else
			{
				BMM_LCM_CR = 0xa0;	//Write dat
			}
		}
		BMM_LCM_STA = 0;		//清标志位
	}
	
	P_SW2 = store;
}
