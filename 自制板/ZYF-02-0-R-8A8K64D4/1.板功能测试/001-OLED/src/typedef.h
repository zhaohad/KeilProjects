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

#endif