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

���4·�仯��PWM�ź�, ����"������"������.
PWM0 P1.7 Ϊ8λPWM.
PWM1 P1.6 Ϊ7λPWM.
PWM2 P1.5 Ϊ6λPWM, ���PWM 1����, ����͵�ƽ1����, ����ߵ�ƽ1����, ����ѭ��.
PWM3 P1.4 Ϊ10λPWM.

����ʱ, ѡ��ʱ�� 24MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/

u16	pwm0,pwm1,pwm2,pwm3;
bit	B_PWM0_Dir,B_PWM1_Dir,B_PWM2_Dir,B_PWM3_Dir;	//����, 0Ϊ+, 1Ϊ-.

/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	P1_MODE_IO_PU(GPIO_Pin_HIGH);			//P1.4~P1.7 ����Ϊ׼˫���
	PCA_SW(PCA_P12_P17_P16_P15_P14);	//PCA_P12_P17_P16_P15_P14,PCA_P22_P23_P24_P25_P26,PCA_P74_P70_P71_P72_P73,PCA_P35_P33_P32_P31_P30
}

/******************** PCA���� ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_8bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 128 << 8;				//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_7bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 64 << 8;					//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_6bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 32 << 8;					//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA2,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_10bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 256 << 8;					//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA3,&PCA_InitStructure);

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = ENABLE;				//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);			//���ù���Counter

	NVIC_PCA_Init(PCA_Counter,PCA_Mode_PWM,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_PWM,Priority_0);
	NVIC_PCA_Init(PCA1,PCA_Mode_PWM,Priority_0);
	NVIC_PCA_Init(PCA2,PCA_Mode_PWM,Priority_0);
	NVIC_PCA_Init(PCA3,PCA_Mode_PWM,Priority_0);
}


/******************** main **************************/
void main(void)
{
	GPIO_config();
	PCA_config();
	pwm0 = 128;
	pwm1 = 64;
	pwm2 = 32;
	pwm3 = 512;
	B_PWM0_Dir = 0;
	B_PWM1_Dir = 0;
	B_PWM2_Dir = 0;
	B_PWM3_Dir = 0;

	UpdatePcaPwm(PCA0,pwm0);
	UpdatePcaPwm(PCA1,pwm1);
	UpdatePcaPwm(PCA2,pwm2);
	UpdatePcaPwm(PCA3,pwm3);
//	EA = 1;
	
	while (1)
	{
		delay_ms(10);

		if(B_PWM0_Dir)
		{
			if(--pwm0 <= 16)	B_PWM0_Dir = 0;	//8λPWM
		}
		else	if(++pwm0 >= 240)	B_PWM0_Dir = 1;	//8λPWM
		UpdatePcaPwm(PCA0,pwm0);

		if(B_PWM1_Dir)
		{
			if(--pwm1 <= 8)		B_PWM1_Dir = 0;	//7λPWM
		}
		else	if(++pwm1 >= 120)	B_PWM1_Dir = 1;	//7λPWM
		UpdatePcaPwm(PCA1,pwm1);

//		if(B_PWM2_Dir)
//		{
//			if(--pwm2 <= 4)		B_PWM2_Dir = 0;	//6λPWM
//		}
//		else	if(++pwm2 >= 60)	B_PWM2_Dir = 1;	//6λPWM
//		UpdatePcaPwm(PCA2,pwm2);

		if(pwm2 >= 300)
		{
			pwm2 = 0;
		}
		else	if(pwm2 >= 200)
		{
			PCALevelSet(PCA2,1);	//PWM_ID, ǿ������ߵ�ƽ
		}
		else	if(pwm2 >= 100)
		{
			PCALevelSet(PCA2,0);	//PWM_ID, ǿ������͵�ƽ
		}
		else
		{
			UpdatePcaPwm(PCA2,32);//PWM_ID, ���PWM
		}
		pwm2++;
		
		if(B_PWM3_Dir)
		{
			if(--pwm3 <= 24)		B_PWM3_Dir = 0;	//10λPWM
		}
		else	if(++pwm3 >= 1000)	B_PWM3_Dir = 1;	//10λPWM
		UpdatePcaPwm(PCA3,pwm3);
	}
}



