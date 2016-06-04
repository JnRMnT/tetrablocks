#pragma once
#include "Grid.h"
#include "GameState.h"
#include "Timer.h"
#include "IntervalHandler.h"
#include "Player.h"

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
	void SetPlayer(Player* player);
	void SpawnNewBlock();
	void MoveActiveBlock();
	Grid* GetGridInstance();
private:
	Grid* grid;
	Player* player;
	GameState state;
	IntervalHandler* intervalHandler;
	BlockType* randomPool;
	BlockType GetNextBlockType();
	BlockType nextBlockType;
	int AddToPool(BlockType type, BlockType* pool, int count, int index);
};

