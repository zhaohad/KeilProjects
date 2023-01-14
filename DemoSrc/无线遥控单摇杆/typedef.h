#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <reg51.h>

typedef unsigned char				uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int				uint32_t;

sbit G01S_0_CE		= P0 ^ 0;
sbit G01S_0_CSN		= P0 ^ 1;
sbit G01S_0_SCK		= P0 ^ 2;
sbit G01S_0_MOSI	= P0 ^ 3;
sbit G01S_0_MISO	= P0 ^ 4;
sbit G01S_0_IRQ		= P0 ^ 5;

sbit PIN_I2C_SCL = P0 ^ 6;
sbit PIN_I2C_SDA = P0 ^ 7;

sbit PIN_MOTOR_A = P0 ^ 7;
sbit PIN_MOTOR_B = P2 ^ 0;
sbit PIN_PWM = P0 ^ 6;


#endif