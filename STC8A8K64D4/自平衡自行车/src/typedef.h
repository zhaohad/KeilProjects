#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"

typedef unsigned char uchar;


/**
* Configuration for MPU6500
*/
#define	I2C_ADDR_MPU6500	0xD0

#define P_MPU6500_FSYNC GND
#define P_MPU6500_NCS NULL
#define P_MPU6500_INT NULL
#define P_MPU6500_AD0 GND
#define P_MPU6500_ECL NULL
#define P_MPU6500_EDA NULL
sbit P_MPU6500_SDA = P1 ^ 4;
sbit P_MPU6500_SCL = P1 ^ 5;

/**
* Configuration for SERVO
*/
sbit P_SERVO = P4 ^ 0;

/**
* Configuration for MOTOR
*/
sbit P_MOTOR_A = P2 ^ 0;
sbit P_MOTOR_B = P2 ^ 1;

/**
* Configuration for OLED-12864
*/
sbit P_OLED12864_SCK = P0 ^ 0;
sbit P_OLED12864_SDA = P0 ^ 1;
sbit P_OLED12864_RES = P0 ^ 2;
sbit P_OLED12864_DC = P0 ^ 3;
sbit P_OLED12864_CS = P0 ^ 4;

#endif