#pragma once
#include "GameWindow.h"
#include "Alien.h"
#include "Player.h"
#include "Menu.h"
#include "GameState.h"

class GameSource
{
private:

	GameState gameState = STARTMENU;
	Menu mainMenu;

	bool m_runLoop = true;

	const int m_width = 80;
	const int m_height = 30;
	GameWindow m_gameWindow;

	GameObject ground;
	Player player;

	const int NUMBER_OF_ALIENS = 20;
	const int NUMBER_OF_BARRIERS = 20;
	Alien* aliens = new Alien[NUMBER_OF_ALIENS];
	GameObject* barriers = new GameObject[NUMBER_OF_BARRIERS];

public:
	GameSource();
	~GameSource();
	void initialiseGame();
	void processInput();
	void updateGame();
	void drawGame();
	void gameLoop();


};

