#pragma once

#include <chrono>

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>

#include "Entity.h"
#include "WorldCoordinate.h"
#include "Event.h"

class Character : public Entity
{
	/*
	Character& operator=(Character&& other) noexcept {
		if(&other == this){
			return *this;
		}
		entityType = std::move(other.entityType);
		graphic = std::move(other.graphic);
		id = std::move(other.id);
		x = std::move(other.x);
		y = std::move(other.y);
		return *this;
	}
	*/

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& entityType;
		ar& graphic;
		ar& x;
		ar& y;
		ar& id;
		//ar& boost::serialization::base_object<Entity>(*this);
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& entityType;
		ar& graphic;
		ar& x;
		ar& y;
		ar& id;
		//ar& boost::serialization::base_object<Entity>(*this);

		immovable = false;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:

	Character(size_t x, size_t y);
	Character() {};

	

	bool immovable = true;

private:
	

};

