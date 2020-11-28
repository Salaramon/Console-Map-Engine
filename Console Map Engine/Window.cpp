#include "Window.h"

Window::Window(size_t w, size_t h)
{
	windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	window = GetConsoleWindow();
	resize(w,h);
	setup(w, h);
}

Window::Window(Setting::Window setting)
{
	setup(setting);
}

bool Window::setup(size_t w, size_t h)
{
	bool success = true;

	//Initialize winow
	if (!initialize()) {
		success = false;
	}
	else{

		//Resize window
		resize(w, h);
		ShowWindow(window, SW_SHOW);
	}

	return success;
}

bool Window::setup(Setting::Window setting)
{
	bool success = true;

	//Initialize window
	if (!initialize()) {
		success = false;
	}
	else {
		//Resize window
		resize(setting);
		ShowWindow(window, SW_SHOW);
	}
	

	return false;
}

void Window::resize(size_t w, size_t h)
{
	width = w;
	height = h;

	COORD newSize = { w,h };
	size_t x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (w / 2);
	size_t y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (h / 2);
	//SetConsoleScreenBufferSize(windowHandle, newSize);
	MoveWindow(window, x, y, w, h, true);
}

void Window::resize(Setting::Window setting)
{
	if (setting == Setting::Window::FULLSCREEN) {
		ShowWindow(window, SW_MAXIMIZE);
	}
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CXSCREEN);
}

bool Window::initialize()
{
	bool success = true;
	

	//Set console font.
	CONSOLE_FONT_INFOEX cf = { 0 };
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = 8;
	cf.dwFontSize.Y = 8;
	wcscpy_s(cf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(windowHandle, 0, &cf);

	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(windowHandle,&binfo);
	COORD coord;
	coord.X = binfo.dwSize.X;
	coord.Y = binfo.dwSize.Y-35;
	SetConsoleScreenBufferSize(windowHandle, coord);
	
	if (window == 0) {
		success = false;
	}
	else {
		//Hides window during setup
		ShowWindow(window, SW_HIDE);

		ShowScrollBar(window, SB_BOTH, false);

	}

	//Hide console cursor.
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.dwSize = 100;
	cinfo.bVisible = FALSE;
	SetConsoleCursorInfo(windowHandle, &cinfo);

	return success;
}
