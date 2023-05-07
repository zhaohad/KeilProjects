#include "test.h"
#include "oled12864.h"

void Test_All() {
	while (1) {
		Test_Interruption_Check(0);
	}
}

void Test_Interruption_Check(u8 line) {
	if (P_INT) {
		OLED_ShowString8(0, line, "Not interrupted");
	} else if (!P_INT) {
		OLED_ShowString8(0, line, "interrupted!!!!");
	}
}