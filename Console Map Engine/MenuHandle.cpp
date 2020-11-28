#include "MenuHandle.h"

Menu* MenuHandle::getActiveMenu()
{
	for (auto menu : menuList) {
		if (menu->accessed) {
			return menu;
		}
	}

	return nullptr;
}

void MenuHandle::addMenu(Menu* menu)
{
	menuList.push_back(menu);
}
