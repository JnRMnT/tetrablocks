#include "Player.h"

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