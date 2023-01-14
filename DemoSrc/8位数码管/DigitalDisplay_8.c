#include "DigitalDisplay_8.h"

#define PIN_OUT_SRF P0
#define D_NULL_CODE 0x00

sbit latch_bit = P2 ^ 6;
sbit latch_frag = P2 ^ 7;

#define MAX_CNT 8

unsigned char DIGITAL_CODE[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, D_NULL_CODE};
unsigned char BIT_CODE[8] = {0xff ^ 0x80, 0xff ^ 0x40, 0xff ^ 0x20, 0xff ^ 0x10, 0xff ^ 0x08, 0xff ^ 0x04, 0xff ^ 0x02, 0xff ^ 0x01};

unsigned char g_numbers[8];
unsigned char g_cnt;


void DigitalDisplay_8_Loop() {
	DigitalDisplay_8_Display(g_numbers, g_cnt);
}

void DigitalDisplay_8_Set(unsigned char nums[], unsigned char cnt) {
	int i = 0;
	if (cnt > 8) {
		cnt = 8;
	}

	g_cnt = cnt;
	for (; i < cnt; ++i) {
		g_numbers[i] = nums[i];
	}
}

void DigitalDisplay_8_Display(unsigned char nums[], unsigned char cnt) {
	int i = 0;
	latch_frag = 0;
	latch_bit = 0;
	for (; i < cnt; ++i) {
		PIN_OUT_SRF = D_NULL_CODE;
		latch_frag = 1;
		latch_frag =0;
		
		PIN_OUT_SRF = BIT_CODE[i];
		latch_bit = 1;
		latch_bit = 0;

		PIN_OUT_SRF = DIGITAL_CODE[nums[i]];
		latch_frag = 1;
		latch_frag = 0;
	}
}