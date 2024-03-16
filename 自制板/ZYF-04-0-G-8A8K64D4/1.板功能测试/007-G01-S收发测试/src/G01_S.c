#include "G01_S.h"
#include "delay.h"
#include "STC8A_GPIO.h"

/**
  * @brief :NRF24L01��ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void NRF24L01_Gpio_Init() {
	//�������� ����51��Ƭ������Ҫ 
	//CE ����Ϊ��� IRQ����Ϊ����
	RF24L01_CE = 1;
	RF24L01_CE = 0;				//ʹ���豸
	RF24L01_IRQ = 1;			//���ж�
	RF24L01_SET_CSN_HIGH();		//ȡ��SPIƬѡ
}


/**
  * @brief :NRF24L01���
  * @param :��
  * @note  :��
  * @retval:��
  */ 
bit NRF24L01_check() {
	bit exist = 0;
	xdata uint8_t cnt = 5;
	xdata uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
	xdata uint8_t read_buf[5] = {0};
	 
	while(cnt--) {
		xdata uint8_t i;
		NRF24L01_Write_Buf(TX_ADDR, buf, 5); //д��5���ֽڵĵ�ַ
		NRF24L01_Read_Buf(TX_ADDR, read_buf, 5); //����д��ĵ�ַ  
		for(i = 0; i < 5; i++) {
			if(buf[i] != read_buf[i]) {
				break; //������ֵ��д����ò�ͬ
			}	
		}

		if(5 == i) {
			exist = 1;
			break; //�������ַ�����д����ַ�����ͬ���ж�Ϊ�豸����
		}
		delay_ms(500);//500MS���һ��
	}
	return exist;
}


/**
  * @brief :NRF24L01дָ�����ȵ�����
  * @param :
  *			@reg:��ַ
  *			@pBuf:д������ݵ�ַ
  *			@len:���ݳ���
  * @note  :���ݳ��Ȳ�����255����ַ���豸����Ч
  * @retval:д״̬
  */
void NRF24L01_Write_Buf(uint8_t RegAddr, uint8_t * pBuf, uint8_t len) {
	xdata uint8_t i;
  RF24L01_SET_CSN_LOW(); //Ƭѡ
	
	spi_read_write_byte(NRF_WRITE_REG | RegAddr); //д���� ��ַ
  for(i = 0; i < len; i++) {
		spi_read_write_byte(*(pBuf + i)); //д����
  }
		
  RF24L01_SET_CSN_HIGH(); //ȡ��Ƭѡ
}


/**
  * @brief :NRF24L01��ָ�����ȵ�����
  * @param :
  *			@reg:��ַ
  *			@pBuf:���ݴ�ŵ�ַ
  *			@len:���ݳ���
  * @note  :���ݳ��Ȳ�����255����ַ���豸����Ч
  * @retval:��ȡ״̬
  */
void NRF24L01_Read_Buf(uint8_t RegAddr, uint8_t *pBuf, uint8_t len) {
    xdata uint8_t btmp;
	
    RF24L01_SET_CSN_LOW(); //Ƭѡ
	
    spi_read_write_byte(NRF_READ_REG | RegAddr); //������ ��ַ
    for(btmp = 0; btmp < len; btmp++) {
			*(pBuf + btmp) = spi_read_write_byte(0xFF);	//������
    }
    RF24L01_SET_CSN_HIGH(); //ȡ��Ƭѡ
}

 /**
  * @brief :RF24L01ģ���ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void RF24L01_Init() {
	xdata uint8_t addr[5] = {INIT_ADDR};
	RF24L01_SET_CE_HIGH();
	NRF24L01_Clear_IRQ_Flag(IRQ_ALL);

	NRF24L01_Write_Reg(DYNPD, (1 << 0)); //ʹ��ͨ��1��̬���ݳ���
	NRF24L01_Write_Reg(FEATRUE, 0x07);
	NRF24L01_Read_Reg(DYNPD);
	NRF24L01_Read_Reg(FEATRUE);

	NRF24L01_Write_Reg(CONFIG, /*(1<<MASK_RX_DR) |*/  //�����ж�
                               (1 << EN_CRC)   //ʹ��CRC 1���ֽ�
                             | (1 << PWR_UP)); //�����豸
	NRF24L01_Write_Reg(EN_AA, (1 << ENAA_P0)); //ͨ��0�Զ�Ӧ��
	NRF24L01_Write_Reg(EN_RXADDR, (1 << ERX_P0)); //ͨ��0����
	NRF24L01_Write_Reg(SETUP_AW, AW_5BYTES); //��ַ��� 5���ֽ�
	NRF24L01_Write_Reg(SETUP_RETR, ARD_4000US
                 	| (REPEAT_CNT & 0x0F)); //�ظ��ȴ�ʱ�� 250us
	NRF24L01_Write_Reg(RF_CH, 60); //��ʼ��ͨ��
	NRF24L01_Write_Reg(RF_SETUP, 0x26);

	NRF24L01_Set_TxAddr(&addr[0], 5); //����TX��ַ
	NRF24L01_Set_RxAddr(0, &addr[0], 5); //����RX��ַ
}

