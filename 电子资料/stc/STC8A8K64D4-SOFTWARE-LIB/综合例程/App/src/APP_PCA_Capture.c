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

#include	"APP.h"
#include	"STC8A_PCA.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_NVIC.h"

/*************   ����˵��   ***************

PCA0  ����Ϊ8λPWM, P1.7����仯��PWM�ź�, ����"������"������.
PCA1  ����Ϊ����. �������ӵ�P1.7����P1.5�������Բ���, �����ʱ�����Ӵ���1���. Ҳ���Դ��ⲿ����һ���ź�������.
PCA2  ����Ϊ16λ�����ʱ, ��ʱʱ��Ϊ15000��PCAʱ��, ���Ҵ�P1.5�������ź�,�������Ϊ30000��PCAʱ��.
PCA3  ����Ϊ10λPWM, P1.4����̶���PWM�ź�.

��������ʱ��=�����ʱ����/PCAʱ��Դ, ���� �����ʱ���� = 256, PCAʱ��Դ = 22.1184MHz(1T), ���� = 256/22.1184MHz = 11.57us.

����ʱ, ѡ��ʱ�� 22.1184MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/


//========================================================================
//                               ���س�������	
//========================================================================


//========================================================================
//                               ���ر�������
//========================================================================

static u8	cnt0;
static u8	pwm0;		//pwm
static bit	B_PWM0_Dir;	//����, 0Ϊ+, 1Ϊ-.

//========================================================================
//                               ���غ�������
//========================================================================


//========================================================================
//                            �ⲿ�����ͱ�������
//========================================================================


//========================================================================
// ����: PCA_Capture_init
// ����: �û���ʼ������.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-28
//========================================================================
void PCA_Capture_init(void)
{
	COMx_InitDefine		COMx_InitStructure;				//�ṹ����
	PCA_InitTypeDef		PCA_InitStructure;

	P1_MODE_IN_HIZ(GPIO_Pin_6);		//P1.6 ����Ϊ��������
	P1_MODE_IO_PU(GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4);		//P1.7,P1.5,P1.4 ����Ϊ׼˫���
	//--------------------------------------------
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	printf("STC8A8K64D4 PCA Test Programme!\r\n");	//UART1����һ���ַ���
	//--------------------------------------------
	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_8bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 128 << 8;				//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0;								//���ڲ���, ���ֵû����
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 15000;						//���������ʱ, Ϊƥ��Ƚ�ֵ
	PCA_Init(PCA2,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_10bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 256 << 8;				//����PWM,��8λΪPWMռ�ձ�
	PCA_Init(PCA3,&PCA_InitStructure);

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = ENABLE;					//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);		//���ù���Counter

	NVIC_PCA_Init(PCA_Counter,DISABLE,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_PWM,Priority_0);		//PWM
	NVIC_PCA_Init(PCA1,PCA_Mode_Capture,Priority_0);		//Capture
	NVIC_PCA_Init(PCA2,PCA_Mode_HighPulseOutput,Priority_0);	//HighPulseOutput
	NVIC_PCA_Init(PCA3,PCA_Mode_PWM,Priority_0);		//PWM
	//--------------------------------------------
	pwm0 = 128;
	B_PWM0_Dir = 0;
	UpdatePcaPwm(PCA3,500);
}


//========================================================================
// ����: Sample_PCA_Capture
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-28
//========================================================================
void Sample_PCA_Capture(void)
{
	if(B_Capture1)
	{
		B_Capture1 = 0;
		//��������ʱ��=CCAP1_tmp/PCA_Clock, ���� CCAP1_tmp = 256, PCA_Clock = 22.1184MHz(1T), ���� = 256/22.1184MHz = 11.57us
		printf("Capture=%d\r\n",CCAP1_tmp);
	}

	cnt0++;
	if((cnt0 & 15) == 15)	//16ms
	{
		if(B_PWM0_Dir)
		{
				if(--pwm0 <= 8)		B_PWM0_Dir = 0;
		}
		else	if(++pwm0 >= 248)	B_PWM0_Dir = 1;
		UpdatePcaPwm(PCA0,pwm0);
	}
}



