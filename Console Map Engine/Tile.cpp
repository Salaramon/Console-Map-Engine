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

Tile Tile::generate(WorldCoordinate seed)
{
	size_t x1 = std::hash<int>{}((seed.x+SIZE_MAX/2)%123456789);
	size_t y1 = std::hash<int>{}((seed.y + SIZE_MAX / 2) % 987654321);

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
	
	//0.06 * std::tan(randomNumber1) * SIZE_MAX / 2
}
