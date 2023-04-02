#include "rotationCounter.h"
#include "typedef.h"

xdata int __rotation_count__ = 0;
xdata unsigned char __rotation_counter_current_state = ROTATION_COUNTER_STATE_RAGION_INVALID;
xdata unsigned char __rotation_counter_last_state = ROTATION_COUNTER_STATE_RAGION_INVALID;
xdata unsigned char __rotation_counter_last_state2 = ROTATION_COUNTER_STATE_RAGION_INVALID;

void RotationCounter_GPIO_Config() {
	// ʹ��P00����
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_0;
	GPIO_Inilize(GPIO_P0, &conf);
}

void RotationCounter_ADC_config() {
	ADC_InitTypeDef ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	// NVIC_ADC_Init(DISABLE, Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

void RotationCounter_init() {
	RotationCounter_GPIO_Config();
	RotationCounter_ADC_config();
}

void RotationCounter_reset() {
	__rotation_count__ = 0;
}

int RotationCounter_getRotationCount() {
	return __rotation_count__;
}

void RotationCounter_countRotation(unsigned char ragionvalue) {
	if (ragionvalue > RAGION_VALUE_L_L && ragionvalue < RAGION_VALUE_L_H) {
		__rotation_counter_current_state = ROTATION_COUNTER_STATE_RAGION_L;
	} else if (ragionvalue > RAGION_VALUE_M_L && ragionvalue < RAGION_VALUE_M_H) {
		__rotation_counter_current_state = ROTATION_COUNTER_STATE_RAGION_M;
	} else if (ragionvalue > RAGION_VALUE_H_L && ragionvalue < RAGION_VALUE_H_H) {
		__rotation_counter_current_state = ROTATION_COUNTER_STATE_RAGION_H;
	}
	
	if (__rotation_counter_current_state == ROTATION_COUNTER_STATE_RAGION_L) {
		if (__rotation_counter_last_state == ROTATION_COUNTER_STATE_RAGION_M &&
			__rotation_counter_last_state2 == ROTATION_COUNTER_STATE_RAGION_H) {
				--__rotation_count__;
			}
	} else if (__rotation_counter_current_state == ROTATION_COUNTER_STATE_RAGION_H) {
		if (__rotation_counter_last_state == ROTATION_COUNTER_STATE_RAGION_M &&
			__rotation_counter_last_state2 == ROTATION_COUNTER_STATE_RAGION_L) {
				++__rotation_count__;
		}
	}
	if (__rotation_counter_current_state != __rotation_counter_last_state) {
		__rotation_counter_last_state2 = __rotation_counter_last_state;
		__rotation_counter_last_state = __rotation_counter_current_state;
	}
}

void RotationCounter_check() {
		u16 adc = Get_ADCResult(ADC_CHANEL);
		float r;
		r = adc / 4096.f * 100.f;
		RotationCounter_countRotation((unsigned char) r);
}