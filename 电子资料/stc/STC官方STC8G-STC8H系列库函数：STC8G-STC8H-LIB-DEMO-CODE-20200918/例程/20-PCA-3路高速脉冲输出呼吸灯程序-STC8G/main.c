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
#include	"GPIO.h"
#include	"PCA.h"
#include	"delay.h"

/*************   ����˵��   ***************

�����̻���STC8G1K08-20PIN���б�д���ԣ�STC8Gϵ��оƬ��ͨ�òο�.

���3·�仯��PWM�ź�, ����"������"������.

PCA0, PCA1, PCA2 Ϊ16λPWM.

����ʱ, ѡ��ʱ�� 24MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/

u16	pwm0,pwm1,pwm2;
bit	B_PWM0_Dir,B_PWM1_Dir,B_PWM2_Dir;	//����, 0Ϊ+, 1Ϊ-.

/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_All;			//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//��ʼ��

	GPIO_InitStructure.Pin  = GPIO_Pin_7;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��
}

/******************** PCA���� ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_IoUse    = PCA_P12_P11_P10_P37;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//ENABLE, DISABLE
	PCA_InitStructure.PCA_Polity   = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	PCA_InitStructure.PCA_RUN      = DISABLE;				//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);			//���ù���Counter

	PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;					//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 65535;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;					//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 65535;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;					//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 65535;			//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA2,&PCA_InitStructure);
}


/******************** task A **************************/
void main(void)
{
	GPIO_config();
	PCA_config();
	pwm0 = (PWM_DUTY / 4 * 1);	//��PWMһ����ֵ
	pwm1 = (PWM_DUTY / 4 * 2);
	pwm2 = (PWM_DUTY / 4 * 3);
	B_PWM0_Dir = 0;
	B_PWM1_Dir = 0;
	B_PWM2_Dir = 0;

	PWMn_Update(PCA0,pwm0);
	PWMn_Update(PCA1,pwm1);
	PWMn_Update(PCA2,pwm2);
	EA = 1;
	
	while (1)
	{
		delay_ms(1);

		if(B_PWM0_Dir)
		{
				if(--pwm0 <= PWM_HIGH_MIN)	B_PWM0_Dir = 0;
		}
		else	if(++pwm0 >= PWM_HIGH_MAX)	B_PWM0_Dir = 1;
		PWMn_Update(PCA0,pwm0);

		if(B_PWM1_Dir)
		{
				if(--pwm1 <= PWM_HIGH_MIN)		B_PWM1_Dir = 0;
		}
		else	if(++pwm1 >= PWM_HIGH_MAX)	B_PWM1_Dir = 1;
		PWMn_Update(PCA1,pwm1);

		if(B_PWM2_Dir)
		{
				if(--pwm2 <= PWM_HIGH_MIN)		B_PWM2_Dir = 0;
		}
		else	if(++pwm2 >= PWM_HIGH_MAX)	B_PWM2_Dir = 1;
		PWMn_Update(PCA2,pwm2);
	}
}



