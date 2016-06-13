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
	bool Move(Direction movement);
	CellStatus GetStatusEquivalent();
	bool CanMove(int x, int y, Uint16 previousState);
	bool HasCollision(Uint16 gridState);
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