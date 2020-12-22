#include "Menu.h"

Menu::Menu()
{
	x = 0;
	y = 0;
	selection = 0;
}

Menu::Menu(const size_t size)
{
	selection = 0;
	slots.resize(size);
	x = 0;
	y = 0;
}

void Menu::up()
{
	if (selection > 0) {
		selection--;
	}
}

void Menu::down()
{
	if (selection < slots.size() - 1) {
		selection++;
	}
}

void Menu::select()
{
	slots[selection].function();
}
