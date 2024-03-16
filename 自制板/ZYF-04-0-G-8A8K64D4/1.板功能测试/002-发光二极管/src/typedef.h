#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P0 ^ 2;
sbit P_OLED12864_SDA = P0 ^ 1;
sbit P_OLED12864_RES = P0 ^ 0;
sbit P_OLED12864_DC = P2 ^ 7;
sbit P_OLED12864_CS = P2 ^ 6;

sbit P_LED_1 = P1 ^ 7;
sbit P_LED_2 = P5 ^ 5;
sbit P_LED_3 = P4 ^ 0;

sbit P_ADC_0 = P1 ^ 0;
sbit P_ADC_1 = P1 ^ 1;
sbit P_ADC_2 = P1 ^ 3;
sbit P_ADC_3 = P1 ^ 2;

sbit P_KEY_4 = P1 ^ 4;
sbit P_KEY_5 = P4 ^ 4;
sbit P_KEY_6 = P1 ^ 6;
sbit P_KEY_7 = P1 ^ 5;

#endif