/**
  * @brief :NRF24L01���ж�
  * @param :
           @IRQ_Source:�ж�Դ
  * @note  :��
  * @retval:�����״̬�Ĵ�����ֵ
  */
uint8_t NRF24L01_Clear_IRQ_Flag(uint8_t IRQ_Source) {
	xdata uint8_t btmp = 0;

	IRQ_Source &= (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT); //�жϱ�־����
	btmp = NRF24L01_Read_Status_Register(); //��״̬�Ĵ���

	RF24L01_SET_CSN_LOW();			//Ƭѡ
  spi_read_write_byte(NRF_WRITE_REG + STATUS); //д״̬�Ĵ�������
	spi_read_write_byte(IRQ_Source | btmp); //����Ӧ�жϱ�־
  RF24L01_SET_CSN_HIGH(); //ȡ��Ƭѡ
	
	return (NRF24L01_Read_Status_Register()); //����״̬�Ĵ���״̬
}

/**
  * @brief :NRF24L01��״̬�Ĵ���
  * @param :��
  * @note  :��
  * @retval:RF24L01״̬
  */
uint8_t NRF24L01_Read_Status_Register() {
	xdata uint8_t Status;
	RF24L01_SET_CSN_LOW(); //Ƭѡ
	Status = spi_read_write_byte(NRF_READ_REG + STATUS); //��״̬�Ĵ���
	RF24L01_SET_CSN_HIGH(); //ȡ��Ƭѡ
	return Status;
}

/**
  * @brief :NRF24L01д�Ĵ���
  * @param :��
  * @note  :��ַ���豸����Ч
  * @retval:��д״̬
  */
void NRF24L01_Write_Reg(uint8_t RegAddr, uint8_t Value) {
	RF24L01_SET_CSN_LOW( ); //Ƭѡ
	spi_read_write_byte(NRF_WRITE_REG | RegAddr); //д���� ��ַ
	spi_read_write_byte(Value); //д����
  RF24L01_SET_CSN_HIGH(); //ȡ��Ƭѡ
}

/**
  * @brief :NRF24L01���Ĵ���
  * @param :
           @Addr:�Ĵ�����ַ
  * @note  :��ַ���豸����Ч
  * @retval:��ȡ������
  */
uint8_t NRF24L01_Read_Reg(uint8_t RegAddr) {
	xdata uint8_t btmp;
	RF24L01_SET_CSN_LOW(); //Ƭѡ
	spi_read_write_byte(NRF_READ_REG | RegAddr); //������ ��ַ
	btmp = spi_read_write_byte(0xFF); //������
	RF24L01_SET_CSN_HIGH( ); //ȡ��Ƭѡ
  return btmp;
}

 /**
  * @brief :���÷��͵�ַ
  * @param :
  *			@pAddr:��ַ��ŵ�ַ
  *			@len:����
  * @note  :��
  * @retval:��
  */
void NRF24L01_Set_TxAddr(uint8_t *pAddr, uint8_t len) {
	len = (len > 5) ? 5 : len; //��ַ���ܴ���5���ֽ�
	NRF24L01_Write_Buf(TX_ADDR, pAddr, len); //д��ַ
}

 /**
  * @brief :���ý���ͨ����ַ
  * @param :
  *			@PipeNum:ͨ��
  *			@pAddr:��ַ����ŵ�ַ
  *			@Len:����
  * @note  :ͨ��������5 ��ַ���Ȳ�����5���ֽ�
  * @retval:��
  */
