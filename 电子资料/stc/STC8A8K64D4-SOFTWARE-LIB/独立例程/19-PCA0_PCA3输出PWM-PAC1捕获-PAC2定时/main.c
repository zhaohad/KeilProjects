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
#include	"STC8A_UART.h"
#include	"STC8A_Delay.h"
#include	"STC8A_Switch.h"

/*************   功能说明   ***************

PCA0  设置为8位PWM, P1.7输出变化的PWM信号, 类似"呼吸灯"的驱动.
PCA1  设置为捕获. 可以连接到P1.7或者P1.5用来测试捕获, 捕获的时钟数从串口1输出. 也可以从外部输入一个信号来捕获.
PCA2  设置为16位软件定时, 定时时间为15000个PCA时钟, 并且从P1.5输出这个信号,输出周期为30000个PCA时钟.
PCA3  设置为10位PWM, P1.4输出固定的PWM信号.

捕获脉宽时间=捕获的时钟数/PCA时钟源, 比如 捕获的时钟数 = 256, PCA时钟源 = 22.1184MHz(1T), 脉宽 = 256/22.1184MHz = 11.57us.

下载时, 选择时钟 22.1184MHz (用户可在"config.h"修改频率).

******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/

u8	cnt0;
u8	pwm0;		//pwm
bit	B_PWM0_Dir;	//方向, 0为+, 1为-.

/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/


/******************** IO口配置 ********************/
void	GPIO_config(void)
{
	P1_MODE_IN_HIZ(GPIO_Pin_6);		//P1.6 设置为高阻输入
	P1_MODE_IO_PU(GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4);		//P1.7,P1.5,P1.4 设置为准双向口
}

/***************  串口初始化函数 *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;				//结构定义

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//使用波特率, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** PCA配置 ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_8bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 128 << 8;				//对于PWM,高8位为PWM占空比
	PCA_Init(PCA0,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 0;								//对于捕获, 这个值没意义
	PCA_Init(PCA1,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = 0;								//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 15000;						//对于软件定时, 为匹配比较值
	PCA_Init(PCA2,&PCA_InitStructure);

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_10bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 256 << 8;				//对于PWM,高8位为PWM占空比
	PCA_Init(PCA3,&PCA_InitStructure);

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = ENABLE;					//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);		//设置公用Counter

	NVIC_PCA_Init(PCA_Counter,DISABLE,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_PWM,Priority_0);		//PWM
	NVIC_PCA_Init(PCA1,PCA_Mode_Capture,Priority_0);		//Capture
	NVIC_PCA_Init(PCA2,PCA_Mode_HighPulseOutput,Priority_0);	//HighPulseOutput
	NVIC_PCA_Init(PCA3,PCA_Mode_PWM,Priority_0);		//PWM

	UpdatePcaPwm(PCA3,500);
}


/******************** task A **************************/
void main(void)
{
	GPIO_config();
	UART_config();
	PCA_config();
	EA = 1;

	pwm0 = 128;
	B_PWM0_Dir = 0;

	printf("STC8A8K64D4 PCA Test Programme!\r\n");	//UART1发送一个字符串

	while (1)
	{
		delay_ms(1);

		if(B_Capture1)
		{
			B_Capture1 = 0;
			//捕获脉宽时间=CCAP1_tmp/PCA_Clock, 比如 CCAP1_tmp = 256, PCA_Clock = 22.1184MHz(1T), 脉宽 = 256/22.1184MHz = 11.57us
			printf("Capture=%d\r\n",CCAP1_tmp);
		}

		cnt0++;
		if((cnt0 & 15) == 15)	//16ms
		{
			if(B_PWM0_Dir)
			{
					if(--pwm0 <= 8)		B_PWM0_Dir = 0;
			}
			else	if(++pwm0 >= 248)	B_PWM0_Dir = 1;
			UpdatePcaPwm(PCA0,pwm0);
		}
	}
}



