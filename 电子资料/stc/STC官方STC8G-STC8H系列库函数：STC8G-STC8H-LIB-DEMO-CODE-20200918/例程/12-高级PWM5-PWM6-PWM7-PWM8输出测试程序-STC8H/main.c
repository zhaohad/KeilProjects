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
#include	"timer.h"
#include	"GPIO.h"
#include	"PWM.h"

/*************	����˵��	**************

�����̻���STC8H8K64UΪ����оƬ��ʵ����8���б�д���ԣ�STC8Hϵ��оƬ��ͨ�òο�.

�߼�PWM��ʱ�� PWM5,PWM6,PWM7,PWM8 ÿ��ͨ�����ɶ���ʵ��PWM���.

4��ͨ��PWM������Ҫ���ö�Ӧ����ڣ���ͨ��ʾ�����۲�������ź�.

PWM���ں�ռ�ձȿ����Զ������ã���߿ɴ�65535.

����ʱ, ѡ��ʱ�� 24MHZ (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/

PWMx_Duty PWMB_Duty;

/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



/************************ IO������ ****************************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_All;			//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
}

/************************ ��ʱ������ ****************************/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	TIM_InitStructure.TIM_Interrupt = ENABLE;					//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);		//�ж�Ƶ��, 1000��/��
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);					//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
}

/***************  ���ڳ�ʼ������ *****************/
void	PWM_config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMx_InitStructure.PWM5_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM6_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM7_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM8_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2

	PWMx_InitStructure.PWM5_SetPolity  = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	
	PWMx_InitStructure.PWM_Period   = 2047;							//����ʱ��,   0~65535
	PWMx_InitStructure.PWM5_Duty    = PWMB_Duty.PWM5_Duty;	//PWM5ռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM6_Duty    = PWMB_Duty.PWM6_Duty;	//PWM6ռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM7_Duty    = PWMB_Duty.PWM7_Duty;	//PWM7ռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM8_Duty    = PWMB_Duty.PWM8_Duty;	//PWM8ռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
	
	PWMx_InitStructure.PWM_EnoSelect   = ENO5P | ENO6P | ENO7P | ENO8P;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWMx_InitStructure.PWM_PS_SW       = PWM5_SW_P20| PWM6_SW_P21 | PWM7_SW_P22 | PWM8_SW_P23;	//�л��˿�,		PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74
																											//						PWM6_SW_P21,PWM6_SW_P54,PWM6_SW_P01,PWM6_SW_P75
																											//						PWM7_SW_P22,PWM7_SW_P33,PWM7_SW_P02,PWM7_SW_P76
																											//						PWM8_SW_P23,PWM8_SW_P34,PWM8_SW_P03,PWM8_SW_P77

	PWMx_InitStructure.PWM_CC5Enable   = ENABLE;				//����PWM5P���벶��/�Ƚ����,  ENABLE,DISABLE
	PWMx_InitStructure.PWM_CC6Enable   = ENABLE;				//����PWM6P���벶��/�Ƚ����,  ENABLE,DISABLE
	PWMx_InitStructure.PWM_CC7Enable   = ENABLE;				//����PWM7P���벶��/�Ƚ����,  ENABLE,DISABLE
	PWMx_InitStructure.PWM_CC8Enable   = ENABLE;				//����PWM8P���벶��/�Ƚ����,  ENABLE,DISABLE
	
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMB, &PWMx_InitStructure);				//��ʼ��PWM,  PWMA,PWMB
}

/******************** ������**************************/
void main(void)
{
	PWMB_Duty.PWM5_Duty = 128;
	PWMB_Duty.PWM6_Duty = 256;
	PWMB_Duty.PWM7_Duty = 512;
	PWMB_Duty.PWM8_Duty = 1024;
	
	GPIO_config();
	Timer_config();
	PWM_config();
	EA = 1;

	while (1);
}



