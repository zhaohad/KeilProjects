#ifndef __HANDLECONTROL_H__
#define __HANDLECONTROL_H__

#define CMD_STEERING 0x01
#define CMD_GO 0x02

#include "typedef.h"

uint8_t calculateSteeringDegree(uint8_t analog);
int getMotorSpeed(uint8_t analog);

#endif