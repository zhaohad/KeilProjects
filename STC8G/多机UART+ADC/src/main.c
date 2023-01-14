#include "typedef.h"
#include "gpio.h"
#include "uart.h"
#include "delay.h"
#include "adc.h"

void Uart_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);	//��ʼ��
}

void UART_config() {
	COMx_InitDefine COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;		//ģʽ,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1;			//ѡ�����ʷ�����,   BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Priority = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
}

void ADC_GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin = GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_HighZ;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);	//��ʼ��
}

void ADC_config() {
	ADC_InitTypeDef ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_Power = ENABLE;				//ADC��������/�ر�	ENABLE,DISABLE
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_InitStructure.ADC_Priority = Priority_0;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	ADC_InitStructure.ADC_Interrupt = DISABLE;			//�ж�����	ENABLE,DISABLE
	ADC_Inilize(&ADC_InitStructure);					//��ʼ��
	ADC_PowerControl(ENABLE);							//������ADC��Դ��������, ENABLE��DISABLE
}

void UART_Init() {
	Uart_GPIO_Config();
	UART_config();
}

void ADC_Init() {
	ADC_GPIO_Config();
	ADC_config();
}

bit getUARTData(u8 * outC) {
	u8 index;
	if (COM1.RX_TimeOut > 0) {
		COM1.B_RX_OK = 1; // synchronize receive
		COM1.RX_TimeOut = 0;
		index = COM1.RX_Cnt;
		if (index == 0) {
			index = COM_RX1_Lenth;
		}
		--index;
		*outC = RX1_Buffer[index];
		COM1.B_RX_OK = 0;
		return 1;
	}
	return 0;
}

void main() {
	UART_Init();
	ADC_Init();

	EA = 1;
	while(1) {
		u8 send;
		u8 c;
		u16 adc;
		bit hasUart = getUARTData(&c);
		if (hasUart) {
			TX1_write2buff(c);
		} else {
		}

		adc = Get_ADCResult(4);
		if (adc == 4096) {
			send = 0xff;
		} else {
			send = adc / 1024.f * 0xff;
		}
		TX1_write2buff(send);
	}
	return;
}