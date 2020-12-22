#pragma once

#include <unordered_map>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/split_member.hpp>

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

	TileMap();

	struct WorldCoordinate
	{
		friend boost::serialization::access;

		template <class Archive>
		void save(Archive& ar, const unsigned int version) const {
			ar& x;
			ar& y;
		}
		template <class Archive>
		void load(Archive& ar, const unsigned int version) {
			ar& x;
			ar& y;
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER()

		WorldCoordinate() {}
		WorldCoordinate(size_t x, size_t y) : x(x), y(y) {}

		bool operator==(WorldCoordinate const& other) const {
			return other.x == x && other.y == y;
		}

		int x;
		int y;
	};


	struct WorldCoordinateHasher {
		std::size_t operator()(const WorldCoordinate& type) const {
			std::size_t h1 = std::hash<int>{}(type.x);
			std::size_t h2 = std::hash<int>{}(type.y);
			return h1 ^ (h2 << 1);
		}
	};

	const char at(intmax_t x, intmax_t y) override;
	void placeTile(Tile tile, intmax_t x, intmax_t y);

	typedef std::unordered_map<WorldCoordinate, Tile, WorldCoordinateHasher> uMapTile;

protected:
	virtual uMapTile::iterator generateTile(intmax_t x, intmax_t y);

private:

	uMapTile tileMap;

};