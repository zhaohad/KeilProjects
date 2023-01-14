   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  32                     ; 59 void USART_DeInit(void)
  32                     ; 60 {
  34                     	switch	.text
  35  0000               _USART_DeInit:
  39                     ; 63   (void)USART->SR;
  41  0000 c65230        	ld	a,21040
  42  0003 97            	ld	xl,a
  43                     ; 64   (void)USART->DR;
  45  0004 c65231        	ld	a,21041
  46  0007 97            	ld	xl,a
  47                     ; 66   USART->BRR2 = USART_BRR2_RESET_VALUE;  /* Set USART_BRR2 to reset value 0x00 */
  49  0008 725f5233      	clr	21043
  50                     ; 67   USART->BRR1 = USART_BRR1_RESET_VALUE;  /* Set USART_BRR1 to reset value 0x00 */
  52  000c 725f5232      	clr	21042
  53                     ; 69   USART->CR1 = USART_CR1_RESET_VALUE;  /* Set USART_CR1 to reset value 0x00 */
  55  0010 725f5234      	clr	21044
  56                     ; 70   USART->CR2 = USART_CR2_RESET_VALUE;  /* Set USART_CR2 to reset value 0x00 */
  58  0014 725f5235      	clr	21045
  59                     ; 71   USART->CR3 = USART_CR3_RESET_VALUE;  /* Set USART_CR3 to reset value 0x00 */
  61  0018 725f5236      	clr	21046
  62                     ; 72   USART->CR4 = USART_CR4_RESET_VALUE;  /* Set USART_CR4 to reset value 0x00 */
  64  001c 725f5237      	clr	21047
  65                     ; 73 }
  68  0020 81            	ret
 241                     ; 100 void USART_Init(uint32_t BaudRate, USART_WordLength_TypeDef USART_WordLength,
 241                     ; 101                 USART_StopBits_TypeDef USART_StopBits, USART_Parity_TypeDef
 241                     ; 102                 USART_Parity, USART_Mode_TypeDef USART_Mode)
 241                     ; 103 {
 242                     	switch	.text
 243  0021               _USART_Init:
 245  0021 5204          	subw	sp,#4
 246       00000004      OFST:	set	4
 249                     ; 104   uint32_t BaudRate_Mantissa = 0;
 251  0023 ae0000        	ldw	x,#0
 252  0026 1f03          	ldw	(OFST-1,sp),x
 253  0028 ae0000        	ldw	x,#0
 254  002b 1f01          	ldw	(OFST-3,sp),x
 255                     ; 107   assert_param(IS_USART_BAUDRATE(BaudRate));
 257                     ; 109   assert_param(IS_USART_WordLength(USART_WordLength));
 259                     ; 111   assert_param(IS_USART_STOPBITS(USART_StopBits));
 261                     ; 113   assert_param(IS_USART_PARITY(USART_Parity));
 263                     ; 115   assert_param(IS_USART_MODE(USART_Mode));
 265                     ; 118   USART->CR1 &= (uint8_t)(~(USART_CR1_PCEN | USART_CR1_PS | USART_CR1_M));
 267  002d c65234        	ld	a,21044
 268  0030 a4e9          	and	a,#233
 269  0032 c75234        	ld	21044,a
 270                     ; 121   USART->CR1 |= (uint8_t)((uint8_t)USART_WordLength | (uint8_t)USART_Parity);
 272  0035 7b0b          	ld	a,(OFST+7,sp)
 273  0037 1a0d          	or	a,(OFST+9,sp)
 274  0039 ca5234        	or	a,21044
 275  003c c75234        	ld	21044,a
 276                     ; 124   USART->CR3 &= (uint8_t)(~USART_CR3_STOP);
 278  003f c65236        	ld	a,21046
 279  0042 a4cf          	and	a,#207
 280  0044 c75236        	ld	21046,a
 281                     ; 126   USART->CR3 |= (uint8_t)USART_StopBits;
 283  0047 c65236        	ld	a,21046
 284  004a 1a0c          	or	a,(OFST+8,sp)
 285  004c c75236        	ld	21046,a
 286                     ; 129   USART->BRR1 &= (uint8_t)(~USART_BRR1_DIVM);
 288  004f 725f5232      	clr	21042
 289                     ; 131   USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVM);
 291  0053 c65233        	ld	a,21043
 292  0056 a40f          	and	a,#15
 293  0058 c75233        	ld	21043,a
 294                     ; 133   USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVF);
 296  005b c65233        	ld	a,21043
 297  005e a4f0          	and	a,#240
 298  0060 c75233        	ld	21043,a
 299                     ; 135   BaudRate_Mantissa  = ((uint32_t)CLK_GetClockFreq() / BaudRate);
 301  0063 cd0000        	call	_CLK_GetClockFreq
 303  0066 96            	ldw	x,sp
 304  0067 1c0007        	addw	x,#OFST+3
 305  006a cd0000        	call	c_ludv
 307  006d 96            	ldw	x,sp
 308  006e 1c0001        	addw	x,#OFST-3
 309  0071 cd0000        	call	c_rtol
 311                     ; 137   USART->BRR2 = (uint8_t)((BaudRate_Mantissa >> (uint8_t)8) & (uint8_t)0xF0);
 313  0074 7b03          	ld	a,(OFST-1,sp)
 314  0076 a4f0          	and	a,#240
 315  0078 c75233        	ld	21043,a
 316                     ; 139   USART->BRR2 |= (uint8_t)(BaudRate_Mantissa & (uint8_t)0x0F);
 318  007b 7b04          	ld	a,(OFST+0,sp)
 319  007d a40f          	and	a,#15
 320  007f ca5233        	or	a,21043
 321  0082 c75233        	ld	21043,a
 322                     ; 141   USART->BRR1 = (uint8_t)(BaudRate_Mantissa >> (uint8_t)4);
 324  0085 96            	ldw	x,sp
 325  0086 1c0001        	addw	x,#OFST-3
 326  0089 cd0000        	call	c_ltor
 328  008c a604          	ld	a,#4
 329  008e cd0000        	call	c_lursh
 331  0091 b603          	ld	a,c_lreg+3
 332  0093 c75232        	ld	21042,a
 333                     ; 144   USART->CR2 &= (uint8_t)~(USART_CR2_TEN | USART_CR2_REN);
 335  0096 c65235        	ld	a,21045
 336  0099 a4f3          	and	a,#243
 337  009b c75235        	ld	21045,a
 338                     ; 146   USART->CR2 |= (uint8_t)USART_Mode;
 340  009e c65235        	ld	a,21045
 341  00a1 1a0e          	or	a,(OFST+10,sp)
 342  00a3 c75235        	ld	21045,a
 343                     ; 147 }
 346  00a6 5b04          	addw	sp,#4
 347  00a8 81            	ret
 495                     ; 171 void USART_ClockInit(USART_Clock_TypeDef USART_Clock, USART_CPOL_TypeDef USART_CPOL,
 495                     ; 172                      USART_CPHA_TypeDef USART_CPHA, USART_LastBit_TypeDef USART_LastBit)
 495                     ; 173 {
 496                     	switch	.text
 497  00a9               _USART_ClockInit:
 499  00a9 89            	pushw	x
 500       00000000      OFST:	set	0
 503                     ; 175   assert_param(IS_USART_CLOCK(USART_Clock));
 505                     ; 176   assert_param(IS_USART_CPOL(USART_CPOL));
 507                     ; 177   assert_param(IS_USART_CPHA(USART_CPHA));
 509                     ; 178   assert_param(IS_USART_LASTBIT(USART_LastBit));
 511                     ; 181   USART->CR3 &= (uint8_t)~(USART_CR3_CPOL | USART_CR3_CPHA | USART_CR3_LBCL);
 513  00aa c65236        	ld	a,21046
 514  00ad a4f8          	and	a,#248
 515  00af c75236        	ld	21046,a
 516                     ; 183   USART->CR3 |= (uint8_t)((uint8_t)USART_CPOL | (uint8_t)USART_CPHA | (uint8_t)USART_LastBit);
 518  00b2 9f            	ld	a,xl
 519  00b3 1a05          	or	a,(OFST+5,sp)
 520  00b5 1a06          	or	a,(OFST+6,sp)
 521  00b7 ca5236        	or	a,21046
 522  00ba c75236        	ld	21046,a
 523                     ; 185   if (USART_Clock != USART_Clock_Disable)
 525  00bd 0d01          	tnz	(OFST+1,sp)
 526  00bf 2706          	jreq	L712
 527                     ; 187     USART->CR3 |= (uint8_t)(USART_CR3_CLKEN); /* Set the Clock Enable bit */
 529  00c1 72165236      	bset	21046,#3
 531  00c5 2004          	jra	L122
 532  00c7               L712:
 533                     ; 191     USART->CR3 &= (uint8_t)(~USART_CR3_CLKEN); /* Clear the Clock Enable bit */
 535  00c7 72175236      	bres	21046,#3
 536  00cb               L122:
 537                     ; 193 }
 540  00cb 85            	popw	x
 541  00cc 81            	ret
 596                     ; 201 void USART_Cmd(FunctionalState NewState)
 596                     ; 202 {
 597                     	switch	.text
 598  00cd               _USART_Cmd:
 602                     ; 203   assert_param(IS_FUNCTIONAL_STATE(NewState));
 604                     ; 205   if (NewState != DISABLE)
 606  00cd 4d            	tnz	a
 607  00ce 2706          	jreq	L152
 608                     ; 207     USART->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
 610  00d0 721b5234      	bres	21044,#5
 612  00d4 2004          	jra	L352
 613  00d6               L152:
 614                     ; 211     USART->CR1 |= USART_CR1_USARTD;  /**< USART Disable */
 616  00d6 721a5234      	bset	21044,#5
 617  00da               L352:
 618                     ; 213 }
 621  00da 81            	ret
 732                     ; 229 void USART_ITConfig(USART_IT_TypeDef USART_IT, FunctionalState NewState)
 732                     ; 230 {
 733                     	switch	.text
 734  00db               _USART_ITConfig:
 736  00db 89            	pushw	x
 737  00dc 89            	pushw	x
 738       00000002      OFST:	set	2
 741                     ; 231   uint8_t uartreg, itpos = 0x00;
 743  00dd 7b02          	ld	a,(OFST+0,sp)
 744  00df 97            	ld	xl,a
 745                     ; 232   assert_param(IS_USART_CONFIG_IT(USART_IT));
 747                     ; 233   assert_param(IS_FUNCTIONAL_STATE(NewState));
 749                     ; 236   uartreg = (uint8_t)((uint16_t)USART_IT >> (uint8_t)0x08);
 751  00e0 7b03          	ld	a,(OFST+1,sp)
 752  00e2 6b01          	ld	(OFST-1,sp),a
 753                     ; 238   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
 755  00e4 7b04          	ld	a,(OFST+2,sp)
 756  00e6 a40f          	and	a,#15
 757  00e8 5f            	clrw	x
 758  00e9 97            	ld	xl,a
 759  00ea a601          	ld	a,#1
 760  00ec 5d            	tnzw	x
 761  00ed 2704          	jreq	L61
 762  00ef               L02:
 763  00ef 48            	sll	a
 764  00f0 5a            	decw	x
 765  00f1 26fc          	jrne	L02
 766  00f3               L61:
 767  00f3 6b02          	ld	(OFST+0,sp),a
 768                     ; 240   if (NewState != DISABLE)
 770  00f5 0d07          	tnz	(OFST+5,sp)
 771  00f7 271a          	jreq	L723
 772                     ; 243     if (uartreg == 0x01)
 774  00f9 7b01          	ld	a,(OFST-1,sp)
 775  00fb a101          	cp	a,#1
 776  00fd 260a          	jrne	L133
 777                     ; 245       USART->CR1 |= itpos;
 779  00ff c65234        	ld	a,21044
 780  0102 1a02          	or	a,(OFST+0,sp)
 781  0104 c75234        	ld	21044,a
 783  0107 2024          	jra	L533
 784  0109               L133:
 785                     ; 250       USART->CR2 |= itpos;
 787  0109 c65235        	ld	a,21045
 788  010c 1a02          	or	a,(OFST+0,sp)
 789  010e c75235        	ld	21045,a
 790  0111 201a          	jra	L533
 791  0113               L723:
 792                     ; 256     if (uartreg == 0x01)
 794  0113 7b01          	ld	a,(OFST-1,sp)
 795  0115 a101          	cp	a,#1
 796  0117 260b          	jrne	L733
 797                     ; 258       USART->CR1 &= (uint8_t)(~itpos);
 799  0119 7b02          	ld	a,(OFST+0,sp)
 800  011b 43            	cpl	a
 801  011c c45234        	and	a,21044
 802  011f c75234        	ld	21044,a
 804  0122 2009          	jra	L533
 805  0124               L733:
 806                     ; 263       USART->CR2 &= (uint8_t)(~itpos);
 808  0124 7b02          	ld	a,(OFST+0,sp)
 809  0126 43            	cpl	a
 810  0127 c45235        	and	a,21045
 811  012a c75235        	ld	21045,a
 812  012d               L533:
 813                     ; 267 }
 816  012d 5b04          	addw	sp,#4
 817  012f 81            	ret
 840                     ; 275 uint8_t USART_ReceiveData8(void)
 840                     ; 276 {
 841                     	switch	.text
 842  0130               _USART_ReceiveData8:
 846                     ; 277   return USART->DR;
 848  0130 c65231        	ld	a,21041
 851  0133 81            	ret
 885                     ; 287 uint16_t USART_ReceiveData9(void)
 885                     ; 288 {
 886                     	switch	.text
 887  0134               _USART_ReceiveData9:
 889  0134 89            	pushw	x
 890       00000002      OFST:	set	2
 893                     ; 289   uint16_t temp = 0;
 895  0135 5f            	clrw	x
 896  0136 1f01          	ldw	(OFST-1,sp),x
 897                     ; 291   temp = ((uint16_t)(((uint16_t)((uint16_t)USART->CR1 & (uint16_t)USART_CR1_R8)) << 1));
 899  0138 c65234        	ld	a,21044
 900  013b 5f            	clrw	x
 901  013c a480          	and	a,#128
 902  013e 5f            	clrw	x
 903  013f 02            	rlwa	x,a
 904  0140 58            	sllw	x
 905  0141 1f01          	ldw	(OFST-1,sp),x
 906                     ; 292   return (uint16_t)( ((uint16_t)((uint16_t)USART->DR) | temp) & ((uint16_t)0x01FF));
 908  0143 c65231        	ld	a,21041
 909  0146 5f            	clrw	x
 910  0147 97            	ld	xl,a
 911  0148 01            	rrwa	x,a
 912  0149 1a02          	or	a,(OFST+0,sp)
 913  014b 01            	rrwa	x,a
 914  014c 1a01          	or	a,(OFST-1,sp)
 915  014e 01            	rrwa	x,a
 916  014f 01            	rrwa	x,a
 917  0150 a4ff          	and	a,#255
 918  0152 01            	rrwa	x,a
 919  0153 a401          	and	a,#1
 920  0155 01            	rrwa	x,a
 923  0156 5b02          	addw	sp,#2
 924  0158 81            	ret
 960                     ; 301 void USART_ReceiverWakeUpCmd(FunctionalState NewState)
 960                     ; 302 {
 961                     	switch	.text
 962  0159               _USART_ReceiverWakeUpCmd:
 966                     ; 303   assert_param(IS_FUNCTIONAL_STATE(NewState));
 968                     ; 305   if (NewState != DISABLE)
 970  0159 4d            	tnz	a
 971  015a 2706          	jreq	L704
 972                     ; 308     USART->CR2 |= USART_CR2_RWU;
 974  015c 72125235      	bset	21045,#1
 976  0160 2004          	jra	L114
 977  0162               L704:
 978                     ; 313     USART->CR2 &= ((uint8_t)~USART_CR2_RWU);
 980  0162 72135235      	bres	21045,#1
 981  0166               L114:
 982                     ; 315 }
 985  0166 81            	ret
1008                     ; 322 void USART_SendBreak(void)
1008                     ; 323 {
1009                     	switch	.text
1010  0167               _USART_SendBreak:
1014                     ; 324   USART->CR2 |= USART_CR2_SBK;
1016  0167 72105235      	bset	21045,#0
1017                     ; 325 }
1020  016b 81            	ret
1054                     ; 332 void USART_SendData8(uint8_t Data)
1054                     ; 333 {
1055                     	switch	.text
1056  016c               _USART_SendData8:
1060                     ; 335   USART->DR = Data;
1062  016c c75231        	ld	21041,a
1063                     ; 336 }
1066  016f 81            	ret
1100                     ; 344 void USART_SendData9(uint16_t Data)
1100                     ; 345 {
1101                     	switch	.text
1102  0170               _USART_SendData9:
1104  0170 89            	pushw	x
1105       00000000      OFST:	set	0
1108                     ; 346   assert_param(IS_USART_DATA_9BITS(Data));
1110                     ; 348   USART->CR1 &= ((uint8_t)~USART_CR1_T8);                    /* Clear the transmit data bit 8     */
1112  0171 721d5234      	bres	21044,#6
1113                     ; 349   USART->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & USART_CR1_T8); /* Write the transmit data bit [8]   */
1115  0175 54            	srlw	x
1116  0176 54            	srlw	x
1117  0177 9f            	ld	a,xl
1118  0178 a440          	and	a,#64
1119  017a ca5234        	or	a,21044
1120  017d c75234        	ld	21044,a
1121                     ; 350   USART->DR   = (uint8_t)(Data);                             /* Write the transmit data bit [0:7] */
1123  0180 7b02          	ld	a,(OFST+2,sp)
1124  0182 c75231        	ld	21041,a
1125                     ; 352 }
1128  0185 85            	popw	x
1129  0186 81            	ret
1163                     ; 360 void USART_SetAddress(uint8_t Address)
1163                     ; 361 {
1164                     	switch	.text
1165  0187               _USART_SetAddress:
1167  0187 88            	push	a
1168       00000000      OFST:	set	0
1171                     ; 363   assert_param(IS_USART_ADDRESS(Address));
1173                     ; 366   USART->CR4 &= ((uint8_t)~USART_CR4_ADD);
1175  0188 c65237        	ld	a,21047
1176  018b a4f0          	and	a,#240
1177  018d c75237        	ld	21047,a
1178                     ; 368   USART->CR4 |= Address;
1180  0190 c65237        	ld	a,21047
1181  0193 1a01          	or	a,(OFST+1,sp)
1182  0195 c75237        	ld	21047,a
1183                     ; 369 }
1186  0198 84            	pop	a
1187  0199 81            	ret
1244                     ; 379 void USART_WakeUpConfig(USART_WakeUp_TypeDef USART_WakeUp)
1244                     ; 380 {
1245                     	switch	.text
1246  019a               _USART_WakeUpConfig:
1250                     ; 381   assert_param(IS_USART_WAKEUP(USART_WakeUp));
1252                     ; 383   USART->CR1 &= ((uint8_t)~USART_CR1_WAKE);
1254  019a 72175234      	bres	21044,#3
1255                     ; 384   USART->CR1 |= (uint8_t)USART_WakeUp;
1257  019e ca5234        	or	a,21044
1258  01a1 c75234        	ld	21044,a
1259                     ; 385 }
1262  01a4 81            	ret
1398                     ; 400 FlagStatus USART_GetFlagStatus(USART_FLAG_TypeDef USART_FLAG)
1398                     ; 401 {
1399                     	switch	.text
1400  01a5               _USART_GetFlagStatus:
1402  01a5 89            	pushw	x
1403  01a6 88            	push	a
1404       00000001      OFST:	set	1
1407                     ; 402   FlagStatus status = RESET;
1409  01a7 0f01          	clr	(OFST+0,sp)
1410                     ; 405   assert_param(IS_USART_FLAG(USART_FLAG));
1412                     ; 407   if (USART_FLAG == USART_FLAG_SBK)
1414  01a9 a30101        	cpw	x,#257
1415  01ac 2610          	jrne	L306
1416                     ; 409     if ((USART->CR2 & (uint8_t)USART_FLAG) != (uint8_t)0x00)
1418  01ae 9f            	ld	a,xl
1419  01af c45235        	and	a,21045
1420  01b2 2706          	jreq	L506
1421                     ; 412       status = SET;
1423  01b4 a601          	ld	a,#1
1424  01b6 6b01          	ld	(OFST+0,sp),a
1426  01b8 2013          	jra	L116
1427  01ba               L506:
1428                     ; 417       status = RESET;
1430  01ba 0f01          	clr	(OFST+0,sp)
1431  01bc 200f          	jra	L116
1432  01be               L306:
1433                     ; 422     if ((USART->SR & (uint8_t)USART_FLAG) != (uint8_t)0x00)
1435  01be c65230        	ld	a,21040
1436  01c1 1503          	bcp	a,(OFST+2,sp)
1437  01c3 2706          	jreq	L316
1438                     ; 425       status = SET;
1440  01c5 a601          	ld	a,#1
1441  01c7 6b01          	ld	(OFST+0,sp),a
1443  01c9 2002          	jra	L116
1444  01cb               L316:
1445                     ; 430       status = RESET;
1447  01cb 0f01          	clr	(OFST+0,sp)
1448  01cd               L116:
1449                     ; 434   return status;
1451  01cd 7b01          	ld	a,(OFST+0,sp)
1454  01cf 5b03          	addw	sp,#3
1455  01d1 81            	ret
1478                     ; 454 void USART_ClearFlag(void)
1478                     ; 455 {
1479                     	switch	.text
1480  01d2               _USART_ClearFlag:
1484                     ; 457   USART->SR = (uint8_t)~(USART_SR_RXNE);
1486  01d2 35df5230      	mov	21040,#223
1487                     ; 458 }
1490  01d6 81            	ret
1572                     ; 472 ITStatus USART_GetITStatus(USART_IT_TypeDef USART_IT)
1572                     ; 473 {
1573                     	switch	.text
1574  01d7               _USART_GetITStatus:
1576  01d7 89            	pushw	x
1577  01d8 89            	pushw	x
1578       00000002      OFST:	set	2
1581                     ; 474   ITStatus pendingbitstatus = RESET;
1583  01d9 7b02          	ld	a,(OFST+0,sp)
1584  01db 97            	ld	xl,a
1585                     ; 475   uint8_t itpos = 0;
1587  01dc 7b01          	ld	a,(OFST-1,sp)
1588  01de 97            	ld	xl,a
1589                     ; 476   uint8_t itmask1 = 0;
1591  01df 7b02          	ld	a,(OFST+0,sp)
1592  01e1 97            	ld	xl,a
1593                     ; 477   uint8_t itmask2 = 0;
1595  01e2 7b02          	ld	a,(OFST+0,sp)
1596  01e4 97            	ld	xl,a
1597                     ; 478   uint8_t enablestatus = 0;
1599  01e5 7b02          	ld	a,(OFST+0,sp)
1600  01e7 97            	ld	xl,a
1601                     ; 481   assert_param(IS_USART_GET_IT(USART_IT));
1603                     ; 484   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
1605  01e8 7b04          	ld	a,(OFST+2,sp)
1606  01ea a40f          	and	a,#15
1607  01ec 5f            	clrw	x
1608  01ed 97            	ld	xl,a
1609  01ee a601          	ld	a,#1
1610  01f0 5d            	tnzw	x
1611  01f1 2704          	jreq	L05
1612  01f3               L25:
1613  01f3 48            	sll	a
1614  01f4 5a            	decw	x
1615  01f5 26fc          	jrne	L25
1616  01f7               L05:
1617  01f7 6b01          	ld	(OFST-1,sp),a
1618                     ; 486   itmask1 = (uint8_t)((uint8_t)USART_IT >> (uint8_t)4);
1620  01f9 7b04          	ld	a,(OFST+2,sp)
1621  01fb 4e            	swap	a
1622  01fc a40f          	and	a,#15
1623  01fe 6b02          	ld	(OFST+0,sp),a
1624                     ; 488   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
1626  0200 7b02          	ld	a,(OFST+0,sp)
1627  0202 5f            	clrw	x
1628  0203 97            	ld	xl,a
1629  0204 a601          	ld	a,#1
1630  0206 5d            	tnzw	x
1631  0207 2704          	jreq	L45
1632  0209               L65:
1633  0209 48            	sll	a
1634  020a 5a            	decw	x
1635  020b 26fc          	jrne	L65
1636  020d               L45:
1637  020d 6b02          	ld	(OFST+0,sp),a
1638                     ; 492   if (USART_IT == USART_IT_PE)
1640  020f 1e03          	ldw	x,(OFST+1,sp)
1641  0211 a30100        	cpw	x,#256
1642  0214 261c          	jrne	L176
1643                     ; 495     enablestatus = (uint8_t)((uint8_t)USART->CR1 & itmask2);
1645  0216 c65234        	ld	a,21044
1646  0219 1402          	and	a,(OFST+0,sp)
1647  021b 6b02          	ld	(OFST+0,sp),a
1648                     ; 498     if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
1650  021d c65230        	ld	a,21040
1651  0220 1501          	bcp	a,(OFST-1,sp)
1652  0222 270a          	jreq	L376
1654  0224 0d02          	tnz	(OFST+0,sp)
1655  0226 2706          	jreq	L376
1656                     ; 501       pendingbitstatus = SET;
1658  0228 a601          	ld	a,#1
1659  022a 6b02          	ld	(OFST+0,sp),a
1661  022c 201e          	jra	L776
1662  022e               L376:
1663                     ; 506       pendingbitstatus = RESET;
1665  022e 0f02          	clr	(OFST+0,sp)
1666  0230 201a          	jra	L776
1667  0232               L176:
1668                     ; 512     enablestatus = (uint8_t)((uint8_t)USART->CR2 & itmask2);
1670  0232 c65235        	ld	a,21045
1671  0235 1402          	and	a,(OFST+0,sp)
1672  0237 6b02          	ld	(OFST+0,sp),a
1673                     ; 514     if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
1675  0239 c65230        	ld	a,21040
1676  023c 1501          	bcp	a,(OFST-1,sp)
1677  023e 270a          	jreq	L107
1679  0240 0d02          	tnz	(OFST+0,sp)
1680  0242 2706          	jreq	L107
1681                     ; 517       pendingbitstatus = SET;
1683  0244 a601          	ld	a,#1
1684  0246 6b02          	ld	(OFST+0,sp),a
1686  0248 2002          	jra	L776
1687  024a               L107:
1688                     ; 522       pendingbitstatus = RESET;
1690  024a 0f02          	clr	(OFST+0,sp)
1691  024c               L776:
1692                     ; 527   return  pendingbitstatus;
1694  024c 7b02          	ld	a,(OFST+0,sp)
1697  024e 5b04          	addw	sp,#4
1698  0250 81            	ret
1722                     ; 546 void USART_ClearITPendingBit(void)
1722                     ; 547 {
1723                     	switch	.text
1724  0251               _USART_ClearITPendingBit:
1728                     ; 549   USART->SR = (uint8_t)~(USART_SR_RXNE);
1730  0251 35df5230      	mov	21040,#223
1731                     ; 550 }
1734  0255 81            	ret
1747                     	xdef	_USART_ClearITPendingBit
1748                     	xdef	_USART_GetITStatus
1749                     	xdef	_USART_ClearFlag
1750                     	xdef	_USART_GetFlagStatus
1751                     	xdef	_USART_WakeUpConfig
1752                     	xdef	_USART_SetAddress
1753                     	xdef	_USART_SendData9
1754                     	xdef	_USART_SendData8
1755                     	xdef	_USART_SendBreak
1756                     	xdef	_USART_ReceiverWakeUpCmd
1757                     	xdef	_USART_ReceiveData9
1758                     	xdef	_USART_ReceiveData8
1759                     	xdef	_USART_ITConfig
1760                     	xdef	_USART_Cmd
1761                     	xdef	_USART_ClockInit
1762                     	xdef	_USART_Init
1763                     	xdef	_USART_DeInit
1764                     	xref	_CLK_GetClockFreq
1765                     	xref.b	c_lreg
1784                     	xref	c_lursh
1785                     	xref	c_ltor
1786                     	xref	c_rtol
1787                     	xref	c_ludv
1788                     	end
