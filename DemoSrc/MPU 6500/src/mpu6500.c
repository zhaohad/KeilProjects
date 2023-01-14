#include "mpu6500.h"
#include <intrins.h>
#include "I2CBus.h"

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