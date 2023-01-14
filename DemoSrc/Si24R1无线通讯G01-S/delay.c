#include "delay.h"

/**
  * @brief :1MS延时函数
  * @param :
  * @note  :12MHz 下1MS延时
  * @retval:无
  */
void delay_1ms() {
	uint16_t Ms = 1;
	uint32_t j = 80;

	while(Ms--) {
		while(j--);
	}
}

/**
  * @brief :MS延时函数
  * @param :
  *			@Ms:延时的MS数
  * @note  :无
  * @retval:无
  */
void delay_ms(uint16_t Ms) {
	while(Ms--) {
		delay_1ms();
	}
}