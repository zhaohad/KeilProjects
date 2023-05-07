#include "STC8A8K64D4.H"
#include "STC8A_GPIO.H"
#include "typedef.h"
#include "RZ7899.h"
#include "oled12864.h"
#include "STC8A_ADC.h"
#include "rotationCounter.h"
#include "dtos.h"
#include "test.h"

void INT_Init();
void StateInit_check();
void Interrupt_check();
bit IsInterrupted(bit clearFlag);
void CMD_Check();
void CMD_Work();

bit gIntFlag;
bit gIsInInt;

u8 g_state;
u8 g_initStage;
int g_MaxCount;

u8 g_CMD;
u8 g_CMD_Value;
u8 g_CMD_Stage;

#define INITSTAGE_NONE 0
#define INITSTAGE_TO_MIN 1
#define INITSTAGE_TO_MIN_START 2
#define INITSTAGE_TO_MAX 3
#define INITSTAGE_TO_START 4
#define INITSTAGE_READY 5

#define STATE_IDLE 0
#define STATE_INIT 1
#define STATE_BUSY 2

#define CMD_NONE 0
#define CMD_STOP 1
#define CMD_GO_UP 2
#define CMD_GO_DOWN 3
#define CMD_GO_MAX 4
#define CMD_GO_MIN 5
#define CMD_GO_VALUE 6

#define CMD_STAGE_NONE 0
#define CMD_STAGE_UP 1
#define CMD_STAGE_UP_ADJUST 2
#define CMD_STAGE_UP_LIMIT 3
#define CMD_STAGE_DOWN 4
#define CMD_STAGE_DOWN_ADJUST 5
#define CMD_STAGE_DOWN_LIMIT 6

void main() {
	RZ7899_Init();

	OLED_Init();
	OLED_ShowString8(0, 0, "START");
	
	// RZ7899_Run(RUN_STATE_INV);
	// while(1);
	
	RotationCounter_init();
	
	g_state = STATE_INIT;
	g_initStage = INITSTAGE_NONE;
	g_CMD = CMD_NONE;
	g_CMD_Stage = CMD_STAGE_NONE;
	
	// Test_All();
	
	while(1) {
		int rc;
		char str[20];
		u16 adc;
		float r;
		
		OLED_Clear();

		Interrupt_check();
		RotationCounter_check();
		CMD_Check();

		rc = RotationCounter_getRotationCount();
		intToS(rc, str, 20);
		// adc = Get_ADCResult(ADC_CHANEL);
		// r = adc / 4096.f * 100.f;
		// floatToS(r, str, 20);
		// sprintf(str, "maxcount = %d", g_MaxCount);
		
		OLED_ShowString8(0, 3, str);
		
		switch (g_state) {
			case STATE_INIT: {
				StateInit_check();
				if (g_initStage == INITSTAGE_READY) {
					g_state = STATE_IDLE;
				}
				break;
			}
			case STATE_IDLE: {
				if (g_CMD != CMD_NONE) {
					g_state = STATE_BUSY;
					CMD_Work();
				}
				break;
			}
			case STATE_BUSY: {
				CMD_Work();
				break;
			}
			default:
				break;
		}
		Test_Interruption_Check(5);
	}
}

void INT_Init() {
	GPIO_InitTypeDef conf;
	GPIO_InitTypeDef conf1;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P5, &conf);
	P_INT = 1;
	gIsInInt = 0;

	conf1.Mode = GPIO_PullUp;
	conf1.Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Inilize(GPIO_P0, &conf);
	P_INT = 1;
	
	P_INT_01 = 1;
	P_INT_02 = 1;
	P_INT_03 = 1;
	P_INT_04 = 1;
	P_INT_05 = 1;
	P_INT_06 = 1;
	P_INT_07 = 1;
}

void Interrupt_check() {
	if (!P_INT && !gIsInInt) {
		gIntFlag = 1;
		gIsInInt = 1;
	}
	if (gIsInInt && P_INT) {
		gIsInInt = 0;
		gIntFlag = 0;
	}
}

bit IsInterrupted(bit clearFlag) {
	bit res = gIntFlag;
	if (clearFlag) {
		gIntFlag = 0;
	}
	return res;
}

void StateInit_check() {
	switch (g_initStage) {
		case INITSTAGE_NONE: {
			OLED_ShowString8(0, 2, "INITSTAGE_NONE");
			RZ7899_Run(RUN_STATE_INV);
			g_initStage = INITSTAGE_TO_MIN;
			break;
		}
		case INITSTAGE_TO_MIN: {
			OLED_ShowString8(0, 2, "INITSTAGE_TO_MIN");
			if (IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_NORM);
				g_initStage = INITSTAGE_TO_MIN_START;
			}
			break;
		}
		case INITSTAGE_TO_MIN_START: {
			OLED_ShowString8(0, 2, "INITSTAGE_TO_MIN_START");
			if (!IsInterrupted(0)) {
				RotationCounter_reset();
				g_initStage = INITSTAGE_TO_MAX;
			}
			break;
		}
		case INITSTAGE_TO_MAX: {
			OLED_ShowString8(0, 2, "INITSTAGE_TO_MAX");
			if (IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_INV);
				g_initStage = INITSTAGE_TO_START;
			}
			break;
		}
		case INITSTAGE_TO_START: {
			OLED_ShowString8(0, 2, "INITSTAGE_TO_START");
			if (!IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_STOP);
				g_initStage = INITSTAGE_READY;
				g_MaxCount = RotationCounter_getRotationCount();
			}
			break;
		}
		case INITSTAGE_READY: {
			OLED_ShowString8(0, 2, "INITSTAGE_READY");
			break;
		}
	}
}

