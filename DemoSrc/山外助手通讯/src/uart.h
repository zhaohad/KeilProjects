#ifndef __UART_H__
#define __UART_H__

#include "typedef.h"

typedef void (*UART_onRec)(u8);

void UART_Init_24MHz_4800bps(UART_onRec cb);
void UART_Init_110592MHz_9600bps(UART_onRec cb);
void UART_sendByte(char c);
void UART_sendStr(char * s);

#endif