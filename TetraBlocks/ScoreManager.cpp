#include "ScoreManager.h"
#include "Constants.h"

ScoreManager::ScoreManager()
{
}


ScoreManager::~ScoreManager()
{
}

void ScoreManager::ResetScore()
{
	this->score = 0;
}

//Adds the score and returns the new sum
int ScoreManager::AddScore(int score)
{
	this->score += score;
	return this->score;
}

void ScoreManager::Render(SDL_Renderer* gRenderer, SDL_Rect* drawRect, LTexture* textTexture)
{
	int centerX, centerY;
	std::string text = std::to_string(score);

	centerX = drawRect->x + drawRect->w / 2 - text.length() * 5;

	centerY = drawRect->y + Player::FontSize / 2;

	textTexture->loadFromRenderedText(gRenderer, text);
	textTexture->render(gRenderer, centerX, centerY);
}