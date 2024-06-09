#ifndef __74HC595_H__
#define __74HC595_H__
#include "typedef.h"

void write_byte_595(u8 d);
void flush_595();
void keep_595();
void clear_595();
void stop_595();

#endif