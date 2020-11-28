#include "WorldCoordinate.h"
#include "Tile.h"
#include "Entity.h"

WorldCoordinate::WorldCoordinate() {};

WorldCoordinate::WorldCoordinate(int x, int y) {
	WorldCoordinate::x = x;
	WorldCoordinate::y = y;
}

bool WorldCoordinate::operator==(const WorldCoordinate& other) const {
	return (x == other.x) && (y == other.y);
}