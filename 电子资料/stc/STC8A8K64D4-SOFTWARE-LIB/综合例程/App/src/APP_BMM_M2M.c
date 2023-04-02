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

#include	"APP_BMM_M2M.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_BMM.h"
#include	"STC8A_NVIC.h"


/*************	����˵��	**************

��������ʾBMM Memory to Memory����ת��.

����2���洢���ռ䣬һ������һ�����գ��ֱ��ʼ��2���洢���ռ�����.

����M2M BMM���ϵ���Զ������ʹ洢�������д�뵽���մ洢���ռ�.

���ݲ�ͬ�Ķ�ȡ˳��д��˳�򣬽��յ���ͬ�����ݽ��.

ͨ������(P3.0,P3.1)��ӡ���մ洢������(�ϵ��ӡһ��).

�ö�ʱ���������ʷ�����������ʹ��1Tģʽ(���ǵͲ�������12T)����ѡ��ɱ�������������ʱ��Ƶ�ʣ�����߾���.

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/


//========================================================================
//                               ���س�������	
//========================================================================


//========================================================================
//                               ���ر�������
//========================================================================

bit BmmM2MFlag = 0;
u8 xdata BmmTxBuffer[256];
u8 xdata BmmRxBuffer[256];

//========================================================================
//                               ���غ�������
//========================================================================


//========================================================================
//                            �ⲿ�����ͱ�������
//========================================================================


//========================================================================
// ����: BMM_M2M_init
// ����: �û���ʼ������.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-28
//========================================================================
void BMM_M2M_init(void)
{
	u16	i;
	COMx_InitDefine		COMx_InitStructure;		//�ṹ����
	BMM_M2M_InitTypeDef		BMM_M2M_InitStructure;		//�ṹ����

	//----------------------------------------------
	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 ����Ϊ׼˫���
	
	//----------------------------------------------
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������ UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	printf("STC8A8K64D4 Memory to Memory BMM Test Programme!\r\n");  //UART����һ���ַ���

	//----------------------------------------------
	BMM_M2M_InitStructure.BMM_Enable = ENABLE;			//BMMʹ��  	ENABLE,DISABLE
	BMM_M2M_InitStructure.BMM_Length = 127;					//BMM�������ֽ���  	(0~255) + 1
	BMM_M2M_InitStructure.BMM_Tx_Buffer = BmmTxBuffer;	//�������ݴ洢��ַ
	BMM_M2M_InitStructure.BMM_Rx_Buffer = (u16)&BmmRxBuffer[255];	//�������ݴ洢��ַ
	BMM_M2M_InitStructure.BMM_SRC_Dir = M2M_ADDR_INC;		//����Դ��ַ�ı䷽��  	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_InitStructure.BMM_DEST_Dir = M2M_ADDR_DEC;	//����Ŀ���ַ�ı䷽�� 	M2M_ADDR_INC,M2M_ADDR_DEC
	BMM_M2M_Inilize(&BMM_M2M_InitStructure);		//��ʼ��
	NVIC_BMM_M2M_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3

	for(i=0; i<256; i++)
	{
		BmmTxBuffer[i] = i;
		BmmRxBuffer[i] = 0;
	}
	BMM_M2M_TRIG();		//��������ת��
}

//========================================================================
// ����: Sample_BMM_M2M
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-24
//========================================================================
void Sample_BMM_M2M(void)
{
	u16	i;

	if(BmmM2MFlag)
	{
		BmmM2MFlag = 0;

		for(i=0; i<256; i++)
		{
			printf("%02bX ", BmmRxBuffer[i]);
			if((i & 0x0f) == 0x0f)
				printf("\r\n");
		}
	}
}

//========================================================================
// ����: void M2M_BMM_Interrupt (void) interrupt 47
// ����: M2M BMM�жϺ���
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2021-5-8
// ��ע: 
//========================================================================
//void M2M_BMM_Interrupt(void) interrupt 13
//{
//	BMM_M2MIF_CLR();
//	BmmM2MFlag = 1;
//}


