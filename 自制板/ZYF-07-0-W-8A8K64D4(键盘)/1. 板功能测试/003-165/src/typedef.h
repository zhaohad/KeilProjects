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


#endif
