#ifndef __ACTION_H__
#define __ACTION_H__

#include "typedef.h"

extern xdata u8 g_action_cmd;
extern xdata u8 g_action_cmd_v;
extern xdata u8 g_action_cmd_next;
extern xdata u8 g_action_cmd_v_next;

void Action_Timer_Init();
void Action_Timer_Callback();


#endif