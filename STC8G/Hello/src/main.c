#include "typedef.h"
#include "gpio.h"

void	GPIO_config() {
	GPIO_InitTypeDef GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin = GPIO_Pin_All;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);	//初始化

	GPIO_InitStructure.Pin = GPIO_Pin_All;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);	//初始化
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