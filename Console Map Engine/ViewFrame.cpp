#include "ViewFrame.h"

ViewFrame::ViewFrame()
{
}

ViewFrame::ViewFrame(size_t x, size_t y, size_t w, size_t h) :
	x(x), y(y), w(w), h(h)
{
}

void ViewFrame::move(size_t x, size_t y)
{
	ViewFrame::x += x;
	ViewFrame::y += y;
}