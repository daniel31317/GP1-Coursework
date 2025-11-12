#pragma once
#include "GameWindow.h"
#include "Alien.h"
#include "Player.h"
#include "ScreenBuffer.h"
#include "Button.h"
#include <memory>
#include <algorithm>
#include <vector>
#include <stdio.h>

class GameSource
{
private:

	bool m_runLoop = true;

	const int m_width = 80;
	const int m_height = 30;
	GameWindow m_gameWindow;

	GameObject m_ground;
	Player m_player;

	const int NUMBER_OF_ALIENS = 20;
	const int NUMBER_OF_BARRIERS = 20;

	std::vector<Alien> m_aliens;
	std::vector<GameObject> m_barriers;

	std::unique_ptr<ScreenBuffer> m_frontBuffer;
	std::unique_ptr<ScreenBuffer> m_backBuffer;

	std::unique_ptr <Button> m_spaceInvadersBtn;
	std::unique_ptr <Button> m_snakeBtn;
	std::unique_ptr <Button> m_quitBtn;
	std::unique_ptr <Button> m_Border;

	//stores current state of the game as a function pointer
	void (GameSource::*m_currentState)();

	VOID ErrorExit(LPCSTR, HANDLE& out, DWORD& oldConsole);
	void HandleSettingUpConsoleForMenu(HANDLE& out, DWORD& oldConsole);

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

