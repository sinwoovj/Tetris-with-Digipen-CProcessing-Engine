#include "cprocessing.h"
#include <stdio.h>
#include "logic.h"
#include "color.h"

#define block_cnt 20 // + None

Block blocks[block_cnt] = {
	{ None, 0, 0, NoneColor, {0,0}, {0,0}, {0,0}, 0, 0, 0},
	{ J, 1, 1, Blue, {1,0}, {1,1}, {1,2}, 4, 2, 3		},
	{ J, 2, 2, Blue, {1,0}, {2,0}, {0,1}, 1, 3, 4		},
	{ J, 3, 3, Blue, {0,1}, {0,2}, {1,2}, 2, 4, 1	 	},
	{ J, 4, 4, Blue, {-2,1}, {-1,1}, {0,1}, 3, 1, 2	 	},
	{ L, 5, 1, Orange, {1,0}, {0,1}, {0,2}, 4, 2, 3	 	},
	{ L, 6, 2, Orange, {0,1}, {1,1}, {2,1}, 1, 3, 4	 	},
	{ L, 7, 3, Orange, {0,1}, {-1,2}, {0,2}, 2, 4, 1 	},
	{ L, 8, 4, Orange, {1,0}, {2,0}, {2,1}, 3, 1, 2	 	},
	{ T, 9, 1, Purple, {-1,1}, {0,1}, {1,1}, 4, 2, 3 	},
	{ T, 10, 2, Purple, {-1,1}, {0,1}, {0,2}, 1, 3, 4	},
	{ T, 11, 3, Purple, {1,0}, {2,0}, {1,1}, 2, 4, 1 	},
	{ T, 12, 4, Purple, {0,1}, {1,1}, {0,2}, 3, 1, 2 	},
	{ Z, 13, 1, Red, {1,0}, {-1,1}, {0,1}, 0, 0, 0	 	},
	{ Z, 14, 2, Red, {0,1}, {1,1}, {1,2}, 0, 0, 0	 	},
	{ S, 15, 1, Green, {1,0}, {1,1}, {2,1}, 0, 0, 0	 	},
	{ S, 16, 2, Green, {0,1}, {-1,1}, {-1,2}, 0, 0, 0	},
	{ O, 17, 1, Yellow, {1,0}, {1,0}, {1,1}, 0, 0, 0 	},
	{ I, 18, 1, Sky, {0,1}, {0,2}, {0,3}, 0, 0, 0	 	},
	{ I, 19, 2, Sky, {1,0}, {2,0}, {3,0}, 0, 0, 0	 	}
};

Block Get_Block(int num) {
	for (int i = 0; i < block_cnt; i++) {
		if (blocks[i].b_num == num) {
			return blocks[i];
		}
	}
	return blocks[0];
}

void BlockProcess(void) {

}