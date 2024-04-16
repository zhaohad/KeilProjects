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

sbit P_2_4_240320_LCD_CS = P0 ^ 7;
sbit P_2_4_240320_LCD_RESET = P0 ^ 6;
sbit P_2_4_240320_LCD_DC = P0 ^ 5; // RS
sbit P_2_4_240320_LCD_SDI = P0 ^ 4;
sbit P_2_4_240320_LCD_SCK = P0 ^ 3; // CLK
sbit P_2_4_240320_LCD_LED = P0 ^ 2; // BL
sbit P_2_4_240320_LCD_SDO = P0 ^ 1;

#endif