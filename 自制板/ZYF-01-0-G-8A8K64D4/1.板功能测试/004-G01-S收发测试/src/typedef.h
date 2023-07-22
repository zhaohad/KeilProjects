#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "STC8A_ADC.h"
#include "Type_def.h"
#include "delay.h"

typedef unsigned char uchar;
typedef unsigned char uint8_t;
typedef unsigned short int	uint16_t;

sbit P_OLED12864_SCK = P4 ^ 0;
sbit P_OLED12864_SDA = P4 ^ 1;
sbit P_OLED12864_RES = P4 ^ 2;
sbit P_OLED12864_DC = P4 ^ 3;
sbit P_OLED12864_CS = P4 ^ 4;

sbit P_VM1_RZ7899_I1 = P2 ^ 0;
sbit P_VM1_RZ7899_I2 = P2 ^ 1;

sbit P_VM2_RZ7899_I1 = P2 ^ 2;
sbit P_VM2_RZ7899_I2 = P2 ^ 3;

sbit P_G01_S_CE = P1 ^ 0; // out
sbit P_G01_S_CSN = P1 ^ 1; // out
sbit P_G01_S_SCK = P1 ^ 2; // out
sbit P_G01_S_MOSI = P1 ^ 3; // out
sbit P_G01_S_MISO = P1 ^ 6; // in
sbit P_G01_S_IRQ = P1 ^ 7; // in

#endif