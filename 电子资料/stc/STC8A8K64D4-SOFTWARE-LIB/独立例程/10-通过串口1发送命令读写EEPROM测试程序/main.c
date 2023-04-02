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
#include	"STC8A_NVIC.h"
#include	"STC8A_Delay.h"
#include	"STC8A_EEPROM.h"

/*************	��������˵��	**************

ͨ�����ڶ�STC�ڲ��Դ���EEPROM(FLASH)���ж�д���ԡ�

��FLASH������������д�롢�����Ĳ���������ָ����ַ��

Ĭ�ϲ�����:  115200,N,8,1. 

������������: (������ĸ�����ִ�Сд)
    E 0x0040             --> ��0x0040��ַ�������ݽ��в���.
    W 0x0040 1234567890  --> ��0x0040��ַд���ַ�1234567890.
    R 0x0040 10          --> ��0x0040��ַ����10���ֽ�����. 

ע�⣺����ʱ�����ؽ���"Ӳ��ѡ��"�������û�EEPROM��С��

��ȷ�����������еĵ�ַ��EEPROM���õĴ�С��Χ֮�ڡ�

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/

#define     Max_Length          100      //��дEEPROM���峤��

/*************	���س�������	**************/


/*************	���ر�������	**************/
u8  xdata   tmp[Max_Length];        //EEPROM��������


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/******************* IO���ú��� *******************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����

	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��
}

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ʹ�ò�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/**********************************************/

u8	CheckData(u8 dat)
{
	if((dat >= '0') && (dat <= '9'))		return (dat-'0');
	if((dat >= 'A') && (dat <= 'F'))		return (dat-'A'+10);
	if((dat >= 'a') && (dat <= 'f'))		return (dat-'a'+10);
	return 0xff;
}

//========================================================================
// ����: u16    GetAddress(void)
// ����: ����������뷽ʽ�ĵ�ַ.
// ����: ��.
// ����: 16λEEPROM��ַ.
// �汾: V1.0, 2013-6-6
//========================================================================
u16 GetAddress(void)
{
	u16 address;
	u8  i,j;
	
	address = 0;
	if((RX1_Buffer[2] == '0') && (RX1_Buffer[3] == 'X'))
	{
		for(i=4; i<8; i++)
		{
			j = CheckData(RX1_Buffer[i]);
			if(j >= 0x10)   return 65535;   //error
			address = (address << 4) + j;
		}
		return (address);
	}
	return  65535;  //error
}

/**************** ��ȡҪ�������ݵ��ֽ��� ****************************/
u8 GetDataLength(void)
{
	u8  i;
	u8  length;
	
	length = 0;
	for(i=9; i<COM1.RX_Cnt; i++)
	{
		if(CheckData(RX1_Buffer[i]) >= 10)  break;
		length = length * 10 + CheckData(RX1_Buffer[i]);
	}
	return (length);
}

/********************* ������ *************************/
void main(void)
{
	u8  i,j;
	u16 addr;
	u8  status;

	GPIO_config();
	UART_config();
	EA = 1;

	PrintString1("STC8ϵ�е�Ƭ��EEPROM���Գ��򣬴���������������:\r\n");    //UART1����һ���ַ���
	PrintString1("E 0x0040             --> ��0x0040��ַ�������ݽ��в���.\r\n");     //UART1����һ���ַ���
	PrintString1("W 0x0040 1234567890  --> ��0x0040��ַд���ַ�1234567890.\r\n");  //UART1����һ���ַ���
	PrintString1("R 0x0040 10          --> ��0x0040��ַ����10���ֽ�����.\r\n");    //UART1����һ���ַ���
	while(1)
	{
		delay_ms(1);
		if(COM1.RX_TimeOut > 0)		//��ʱ����
		{
			if(--COM1.RX_TimeOut == 0)
			{
				for(i=0; i<COM1.RX_Cnt; i++)    TX1_write2buff(RX1_Buffer[i]);    //���յ�������ԭ������,���ڲ���

				status = 0xff;  //״̬��һ����0ֵ
				if((COM1.RX_Cnt >= 8) && (RX1_Buffer[1] == ' ')) //�������Ϊ8���ֽ�
				{
					for(i=0; i<8; i++)
					{
						if((RX1_Buffer[i] >= 'a') && (RX1_Buffer[i] <= 'z'))    RX1_Buffer[i] = RX1_Buffer[i] - 'a' + 'A';  //Сдת��д
					}
					addr = GetAddress();
					if(addr < 63488)    //������0~123����
					{
						if(RX1_Buffer[0] == 'E')    //д��N���ֽ�
						{
							EEPROM_SectorErase(addr);           //��������
							PrintString1("�����ɹ���\r\n");
							status = 0; //������ȷ
						}

						else if((RX1_Buffer[0] == 'W') && (RX1_Buffer[8] == ' '))    //д��N���ֽ�
						{
							j = COM1.RX_Cnt - 9;
							if(j > Max_Length)  j = Max_Length; //Խ����
							//EEPROM_SectorErase(addr);           //��������
							EEPROM_write_n(addr,&RX1_Buffer[9],j);      //дN���ֽ�
							PrintString1("��д��");
							if(j >= 100)    {TX1_write2buff(j/100+'0');   j = j % 100;}
							if(j >= 10)     {TX1_write2buff(j/10+'0');    j = j % 10;}
							TX1_write2buff(j%10+'0');
							PrintString1("�ֽڣ�\r\n");
							status = 0; //������ȷ
						}

						else if((RX1_Buffer[0] == 'R') && (RX1_Buffer[8] == ' '))   //PC���󷵻�N�ֽ�EEPROM����
						{
							j = GetDataLength();
							if(j > Max_Length)  j = Max_Length; //Խ����
							if(j > 0)
							{
								PrintString1("����");
								TX1_write2buff(j/10+'0');
								TX1_write2buff(j%10+'0');
								PrintString1("���ֽ��������£�\r\n");
								EEPROM_read_n(addr,tmp,j);
								for(i=0; i<j; i++)  TX1_write2buff(tmp[i]);
								TX1_write2buff(0x0d);
								TX1_write2buff(0x0a);
								status = 0; //������ȷ
							}
						}
					}
				}
				if(status != 0) PrintString1("�������\r\n");
				COM1.RX_Cnt = 0;
			}
		}
	}
} 
/**********************************************/


