#include "Entity.h"
#include "EntityMap.h"

size_t Entity::nextID = 0;

Entity::Entity() : x(0), y(0)/*, owner(nullptr)*/ {
	id = nextID;
	nextID++;
}

Entity::Entity(size_t x, size_t y) : x(x), y(y)/*, owner(nullptr)*/ {
	id = nextID;
	nextID++;
}


char Entity::getGraphic()
{
	return graphic;
}

WorldCoordinate Entity::getPosition()
{
	return WorldCoordinate(x,y);
}
/*
void Entity::setOwner(EntityMap* entityMap)
{
	owner = entityMap;
}
*/
void Entity::move(size_t x, size_t y)
{
	Entity::x += x;
	Entity::y += y;
}
