#pragma once
#include "Block.h"

class Player
{
public:
	Player(Grid* grid);
	~Player();
	Block* ActiveBlock;
	RotationHelper* rotationHelper;
	Grid* grid;
};

