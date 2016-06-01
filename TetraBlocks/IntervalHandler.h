#pragma once
#include "Timer.h"
#include "GameManager.h"
#include "Player.h"

class GameManager;
class IntervalHandler
{
public:
	IntervalHandler(GameManager* gameManager,Player* player);
	~IntervalHandler();
	void StartTimer();
	void StopTimer();
	void PauseTimer();
	void ResumeTimer();
	void Update();
private:
	Timer* timer;
	GameManager* gameManager;
	Player* player;
	Uint32 blockMovementInterval;
};

