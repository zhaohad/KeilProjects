#include <reg51.h>
#include <intrins.h>
#include "G01_S.h"
#include "delay.h"
#include "I2CBus.h"
#include "HandleControl.h"
#include "SteeringSG90.h"

sbit P10 = P1 ^ 0;
sbit P11 = P1 ^ 1;
sbit P12 = P1 ^ 2;
sbit P17 = P1 ^ 7;
sbit P16 = P1 ^ 6;
sbit P15 = P1 ^ 5;
bit shanshuo = 0;

bit g_TX = 0;

uint8_t g_rece[8];

uint8_t g_adSteering = 0;
uint8_t g_adGo = 0;
uint8_t lastAdSteering = 1;
uint8_t lastAdGo = 1;

uint8_t g_steering;

void updateValue();
uint8_t sendData();

void main() {
	/*P1 = 0xff;
	P0 = 0xff;
	while(1) {
	PIN_MOTOR_A = 0;
	PIN_MOTOR_B = 1;
	PIN_PWM = 0;
		P10 = PIN_MOTOR_A;
		P11 = PIN_MOTOR_B;
		P12 = PIN_PWM;
		P17 = 0;
	}*/
	bit exist;
	P1 = 0xFF;
	PIN_MOTOR_A = 0;
	PIN_MOTOR_B = 0;

	NRF24L01_Gpio_Init();

	//检测nRF24L01
	exist = NRF24L01_check();

	if (exist) {
		P1 = ~0x03;
		RF24L01_Init();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		
		if (g_TX) {
			RF24L01_Set_Mode(MODE_TX); //发送模式
			_nop_();_nop_();_nop_();_nop_();_nop_();

			while (1) {
				uint8_t res;
				updateValue();
				P1 = ~lastAdSteering;
				res = sendData();
				if (res == 0xff) {
					P1 = 0x20;
					break;
				}
			}
		} else {
			g_rece[0] = 0xff;
			g_rece[1] = 0xff;
			initSteeringPWMTimer24M12T();
			RF24L01_Set_Mode(MODE_RX); //接收模式
			_nop_();_nop_();_nop_();_nop_();_nop_();
			while(1) {
				uint8_t rx;
				
				rx = NRF24L01_RxPacket(g_rece); //接收字节
				// P1 = rx;
				shanshuo = ~shanshuo;
				P17 = shanshuo;
				if(2 == rx) {
					uint8_t tmp, value, cmd;
					cmd = g_rece[0];
					value = g_rece[1];
					switch (cmd) {
						case CMD_STEERING:
							tmp = calculateSteeringDegree(value);
							if (g_steering != tmp) {
								g_steering = tmp;
								setSteeringDegree(g_steering);
							}
							break;
						case CMD_GO: {
							int motorSpeed;
							if (value == 0x02) {
								break;
							}
							P1 = ~value;
							motorSpeed = getMotorSpeed(value);
							if (motorSpeed > 0) {
								PIN_MOTOR_A = 1;
								PIN_MOTOR_B = 0;
								// P1 = 0x01;
							} else if (motorSpeed < 0) {
								PIN_MOTOR_A = 0;
								PIN_MOTOR_B = 1;
								// P1 = 0x02;
							} else {
								PIN_MOTOR_A = 0;
								PIN_MOTOR_B = 0;
								// P1 = 0xff;
							}
							break;
						}
					}
				}
			}
		}
	} else {
		P11 = 0;
	}
	
	while(1);
}

uint8_t sendData() {
	uint8_t res;
	uint8_t tx[2];

	tx[0] = CMD_STEERING;
	tx[1] = lastAdSteering;
	res = NRF24L01_TxPacket((uint8_t *) tx, 2);
	
	tx[0] = CMD_GO;
	tx[1] = lastAdGo;
	res = NRF24L01_TxPacket((uint8_t *) tx, 2);
	
	return res;
}

void updateValue() {
	I2CBus_Start();
	I2CBus_Write(0x90); // 写命令
	I2CBus_Write(0x00); // 选择AIN0
	I2CBus_Stop();

	I2CBus_Start(); // 可以不Stop直接start
	I2CBus_Write(0x91); // 读命令
	g_adGo = I2CBus_Read(1); // PCF8591T是先要将数据放到其内部buffer，每次从其buffer中发送数据，所以数据会有错位
	I2CBus_Stop();

	
	I2CBus_Start();
	I2CBus_Write(0x90); // 写命令
	I2CBus_Write(0x01); // 选择AIN1
	I2CBus_Stop();

	I2CBus_Start(); // 可以不Stop直接start
	I2CBus_Write(0x91);
	g_adSteering = I2CBus_Read(1); // PCF8591T是先要将数据放到其内部buffer，每次从其buffer中发送数据，所以数据会有错位
	I2CBus_Stop();
	
	if (g_adSteering != lastAdSteering) {
		lastAdSteering = g_adSteering;
	}
	
	if (g_adGo != lastAdGo) {
		lastAdGo = g_adGo;
	}
}

void tm1_isr() interrupt 3 {
	SteeringPWMTimerInterruption();
}