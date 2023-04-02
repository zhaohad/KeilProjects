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

#ifndef	__BMM_H
#define	__BMM_H

#include	"config.h"

//========================================================================
//                              ��������
//========================================================================

#define BMM_ADC_TRIG()					{EAXSFR(); BMM_ADC_CR |= 0x40; EAXRAM();}
#define BMM_ADCIF_CLR()					{EAXSFR(); BMM_ADC_STA &= ~0x01; EAXRAM();}

#define BMM_M2M_TRIG()					{EAXSFR(); BMM_M2M_CR |= 0x40; EAXRAM();}
#define BMM_M2MIF_CLR()					{EAXSFR(); BMM_M2M_STA &= ~0x01; EAXRAM();}

#define BMM_UR1T_TRIG()					{EAXSFR(); BMM_UR1T_CR |= 0x40; EAXRAM();}
#define BMM_UR2T_TRIG()					{EAXSFR(); BMM_UR2T_CR |= 0x40; EAXRAM();}
#define BMM_UR3T_TRIG()					{EAXSFR(); BMM_UR3T_CR |= 0x40; EAXRAM();}
#define BMM_UR4T_TRIG()					{EAXSFR(); BMM_UR4T_CR |= 0x40; EAXRAM();}

#define BMM_UR1R_TRIG()					{EAXSFR(); BMM_UR1R_CR |= 0x20; EAXRAM();}
#define BMM_UR2R_TRIG()					{EAXSFR(); BMM_UR2R_CR |= 0x20; EAXRAM();}
#define BMM_UR3R_TRIG()					{EAXSFR(); BMM_UR3R_CR |= 0x20; EAXRAM();}
#define BMM_UR4R_TRIG()					{EAXSFR(); BMM_UR4R_CR |= 0x20; EAXRAM();}

#define BMM_SPI_TRIG_M()				{EAXSFR(); BMM_SPI_CR |= 0x40; EAXRAM();}		//SPI��������ģʽ
#define BMM_SPI_TRIG_S()				{EAXSFR(); BMM_SPI_CR |= 0x20; EAXRAM();}		//SPI�����ӻ�ģʽ

#define BMM_UR1R_CLRFIFO()			{EAXSFR(); BMM_UR1R_CR |= 0x01; EAXRAM();}
#define BMM_UR2R_CLRFIFO()			{EAXSFR(); BMM_UR2R_CR |= 0x01; EAXRAM();}
#define BMM_UR3R_CLRFIFO()			{EAXSFR(); BMM_UR3R_CR |= 0x01; EAXRAM();}
#define BMM_UR4R_CLRFIFO()			{EAXSFR(); BMM_UR4R_CR |= 0x01; EAXRAM();}
#define BMM_SPI_CLRFIFO()				{EAXSFR(); BMM_SPI_CR |= 0x01; EAXRAM();}

#define BMM_ADC_CLR_STA()				{EAXSFR(); BMM_ADC_STA = 0; EAXRAM();}
#define BMM_SPI_CLR_STA()				{EAXSFR(); BMM_SPI_STA = 0; EAXRAM();}
#define BMM_M2M_CLR_STA()				{EAXSFR(); BMM_M2M_STA = 0; EAXRAM();}
#define BMM_UR1T_CLR_STA()			{EAXSFR(); BMM_UR1T_STA = 0; EAXRAM();}
#define BMM_UR1R_CLR_STA()			{EAXSFR(); BMM_UR1R_STA = 0; EAXRAM();}
#define BMM_UR2T_CLR_STA()			{EAXSFR(); BMM_UR2T_STA = 0; EAXRAM();}
#define BMM_UR2R_CLR_STA()			{EAXSFR(); BMM_UR2R_STA = 0; EAXRAM();}
#define BMM_UR3T_CLR_STA()			{EAXSFR(); BMM_UR3T_STA = 0; EAXRAM();}
#define BMM_UR3R_CLR_STA()			{EAXSFR(); BMM_UR3R_STA = 0; EAXRAM();}
#define BMM_UR4T_CLR_STA()			{EAXSFR(); BMM_UR4T_STA = 0; EAXRAM();}
#define BMM_UR4R_CLR_STA()			{EAXSFR(); BMM_UR4R_STA = 0; EAXRAM();}

