#include "action_def.h"


// 角度 X 6 X 2, 一步周期数，每步步距角度
u8 code ACT_FORWORD[CNT_ACTION_FORWARD][CNT_ITEM_PER_ACTION] = {
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5, 
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5, 
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5, 
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	75, 	75, 	150, 135, 0, 0, 	105, 	105, 150, 135, 0, 0, 1, 5,
	75, 	75, 	135, 135, 0, 0, 	105, 	105, 135, 135, 0, 0, 1, 5,
	105, 	105, 	135, 150, 0, 0, 	75, 	75, 135, 150, 0, 0, 1, 5,
	105, 	105, 	135, 135, 0, 0, 	75, 	75, 135, 135, 0, 0, 1, 5,
	
	90, 90, 135, 135, 0, 0, 90, 90, 135, 135, 0, 0, 1, 5,
};