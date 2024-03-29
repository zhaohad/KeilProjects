#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "typedef.h"
#include "servo_t0.h"
#include "servo_t1.h"
#include "delay.h"
#include "action_def.h"
#include "action.h"
#include "dtos.h"
#include "G01_S.h"
#include "oled12864.h"
#include <stdlib.h>
#include <stdio.h>
#include "communication_protocol.h"

#define CNT_SERVOS 6
#define DMS_MIN 10
#define DMS_NORM 32
#define INTER_ANGLE 30


void OLED_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_2;
	GPIO_Inilize(GPIO_P4, &conf);

	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P2, &conf);
}

void G01_S_GPIO_config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;	
	conf.Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P0, &conf);
	
	conf.Pin = GPIO_Pin_3;
	GPIO_Inilize(GPIO_P4, &conf);
	
	NRF24L01_Gpio_Init();
}

void SERVO_GPIO_Config() {
	xdata GPIO_InitTypeDef conf;
	conf.Mode = GPIO_PullUp;
	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2, &conf);

	conf.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P0, &conf);

	conf.Pin = GPIO_Pin_7 | GPIO_Pin_2;
	GPIO_Inilize(GPIO_P3, &conf);
	
	conf.Pin = GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P4, &conf);
	
	conf.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P5, &conf);
}

void initing_delay() {
	xdata u8 i = 0;
	for (i = 0; i < 5; ++i) {
		delay_ms(254);
	}
}

void delay_per_degree(u8 dms) {
	xdata u8 i;
	for (i = 0; i < 1; ++i) {
		// delay_ms(32);
		delay_ms(dms);
	}
}

void to_initial_pos() {
	Servo_T0_Set_Target_Degree((u8 *) ACT_TO_INIT[0]);
	Servo_T1_Set_Target_Degree((u8 *) ACT_TO_INIT[0] + CNT_SERVOS);
}

// 使用 30.000 MHz烧录
void main() {
	bit exist;
	SERVO_GPIO_Config();
	Servo_T0_Init();
	Servo_T1_Init();
	OLED_GPIO_Config();
	OLED_Init();
	G01_S_GPIO_config();

	to_initial_pos();
	initing_delay();
	Action_Timer_Init();

	exist = NRF24L01_check();
	
	RF24L01_Init();
	_nop_();_nop_();_nop_();_nop_();_nop_();


	RF24L01_Set_Mode(MODE_RX); //接收模式
	_nop_();_nop_();_nop_();_nop_();_nop_();
	
	OLED_ShowBootIMG();

	while(1) {
		xdata u8 forwardV = 0;
		xdata u8 backwardV = 0;
		bit turnLeft = 0;
		bit turnRight = 0;
		bit actDance = 0;
		bit actRock = 0;
		bit actWangtian = 0;

		xdata uint8_t rx;
		xdata uint8_t g_rece[MAX_INTERACTIVE_CNT * 3];
		rx = NRF24L01_RxPacket(g_rece); //接收字节
		
		if (rx >= 2) {
			xdata u8 i;
			for (i = 0; i < rx; ++i) {
				u8 cmd = g_rece[i];
				xdata v = g_rece[i + 1];
				++i;
				switch (cmd) {
					case KEY_JOINSTICK_LEFT_V:
						if (v > 90) { forwardV = 5; } else if (v > 80) { forwardV = 4; } else if (v > 70) { forwardV = 3; } else if (v > 60) { forwardV = 2; } else if (v > 50) { forwardV = 1; } else if (v < 10) { backwardV = 5; } else if (v < 20) { backwardV = 4; } else if (v < 30) { backwardV = 3; } else if (v < 40) { backwardV = 2; } else if (v < 50) { backwardV = 1; }
						break;
					case KEY_K5:
						turnLeft = v;
						break;
					case KEY_K7:
						turnRight = v;
						break;
					case KEY_K10:
						actRock = v;
						break;
					case KEY_K11:
						actDance = v;
						break;
					case KEY_K4:
						actWangtian = v;
						break;
				}
			}
		}
			
		if (forwardV) {
			g_action_cmd_next = ACTION_FORWARD;
			g_action_cmd_v_next = forwardV;
		} else if (backwardV) {
			g_action_cmd_next = ACTION_BACKWARD;
			g_action_cmd_v_next = backwardV;
		} else if (turnLeft) {
			g_action_cmd_next = ACTION_TURN_LEFT;
		} else if (turnRight) {
			g_action_cmd_next = ACTION_TURN_RIGHT;
		} else if (actRock) {
			g_action_cmd_next = ACTION_ROCK;
		} else if (actWangtian) {
			g_action_cmd_next = ACTION_WANGTIAN;
		}	else if (actDance) {
			g_action_cmd_next = ACTION_DANCE;
		} else {
			g_action_cmd_next = ACTION_NONE;
			g_action_cmd_v_next = 0;
		}
	}
}