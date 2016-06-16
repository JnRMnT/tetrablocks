#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "GameManager.h"
#include "Constants.h"
#include "Player.h"
#include "InputHandler.h"
#include "IntervalHandler.h"
#include <SDL_ttf.h>

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

//TrueType Font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture* gTextTexture = NULL;

GameManager* gameManager = NULL;
Player* player = NULL;
IntervalHandler* intervalHandler = NULL;

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
		gWindow = SDL_CreateWindow("Tetra Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_SetWindowMinimumSize(gWindow, MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);
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


				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				gTextTexture = new LTexture();
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Resources/Square.ttf", DefaultFontSize);
	if (gFont == NULL)
	{
		printf("Failed to load global font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		gTextTexture->SetFont(gFont);
	}

	return success;
}

void close()
{
	//Free loaded images
	gTextTexture->free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();


	free(gameManager);
	free(player);
	free(intervalHandler);
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
			gameManager = new GameManager();
			player = new Player(gameManager->GetGridInstance());
			intervalHandler = new IntervalHandler(gameManager, player);
			gameManager->SetPlayer(player);
			gameManager->SetIntervalHandler(intervalHandler);

			// Start the Game
			gameManager->StartGame();

			//While application is running
			while (!quit)
			{
				if (gameManager->IsPlaying())
				{
					//Game is in session
					intervalHandler->Update();
				}


				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (gameManager->IsPlaying())
					{
						InputHandler::HandleInput(e, player, gFont, gTextTexture);
					}
				}
				
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				
				gameManager->GetGridInstance()->Render(gRenderer);
				gameManager->Render(gRenderer, gTextTexture);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}