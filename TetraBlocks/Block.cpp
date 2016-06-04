#include "Block.h"


Block::Block(int center_x, int center_y, BlockType type, RotationHelper* rotationHelper, Grid* grid)
{
	this->rotationHelper = rotationHelper;
	this->type = type;
	this->center_x = center_x;
	this->center_y = center_y;
	this->state = rotationHelper->GetBlockState(type, 0);
	this->grid = grid;
}


Block::~Block()
{
}

void Block::Move(Direction movement)
{
	int newCenterX = this->center_x;
	int newCenterY = this->center_y;

	switch (movement)
	{
	default:
		break;
	case Left:
		newCenterX--;
		break;
	case Right:
		newCenterX++;
		break;
	case Down:
		newCenterY++;
		break;
	}

	if (CanMove(newCenterX, newCenterY))
	{
		grid->UpdateBlock(center_y, center_x, grid->GetPartialStatus(newCenterY, newCenterX, state, true), newCenterY, newCenterX, state, state, this);
		this->center_x = newCenterX;
		this->center_y = newCenterY;
	}
}

bool Block::CanMove(int x, int y)
{
	return grid->IsInBounds(x, y, state) && grid->IsInBounds(x, y, grid->GetPartialStatus(y, x, state, true));
}

void Block::Rotate(Direction direction)
{
	Uint16 nextState;
	if (direction == Left)
	{
		nextState = rotationHelper->GetPrevious(type, state);
	}
	else
	{
		nextState = rotationHelper->GetNext(type, state);
	}

	if (rotationHelper->CanRotateTo(grid, this, nextState))
	{
		grid->UpdateBlock(center_y, center_x, state, center_y, center_x, state, nextState, this);
		state = nextState;
	}
}

CellStatus Block::GetStatusEquivalent()
{
	return (CellStatus)(int)this->type;
}

int Block::GetCenterX()
{
	return this->center_x;
}

int Block::GetCenterY()
{
	return this->center_y;
}

Uint16 Block::GetState()
{
	return this->state;
}