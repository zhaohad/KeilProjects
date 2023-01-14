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
// ����: u8 PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
// ����: PWMͨ�����ƼĴ�������. 
// ����: PWM_id: PWMͨ�����. ȡֵ 0~7
//			 pwm_eno:   pwm���ʹ��, 0��ΪGPIO, 1��ΪPWM���.
//			 pwm_ini:   pwm����˵ĳ�ʼ��ƽ, 0Ϊ�͵�ƽ, 1Ϊ�ߵ�ƽ.
//			 pwm_eni:   pwmͨ���ж�ʹ�ܿ���, 0Ϊ�ر�PWM�ж�, 1Ϊʹ��PWM�ж�.
//			 pwm_ent2i: pwmͨ���ڶ����������ж�ʹ�ܿ���, 0Ϊ�ر�PWM�ڶ����������ж�, 1Ϊʹ��PWM�ڶ����������ж�.
//			 pwm_ent1i: pwmͨ����һ���������ж�ʹ�ܿ���, 0Ϊ�ر�PWM��һ���������ж�, 1Ϊʹ��PWM��һ���������ж�.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
{
	u8	xdata *pPWMxCR;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id����
	if(pwm_eno > 1)	return FAIL;	//���ʹ�ܴ���
	if(pwm_ini > 1)	return FAIL;	//����˵ĳ�ʼ��ƽ����
	if(pwm_eni > 1)	return FAIL;	//�ж�ʹ�ܿ��ƴ���
	if(pwm_ent2i > 1)	return FAIL;	//�ڶ����������ж�ʹ�ܿ��ƴ���
	if(pwm_ent1i > 1)	return FAIL;	//��һ���������ж�ʹ�ܿ��ƴ���
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxCR = (u8 *)PWMxCR[PWM_id];
	*pPWMxCR = (pwm_eno << 7) | (pwm_ini << 6) | (pwm_eni << 2)| (pwm_ent2i << 1)| pwm_ent1i;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// ����: u8 PWM15Duty(u8 PWM_id, u16 Period, u16 dutyL, u16 dutyH)
// ����: PWM ռ�ձ�����. 
// ����: PWM_id:  PWMͨ�����. ȡֵ 0~7
//			 dutyL:   pwm����͵�ƽλ��, ȡֵ 0~0x7fff.
//			 dutyH:   pwm����ߵ�ƽλ��, ȡֵ 0~0x7fff.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWM15Duty(u8 PWM_id, u16 dutyL, u16 dutyH)
{
	u16	xdata *pPWMxT1;
	u16	xdata *pPWMxT2;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id����
	if(dutyL > 0x7fff)	return FAIL;	//�͵�ƽʱ�����ô���
	if(dutyH > 0x7fff)	return FAIL;	//�ߵ�ƽʱ�����ô���
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxT1 = (u16 *)PWMxT1[PWM_id];
	*pPWMxT1 = dutyL & 0x7fff;

	pPWMxT2 = (u16 *)PWMxT2[PWM_id];
	*pPWMxT2 = dutyH & 0x7fff;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// ����: u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
// ����: PWMͨ�����ƼĴ�������. 
// ����: PWM_id: PWMͨ�����. ȡֵ 0~7
//			 pwm_hldl:   pwmǿ������͵�ƽ����λ, 0�������, 1ǿ������͵�ƽ.
//			 pwm_hldh:   pwmǿ������ߵ�ƽ����λ, 0�������, 1ǿ������ߵ�ƽ.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
{
	u8	xdata *pPWMxHLD;
	
	if(PWM_id > PWM15_7)	return FAIL;	//id����
	if(pwm_hldh > 1)	return FAIL;	//���ʹ�ܴ���
	if(pwm_hldl > 1)	return FAIL;	//����˵ĳ�ʼ��ƽ����
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxHLD = (u8 *)PWMxHLD[PWM_id];
	*pPWMxHLD = (pwm_hldh << 1) | pwm_hldl;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return SUCCESS;
}

//========================================================================
// ����: u8	PWM15_Init(PWM15_InitTypeDef *PWMx)
// ����: 15λ��ǿ��PWM��ʼ������.
// ����: PWMx: �ṹ����,��ο�ͷ�ļ���Ķ���.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWM15_Init(PWM15_InitTypeDef *PWMx)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */

	PWM15_PWM_Set(PWMx->PWM_Enable);	//ʹ��/�ر� PWM0������ PWM00~PWM07��
	PWM15_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
	PWM15_Clock_Sel(PWMx->PWM_Clock_Sel);	//PWMnʱ��Դѡ��
	PWMC = PWMx->PWM_Period & 0x7fff;
	PWM15_CounterInt_Set(PWMx->PWM_CInt);	//PWMn�����������ж�ʹ������
	PWM15_Counter_Set(PWMx->PWM_Counter);	//PWMn������ʹ������
	
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return SUCCESS;
}
