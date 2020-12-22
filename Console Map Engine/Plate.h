#pragma once

#include <vector>
#include <string>

#include "Scape.h"

class Plate : public Scape
{
public:
	Plate() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
	Plate(size_t width, size_t height) {
		x = 0;
		y = 0;
		w = width;
		h = height;
	}

	const char at(intmax_t x, intmax_t y) override {
		std::vector<std::string> scape(h);
		for (size_t i = 0; i < h; i++) {
			if (i == 0 || i == h - 1) {
				scape[i].append(w, '+');
			}
				scape[i] += '+';
				scape[i].append(w-2, ' ');
				scape[i] += '+';
		}

		return scape[y][x];

	}

};

