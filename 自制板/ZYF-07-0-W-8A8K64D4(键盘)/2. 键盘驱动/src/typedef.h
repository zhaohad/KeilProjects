#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uint8_t;

sbit P_595_SER = P5 ^ 5;
sbit P_595_G = P3 ^ 6;
sbit P_595_RCK = P3 ^ 7;
sbit P_595_SCK = P4 ^ 1;
sbit P_595_SCLR = P2 ^ 0;


sbit P_165_PL = P4 ^ 2;
sbit P_165_CP = P2 ^ 1;
sbit P_165_CE = P2 ^ 2;
sbit P_165_Q7 = P0 ^ 2;

sbit P_9329_ACT = P5 ^ 4;
sbit P_9329_MODE0 = P1 ^ 7;
sbit P_9329_MODE1 = P1 ^ 6;
sbit P_9329_CFG0 = P1 ^ 5;
sbit P_9329_CFG1 = P1 ^ 4;
sbit P_9329_RST = P1 ^ 2;
sbit P_9329_Rxd = P1 ^ 1;
sbit P_9329_Txd = P1 ^ 0;
sbit P_9329_SET = P4 ^ 4;
sbit P_9329_DEF = P1 ^ 3;


#endif
