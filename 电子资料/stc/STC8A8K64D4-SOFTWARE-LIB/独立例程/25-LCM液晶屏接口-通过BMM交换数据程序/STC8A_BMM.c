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

#include "STC8A_BMM.h"
#include "STC8A_UART.h"

//========================================================================
// ����: void BMM_ADC_Inilize(BMM_ADC_InitTypeDef *BMM)
// ����: BMM ADC ��ʼ������.
// ����: BMM: �ṹ����,��ο�BMM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-05-17
//========================================================================
void BMM_ADC_Inilize(BMM_ADC_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	BMM_ADC_STA = 0x00;
	BMM_ADC_CHSW = BMM->BMM_Channel;
	BMM_ADC_RXA = BMM->BMM_Buffer;
	BMM_ADC_CFG2 = BMM->BMM_Times;

	if(BMM->BMM_Enable == ENABLE)		BMM_ADC_CR |= 0x80;	//ʹ��ADC BMM
	else BMM_ADC_CR &= ~0x80;	//��ֹADC BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void BMM_M2M_Inilize(BMM_M2M_InitTypeDef *BMM)
// ����: BMM M2M ��ʼ������.
// ����: BMM: �ṹ����,��ο�BMM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-05-17
//========================================================================
void BMM_M2M_Inilize(BMM_M2M_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	BMM_M2M_STA = 0x00;
	BMM_M2M_RXA = BMM->BMM_Rx_Buffer;
	BMM_M2M_TXA = BMM->BMM_Tx_Buffer;
	BMM_M2M_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_SRC_Dir == M2M_ADDR_DEC)		BMM_M2M_CFG |= 0x20;	//���ݶ�����ַ�Լ�
	else BMM_M2M_CFG &= ~0x20;	//���ݶ�����ַ�Լ�
	if(BMM->BMM_DEST_Dir == M2M_ADDR_DEC)		BMM_M2M_CFG |= 0x10;	//����д����ַ�Լ�
	else BMM_M2M_CFG &= ~0x10;	//����д����ַ�Լ�
	
	if(BMM->BMM_Enable == ENABLE)		BMM_M2M_CR |= 0x80;	//ʹ��M2M BMM
	else BMM_M2M_CR &= ~0x80;	//��ֹM2M BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void BMM_SPI_Inilize(BMM_SPI_InitTypeDef *BMM)
// ����: BMM SPI ��ʼ������.
// ����: BMM: �ṹ����,��ο�BMM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-05-17
//========================================================================
void BMM_SPI_Inilize(BMM_SPI_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	BMM_SPI_STA = 0x00;
	BMM_SPI_RXA = BMM->BMM_Rx_Buffer;
	BMM_SPI_TXA = BMM->BMM_Tx_Buffer;
	BMM_SPI_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_SS_Sel <= SPI_SS_P35) BMM_SPI_CFG2 = (BMM_SPI_CFG2 & 0xfc) | BMM->BMM_SS_Sel;	//�Զ�����SS��ѡ��

	if(BMM->BMM_Tx_Enable == ENABLE)		BMM_SPI_CFG |= 0x40;	//ʹ��SPI��������
	else BMM_SPI_CFG &= ~0x40;	//��ֹSPI��������
	
	if(BMM->BMM_Rx_Enable == ENABLE)		BMM_SPI_CFG |= 0x20;	//ʹ��SPI��������
	else BMM_SPI_CFG &= ~0x20;	//��ֹSPI��������
	
	if(BMM->BMM_AUTO_SS == ENABLE)		BMM_SPI_CFG2 |= 0x04;	//ʹ��SS�Զ�����
	else BMM_SPI_CFG2 &= ~0x04;	//��ֹSS�Զ�����
	
	if(BMM->BMM_Enable == ENABLE)		BMM_SPI_CR |= 0x80;	//ʹ��SPI BMM
	else BMM_SPI_CR &= ~0x80;	//��ֹSPI BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void BMM_UART_Inilize(u8 UARTx, BMM_UART_InitTypeDef *BMM)
// ����: BMM UART ��ʼ������.
// ����: UARTx: UART���, BMM: �ṹ����,��ο�BMM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-05-17
//========================================================================
void BMM_UART_Inilize(u8 UARTx, BMM_UART_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
#ifdef UART1
	if(UARTx == UART1)
	{
		BMM_UR1T_STA = 0x00;
		BMM_UR1R_STA = 0x00;
		BMM_UR1T_AMT = BMM->BMM_TX_Length;
		BMM_UR1T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR1R_AMT = BMM->BMM_RX_Length;
		BMM_UR1R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR1T_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR1T_CR &= ~0x80;	//��ֹADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR1R_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR1R_CR &= ~0x80;	//��ֹADC BMM
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		BMM_UR2T_STA = 0x00;
		BMM_UR2R_STA = 0x00;
		BMM_UR2T_AMT = BMM->BMM_TX_Length;
		BMM_UR2T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR2R_AMT = BMM->BMM_RX_Length;
		BMM_UR2R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR2T_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR2T_CR &= ~0x80;	//��ֹADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR2R_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR2R_CR &= ~0x80;	//��ֹADC BMM
	}
#endif
#ifdef UART3
	if(UARTx == UART3)
	{
		BMM_UR3T_STA = 0x00;
		BMM_UR3R_STA = 0x00;
		BMM_UR3T_AMT = BMM->BMM_TX_Length;
		BMM_UR3T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR3R_AMT = BMM->BMM_RX_Length;
		BMM_UR3R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR3T_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR3T_CR &= ~0x80;	//��ֹADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR3R_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR3R_CR &= ~0x80;	//��ֹADC BMM
	}
#endif
#ifdef UART4
	if(UARTx == UART4)
	{
		BMM_UR4T_STA = 0x00;
		BMM_UR4R_STA = 0x00;
		BMM_UR4T_AMT = BMM->BMM_TX_Length;
		BMM_UR4T_TXA = BMM->BMM_TX_Buffer;
		BMM_UR4R_AMT = BMM->BMM_RX_Length;
		BMM_UR4R_RXA = BMM->BMM_RX_Buffer;

		if(BMM->BMM_TX_Enable == ENABLE)		BMM_UR4T_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR4T_CR &= ~0x80;	//��ֹADC BMM
		if(BMM->BMM_RX_Enable == ENABLE)		BMM_UR4R_CR |= 0x80;	//ʹ��ADC BMM
		else BMM_UR4R_CR &= ~0x80;	//��ֹADC BMM
	}
#endif
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void BMM_LCM_Inilize(BMM_LCM_InitTypeDef *BMM)
// ����: BMM LCM ��ʼ������.
// ����: BMM: �ṹ����,��ο�BMM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-05-17
//========================================================================
void BMM_LCM_Inilize(BMM_LCM_InitTypeDef *BMM)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	BMM_LCM_STA = 0x00;
	BMM_LCM_RXA = BMM->BMM_Rx_Buffer;
	BMM_LCM_TXA = BMM->BMM_Tx_Buffer;
	BMM_LCM_AMT = BMM->BMM_Length;
	
	if(BMM->BMM_Enable == ENABLE)		BMM_LCM_CR |= 0x80;	//ʹ��LCM BMM
	else BMM_LCM_CR &= ~0x80;	//��ֹLCM BMM
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}
