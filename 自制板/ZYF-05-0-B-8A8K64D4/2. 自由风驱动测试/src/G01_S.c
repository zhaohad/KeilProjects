#include "G01_S.h"
#include "delay.h"
#include "STC8A_GPIO.h"

/**
  * @brief :NRF24L01初始化
  * @param :无
  * @note  :无
  * @retval:无
  */ 
void NRF24L01_Gpio_Init() {
	//引脚配置 部分51单片机不需要 
	//CE 配置为输出 IRQ配置为输入
	RF24L01_CE = 1;
	RF24L01_CE = 0;				//使能设备
	RF24L01_IRQ = 1;			//清中断
	RF24L01_SET_CSN_HIGH();		//取消SPI片选
}


/**
  * @brief :NRF24L01检测
  * @param :无
  * @note  :无
  * @retval:无
  */ 
bit NRF24L01_check() {
	bit exist = 0;
	xdata uint8_t cnt = 5;
	xdata uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
	xdata uint8_t read_buf[5] = {0};
	 
	while(cnt--) {
		xdata uint8_t i;
		NRF24L01_Write_Buf(TX_ADDR, buf, 5); //写入5个字节的地址
		NRF24L01_Read_Buf(TX_ADDR, read_buf, 5); //读出写入的地址  
		for(i = 0; i < 5; i++) {
			if(buf[i] != read_buf[i]) {
				break; //读出的值和写入的置不同
			}	
		}

		if(5 == i) {
			exist = 1;
			break; //读出的字符串与写入的字符串相同，判断为设备存在
		}
		delay_ms(500);//500MS检测一次
	}
	return exist;
}


/**
  * @brief :NRF24L01写指定长度的数据
  * @param :
  *			@reg:地址
  *			@pBuf:写入的数据地址
  *			@len:数据长度
  * @note  :数据长度不超过255，地址在设备中有效
  * @retval:写状态
  */
void NRF24L01_Write_Buf(uint8_t RegAddr, uint8_t * pBuf, uint8_t len) {
	xdata uint8_t i;
  RF24L01_SET_CSN_LOW(); //片选
	
	spi_read_write_byte(NRF_WRITE_REG | RegAddr); //写命令 地址
  for(i = 0; i < len; i++) {
		spi_read_write_byte(*(pBuf + i)); //写数据
  }
		
  RF24L01_SET_CSN_HIGH(); //取消片选
}


/**
  * @brief :NRF24L01读指定长度的数据
  * @param :
  *			@reg:地址
  *			@pBuf:数据存放地址
  *			@len:数据长度
  * @note  :数据长度不超过255，地址在设备中有效
  * @retval:读取状态
  */
void NRF24L01_Read_Buf(uint8_t RegAddr, uint8_t *pBuf, uint8_t len) {
    xdata uint8_t btmp;
	
    RF24L01_SET_CSN_LOW(); //片选
	
    spi_read_write_byte(NRF_READ_REG | RegAddr); //读命令 地址
    for(btmp = 0; btmp < len; btmp++) {
			*(pBuf + btmp) = spi_read_write_byte(0xFF);	//读数据
    }
    RF24L01_SET_CSN_HIGH(); //取消片选
}

 /**
  * @brief :RF24L01模块初始化
  * @param :无
  * @note  :无
  * @retval:无
  */
