   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  33                     ; 28 void drv_button_init( void )
  33                     ; 29 {
  35                     	switch	.text
  36  0000               _drv_button_init:
  40                     ; 31 	GPIO_Init( BUTOTN_GPIO_PORT, BUTTON_GPIO_PIN, GPIO_Mode_In_PU_No_IT );
  42  0000 4b40          	push	#64
  43  0002 4b02          	push	#2
  44  0004 ae500a        	ldw	x,#20490
  45  0007 cd0000        	call	_GPIO_Init
  47  000a 85            	popw	x
  48                     ; 32 }
  51  000b 81            	ret
  76                     ; 42 uint8_t drv_button_check( void )
  76                     ; 43 {
  77                     	switch	.text
  78  000c               _drv_button_check:
  82                     ; 45 	if( BUTTON_GPIO_PIN != ( GPIO_ReadInputData( BUTOTN_GPIO_PORT ) & BUTTON_GPIO_PIN ))	
  84  000c ae500a        	ldw	x,#20490
  85  000f cd0000        	call	_GPIO_ReadInputData
  87  0012 a402          	and	a,#2
  88  0014 a102          	cp	a,#2
  89  0016 2715          	jreq	L13
  90                     ; 47 		drv_delay_ms( 40 );			//æ¶ˆæŠ–
  92  0018 ae0028        	ldw	x,#40
  93  001b cd0000        	call	_drv_delay_ms
  95                     ; 48 		if( BUTTON_GPIO_PIN != ( GPIO_ReadInputData( BUTOTN_GPIO_PORT ) & BUTTON_GPIO_PIN ))
  97  001e ae500a        	ldw	x,#20490
  98  0021 cd0000        	call	_GPIO_ReadInputData
 100  0024 a402          	and	a,#2
 101  0026 a102          	cp	a,#2
 102  0028 2703          	jreq	L13
 103                     ; 50 			return 1;				//°´¼ü°´ÏÂ
 105  002a a601          	ld	a,#1
 108  002c 81            	ret
 109  002d               L13:
 110                     ; 54 	return 0;
 112  002d 4f            	clr	a
 115  002e 81            	ret
 128                     	xref	_drv_delay_ms
 129                     	xdef	_drv_button_check
 130                     	xdef	_drv_button_init
 131                     	xref	_GPIO_ReadInputData
 132                     	xref	_GPIO_Init
 151                     	end
