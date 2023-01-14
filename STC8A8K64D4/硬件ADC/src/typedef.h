#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"
#include "delay.h"

typedef unsigned char uchar;

sbit P_MOTOR_A = P0 ^ 5;
sbit P_MOTOR_B = P0 ^ 6;
sbit P_STEERING = P0 ^ 7;

#endif