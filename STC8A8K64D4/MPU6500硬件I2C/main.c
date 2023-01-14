#include "stc8a8k64d4.h"
#include "stc8a_gpio.h"
#include "STC8A_I2C.h"
#include "stc8a_switch.h"
#include "stc8a_nvic.h"
#include "typedef.h"
#include "oled12864.h"
#include "mpu6500.h"
#include "stdio.h"
#include "shanwai.h"
#include "uart.h"

float idata g_AX = 0, g_AY = 0, g_AZ = 0;
float idata g_GX = 0, g_GY = 0, g_GZ = 0;

void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
	
	P1_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
}

void I2C_Config() {
	I2C_InitTypeDef conf;
	conf.I2C_Mode = I2C_Mode_Master; //主从选择   I2C_Mode_Master, I2C_Mode_Slave
	conf.I2C_Enable = ENABLE; //I2C功能使能,   ENABLE, DISABLE
	conf.I2C_MS_WDTA = DISABLE; //主机使能自动发送,  ENABLE, DISABLE
	conf.I2C_Speed = 16; //总线速度=Fosc/2/(Speed*2+4),      0~63
	I2C_Init(&conf);

	I2C_SW(I2C_P14_P15);
}

void main() {
	GPIO_Config();
	OLED_Init();
	I2C_Config();
	MPU6500_Init();
	UART_Init_110592MHz_9600bps(NULL);
	while (1) {
		char idata str[16];
		float idata values[6];
		float angleX, angleY;
		g_AX = MPU6500_GetData(ACCEL_XOUT_H) / (float) 16384;
		sprintf(str, "AX = %f", g_AX);
		OLED_ShowString8(0, 0, str);
		g_AY = MPU6500_GetData(ACCEL_YOUT_H) / (float) 16384;
		sprintf(str, "AY = %f", g_AY);
		OLED_ShowString8(0, 1, str);
		g_AZ = MPU6500_GetData(ACCEL_ZOUT_H) / (float) 16384;
		sprintf(str, "AZ = %f", g_AZ);
		OLED_ShowString8(0, 2, str);
		g_GX = MPU6500_GetData(GYRO_XOUT_H) / (float) 131;
		sprintf(str, "GX = %f", g_GX);
		OLED_ShowString8(0, 3, str);
		g_GY = MPU6500_GetData(GYRO_YOUT_H) / (float) 131;
		sprintf(str, "GY = %f", g_GY);
		OLED_ShowString8(0, 4, str);
		g_GZ = MPU6500_GetData(GYRO_ZOUT_H) / (float) 131;
		sprintf(str, "GZ = %f", g_GZ);
		OLED_ShowString8(0, 5, str);
		values[0] = g_AX;
		values[1] = g_AY;
		values[2] = g_AZ;
		values[3] = g_GX;
		values[4] = g_GY;
		values[5] = g_GZ;
		SHANWAI_sendWaveValue(values, sizeof(values[0]), 6);
		MPU6500_IMU_Update(g_GX, g_GY, g_GZ, g_AX, g_AY, g_AZ, &angleX, &angleY);
		sprintf(str, "nX = %f", angleX);
		OLED_ShowString8(0, 6, str);
		sprintf(str, "nY = %f", angleY);
		OLED_ShowString8(0, 7, str);
	}
}