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

#include	"APP_BMM_AD.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_ADC.h"
#include	"STC8A_UART.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"


/*************	����˵��	**************

��������ʾ��·ADC BMM����.

��ʼ��ʱ�Ȱ�ҪADCת������������Ϊ��������.

����������������(BMM)���ܣ�����ͨ��һ��ѭ���ɼ��������Զ���ŵ�BMM�����xdata�ռ�.

ͨ������1(P3.0 P3.1)��BMM�����xdata�ռ����յ������ݷ��͸���λ����������115200,8,n,1.

�ö�ʱ���������ʷ�����������ʹ��1Tģʽ(���ǵͲ�������12T)����ѡ��ɱ�������������ʱ��Ƶ�ʣ�����߾���.

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/


//========================================================================
//                               ���س�������	
//========================================================================

#define	ADC_CH		16			/* 1~16, ADCת��ͨ����, ��ͬ���޸�ת��ͨ�� */
#define	ADC_DATA	12			/* 6~n, ÿ��ͨ��ADCת����������, 2*ת������+4, ��ͬ���޸�ת������ */

//========================================================================
//                               ���ر�������
//========================================================================

u8 chn = 0;
bit BmmADCFlag = 0;
u8 xdata BmmAdBuffer[ADC_CH][ADC_DATA];

//========================================================================
//                               ���غ�������
//========================================================================


//========================================================================
//                            �ⲿ�����ͱ�������
//========================================================================


//========================================================================
// ����: ADtoUART_init
// ����: �û���ʼ������.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-28
//========================================================================
void BMM_AD_init(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����
	COMx_InitDefine		COMx_InitStructure;		//�ṹ����
	BMM_ADC_InitTypeDef		BMM_ADC_InitStructure;		//�ṹ����

	//----------------------------------------------
	P0_MODE_IN_HIZ(GPIO_Pin_LOW | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);		//P0.0~P0.6 ����Ϊ��������
	P1_MODE_IN_HIZ(GPIO_Pin_All);		//P1.0~P1.7 ����Ϊ��������
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 ����Ϊ׼˫���
	
	//----------------------------------------------
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������  USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	//----------------------------------------------
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	//----------------------------------------------
	BMM_ADC_InitStructure.BMM_Enable = ENABLE;			//BMMʹ��  	ENABLE,DISABLE
	BMM_ADC_InitStructure.BMM_Channel = 0xffff;			//ADCͨ��ʹ�ܼĴ���, 1:ʹ��, bit15~bit0 ��Ӧ ADC15~ADC0
	BMM_ADC_InitStructure.BMM_Buffer = BmmAdBuffer;	//ADCת�����ݴ洢��ַ
	BMM_ADC_InitStructure.BMM_Times = ADC_4_Times;	//ÿ��ͨ��ת������, ADC_1_Times,ADC_2_Times,ADC_4_Times,ADC_8_Times,ADC_16_Times,ADC_32_Times,ADC_64_Times,ADC_128_Times,ADC_256_Times
	BMM_ADC_Inilize(&BMM_ADC_InitStructure);		//��ʼ��
	NVIC_BMM_ADC_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
	BMM_ADC_TRIG();		//��������ת��
}

//========================================================================
// ����: Sample_BMM_AD
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-24
//========================================================================
void Sample_BMM_AD(void)
{
	u8	i,n;

	if(BmmADCFlag)
	{
		BmmADCFlag = 0;
		for(i=0; i<ADC_CH; i++)
		{
			for(n=0; n<ADC_DATA; n++)
			{
				printf("0x%02bx ",BmmAdBuffer[i][n]);		//��1������,...,��n������,ADͨ��,ƽ������,ƽ��ֵ
			}
			printf("\r\n");
		}
		printf("\r\n");
		BMM_ADC_TRIG();		//���´�������ת��
	}
}

//========================================================================
// ����: void ADC_BMM_Interrupt (void) interrupt 48
// ����: ADC BMM�жϺ���
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2021-5-8
// ��ע: 
//========================================================================
//void ADC_BMM_Interrupt(void) interrupt 13
//{
//	BMM_ADCIF_CLR();
//	BmmADCFlag = 1;
//}


