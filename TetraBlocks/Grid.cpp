#include "Grid.h"
#include "RenderingHelper.h"
#include "Constants.h"
#include <stdlib.h>
#include "Block.h"
#include "GameManager.h"

Grid::Grid(GameManager* gameManager)
{
	for (int i = 0; i < grid_height; i++) {
		for (int j = 0; j < grid_width; j++) {
			grid[i][j] = new Cell();
		}
	}

	this->gameManager = gameManager;
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

void Grid::UpdateBlock(int i, int j, Uint16 nextGridState, Uint16 currentGridState, int nextI, int nextJ, Uint16 currentState, Uint16 nextState, Block* block)
{
	std::bitset<16> nextGridSet = std::bitset<16>(nextGridState);
	std::bitset<16> currentGridSet = std::bitset<16>(currentGridState);
	std::bitset<16> nextBitSet = std::bitset<16>(nextState);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (nextI + y >= 0 && nextI + y < grid_height && nextJ + x >= 0 && nextJ + x < grid_width)
			{
				int bit_pos = 15 - (y * 4 + x);
				bool nextGridCellFilled = nextGridSet.test(bit_pos);
				bool nextCellFilled = nextBitSet.test(bit_pos);
				bool currentGridCellFilled = currentGridSet.test(bit_pos);

				if (currentGridCellFilled && !nextCellFilled)
				{
					grid[nextI + y][nextJ + x]->SetStatus(Empty);
				}
				else if (!nextGridCellFilled && nextCellFilled)
				{
					grid[nextI + y][nextJ + x]->SetStatus(block->GetStatusEquivalent());
				}
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

//Checks Rows For Compleation
void Grid::CheckRows()
{
	int j;
	int i = grid_height - 1;
	bool hasCompleation = false;
	while (i >= 0 && !hasCompleation)
	{
		j = 0;
		bool completed = true;
		while (completed && j < grid_width)
		{
			completed = completed && IsOccupied(i, j);
			j++;
		}

		if (completed)
		{
			gameManager->AddScore(grid_width * 3);
			hasCompleation = true;
			ClearRow(i);
			CheckRows();
		}

		i--;
	}
}

void Grid::ClearRow(int row)
{
	for (int i = row; i >= 0; i--)
	{
		if (i != 0)
		{
			for (int j = 0; j < grid_width; j++)
			{
				grid[i][j]->SetStatus(grid[i - 1][j]->GetStatus());
			}
		}
		else {
			for (int j = 0; j < grid_width; j++)
			{
				grid[i][j]->SetStatus(Empty);
			}
		}
	}
}

Uint16 Grid::GetPartialStatus(int i, int j, Uint16 currentState, bool isMovement)
{
	std::bitset<16> currentBitSet(currentState);
	std::bitset<16> status = 0x0000;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (i + y < 0 || i + y >= grid_height || j + x < 0 || j + x >= grid_width)
			{
				if (isMovement)
				{
					continue;
				}
				else
				{
					status.set(15 - (y * 4 + x));
				}
			}
			else if (grid[i + y][j + x]->GetStatus() != Empty && !currentBitSet.test(15 - (y * 4 + x)))
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
				Uint8* borderColor = RenderingHelper::GetBorderColor((*grid[i][j]).GetStatus());

				SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], color[3]);
				SDL_RenderFillRect(gRenderer, &draw_rect);
				//Gives the border effect
				SDL_SetRenderDrawColor(gRenderer, borderColor[0], borderColor[1], borderColor[2], borderColor[3]);
				SDL_RenderDrawRect(gRenderer, &draw_rect);

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
			if (stateBitSet.test(15 - (i * 4 + j)))
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