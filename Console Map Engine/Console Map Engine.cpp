// Console Map Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include "Plate.h"

void initializeMapScape(Renderer* renderer, Scape* scape) {
	const size_t zoom = 1;
	scape->w = renderer->getWidth() / zoom;
	scape->h = renderer->getHeight() / zoom;
	scape->x = -static_cast<intmax_t>(renderer->getWidth() / (2 * zoom));
	scape->y = -static_cast<intmax_t>(renderer->getHeight() / (2 * zoom));
}


int main()
{
	//Create window.
	Window window(1024,720); 
	Renderer renderer(&window); 


	//Create and initialize game world.
	TileMap world;
	EntityMap entities;

	initializeMapScape(&renderer, &world);
	initializeMapScape(&renderer, &entities);


	//Create player character in game world.
	Player player(
		Character(0, 0),
		ViewFrame(0, 0, renderer.getWidth(), renderer.getHeight()),
		&world,
		&entities
	);
	entities.addEntity(&player.character);


	//Setup and play game music
	Music mainTheme;
	mainTheme.load("Karl's & Isak's Dungeon Adventure (LetsGo).mid");
	mainTheme.loop();
	mainTheme.play();


	//Initialize menu structure
	MenuHandle mainMenuController;
	MenuHandle playerMenuController;

	Menu mainMenu;
	Menu optionsMenu;
	Menu playerMenu;
	Menu musicMenu;
	//Menu resolutionMenu;

	//Setup key menus
	mainMenuController.setKeyMenu(&mainMenu, Key::ESC);
	playerMenuController.setKeyMenu(&playerMenu, Key::ESC);
	mainMenuController.setActiveMenu(&mainMenu);
	playerMenuController.disableMenu();

	//Setup sub-menus
	MenuHandle::SubMenu intoOptionsMenu(&optionsMenu);
	intoOptionsMenu.addHandle(&mainMenuController);
	intoOptionsMenu.addHandle(&playerMenuController);
	/*
	MenuHandle::SubMenu intoResolutionMenu(&resolutionMenu);
	intoResolutionMenu.addHandle(&mainMenuController);
	intoResolutionMenu.addHandle(&playerMenuController);
	*/

	MenuHandle::SubMenu intoMusicMenu(&musicMenu);
	intoMusicMenu.addHandle(&mainMenuController);
	intoMusicMenu.addHandle(&playerMenuController);


	//Setup game state controller... handles cross communication on appklication wide events.
	GameState game(&player, &mainMenuController, &playerMenuController, &world, &entities);


	//Construct menus
	mainMenu.createEntry(0, "Continue", &game, &GameState::loadGame);
	mainMenu.createEntry(1, "New Game", &game, &GameState::newGame);
	mainMenu.createEntry(2, "Options", &intoOptionsMenu, &MenuHandle::SubMenu::enter);
	mainMenu.createEntry(3, "Quit", &game, &GameState::quitGame);

	//optionsMenu.createEntry(0, "Resolution", &intoResolutionMenu, &MenuHandle::SubMenu::enter);
	optionsMenu.createEntry(0, "Music", &intoMusicMenu, &MenuHandle::SubMenu::enter);

	/*
	resolutionMenu.createEntry(0, "Fullscreen", &renderer, &Renderer::fullscreen);
	resolutionMenu.createEntry(1, "800x600", &renderer, &Renderer::r800x600);
	resolutionMenu.createEntry(2, "1024x720", &renderer, &Renderer::r1024x720);
	*/

	musicMenu.createEntry(0, "Play", &mainTheme, &Music::play);
	musicMenu.createEntry(1, "Pause", &mainTheme, &Music::pause);
	musicMenu.createEntry(2, "Stop", &mainTheme, &Music::stop);

	playerMenu.createEntry(0, "Save", &game, &GameState::saveGame);
	playerMenu.createEntry(1, "Load", &game, &GameState::loadGame);
	playerMenu.createEntry(2, "Options", &intoOptionsMenu, &MenuHandle::SubMenu::enter);
	playerMenu.createEntry(3, "Quit", &game, &GameState::quitGame);


	//Opaque blank square.
	Plate menuPlate(20, 10);


	//Add event client objects
	Event events;
	events.addReceiver(&player, 0);
	events.addReceiver(&mainMenuController,1);
	events.addReceiver(&playerMenuController, 0);


	//Max framerate
	double frameRate = 1 / 60;
	//Runs game loop once
	bool launch = true;


	//Ladies and gentlemen, what you all have been waiting for... the game loop!
    while (game.isRunning()) {
        events.pollEvents();

		if (events.anyEvent()  || launch) {
			events.transmitEvents();
			
			//Render world
			if (game.inGame() && frameRate < Event::timeElapsed) {
				renderer.update(&world, player.getViewFrame());
				renderer.update(&entities, player.getViewFrame());
			}
			
			//Get menu if active and render
			Menu* activeMenu = nullptr;
			if (mainMenuController.isEnabled()) {
				activeMenu = mainMenuController.getActiveMenu();
			}
			if (playerMenuController.isEnabled()) {
				activeMenu = playerMenuController.getActiveMenu();
			}
			if (activeMenu != nullptr) {
				ViewFrame menuPlateFrame = menuPlate.getViewFrame((renderer.getWidth() / 2) - (menuPlate.w / 2), (renderer.getHeight() / 2) - (menuPlate.h / 2));
				ViewFrame menuFrame = activeMenu->getViewFrame((renderer.getWidth() / 2) - (activeMenu->w / 2), (renderer.getHeight() / 2) - (activeMenu->h / 2));
				renderer.update(&menuPlate, menuPlateFrame);
				renderer.update(activeMenu, menuFrame);
				if (!player.character.immovable) {
					player.character.immovable = true;
				}
			}
			else {
				if (player.character.immovable) {
					player.character.immovable = false;
				}
			}
			renderer.render();
			
		}
		mainTheme.run();
        
		
    }
	mainTheme.stop();
	launch = false;
}