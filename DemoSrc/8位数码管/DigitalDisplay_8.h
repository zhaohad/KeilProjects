#ifndef __DIGITALDISPLAY_8_H__
#define __DIGITALDISPLAY_8_H__

#include <reg51.h>

void DigitalDisplay_8_Loop();

void DigitalDisplay_8_Set(unsigned char nums[], unsigned char cnt);

void DigitalDisplay_8_Display(unsigned char nums[], unsigned char cnt);

#endif