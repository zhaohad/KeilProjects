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
#include	"gpio.h"
#include	"UART.h"
#include	"delay.h"

/*************	����˵��	**************

�����̻���STC8H8K64UΪ����оƬ��ʵ����8���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

˫����ȫ˫���жϷ�ʽ�շ�ͨѶ����

ͨ��PC��MCU��������, MCU�յ���ͨ�����ڰ��յ�������ԭ������, Ĭ�ϲ����ʣ�115200,N,8,1.

ͨ������ UART.h ͷ�ļ������ UART1~UART4 ���壬������ͬͨ���Ĵ���ͨ�š�

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************* IO���ú��� *******************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);	//��ʼ��
}

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer3;			//ʹ�ò�����,   BRT_Timer2, BRT_Timer3 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	COMx_InitStructure.UART_P_SW      = UART3_SW_P50_P51;	//�л��˿�,   UART3_SW_P00_P01,UART3_SW_P50_P51
	UART_Configuration(UART3, &COMx_InitStructure);		//��ʼ������3 UART1,UART2,UART3,UART4

	PrintString3("STC8 UART3 Test Programme!\r\n");	//UART3����һ���ַ���
}

/**********************************************/
void main(void)
{
	u8	i;

	GPIO_config();
	UART_config();
	EA = 1;

	while (1)
	{
		delay_ms(1);
		if(COM3.RX_TimeOut > 0)		//��ʱ����
		{
			if(--COM3.RX_TimeOut == 0)
			{
				if(COM3.RX_Cnt > 0)
				{
					for(i=0; i<COM3.RX_Cnt; i++)	TX3_write2buff(RX3_Buffer[i]);	//�յ�������ԭ������
				}
				COM3.RX_Cnt = 0;
			}
		}
	}
}



