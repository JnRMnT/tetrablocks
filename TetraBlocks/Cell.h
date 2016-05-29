#pragma once
#include "CellStatus.h"
class Cell
{
public:
	Cell();
	~Cell();
	void SetStatus(CellStatus status);
	CellStatus GetStatus();
private:
	CellStatus status;
};