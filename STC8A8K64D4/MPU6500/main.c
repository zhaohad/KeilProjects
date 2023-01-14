#include "stc/stc8a8k64d4.H"
#include "stc/stc8a_gpio.H"
#include "typedef.h"
#include "12864/oled12864.h"
#include "uart/uart.h"
#include "mpu6500/mpu6500.h"
#include "stdio.h"

float xdata g_AX, g_AY = 0, g_AZ = 0;
float xdata g_GX = 0, g_GY = 0, g_GZ = 0;

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_OD;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	GPIO_Config();
	OLED_Init();
	InitMPU6500();
	while (1) {
		char str[16];
		g_AX = GetData(ACCEL_XOUT_H) / (float) 16384;
		sprintf(str, "AX = %f", g_AX);
		OLED_ShowString8(0, 0, str);
		sprintf(str, "AY = %f", GetData(ACCEL_YOUT_H) / (float) 16384);
		OLED_ShowString8(0, 1, str);
		sprintf(str, "AZ = %f", GetData(ACCEL_ZOUT_H) / (float) 16384);
		OLED_ShowString8(0, 2, str);
		sprintf(str, "GX = %f", GetData(GYRO_XOUT_H) / (float) 131);
		OLED_ShowString8(0, 3, str);
		sprintf(str, "GY = %f", GetData(GYRO_YOUT_H) / (float) 131);
		OLED_ShowString8(0, 4, str);
		sprintf(str, "GZ = %f", GetData(GYRO_ZOUT_H) / (float) 131);
		OLED_ShowString8(0, 5, str);
	}
}