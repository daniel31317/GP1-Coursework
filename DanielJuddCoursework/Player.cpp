#include "Player.h"

//constructors
Player::Player() : GameObject(), m_missile(0, 0, '|', ColourCodes[Pink], true)
{
	
}
Player::Player(int xPos, int yPos, char body, WORD colour, bool isGameSpaceInvaders) : GameObject(xPos, yPos, body, colour), m_isSpaceInvaders(isGameSpaceInvaders), m_missile(xPos, yPos, '|', ColourCodes[Pink], true)
{
	
}


void Player::processInput(float deltaTime)
{
	//Space invaders input
	if (m_isSpaceInvaders)
	{
		//Space is pressed
		if (GetKeyState(32) & 0x8000)
		{
			m_missile.fireMissile(m_position);
		}

		m_moveDelta += deltaTime;

		if(m_moveDelta < m_moveDelay)
		{
			return;
		}



		//A or left arrow is pressed
		if ((GetKeyState(65) & 0x8000 || GetKeyState(37) & 0x8000) && m_position.x > 0)
		{
			move(-1, 0);
			m_moveDelta = 0;
		}
		//D or right arrow is pressed
		else if ((GetKeyState(68) & 0x8000 || GetKeyState(39) & 0x8000) && m_position.x < 78)
		{
			move(1, 0);
			m_moveDelta = 0;
		}
		
	}
	//Frogger Input
	else
	{
		m_moveDelta += deltaTime;

		if (m_moveDelta < m_moveDelay)
		{
			return;
		}

		//W or up arrow is pressed
		if ((GetKeyState(87) & 0x8000 || GetKeyState(38) & 0x8000) && m_position.y > 0)
		{
			move(0, -1);
			m_body = '^';
			m_moveDelta = 0;
		}
		//S or down arrow is pressed
		else if ((GetKeyState(83) & 0x8000 || GetKeyState(40) & 0x8000) && m_position.y < 28)
		{
			move(0, 1);
			m_body = 'v';
			m_moveDelta = 0;
		}
		//A or left arrow is pressed
		else if ((GetKeyState(65) & 0x8000 || GetKeyState(37) & 0x8000) && m_position.x > 0)
		{
			move(-1, 0);
			m_body = '<';
			m_moveDelta = 0;
		}
		//D or right arrow is pressed
		else if ((GetKeyState(68) & 0x8000 || GetKeyState(39) & 0x8000) && m_position.x < 78)
		{
			move(1, 0);
			m_body = '>';
			m_moveDelta = 0;
		}
	}
	
}


void Player::update(float deltaTime)
{
	m_missile.update(deltaTime);
}
