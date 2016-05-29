#pragma once
#include "Grid.h"
#include "GameState.h"
#include "Timer.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void StartGame();
	void PauseGame();
	bool IsPlaying();
	Grid* GetGridInstance();
private:
	Grid* grid;
	Timer* timer;
	GameState state;
};

