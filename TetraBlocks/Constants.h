#pragma once
#include <SDL.h>
#ifndef Constants_Defined
#define Constants_Defined
//Screen dimension constants
const int DEFAULT_SCREEN_WIDTH = 1000;
const int DEFAULT_SCREEN_HEIGHT = 960;

const int MIN_SCREEN_WIDTH = 700;
const int MIN_SCREEN_HEIGHT = 700;

//Grid Coloring Constants
static Uint8* GRID_BG_COLOR = new Uint8[4]{ 0xE0, 0xE0, 0xE0 ,0xFF };
static Uint8* GRID_BORDER_COLOR = new Uint8[4]{ 0xD9, 0xD9, 0xD9 ,0x80 };

//Level/Block Movement Constants
const int LevelScoreRequirement = 50;
const int DefaultBlockMovementInterval = 1000;

//Font Rendering Constants
static SDL_Color DefaultFontColor = { 70, 70, 70 };
const int DefaultFontSize = 28;

//Other Constants
#define RandomPoolSize 24
const int KeyPressInterval = 75;
#endif