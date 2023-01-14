#include "rotationCounter.h"

xdata int __rotation_count__ = 0;
xdata unsigned char __rotation_counter_current_state = ROTATION_COUNTER_STATE_RAGION_INVALID;
xdata unsigned char __rotation_counter_last_state = ROTATION_COUNTER_STATE_RAGION_INVALID;
xdata unsigned char __rotation_counter_last_state2 = ROTATION_COUNTER_STATE_RAGION_INVALID;

int getRotationCount() {
	return __rotation_count__;
}

void countRotation(unsigned char ragionvalue) {
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