#pragma once

#include <vector>
#include <string>
#include <functional>

#include "Event.h"
#include "Scape.h"

class Menu : public Scape
{
public:

	Menu();
	Menu(const size_t size);

	const char at(intmax_t x, intmax_t y) override {
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
	void createEntry(size_t slot, std::string label, T* object, void(T::* func)());
	
	void up();
	void down();
	void select();
	
private:
	std::vector<Element> slots;
	size_t selection;
	size_t longestLabelCharCount;
};

template<class T>
inline void Menu::createEntry(size_t slot, std::string label, T* object, void(T::* func)())
{
	if (slot >= slots.size()) {
		slots.resize(slot + 1);
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
