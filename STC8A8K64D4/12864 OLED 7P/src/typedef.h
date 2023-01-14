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

#endif