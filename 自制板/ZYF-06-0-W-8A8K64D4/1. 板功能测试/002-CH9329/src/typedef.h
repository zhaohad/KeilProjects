#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P0 ^ 7;
sbit P_OLED12864_SDA = P0 ^ 6;
sbit P_OLED12864_RES = P0 ^ 5;
sbit P_OLED12864_DC = P0 ^ 4;
sbit P_OLED12864_CS = P0 ^ 3;

sbit P_595_SER = P3 ^ 3;
sbit P_595_G = P3 ^ 2;
sbit P_595_RCK = P4 ^ 0;
sbit P_595_SCK = P5 ^ 5;
sbit P_595_SCLR = P5 ^ 4;


sbit P_165_PL = P4 ^ 4;
sbit P_165_CP = P1 ^ 5;
sbit P_165_CE = P1 ^ 6;
sbit P_165_Q7 = P1 ^ 7;

sbit P_9329_ACT = P2 ^ 3;
sbit P_9329_MODE0 = P2 ^ 2;
sbit P_9329_MODE1 = P2 ^ 1;
sbit P_9329_CFG0 = P4 ^ 2;
sbit P_9329_CFG1 = P2 ^ 0;
sbit P_9329_RST = P4 ^ 1;
sbit P_9329_Rxd = P3 ^ 7;
sbit P_9329_Txd = P3 ^ 6;
sbit P_9329_SET = P3 ^ 5;
sbit P_9329_DEF = P3 ^ 4;


#endif


