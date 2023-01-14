#include "1602.h"
#include "delay.h"

#define CHECK_BUSY

sbit RS = PIN_RS;
sbit RW = PIN_RW;
sbit EN = PIN_E;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort PIN_DATA


bit LCD_Check_Busy(void) { 
#ifdef CHECK_BUSY
	DataPort = 0xFF;
	RS_CLR;
	RW_SET;
	EN_CLR;
	_nop_();
	EN_SET;
	return (bit)(DataPort & 0x80);
#else
	return 0;
#endif
}

void LCD_Write_Com(unsigned char com) {  
 while(LCD_Check_Busy()); //æ��ȴ�
 RS_CLR; 
 RW_CLR; 
 EN_SET; 
 DataPort = com; 
 _nop_(); 
 EN_CLR;
}

void LCD_Write_Data(unsigned char Data) {
	while(LCD_Check_Busy()); //æ��ȴ�
	RS_SET;
	RW_CLR;
	EN_SET;
	DataPort = Data;
	_nop_();
	EN_CLR;
}

/*------------------------------------------------
                ��������
------------------------------------------------*/
 /*void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }*/
 
void LCD_Write_String_And_Clear_Line(unsigned char x, unsigned char y, unsigned char *s) {
	while (x < MAX_CHARS) {
		if (*s) {
			LCD_Write_Char(x, y, *s++);
		} else {
			LCD_Write_Char(x, y, ' ');
		}
		++x;
	}
}

void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) {
	 while (*s) {
		 LCD_Write_Char(x++, y, *s++);
	 }
}

void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 LCD_Write_Data(Data);  
 }
/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
}
   

