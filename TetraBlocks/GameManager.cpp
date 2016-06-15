#include "GameManager.h"
#include "Constants.h"
#include <time.h>
#include <stdlib.h>
#include "RenderingHelper.h"

GameManager::GameManager()
{
	grid = new Grid(this);
	scoreManager = new ScoreManager();
	srand(time(NULL));

	//Fill the Random Pool with according possibilities
	randomPool = new BlockType[RandomPoolSize];
	int index = 0;
	index = AddToPool(I, randomPool, 2, index);
	index = AddToPool(J, randomPool, 3, index);
	index = AddToPool(L, randomPool, 3, index);
	index = AddToPool(O, randomPool, 4, index);
	index = AddToPool(S, randomPool, 4, index);
	index = AddToPool(T, randomPool, 4, index);
	index = AddToPool(Z, randomPool, 4, index);

	nextBlockType = GetNextBlockType();
}

int GameManager::AddToPool(BlockType type, BlockType* pool, int count, int index)
{
	for (int i = 0; i < count; i++)
	{
		pool[index] = type;
		index++;
	}

	return index;
}

GameManager::~GameManager()
{
	delete grid;
	grid = nullptr;
	delete scoreManager;
	delete randomPool;
}

void GameManager::StartGame()
{
	state = Playing;
	currentLevel = 1;
	scoreManager->ResetScore();
	intervalHandler->StartTimer();
}

void GameManager::PauseGame()
{
	this->intervalHandler->PauseTimer();
}

void GameManager::SetIntervalHandler(IntervalHandler* intervalHandler)
{
	this->intervalHandler = intervalHandler;
}

void GameManager::SetPlayer(Player* player)
{
	this->player = player;
}

bool GameManager::IsPlaying()
{
	return state == Playing;
}

Grid* GameManager::GetGridInstance()
{
	return grid;
}

BlockType GameManager::GetNextBlockType()
{
	return randomPool[rand() % RandomPoolSize];
}

void GameManager::SpawnNewBlock()
{
	player->ActiveBlock = new Block(5, 10, nextBlockType, player->rotationHelper, grid);
	grid->AddBlock(player->ActiveBlock);
	nextBlockType = GetNextBlockType();
}

void GameManager::MoveActiveBlock()
{
	int newX = player->ActiveBlock->GetCenterX();
	int newY = player->ActiveBlock->GetCenterY() + 1;

	if (!player->ActiveBlock->Move(Down))
	{
		player->ActiveBlock = nullptr;
		AddScore(1);
	}
}

void GameManager::AddScore(int score)
{
	int newScore = this->scoreManager->AddScore(score);
	currentLevel = floor((double)newScore / (double)LevelScoreRequirement);
	this->intervalHandler->UpdateLevel(currentLevel);
}

void GameManager::Render(SDL_Renderer* gRenderer, LTexture* textTexture)
{
	//Draw Game Related GUIs
	int guiStartOffset = SCREEN_HEIGHT / grid_height * (grid_width + 1);
	int topOffset = SCREEN_HEIGHT / 20;

	int scoreboardHeight = SCREEN_HEIGHT / 20;

	SDL_Rect draw_rect = { guiStartOffset, topOffset, SCREEN_WIDTH / 8, SCREEN_WIDTH / 8 + scoreboardHeight };
	SDL_SetRenderDrawColor(gRenderer, GRID_BORDER_COLOR[0], GRID_BORDER_COLOR[1], GRID_BORDER_COLOR[2], GRID_BORDER_COLOR[3]);
	SDL_RenderDrawRect(gRenderer, &draw_rect);

	//Render Scoreboard 
	SDL_Rect scoreboard_box = { guiStartOffset, topOffset, draw_rect.w, scoreboardHeight };
	SDL_RenderDrawRect(gRenderer, &scoreboard_box);
	this->scoreManager->Render(gRenderer, &scoreboard_box, textTexture);

	//Render Upcoming Block
	RenderUpcomingBlock(gRenderer, guiStartOffset, topOffset, scoreboardHeight);
}

void GameManager::RenderUpcomingBlock(SDL_Renderer* gRenderer, int guiStartOffset, int topOffset, int scoreboardHeight)
{
	if (nextBlockType)
	{
		Uint16 nextBlockState = player->rotationHelper->GetBlockState(nextBlockType, 0);
		int offsetX = guiStartOffset;
		int offsetY = topOffset + scoreboardHeight;
		int initialOffsetX = offsetX;
		int initialOffsetY = offsetY;
		int cellSize = SCREEN_WIDTH / 8 / 4;

		SDL_Rect draw_rect = { offsetX, offsetY, cellSize, cellSize };
		Uint8* filledColor = RenderingHelper::GetRenderingColor((CellStatus)(int)nextBlockType);
		Uint8* filledBorderColor = RenderingHelper::GetBorderColor((CellStatus)(int)nextBlockType);

		Uint8* emptyColor = RenderingHelper::GetRenderingColor(EmptyGUI);
		Uint8* emptyBorderColor = RenderingHelper::GetBorderColor(EmptyGUI);

		std::bitset<16> nextBlockBitset = std::bitset<16>(nextBlockState);

		for (int i = 0; i < 4; i++) {
			offsetX = initialOffsetX;
			draw_rect.x = offsetX;
			draw_rect.y = offsetY;

			for (int j = 0; j < 4; j++) {
				Uint8* color;
				Uint8* borderColor;

				if (nextBlockBitset.test(15 - (i * 4 + j)))
				{
					color = filledColor;
					borderColor = filledBorderColor;
				}
				else
				{
					color = emptyColor;
					borderColor = emptyBorderColor;
				}

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