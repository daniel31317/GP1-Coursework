#include "GameSource.h"
#include <vector>

GameSource::GameSource()
{
	//set up window
	m_gameWindow.setWindow(m_windowSize);

	//create buffers
	m_frontBuffer = std::make_unique<ScreenBuffer>(m_gameSize);
	m_backBuffer = std::make_unique<ScreenBuffer>(m_gameSize);

	//make buttons
	m_spaceInvadersBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 6), "SpaceInvaders", ColourCodes[Green], ColourCodes[Green]);
	m_froggerBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 13), "Frogger", ColourCodes[Pink], ColourCodes[Pink]);
	m_controlsBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 20), "Controls", ColourCodes[Blue], ColourCodes[Blue]);
	m_quitBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 27), "Quit", ColourCodes[Red], ColourCodes[Red]);
	m_menuBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 14), "Menu", ColourCodes[Blue], ColourCodes[Blue]);
	m_retryBtn = std::make_unique<Button>(19, 5, Vector2(m_windowSize.x / 2, 7), "Retry", ColourCodes[Green], ColourCodes[Green]);
	
	//set up borders
	m_windowBorder = std::make_unique<Button>(m_windowSize.x, m_windowSize.y, Vector2(m_windowSize.x / 2, m_windowSize.y / 2), "", ColourCodes[White], ColourCodes[White]);
	m_GameBorder = std::make_unique<Button>(m_gameSize.x + 2, m_gameSize.y + 2, Vector2(m_windowSize.x / 2, m_windowSize.y / 2), "", ColourCodes[White], ColourCodes[White]);

	//initial function pointers
	m_currentState = &GameSource::runMenu;
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;

	//reserve memory for vectors
	//https://www.geeksforgeeks.org/cpp/using-stdvectorreserve-whenever-possible/
	m_barriers.reserve(NUMBER_OF_BARRIERS);
	m_froggerTopBorder.reserve(NUMBER_OF_TOP_BORDER);
	m_alienManager.setGameSize(m_gameSize);

	//initial time
	m_lastTime = std::chrono::steady_clock::now();
}

void GameSource::runGame()
{
	//main loop if the while loop finishes the GameSource goes out of scope
	while (m_runLoop)
	{
		calculateDeltaTime();	
		(this->*m_currentState)();
	}
}


void GameSource::initialiseSpaceInvaders()
{
	m_isSpaceInvaders = true;

	//create player
	m_player = std::make_unique<Player>(12, m_gameSize.y - 3, '^', ColourCodes[Cyan], m_isSpaceInvaders);

	//make aliens
	m_alienManager.initialiseAliens();

	//create barriers
	m_barriers.clear();
	
	placeRowOfBarriers(5, 4, 10, 14, m_gameSize.y - 6, false, 0.0f, ColourCodes[Yellow]);

	//if the aliens get to this position they win
	m_alienWinPositionY = m_gameSize.y - 5;

	//draw score
	if (!m_keepScore)
	{
		m_gameWindow.drawWordToScreen(Vector2(2, m_windowSize.y), "SCORE : ", ColourCodes[Green]);
		m_score = 0;
		updateScore();

		m_gameWindow.drawWordToScreen(m_livesDrawPosition, "LIVES : <3 <3 <3 <3", ColourCodes[Red]);
	}
	
	//draw ui
	drawGameUI();

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameSpaceInvaders;
	m_updateBuffer = &GameSource::updateBufferSpaceInvaders;

	m_currentState = &GameSource::gameLoop;
}

void GameSource::initialiseFrogger()
{
	m_isSpaceInvaders = false;

	//make player
	m_player = std::make_unique<Player>(m_gameSize.x / 2, m_gameSize.y - 3, '^', ColourCodes[Green], m_isSpaceInvaders);

	//set the highest y pos
	m_player->setHighestYPosition(m_player->getPosition().y);

	//make frogger barriers
	createFroggerBarriers();

	//ui
	drawGameUI();
	drawTimer();

	//reset win points
	m_remianingFroggerWinPointsX = m_froggerWinPointsX;

	//timer reset
	m_lastTimerBarUnits = 20;

	//clear the win objects
	m_froggerWinObjects.clear();

	//set function pointers for game loop for specific game
	m_updateGame = &GameSource::updateGameFrogger;
	m_updateBuffer = &GameSource::updateBufferFrogger;

	m_currentState = &GameSource::gameLoop;
}

