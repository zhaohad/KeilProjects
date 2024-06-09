#ifndef __74HC165_H__
#define __74HC165_H__
#include "typedef.h"

#define CNT_165 11
#define CNT_MAX_165 11
#define CNT_MAX_READ_NORM_KEY 6

void load_data_165();
u8 read_byte_165();
u8 read_keys(u8 keys[CNT_MAX_READ_NORM_KEY]);

#endif


