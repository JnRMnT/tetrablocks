#include "Grid.h"
#include "RenderingHelper.h"
#include "Constants.h"
#include <stdlib.h>
#include "Block.h"

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

void Grid::UpdateBlock(int i, int j, Uint16 gridState, int nextI, int nextJ, Uint16 currentState, Uint16 nextState, Block* block)
{
	std::bitset<16> currentBitSet = std::bitset<16>(gridState);
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
				grid[nextI + y][nextJ + x]->SetStatus(Empty);
			}
			else if (!currentBitSet.test(bit_pos) && nextCellFilled)
			{
				grid[nextI + y][nextJ + x]->SetStatus(block->GetStatusEquivalent());
			}
		}
	}

	if (currentState == nextState)
	{
		//Movement
		if (nextJ != j)
		{
			//Horizontal Movement
			if (nextJ > j)
			{
				//Going Right, Check 3rd, 7th, 11th and 15th bits
				CheckStateAndEmptyCells(currentState, i, j, 3);
				CheckStateAndEmptyCells(currentState, i, j, 7);
				CheckStateAndEmptyCells(currentState, i, j, 11);
				CheckStateAndEmptyCells(currentState, i, j, 15);
			}
			else
			{
				//Going Left, Check 0th, 4th, 8th and 12th bits
				CheckStateAndEmptyCells(currentState, i, j, 0);
				CheckStateAndEmptyCells(currentState, i, j, 4);
				CheckStateAndEmptyCells(currentState, i, j, 8);
				CheckStateAndEmptyCells(currentState, i, j, 12);
			}
		}
		else
		{
			//Vertical Movement - Going Down, Check 12th, 13th, 14th and 15th bits
			CheckStateAndEmptyCells(currentState, i, j, 12);
			CheckStateAndEmptyCells(currentState, i, j, 13);
			CheckStateAndEmptyCells(currentState, i, j, 14);
			CheckStateAndEmptyCells(currentState, i, j, 15);
		}
	}
}

void Grid::CheckStateAndEmptyCells(std::bitset<16> state, int y, int x, int bitToCheck)
{
	if (state.test(bitToCheck))
	{
		int i = (15 - bitToCheck) / 4;
		int j = (15 - bitToCheck) % 4;
		this->grid[y + i][x + j]->SetStatus(Empty);
	}
}

Uint16 Grid::GetPartialStatus(int i, int j, Uint16 currentState)
{
	std::bitset<16> currentBitSet(currentState);
	std::bitset<16> status = 0x0000;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (i + y < 0 || i + y >= grid_height || j + x < 0 || j + x >= grid_width)
			{
				continue;
			}

			if (grid[i + y][j + x]->GetStatus() != Empty && !currentBitSet.test(15 - (y * 4 + x)))
			{
				status.set(15 - (y * 4 + x));
			}
		}
	}

	return status.to_ullong();
}

void Grid::Render(SDL_Renderer* gRenderer)
{
	if (grid != nullptr) {
		int offsetX = 0;
		int offsetY = 0;
		int cellSize = SCREEN_HEIGHT / grid_height;
		SDL_Rect draw_rect = { 0, 0, cellSize, cellSize };

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

bool Grid::IsInBounds(int x, int y, Uint16 testState)
{
	std::bitset<16> stateBitSet = std::bitset<16>(testState);
	bool inBounds = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (stateBitSet.test(i * 4 + j))
			{
				int currentX = x + j;
				int currentY = y + i;
				inBounds = inBounds &&
					currentX >= 0 && currentX < grid_width &&
					currentY >= 0 && currentY < grid_height;
			}
		}
	}

	return inBounds;
}

bool Grid::IsOccupied(int i, int j)
{
	return this->grid[i][j]->GetStatus() != Empty;
}