void GameSource::createFroggerBarriers()
{
	 m_barriers.clear();

	int y = m_gameSize.y - 6;

	//first set of barriers
	placeRowOfBarriers(5, 4, 10, 15, y, false, 0.25f, ColourCodes[Yellow]);
	y--;
	placeRowOfBarriers(5, 4, 10, 15, y, true, 0.25f, ColourCodes[Blue]);
	y--;
	placeRowOfBarriers(3, 10, 0, 5, y, false, 0.125f, ColourCodes[Grey]);
	y--;
	placeRowOfBarriers(10, 3, 16, 15, y, true, 0.5f, ColourCodes[Pink]);
	y--;
	placeRowOfBarriers(5, 4, 15, 15, y, false, 0.25f, ColourCodes[Red]);

	//second set of barriers
	y -= 4;
	placeRowOfBarriers(5, 4, 10, 15, y, true, 0.25f, ColourCodes[DarkPink]);
	y--;
	placeRowOfBarriers(3, 10, 0, 5, y, true, 0.125f, ColourCodes[DarkCyan]);
	y--;
	placeRowOfBarriers(5, 4, 10, 15, y, false, 0.25f, ColourCodes[Cyan]);
	y--;
	placeRowOfBarriers(10, 3, 16, 15, y, false, 0.5f, ColourCodes[White]);
	y--;
	placeRowOfBarriers(5, 4, 15, 15, y, true, 0.25f, ColourCodes[DarkRed]);

	//third set of barriers
	y -= 4;
	placeRowOfBarriersWithWater(5, 15, y, false, 0.25f);
	y--;
	placeRowOfBarriersWithWater(6, 13, y, true, 0.25f);
	y--;
	placeRowOfBarriersWithWater(3, 5, y, false, 0.125f);
	y--;
	placeRowOfBarriersWithWater(8, 10, y, true, 0.5f);
	y--;
	placeRowOfBarriersWithWater(5, 10, y, false, 0.3f);
	y--;


	//create the top border of the frogger world
	m_froggerTopBorder.clear();

	for (int x = 0; x < m_gameSize.x; x++)
	{
		bool isWinPoint = false;
		for(int i = 0; i < m_froggerWinPointsX.size(); i++)
		{
			if(x == m_froggerWinPointsX[i])
			{
				isWinPoint = true;
				break;
			}
		}

		if(isWinPoint)
		{
			//remove the last point as we will replace it
			//https://gist.github.com/florianvazelle/e2902878ddf460d0d5986abd303f7771
			m_froggerTopBorder.pop_back();
			m_froggerTopBorder.emplace_back(x - 2, y, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x - 2, y - 1, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x - 2, y - 2, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x - 1, y - 2, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x, y - 2, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x + 1, y - 2, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x + 2, y - 2, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x + 2, y - 1, '-', ColourCodes[White], true, true, 0.0f);
			m_froggerTopBorder.emplace_back(x + 2, y, '-', ColourCodes[White], true, true, 0.0f);
			x += 2;
		}
		else
		{
			m_froggerTopBorder.emplace_back(x, y, '-', ColourCodes[White], true, true, 0.0f);
		}
	}


}


