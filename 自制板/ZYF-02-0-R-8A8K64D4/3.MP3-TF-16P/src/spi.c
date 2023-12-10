#include <intrins.h>
#include "spi.h"

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t spi_read_write_byte(uint8_t TxByte) {
	xdata uint8_t i = 0, Data = 0;
	
	spi_set_clk_low();

	for(i = 0; i < 8; i++ ) { //һ���ֽ�8byte��Ҫѭ��8��
		/** ���� */
		if(0x80 == (TxByte & 0x80)) {
			spi_set_mosi_hight(); //�������Ҫ���͵�λΪ 1 ���ø�IO����
		} else {
			spi_set_mosi_low(); //�������Ҫ���͵�λΪ 0 ���õ�IO����
		}
		TxByte <<= 1; //��������һλ���ȷ��͵������λ
		spi_set_clk_high(); //ʱ�����ø�
		_nop_();

		/** ���� */
		Data <<= 1; //������������һλ���Ƚ��յ��������λ
		if(1 == spi_get_miso()) {
			Data |= 0x01; //�������ʱIO����Ϊ������Ϊ���յ� 1
		}

		spi_set_clk_low(); //ʱ�����õ�
		_nop_();
	}

	return Data;		//���ؽ��յ����ֽ�
}