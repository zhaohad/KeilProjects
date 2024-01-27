#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "typedef.h"
#include "servo.h"
#include "delay.h"

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
	GPIO_Inilize(GPIO_P1, &conf);
	GPIO_Inilize(GPIO_P2, &conf);
}

bit rec = 0;

void main() {
	GPIO_Config();
	Servo_Init();
	if (!rec) {
		Servo_Set_Target_Degree(90);
	}
	while (1) {
		if (rec) {
			int i = 0;
			int f = -1;
			for (i = 0; i <= 180; i += f) {
				if (i == 0 || i == 180) {
					f = -f;
				}
				Servo_Set_Target_Degree(i);
				delay_ms(1);
			}
		}
	}
}