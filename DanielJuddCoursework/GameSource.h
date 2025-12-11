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

	//actual game running exit condition if false
	bool m_runLoop = true;

	bool m_isSpaceInvaders = true;

	const Vector2 m_windowSize = Vector2(85, 35);
	const Vector2 m_gameSize = Vector2(79, 29);
	//there is a draw offset since the game size is less than window size
	const int m_gameDrawOffset = 3;

	const Vector2 m_scoreDrawPosition = Vector2(10, 33);
	const Vector2 m_livesDrawPosition = Vector2(64, 33);
	const Vector2 m_timerDrawPosition = Vector2(56, 1);

	//frogger timer
	const float m_froggerTimeLimit = 60.0f;
	float m_currentFroggerTime = m_froggerTimeLimit;
	int m_lastTimerBarUnits = 20;

	const std::vector<int> m_froggerWinPointsX = 
	{
		9, 24, 39, 54, 69
	};

	std::vector<int> m_remianingFroggerWinPointsX = m_froggerWinPointsX;

	std::vector<GameObject> m_froggerWinObjects;
	
	//used for reserving space in vectors
	const int NUMBER_OF_BARRIERS = 640;
	const int NUMBER_OF_TOP_BORDER = 104;

	int m_score = 0;

	int m_alienWinPositionY = 0;

	bool m_keepScore = false;

	GameWindow m_gameWindow;

	
	

	//delta time
	float m_deltaTime = 0;
	std::chrono::steady_clock::time_point m_lastTime;

	//objects in game
	std::vector<Barrier> m_barriers;
	std::vector<Barrier> m_froggerTopBorder;
	std::unique_ptr<Player> m_player;

	//managers
	AlienManager m_alienManager;

	//buffers
	std::unique_ptr<ScreenBuffer> m_frontBuffer;
	std::unique_ptr<ScreenBuffer> m_backBuffer;

	//buttons
	std::unique_ptr<Button> m_spaceInvadersBtn;
	std::unique_ptr<Button> m_froggerBtn;
	std::unique_ptr<Button> m_quitBtn;
	std::unique_ptr<Button> m_menuBtn;
	std::unique_ptr<Button> m_retryBtn;
	std::unique_ptr<Button> m_controlsBtn;

	//buttons with no name but we can use these as borders
	std::unique_ptr<Button> m_windowBorder;
	std::unique_ptr<Button> m_GameBorder;

	//stores current state of the game as a function pointer
	void (GameSource::*m_currentState)();

	//stores which update functions we are doing for each specific game
	void (GameSource::*m_updateGame)();
	void (GameSource::*m_updateBuffer)();


	VOID ErrorExit(LPCSTR, HANDLE& out, DWORD& oldConsole);
	void HandleSettingUpConsoleForMenu(HANDLE& out, DWORD& oldConsole);

public:
	//constructor
	GameSource();

	//initialise games
	void initialiseSpaceInvaders();
	void initialiseFrogger();

	//barrier stuff
	void createFroggerBarriers();
	void placeRowOfBarriersWithWater(int barrierSize,int gapBetweenBarriers, int yPos, bool movingRight, float moveDelay);
	void placeRowOfBarriers(int barrierSize,int amount, int initialGap, int gapBetween, int yPos, bool movingRight, float moveDelay, WORD colour);
	
	//main entry point from main
	void runGame();

	void gameLoop();

	void processInput();

	//buffer updates
	void updateGameSpaceInvaders();
	void updateBufferSpaceInvaders();
	
	//game updates
	void updateGameFrogger();
	void updateBufferFrogger();

	//buffer swaping and drawing
	void swapBuffers();
	void drawGame();

	//ui 
	void updateScore() const;
	void removeLife(int prevLives);
	void drawGameUI();
	void drawTimer();
	void updateTimer();

	void checkFroggerWinConditions();

	//menus
	void runMenu();
	void runRetryMenu();
	void runControlsMenu();

	//exit function
	void quitGame();

	void calculateDeltaTime();
};

