   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  37                     ; 34 void drv_spi_init( void )
  37                     ; 35 {
  39                     	switch	.text
  40  0000               _drv_spi_init:
  44                     ; 37 	GPIO_Init( SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast  );
  46  0000 4be0          	push	#224
  47  0002 4b20          	push	#32
  48  0004 ae5005        	ldw	x,#20485
  49  0007 cd0000        	call	_GPIO_Init
  51  000a 85            	popw	x
  52                     ; 38 	GPIO_Init( SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN, GPIO_Mode_Out_PP_High_Slow  );
  54  000b 4bd0          	push	#208
  55  000d 4b40          	push	#64
  56  000f ae5005        	ldw	x,#20485
  57  0012 cd0000        	call	_GPIO_Init
  59  0015 85            	popw	x
  60                     ; 39 	GPIO_Init( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_Mode_Out_PP_High_Slow  );
  62  0016 4bd0          	push	#208
  63  0018 4b10          	push	#16
  64  001a ae5005        	ldw	x,#20485
  65  001d cd0000        	call	_GPIO_Init
  67  0020 85            	popw	x
  68                     ; 40 	GPIO_Init( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN, GPIO_Mode_In_PU_No_IT  );
  70  0021 4b40          	push	#64
  71  0023 4b80          	push	#128
  72  0025 ae5005        	ldw	x,#20485
  73  0028 cd0000        	call	_GPIO_Init
  75  002b 85            	popw	x
  76                     ; 43 	CLK_PeripheralClockConfig( CLK_Peripheral_SPI,ENABLE );		//开SPI时钟
  78  002c ae0001        	ldw	x,#1
  79  002f a610          	ld	a,#16
  80  0031 95            	ld	xh,a
  81  0032 cd0000        	call	_CLK_PeripheralClockConfig
  83                     ; 44 	SPI_DeInit( );		//SPI复位
  85  0035 cd0000        	call	_SPI_DeInit
  87                     ; 46 	SPI_Init( SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master, SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft );
  89  0038 4b02          	push	#2
  90  003a 4b00          	push	#0
  91  003c 4b00          	push	#0
  92  003e 4b00          	push	#0
  93  0040 4b04          	push	#4
  94  0042 ae0010        	ldw	x,#16
  95  0045 4f            	clr	a
  96  0046 95            	ld	xh,a
  97  0047 cd0000        	call	_SPI_Init
  99  004a 5b05          	addw	sp,#5
 100                     ; 47 	SPI_Cmd( ENABLE );	//SPI使能
 102  004c a601          	ld	a,#1
 103  004e cd0000        	call	_SPI_Cmd
 105                     ; 48 }
 108  0051 81            	ret
 164                     ; 57 uint8_t drv_spi_read_write_byte( uint8_t TxByte )
 164                     ; 58 {
 165                     	switch	.text
 166  0052               _drv_spi_read_write_byte:
 168  0052 88            	push	a
 169  0053 5203          	subw	sp,#3
 170       00000003      OFST:	set	3
 173                     ; 59 	uint8_t l_Data = 0;
 175  0055 7b01          	ld	a,(OFST-2,sp)
 176  0057 97            	ld	xl,a
 177                     ; 60 	uint16_t l_WaitTime = 0;
 179  0058 5f            	clrw	x
 180  0059 1f02          	ldw	(OFST-1,sp),x
 182  005b 2018          	jra	L35
 183  005d               L74:
 184                     ; 64 		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
 186  005d 1e02          	ldw	x,(OFST-1,sp)
 187  005f 1c0001        	addw	x,#1
 188  0062 1f02          	ldw	(OFST-1,sp),x
 189  0064 a3ffff        	cpw	x,#65535
 190  0067 260c          	jrne	L35
 191                     ; 66 			break;			//等待超时
 192  0069               L55:
 193                     ; 69 	SPI_SendData( TxByte );	//发送数据
 195  0069 7b04          	ld	a,(OFST+1,sp)
 196  006b cd0000        	call	_SPI_SendData
 198                     ; 70 	l_WaitTime = SPI_WAIT_TIMEOUT / 2;
 200  006e ae7fff        	ldw	x,#32767
 201  0071 1f02          	ldw	(OFST-1,sp),x
 203  0073 2020          	jra	L56
 204  0075               L35:
 205                     ; 62 	while( RESET == SPI_GetFlagStatus( SPI_FLAG_TXE ) )		//等待发送缓冲区空
 207  0075 a602          	ld	a,#2
 208  0077 cd0000        	call	_SPI_GetFlagStatus
 210  007a 4d            	tnz	a
 211  007b 27e0          	jreq	L74
 212  007d 20ea          	jra	L55
 213  007f               L16:
 214                     ; 73 		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
 216  007f 1e02          	ldw	x,(OFST-1,sp)
 217  0081 1c0001        	addw	x,#1
 218  0084 1f02          	ldw	(OFST-1,sp),x
 219  0086 a3ffff        	cpw	x,#65535
 220  0089 260a          	jrne	L56
 221                     ; 75 			break;			//等待超时
 222  008b               L76:
 223                     ; 79 	l_Data = SPI_ReceiveData( );
 225  008b cd0000        	call	_SPI_ReceiveData
 227  008e 6b01          	ld	(OFST-2,sp),a
 228                     ; 80 	return l_Data;	//返回数据
 230  0090 7b01          	ld	a,(OFST-2,sp)
 233  0092 5b04          	addw	sp,#4
 234  0094 81            	ret
 235  0095               L56:
 236                     ; 71 	while( RESET == SPI_GetFlagStatus( SPI_FLAG_RXNE ) )	//等待接收缓冲区非空
 238  0095 a601          	ld	a,#1
 239  0097 cd0000        	call	_SPI_GetFlagStatus
 241  009a 4d            	tnz	a
 242  009b 27e2          	jreq	L16
 243  009d 20ec          	jra	L76
 301                     ; 92 void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
 301                     ; 93 {
 302                     	switch	.text
 303  009f               _drv_spi_read_write_string:
 305  009f 89            	pushw	x
 306       00000000      OFST:	set	0
 309                     ; 94 	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);			//片选
 311  00a0 4b10          	push	#16
 312  00a2 ae5005        	ldw	x,#20485
 313  00a5 cd0000        	call	_GPIO_ResetBits
 315  00a8 84            	pop	a
 317  00a9 2016          	jra	L321
 318  00ab               L121:
 319                     ; 97 		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//一个字节的数据收发
 321  00ab 1e05          	ldw	x,(OFST+5,sp)
 322  00ad f6            	ld	a,(x)
 323  00ae ada2          	call	_drv_spi_read_write_byte
 325  00b0 1e01          	ldw	x,(OFST+1,sp)
 326  00b2 f7            	ld	(x),a
 327                     ; 98 		ReadBuffer++;
 329  00b3 1e01          	ldw	x,(OFST+1,sp)
 330  00b5 1c0001        	addw	x,#1
 331  00b8 1f01          	ldw	(OFST+1,sp),x
 332                     ; 99 		WriteBuffer++;				//地址加1
 334  00ba 1e05          	ldw	x,(OFST+5,sp)
 335  00bc 1c0001        	addw	x,#1
 336  00bf 1f05          	ldw	(OFST+5,sp),x
 337  00c1               L321:
 338                     ; 95 	while( Length-- )
 340  00c1 1e07          	ldw	x,(OFST+7,sp)
 341  00c3 1d0001        	subw	x,#1
 342  00c6 1f07          	ldw	(OFST+7,sp),x
 343  00c8 1c0001        	addw	x,#1
 344  00cb a30000        	cpw	x,#0
 345  00ce 26db          	jrne	L121
 346                     ; 101 	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				//取消片选
 348  00d0 4b10          	push	#16
 349  00d2 ae5005        	ldw	x,#20485
 350  00d5 cd0000        	call	_GPIO_SetBits
 352  00d8 84            	pop	a
 353                     ; 102 }
 356  00d9 85            	popw	x
 357  00da 81            	ret
 370                     	xdef	_drv_spi_read_write_string
 371                     	xdef	_drv_spi_read_write_byte
 372                     	xdef	_drv_spi_init
 373                     	xref	_CLK_PeripheralClockConfig
 374                     	xref	_SPI_GetFlagStatus
 375                     	xref	_SPI_ReceiveData
 376                     	xref	_SPI_SendData
 377                     	xref	_SPI_Cmd
 378                     	xref	_SPI_Init
 379                     	xref	_SPI_DeInit
 380                     	xref	_GPIO_ResetBits
 381                     	xref	_GPIO_SetBits
 382                     	xref	_GPIO_Init
 401                     	end
