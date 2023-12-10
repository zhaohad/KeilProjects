#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "delay.h"
#include "STC8xxxx.h"

typedef unsigned char uchar;
typedef unsigned char uint8_t;
typedef unsigned short int	uint16_t;

sbit P_VM1_RZ7899_I1 = P1 ^ 4;
sbit P_VM1_RZ7899_I2 = P1 ^ 5;

sbit P_VM1_DRV8833_I1 = P1 ^ 1;
sbit P_VM1_DRV8833_I2 = P1 ^ 0;
sbit P_VM1_DRV8833_I3 = P1 ^ 2;
sbit P_VM1_DRV8833_I4 = P1 ^ 3;

#endif