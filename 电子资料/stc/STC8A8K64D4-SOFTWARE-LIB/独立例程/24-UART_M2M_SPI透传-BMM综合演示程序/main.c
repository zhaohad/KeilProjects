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
#include	"STC8A_UART.h"
#include	"STC8A_SPI.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Switch.h"

/*************   ����˵��   ***************

UART_BMM, M2M_BMM, SPI_BMM �ۺ�ʹ����ʾ����.

ͨ�����ڷ������ݸ�MCU1��MCU1�����յ���������SPI���͸�MCU2��MCU2��ͨ�����ڷ��ͳ�ȥ.

ͨ�����ڷ������ݸ�MCU2��MCU2�����յ���������SPI���͸�MCU1��MCU1��ͨ�����ڷ��ͳ�ȥ.

MCU1/MCU2: UART���� -> UART Rx BMM -> M2M -> SPI Tx BMM -> SPI����

MCU2/MCU1: SPI���� -> SPI Rx BMM -> M2M -> UART Tx BMM -> UART����

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

#define BUF_LENGTH          107			//n+1

/*************	���ر�������	**************/

bit	SpiTxFlag;
bit	SpiRxFlag;
bit	BmmTx1Flag;
bit	BmmRx1Flag;

bit	u2sFlag;    //UART to SPI
bit	s2uFlag;    //SPI to UART

bit	SpiSendFlag;
bit	UartSendFlag;

u8 xdata UartTxBuffer[256];
u8 xdata UartRxBuffer[256];
u8 xdata SpiTxBuffer[256];
u8 xdata SpiRxBuffer[256];


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	P2_MODE_IO_PU(GPIO_Pin_All);		//P2 ����Ϊ׼˫���
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);		//P3.0,P3.1 ����Ϊ׼˫���

	SPI_SW(SPI_P22_P23_P24_P25);	//SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P74_P75_P76_P77,SPI_P35_P34_P33_P32
	SPI_SS_2 = 1;
}

/******************** UART���� ********************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;		//�ṹ����

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** SPI ���� ********************/
void	SPI_config(void)
{
	SPI_InitTypeDef		SPI_InitStructure;

	SPI_InitStructure.SPI_Enable    = ENABLE;						//SPI����    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = ENABLE;						//Ƭѡλ     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;					//��λ����   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Slave;		//����ѡ��   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;			//ʱ����λ   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;		//���ݱ���   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_64;			//SPI�ٶ�    SPI_Speed_4, SPI_Speed_16, SPI_Speed_64, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	NVIC_SPI_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** BMM ���� ********************/
void	BMM_config(void)
{
	BMM_M2M_InitTypeDef		BMM_M2M_InitStructure;		//�ṹ����
	BMM_SPI_InitTypeDef		BMM_SPI_InitStructure;		//�ṹ����
	BMM_UART_InitTypeDef		BMM_UART_InitStructure;		//�ṹ����

	//----------------------------------------------
	BMM_UART_InitStructure.BMM_TX_Length = BUF_LENGTH;	//BMM�������ֽ���  	(0~255) + 1
	BMM_UART_InitStructure.BMM_TX_Buffer = UartTxBuffer;	//�������ݴ洢��ַ
	BMM_UART_InitStructure.BMM_RX_Length = BUF_LENGTH;	//BMM�������ֽ���  	(0~255) + 1
	BMM_UART_InitStructure.BMM_RX_Buffer = UartRxBuffer;	//�������ݴ洢��ַ
	BMM_UART_InitStructure.BMM_TX_Enable = ENABLE;		//BMMʹ��  	ENABLE,DISABLE
	BMM_UART_InitStructure.BMM_RX_Enable = ENABLE;		//BMMʹ��  	ENABLE,DISABLE
	BMM_UART_Inilize(UART1, &BMM_UART_InitStructure);	//��ʼ��

	NVIC_BMM_UART1_Tx_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
	NVIC_BMM_UART1_Rx_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
	BMM_UR1R_TRIG();	//����UART1���չ���

	//----------------------------------------------
	BMM_M2M_InitStructure.BMM_Enable = ENABLE;			//BMMʹ��  	ENABLE,DISABLE
	BMM_M2M_InitStructure.BMM_Length = BUF_LENGTH;			//BMM�������ֽ���  	(0~255) + 1
	BMM_M2M_InitStructure.BMM_Tx_Buffer = UartRxBuffer;	//�������ݴ洢��ַ
	BMM_M2M_InitStructure.BMM_Rx_Buffer = SpiTxBuffer;	//�������ݴ洢��ַ
	BMM_M2M_InitStructure.BMM_SRC_Dir = M2M_ADDR_INC;		//����Դ��ַ�ı䷽��  	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_InitStructure.BMM_DEST_Dir = M2M_ADDR_INC;	//����Ŀ���ַ�ı䷽�� 	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_Inilize(&BMM_M2M_InitStructure);		//��ʼ��
	NVIC_BMM_M2M_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3

	//----------------------------------------------
	BMM_SPI_InitStructure.BMM_Enable = DISABLE;					//BMMʹ��  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Tx_Enable = ENABLE;				//BMM��������ʹ��  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Rx_Enable = ENABLE;				//BMM��������ʹ��  	ENABLE,DISABLE
	BMM_SPI_InitStructure.BMM_Length = BUF_LENGTH;			//BMM�������ֽ���  	(0~255) + 1
	BMM_SPI_InitStructure.BMM_Tx_Buffer = SpiTxBuffer;	//�������ݴ洢��ַ
	BMM_SPI_InitStructure.BMM_Rx_Buffer = SpiRxBuffer;	//�������ݴ洢��ַ
	BMM_SPI_InitStructure.BMM_SS_Sel = SPI_SS_P22;			//�Զ�����SS��ѡ�� 	SPI_SS_P12,SPI_SS_P22,SPI_SS_P74,SPI_SS_P35
	BMM_SPI_InitStructure.BMM_AUTO_SS = DISABLE;				//�Զ�����SS��ʹ��  	ENABLE,DISABLE
	BMM_SPI_Inilize(&BMM_SPI_InitStructure);		//��ʼ��
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_S | CLR_FIFO);	//bit7 1:ʹ�� SPI_BMM, bit5 1:��ʼ SPI_BMM �ӻ�ģʽ, bit0 1:��� SPI_BMM FIFO
	NVIC_BMM_SPI_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
}

