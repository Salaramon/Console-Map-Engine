#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <chrono>
#include <type_traits>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/split_member.hpp>

#include "WorldCoordinate.h"
#include "Tile.h"
#include "Scape.h"

class TileMap : public Scape
{

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& tileMap;
		ar& boost::serialization::base_object<Scape>(*this);
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& tileMap;
		ar& boost::serialization::base_object<Scape>(*this);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:

	TileMap(){}


	const char at(size_t x, size_t y) override;

	uMapTile tileMap;

	uMapTile::iterator generateTile(WorldCoordinate coordinate);
	void placeTile(Tile tile, size_t x, size_t y);

};