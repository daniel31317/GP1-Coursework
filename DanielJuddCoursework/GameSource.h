#pragma once
#include "GameWindow.h"
#include "Alien.h"
#include "Player.h"
#include "ScreenBuffer.h"
#include <memory>
#include <algorithm>


class GameSource
{
private:

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
	std::unique_ptr<ScreenBuffer> backBuffer;

	//stores current state of the game as a function pointer
	void (GameSource::*m_currentState)();

public:
	GameSource();
	~GameSource();
	void initialiseGame();
	
	void runGame();

	void gameLoop();
	void processInput();
	void updateGame();
	void updateBuffer();
	void swapBuffers();
	void drawGame();

	void runMenu();

	void quitGame();


};

