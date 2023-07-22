   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  52                     ; 28 static void drv_delay_1ms( void )
  52                     ; 29 {
  54                     	switch	.text
  55  0000               L3_drv_delay_1ms:
  57  0000 5206          	subw	sp,#6
  58       00000006      OFST:	set	6
  61                     ; 30 	uint16_t Ms = 1;
  63  0002 ae0001        	ldw	x,#1
  64  0005 1f01          	ldw	(OFST-5,sp),x
  65                     ; 31 	uint32_t j = 30;
  67  0007 ae001e        	ldw	x,#30
  68  000a 1f05          	ldw	(OFST-1,sp),x
  69  000c ae0000        	ldw	x,#0
  70  000f 1f03          	ldw	(OFST-3,sp),x
  72  0011 2015          	jra	L14
  73  0013               L74:
  74                     ; 35 		while( j-- );
  76  0013 96            	ldw	x,sp
  77  0014 1c0003        	addw	x,#OFST-3
  78  0017 cd0000        	call	c_ltor
  80  001a 96            	ldw	x,sp
  81  001b 1c0003        	addw	x,#OFST-3
  82  001e a601          	ld	a,#1
  83  0020 cd0000        	call	c_lgsbc
  85  0023 cd0000        	call	c_lrzmp
  87  0026 26eb          	jrne	L74
  88  0028               L14:
  89                     ; 33 	while( Ms-- )
  91  0028 1e01          	ldw	x,(OFST-5,sp)
  92  002a 1d0001        	subw	x,#1
  93  002d 1f01          	ldw	(OFST-5,sp),x
  94  002f 1c0001        	addw	x,#1
  95  0032 a30000        	cpw	x,#0
  96  0035 26dc          	jrne	L74
  97                     ; 37 }
 100  0037 5b06          	addw	sp,#6
 101  0039 81            	ret
 136                     ; 46 void drv_delay_ms( uint16_t Ms )
 136                     ; 47 {
 137                     	switch	.text
 138  003a               _drv_delay_ms:
 140  003a 89            	pushw	x
 141       00000000      OFST:	set	0
 144  003b 2002          	jra	L37
 145  003d               L17:
 146                     ; 50 		drv_delay_1ms( );
 148  003d adc1          	call	L3_drv_delay_1ms
 150  003f               L37:
 151                     ; 48 	while( Ms-- )
 153  003f 1e01          	ldw	x,(OFST+1,sp)
 154  0041 1d0001        	subw	x,#1
 155  0044 1f01          	ldw	(OFST+1,sp),x
 156  0046 1c0001        	addw	x,#1
 157  0049 a30000        	cpw	x,#0
 158  004c 26ef          	jrne	L17
 159                     ; 52 }
 162  004e 85            	popw	x
 163  004f 81            	ret
 176                     	xdef	_drv_delay_ms
 195                     	xref	c_lrzmp
 196                     	xref	c_lgsbc
 197                     	xref	c_ltor
 198                     	end