void CMD_Check() {
	if (!P_INT_01) {
		P_INT_01 = 1;
		P_INT_02 = 1;
		P_INT_03 = 1;
		P_INT_04 = 1;
		P_INT_05 = 1;
		P_INT_06 = 1;
		P_INT_07 = 1;
		g_CMD = CMD_STOP;
		OLED_ShowString8(0, 4, "01 INT");
	} else if (!P_INT_02) {
		OLED_ShowString8(0, 4, "02 INT");
		g_CMD = CMD_GO_UP;
	} else if (!P_INT_03) {
		OLED_ShowString8(0, 4, "03 INT");
		g_CMD = CMD_GO_DOWN;
	} else if (!P_INT_04) {
		OLED_ShowString8(0, 4, "04 INT");
		g_CMD = CMD_GO_MAX;
	} else if (!P_INT_05) {
		OLED_ShowString8(0, 4, "05 INT");
		g_CMD = CMD_GO_MIN;
	} else if (!P_INT_06) {
		OLED_ShowString8(0, 4, "06 INT");
		g_CMD = CMD_GO_VALUE;
		g_CMD_Value = 50;
	} else if (!P_INT_07) {
		OLED_ShowString8(0, 4, "07 INT");
		g_CMD = CMD_GO_VALUE;
		g_CMD_Value = 20;
	} else {
		OLED_ShowString8(0, 4, "NO INT");
	}
}

void CMD_Work() {
	switch (g_CMD) {
		case CMD_NONE: {
			OLED_ShowString8(0, 2, "CMD_NONE");
			g_state = STATE_IDLE;
			g_CMD_Stage = CMD_STAGE_NONE;
			break;
		}
		case CMD_STOP: {
			OLED_ShowString8(0, 2, "CMD_STOP");
			RZ7899_Run(RUN_STATE_STOP);
			g_state = STATE_IDLE;
			g_CMD = CMD_NONE;
			g_CMD_Stage = CMD_STAGE_NONE;
			break;
		}
		case CMD_GO_UP:
		case CMD_GO_MAX: {
			OLED_ShowString8(0, 2, "CMD_GO_UP OR MAX");
			if (g_CMD_Stage != CMD_STAGE_UP && g_CMD_Stage == CMD_STAGE_NONE) {
				RZ7899_Run(RUN_STATE_NORM);
				g_CMD_Stage = CMD_STAGE_UP;
			}
			if (g_CMD_Stage == CMD_STAGE_UP && IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_INV);
				g_CMD_Stage = CMD_STAGE_UP_ADJUST;
			}
			if (g_CMD_Stage == CMD_STAGE_UP_ADJUST && !IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_STOP);
				g_CMD_Stage = CMD_STAGE_UP_LIMIT;
				if (g_CMD == CMD_GO_MAX) {
					g_CMD = CMD_STOP;
					g_CMD_Stage = CMD_STAGE_NONE;
				}
			}
			if (g_CMD == CMD_GO_UP && P_INT_02) {
				g_CMD = CMD_STOP;
				g_CMD_Stage = CMD_STAGE_NONE;
			}
			break;
		}
		case CMD_GO_DOWN:
		case CMD_GO_MIN:{
			OLED_ShowString8(0, 2, "CMD_GO_DOWN OR MIN");
			if (g_CMD_Stage != CMD_STAGE_DOWN && g_CMD_Stage == CMD_STAGE_NONE) {
				RZ7899_Run(RUN_STATE_INV);
				g_CMD_Stage = CMD_STAGE_DOWN;
			}
			if (g_CMD_Stage == CMD_STAGE_DOWN && IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_NORM);
				g_CMD_Stage = CMD_STAGE_DOWN_ADJUST;
			}
			if (g_CMD_Stage == CMD_STAGE_DOWN_ADJUST && !IsInterrupted(0)) {
				RZ7899_Run(RUN_STATE_STOP);
				g_CMD_Stage = CMD_STAGE_DOWN_LIMIT;
				if (g_CMD == CMD_GO_MIN) {
					g_CMD = CMD_STOP;
					g_CMD_Stage = CMD_STAGE_NONE;
				}
			}
			if (g_CMD == CMD_GO_DOWN && P_INT_03) {
				g_CMD = CMD_STOP;
				g_CMD_Stage = CMD_STAGE_NONE;
			}
			break;
		}
		case CMD_GO_VALUE: {
			OLED_ShowString8(0, 2, "CMD_GO_VALUE");
			break;
		}
	}
}