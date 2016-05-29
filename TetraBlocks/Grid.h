#pragma once
#include "Cell.h"
#include "Block.h"
#include <SDL.h>
#include <SDL_image.h>

#define grid_width 10
#define grid_height 20

class Block;
class Grid
{
public:
	Grid();
	~Grid();
	void Render(SDL_Renderer* gRenderer);
	void AddBlock(Block* block);
	void UpdateBlock(int i, int j, Uint16 currentState, Uint16 nextState, Block* block);
	Uint16 GetPartialStatus(int i, int j, Uint16 currentState);
private:
	Cell* grid[grid_height][grid_width];
};