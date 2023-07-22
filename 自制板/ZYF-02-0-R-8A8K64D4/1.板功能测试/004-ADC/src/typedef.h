#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "STC8A_ADC.h"
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

#define CHANEL_ADC1 ADC_CH0
#define CHANEL_ADC2 ADC_CH1
#define CHANEL_ADC3 ADC_CH2
#define CHANEL_ADC4 ADC_CH3

sbit P_ADC_1 = P1 ^ 0;
sbit P_ADC_2 = P1 ^ 1;
sbit P_ADC_3 = P1 ^ 2;
sbit P_ADC_4 = P1 ^ 3;

#endif