/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"STC8A_BMM.h"
#include	"STC8A_GPIO.h"
#include	"STC8A_LCM.h"
#include	"STC8A_NVIC.h"
#include	"STC8A_Delay.h"
#include	"STC8A_Switch.h"
#include	"font.h"

/*************   ����˵��   ***************

LCM�ӿ�+BMM����Һ��������

8bit I8080ģʽ, P2�ڽ�D8~D15

sbit LCD_RS = P4^1;      //����/�����л�
sbit LCD_WR = P3^6;      //д����
sbit LCD_RD = P3^7;      //������
sbit LCD_CS = P3^4;      //Ƭѡ
sbit LCD_RESET = P3^5;   //��λ

LCMָ��ͨ���жϷ�ʽ�ȴ��������

BMM���ó���256�ֽڣ�ͨ���жϷ�ʽ�жϴ������

����ʱ, ѡ��ʱ�� 22.1184MHz (�����������ļ�"config.h"���޸�).

******************************************/

/*************	���س�������	**************/

#define  LCD_DataPort P2     //8λ���ݿ�

//֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL  	  1   //����Һ������ʾ���� 	0-������1-����

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE             0x001F  
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN            0XBC40 //��ɫ
#define BRRED            0XFC07 //�غ�ɫ
#define GRAY             0X8430 //��ɫ

/*************	���ر�������	**************/

u16 LCD_W;			//LCD ���
u16 LCD_H;			//LCD �߶�

u16 POINT_COLOR=0x0000;	//������ɫ

u16 LCM_Cnt;
u16 xdata Buffer[8]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
u16 xdata Color[256];
bit BmmLcmFlag;
bit LcmFlag;

/*************	���غ�������	**************/

void Test_Color(void);
void LCD_WR_DATA_16Bit(u16 Data);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
u16 LCD_Read_ID(void);
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_Init(void);

/*************  �ⲿ�����ͱ������� *****************/


/******************** IO������ ********************/
void	GPIO_config(void)
{
	P2_MODE_OUT_PP(GPIO_Pin_All);		//P2 ���ó��������
	P3_MODE_OUT_PP(GPIO_Pin_HIGH);	//P3.4~P3.7�����ó��������
	P4_MODE_OUT_PP(GPIO_Pin_1);			//P4.1 ���ó��������

	LCM_CTRL_SW(LCM_CTRL_P41_P37_P36);	//LCM_CTRL_P41_P44_P43,LCM_CTRL_P41_P37_P36,LCM_CTRL_P41_P42_P40,LCM_CTRL_P40_P37_P36
	LCM_DATA_SW(LCM_D8_NA_P2);		//LCM_D8_NA_P2,LCM_D8_NA_P6 / LCM_D16_P2_P0,LCM_D16_P6_P2,LCM_D16_P2_P7,LCM_D16_P6_P7
}

