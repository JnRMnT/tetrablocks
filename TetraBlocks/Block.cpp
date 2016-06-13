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

bool Block::Move(Direction movement)
{
	int newCenterX = this->center_x;
	int newCenterY = this->center_y;
	Uint16 previousState;
	std::bitset<16> nextBitset(0);
	std::bitset<16> currentBitset(state);

	switch (movement)
	{
	default:
		break;
	case Left:
		newCenterX--;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bool set = false;
				if (j != 0 && currentBitset.test(15 - (i * 4 + j - 1)))
				{
					set = true;
				}
				nextBitset.set(15 - (i * 4 + j), set);
			}
		}
		break;
	case Right:
		newCenterX++;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bool set = false;
				if (j != 3 && currentBitset.test(15 - (i * 4 + j + 1)))
				{
					set = true;
				}
				nextBitset.set(15 - (i * 4 + j), set);
			}
		}
		break;
	case Down:
		newCenterY++;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bool set = false;
				if (i != 3 && currentBitset.test(15 - ((i + 1) * 4 + j)))
				{
					set = true;
				}
				nextBitset.set(15 - (i * 4 + j), set);
			}
		}
		break;
	}

	previousState = nextBitset.to_ullong();

	if (CanMove(newCenterX, newCenterY, previousState))
	{
		grid->UpdateBlock(center_y, center_x, grid->GetPartialStatus(newCenterY, newCenterX, state, true), previousState, newCenterY, newCenterX, state, state, this);
		this->center_x = newCenterX;
		this->center_y = newCenterY;
		return true;
	}
	else
	{
		return false;
	}
}

bool Block::CanMove(int x, int y, Uint16 previousState)
{
	if (grid->IsInBounds(x, y, state) && !HasCollision(grid->GetPartialStatus(y, x, previousState, true)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Block::HasCollision(Uint16 gridState)
{
	return ((gridState & state) != 0);
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
		grid->UpdateBlock(center_y, center_x, state, state, center_y, center_x, state, nextState, this);
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