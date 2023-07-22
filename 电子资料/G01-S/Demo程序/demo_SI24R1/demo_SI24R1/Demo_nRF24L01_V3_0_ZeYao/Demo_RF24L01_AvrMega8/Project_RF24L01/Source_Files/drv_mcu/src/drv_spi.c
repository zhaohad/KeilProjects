/**
  ******************************************************************************
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  * 
  * 
  ******************************************************************************
  */



#include "drv_spi.h"


#ifndef __USE_SOFT_SPI_INTERFACE__
/** Ӳ��SPI */


/**
  * @brief :SPI��ʼ��(Ӳ��)
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void drv_spi_init( void )
{
	/** ������������ */
	//SCK MOSI NSS����Ϊ��� MISO����Ϊ����
	SPI_CLK_GPIO_ODR |= 0x01 << SPI_CLK_GPIO_BIT;						//��λ��Ӧ��ODR ����Ϊ���
	SPI_MOSI_GPIO_ODR |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_ODR |= 0x01 << SPI_NSS_GPIO_BIT;
	SPI_MISO_GPIO_ODR &= (uint8_t)( ~( 0x01 << SPI_MISO_GPIO_BIT ));	//������Ӧ��ODR ����Ϊ����
	
	//SCK��ʼ״̬����Ϊ�� MOSI NSS��ʼ״̬����Ϊ��
	SPI_CLK_GPIO_PORT &= (uint8_t)( ~( 0x01 << SPI_CLK_GPIO_BIT ));		//��0 PORT�����
	SPI_MOSI_GPIO_PORT |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_PORT |= 0x01 << SPI_NSS_GPIO_BIT;						//��1 PORT�����
	
	/** SPI�������� */
	SPCR &= (uint8_t)( ~( 0x01 << SPE ));	//�ر�SPI
	SPCR &= (uint8_t)( ~(( 0x01 << SPIE ) | ( 0x01 << DORD ) | ( 0x01 << CPOL ) | ( 0x01 << CPHA )));	//���ж� MSB��ǰ CPOL = CPHA = 0( ���е͵�ƽ ��һ���زɼ����� )
	//ʱ��4��Ƶ
	SPCR &= (uint8_t)( ~(( 0x01 << SPR0 ) | ( 0x01 << SPR1 )));
	SPSR  = 0x00;							
	SPCR |= 0x01 << MSTR;					//����ģʽ
	SPCR |= 0x01 << SPE;					//ʹ��SPI
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :��
  * @retval:���յ����ֽ�
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	SPDR = TxByte;					//��������
	while( 0x00 == ( SPSR & ( 0x01 << SPIF )));	//�ȴ����ݴ������
	return ( (uint8_t)SPDR );		//���ؽ��յ�������
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :��
  * @retval:��
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	spi_set_nss_low( );			//����Ƭѡ
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;			//��д��ַ��1
	}
	spi_set_nss_high( );		//����Ƭѡ
}

/** Ӳ��SPI */



#else



/** ���SPI */


/**
  * @brief :SPI��ʼ��(���)
  * @param :��
  * @note  :��
  * @retval:��
  */
void drv_spi_init( void )
{
	//SCK MOSI NSS����Ϊ��� MISO����Ϊ����
	SPI_CLK_GPIO_ODR |= 0x01 << SPI_CLK_GPIO_BIT;						//��λ��Ӧ��ODR ����Ϊ���
	SPI_MOSI_GPIO_ODR |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_ODR |= 0x01 << SPI_NSS_GPIO_BIT;
	SPI_MISO_GPIO_ODR &= (uint8_t)( ~( 0x01 << SPI_MISO_GPIO_BIT ));	//������Ӧ��ODR ����Ϊ����
	
	//SCK��ʼ״̬����Ϊ�� MOSI NSS��ʼ״̬����Ϊ��
	SPI_CLK_GPIO_PORT &= (uint8_t)( ~( 0x01 << SPI_CLK_GPIO_BIT ));		//��0 PORT�����
	SPI_MOSI_GPIO_PORT |= 0x01 << SPI_MOSI_GPIO_BIT;
	SPI_NSS_GPIO_PORT |= 0x01 << SPI_NSS_GPIO_BIT;						//��1 PORT�����
	
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t i = 0, Data = 0;
	
	spi_set_clk_low( );
	
	for( i = 0; i < 8; i++ )			//һ���ֽ�8byte��Ҫѭ��8��
	{
		/** ���� */
		if( 0x80 == ( TxByte & 0x80 ))
		{
			spi_set_mosi_hight( );		//�������Ҫ���͵�λΪ 1 ���ø�IO����
		}
		else
		{
			spi_set_mosi_low( );		//�������Ҫ���͵�λΪ 0 ���õ�IO����
		}
		TxByte <<= 1;					//��������һλ���ȷ��͵������λ
		
		spi_set_clk_high( );			//ʱ�����ø�
//		__nop( );
//		__nop( );
		
		/** ���� */
		Data <<= 1;						//������������һλ���Ƚ��յ��������λ
		if( 1 == spi_get_miso( ))
		{
			Data |= 0x01;				//�������ʱIO����Ϊ������Ϊ���յ� 1
		}
		
		spi_set_clk_low( );				//ʱ�����õ�
//		__nop( );
//		__nop( );
	}
	
	return Data;		//���ؽ��յ����ֽ�
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	spi_set_nss_low( );			//Ƭѡ����
	
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;			//��д��ַ��1
	}
	
	spi_set_nss_high( );		//Ƭѡ����
}


/** ���SPI */
#endif


