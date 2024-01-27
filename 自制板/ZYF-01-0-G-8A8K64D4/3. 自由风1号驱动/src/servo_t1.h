#ifndef __SERVO_T1_H__
#define __SERVO_T1_H__

#include "typedef.h"

#define MAX_SERVO_TIMER_10US 2000

#define PIN_CONTROL7 P_SERVO7
#define PIN_CONTROL8 P_SERVO8
#define PIN_CONTROL9 P_SERVO9
#define PIN_CONTROL10 P_SERVO10
#define PIN_CONTROL11 P_SERVO11
#define PIN_CONTROL12 P_SERVO12

#define SET_CONTROL7(b) PIN_CONTROL7 = b
#define SET_CONTROL8(b) PIN_CONTROL8 = b
#define SET_CONTROL9(b) PIN_CONTROL9 = b
#define SET_CONTROL10(b) PIN_CONTROL10 = b
#define SET_CONTROL11(b) PIN_CONTROL11 = b
#define SET_CONTROL12(b) PIN_CONTROL12 = b

#define CNT_SERVOS 6

void Servo_T1_Init();
void Servo_T1_Set_Target_Degree(int tds[CNT_SERVOS], u8 ens[CNT_SERVOS]);
void Servo_T1_Timer_Callback();

#endif