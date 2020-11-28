#include "Renderer.h"

Renderer::Renderer(Window* target)
{
	setup(target);
}

Renderer::Renderer(size_t x, size_t y)
{
	setup(x, y);
}

bool Renderer::setup(Window* target)
{
	return setup(target->width, target->height);
}

bool Renderer::setup(size_t x, size_t y)
{
	buffer.lineColumns = (x / 8) - 2;
	buffer.lineRows = (y / 8) - 5;

	clear();

	return false;
}

void Renderer::draw(size_t x, size_t y)
{
	buffer.at(x, y);
}

void Renderer::render()
{
	system("CLS");
	printf(buffer.string.c_str());
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Renderer::render(Scape *scape, ViewFrame view)
{	
	for (size_t y = 0; y < view.h; y++) {
		for (size_t x = 0; x < view.w; x++) {
			char input = scape->at(std::floor(x * (static_cast<double_t>(scape->w) / view.w)) + scape->x, std::floor(y * (static_cast<double_t>(scape->h) / view.h)) + scape->y);
			if (input != 0) {
				buffer.at(view.x + x, view.y + y) = input;
			}
			
		}
	}
	render();
}

void Renderer::clear()
{
	buffer.string.clear();
	for (size_t y = 0; y < buffer.lineRows; y++) {
		for (size_t x = 0; x < buffer.lineColumns; x++) {
			buffer.string += ' ';
		}
		if (buffer.lineRows - 1 != y) {
			buffer.string += '\n';
		}
	}
}
