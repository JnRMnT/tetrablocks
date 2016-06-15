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
		return new Uint8[4]{ 0x00, 0x99, 0x33,0xFF };
		break;
	case Orange:
		return new Uint8[4]{ 0xE6, 0xA5, 0x00,0xFF };
		break;
	case Yellow:
		return new Uint8[4]{ 0xFF, 0xCC, 0x00 ,0xFF };
		break;
	case Pink:
		return new Uint8[4]{ 0xFF, 0x66, 0x66 ,0xFF };
		break;
	case Blue:
		return new Uint8[4]{ 0x33, 0x66, 0xFF,0xFF };
		break;
	case Red:
		return new Uint8[4]{ 0xCC, 0x00, 0x00 ,0xFF };
		break;
	case White:
		return new Uint8[4]{ 0xE6, 0xE6, 0xE6 ,0xFF };
		break;
	case EmptyGUI:
		return new Uint8[4]{ 0xF0, 0xF5, 0xF5 ,0x55 };
		break;
	default:
		break;
	}
}

Uint8* RenderingHelper::GetBorderColor(CellStatus status)
{
	switch (status)
	{
	case Empty:
		return GRID_BORDER_COLOR;
		break;
	case Green:
		return new Uint8[4]{ 0x00, 0x4D, 0x1A,0xFF };
		break;
	case Orange:
		return new Uint8[4]{ 0xE6, 0x3D, 0x00,0xFF };
		break;
	case Yellow:
		return new Uint8[4]{ 0xCC, 0xA3, 0x00 ,0xFF };
		break;
	case Pink:
		return new Uint8[4]{ 0xFF, 0x4D, 0x4D ,0xFF };
		break;
	case Blue:
		return new Uint8[4]{ 0x1A, 0x53, 0xFF,0xFF };
		break;
	case Red:
		return new Uint8[4]{ 0xB3, 0x00, 0x00 ,0xFF };
		break;
	case White:
		return new Uint8[4]{ 0x1A, 0x1A, 0x1A ,0xFF };
		break;
	case EmptyGUI:
		return new Uint8[4]{ 0xE0, 0xEB, 0xEB ,0x55 };
		break;
	default:
		break;
	}
}