#include "Renderer.h"

Renderer::Renderer(Window* target)
{
	setup(target);
}

bool Renderer::setup(Window* target)
{
	window = target;
	return setup();
}

bool Renderer::setup()
{
	backBuffer.lineColumns = (window->width / 8) - 2;
	backBuffer.lineRows = (window->height / 8) - 4;

	clear();
	frontBuffer = backBuffer;
	return false;
}

void Renderer::draw(size_t x, size_t y)
{
	backBuffer.at(x, y);
}

void Renderer::render()
{
	if (0 != (backBuffer.string.compare(frontBuffer.string))) {
		frontBuffer = backBuffer;
		system("CLS");
		printf(frontBuffer.string.c_str());
	}
	
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

size_t Renderer::getHeight()
{
    return backBuffer.lineRows;
}

size_t Renderer::getWidth()
{
    return backBuffer.lineColumns;
}

void Renderer::update(Scape *scape, ViewFrame view)
{
	int dissimilarityCount = 0;
	for (size_t y = 0; y < view.h; y++) {
		for (size_t x = 0; x < view.w; x++) {
			char input = scape->at(std::floor(x * (static_cast<double_t>(scape->w) / view.w)) + scape->x, std::floor(y * (static_cast<double_t>(scape->h) / view.h)) + scape->y);
			if (input != 0) {
				backBuffer.at(view.x + x, view.y + y) = input;
			}
			
		}
	}
}

void Renderer::clear()
{
	clear(&backBuffer);
	clear(&frontBuffer);
}

void Renderer::clear(Buffer * buffer) {
	buffer->string.clear();
	for (size_t y = 0; y < buffer->lineRows; y++) {
		for (size_t x = 0; x < buffer->lineColumns; x++) {
			buffer->string += ' ';
		}
		if (buffer->lineRows - 1 != y) {
			buffer->string += '\n';
		}
	}
}

/*
void Renderer::fullscreen() {
	window->resize(Window::Setting::Window::FULLSCREEN);
	setup();
}

void Renderer::r1024x720() {
	window->resize(1024,720);
	setup();
}

void Renderer::r800x600() {
	window->resize(800, 600);
	setup();
}
*/