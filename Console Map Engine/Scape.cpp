#include "Scape.h"

ViewFrame Scape::getViewFrame(size_t x, size_t y) {
	return ViewFrame(x,y,w,h);
}

void Scape::move(size_t x, size_t y)
{
	Scape::x += x;
	Scape::y += y;
}