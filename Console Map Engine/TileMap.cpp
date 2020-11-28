#include "TileMap.h"


const char TileMap::at(size_t x, size_t y) {
	
	char character;
	WorldCoordinate coordinate = WorldCoordinate(x, y);
	auto tileMapIterator = tileMap.find(coordinate);
	if (tileMapIterator == tileMap.end()) {
		tileMapIterator = generateTile(coordinate);
	}
	character = tileMapIterator->second.getGraphic();

	return character;
}

uMapTile::iterator TileMap::generateTile(WorldCoordinate coordinate) {
	return tileMap.emplace(coordinate, Tile::generate(coordinate)).first;
}

void TileMap::placeTile(Tile tile, size_t x, size_t y)
{
	WorldCoordinate position(x, y);
	auto iterator = tileMap.find(position);
	if (iterator != tileMap.end()) {
		tileMap.erase(position);
	}
	tileMap.emplace(position, tile);
}