void GameSource::placeRowOfBarriersWithWater(int barrierSize, int gapBetweenBarriers, int yPos, bool movingRight, float moveDelay)
{
	for (int i = 0; i < m_gameSize.x; i++)
	{
		//these conditions need to met for a barrier to be placed
		if (i % (barrierSize + gapBetweenBarriers) == 0 && i != 0)
		{
			//make barrier
			for (int j = 0; j < barrierSize; j++)
			{
				m_barriers.emplace_back(i + j, yPos, '=', ColourCodes[DarkYellow], movingRight, false, moveDelay);
			}
			//add barrier size to i so it keeps going
			i += barrierSize - 1;
		}
		else //if not placing barrier then we are placing water
		{
			m_barriers.emplace_back(i, yPos, '~', ColourCodes[DarkBlue], movingRight, true, moveDelay);
		}
	}
}

//places a row of barriers across the screen with gaps
void GameSource::placeRowOfBarriers(int barrierSize, int amount, int initialGap, int gapBetween, int yPos, bool movingRight, float moveDelay, WORD colour)
{
	int x = initialGap;
	for (int i = 0; i < amount * barrierSize; i++)
	{
		if (i % barrierSize == 0 && i != 0)
		{
			x += gapBetween;
		}
		m_barriers.emplace_back(i + x, yPos, '=', colour, movingRight, true, moveDelay);
	}
}


void GameSource::processInput()
{
	m_player->processInput(m_deltaTime);

	//if esc is pressed quit game to menu
	if (GetKeyState(27) & 0x8000)
	{
		m_currentState = &GameSource::runMenu;
	}

	//reset game if R is pressed
	if (GetKeyState(82) & 0x8000)
	{
		if(m_isSpaceInvaders)
		{
			m_currentState = &GameSource::initialiseSpaceInvaders;
		}
		else
		{
			m_currentState = &GameSource::initialiseFrogger;
		}
	}
}


void GameSource::updateGameSpaceInvaders()
{
	m_player->update(m_deltaTime);

	//get the lives before
	int livesBefore = m_player->getPlayerLives();

	//we then update the aliens which has its alien missile player detection
	m_alienManager.update(m_deltaTime, *m_player, m_barriers);

	//if the player was hit by the aliens missile then lose a life and handle 0 lioves
	if (livesBefore != m_player->getPlayerLives())
	{
		removeLife(livesBefore);
		if (m_player->getPlayerLives() == 0)
		{
			m_currentState = &GameSource::runRetryMenu;
		}
	}

	//check for lose condition
	if (m_alienManager.getLowestAlienY() == m_alienWinPositionY)
	{
		m_currentState = &GameSource::runRetryMenu;
	}

	//get pointer to players missile
 	Missile* playerMissile = m_player->getMissile();

	//if the missile collides with an alien
	if(playerMissile->collisionDetection(*m_alienManager.getAliens()))
	{
		//handle score and making aliens faster
		m_alienManager.reduceDelay();
		m_score += playerMissile->getAlienHitScore();
		updateScore();
		if (m_alienManager.getNumberOfAliens() == 0)
		{
			m_keepScore = true;
			m_currentState = &GameSource::initialiseSpaceInvaders;
		}
	}

	//handle missile collision detection with speial alien
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

	//barrier collision
	playerMissile->collisionDetection(m_barriers);
}


//set all game objects to the buffer
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
	//if the player has reached a higher y point than previous give score
	if(m_player->getPosition().y < m_player->getHighestYPosition())
	{
		m_player->setHighestYPosition(m_player->getPosition().y);
		m_score += 10;
		updateScore();
	}


	//get lives before collision detection with barriers
	int livesBefore = m_player->getPlayerLives();

	//we do update timer since if its zero we lose a life
	updateTimer();

	//update barriers and do collision checks
	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_barriers[i].update(m_deltaTime);
		m_barriers[i].playerCollision(*m_player);
	}

	//check for collision with the top border since if we touch this its over
	for (int i = 0; i < m_froggerTopBorder.size(); i++)
	{
		m_froggerTopBorder[i].playerCollision(*m_player);
	}

	
	checkFroggerWinConditions();

	//if we have lost a life handle udpating ui and loss conditions
	if (livesBefore != m_player->getPlayerLives())
	{
		removeLife(livesBefore);
		drawTimer();
		if (m_player->getPlayerLives() == 0)
		{
			m_currentState = &GameSource::runRetryMenu;
		}
	}
}