void NRF24L01_Set_RxAddr(uint8_t PipeNum, uint8_t *pAddr, uint8_t Len) {
	Len = (Len > 5) ? 5 : Len;
	PipeNum = (PipeNum > 5) ? 5 : PipeNum; //ͨ��������5 ��ַ���Ȳ�����5���ֽ�
	NRF24L01_Write_Buf(RX_ADDR_P0 + PipeNum, pAddr, Len ); //д���ַ
}

 /**
  * @brief :����ģʽ
  * @param :
  *			@Mode:ģʽ����ģʽ�����ģʽ
  * @note  :��
  * @retval:��
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
  * @brief :NRF24L01����һ������
  * @param :
  *			@txbuf:�����������׵�ַ
  *			@Length:�������ݳ���
  * @note  :��
  * @retval:
  *			MAX_TX���ﵽ����ط�����
  *			TX_OK���������
  *			0xFF:����ԭ��
  */ 
uint8_t NRF24L01_TxPacket(uint8_t * txbuf, uint8_t Length) {
	xdata uint8_t l_Status = 0;
	xdata uint16_t l_MsTimes = 0;

	RF24L01_SET_CSN_LOW(); //Ƭѡ
	spi_read_write_byte(FLUSH_TX);
	RF24L01_SET_CSN_HIGH();

	RF24L01_SET_CE_LOW();		
	NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, Length); //д���ݵ�TX BUF 32�ֽ�  TX_PLOAD_WIDTH
	RF24L01_SET_CE_HIGH(); //��������
	while(0 != RF24L01_GET_IRQ_STATUS()) {
		delay_ms(1);
		if(500 == l_MsTimes++) { //500ms��û�з��ͳɹ������³�ʼ���豸
			NRF24L01_Gpio_Init();
			RF24L01_Init();
			RF24L01_Set_Mode( MODE_TX );
			break;
		}
	}
	l_Status = NRF24L01_Read_Reg(STATUS); //��״̬�Ĵ���
	NRF24L01_Write_Reg(STATUS, l_Status); //���TX_DS��MAX_RT�жϱ�־
	
	if(l_Status & MAX_TX) { //�ﵽ����ط�����
		NRF24L01_Write_Reg( FLUSH_TX,0xff ); //���TX FIFO�Ĵ���
		return MAX_TX;
	}

	if(l_Status & TX_OK) { //�������
		return TX_OK;
	}

	return 0xFF;	//����ԭ����ʧ��
}

/**
  * @brief :NRF24L01��������
  * @param :
  *			@rxbuf:�������ݴ�ŵ�ַ
  * @note  :��
  * @retval:
  *			0:�������
  *			1:û�н��յ�����
  */ 
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf) {
	xdata uint8_t l_Status = 0, l_RxLength = 0, l_100MsTimes = 0;
	
	RF24L01_SET_CSN_LOW(); //Ƭѡ
	spi_read_write_byte(FLUSH_RX);
	RF24L01_SET_CSN_HIGH();
	
	while(0 != RF24L01_GET_IRQ_STATUS()) {
		delay_ms(100);

		if(30 == l_100MsTimes++) { //3sû���չ����ݣ����³�ʼ��ģ��
			NRF24L01_Gpio_Init();
			RF24L01_Init();
			RF24L01_Set_Mode(MODE_RX);
			break;
		}
	}
	
	l_Status = NRF24L01_Read_Reg(STATUS); //��״̬�Ĵ���
	NRF24L01_Write_Reg(STATUS, l_Status); //���жϱ�־
	if(l_Status & RX_OK) { //���յ�����
		l_RxLength = NRF24L01_Read_Reg(R_RX_PL_WID); //��ȡ���յ������ݸ���
		NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, l_RxLength );	//���յ����� 
		NRF24L01_Write_Reg(FLUSH_RX, 0xff);				//���RX FIFO
		return l_RxLength;
	}	

	return 0;				//û���յ�����	
}