#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <map>

#include "Event.h"
#include "Scape.h"

class Menu : public Event::Receiver, public Scape
{
public:

	Menu() {
		x = 0;
		y = 0;
		selection = 0;
		accessed = false;
	};
	Menu(const size_t size) {
		selection = 0;
		accessed = false;
		slots.resize(size);
		x = 0;
		y = 0;
	};

	const char at(size_t x, size_t y) override {
		std::vector<std::string> scape(slots.size());
		for (size_t i = 0; i < slots.size(); i++) {
			if (i == selection) {
				scape[i] += "[" + slots[i].label + "]";
				scape[i].append(longestLabelCharCount + 2 - scape[i].size(), ' ');
			}
			else {
				scape[i] += slots[i].label;
				scape[i].append(longestLabelCharCount + 2 - scape[i].size(), ' ');
			}
		}

		return scape[y][x];

	}

	void response(Key key) override
	{
		if (accessed) {
			if (key.charCode == Key::W && key.stateCode == Key::PRESSED) {
				up();
			}
			if (key.charCode == Key::S && key.stateCode == Key::PRESSED) {
				down();
			}
			if (key.charCode == Key::E && key.stateCode == Key::PRESSED) {
				select();
			}
		}

		if (escLaunchable && key.charCode == Key::ESC && key.stateCode == Key::PRESSED) {
			accessed = !accessed;
		}
		if (swapped) {
			swapped = false;
			accessed = !accessed;
		}
	}

	
	

	struct Element {
		Element() {}
		Element(const Element& other) :
			label(other.label),
			function(other.function)
		{}

		std::function<void()> function;
		std::string label;
	};

	Element& operator[](const size_t index) {
		return slots[index];
	}
	
	template<class T>
	void createElement(size_t slot, std::string label, T* object, void(T::* func)()) {
		if (slot >= slots.size()) {
			slots.resize(slot+1);
		}
		if (label.size() > longestLabelCharCount) {
			longestLabelCharCount = label.size();
			w = longestLabelCharCount + 2;
		}
		h = slots.size();
		Element elm;
		elm.function = std::bind(func, object);
		elm.label = label;
		slots[slot] = elm;
	}

	void render() {
		std::string renderedScreen = "";
		for (size_t i = 0; i < slots.size(); i++) {
			if (i == selection) {
				renderedScreen += "[" + slots[i].label + "]\n";
			}
			else {
				renderedScreen += slots[i].label + "\n";
			}
		}
		system("CLS");
		std::cout << renderedScreen;
	}
	
	void up() {
		if (selection > 0) {
			selection--;
		}
	}
	void down() {
		if (selection < slots.size()-1) {
			selection++;
		}
	}
	void select() {
		slots[selection].function();
	}
	void exit() {
		accessed = false;
	}
	void setESCLaunchable(bool launchable) {
		escLaunchable = launchable;
	}
	
	struct MenuSwap {
		MenuSwap(Menu* menu1, Menu* menu2) : menu1(menu1), menu2(menu2) {}
		void swap() {
			if (menu1->accessed ^ menu2->accessed) {
				menu1->swapped = true;
				menu2->swapped = true;
			}
		}
		Menu* menu1;
		Menu* menu2;
	};

	bool accessed;
	bool swapped;
private:
	bool escLaunchable = false;
	std::vector <Element> slots;
	size_t selection;
	size_t longestLabelCharCount;

	
};


