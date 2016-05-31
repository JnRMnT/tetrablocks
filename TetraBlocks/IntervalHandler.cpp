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
	if (this->timer->getTicks() > blockMovementInterval)
	{
		//Move The Block

	}
}
