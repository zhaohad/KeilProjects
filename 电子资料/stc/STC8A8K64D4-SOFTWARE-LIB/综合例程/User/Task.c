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

#include	"Task.h"
#include	"app.h"

//========================================================================
//                               ���ر�������
//========================================================================

static TASK_COMPONENTS Task_Comps[]=
{
//״̬  ����  ����  ����
//	{0, 250, 250, Sample_Lamp},				/* task 1 Period�� 250ms */
//	{0, 200, 200, Sample_ADtoUART},		/* task 2 Period�� 200ms */
//	{0, 20, 20, Sample_INTtoUART},		/* task 3 Period�� 20ms */
//	{0, 1, 1, Sample_RTC},						/* task 4 Period�� 1ms */
//	{0, 1, 1, Sample_I2C_PS},					/* task 5 Period�� 1ms */
//	{0, 1, 1, Sample_SPI_PS},					/* task 6 Period�� 1ms */
//	{0, 1, 1, Sample_EEPROM},					/* task 7 Period�� 1ms */
//	{0, 100, 100, Sample_WDT},				/* task 8 Period�� 100ms */
//	{0, 10, 10, Sample_PCA_PWM},			/* task 9 Period�� 10ms */
//	{0, 1, 1, Sample_PCA_Capture},		/* task 10 Period�� 1ms */
//	{0, 1, 1, Sample_PWM15bit},				/* task 11 Period�� 1ms */
//	{0, 500, 500, Sample_BMM_AD},			/* task 12 Period�� 500ms */
//	{0, 500, 500, Sample_BMM_M2M},		/* task 13 Period�� 100ms */
//	{0, 1, 1, Sample_BMM_UART},				/* task 14 Period�� 1ms */
//	{0, 1, 1, Sample_BMM_SPI_PS},			/* task 15 Period�� 1ms */
	{0, 1, 1, Sample_BMM_LCM},				/* task 16 Period�� 1ms */
	/* Add new task here */
};

u8 Tasks_Max = sizeof(Task_Comps)/sizeof(Task_Comps[0]);

//========================================================================
// ����: Task_Handler_Callback
// ����: �����ǻص�����.
// ����: None.
// ����: None.
// �汾: V1.0, 2012-10-22
//========================================================================
void Task_Marks_Handler_Callback(void)
{
	u8 i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].TIMCount)    /* If the time is not 0 */
		{
			Task_Comps[i].TIMCount--;  /* Time counter decrement */
			if(Task_Comps[i].TIMCount == 0)  /* If time arrives */
			{
				/*Resume the timer value and try again */
				Task_Comps[i].TIMCount = Task_Comps[i].TRITime;  
				Task_Comps[i].Run = 1;    /* The task can be run */
			}
		}
	}
}

//========================================================================
// ����: Task_Pro_Handler_Callback
// ����: ������ص�����.
// ����: None.
// ����: None.
// �汾: V1.0, 2012-10-22
//========================================================================
void Task_Pro_Handler_Callback(void)
{
	u8 i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].Run) /* If task can be run */
		{
			Task_Comps[i].Run = 0;    /* Flag clear 0 */
			Task_Comps[i].TaskHook();  /* Run task */
		}
	}
}


