#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "STC8A8K64D4.h"
#include "Type_def.h"
#include "delay.h"
#include	"STC8A_UART.h"

typedef unsigned char uint8_t;

sbit P_OLED12864_SCK = P4 ^ 0;
sbit P_OLED12864_SDA = P4 ^ 1;
sbit P_OLED12864_RES = P4 ^ 2;
sbit P_OLED12864_DC = P4 ^ 3;
sbit P_OLED12864_CS = P4 ^ 4;

sbit P_UART_RXD = P3 ^ 6;
sbit P_UART_TXD = P3 ^ 7;
#define P_UART UART1_SW_P36_P37

typedef void (*CB_1Byte) (u8 d);
extern CB_1Byte g_onURAT_1Byte_CB;

#endif