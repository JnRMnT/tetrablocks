#pragma once
#include "Grid.h"
#include "GameState.h"
#include "Timer.h"
#include "IntervalHandler.h"
#include "Player.h"
#include "ScoreManager.h"
#include "LTexture.h";

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
	void AddScore(int score);
	void Render(SDL_Renderer* gRenderer, LTexture* textTexture);
	Grid* GetGridInstance();
private:
	Grid* grid;
	Player* player;
	ScoreManager* scoreManager;
	GameState state;
	IntervalHandler* intervalHandler;
	BlockType* randomPool;
	BlockType GetNextBlockType();
	BlockType nextBlockType;
	int AddToPool(BlockType type, BlockType* pool, int count, int index);
	int currentLevel;
};