//set all objects on screen to the buffer
void GameSource::updateBufferFrogger()
{
	for (int i = 0; i < m_barriers.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_barriers[i]);
	}

	for (int i = 0; i < m_froggerTopBorder.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_froggerTopBorder[i]);
	}

	m_backBuffer->setGameObjectAtPos(*m_player);

	for(int i = 0; i < m_froggerWinObjects.size(); i++)
	{
		m_backBuffer->setGameObjectAtPos(m_froggerWinObjects[i]);
	}
}

//swap the fornt and back buffer pointers and then clear the back buffer
void GameSource::swapBuffers()
{	
	std::swap(m_frontBuffer, m_backBuffer);
	m_backBuffer->clearBuffer();
}

//draw the front buffer to the screen
void GameSource::drawGame()
{
	for (int y = 0; y < m_gameSize.y; y++)
	{
		for (int x = 0; x < m_gameSize.x; x++)
		{
			m_gameWindow.drawCharToScreen(Vector2(x + m_gameDrawOffset, y + m_gameDrawOffset), m_frontBuffer->getBufferCell(x, y));
		}
	}
}

//updates the score
void GameSource::updateScore() const
{
	m_gameWindow.drawWordToScreen(m_scoreDrawPosition, std::to_string(m_score), ColourCodes[Green]);
}

//remove a life from the player and draw that to the ui
void GameSource::removeLife(int previousLives)
{
	Vector2 lifeToRemove = Vector2(m_livesDrawPosition.x + 6, m_livesDrawPosition.y);
	lifeToRemove.x += ((previousLives) * 2) + previousLives - 1;
	m_gameWindow.setCursorPosition(lifeToRemove);
	std::cout << "  ";
	m_player->setPosition(m_gameSize.x / 2, m_gameSize.y - 3);
}


//draws the ui to the screen
void GameSource::drawGameUI()
{
	m_GameBorder->drawButton(m_gameWindow);
	m_gameWindow.setCursorPosition(2, 1);
	std::cout << "<-- ESC";

	//if we keep are score (we beat the level) then don't overwrite it
	if (!m_keepScore)
	{
		m_gameWindow.drawWordToScreen(Vector2(2, m_windowSize.y - 2), "SCORE : ", ColourCodes[Green]);
		m_score = 0;
		updateScore();

		m_gameWindow.drawWordToScreen(m_livesDrawPosition, "LIVES : <3 <3 <3 <3", ColourCodes[Red]);
	}

	m_keepScore = false;

}

//draw the timer to the screen
void GameSource::drawTimer()
{
	m_lastTimerBarUnits = 20;
	m_currentFroggerTime = m_froggerTimeLimit;
	m_gameWindow.drawWordToScreen(m_timerDrawPosition, "TIME : [][][][][][][][][][]", ColourCodes[Red]);
}

//update the timer every three seconds by removing one of the brackets the total time is 60s
void GameSource::updateTimer()
{
	m_currentFroggerTime -= m_deltaTime;
	int m_thisTimeBarUnits = static_cast<int>(ceil(m_currentFroggerTime / 3.f));
	if (m_thisTimeBarUnits < m_lastTimerBarUnits)
	{
		m_gameWindow.setCursorPosition(m_timerDrawPosition.x + 7 + m_thisTimeBarUnits, m_timerDrawPosition.y);
		std::cout << ' ';
		m_lastTimerBarUnits = m_thisTimeBarUnits;
		if (m_thisTimeBarUnits == 0)
		{
			m_player->loseLife();
		}
	}
}

