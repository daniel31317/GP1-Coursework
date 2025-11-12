#include "Player.h"
Player::Player() : GameObject()
{
	m_missile = Missile(0,0,'!');
}
Player::Player(int xPos, int yPos, char body, int health) : GameObject(xPos, yPos, body), m_health(health)
{
	m_missile = Missile(xPos, yPos, '!');
}


void Player::processInput()
{
	//A is pressed
	if (GetKeyState(65) & 0x8000 && position.x > 1)
	{
		move(-1, 0);
	}
	//D is pressed
	else if (GetKeyState(68) & 0x8000 && position.x < 79)
	{
		move(1, 0);
	}
	//Space is pressed
	if (GetKeyState(32) & 0x8000)
	{
		m_missile.fireMissile(position);
	}
}
void Player::update()
{
	m_missile.update();
}
