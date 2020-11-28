#pragma once

#include <boost/serialization/split_member.hpp>

#include <Interfaces.h>

#include "WorldCoordinate.h"


class EntityMap;

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

	enum class Type {
		NONE,
		PLAYER,
		WILD
	};

	Entity(size_t x, size_t y);
	char getGraphic();

	bool operator==(Entity const& other) const {
		return other.id == id;
	}
	struct EntityHasher {
		std::size_t operator()(const Entity& type) const {
			std::size_t h = std::hash<int>{}(type.id);
			return h;
		}
	};

	WorldCoordinate getPosition();

	//void setOwner(EntityMap* entityMap);

	size_t id;
	static size_t nextID;

	typedef std::unordered_multimap<Entity, WorldCoordinate, EntityHasher> uMultimapEntityCoordinate;
	intmax_t x, y;

	virtual void move(size_t x, size_t y);
protected:

	//EntityMap* owner;
	Type entityType = Type::NONE;
	char graphic = '?';
};