/******************** LCM ���� ********************/
void	LCM_config(void)
{
	LCM_InitTypeDef		LCM_InitStructure;		//�ṹ����

	LCM_InitStructure.LCM_Enable = ENABLE;				//LCM�ӿ�ʹ��  	ENABLE,DISABLE
	LCM_InitStructure.LCM_Mode = MODE_I8080;			//LCM�ӿ�ģʽ  	MODE_I8080,MODE_M6800
	LCM_InitStructure.LCM_Bit_Wide = BIT_WIDE_8;	//LCM���ݿ��  	BIT_WIDE_8,BIT_WIDE_16
	LCM_InitStructure.LCM_Setup_Time = 2;					//LCMͨ�����ݽ���ʱ��  	0~7
	LCM_InitStructure.LCM_Hold_Time = 1;					//LCMͨ�����ݱ���ʱ��  	0~3
	LCM_Inilize(&LCM_InitStructure);		//��ʼ��
	NVIC_LCM_Init(ENABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** BMM ���� ********************/
void	BMM_config(void)
{
	BMM_LCM_InitTypeDef		BMM_LCM_InitStructure;		//�ṹ����

	BMM_LCM_InitStructure.BMM_Enable = ENABLE;			//BMMʹ��  	ENABLE,DISABLE
	BMM_LCM_InitStructure.BMM_Length = 255;					//BMM�������ֽ���  	(0~255) + 1
	BMM_LCM_InitStructure.BMM_Tx_Buffer = &Color;		//�������ݴ洢��ַ
	BMM_LCM_InitStructure.BMM_Rx_Buffer = &Buffer;		//�������ݴ洢��ַ
	BMM_LCM_Inilize(&BMM_LCM_InitStructure);		//��ʼ��
	NVIC_BMM_LCM_Init(ENABLE,Priority_0,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0~Priority_3; �������ȼ�(�͵���) Priority_0~Priority_3
}

/******************** task A **************************/
void main(void)
{
	GPIO_config();
	LCM_config();
	BMM_config();
	EA = 1;
	LCD_Init();	//LCM��ʼ��

	while (1)
	{
		Test_Color();
	}
}

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{  	
	u16 i,j;			
	u16 width=ex-sx+1; 		//�õ����Ŀ��
	u16 height=ey-sy+1;		//�߶�
	LCD_SetWindows(sx,sy,ex,ey);//������ʾ����

	for(j=0,i=0;i<256;i++)
	{
		Color[i] = color;
	}
	LCM_Cnt = 600;
	LCD_CS=0;
	BMM_LCM_TRIG_WD();	//Write dat
//	P40 = 0;
}

void Test_Color(void)
{
	u16 lcd_id;
	u8 buf[10] = {0};

//	P40 = 0;
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
//	P40 = 1;
	while(!LCD_CS);

	SET_LCM_BMM_LEN(0x01);		//Exe 2(n+1) bytes
	lcd_id = LCD_Read_ID();
	sprintf((char *)buf,"ID:0x%x",lcd_id);
	Show_Str(50,25,BLUE,YELLOW,buf,16,1);
	SET_LCM_BMM_LEN(0xff);		//Exe 256(n+1) bytes

	delay_ms(800);
//	P40 = 0;
	LCD_Fill(0,0,LCD_W,LCD_H,RED);
//	P40 = 1;
	delay_ms(800);
//	P40 = 0;
	LCD_Fill(0,0,LCD_W,LCD_H,GREEN);
//	P40 = 1;
	delay_ms(800);
//	P40 = 0;
	LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
//	P40 = 1;
	delay_ms(800);
}

void Write_Cmd(unsigned char DH,unsigned char DL)
{
	SET_LCM_DAT_LOW(DH);
	LCD_CS = 0;
	LcmFlag = 1;
	LCM_WRITE_CMD();		//Enable interface, write command out
	while(LcmFlag);
	
	SET_LCM_DAT_LOW(DL);
	LcmFlag = 1;
	LCM_WRITE_CMD();		//Enable interface, write command out
	while(LcmFlag);
	LCD_CS = 1 ;
}

void Write_Data(unsigned char DH,unsigned char DL)
{
	SET_LCM_DAT_LOW(DH);
	LCD_CS = 0;
	LcmFlag = 1;
	LCM_WRITE_DAT();		//Enable interface, write data out
	while(LcmFlag);
	
	SET_LCM_DAT_LOW(DL);
	LcmFlag = 1;
	LCM_WRITE_DAT();		//Enable interface, write data out
	while(LcmFlag);
	LCD_CS = 1 ;
}

void LCD_WR_REG(u8 Reg)
{	
	SET_LCM_DAT_LOW(Reg);
	LCD_CS = 0;
	LcmFlag = 1;
	LCM_WRITE_CMD();		//Enable interface, write command out
	while(LcmFlag);
	LCD_CS = 1 ;
}

u16 LCD_RD_DATA(void)
{
	//BMM Read
	LCD_CS=0;
	BmmLcmFlag = 1;
	BMM_LCM_TRIG_RD();	//Read data
	while(BmmLcmFlag);
	LCD_CS=1;
	return (Buffer[0]);
}

void LCD_WR_REG16(u8 Reg, u16 dat)
{	
	Write_Cmd(0x00,Reg);
	Write_Data((dat>>8)&0xFF,dat&0xFF);
}

void LCD_WR_DATA_16Bit(u16 Data)
{
	Write_Data((Data>>8)&0xFF,Data&0xFF);
}

/*****************************************************************************
 * @name       :u16 LCD_Read_ID(void)
 * @date       :2020-12-11 
 * @function   :Read ID
 * @parameters :None
 * @retvalue   :ID value
******************************************************************************/ 
u16 LCD_Read_ID(void)
{
	u16 val;

	LCD_WR_REG(0x00);		//ID: Status Read (RS)
	val = LCD_RD_DATA();
	return (val);
}

/*****************************************************************************
 * @name       :void LCDReset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCDReset(void)
{
	LCD_CS=1;
	delay_ms(50);	
	LCD_RESET=0;
	delay_ms(150);
	LCD_RESET=1;
	delay_ms(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{
	LCDReset(); //��ʼ��֮ǰ��λ
	delay_ms(150);                     //���ݲ�ͬ�����ٶȿ��Ե�����ʱ�������ȶ���ʾ
//*************2.4inch ILI9325��ʼ��**********//	
	LCD_WR_REG16(0x00E5,0x78F0); 
	LCD_WR_REG16(0x0001,0x0100); 
	LCD_WR_REG16(0x0002,0x0700); 
	LCD_WR_REG16(0x0003,0x1030); 
	LCD_WR_REG16(0x0004,0x0000); 
	LCD_WR_REG16(0x0008,0x0202);  
	LCD_WR_REG16(0x0009,0x0000);
	LCD_WR_REG16(0x000A,0x0000); 
	LCD_WR_REG16(0x000C,0x0000); 
	LCD_WR_REG16(0x000D,0x0000);
	LCD_WR_REG16(0x000F,0x0000);
	//power on sequence VGHVGL
	LCD_WR_REG16(0x0010,0x0000);   
	LCD_WR_REG16(0x0011,0x0007);  
	LCD_WR_REG16(0x0012,0x0000);  
	LCD_WR_REG16(0x0013,0x0000); 
	LCD_WR_REG16(0x0007,0x0000); 
	//vgh 
	LCD_WR_REG16(0x0010,0x1690);   
	LCD_WR_REG16(0x0011,0x0227);
	delay_ms(10);
	//vregiout 
	LCD_WR_REG16(0x0012,0x009D); //0x001b
	delay_ms(10); 
	//vom amplitude
	LCD_WR_REG16(0x0013,0x1900);
	delay_ms(10); 
	//vom H
	LCD_WR_REG16(0x0029,0x0025); 
	LCD_WR_REG16(0x002B,0x000D); 
	//gamma
	LCD_WR_REG16(0x0030,0x0007);
	LCD_WR_REG16(0x0031,0x0303);
	LCD_WR_REG16(0x0032,0x0003); //0006
	LCD_WR_REG16(0x0035,0x0206);
	LCD_WR_REG16(0x0036,0x0008);
	LCD_WR_REG16(0x0037,0x0406); 
	LCD_WR_REG16(0x0038,0x0304); //0200
	LCD_WR_REG16(0x0039,0x0007); 
	LCD_WR_REG16(0x003C,0x0602); //0504
	LCD_WR_REG16(0x003D,0x0008); 
	//ram
	LCD_WR_REG16(0x0050,0x0000); 
	LCD_WR_REG16(0x0051,0x00EF);
	LCD_WR_REG16(0x0052,0x0000); 
	LCD_WR_REG16(0x0053,0x013F);  
	LCD_WR_REG16(0x0060,0xA700); 
	LCD_WR_REG16(0x0061,0x0001); 
	LCD_WR_REG16(0x006A,0x0000); 
	//
	LCD_WR_REG16(0x0080,0x0000); 
	LCD_WR_REG16(0x0081,0x0000); 
	LCD_WR_REG16(0x0082,0x0000); 
	LCD_WR_REG16(0x0083,0x0000); 
	LCD_WR_REG16(0x0084,0x0000); 
	LCD_WR_REG16(0x0085,0x0000); 
	//
	LCD_WR_REG16(0x0090,0x0010); 
	LCD_WR_REG16(0x0092,0x0600); 
	
	LCD_WR_REG16(0x0007,0x0133);
	LCD_WR_REG16(0x0000,0x0022);

	//����LCD���Բ���
	#if USE_HORIZONTAL==1
	LCD_W = 320;
	LCD_H = 240;
	LCD_WR_REG16(0x0003, 0x1038); // set GRAM write direction and BGR=1.
	LCD_WR_REG16(0x0001, 0x0000); // set SS and SM bit
	#else
	LCD_W = 240;
	LCD_H = 320;
	LCD_WR_REG16(0x0003, 0x1030); // set GRAM write direction and BGR=1.
	LCD_WR_REG16(0x0001, 0x0100); // set SS and SM bit
	#endif 
}

#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END		0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write

void LCD_SetWindows(u16 xStar0, u16 yStar0,u16 xEnd0,u16 yEnd0)
{	
	u16 xStar; u16 yStar;u16 xEnd;u16 yEnd;
	#if USE_HORIZONTAL==1
	xStar = yStar0;
	xEnd = yEnd0;
	yStar = xStar0;
	yEnd = xEnd0;
	#else
	xStar = xStar0;
	xEnd = xEnd0;
	yStar = yStar0;
	yEnd = yEnd0;
	#endif 

  LCD_WR_REG16(WINDOW_XADDR_START,xStar);
  LCD_WR_REG16(WINDOW_XADDR_END,xEnd);
  LCD_WR_REG16(WINDOW_YADDR_START,yStar);
  LCD_WR_REG16(WINDOW_YADDR_END,yEnd);
  LCD_WR_REG16(GRAM_XADDR,xStar);
  LCD_WR_REG16(GRAM_YADDR,yStar);
	LCD_WR_REG(GRAMWR);
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetWindows(x,y,x,y);//���ù��λ��
	LCD_WR_DATA_16Bit(POINT_COLOR);
} 	 

/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display a single English character
 * @parameters :x:the beginning x coordinate of the Character display position
                y:the beginning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								num:the ascii code of display character(0~94)
								size:the size of display character
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/ 
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
{
	u8 temp;
	u8 pos,t;
	u16 colortemp=POINT_COLOR;

	num=num-' ';//�õ�ƫ�ƺ��ֵ
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//���õ���������ʾ����
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
			{
				if(temp&0x01)LCD_WR_DATA_16Bit(fc); 
				else LCD_WR_DATA_16Bit(bc); 
				temp>>=1; 
			}
		}
	}
	else//���ӷ�ʽ
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//����1206����
			else temp=asc2_1608[num][pos];		 //����1608����
			for(t=0;t<size/2;t++)
			{
				POINT_COLOR=fc;
				if(temp&0x01)	LCD_DrawPoint(x+t,y+pos);//��һ����
				temp>>=1;
			}
		}
	}
	POINT_COLOR=colortemp;	
	LCD_SetWindows(0,0,LCD_W-1,LCD_H-1);//�ָ�����Ϊȫ��    	   	 	  
}

