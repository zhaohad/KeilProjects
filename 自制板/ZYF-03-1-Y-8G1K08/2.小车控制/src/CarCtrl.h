#ifndef __CARCTRL_H__
#define __CARCTRL_H__

#include <intrins.h>
#include "typedef.h"

#define M_A1 P_VM1_DRV8833_I1
#define M_A2 P_VM1_DRV8833_I2
#define M_B1 P_VM1_DRV8833_I3
#define M_B2 P_VM1_DRV8833_I4

#define M1 P_VM1_RZ7899_I1
#define M2 P_VM1_RZ7899_I2

void CarControl_Init();

void Motor_Step(unsigned int step, bit forward);
void TurnBack();
void TurnRight();
void TurnLeft();

void Motor_Go(bit forward);
void Motor_Stop();
void SetSpeed(u8 speed);

#endif