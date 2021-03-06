#pragma once
#include <SDL.h>
#include "CellStatus.h"

class RenderingHelper
{
public:
	RenderingHelper();
	~RenderingHelper();
	static Uint8* GetRenderingColor(CellStatus status);
	static Uint8* GetBorderColor(CellStatus status);
};