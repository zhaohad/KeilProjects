#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "stc8a8k64d4.h"
#include "type_def.h"
#include "delay.h"

typedef unsigned char uchar;
typedef unsigned char uint8_t;
typedef unsigned short int	uint16_t;

sbit P_SERVO1 = P2 ^ 7;  // P_SERVO-T01
sbit P_SERVO2 = P0 ^ 5;  // P_SERVO-T02
sbit P_SERVO3 = P2 ^ 6;  // P_SERVO-T03
sbit P_SERVO4 = P0 ^ 6;  // P_SERVO-T04
sbit P_SERVO5 = P2 ^ 5;  // P_SERVO-T05
sbit P_SERVO6 = P0 ^ 7;  // P_SERVO-T06

sbit P_SERVO7 = P3 ^ 7;  // P_SERVO-T11
sbit P_SERVO8 = P3 ^ 2;  // P_SERVO-T12
sbit P_SERVO9 = P4 ^ 1;  // P_SERVO-T13
sbit P_SERVO10 = P4 ^ 0; // P_SERVO-T14
sbit P_SERVO11 = P2 ^ 0; // P_SERVO-T15
sbit P_SERVO12 = P5 ^ 5; // P_SERVO-T16

sbit P_OLED12864_SCK = P4 ^ 2;
sbit P_OLED12864_SDA = P2 ^ 1;
sbit P_OLED12864_RES = P2 ^ 2;
sbit P_OLED12864_DC = P2 ^ 3;
sbit P_OLED12864_CS = P2 ^ 4;

sbit P_G01_S_CE = P0 ^ 4; // out
sbit P_G01_S_CSN = P0 ^ 3; // out
sbit P_G01_S_SCK = P4 ^ 3; // out
sbit P_G01_S_MOSI = P0 ^ 2; // out
sbit P_G01_S_MISO = P0 ^ 1; // in
sbit P_G01_S_IRQ = P0 ^ 0; // in

#endif