#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "GameManager.h"
#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

GameManager* game_manager = NULL;
Player* player = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load arrow
	/*
	if (!gArrowTexture.loadFromFile("15_rotation_and_flipping/arrow.png"))
	{
		printf("Failed to load arrow texture!\n");
		success = false;
	}
	*/
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			game_manager = new GameManager();
			game_manager->StartGame();

			player = new Player(game_manager->GetGridInstance());

			player->ActiveBlock = new Block(5, 5, Z, player->rotationHelper, game_manager->GetGridInstance());
			game_manager->GetGridInstance()->AddBlock(player->ActiveBlock);

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (game_manager->IsPlaying())
					{
						InputHandler::HandleInput(e, player);
					}
				}

				if (game_manager->IsPlaying())
				{
					//Game is in session
					if(player->ActiveBlock != nullptr)
					{
						//Move the active block
					}
				}


				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				/*
				//Top left corner viewport
				SDL_Rect leftViewport;
				leftViewport.x = 0;
				leftViewport.y = 0;
				leftViewport.w = SCREEN_WIDTH / 4 * 3;
				leftViewport.h = SCREEN_HEIGHT;
				SDL_RenderSetViewport(gRenderer, &leftViewport);
				*/
				game_manager->GetGridInstance()->Render(gRenderer);

				/*
				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


				//Top right viewport
				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &topRightViewport);

				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


				//Bottom viewport
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &bottomViewport);


				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


				*/

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}