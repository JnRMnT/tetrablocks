#include "GameManager.h"

GameManager::GameManager()
{
	grid = new Grid();
}

GameManager::~GameManager()
{
	delete grid;
	grid = nullptr;
	state = Paused;
}

void GameManager::StartGame() 
{
	state = Playing;
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

bool GameManager::IsPlaying()
{
	return state == Playing;
}

Grid* GameManager::GetGridInstance() 
{
	return grid;
}
