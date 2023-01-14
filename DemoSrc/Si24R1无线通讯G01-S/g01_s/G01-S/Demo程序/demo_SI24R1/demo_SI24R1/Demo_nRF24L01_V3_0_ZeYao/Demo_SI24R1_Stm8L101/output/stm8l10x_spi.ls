   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
  32                     ; 55 void SPI_DeInit(void)
  32                     ; 56 {
  34                     	switch	.text
  35  0000               _SPI_DeInit:
  39                     ; 57   SPI->CR1 = SPI_CR1_RESET_VALUE;
  41  0000 725f5200      	clr	20992
  42                     ; 58   SPI->CR2 = SPI_CR2_RESET_VALUE;
  44  0004 725f5201      	clr	20993
  45                     ; 59   SPI->ICR = SPI_ICR_RESET_VALUE;
  47  0008 725f5202      	clr	20994
  48                     ; 60   SPI->SR = SPI_SR_RESET_VALUE;
  50  000c 35025203      	mov	20995,#2
  51                     ; 61 }
  54  0010 81            	ret
 358                     ; 103 void SPI_Init(SPI_FirstBit_TypeDef SPI_FirstBit, SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler,
 358                     ; 104               SPI_Mode_TypeDef SPI_Mode, SPI_CPOL_TypeDef SPI_CPOL, SPI_CPHA_TypeDef SPI_CPHA,
 358                     ; 105               SPI_DirectionMode_TypeDef SPI_DirectionMode, SPI_NSS_TypeDef SPI_NSS)
 358                     ; 106 {
 359                     	switch	.text
 360  0011               _SPI_Init:
 362  0011 89            	pushw	x
 363       00000000      OFST:	set	0
 366                     ; 109   assert_param(IS_SPI_FIRST_BIT(SPI_FirstBit));
 368                     ; 110   assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
 370                     ; 111   assert_param(IS_SPI_MODE(SPI_Mode));
 372                     ; 112   assert_param(IS_SPI_CPOL(SPI_CPOL));
 374                     ; 113   assert_param(IS_SPI_CPHA(SPI_CPHA));
 376                     ; 114   assert_param(IS_SPI_DIRECTION_MODE(SPI_DirectionMode));
 378                     ; 115   assert_param(IS_SPI_NSS(SPI_NSS));
 380                     ; 118   SPI->CR1 = (uint8_t)((uint8_t)(SPI_FirstBit) |
 380                     ; 119                        (uint8_t)(SPI_BaudRatePrescaler) |
 380                     ; 120                        (uint8_t)(SPI_CPOL) |
 380                     ; 121                        (uint8_t)(SPI_CPHA));
 382  0012 9f            	ld	a,xl
 383  0013 1a01          	or	a,(OFST+1,sp)
 384  0015 1a06          	or	a,(OFST+6,sp)
 385  0017 1a07          	or	a,(OFST+7,sp)
 386  0019 c75200        	ld	20992,a
 387                     ; 124   SPI->CR2 = (uint8_t)((uint8_t)(SPI_DirectionMode) | (uint8_t)(SPI_NSS));
 389  001c 7b08          	ld	a,(OFST+8,sp)
 390  001e 1a09          	or	a,(OFST+9,sp)
 391  0020 c75201        	ld	20993,a
 392                     ; 126   if (SPI_Mode == SPI_Mode_Master)
 394  0023 7b05          	ld	a,(OFST+5,sp)
 395  0025 a104          	cp	a,#4
 396  0027 2606          	jrne	L771
 397                     ; 128     SPI->CR2 |= (uint8_t)SPI_CR2_SSI;
 399  0029 72105201      	bset	20993,#0
 401  002d 2004          	jra	L102
 402  002f               L771:
 403                     ; 132     SPI->CR2 &= (uint8_t)~(SPI_CR2_SSI);
 405  002f 72115201      	bres	20993,#0
 406  0033               L102:
 407                     ; 136   SPI->CR1 |= (uint8_t)(SPI_Mode);
 409  0033 c65200        	ld	a,20992
 410  0036 1a05          	or	a,(OFST+5,sp)
 411  0038 c75200        	ld	20992,a
 412                     ; 137 }
 415  003b 85            	popw	x
 416  003c 81            	ret
 471                     ; 145 void SPI_Cmd(FunctionalState NewState)
 471                     ; 146 {
 472                     	switch	.text
 473  003d               _SPI_Cmd:
 477                     ; 149   assert_param(IS_FUNCTIONAL_STATE(NewState));
 479                     ; 151   if (NewState != DISABLE)
 481  003d 4d            	tnz	a
 482  003e 2706          	jreq	L132
 483                     ; 153     SPI->CR1 |= SPI_CR1_SPE; /* Enable the SPI peripheral */
 485  0040 721c5200      	bset	20992,#6
 487  0044 2004          	jra	L332
 488  0046               L132:
 489                     ; 157     SPI->CR1 &= (uint8_t)(~SPI_CR1_SPE); /* Disable the SPI peripheral */
 491  0046 721d5200      	bres	20992,#6
 492  004a               L332:
 493                     ; 160 }
 496  004a 81            	ret
 598                     ; 174 void SPI_ITConfig(SPI_IT_TypeDef SPI_IT, FunctionalState NewState)
 598                     ; 175 {
 599                     	switch	.text
 600  004b               _SPI_ITConfig:
 602  004b 89            	pushw	x
 603  004c 88            	push	a
 604       00000001      OFST:	set	1
 607                     ; 176   uint8_t itpos = 0;
 609  004d 0f01          	clr	(OFST+0,sp)
 610                     ; 178   assert_param(IS_SPI_CONFIG_IT(SPI_IT));
 612                     ; 179   assert_param(IS_FUNCTIONAL_STATE(NewState));
 614                     ; 182   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)SPI_IT & (uint8_t)0x0F));
 616  004f 9e            	ld	a,xh
 617  0050 a40f          	and	a,#15
 618  0052 5f            	clrw	x
 619  0053 97            	ld	xl,a
 620  0054 a601          	ld	a,#1
 621  0056 5d            	tnzw	x
 622  0057 2704          	jreq	L41
 623  0059               L61:
 624  0059 48            	sll	a
 625  005a 5a            	decw	x
 626  005b 26fc          	jrne	L61
 627  005d               L41:
 628  005d 6b01          	ld	(OFST+0,sp),a
 629                     ; 184   if (NewState != DISABLE)
 631  005f 0d03          	tnz	(OFST+2,sp)
 632  0061 270a          	jreq	L303
 633                     ; 186     SPI->ICR |= itpos; /* Enable interrupt*/
 635  0063 c65202        	ld	a,20994
 636  0066 1a01          	or	a,(OFST+0,sp)
 637  0068 c75202        	ld	20994,a
 639  006b 2009          	jra	L503
 640  006d               L303:
 641                     ; 190     SPI->ICR &= (uint8_t)(~itpos); /* Disable interrupt*/
 643  006d 7b01          	ld	a,(OFST+0,sp)
 644  006f 43            	cpl	a
 645  0070 c45202        	and	a,20994
 646  0073 c75202        	ld	20994,a
 647  0076               L503:
 648                     ; 192 }
 651  0076 5b03          	addw	sp,#3
 652  0078 81            	ret
 686                     ; 199 void SPI_SendData(uint8_t Data)
 686                     ; 200 {
 687                     	switch	.text
 688  0079               _SPI_SendData:
 692                     ; 201   SPI->DR = Data; /* Write in the DR register the data to be sent*/
 694  0079 c75204        	ld	20996,a
 695                     ; 202 }
 698  007c 81            	ret
 721                     ; 209 uint8_t SPI_ReceiveData(void)
 721                     ; 210 {
 722                     	switch	.text
 723  007d               _SPI_ReceiveData:
 727                     ; 211   return ((uint8_t)SPI->DR); /* Return the data in the DR register */
 729  007d c65204        	ld	a,20996
 732  0080 81            	ret
 768                     ; 221 void SPI_NSSInternalSoftwareCmd(FunctionalState NewState)
 768                     ; 222 {
 769                     	switch	.text
 770  0081               _SPI_NSSInternalSoftwareCmd:
 774                     ; 225   assert_param(IS_FUNCTIONAL_STATE(NewState));
 776                     ; 227   if (NewState != DISABLE)
 778  0081 4d            	tnz	a
 779  0082 2706          	jreq	L353
 780                     ; 229     SPI->CR2 |= SPI_CR2_SSI; /* Set NSS pin internally by software */
 782  0084 72105201      	bset	20993,#0
 784  0088 2004          	jra	L553
 785  008a               L353:
 786                     ; 233     SPI->CR2 &= (uint8_t)(~SPI_CR2_SSI); /* Reset NSS pin internally by software */
 788  008a 72115201      	bres	20993,#0
 789  008e               L553:
 790                     ; 236 }
 793  008e 81            	ret
 849                     ; 246 void SPI_BiDirectionalLineConfig(SPI_Direction_TypeDef SPI_Direction)
 849                     ; 247 {
 850                     	switch	.text
 851  008f               _SPI_BiDirectionalLineConfig:
 855                     ; 250   assert_param(IS_SPI_DIRECTION(SPI_Direction));
 857                     ; 251   if (SPI_Direction != SPI_Direction_Rx)
 859  008f 4d            	tnz	a
 860  0090 2706          	jreq	L504
 861                     ; 253     SPI->CR2 |= SPI_CR2_BDOE; /* Set the Tx only mode*/
 863  0092 721c5201      	bset	20993,#6
 865  0096 2004          	jra	L704
 866  0098               L504:
 867                     ; 257     SPI->CR2 &= (uint8_t)(~SPI_CR2_BDOE); /* Set the Rx only mode*/
 869  0098 721d5201      	bres	20993,#6
 870  009c               L704:
 871                     ; 259 }
 874  009c 81            	ret
 988                     ; 275 FlagStatus SPI_GetFlagStatus(SPI_FLAG_TypeDef SPI_FLAG)
 988                     ; 276 {
 989                     	switch	.text
 990  009d               _SPI_GetFlagStatus:
 992  009d 88            	push	a
 993       00000001      OFST:	set	1
 996                     ; 277   FlagStatus status = RESET;
 998  009e 0f01          	clr	(OFST+0,sp)
 999                     ; 279   assert_param(IS_SPI_FLAG(SPI_FLAG));
1001                     ; 282   if ((SPI->SR & (uint8_t)SPI_FLAG) != (uint8_t)RESET)
1003  00a0 c45203        	and	a,20995
1004  00a3 2706          	jreq	L364
1005                     ; 284     status = SET; /* SPI_FLAG is set */
1007  00a5 a601          	ld	a,#1
1008  00a7 6b01          	ld	(OFST+0,sp),a
1010  00a9 2002          	jra	L564
1011  00ab               L364:
1012                     ; 288     status = RESET; /* SPI_FLAG is reset*/
1014  00ab 0f01          	clr	(OFST+0,sp)
1015  00ad               L564:
1016                     ; 292   return status;
1018  00ad 7b01          	ld	a,(OFST+0,sp)
1021  00af 5b01          	addw	sp,#1
1022  00b1 81            	ret
1045                     ; 306 void SPI_ClearFlag(void)
1045                     ; 307 {
1046                     	switch	.text
1047  00b2               _SPI_ClearFlag:
1051                     ; 309   SPI->SR = (uint8_t)(~SPI_SR_WKUP);
1053  00b2 35f75203      	mov	20995,#247
1054                     ; 310 }
1057  00b6 81            	ret
1139                     ; 323 ITStatus SPI_GetITStatus(SPI_IT_TypeDef SPI_IT)
1139                     ; 324 {
1140                     	switch	.text
1141  00b7               _SPI_GetITStatus:
1143  00b7 88            	push	a
1144  00b8 89            	pushw	x
1145       00000002      OFST:	set	2
1148                     ; 325   ITStatus pendingbitstatus = RESET;
1150  00b9 7b02          	ld	a,(OFST+0,sp)
1151  00bb 97            	ld	xl,a
1152                     ; 326   uint8_t itpos = 0;
1154  00bc 7b01          	ld	a,(OFST-1,sp)
1155  00be 97            	ld	xl,a
1156                     ; 327   uint8_t itmask1 = 0;
1158  00bf 7b02          	ld	a,(OFST+0,sp)
1159  00c1 97            	ld	xl,a
1160                     ; 328   uint8_t itmask2 = 0;
1162  00c2 7b02          	ld	a,(OFST+0,sp)
1163  00c4 97            	ld	xl,a
1164                     ; 329   uint8_t enablestatus = 0;
1166  00c5 7b02          	ld	a,(OFST+0,sp)
1167  00c7 97            	ld	xl,a
1168                     ; 330   assert_param(IS_SPI_GET_IT(SPI_IT));
1170                     ; 332   itpos = (uint8_t)((uint8_t)1 << ((uint8_t)SPI_IT & (uint8_t)0x0F));
1172  00c8 7b03          	ld	a,(OFST+1,sp)
1173  00ca a40f          	and	a,#15
1174  00cc 5f            	clrw	x
1175  00cd 97            	ld	xl,a
1176  00ce a601          	ld	a,#1
1177  00d0 5d            	tnzw	x
1178  00d1 2704          	jreq	L63
1179  00d3               L04:
1180  00d3 48            	sll	a
1181  00d4 5a            	decw	x
1182  00d5 26fc          	jrne	L04
1183  00d7               L63:
1184  00d7 6b01          	ld	(OFST-1,sp),a
1185                     ; 335   itmask1 = (uint8_t)((uint8_t)SPI_IT >> (uint8_t)4);
1187  00d9 7b03          	ld	a,(OFST+1,sp)
1188  00db 4e            	swap	a
1189  00dc a40f          	and	a,#15
1190  00de 6b02          	ld	(OFST+0,sp),a
1191                     ; 337   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
1193  00e0 7b02          	ld	a,(OFST+0,sp)
1194  00e2 5f            	clrw	x
1195  00e3 97            	ld	xl,a
1196  00e4 a601          	ld	a,#1
1197  00e6 5d            	tnzw	x
1198  00e7 2704          	jreq	L24
1199  00e9               L44:
1200  00e9 48            	sll	a
1201  00ea 5a            	decw	x
1202  00eb 26fc          	jrne	L44
1203  00ed               L24:
1204  00ed 6b02          	ld	(OFST+0,sp),a
1205                     ; 339   enablestatus = (uint8_t)((uint8_t)SPI->SR & itmask2);
1207  00ef c65203        	ld	a,20995
1208  00f2 1402          	and	a,(OFST+0,sp)
1209  00f4 6b02          	ld	(OFST+0,sp),a
1210                     ; 341   if (((SPI->ICR & itpos) != (uint8_t)RESET) && enablestatus)
1212  00f6 c65202        	ld	a,20994
1213  00f9 1501          	bcp	a,(OFST-1,sp)
1214  00fb 270a          	jreq	L145
1216  00fd 0d02          	tnz	(OFST+0,sp)
1217  00ff 2706          	jreq	L145
1218                     ; 344     pendingbitstatus = SET;
1220  0101 a601          	ld	a,#1
1221  0103 6b02          	ld	(OFST+0,sp),a
1223  0105 2002          	jra	L345
1224  0107               L145:
1225                     ; 349     pendingbitstatus = RESET;
1227  0107 0f02          	clr	(OFST+0,sp)
1228  0109               L345:
1229                     ; 352   return  pendingbitstatus;
1231  0109 7b02          	ld	a,(OFST+0,sp)
1234  010b 5b03          	addw	sp,#3
1235  010d 81            	ret
1259                     ; 367 void SPI_ClearITPendingBit(void)
1259                     ; 368 {
1260                     	switch	.text
1261  010e               _SPI_ClearITPendingBit:
1265                     ; 370   SPI->SR = (uint8_t)(~SPI_SR_WKUP);
1267  010e 35f75203      	mov	20995,#247
1268                     ; 371 }
1271  0112 81            	ret
1284                     	xdef	_SPI_ClearITPendingBit
1285                     	xdef	_SPI_ClearFlag
1286                     	xdef	_SPI_GetITStatus
1287                     	xdef	_SPI_GetFlagStatus
1288                     	xdef	_SPI_ReceiveData
1289                     	xdef	_SPI_SendData
1290                     	xdef	_SPI_BiDirectionalLineConfig
1291                     	xdef	_SPI_NSSInternalSoftwareCmd
1292                     	xdef	_SPI_ITConfig
1293                     	xdef	_SPI_Cmd
1294                     	xdef	_SPI_Init
1295                     	xdef	_SPI_DeInit
1314                     	end
