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

#include	"I2C.h"

#define Software_I2C			//ʹ�����ģ��I2C

u8 	I2C_BUF_type I2C_Buffer[I2C_BUF_LENTH];
I2C_IsrTypeDef I2CIsr;

extern bit DisplayFlag;

//========================================================================
// ����: void	I2C_Init(I2C_InitTypeDef *I2Cx)
// ����: I2C��ʼ������.
// ����: I2Cx: �ṹ����,��ο�I2C.h��Ķ���.
// ����: none.
// �汾: V1.0, 2020-09-16
//========================================================================
void	I2C_Init(I2C_InitTypeDef *I2Cx)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	
	if(I2Cx->I2C_Mode == I2C_Mode_Master)
	{
		I2C_Master();			//��Ϊ����	
		I2CMSST = 0x00;		//���I2C����״̬�Ĵ���
		I2C_Master_Inturrupt(I2Cx->I2C_MS_Interrupt);
		I2C_SetSpeed(I2Cx->I2C_Speed);
		if(I2Cx->I2C_MS_WDTA == ENABLE)		I2C_WDTA_EN();	//ʹ���Զ�����
		else									I2C_WDTA_DIS();	//��ֹ�Զ�����
	}
	else
	{
		I2C_Slave();	//��Ϊ�ӻ�
		I2CSLST = 0x00;		//���I2C�ӻ�״̬�Ĵ��� 
		if(I2Cx->I2C_SL_ESTAI == ENABLE)		I2C_ESTAI_EN();	//ʹ�ܴӻ�����START�ź��ж�
		else									I2C_ESTAI_DIS();	//��ֹ�ӻ�����START�ź��ж�
		if(I2Cx->I2C_SL_ERXI == ENABLE)		I2C_ERXI_EN();	//ʹ�ܴӻ�����1�ֽ������ж�
		else									I2C_ERXI_DIS();	//��ֹ�ӻ�����1�ֽ������ж�
		if(I2Cx->I2C_SL_ETXI == ENABLE)		I2C_ETXI_EN();	//ʹ�ܴӻ�����1�ֽ������ж�
		else									I2C_ETXI_DIS();	//��ֹ�ӻ�����1�ֽ������ж�
		if(I2Cx->I2C_SL_ESTOI == ENABLE)		I2C_ESTOI_EN();	//ʹ�ܴӻ�����STOP�ź��ж�
		else									I2C_ESTOI_DIS();	//��ֹ�ӻ�����STOP�ź��ж�
		I2C_Address(I2Cx->I2C_SL_ADR);
		if(I2Cx->I2C_SL_MA == ENABLE)		I2C_MATCH_EN();	//�ӻ���ַ�ȽϹ��ܣ�ֻ������ƥ���ַ
		else									I2C_MATCH_DIS();	//��ֹ�ӻ���ַ�ȽϹ��ܣ����������豸��ַ
	}
	
	P_SW2 = (P_SW2 & ~(3<<4)) | I2Cx->I2C_IoUse;
	I2C_Function(I2Cx->I2C_Enable);
	
	I2CIsr.isda = 1;
	I2CIsr.isma = 1;
	I2CIsr.addr = 0;
	I2CTXD = I2C_Buffer[I2CIsr.addr];

	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

#ifdef Software_I2C

#define SLAW    0x5A
#define SLAR    0x5B

sbit    SDA = P0^1; //����SDA
sbit    SCL = P0^0; //����SCL

/****************************/
void I2C_Delay(void) //for normal MCS51, delay (2 * dly + 4) T, for STC12Cxxxx delay (4 * dly + 10) T
{
	u8  dly;
	dly = MAIN_Fosc / 2000000UL;        //��2us����
	while(--dly);
}

/****************************/
void I2C_Start(void)               //start the I2C, SDA High-to-low when SCL is high
{
	SDA = 1;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SDA = 0;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}       


void I2C_Stop(void)                 //STOP the I2C, SDA Low-to-high when SCL is high
{
	SDA = 0;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SDA = 1;
	I2C_Delay();
}

