#include "GameSource.h"
#include <vector>

GameSource::GameSource()
{

}
GameSource::~GameSource()
{
	delete aliens;
	delete barriers;
}

void GameSource::initialiseGame()
{
	m_gameWindow.setWindow(m_width, m_height);
	player = Player(m_width / 2, m_height - 2, '^', 10);
	//we can just use one ground object for it and just loop it in draw and just set the x to 0 since it doesnt matter for the moment
	ground = GameObject(0, m_height - 1, '_');

	m_currentState = &GameSource::runMenu;

	srand((unsigned int)time(0));

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		aliens[i] = Alien(rand() % m_width, i, 'A');
	}

	int x = 10;

	for (int i = 0; i < NUMBER_OF_BARRIERS; ++i) 
	{
		if (i % 5 == 0 && i != 0)
		{
			x += 14;
		}
		barriers[i] = GameObject(i + x, m_height - 8, '=');
	}


	frontBuffer = std::make_unique<ScreenBuffer>(m_width, m_height);
	backBuffer = std::make_unique<ScreenBuffer>(m_width, m_height);
}


void GameSource::processInput()
{
	player.processInput();
}


void GameSource::updateGame()
{
	player.update();
	player.getMissile()->missileCollisionDetection(aliens, NUMBER_OF_ALIENS, barriers, NUMBER_OF_BARRIERS);

}

void GameSource::updateBuffer()
{
	backBuffer->setGameObjectAtPos(player);

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		backBuffer->setGameObjectAtPos(aliens[i]);
	}

	for (int i = 0; i < NUMBER_OF_BARRIERS; i++)
	{
		backBuffer->setGameObjectAtPos(barriers[i]);
	}

	if (player.getMissile()->isMissileActive())
	{
		backBuffer->setGameObjectAtPos(*player.getMissile());
	}
}

void GameSource::swapBuffers()
{	
	std::swap(frontBuffer, backBuffer);
	backBuffer->clearBuffer();
}


void GameSource::drawGame()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			m_gameWindow.setCursorPosition(x, y);
			std::cout << frontBuffer->getChar(x, y);
		}
	}
}

void GameSource::runMenu()
{
	system("cls");
	std::cout << "Start Screen:\n";
	std::cout << "1. Player Space Invaders\n";
	std::cout << "2. Quit\n";
	std::cout << "Enter your choice: ";

	int choice;

	bool madeChoice = false;

	while (!madeChoice)
	{
		if (std::cin >> choice)
		{
			if (choice == 1)
			{
				system("cls");
				m_currentState = &GameSource::gameLoop;
				madeChoice = true;
			}
			else if (choice == 2)
			{
				system("cls");
				m_currentState = &GameSource::quitGame;
				madeChoice = true;
			}
			else
			{
				std::cout << "Invalid Choice Please Choose 1 or 2:";
			}
		}
		else //if the player enters a string or char handle it
		{
			std::cout << "Invalid Input Please Try Again: ";
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}

	}
}





void GameSource::gameLoop()
{
	processInput();
	updateGame();
	updateBuffer();
	swapBuffers();
	drawGame();
}

void GameSource::quitGame()
{
	m_runLoop = false;
}

void GameSource::runGame()
{
	while (m_runLoop)
	{
		(this->*m_currentState)();
	}
}

