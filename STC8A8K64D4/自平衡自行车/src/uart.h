#ifndef __UART_H__
#define __UART_H__

#include "typedef.h"
#include "stc8a_uart.h"
#include "stc8a_nvic.h"
#include "stc8a_switch.h"

void	UART_config();
void UART_writeByte(u8 dat);
void UART_writeStr(u8 * str);

#endif