void M2M_UART_SPI(void)
{
	BMM_M2M_CLR_STA();
	SET_M2M_TX_FIFO(UartRxBuffer);
	SET_M2M_RX_FIFO(SpiTxBuffer);
	BMM_M2M_TRIG();
}

void M2M_SPI_UART(void)
{
	BMM_M2M_CLR_STA();
	SET_M2M_TX_FIFO(SpiRxBuffer);
	SET_M2M_RX_FIFO(UartTxBuffer);
	BMM_M2M_TRIG();
}

void UART_BMM_Tx(void)
{
	BMM_UR1T_TRIG();
}

void UART_BMM_Rx(void)
{
	BMM_UR1R_TRIG();
}

void SPI_BMM_Master(void)
{
	SET_BMM_SPI_CR(0);
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPI_SS_2 = 0;
	SPCTL = 0xd2;   //ʹ�� SPI ����ģʽ������SS���Ź���
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_M);	//bit7 1:ʹ�� SPI_BMM, bit6 1:��ʼ SPI_BMM ����ģʽ
}

void SPI_BMM_Slave(void)
{
	SET_BMM_SPI_CR(0);
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SPCTL = 0x42;  //��������Ϊ�ӻ�����
	SET_BMM_SPI_CR(BMM_ENABLE | SPI_TRIG_S);	//bit7 1:ʹ�� SPI_BMM, bit5 1:��ʼ SPI_BMM �ӻ�ģʽ
}

/******************** task A **************************/
void main(void)
{
	GPIO_config();
	UART_config();
	SPI_config();
	BMM_config();
	EA = 1;

	printf("STC8A8K64D4 UART1-BMM-SPI��Ϊ����͸������.\r\n");
	
	while (1)
	{
		//UART���� -> UART BMM -> SPI BMM -> SPI����
		if(BmmRx1Flag)
		{
			BmmRx1Flag = 0;
			u2sFlag = 1;
			M2M_UART_SPI();			//UART Memory -> SPI Memory
		}

		if(SpiSendFlag)
		{
			SpiSendFlag = 0;
			UART_BMM_Rx();			//UART Recive Continue
			SPI_BMM_Master();		//SPI Send Memory
		}

		if(SpiTxFlag)
		{
			SpiTxFlag = 0;
			SPI_BMM_Slave();		//SPI Slave Mode
		}

		
		//SPI���� -> SPI BMM -> UART BMM -> UART����
		if(SpiRxFlag)
		{
			SpiRxFlag = 0;
			s2uFlag = 1;
			M2M_SPI_UART();			//SPI Memory -> UART Memory
		}

		if(UartSendFlag)
		{
			UartSendFlag = 0;
			SPI_BMM_Slave();		//SPI Slave Mode
			UART_BMM_Tx();			//UART Send Memory
		}
	}
}