void S_ACK(void)              //Send ACK (LOW)
{
	SDA = 0;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}

void S_NoACK(void)           //Send No ACK (High)
{
	SDA = 1;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	SCL = 0;
	I2C_Delay();
}
        
void I2C_Check_ACK(void)         //Check ACK, If F0=0, then right, if F0=1, then error
{
	SDA = 1;
	I2C_Delay();
	SCL = 1;
	I2C_Delay();
	F0  = SDA;
	SCL = 0;
	I2C_Delay();
}

/****************************/
void I2C_WriteAbyte(u8 dat)     //write a byte to I2C
{
	u8 i;
	i = 8;
	do
	{
		if(dat & 0x80)  SDA = 1;
		else            SDA = 0;
		dat <<= 1;
		I2C_Delay();
		SCL = 1;
		I2C_Delay();
		SCL = 0;
		I2C_Delay();
	}
	while(--i);
}

/****************************/
u8 I2C_ReadAbyte(void)          //read A byte from I2C
{
	u8 i,dat;
	i = 8;
	SDA = 1;
	do
	{
		SCL = 1;
		I2C_Delay();
		dat <<= 1;
		if(SDA)     dat++;
		SCL  = 0;
		I2C_Delay();
	}
	while(--i);
	return(dat);
}

/****************************/
void WriteNbyte(u8 addr, u8 *p, u8 number)          /*  WordAddress,First Data Address,Byte lenth   */
{
	I2C_Start();
	I2C_WriteAbyte(SLAW);
	I2C_Check_ACK();
	if(!F0)                                           //F0=0,right, F0=1,error
	{
		I2C_WriteAbyte(addr);
		I2C_Check_ACK();
		if(!F0)
		{
			do
			{
				I2C_WriteAbyte(*p); p++;
				I2C_Check_ACK();
				if(F0)  break;
			}
			while(--number);
		}
	}
	I2C_Stop();
}


/****************************/
void ReadNbyte(u8 addr, u8 *p, u8 number)       /*  WordAddress,First Data Address,Byte lenth   */
{
	I2C_Start();
	I2C_WriteAbyte(SLAW);
	I2C_Check_ACK();
	if(!F0)
	{
		I2C_WriteAbyte(addr);
		I2C_Check_ACK();
		if(!F0)
		{
			I2C_Start();
			I2C_WriteAbyte(SLAR);
			I2C_Check_ACK();
			if(!F0)
			{
				do
				{
					*p = I2C_ReadAbyte();   p++;
					if(number != 1)     S_ACK();    //send ACK
				}
				while(--number);
				S_NoACK();          //send no ACK
			}
		}
	}
	I2C_Stop();
}

#else

#define SLAW    0xA2
#define SLAR    0xA3
//========================================================================
// ����: void	Wait (void)
// ����: �ȴ�����ģʽI2C������ִ�����I2CMSCR.
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void Wait()
{
	while (!(I2CMSST & 0x40));
	I2CMSST &= ~0x40;
}

//========================================================================
// ����: void Start (void)
// ����: I2C������ʼ����.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void Start()
{
	I2CMSCR = 0x01;                         //����START����
	Wait();
}

//========================================================================
// ����: void SendData (char dat)
// ����: I2C����һ���ֽ����ݺ���.
// ����: ���͵�����.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void SendData(char dat)
{
	I2CTXD = dat;                           //д���ݵ����ݻ�����
	I2CMSCR = 0x02;                         //����SEND����
	Wait();
}

//========================================================================
// ����: void RecvACK (void)
// ����: I2C��ȡACK����.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void RecvACK()
{
	I2CMSCR = 0x03;                         //���Ͷ�ACK����
	Wait();
}

//========================================================================
// ����: char RecvData (void)
// ����: I2C��ȡһ���ֽ����ݺ���.
// ����: none.
// ����: ��ȡ����.
// �汾: V1.0, 2020-09-15
//========================================================================
char RecvData()
{
	I2CMSCR = 0x04;                         //����RECV����
	Wait();
	return I2CRXD;
}

