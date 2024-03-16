#include "dtos.h"

unsigned char intToS(int v, char * out, unsigned char maxL) {
	xdata int lplus = 0;
	if (v < 0) {
		v = -v;
		out[0] = '-';
		out = out + 1;
		maxL = maxL - 1;
		lplus = 1;
	}
	return uintToS(v, out, maxL) + lplus;
}

unsigned char uintToS(unsigned int v, char * out, unsigned char maxL) {
	xdata unsigned char maxD;
	xdata t[MAX_INT_CNT];
	xdata unsigned char i;
	xdata unsigned char j;
	if (v == 0) {
		out[0] = '0';
		out[1] = 0;
		return 1;
	}
	if (maxL > MAX_INT_CNT) {
		maxL = MAX_INT_CNT;
	}
	maxD = maxL - 1;
	for (i = 0; v; ++i) {
		unsigned char c = v % 10;
		t[i] = '0' + c;
		v /= 10;
	}
	for (j = 0; j < maxD && i; ++j, --i) {
		out[j] = t[i - 1];
	}
	out[j] = 0;
	return j;
}


unsigned char floatToS(float v, char * out, unsigned char maxL) {
	return floatToSS(v, out, maxL, 4);
}

unsigned char floatToSS(float v, char * out, unsigned char maxL, unsigned char s) {
	xdata unsigned int t;
	xdata unsigned char len = 0;
	xdata char l;
	if (s > MAX_FLOAT_SIGNIFICANT_FRACTION) {
		s = MAX_FLOAT_SIGNIFICANT_FRACTION;
	}
	if (v < 0) {
		out[0] = '-';
		out = out + 1;
		len = 1;
		v = -v;
	}
	t = (int) v;
	v -= t;
	l = uintToS(t, out, maxL);
	len += l;
	out += l;
	out[0] = '.';
	out += 1;
	++len;

	maxL = maxL - len - 1;
	if (maxL <= 0) {
		return len;
	}

	if (s == 0) {
		out[0] = 0;
		return len;
	} else {
		unsigned char temp[MAX_FLOAT_SIGNIFICANT_FRACTION];
		bit last0 = 1;
		for (l = 0; l < maxL && l < s; ++l) {
			v *= 10;
			temp[l] = (unsigned char) v;
			v = v - temp[l];
		}
		len += l;
		out[l] = 0;
		--l;
		for (; l >= 0; --l) {
			if (l == 0 && last0) {
				out[l] = '0' + temp[l];
			} else if (last0 && temp[l] == 0) {
				--len;
				out[l] = 0;
			} else {
				last0 = 0;
			  out[l] = '0' + temp[l];
			}
		}
	}
	return len;
}