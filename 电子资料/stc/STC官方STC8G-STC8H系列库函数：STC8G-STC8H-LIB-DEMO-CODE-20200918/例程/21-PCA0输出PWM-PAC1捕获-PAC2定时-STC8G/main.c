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
#include	"UART.h"
#include	"delay.h"

/*************   ����˵��   ***************

�����̻���STC8G1K08-20PIN���б�д���ԣ�STC8Gϵ��оƬ��ͨ�òο�.

PCA0  ����Ϊ8λPWM. P1.1����仯��PWM�ź�, ����"������"������.
PCA1  ����Ϊ��׽. �������ӵ�P1.0����P3.7�������Բ�׽, ��׽��ʱ�����Ӵ���1���. Ҳ���Դ��ⲿ����һ���ź�����׽.
PCA2  ����Ϊ16λ�����ʱ, ��ʱʱ��Ϊ15000��PCAʱ��, ���Ҵ�P3.7��������ź�,�������Ϊ30000��PCAʱ��.

��������ʱ��=��׽��ʱ����/PCAʱ��Դ, ���� ��׽��ʱ���� = 256, PCAʱ��Դ = 22.1184MHz(1T), ���� = 256/22.1184MHz = 11.57us.

����ʱ, ѡ��ʱ�� 22.1184MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/

u8	cnt0;
u8	pwm0;		//pwm
bit	B_PWM0_Dir;	//����, 0Ϊ+, 1Ϊ-.

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

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

	PrintString1("STC8G1K08 PCA Test Programme!\r\n");	//UART1����һ���ַ���
}

/******************** PCA���� ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_IoUse    = PCA_P12_P11_P10_P37;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//ENABLE, DISABLE
	PCA_InitStructure.PCA_Polity   = Polity_0;				//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	PCA_InitStructure.PCA_RUN      = DISABLE;					//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);		//���ù���Counter

	PCA_InitStructure.PCA_Mode     = PCA_Mode_PWM;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_8bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 128 << 8;				//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_Mode     = PCA_Mode_Capture;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = PCA_Fall_Active | ENABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 0;								//���ڲ�׽, ���ֵû����
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 15000;						//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA2,&PCA_InitStructure);

	CR = 1;							//����PCA
}


/******************** task A **************************/
void main(void)
{
	GPIO_config();
	UART_config();
	PCA_config();
	EA = 1;

	pwm0 = 128;
	B_PWM0_Dir = 0;

	while (1)
	{
		delay_ms(1);

		if(B_Capture1)
		{
			B_Capture1 = 0;
			//��������ʱ��=CCAP1_tmp/PCA_Clock, ���� CCAP1_tmp = 256, PCA_Clock = 22.1184MHz(1T), ���� = 256/22.1184MHz = 11.57us
			TX1_write2buff(CCAP1_tmp/10000 + '0');
			TX1_write2buff(CCAP1_tmp%10000/1000 + '0');
			TX1_write2buff(CCAP1_tmp%1000/100 + '0');
			TX1_write2buff(CCAP1_tmp%100/10 + '0');
			TX1_write2buff(CCAP1_tmp%10 + '0');
			PrintString1("\r\n");
		}

		cnt0++;
		if((cnt0 & 15) == 15)	//16ms
		{
			if(B_PWM0_Dir)
			{
					if(--pwm0 <= 8)		B_PWM0_Dir = 0;
			}
			else	if(++pwm0 >= 248)	B_PWM0_Dir = 1;
			UpdatePwm(PCA0,pwm0);
		}
	}
}



