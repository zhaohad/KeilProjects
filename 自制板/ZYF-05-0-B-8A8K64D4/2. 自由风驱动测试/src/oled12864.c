#include "oled12864.h"
#include "oled12864wordlib.h"

//初始化SSD1306	    
void OLED_Init() {
  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 

	OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00, OLED_CMD); //-not offset
	OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
	OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
	OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
	OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02, OLED_CMD); //
	OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
	OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
	OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0, 0); 	
}

//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat, u8 cmd) {	
	xdata u8 i;
	if(cmd) {
	  OLED_DC_Set();
	} else { 
	  OLED_DC_Clr();
	}	  
	OLED_CS_Clr();
	for(i = 0; i < 8; i++) {
		OLED_SCLK_Clr();
		if(dat & 0x80) {
			OLED_SDIN_Set();
		}
		else {
			OLED_SDIN_Clr();
		}
		OLED_SCLK_Set();
		dat <<= 1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
}

void OLED_Set_Pos(u8 x, u8 y) { 
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f) | 0x01, OLED_CMD); 
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear() {
	xdata u8 i, n;
	for(i = 0; i < 8; i++) {  
		OLED_WR_Byte(0xb0 + i, OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);      //设置显示位置—列高地址   
		for(n = 0; n < 128; n++) {
			OLED_WR_Byte(0, OLED_DATA);
		}
	} //更新显示
}

u8 Bit4ToHex(u8 bit4) {
	bit4 &= 0x0f;
	if (bit4 < 10) {
		bit4 = bit4 + '0';
	} else {
		bit4 = bit4 + 'A' - 10;
	}
	return bit4;
}

#if DISPLAY_MODE & DISPLAY_MODE_X16
void OLED_ShowChar(u8 x, u8 y, u8 chr) {
	xdata u8 c, i;
	c = chr - ' ';
	if (c < 0 || chr > '~') {
		c = '?' - ' ';
	}

	if (x > Max_Column - 1) {
		x = 0;
		y = y + 2;
	}
	OLED_Set_Pos(x, y);
	for (i = 0; i < 8; ++i) {
		OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
	}
	OLED_Set_Pos(x, y + 1);
	for (i = 0; i < 8; ++i) {
		OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
}

//显示一个字符号串
void OLED_ShowString(u8 x,u8 y, u8 * chr) {
	xdata u8 j = 0;
	while (chr[j] != '\0') {
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if(x > 120) {
			x = 0;
			y += 2;
		}
		j++;
	}
}
#endif

#if DISPLAY_MODE & DISPLAY_MODE_X8
void OLED_ShowChar8(u8 x, u8 y, u8 chr) {
	xdata u8 c, i;
	c = chr - ' ';
	if (x > Max_Column - 1) {
		x = 0;
		y = y + 1;
	}
	OLED_Set_Pos(x, y);
  for(i = 0; i < 6; i++) {
		OLED_WR_Byte(F6x8[c][i], OLED_DATA);
	}
}

void OLED_ShowString8(u8 x,u8 y, u8 * chr) {
	xdata u8 j = 0;
	while (chr[j] != '\0') {
		OLED_ShowChar8(x, y, chr[j]);
		x += 6;
		if(x > 120) {
			x = 0;
			y += 1;
		}
		j++;
	}
}

void OLED_ShowHexBuf8(u8 x, u8 y, u8 * buf, u8 len) {
	xdata u8 i;
	for (i = 0; i < len; ++i) {
		x += 1;
		OLED_ShowChar8(x, y, Bit4ToHex(buf[i] >> 4));
		x += 6;
		OLED_ShowChar8(x, y, Bit4ToHex(buf[i]));
		x += 9;
	}
}

void OLED_ShowBootIMG() {
	u8 r, c;
	for (r = 0; r < BOOT_IMG_ROWS; ++r) {
		OLED_Set_Pos(0, r);
		for (c = 0; c < BOOT_IMG_COLS; ++c) {
			OLED_WR_Byte(BOOT_IMG[r][c], OLED_DATA);
		}
	}
}
#endif