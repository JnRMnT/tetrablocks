#include "GameManager.h"

GameManager::GameManager()
{
	timer = new Timer();
}


GameManager::~GameManager()
{
	delete grid;
	grid = nullptr;
	state = Paused;
	delete timer;
}

void GameManager::StartGame() 
{
	grid = new Grid();
	state = Playing;
	if (timer->isStarted())
	{
		timer->stop();
	}

	timer->start();


}

bool GameManager::IsPlaying()
{
	return state == Playing;
}

Grid* GameManager::GetGridInstance() 
{
	return grid;
}
