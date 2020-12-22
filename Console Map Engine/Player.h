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
	}
	template <class Archive>
	void load(Archive& ar, const unsigned int version)  {
		ar& character;
		ar& viewFrame;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
	void response(Keys keys, double_t timeStamp) override {
		if (!character.immovable) {
			intmax_t x = 0, y = 0;
			double_t walkSpeed = 15;

			for (Key key : keys) {
				switch (key.charCode) {
				case Key::W:
					y = -1;
					break;
				case Key::A:
					x = -1;
					break;
				case Key::S:
					y = 1;
					break;
				case Key::D:
					x = 1;
					break;
				}

				if (key.charCode == Key::E && key.stateCode == Key::PRESSED) {
					tileMap->placeTile(Tile('#', true), character.x, character.y);
				}

				if (key.charCode == Key::LSHIFT) {
					walkSpeed /= 3;
				}
			}

			if (!(x == 0 && y == 0)) {
				double_t length = sqrt(std::pow(x, 2) + std::pow(y, 2));
				double_t moveX = ((double_t)x / length) * walkSpeed * Event::deltaTime;
				double_t moveY = ((double_t)y / length) * walkSpeed * Event::deltaTime;
				

				if (tileMap->at(std::trunc(character.x) + x, std::trunc(character.y) + y) != '#') {
					character.move(moveX, moveY);
					if (outOfViewFrameBounds()) {
						tileMap->move(moveX, moveY);
						entityMap->move(moveX, moveY);
					}
				}
			}
		}
	}

	Player();
	Player(Character character, ViewFrame viewFrame, TileMap* tileMap, EntityMap* entityMap);

	ViewFrame getViewFrame();

	Character character;
	TileMap* tileMap;
	EntityMap* entityMap;
private:
	bool outOfViewFrameBounds();

	ViewFrame viewFrame;

};

