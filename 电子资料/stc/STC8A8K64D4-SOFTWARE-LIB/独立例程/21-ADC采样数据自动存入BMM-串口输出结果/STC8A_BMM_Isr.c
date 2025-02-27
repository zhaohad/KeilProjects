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
	if(BMM_ADC_STA & 0x01)	//AD转换完成
	{
		BMM_ADC_STA &= ~0x01;	//清标志位
		BmmADCFlag = 1;
	}

	P_SW2 = store;
}
