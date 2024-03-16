#include "joinstick.h"

#define PU_YAO_FJM10K_S_MID_VALUE 67
#define PU_YAO_FJM10K_S_E 2

u8 JOIN_STICK_Pu_Yao_FJM10K_S_Cal(float v) {
	if (v <= PU_YAO_FJM10K_S_MID_VALUE + PU_YAO_FJM10K_S_E && v >= PU_YAO_FJM10K_S_MID_VALUE - PU_YAO_FJM10K_S_E) {
		return 50;
	} else if (v < PU_YAO_FJM10K_S_MID_VALUE) {
		return (u8) (50.f / PU_YAO_FJM10K_S_MID_VALUE * v + 0.5);
	} else if (v > PU_YAO_FJM10K_S_MID_VALUE) {
		return (u8) (50.f / (100 - PU_YAO_FJM10K_S_MID_VALUE) * v + 100 * (1 - 50.f / (100 - PU_YAO_FJM10K_S_MID_VALUE)) + 0.5);
	}
	return 0;
}