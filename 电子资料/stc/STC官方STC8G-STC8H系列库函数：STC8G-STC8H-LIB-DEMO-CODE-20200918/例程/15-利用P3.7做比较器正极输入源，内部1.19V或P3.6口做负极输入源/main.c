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

�����̻���STC8H8K64UΪ����оƬ��ʵ����8���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

�Ƚ��������������� P3.7 �˿ڻ��� ADC ��ģ������ͨ����

������������ P3.6 �˿ڻ������ڲ� BandGap ���� OP ��� REFV ��ѹ��1.19V�ڲ��̶��Ƚϵ�ѹ����

ͨ���жϻ��߲�ѯ��ʽ��ȡ�Ƚ����ȽϽ����CMP+�ĵ�ƽ����CMP-�ĵ�ƽP47������͵�ƽ(LED10��)����֮����ߵ�ƽ(LED10��)��

����ʱ, ѡ��ʱ�� 24MHz (�����������ļ�"config.h"���޸�).

******************************************/

#include	"config.h"
#include	"compare.h"
#include	"GPIO.h"

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/


/*************  �ⲿ�����ͱ������� *****************/


/************************ �Ƚ������� ****************************/
void	CMP_config(void)
{
	CMP_InitDefine CMP_InitStructure;						//�ṹ����
	CMP_InitStructure.CMP_EN = ENABLE;								//����Ƚ���		ENABLE,DISABLE
	CMP_InitStructure.CMP_RiseInterruptEn = ENABLE;		//�����������ж�	ENABLE,DISABLE
	CMP_InitStructure.CMP_FallInterruptEn = ENABLE;		//�����½����ж�	ENABLE,DISABLE
	CMP_InitStructure.CMP_P_Select     = CMP_P_P37;		//�Ƚ�������������ѡ��, CMP_P_P37: ѡ���ڲ�P3.7��������, CMP_P_ADC: ��ADCIS[2:0]��ѡ���ADC�������������.
	CMP_InitStructure.CMP_N_Select     = CMP_N_GAP;		//�Ƚ������븺����ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap��ѹBGv��������, CMP_N_P36: ѡ���ⲿP3.6������.
	CMP_InitStructure.CMP_InvCMPO      = DISABLE;			//�Ƚ������ȡ��, 	ENABLE,DISABLE
	CMP_InitStructure.CMP_100nsFilter  = ENABLE;			//�ڲ�0.1uF�˲�,  	ENABLE,DISABLE
	CMP_InitStructure.CMP_Outpt_En     = ENABLE;			//����ȽϽ�����,ENABLE,DISABLE
	CMP_InitStructure.CMP_P_SW         = CMP_OUT_P41;	//ѡ��P3.4/P4.1��Ϊ�Ƚ��������,  CMP_OUT_P34,CMP_OUT_P41
	CMP_InitStructure.CMP_OutDelayDuty = 16;					//�ȽϽ���仯��ʱ������, 0~63
	CMP_InitStructure.CMP_Polity	     = Polity_0;		//ָ���ж����ȼ�(�͵���) Polity_0,Polity_1,Polity_2,Polity_3
	CMP_Inilize(&CMP_InitStructure);				//��ʼ���Ƚ���
}


/************************ IO������ ****************************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_6 | GPIO_Pin_7;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_HighZ;				//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//��ʼ��

	GPIO_InitStructure.Pin  = GPIO_Pin_1 | GPIO_Pin_7;				//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;			//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4,&GPIO_InitStructure);	//��ʼ��
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
