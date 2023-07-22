#ifndef __DTOS_H__
#define __DTOS_H__

// 数字转字符串

#define MAX_INT_CNT 7
#define MAX_FLOAT_SIGNIFICANT_INT_CNT 6
#define MAX_FLOAT_SIGNIFICANT_FRACTION 6
#define MAX_FLOAT_CNT 15 /*(MAX_FLOAT_SIGNIFICANT_INT_CNT + 1 + MAX_FLOAT_SIGNIFICANT_FRACTION + 1 + 1)*/

unsigned char intToS(int v, char * out, unsigned char maxL);
unsigned char uintToS(unsigned int v, char * out, unsigned char maxL);
unsigned char floatToS(float v, char * out, unsigned char maxL);
unsigned char floatToSS(float v, char * out, unsigned char maxL, unsigned char s);

#endif