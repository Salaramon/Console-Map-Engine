#include "EntityMap.h"

void EntityMap::addEntity(Entity *entity)
{
	entities.push_back(entity);
}

void EntityMap::removeEntity(Entity entity)
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->getID() == entity.getID()) {
			entities.erase(it);
			break;
		}
	}
}

size_t EntityMap::getIndex(Entity entity) {
	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i]->getID() == entity.getID()) {
			return i;
		}
	}
	return entities.size();
}

size_t EntityMap::getIndex(intmax_t x, intmax_t y) {
	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i]->x == x && entities[i]->y == y) {
			return i;
		}
	}
	return entities.size();
}

void EntityMap::removeAllEntities()
{
	entities.clear();
}