#define SET_M2M_TX_FIFO(n)			{EAXSFR(); BMM_M2M_TXA = (n); EAXRAM();}
#define SET_M2M_RX_FIFO(n)			{EAXSFR(); BMM_M2M_RXA = (n); EAXRAM();}

#define SET_BMM_ADC_CR(n)				{EAXSFR(); BMM_ADC_CR = (n); EAXRAM();}
#define SET_BMM_SPI_CR(n)				{EAXSFR(); BMM_SPI_CR = (n); EAXRAM();}
#define SET_BMM_M2M_CR(n)				{EAXSFR(); BMM_M2M_CR = (n); EAXRAM();}
#define SET_BMM_UR1T_CR(n)			{EAXSFR(); BMM_UR1T_CR = (n); EAXRAM();}
#define SET_BMM_UR1R_CR(n)			{EAXSFR(); BMM_UR1R_CR = (n); EAXRAM();}
#define SET_BMM_UR2T_CR(n)			{EAXSFR(); BMM_UR2T_CR = (n); EAXRAM();}
#define SET_BMM_UR2R_CR(n)			{EAXSFR(); BMM_UR2R_CR = (n); EAXRAM();}
#define SET_BMM_UR3T_CR(n)			{EAXSFR(); BMM_UR3T_CR = (n); EAXRAM();}
#define SET_BMM_UR3R_CR(n)			{EAXSFR(); BMM_UR3R_CR = (n); EAXRAM();}
#define SET_BMM_UR4T_CR(n)			{EAXSFR(); BMM_UR4T_CR = (n); EAXRAM();}
#define SET_BMM_UR4R_CR(n)			{EAXSFR(); BMM_UR4R_CR = (n); EAXRAM();}

#define SET_LCM_BMM_LEN(n)			{EAXSFR(); BMM_LCM_AMT = (n); EAXRAM();}
#define BMM_LCM_TRIG_WC()				{EAXSFR(); BMM_LCM_CR |= 0xC0; EAXRAM();}		//���� LCM_BMM ���������
#define BMM_LCM_TRIG_WD()				{EAXSFR(); BMM_LCM_CR |= 0xA0; EAXRAM();}		//���� LCM_BMM �����ݲ���
#define BMM_LCM_TRIG_RC()				{EAXSFR(); BMM_LCM_CR |= 0x90; EAXRAM();}		//���� LCM_BMM ���������
#define BMM_LCM_TRIG_RD()				{EAXSFR(); BMM_LCM_CR |= 0x88; EAXRAM();}		//���� LCM_BMM �����ݲ���

//========================================================================
//                              ��������
//========================================================================

#define BMM_ENABLE				0x80
#define M2M_TRIG					0x40
#define ADC_TRIG					0x40
#define UR_T_TRIG					0x40
#define UR_R_TRIG					0x20
#define SPI_TRIG_M				0x40
#define SPI_TRIG_S				0x20
#define CLR_FIFO					0x01

#define ADC_1_Times				0
#define ADC_2_Times				8
#define ADC_4_Times				9
#define ADC_8_Times				10
#define ADC_16_Times			11
#define ADC_32_Times			12
#define ADC_64_Times			13
#define ADC_128_Times			14
#define ADC_256_Times			15

#define M2M_ADDR_INC			0
#define M2M_ADDR_DEC			1

#define SPI_SS_P12				0
#define SPI_SS_P22				1
#define SPI_SS_P74				2
#define SPI_SS_P35				3


//========================================================================
//                              ��������
//========================================================================

typedef struct
{
	u8	BMM_Enable;					//BMMʹ��  	ENABLE,DISABLE
	u16	BMM_Channel;				//ADCͨ��ʹ�ܼĴ���, 1:ʹ��, bit15~bit0 ��Ӧ ADC15~ADC0
	u16	BMM_Buffer;					//ADCת�����ݴ洢��ַ
	u8	BMM_Times;					//ÿ��ͨ��ת������, ADC_1_Times,ADC_2_Times,ADC_4_Times,ADC_8_Times,ADC_16_Times,ADC_32_Times,ADC_64_Times,ADC_128_Times,ADC_256_Times
} BMM_ADC_InitTypeDef;

