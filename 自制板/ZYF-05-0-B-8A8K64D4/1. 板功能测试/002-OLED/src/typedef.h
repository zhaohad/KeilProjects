#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P4 ^ 2;
sbit P_OLED12864_SDA = P2 ^ 1;
sbit P_OLED12864_RES = P2 ^ 2;
sbit P_OLED12864_DC = P2 ^ 3;
sbit P_OLED12864_CS = P2 ^ 4;

#endif