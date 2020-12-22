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
		bool operator!=(Buffer& other) {
			return
				string != other.string &&
				lineRows != other.lineRows &&
				lineColumns != other.lineColumns;
		}
		char& at(size_t x, size_t y) {
			return string[y * lineColumns + y + x];
		}
		std::string string;
		size_t lineRows, lineColumns;
	};
public:
	Renderer(Window* target);
	bool setup(Window *target);
	bool setup();

	//Draw directly to the renderer
	void draw(size_t x, size_t y);

	//Update the buffer
	void update(Scape* scape, ViewFrame view);

	//Render to screen
	void render();

	size_t getHeight();
	size_t getWidth();

	/*
	//Resolution options
	void fullscreen();
	void r1024x720();
	void r800x600();
	*/

private:
	//Clear all buffers
	void clear();
	void clear(Buffer* buffer);

	Buffer backBuffer;
	Buffer frontBuffer;

	Window* window;

};

