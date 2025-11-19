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

	m_Border = std::make_unique<Button>(m_windowSize.x, m_windowSize.y, Vector2(m_windowSize.x / 2, m_windowSize.y / 2), "");

	m_currentState = &GameSource::runMenu;
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;
}
GameSource::~GameSource()
{

}

void GameSource::runGame()
{
	while (m_runLoop)
	{
		(this->*m_currentState)();
	}
}


void GameSource::initialiseSpaceInvaders()
{
	m_player = Player(m_gameSize.x / 2, m_gameSize.y - 2, '^', 10, true);

	//reserve blocks of memory for the vectors
	m_aliens.reserve(NUMBER_OF_ALIENS);
	m_barriers.reserve(NUMBER_OF_ALIENS);

	srand((unsigned int)time(0));

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		m_aliens.emplace_back(Alien(rand() % m_gameSize.x, i, 'A'));
	}

	int x = 10;

	for (int i = 0; i < NUMBER_OF_BARRIERS; ++i) 
	{
		if (i % 5 == 0 && i != 0)
		{
			x += 14;
		}
		m_barriers.emplace_back(GameObject(i + x, m_gameSize.y - 8, '='));
	}

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;

	m_currentState = &GameSource::gameLoop;
}

void GameSource::initialiseFrogger()
{
	m_player = Player(m_gameSize.x / 2, m_gameSize.y - 2, '^', 10, false);

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameFrogger;
	m_updateBuffer = &GameSource::updateBufferFrogger;

	m_currentState = &GameSource::gameLoop;
}


void GameSource::processInput()
{
	m_player.processInput();
}


void GameSource::updateGameSpaceInvaders()
{
	m_player.update();
	m_player.getMissile()->missileCollisionDetection(m_aliens, m_barriers);
}

void GameSource::updateBufferSpaceInvaders()
{
	m_backBuffer->setGameObjectAtPos(m_player);

	for (int i = 0; i < m_aliens.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_aliens[i]);
	}

	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_barriers[i]);
	}

	if (m_player.getMissile()->isMissileActive())
	{
		m_backBuffer->setGameObjectAtPos(*m_player.getMissile());
	}

	for (int i = 0; i < m_gameSize.x; i++)
	{
		m_backBuffer->setChar('_', i, m_gameSize.y - 1);
	}
}


void GameSource::updateGameFrogger()
{
	m_player.update();
}

void GameSource::updateBufferFrogger()
{
	m_backBuffer->setGameObjectAtPos(m_player);
}







void GameSource::swapBuffers()
{	
	std::swap(m_frontBuffer, m_backBuffer);
	m_backBuffer->clearBuffer();
}


void GameSource::drawGame()
{
	for (int y = 0; y < m_gameSize.y; y++)
	{
		for (int x = 0; x < m_gameSize.x; x++)
		{
			m_gameWindow.setCursorPosition(x + m_gameDrawOffset, y + m_gameDrawOffset);
			std::cout << m_frontBuffer->getChar(x, y);
		}
	}
}

void GameSource::runMenu()
{
	system("cls");

	m_Border->drawButton(m_gameWindow);
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
					madeChoice = true;
				}
				else if (m_froggerBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::initialiseFrogger;
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

	ExitProcess(0);
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


