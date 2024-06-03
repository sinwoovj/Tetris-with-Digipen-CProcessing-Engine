#include "cprocessing.h"
#include <stdio.h>
#include "logic.h"
#include "color.h"
#include <stdlib.h>
#include <time.h>

#define block_cnt 20 // + None

Block blocks[block_cnt] = {
	{ None, 0, -1, 0, NoneColor, {0,0}, {0,0}, {0,0}, 0, 0, 0},
	{ J, 1, 0, 1, Blue, {1,0}, {1,1}, {1,2}, 4, 2, 3		},
	{ J, 2, 0, 2, Blue, {1,0}, {2,0}, {0,1}, 1, 3, 4		},
	{ J, 3, 0, 3, Blue, {0,1}, {0,2}, {1,2}, 2, 4, 1	 	},
	{ J, 4, 0, 4, Blue, {-2,1}, {-1,1}, {0,1}, 3, 1, 2	 	},
	{ L, 5, 1, 1, Orange, {1,0}, {0,1}, {0,2}, 4, 2, 3	 	},
	{ L, 6, 1, 2, Orange, {0,1}, {1,1}, {2,1}, 1, 3, 4	 	},
	{ L, 7, 1, 3, Orange, {0,1}, {-1,2}, {0,2}, 2, 4, 1 	},
	{ L, 8, 1, 4, Orange, {1,0}, {2,0}, {2,1}, 3, 1, 2	 	},
	{ T, 9, 2, 1, Purple, {-1,1}, {0,1}, {1,1}, 4, 2, 3 	},
	{ T, 10, 2, 2, Purple, {-1,1}, {0,1}, {0,2}, 1, 3, 4	},
	{ T, 11, 2, 3, Purple, {1,0}, {2,0}, {1,1}, 2, 4, 1 	},
	{ T, 12, 2, 4, Purple, {0,1}, {1,1}, {0,2}, 3, 1, 2 	},
	{ Z, 13, 3, 1, Red, {1,0}, {-1,1}, {0,1}, 0, 0, 0	 	},
	{ Z, 14, 3, 2, Red, {0,1}, {1,1}, {1,2}, 0, 0, 0	 	},
	{ S, 15, 4, 1, Green, {1,0}, {1,1}, {2,1}, 0, 0, 0	 	},
	{ S, 16, 4, 2, Green, {0,1}, {-1,1}, {-1,2}, 0, 0, 0	},
	{ O, 17, 5, 1, Yellow, {1,0}, {1,0}, {1,1}, 0, 0, 0 	},
	{ I, 18, 6, 1, Sky, {0,1}, {0,2}, {0,3}, 0, 0, 0	 	},
	{ I, 19, 6, 2, Sky, {1,0}, {2,0}, {3,0}, 0, 0, 0	 	}
};
int kind_blocks[7] = {1,5,9,13,15,17,18}; // b_num

Block Get_Block(int num) {
	for (int i = 0; i < block_cnt; i++) {
		if (blocks[i].b_num == num) {
			return blocks[i];
		}
	}
	return blocks[0];
}


void shuffle(int* arr, int num)
{
	srand((unsigned int)time(NULL));
	int temp;
	int rn;
	for (int i = 0; i < num - 1; i++)
	{
		rn = rand() % (num - i) + i;    // i 부터 num-1 사이에 임의의 정수 생성
		temp = arr[i];
		arr[i] = arr[rn];
		arr[rn] = temp;
	}
}


Block* RandomBlock(Block* res_blocks) {
	int invailed_num[7] = { 1,5,9,13,15,17,18 };
	shuffle(invailed_num,7);
	for (int i = 0; i < 7; i++) {
		res_blocks[i] = Get_Block(invailed_num[i]);
	}
	return res_blocks;
}

void BlockInit(Block* block_list) {
	Block* b1;
	Block* b2;
	b1 = (Block*)malloc(sizeof(Block) * 7);
	b2 = (Block*)malloc(sizeof(Block) * 7);
	b1 = RandomBlock(b1);
	b2 = RandomBlock(b2);
	for (int i = 0; i < 14; i++) {
		if (i < 7) {
			block_list[i] = b1[i];
		}
		else {
			block_list[i] = b2[i - 6];
		}
	}
	free(b1);
	free(b2);
}

void BlockReFill(Block* block_list) {
	Block* b1;
	b1 = (Block*)malloc(sizeof(Block) * 7);
	b1 = RandomBlock(b1);
	for (int i = 0; i < 7; i++) {
		block_list[i+7] = b1[i];
	}
	free(b1);
}

void SubtractList(Block* block_list) {
	for (int i = 0; i < 13; i++) {
		block_list[i] = block_list[i + 1];
	}
}