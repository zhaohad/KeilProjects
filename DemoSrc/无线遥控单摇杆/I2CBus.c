#include <reg51.h>
#include "I2CBus.h"
#include <intrins.h>

/**
 * 晶振：12MHz
 * 工作模式：12T
 * 指令周期：1微秒
 */

void I2CBus_Start() {
	PIN_SDA = 1;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4.7us
	PIN_SDA = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	PIN_SCL = 0;
}

void I2CBus_Stop() {
	PIN_SDA = 0;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	PIN_SDA = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4.7us
	PIN_SCL = 0;
}

bit I2CBus_Write(uint8_t d) {
	bit s;
	// 0
	PIN_SCL = 0;
	s = (d >> 7) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 1
	PIN_SCL = 0;
	s = (d >> 6) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 2
	PIN_SCL = 0;
	s = (d >> 5) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 3
	PIN_SCL = 0;
	s = (d >> 4) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 4
	PIN_SCL = 0;
	s = (d >> 3) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 5
	PIN_SCL = 0;
	s = (d >> 2) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 6
	PIN_SCL = 0;
	s = (d >> 1) & 0x01; // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// 7
	PIN_SCL = 0;
	s = d & 0x01;
  _nop_();  // 以上 > 4.7us
	PIN_SDA = s;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us

	PIN_SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4.7us
	PIN_SDA = 1;
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	// while (PIN_SDA);
	
	s = PIN_SDA;
	PIN_SCL = 0;
	return s;
}

uint8_t I2CBus_Read(bit fi) {
	uint8_t d;
	// 0
	PIN_SCL = 0;
	d = 0x00;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 1
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 2
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 3
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 4
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 5
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 6
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	// 7
	PIN_SCL = 0;
	d <<= 1;
	_nop_();_nop_();_nop_(); // 以上5us > 4.7us
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	d |= PIN_SDA;
	
	PIN_SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4.7us
	PIN_SDA = fi; // ACK or NACK
	PIN_SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); // 5us > 4us
	PIN_SCL = 0;
	
	return d;
}