/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"STC8A_PCA.h"

bit		B_Capture0,B_Capture1,B_Capture2,B_Capture3;
u8		PCA0_mode,PCA1_mode,PCA2_mode,PCA3_mode;
u16		CCAP0_tmp,PCA_Timer0;
u16		CCAP1_tmp,PCA_Timer1;
u16		CCAP2_tmp,PCA_Timer2;
u16		CCAP3_tmp,PCA_Timer3;

//========================================================================
// ����: UpdatePcaPwm(u8 PCA_id, u16 pwm_value)
// ����: ����PWMֵ. 
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA_Counter
//		 pwm_value: pwmֵ, ���ֵ������͵�ƽ��ʱ��.
// ����: none.
// �汾: V1.0, 2012-11-22
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
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
		PCA_PWM3 = (PCA_PWM3 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP3H = (u8)pwm_value;
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	}
}

//========================================================================
// ����: void	PCALevelSet(u8 PCA_id, u8 PCA_Level)
// ����: ����PWMֵ. 
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA3
//       PCA_Level: PWM�̶�����ߵ�ƽ, 0: �͵�ƽ, 1: �ߵ�ƽ.
// ����: none.
// �汾: V1.0, 2021-6-10
//========================================================================
void	PCALevelSet(u8 PCA_id, u8 PCA_Level)
{
	if(PCA_id == PCA0)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM0 &= ~0x32; //PWM�̶�����ߵ�ƽ
			CCAP0H = 0x00;
		}
		else
		{
			PCA_PWM0 |= 0x32; //PWM�̶�����͵�ƽ
			CCAP0H = 0xff;
		}
	}
	else if(PCA_id == PCA1)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM1 &= ~0x32; //PWM�̶�����ߵ�ƽ
			CCAP1H = 0x00;
		}
		else
		{
			PCA_PWM1 |= 0x32; //PWM�̶�����͵�ƽ
			CCAP1H = 0xff;
		}
	}
	else if(PCA_id == PCA2)
	{
		if(PCA_Level == 1)
		{
			PCA_PWM2 &= ~0x32; //PWM�̶�����ߵ�ƽ
			CCAP2H = 0x00;
		}
		else
		{
			PCA_PWM2 |= 0x32; //PWM�̶�����͵�ƽ
			CCAP2H = 0xff;
		}
	}
	else if(PCA_id == PCA3)
	{
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
		if(PCA_Level == 1)
		{
			PCA_PWM3 &= ~0x32; //PWM�̶�����ߵ�ƽ
			CCAP3H = 0x00;
		}
		else
		{
			PCA_PWM3 |= 0x32; //PWM�̶�����͵�ƽ
			CCAP3H = 0xff;
		}
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	}
}

//========================================================================
// ����: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// ����: PCA��ʼ������.
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA3,PCA_Counter
//		 PCAx: �ṹ����,��ο�PCA.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id == PCA_Counter)			//���ù���Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//ѡ��ʱ��Դ
		if(PCAx->PCA_RUN == ENABLE)	CR = 1;
		return;
	}

	if(PCA_id == PCA0)
	{
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM���

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (u8)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAPxL
		CCAP0H = (u8)(CCAP0_tmp >> 8);	//��дCCAPxH
	}
	if(PCA_id == PCA1)
	{
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (u8)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAPxL
		CCAP1H = (u8)(CCAP1_tmp >> 8);	//��дCCAPxH
	}
	if(PCA_id == PCA2)
	{
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (u8)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAPxL
		CCAP2H = (u8)(CCAP2_tmp >> 8);	//��дCCAPxH
	}
	if(PCA_id == PCA3)
	{
		EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
		PCA_PWM3  = (PCA_PWM3 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer3 = PCAx->PCA_Value;
		B_Capture3 = 0;
		CCAP3_tmp = PCA_Timer3;
		CCAP3L = (u8)CCAP3_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAPxL
		CCAP3H = (u8)(CCAP3_tmp >> 8);	//��дCCAPxH
		EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	}
}
