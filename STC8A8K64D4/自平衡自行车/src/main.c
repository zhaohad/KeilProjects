#include "stc8a8k64d4.h"
#include "typedef.h"
#include "stc8a_gpio.h"
#include "stc8a_i2c.h"
#include "shanwai.h"
#include "mpu6500.h"
#include "stdio.h"
#include "servo.h"
#include "stc8a_pwm15bit.h"
#include "oled12864.h"

float idata g_AX = 0, g_AY = 0, g_AZ = 0;
float idata g_GX = 0, g_GY = 0, g_GZ = 0;

#define FACTOR_DEGREE 0.6f 

#define MAX_FILTER_DEGREE 10
#define MAX_INVTURNINTERVAL 5
u8 idata g_LastDegree;
bit idata g_LastDirection;
u8 idata g_TurnInterval;
u8 filterDegree(u8 d);

void MPU6500_GPIO_Config() {
	P1_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
}

void Servo_GPIO_Config() {
	P4_MODE_IO_PU(GPIO_Pin_0);
}

void MPU6500_I2C_Config() {
	I2C_InitTypeDef conf;
	conf.I2C_Mode = I2C_Mode_Master; //主从选择   I2C_Mode_Master, I2C_Mode_Slave
	conf.I2C_Enable = ENABLE; //I2C功能使能,   ENABLE, DISABLE
	conf.I2C_MS_WDTA = DISABLE; //主机使能自动发送,  ENABLE, DISABLE
	conf.I2C_Speed = 16; //总线速度=Fosc/2/(Speed*2+4),      0~63
	I2C_Init(&conf);

	I2C_SW(I2C_P14_P15);
}

void MOTOR1_GPIO_Config() {
	P2_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
}

void MOTOR1_PWM15bit_init() {
	PWM15_InitTypeDef PWM15_InitStructure;

	PWM15_InitStructure.PWM_Enable    = ENABLE;		//PWM使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Period    = 0x7fff;		//PWM周期,  0~0x7fff
	PWM15_InitStructure.PWM_Clock_Sel = PWM_CLK_SYS; //时钟源选择,  PWM_CLK_SYS, PWM_CLK_TM2
	PWM15_InitStructure.PWM_Clock_PS  = 0;				//系统时钟分频参数(PS+1分频),  0~15
	PWM15_InitStructure.PWM_CInt      = DISABLE;	//计数器归零中断使能,  ENABLE, DISABLE
	PWM15_InitStructure.PWM_Counter   = ENABLE;		//计数器使能,  ENABLE, DISABLE
	PWM15_Init(&PWM15_InitStructure);
	
	// PWM15Duty(PWM15_1, 0, 999);		//PWM_ID, 输出低电平位置, 输出高电平位置
	PWMChannelCtrl(PWM15_0,ENABLE,0,DISABLE,DISABLE,DISABLE);	//PWM_ID, 输出使能, 初始电平, PWM中断, 第二个触发点中断, 第一触发点中断
}

void OLED12864_GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_PP;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
}

void main() {
	
	// UART Init
	UART_config();
	
	// MPU6500 Init
	MPU6500_GPIO_Config();
	MPU6500_I2C_Config();
	MPU6500_Init();
	
	// Servo Init
	Servo_GPIO_Config();
	Servo_Init();
	
	// Motor1 Init
	MOTOR1_GPIO_Config();
	P_MOTOR_A = 1;
	P_MOTOR_B = 0;
	
	// OLED12864 Init
	OLED12864_GPIO_Config();
	OLED_Init();

	EA = 1;

	while (1) {
		float idata values[6];
		float idata angle[2];
		char idata str[16];
		u8 idata d;
		char idata diff;
		MPI6500_GetGAData(values);
		MPU6500_IMU_Update_arr(values, angle);
		// SHANWAI_sendWaveValue(&angle, sizeof(angle[0]), 2);
		sprintf(str, "nX = %f", angle[0]);
		OLED_ShowString8(0, 0, str);
		sprintf(str, "nY = %f", angle[1]);
		OLED_ShowString8(0, 1, str);
		diff = (int) angle[1] / FACTOR_DEGREE;
		sprintf(str, "diff = %03d", (int) diff);
		OLED_ShowString8(0, 2, str);
		d = 90 - diff;
		/*sprintf(str, "d = %03d", (int) d);
		OLED_ShowString8(0, 3, str);
		sprintf(str, "l_d = %03d", (int) g_LastDegree);
		OLED_ShowString8(0, 4, str);*/
		d = filterDegree(d);
		if (d < 50) {
			d = 50;
		} else if (d > 130) {
			d = 130;
		}
		/*sprintf(str, "f_d = %03d", (int) d);
		OLED_ShowString8(0, 5, str);*/
		Servo_Set_Target_Degree(d);
		// Servo_Set_Target_Degree(90);
	}
}

u8 filterDegree(u8 d) {
	u8 idata diff;
	bit idata dir;
	if (d > 90 + 10) {
		d = 130;
	} else if (d < 90 - 10) {
		d = 50;
	} else {
		d = 90;
	}
	
	if (g_LastDegree > d) {
		diff = g_LastDegree - d;
		dir = 1;
	} else {
		diff = d - g_LastDegree;
		dir = 0;
	}

	g_TurnInterval++;
	if (dir != g_LastDirection) {
		if (g_TurnInterval < MAX_INVTURNINTERVAL) {
			return g_LastDegree;
		}
	}

	if (diff > MAX_FILTER_DEGREE) {
		g_LastDegree = d;
		g_LastDirection = dir;
		g_TurnInterval = 0;
	}
	return g_LastDegree;
}