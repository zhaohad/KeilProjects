#ifndef __I2CBUS__H
#define __I2CBUS__H

#include "typedef.h"

void I2CBus_Start();
void I2CBus_Stop();
bit I2CBus_Write(unsigned char d);
unsigned char I2CBus_Read(bit fi);

#endif