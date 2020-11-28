#pragma once

#include <memory>
#include <unordered_map>

#include <boost/serialization/split_member.hpp>

class Tile;
class Entity;


class WorldCoordinate
{

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& x;
		ar& y;
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& x;
		ar& y;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
	WorldCoordinate();
	WorldCoordinate(int x, int y);

	bool operator==(const WorldCoordinate& other) const;

	int x;
	int y;

	struct WorldCoordinateHasher {
		std::size_t operator()(const WorldCoordinate& type) const {
			std::size_t h1 = std::hash<int>{}(type.x);
			std::size_t h2 = std::hash<int>{}(type.y);
			return h1 ^ (h2 << 1);
		}
	};

	

};

typedef std::unordered_map<WorldCoordinate, Tile, WorldCoordinate::WorldCoordinateHasher> uMapTile;
