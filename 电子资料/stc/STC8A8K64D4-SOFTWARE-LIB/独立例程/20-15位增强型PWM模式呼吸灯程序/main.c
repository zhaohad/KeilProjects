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
#include	"STC8A_GPIO.h"
#include	"STC8A_Delay.h"
#include	"STC8A_PWM15bit.h"

/*************   ����˵��   ***************

���4·PWM�źţ�
PWM0  ���"������"Ч��PWM.
PWM1  ѭ�����1����PWM��1���Ӹߵ�ƽ��1���ӵ͵�ƽ.
PWM2,PWM3  �̶�PWM.

����ʱ, ѡ��ʱ�� 24MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/

u16	pwm0,pwm1;
bit	B_PWM0_Dir;	//����, 0Ϊ+, 1Ϊ-.

/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_All;			//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
}

/******************** PWM15���� ********************/
void	PWM15_config(void)
{
	PWM15_InitTypeDef		PWM15_InitStructure;

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWMʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x1000;		//PWM����,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS;		//ʱ��Դѡ��,  PWM_CLK_SYS, PWM_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//ϵͳʱ�ӷ�Ƶ����(PS+1��Ƶ),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//�����������ж�ʹ��,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//������ʹ��,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	PWM15Duty(PWM15_0,0x000,0x200);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM15_1,0x200,0xc00);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM15_2,0x400,0x800);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWM15Duty(PWM15_3,0x800,0xe00);		//PWM_ID, ����͵�ƽλ��, ����ߵ�ƽλ��
	PWMChannelCtrl(PWM15_0,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM15_1,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM15_2,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
	PWMChannelCtrl(PWM15_3,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, ���ʹ��, ��ʼ��ƽ, PWM�ж�, �ڶ����������ж�, ��һ�������ж�
}

/******************** task A **************************/
void main(void)
{
	GPIO_config();
	PWM15_config();
	pwm0 = 0;
	pwm1 = 0;
	B_PWM0_Dir = 0;

//	EA = 1;
	
	while (1)
	{
		delay_ms(1);

		if(B_PWM0_Dir)
		{
			if(--pwm0 <= 0x100)	B_PWM0_Dir = 0;	//PWM0
		}
		else	if(++pwm0 >= 0xf00)	B_PWM0_Dir = 1;	//PWM0
		PWM15Duty(PWM15_0,0,pwm0);

		if(pwm1 >= 3000)
		{
			pwm1 = 0;
		}
		else	if(pwm1 >= 2000)
		{
			PWMLevelSet(PWM15_1,ENABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
		}
		else	if(pwm1 >= 1000)
		{
			PWMLevelSet(PWM15_1,DISABLE,ENABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
		}
		else
		{
			PWMLevelSet(PWM15_1,DISABLE,DISABLE);	//PWM_ID, ǿ������͵�ƽ, ǿ������ߵ�ƽ
		}
		pwm1++;
	}
}



