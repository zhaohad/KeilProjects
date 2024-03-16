#ifndef __GLOBAL_STATUS__H
#define __GLOBAL_STATUS__H
// @11.0592MHz
#include <intrins.h>
#include "typedef.h"

#define STATUS_CONNECTING 0
#define STATUS_CONNECTED 1
extern xdata u8 g_status;

void Global_Status_Timer_Init();
void Global_Status_Timer_Callback();
void Global_Status_Set_Status(u8 status);

void Global_Status_Hear_Beat_Timer_Init();
void Global_Status_Heart_Beat_Timer_Callback();
void Global_Status_Do_Heart_Beat(bit hb);

#endif