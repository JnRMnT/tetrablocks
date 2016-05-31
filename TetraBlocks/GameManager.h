#pragma once
#include "Grid.h"
#include "GameState.h"
#include "Timer.h"
#include "IntervalHandler.h"

class IntervalHandler;
class GameManager
{
public:
	GameManager();
	~GameManager();
	void StartGame();
	void PauseGame();
	bool IsPlaying();
	void SetIntervalHandler(IntervalHandler* intervalHandler);
	Grid* GetGridInstance();
private:
	Grid* grid;
	GameState state;
	IntervalHandler* intervalHandler;
};

