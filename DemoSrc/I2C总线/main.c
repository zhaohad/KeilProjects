#include <reg51.h>
#include <intrins.h>
#include "DigitalDisplay_8.h"
#include "I2CBus.h"

sbit lastAck = P1 ^ 0;
sbit err = P1 ^ 1;

unsigned char analog1 = 0;
unsigned char analog2 = 0;
unsigned char lastAnalog1 = 1;
unsigned char lastAnalog2 = 1;

unsigned char nums[8];

void Display_Analog();

void main() {
	err = 1;

	while(1) {
		I2CBus_Start();
		lastAck = I2CBus_Write(0x90);
		err &= ~lastAck;
		lastAck = I2CBus_Write(0x41); // 0x41 һֱ�������״̬������LED����˸
		err &= ~lastAck;
		// I2CBus_Stop();
		I2CBus_Start(); // ���Բ�Stopֱ��start
		lastAck = I2CBus_Write(0x91);
		err &= ~lastAck;
		analog2 = I2CBus_Read(1); // PCF8591T����Ҫ�����ݷŵ����ڲ�buffer��ÿ�δ���buffer�з������ݣ��������ݻ��д�λ
		I2CBus_Stop();
		
		I2CBus_Start();
		lastAck = I2CBus_Write(0x90);
		err &= ~lastAck;
		lastAck = I2CBus_Write(0x43); // 0x43 һֱ�������״̬������LED����˸
		err &= ~lastAck;
		// I2CBus_Stop();
		I2CBus_Start(); // ���Բ�Stopֱ��start
		lastAck = I2CBus_Write(0x91);
		err &= ~lastAck;
		analog1 = I2CBus_Read(1);  // PCF8591T����Ҫ�����ݷŵ����ڲ�buffer��ÿ�δ���buffer�з������ݣ��������ݻ��д�λ
		I2CBus_Stop();
		
		if (lastAnalog1 != analog1) {
			lastAnalog1 = analog1;
			I2CBus_Start();
			lastAck = I2CBus_Write(0x90);
			err &= ~lastAck;
			lastAck = I2CBus_Write(0x40);
			err &= ~lastAck;
			lastAck = I2CBus_Write(analog1);
			err &= ~lastAck;
			I2CBus_Stop();

			nums[0] = analog1 & 0x0f;
			nums[1] = analog1 >> 4;
		}
		if (lastAnalog2 != analog2) {
			lastAnalog2 = analog2;

			nums[2] = analog2 & 0x0f;
			nums[3] = analog2 >> 4;
		}
		DigitalDisplay_8_Display(nums, 4);
	}
}

void Display_Analog() {
	nums[2] = analog2 & 0x0f;
	nums[3] = analog2 >> 4;
	DigitalDisplay_8_Display(nums, 8);
}