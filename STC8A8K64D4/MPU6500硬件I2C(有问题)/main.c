/*#include "stc/stc8a8k64d4.H"
#include "stc/stc8a_gpio.H"
#include "stc/STC8A_I2C.h"
#include "stc/stc8a_switch.h"
#include "stc/stc8a_nvic.h"*/
#include "typedef.h"
/*#include "12864/oled12864.h"
#include "mpu6500/mpu6500.h"
#include "stdio.h"*/

float xdata g_AX, g_AY = 0, g_AZ = 0;
float xdata g_GX = 0, g_GY = 0, g_GZ = 0;

/*void GPIO_Config() {
	GPIO_InitTypeDef conf;
	conf.Mode = GPIO_OUT_OD;
	conf.Pin = GPIO_Pin_All;
	GPIO_Inilize(GPIO_P0, &conf);
	
	P1_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
}

void I2C_Config() {
	I2C_InitTypeDef conf;
	conf.I2C_Mode = I2C_Mode_Master; //����ѡ��   I2C_Mode_Master, I2C_Mode_Slave
	conf.I2C_Enable = ENABLE; //I2C����ʹ��,   ENABLE, DISABLE
	conf.I2C_MS_WDTA = DISABLE; //����ʹ���Զ�����,  ENABLE, DISABLE
	conf.I2C_Speed = 16; //�����ٶ�=Fosc/2/(Speed*2+4),      0~63
	I2C_Init(&conf);
	NVIC_I2C_Init(I2C_Mode_Master, DISABLE,Priority_0); //����ģʽ, I2C_Mode_Master, I2C_Mode_Slave; �ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	I2C_SW(I2C_P14_P15);
}*/

void main() {
	/*GPIO_Config();
	OLED_Init();
	I2C_Config();*/
}