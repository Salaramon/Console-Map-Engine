#pragma once
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "Event.h"
#include "Menu.h"
#include "Player.h"
#include "TileMap.h"
#include "EntityMap.h"

class GameState : public Event::Receiver
{
public:
	GameState(Player * player, Menu * mainMenu, Menu * playerMenu, TileMap * tileMap, EntityMap * entityMap) :
		player(player), mainMenu(mainMenu), playerMenu(playerMenu), tileMap(tileMap), entityMap(entityMap)
	{}

	void response(Key key) override
	{
		eventHappened = true;
	}
		
	
	bool anyEvent() {
		if (eventHappened) {
			eventHappened = false;
			return true;
		}
		return false;
	}
	void quitGame() {
		quit = true;
	}
	
	void setGame() {
		playerMenu->setESCLaunchable(true);
		gameplayState = true;
		player->character.immovable = false;
		mainMenu->accessed = false;
		playerMenu->accessed = false;
	}

	void newGame() {
		setGame();
	}
	void loadGame() {
		setGame();
		gameWasLoaded = true;
		std::ifstream saveFile("save1");
		boost::archive::text_iarchive in(saveFile);
		Player tempPlayer;
		TileMap tempTileMap;
		EntityMap tempEntityMap;
		in >> tempTileMap >> tempEntityMap >> tempPlayer;
		*player = std::move(tempPlayer);
		*tileMap = std::move(tempTileMap);
		*entityMap = std::move(tempEntityMap);
		entityMap->addEntity(&player->character);
		player->tileMap = tileMap;
		player->entityMap = entityMap;
	}

	void saveGame() {
		playerMenu->accessed = false;
		std::ofstream saveFile("save1");
		boost::archive::text_oarchive out(saveFile);
		out << *tileMap << *entityMap << *player;
	}

	bool renderGame = false;
	
	bool isRunning() { return !quit; }
	bool quit = false;
	bool eventHappened = true;
	bool gameplayState = false;
	bool gameWasLoaded = false;

	Player* player;
	Menu* mainMenu;
	Menu* playerMenu;
	TileMap* tileMap;
	EntityMap * entityMap;
};

