#include "Player.h"

Player::Player() {}

Player::Player(Character character, ViewFrame viewFrame, TileMap* tileMap, EntityMap* entityMap) :
	character(character), viewFrame(viewFrame), tileMap(tileMap), entityMap(entityMap)
{}

bool Player::outOfViewFrameBounds()
{
	double_t minValue = (std::min)(tileMap->w, tileMap->h)/5.0;

	return !(
		(character.x < tileMap->x + static_cast<double_t>(tileMap->w) - minValue) &&
		(character.x > tileMap->x + minValue) &&
		(character.y < tileMap->y + static_cast<double_t>(tileMap->h) - minValue) &&
		(character.y > tileMap->y + minValue)
	);
}

ViewFrame Player::getViewFrame()
{
	return viewFrame;
}
