/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include	"config.h"
#include	"STC8A_PCA.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Delay.h"
#include	"STC8A_Switch.h"

/*************   功能说明   ***************

PCA输出4路高速脉冲.

下载时, 选择时钟 24MHz (用户可在"config.h"修改频率).

******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/


/******************** IO口配置 ********************/
void	GPIO_config(void)
{
	P2_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_HIGH);			//P2.3~P2.7 设置为准双向口
	PCA_SW(PCA_P22_P23_P24_P25_P26);	//PCA_P12_P17_P16_P15_P14,PCA_P22_P23_P24_P25_P26,PCA_P74_P70_P71_P72_P73,PCA_P35_P33_P32_P31_P30
}

/******************** PCA配置 ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0xffff;			//对于软件定时, 为匹配比较值
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x7fff;			//对于软件定时, 为匹配比较值
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x3fff;			//对于软件定时, 为匹配比较值
	PCA_Init(PCA2,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;						//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0x1fff;			//对于软件定时, 为匹配比较值
	PCA_Init(PCA3,&PCA_InitStructure);

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = ENABLE;				//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);			//设置公用Counter

	NVIC_PCA_Init(PCA_Counter,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA1,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA2,PCA_Mode_HighPulseOutput,Priority_0);
	NVIC_PCA_Init(PCA3,PCA_Mode_HighPulseOutput,Priority_0);
}

/******************** main **************************/
void main(void)
{
	GPIO_config();
	PCA_config();
	EA = 1;
	
	while (1)
	{
	}
}