void RF24L01_Init() {
	xdata uint8_t addr[5] = {INIT_ADDR};
	RF24L01_SET_CE_HIGH();
	NRF24L01_Clear_IRQ_Flag(IRQ_ALL);

	NRF24L01_Write_Reg(DYNPD, (1 << 0)); //使能通道1动态数据长度
	NRF24L01_Write_Reg(FEATRUE, 0x07);
	NRF24L01_Read_Reg(DYNPD);
	NRF24L01_Read_Reg(FEATRUE);

	NRF24L01_Write_Reg(CONFIG, /*(1<<MASK_RX_DR) |*/  //接收中断
                               (1 << EN_CRC)   //使能CRC 1个字节
                             | (1 << PWR_UP)); //开启设备
	NRF24L01_Write_Reg(EN_AA, (1 << ENAA_P0)); //通道0自动应答
	NRF24L01_Write_Reg(EN_RXADDR, (1 << ERX_P0)); //通道0接收
	NRF24L01_Write_Reg(SETUP_AW, AW_5BYTES); //地址宽度 5个字节
	NRF24L01_Write_Reg(SETUP_RETR, ARD_4000US
                 	| (REPEAT_CNT & 0x0F)); //重复等待时间 250us
	NRF24L01_Write_Reg(RF_CH, 60); //初始化通道
	NRF24L01_Write_Reg(RF_SETUP, 0x26);

	NRF24L01_Set_TxAddr(&addr[0], 5); //设置TX地址
	NRF24L01_Set_RxAddr(0, &addr[0], 5); //设置RX地址
}

/**
  * @brief :NRF24L01清中断
  * @param :
           @IRQ_Source:中断源
  * @note  :无
  * @retval:清除后状态寄存器的值
  */
uint8_t NRF24L01_Clear_IRQ_Flag(uint8_t IRQ_Source) {
	xdata uint8_t btmp = 0;

	IRQ_Source &= (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT); //中断标志处理
	btmp = NRF24L01_Read_Status_Register(); //读状态寄存器

	RF24L01_SET_CSN_LOW();			//片选
  spi_read_write_byte(NRF_WRITE_REG + STATUS); //写状态寄存器命令
	spi_read_write_byte(IRQ_Source | btmp); //清相应中断标志
  RF24L01_SET_CSN_HIGH(); //取消片选
	
	return (NRF24L01_Read_Status_Register()); //返回状态寄存器状态
}

/**
  * @brief :NRF24L01读状态寄存器
  * @param :无
  * @note  :无
  * @retval:RF24L01状态
  */
uint8_t NRF24L01_Read_Status_Register() {
	xdata uint8_t Status;
	RF24L01_SET_CSN_LOW(); //片选
	Status = spi_read_write_byte(NRF_READ_REG + STATUS); //读状态寄存器
	RF24L01_SET_CSN_HIGH(); //取消片选
	return Status;
}

/**
  * @brief :NRF24L01写寄存器
  * @param :无
  * @note  :地址在设备中有效
  * @retval:读写状态
  */
void NRF24L01_Write_Reg(uint8_t RegAddr, uint8_t Value) {
	RF24L01_SET_CSN_LOW( ); //片选
	spi_read_write_byte(NRF_WRITE_REG | RegAddr); //写命令 地址
	spi_read_write_byte(Value); //写数据
  RF24L01_SET_CSN_HIGH(); //取消片选
}

/**
  * @brief :NRF24L01读寄存器
  * @param :
           @Addr:寄存器地址
  * @note  :地址在设备中有效
  * @retval:读取的数据
  */
uint8_t NRF24L01_Read_Reg(uint8_t RegAddr) {
	xdata uint8_t btmp;
	RF24L01_SET_CSN_LOW(); //片选
	spi_read_write_byte(NRF_READ_REG | RegAddr); //读命令 地址
	btmp = spi_read_write_byte(0xFF); //读数据
	RF24L01_SET_CSN_HIGH( ); //取消片选
  return btmp;
}

 /**
  * @brief :设置发送地址
  * @param :
  *			@pAddr:地址存放地址
  *			@len:长度
  * @note  :无
  * @retval:无
  */
void NRF24L01_Set_TxAddr(uint8_t *pAddr, uint8_t len) {
	len = (len > 5) ? 5 : len; //地址不能大于5个字节
	NRF24L01_Write_Buf(TX_ADDR, pAddr, len); //写地址
}

 /**
  * @brief :设置接收通道地址
  * @param :
  *			@PipeNum:通道
  *			@pAddr:地址存肥着地址
  *			@Len:长度
  * @note  :通道不大于5 地址长度不大于5个字节
  * @retval:无
  */
