#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.H"
#include "STC8A_GPIO.h"
#include "type_def.h"
#include "delay.h"
#include "STC8A_ADC.h"

typedef unsigned char uchar;

sbit P_MOTOR_A = P2 ^ 2;
sbit P_MOTOR_B = P2 ^ 3;

sbit P_OLED12864_SCK = P4 ^ 0;
sbit P_OLED12864_SDA = P4 ^ 1;
sbit P_OLED12864_RES = P4 ^ 2;
sbit P_OLED12864_DC = P4 ^ 3;
sbit P_OLED12864_CS = P4 ^ 4;

sbit P_INT = P5 ^ 4;
sbit P_INT_01 = P0 ^ 1;
sbit P_INT_02 = P0 ^ 2;
sbit P_INT_03 = P0 ^ 3;
sbit P_INT_04 = P0 ^ 4;
sbit P_INT_05 = P0 ^ 5;
sbit P_INT_06 = P0 ^ 6;
sbit P_INT_07 = P0 ^ 7;

// ADC Òý½Å P00
#define ADC_CHANEL ADC_CH8

#endif