#include "EntityMap.h"

void EntityMap::addEntity(Entity *entity)
{
	entities.push_back(entity);
	//entities.back()->setOwner(this);
}

void EntityMap::removeEntity(Entity entity)
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->id == entity.id) {
			entities.erase(it);
			break;
		}
	}
}

size_t EntityMap::getIndex(Entity entity) {
	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i]->id == entity.id) {
			return i;
		}
	}
	return entities.size();
}

size_t EntityMap::getIndex(WorldCoordinate position) {
	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i]->getPosition() == position) {
			return i;
		}
	}
	return entities.size();
}

void EntityMap::removeAllEntities()
{
	entities.clear();
}
