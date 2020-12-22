#pragma once

#include <boost/serialization/split_member.hpp>

#include <Interfaces.h>



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
	
	static Tile generate(intmax_t x, intmax_t y);

private:
	char graphic;
	bool collidable;
};
