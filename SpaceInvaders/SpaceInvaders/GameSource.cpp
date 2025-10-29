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
	player = Player(m_width / 2, m_height - 2, 'P');
	//we can just use one ground object for it and just loop it in draw and just set the x to 0 since it doesnt matter for the moment
	ground = GameObject(0, m_height - 1, '_');
	mainMenu = Menu();

	srand((unsigned int)time(0));

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		aliens[i] = Alien(rand() % m_width, i, 'A');
	}
	
	for (int i = 0; i < NUMBER_OF_BARRIERS; i++)
	{
		barriers[i] = GameObject(m_width / NUMBER_OF_BARRIERS * i, m_height - 8, 'B');
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

	/*
	//loop through the window "grid"
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			//stores if we have drawn to the m_width, m_height position
			bool drawnToPos = false;
			//check for alien position and draw if true
			for (int i = 0; i < NUMBER_OF_ALIENS; i++)
			{
				if (aliens[i].getPosition() == Vector2(x, y))
				{
					aliens[i].draw();
					drawnToPos = true;
				}
			}

			//check for barrier position and draw if true
			for (int i = 0; i < NUMBER_OF_BARRIERS; i++)
			{
				if (barriers[i].getPosition() == Vector2(x, y))
				{
					barriers[i].draw();
					drawnToPos = true;
				}
			}

			//check for player position and draw if true
			if (player.getPosition() == Vector2(x, y))
			{
				player.draw();
				drawnToPos = true;
			}	

			//check for barrier position and draw if true
			if (ground.getPosition().y == y)
			{
				ground.draw();
				drawnToPos = true;
			}	

			//if we have not drawn to the current position then we draw a space 
			if (!drawnToPos)
			{
				std::cout << " ";
			}
		}
		//go to next line
		std::cout << "\n";
	}
	*/
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


