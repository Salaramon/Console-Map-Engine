#pragma once
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "Event.h"
#include "MenuHandle.h"
#include "Player.h"
#include "TileMap.h"
#include "EntityMap.h"

class GameState
{
public:
	GameState(Player * player, MenuHandle * mainMenu, MenuHandle * playerMenu, TileMap * tileMap, EntityMap * entityMap) :
		player(player), mainMenu(mainMenu), playerMenu(playerMenu), tileMap(tileMap), entityMap(entityMap)
	{}
		
	bool isRunning();
	bool inGame();

	void quitGame();
	void newGame();
	void loadGame();
	void saveGame();

private:
	void initializeGame();

	bool quit = false;
	bool eventHappened = true;
	bool gameplayState = false;
	bool gameWasLoaded = false;

	Player* player;
	MenuHandle* mainMenu;
	MenuHandle* playerMenu;
	TileMap* tileMap;
	EntityMap * entityMap;
};

