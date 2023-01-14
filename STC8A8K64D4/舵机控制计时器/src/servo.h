#ifndef __SERVO_H__
#define __SERVO_H__

#include "typedef.h"

#define MAX_SERVO_TIMER_10US 2000

#define PIN_CONTROL P_SERVO
#define SET_CONTROL() PIN_CONTROL = 1
#define CLR_CONTROL() PIN_CONTROL = 0

void Servo_Init();
void Servo_Set_Target_Degree(int td);
void Servo_Timer_10us_Callback();

#endif