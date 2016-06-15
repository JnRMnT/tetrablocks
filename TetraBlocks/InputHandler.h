#pragma once
#include <SDL.h>
#include "Player.h"
#include "Timer.h"

class InputHandler
{
public:
	static void HandleInput(SDL_Event e, Player* player);
private:
	static void HandleSingleInput(SDL_Event e, Player* player);
};