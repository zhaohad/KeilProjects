#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <reg51.h>

sfr AUXR = 0x8e;

typedef unsigned char u8;
typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P0 ^ 0;
sbit P_OLED12864_SDA = P0 ^ 1;
sbit P_OLED12864_RES = P0 ^ 2;
sbit P_OLED12864_DC = P0 ^ 3;
sbit P_OLED12864_CS = P0 ^ 4;

sbit P_KEY = P2 ^ 0;

#endif