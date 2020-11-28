#pragma once

#include <vector>

#include "Menu.h"
#include "ViewFrame.h"

class MenuHandle
{
public:
	Menu* getActiveMenu();
	void addMenu(Menu* menu);
	
private:
	std::vector<Menu*> menuList;

};

