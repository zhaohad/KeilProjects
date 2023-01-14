#include "HandleControl.h"

#define MIDDLE_E_MIN 0x78
#define MIDDLE_E_MAX 0x8F

unsigned char calculateSteeringDegree(unsigned char analog) {
	unsigned char d;
	if (analog < MIDDLE_E_MIN) {
		d = 90 * analog / MIDDLE_E_MIN;
	} else if (analog > MIDDLE_E_MAX) {
		d = 90 * (analog - 0xFF) / (0xFF - MIDDLE_E_MAX) + 180;
	} else {
		d = 90;
	}
	
	return d;
}