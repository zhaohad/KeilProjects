#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8XXXX.h"

sbit P_MOTOR_A = P3 ^ 2;
sbit P_MOTOR_B = P3 ^ 3;

sbit P_UART_RXD = P3 ^ 0;
sbit P_UART_TXD = P3 ^ 1;

sbit P_ADC = P5 ^ 4;

#endif