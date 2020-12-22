#include "TileMap.h"


TileMap::TileMap() {}


const char TileMap::at(intmax_t x, intmax_t y) {
	
	char character;
	WorldCoordinate coordinate(x, y);
	auto tileMapIterator = tileMap.find(coordinate);
	if (tileMapIterator == tileMap.end()) {
		tileMapIterator = generateTile(x,y);
	}
	character = tileMapIterator->second.getGraphic();

	return character;
}

TileMap::uMapTile::iterator TileMap::generateTile(intmax_t x, intmax_t y) {
	WorldCoordinate coordinate(x, y);
	return tileMap.emplace(coordinate, Tile::generate(x, y)).first;
}

void TileMap::placeTile(Tile tile, intmax_t x, intmax_t y)
{
	WorldCoordinate position(x, y);
	auto iterator = tileMap.find(position);
	if (iterator != tileMap.end()) {
		tileMap.erase(position);
	}
	tileMap.emplace(position, tile);
}

