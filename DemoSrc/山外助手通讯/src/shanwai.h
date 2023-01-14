#ifndef __SHANWAI_H__
#define __SHANWAI_H__

#include "typedef.h"
#include "uart.h"

#define SHANWAI_CMD_WAVEVALUE 0x03
#define SHANWAI_CMD_WAVEVALUE_INV 0xFC

void SHANWAI_sendWaveValue(void * d, u8 sized, u8 len);

#endif