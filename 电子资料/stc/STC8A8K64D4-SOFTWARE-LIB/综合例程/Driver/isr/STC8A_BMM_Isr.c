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

#include "STC8A_BMM.h"
#include "STC8A_SPI.h"
#include "STC8A_LCM.h"

//========================================================================
// ����: BMM_ISR_Handler
// ����: BMM�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-05-25
//========================================================================
void BMM_ISR_Handler (void) interrupt 13
{
	char store;
	
	store = P_SW2;
	P_SW2 |= 0x80;		//ʹ����չSFR(XSFR)����

	// TODO: �ڴ˴�����û�����
	
	//----------- BMM ADC --------------
	if(BMM_ADC_STA & 0x01)	//ADת�����
	{
		BMM_ADC_STA &= ~0x01;	//���־λ
		BmmADCFlag = 1;
	}

	//----------- BMM M2M --------------
	if(BMM_M2M_STA & 0x01)	//M2M�������
	{
		BMM_M2M_STA &= ~0x01;	//���־λ
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
	if (BMM_UR1T_STA & 0x01)	//�������
	{
		BMM_UR1T_STA &= ~0x01;	//���־λ
		BmmTx1Flag = 1;
	}
	if (BMM_UR1T_STA & 0x04)	//���ݸ���
	{
		BMM_UR1T_STA &= ~0x04;	//���־λ
	}
	
	if (BMM_UR1R_STA & 0x01)	//�������
	{
		BMM_UR1R_STA &= ~0x01;	//���־λ
		BmmRx1Flag = 1;
	}
	if (BMM_UR1R_STA & 0x02)	//���ݶ���
	{
		BMM_UR1R_STA &= ~0x02;	//���־λ
	}
	//---------- BMM UART2 -------------
	if (BMM_UR2T_STA & 0x01)	//�������
	{
		BMM_UR2T_STA &= ~0x01;	//���־λ
		BmmTx2Flag = 1;
	}
	if (BMM_UR2T_STA & 0x04)	//���ݸ���
	{
		BMM_UR2T_STA &= ~0x04;	//���־λ
	}
	
	if (BMM_UR2R_STA & 0x01)	//�������
	{
		BMM_UR2R_STA &= ~0x01;	//���־λ
		BmmRx2Flag = 1;
	}
	if (BMM_UR2R_STA & 0x02)	//���ݶ���
	{
		BMM_UR2R_STA &= ~0x02;	//���־λ
	}
	//---------- BMM UART3 -------------
	if (BMM_UR3T_STA & 0x01)	//�������
	{
		BMM_UR3T_STA &= ~0x01;	//���־λ
		BmmTx3Flag = 1;
	}
	if (BMM_UR3T_STA & 0x04)	//���ݸ���
	{
		BMM_UR3T_STA &= ~0x04;	//���־λ
	}
	
	if (BMM_UR3R_STA & 0x01)	//�������
	{
		BMM_UR3R_STA &= ~0x01;	//���־λ
		BmmRx3Flag = 1;
	}
	if (BMM_UR3R_STA & 0x02)	//���ݶ���
	{
		BMM_UR3R_STA &= ~0x02;	//���־λ
	}
	//---------- BMM UART4 -------------
	if (BMM_UR4T_STA & 0x01)	//�������
	{
		BMM_UR4T_STA &= ~0x01;	//���־λ
		BmmTx4Flag = 1;
	}
	if (BMM_UR4T_STA & 0x04)	//���ݸ���
	{
		BMM_UR4T_STA &= ~0x04;	//���־λ
	}
	
	if (BMM_UR4R_STA & 0x01)	//�������
	{
		BMM_UR4R_STA &= ~0x01;	//���־λ
		BmmRx4Flag = 1;
	}
	if (BMM_UR4R_STA & 0x02)	//���ݶ���
	{
		BMM_UR4R_STA &= ~0x02;	//���־λ
	}

	//---------- BMM SPI -------------
	if(BMM_SPI_STA & 0x01)	//ͨ�����
	{
		BMM_SPI_STA &= ~0x01;	//���־λ
		if(SPCTL & 0x10) 
		{ //����ģʽ
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //�ӻ�ģʽ
			SpiRxFlag = 1;
		}
	}
	if(BMM_SPI_STA & 0x02)	//���ݶ���
	{
		BMM_SPI_STA &= ~0x02;	//���־λ
	}
	if(BMM_SPI_STA & 0x04)	//���ݸ���
	{
		BMM_SPI_STA &= ~0x04;	//���־λ
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
		BMM_LCM_STA = 0;		//���־λ
	}
	
	P_SW2 = store;
}