/*****************************************************************************
 * @name       :void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
 * @date       :2018-08-09 
 * @function   :Display Chinese and English strings
 * @parameters :x:the beginning x coordinate of the Chinese and English strings
                y:the beginning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								mode:0-no overlying,1-overlying
 * @retvalue   :None
******************************************************************************/	   		   
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode)
{					
	u16 x0=x;							  	  
	u8 bHz=0;     //�ַ��������� 
	while(*str!=0)//����δ����
	{ 
		if(!bHz)
		{
			if(x>(LCD_W-size/2)||y>(LCD_H-size)) 
			return;
			if(*str>0x80)	bHz=1;//���� 
			else              //�ַ�
			{
				if(*str==0x0D)//���з���
				{
					y+=size;
					x=x0;
					str++;
				}
				else
				{
					if(size>16)//�ֿ���û�м���12X24 16X32��Ӣ������,��8X16����
					{  
						LCD_ShowChar(x,y,fc,bc,*str,16,mode);
						x+=8; //�ַ�,Ϊȫ�ֵ�һ�� 
					}
					else
					{
						LCD_ShowChar(x,y,fc,bc,*str,size,mode);
						x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
					}
				}
				str++;
			}
		}
		else//����
		{
//			if(x>(lcddev.width-size)||y>(lcddev.height-size))
//			return;
//			bHz=0;//�к��ֿ�
//			if(size==32)
//			GUI_DrawFont32(x,y,fc,bc,str,mode);
//			else if(size==24)
//			GUI_DrawFont24(x,y,fc,bc,str,mode);
//			else
//			GUI_DrawFont16(x,y,fc,bc,str,mode);

			str+=2;
			x+=size;//��һ������ƫ��
		}
	}
}
