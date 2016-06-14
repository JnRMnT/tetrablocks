#pragma once
#include <SDL.h>
#ifndef Constants_Defined
#define Constants_Defined
//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
static Uint8* GRID_BG_COLOR = new Uint8[4]{ 0xE0, 0xE0, 0xE0 ,0xFF };
static Uint8* GRID_BORDER_COLOR = new Uint8[4]{ 0xD9, 0xD9, 0xD9 ,0x80 };

const int DefaultBlockMovementInterval = 1000;
#define RandomPoolSize 24
#endif