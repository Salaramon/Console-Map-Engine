#include "Entity.h"

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

size_t Entity::getID()
{
    return id;
}

void Entity::move(double_t x, double_t y)
{
	Entity::x += x;
	Entity::y += y;
}
