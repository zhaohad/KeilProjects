#include "STC8A8K64D4.H"
#include "STC8A_GPIO.H"
#include "RZ7899.h"

u8 g_RZ7899_State = RUN_STATE_NONE;

// 根据使用的引脚不同需要对init方法进行修改
void RZ7899_Init() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2, &conf);
}

u8 RZ7899_GetState() {
	return g_RZ7899_State;
}

void RZ7899_Run(u8 state) {
	g_RZ7899_State = state;
	switch (state) {
		case RUN_STATE_NONE: {
			PIN_BI = 0;
			PIN_FI = 0;
			break;
		}
		case RUN_STATE_NORM: {
			PIN_BI = 0;
			PIN_FI = 1;
			break;
		}
		case RUN_STATE_INV: {
			PIN_BI = 1;
			PIN_FI = 0;
			break;
		}
		case RUN_STATE_STOP: {
			PIN_BI = 1;
			PIN_FI = 1;
			break;
		}
	}
}