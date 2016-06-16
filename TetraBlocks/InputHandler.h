#pragma once
#include <SDL.h>
#include "Player.h"
#include "Timer.h"
#include <SDL_ttf.h>
#include <math.h>
#include "LTexture.h"

class InputHandler
{
public:
	static void HandleInput(SDL_Event e, Player* player, TTF_Font* gFont, LTexture* fontTexture);
private:
	static void HandleSingleInput(SDL_Event e, Player* player);
};