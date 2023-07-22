   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
   4                     .const:	section	.text
   5  0000               _HSIDivFactor:
   6  0000 01            	dc.b	1
   7  0001 02            	dc.b	2
   8  0002 04            	dc.b	4
   9  0003 08            	dc.b	8
  38                     ; 68 void CLK_DeInit(void)
  38                     ; 69 {
  40                     	switch	.text
  41  0000               _CLK_DeInit:
  45                     ; 70   CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
  47  0000 350350c0      	mov	20672,#3
  48                     ; 71   CLK->PCKENR = CLK_PCKENR_RESET_VALUE;
  50  0004 725f50c3      	clr	20675
  51                     ; 72   CLK->CCOR  = CLK_CCOR_RESET_VALUE;
  53  0008 725f50c5      	clr	20677
  54                     ; 73 }
  57  000c 81            	ret
 112                     ; 80 void CLK_CCOCmd(FunctionalState NewState)
 112                     ; 81 {
 113                     	switch	.text
 114  000d               _CLK_CCOCmd:
 118                     ; 83   assert_param(IS_FUNCTIONAL_STATE(NewState));
 120                     ; 85   if (NewState != DISABLE)
 122  000d 4d            	tnz	a
 123  000e 2706          	jreq	L74
 124                     ; 88     CLK->CCOR |= CLK_CCOR_CCOEN;
 126  0010 721050c5      	bset	20677,#0
 128  0014 2004          	jra	L15
 129  0016               L74:
 130                     ; 93     CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOEN);
 132  0016 721150c5      	bres	20677,#0
 133  001a               L15:
 134                     ; 96 }
 137  001a 81            	ret
 242                     ; 113 void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
 242                     ; 114 {
 243                     	switch	.text
 244  001b               _CLK_PeripheralClockConfig:
 246  001b 89            	pushw	x
 247       00000000      OFST:	set	0
 250                     ; 116     assert_param(IS_FUNCTIONAL_STATE(NewState));
 252                     ; 117     assert_param(IS_CLK_PERIPHERAL(CLK_Peripheral));
 254                     ; 119     if (NewState != DISABLE)
 256  001c 9f            	ld	a,xl
 257  001d 4d            	tnz	a
 258  001e 2709          	jreq	L711
 259                     ; 122       CLK->PCKENR |= ((uint8_t)CLK_Peripheral);
 261  0020 9e            	ld	a,xh
 262  0021 ca50c3        	or	a,20675
 263  0024 c750c3        	ld	20675,a
 265  0027 2009          	jra	L121
 266  0029               L711:
 267                     ; 127       CLK->PCKENR &= (uint8_t)(~(uint8_t)CLK_Peripheral);
 269  0029 7b01          	ld	a,(OFST+1,sp)
 270  002b 43            	cpl	a
 271  002c c450c3        	and	a,20675
 272  002f c750c3        	ld	20675,a
 273  0032               L121:
 274                     ; 129 }
 277  0032 85            	popw	x
 278  0033 81            	ret
 353                     ; 141 void CLK_MasterPrescalerConfig(CLK_MasterPrescaler_TypeDef CLK_MasterPrescaler)
 353                     ; 142 {
 354                     	switch	.text
 355  0034               _CLK_MasterPrescalerConfig:
 357  0034 88            	push	a
 358       00000000      OFST:	set	0
 361                     ; 144   assert_param(IS_CLK_MASTER_PRESCALER(CLK_MasterPrescaler));
 363                     ; 146   CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
 365  0035 c650c0        	ld	a,20672
 366  0038 a4fc          	and	a,#252
 367  003a c750c0        	ld	20672,a
 368                     ; 147   CLK->CKDIVR = (uint8_t)CLK_MasterPrescaler;
 370  003d 7b01          	ld	a,(OFST+1,sp)
 371  003f c750c0        	ld	20672,a
 372                     ; 148 }
 375  0042 84            	pop	a
 376  0043 81            	ret
 449                     ; 161 void CLK_CCOConfig(CLK_Output_TypeDef CLK_Output)
 449                     ; 162 {
 450                     	switch	.text
 451  0044               _CLK_CCOConfig:
 453  0044 88            	push	a
 454       00000000      OFST:	set	0
 457                     ; 164   assert_param(IS_CLK_OUTPUT(CLK_Output));
 459                     ; 167   CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOSEL);
 461  0045 c650c5        	ld	a,20677
 462  0048 a4f9          	and	a,#249
 463  004a c750c5        	ld	20677,a
 464                     ; 170   CLK->CCOR |= ((uint8_t)CLK_Output);
 466  004d c650c5        	ld	a,20677
 467  0050 1a01          	or	a,(OFST+1,sp)
 468  0052 c750c5        	ld	20677,a
 469                     ; 173   CLK->CCOR |= CLK_CCOR_CCOEN;
 471  0055 721050c5      	bset	20677,#0
 472                     ; 174 }
 475  0059 84            	pop	a
 476  005a 81            	ret
 529                     ; 181 uint32_t CLK_GetClockFreq(void)
 529                     ; 182 {
 530                     	switch	.text
 531  005b               _CLK_GetClockFreq:
 533  005b 5209          	subw	sp,#9
 534       00000009      OFST:	set	9
 537                     ; 183   uint32_t clockfrequency = 0;
 539  005d 96            	ldw	x,sp
 540  005e 1c0005        	addw	x,#OFST-4
 541  0061 cd0000        	call	c_ltor
 543                     ; 184   uint8_t tmp = 0, presc = 0;
 545  0064 7b09          	ld	a,(OFST+0,sp)
 546  0066 97            	ld	xl,a
 549  0067 7b09          	ld	a,(OFST+0,sp)
 550  0069 97            	ld	xl,a
 551                     ; 186   tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
 553  006a c650c0        	ld	a,20672
 554  006d a403          	and	a,#3
 555  006f 6b09          	ld	(OFST+0,sp),a
 556                     ; 187   presc = HSIDivFactor[tmp];
 558  0071 7b09          	ld	a,(OFST+0,sp)
 559  0073 5f            	clrw	x
 560  0074 97            	ld	xl,a
 561  0075 d60000        	ld	a,(_HSIDivFactor,x)
 562  0078 6b09          	ld	(OFST+0,sp),a
 563                     ; 188   clockfrequency = HSI_VALUE / presc;
 565  007a 7b09          	ld	a,(OFST+0,sp)
 566  007c b703          	ld	c_lreg+3,a
 567  007e 3f02          	clr	c_lreg+2
 568  0080 3f01          	clr	c_lreg+1
 569  0082 3f00          	clr	c_lreg
 570  0084 96            	ldw	x,sp
 571  0085 1c0001        	addw	x,#OFST-8
 572  0088 cd0000        	call	c_rtol
 574  008b ae2400        	ldw	x,#9216
 575  008e bf02          	ldw	c_lreg+2,x
 576  0090 ae00f4        	ldw	x,#244
 577  0093 bf00          	ldw	c_lreg,x
 578  0095 96            	ldw	x,sp
 579  0096 1c0001        	addw	x,#OFST-8
 580  0099 cd0000        	call	c_ludv
 582  009c 96            	ldw	x,sp
 583  009d 1c0005        	addw	x,#OFST-4
 584  00a0 cd0000        	call	c_rtol
 586                     ; 190   return((uint32_t)clockfrequency);
 588  00a3 96            	ldw	x,sp
 589  00a4 1c0005        	addw	x,#OFST-4
 590  00a7 cd0000        	call	c_ltor
 594  00aa 5b09          	addw	sp,#9
 595  00ac 81            	ret
 620                     	xdef	_HSIDivFactor
 621                     	xdef	_CLK_GetClockFreq
 622                     	xdef	_CLK_CCOConfig
 623                     	xdef	_CLK_MasterPrescalerConfig
 624                     	xdef	_CLK_PeripheralClockConfig
 625                     	xdef	_CLK_CCOCmd
 626                     	xdef	_CLK_DeInit
 627                     	xref.b	c_lreg
 646                     	xref	c_ludv
 647                     	xref	c_rtol
 648                     	xref	c_ltor
 649                     	end
