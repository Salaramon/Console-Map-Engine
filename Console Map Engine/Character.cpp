#include "Character.h"

Character::Character(size_t x, size_t y) : Entity(x,y)
{
	entityType = Entity::Type::PLAYER;
	graphic = 'O';
}
