#include "InputHandler.h"

void InputHandler::HandleInput(SDL_Event e, Player* player)
{
	if (e.type == SDL_KEYUP) 
	{
		//Only Handle Key Up Events
		switch (e.key.keysym.scancode)
		{
		case SDL_SCANCODE_D:
			player->ActiveBlock->Rotate(Right);
			break;
		case SDL_SCANCODE_A:
			player->ActiveBlock->Rotate(Left);
			break;
		case SDL_SCANCODE_LEFT:
			player->ActiveBlock->Move(Left);
			break;
		case SDL_SCANCODE_RIGHT:
			player->ActiveBlock->Move(Right);
			break;
		case SDL_SCANCODE_DOWN:
			player->ActiveBlock->Move(Down);
			break;
		default:
			break;
		}
	}
}