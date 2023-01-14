#ifndef __UART_H__
#define __UART_H__

#include "typedef.h"

typedef void (*UART_onRec)(u8 *, u8);

void UART_Init(UART_onRec cb);
void UART_sendByte(u8 c);
void UART_sendStr(u8 * s);

#endif