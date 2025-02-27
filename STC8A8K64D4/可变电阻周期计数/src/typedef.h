#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P4 ^ 0;
sbit P_OLED12864_SDA = P4 ^ 1;
sbit P_OLED12864_RES = P4 ^ 2;
sbit P_OLED12864_DC = P4 ^ 3;
sbit P_OLED12864_CS = P4 ^ 4;

sbit P_ADC = P0 ^ 0;

// ADC 引脚
#define ADC_CHANEL 0x08

sbit P_MOTOR_A = P0 ^ 1;
sbit P_MOTOR_B = P0 ^ 2;

#endif