   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  98                     ; 57 void GPIO_DeInit(GPIO_TypeDef* GPIOx)
  98                     ; 58 {
 100                     	switch	.text
 101  0000               _GPIO_DeInit:
 105                     ; 59   GPIOx->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
 107  0000 7f            	clr	(x)
 108                     ; 60   GPIOx->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
 110  0001 6f02          	clr	(2,x)
 111                     ; 61   GPIOx->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
 113  0003 6f03          	clr	(3,x)
 114                     ; 62   GPIOx->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
 116  0005 6f04          	clr	(4,x)
 117                     ; 63 }
 120  0007 81            	ret
 276                     ; 98 void GPIO_Init(GPIO_TypeDef* GPIOx,
 276                     ; 99                uint8_t GPIO_Pin,
 276                     ; 100                GPIO_Mode_TypeDef GPIO_Mode)
 276                     ; 101 {
 277                     	switch	.text
 278  0008               _GPIO_Init:
 280  0008 89            	pushw	x
 281       00000000      OFST:	set	0
 284                     ; 106   assert_param(IS_GPIO_MODE(GPIO_Mode));
 286                     ; 107   assert_param(IS_GPIO_PIN(GPIO_Pin));
 288                     ; 113   if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) != (uint8_t)0x00) /* Output mode */
 290  0009 7b06          	ld	a,(OFST+6,sp)
 291  000b a580          	bcp	a,#128
 292  000d 271d          	jreq	L541
 293                     ; 115     if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) != (uint8_t)0x00) /* High level */
 295  000f 7b06          	ld	a,(OFST+6,sp)
 296  0011 a510          	bcp	a,#16
 297  0013 2706          	jreq	L741
 298                     ; 117       GPIOx->ODR |= GPIO_Pin;
 300  0015 f6            	ld	a,(x)
 301  0016 1a05          	or	a,(OFST+5,sp)
 302  0018 f7            	ld	(x),a
 304  0019 2007          	jra	L151
 305  001b               L741:
 306                     ; 120       GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
 308  001b 1e01          	ldw	x,(OFST+1,sp)
 309  001d 7b05          	ld	a,(OFST+5,sp)
 310  001f 43            	cpl	a
 311  0020 f4            	and	a,(x)
 312  0021 f7            	ld	(x),a
 313  0022               L151:
 314                     ; 123     GPIOx->DDR |= GPIO_Pin;
 316  0022 1e01          	ldw	x,(OFST+1,sp)
 317  0024 e602          	ld	a,(2,x)
 318  0026 1a05          	or	a,(OFST+5,sp)
 319  0028 e702          	ld	(2,x),a
 321  002a 2009          	jra	L351
 322  002c               L541:
 323                     ; 127     GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
 325  002c 1e01          	ldw	x,(OFST+1,sp)
 326  002e 7b05          	ld	a,(OFST+5,sp)
 327  0030 43            	cpl	a
 328  0031 e402          	and	a,(2,x)
 329  0033 e702          	ld	(2,x),a
 330  0035               L351:
 331                     ; 134   if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) != (uint8_t)0x00) /* Pull-Up or Push-Pull */
 333  0035 7b06          	ld	a,(OFST+6,sp)
 334  0037 a540          	bcp	a,#64
 335  0039 270a          	jreq	L551
 336                     ; 136     GPIOx->CR1 |= GPIO_Pin;
 338  003b 1e01          	ldw	x,(OFST+1,sp)
 339  003d e603          	ld	a,(3,x)
 340  003f 1a05          	or	a,(OFST+5,sp)
 341  0041 e703          	ld	(3,x),a
 343  0043 2009          	jra	L751
 344  0045               L551:
 345                     ; 139     GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
 347  0045 1e01          	ldw	x,(OFST+1,sp)
 348  0047 7b05          	ld	a,(OFST+5,sp)
 349  0049 43            	cpl	a
 350  004a e403          	and	a,(3,x)
 351  004c e703          	ld	(3,x),a
 352  004e               L751:
 353                     ; 146   if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) != (uint8_t)0x00) /* Interrupt or Slow slope */
 355  004e 7b06          	ld	a,(OFST+6,sp)
 356  0050 a520          	bcp	a,#32
 357  0052 270a          	jreq	L161
 358                     ; 148     GPIOx->CR2 |= GPIO_Pin;
 360  0054 1e01          	ldw	x,(OFST+1,sp)
 361  0056 e604          	ld	a,(4,x)
 362  0058 1a05          	or	a,(OFST+5,sp)
 363  005a e704          	ld	(4,x),a
 365  005c 2009          	jra	L361
 366  005e               L161:
 367                     ; 151     GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
 369  005e 1e01          	ldw	x,(OFST+1,sp)
 370  0060 7b05          	ld	a,(OFST+5,sp)
 371  0062 43            	cpl	a
 372  0063 e404          	and	a,(4,x)
 373  0065 e704          	ld	(4,x),a
 374  0067               L361:
 375                     ; 154 }
 378  0067 85            	popw	x
 379  0068 81            	ret
 425                     ; 163 void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t GPIO_PortVal)
 425                     ; 164 {
 426                     	switch	.text
 427  0069               _GPIO_Write:
 429  0069 89            	pushw	x
 430       00000000      OFST:	set	0
 433                     ; 165   GPIOx->ODR = GPIO_PortVal;
 435  006a 7b05          	ld	a,(OFST+5,sp)
 436  006c 1e01          	ldw	x,(OFST+1,sp)
 437  006e f7            	ld	(x),a
 438                     ; 166 }
 441  006f 85            	popw	x
 442  0070 81            	ret
 602                     ; 185 void GPIO_WriteBit(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, BitAction GPIO_BitVal)
 602                     ; 186 {
 603                     	switch	.text
 604  0071               _GPIO_WriteBit:
 606  0071 89            	pushw	x
 607       00000000      OFST:	set	0
 610                     ; 188   assert_param(IS_GPIO_PIN(GPIO_Pin));
 612                     ; 189   assert_param(IS_STATE_VALUE(GPIO_BitVal));
 614                     ; 191   if (GPIO_BitVal != RESET)
 616  0072 0d06          	tnz	(OFST+6,sp)
 617  0074 2715          	jreq	L303
 618                     ; 193     SetBit(GPIOx->ODR, GPIO_Pin);
 620  0076 7b05          	ld	a,(OFST+5,sp)
 621  0078 905f          	clrw	y
 622  007a 9097          	ld	yl,a
 623  007c a601          	ld	a,#1
 624  007e 905d          	tnzw	y
 625  0080 2705          	jreq	L41
 626  0082               L61:
 627  0082 48            	sll	a
 628  0083 905a          	decw	y
 629  0085 26fb          	jrne	L61
 630  0087               L41:
 631  0087 fa            	or	a,(x)
 632  0088 f7            	ld	(x),a
 634  0089 2017          	jra	L503
 635  008b               L303:
 636                     ; 198     ClrBit(GPIOx->ODR, GPIO_Pin);
 638  008b 1e01          	ldw	x,(OFST+1,sp)
 639  008d 7b05          	ld	a,(OFST+5,sp)
 640  008f 905f          	clrw	y
 641  0091 9097          	ld	yl,a
 642  0093 a601          	ld	a,#1
 643  0095 905d          	tnzw	y
 644  0097 2705          	jreq	L02
 645  0099               L22:
 646  0099 48            	sll	a
 647  009a 905a          	decw	y
 648  009c 26fb          	jrne	L22
 649  009e               L02:
 650  009e a8ff          	xor	a,#255
 651  00a0 f4            	and	a,(x)
 652  00a1 f7            	ld	(x),a
 653  00a2               L503:
 654                     ; 200 }
 657  00a2 85            	popw	x
 658  00a3 81            	ret
 704                     ; 218 void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
 704                     ; 219 {
 705                     	switch	.text
 706  00a4               _GPIO_SetBits:
 708  00a4 89            	pushw	x
 709       00000000      OFST:	set	0
 712                     ; 220   GPIOx->ODR |= GPIO_Pin;
 714  00a5 f6            	ld	a,(x)
 715  00a6 1a05          	or	a,(OFST+5,sp)
 716  00a8 f7            	ld	(x),a
 717                     ; 221 }
 720  00a9 85            	popw	x
 721  00aa 81            	ret
 767                     ; 239 void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
 767                     ; 240 {
 768                     	switch	.text
 769  00ab               _GPIO_ResetBits:
 771  00ab 89            	pushw	x
 772       00000000      OFST:	set	0
 775                     ; 241   GPIOx->ODR &= (uint8_t)(~GPIO_Pin);
 777  00ac 7b05          	ld	a,(OFST+5,sp)
 778  00ae 43            	cpl	a
 779  00af f4            	and	a,(x)
 780  00b0 f7            	ld	(x),a
 781                     ; 242 }
 784  00b1 85            	popw	x
 785  00b2 81            	ret
 831                     ; 251 void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
 831                     ; 252 {
 832                     	switch	.text
 833  00b3               _GPIO_ToggleBits:
 835  00b3 89            	pushw	x
 836       00000000      OFST:	set	0
 839                     ; 253   GPIOx->ODR ^= GPIO_Pin;
 841  00b4 f6            	ld	a,(x)
 842  00b5 1805          	xor	a,	(OFST+5,sp)
 843  00b7 f7            	ld	(x),a
 844                     ; 254 }
 847  00b8 85            	popw	x
 848  00b9 81            	ret
 885                     ; 262 uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
 885                     ; 263 {
 886                     	switch	.text
 887  00ba               _GPIO_ReadInputData:
 891                     ; 264   return ((uint8_t)GPIOx->IDR);
 893  00ba e601          	ld	a,(1,x)
 896  00bc 81            	ret
 934                     ; 273 uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
 934                     ; 274 {
 935                     	switch	.text
 936  00bd               _GPIO_ReadOutputData:
 940                     ; 275   return ((uint8_t)GPIOx->ODR);
 942  00bd f6            	ld	a,(x)
 945  00be 81            	ret
 994                     ; 294 BitStatus GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
 994                     ; 295 {
 995                     	switch	.text
 996  00bf               _GPIO_ReadInputDataBit:
 998  00bf 89            	pushw	x
 999       00000000      OFST:	set	0
1002                     ; 296   return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
1004  00c0 e601          	ld	a,(1,x)
1005  00c2 1405          	and	a,(OFST+5,sp)
1008  00c4 85            	popw	x
1009  00c5 81            	ret
1058                     ; 315 BitStatus GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
1058                     ; 316 {
1059                     	switch	.text
1060  00c6               _GPIO_ReadOutputDataBit:
1062  00c6 89            	pushw	x
1063       00000000      OFST:	set	0
1066                     ; 317   return ((BitStatus)(GPIOx->ODR & (uint8_t)GPIO_Pin));
1068  00c7 f6            	ld	a,(x)
1069  00c8 1405          	and	a,(OFST+5,sp)
1072  00ca 85            	popw	x
1073  00cb 81            	ret
1150                     ; 337 void GPIO_ExternalPullUpConfig(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin, FunctionalState NewState)
1150                     ; 338 {
1151                     	switch	.text
1152  00cc               _GPIO_ExternalPullUpConfig:
1154  00cc 89            	pushw	x
1155       00000000      OFST:	set	0
1158                     ; 340   assert_param(IS_GPIO_PIN(GPIO_Pin));
1160                     ; 341   assert_param(IS_FUNCTIONAL_STATE(NewState));
1162                     ; 343   if (NewState != DISABLE) /* External Pull-Up Set*/
1164  00cd 0d06          	tnz	(OFST+6,sp)
1165  00cf 2708          	jreq	L355
1166                     ; 345     GPIOx->CR1 |= GPIO_Pin;
1168  00d1 e603          	ld	a,(3,x)
1169  00d3 1a05          	or	a,(OFST+5,sp)
1170  00d5 e703          	ld	(3,x),a
1172  00d7 2009          	jra	L555
1173  00d9               L355:
1174                     ; 348     GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
1176  00d9 1e01          	ldw	x,(OFST+1,sp)
1177  00db 7b05          	ld	a,(OFST+5,sp)
1178  00dd 43            	cpl	a
1179  00de e403          	and	a,(3,x)
1180  00e0 e703          	ld	(3,x),a
1181  00e2               L555:
1182                     ; 350 }
1185  00e2 85            	popw	x
1186  00e3 81            	ret
1199                     	xdef	_GPIO_ExternalPullUpConfig
1200                     	xdef	_GPIO_ReadOutputDataBit
1201                     	xdef	_GPIO_ReadInputDataBit
1202                     	xdef	_GPIO_ReadOutputData
1203                     	xdef	_GPIO_ReadInputData
1204                     	xdef	_GPIO_ToggleBits
1205                     	xdef	_GPIO_ResetBits
1206                     	xdef	_GPIO_SetBits
1207                     	xdef	_GPIO_WriteBit
1208                     	xdef	_GPIO_Write
1209                     	xdef	_GPIO_Init
1210                     	xdef	_GPIO_DeInit
1229                     	end
