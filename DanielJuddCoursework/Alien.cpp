#include "Alien.h"
void Alien::setPlayerHealth(int health)
{
	m_health = health;
}
int Alien::getPlayerHealth()
{
	return m_health;
}

bool Alien::moveAlien(Vector2 gameSize)
{
	if (m_movingRight)
	{
		move(1, 0);
	}
	else
	{
		move(-1, 0);
	}

	if (m_position.x == 0 || m_position.x == gameSize.x - 2)
	{	
		if (m_movingRight)
		{
			move(-1, 0);
		}
		else
		{
			move(1, 0);
		}
		return true;
	}

	return false;
}

void Alien::switchDirection()
{
	m_movingRight = !m_movingRight;
}


