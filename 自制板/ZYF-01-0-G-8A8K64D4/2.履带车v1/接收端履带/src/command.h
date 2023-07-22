#ifndef __COMMAND_H__
#define __COMMAND_H__

#define NONE_COMMAND 0x00

#define MODE_COMMAND 0x20
#define MODE_LVDAI 0x00
#define MODE_KONGZHI 0x01

// right forward and backward
#define ADC_COMMAND_0 0x10
// right leftward and rightward
#define ADC_COMMAND_1 ADC_COMMAND_0 + 1
// left forward and backward
#define ADC_COMMAND_2 ADC_COMMAND_0 + 2
// left leftward and rightward
#define ADC_COMMAND_3 ADC_COMMAND_0 + 3

#define ADC_NONE_VALUE 50

#define FORWARD_THRESHOLD 75
#define BACKWARD_THRESHOLD 25

#endif