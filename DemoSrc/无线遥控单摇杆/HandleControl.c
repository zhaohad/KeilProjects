#include "HandleControl.h"

#define MIDDLE_STEERING_MIN 0x78
#define MIDDLE_STEERING_MAX 0x8F

#define MIDDLE_MOTOR_MIN 0x10
#define MIDDLE_MOTOR_MAX 0x8F


uint8_t calculateSteeringDegree(uint8_t analog) {
	uint8_t d;
	if (analog < MIDDLE_STEERING_MIN) {
		d = 90 * analog / MIDDLE_STEERING_MIN;
	} else if (analog > MIDDLE_STEERING_MAX) {
		d = 90 * (analog - 0xFF) / (0xFF - MIDDLE_STEERING_MAX) + 180;
	} else {
		d = 90;
	}
	
	return d;
}

int getMotorSpeed(uint8_t analog) {
	if (analog < MIDDLE_MOTOR_MIN) {
		return -0xff;
	}
	if (analog > MIDDLE_MOTOR_MAX) {
		return 0xff;
	}
	return 0;
}