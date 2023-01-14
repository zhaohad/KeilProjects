   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
   4                     	bsct
   5  0000               _g_Ashining:
   6  0000 0000          	dc.w	L3
   7  0002               _g_TxMode:
   8  0002 00            	dc.b	0
   9  0003               _g_UartRxFlag:
  10  0003 00            	dc.b	0
  11  0004               _g_UartRxBuffer:
  12  0004 00            	dc.b	0
  13  0005 000000000000  	ds.b	99
  14  0068               _g_RF24L01RxBuffer:
  15  0068 01            	dc.b	1
  16  0069 02            	dc.b	2
  17  006a 03            	dc.b	3
  18  006b 04            	dc.b	4
  19  006c 05            	dc.b	5
  20  006d 06            	dc.b	6
  21  006e 07            	dc.b	7
  22  006f 08            	dc.b	8
  23  0070 09            	dc.b	9
  24  0071 000000000000  	ds.b	23
  81                     ; 34 void main( void )
  81                     ; 35 {
  83                     	switch	.text
  84  0000               _main:
  86  0000 88            	push	a
  87       00000001      OFST:	set	1
  90                     ; 36 	uint8_t i = 0;
  92  0001 0f01          	clr	(OFST+0,sp)
  93                     ; 39 	drv_uart_init( 9600 );
  95  0003 ae2580        	ldw	x,#9600
  96  0006 89            	pushw	x
  97  0007 ae0000        	ldw	x,#0
  98  000a 89            	pushw	x
  99  000b cd0000        	call	_drv_uart_init
 101  000e 5b04          	addw	sp,#4
 102                     ; 42 	drv_led_init( );
 104  0010 cd0000        	call	_drv_led_init
 106                     ; 45 	drv_spi_init( );
 108  0013 cd0000        	call	_drv_spi_init
 110                     ; 48 	NRF24L01_Gpio_Init( );
 112  0016 cd0000        	call	_NRF24L01_Gpio_Init
 114                     ; 49 	NRF24L01_check( );
 116  0019 cd0000        	call	_NRF24L01_check
 118                     ; 50 	RF24L01_Init( );
 120  001c cd0000        	call	_RF24L01_Init
 122                     ; 52 	led_red_off( );
 124  001f 4f            	clr	a
 125  0020 cd0000        	call	_drv_led_off
 127                     ; 53 	led_green_off( );
 129  0023 a601          	ld	a,#1
 130  0025 cd0000        	call	_drv_led_off
 132                     ; 54 	for( i = 0; i < 6; i++ )
 134  0028 0f01          	clr	(OFST+0,sp)
 135  002a               L13:
 136                     ; 56 		led_red_flashing( );
 138  002a 4f            	clr	a
 139  002b cd0000        	call	_drv_led_flashing
 141                     ; 57 		led_green_flashing( );
 143  002e a601          	ld	a,#1
 144  0030 cd0000        	call	_drv_led_flashing
 146                     ; 58 		drv_delay_ms( 500 );
 148  0033 ae01f4        	ldw	x,#500
 149  0036 cd0000        	call	_drv_delay_ms
 151                     ; 54 	for( i = 0; i < 6; i++ )
 153  0039 0c01          	inc	(OFST+0,sp)
 156  003b 7b01          	ld	a,(OFST+0,sp)
 157  003d a106          	cp	a,#6
 158  003f 25e9          	jrult	L13
 159                     ; 69 	drv_button_init( );
 161  0041 cd0000        	call	_drv_button_init
 163                     ; 71 	RF24L01_Set_Mode( MODE_TX );		//发送模式
 165  0044 4f            	clr	a
 166  0045 cd0000        	call	_RF24L01_Set_Mode
 168  0048               L73:
 169                     ; 76 		if( BUTOTN_PRESS_DOWN == drv_button_check( ))
 171  0048 cd0000        	call	_drv_button_check
 173  004b a101          	cp	a,#1
 174  004d 263e          	jrne	L34
 175                     ; 78 			g_TxMode = 1 - g_TxMode;		//模式会在 TX_MODE_1( 0 ),TX_MODE_2( 1 )之间切换
 177  004f a601          	ld	a,#1
 178  0051 b002          	sub	a,_g_TxMode
 179  0053 b702          	ld	_g_TxMode,a
 180                     ; 81 			led_green_off( );
 182  0055 a601          	ld	a,#1
 183  0057 cd0000        	call	_drv_led_off
 185                     ; 82 			led_red_off( );
 187  005a 4f            	clr	a
 188  005b cd0000        	call	_drv_led_off
 190                     ; 84 			if( TX_MODE_1 == g_TxMode )
 192  005e 3d02          	tnz	_g_TxMode
 193  0060 2616          	jrne	L54
 194                     ; 86 				for( i = 0; i < 6; i++ )		
 196  0062 0f01          	clr	(OFST+0,sp)
 197  0064               L74:
 198                     ; 88 					led_red_flashing( );	//固定发送模式，红灯闪烁3次
 200  0064 4f            	clr	a
 201  0065 cd0000        	call	_drv_led_flashing
 203                     ; 89 					drv_delay_ms( 500 );		
 205  0068 ae01f4        	ldw	x,#500
 206  006b cd0000        	call	_drv_delay_ms
 208                     ; 86 				for( i = 0; i < 6; i++ )		
 210  006e 0c01          	inc	(OFST+0,sp)
 213  0070 7b01          	ld	a,(OFST+0,sp)
 214  0072 a106          	cp	a,#6
 215  0074 25ee          	jrult	L74
 217  0076 2015          	jra	L34
 218  0078               L54:
 219                     ; 94 				for( i = 0; i < 6; i++ )
 221  0078 0f01          	clr	(OFST+0,sp)
 222  007a               L75:
 223                     ; 96 					led_green_flashing( );	//串口发送模式，绿灯闪烁3次
 225  007a a601          	ld	a,#1
 226  007c cd0000        	call	_drv_led_flashing
 228                     ; 97 					drv_delay_ms( 500 );
 230  007f ae01f4        	ldw	x,#500
 231  0082 cd0000        	call	_drv_delay_ms
 233                     ; 94 				for( i = 0; i < 6; i++ )
 235  0085 0c01          	inc	(OFST+0,sp)
 238  0087 7b01          	ld	a,(OFST+0,sp)
 239  0089 a106          	cp	a,#6
 240  008b 25ed          	jrult	L75
 241  008d               L34:
 242                     ; 103 		if( TX_MODE_1 == g_TxMode )
 244  008d 3d02          	tnz	_g_TxMode
 245  008f 2614          	jrne	L56
 246                     ; 105 			NRF24L01_TxPacket( (uint8_t *)g_Ashining, 8 );		//模式1发送固定字符,1S一包
 248  0091 4b08          	push	#8
 249  0093 be00          	ldw	x,_g_Ashining
 250  0095 cd0000        	call	_NRF24L01_TxPacket
 252  0098 84            	pop	a
 253                     ; 106 			drv_delay_ms( 1000 );		
 255  0099 ae03e8        	ldw	x,#1000
 256  009c cd0000        	call	_drv_delay_ms
 258                     ; 107 			led_red_flashing( );			
 260  009f 4f            	clr	a
 261  00a0 cd0000        	call	_drv_led_flashing
 264  00a3 20a3          	jra	L73
 265  00a5               L56:
 266                     ; 112 			i = drv_uart_rx_bytes( g_UartRxBuffer );
 268  00a5 ae0004        	ldw	x,#_g_UartRxBuffer
 269  00a8 cd0000        	call	_drv_uart_rx_bytes
 271  00ab 6b01          	ld	(OFST+0,sp),a
 272                     ; 114 			if( 0 != i )
 274  00ad 0d01          	tnz	(OFST+0,sp)
 275  00af 2797          	jreq	L73
 276                     ; 116 				NRF24L01_TxPacket( g_UartRxBuffer, i );
 278  00b1 7b01          	ld	a,(OFST+0,sp)
 279  00b3 88            	push	a
 280  00b4 ae0004        	ldw	x,#_g_UartRxBuffer
 281  00b7 cd0000        	call	_NRF24L01_TxPacket
 283  00ba 84            	pop	a
 284                     ; 117 				led_red_flashing( );
 286  00bb 4f            	clr	a
 287  00bc cd0000        	call	_drv_led_flashing
 289  00bf 2087          	jra	L73
 352                     	xdef	_main
 353                     	xdef	_g_RF24L01RxBuffer
 354                     	xdef	_g_UartRxBuffer
 355                     	xdef	_g_UartRxFlag
 356                     	xdef	_g_TxMode
 357                     	xdef	_g_Ashining
 358                     	xref	_RF24L01_Init
 359                     	xref	_NRF24L01_Gpio_Init
 360                     	xref	_NRF24L01_TxPacket
 361                     	xref	_NRF24L01_check
 362                     	xref	_RF24L01_Set_Mode
 363                     	xref	_drv_uart_rx_bytes
 364                     	xref	_drv_uart_init
 365                     	xref	_drv_spi_init
 366                     	xref	_drv_led_flashing
 367                     	xref	_drv_led_off
 368                     	xref	_drv_led_init
 369                     	xref	_drv_delay_ms
 370                     	xref	_drv_button_check
 371                     	xref	_drv_button_init
 372                     .const:	section	.text
 373  0000               L3:
 374  0000 676973656d69  	dc.b	"gisemi",0
 394                     	end
