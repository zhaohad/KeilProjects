   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  33                     ; 28 void drv_led_init( void )
  33                     ; 29 {
  35                     	switch	.text
  36  0000               _drv_led_init:
  40                     ; 31 	GPIO_Init( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast );
  42  0000 4be0          	push	#224
  43  0002 4b04          	push	#4
  44  0004 ae5000        	ldw	x,#20480
  45  0007 cd0000        	call	_GPIO_Init
  47  000a 85            	popw	x
  48                     ; 32 	GPIO_Init( LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN, GPIO_Mode_Out_PP_Low_Fast );	
  50  000b 4be0          	push	#224
  51  000d 4b08          	push	#8
  52  000f ae5000        	ldw	x,#20480
  53  0012 cd0000        	call	_GPIO_Init
  55  0015 85            	popw	x
  56                     ; 33 }
  59  0016 81            	ret
 115                     ; 42 void drv_led_on( LedPortType LedPort )
 115                     ; 43 {
 116                     	switch	.text
 117  0017               _drv_led_on:
 121                     ; 44 	if( LED_RED == LedPort )	//LED_RED
 123  0017 4d            	tnz	a
 124  0018 260b          	jrne	L74
 125                     ; 46 		GPIO_SetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );
 127  001a 4b04          	push	#4
 128  001c ae5000        	ldw	x,#20480
 129  001f cd0000        	call	_GPIO_SetBits
 131  0022 84            	pop	a
 133  0023 2009          	jra	L15
 134  0025               L74:
 135                     ; 50 		GPIO_SetBits( LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN );
 137  0025 4b08          	push	#8
 138  0027 ae5000        	ldw	x,#20480
 139  002a cd0000        	call	_GPIO_SetBits
 141  002d 84            	pop	a
 142  002e               L15:
 143                     ; 53 }
 146  002e 81            	ret
 182                     ; 62 void drv_led_off( LedPortType LedPort )
 182                     ; 63 {
 183                     	switch	.text
 184  002f               _drv_led_off:
 188                     ; 64 	if( LED_RED == LedPort )	//LED_RED
 190  002f 4d            	tnz	a
 191  0030 260b          	jrne	L17
 192                     ; 66 		GPIO_ResetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );	
 194  0032 4b04          	push	#4
 195  0034 ae5000        	ldw	x,#20480
 196  0037 cd0000        	call	_GPIO_ResetBits
 198  003a 84            	pop	a
 200  003b 2009          	jra	L37
 201  003d               L17:
 202                     ; 70 		GPIO_ResetBits( LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN );
 204  003d 4b08          	push	#8
 205  003f ae5000        	ldw	x,#20480
 206  0042 cd0000        	call	_GPIO_ResetBits
 208  0045 84            	pop	a
 209  0046               L37:
 210                     ; 73 }
 213  0046 81            	ret
 249                     ; 82 void drv_led_flashing( LedPortType LedPort )
 249                     ; 83 {
 250                     	switch	.text
 251  0047               _drv_led_flashing:
 255                     ; 85 	if( LED_RED == LedPort )
 257  0047 4d            	tnz	a
 258  0048 260b          	jrne	L311
 259                     ; 87 		GPIO_ToggleBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );
 261  004a 4b04          	push	#4
 262  004c ae5000        	ldw	x,#20480
 263  004f cd0000        	call	_GPIO_ToggleBits
 265  0052 84            	pop	a
 267  0053 2009          	jra	L511
 268  0055               L311:
 269                     ; 91 		GPIO_ToggleBits( LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN );
 271  0055 4b08          	push	#8
 272  0057 ae5000        	ldw	x,#20480
 273  005a cd0000        	call	_GPIO_ToggleBits
 275  005d 84            	pop	a
 276  005e               L511:
 277                     ; 93 }
 280  005e 81            	ret
 293                     	xdef	_drv_led_flashing
 294                     	xdef	_drv_led_off
 295                     	xdef	_drv_led_on
 296                     	xdef	_drv_led_init
 297                     	xref	_GPIO_ToggleBits
 298                     	xref	_GPIO_ResetBits
 299                     	xref	_GPIO_SetBits
 300                     	xref	_GPIO_Init
 319                     	end
