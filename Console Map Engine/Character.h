#pragma once

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>

#include "Entity.h"

class Character : public Entity
{

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