//========================================================================
// ����: void SendACK (void)
// ����: I2C����ACK����.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void SendACK()
{
	I2CMSST = 0x00;                         //����ACK�ź�
	I2CMSCR = 0x05;                         //����ACK����
	Wait();
}

//========================================================================
// ����: void SendNAK (void)
// ����: I2C����NAK����.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void SendNAK()
{
	I2CMSST = 0x01;                         //����NAK�ź�
	I2CMSCR = 0x05;                         //����ACK����
	Wait();
}

//========================================================================
// ����: void Stop (void)
// ����: I2C����ֹͣ����.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void Stop()
{
	I2CMSCR = 0x06;                         //����STOP����
	Wait();
}

//========================================================================
// ����: void	WriteNbyte(u8 addr, u8 *p, u8 number)
// ����: I2Cд�����ݺ���.
// ����: addr: ָ����ַ, *pд�����ݴ洢λ��, numberд�����ݸ���.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void WriteNbyte(u8 addr, u8 *p, u8 number)  /*  WordAddress,First Data Address,Byte lenth   */
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAW);                         //�����豸��ַ+д����
	RecvACK();
	SendData(addr);                         //���ʹ洢��ַ
	RecvACK();
	do
	{
		SendData(*p++);
		RecvACK();
	}
	while(--number);
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

//========================================================================
// ����: void	ReadNbyte(u8 addr, u8 *p, u8 number)
// ����: I2C��ȡ���ݺ���.
// ����: addr: ָ����ַ, *p��ȡ���ݴ洢λ��, number��ȡ���ݸ���.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void ReadNbyte(u8 addr, u8 *p, u8 number)   /*  WordAddress,First Data Address,Byte lenth   */
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	Start();                                //������ʼ����
	SendData(SLAW);                         //�����豸��ַ+д����
	RecvACK();
	SendData(addr);                         //���ʹ洢��ַ
	RecvACK();
	Start();                                //������ʼ����
	SendData(SLAR);                         //�����豸��ַ+������
	RecvACK();
	do
	{
		*p = RecvData();
		p++;
		if(number != 1) SendACK();          //send ACK
	}
	while(--number);
	SendNAK();                              //send no ACK	
	Stop();                                 //����ֹͣ����
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}

#endif
//========================================================================
// ����: void I2C_Isr (void) interrupt I2C_VECTOR
// ����: I2C�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-15
//========================================================================
void I2C_Isr() interrupt I2C_VECTOR
{
	char store;
	
	store = P_SW2;
	P_SW2 |= 0x80;

	if (I2CSLST & 0x40)
	{
		I2CSLST &= ~0x40;                       //����START�¼�
	}
	else if (I2CSLST & 0x20)
	{
		I2CSLST &= ~0x20;                       //����RECV�¼���SLACKO����Ϊ0
		if (I2CIsr.isda)
		{
			I2CIsr.isda = 0;                           //����RECV�¼���RECV DEVICE ADDR��
		}
		else if (I2CIsr.isma)
		{
			I2CIsr.isma = 0;                           //����RECV�¼���RECV MEMORY ADDR��
			I2CIsr.addr = I2CRXD;
			I2CTXD = I2C_Buffer[I2CIsr.addr];
		}
		else
		{
			I2C_Buffer[I2CIsr.addr++] = I2CRXD;            //����RECV�¼���RECV DATA��
		}
	}
	else if (I2CSLST & 0x10)
	{
		I2CSLST &= ~0x10;                       //����SEND�¼�
		if (I2CSLST & 0x02)
		{
			I2CTXD = 0xff;
		}
		else
		{
			I2CTXD = I2C_Buffer[++I2CIsr.addr];
		}
	}
	else if (I2CSLST & 0x08)
	{
		I2CSLST &= ~0x08;                       //����STOP�¼�
		I2CIsr.isda = 1;
		I2CIsr.isma = 1;
		DisplayFlag = 1;
	}

	P_SW2 = store;
}

