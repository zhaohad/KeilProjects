#ifndef __ROTATIONCOUNTER_H__
#define __ROTATIONCOUNTER_H__

#define ROTATION_COUNTER_STATE_RAGION_INVALID 0
#define ROTATION_COUNTER_STATE_RAGION_L 1
#define ROTATION_COUNTER_STATE_RAGION_M 2
#define ROTATION_COUNTER_STATE_RAGION_H 3

#define RAGION_VALUE_L_L 0
#define RAGION_VALUE_L_H 25
#define RAGION_VALUE_M_L 35
#define RAGION_VALUE_M_H 65
#define RAGION_VALUE_H_L 75
#define RAGION_VALUE_H_H 100

void RotationCounter_init();
void RotationCounter_reset();
int RotationCounter_getRotationCount();
void RotationCounter_countRotation(unsigned char ragionvalue);
void RotationCounter_check();

#endif