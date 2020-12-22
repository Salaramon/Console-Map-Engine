#pragma once

#include <boost/serialization/split_member.hpp>

#include <Interfaces.h>

class Entity
{
	
	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {

	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {

	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()
	
public:

	Entity();
	Entity(size_t x, size_t y);

	bool operator==(Entity const& other) const {
		return other.id == id;
	}

	struct EntityHasher {
		std::size_t operator()(const Entity& type) const {
			std::size_t h = std::hash<size_t>{}(type.id);
			return h;
		}
	};

	enum class Type {
		NONE,
		PLAYER,
		WILD
	};

	char getGraphic();
	size_t getID();

	virtual void move(double_t x, double_t y);

	double_t x, y;
protected:

	size_t id;
	static size_t nextID;

	Type entityType = Type::NONE;
	char graphic = '?';
};

