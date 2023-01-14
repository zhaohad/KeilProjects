#ifndef __I2CBUS__H
#define __I2CBUS__H

#include "typedef.h"

#define PIN_SDA PIN_I2C_SDA
#define PIN_SCL PIN_I2C_SCL

void I2CBus_Start();
void I2CBus_Stop();
bit I2CBus_Write(uint8_t d);
uint8_t I2CBus_Read(bit fi);

#endif