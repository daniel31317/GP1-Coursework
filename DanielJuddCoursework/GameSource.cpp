#include "GameSource.h"
#include <vector>

GameSource::GameSource()
{
	m_gameWindow.setWindow(m_windowSize);

	m_frontBuffer = std::make_unique<ScreenBuffer>(m_gameSize);
	m_backBuffer = std::make_unique<ScreenBuffer>(m_gameSize);

	m_spaceInvadersBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 7), "SpaceInvaders");
	m_froggerBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 14), "Frogger");
	m_quitBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 21), "Quit");
	m_menuBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 14), "Menu");
	m_retryBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 7), "Retry");


	m_windowBorder = std::make_unique<Button>(m_windowSize.x, m_windowSize.y, Vector2(m_windowSize.x / 2, m_windowSize.y / 2), "");
	m_GameBorder = std::make_unique<Button>(m_gameSize.x, m_gameSize.y, Vector2(m_windowSize.x / 2, m_windowSize.y / 2), "");

	m_currentState = &GameSource::runMenu;
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;

	m_barriers.reserve(NUMBER_OF_BARRIERS);
	m_alienManager.setGameSize(m_gameSize);

	m_lastTime = std::chrono::steady_clock::now();
}

void GameSource::runGame()
{
	while (m_runLoop)
	{
		calculateDeltaTime();	
		(this->*m_currentState)();
	}
}


void GameSource::initialiseSpaceInvaders()
{
	m_player = std::make_unique<Player>(m_gameSize.x / 2, m_gameSize.y - 3, '^', ColourCodes[Cyan], true);

	m_alienManager.initialiseAliens();

	m_barriers.clear();
	
	Vector2 barrierPos = Vector2(10, m_gameSize.y - 8);

	for (int i = 0; i < NUMBER_OF_BARRIERS; ++i) 
	{
		if (i % 5 == 0 && i != 0)
		{
			barrierPos.x += 14;
		}
		m_barriers.emplace_back(barrierPos.x + i, barrierPos.y, '#', ColourCodes[Yellow], false);
	}

	//draw score
	if (!m_keepScore)
	{
		m_gameWindow.drawWordToScreen(Vector2(2, m_windowSize.y - 2), "SCORE : ", ColourCodes[Green]);
		m_score = 0;
		updateScore();

		m_gameWindow.drawWordToScreen(m_livesDrawPosition, "LIVES : <3 <3 <3 <3", ColourCodes[Red]);
	}
	

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;

	m_currentState = &GameSource::gameLoop;

	m_keepScore = false;
}

void GameSource::initialiseFrogger()
{
	m_player = std::make_unique<Player>(m_gameSize.x / 2, m_gameSize.y - 3, '^', ColourCodes[Green], false);

	m_barriers.clear();	

	int x = 10;

	for (int i = 0; i < NUMBER_OF_BARRIERS; ++i)
	{
		if (i % 5 == 0 && i != 0)
		{
			x += 14;
		}
		m_barriers.emplace_back(i + x, m_gameSize.y - 8, '=', ColourCodes[Yellow], false);
	}

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameFrogger;
	m_updateBuffer = &GameSource::updateBufferFrogger;

	m_currentState = &GameSource::gameLoop;
}


void GameSource::processInput()
{
	m_player->processInput(m_deltaTime);

	//if esc is pressed
	if (GetKeyState(27) & 0x8000)
	{
		m_currentState = &GameSource::runMenu;
	}
}


void GameSource::updateGameSpaceInvaders()
{
	m_player->update(m_deltaTime);

	int livesBefore = m_player->getPlayerLives();
	m_alienManager.update(m_deltaTime, *m_player, m_barriers);
	if (livesBefore != m_player->getPlayerLives())
	{
		removeLife(livesBefore);
		if (m_player->getPlayerLives() == 0)
		{
			m_currentState = &GameSource::runRetryMenu;
		}
	}

 	Missile* playerMissile = m_player->getMissile();

	if(playerMissile->collisionDetection(*m_alienManager.getAliens()))
	{
		m_alienManager.reduceDelay();
		m_score += playerMissile->getAlienHitScore();
		updateScore();
		if (m_alienManager.getNumberOfAliens() == 0)
		{
			m_keepScore = true;
			m_currentState = &GameSource::initialiseSpaceInvaders;
		}
	}

	SpecialAlien* specialAlien = m_alienManager.getSpecialAlien();

	if(specialAlien->isActive())
	{
		if (playerMissile->collisionDetection(*specialAlien))
		{
			m_score += specialAlien->getScoreForKill();
			specialAlien->kill();
			updateScore();
		}
	}

	playerMissile->collisionDetection(m_barriers);
}

void GameSource::updateBufferSpaceInvaders()
{
	m_backBuffer->setGameObjectAtPos(*m_player);

	m_alienManager.updateBuffer(*m_backBuffer);

	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_barriers[i]);
	}

	if (m_player->getMissile()->isMissileActive())
	{
		m_backBuffer->setGameObjectAtPos(*m_player->getMissile());
	}
}


void GameSource::updateGameFrogger()
{
	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_barriers[i].update(m_deltaTime);
	}
}

void GameSource::updateBufferFrogger()
{
	m_backBuffer->setGameObjectAtPos(*m_player);

	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_barriers[i]);
	}
}


void GameSource::swapBuffers()
{	
	std::swap(m_frontBuffer, m_backBuffer);
	m_backBuffer->clearBuffer();
}


