#include "delay.h"

/**
  * @brief :1MS��ʱ����
  * @param :
  * @note  :12MHz ��1MS��ʱ
  * @retval:��
  */
void delay_1ms() {
	uint16_t Ms = 1;
	uint32_t j = 80;

	while(Ms--) {
		while(j--);
	}
}

/**
  * @brief :MS��ʱ����
  * @param :
  *			@Ms:��ʱ��MS��
  * @note  :��
  * @retval:��
  */
void delay_ms(uint16_t Ms) {
	while(Ms--) {
		delay_1ms();
	}
}