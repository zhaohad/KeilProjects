#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "STC8A_ADC.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uchar;
typedef unsigned char uint8_t;
typedef unsigned short int	uint16_t;

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
#define CHANEL_ADC0 ADC_CH0
#define CHANEL_ADC1 ADC_CH1
#define CHANEL_ADC2 ADC_CH2
#define CHANEL_ADC3 ADC_CH3

sbit P_KEY_0 = P2 ^ 3;
sbit P_KEY_1 = P4 ^ 2;
sbit P_KEY_2 = P2 ^ 1;
sbit P_KEY_3 = P2 ^ 2;
sbit P_KEY_4 = P1 ^ 4;
sbit P_KEY_5 = P4 ^ 4;
sbit P_KEY_6 = P1 ^ 6;
sbit P_KEY_7 = P1 ^ 5;
sbit P_KEY_8 = P0 ^ 3;
sbit P_KEY_9 = P2 ^ 5;
sbit P_KEY_10 = P0 ^ 5;
sbit P_KEY_11 = P0 ^ 4;

sbit P_KEY_YG0 = P4 ^ 3;
sbit P_KEY_YG1 = P3 ^ 3;

sbit P_G01_S_CE = P2 ^ 0; // out
sbit P_G01_S_CSN = P4 ^ 1; // out
sbit P_G01_S_SCK = P3 ^ 7; // out
sbit P_G01_S_MOSI = P3 ^ 6; // out
sbit P_G01_S_MISO = P3 ^ 5; // in
sbit P_G01_S_IRQ = P3 ^ 4; // in

sbit P_MOTOR = P2 ^4;

#endif