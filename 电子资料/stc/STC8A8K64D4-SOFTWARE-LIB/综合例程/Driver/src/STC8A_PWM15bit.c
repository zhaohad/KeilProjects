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

#include	"STC8A_PWM15bit.h"

u16 code PWMxCR[8] = {
	0xff14,		/* PWM0CR */
	0xff1c,		/* PWM1CR */
	0xff24,		/* PWM2CR */
	0xff2c,		/* PWM3CR */
	0xff34,		/* PWM4CR */
	0xff3c,		/* PWM5CR */
	0xff44,		/* PWM6CR */
	0xff4c,		/* PWM7CR */
};

u16 code PWMxT1[8] = {
	0xff10,		/* PWM0T1 */
	0xff18,		/* PWM1T1 */
	0xff20,		/* PWM2T1 */
	0xff28,		/* PWM3T1 */
	0xff30,		/* PWM4T1 */
	0xff38,		/* PWM5T1 */
	0xff40,		/* PWM6T1 */
	0xff48,		/* PWM7T1 */
};

u16 code PWMxT2[8] = {
	0xff12,		/* PWM0T2 */
	0xff1a,		/* PWM1T2 */
	0xff22,		/* PWM2T2 */
	0xff2a,		/* PWM3T2 */
	0xff32,		/* PWM4T2 */
	0xff3a,		/* PWM5T2 */
	0xff42,		/* PWM6T2 */
	0xff4a,		/* PWM7T2 */
};

u16 code PWMxHLD[8] = {
	0xff15,		/* PWM0HLD */
	0xff1d,		/* PWM1HLD */
	0xff25,		/* PWM2HLD */
	0xff2d,		/* PWM3HLD */
	0xff35,		/* PWM4HLD */
	0xff3d,		/* PWM5HLD */
	0xff45,		/* PWM6HLD */
	0xff4d,		/* PWM7HLD */
};

//========================================================================
// 函数: u8 PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
// 描述: PWM通道控制寄存器设置. 
// 参数: PWM_id: PWM通道序号. 取值 0~7
//			 pwm_eno:   pwm输出使能, 0设为GPIO, 1设为PWM输出.
//			 pwm_ini:   pwm输出端的初始电平, 0为低电平, 1为高电平.
//			 pwm_eni:   pwm通道中断使能控制, 0为关闭PWM中断, 1为使能PWM中断.
//			 pwm_ent2i: pwm通道第二个触发点中断使能控制, 0为关闭PWM第二个触发点中断, 1为使能PWM第二个触发点中断.
//			 pwm_ent1i: pwm通道第一个触发点中断使能控制, 0为关闭PWM第一个触发点中断, 1为使能PWM第一个触发点中断.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2020-09-22
//========================================================================
u8	PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
{
	u8	xdata *pPWMxCR;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id错误
	if(pwm_eno > 1)	return FAIL;	//输出使能错误
	if(pwm_ini > 1)	return FAIL;	//输出端的初始电平错误
	if(pwm_eni > 1)	return FAIL;	//中断使能控制错误
	if(pwm_ent2i > 1)	return FAIL;	//第二个触发点中断使能控制错误
	if(pwm_ent1i > 1)	return FAIL;	//第一个触发点中断使能控制错误
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	pPWMxCR = (u8 *)PWMxCR[PWM_id];
	*pPWMxCR = (pwm_eno << 7) | (pwm_ini << 6) | (pwm_eni << 2)| (pwm_ent2i << 1)| pwm_ent1i;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// 函数: u8 PWM15Duty(u8 PWM_id, u16 Period, u16 dutyL, u16 dutyH)
// 描述: PWM 占空比设置. 
// 参数: PWM_id:  PWM通道序号. 取值 0~7
//			 dutyL:   pwm输出低电平位置, 取值 0~0x7fff.
//			 dutyH:   pwm输出高电平位置, 取值 0~0x7fff.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2020-09-22
//========================================================================
u8	PWM15Duty(u8 PWM_id, u16 dutyL, u16 dutyH)
{
	u16	xdata *pPWMxT1;
	u16	xdata *pPWMxT2;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id错误
	if(dutyL > 0x7fff)	return FAIL;	//低电平时间设置错误
	if(dutyH > 0x7fff)	return FAIL;	//高电平时间设置错误
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	pPWMxT1 = (u16 *)PWMxT1[PWM_id];
	*pPWMxT1 = dutyL & 0x7fff;

	pPWMxT2 = (u16 *)PWMxT2[PWM_id];
	*pPWMxT2 = dutyH & 0x7fff;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// 函数: u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
// 描述: PWM通道控制寄存器设置. 
// 参数: PWM_id: PWM通道序号. 取值 0~7
//			 pwm_hldl:   pwm强制输出低电平控制位, 0正常输出, 1强制输出低电平.
//			 pwm_hldh:   pwm强制输出高电平控制位, 0正常输出, 1强制输出高电平.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2020-09-22
//========================================================================
u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
{
	u8	xdata *pPWMxHLD;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id错误
	if(pwm_hldh > 1)	return FAIL;	//输出使能错误
	if(pwm_hldl > 1)	return FAIL;	//输出端的初始电平错误
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	pPWMxHLD = (u8 *)PWMxHLD[PWM_id];
	*pPWMxHLD = (pwm_hldh << 1) | pwm_hldl;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// 函数: u8	PWM15_Init(PWM15_InitTypeDef *PWMx)
// 描述: 15位增强型PWM初始化程序.
// 参数: PWMx: 结构参数,请参考头文件里的定义.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2020-09-22
//========================================================================
u8	PWM15_Init(PWM15_InitTypeDef *PWMx)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */

	PWM15_PWM_Set(PWMx->PWM_Enable);	//使能/关闭 PWM0（包括 PWM00~PWM07）
	PWM15_PS_Set(PWMx->PWM_Clock_PS);	//系统时钟分频参数,  0~15
	PWM15_Clock_Sel(PWMx->PWM_Clock_Sel);	//PWMn时钟源选择
	PWMC = PWMx->PWM_Period & 0x7fff;
	PWM15_CounterInt_Set(PWMx->PWM_CInt);	//PWMn计数器归零中断使能设置
	PWM15_Counter_Set(PWMx->PWM_Counter);	//PWMn计数器使能设置
	
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
	return SUCCESS;
}
