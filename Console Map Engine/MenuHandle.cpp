#include "MenuHandle.h"

MenuHandle::MenuHandle()
{
	enabled = true;
}

Menu* MenuHandle::getActiveMenu()
{
	return activeMenu;
}

void MenuHandle::addSubMenu(Menu* from, Menu* into) {
	menuList.emplace(into, from);
}

void MenuHandle::setKeyMenu(Menu* menu, KEY key)
{
	keyMenu = menu;
	keyMenuKey = key;
}

void MenuHandle::menuEnter(Menu* menu)
{
	activeMenu = menu;
}

void MenuHandle::menuReturn()
{
	if (activeMenu != keyMenu) {
		menuStackPop();
	}
	else {
		activeMenu = nullptr;
	}
}

void MenuHandle::setActiveMenu(Menu* menu)
{
	activeMenu = menu;
}

void MenuHandle::disableMenu()
{
	enabled = false;
}

void MenuHandle::enableMenu()
{
	enabled = true;
}

bool MenuHandle::isEnabled()
{
	return enabled;
}

void MenuHandle::menuStackPush(Menu* menu)
{
	menuStack.push_back(menu);
	setActiveMenu(menu);
}

void MenuHandle::menuStackPop()
{
	menuStack.pop_back();
	if (!menuStack.empty()) {
		setActiveMenu(menuStack.back());
	}
	else {
		activeMenu = keyMenu;
	}
}