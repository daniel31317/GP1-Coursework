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
#include "AlienManager.h"
#include "Colour.h"


class GameSource
{
private:

	bool m_runLoop = true;

	bool m_isSpaceInvaders = true;

	const Vector2 m_windowSize = Vector2(85, 35);
	const Vector2 m_gameSize = Vector2(81, 31);
	const int m_gameDrawOffset = 3;
	const Vector2 m_scoreDrawPosition = Vector2(10, 33);
	const Vector2 m_livesDrawPosition = Vector2(64, 33);
	
	const int NUMBER_OF_BARRIERS = 20;

	int m_score = 0;

	int m_alienWinPositionY = 0;

	bool m_keepScore = false;

	GameWindow m_gameWindow;

	GameObject m_ground;
	std::unique_ptr<Player> m_player;
	AlienManager m_alienManager;

	float m_deltaTime = 0;
	std::chrono::steady_clock::time_point m_lastTime;

	std::vector<Barrier> m_barriers;

	std::unique_ptr<ScreenBuffer> m_frontBuffer;
	std::unique_ptr<ScreenBuffer> m_backBuffer;

	std::unique_ptr<Button> m_spaceInvadersBtn;
	std::unique_ptr<Button> m_froggerBtn;
	std::unique_ptr<Button> m_quitBtn;
	std::unique_ptr<Button> m_menuBtn;
	std::unique_ptr<Button> m_retryBtn;

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
	void initialiseSpaceInvaders();
	void initialiseFrogger();

	void createFroggerBarriers();
	void placeRowOfBarriersWithWater(int barrierSize,int gapBetweenBarriers, int yPos, bool movingRight, float moveDelay);
	
	void runGame();

	void gameLoop();

	void processInput();

	void updateGameSpaceInvaders();
	void updateBufferSpaceInvaders();
	
	void updateGameFrogger();
	void updateBufferFrogger();

	void swapBuffers();
	void drawGame();

	void updateScore() const;
	void removeLife(int prevLives);
	void drawGameUI();

	void runMenu();

	void runRetryMenu();

	void quitGame();

	void calculateDeltaTime();
};

