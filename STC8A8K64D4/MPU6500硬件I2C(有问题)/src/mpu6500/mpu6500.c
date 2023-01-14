#include "mpu6500.h"

void Single_WriteI2C(u8 REG_Address,uchar REG_data) {
    I2CBus_Start();                  //起始信号
    I2CBus_Write(MPU_ADDR);   //发送设备地址+写信号
    I2CBus_Write(REG_Address);    //内部寄存器地址，
    I2CBus_Write(REG_data);       //内部寄存器数据，
    I2CBus_Stop();                   //发送停止信号
}

void InitMPU6500() {
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}

/*void MPU6500_Init() {
	u8 p[1] = {0x00};
	I2C_writeNbyte_DAddr(MPU_ADDR, PWR_MGMT_1, p, 1);
	p[0] = 0x07;
	I2C_writeNbyte_DAddr(MPU_ADDR, SMPLRT_DIV, p, 1);
	p[0] = 0x06;
	I2C_writeNbyte_DAddr(MPU_ADDR, CONFIG, p, 1);
	p[0] = 0x18;
	I2C_writeNbyte_DAddr(MPU_ADDR, GYRO_CONFIG, p, 1);
	p[0] = 0x01;
	I2C_writeNbyte_DAddr(MPU_ADDR, ACCEL_CONFIG, p, 1);
}*/

uchar Single_ReadI2C(uchar REG_Address) {
	uchar REG_data;
	I2CBus_Start();                   //起始信号
	I2CBus_Write(MPU_ADDR);    //发送设备地址+写信号
	I2CBus_Write(REG_Address);     //发送存储单元地址，从0开始	
	I2CBus_Start();                   //起始信号
	I2CBus_Write(MPU_ADDR + 1);  //发送设备地址+读信号
	REG_data = I2CBus_Read(1);       //读出寄存器数据
	I2CBus_Stop();                    //停止信号
	return REG_data;
}

int GetData(uchar REG_Address) {
	uchar H,L;
	H = Single_ReadI2C(REG_Address);
	L = Single_ReadI2C(REG_Address + 1);
	return ((H << 8) + L);   //合成数据
}

/*int MPU6500_GetData(uchar REG_Address) {
	uchar H, L;
	I2C_ReadNbyte_DAddr(MPU_ADDR, REG_Address, &H, 1);
	I2C_ReadNbyte_DAddr(MPU_ADDR, REG_Address, &L, 1);
	return ((H << 8) + L);
}*/