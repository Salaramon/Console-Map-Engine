// Console Map Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <ratio>
#include <functional>

#include <boost/serialization/serialization.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>

#include <MidiFile.h>

#include "csv.h"

#include "Event.h"
#include "Player.h"
#include "TileMap.h"
#include "Music.h"
#include "Window.h"
#include "Renderer.h"
#include "Character.h"
#include "GameState.h"
#include "Menu.h"
#include "EntityMap.h"
#include "MenuHandle.h"


int main()
{
	const size_t zoom = 1;

	Window window(1024, 720); //Fullscreen is odd
	Renderer renderer(&window); //other overload character size

	TileMap world;
	world.w = renderer.buffer.lineColumns/zoom;
	world.h = renderer.buffer.lineRows/zoom;
	world.x = -static_cast<intmax_t>(renderer.buffer.lineColumns / (2 * zoom));
	world.y = -static_cast<intmax_t>(renderer.buffer.lineRows/ (2 * zoom));

	EntityMap entityMap;
	entityMap.w = renderer.buffer.lineColumns / zoom;
	entityMap.h = renderer.buffer.lineRows / zoom;
	entityMap.x = -static_cast<intmax_t>(renderer.buffer.lineColumns / (2 * zoom));
	entityMap.y = -static_cast<intmax_t>(renderer.buffer.lineRows / (2 * zoom));


	Event events;

	Player player(
		Character(0, 0),
		ViewFrame(0, 0, renderer.buffer.lineColumns, renderer.buffer.lineRows),
		&world,
		&entityMap
	);
	entityMap.addEntity(&player.character);

	Music mainTheme;
	mainTheme.load("Karl's & Isak's Dungeon Adventure (LetsGo).mid");
	mainTheme.loop();
	mainTheme.play();


	Menu mainMenu;
	Menu optionsMenu;
	Menu playerMenu;
	Menu playerOptionsMenu;

	mainMenu.accessed = true;

	GameState game(&player, &mainMenu, &playerMenu, &world, &entityMap);

	
	Menu::MenuSwap swapMainMenuOptions(&mainMenu, &optionsMenu);

	mainMenu.createElement(0, "Continue", &game, &GameState::loadGame);
	mainMenu.createElement(1, "New Game", &game, &GameState::newGame);
	mainMenu.createElement(2, "Options", &swapMainMenuOptions, &Menu::MenuSwap::swap);
	mainMenu.createElement(3, "Quit", &game, &GameState::quitGame);

	optionsMenu.createElement(0, "Play", &mainTheme, &Music::play);
	optionsMenu.createElement(1, "Pause", &mainTheme, &Music::pause); //Not working
	optionsMenu.createElement(2, "Stop", &mainTheme, &Music::stop);
	optionsMenu.createElement(3, "Return", &swapMainMenuOptions, &Menu::MenuSwap::swap);


	Menu::MenuSwap swapPlayerMenuOptions(&playerMenu, &playerOptionsMenu);

	playerMenu.createElement(0, "Options", &swapPlayerMenuOptions, &Menu::MenuSwap::swap);
	playerMenu.createElement(1, "Save", &game, &GameState::saveGame);
	playerMenu.createElement(2, "Load", &game, &GameState::loadGame);
	playerMenu.createElement(3, "Quit", &game, &GameState::quitGame);

	playerOptionsMenu.createElement(0, "Play", &mainTheme, &Music::play);
	playerOptionsMenu.createElement(1, "Pause", &mainTheme, &Music::pause); //Not working
	playerOptionsMenu.createElement(2, "Stop", &mainTheme, &Music::stop);
	playerOptionsMenu.createElement(3, "Return", &swapPlayerMenuOptions, &Menu::MenuSwap::swap);
	

	MenuHandle menuController;
	menuController.addMenu(&mainMenu);
	menuController.addMenu(&optionsMenu);
	menuController.addMenu(&playerMenu);
	menuController.addMenu(&playerOptionsMenu);


	events.addReceiver(&player, 0);
	events.addReceiver(&playerMenu,0);
	events.addReceiver(&optionsMenu, 0);
	events.addReceiver(&playerOptionsMenu, 0);
	events.addReceiver(&mainMenu, 0);
	events.addReceiver(&game, 0);

	std::chrono::steady_clock::time_point gameTimerStart = std::chrono::steady_clock::now();
	double frameRate = 1 / 20;

    while (game.isRunning()) {
        events.transmitEvents();

		if (game.anyEvent() && frameRate < std::chrono::duration<double>(std::chrono::steady_clock::now() - gameTimerStart).count()) {
			gameTimerStart = std::chrono::steady_clock::now();

			if (game.gameplayState) {
				renderer.render(&world, player.viewFrame);
				renderer.render(&entityMap, player.viewFrame);
			}
			Menu* activeMenu = menuController.getActiveMenu();
			if (activeMenu != nullptr) {
				ViewFrame menuFrame = activeMenu->getViewFrame((renderer.buffer.lineColumns / 2) - (activeMenu->w / 2), (renderer.buffer.lineRows / 2) - (activeMenu->h / 2));
				renderer.render(activeMenu, menuFrame);
				if (!player.character.immovable) {
					player.character.immovable = true;
				}
			}
			else {
				if (player.character.immovable) {
					player.character.immovable = false;
				}
			}
			
		}
		mainTheme.run();
        
		
    }
	mainTheme.stop();
}


/*
Need to update interface with this line
tags.emplace(tag, static_cast<size_t>(std::distance(observers.begin(),observers.end() - 1)));
*/

/*
TODO
Fix standalone release
fix fullscreen
contemplate event structure alterations
get feedback
*/