typedef struct
{
	u8	BMM_Enable;					//BMMʹ��  	ENABLE,DISABLE
	u16	BMM_Rx_Buffer;			//�������ݴ洢��ַ
	u16	BMM_Tx_Buffer;			//�������ݴ洢��ַ
	u8	BMM_Length;					//BMM�������ֽ���  	(0~255) + 1
	u8	BMM_SRC_Dir;				//����Դ��ַ�ı䷽��  	M2M_ADDR_INC,M2M_ADDR_DEC
	u8	BMM_DEST_Dir;				//����Ŀ���ַ�ı䷽�� 	M2M_ADDR_INC,M2M_ADDR_DEC
} BMM_M2M_InitTypeDef;

typedef struct
{
	u8	BMM_TX_Enable;			//BMMʹ��  	ENABLE,DISABLE
	u8	BMM_TX_Length;			//BMM�������ֽ���  	(0~255) + 1
	u16	BMM_TX_Buffer;			//�������ݴ洢��ַ

	u8	BMM_RX_Enable;			//BMMʹ��  	ENABLE,DISABLE
	u8	BMM_RX_Length;			//BMM�������ֽ���  	(0~255) + 1
	u16	BMM_RX_Buffer;			//�������ݴ洢��ַ
} BMM_UART_InitTypeDef;

typedef struct
{
	u8	BMM_Enable;					//BMMʹ��  	ENABLE,DISABLE
	u8	BMM_Tx_Enable;			//BMM��������ʹ��  	ENABLE,DISABLE
	u8	BMM_Rx_Enable;			//BMM��������ʹ��  	ENABLE,DISABLE
	u16	BMM_Rx_Buffer;			//�������ݴ洢��ַ
	u16	BMM_Tx_Buffer;			//�������ݴ洢��ַ
	u8	BMM_Length;					//BMM�������ֽ���  	(0~255) + 1
	u8	BMM_AUTO_SS;				//�Զ�����SS��ʹ��  	ENABLE,DISABLE
	u8	BMM_SS_Sel;					//�Զ�����SS��ѡ�� 	SPI_SS_P12,SPI_SS_P22,SPI_SS_P74,SPI_SS_P35
} BMM_SPI_InitTypeDef;

typedef struct
{
	u8	BMM_Enable;					//BMMʹ��  	ENABLE,DISABLE
	u16	BMM_Rx_Buffer;			//�������ݴ洢��ַ
	u16	BMM_Tx_Buffer;			//�������ݴ洢��ַ
	u8	BMM_Length;					//BMM�������ֽ���  	(0~255) + 1
} BMM_LCM_InitTypeDef;

//========================================================================
//                              �ⲿ����
//========================================================================
extern bit BmmADCFlag;
extern bit BmmM2MFlag;
extern bit BmmTx1Flag;
extern bit BmmRx1Flag;
extern bit BmmTx2Flag;
extern bit BmmRx2Flag;
extern bit BmmTx3Flag;
extern bit BmmRx3Flag;
extern bit BmmTx4Flag;
extern bit BmmRx4Flag;
extern bit SpiTxFlag;
extern bit SpiRxFlag;
extern bit u2sFlag;    //UART to SPI
extern bit s2uFlag;    //SPI to UART
extern bit SpiSendFlag;
extern bit UartSendFlag;
extern bit BmmLcmFlag;
extern bit LcmFlag;
extern u16 LCM_Cnt;

void BMM_ADC_Inilize(BMM_ADC_InitTypeDef *BMM);
void BMM_M2M_Inilize(BMM_M2M_InitTypeDef *BMM);
void BMM_SPI_Inilize(BMM_SPI_InitTypeDef *BMM);
void BMM_LCM_Inilize(BMM_LCM_InitTypeDef *BMM);
void BMM_UART_Inilize(u8 UARTx, BMM_UART_InitTypeDef *BMM);

#endif
