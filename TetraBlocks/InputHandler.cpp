#include "InputHandler.h"
#include "Constants.h"

SDL_Keycode lastPressedKey;
Timer* timer;
int reocurrenceCount;

void InputHandler::HandleInput(SDL_Event e, Player* player, TTF_Font* gFont, LTexture* fontTexture)
{
	if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		Player::ScreenWidth = e.window.data1;
		Player::ScreenHeight = e.window.data2;
		Player::FontSize = (double)DefaultFontSize * ((double)Player::ScreenWidth * (double)Player::ScreenHeight / (double)DEFAULT_SCREEN_WIDTH / (double)DEFAULT_SCREEN_HEIGHT);
		gFont = TTF_OpenFont("Resources/Square.ttf", Player::FontSize);
		fontTexture->SetFont(gFont);
	}
	else if (e.type == SDL_KEYUP)
	{
		lastPressedKey = NULL;
		reocurrenceCount = 0;
		//Handle Single Presses
		HandleSingleInput(e, player);
	}
	else if (e.type == SDL_KEYDOWN)
	{
		//Handle Continious Presses

		if (timer == nullptr)
		{
			timer = new Timer();
		}

		if (lastPressedKey == NULL || e.key.keysym.scancode != lastPressedKey)
		{
			lastPressedKey = e.key.keysym.scancode;
			timer->stop();
		}
		else
		{
			int reoccurrenceBoost;
			if (reocurrenceCount >= 10)
			{
				reoccurrenceBoost = KeyPressInterval - KeyPressInterval / 10;
			}
			else
			{
				reoccurrenceBoost = reocurrenceCount * KeyPressInterval / 10;
			}

			if (!timer->isStarted())
			{
				timer->start();
			}
			else if (timer->getTicks() > KeyPressInterval - reoccurrenceBoost)
			{
				reocurrenceCount++;
				timer->stop();
				timer->start();
				if (player->ActiveBlock != nullptr)
				{
					HandleSingleInput(e, player);
				}
			}
		}
	}
}

void InputHandler::HandleSingleInput(SDL_Event e, Player* player)
{
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