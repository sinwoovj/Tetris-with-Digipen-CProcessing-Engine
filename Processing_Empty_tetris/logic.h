#pragma once

enum KindOfBlock {
	None = 0,
	J = 1,
	L = 2,
	T = 3,
	Z = 4,
	S = 5,
	O = 6,
	I = 7
}typedef KindOfBlock;

struct Vector2 {
	float x;
	float y;
}typedef Vector2;

struct Block {
	KindOfBlock kindOfBlock;
	int b_num;
	int name;
	int shape;
	// This value will be changed
	//Vector2 c00;
	// it's a fixed value
	int color;
	Vector2 c01;
	Vector2 c10;
	Vector2 c11;
	int leftDirBlock;
	int rightDirBlock;
	int reversalDirBlock;
}typedef Block;

Block Get_Block(int num);
void BlockInit(Block* block_list);
void SubtractList(Block* block_list);
void BlockReFill(Block* block_list);