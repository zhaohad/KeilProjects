#include "typedef.h"
#include "gpio.h"

void	GPIO_config() {
	GPIO_InitTypeDef GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);	//��ʼ��

	GPIO_InitStructure.Pin = GPIO_Pin_All;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);	//��ʼ��
}

void main() {
	GPIO_config();
	P55 = 0;
	P54 = 0;
	P33 = 0;
	P32 = 1;
	while(1);
	return;
}