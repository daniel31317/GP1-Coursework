#include "Player.h"
Player::Player() : GameObject()
{
	m_missile = Missile(0,0,'!', true);
}
Player::Player(int xPos, int yPos, char body, int health, bool isGameSpaceInvaders) : GameObject(xPos, yPos, body), m_lives(health), m_isSpaceInvaders(isGameSpaceInvaders)
{
	m_missile = Missile(xPos, yPos, '!', true);
}


void Player::processInput()
{
	//Space invaders input
	if (m_isSpaceInvaders)
	{
		//A is pressed
		if (GetKeyState(65) & 0x8000 && m_position.x > 1)
		{
			move(-1, 0);
		}
		//D is pressed
		else if (GetKeyState(68) & 0x8000 && m_position.x < 79)
		{
			move(1, 0);
		}
		//Space is pressed
		if (GetKeyState(32) & 0x8000)
		{
			m_missile.fireMissile(m_position);
		}
	}
	//Frogger Input
	else
	{
		//W is pressed
		if (GetKeyState(87) & 0x8000 && m_position.y > 0)
		{
			move(0, -1);
			m_body = '^';
		}
		//S is pressed
		else if (GetKeyState(83) & 0x8000 && m_position.y < 29)
		{
			move(0, 1);
			m_body = 'v';
		}
		//A is pressed
		else if (GetKeyState(65) & 0x8000 && m_position.x > 0)
		{
			move(-1, 0);
			m_body = '<';
		}
		//D is pressed
		else if (GetKeyState(68) & 0x8000 && m_position.x < 79)
		{
			move(1, 0);
			m_body = '>';
		}
	}
	
}
void Player::update()
{
	m_missile.update();
}
