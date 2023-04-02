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
#include	"STC8A_Exti.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_UART.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Delay.h"

/*************	����˵��	**************

��ʾINT0~INT4 5������Դ��MCU�����߻���.

�Ӵ����������Դ�����Ѵ�����115200,N,8,1.

����ʱ, ѡ��ʱ�� 22.1184MHz (�û�����"config.h"�޸�Ƶ��).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/
u8 WakeUpSource;
u8 WakeUpCnt;

/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



/******************** IO������ ********************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_All;			//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��
}

/******************** INT���� ********************/
void	Exti_config(void)
{
	EXTI_InitTypeDef	Exti_InitStructure;							//�ṹ����

	Exti_InitStructure.EXTI_Mode      = EXT_MODE_Fall;//�ж�ģʽ,   EXT_MODE_RiseFall,EXT_MODE_Fall
	Ext_Inilize(EXT_INT0,&Exti_InitStructure);				//��ʼ��
	NVIC_INT0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	Exti_InitStructure.EXTI_Mode      = EXT_MODE_Fall;//�ж�ģʽ,   EXT_MODE_RiseFall,EXT_MODE_Fall
	Ext_Inilize(EXT_INT1,&Exti_InitStructure);				//��ʼ��
	NVIC_INT1_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	NVIC_INT2_Init(ENABLE,NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�
	NVIC_INT3_Init(ENABLE,NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�
	NVIC_INT4_Init(ENABLE,NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�
}

/****************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������ USART1,USART2,USART3,USART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** ������***********************/
void main(void)
{
	GPIO_config();
	UART_config();
	EA  = 1;		//Enable all interrupt

	printf("STC8 EXINT Wakeup Test Programme!\r\n");	//UART����һ���ַ���
	
	while(1)
	{
		while(!INT0);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT1);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT2);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT3);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT4);	//�ȴ����ж�Ϊ�ߵ�ƽ
		delay_ms(10);	//delay 10ms

		while(!INT0);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT1);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT2);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT3);	//�ȴ����ж�Ϊ�ߵ�ƽ
		while(!INT4);	//�ȴ����ж�Ϊ�ߵ�ƽ
		delay_ms(10);	//delay 10ms

		Exti_config();
		WakeUpSource = 0;

		PCON |= 2;		//Sleep
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		
		if(WakeUpSource == 1)	printf("���ж�INT0����  ");
		if(WakeUpSource == 2)	printf("���ж�INT1����  ");
		if(WakeUpSource == 3)	printf("���ж�INT2����  ");
		if(WakeUpSource == 4)	printf("���ж�INT3����  ");
		if(WakeUpSource == 5)	printf("���ж�INT4����  ");
		WakeUpSource = 0;
		
		WakeUpCnt++;
		TX1_write2buff(WakeUpCnt/100+'0');
		TX1_write2buff(WakeUpCnt%100/10+'0');
		TX1_write2buff(WakeUpCnt%10+'0');
		PrintString1("�λ���\r\n");
	}

}

