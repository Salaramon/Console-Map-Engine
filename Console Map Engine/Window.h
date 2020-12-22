#pragma once

#include <Windows.h>
#include <iostream>

class Window
{
public:

	enum class Setting {
		FULLSCREEN
	};

	Window(size_t w, size_t h);
	Window(Setting setting);
	void resize(size_t w, size_t h);
	void resize(Setting setting);

	size_t height, width;
private:

	void setup();

	HWND window;
	HANDLE windowHandle;
};

