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

#include	"config.h"
#include	"STC8A_PCA.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Delay.h"
#include	"STC8A_Switch.h"

/*************   ����˵��   ***************

PCA���4·��������.

����ʱ, ѡ��ʱ�� 24MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	P2_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_HIGH);			//P2.3~P2.7 ����Ϊ׼˫���
	PCA_SW(PCA_P22_P23_P24_P25_P26);	//PCA_P12_P17_P16_P15_P14,PCA_P22_P23_P24_P25_P26,PCA_P74_P70_P71_P72_P73,PCA_P35_P33_P32_P31_P30
}

/******************** PCA���� ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0xffff;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x7fff;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x3fff;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA2,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x1fff;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA3,&PCA_InitStructure);

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = ENABLE;				//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);			//���ù���Counter

	NVIC_PCA_Init(PCA_Counter,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA1,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA2,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA3,PCA_Mode_HighPulseOutput,Priority_0);
}

/******************** main **************************/
void main(void)
{
	GPIO_config();
	PCA_config();
	EA = 1;
	
	while (1)
	{
	}
}