void GameSource::checkFroggerWinConditions()
{
	Vector2 playerPos = m_player->getPosition();

	//if we are not at the top dont check
	if(playerPos.y != 2)
	{
		return;
	}

	//check all remaning points and if the player is within range of a valid forgger win point draw that player and add score
	//if it is not (the player has already finshed there) then lose a life
	for (int i = 0; i < m_froggerWinPointsX.size(); i++)
	{
		if (m_player->getPosition().x >= m_froggerWinPointsX[i] - 1 && m_player->getPosition().x <= m_froggerWinPointsX[i] + 1)
		{
			if(std::find(m_remianingFroggerWinPointsX.begin(), m_remianingFroggerWinPointsX.end(), m_froggerWinPointsX[i]) == m_remianingFroggerWinPointsX.end())
			{
				m_player->loseLife();	
				return;
			}
			m_score += 50;
			m_score += m_lastTimerBarUnits * 10;
			drawTimer();
			updateScore();

			auto it = std::remove(m_remianingFroggerWinPointsX.begin(), m_remianingFroggerWinPointsX.end(), m_froggerWinPointsX[i]);

			m_remianingFroggerWinPointsX.erase(it, m_remianingFroggerWinPointsX.end());

			if(m_remianingFroggerWinPointsX.size() == 0)
			{
				m_keepScore = true;
				m_currentState = &GameSource::initialiseFrogger;
				m_score += 1000;
			}

			m_froggerWinObjects.emplace_back(m_froggerWinPointsX[i], 1, 'v', ColourCodes[Green]);
			m_player->setPosition(m_gameSize.x / 2, m_gameSize.y - 2);
			m_player->setHighestYPosition(m_player->getPosition().y);
			return;
		}
	}
}

void GameSource::runMenu()
{
	//clear buffers and screen
	system("cls");

	m_frontBuffer->clearBuffer();
	m_backBuffer->clearBuffer();

	//draw buttons
	m_windowBorder->drawButton(m_gameWindow);
	m_spaceInvadersBtn->drawButton(m_gameWindow);
	m_froggerBtn->drawButton(m_gameWindow);
	m_controlsBtn->drawButton(m_gameWindow);
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
				else if (m_controlsBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::runControlsMenu;
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
	//clear buffers and screen
	system("cls");

	m_frontBuffer->clearBuffer();
	m_backBuffer->clearBuffer();

	//draw buttons
	m_windowBorder->drawButton(m_gameWindow);
	m_quitBtn->drawButton(m_gameWindow);
	m_menuBtn->setPosition(m_windowSize.x / 2, 17);
	m_menuBtn->drawButton(m_gameWindow);
	m_retryBtn->drawButton(m_gameWindow);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x / 2 - 1, 3), "GAME OVER", ColourCodes[DarkRed]);

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
					m_currentState = m_isSpaceInvaders ? &GameSource::initialiseSpaceInvaders : &GameSource::initialiseFrogger;				
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

void GameSource::runControlsMenu()
{
	//clear buffers and screen
	system("cls");

	m_frontBuffer->clearBuffer();
	m_backBuffer->clearBuffer();

	//draw buttons
	m_windowBorder->drawButton(m_gameWindow);
	m_menuBtn->setPosition(m_windowSize.x / 2, 27);
	m_menuBtn->drawButton(m_gameWindow);

	//write controls to screen
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x / 2 - 1, 3), "CONTROLS", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(10, 5), "SPACE INVADERS", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(10, 7), "Move Left - A or <", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(10, 9), "Move Right - D or >", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(10, 11), "Fire Laser - SPACE", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(10, 13), "Reset - R", ColourCodes[White]);


	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 5), "FROGGER", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 7), "Move Left - A or <", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 9), "Move Right - D or >", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 11), "Move Up - W or ^", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 13), "Move Down - S or v", ColourCodes[White]);
	m_gameWindow.drawWordToScreen(Vector2(m_gameSize.x - 22, 15), "Reset - R", ColourCodes[White]);

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
				if (m_menuBtn->buttonInput(ir.Event.MouseEvent.dwMousePosition.X, ir.Event.MouseEvent.dwMousePosition.Y))
				{
					m_currentState = &GameSource::runMenu;
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


//main loop for both games
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


//gets the time now and compares to the previous time to give delta time in seconds
void GameSource::calculateDeltaTime()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;
	m_deltaTime = deltaTime.count();
}



