#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"
#include "delay.h"

typedef unsigned char uchar;

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
sbit P_MPU6500_SCL = P1 ^ 5;
sbit P_MPU6500_SDA = P1 ^ 4;

#endif