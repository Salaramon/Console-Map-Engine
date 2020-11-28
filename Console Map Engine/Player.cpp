#include "Player.h"

bool Player::outOfViewFrameBounds()
{
	intmax_t minValue = (std::min)(tileMap->w, tileMap->h)/5.0;

	return !(
		(character.x < tileMap->x + static_cast<intmax_t>(tileMap->w) - minValue) &&
		(character.x > tileMap->x + minValue) &&
		(character.y < tileMap->y + static_cast<intmax_t>(tileMap->h) - minValue) &&
		(character.y > tileMap->y + minValue)
	);
}

Player::Player(){}

Player::Player(Character character, ViewFrame viewFrame, TileMap* tileMap, EntityMap * entityMap) :
	character(character), viewFrame(viewFrame), tileMap(tileMap), entityMap(entityMap)
{}

