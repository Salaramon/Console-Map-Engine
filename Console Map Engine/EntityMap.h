#pragma once

#include <vector>
#include <map>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>

#include "Scape.h"
#include "Entity.h"

class EntityMap : public Scape
{
	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& boost::serialization::base_object<Scape>(*this);
		
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Scape>(*this);
		entities.clear();
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
	const char at(intmax_t x, intmax_t y) override {
		size_t index = getIndex(x, y);
		if (index == entities.size()) {
			return 0;
		}
		else {
			return entities[index]->getGraphic();
		}
	}

	std::vector<Entity*> entities;
	void addEntity(Entity *entity);
	void removeEntity(Entity entity);
	void removeAllEntities();

	size_t getIndex(Entity entity);

	size_t getIndex(intmax_t x, intmax_t y);
	
};

