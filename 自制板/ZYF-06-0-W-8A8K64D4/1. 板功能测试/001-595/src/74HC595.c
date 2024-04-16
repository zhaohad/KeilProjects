#include "74hc595.h"

void stop_595() {
	P_595_G = 1;
}

void clear_595() {
	P_595_SCLR = 0;
}

void keep_595() {
	P_595_G = 0;
}

void write_byte_595(u8 d) {
	P_595_SCLR = 1;
	P_595_G = 0;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x80;
	P_595_SCK = 1;

	P_595_SCK = 0;
	P_595_SER = d & 0x40;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x20;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x10;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x08;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x04;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x02;
	P_595_SCK = 1;
	
	P_595_SCK = 0;
	P_595_SER = d & 0x01;
	P_595_SCK = 1;
}

void flush_595() {
	P_595_RCK = 0;
	P_595_SCLR = 1;
	P_595_G = 0;
	P_595_RCK = 1;
}
