#pragma once

#include <Windows.h>
#include <iostream>

class Window
{
public:
	struct Setting{
		enum class Window {
			FULLSCREEN
		};
	};
	Window(size_t w, size_t h);
	Window(Setting::Window setting);
	bool setup(size_t w, size_t h);
	bool setup(Setting::Window setting);
	void resize(size_t w, size_t h);
	void resize(Setting::Window setting);

	size_t height, width;
private:
	bool initialize();

	HWND window;
	HANDLE windowHandle;
};

