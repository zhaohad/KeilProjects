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

#include	"APP_BMM_UART.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_BMM.h"


/*************	����˵��	**************

ͨ��PC��MCU��������, MCU���յ��������Զ�����BMM�ռ�.

��BMM�ռ�������ô�С�����ݺ�ͨ�����ڵ�BMM�Զ����͹��ܰѴ洢�ռ������ԭ������.

�ö�ʱ���������ʷ�����������ʹ��1Tģʽ(���ǵͲ�������12T)����ѡ��ɱ�������������ʱ��Ƶ�ʣ�����߾��ȡ�

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/


//========================================================================
//                               ���س�������	
//========================================================================


//========================================================================
//                               ���ر�������
//========================================================================

bit	BmmTx1Flag;
bit	BmmRx1Flag;
bit	BmmTx2Flag;
bit	BmmRx2Flag;
bit	BmmTx3Flag;
bit	BmmRx3Flag;
bit	BmmTx4Flag;
bit	BmmRx4Flag;
u8 xdata BmmBuffer[256];	//�շ����û��棬ͬʱʹ�ö�·����ʱÿ��������ֱ��建�棬�����໥����

//========================================================================
//                               ���غ�������
//========================================================================


//========================================================================
//                            �ⲿ�����ͱ�������
//========================================================================


//========================================================================
// ����: BMM_UART_init
// ����: �û���ʼ������.
// ����: None.
// ����: None.
// �汾: V1.0, 2021-05-27
//========================================================================
void BMM_UART_init(void)
{
	u16	i;
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	BMM_UART_InitTypeDef		BMM_UART_InitStructure;		//�ṹ����
	
	//----------------------------------------------
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 ����Ϊ׼˫��� - UART1
//	P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P1.0,P1.1 ����Ϊ׼˫��� - UART2
//	P0_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P0.0,P0.1 ����Ϊ׼˫��� - UART3
//	P0_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3);	//P0.2,P0.3 ����Ϊ׼˫��� - UART4
	
	//----------------------------------------------
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������ USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART2, &COMx_InitStructure);		//��ʼ������ USART1,USART2,USART3,USART4
//	NVIC_UART2_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART3, &COMx_InitStructure);		//��ʼ������ USART1,USART2,USART3,USART4
//	NVIC_UART3_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	UART_Configuration(UART4, &COMx_InitStructure);		//��ʼ������ USART1,USART2,USART3,USART4
//	NVIC_UART4_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	printf("STC8A8K64D4 UART BMM Test Programme!\r\n");  //UART����һ���ַ���

	//----------------------------------------------
	BMM_UART_InitStructure.BMM_TX_Length = 255;				//BMM�������ֽ���  	(0~255) + 1
	BMM_UART_InitStructure.BMM_TX_Buffer = BmmBuffer;	//�������ݴ洢��ַ
	BMM_UART_InitStructure.BMM_RX_Length = 255;				//BMM�������ֽ���  	(0~255) + 1
	BMM_UART_InitStructure.BMM_RX_Buffer = BmmBuffer;	//�������ݴ洢��ַ
	BMM_UART_InitStructure.BMM_TX_Enable = ENABLE;		//BMMʹ��  	ENABLE,DISABLE
	BMM_UART_InitStructure.BMM_RX_Enable = ENABLE;		//BMMʹ��  	ENABLE,DISABLE
	BMM_UART_Inilize(UART1, &BMM_UART_InitStructure);	//��ʼ��
//	BMM_UART_Inilize(UART2, &BMM_UART_InitStructure);	//��ʼ��
//	BMM_UART_Inilize(UART3, &BMM_UART_InitStructure);	//��ʼ��
//	BMM_UART_Inilize(UART4, &BMM_UART_InitStructure);	//��ʼ��

	NVIC_BMM_UART1_Tx_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
	NVIC_BMM_UART1_Rx_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
//	NVIC_BMM_UART2_Tx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART2_Rx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART3_Tx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART3_Rx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART4_Tx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	NVIC_BMM_UART4_Rx_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	//----------------------------------------------
	BmmTx1Flag = 0;
	BmmRx1Flag = 0;
	BmmTx2Flag = 0;
	BmmRx2Flag = 0;
	BmmTx3Flag = 0;
	BmmRx3Flag = 0;
	BmmTx4Flag = 0;
	BmmRx4Flag = 0;
	for(i=0; i<256; i++)
	{
		BmmBuffer[i] = i;
	}
	BMM_UR1T_TRIG();	//����UART1���͹���
	BMM_UR1R_TRIG();	//����UART1���չ���
//	BMM_UR2T_TRIG();	//����UART2���͹���
//	BMM_UR2R_TRIG();	//����UART2���չ���
//	BMM_UR3T_TRIG();	//����UART3���͹���
//	BMM_UR3R_TRIG();	//����UART3���չ���
//	BMM_UR4T_TRIG();	//����UART4���͹���
//	BMM_UR4R_TRIG();	//����UART4���չ���
}

//========================================================================
// ����: Sample_BMM_UART
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2021-05-27
//========================================================================
void Sample_BMM_UART(void)
{
	if((BmmTx1Flag) && (BmmRx1Flag))
	{
		BmmTx1Flag = 0;
		BmmRx1Flag = 0;
		BMM_UR1T_TRIG();	//���´���UART1���͹���
		BMM_UR1R_TRIG();	//���´���UART1���չ���
	}

	if((BmmTx2Flag) && (BmmRx2Flag))
	{
		BmmTx2Flag = 0;
		BmmRx2Flag = 0;
		BMM_UR2T_TRIG();	//���´���UART2���͹���
		BMM_UR2R_TRIG();	//���´���UART2���չ���
	}

	if((BmmTx3Flag) && (BmmRx3Flag))
	{
		BmmTx3Flag = 0;
		BmmRx3Flag = 0;
		BMM_UR3T_TRIG();	//���´���UART3���͹���
		BMM_UR3R_TRIG();	//���´���UART3���չ���
	}

	if((BmmTx4Flag) && (BmmRx4Flag))
	{
		BmmTx4Flag = 0;
		BmmRx4Flag = 0;
		BMM_UR4T_TRIG();	//���´���UART4���͹���
		BMM_UR4R_TRIG();	//���´���UART4���չ���
	}
}