void NRF24L01_Set_RxAddr(uint8_t PipeNum, uint8_t *pAddr, uint8_t Len) {
	Len = (Len > 5) ? 5 : Len;
	PipeNum = (PipeNum > 5) ? 5 : PipeNum; //通道不大于5 地址长度不大于5个字节
	NRF24L01_Write_Buf(RX_ADDR_P0 + PipeNum, pAddr, Len ); //写入地址
}

 /**
  * @brief :设置模式
  * @param :
  *			@Mode:模式发送模式或接收模式
  * @note  :无
  * @retval:无
  */
void RF24L01_Set_Mode(nRf24l01ModeType Mode) {
	xdata uint8_t controlreg = 0;
	controlreg = NRF24L01_Read_Reg(CONFIG);
	if (Mode == MODE_TX) {
		controlreg &= ~(1<< PRIM_RX);
	} else if (Mode == MODE_RX) { 
		controlreg |= (1 << PRIM_RX); 
	}
	NRF24L01_Write_Reg(CONFIG, controlreg);
}

/**
  * @brief :NRF24L01发送一次数据
  * @param :
  *			@txbuf:待发送数据首地址
  *			@Length:发送数据长度
  * @note  :无
  * @retval:
  *			MAX_TX：达到最大重发次数
  *			TX_OK：发送完成
  *			0xFF:其他原因
  */ 
uint8_t NRF24L01_TxPacket(uint8_t * txbuf, uint8_t Length) {
	xdata uint8_t l_Status = 0;
	xdata uint16_t l_MsTimes = 0;

	RF24L01_SET_CSN_LOW(); //片选
	spi_read_write_byte(FLUSH_TX);
	RF24L01_SET_CSN_HIGH();

	RF24L01_SET_CE_LOW();		
	NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, Length); //写数据到TX BUF 32字节  TX_PLOAD_WIDTH
	RF24L01_SET_CE_HIGH(); //启动发送
	while(0 != RF24L01_GET_IRQ_STATUS()) {
		delay_ms(1);
		if(500 == l_MsTimes++) { //500ms还没有发送成功，重新初始化设备
			NRF24L01_Gpio_Init();
			RF24L01_Init();
			RF24L01_Set_Mode( MODE_TX );
			break;
		}
	}
	l_Status = NRF24L01_Read_Reg(STATUS); //读状态寄存器
	NRF24L01_Write_Reg(STATUS, l_Status); //清除TX_DS或MAX_RT中断标志
	
	if(l_Status & MAX_TX) { //达到最大重发次数
		NRF24L01_Write_Reg( FLUSH_TX,0xff ); //清除TX FIFO寄存器
		return MAX_TX;
	}

	if(l_Status & TX_OK) { //发送完成
		return TX_OK;
	}

	return 0xFF;	//其他原因发送失败
}

/**
  * @brief :NRF24L01接收数据
  * @param :
  *			@rxbuf:接收数据存放地址
  * @note  :无
  * @retval:
  *			0:接收完成
  *			1:没有接收到数据
  */ 
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf) {
	xdata uint8_t l_Status = 0, l_RxLength = 0, l_100MsTimes = 0;
	
	RF24L01_SET_CSN_LOW(); //片选
	spi_read_write_byte(FLUSH_RX);
	RF24L01_SET_CSN_HIGH();
	
	while(0 != RF24L01_GET_IRQ_STATUS()) {
		delay_ms(100);

		if(30 == l_100MsTimes++) { //3s没接收过数据，重新初始化模块
			NRF24L01_Gpio_Init();
			RF24L01_Init();
			RF24L01_Set_Mode(MODE_RX);
			break;
		}
	}
	
	l_Status = NRF24L01_Read_Reg(STATUS); //读状态寄存器
	NRF24L01_Write_Reg(STATUS, l_Status); //清中断标志
	if(l_Status & RX_OK) { //接收到数据
		l_RxLength = NRF24L01_Read_Reg(R_RX_PL_WID); //读取接收到的数据个数
		NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, l_RxLength );	//接收到数据 
		NRF24L01_Write_Reg(FLUSH_RX, 0xff);				//清除RX FIFO
		return l_RxLength;
	}	

	return 0;				//没有收到数据	
}