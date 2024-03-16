#include "global_status.h"
#include "stc8a_timer.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "communication_protocol.h"
#include "G01_S.h"

xdata u8 g_status = 0;

bit g_heart_beat = 1;
xdata u8 g_heart_beat_cnt = 0;
xdata u8 g_heart_beat_retry_cnt = 0;
#define HEART_BEAT_INTERVAL 50
#define HEART_BEAT_RETRY_CNT 3


#define CONNECTED_FLICKER_INTERVAL 40
xdata u8 g_connected_flicker_cnt = 0;


// 30.000 MHZ T2 12T 16λ�Զ����� ����10ms
void Global_Status_Timer_Init() {
	TIM_InitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer2, &TIM_InitStructure);					//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	T2L = 0x58;				//���ö�ʱ��ʼֵ
	T2H = 0x9E;				//���ö�ʱ��ʼֵ
	NVIC_Timer2_Init(ENABLE, NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�

	EA = 1;
}

// 30.000 MHZ T3 12T 16λ�Զ����� �������26214us -> 26ms
void Global_Status_Hear_Beat_Timer_Init() {
	TIM_InitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Run       = ENABLE;					//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer3, &TIM_InitStructure);					//��ʼ��Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
	T2L = 0;				//���ö�ʱ��ʼֵ
	T2H = 0;				//���ö�ʱ��ʼֵ
	NVIC_Timer3_Init(ENABLE, NULL);		//�ж�ʹ��, ENABLE/DISABLE; �����ȼ�

	EA = 1;
}

// 30.000 MHZ T3 12T 16λ�Զ����� �������26214us -> 26ms
void Global_Status_Heart_Beat_Timer_Callback() {
	if (g_heart_beat) {
		g_heart_beat_cnt++;
		if (g_heart_beat_cnt == HEART_BEAT_INTERVAL) {
			xdata u8 res = 0;
			
			res = NRF24L01_TxPacket((uint8_t *) COMMUICATION_HEART_BEAT, HEART_BEAT_LEN);
			if (res == TX_OK) {
				g_heart_beat_retry_cnt = 0;
				Global_Status_Set_Status(STATUS_CONNECTED);
			} else {
				g_heart_beat_retry_cnt++;
				if (g_heart_beat_retry_cnt == HEART_BEAT_RETRY_CNT) {
					Global_Status_Set_Status(STATUS_CONNECTING);
					g_heart_beat_retry_cnt = 0;
				}
			}
			g_heart_beat_cnt = 0;
		}
	} else {
		g_heart_beat_cnt = 0;
		g_heart_beat_retry_cnt = 0;
	}
}

// 30.000 MHZ 10msһ����
void Global_Status_Timer_Callback() {
	switch (g_status) {
		case STATUS_CONNECTING:
			g_connected_flicker_cnt++;
			if (g_connected_flicker_cnt == CONNECTED_FLICKER_INTERVAL) {
				P_LED_3 = !P_LED_3;
				g_connected_flicker_cnt = 0;
			}
			break;
		case STATUS_CONNECTED:
			P_LED_3 = 0;
			break;
	}
}

void Global_Status_Set_Status(u8 status) {
	g_status = status;
}

void Global_Status_Do_Heart_Beat(bit hb) {
	g_heart_beat = hb;
}