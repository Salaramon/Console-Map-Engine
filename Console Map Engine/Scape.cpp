#include "Scape.h"

ViewFrame Scape::getViewFrame(size_t x, size_t y) {
	return ViewFrame(x,y,w,h);
}

void Scape::move(double_t x, double_t y)
{
	Scape::x += x;
	Scape::y += y;
}