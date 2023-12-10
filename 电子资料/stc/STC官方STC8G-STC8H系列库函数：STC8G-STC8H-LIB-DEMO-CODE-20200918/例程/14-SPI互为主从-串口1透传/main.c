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
#include	"delay.h"
#include	"UART.h"
#include	"spi.h"

/*************	����˵��	**************

�����̻���STC8H8K64UΪ����оƬ��ʵ����8���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

ͨ�����ڷ������ݸ�MCU1��MCU1�����յ���������SPI���͸�MCU2��MCU2��ͨ�����ڷ��ͳ�ȥ.

���÷��� 2��
�����豸��ʼ��ʱ������ SSIG Ϊ 0��MSTR ����Ϊ0����ʱ�����豸���ǲ����� SS �Ĵӻ�ģʽ��
������һ���豸��Ҫ��������ʱ���ȼ�� SS �ܽŵĵ�ƽ�����ʱ��ߵ�ƽ��
�ͽ��Լ����óɺ��� SS ����ģʽ���Լ��� SS ������͵�ƽ�����ͶԷ��� SS �ţ����ɽ������ݴ��䡣

         MCU1                          MCU2
  |-----------------|           |-----------------|
  |            MISO |-----------| MISO            |
--| TX         MOSI |-----------| MOSI         TX |--
  |            SCLK |-----------| SCLK            |
--| RX           SS |-----------| SS           RX |--
  |-----------------|           |-----------------|


����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


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

/****************  ���ڳ�ʼ������ *****************/
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

	PrintString1("STC8 UART1��SPI͸������\r\n");		//UART1����һ���ַ���
}

/****************  SPI��ʼ������ *****************/
void	SPI_config(void)
{
	SPI_InitTypeDef		SPI_InitStructure;
	SPI_InitStructure.SPI_Module    = ENABLE;						//SPI����    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = ENABLE;					//Ƭѡλ     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;					//��λ����   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Slave;	  //����ѡ��   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;    //ʱ����λ   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;	  //���ݱ���   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Interrupt = ENABLE;			  //�ж�����   ENABLE,DISABLE
	SPI_InitStructure.SPI_Speed     = SPI_Speed_4;		  //SPI�ٶ�    SPI_Speed_4, SPI_Speed_16, SPI_Speed_64, SPI_Speed_128
	SPI_InitStructure.SPI_IoUse     = SPI_P22_P23_P24_P25; //IO���л�   SPI_P12_P13_P14_P15, SPI_P22_P23_P24_P25, SPI_P54_P40_P41_P43, SPI_P35_P34_P33_P32
	SPI_Init(&SPI_InitStructure);
	
	SPI_SS_2 = 1;
}


/******************** task A **************************/
void main(void)
{
	u8	i;

	GPIO_config();
	UART_config();
	SPI_config();
	EA = 1;

	while (1)
	{
		delay_ms(1);
				
		if(COM1.RX_TimeOut > 0)
		{
			if(--COM1.RX_TimeOut == 0)
			{
				if(COM1.RX_Cnt > 0)
				{
					COM1.B_RX_OK = 1;
				}
			}
		}
		if((COM1.B_RX_OK) && (SPI_SS_2))
		{
			SPI_SS_2 = 0;     //���ʹӻ� SS �ܽ�
			SPI_SetMode(SPI_Mode_Master);
			for(i=0;i<COM1.RX_Cnt;i++)
			{
				SPI_WriteByte(RX1_Buffer[i]); //���ʹ�������
			}
			SPI_SS_2 = 1;    //���ߴӻ��� SS �ܽ�
			SPI_SetMode(SPI_Mode_Slave);
			COM1.RX_Cnt = 0;	//COM1.B_RX_OK = 0;
			COM1.B_RX_OK = 0;
		}
		
		if(SPI_RxTimerOut > 0)
		{
			if(--SPI_RxTimerOut == 0)
			{
				if(SPI_RxCnt > 0)
				{
					for(i=0; i<SPI_RxCnt; i++)	TX1_write2buff(SPI_RxBuffer[i]);
				}
				SPI_RxCnt = 0;
			}
		}
	}
}



