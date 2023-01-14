#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifndef __STC8A8K64D4_H_
#include <reg51.h>
#include <intrins.h>

sfr AUXR = 0x8e;

typedef unsigned char u8;
typedef unsigned char uint8_t;
#else
#endif

typedef unsigned char uchar;

#include "com/delay.h"
#include "I2CBus/I2CBus.h"

sbit P_OLED12864_SCK = P0 ^ 0;
sbit P_OLED12864_SDA = P0 ^ 1;
sbit P_OLED12864_RES = P0 ^ 2;
sbit P_OLED12864_DC = P0 ^ 3;
sbit P_OLED12864_CS = P0 ^ 4;

#define	I2C_ADDR_MPU6500	0xD0

#define P_FSYNC GND
#define P_NCS NULL
#define P_INT NULL
#define P_AD0 GND
#define P_ECL NULL
#define P_EDA NULL
sbit P_MPU6500_SCL = P0 ^ 5;
sbit P_MPU6500_SDA = P0 ^ 6;

#endif