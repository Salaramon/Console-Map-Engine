#pragma once

#include <algorithm>

#include <boost/serialization/split_member.hpp>

#include "Character.h"
#include "ViewFrame.h"
#include "Event.h"
#include "TileMap.h"
#include "EntityMap.h"


class Player : public Event::Receiver{

	friend boost::serialization::access;

	template <class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar& character;
		ar& viewFrame;
		//ar& tileMap;
		//ar& entityMap;
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& character;
		ar& viewFrame;
		//ar& tileMap;
		//ar& entityMap;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:

	size_t runCycle = 0;
	double lastEventTime = 0;

	void response(Key key) override {
		if (!character.immovable) {
			intmax_t step = 1;
			intmax_t x = 0, y = 0;
			double walkSpeed = (double)1 / 20;

			if (key.charCode == Key::E && key.stateCode == Key::PRESSED) {
				tileMap->placeTile(Tile('#', true), character.x, character.y);
			}

			if (key.eventCycle == runCycle) {
				
				switch (key.charCode) {
				case Key::W:
					y = (-step);
					break;
				case Key::A:
					x = (-step);
					break;
				case Key::S:
					y = (step);
					break;
				case Key::D:
					x = (step);
					break;
				}
				if (tileMap->at(character.x + x, character.y + y) != '#') {
					character.move(x, y);
					if (outOfViewFrameBounds()) {
						tileMap->move(x, y);
						entityMap->move(x, y);
						std::cout << tileMap->x << ":" << tileMap->y << " " << entityMap->x << ":" << entityMap->y;
					}
				}
				
				lastEventTime = key.timeStamp;
			}

			if (key.timeStamp > walkSpeed + lastEventTime) {
				runCycle = key.eventCycle + 1;
			}
		}
	}

	bool outOfViewFrameBounds();

	Player();
	Player(Character character, ViewFrame viewFrame, TileMap * tileMap, EntityMap * entityMap);

	Character character;
	ViewFrame viewFrame;
	TileMap* tileMap;
	EntityMap* entityMap;

};

