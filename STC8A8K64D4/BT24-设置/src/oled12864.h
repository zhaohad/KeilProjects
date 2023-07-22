#ifndef __OLED12864_H__
#define __OLED12864_H__

#include "typedef.h"

#define DISPLAY_MODE_X8 (1 << 0)
#define DISPLAY_MODE_X16 (1 << 1)
#define DISPLAY_MODE_ALL DISPLAY_MODE_X8 | DISPLAY_MODE_X16

#define DISPLAY_MODE DISPLAY_MODE_ALL

#define OLED_CS P_OLED12864_CS
#define OLED_RST P_OLED12864_RES
#define OLED_DC P_OLED12864_DC
#define OLED_SCL P_OLED12864_SCK
#define OLED_SDIN P_OLED12864_SDA

#define OLED_CS_Clr()  OLED_CS = 0
#define OLED_CS_Set()  OLED_CS = 1

#define OLED_RST_Clr() OLED_RST = 0
#define OLED_RST_Set() OLED_RST = 1

#define OLED_DC_Clr() OLED_DC = 0
#define OLED_DC_Set() OLED_DC = 1

#define OLED_SCLK_Clr() OLED_SCL = 0
#define OLED_SCLK_Set() OLED_SCL = 1

#define OLED_SDIN_Clr() OLED_SDIN = 0
#define OLED_SDIN_Set() OLED_SDIN = 1;

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý

#define SIZE 16
#define Max_Column	128
#define Max_Row		64
#define MAX_CHAR8_COL 16 + 1
#define MAX_CHAR6_COL 21 + 1

void OLED_Init();
void OLED_WR_Byte(u8 dat, u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Clear();

#if (DISPLAY_MODE & DISPLAY_MODE_X16)
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowString(u8 x, u8 y, u8 * p);
#endif

#if (DISPLAY_MODE & DISPLAY_MODE_X8)
void OLED_ShowChar8(u8 x, u8 y, u8 chr);
void OLED_ShowString8(u8 x,u8 y, u8 * chr);
void OLED_ShowHexBuf8(u8 x, u8 y, u8 * buf, u8 len);
#endif

#endif