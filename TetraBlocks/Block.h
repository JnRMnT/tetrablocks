#pragma once
#include "RotationHelper.h"
#include "Direction.h"
#include "Grid.h"

class Grid;
class RotationHelper;
class Block
{
public:
	Block(int center_x, int center_y, BlockType type, RotationHelper* rotationHelper, Grid* grid);
	~Block();
	void Rotate(Direction direction);
	void Move(Direction movement);
	CellStatus GetStatusEquivalent();
	bool CanMove(int x, int y);
	int GetCenterX();
	int GetCenterY();
	Uint16 GetState();
private:
	int center_x;
	int center_y;
	BlockType type;
	Uint16 state;
	RotationHelper* rotationHelper;
	Grid* grid;
};