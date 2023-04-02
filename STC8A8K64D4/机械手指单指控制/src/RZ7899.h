#ifndef __RZ7899_H__
#define __RZ7899_H__

#include "STC8A8K64D4.H"
#include "typedef.h"

#define PIN_BI P_MOTOR_A
#define PIN_FI P_MOTOR_B

#define RUN_STATE_NONE 0
#define RUN_STATE_NORM 1
#define RUN_STATE_INV 2
#define RUN_STATE_STOP 3

void RZ7899_Init();
void RZ7899_Run(u8 state);
u8 RZ7899_GetState();

#endif