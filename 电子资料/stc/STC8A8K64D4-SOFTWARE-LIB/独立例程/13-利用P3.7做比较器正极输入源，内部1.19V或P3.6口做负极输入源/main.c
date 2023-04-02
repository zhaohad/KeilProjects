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

/*************  ����˵��    **************

�Ƚ��������������� P3.7/P5.0/P5.1 �˿ڻ��� ADC ��ģ������ͨ����

������������ P3.6 �˿ڻ������ڲ� BandGap ���� OP ��� REFV ��ѹ��1.19V�ڲ��̶��Ƚϵ�ѹ����

ͨ���жϻ��߲�ѯ��ʽ��ȡ�Ƚ����ȽϽ����CMP+�ĵ�ƽ����CMP-�ĵ�ƽP50������͵�ƽ����֮����ߵ�ƽ��

����ʱ, ѡ��ʱ�� 24MHz (�����������ļ�"config.h"���޸�).

******************************************/

#include	"config.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Compare.h"

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/************************ �Ƚ������� ****************************/
void	CMP_config(void)
{
	CMP_InitDefine CMP_InitStructure;						//�ṹ����
	CMP_InitStructure.CMP_EN = ENABLE;								//����Ƚ���		ENABLE,DISABLE
	CMP_InitStructure.CMP_P_Select     = CMP_P_P37;		//�Ƚ�����������ѡ��, CMP_P_P37/CMP_P_P50/CMP_P_P51, CMP_P_ADC: ��ADCģ���������������.
	CMP_InitStructure.CMP_N_Select     = CMP_N_GAP;		//�Ƚ������븺��ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap����OP��ĵ�ѹ��������, CMP_N_P36: ѡ��P3.6��������.
	CMP_InitStructure.CMP_InvCMPO      = DISABLE;			//�Ƚ������ȡ��, 	ENABLE,DISABLE
	CMP_InitStructure.CMP_100nsFilter  = ENABLE;			//�ڲ�0.1uF�˲�,  	ENABLE,DISABLE
	CMP_InitStructure.CMP_Outpt_En     = ENABLE;			//����ȽϽ�����,ENABLE,DISABLE
	CMP_InitStructure.CMP_OutDelayDuty = 16;					//�ȽϽ���仯��ʱ������, 0~63
	CMP_Inilize(&CMP_InitStructure);				//��ʼ���Ƚ���
	NVIC_CMP_Init(RISING_EDGE|FALLING_EDGE,Priority_0);	//�ж�ʹ��, RISING_EDGE/FALLING_EDGE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/************************ IO������ ****************************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_6 | GPIO_Pin_7;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_HighZ;				//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��

	GPIO_InitStructure.Pin  = GPIO_Pin_0;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);	//��ʼ��
}

/************************ ��ʱ������ ****************************/

/******************** task A **************************/
void main(void)
{
	GPIO_config();
	CMP_config();

	EA = 1;
	while (1);
}
