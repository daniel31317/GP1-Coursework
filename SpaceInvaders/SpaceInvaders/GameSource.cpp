#include "GameSource.h"

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
	mainMenu = Menu();

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


void GameSource::gameLoop()
{
	while (m_runLoop)
	{
		switch (gameState)
		{
			case STARTMENU:
				gameState = mainMenu.RunMenu();
				break;
			case GAMERUNNING:
				processInput();
				updateGame();
				updateBuffer();
				swapBuffers();
				drawGame();
				break;
			case QUITGAME:
				m_runLoop = false;
				break;
			default: std::cout << "Unknown game state";
				break; 
		}
	}
	
}


