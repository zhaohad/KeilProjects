#include "mpu6500.h"
#include <math.H>

#define	pi		3.14159265f                           
//#define	Kp		0.8f                        
//#define	Ki		0.001f
//#define	halfT	0.004f
                           
#define	Kp		400.0f                        
#define	Ki		0.1f
#define	halfT	0.001f

float idata q0 = 1, q1 = 0, q2 = 0, q3 = 0;   
float idata exInt = 0, eyInt = 0, ezInt = 0;

void MPU6500_Init() {
	u8 p[1] = {0x00};
	I2C_WriteNbyte_DAddr(MPU_ADDR, PWR_MGMT_1, p, 1);
	p[0] = 0x07;
	I2C_WriteNbyte_DAddr(MPU_ADDR, SMPLRT_DIV, p, 1);
	p[0] = 0x06;
	I2C_WriteNbyte_DAddr(MPU_ADDR, CONFIG, p, 1);
	p[0] = 0x18;
	I2C_WriteNbyte_DAddr(MPU_ADDR, GYRO_CONFIG, p, 1);
	p[0] = 0x01;
	I2C_WriteNbyte_DAddr(MPU_ADDR, ACCEL_CONFIG, p, 1);
}

int MPU6500_GetData(uchar REG_Address) {
	uchar H, L;
	I2C_ReadNbyte_DAddr(MPU_ADDR, REG_Address, &H, 1);
	I2C_ReadNbyte_DAddr(MPU_ADDR, REG_Address, &L, 1);
	return ((H << 8) + L);
}
void MPI6500_GetGAData(float outV[6]) {
	outV[0] = MPU6500_GetData(GYRO_XOUT_H) / (float) 131;
	outV[1] = MPU6500_GetData(GYRO_YOUT_H) / (float) 131;
	outV[2] = MPU6500_GetData(GYRO_ZOUT_H) / (float) 131;
	outV[3] = MPU6500_GetData(ACCEL_XOUT_H) / (float) 16384;
	outV[4] = MPU6500_GetData(ACCEL_YOUT_H) / (float) 16384;
	outV[5] = MPU6500_GetData(ACCEL_ZOUT_H) / (float) 16384;
}

void MPU6500_IMU_Update_arr(float v[6], float outAngle[2]) {
	MPU6500_IMU_Update(v[0], v[1], v[2], v[3], v[4], v[5], outAngle, outAngle + 1);
}

void MPU6500_IMU_Update(float gx, float gy, float gz, float ax, float ay, float az, float *angleX, float *angleY) {
	float idata norm;
	float idata vx, vy, vz;
	float idata ex, ey, ez;

	norm = sqrt(ax * ax + ay * ay + az * az);	//把加速度计的三维向量转成单维向量   
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

	// 下面是把四元数换算成《方向余弦矩阵》中的第三列的三个元素。 
	// 根据余弦矩阵和欧拉角的定义，地理坐标系的重力向量，转到机体坐标系，正好是这三个元素
	// 所以这里的vx vy vz，其实就是当前的欧拉角（即四元数）的机体坐标参照系上，换算出来的
	// 重力单位向量。
	vx = 2 * (q1 * q3 - q0 * q2);
	vy = 2 * (q0 * q1 + q2 * q3);
	vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3 ;

	ex = (ay * vz - az * vy);
	ey = (az * vx - ax * vz);
	ez = (ax * vy - ay * vx);

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp * ex + exInt;
	gy = gy + Kp * ey + eyInt;
	gz = gz + Kp * ez + ezInt;

	q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
	q1 = q1 + ( q0 * gx + q2 * gz - q3 * gy) * halfT;
	q2 = q2 + ( q0 * gy - q1 * gz + q3 * gx) * halfT;
	q3 = q3 + ( q0 * gz + q1 * gy - q2 * gx) * halfT;

	norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;

	*angleX = asin(2 * (q0 * q2 - q1 * q3 )) * 57.2957795f; // 俯仰 换算成度
	*angleY = asin(2 * (q0 * q1 + q2 * q3 )) * 57.2957795f; // 横滚
}