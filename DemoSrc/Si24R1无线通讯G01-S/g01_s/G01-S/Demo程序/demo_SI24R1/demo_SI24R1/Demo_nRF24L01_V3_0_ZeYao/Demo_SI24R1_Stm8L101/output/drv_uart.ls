   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  48                     ; 27 void drv_uart_init( uint32_t UartBaudRate )
  48                     ; 28 {
  50                     	switch	.text
  51  0000               _drv_uart_init:
  53       00000000      OFST:	set	0
  56                     ; 30 	GPIO_Init( UART_TX_GPIO_PORT, UART_TX_GPIO_PIN,GPIO_Mode_Out_PP_High_Slow  );
  58  0000 4bd0          	push	#208
  59  0002 4b08          	push	#8
  60  0004 ae500a        	ldw	x,#20490
  61  0007 cd0000        	call	_GPIO_Init
  63  000a 85            	popw	x
  64                     ; 31 	GPIO_Init( UART_RX_GPIO_PORT, UART_RX_GPIO_PIN,GPIO_Mode_In_PU_No_IT );
  66  000b 4b40          	push	#64
  67  000d 4b04          	push	#4
  68  000f ae500a        	ldw	x,#20490
  69  0012 cd0000        	call	_GPIO_Init
  71  0015 85            	popw	x
  72                     ; 34 	CLK_PeripheralClockConfig( CLK_Peripheral_USART, ENABLE);	//使能串口时钟
  74  0016 ae0001        	ldw	x,#1
  75  0019 a620          	ld	a,#32
  76  001b 95            	ld	xh,a
  77  001c cd0000        	call	_CLK_PeripheralClockConfig
  79                     ; 35 	USART_DeInit();		//串口复位
  81  001f cd0000        	call	_USART_DeInit
  83                     ; 37 	USART_Init( UartBaudRate, USART_WordLength_8D, USART_StopBits_1, USART_Parity_No, USART_Mode_Tx | USART_Mode_Rx );
  85  0022 4b0c          	push	#12
  86  0024 4b00          	push	#0
  87  0026 4b00          	push	#0
  88  0028 4b00          	push	#0
  89  002a 1e09          	ldw	x,(OFST+9,sp)
  90  002c 89            	pushw	x
  91  002d 1e09          	ldw	x,(OFST+9,sp)
  92  002f 89            	pushw	x
  93  0030 cd0000        	call	_USART_Init
  95  0033 5b08          	addw	sp,#8
  96                     ; 38 	USART_Cmd(ENABLE);	//使能串口
  98  0035 a601          	ld	a,#1
  99  0037 cd0000        	call	_USART_Cmd
 101                     ; 39 }
 104  003a 81            	ret
 150                     ; 49 void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length )
 150                     ; 50 {
 151                     	switch	.text
 152  003b               _drv_uart_tx_bytes:
 154  003b 89            	pushw	x
 155       00000000      OFST:	set	0
 158  003c 2016          	jra	L35
 159  003e               L16:
 160                     ; 53 		while( RESET == USART_GetFlagStatus( USART_FLAG_TXE ));
 162  003e ae0080        	ldw	x,#128
 163  0041 cd0000        	call	_USART_GetFlagStatus
 165  0044 4d            	tnz	a
 166  0045 27f7          	jreq	L16
 167                     ; 54 		USART_SendData8( * TxBuffer );
 169  0047 1e01          	ldw	x,(OFST+1,sp)
 170  0049 f6            	ld	a,(x)
 171  004a cd0000        	call	_USART_SendData8
 173                     ; 55 		TxBuffer++;
 175  004d 1e01          	ldw	x,(OFST+1,sp)
 176  004f 1c0001        	addw	x,#1
 177  0052 1f01          	ldw	(OFST+1,sp),x
 178  0054               L35:
 179                     ; 51 	while( Length-- )
 181  0054 7b05          	ld	a,(OFST+5,sp)
 182  0056 0a05          	dec	(OFST+5,sp)
 183  0058 4d            	tnz	a
 184  0059 26e3          	jrne	L16
 185                     ; 57 }
 188  005b 85            	popw	x
 189  005c 81            	ret
 244                     ; 66 uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer )
 244                     ; 67 {
 245                     	switch	.text
 246  005d               _drv_uart_rx_bytes:
 248  005d 89            	pushw	x
 249  005e 5203          	subw	sp,#3
 250       00000003      OFST:	set	3
 253                     ; 68 	uint8_t l_RxLength = 0;
 255  0060 0f03          	clr	(OFST+0,sp)
 256                     ; 69 	uint16_t l_UartRxTimOut = 0xFFF;
 258  0062 ae0fff        	ldw	x,#4095
 259  0065 1f01          	ldw	(OFST-2,sp),x
 261  0067 2028          	jra	L711
 262  0069               L311:
 263                     ; 73 		if( RESET != USART_GetFlagStatus( USART_FLAG_RXNE ))
 265  0069 ae0020        	ldw	x,#32
 266  006c cd0000        	call	_USART_GetFlagStatus
 268  006f 4d            	tnz	a
 269  0070 2714          	jreq	L321
 270                     ; 75 			*RxBuffer = USART_ReceiveData8( );
 272  0072 cd0000        	call	_USART_ReceiveData8
 274  0075 1e04          	ldw	x,(OFST+1,sp)
 275  0077 f7            	ld	(x),a
 276                     ; 76 			RxBuffer++;
 278  0078 1e04          	ldw	x,(OFST+1,sp)
 279  007a 1c0001        	addw	x,#1
 280  007d 1f04          	ldw	(OFST+1,sp),x
 281                     ; 77 			l_RxLength++;
 283  007f 0c03          	inc	(OFST+0,sp)
 284                     ; 78 			l_UartRxTimOut = 0xFFF;		//恢复超时等待时间
 286  0081 ae0fff        	ldw	x,#4095
 287  0084 1f01          	ldw	(OFST-2,sp),x
 288  0086               L321:
 289                     ; 80 		if( 100 == l_RxLength )
 291  0086 7b03          	ld	a,(OFST+0,sp)
 292  0088 a164          	cp	a,#100
 293  008a 2605          	jrne	L711
 294                     ; 82 			break;						//字节不能超过100个字节，由于部分8位机内存较小，接收buffer开得较小
 295  008c               L121:
 296                     ; 86 	return l_RxLength;					//返回接收到的字节个数
 298  008c 7b03          	ld	a,(OFST+0,sp)
 301  008e 5b05          	addw	sp,#5
 302  0090 81            	ret
 303  0091               L711:
 304                     ; 71 	while( l_UartRxTimOut-- )			//在超时范围内查询数据
 306  0091 1e01          	ldw	x,(OFST-2,sp)
 307  0093 1d0001        	subw	x,#1
 308  0096 1f01          	ldw	(OFST-2,sp),x
 309  0098 1c0001        	addw	x,#1
 310  009b a30000        	cpw	x,#0
 311  009e 26c9          	jrne	L311
 312  00a0 20ea          	jra	L121
 325                     	xdef	_drv_uart_rx_bytes
 326                     	xdef	_drv_uart_tx_bytes
 327                     	xdef	_drv_uart_init
 328                     	xref	_CLK_PeripheralClockConfig
 329                     	xref	_USART_GetFlagStatus
 330                     	xref	_USART_SendData8
 331                     	xref	_USART_ReceiveData8
 332                     	xref	_USART_Cmd
 333                     	xref	_USART_Init
 334                     	xref	_USART_DeInit
 335                     	xref	_GPIO_Init
 354                     	end
