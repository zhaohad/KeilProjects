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

/*sbit G01S_1_CE		= P2 ^ 7;
sbit G01S_1_CSN		= P2 ^ 6;
sbit G01S_1_SCK		= P2 ^ 5;
sbit G01S_1_MOSI	= P2 ^ 4;
sbit G01S_1_MISO	= P2 ^ 3;
sbit G01S_1_IRQ		= P2 ^ 2;*/

#endif