#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "STC8A_ADC.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uchar;
typedef unsigned char uint8_t;
typedef unsigned short int	uint16_t;

sbit P_OLED12864_SCK = P4 ^ 2;
sbit P_OLED12864_SDA = P2 ^ 1;
sbit P_OLED12864_RES = P2 ^ 2;
sbit P_OLED12864_DC = P2 ^ 3;
sbit P_OLED12864_CS = P2 ^ 4;

sbit P_LED_1 = P1 ^ 7;
sbit P_LED_2 = P5 ^ 5;
sbit P_LED_3 = P4 ^ 0;

sbit P_G01_S_CE = P0 ^ 4; // out
sbit P_G01_S_CSN = P0 ^ 3; // out
sbit P_G01_S_SCK = P4 ^ 3; // out
sbit P_G01_S_MOSI = P0 ^ 2; // out
sbit P_G01_S_MISO = P0 ^ 1; // in
sbit P_G01_S_IRQ = P0 ^ 0; // in

#endif