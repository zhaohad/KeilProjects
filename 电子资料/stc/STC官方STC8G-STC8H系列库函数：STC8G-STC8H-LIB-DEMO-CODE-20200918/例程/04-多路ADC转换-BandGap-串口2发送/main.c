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
#include	"adc.h"
#include	"delay.h"
#include	"uart.h"

/*************	����˵��	**************

�����̻���STC8H8K64UΪ����оƬ��ʵ����8���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

������ʾ��·ADC��ѯ������ͨ������2���͸���λ����������115200,N,8,1��

˵��:
    ADC�ĵ�15ͨ�������������ڲ�BandGap�ο���ѹ��,�����ڲ�BandGap�ο���
ѹ���ȶ�,������оƬ�Ĺ�����ѹ�ĸı���仯,���Կ���ͨ�������ڲ�BandGap
�ο���ѹ,Ȼ��ͨ��ADC��ֵ��ɷ��Ƴ�VCC�ĵ�ѹ,�Ӷ��û�����ʵ���Լ��ĵ�
ѹ��⹦��.
    ADC�ĵ�15ͨ���Ĳ�������:ͨ��ADC�ĵ�15ͨ����ȡ��ǰ�ڲ�BandGap�ο���ѹֵ.
    �û�ʵ���Լ��ĵ�ѹ��⹦�ܵ�ʵ�ַ���:�����û���Ҫ��VCC�ܾ�׼�������
(����5.0V),�������ڲ�BandGap�ο���ѹ��ADCת��ֵ(����ΪBGV5),�����ֵ����
��EEPROM��,Ȼ���ڵ�ѹ���Ĵ�����,��ʵ��VCC�仯��,�����������ڲ�BandGap
�ο���ѹ��ADCת��ֵ(����ΪBGVx),ͨ�����㹫ʽ: ʵ��VCC = 5.0V * BGV5 / BGVx,
���ɼ����ʵ�ʵ�VCC��ѹֵ,��Ҫע�����,��һ����BGV5�Ļ�׼����һ��Ҫ��ȷ.

�궨�ڲ���׼Vref, �ṩһ���ȶ��Ĺ�����ѹVcc, ���ڲ���׼Nref. 
�����ڲ���׼(10λAD) Vref = Nref * Vcc / 1024.
�����ڲ���׼(12λAD) Vref = Nref * Vcc / 4096.

����ĳ����ѹ, ��ADCֵNx, ���ѹ Ux = Vref * Nx / Nref. һ��Vref = 1190mV.

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/
u16	Nref;


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************* IO���ú��� *******************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	//AD������Ϊ�����
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_HighZ;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//��ʼ��

	GPIO_InitStructure.Pin  = GPIO_Pin_6 | GPIO_Pin_7;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4,&GPIO_InitStructure);	//��ʼ��
}

/******************* AD���ú��� *******************/
void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_Power     = ENABLE;				//ADC��������/�ر�	ENABLE,DISABLE
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_InitStructure.ADC_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	ADC_InitStructure.ADC_Interrupt = DISABLE;			//�ж�����	ENABLE,DISABLE
	ADC_Inilize(&ADC_InitStructure);					//��ʼ��
	ADC_PowerControl(ENABLE);							//������ADC��Դ��������, ENABLE��DISABLE
}

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = Polity_0;			//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	COMx_InitStructure.UART_P_SW      = UART2_SW_P46_P47;	//�л��˿�,   UART2_SW_P10_P11,UART2_SW_P46_P47
	UART_Configuration(UART2, &COMx_InitStructure);		//��ʼ������2 USART1,USART2,USART3,USART4

	PrintString2("STC8 AD to UART2 Test Programme!\r\n");	//UART2����һ���ַ���
}

/**********************************************/
void main(void)
{
	u8	i;
	u16	j;

	GPIO_config();
	UART_config();
	ADC_config();
	EA = 1;

	while (1)
	{
		for(i=0; i<4; i++)
		{
			delay_ms(250);		//Ϊ���÷��͵��ٶ���һ�㣬��ʱ250ms

			if(i <3)	//ADC0~ADC2
			{
				j = Get_ADCResult(i);	//����0~14,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��, == 4096 Ϊ����
				TX2_write2buff('A');
				TX2_write2buff('D');
				TX2_write2buff(i+'0');
			}
			else		//�ڻ�׼
			{
				j = Get_ADCResult(15);	//���ڲ���׼��ѹ, ��15ͨ��
				Nref = j;
				TX2_write2buff('A');
				TX2_write2buff('D');
				TX2_write2buff('r');
				TX2_write2buff('e');
				TX2_write2buff('f');
			}
			TX2_write2buff('=');
			TX2_write2buff(j/1000 + '0');
			TX2_write2buff(j%1000/100 + '0');
			TX2_write2buff(j%100/10 + '0');
			TX2_write2buff(j%10 + '0');
			TX2_write2buff(' ');
			TX2_write2buff(' ');

			TX2_write2buff('V');
			TX2_write2buff('=');
			j = (u32)1190 * (u32)j / Nref;			//Ux = Vref * Nx / Nref. Vref = 1190mV
			TX2_write2buff(j/1000 + '0');
			TX2_write2buff('.');
			TX2_write2buff(j%1000/100 + '0');
			TX2_write2buff(j%100/10 + '0');
			TX2_write2buff(j%10 + '0');
			TX2_write2buff(' ');
			TX2_write2buff(' ');
		}
		PrintString2("\r\n");
		//=====================================================================
	}
}



