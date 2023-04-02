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
#include	"STC8A_I2C.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Timer.h"
#include	"STC8A_Switch.h"
#include	"STC8A_Soft_I2C.h"

/*************	����˵��	**************

�ڲ�����I2C�������߿��������ӻ�ģʽ��SCL->P3.2, SDA->P3.3;
IO��ģ��I2C������ģʽ��SCL->P0.0, SDA->P0.1;
ͨ���ⲿ�������� P0.0->P3.2, P0.1->P3.3��ʵ��I2C�Է����չ��ܡ�

��STC��MCU��IO��ʽ����8λ����ܡ�
ʹ��Timer0��16λ�Զ���װ������1ms����,�������������������,�û��޸�MCU��ʱ��Ƶ��ʱ,�Զ���ʱ��1ms.
������ÿ���Ӽ�1, ������ΧΪ0~9999.

��ʾЧ��Ϊ: �ϵ������ÿ���ӷ���һ�μ������ݣ��������4�����������ʾ�������ݣ��ӻ����յ����ݺ����ұ�4���������ʾ��

����ʱ, ѡ��ʱ�� 24MHz (�����������ļ�"config.h"���޸�).

******************************************/

/*************	���س�������	**************/
#define DIS_DOT     0x20
#define DIS_BLACK   0x10
#define DIS_        0x11

u8 code t_display[]={                       //��׼�ֿ�
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //λ��

/*************	���ر�������	**************/
u8  LED8[8];        //��ʾ����
u8  display_index;  //��ʾλ����
bit DisplayFlag;
bit B_1ms;          //1ms��־

u16 msecond;
u16 second;   //�����õ����������
u8  tmp[4];     //ͨ������

/*************	���غ�������	**************/

void DisplayScan(void);

/*************  �ⲿ�����ͱ������� *****************/



/******************** IO������ ********************/
void	GPIO_config(void)
{
	P0_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);		//P0.0,P0.1 ����Ϊ׼˫���
	P3_MODE_IO_PU(GPIO_Pin_3);			//P3.3 ����Ϊ׼˫���
	P6_MODE_IO_PU(GPIO_Pin_All);		//P6 ����Ϊ׼˫���
	P7_MODE_IO_PU(GPIO_Pin_All);		//P7 ����Ϊ׼˫���
}

/************************ ��ʱ������ ****************************/
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;						//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);		//�ж�Ƶ��, 1000��/��
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);					//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/****************  I2C��ʼ������ *****************/
void	I2C_config(void)
{
	I2C_InitTypeDef		I2C_InitStructure;
	I2C_InitStructure.I2C_Mode      = I2C_Mode_Slave;		//����ѡ��   I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;						//I2C����ʹ��,   ENABLE, DISABLE
	I2C_InitStructure.I2C_SL_MA     = ENABLE;						//ʹ�ܴӻ���ַ�ȽϹ���,   ENABLE, DISABLE
	I2C_InitStructure.I2C_SL_ADR    = 0x2d;							//�ӻ��豸��ַ,  0~127  (0x2d<<1 = 0x5a)
	I2C_Init(&I2C_InitStructure);
	NVIC_I2C_Init(I2C_Mode_Slave,I2C_ESTAI|I2C_ERXI|I2C_ETXI|I2C_ESTOI,Priority_0);	//����ģʽ, I2C_Mode_Master, I2C_Mode_Slave; �ж�ʹ��, I2C_ESTAI/I2C_ERXI/I2C_ETXI/I2C_ESTOI/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	I2C_SW(I2C_P33_P32);					//I2C_P14_P15,I2C_P24_P25,I2C_P33_P32
}


/******************** task A **************************/
void main(void)
{
	u8  i;
	
	GPIO_config();
	Timer_config();
	I2C_config();
	EA = 1;

	display_index = 0;
	DisplayFlag = 0;
	
	for(i=0; i<8; i++)  LED8[i] = 0x10; //�ϵ�����

	while (1)
	{
		if(DisplayFlag)
		{
			DisplayFlag = 0;
			LED8[4] = I2C_Buffer[0];
			LED8[5] = I2C_Buffer[1];
			LED8[6] = I2C_Buffer[2];
			LED8[7] = I2C_Buffer[3];
		}
		
		if(B_1ms)
		{
			B_1ms = 0;
			DisplayScan();
			
			if(++msecond >= 1000)   //1�뵽
			{
				msecond = 0;        //��1000ms����
				second++;         //�����+1
				if(second >= 10000)    second = 0;   //�������ΧΪ0~9999

				tmp[0] = second / 1000;
				tmp[1] = (second % 1000) / 100;
				tmp[2] = (second % 100) / 10;
				tmp[3] = second % 10;
				LED8[0] = tmp[0];
				LED8[1] = tmp[1];
				LED8[2] = tmp[2];
				LED8[3] = tmp[3];

				SI2C_WriteNbyte(0, tmp, 4);
			}
		}
	}
}

/********************** ��ʾɨ�躯�� ************************/
void DisplayScan(void)
{   
    P7 = ~T_COM[7-display_index];
    P6 = ~t_display[LED8[display_index]];
    if(++display_index >= 8)    display_index = 0;  //8λ������0
}



