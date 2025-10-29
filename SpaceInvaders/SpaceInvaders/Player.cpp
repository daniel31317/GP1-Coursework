#include "Player.h"
void Player::setPlayerHealth(int health)
{
	m_health = health;
}
int Player::getPlayerHealth()
{
	return m_health;
}
void Player::processInput()
{
	if (GetKeyState(65) & 0x8000 && position.x > 1)
	{
		move(-1, 0);
	}
	else if (GetKeyState(68) & 0x8000 && position.x < 79)
	{
		move(1, 0);
	}
}
