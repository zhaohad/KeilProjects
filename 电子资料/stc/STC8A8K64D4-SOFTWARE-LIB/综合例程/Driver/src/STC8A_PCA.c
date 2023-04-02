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

#include	"STC8A_PCA.h"

bit		B_Capture0,B_Capture1,B_Capture2,B_Capture3;
u8		PCA0_mode,PCA1_mode,PCA2_mode,PCA3_mode;
u16		CCAP0_tmp,PCA_Timer0;
u16		CCAP1_tmp,PCA_Timer1;
u16		CCAP2_tmp,PCA_Timer2;
u16		CCAP3_tmp,PCA_Timer3;

//========================================================================
// 函数: UpdatePcaPwm(u8 PCA_id, u16 pwm_value)
// 描述: 更新PWM值. 
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA_Counter
//		 pwm_value: pwm值, 这个值是输出低电平的时间.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void	UpdatePcaPwm(u8 PCA_id, u16 pwm_value)
{
	if(PCA_id == PCA0)
	{
		PCA_PWM0 = (PCA_PWM0 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP0H = (u8)pwm_value;
	}
	else if(PCA_id == PCA1)
	{
		PCA_PWM1 = (PCA_PWM1 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP1H = (u8)pwm_value;
	}
	else if(PCA_id == PCA2)
	{
		PCA_PWM2 = (PCA_PWM2 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP2H = (u8)pwm_value;
	}
	else if(PCA_id == PCA3)
	{
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
		PCA_PWM3 = (PCA_PWM3 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP3H = (u8)pwm_value;
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	}
}

//========================================================================
// 函数: void	PCALevelSet(u8 PCA_id, u8 PCA_Level)
// 描述: 更新PWM值. 
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA3
//       PCA_Level: PWM固定输出高电平, 0: 低电平, 1: 高电平.
// 返回: none.
// 版本: V1.0, 2021-6-10
//========================================================================
void	PCALevelSet(u8 PCA_id, u8 PCA_Level)
{
	if(PCA_id == PCA0)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM0 &= ~0x32; //PWM固定输出高电平
			CCAP0H = 0x00;
		}
		else
		{
			PCA_PWM0 |= 0x32; //PWM固定输出低电平
			CCAP0H = 0xff;
		}
	}
	else if(PCA_id == PCA1)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM1 &= ~0x32; //PWM固定输出高电平
			CCAP1H = 0x00;
		}
		else
		{
			PCA_PWM1 |= 0x32; //PWM固定输出低电平
			CCAP1H = 0xff;
		}
	}
	else if(PCA_id == PCA2)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM2 &= ~0x32; //PWM固定输出高电平
			CCAP2H = 0x00;
		}
		else
		{
			PCA_PWM2 |= 0x32; //PWM固定输出低电平
			CCAP2H = 0xff;
		}
	}
	else if(PCA_id == PCA3)
	{
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
		if(PCA_Level == 1)
		{
			PCA_PWM3 &= ~0x32; //PWM固定输出高电平
			CCAP3H = 0x00;
		}
		else
		{
			PCA_PWM3 |= 0x32; //PWM固定输出低电平
			CCAP3H = 0xff;
		}
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	}
}

//========================================================================
// 函数: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// 描述: PCA初始化程序.
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA3,PCA_Counter
//		 PCAx: 结构参数,请参考PCA.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id == PCA_Counter)			//设置公用Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//选择时钟源
		if(PCAx->PCA_RUN == ENABLE)	CR = 1;
		return;
	}

	if(PCA_id == PCA0)
	{
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM宽度

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (u8)CCAP0_tmp;			//将影射寄存器写入捕获寄存器，先写CCAPxL
		CCAP0H = (u8)(CCAP0_tmp >> 8);	//后写CCAPxH
	}
	if(PCA_id == PCA1)
	{
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (u8)CCAP1_tmp;			//将影射寄存器写入捕获寄存器，先写CCAPxL
		CCAP1H = (u8)(CCAP1_tmp >> 8);	//后写CCAPxH
	}
	if(PCA_id == PCA2)
	{
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (u8)CCAP2_tmp;			//将影射寄存器写入捕获寄存器，先写CCAPxL
		CCAP2H = (u8)(CCAP2_tmp >> 8);	//后写CCAPxH
	}
	if(PCA_id == PCA3)
	{
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
		PCA_PWM3  = (PCA_PWM3 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer3 = PCAx->PCA_Value;
		B_Capture3 = 0;
		CCAP3_tmp = PCA_Timer3;
		CCAP3L = (u8)CCAP3_tmp;			//将影射寄存器写入捕获寄存器，先写CCAPxL
		CCAP3H = (u8)(CCAP3_tmp >> 8);	//后写CCAPxH
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	}
}
