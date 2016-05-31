#include "Grid.h"
#include "RenderingHelper.h"
#include "Constants.h"
#include <stdlib.h>
#include "Block.h"
#include <bitset>

Grid::Grid()
{
	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			grid[i][j] = new Cell();
		}
	}
}


Grid::~Grid()
{
	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			delete grid[i][j];
			grid[i][j] = nullptr;
		}
	}
}


void Grid::AddBlock(Block* block)
{
	CellStatus status = block->GetStatusEquivalent();
	Uint16 state = block->GetState();
	std::bitset<16> stateBitSet = std::bitset<16>(state);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int bit_pos = 15 - (i * 4 + j);
			if (stateBitSet.test(bit_pos))
			{
				this->grid[block->GetCenterY() + i][block->GetCenterX() + j]->SetStatus(status);
			}
		}
	}
}

void Grid::UpdateBlock(int i, int j, Uint16 currentState, Uint16 nextState, Block* block)
{
	std::bitset<16> currentBitSet = std::bitset<16>(currentState);
	std::bitset<16> nextBitSet = std::bitset<16>(nextState);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int bit_pos = 15 - (y * 4 + x);
			bool currentCellFilled = currentBitSet.test(bit_pos);
			bool nextCellFilled = nextBitSet.test(bit_pos);

			if (currentCellFilled && !nextCellFilled)
			{
				grid[i + y][j + x]->SetStatus(Empty);
			}
			else if (!currentBitSet.test(bit_pos) && nextCellFilled)
			{
				grid[i + y][j + x]->SetStatus(block->GetStatusEquivalent());
			}
		}
	}
}

Uint16 Grid::GetPartialStatus(int i, int j, Uint16 currentState)
{
	std::bitset<16> currentBitSet(currentState);
	if (i < 0 || i + 4 >= grid_height || j < 0 || j + 4 >= grid_width)
	{
		return 0xFF;
	}
	else
	{
		std::bitset<16> status =  0x0000;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (grid[i + y][j + x]->GetStatus() != Empty && !currentBitSet.test(15 - (y * 4 + x)))
				{
					status.set(15 - (y * 4 + x));
				}
			}
		}

		return status.to_ullong();
	}
}

void Grid::Render(SDL_Renderer* gRenderer)
{
	if (grid != nullptr) {
		int offsetX = 0;
		int offsetY = 0;
		SDL_Rect draw_rect = { 0, 0, SCREEN_WIDTH / 5 * 3 / grid_width, SCREEN_HEIGHT / grid_height };

		for (int i = 0; i < grid_height; i++) {
			offsetX = 0;
			draw_rect.x = 0;
			draw_rect.y = offsetY;

			for (int j = 0; j < grid_width; j++) {
				Uint8* color = RenderingHelper::GetRenderingColor((*grid[i][j]).GetStatus());
				SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], color[3]);
				SDL_RenderFillRect(gRenderer, &draw_rect);

				offsetX += draw_rect.w;
				draw_rect.x = offsetX;
			}
			offsetY += draw_rect.h;
		}
	}
}
