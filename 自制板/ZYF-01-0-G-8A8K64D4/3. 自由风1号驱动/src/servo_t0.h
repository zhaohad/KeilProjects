#ifndef __SERVO_T0_H__
#define __SERVO_T0_H__

#include "typedef.h"

#define MAX_SERVO_TIMER_10US 2000

#define PIN_CONTROL1 P_SERVO1
#define PIN_CONTROL2 P_SERVO2
#define PIN_CONTROL3 P_SERVO3
#define PIN_CONTROL4 P_SERVO4
#define PIN_CONTROL5 P_SERVO5
#define PIN_CONTROL6 P_SERVO6

#define SET_CONTROL1(b) PIN_CONTROL1 = b
#define SET_CONTROL2(b) PIN_CONTROL2 = b
#define SET_CONTROL3(b) PIN_CONTROL3 = b
#define SET_CONTROL4(b) PIN_CONTROL4 = b
#define SET_CONTROL5(b) PIN_CONTROL5 = b
#define SET_CONTROL6(b) PIN_CONTROL6 = b

#define CNT_SERVOS 6

void Servo_T0_Init();
void Servo_T0_Set_Target_Degree(int tds[CNT_SERVOS], u8 ens[CNT_SERVOS]);
void Servo_T0_Timer_Callback();

#endif