#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P1 ^ 4;
sbit P_OLED12864_SDA = P4 ^ 4;
sbit P_OLED12864_RES = P1 ^ 5;
sbit P_OLED12864_DC = P1 ^ 6;
sbit P_OLED12864_CS = P1 ^ 7;

sbit P_VM1_RZ7899_I1 = P6 ^ 0;
sbit P_VM1_RZ7899_I2 = P6 ^ 1;
sbit P_VM1_DRV8833_I1 = P7 ^0;
sbit P_VM1_DRV8833_I2 = P7 ^1;
sbit P_VM1_DRV8833_I3 = P7 ^3;
sbit P_VM1_DRV8833_I4 = P7 ^2;
sbit P_VM1_DRV8833_FAULT = P2 ^ 0;

sbit P_VM2_RZ7899_I1 = P6 ^ 2;
sbit P_VM2_RZ7899_I2 = P6 ^ 3;
sbit P_VM2_DRV8833_I1 = P4 ^ 0;
sbit P_VM2_DRV8833_I2 = P6 ^ 4;
sbit P_VM2_DRV8833_I3 = P6 ^ 5;
sbit P_VM2_DRV8833_I4 = P6 ^ 6;
sbit P_VM2_DRV8833_FAULT = P6 ^ 7;

sbit P_KEY1 = P5 ^ 5;
sbit P_KEY2 = P4 ^ 1;
sbit P_KEY3 = P7 ^ 4;
sbit P_KEY4 = P7 ^ 5;
sbit P_KEY5 = P7 ^ 6;

#endif