#include "Cell.h"


Cell::Cell()
{
	status = Empty;
}


Cell::~Cell()
{
}

void Cell::SetStatus(CellStatus status)
{
	this->status = status;
}

CellStatus Cell::GetStatus()
{
	return this->status;
}
