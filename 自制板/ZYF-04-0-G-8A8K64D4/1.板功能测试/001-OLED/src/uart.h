#ifndef __UART_H__
#define __UART_H__

#include "typedef.h"

typedef void (*UART_onRec)(u8 *, u8);

void UART_Init(UART_onRec cb);
void UART_sendByte(char c);
void UART_sendStr(char * s);

#endif