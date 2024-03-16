#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"
#include "delay.h"

typedef unsigned char uchar;

sbit P_SERVO1 = P2 ^ 7;  // P_SERVO-T01
sbit P_SERVO2 = P0 ^ 5;  // P_SERVO-T02
sbit P_SERVO3 = P2 ^ 6;  // P_SERVO-T03
sbit P_SERVO4 = P0 ^ 6;  // P_SERVO-T04
sbit P_SERVO5 = P2 ^ 5;  // P_SERVO-T05
sbit P_SERVO6 = P0 ^ 7;  // P_SERVO-T06

sbit P_SERVO7 = P3 ^ 7;  // P_SERVO-T11
sbit P_SERVO8 = P3 ^ 2;  // P_SERVO-T12
sbit P_SERVO9 = P4 ^ 1;  // P_SERVO-T13
sbit P_SERVO10 = P4 ^ 0; // P_SERVO-T14
sbit P_SERVO11 = P2 ^ 0; // P_SERVO-T15
sbit P_SERVO12 = P5 ^ 5; // P_SERVO-T16

#endif