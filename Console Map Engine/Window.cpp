#include "Window.h"

Window::Window(size_t w, size_t h)
{
	setup();
	resize(w+16, h+15); //MAGIC NUMBERS
}

Window::Window(Setting setting)
{
	setup();
	if (setting == Setting::FULLSCREEN) {
		resize(GetSystemMetrics(SM_CXSCREEN)+16, GetSystemMetrics(SM_CYSCREEN)+15);
	}
	
}

void Window::setup()
{

	windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	window = GetConsoleWindow();
	
	//Set console font.
	CONSOLE_FONT_INFOEX cf = { 0 };
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = 8;
	cf.dwFontSize.Y = 8;
	wcscpy_s(cf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(windowHandle, 0, &cf);

	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(windowHandle, &binfo);
	COORD coord;
	binfo.dwSize.Y;
	coord.X = binfo.srWindow.Right + 1;
	coord.Y = binfo.srWindow.Bottom + 1;
	//std::cout << binfo.srWindow.Top << std::endl;
	//system("pause");
	SetConsoleScreenBufferSize(windowHandle, coord);

	//Hide console cursor. !DOES NOT WORK ANYMORE FOR MAGICAL REASONS
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.dwSize = 100;
	cinfo.bVisible = FALSE;
	SetConsoleCursorInfo(windowHandle, &cinfo);

}

void Window::resize(size_t w, size_t h)
{
	width = w;
	height = h;
	if (GetSystemMetrics(SM_CXSCREEN)+16 == w && GetSystemMetrics(SM_CYSCREEN)+15 == h) {
		ShowWindow(window, SW_MAXIMIZE);
	}
	else {
		size_t x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
		size_t y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
		MoveWindow(window, x, y, w, h, true);
	}
}

void Window::resize(Setting setting)
{
	if (setting == Setting::FULLSCREEN) {
		resize(GetSystemMetrics(SM_CXSCREEN) + 16, GetSystemMetrics(SM_CYSCREEN) + 15);
	}
}
