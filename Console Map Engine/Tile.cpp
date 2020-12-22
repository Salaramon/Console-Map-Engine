#include "Tile.h"


Tile::Tile() : collidable(false)
{
}

Tile::Tile(char graphic, bool collidable) :
	graphic(graphic),
	collidable(collidable)
{}

Tile::~Tile()
{
}

char Tile::getGraphic()
{
	return graphic;
}

Tile Tile::generate(intmax_t x, intmax_t y)
{
	size_t x1 = std::hash<int>{}((x+SIZE_MAX/2)%123456789);
	size_t y1 = std::hash<int>{}((y + SIZE_MAX / 2) % 987654321);

	size_t r = std::hash<size_t>{}(x1 ^ y1);
	
	
	Tile tree;
	tree.collidable = true;
	tree.graphic = 'T';
	Tile empty;
	empty.graphic = ' ';

	if (r > SIZE_MAX*0.95) {
		return tree;
	}
	else {
		return empty;
	}
}
