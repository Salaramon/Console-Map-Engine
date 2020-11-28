#pragma once

#include <memory>
#include <algorithm>
#include <unordered_map>

#include <boost/serialization/split_member.hpp>

#include <Interfaces.h>

#include "WorldCoordinate.h"



class Tile
{

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& graphic;
		ar& collidable;
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& graphic;
		ar& collidable;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
	Tile();
	Tile(char graphic, bool collidable);
	~Tile();

	char getGraphic();
	
	static Tile generate(WorldCoordinate seed);

private:
	char graphic;
	bool collidable;
};
