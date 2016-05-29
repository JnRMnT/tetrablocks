#include "RenderingHelper.h"
#include "Constants.h"


RenderingHelper::RenderingHelper()
{
}


RenderingHelper::~RenderingHelper()
{
}

Uint8* RenderingHelper::GetRenderingColor(CellStatus status)
{
	switch (status)
	{
	case Empty:
		return GRID_BG_COLOR;
		break;
	case Green:
		return new Uint8[4]{ 0x00, 0xFF, 0x00,0xFF };
		break;
	case Orange:
		return new Uint8[4]{ 0xFF, 0xA5, 0x00,0xFF };
		break;
	case Yellow:
		return new Uint8[4]{ 0xFF, 0xFF, 0x00 ,0xFF };
		break;
	case Pink:
		return new Uint8[4]{ 0xFF, 0x66, 0x66 ,0xFF };
		break;
	case Blue:
		return new Uint8[4]{ 0x33, 0x33, 0xFF,0xFF };
		break;
	case Red:
		return new Uint8[4]{ 0xCC, 0x00, 0x00 ,0xFF };
		break;
	case White:
		return new Uint8[4]{ 0xFF, 0xFF, 0xFF ,0xFF };
		break;
	default:
		break;
	}
}