#pragma once
#include <SDL.h>
#include "LTexture.h"

class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void ResetScore();
	int AddScore(int score);
	void Render(SDL_Renderer* gRenderer, SDL_Rect* drawRect, LTexture* textTexture);
private:
	int score;
};