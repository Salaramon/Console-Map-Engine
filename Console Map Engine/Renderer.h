#pragma once

#include <string>
#include <iostream>

#include "Window.h"
#include "ViewFrame.h"
#include "Scape.h"

class Renderer
{
private:
	struct Buffer {

		char& at(size_t x, size_t y) {
			return string[y * lineColumns + y + x];
		}
		std::string string;
		size_t lineRows, lineColumns;

	};
public:
	Renderer(Window* target);
	Renderer(size_t x, size_t y);
	bool setup(Window *target);
	bool setup(size_t x, size_t y);
	void draw(size_t x, size_t y);
	void render();
	void render(Scape* scape, ViewFrame view);
	void clear();

	Buffer buffer;

	HANDLE window;

};

