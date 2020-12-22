#include "GameState.h"

bool GameState::isRunning()
{
	return !quit;
}

bool GameState::inGame()
{
	return gameplayState;
}

void GameState::quitGame()
{
	quit = true;
}

void GameState::newGame()
{
	initializeGame();
}

void GameState::loadGame()
{
	initializeGame();
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

void GameState::saveGame()
{
	playerMenu->setActiveMenu(nullptr);

	std::ofstream saveFile("save1");
	boost::archive::text_oarchive out(saveFile);
	out << *tileMap << *entityMap << *player;
}

void GameState::initializeGame()
{
	gameplayState = true;
	player->character.immovable = false;

	mainMenu->setActiveMenu(nullptr);
	mainMenu->disableMenu();
	playerMenu->setActiveMenu(nullptr);
	playerMenu->enableMenu();
}
