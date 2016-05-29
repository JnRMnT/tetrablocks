#pragma once
#include <SDL.h>
#include "BlockType.h"
#include "Block.h"
#include <string>
#include "Grid.h"
#include <vector>

class Grid;
class Block;
class RotationHelper
{
public:
	RotationHelper();
	~RotationHelper();
	Uint16 GetNext(BlockType blockType, Uint16 currentState);
	Uint16 GetPrevious(BlockType blockType, Uint16 currentState);
	Uint16* GetBlockStates(BlockType blockType);
	Uint16 GetBlockState(BlockType blockType, int index);
	bool CanRotateTo(Grid* grid, Block* block, Uint16 state);
	int GetStateIndex(BlockType blockType, Uint16 currentState);
private:
	static Uint16 stateList[7][4];
};