#include "IntervalHandler.h"
#include "Constants.h"


IntervalHandler::IntervalHandler(GameManager* gameManager, Player* player)
{
	this->timer = new Timer();
	this->gameManager = gameManager;
	this->player = player;
}


IntervalHandler::~IntervalHandler()
{
	delete timer;
}

void IntervalHandler::StartTimer()
{
	if (timer->isStarted())
	{
		timer->stop();
	}

	blockMovementInterval = DefaultBlockMovementInterval;
	timer->start();
}

void IntervalHandler::StopTimer()
{
	timer->stop();
}

void IntervalHandler::PauseTimer()
{
	timer->pause();
}

void IntervalHandler::ResumeTimer()
{
	timer->unpause();
}

void IntervalHandler::Update()
{
	//First Check If There is an Active Block
	if (player->ActiveBlock != nullptr)
	{
		//Move the active block
		if (this->timer->getTicks() > blockMovementInterval)
		{
			//Move The Block
			gameManager->MoveActiveBlock();
			this->timer->stop();
			this->timer->start();
		}
	}
	else
	{
		//Spawn a new block
		gameManager->SpawnNewBlock();
	}
}


void IntervalHandler::UpdateLevel(int level)
{
	this->blockMovementInterval = (DefaultBlockMovementInterval - (level * DefaultBlockMovementInterval / 20));
}
