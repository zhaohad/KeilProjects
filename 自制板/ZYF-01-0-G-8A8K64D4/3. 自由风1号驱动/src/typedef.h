#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"
#include "delay.h"

typedef unsigned char uchar;

sbit P_SERVO1 = P0 ^ 0;
sbit P_SERVO2 = P0 ^ 1;
sbit P_SERVO3 = P0 ^ 2;
sbit P_SERVO4 = P0 ^ 3;
sbit P_SERVO5 = P0 ^ 4;
sbit P_SERVO6 = P0 ^ 5;

sbit P_SERVO7 = P1 ^ 4;
sbit P_SERVO8 = P1 ^ 5;
sbit P_SERVO9 = P3 ^ 2;
sbit P_SERVO10 = P3 ^ 3;
sbit P_SERVO11 = P3 ^ 4;
sbit P_SERVO12 = P3 ^ 5;

#endif