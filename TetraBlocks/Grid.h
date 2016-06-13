#pragma once
#include "Cell.h"
#include "Block.h"
#include <SDL.h>
#include <SDL_image.h>
#include <bitset>

#define grid_width 20
#define grid_height 30

class Block;
class Grid
{
public:
	Grid();
	~Grid();
	void Render(SDL_Renderer* gRenderer);
	void AddBlock(Block* block);
	void UpdateBlock(int i, int j, Uint16 nextGridState, Uint16 currentGridState, int nextI, int nextJ, Uint16 currentState, Uint16 nextState, Block* block);
	Uint16 GetPartialStatus(int i, int j, Uint16 currentState, bool isMovement);
	bool IsOccupied(int i, int j);
	bool IsInBounds(int x, int y, Uint16 testState);
private:
	Cell* grid[grid_height][grid_width];
	void CheckStateAndEmptyCells(std::bitset<16> state, int i, int j, int bitToCheck);
};