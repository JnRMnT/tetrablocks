#pragma once
#include <SDL.h>
#include "Player.h"

class InputHandler
{
public:
	static void HandleInput(SDL_Event e, Player* player);
};