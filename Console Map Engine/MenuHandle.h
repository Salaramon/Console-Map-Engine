#pragma once

#include <map>

#include "Menu.h"
#include "Event.h"

class MenuHandle : public Event::Receiver
{
public:

	MenuHandle();

	void response(Keys keys, double_t timeStamp) override
	{
		if (enabled) {
			for (Key key : keys) {
				if (activeMenu != nullptr) {
					if (key.charCode == Key::W && key.stateCode == Key::PRESSED) {
						activeMenu->up();
					}
					if (key.charCode == Key::S && key.stateCode == Key::PRESSED) {
						activeMenu->down();
					}
					if (key.charCode == Key::E && key.stateCode == Key::PRESSED) {
						activeMenu->select();
					}
					if (key.charCode == Key::ESC && key.stateCode == Key::PRESSED) {
						menuReturn();
					}
				}
				else if (key.charCode == keyMenuKey && key.stateCode == Key::PRESSED) {
					activeMenu = keyMenu;
				}
			}
		}
	}

	struct SubMenu {
		SubMenu(Menu* menu) : menu(menu) {
		};
		void addHandle(MenuHandle* handle) {
			handles.push_back(handle);
		}
		void enter() {
			for (MenuHandle * handle : handles) {
				if (handle->isEnabled()) {
					handle->menuStackPush(menu);
				}
			}
		}
		std::vector<MenuHandle*> handles;
		Menu* menu;
	};

	Menu* getActiveMenu();

	void addSubMenu(Menu* from, Menu* into);
	void setKeyMenu(Menu* menu, KEY key);

	void menuEnter(Menu* menu);
	void menuReturn();
	void setActiveMenu(Menu* menu);
	void disableMenu();
	void enableMenu();
	bool isEnabled();
	void menuStackPush(Menu* menu);

	void menuStackPop();
	
private:
	std::vector<Menu*> menuStack;
	std::unordered_map<Menu*, Menu*> menuList;
	Menu* activeMenu;
	Menu* keyMenu;
	KEY keyMenuKey;
	bool enabled;
};

