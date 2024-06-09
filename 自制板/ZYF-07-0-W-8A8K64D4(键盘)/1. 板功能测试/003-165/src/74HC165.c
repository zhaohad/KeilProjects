#include "74hc165.h"

void load_data_165() {
	P_165_PL = 0;
}

u8 read_byte_165() {
	u8 d = 0;
	P_165_PL = 1;
	P_165_CE = 0;
	
	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;
	
	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;
	
	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;
	
	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	d <<= 1;
	P_165_CP = 1;

	P_165_CP = 0;
	d |= P_165_Q7;
	P_165_CP = 1;
	
	P_165_CE = 1;
	return d;
}
