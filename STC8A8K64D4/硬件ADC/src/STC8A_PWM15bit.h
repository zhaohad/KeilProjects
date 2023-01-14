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

#ifndef	__PWM15BIT_H
#define	__PWM15BIT_H

#include	"config.h"

//========================================================================
//                              PWM����
//========================================================================

#define PWM15_PWM_Set(n)					(n==1?(PWMSET |= 0x01):(PWMSET &= ~0x01))				//ʹ��/�ر� PWM������ PWM0~PWM7��

#define PWM15_PS_Set(n)						PWMCKS = (PWMCKS & ~0x0F) | (n & 0x0F)				//ϵͳʱ��Ԥ��Ƶ�������ã�SYSclk / (PWM_PS+1)

#define PWM15_Clock_Sel(n)				(n==1?(PWMCKS |= 0x10):(PWMCKS &= ~0x10))				//PWMʱ��Դѡ��

#define PWM15_Counter_Set(n)			(n==1?(PWMCFG |= 0x01):(PWMCFG &= ~0x01))				//PWM������ʹ������

#define PWM15_CounterInt_Set(n)		(n==1?(PWMCFG |= 0x04):(PWMCFG &= ~0x04))				//PWM�����������ж�ʹ������

//========================================================================
//                              ��������
//========================================================================

#define	PWM15_0				0
#define	PWM15_1				1
#define	PWM15_2				2
#define	PWM15_3				3
#define	PWM15_4				4
#define	PWM15_5				5
#define	PWM15_6				6
#define	PWM15_7				7

#define	PWM_CLK_SYS			0
#define	PWM_CLK_TM2			1

typedef struct
{
	u8	PWM_Enable;	//PWMʹ��,  ENABLE, DISABLE
	u8	PWM_Counter;		//������ʹ��,  ENABLE, DISABLE
	u8	PWM_CInt;				//�����������ж�ʹ��,  ENABLE, DISABLE
	u8	PWM_Clock_Sel;	//ʱ��Դѡ��,  PWM_CLK_SYS, PWM_CLK_TM2
	u8	PWM_Clock_PS;		//ϵͳʱ�ӷ�Ƶ����,  0~15
	u16	PWM_Period;			//PWM����,  0~0x7fff
} PWM15_InitTypeDef;

u8	PWM15_Init(PWM15_InitTypeDef *PWMx);
u8	PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i);
u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh);
u8	PWM15Duty(u8 PWM_id, u16 dutyL, u16 dutyH);

#endif

