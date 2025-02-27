#include "action_def.h"

// 角度 X 6 X 2, 一步周期数，每步步距角度
u8 code ACT_TO_INIT[CNT_ACTION_TO_INIT][CNT_ITEM_PER_ACTION] = {
	75, 105, 135, 135, 0, 0, 105, 75, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_FORWORD[CNT_ACTION_FORWARD][CNT_ITEM_PER_ACTION] = {
	60, 	90, 	160, 135, 0, 0, 	120, 	90, 135, 160, 0, 0, 1, 5,
	60, 	90, 	135, 135, 0, 0, 	120, 	90, 135, 135, 0, 0, 1, 5,
	90, 	120, 	135, 160, 0, 0, 	90, 	60, 160, 135, 0, 0, 1, 5, 
	90, 	120, 	135, 135, 0, 0, 	90, 	60, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_BACKWORD[CNT_ACTION_BACKWARD][CNT_ITEM_PER_ACTION] = {
	90, 	120, 	160, 135, 0, 0, 	90, 	60, 135, 160, 0, 0, 1, 5,
	90, 	120, 	135, 135, 0, 0, 	90, 	60, 135, 135, 0, 0, 1, 5,
	60, 	90, 	135, 160, 0, 0, 	120, 	90, 160, 135, 0, 0, 1, 5, 
	60, 	90, 	135, 135, 0, 0, 	120, 	90, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_TURN_LEFT[CNT_ACTION_TURN_LEFT][CNT_ITEM_PER_ACTION] = {
	60, 	120, 	160, 135, 0, 0, 	120, 	60, 135, 160, 0, 0, 1, 5,
	60, 	120, 	135, 135, 0, 0, 	120, 	60, 135, 135, 0, 0, 1, 5,
	90, 	90, 	135, 160, 0, 0, 	90, 	90, 160, 135, 0, 0, 1, 5, 
	90, 	90, 	135, 135, 0, 0, 	90, 	90, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_TURN_RIGHT[CNT_ACTION_TURN_RIGHT][CNT_ITEM_PER_ACTION] = {
	60, 	120, 	135, 160, 0, 0, 	120, 	60, 160, 135, 0, 0, 1, 5,
	60, 	120, 	135, 135, 0, 0, 	120, 	60, 135, 135, 0, 0, 1, 5,
	90, 	90, 	160, 135, 0, 0, 	90, 	90, 135, 160, 0, 0, 1, 5, 
	90, 	90, 	135, 135, 0, 0, 	90, 	90, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_ROCK[CNT_ACTION_ROCK][CNT_ITEM_PER_ACTION] = {
	75, 	105, 	160, 160, 0, 0, 	75, 	105, 160, 160, 0, 0, 1, 5,
	75, 	105, 	135, 135, 0, 0, 	75, 	105, 135, 135, 0, 0, 1, 5,
	105, 	75, 	160, 160, 0, 0, 	105, 	75, 160, 160, 0, 0, 1, 5, 
	105, 	75, 	135, 135, 0, 0, 	105, 	75, 135, 135, 0, 0, 1, 5,
};

u8 code ACT_WANGTIAN[CNT_ACTION_WANGTIAN][CNT_ITEM_PER_ACTION] = {
	75, 105, 0, 0, 120, 120, 105, 75, 130, 130, 5, 5, 1, 5,
	75, 105, 90, 10, 120, 120, 105, 75, 130, 130, 5, 5, 1, 5,
	0, 105, 90, 10, 115, 115, 105, 75, 130, 130, 5, 5, 1, 5,
};

u8 code ACT_DANCE[CNT_ACTION_DANCE][CNT_ITEM_PER_ACTION] = {
	75, 105, 80, 80, 50, 50, 105, 75, 120, 120, 15, 15, 1, 5,
	75, 105, 80, 80, 50, 50, 105, 75, 135, 105, 0, 30, 1, 3,
	75, 105, 80, 80, 50, 50, 105, 75, 120, 120, 15, 15, 1, 3,
	75, 105, 80, 80, 50, 50, 105, 75, 120, 135, 30, 0, 1, 3,
};