#include "Player.h"
#include "Constants.h"

int Player::ScreenWidth = DEFAULT_SCREEN_WIDTH;
int Player::ScreenHeight = DEFAULT_SCREEN_HEIGHT;
int Player::FontSize = DefaultFontSize;

Player::Player(Grid* grid)
{
	this->grid = grid;
	this->rotationHelper = new RotationHelper();
}


Player::~Player()
{
	free(ActiveBlock);
	free(rotationHelper);
}