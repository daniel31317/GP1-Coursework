#pragma once
#include "GameWindow.h"
#include "Alien.h"
#include "Player.h"
#include "Menu.h"
#include "GameState.h"
#include "ScreenBuffer.h"
#include <memory>
#include <algorithm>


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

	std::unique_ptr<ScreenBuffer> frontBuffer;
	std::unique_ptr <ScreenBuffer> backBuffer;

public:
	GameSource();
	~GameSource();
	void initialiseGame();
	void processInput();
	void updateGame();
	void updateBuffer();
	void swapBuffers();
	void drawGame();
	void gameLoop();


};

