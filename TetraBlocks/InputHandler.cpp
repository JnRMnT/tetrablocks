#include "InputHandler.h"

void InputHandler::HandleInput(SDL_Event e, Player* player)
{
	if (e.type == SDL_KEYUP) 
	{
		//Only Handle Key Up Events
		switch (e.key.keysym.scancode)
		{
		case SDL_SCANCODE_RIGHT:
			player->ActiveBlock->Rotate(Right);
			break;
		case SDL_SCANCODE_LEFT:
			player->ActiveBlock->Rotate(Left);
			break;
		default:
			break;
		}
	}
}