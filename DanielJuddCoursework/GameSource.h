#pragma once
#include "GameWindow.h"
#include "Alien.h"
#include "Player.h"
#include "ScreenBuffer.h"
#include "Button.h"
#include "Barrier.h"
#include <memory>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <chrono>

class GameSource
{
private:

	bool m_runLoop = true;

	const Vector2 m_windowSize = Vector2(85, 35);
	const Vector2 m_gameSize = Vector2(81, 31);
	const int m_gameDrawOffset = 3;
	const Vector2 m_scoreDrawPosition = Vector2(9, 33);
	const Vector2 m_livesDrawPosition = Vector2(65, 33);
	const int NUMBER_OF_ALIENS = 45;
	const int NUMBER_OF_BARRIERS = 20;

	const float m_maxAlienMoveDelay = 1.5f;
	float m_currentAlienMoveDelay = m_maxAlienMoveDelay;
	float m_currentAlienMoveDelta = 0;

	const int m_maxLives = 4;
	int m_currentLives = m_maxLives;


	int score = 0;

	GameWindow m_gameWindow;

	GameObject m_ground;
	Player m_player;

	float m_deltaTime = 0;
	std::chrono::steady_clock::time_point m_lastTime;

	std::vector<Alien> m_aliens;
	std::vector<Barrier> m_barriers;

	std::unique_ptr<ScreenBuffer> m_frontBuffer;
	std::unique_ptr<ScreenBuffer> m_backBuffer;

	std::unique_ptr<Button> m_spaceInvadersBtn;
	std::unique_ptr<Button> m_froggerBtn;
	std::unique_ptr<Button> m_quitBtn;

	std::unique_ptr<Button> m_windowBorder;
	std::unique_ptr<Button> m_GameBorder;

	//stores current state of the game as a function pointer
	void (GameSource::*m_currentState)();

	void (GameSource::*m_updateGame)();
	void (GameSource::*m_updateBuffer)();

	VOID ErrorExit(LPCSTR, HANDLE& out, DWORD& oldConsole);
	void HandleSettingUpConsoleForMenu(HANDLE& out, DWORD& oldConsole);

public:
	GameSource();
	~GameSource();
	void initialiseSpaceInvaders();
	void initialiseFrogger();
	
	void runGame();

	void gameLoop();

	void processInput();

	void updateGameSpaceInvaders();
	void updateBufferSpaceInvaders();
	
	void updateGameFrogger();
	void updateBufferFrogger();

	void swapBuffers();
	void drawGame();

	void updateScore();
	void removeLife();
	void drawGameUI();

	void runMenu();

	void quitGame();

	void calculateDeltaTime();


};