void GameSource::drawGame()
{
	for (int y = 0; y < m_gameSize.y - 2; y++)
	{
		for (int x = 0; x < m_gameSize.x - 2; x++)
		{
			m_gameWindow.drawCharToScreen(Vector2(x + m_gameDrawOffset, y + m_gameDrawOffset), m_frontBuffer->getBufferCell(x, y));
		}
	}
}


void GameSource::updateScore() const
{
	m_gameWindow.drawWordToScreen(m_scoreDrawPosition, std::to_string(m_score), ColourCodes[Green]);
}

void GameSource::removeLife(int previousLives)
{
	Vector2 lifeToRemove = Vector2(m_livesDrawPosition.x + 6, m_livesDrawPosition.y);
	lifeToRemove.x += ((previousLives) * 2) + previousLives - 1;
	m_gameWindow.setCursorPosition(lifeToRemove);
	std::cout << "  ";
	m_player->setPosition(m_gameSize.x / 2, m_gameSize.y - 3);
}



void GameSource::drawGameUI()
{
	m_GameBorder->drawButton(m_gameWindow);
	m_gameWindow.setCursorPosition(2, 1);
	std::cout << "<-- ESC";

}

void GameSource::runMenu()
{
	system("cls");

	m_frontBuffer->clearBuffer();
	m_backBuffer->clearBuffer();

	m_windowBorder->drawButton(m_gameWindow);
	m_spaceInvadersBtn->drawButton(m_gameWindow);
	m_froggerBtn->drawButton(m_gameWindow);
	m_quitBtn->drawButton(m_gameWindow);
	

	//from https://stackoverflow.com/questions/73958407/c-get-users-cursor-position-in-console-cells 
	//and https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events
	//with some additional settings and modifications to get it working with what i needed it to do
		
	HANDLE out = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir;
	DWORD dwRead;
	DWORD oldConsole;

	bool madeChoice = false;

	HandleSettingUpConsoleForMenu(out, oldConsole);

	while (ReadConsoleInput(out, &ir, 1, &dwRead) && dwRead == 1 && !madeChoice)
	{
		//if it is a mouse event
		if (ir.EventType == MOUSE_EVENT)
		{
			//ignore all mouse events which don't involve mouse button presses
			if (ir.Event.MouseEvent.dwEventFlags != 0 && ir.Event.MouseEvent.dwEventFlags != DOUBLE_CLICK)
				continue;

			//if mouse was released
			if (ir.Event.MouseEvent.dwButtonState == 0)
			{
				if (m_spaceInvadersBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::initialiseSpaceInvaders;		
					drawGameUI();
					madeChoice = true;
				}
				else if (m_froggerBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::initialiseFrogger;
					drawGameUI();
					madeChoice = true;
				}
				else if (m_quitBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::quitGame;
					madeChoice = true;
				}
			}
			fflush(stdout);
		}
	}

	//set console to what it was previously
	SetConsoleMode(out, oldConsole);
}

void GameSource::runRetryMenu()
{
	system("cls");

	m_frontBuffer->clearBuffer();
	m_backBuffer->clearBuffer();

	m_windowBorder->drawButton(m_gameWindow);
	m_quitBtn->drawButton(m_gameWindow);
	m_menuBtn->drawButton(m_gameWindow);
	m_retryBtn->drawButton(m_gameWindow);


	//from https://stackoverflow.com/questions/73958407/c-get-users-cursor-position-in-console-cells 
	//and https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events
	//with some additional settings and modifications to get it working with what i needed it to do

	HANDLE out = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir;
	DWORD dwRead;
	DWORD oldConsole;

	bool madeChoice = false;

	HandleSettingUpConsoleForMenu(out, oldConsole);

	while (ReadConsoleInput(out, &ir, 1, &dwRead) && dwRead == 1 && !madeChoice)
	{
		//if it is a mouse event
		if (ir.EventType == MOUSE_EVENT)
		{
			//ignore all mouse events which don't involve mouse button presses
			if (ir.Event.MouseEvent.dwEventFlags != 0 && ir.Event.MouseEvent.dwEventFlags != DOUBLE_CLICK)
				continue;

			//if mouse was released
			if (ir.Event.MouseEvent.dwButtonState == 0)
			{
				if (m_retryBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::initialiseSpaceInvaders;
					drawGameUI();
					madeChoice = true;
				}
				else if (m_menuBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::runMenu;
					madeChoice = true;
				}
				else if (m_quitBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::quitGame;
					madeChoice = true;
				}
			}
			fflush(stdout);
		}
	}

	//set console to what it was previously
	SetConsoleMode(out, oldConsole);
}


void GameSource::HandleSettingUpConsoleForMenu(HANDLE& out, DWORD& oldConsole)
{
	if (out == INVALID_HANDLE_VALUE) 
	{
		ErrorExit("GetStdHandle", out, oldConsole);
	}

	//save the original console mode
	if (!GetConsoleMode(out, &oldConsole)) {
		ErrorExit("GetConsoleMode", out, oldConsole);
	}

	//set console to report mouse events
	if (!SetConsoleMode(out, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT))
	{
		ErrorExit("SetConsoleMode", out, oldConsole);
	}
}

VOID GameSource::ErrorExit(LPCSTR lpszMessage, HANDLE& out, DWORD& oldConsole)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(out, oldConsole);

	std::exit(1);
}


void GameSource::gameLoop()
{
	processInput();
	(this->*m_updateGame)();
	(this->*m_updateBuffer)();
	swapBuffers();
	drawGame();
}

void GameSource::quitGame()
{
	m_runLoop = false;
	system("cls");
}

void GameSource::calculateDeltaTime()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;
	m_deltaTime = deltaTime.count();
}



