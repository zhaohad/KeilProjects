   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
   4                     	bsct
   5  0000               _g_ErrorString:
   6  0000 000f          	dc.w	L3
  58                     ; 32 uint8_t NRF24L01_Read_Reg( uint8_t RegAddr )
  58                     ; 33 {
  60                     	switch	.text
  61  0000               _NRF24L01_Read_Reg:
  63  0000 88            	push	a
  64  0001 88            	push	a
  65       00000001      OFST:	set	1
  68                     ; 36     RF24L01_SET_CS_LOW( );			//片选
  70  0002 4b10          	push	#16
  71  0004 ae5005        	ldw	x,#20485
  72  0007 cd0000        	call	_GPIO_ResetBits
  74  000a 84            	pop	a
  75                     ; 38     drv_spi_read_write_byte( NRF_READ_REG | RegAddr );	//读命令 地址
  77  000b 7b02          	ld	a,(OFST+1,sp)
  78  000d cd0000        	call	_drv_spi_read_write_byte
  80                     ; 39     btmp = drv_spi_read_write_byte( 0xFF );				//读数据
  82  0010 a6ff          	ld	a,#255
  83  0012 cd0000        	call	_drv_spi_read_write_byte
  85  0015 6b01          	ld	(OFST+0,sp),a
  86                     ; 41     RF24L01_SET_CS_HIGH( );			//取消片选
  88  0017 4b10          	push	#16
  89  0019 ae5005        	ldw	x,#20485
  90  001c cd0000        	call	_GPIO_SetBits
  92  001f 84            	pop	a
  93                     ; 43     return btmp;
  95  0020 7b01          	ld	a,(OFST+0,sp)
  98  0022 85            	popw	x
  99  0023 81            	ret
 164                     ; 55 void NRF24L01_Read_Buf( uint8_t RegAddr, uint8_t *pBuf, uint8_t len )
 164                     ; 56 {
 165                     	switch	.text
 166  0024               _NRF24L01_Read_Buf:
 168  0024 88            	push	a
 169  0025 88            	push	a
 170       00000001      OFST:	set	1
 173                     ; 59     RF24L01_SET_CS_LOW( );			//片选
 175  0026 4b10          	push	#16
 176  0028 ae5005        	ldw	x,#20485
 177  002b cd0000        	call	_GPIO_ResetBits
 179  002e 84            	pop	a
 180                     ; 61     drv_spi_read_write_byte( NRF_READ_REG | RegAddr );	//读命令 地址
 182  002f 7b02          	ld	a,(OFST+1,sp)
 183  0031 cd0000        	call	_drv_spi_read_write_byte
 185                     ; 62     for( btmp = 0; btmp < len; btmp ++ )
 187  0034 0f01          	clr	(OFST+0,sp)
 189  0036 2015          	jra	L37
 190  0038               L76:
 191                     ; 64         *( pBuf + btmp ) = drv_spi_read_write_byte( 0xFF );	//读数据
 193  0038 7b05          	ld	a,(OFST+4,sp)
 194  003a 97            	ld	xl,a
 195  003b 7b06          	ld	a,(OFST+5,sp)
 196  003d 1b01          	add	a,(OFST+0,sp)
 197  003f 2401          	jrnc	L01
 198  0041 5c            	incw	x
 199  0042               L01:
 200  0042 02            	rlwa	x,a
 201  0043 89            	pushw	x
 202  0044 a6ff          	ld	a,#255
 203  0046 cd0000        	call	_drv_spi_read_write_byte
 205  0049 85            	popw	x
 206  004a f7            	ld	(x),a
 207                     ; 62     for( btmp = 0; btmp < len; btmp ++ )
 209  004b 0c01          	inc	(OFST+0,sp)
 210  004d               L37:
 213  004d 7b01          	ld	a,(OFST+0,sp)
 214  004f 1107          	cp	a,(OFST+6,sp)
 215  0051 25e5          	jrult	L76
 216                     ; 66     RF24L01_SET_CS_HIGH( );		//取消片选
 218  0053 4b10          	push	#16
 219  0055 ae5005        	ldw	x,#20485
 220  0058 cd0000        	call	_GPIO_SetBits
 222  005b 84            	pop	a
 223                     ; 67 }
 226  005c 85            	popw	x
 227  005d 81            	ret
 273                     ; 75 void NRF24L01_Write_Reg( uint8_t RegAddr, uint8_t Value )
 273                     ; 76 {
 274                     	switch	.text
 275  005e               _NRF24L01_Write_Reg:
 277  005e 89            	pushw	x
 278       00000000      OFST:	set	0
 281                     ; 77     RF24L01_SET_CS_LOW( );		//片选
 283  005f 4b10          	push	#16
 284  0061 ae5005        	ldw	x,#20485
 285  0064 cd0000        	call	_GPIO_ResetBits
 287  0067 84            	pop	a
 288                     ; 79     drv_spi_read_write_byte( NRF_WRITE_REG | RegAddr );	//写命令 地址
 290  0068 7b01          	ld	a,(OFST+1,sp)
 291  006a aa20          	or	a,#32
 292  006c cd0000        	call	_drv_spi_read_write_byte
 294                     ; 80     drv_spi_read_write_byte( Value );			//写数据
 296  006f 7b02          	ld	a,(OFST+2,sp)
 297  0071 cd0000        	call	_drv_spi_read_write_byte
 299                     ; 82     RF24L01_SET_CS_HIGH( );		//取消片选
 301  0074 4b10          	push	#16
 302  0076 ae5005        	ldw	x,#20485
 303  0079 cd0000        	call	_GPIO_SetBits
 305  007c 84            	pop	a
 306                     ; 83 }
 309  007d 85            	popw	x
 310  007e 81            	ret
 375                     ; 94 void NRF24L01_Write_Buf( uint8_t RegAddr, uint8_t *pBuf, uint8_t len )
 375                     ; 95 {
 376                     	switch	.text
 377  007f               _NRF24L01_Write_Buf:
 379  007f 88            	push	a
 380  0080 88            	push	a
 381       00000001      OFST:	set	1
 384                     ; 98     RF24L01_SET_CS_LOW( );		//片选
 386  0081 4b10          	push	#16
 387  0083 ae5005        	ldw	x,#20485
 388  0086 cd0000        	call	_GPIO_ResetBits
 390  0089 84            	pop	a
 391                     ; 100     drv_spi_read_write_byte( NRF_WRITE_REG | RegAddr );	//写命令 地址
 393  008a 7b02          	ld	a,(OFST+1,sp)
 394  008c aa20          	or	a,#32
 395  008e cd0000        	call	_drv_spi_read_write_byte
 397                     ; 101     for( i = 0; i < len; i ++ )
 399  0091 0f01          	clr	(OFST+0,sp)
 401  0093 2011          	jra	L751
 402  0095               L351:
 403                     ; 103         drv_spi_read_write_byte( *( pBuf + i ) );		//写数据
 405  0095 7b05          	ld	a,(OFST+4,sp)
 406  0097 97            	ld	xl,a
 407  0098 7b06          	ld	a,(OFST+5,sp)
 408  009a 1b01          	add	a,(OFST+0,sp)
 409  009c 2401          	jrnc	L61
 410  009e 5c            	incw	x
 411  009f               L61:
 412  009f 02            	rlwa	x,a
 413  00a0 f6            	ld	a,(x)
 414  00a1 cd0000        	call	_drv_spi_read_write_byte
 416                     ; 101     for( i = 0; i < len; i ++ )
 418  00a4 0c01          	inc	(OFST+0,sp)
 419  00a6               L751:
 422  00a6 7b01          	ld	a,(OFST+0,sp)
 423  00a8 1107          	cp	a,(OFST+6,sp)
 424  00aa 25e9          	jrult	L351
 425                     ; 106     RF24L01_SET_CS_HIGH( );		//取消片选
 427  00ac 4b10          	push	#16
 428  00ae ae5005        	ldw	x,#20485
 429  00b1 cd0000        	call	_GPIO_SetBits
 431  00b4 84            	pop	a
 432                     ; 107 }
 435  00b5 85            	popw	x
 436  00b6 81            	ret
 463                     ; 115 void NRF24L01_Flush_Tx_Fifo ( void )
 463                     ; 116 {
 464                     	switch	.text
 465  00b7               _NRF24L01_Flush_Tx_Fifo:
 469                     ; 117     RF24L01_SET_CS_LOW( );		//片选
 471  00b7 4b10          	push	#16
 472  00b9 ae5005        	ldw	x,#20485
 473  00bc cd0000        	call	_GPIO_ResetBits
 475  00bf 84            	pop	a
 476                     ; 119     drv_spi_read_write_byte( FLUSH_TX );	//清TX FIFO命令
 478  00c0 a6e1          	ld	a,#225
 479  00c2 cd0000        	call	_drv_spi_read_write_byte
 481                     ; 121     RF24L01_SET_CS_HIGH( );		//取消片选
 483  00c5 4b10          	push	#16
 484  00c7 ae5005        	ldw	x,#20485
 485  00ca cd0000        	call	_GPIO_SetBits
 487  00cd 84            	pop	a
 488                     ; 122 }
 491  00ce 81            	ret
 518                     ; 130 void NRF24L01_Flush_Rx_Fifo( void )
 518                     ; 131 {
 519                     	switch	.text
 520  00cf               _NRF24L01_Flush_Rx_Fifo:
 524                     ; 132     RF24L01_SET_CS_LOW( );		//片选
 526  00cf 4b10          	push	#16
 527  00d1 ae5005        	ldw	x,#20485
 528  00d4 cd0000        	call	_GPIO_ResetBits
 530  00d7 84            	pop	a
 531                     ; 134     drv_spi_read_write_byte( FLUSH_RX );	//清RX FIFO命令
 533  00d8 a6e2          	ld	a,#226
 534  00da cd0000        	call	_drv_spi_read_write_byte
 536                     ; 136     RF24L01_SET_CS_HIGH( );		//取消片选
 538  00dd 4b10          	push	#16
 539  00df ae5005        	ldw	x,#20485
 540  00e2 cd0000        	call	_GPIO_SetBits
 542  00e5 84            	pop	a
 543                     ; 137 }
 546  00e6 81            	ret
 573                     ; 145 void NRF24L01_Reuse_Tx_Payload( void )
 573                     ; 146 {
 574                     	switch	.text
 575  00e7               _NRF24L01_Reuse_Tx_Payload:
 579                     ; 147     RF24L01_SET_CS_LOW( );		//片选
 581  00e7 4b10          	push	#16
 582  00e9 ae5005        	ldw	x,#20485
 583  00ec cd0000        	call	_GPIO_ResetBits
 585  00ef 84            	pop	a
 586                     ; 149     drv_spi_read_write_byte( REUSE_TX_PL );		//重新使用上一包命令
 588  00f0 a6e3          	ld	a,#227
 589  00f2 cd0000        	call	_drv_spi_read_write_byte
 591                     ; 151     RF24L01_SET_CS_HIGH( );		//取消片选
 593  00f5 4b10          	push	#16
 594  00f7 ae5005        	ldw	x,#20485
 595  00fa cd0000        	call	_GPIO_SetBits
 597  00fd 84            	pop	a
 598                     ; 152 }
 601  00fe 81            	ret
 627                     ; 160 void NRF24L01_Nop( void )
 627                     ; 161 {
 628                     	switch	.text
 629  00ff               _NRF24L01_Nop:
 633                     ; 162     RF24L01_SET_CS_LOW( );		//片选
 635  00ff 4b10          	push	#16
 636  0101 ae5005        	ldw	x,#20485
 637  0104 cd0000        	call	_GPIO_ResetBits
 639  0107 84            	pop	a
 640                     ; 164     drv_spi_read_write_byte( NOP );		//空操作命令
 642  0108 a6ff          	ld	a,#255
 643  010a cd0000        	call	_drv_spi_read_write_byte
 645                     ; 166     RF24L01_SET_CS_HIGH( );		//取消片选
 647  010d 4b10          	push	#16
 648  010f ae5005        	ldw	x,#20485
 649  0112 cd0000        	call	_GPIO_SetBits
 651  0115 84            	pop	a
 652                     ; 167 }
 655  0116 81            	ret
 693                     ; 175 uint8_t NRF24L01_Read_Status_Register( void )
 693                     ; 176 {
 694                     	switch	.text
 695  0117               _NRF24L01_Read_Status_Register:
 697  0117 88            	push	a
 698       00000001      OFST:	set	1
 701                     ; 179     RF24L01_SET_CS_LOW( );		//片选
 703  0118 4b10          	push	#16
 704  011a ae5005        	ldw	x,#20485
 705  011d cd0000        	call	_GPIO_ResetBits
 707  0120 84            	pop	a
 708                     ; 181     Status = drv_spi_read_write_byte( NRF_READ_REG + STATUS );	//读状态寄存器
 710  0121 a607          	ld	a,#7
 711  0123 cd0000        	call	_drv_spi_read_write_byte
 713  0126 6b01          	ld	(OFST+0,sp),a
 714                     ; 183     RF24L01_SET_CS_HIGH( );		//取消片选
 716  0128 4b10          	push	#16
 717  012a ae5005        	ldw	x,#20485
 718  012d cd0000        	call	_GPIO_SetBits
 720  0130 84            	pop	a
 721                     ; 185     return Status;
 723  0131 7b01          	ld	a,(OFST+0,sp)
 726  0133 5b01          	addw	sp,#1
 727  0135 81            	ret
 775                     ; 195 uint8_t NRF24L01_Clear_IRQ_Flag( uint8_t IRQ_Source )
 775                     ; 196 {
 776                     	switch	.text
 777  0136               _NRF24L01_Clear_IRQ_Flag:
 779  0136 88            	push	a
 780  0137 88            	push	a
 781       00000001      OFST:	set	1
 784                     ; 197     uint8_t btmp = 0;
 786  0138 0f01          	clr	(OFST+0,sp)
 787                     ; 199     IRQ_Source &= ( 1 << RX_DR ) | ( 1 << TX_DS ) | ( 1 << MAX_RT );	//中断标志处理
 789  013a 7b02          	ld	a,(OFST+1,sp)
 790  013c a470          	and	a,#112
 791  013e 6b02          	ld	(OFST+1,sp),a
 792                     ; 200     btmp = NRF24L01_Read_Status_Register( );			//读状态寄存器
 794  0140 add5          	call	_NRF24L01_Read_Status_Register
 796  0142 6b01          	ld	(OFST+0,sp),a
 797                     ; 202     RF24L01_SET_CS_LOW( );			//片选
 799  0144 4b10          	push	#16
 800  0146 ae5005        	ldw	x,#20485
 801  0149 cd0000        	call	_GPIO_ResetBits
 803  014c 84            	pop	a
 804                     ; 203     drv_spi_read_write_byte( NRF_WRITE_REG + STATUS );	//写状态寄存器命令
 806  014d a627          	ld	a,#39
 807  014f cd0000        	call	_drv_spi_read_write_byte
 809                     ; 204     drv_spi_read_write_byte( IRQ_Source | btmp );		//清相应中断标志
 811  0152 7b02          	ld	a,(OFST+1,sp)
 812  0154 1a01          	or	a,(OFST+0,sp)
 813  0156 cd0000        	call	_drv_spi_read_write_byte
 815                     ; 205     RF24L01_SET_CS_HIGH( );			//取消片选
 817  0159 4b10          	push	#16
 818  015b ae5005        	ldw	x,#20485
 819  015e cd0000        	call	_GPIO_SetBits
 821  0161 84            	pop	a
 822                     ; 207     return ( NRF24L01_Read_Status_Register( ));			//返回状态寄存器状态
 824  0162 adb3          	call	_NRF24L01_Read_Status_Register
 828  0164 85            	popw	x
 829  0165 81            	ret
 854                     ; 216 uint8_t RF24L01_Read_IRQ_Status( void )
 854                     ; 217 {
 855                     	switch	.text
 856  0166               _RF24L01_Read_IRQ_Status:
 860                     ; 218     return ( NRF24L01_Read_Status_Register( ) & (( 1 << RX_DR ) | ( 1 << TX_DS ) | ( 1 << MAX_RT )));	//返回中断状态
 862  0166 adaf          	call	_NRF24L01_Read_Status_Register
 864  0168 a470          	and	a,#112
 867  016a 81            	ret
 905                     ; 227 uint8_t NRF24L01_Read_Top_Fifo_Width( void )
 905                     ; 228 {
 906                     	switch	.text
 907  016b               _NRF24L01_Read_Top_Fifo_Width:
 909  016b 88            	push	a
 910       00000001      OFST:	set	1
 913                     ; 231     RF24L01_SET_CS_LOW( );		//片选
 915  016c 4b10          	push	#16
 916  016e ae5005        	ldw	x,#20485
 917  0171 cd0000        	call	_GPIO_ResetBits
 919  0174 84            	pop	a
 920                     ; 233     drv_spi_read_write_byte( R_RX_PL_WID );	//读FIFO中数据宽度命令
 922  0175 a660          	ld	a,#96
 923  0177 cd0000        	call	_drv_spi_read_write_byte
 925                     ; 234     btmp = drv_spi_read_write_byte( 0xFF );	//读数据
 927  017a a6ff          	ld	a,#255
 928  017c cd0000        	call	_drv_spi_read_write_byte
 930  017f 6b01          	ld	(OFST+0,sp),a
 931                     ; 236     RF24L01_SET_CS_HIGH( );		//取消片选
 933  0181 4b10          	push	#16
 934  0183 ae5005        	ldw	x,#20485
 935  0186 cd0000        	call	_GPIO_SetBits
 937  0189 84            	pop	a
 938                     ; 238     return btmp;
 940  018a 7b01          	ld	a,(OFST+0,sp)
 943  018c 5b01          	addw	sp,#1
 944  018e 81            	ret
1004                     ; 248 uint8_t NRF24L01_Read_Rx_Payload( uint8_t *pRxBuf )
1004                     ; 249 {
1005                     	switch	.text
1006  018f               _NRF24L01_Read_Rx_Payload:
1008  018f 89            	pushw	x
1009  0190 89            	pushw	x
1010       00000002      OFST:	set	2
1013                     ; 252     PipeNum = ( NRF24L01_Read_Reg( STATUS ) >> 1 ) & 0x07;	//读接收状态
1015  0191 7b02          	ld	a,(OFST+0,sp)
1016  0193 97            	ld	xl,a
1017  0194 a607          	ld	a,#7
1018  0196 cd0000        	call	_NRF24L01_Read_Reg
1020  0199 44            	srl	a
1021  019a a407          	and	a,#7
1022                     ; 253     Width = NRF24L01_Read_Top_Fifo_Width( );		//读接收数据个数
1024  019c adcd          	call	_NRF24L01_Read_Top_Fifo_Width
1026  019e 6b01          	ld	(OFST-1,sp),a
1027                     ; 255     RF24L01_SET_CS_LOW( );		//片选
1029  01a0 4b10          	push	#16
1030  01a2 ae5005        	ldw	x,#20485
1031  01a5 cd0000        	call	_GPIO_ResetBits
1033  01a8 84            	pop	a
1034                     ; 256     drv_spi_read_write_byte( RD_RX_PLOAD );			//读有效数据命令
1036  01a9 a661          	ld	a,#97
1037  01ab cd0000        	call	_drv_spi_read_write_byte
1039                     ; 258     for( PipeNum = 0; PipeNum < Width; PipeNum ++ )
1041  01ae 0f02          	clr	(OFST+0,sp)
1043  01b0 2015          	jra	L343
1044  01b2               L733:
1045                     ; 260         *( pRxBuf + PipeNum ) = drv_spi_read_write_byte( 0xFF );		//读数据
1047  01b2 7b03          	ld	a,(OFST+1,sp)
1048  01b4 97            	ld	xl,a
1049  01b5 7b04          	ld	a,(OFST+2,sp)
1050  01b7 1b02          	add	a,(OFST+0,sp)
1051  01b9 2401          	jrnc	L24
1052  01bb 5c            	incw	x
1053  01bc               L24:
1054  01bc 02            	rlwa	x,a
1055  01bd 89            	pushw	x
1056  01be a6ff          	ld	a,#255
1057  01c0 cd0000        	call	_drv_spi_read_write_byte
1059  01c3 85            	popw	x
1060  01c4 f7            	ld	(x),a
1061                     ; 258     for( PipeNum = 0; PipeNum < Width; PipeNum ++ )
1063  01c5 0c02          	inc	(OFST+0,sp)
1064  01c7               L343:
1067  01c7 7b02          	ld	a,(OFST+0,sp)
1068  01c9 1101          	cp	a,(OFST-1,sp)
1069  01cb 25e5          	jrult	L733
1070                     ; 262     RF24L01_SET_CS_HIGH( );		//取消片选
1072  01cd 4b10          	push	#16
1073  01cf ae5005        	ldw	x,#20485
1074  01d2 cd0000        	call	_GPIO_SetBits
1076  01d5 84            	pop	a
1077                     ; 263     NRF24L01_Flush_Rx_Fifo( );	//清空RX FIFO
1079  01d6 cd00cf        	call	_NRF24L01_Flush_Rx_Fifo
1081                     ; 265     return Width;
1083  01d9 7b01          	ld	a,(OFST-1,sp)
1086  01db 5b04          	addw	sp,#4
1087  01dd 81            	ret
1154                     ; 276 void NRF24L01_Write_Tx_Payload_Ack( uint8_t *pTxBuf, uint8_t len )
1154                     ; 277 {
1155                     	switch	.text
1156  01de               _NRF24L01_Write_Tx_Payload_Ack:
1158  01de 89            	pushw	x
1159  01df 89            	pushw	x
1160       00000002      OFST:	set	2
1163                     ; 279     uint8_t length = ( len > 32 ) ? 32 : len;		//数据长达大约32 则只发送32个
1165  01e0 7b07          	ld	a,(OFST+5,sp)
1166  01e2 a121          	cp	a,#33
1167  01e4 2504          	jrult	L64
1168  01e6 a620          	ld	a,#32
1169  01e8 2002          	jra	L05
1170  01ea               L64:
1171  01ea 7b07          	ld	a,(OFST+5,sp)
1172  01ec               L05:
1173  01ec 6b01          	ld	(OFST-1,sp),a
1174                     ; 281     NRF24L01_Flush_Tx_Fifo( );		//清TX FIFO
1176  01ee cd00b7        	call	_NRF24L01_Flush_Tx_Fifo
1178                     ; 283     RF24L01_SET_CS_LOW( );			//片选
1180  01f1 4b10          	push	#16
1181  01f3 ae5005        	ldw	x,#20485
1182  01f6 cd0000        	call	_GPIO_ResetBits
1184  01f9 84            	pop	a
1185                     ; 284     drv_spi_read_write_byte( WR_TX_PLOAD );	//发送命令
1187  01fa a6a0          	ld	a,#160
1188  01fc cd0000        	call	_drv_spi_read_write_byte
1190                     ; 286     for( btmp = 0; btmp < length; btmp ++ )
1192  01ff 0f02          	clr	(OFST+0,sp)
1194  0201 2011          	jra	L504
1195  0203               L104:
1196                     ; 288         drv_spi_read_write_byte( *( pTxBuf + btmp ) );	//发送数据
1198  0203 7b03          	ld	a,(OFST+1,sp)
1199  0205 97            	ld	xl,a
1200  0206 7b04          	ld	a,(OFST+2,sp)
1201  0208 1b02          	add	a,(OFST+0,sp)
1202  020a 2401          	jrnc	L25
1203  020c 5c            	incw	x
1204  020d               L25:
1205  020d 02            	rlwa	x,a
1206  020e f6            	ld	a,(x)
1207  020f cd0000        	call	_drv_spi_read_write_byte
1209                     ; 286     for( btmp = 0; btmp < length; btmp ++ )
1211  0212 0c02          	inc	(OFST+0,sp)
1212  0214               L504:
1215  0214 7b02          	ld	a,(OFST+0,sp)
1216  0216 1101          	cp	a,(OFST-1,sp)
1217  0218 25e9          	jrult	L104
1218                     ; 290     RF24L01_SET_CS_HIGH( );			//取消片选
1220  021a 4b10          	push	#16
1221  021c ae5005        	ldw	x,#20485
1222  021f cd0000        	call	_GPIO_SetBits
1224  0222 84            	pop	a
1225                     ; 291 }
1228  0223 5b04          	addw	sp,#4
1229  0225 81            	ret
1277                     ; 301 void NRF24L01_Write_Tx_Payload_NoAck( uint8_t *pTxBuf, uint8_t len )
1277                     ; 302 {
1278                     	switch	.text
1279  0226               _NRF24L01_Write_Tx_Payload_NoAck:
1281  0226 89            	pushw	x
1282       00000000      OFST:	set	0
1285                     ; 303     if( len > 32 || len == 0 )
1287  0227 7b05          	ld	a,(OFST+5,sp)
1288  0229 a121          	cp	a,#33
1289  022b 2404          	jruge	L534
1291  022d 0d05          	tnz	(OFST+5,sp)
1292  022f 2602          	jrne	L334
1293  0231               L534:
1294                     ; 305         return ;		//数据长度大于32 或者等于0 不执行
1296  0231 202d          	jra	L65
1297  0233               L334:
1298                     ; 308     RF24L01_SET_CS_LOW( );	//片选
1300  0233 4b10          	push	#16
1301  0235 ae5005        	ldw	x,#20485
1302  0238 cd0000        	call	_GPIO_ResetBits
1304  023b 84            	pop	a
1305                     ; 309     drv_spi_read_write_byte( WR_TX_PLOAD_NACK );	//发送命令
1307  023c a6b0          	ld	a,#176
1308  023e cd0000        	call	_drv_spi_read_write_byte
1311  0241 200d          	jra	L144
1312  0243               L734:
1313                     ; 312         drv_spi_read_write_byte( *pTxBuf );			//发送数据
1315  0243 1e01          	ldw	x,(OFST+1,sp)
1316  0245 f6            	ld	a,(x)
1317  0246 cd0000        	call	_drv_spi_read_write_byte
1319                     ; 313 		pTxBuf++;
1321  0249 1e01          	ldw	x,(OFST+1,sp)
1322  024b 1c0001        	addw	x,#1
1323  024e 1f01          	ldw	(OFST+1,sp),x
1324  0250               L144:
1325                     ; 310     while( len-- )
1327  0250 7b05          	ld	a,(OFST+5,sp)
1328  0252 0a05          	dec	(OFST+5,sp)
1329  0254 4d            	tnz	a
1330  0255 26ec          	jrne	L734
1331                     ; 315     RF24L01_SET_CS_HIGH( );		//取消片选
1333  0257 4b10          	push	#16
1334  0259 ae5005        	ldw	x,#20485
1335  025c cd0000        	call	_GPIO_SetBits
1337  025f 84            	pop	a
1338                     ; 316 }
1339  0260               L65:
1342  0260 85            	popw	x
1343  0261 81            	ret
1400                     ; 326 void NRF24L01_Write_Tx_Payload_InAck( uint8_t *pData, uint8_t len )
1400                     ; 327 {
1401                     	switch	.text
1402  0262               _NRF24L01_Write_Tx_Payload_InAck:
1404  0262 89            	pushw	x
1405  0263 88            	push	a
1406       00000001      OFST:	set	1
1409                     ; 330 	len = ( len > 32 ) ? 32 : len;		//数据长度大于32个则只写32个字节
1411  0264 7b06          	ld	a,(OFST+5,sp)
1412  0266 a121          	cp	a,#33
1413  0268 2504          	jrult	L26
1414  026a a620          	ld	a,#32
1415  026c 2002          	jra	L46
1416  026e               L26:
1417  026e 7b06          	ld	a,(OFST+5,sp)
1418  0270               L46:
1419  0270 6b06          	ld	(OFST+5,sp),a
1420                     ; 332     RF24L01_SET_CS_LOW( );			//片选
1422  0272 4b10          	push	#16
1423  0274 ae5005        	ldw	x,#20485
1424  0277 cd0000        	call	_GPIO_ResetBits
1426  027a 84            	pop	a
1427                     ; 333     drv_spi_read_write_byte( W_ACK_PLOAD );		//命令
1429  027b a6a8          	ld	a,#168
1430  027d cd0000        	call	_drv_spi_read_write_byte
1432                     ; 334     for( btmp = 0; btmp < len; btmp ++ )
1434  0280 0f01          	clr	(OFST+0,sp)
1436  0282 2011          	jra	L774
1437  0284               L374:
1438                     ; 336         drv_spi_read_write_byte( *( pData + btmp ) );	//写数据
1440  0284 7b02          	ld	a,(OFST+1,sp)
1441  0286 97            	ld	xl,a
1442  0287 7b03          	ld	a,(OFST+2,sp)
1443  0289 1b01          	add	a,(OFST+0,sp)
1444  028b 2401          	jrnc	L66
1445  028d 5c            	incw	x
1446  028e               L66:
1447  028e 02            	rlwa	x,a
1448  028f f6            	ld	a,(x)
1449  0290 cd0000        	call	_drv_spi_read_write_byte
1451                     ; 334     for( btmp = 0; btmp < len; btmp ++ )
1453  0293 0c01          	inc	(OFST+0,sp)
1454  0295               L774:
1457  0295 7b01          	ld	a,(OFST+0,sp)
1458  0297 1106          	cp	a,(OFST+5,sp)
1459  0299 25e9          	jrult	L374
1460                     ; 338     RF24L01_SET_CS_HIGH( );			//取消片选
1462  029b 4b10          	push	#16
1463  029d ae5005        	ldw	x,#20485
1464  02a0 cd0000        	call	_GPIO_SetBits
1466  02a3 84            	pop	a
1467                     ; 339 }
1470  02a4 5b03          	addw	sp,#3
1471  02a6 81            	ret
1517                     ; 349 void NRF24L01_Set_TxAddr( uint8_t *pAddr, uint8_t len )
1517                     ; 350 {
1518                     	switch	.text
1519  02a7               _NRF24L01_Set_TxAddr:
1521  02a7 89            	pushw	x
1522       00000000      OFST:	set	0
1525                     ; 351 	len = ( len > 5 ) ? 5 : len;					//地址不能大于5个字节
1527  02a8 7b05          	ld	a,(OFST+5,sp)
1528  02aa a106          	cp	a,#6
1529  02ac 2504          	jrult	L27
1530  02ae a605          	ld	a,#5
1531  02b0 2002          	jra	L47
1532  02b2               L27:
1533  02b2 7b05          	ld	a,(OFST+5,sp)
1534  02b4               L47:
1535  02b4 6b05          	ld	(OFST+5,sp),a
1536                     ; 352     NRF24L01_Write_Buf( TX_ADDR, pAddr, len );	//写地址
1538  02b6 7b05          	ld	a,(OFST+5,sp)
1539  02b8 88            	push	a
1540  02b9 89            	pushw	x
1541  02ba a610          	ld	a,#16
1542  02bc cd007f        	call	_NRF24L01_Write_Buf
1544  02bf 5b03          	addw	sp,#3
1545                     ; 353 }
1548  02c1 85            	popw	x
1549  02c2 81            	ret
1604                     ; 364 void NRF24L01_Set_RxAddr( uint8_t PipeNum, uint8_t *pAddr, uint8_t Len )
1604                     ; 365 {
1605                     	switch	.text
1606  02c3               _NRF24L01_Set_RxAddr:
1608  02c3 88            	push	a
1609       00000000      OFST:	set	0
1612                     ; 366     Len = ( Len > 5 ) ? 5 : Len;
1614  02c4 7b06          	ld	a,(OFST+6,sp)
1615  02c6 a106          	cp	a,#6
1616  02c8 2504          	jrult	L001
1617  02ca a605          	ld	a,#5
1618  02cc 2002          	jra	L201
1619  02ce               L001:
1620  02ce 7b06          	ld	a,(OFST+6,sp)
1621  02d0               L201:
1622  02d0 6b06          	ld	(OFST+6,sp),a
1623                     ; 367     PipeNum = ( PipeNum > 5 ) ? 5 : PipeNum;		//通道不大于5 地址长度不大于5个字节
1625  02d2 7b01          	ld	a,(OFST+1,sp)
1626  02d4 a106          	cp	a,#6
1627  02d6 2504          	jrult	L401
1628  02d8 a605          	ld	a,#5
1629  02da 2002          	jra	L601
1630  02dc               L401:
1631  02dc 7b01          	ld	a,(OFST+1,sp)
1632  02de               L601:
1633  02de 6b01          	ld	(OFST+1,sp),a
1634                     ; 369     NRF24L01_Write_Buf( RX_ADDR_P0 + PipeNum, pAddr, Len );	//写入地址
1636  02e0 7b06          	ld	a,(OFST+6,sp)
1637  02e2 88            	push	a
1638  02e3 1e05          	ldw	x,(OFST+5,sp)
1639  02e5 89            	pushw	x
1640  02e6 7b04          	ld	a,(OFST+4,sp)
1641  02e8 ab0a          	add	a,#10
1642  02ea cd007f        	call	_NRF24L01_Write_Buf
1644  02ed 5b03          	addw	sp,#3
1645                     ; 370 }
1648  02ef 84            	pop	a
1649  02f0 81            	ret
1722                     ; 379 void NRF24L01_Set_Speed( nRf24l01SpeedType Speed )
1722                     ; 380 {
1723                     	switch	.text
1724  02f1               _NRF24L01_Set_Speed:
1726  02f1 88            	push	a
1727  02f2 88            	push	a
1728       00000001      OFST:	set	1
1731                     ; 381 	uint8_t btmp = 0;
1733  02f3 0f01          	clr	(OFST+0,sp)
1734                     ; 383 	btmp = NRF24L01_Read_Reg( RF_SETUP );
1736  02f5 a606          	ld	a,#6
1737  02f7 cd0000        	call	_NRF24L01_Read_Reg
1739  02fa 6b01          	ld	(OFST+0,sp),a
1740                     ; 384 	btmp &= ~( ( 1<<5 ) | ( 1<<3 ) );
1742  02fc 7b01          	ld	a,(OFST+0,sp)
1743  02fe a4d7          	and	a,#215
1744  0300 6b01          	ld	(OFST+0,sp),a
1745                     ; 386 	if( Speed == SPEED_250K )		//250K
1747  0302 0d02          	tnz	(OFST+1,sp)
1748  0304 2608          	jrne	L706
1749                     ; 388 		btmp |= ( 1<<5 );
1751  0306 7b01          	ld	a,(OFST+0,sp)
1752  0308 aa20          	or	a,#32
1753  030a 6b01          	ld	(OFST+0,sp),a
1755  030c 201a          	jra	L116
1756  030e               L706:
1757                     ; 390 	else if( Speed == SPEED_1M )   //1M
1759  030e 7b02          	ld	a,(OFST+1,sp)
1760  0310 a101          	cp	a,#1
1761  0312 2608          	jrne	L316
1762                     ; 392    		btmp &= ~( ( 1<<5 ) | ( 1<<3 ) );
1764  0314 7b01          	ld	a,(OFST+0,sp)
1765  0316 a4d7          	and	a,#215
1766  0318 6b01          	ld	(OFST+0,sp),a
1768  031a 200c          	jra	L116
1769  031c               L316:
1770                     ; 394 	else if( Speed == SPEED_2M )   //2M
1772  031c 7b02          	ld	a,(OFST+1,sp)
1773  031e a102          	cp	a,#2
1774  0320 2606          	jrne	L116
1775                     ; 396 		btmp |= ( 1<<3 );
1777  0322 7b01          	ld	a,(OFST+0,sp)
1778  0324 aa08          	or	a,#8
1779  0326 6b01          	ld	(OFST+0,sp),a
1780  0328               L116:
1781                     ; 399 	NRF24L01_Write_Reg( RF_SETUP, btmp );
1783  0328 7b01          	ld	a,(OFST+0,sp)
1784  032a 97            	ld	xl,a
1785  032b a606          	ld	a,#6
1786  032d 95            	ld	xh,a
1787  032e cd005e        	call	_NRF24L01_Write_Reg
1789                     ; 400 }
1792  0331 85            	popw	x
1793  0332 81            	ret
1873                     ; 409 void NRF24L01_Set_Power( nRf24l01PowerType Power )
1873                     ; 410 {
1874                     	switch	.text
1875  0333               _NRF24L01_Set_Power:
1877  0333 88            	push	a
1878  0334 88            	push	a
1879       00000001      OFST:	set	1
1882                     ; 413 	btmp = NRF24L01_Read_Reg( RF_SETUP ) & ~0x07;
1884  0335 a606          	ld	a,#6
1885  0337 cd0000        	call	_NRF24L01_Read_Reg
1887  033a a4f8          	and	a,#248
1888  033c 6b01          	ld	(OFST+0,sp),a
1889                     ; 414     switch( Power )
1891  033e 7b02          	ld	a,(OFST+1,sp)
1893                     ; 428         default:
1893                     ; 429             break;
1894  0340 4d            	tnz	a
1895  0341 270b          	jreq	L126
1896  0343 4a            	dec	a
1897  0344 270d          	jreq	L326
1898  0346 4a            	dec	a
1899  0347 2712          	jreq	L526
1900  0349 4a            	dec	a
1901  034a 2717          	jreq	L726
1902  034c 201b          	jra	L376
1903  034e               L126:
1904                     ; 416         case POWER_F18DBM:
1904                     ; 417             btmp |= PWR_18DB;
1906  034e 7b01          	ld	a,(OFST+0,sp)
1907  0350 97            	ld	xl,a
1908                     ; 418             break;
1910  0351 2016          	jra	L376
1911  0353               L326:
1912                     ; 419         case POWER_F12DBM:
1912                     ; 420             btmp |= PWR_12DB;
1914  0353 7b01          	ld	a,(OFST+0,sp)
1915  0355 aa02          	or	a,#2
1916  0357 6b01          	ld	(OFST+0,sp),a
1917                     ; 421             break;
1919  0359 200e          	jra	L376
1920  035b               L526:
1921                     ; 422         case POWER_F6DBM:
1921                     ; 423             btmp |= PWR_6DB;
1923  035b 7b01          	ld	a,(OFST+0,sp)
1924  035d aa04          	or	a,#4
1925  035f 6b01          	ld	(OFST+0,sp),a
1926                     ; 424             break;
1928  0361 2006          	jra	L376
1929  0363               L726:
1930                     ; 425         case POWER_0DBM:
1930                     ; 426             btmp |= PWR_0DB;
1932  0363 7b01          	ld	a,(OFST+0,sp)
1933  0365 aa06          	or	a,#6
1934  0367 6b01          	ld	(OFST+0,sp),a
1935                     ; 427             break;
1937  0369               L136:
1938                     ; 428         default:
1938                     ; 429             break;
1940  0369               L376:
1941                     ; 431     NRF24L01_Write_Reg( RF_SETUP, btmp );
1943  0369 7b01          	ld	a,(OFST+0,sp)
1944  036b 97            	ld	xl,a
1945  036c a606          	ld	a,#6
1946  036e 95            	ld	xh,a
1947  036f cd005e        	call	_NRF24L01_Write_Reg
1949                     ; 432 }
1952  0372 85            	popw	x
1953  0373 81            	ret
1989                     ; 441 void RF24LL01_Write_Hopping_Point( uint8_t FreqPoint )
1989                     ; 442 {
1990                     	switch	.text
1991  0374               _RF24LL01_Write_Hopping_Point:
1995                     ; 443     NRF24L01_Write_Reg(  RF_CH, FreqPoint & 0x7F );
1997  0374 a47f          	and	a,#127
1998  0376 97            	ld	xl,a
1999  0377 a605          	ld	a,#5
2000  0379 95            	ld	xh,a
2001  037a cd005e        	call	_NRF24L01_Write_Reg
2003                     ; 444 }
2006  037d 81            	ret
2009                     .const:	section	.text
2010  0000               L317_buf:
2011  0000 a5            	dc.b	165
2012  0001 a5            	dc.b	165
2013  0002 a5            	dc.b	165
2014  0003 a5            	dc.b	165
2015  0004 a5            	dc.b	165
2016  0005               L517_read_buf:
2017  0005 00            	dc.b	0
2018  0006 00000000      	ds.b	4
2075                     ; 452 void NRF24L01_check( void )
2075                     ; 453 {
2076                     	switch	.text
2077  037e               _NRF24L01_check:
2079  037e 520c          	subw	sp,#12
2080       0000000c      OFST:	set	12
2083                     ; 455 	uint8_t buf[5]={ 0XA5, 0XA5, 0XA5, 0XA5, 0XA5 };
2085  0380 96            	ldw	x,sp
2086  0381 1c0002        	addw	x,#OFST-10
2087  0384 90ae0000      	ldw	y,#L317_buf
2088  0388 a605          	ld	a,#5
2089  038a cd0000        	call	c_xymvx
2091                     ; 456 	uint8_t read_buf[ 5 ] = { 0 };
2093  038d 96            	ldw	x,sp
2094  038e 1c0007        	addw	x,#OFST-5
2095  0391 90ae0005      	ldw	y,#L517_read_buf
2096  0395 a605          	ld	a,#5
2097  0397 cd0000        	call	c_xymvx
2099  039a               L547:
2100                     ; 460 		NRF24L01_Write_Buf( TX_ADDR, buf, 5 );			//写入5个字节的地址
2102  039a 4b05          	push	#5
2103  039c 96            	ldw	x,sp
2104  039d 1c0003        	addw	x,#OFST-9
2105  03a0 89            	pushw	x
2106  03a1 a610          	ld	a,#16
2107  03a3 cd007f        	call	_NRF24L01_Write_Buf
2109  03a6 5b03          	addw	sp,#3
2110                     ; 461 		NRF24L01_Read_Buf( TX_ADDR, read_buf, 5 );		//读出写入的地址  
2112  03a8 4b05          	push	#5
2113  03aa 96            	ldw	x,sp
2114  03ab 1c0008        	addw	x,#OFST-4
2115  03ae 89            	pushw	x
2116  03af a610          	ld	a,#16
2117  03b1 cd0024        	call	_NRF24L01_Read_Buf
2119  03b4 5b03          	addw	sp,#3
2120                     ; 462 		for( i = 0; i < 5; i++ )
2122  03b6 0f0c          	clr	(OFST+0,sp)
2123  03b8               L157:
2124                     ; 464 			if( buf[ i ] != read_buf[ i ] )
2126  03b8 96            	ldw	x,sp
2127  03b9 1c0007        	addw	x,#OFST-5
2128  03bc 9f            	ld	a,xl
2129  03bd 5e            	swapw	x
2130  03be 1b0c          	add	a,(OFST+0,sp)
2131  03c0 2401          	jrnc	L021
2132  03c2 5c            	incw	x
2133  03c3               L021:
2134  03c3 02            	rlwa	x,a
2135  03c4 f6            	ld	a,(x)
2136  03c5 6b01          	ld	(OFST-11,sp),a
2137  03c7 96            	ldw	x,sp
2138  03c8 1c0002        	addw	x,#OFST-10
2139  03cb 9f            	ld	a,xl
2140  03cc 5e            	swapw	x
2141  03cd 1b0c          	add	a,(OFST+0,sp)
2142  03cf 2401          	jrnc	L221
2143  03d1 5c            	incw	x
2144  03d2               L221:
2145  03d2 02            	rlwa	x,a
2146  03d3 f6            	ld	a,(x)
2147  03d4 1101          	cp	a,(OFST-11,sp)
2148  03d6 2608          	jrne	L557
2149                     ; 466 				break;
2151                     ; 462 		for( i = 0; i < 5; i++ )
2153  03d8 0c0c          	inc	(OFST+0,sp)
2156  03da 7b0c          	ld	a,(OFST+0,sp)
2157  03dc a105          	cp	a,#5
2158  03de 25d8          	jrult	L157
2159  03e0               L557:
2160                     ; 470 		if( 5 == i )
2162  03e0 7b0c          	ld	a,(OFST+0,sp)
2163  03e2 a105          	cp	a,#5
2164  03e4 2603          	jrne	L167
2165                     ; 472 			break;
2166                     ; 480 }
2169  03e6 5b0c          	addw	sp,#12
2170  03e8 81            	ret
2171  03e9               L167:
2172                     ; 476 			drv_uart_tx_bytes( (uint8_t *)g_ErrorString, 26 );
2174  03e9 4b1a          	push	#26
2175  03eb be00          	ldw	x,_g_ErrorString
2176  03ed cd0000        	call	_drv_uart_tx_bytes
2178  03f0 84            	pop	a
2179                     ; 478 		drv_delay_ms( 2000 );
2181  03f1 ae07d0        	ldw	x,#2000
2182  03f4 cd0000        	call	_drv_delay_ms
2185  03f7 20a1          	jra	L547
2251                     ; 489 void RF24L01_Set_Mode( nRf24l01ModeType Mode )
2251                     ; 490 {
2252                     	switch	.text
2253  03f9               _RF24L01_Set_Mode:
2255  03f9 88            	push	a
2256  03fa 88            	push	a
2257       00000001      OFST:	set	1
2260                     ; 491     uint8_t controlreg = 0;
2262  03fb 0f01          	clr	(OFST+0,sp)
2263                     ; 492 	controlreg = NRF24L01_Read_Reg( CONFIG );
2265  03fd 4f            	clr	a
2266  03fe cd0000        	call	_NRF24L01_Read_Reg
2268  0401 6b01          	ld	(OFST+0,sp),a
2269                     ; 494     if( Mode == MODE_TX )       
2271  0403 0d02          	tnz	(OFST+1,sp)
2272  0405 2608          	jrne	L7101
2273                     ; 496 		controlreg &= ~( 1<< PRIM_RX );
2275  0407 7b01          	ld	a,(OFST+0,sp)
2276  0409 a4fe          	and	a,#254
2277  040b 6b01          	ld	(OFST+0,sp),a
2279  040d 200c          	jra	L1201
2280  040f               L7101:
2281                     ; 500 		if( Mode == MODE_RX )  
2283  040f 7b02          	ld	a,(OFST+1,sp)
2284  0411 a101          	cp	a,#1
2285  0413 2606          	jrne	L1201
2286                     ; 502 			controlreg |= ( 1<< PRIM_RX ); 
2288  0415 7b01          	ld	a,(OFST+0,sp)
2289  0417 aa01          	or	a,#1
2290  0419 6b01          	ld	(OFST+0,sp),a
2291  041b               L1201:
2292                     ; 506     NRF24L01_Write_Reg( CONFIG, controlreg );
2294  041b 7b01          	ld	a,(OFST+0,sp)
2295  041d 97            	ld	xl,a
2296  041e 4f            	clr	a
2297  041f 95            	ld	xh,a
2298  0420 cd005e        	call	_NRF24L01_Write_Reg
2300                     ; 507 }
2303  0423 85            	popw	x
2304  0424 81            	ret
2376                     ; 520 uint8_t NRF24L01_TxPacket( uint8_t *txbuf, uint8_t Length )
2376                     ; 521 {
2377                     	switch	.text
2378  0425               _NRF24L01_TxPacket:
2380  0425 89            	pushw	x
2381  0426 5203          	subw	sp,#3
2382       00000003      OFST:	set	3
2385                     ; 522 	uint8_t l_Status = 0;
2387  0428 7b03          	ld	a,(OFST+0,sp)
2388  042a 97            	ld	xl,a
2389                     ; 523 	uint16_t l_MsTimes = 0;
2391  042b 5f            	clrw	x
2392  042c 1f01          	ldw	(OFST-2,sp),x
2393                     ; 525 	RF24L01_SET_CS_LOW( );		//片选
2395  042e 4b10          	push	#16
2396  0430 ae5005        	ldw	x,#20485
2397  0433 cd0000        	call	_GPIO_ResetBits
2399  0436 84            	pop	a
2400                     ; 526 	drv_spi_read_write_byte( FLUSH_TX );
2402  0437 a6e1          	ld	a,#225
2403  0439 cd0000        	call	_drv_spi_read_write_byte
2405                     ; 527 	RF24L01_SET_CS_HIGH( );
2407  043c 4b10          	push	#16
2408  043e ae5005        	ldw	x,#20485
2409  0441 cd0000        	call	_GPIO_SetBits
2411  0444 84            	pop	a
2412                     ; 529 	RF24L01_SET_CE_LOW( );		
2414  0445 4b08          	push	#8
2415  0447 ae5005        	ldw	x,#20485
2416  044a cd0000        	call	_GPIO_ResetBits
2418  044d 84            	pop	a
2419                     ; 530 	NRF24L01_Write_Buf( WR_TX_PLOAD, txbuf, Length );	//写数据到TX BUF 32字节  TX_PLOAD_WIDTH
2421  044e 7b08          	ld	a,(OFST+5,sp)
2422  0450 88            	push	a
2423  0451 1e05          	ldw	x,(OFST+2,sp)
2424  0453 89            	pushw	x
2425  0454 a6a0          	ld	a,#160
2426  0456 cd007f        	call	_NRF24L01_Write_Buf
2428  0459 5b03          	addw	sp,#3
2429                     ; 531 	RF24L01_SET_CE_HIGH( );			//启动发送
2431  045b 4b08          	push	#8
2432  045d ae5005        	ldw	x,#20485
2433  0460 cd0000        	call	_GPIO_SetBits
2435  0463 84            	pop	a
2437  0464 2042          	jra	L1601
2438  0466               L7501:
2439                     ; 534 		drv_delay_ms( 1 );
2441  0466 ae0001        	ldw	x,#1
2442  0469 cd0000        	call	_drv_delay_ms
2444                     ; 535 		if( 500 == l_MsTimes++ )						//500ms还没有发送成功，重新初始化设备
2446  046c 1e01          	ldw	x,(OFST-2,sp)
2447  046e 1c0001        	addw	x,#1
2448  0471 1f01          	ldw	(OFST-2,sp),x
2449  0473 1d0001        	subw	x,#1
2450  0476 a301f4        	cpw	x,#500
2451  0479 262d          	jrne	L1601
2452                     ; 537 			NRF24L01_Gpio_Init( );
2454  047b cd0554        	call	_NRF24L01_Gpio_Init
2456                     ; 538 			RF24L01_Init( );
2458  047e cd057d        	call	_RF24L01_Init
2460                     ; 539 			RF24L01_Set_Mode( MODE_TX );
2462  0481 4f            	clr	a
2463  0482 cd03f9        	call	_RF24L01_Set_Mode
2465                     ; 540 			break;
2466  0485               L3601:
2467                     ; 543 	l_Status = NRF24L01_Read_Reg(STATUS);						//读状态寄存器
2469  0485 a607          	ld	a,#7
2470  0487 cd0000        	call	_NRF24L01_Read_Reg
2472  048a 6b03          	ld	(OFST+0,sp),a
2473                     ; 544 	NRF24L01_Write_Reg( STATUS, l_Status );						//清除TX_DS或MAX_RT中断标志
2475  048c 7b03          	ld	a,(OFST+0,sp)
2476  048e 97            	ld	xl,a
2477  048f a607          	ld	a,#7
2478  0491 95            	ld	xh,a
2479  0492 cd005e        	call	_NRF24L01_Write_Reg
2481                     ; 546 	if( l_Status & MAX_TX )	//达到最大重发次数
2483  0495 7b03          	ld	a,(OFST+0,sp)
2484  0497 a510          	bcp	a,#16
2485  0499 2721          	jreq	L7601
2486                     ; 548 		NRF24L01_Write_Reg( FLUSH_TX,0xff );	//清除TX FIFO寄存器
2488  049b ae00ff        	ldw	x,#255
2489  049e a6e1          	ld	a,#225
2490  04a0 95            	ld	xh,a
2491  04a1 cd005e        	call	_NRF24L01_Write_Reg
2493                     ; 549 		return MAX_TX; 
2495  04a4 a610          	ld	a,#16
2497  04a6 201c          	jra	L431
2498  04a8               L1601:
2499                     ; 532 	while( 0 != RF24L01_GET_IRQ_STATUS( ))
2501  04a8 c6500b        	ld	a,20491
2502  04ab a501          	bcp	a,#1
2503  04ad 2603          	jrne	L031
2504  04af 5f            	clrw	x
2505  04b0 2003          	jra	L231
2506  04b2               L031:
2507  04b2 ae0001        	ldw	x,#1
2508  04b5               L231:
2509  04b5 a30000        	cpw	x,#0
2510  04b8 26ac          	jrne	L7501
2511  04ba 20c9          	jra	L3601
2512  04bc               L7601:
2513                     ; 551 	if( l_Status & TX_OK )	//发送完成
2515  04bc 7b03          	ld	a,(OFST+0,sp)
2516  04be a520          	bcp	a,#32
2517  04c0 2705          	jreq	L1701
2518                     ; 553 		return TX_OK;
2520  04c2 a620          	ld	a,#32
2522  04c4               L431:
2524  04c4 5b05          	addw	sp,#5
2525  04c6 81            	ret
2526  04c7               L1701:
2527                     ; 556 	return 0xFF;	//其他原因发送失败
2529  04c7 a6ff          	ld	a,#255
2531  04c9 20f9          	jra	L431
2603                     ; 566 uint8_t NRF24L01_RxPacket( uint8_t *rxbuf )
2603                     ; 567 {
2604                     	switch	.text
2605  04cb               _NRF24L01_RxPacket:
2607  04cb 89            	pushw	x
2608  04cc 88            	push	a
2609       00000001      OFST:	set	1
2612                     ; 568 	uint8_t l_Status = 0, l_RxLength = 0, l_100MsTimes = 0;
2614  04cd 7b01          	ld	a,(OFST+0,sp)
2615  04cf 97            	ld	xl,a
2618  04d0 7b01          	ld	a,(OFST+0,sp)
2619  04d2 97            	ld	xl,a
2622  04d3 0f01          	clr	(OFST+0,sp)
2623                     ; 570 	RF24L01_SET_CS_LOW( );		//片选
2625  04d5 4b10          	push	#16
2626  04d7 ae5005        	ldw	x,#20485
2627  04da cd0000        	call	_GPIO_ResetBits
2629  04dd 84            	pop	a
2630                     ; 571 	drv_spi_read_write_byte( FLUSH_RX );
2632  04de a6e2          	ld	a,#226
2633  04e0 cd0000        	call	_drv_spi_read_write_byte
2635                     ; 572 	RF24L01_SET_CS_HIGH( );
2637  04e3 4b10          	push	#16
2638  04e5 ae5005        	ldw	x,#20485
2639  04e8 cd0000        	call	_GPIO_SetBits
2641  04eb 84            	pop	a
2643  04ec 204e          	jra	L7211
2644  04ee               L5211:
2645                     ; 576 		drv_delay_ms( 100 );
2647  04ee ae0064        	ldw	x,#100
2648  04f1 cd0000        	call	_drv_delay_ms
2650                     ; 578 		if( 30 == l_100MsTimes++ )		//3s没接收过数据，重新初始化模块
2652  04f4 7b01          	ld	a,(OFST+0,sp)
2653  04f6 0c01          	inc	(OFST+0,sp)
2654  04f8 a11e          	cp	a,#30
2655  04fa 2640          	jrne	L7211
2656                     ; 580 			NRF24L01_Gpio_Init( );
2658  04fc ad56          	call	_NRF24L01_Gpio_Init
2660                     ; 581 			RF24L01_Init( );
2662  04fe ad7d          	call	_RF24L01_Init
2664                     ; 582 			RF24L01_Set_Mode( MODE_RX );
2666  0500 a601          	ld	a,#1
2667  0502 cd03f9        	call	_RF24L01_Set_Mode
2669                     ; 583 			break;
2670  0505               L1311:
2671                     ; 587 	l_Status = NRF24L01_Read_Reg( STATUS );		//读状态寄存器
2673  0505 a607          	ld	a,#7
2674  0507 cd0000        	call	_NRF24L01_Read_Reg
2676  050a 6b01          	ld	(OFST+0,sp),a
2677                     ; 588 	NRF24L01_Write_Reg( STATUS,l_Status );		//清中断标志
2679  050c 7b01          	ld	a,(OFST+0,sp)
2680  050e 97            	ld	xl,a
2681  050f a607          	ld	a,#7
2682  0511 95            	ld	xh,a
2683  0512 cd005e        	call	_NRF24L01_Write_Reg
2685                     ; 589 	if( l_Status & RX_OK)	//接收到数据
2687  0515 7b01          	ld	a,(OFST+0,sp)
2688  0517 a540          	bcp	a,#64
2689  0519 2735          	jreq	L5311
2690                     ; 591 		l_RxLength = NRF24L01_Read_Reg( R_RX_PL_WID );		//读取接收到的数据个数
2692  051b a660          	ld	a,#96
2693  051d cd0000        	call	_NRF24L01_Read_Reg
2695  0520 6b01          	ld	(OFST+0,sp),a
2696                     ; 592 		NRF24L01_Read_Buf( RD_RX_PLOAD,rxbuf,l_RxLength );	//接收到数据 
2698  0522 7b01          	ld	a,(OFST+0,sp)
2699  0524 88            	push	a
2700  0525 1e03          	ldw	x,(OFST+2,sp)
2701  0527 89            	pushw	x
2702  0528 a661          	ld	a,#97
2703  052a cd0024        	call	_NRF24L01_Read_Buf
2705  052d 5b03          	addw	sp,#3
2706                     ; 593 		NRF24L01_Write_Reg( FLUSH_RX,0xff );				//清除RX FIFO
2708  052f ae00ff        	ldw	x,#255
2709  0532 a6e2          	ld	a,#226
2710  0534 95            	ld	xh,a
2711  0535 cd005e        	call	_NRF24L01_Write_Reg
2713                     ; 594 		return l_RxLength; 
2715  0538 7b01          	ld	a,(OFST+0,sp)
2717  053a 2015          	jra	L441
2718  053c               L7211:
2719                     ; 574 	while( 0 != RF24L01_GET_IRQ_STATUS( ))
2721  053c c6500b        	ld	a,20491
2722  053f a501          	bcp	a,#1
2723  0541 2603          	jrne	L041
2724  0543 5f            	clrw	x
2725  0544 2003          	jra	L241
2726  0546               L041:
2727  0546 ae0001        	ldw	x,#1
2728  0549               L241:
2729  0549 a30000        	cpw	x,#0
2730  054c 26a0          	jrne	L5211
2731  054e 20b5          	jra	L1311
2732  0550               L5311:
2733                     ; 597 	return 0;				//没有收到数据	
2735  0550 4f            	clr	a
2737  0551               L441:
2739  0551 5b03          	addw	sp,#3
2740  0553 81            	ret
2766                     ; 606 void NRF24L01_Gpio_Init( void )
2766                     ; 607 {
2767                     	switch	.text
2768  0554               _NRF24L01_Gpio_Init:
2772                     ; 609 	GPIO_Init( RF24L01_CE_GPIO_PORT, RF24L01_CE_GPIO_PIN, GPIO_Mode_Out_PP_High_Fast );
2774  0554 4bf0          	push	#240
2775  0556 4b08          	push	#8
2776  0558 ae5005        	ldw	x,#20485
2777  055b cd0000        	call	_GPIO_Init
2779  055e 85            	popw	x
2780                     ; 610 	GPIO_Init( RF24L01_IRQ_GPIO_PORT, RF24L01_IRQ_GPIO_PIN, GPIO_Mode_In_PU_No_IT );
2782  055f 4b40          	push	#64
2783  0561 4b01          	push	#1
2784  0563 ae500a        	ldw	x,#20490
2785  0566 cd0000        	call	_GPIO_Init
2787  0569 85            	popw	x
2788                     ; 612 	RF24L01_SET_CE_LOW( );		//使能设备
2790  056a 4b08          	push	#8
2791  056c ae5005        	ldw	x,#20485
2792  056f cd0000        	call	_GPIO_ResetBits
2794  0572 84            	pop	a
2795                     ; 613 	RF24L01_SET_CS_HIGH( );		//取消SPI片选
2797  0573 4b10          	push	#16
2798  0575 ae5005        	ldw	x,#20485
2799  0578 cd0000        	call	_GPIO_SetBits
2801  057b 84            	pop	a
2802                     ; 614 }
2805  057c 81            	ret
2808                     	switch	.const
2809  000a               L7411_addr:
2810  000a 34            	dc.b	52
2811  000b 43            	dc.b	67
2812  000c 10            	dc.b	16
2813  000d 10            	dc.b	16
2814  000e 01            	dc.b	1
2853                     ; 622 void RF24L01_Init( void )
2853                     ; 623 {
2854                     	switch	.text
2855  057d               _RF24L01_Init:
2857  057d 5205          	subw	sp,#5
2858       00000005      OFST:	set	5
2861                     ; 624     uint8_t addr[5] = {INIT_ADDR};
2863  057f 96            	ldw	x,sp
2864  0580 1c0001        	addw	x,#OFST-4
2865  0583 90ae000a      	ldw	y,#L7411_addr
2866  0587 a605          	ld	a,#5
2867  0589 cd0000        	call	c_xymvx
2869                     ; 626     RF24L01_SET_CE_HIGH( );
2871  058c 4b08          	push	#8
2872  058e ae5005        	ldw	x,#20485
2873  0591 cd0000        	call	_GPIO_SetBits
2875  0594 84            	pop	a
2876                     ; 627     NRF24L01_Clear_IRQ_Flag( IRQ_ALL );
2878  0595 a670          	ld	a,#112
2879  0597 cd0136        	call	_NRF24L01_Clear_IRQ_Flag
2881                     ; 630     NRF24L01_Write_Reg( DYNPD, ( 1 << 0 ) ); 	//使能通道1动态数据长度
2883  059a ae0001        	ldw	x,#1
2884  059d a61c          	ld	a,#28
2885  059f 95            	ld	xh,a
2886  05a0 cd005e        	call	_NRF24L01_Write_Reg
2888                     ; 631     NRF24L01_Write_Reg( FEATRUE, 0x07 );
2890  05a3 ae0007        	ldw	x,#7
2891  05a6 a61d          	ld	a,#29
2892  05a8 95            	ld	xh,a
2893  05a9 cd005e        	call	_NRF24L01_Write_Reg
2895                     ; 632     NRF24L01_Read_Reg( DYNPD );
2897  05ac a61c          	ld	a,#28
2898  05ae cd0000        	call	_NRF24L01_Read_Reg
2900                     ; 633     NRF24L01_Read_Reg( FEATRUE );
2902  05b1 a61d          	ld	a,#29
2903  05b3 cd0000        	call	_NRF24L01_Read_Reg
2905                     ; 641     NRF24L01_Write_Reg( CONFIG, /*( 1<<MASK_RX_DR ) |*/		//接收中断
2905                     ; 642                                       ( 1 << EN_CRC ) |     //使能CRC 1个字节
2905                     ; 643                                       ( 1 << PWR_UP ) );    //开启设备
2907  05b6 ae000a        	ldw	x,#10
2908  05b9 4f            	clr	a
2909  05ba 95            	ld	xh,a
2910  05bb cd005e        	call	_NRF24L01_Write_Reg
2912                     ; 644     NRF24L01_Write_Reg( EN_AA, ( 1 << ENAA_P0 ) );   		//通道0自动应答
2914  05be ae0001        	ldw	x,#1
2915  05c1 a601          	ld	a,#1
2916  05c3 95            	ld	xh,a
2917  05c4 cd005e        	call	_NRF24L01_Write_Reg
2919                     ; 645     NRF24L01_Write_Reg( EN_RXADDR, ( 1 << ERX_P0 ) );		//通道0接收
2921  05c7 ae0001        	ldw	x,#1
2922  05ca a602          	ld	a,#2
2923  05cc 95            	ld	xh,a
2924  05cd cd005e        	call	_NRF24L01_Write_Reg
2926                     ; 646     NRF24L01_Write_Reg( SETUP_AW, AW_5BYTES );     			//地址宽度 5个字节
2928  05d0 ae0003        	ldw	x,#3
2929  05d3 a603          	ld	a,#3
2930  05d5 95            	ld	xh,a
2931  05d6 cd005e        	call	_NRF24L01_Write_Reg
2933                     ; 647     NRF24L01_Write_Reg( SETUP_RETR, ARD_4000US |
2933                     ; 648                         ( REPEAT_CNT & 0x0F ) );         	//重复等待时间 250us
2935  05d9 ae00ff        	ldw	x,#255
2936  05dc a604          	ld	a,#4
2937  05de 95            	ld	xh,a
2938  05df cd005e        	call	_NRF24L01_Write_Reg
2940                     ; 649     NRF24L01_Write_Reg( RF_CH, 60 );             			//初始化通道
2942  05e2 ae003c        	ldw	x,#60
2943  05e5 a605          	ld	a,#5
2944  05e7 95            	ld	xh,a
2945  05e8 cd005e        	call	_NRF24L01_Write_Reg
2947                     ; 650     NRF24L01_Write_Reg( RF_SETUP, 0x26 );
2949  05eb ae0026        	ldw	x,#38
2950  05ee a606          	ld	a,#6
2951  05f0 95            	ld	xh,a
2952  05f1 cd005e        	call	_NRF24L01_Write_Reg
2954                     ; 652     NRF24L01_Set_TxAddr( &addr[0], 5 );                      //设置TX地址
2956  05f4 4b05          	push	#5
2957  05f6 96            	ldw	x,sp
2958  05f7 1c0002        	addw	x,#OFST-3
2959  05fa cd02a7        	call	_NRF24L01_Set_TxAddr
2961  05fd 84            	pop	a
2962                     ; 653     NRF24L01_Set_RxAddr( 0, &addr[0], 5 );                   //设置RX地址
2964  05fe 4b05          	push	#5
2965  0600 96            	ldw	x,sp
2966  0601 1c0002        	addw	x,#OFST-3
2967  0604 89            	pushw	x
2968  0605 4f            	clr	a
2969  0606 cd02c3        	call	_NRF24L01_Set_RxAddr
2971  0609 5b03          	addw	sp,#3
2972                     ; 654 }
2975  060b 5b05          	addw	sp,#5
2976  060d 81            	ret
3001                     	xdef	_g_ErrorString
3002                     	xdef	_RF24L01_Init
3003                     	xdef	_NRF24L01_Gpio_Init
3004                     	xdef	_NRF24L01_RxPacket
3005                     	xdef	_NRF24L01_TxPacket
3006                     	xdef	_NRF24L01_check
3007                     	xdef	_RF24L01_Set_Mode
3008                     	xdef	_RF24LL01_Write_Hopping_Point
3009                     	xdef	_NRF24L01_Set_Power
3010                     	xdef	_NRF24L01_Set_Speed
3011                     	xdef	_NRF24L01_Set_RxAddr
3012                     	xdef	_NRF24L01_Set_TxAddr
3013                     	xdef	_NRF24L01_Write_Tx_Payload_InAck
3014                     	xdef	_NRF24L01_Write_Tx_Payload_NoAck
3015                     	xdef	_NRF24L01_Write_Tx_Payload_Ack
3016                     	xdef	_NRF24L01_Read_Rx_Payload
3017                     	xdef	_NRF24L01_Read_Top_Fifo_Width
3018                     	xdef	_RF24L01_Read_IRQ_Status
3019                     	xdef	_NRF24L01_Clear_IRQ_Flag
3020                     	xdef	_NRF24L01_Read_Status_Register
3021                     	xdef	_NRF24L01_Nop
3022                     	xdef	_NRF24L01_Reuse_Tx_Payload
3023                     	xdef	_NRF24L01_Flush_Rx_Fifo
3024                     	xdef	_NRF24L01_Flush_Tx_Fifo
3025                     	xdef	_NRF24L01_Write_Buf
3026                     	xdef	_NRF24L01_Write_Reg
3027                     	xdef	_NRF24L01_Read_Buf
3028                     	xdef	_NRF24L01_Read_Reg
3029                     	xref	_drv_spi_read_write_byte
3030                     	xref	_drv_uart_tx_bytes
3031                     	xref	_drv_delay_ms
3032                     	xref	_GPIO_ResetBits
3033                     	xref	_GPIO_SetBits
3034                     	xref	_GPIO_Init
3035                     	switch	.const
3036  000f               L3:
3037  000f 524632344c30  	dc.b	"RF24L01 is not fin"
3038  0021 6420212e2e2e  	dc.b	"d !...",0
3058                     	xref	c_xymvx
3059                     	end
